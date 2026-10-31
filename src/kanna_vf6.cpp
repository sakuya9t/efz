// CKanna::UpdatePattern (0x667570-0x675c7f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CKanna's
// .rdata, which starts with its constructor's folder name (kanna.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CKanna::UpdatePattern()
{
    WORD x8;
    WORD l4;

    if (m_hitstop > 0 || (*m_opponent)->m_freezeTime > 0) {
        return;
    }
    EffectDesc l50;
    l4 = (short)anims[pattern].frames[frame].duration;
    x8 = anims[pattern].frameCount;
    InitEffectDesc((EffectDesc*)&l50);
    switch (pattern) {
    default:
        m_dashMomentum = 0;
        vx = 0.0;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case kWalkForward:
        m_dashMomentum = 0;
        vx = 0.8;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case kWalkBack:
        m_dashMomentum = 0;
        vx = -0.8;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case kCrouch:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case kJump:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            vx = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                    break;
                }
                StartPattern();
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            m_playVoice = 0;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kJumpForward:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            vx = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = 1.5;
            m_playVoice = 0;
        }
        if (frame > 6) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kJumpBack:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            vx = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = -1.5;
            m_playVoice = 0;
        }
        if (frame > 6) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kStandUp:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kCrouchDown:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kFall:
        vy = vy + ay;
        m_patternVar3++;
        if (m_patternVar3 > 0) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            pattern = kLand;
            StartPattern();
        }
        break;
    case kSuperJump:
        vy = vy + ay;
        m_dashMomentum = 0;
        if (m_patternVar1 == 0) {
            vx *= 0.3;
            m_patternVar1++;
        }
        if (vy > 0.4) {
            vy = 0.4;
        }
        if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
            m_airActions++;
            pattern = kAirJump;
            if (m_inputX == facing) {
                pattern = kAirJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (m_inputY == 1) {
            pattern = kFall;
            StartPattern();
            if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                m_airActions++;
                if (m_inputX == facing) {
                    pattern = 0x12;
                }
                if (m_inputX == -facing) {
                    pattern = 0x14;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
        }
        if (m_airActions < 2 && m_sealLevel < 3) {
            if (m_inputX == facing) {
                pattern = 0x11;
                m_airActions++;
                StartPattern();
                m_attackResult = 0;
                break;
            }
            if (m_inputX == -facing) {
                pattern = 0x13;
                m_airActions++;
                StartPattern();
                m_attackResult = 0;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            pattern = kLand;
            StartPattern();
        }
        break;
    case kLand:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kAirJump:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.5;
            vx = 0.0;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpForward:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = 1.5;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpBack:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = -1.5;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case 0x11:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = 2.0;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case 0x12:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = 1.5;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case 0x13:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = -2.0;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case 0x14:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = -1.5;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kResultLoserFall:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            ay = 0.035;
        }
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 2) {
            timer = 0;
            frame = 2;
            m_playSound = 7;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case kHitStandHighLight:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.1;
            if (m_rfBlue != 0) {
                m_rfGauge -= 10.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandHighMedium:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.5;
            if (m_rfBlue != 0) {
                m_rfGauge -= 20.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandHighHeavy:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.8;
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandLowLight:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.1;
            if (m_rfBlue != 0) {
                m_rfGauge -= 10.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandLowMedium:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.5;
            if (m_rfBlue != 0) {
                m_rfGauge -= 20.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandLowHeavy:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.8;
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitCrouchLight:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.1;
            if (m_rfBlue != 0) {
                m_rfGauge -= 10.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kHitCrouchMedium:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.5;
            if (m_rfBlue != 0) {
                m_rfGauge -= 20.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kHitCrouchHeavy:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.8;
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kHitAir:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -2.0) {
                vy = -2.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirHigh:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -4.0) {
                vy = -4.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirHigher:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -6.0) {
                vy = -6.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirCarry:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirLaunch:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirWallBounce:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame > 0 && (char)AtScreenEdge() != 0) {
            pattern = kHitWallBounce;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -2.0) {
                vy = -2.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirHighWallBounce:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame > 0 && (char)AtScreenEdge() != 0) {
            pattern = kHitWallBounce;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -4.0) {
                vy = -4.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirCarryWallBounce:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame > 0 && (char)AtScreenEdge() != 0) {
            pattern = kHitWallBounce;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirLaunchWallBounce:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame > 0 && (char)AtScreenEdge() != 0) {
            pattern = kHitWallBounce;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.032;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitBlownAwayWallBounce:
        if (m_rfBlue != 0) {
            m_rfGauge -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = m_hitVx;
        vy = m_hitVy;
        timer++;
        if ((char)AtScreenEdge() != 0) {
            pattern = kHitWallBounce;
            StartPattern();
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitBlownAway:
        if (m_rfBlue != 0) {
            m_rfGauge -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = m_hitVx;
        vy = m_hitVy;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitWallBounce:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            m_gauge = m_gauge + 0x1e;
            m_patternVar1++;
            m_untechTime = m_untechTime + 0x78;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            m_playSound = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitAirHeavy:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.072;
        }
        if (vy <= 0.0) {
            frame = 1;
            timer = 0;
        }
        if (vy >= 0.0 && frame <= 1) {
            frame = 2;
            timer = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitStandHighHold:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        m_dashMomentum = 0;
        vx = 0.0;
        vy = 0.0;
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandLowHold:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        m_dashMomentum = 0;
        vx = 0.0;
        vy = 0.0;
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitCrouchHold:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        m_dashMomentum = 0;
        vx = 0.0;
        vy = 0.0;
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kHitStandHighPull:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            vx = 2.2;
        }
        vy = 0.0;
        y = 0.0;
        ay = 0.0;
        ax = 0.06;
        vx = vx - ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitStandLowPull:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            vx = 2.2;
        }
        vy = 0.0;
        y = 0.0;
        ay = 0.0;
        ax = 0.06;
        vx = vx - ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kHitCrouchPull:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.6;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            vx = 2.2;
        }
        vy = 0.0;
        y = 0.0;
        ay = 0.0;
        ax = 0.06;
        vx = vx - ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kHitBurn:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x1f3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.032;
        }
        vx += 0.02;
        vy = vy + ay;
        if (vx > 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame--;
            }
        }
        if (y + vy >= 0.0 && frame == 1) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kHitShock:
        if (m_rfBlue != 0) {
            m_rfGauge -= 0.8;
        }
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            m_playSound = 0x1e;
            vy = -0.45;
            vx = -0.1;
            m_patternVar1++;
            m_gauge = m_gauge + 0x1e;
        }
        if (frame == 4 && timer == 0) {
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.032;
        }
        if (vy > 0.0 && frame == 4) {
            frame = 5;
            timer = 0;
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4 && m_patternVar1 < 8) {
                frame = 0;
                m_patternVar1++;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 4) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kEncased:
        if (frame == 0 && timer == 0) {
            if (m_encasedBreakOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_encasedBreakOut = 1;
            }
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            m_playSound = 0x21;
            vy = -1.5;
            vx = -0.8;
            m_gauge = m_gauge + 0x1e;
        }
        vy += 0.04;
        if (frame == 0 && vy + y > 0.0) {
            y = 0.0;
            vy = 0.0;
            timer = 0;
            frame = 1;
            break;
        }
        if (frame == 1) {
            vx += 0.01;
        }
        if (frame == 2 && timer == 0) {
            vx = -2.0;
        }
        if (frame > 1) {
            vx += 0.06;
        }
        if (vx > 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kEncased2:
        if (frame == 0 && timer == 0) {
            if (m_encasedBreakOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_encasedBreakOut = 1;
            }
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            m_playSound = 0x21;
            vy = -1.5;
            vx = -0.8;
            m_gauge = m_gauge + 0x1e;
        }
        vy += 0.04;
        if (frame == 0 && vy + y > 0.0) {
            y = 0.0;
            vy = 0.0;
            timer = 0;
            frame = 1;
            break;
        }
        if (frame == 1) {
            vx += 0.01;
        }
        if (frame == 2 && timer == 0) {
            vx = -2.0;
        }
        if (frame > 1) {
            vx += 0.06;
        }
        if (vx > 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kEncasedAir:
        if (frame == 0 && timer == 0) {
            if (m_encasedBreakOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_encasedBreakOut = 1;
            }
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            m_playSound = 0x21;
            vx = m_hitVx;
            vy = m_hitVy;
            m_gauge = m_gauge + 0x1e;
        }
        vy += 0.04;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kEncasedSpin:
        if (frame == 0 && timer == 0) {
            if (m_encasedBreakOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_encasedBreakOut = 1;
            }
            if (m_patternVar1 == 0) {
                if (m_rfBlue != 0) {
                    m_rfGauge -= 30.0;
                }
                m_playSound = 0x21;
                vx = m_hitVx;
                vy = m_hitVy;
                m_gauge = m_gauge + 0x1e;
                m_patternVar1++;
            }
        }
        vy += 0.06;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            if (m_landHittable != 0) {
                pattern = kKnockdownHittable;
                StartPattern();
            } else {
                pattern = kKnockdown;
                StartPattern();
            }
        }
        break;
    case kFallInDarkness:
        if (frame == 0 && timer == 0) {
            l50.type = 0x1ef;
            l50.x = 60.0;
            l50.y = 40.0;
            l50.screen = 1;
            l50.facing = 1;
            l50.scale = 0;
            l50.layer = 0;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kWakeUp:
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8 - 1) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kKnockdownHittable:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kLyingDown;
                StartPattern();
            }
        }
        break;
    case kKnockdown:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kLyingDown;
                StartPattern();
            }
        }
        break;
    case kLyingDown:
        if (m_hp > 0 && timer > 0x3c && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
            m_dashMomentum = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kWakeUp;
                StartPattern();
            }
        }
        break;
    case kGuardStandLight:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0xa;
            vx = -1.5;
            vy = 0.0;
            y = 0.0;
        }
        vy = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kGuardStandMedium:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0xf;
            vx = -1.8;
            vy = 0.0;
            y = 0.0;
        }
        vy = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kGuardStandHeavy:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0x14;
            vx = -2.3;
            vy = 0.0;
            y = 0.0;
        }
        vy = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kGuardCrouchLight:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0xa;
            vx = -1.5;
            vy = 0.0;
            y = 0.0;
        }
        vy = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kGuardCrouchMedium:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0xf;
            vx = -1.8;
            vy = 0.0;
            y = 0.0;
        }
        vy = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kGuardCrouchHeavy:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0x14;
            vx = -2.3;
            vy = 0.0;
            y = 0.0;
        }
        vy = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            m_cornerPushback = vx;
        } else {
            m_cornerPushback = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kGuardAir:
        if (frame == 0 && timer == 0) {
            vy = -2.6;
            m_gauge = m_gauge + 0xf;
            ay = 0.06;
        }
        vx = -1.2;
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirRecoveryForward:
        vx = 1.0;
        ay = 0.045;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.3;
            l50.type = 8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
        } else {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirRecoveryBack:
        vx = -1.0;
        ay = 0.045;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.3;
            l50.type = 8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
        } else {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 2.0;
            vy = -1.0;
            ay = 0.02;
            m_playVoice = 0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
                break;
            }
        }
        if (frame > 6) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        break;
    case kDashBack:
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vx = -2.0;
            vy = -1.0;
            ay = 0.035;
            m_playVoice = 0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 1;
                break;
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = 2.0;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        m_patternVar3++;
        if (m_patternVar3 > m_airMoveDelay) {
            if (m_inputY == -1 && m_sealLevel < 3 && m_airActions < 2) {
                m_airActions++;
                pattern = kAirJump;
                if (m_inputX == facing) {
                    pattern = kAirJumpForward;
                }
                if (m_inputX == -facing) {
                    pattern = kAirJumpBack;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
            if (m_inputY == 1) {
                pattern = kFall;
                StartPattern();
                if (m_airActions < 2 && m_inputX != 0 && m_sealLevel < 3) {
                    m_airActions++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (m_airActions < 2 && m_sealLevel < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    m_airActions++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = -2.0;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kInstantCharge:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            if (m_rfBlue == 1) {
                m_proration = m_rfGauge * 5.0 + m_proration;
            }
            m_rfGauge = 0.0;
            m_freezeTime = 0x5a;
            FillBackground(0xb0, 3);
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x12;
            l50.type = 1;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 4;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kRecoilGuardStand:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            m_recoilGuardWindow = 0;
            m_cornerPushback = 0.0;
            ax = 0.0;
            l50.type = 8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kRecoilGuardCrouch:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            m_recoilGuardWindow = 0;
            m_cornerPushback = 0.0;
            ax = 0.0;
            l50.type = 8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kRecoilGuardAir:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = (int)(vx * 100.0);
            m_patternVar2 = (int)(vy * 100.0);
            vx = 0.0;
            vy = 0.0;
            if (ay == 0.0) {
                ay = 0.035;
            }
            m_recoilGuardWindow = 0;
            m_cornerPushback = 0.0;
            m_freezeTime = 0x3c;
        }
        if (m_freezeTime == 0 && m_patternVar3 == 0) {
            m_patternVar3++;
            vx = m_patternVar1 * 0.01;
            vy = m_patternVar2 * 0.01;
        }
        if (m_freezeTime == 0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            StopMoving();
            y = 0.0;
            pattern = kRecoilGuardCrouch;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kAirInstantCharge:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = (int)(vx * 100.0);
            m_patternVar2 = (int)(vy * 100.0);
            vx = 0.0;
            vy = 0.0;
            if (m_rfBlue == 1) {
                m_proration = m_rfGauge * 5.0 + m_proration;
            }
            m_rfGauge = 0.0;
            m_freezeTime = 0x5a;
            FillBackground(0xb0, 3);
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x12;
            l50.type = 1;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 4;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kFall;
                vx = m_patternVar1 * 0.01;
                vy = m_patternVar2 * 0.01;
                ay = 0.035;
                StartPattern();
            }
        }
        break;
    case kDashStop:
        vx -= 0.03;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        break;
    case k5A:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5BClose:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1a4;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5BFar:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x1a5;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            l50.keep = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5C:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult == 3) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x23;
            m_hitsLeft = 1;
        }
        if (frame == 6 && timer == 0) {
            l50.type = 0x1a8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k2A:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k2B:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1a6;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k2C:
        if (m_dashMomentum == 0 && frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1 && frame < 3) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0 && m_patternVar1 == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_patternVar1++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kJumpA:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 2) {
            m_airActions++;
            pattern = kAirJump;
            if (m_inputX == facing) {
                pattern = kAirJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (m_inputY == 0 && m_inputX != 0 && frame > 0 && m_attackResult >= 2 && m_airActions < 2 && m_sealLevel < 3) {
            m_airActions++;
            if (m_inputX == facing) {
                pattern = kAirDashForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirDashBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kJumpB:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 2) {
            m_airActions++;
            pattern = kAirJump;
            if (m_inputX == facing) {
                pattern = kAirJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (m_inputY == 0 && m_inputX != 0 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 2) {
            m_airActions++;
            if (m_inputX == facing) {
                pattern = kAirDashForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirDashBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x1a7;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kJumpC:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 2) {
            m_airActions++;
            pattern = kAirJump;
            if (m_inputX == facing) {
                pattern = kAirJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (m_inputY == 0 && m_inputX != 0 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 2) {
            m_airActions++;
            if (m_inputX == facing) {
                pattern = kAirDashForward;
            }
            if (m_inputX == -facing) {
                pattern = kAirDashBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1a9;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kUnused6B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.08;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                if (y + vy < 0.0) {
                    frame--;
                } else {
                    y = 0.0;
                }
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnused6C:
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2) {
            pattern = kJump;
            if (m_inputX == facing) {
                pattern = kJumpForward;
            }
            if (m_inputX == -facing) {
                pattern = kJumpBack;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedJump2C:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = kUnusedJump2CRebound;
            StartPattern();
            StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.sound = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
            pattern = kUnusedJump2CLanding;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kUnusedJump2CRebound:
        ay = 0.042;
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = -1.0;
            vy = -2.4;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kUnusedJump2CLanding:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.sound = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedThrow:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = kUnusedThrowHit;
            (*m_opponent)->m_noAirRecovery = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedThrowHit:
        if (frame == 4 && timer == 0) {
            DealDamage(0x4e2, 750.0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StopMoving();
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -86.0;
                (*m_opponent)->x = facing * 0x29 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -97.0;
                (*m_opponent)->x = facing * 0x24 + x;
            }
            if (frame == 3) {
                (*m_opponent)->y = -97.0;
                (*m_opponent)->x = facing * 0x22 + x;
                (*m_opponent)->facing = -facing;
            }
            if (frame == 4) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x24 + x;
                (*m_opponent)->facing = -facing;
                ShakeScreen(3, 0);
                (*m_opponent)->pattern = kKnockdownHittable;
                (*m_opponent)->StopMoving();
                (*m_opponent)->StartPattern();
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedDashA:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedDashB:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 2.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedDashC:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame < 3) {
            if (m_dashMomentum == 0) {
                vx = 0.0;
            }
            if (vx > 0.0 && m_dashMomentum == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                m_dashMomentum = 0;
            }
        }
        if (frame == 3 && timer == 0) {
            m_playSound = 0x14;
            vx = 3.0;
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x23;
        }
        vx = vx - (vx > 0.0) * 0.07;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedDash2A:
        StartAfterimages(3);
        vx -= 0.03;
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kUnusedDash2B:
        StartAfterimages(3);
        vx -= 0.03;
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 2.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kUnusedDash2C:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame < 3) {
            if (m_dashMomentum == 0) {
                vx = 0.0;
            }
            if (vx > 0.0 && m_dashMomentum == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2 && frame < 0xf) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                timer = 0;
                StopMoving();
                y = 0.0;
                frame = 0xf;
            }
        }
        if (frame == 7 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x23;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.5;
                vy = -1.5;
                ay = 0.032;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedF9:
        if (frame == 0 && timer == 0) {
            unkdc = 4;
            unkde = -0x14;
            vx = 0.0;
            m_hitsLeft = 1;
            m_recoilGuardWindow = 0;
            m_freezeTime = 0x3c;
            l50.type = 0x28;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.sound = 0x13;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 1;
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x194;
            l50.x = (double)((int)x - facing * 0x50);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            StartAfterimages(3);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
            if (y < 0.0) {
                frame = 6;
            }
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 1;
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1ab;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir236:
        if (frame == 0 && timer == 0) {
            vx *= 0.3;
            vy *= 0.3;
        }
        vy += 0.01;
        if (vy > 0.3) {
            vy = 0.3;
        }
        if (frame == 4 && timer == 0) {
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 1;
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x194;
            l50.x = (double)((int)x - facing * 0x50);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case k623:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 2;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (vy + y >= 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = k623Landing;
                break;
            }
        }
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vy = -2.5;
                ay = 0.045;
                l50.type = 0x1b9;
                l50.x = x;
                l50.y = y;
                l50.keep = 1;
                l50.facing = facing;
                l50.scale = 2;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            StartAfterimages(1);
            if (m_patternVar2 == 0) {
                StopMoving();
                if (m_rfBlue == 0) {
                    m_rfGauge -= 500.0;
                } else {
                    m_rfGauge -= 250.0;
                }
                l50.type = 0x21;
                l50.sound = 0xb;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x32);
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                m_patternVar2++;
            }
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b9;
            l50.x = x;
            l50.y = y;
            l50.keep = 1;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (vy + y >= 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = k623Landing;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 && m_patternVar2 == 1) {
                vy = -3.5;
                ay = 0.015;
                m_patternVar2++;
            }
            if (frame == 8 && m_patternVar1 < 5) {
                frame = 0;
                m_patternVar1++;
            }
            if (frame == 9) {
                m_hitsLeft = 1;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kFall;
            }
        }
        break;
    case k623Landing:
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.shadow = 1;
            l50.keep = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame > 9) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.shadow = 1;
            l50.keep = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame > 9) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.shadow = 1;
            l50.keep = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame > 9) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k41236:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.shadow = 0;
            l50.keep = 1;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.shadow = 0;
            l50.keep = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k41236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            StartAfterimages(3);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1ad;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.shadow = 0;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 0xc6;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            m_playSound = 0x25;
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x19f;
            l50.x = x - facing * 0x23;
            l50.y = y - 67.0;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 0;
            l50.sound = -1;
            l50.movesInFreeze = 1;
            l50.keep = 1;
            SpawnObject(&l50);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 0xd && timer == 0) {
            m_playVoice = 5;
        }
        if (frame > 0xd && frame < 0x11) {
            m_patternVar2++;
            if ((WORD)Random(0, 0x64) > m_patternVar2 * 0.08 + 60.0) {
                l50.type = 0x1a1;
                l50.layer = 1;
                l50.keep = 1;
                if ((WORD)Random(0, 0x64) > 0x32) {
                    l50.type = 0x1a0;
                    l50.layer = 0;
                }
                l50.x = x - facing * 0x12c;
                l50.y = (double)((WORD)Random(0, 0x140) - 0x140);
                l50.facing = facing;
                l50.scale = 2;
                SpawnObject(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (m_patternVar1 < 0xd && frame == 0x11) {
                frame = frame - 3;
                m_patternVar1++;
                break;
            }
            if (frame >= x8) {
                FaceOpponent();
                StartPattern();
                pattern = kStand;
                if (y < 0.0) {
                    pattern = kFall;
                    ay = 0.035;
                }
            }
        }
        break;
    case k236236B:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_patternVar1 = 0xa;
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
        }
        if (frame > 6 && frame < 0xc) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 8 && timer == 0) {
            ShakeScreen(3, 0x14);
            l50.type = 0x1a2;
            l50.x = x + 0.0 - 30.0;
            l50.y = y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            SpawnObject(&l50);
            l50.x = x - facing * 0x28 - 30.0;
            l50.facing = -facing;
            SpawnObject(&l50);
            m_playSound = 0x12;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kAir236236B:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.035;
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 0x21);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 6 && frame < 0xc) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1aa;
            l50.x = x;
            l50.y = y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kFall;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
        }
        if (frame == 5 && timer == 0) {
            l50.type = 0x1b2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            l50.keep = 1;
            SpawnObject(&l50);
        }
        if (frame == 0x10 && timer == 0) {
            l50.type = 0x1b3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if ((frame == 8 || frame == 0x12) && m_attackResult == 3) {
            (*m_opponent)->m_hitstop = 0x10e;
        }
        if (frame == 0x20 && timer == 0) {
            l50.type = 0x1b0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            (*m_opponent)->m_koDelay = 0x7530;
        }
        if (frame == 0x2c && timer == 0) {
            m_freezeTime = 0x23a;
            FillBackground(0xb0, 0xbb8);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            (*m_opponent)->x = x;
            m_playVoice = 0xa;
            m_game->m_hideObjectsTime = 0x7530;
        }
        if (frame == 0x33 && timer == 0) {
            vy = -7.5;
            ay = 0.035;
            l50.type = 0x1b4;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 0;
            l50.keep = 1;
            l50.screen = 1;
            l50.facing = 1;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            l50.type = 0x1b5;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 0;
            l50.keep = 1;
            l50.screen = 1;
            l50.facing = 1;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            l50.type = 0x1b6;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.screen = 1;
            l50.facing = 1;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            m_playVoice = 0xb;
        }
        if (frame == 0x35 && m_attackResult == 3) {
            timer = 0;
            frame = 0x36;
            (*m_opponent)->m_hitstop = 0xbb8;
            vy = -0.05;
            ay = 0.0;
            FillBackground(0xb0, 3);
            m_playVoice = 0xc;
            l50.type = 0x1b7;
            l50.x = x;
            l50.y = y - 160.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = 1;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            (*m_opponent)->m_game->m_hideObjectsTime = 0;
        }
        if (frame == 0x37 && timer == 0) {
            vy = -7.0;
            ay = 0.03;
            l50.type = 0x1c0;
            l50.x = x;
            l50.y = y - 150.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            l50.facing = 1;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            l50.x = x + 40.0;
            l50.y = y - 140.0;
            SpawnObject(&l50);
            l50.x = x - 50.0;
            l50.y = y - 150.0;
            SpawnObject(&l50);
            l50.type = 0x1b8;
            l50.x = x;
            l50.y = y - 150.0;
            SpawnObject(&l50);
        }
        if (frame == 0x37 && m_attackResult == 3) {
            (*m_opponent)->m_koDelay = 0;
        }
        if (frame > 0 && frame < 0x37) {
            FocusCameraY(0x32, 3);
        }
        if (frame > 0x25 && frame < 0x37) {
            FocusCameraX(0x32, 3);
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame == 0x35 && vy > 1.0) {
            vy = 1.0;
        }
        if (frame > 0x37 && y + vy > 0.0) {
            StopMoving();
            StartPattern();
            y = 0.0;
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0x12 || frame == 0x23 || frame > 0x32) {
                m_attackResult = 0;
            }
            if (frame == 0xe && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame == 0x1b && (m_attackResult != 3 || (*m_opponent)->m_hp <= 0)) {
                StartPattern();
                FaceOpponent();
                pattern = kStand;
                break;
            }
            if (frame == 0x24 && m_attackResult != 3) {
                StartPattern();
                pattern = kLv4Miss;
            }
            if (frame == 0x2b) {
                l50.type = 0x1b1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.keep = 1;
                l50.facing = facing;
                l50.movesInFreeze = 1;
                SpawnObject(&l50);
            }
            if (frame == 0x35) {
                m_playVoice = 9;
            }
            if (frame == 0x36) {
                frame--;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kLv4Miss:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
    }
}
