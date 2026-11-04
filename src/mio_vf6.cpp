// CMio::UpdatePattern (0x5736d0-0x58830f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMio's
// .rdata, which starts with its constructor's folder name (mio.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMio::UpdatePattern()
{
    WORD frameCount; // frames in the action's animation
    WORD duration; // ticks the current frame lasts

    if (m_hitstop > 0 || (*m_opponent)->m_freezeTime > 0) {
        return;
    }
    EffectDesc effect; // what CreateEffect or SpawnObject is to make
    duration = (short)anims[pattern].frames[frame].duration;
    frameCount = anims[pattern].frameCount;
    InitEffectDesc((EffectDesc*)&effect);
    switch (pattern) {
    default:
        m_dashMomentum = 0;
        vx = 0.0;
        vy = 0.0;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
            }
        }
        break;
    case kWalkForward:
        m_dashMomentum = 0;
        vx = 0.5;
        if (m_stance == 0) {
            vx = 0.7;
        }
        vy = 0.0;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
            }
        }
        break;
    case kWalkBack:
        m_dashMomentum = 0;
        vx = -0.5;
        if (m_stance == 0) {
            vx = -0.7;
        }
        vy = 0.0;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
            }
        }
        break;
    case kJump:
        if (frame == 0 && timer == 0) {
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.0;
            if (m_dashMomentum == 1) {
                vx = 0.4;
                m_dashMomentum = 0;
            }
            if (m_stance == 1) {
                vy = -2.0;
                ay = 0.02;
            }
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
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
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.0;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
            }
            if (m_stance == 1) {
                vy = -2.0;
                ay = 0.02;
            }
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
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
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.0;
            vx = -0.7;
            if (m_stance == 1) {
                vy = -2.0;
                ay = 0.02;
            }
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kFall:
        vy = vy + ay;
        m_dashMomentum = 0;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kAirJump:
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 0.0;
            ay = 0.045;
            if (m_stance == 1) {
                vy = -2.0;
                ay = 0.02;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
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
            vy = -3.0;
            vx = 0.7;
            ay = 0.045;
            if (m_stance == 1) {
                vy = -2.0;
                ay = 0.02;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
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
            vy = -3.0;
            vx = -0.7;
            ay = 0.045;
            if (m_stance == 1) {
                vy = -2.0;
                ay = 0.02;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
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
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx *= 0.25;
            vy *= 0.25;
        }
        m_rfGauge--;
        if (frame == 0 && timer == 0) {
            m_playSound = 21;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 21;
        }
        if (m_inputY == 1 && m_patternVar1 > 2) {
            pattern = kFall;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_patternVar1++;
                if (m_patternVar1 < 2) {
                    frame = 0;
                }
            }
            if (frame >= frameCount) {
                frame = frame - 2;
                m_patternVar1++;
                if (m_patternVar1 > 15) {
                    StartPattern();
                    pattern = kFall;
                    break;
                }
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 10;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 15;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 10;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 15;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 10;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 15;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -2.0) {
                vy = -2.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -4.0) {
                vy = -4.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -6.0) {
                vy = -6.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -2.0) {
                vy = -2.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            if (vy < -4.0) {
                vy = -4.0;
            } else if (vy > -0.5) {
                vy = -0.5;
            }
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = vy * 0.75 + m_hitVy;
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.032;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            m_patternVar1++;
            m_untechTime = m_untechTime + 120;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            m_playSound = 31;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            vx = m_hitVx;
            vy = m_hitVy;
            ay = 0.072;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 11) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 11;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            effect.type = 0x1f3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_playSound = 30;
            vy = -0.45;
            vx = -0.1;
            m_patternVar1++;
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4 && m_patternVar1 < 8) {
                frame = 0;
                m_patternVar1++;
            }
            if (frame == 15) {
                frame = 7;
            }
            if (frame == 8 && vy > -0.5) {
                frame = 15;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 5) {
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
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_encasedBreakOut = 1;
            }
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            m_playSound = 33;
            vy = -1.5;
            vx = -0.8;
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kEncased2:
        if (frame == 0 && timer == 0) {
            if (m_encasedBreakOut == 0) {
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_encasedBreakOut = 1;
            }
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            m_playSound = 33;
            vy = -1.5;
            vx = -0.8;
            m_gauge = m_gauge + 30;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kEncasedAir:
        if (frame == 0 && timer == 0) {
            if (m_encasedBreakOut == 0) {
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_encasedBreakOut = 1;
            }
            if (m_rfBlue != 0) {
                m_rfGauge -= 30.0;
            }
            m_playSound = 33;
            vx = m_hitVx;
            vy = m_hitVy;
            m_gauge = m_gauge + 30;
        }
        vy += 0.04;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_encasedBreakOut = 1;
            }
            if (m_patternVar1 == 0) {
                if (m_rfBlue != 0) {
                    m_rfGauge -= 30.0;
                }
                m_playSound = 33;
                vx = m_hitVx;
                vy = m_hitVy;
                m_gauge = m_gauge + 30;
                m_patternVar1++;
            }
        }
        vy += 0.06;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            effect.type = 0x1ef;
            effect.x = 60.0;
            effect.y = 40.0;
            effect.screen = 1;
            effect.facing = 1;
            effect.scale = 0;
            effect.layer = 0;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kWakeUp:
        if (y < 0.0) {
            vy += 0.04;
        }
        if (y + vy > 0.0 && frame > 1) {
            y = 0.0;
            vy = 0.0;
            timer = 0;
            frame = 7;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                vy = -1.0;
            }
            if (frame == frameCount - 1) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kStand;
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
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kLyingDown;
                StartPattern();
            }
        }
        break;
    case kLyingDown:
        timer++;
        m_dashMomentum = 0;
        if (m_hp > 0 && timer > 99 && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
        }
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kWakeUp;
                StartPattern();
            }
        }
        break;
    case kGuardStandLight:
        if (m_inputY == 1) {
            pattern = kGuardCrouchLight;
        }
        if (m_inputY != 1) {
            pattern = kGuardStandLight;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 10;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kGuardStandMedium:
        if (m_inputY == 1) {
            pattern = kGuardCrouchMedium;
        }
        if (m_inputY != 1) {
            pattern = kGuardStandMedium;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 15;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kGuardStandHeavy:
        if (m_inputY == 1) {
            pattern = kGuardCrouchHeavy;
        }
        if (m_inputY != 1) {
            pattern = kGuardStandHeavy;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kGuardCrouchLight:
        if (m_inputY == 1) {
            pattern = kGuardCrouchLight;
        }
        if (m_inputY != 1) {
            pattern = kGuardStandLight;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 10;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kGuardCrouchMedium:
        if (m_inputY == 1) {
            pattern = kGuardCrouchMedium;
        }
        if (m_inputY != 1) {
            pattern = kGuardStandMedium;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 15;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kGuardCrouchHeavy:
        if (m_inputY == 1) {
            pattern = kGuardCrouchHeavy;
        }
        if (m_inputY != 1) {
            pattern = kGuardStandHeavy;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kGuardAir:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = -2.6;
            m_gauge = m_gauge + 15;
            ay = 0.06;
        }
        vx = -1.2;
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = -2.3;
            effect.type = 8;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
        } else {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = -2.3;
            effect.type = 8;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
        } else {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
    case 0xa1:
        if (frame == 0 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 60);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
            m_playSound = 62;
            m_patternVar1++;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
                ay = 0.035;
            }
        }
        break;
    case kWakeUpAttack:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 6 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 60);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
            m_playSound = 62;
            m_gauge = m_gauge - 1000;
            m_patternVar1++;
        }
        vy = vy + ay;
        if (y + vy > 0.0) {
            pattern = kLand;
            StartPattern();
            StartPattern();
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 12) {
                ay = 0.035;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
        }
        if (m_inputY == -1 && frame > 0) {
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
            vy = 0.0;
            ay = 0.0;
        }
        vx = 1.7;
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 100.0) {
            pattern = kDashStop;
            StartPattern();
        }
        if (m_inputX != facing && m_patternVar1 >= 60) {
            pattern = kDashStop;
            StartPattern();
        }
        break;
    case kDashBack:
        StartAfterimages(2);
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if ((frame == 5 || frame == 6) && vy + y > 0.0) {
            timer = 0;
            StopMoving();
            frame = 7;
            y = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -2.0;
                vy = -1.3;
                m_playVoice = 1;
                ay = 0.04;
            }
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                FaceOpponent();
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0) {
            vx = 1.2;
            vy = -0.4;
            StartAfterimages(3);
            ay = 0.0;
            m_playSound = 20;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.8;
            vy = 0.0;
            StartAfterimages(3);
            ay = 0.0;
            m_playSound = 20;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 120.0) {
            pattern = kFall;
            StartPattern();
            vx = 0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 48) {
            pattern = kFall;
            StartPattern();
            vx = 0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0) {
            vx = -1.2;
            vy = -0.4;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 20;
        }
        if (frame == 3 && timer == 0) {
            vx = -1.8;
            vy = 0.0;
            StartAfterimages(3);
            ay = 0.0;
            m_playSound = 20;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && m_patternVar2 >= 120.0) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && m_patternVar1 >= 48) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kInstantCharge:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_game->FlashNegative(0);
            vx = 0.0;
            vy = 0.0;
            if (m_rfBlue == 1) {
                m_proration = m_rfGauge * 5.0 + m_proration;
            }
            m_rfGauge = 0.0;
            m_freezeTime = 90;
            FillBackground(176, 3);
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 18;
            effect.type = 1;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 2 && timer == 0) {
            effect.type = 4;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            effect.type = 8;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
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
            effect.type = 8;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount) {
                FaceOpponent();
            }
            if (frame >= frameCount) {
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
            m_recoilGuardWindow = 0;
            m_cornerPushback = 0.0;
            if (ay == 0.0) {
                ay = 0.035;
            }
            m_freezeTime = 60;
        }
        if (m_freezeTime == 0 && m_patternVar3 == 0.0) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_freezeTime = 90;
            FillBackground(176, 3);
        }
        if (frame == 0 && timer == 0) {
            m_playSound = 18;
            effect.type = 1;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kFall;
                vx = m_patternVar1 * 0.01;
                vy = m_patternVar2 * 0.01;
                if (ay == 0.0) {
                    ay = 0.035;
                }
                StartPattern();
            }
        }
        break;
    case kDashStop:
        vx -= 0.06;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (vx == 0.0) {
            pattern = kStand;
            StartPattern();
            break;
        }
        if (m_inputY == -1 && frame > 0) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
                break;
            }
        }
        break;
    case 0xb4:
        if (frame == 0 && timer == 0) {
            StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 7) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 7;
            m_playSound = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_playVoice = 1;
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
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
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            vx -= 0.03;
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 99;
        }
        if (frame == 3 && timer == 0) {
            m_playSound = 20;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 5 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = 3;
            }
            if (frame >= frameCount) {
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
        m_dashMomentum = 0;
        if (frame == 2 && timer == 0) {
            vx += 1.7;
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        } else {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kJumpA:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && m_airActions == 0 && m_sealLevel < 3) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kJumpB:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && m_airActions == 0 && m_sealLevel < 3) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kJumpC:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && m_airActions == 0 && m_sealLevel < 3) {
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 3;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 6 && m_patternVar1 < 1) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kFloat5A:
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
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat5BClose:
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat5BFar:
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat5C:
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat2A:
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat2B:
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            m_playSound = 20;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat2C:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0) {
            vx -= 0.04;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 7;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_playSound = 20;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 9 && m_patternVar1 == 0) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloatJumpA:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
            FaceOpponent();
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kFloatJumpB:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
            FaceOpponent();
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kFloatJumpC:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
            FaceOpponent();
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kThrow:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            if ((*m_opponent)->x > 600.0) {
                (*m_opponent)->x = 600.0;
            }
            if ((*m_opponent)->x < 40.0) {
                (*m_opponent)->x = 40.0;
            }
            StartPattern();
            (*m_opponent)->StartPattern();
            pattern = kThrowHold;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            x = (*m_opponent)->x - (*m_opponent)->m_pointX[0] * facing;
            y = (*m_opponent)->m_pointY[0] + 57 + y;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kThrowHold:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->pattern = kThrownStandHigh2;
            x = (*m_opponent)->x - (*m_opponent)->m_pointX[0] * facing;
            y = (*m_opponent)->m_pointY[0] + 57 + y;
            m_attackResult = 0;
        }
        if ((m_patternVar1 > 600 && frame == 3 || (*m_opponent)->m_hp <= 0) && frame < 5) {
            facing = -facing;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->StartPattern();
            timer = 0;
            frame = 5;
            ay = 0.035;
            DealDamage(400, 1000.0);
            break;
        }
        if (frame > 2 && frame < 5) {
            m_patternVar2++;
            m_patternVar1++;
        }
        if (m_patternVar2 > 70.0 && frame < 5 && (*m_opponent)->m_hp > 0) {
            m_patternVar2 = 0.0;
            frame = 4;
            timer = 0;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            m_patternVar2 = 0.0;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 54);
            effect.scale = 2;
            effect.sound = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(100, 1000.0);
        }
        if (frame > 4) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                effect.type = 0x1c6;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
            }
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case kJump2C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                vx = 1.0;
                vy = 1.0;
                ay = 0.0;
                m_playVoice = 3;
                m_gauge = m_gauge + 20;
                m_hitsLeft = 1;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (y < 0.0 && vx > 0.0) {
            vx += 0.035;
            vy += 0.035;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            pattern = kJump2CLanding;
            StartPattern();
        }
        break;
    case kJump2CLanding:
        vy = 0.0;
        m_attackResult = 3;
        vx -= 0.08;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case k6C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 2.0;
            m_gauge = m_gauge + 15;
            m_playSound = 20;
        }
        vx -= 0.05;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kFloatJump2B:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult == 3 && m_airActions == 0) {
            FaceOpponent();
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kFloat4B:
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloatJump2C:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
            FaceOpponent();
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kDashA:
        StartAfterimages(3);
        vx -= 0.032;
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kDashB:
        StartAfterimages(3);
        vx -= 0.032;
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
            m_hitsLeft = 1;
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kDashC:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kDash2A:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kDash2B:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kDash2C:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 21;
            vx = 2.3;
        }
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloatDashA:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloatDashB:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
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
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloatDashC:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloatDash2A:
        StartAfterimages(3);
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kFloatDash2B:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kFloatDash2C:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 7;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_playSound = 20;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 9 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat5AClose:
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
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat2AClose:
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 2 && timer == 0) {
                m_gauge = m_gauge + 5;
                m_playSound = 21;
                m_hitsLeft = 1;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloatAirThrow:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            ay = 0.035;
            pattern = kAirThrowSlam;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 35);
            effect.y = (double)((int)y - 58);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = (int)x + facing * 35;
            (*m_opponent)->y = (int)y - 58;
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kFloatJumpC;
                frame = 2;
            }
        }
        break;
    case kAirThrow:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            ay = 0.035;
            pattern = kAirThrowSlam;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 35);
            effect.y = (double)((int)y - 58);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = (int)x + facing * 35;
            (*m_opponent)->y = (int)y - 58;
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kJumpC;
                frame = 1;
            }
        }
        break;
    case kAirThrowSlam:
        if (frame < 6) {
            FocusCameraX(50, 3);
        }
        if (frame < 6) {
            FocusCameraY(50, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            StopMoving();
            y = 0.0;
            StartPattern();
            pattern = kLand;
            break;
        }
        if (frame == 0) {
            (*m_opponent)->y = y - 35.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = kThrownStandHigh;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 59.0;
            (*m_opponent)->x = facing * 36 + x;
            (*m_opponent)->pattern = kThrownStandHigh;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = facing * 35 + x;
            (*m_opponent)->pattern = kThrownStandHigh;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)((int)x + facing * 35);
            effect.y = (double)((int)y - 56);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 35 + x;
            (*m_opponent)->y = y - 56.0;
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -2.5;
            (*m_opponent)->m_hitVy = -0.5;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->x = facing * 15 + x;
            DealDamage(1000, 500.0);
            (*m_opponent)->m_untechTime = (int)(200.0 * m_proration * 0.0001);
            (*m_opponent)->StartPattern();
            effect.type = 0x1c2;
            effect.x = (double)((int)x + facing * 35);
            effect.y = (double)((int)y - 56);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c3;
            SpawnObject(&effect);
            effect.type = 0x1c4;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 8;
        }
        if (frame > 1 && frame < 9) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            StartPattern();
            frame = 9;
        }
        if (frame == 9 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -1.8;
                ay = 0.025;
                x = facing * 10 + x;
            }
            if (vy > 0.0 && frame == 5) {
                frame = 6;
                break;
            }
            if (frame == 6) {
                frame = frame - 4;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                StopMoving();
                pattern = kStand;
            }
            m_attackResult = 0;
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 12;
        }
        if (frame > 1 && frame < 9) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            StartPattern();
            frame = 9;
        }
        if (frame == 9 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -2.8;
                ay = 0.025;
                x = facing * 10 + x;
            }
            if (vy > 0.0 && frame == 5) {
                frame = 6;
                break;
            }
            if (frame == 6) {
                frame = frame - 4;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                StopMoving();
                pattern = kStand;
            }
            m_attackResult = 0;
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
            m_hitsLeft = 20;
        }
        if (frame == 1 && timer == 0) {
            effect.type = 0x1bd;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = -facing;
            SpawnObject(&effect);
        }
        if (frame > 1 && frame < 9) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            StartPattern();
            frame = 9;
        }
        if (frame == 9 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -2.8;
                ay = 0.015;
                x = facing * 10 + x;
            }
            if (vy > 0.0 && frame == 5) {
                ay = 0.025;
                frame = 6;
                break;
            }
            if (frame == 6) {
                frame = frame - 4;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                StopMoving();
                pattern = kStand;
            }
            m_attackResult = 0;
        }
        break;
    case 0xfd:
        if (y + vy > 0.0 && frame < 3) {
            StartPattern();
            frame = 3;
        }
        if (frame == 3 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
        }
        if (y < 0.0) {
            vy += 0.025;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236A:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (m_attackResult > 1 && m_command == kCmd236A && frame == 6) {
            pattern = k236AFollowupA;
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (m_command == kCmd236B && frame == 6) {
            pattern = k236FollowupB;
            m_attackResult = 0;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        break;
    case k236C:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x1c0;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 95);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c1;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 80);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c0;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 65);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c1;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c0;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 35);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c1;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 20);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c0;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 5);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        break;
    case k236AFollowupA:
        if (frame == 0 && timer == 0) {
            m_playSound = 20;
            m_gauge = m_gauge + 10;
            m_hitsLeft = 3;
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 138);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame == 1 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 100);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame == 2 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 62);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 24);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            m_playSound = 20;
            m_gauge = m_gauge + 35;
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            effect.type = 0x198;
            effect.x = (double)((int)x - facing * 9);
            effect.y = (double)((int)y - 58);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            m_dashMomentum = 0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 4;
        }
        if (frame == 2 && y + vy >= 0.0 && vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 1.7;
            frame = 3;
            timer = 0;
        }
        if (frame > 2) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        vy += 0.042;
        if (vy > 0.0 && y >= 0.0) {
            vy = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                vx = 0.3;
                vy = -0.9;
                m_playVoice = 1;
            }
            if (frame == 5 && vx > 0.8) {
                frame = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 10;
        }
        if (frame == 2 && y + vy >= 0.0 && vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 2.4;
            frame = 3;
            timer = 0;
        }
        if (frame > 2) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        vy += 0.042;
        if (vy > 0.0 && y >= 0.0) {
            vy = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                vx = 0.3;
                vy = -1.2;
                m_playVoice = 1;
            }
            if (frame == 5 && vx > 0.8) {
                frame = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 10;
        }
        if (frame == 2 && y + vy >= 0.0 && vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 2.4;
            frame = 3;
            timer = 0;
        }
        if (frame > 2) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        vy += 0.042;
        if (vy > 0.0 && y >= 0.0) {
            vy = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                vx = 0.3;
                vy = -1.2;
                m_playVoice = 1;
            }
            if (frame == 5 && vx > 0.8) {
                frame = frame - 2;
            }
            if (frame == 7 && m_patternVar1 < 5) {
                frame = frame - 2;
                m_patternVar1++;
                m_hitsLeft = m_hitsLeft + 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat412A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (m_patternVar3 > 2.5) {
            m_patternVar2 = -0.06;
        }
        if (m_patternVar3 < 0.0) {
            m_patternVar2 = 0.06;
        }
        m_patternVar3 = m_patternVar3 + m_patternVar2;
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_patternVar1 = 0;
            m_patternVar2 = 0.05;
            vy = -1.1;
            vx = 0.0;
        }
        if (frame > 2 && frame < 8) {
            vy += 0.022;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.012;
            if (vy > 0.8) {
                vy = 0.8;
            }
        }
        if (frame == 8 && timer == 0 && m_patternVar1 < 7) {
            effect.type = 0x194;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)((int)y - 47);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if ((frame == 8 || frame == 9) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 10;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_playVoice = 3;
                vy -= 0.4;
            }
            if (frame == 10 && m_patternVar1 < 16) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame == 11 && y < 0.0) {
                pattern = kFall;
                StartPattern();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat412B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (m_patternVar3 > 2.5) {
            m_patternVar2 = -0.06;
        }
        if (m_patternVar3 < 0.0) {
            m_patternVar2 = 0.06;
        }
        m_patternVar3 = m_patternVar3 + m_patternVar2;
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_patternVar2 = 0.05;
            m_patternVar1 = 0;
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame > 2 && frame < 8) {
            vy += 0.022;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.012;
            if (vy > 0.8) {
                vy = 0.8;
            }
        }
        if (frame == 8 && timer == 0 && m_patternVar1 < 12) {
            effect.type = 0x194;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)((int)y - 47);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if ((frame == 8 || frame == 9) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 10;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_playVoice = 3;
                vx -= 0.5;
                vy -= 0.9;
            }
            if (frame == 10 && m_patternVar1 < 24) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame == 11 && y < 0.0) {
                pattern = kFall;
                StartPattern();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat412C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0 && m_patternVar1 == 100) {
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_patternVar1 = 0;
        }
        if (m_patternVar3 > 2.5) {
            m_patternVar2 = -0.08;
        }
        if (m_patternVar3 < 0.0) {
            m_patternVar2 = 0.08;
        }
        m_patternVar3 = m_patternVar3 + m_patternVar2;
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_patternVar1 = 0;
            m_patternVar2 = 0.05;
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame > 2 && frame < 8) {
            vy += 0.022;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.008;
            if (vy > 0.6) {
                vy = 0.6;
            }
        }
        if (frame == 8 && timer == 0 && m_patternVar1 < 16) {
            effect.type = 0x1bc;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)((int)y - 47);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if ((frame == 8 || frame == 9) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 10;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_playVoice = 3;
                vx -= 0.5;
                vy -= 0.4;
            }
            if (frame == 10 && m_patternVar1 < 13) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame == 11 && y < 0.0) {
                pattern = kFall;
                StartPattern();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 25;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 29);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 15;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 29);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
        }
        if (frame == 13 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 15;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 29);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
            facing = -facing;
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 25;
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 29);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 25;
            effect.type = 0x1c5;
            effect.x = (double)((int)x + facing * 88);
            effect.y = -3.0;
            effect.facing = facing;
            effect.layer = 0;
            effect.scale = 0;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 25;
            effect.type = 0x1c5;
            effect.x = (double)((int)x + (facing << 7));
            effect.y = -3.0;
            effect.facing = facing;
            effect.layer = 0;
            effect.scale = 0;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kFloat214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 4;
            m_gauge = m_gauge + 25;
            effect.type = 0x1c5;
            effect.x = (double)((int)x + facing * 188);
            effect.y = -3.0;
            effect.facing = facing;
            effect.layer = 0;
            effect.scale = 0;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kStanceChange:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 4 && timer == 0) {
            if (m_stance == 0) {
                m_stance = 1;
                timer++;
                break;
            }
            m_stance = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236B:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (m_attackResult > 1 && m_command == kCmd236A && frame == 6) {
            pattern = k236BFollowupA;
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (m_command == kCmd236B && frame == 6) {
            pattern = k236FollowupB;
            m_attackResult = 0;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        break;
    case k236BFollowupA:
        if (frame == 0 && timer == 0) {
            m_playSound = 20;
            m_gauge = m_gauge + 10;
            m_hitsLeft = 5;
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 138);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame == 1 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 100);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame == 2 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 62);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 24);
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                effect.type = 0x198;
                effect.x = (double)((int)x - facing * 9);
                effect.y = (double)((int)y - 58);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
            }
            if (frame == 8) {
                m_hitsLeft = 1;
                m_playSound = 21;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236FollowupB:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 10;
            effect.type = 0x1c8;
            effect.keep = 1;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 48);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedSuperToFloat:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_stance = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedSuperToGround:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_stance = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (m_attackResult == 3 && m_patternVar1 == 0 && frame == 3) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 120;
            m_patternVar1++;
        }
        if (frame == 5 && timer < 100) {
            m_attackResult = 3;
            if ((WORD)Random(0, 100) < 1) {
                effect.type = 0x19b;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
            if ((WORD)Random(0, 100) < 3) {
                effect.type = 0x19d;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
            if ((WORD)Random(0, 100) < 7) {
                effect.type = 0x19c;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (m_attackResult == 3 && m_patternVar1 == 0 && frame == 3) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 120;
            m_patternVar1++;
        }
        if (frame == 5 && timer < 145) {
            m_attackResult = 3;
            if ((WORD)Random(0, 100) < 2) {
                effect.type = 0x19b;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
            if ((WORD)Random(0, 100) < 3) {
                effect.type = 0x19d;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
            if ((WORD)Random(0, 100) < 6) {
                effect.type = 0x19c;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 2 && timer == 0) {
            m_freezeTime = 120;
            m_hitsLeft = 1;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 1) {
            m_game->FlashNegative(15);
        }
        if (m_attackResult == 3 && m_patternVar1 == 0 && frame == 3) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 120;
            m_patternVar1++;
        }
        if (frame == 4 && timer < 200) {
            m_attackResult = 3;
            if ((WORD)Random(0, 100) < 3) {
                effect.type = 0x19b;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
            if ((WORD)Random(0, 100) < 4) {
                effect.type = 0x19d;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
            if ((WORD)Random(0, 100) < 6) {
                effect.type = 0x19c;
                effect.x = (double)(int)(((WORD)Random(0, 150) - 60) * facing + x);
                effect.y = -480.0;
                effect.facing = 1;
                effect.layer = 1;
                effect.scale = 0;
                SpawnObject(&effect);
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat236236A:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2 && frame < 7) {
            vy += 0.012;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.03;
        }
        if (frame == 5) {
            vy = 0.0;
        }
        if (frame == 9 && timer == 0 && m_patternVar1 == 0) {
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)((int)y - 47);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if ((frame == 9 || frame == 10) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 11;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 9) {
                m_playSound = 22;
                vx -= 0.7;
                vy -= 1.5;
            }
            if (frame == 11 && m_patternVar1 < 16) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame == 12 && y < 0.0) {
                pattern = kFall;
                StartPattern();
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat236236B:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2 && frame < 7) {
            vy += 0.012;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.03;
        }
        if (frame == 5) {
            vy = 0.0;
        }
        if (frame == 9 && timer == 0 && m_patternVar1 == 0) {
            effect.type = 0x1a8;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)((int)y - 47);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if ((frame == 9 || frame == 10) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 11;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 9) {
                m_playSound = 22;
                vx -= 0.7;
                vy -= 1.5;
            }
            if (frame == 11 && m_patternVar1 < 16) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame == 12 && y < 0.0) {
                pattern = kFall;
                StartPattern();
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat236236C:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 4) {
            m_game->FlashNegative(15);
        }
        if (frame > 2 && frame < 7) {
            vy += 0.012;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.03;
        }
        if (frame == 5) {
            vy = 0.0;
        }
        if (frame == 9 && timer == 0 && m_patternVar1 == 0) {
            effect.type = 0x1a9;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)((int)y - 47);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if ((frame == 9 || frame == 10) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 11;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 9) {
                m_playSound = 22;
                vx -= 0.7;
                vy -= 1.5;
            }
            if (frame == 11 && m_patternVar1 < 16) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame == 12 && y < 0.0) {
                pattern = kFall;
                StartPattern();
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214A:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 8;
        }
        if (frame > 2 && frame < 6 && m_patternVar2 <= 0.0) {
            effect.type = 0x1be;
            effect.x = (double)((int)x + facing * 50);
            effect.y = (double)((int)y - 43);
            effect.scale = 2;
            effect.keep = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar2 = 21.0;
            m_playVoice = 6;
        }
        m_patternVar2--;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                m_patternVar1++;
                if (m_patternVar1 > 5) {
                    m_hitsLeft = 0;
                }
                if (m_patternVar1 < 8) {
                    frame = frame - 2;
                }
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214B:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 15;
        }
        if (frame > 2 && frame < 6 && m_patternVar2 <= 0.0) {
            effect.type = 0x1be;
            effect.x = (double)((int)x + facing * 50);
            effect.y = (double)((int)y - 43);
            effect.scale = 2;
            effect.keep = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar2 = 15.0;
            m_playVoice = 6;
        }
        m_patternVar2--;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                m_patternVar1++;
                if (m_patternVar1 < 7) {
                    frame = frame - 2;
                }
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214C:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
            m_playSound = 37;
        }
        m_game->FlashNegative(3);
        if (frame == 3 && timer == 0) {
            m_playSound = 18;
            effect.type = 0x1be;
            effect.x = (double)((int)x + facing * 50);
            effect.y = (double)((int)y - 43);
            effect.scale = 2;
            effect.keep = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 6;
        }
        if (m_attackResult == 3 && m_patternVar1 == 0) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 180;
            m_patternVar1++;
            effect.type = 0x1bf;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (double)((int)(*m_opponent)->y - 50);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat214214A:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 10);
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 12 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            effect.layer = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 16 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            SpawnObject(&effect);
        }
        if (frame == 20 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            effect.layer = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 24 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 19) {
                m_patternVar1++;
                if (m_patternVar1 < 1) {
                    frame = frame - 8;
                }
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat214214B:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 10);
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 12 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            effect.layer = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 16 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            SpawnObject(&effect);
        }
        if (frame == 20 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            effect.layer = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 24 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 19) {
                m_patternVar1++;
                if (m_patternVar1 < 2) {
                    frame = frame - 8;
                }
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloat214214C:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 10);
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        m_game->FlashNegative(15);
        if (frame == 12 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            effect.layer = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 16 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            SpawnObject(&effect);
        }
        if (frame == 20 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            effect.layer = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 24 && timer == 0) {
            m_playSound = 32;
            effect.type = 0x1aa;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 65);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 45);
            SpawnObject(&effect);
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 25);
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 19) {
                m_patternVar1++;
                if (m_patternVar1 < 4) {
                    frame = frame - 8;
                }
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
            m_playSound = 37;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        m_game->FlashNegative(15);
        if (m_attackResult == 2 && frame > 1 && frame < 13) {
            frame = 13;
            timer = 0;
            break;
        }
        if (frame == 13 && timer == 0) {
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
        }
        if (frame > 12) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_hitsLeft == 0 && frame < 13 && m_pressA == 1) {
            StartPattern();
            pattern = kLv4ChainA;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                vx = 2.0;
            }
            if (frame == 13) {
                m_patternVar1++;
                if (m_patternVar1 < 3) {
                    frame = frame - 3;
                }
            }
            if (frame >= frameCount) {
                pattern = kWakeUp;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainA:
        m_game->FlashNegative(15);
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 20;
        }
        if (m_attackResult == 3 && frame > 1 && frame < 4 && m_pressB == 1) {
            StartPattern();
            pattern = kLv4ChainB;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainB:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        m_game->FlashNegative(15);
        if (frame == 2 && timer == 0) {
            m_playSound = 20;
        }
        if (m_attackResult == 3 && frame > 2 && frame < 5 && m_pressC == 1) {
            StartPattern();
            pattern = kLv4ChainC;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainC:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        m_game->FlashNegative(15);
        if (frame == 3 && timer == 0) {
            m_playSound = 21;
        }
        if (m_attackResult == 3 && frame > 5 && frame < 7 && m_pressA == 1) {
            StartPattern();
            pattern = kLv4ChainA2;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainA2:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        m_game->FlashNegative(15);
        if (frame == 0 && timer == 0) {
            m_playSound = 20;
        }
        if (m_attackResult == 3 && frame > 0 && frame < 4 && m_pressB == 1) {
            StartPattern();
            pattern = kLv4ChainB2;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainB2:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        m_game->FlashNegative(15);
        if (frame == 1 && timer == 0) {
            m_playSound = 20;
        }
        if (m_attackResult == 3 && frame > 1 && frame < 4 && m_pressC == 1) {
            StartPattern();
            pattern = kLv4ChainC2;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainC2:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 4;
        }
        m_game->FlashNegative(15);
        if (frame == 1 && timer == 0) {
            m_playSound = 20;
        }
        if (m_hitsLeft == 0 && frame > 2 && frame < 5 && m_pressD == 1) {
            StartPattern();
            pattern = kLv4ChainD;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4ChainD:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        m_game->FlashNegative(120);
        if (frame > 3) {
            m_game->FlashNegative(15);
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 20;
        }
        if (m_attackResult == 3 && frame > 2 && frame < 5 && m_command == kCmd623C) {
            StartPattern();
            pattern = kLv4Finish623C;
            StopMoving();
            break;
        }
        if (m_attackResult == 3 && frame > 2 && frame < 5 && m_command == kCmd236C) {
            StartPattern();
            pattern = kLv4Finish236C;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4Finish623C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 15);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 2;
        }
        m_game->FlashNegative(15);
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 12) {
            frame = 12;
            timer = 0;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                vy = -1.0;
                ay = 0.035;
                vx = 4.0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4Finish236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 15);
            effect.y = (double)((int)y - 20);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        m_game->FlashNegative(15);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
                effect.type = 0x1ba;
                effect.x = (double)((int)x + facing * 11);
                effect.y = (double)((int)y - 53);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 6) {
                m_patternVar1++;
                if (m_patternVar1 < 15) {
                    frame = frame - 2;
                }
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloatLv4:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
            m_playSound = 37;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        m_game->FlashNegative(15);
        if (m_attackResult == 3 && frame == 3) {
            StartPattern();
            StopMoving();
            pattern = kFloatLv4Hit;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownHidden;
            (*m_opponent)->y = 0.0;
            if ((*m_opponent)->x > 480.0) {
                (*m_opponent)->x = 480.0;
            }
            if ((*m_opponent)->x < 160.0) {
                (*m_opponent)->x = 160.0;
            }
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kFloatLv4Hit:
        m_noAirRecovery = 1;
        FocusCameraY(50, 3);
        (*m_opponent)->FocusCameraX(50, 3);
        if ((*m_opponent)->pattern == kLyingDown || (*m_opponent)->pattern == kThrownHidden) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 6) {
            FillBackground(176, 3);
        } else {
            m_patternVar3 = 1.0;
        }
        m_game->FlashNegative(15);
        if (m_patternVar2 == 1.0 && (*m_opponent)->pattern != kHitAirHeavy) {
            DealDamage(5000, 800.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kHitAirHeavy;
            (*m_opponent)->m_hitVy = -15.0;
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->y = -10.0;
            (*m_opponent)->vx = 0.0;
        }
        timer++;
        if (frame < 6 && timer >= duration - 30) {
            m_patternVar3 = 1.0;
        }
        if (timer >= duration) {
            m_patternVar3 = 0.0;
            timer = 0;
            frame++;
            if (frame == 1) {
                effect.type = 0x1ab;
                effect.x = (double)((int)(*m_opponent)->x + facing * 30);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b2;
                effect.x = (double)((int)(*m_opponent)->x - facing * 30);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kLyingDown;
                m_playVoice = 9;
            }
            if (frame == 2) {
                effect.type = 0x1ac;
                effect.x = (double)((int)(*m_opponent)->x + facing * 40);
                effect.y = -40.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.y = 0.0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b3;
                effect.x = (double)((int)(*m_opponent)->x - facing * 30);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kLyingDown;
                m_playVoice = 9;
            }
            if (frame == 3) {
                effect.type = 0x1ad;
                effect.x = (double)((int)(*m_opponent)->x + facing * 60);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b4;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.x = (double)((int)(*m_opponent)->x - facing * 60);
                effect.scale = 2;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kLyingDown;
                m_playVoice = 9;
            }
            if (frame == 4) {
                effect.type = 0x1ae;
                effect.x = (double)((int)(*m_opponent)->x + facing * 30);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b5;
                effect.x = (double)((int)(*m_opponent)->x - facing * 30);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kLyingDown;
                m_playVoice = 9;
            }
            if (frame == 5) {
                effect.type = 0x1af;
                effect.x = (double)((int)(*m_opponent)->x + facing * 60);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b6;
                effect.x = (double)((int)(*m_opponent)->x + facing * 15);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x1b9;
                effect.layer = 0;
                effect.x = (double)((int)(*m_opponent)->x - facing * 65);
                SpawnObject(&effect);
                (*m_opponent)->pattern = kLyingDown;
                m_playVoice = 9;
            }
            if (frame == 6) {
                effect.type = 0x1b0;
                effect.x = (double)((int)(*m_opponent)->x + facing * 60);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                effect.type = 0x1b7;
                effect.x = (double)((int)(*m_opponent)->x - facing * 60);
                effect.y = 0.0;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 0;
                effect.shadow = 1;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kLyingDown;
                m_playVoice = 9;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kHitAirHeavy;
                FaceOpponent();
                StartPattern();
                StopMoving();
                m_hitVy = -3.0;
                m_hitVx = 0.0;
                y = -640.0;
            }
        }
    }
}
