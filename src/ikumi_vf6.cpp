// CIkumi::UpdatePattern and UpdatePatternAlt (0x683550-0x6a59bf): the per-state update, and the second one
// it hands over to while the byte at 0x3460 is 1. They are a file of their own, as in
// the original: their floating-point constants precede the rest of CIkumi's .rdata,
// which starts with its constructor's folder name (ikumi.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CIkumi::UpdatePattern()
{
    WORD frameCount; // frames in the action's animation
    WORD duration; // ticks the current frame lasts

    if (m_altPatternsIn == 1) {
        UpdatePatternAlt();
        return;
    }
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
        vx = 0.8;
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
        vx = -0.8;
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -2.8;
            if (m_dashMomentum == 1) {
                vx = 0.3;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -2.8;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -2.8;
            vx = -0.9;
        }
        if (frame > 2) {
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
        ay = 0.048;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = 0.0;
            if (m_dashMomentum == 1) {
                vx = 0.4;
                m_dashMomentum = 0;
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
        ay = 0.048;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
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
        ay = 0.048;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = -0.7;
            if (m_dashMomentum == 1) {
                m_dashMomentum = 0;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
            m_gauge = m_gauge + 0x1e;
            m_patternVar1++;
            m_untechTime = m_untechTime + 0x78;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            m_playSound = 0x1f;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4 && m_patternVar1 < 8) {
                frame = 0;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
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
            m_playSound = 0x21;
            vx = m_hitVx;
            vy = m_hitVy;
            m_gauge = m_gauge + 0x1e;
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
                m_playSound = 0x21;
                vx = m_hitVx;
                vy = m_hitVy;
                m_gauge = m_gauge + 0x1e;
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount - 1) {
                FaceOpponent();
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
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
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
            vy = -2.6;
            m_gauge = m_gauge + 0xf;
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
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StartAfterimages(1);
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
        vx = 2.5;
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x50 && frame < 4) {
            pattern = kDashStop;
            StartPattern();
        }
        if (m_inputX != facing && m_patternVar1 >= 0x3c && frame < 4) {
            pattern = kDashStop;
            StartPattern();
        }
        break;
    case kDashBack:
        StartAfterimages(3);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = -1.9;
            vy = -1.0;
            ay = 0.04;
        }
        if (frame > 0 && frame < 4) {
            vy = vy + ay;
        }
        if (frame > 1 && vy + y >= 0.0 && m_patternVar1 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            m_patternVar1++;
            m_playSound = 9;
            frame = 4;
            timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
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
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = 1.3;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            m_playSound = 0x11;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = 1.6;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 0x28) {
            pattern = kFall;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = -1.3;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 0x11;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && m_patternVar1 >= 0x28) {
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
            if (ay == 0.0) {
                ay = 0.035;
            }
            vx = 0.0;
            vy = 0.0;
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
            m_freezeTime = 0x5a;
            FillBackground(0xb0, 3);
        }
        if (frame == 0 && timer == 0) {
            m_playSound = 0x12;
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
                ay = 0.035;
                StartPattern();
            }
        }
        break;
    case kDashStop:
        StartAfterimages(1);
        vx -= 0.07;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            m_dashMomentum = 0;
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
                pattern = kStand;
                StartPattern();
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
        if (y + vy > 0.0 && frame < 4) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 4;
            m_playSound = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 4) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                x = facing * 5 + x;
            }
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5C:
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
        if (frame < 2) {
            if (vx > 0.0 && m_dashMomentum == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                m_dashMomentum = 0;
            }
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2) {
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
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.0;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 1) {
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
    case k2C:
        if (frame < 2) {
            if (vx > 0.0 && m_dashMomentum == 1) {
                vx -= 0.03;
            } else {
                vx = 0.0;
                m_dashMomentum = 0;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.5;
        }
        if (frame > 4) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 5 && m_patternVar1 < 2) {
                frame = frame - 2;
                m_patternVar1++;
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
    case kJumpA:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
            m_gauge = m_gauge + 7;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 7;
            m_playSound = 0x14;
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
            if (frame == 1 || frame == 5) {
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
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
        if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = kThrowConnected;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -68.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x19);
            effect.y = (double)((int)y - 0x44);
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
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kThrowConnected:
        if (frame < 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->m_hitstop = 0x3c;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x19);
            effect.y = (double)((int)y - 0x44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(0x384, 750.0);
            m_playVoice = 0;
        }
        if (frame == 2 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -1.2;
            (*m_opponent)->m_hitVy = -1.0;
            (*m_opponent)->y = -15.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kDashA:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        vx -= 0.03;
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
        m_dashMomentum = 0;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
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
    case kDashC:
        StartAfterimages(1);
        m_dashMomentum = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
    case kDash2C:
        if (m_inputY == -1 && frame > 0 && m_attackResult == 3 && m_airActions == 0 && m_sealLevel < 3) {
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
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame == 0) {
            vx -= 0.03;
        }
        if (vx < 0.0 && frame == 0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vy = -1.2;
            vx = 1.0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.025;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 0xb;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
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
            pattern = kAirThrowConnected;
            (*m_opponent)->pattern = kThrownDoubledOver;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x27);
            effect.y = (double)((int)y - 0x4b);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 0x27 + x;
            (*m_opponent)->y = y - 75.0;
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
    case kAirThrowConnected:
        if (frame < 5) {
            FocusCameraX(0x32, 3);
        }
        if (frame < 5) {
            FocusCameraY(0x32, 3);
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 4) {
            StopMoving();
            StartPattern();
            y = 0.0;
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                (*m_opponent)->y = y - 70.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->m_hitstop = 0x3c;
                effect.type = 0xe;
                effect.sound = 4;
                effect.x = (double)((int)x + facing * 0x2a);
                effect.y = (double)((int)y - 0x48);
                effect.scale = 2;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            if (frame == 5 && m_patternVar1 < 5) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 5) {
                ShakeScreen(4, 0);
                (*m_opponent)->y = y - 40.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = kHitAirLaunch;
                DealDamage(0x4b0, 500.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->m_hitVx = -2.0;
                (*m_opponent)->m_hitVy = 0.0;
                ay = 0.035;
                vy = -0.5;
                vx = -2.0;
                effect.type = 0x199;
                effect.x = (double)((int)x + facing * 0x2a);
                effect.y = (double)((int)y - 0x46);
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                m_playVoice = 5;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x193;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
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
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x78);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x193;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
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
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0xb4);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x193;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.1;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 7) {
                m_attackResult = 2;
            }
            if (frame == 8) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.2;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Landing:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case k41236C:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k41236CHold;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x25);
            effect.y = (double)((int)y - 0x2a);
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
    case k41236CHold:
        if (frame == 3 && timer == 0) {
            (*m_opponent)->m_hitstop = 0x5dc;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(0xfa, 1000.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kThrownStandLow2;
            (*m_opponent)->x = facing * 0x28 + x;
            m_playVoice = 4;
        }
        if (frame == 7 && timer == 0) {
            effect.type = 0x1d6;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xc && timer == 0x5a) {
            (*m_opponent)->m_hitstop = 0;
            effect.type = 0x199;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 2;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
            DealDamage(0xfa, 600.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -0.8;
            (*m_opponent)->m_hitVy = -2.8;
            effect.type = 0x1dd;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1dd;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playVoice = 5;
            ShakeScreen(4, 0);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k236BStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 2;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236CStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236BStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 3;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236CStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623BStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.6;
            vy = -1.3;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock3Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623CStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock3Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Stock3Landing:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case k623BStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock6Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623CStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.0;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock6Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Stock6Landing:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case k214AStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19a;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214BStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x78);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19a;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214CStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0xb4);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19a;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214AStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19c;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214BStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x78);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19c;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214CStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0xb4);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19c;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kModeStart:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x2b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        FocusCameraY(0x32, 3);
        if (frame == 4 && timer == 0) {
            effect.type = 0x19e;
            effect.x = (double)((int)x - facing * 5);
            effect.y = (double)((int)y - 0x36);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            ShakeScreen(0xa, 0);
            m_playVoice = 6;
            m_playVoice = 7;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_patternVar3 < 8) {
                    m_patternVar3++;
                    frame = frame - 2;
                    break;
                }
                pattern = kStand;
                StartPattern();
                m_modeTimer = 0x4ec;
                m_stocks = 0xa;
                UseAltPatterns(1);
            }
        }
        break;
    case k4123641236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x58);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k4123641236AHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0xd);
            effect.y = (double)((int)y - 0x41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236AHold:
        if (frame < 0xb) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            effect.type = 0;
            (*m_opponent)->m_hitstop = 0x1e;
            effect.x = (double)((int)x + ((WORD)Random(0, 0x28) + 0xa) * facing);
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1d6;
            effect.x = (double)((int)(*m_opponent)->x + -5 + (WORD)Random(0, 0xa));
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 0;
            effect.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                effect.facing = facing;
            } else {
                effect.facing = -facing;
            }
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                ShakeScreen(3, 0x1e);
                effect.type = 0x19f;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19f;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = -160.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 < 8 && frame == 7) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                DealDamage(0x7d0, 500.0);
                (*m_opponent)->m_hitstop = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x58);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k4123641236BHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0xd);
            effect.y = (double)((int)y - 0x41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236BHold:
        if (frame < 0xb) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            effect.type = 0;
            (*m_opponent)->m_hitstop = 0x1e;
            effect.x = (double)((int)x + ((WORD)Random(0, 0x28) + 0xa) * facing);
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1d6;
            effect.x = (double)((int)(*m_opponent)->x + -5 + (WORD)Random(0, 0xa));
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 0;
            effect.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                effect.facing = facing;
            } else {
                effect.facing = -facing;
            }
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                ShakeScreen(3, 0x1e);
                effect.type = 0x1a0;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a0;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = -160.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 < 0xc && frame == 7) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                DealDamage(0xbb8, 500.0);
                (*m_opponent)->m_hitstop = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x58);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k4123641236CHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0xd);
            effect.y = (double)((int)y - 0x41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236CHold:
        if (frame < 0xb) {
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xb) {
            m_game->FlashNegative(0xf);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            effect.type = 0;
            (*m_opponent)->m_hitstop = 0x1e;
            effect.x = (double)((int)x + ((WORD)Random(0, 0x28) + 0xa) * facing);
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1de;
            effect.x = (double)((int)(*m_opponent)->x + -5 + (WORD)Random(0, 0xa));
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                ShakeScreen(4, 0x1e);
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = -160.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 < 0xc && frame == 7) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                DealDamage(0x1004, 500.0);
                (*m_opponent)->m_hitstop = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 4);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x1a4;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 1;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 2) {
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
    case k214214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 4);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x1a5;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 1;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 2) {
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
    case k214214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 4);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x1a6;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 1;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 2) {
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
    case k21436A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                m_storedSuperLevel = 1;
                m_playVoice = 0xa;
                effect.type = 0x1a7;
                effect.x = (double)((int)x + facing * 0x29);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
                m_attackResult = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                m_storedSuperLevel = 2;
                m_playVoice = 0xa;
                effect.type = 0x1a7;
                effect.x = (double)((int)x + facing * 0x29);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
                m_attackResult = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                m_storedSuperLevel = 3;
                m_playVoice = 0xa;
                effect.type = 0x1a7;
                effect.x = (double)((int)x + facing * 0x29);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
                m_attackResult = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436Release1:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                m_storedSuperLevel = 0;
                effect.type = 0x1a8;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436Release2:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                m_storedSuperLevel = 0;
                effect.type = 0x1aa;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436Release3:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 3 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                m_storedSuperLevel = 0;
                effect.type = 0x1ab;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436AMode:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                effect.type = 0x1a8;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 6) {
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
    case k21436BMode:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                effect.type = 0x1aa;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 6) {
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
    case k21436CMode:
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x - facing * 0xb);
            effect.y = (double)((int)y - 0x65);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                effect.type = 0x1ab;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 6) {
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
    case kLv4:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_hitsLeft = 1;
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x + facing * 0x12);
            effect.y = (double)((int)y - 0x19);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
        }
        m_game->FlashNegative(0xf);
        if (frame < 4) {
            FocusCameraY(0x32, 0xa);
        }
        if (frame == 0xd && m_attackResult == 3) {
            StartAfterimages(0);
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            pattern = kLv4Connected;
            m_hideOffscreenMarker = 3;
            m_koDelay = 3;
            break;
        }
        if (frame == 0xd && m_attackResult != 3 && m_attackResult > 0) {
            StartAfterimages(0);
            timer = 0;
            frame = 0xe;
            break;
        }
        if (frame == 0xd && timer == 0) {
            vx = 5.0;
        }
        if (frame == 0xe && timer == 0) {
            vx = 1.5;
        }
        if (frame > 3 && vx > 0.0) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4Connected:
        m_hideOffscreenMarker = 3;
        if (m_patternVar2 == 0) {
            (*m_opponent)->m_koDelay = 3;
        }
        if (frame == 0 && timer == 0) {
            x = (*m_opponent)->x;
        }
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 6) {
            (*m_opponent)->FocusCameraY(0x32, 5);
            (*m_opponent)->FocusCameraX(0x32, 5);
        }
        if (frame > 5) {
            FocusCameraY(0x32, 5);
            FocusCameraX(0x32, 5);
        }
        if (frame < 6) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 6 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x + facing * 6);
            effect.y = (double)((int)y - 0x30);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 1 && timer == 0) {
            effect.type = 0x1af;
            effect.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            effect.y = (double)((int)(*m_opponent)->y + 0xa0);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 2 && timer == 0) {
            effect.type = 0x1b0;
            effect.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            effect.y = (double)((int)(*m_opponent)->y + 0x78);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = -facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x1b1;
            effect.x = (double)((int)(*m_opponent)->x - facing * 0xa0);
            effect.y = (double)((int)(*m_opponent)->y + 0x118);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 4 && timer == 0) {
            effect.type = 0x1b2;
            effect.x = (double)((int)(*m_opponent)->x + facing * 0xa0);
            effect.y = (double)((int)(*m_opponent)->y + 0x118);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = -facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 0x15 && timer == 0) {
            effect.type = 0x1b3;
            effect.x = (double)((int)x - facing * 0x186);
            effect.y = (double)((int)y - 0x14a);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = facing;
            effect.shadow = 1;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.type = 0x1b4;
            effect.x = (double)((int)x - facing * 0xc3);
            effect.y = (double)((int)y - 0x1ef);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = facing;
            effect.shadow = 1;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.type = 0x1b5;
            effect.x = (double)((int)x + facing * 0x186);
            effect.y = (double)((int)y - 0x14a);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = -facing;
            effect.shadow = 1;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.type = 0x1b6;
            effect.x = (double)((int)x + facing * 0xc3);
            effect.y = (double)((int)y - 0x1ef);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = -facing;
            effect.shadow = 1;
            effect.layer = 0;
            SpawnObject(&effect);
        }
        if (frame == 8 && timer == 0) {
            effect.type = 0x1b7;
            effect.x = (double)((int)x + facing * 0xe);
            effect.y = (double)((int)y + 8);
            effect.scale = 2;
            effect.keep = 1;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 0x16 && m_patternVar1 == 1) {
            frame = 0x17;
            timer = 0;
            m_patternVar1 = 2;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 0xc && m_patternVar1 < 5) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                m_hideOffscreenMarker = 0;
                FaceOpponent();
                StartPattern();
            }
        }
    }
}

void CIkumi::UpdatePatternAlt()
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
        vx = 0.8;
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
        vx = -0.8;
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -2.8;
            if (m_dashMomentum == 1) {
                vx = 0.3;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -2.8;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -2.8;
            vx = -0.9;
        }
        if (frame > 2) {
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
        ay = 0.048;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = 0.0;
            if (m_dashMomentum == 1) {
                vx = 0.4;
                m_dashMomentum = 0;
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
        ay = 0.048;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
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
        ay = 0.048;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = -0.7;
            if (m_dashMomentum == 1) {
                m_dashMomentum = 0;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
            m_gauge = m_gauge + 0x1e;
            m_patternVar1++;
            m_untechTime = m_untechTime + 0x78;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            m_playSound = 0x1f;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4 && m_patternVar1 < 8) {
                frame = 0;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
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
            m_playSound = 0x21;
            vx = m_hitVx;
            vy = m_hitVy;
            m_gauge = m_gauge + 0x1e;
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
                m_playSound = 0x21;
                vx = m_hitVx;
                vy = m_hitVy;
                m_gauge = m_gauge + 0x1e;
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == frameCount - 1) {
                FaceOpponent();
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
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
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
            vy = -2.6;
            m_gauge = m_gauge + 0xf;
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
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StartAfterimages(1);
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
        vx = 2.5;
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x50 && frame < 4) {
            pattern = kDashStop;
            StartPattern();
        }
        if (m_inputX != facing && m_patternVar1 >= 0x3c && frame < 4) {
            pattern = kDashStop;
            StartPattern();
        }
        break;
    case kDashBack:
        StartAfterimages(3);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = -1.9;
            vy = -1.0;
            ay = 0.04;
        }
        if (frame > 0 && frame < 4) {
            vy = vy + ay;
        }
        if (frame > 1 && vy + y >= 0.0 && m_patternVar1 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            m_patternVar1++;
            m_playSound = 9;
            frame = 4;
            timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
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
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = 1.3;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            m_playSound = 0x11;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = 1.6;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 0x28) {
            pattern = kFall;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = -1.3;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 0x11;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && m_patternVar1 >= 0x28) {
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
            if (ay == 0.0) {
                ay = 0.035;
            }
            vx = 0.0;
            vy = 0.0;
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
            m_freezeTime = 0x5a;
            FillBackground(0xb0, 3);
        }
        if (frame == 0 && timer == 0) {
            m_playSound = 0x12;
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
                ay = 0.035;
                StartPattern();
            }
        }
        break;
    case kDashStop:
        StartAfterimages(1);
        vx -= 0.07;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            m_dashMomentum = 0;
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
                pattern = kStand;
                StartPattern();
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
        if (y + vy > 0.0 && frame < 4) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 4;
            m_playSound = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 4) {
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
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                x = facing * 5 + x;
            }
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5C:
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
        if (frame < 2) {
            if (vx > 0.0 && m_dashMomentum == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                m_dashMomentum = 0;
            }
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2) {
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
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.0;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 1) {
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
    case k2C:
        if (frame < 2) {
            if (vx > 0.0 && m_dashMomentum == 1) {
                vx -= 0.03;
            } else {
                vx = 0.0;
                m_dashMomentum = 0;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.5;
        }
        if (frame > 4) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 5 && m_patternVar1 < 2) {
                frame = frame - 2;
                m_patternVar1++;
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
    case kJumpA:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
            m_gauge = m_gauge + 7;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 7;
            m_playSound = 0x14;
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
            if (frame == 1 || frame == 5) {
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
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
        if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = kThrowConnected;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -68.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x19);
            effect.y = (double)((int)y - 0x44);
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
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kThrowConnected:
        if (frame < 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->m_hitstop = 0x3c;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x19);
            effect.y = (double)((int)y - 0x44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(0x384, 750.0);
            m_playVoice = 0;
        }
        if (frame == 2 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -1.2;
            (*m_opponent)->m_hitVy = -1.0;
            (*m_opponent)->y = -15.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kDashA:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        vx -= 0.03;
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
        m_dashMomentum = 0;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
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
    case kDashC:
        StartAfterimages(1);
        m_dashMomentum = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
    case kDash2C:
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions == 0) {
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
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame == 0) {
            vx -= 0.03;
        }
        if (vx < 0.0 && frame == 0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vy = -1.2;
            vx = 1.0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.025;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 0xb;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
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
            pattern = kAirThrowConnected;
            (*m_opponent)->pattern = kThrownDoubledOver;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x27);
            effect.y = (double)((int)y - 0x4b);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 0x27 + x;
            (*m_opponent)->y = y - 75.0;
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
    case kAirThrowConnected:
        if (frame < 5) {
            FocusCameraX(0x32, 3);
        }
        if (frame < 5) {
            FocusCameraY(0x32, 3);
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 4) {
            StopMoving();
            StartPattern();
            y = 0.0;
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                (*m_opponent)->y = y - 70.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->m_hitstop = 0x3c;
                effect.type = 0xe;
                effect.sound = 4;
                effect.x = (double)((int)x + facing * 0x2a);
                effect.y = (double)((int)y - 0x48);
                effect.scale = 2;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            if (frame == 5 && m_patternVar1 < 5) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 5) {
                ShakeScreen(4, 0);
                (*m_opponent)->y = y - 40.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = kHitAirLaunch;
                DealDamage(0x578, 500.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->m_hitVx = -2.0;
                (*m_opponent)->m_hitVy = 0.0;
                ay = 0.035;
                vy = -0.5;
                vx = -2.0;
                effect.type = 0x199;
                effect.x = (double)((int)x + facing * 0x2a);
                effect.y = (double)((int)y - 0x46);
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                m_playVoice = 5;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x193;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
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
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x78);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x193;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
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
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0xb4);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x193;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.1;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.2;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Landing:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case k41236C:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k41236CHold;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x25);
            effect.y = (double)((int)y - 0x2a);
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
    case k41236CHold:
        if (frame == 3 && timer == 0) {
            (*m_opponent)->m_hitstop = 0x5dc;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(0xfa, 1000.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kThrownStandLow2;
            (*m_opponent)->x = facing * 0x28 + x;
            m_playVoice = 4;
        }
        if (frame == 7 && timer == 0) {
            effect.type = 0x1d6;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xc && timer == 0x5a) {
            (*m_opponent)->m_hitstop = 0;
            effect.type = 0x199;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 2;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
            DealDamage(0x1f4, 700.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -0.8;
            (*m_opponent)->m_hitVy = -2.8;
            effect.type = 0x1dd;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1dd;
            effect.x = (double)((int)x + facing * 0x2b);
            effect.y = (double)((int)y - 0x2e);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playVoice = 5;
            ShakeScreen(4, 0);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k236BStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 2;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236CStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236BStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 3;
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236CStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x191;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && m_patternVar1 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 1) {
                frame = 0;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623BStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.6;
            vy = -1.3;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock3Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623CStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock3Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Stock3Landing:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case k623BStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock6Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623CStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.0;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = k623Stock6Landing;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            effect.type = 0x190;
            effect.x = (double)(int)x;
            effect.y = y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Stock6Landing:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case k214AStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19a;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214BStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x78);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19a;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214CStock3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0xb4);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19a;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214AStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19c;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214BStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0x78);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19c;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214CStock6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 0xb4);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19c;
                SpawnObject(&effect);
                ShakeScreen(2, 0);
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kModeStart:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x2b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        FocusCameraY(0x32, 3);
        if (frame == 4 && timer == 0) {
            effect.type = 0x19e;
            effect.x = (double)((int)x - facing * 5);
            effect.y = (double)((int)y - 0x36);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            ShakeScreen(0xa, 0);
            m_playVoice = 6;
            m_playVoice = 7;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_patternVar3 < 8) {
                    m_patternVar3++;
                    frame = frame - 2;
                    break;
                }
                pattern = kStand;
                StartPattern();
                m_modeTimer = 0x4ec;
                m_stocks = 0xa;
                UseAltPatterns(1);
            }
        }
        break;
    case k4123641236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x58);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k4123641236AHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0xd);
            effect.y = (double)((int)y - 0x41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236AHold:
        if (frame < 0xb) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            effect.type = 0;
            (*m_opponent)->m_hitstop = 0x1e;
            effect.x = (double)((int)x + ((WORD)Random(0, 0x28) + 0xa) * facing);
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1d6;
            effect.x = (double)((int)(*m_opponent)->x + -5 + (WORD)Random(0, 0xa));
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 0;
            effect.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                effect.facing = facing;
            } else {
                effect.facing = -facing;
            }
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                ShakeScreen(3, 0x1e);
                effect.type = 0x19f;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19f;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = -160.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 < 8 && frame == 7) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                DealDamage(0xaf0, 500.0);
                (*m_opponent)->m_hitstop = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x58);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k4123641236BHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0xd);
            effect.y = (double)((int)y - 0x41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236BHold:
        if (frame < 0xb) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            effect.type = 0;
            (*m_opponent)->m_hitstop = 0x1e;
            effect.x = (double)((int)x + ((WORD)Random(0, 0x28) + 0xa) * facing);
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1d6;
            effect.x = (double)((int)(*m_opponent)->x + -5 + (WORD)Random(0, 0xa));
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 0;
            effect.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                effect.facing = facing;
            } else {
                effect.facing = -facing;
            }
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                ShakeScreen(3, 0x1e);
                effect.type = 0x1a0;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a0;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = -160.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 < 0xc && frame == 7) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                DealDamage(0xed8, 500.0);
                (*m_opponent)->m_hitstop = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x58);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = k4123641236CHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            FocusCameraY(0x32, 0x1e);
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0xd);
            effect.y = (double)((int)y - 0x41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k4123641236CHold:
        if (frame < 0xb) {
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xb) {
            m_game->FlashNegative(0xf);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            effect.type = 0;
            (*m_opponent)->m_hitstop = 0x1e;
            effect.x = (double)((int)x + ((WORD)Random(0, 0x28) + 0xa) * facing);
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1de;
            effect.x = (double)((int)(*m_opponent)->x + -5 + (WORD)Random(0, 0xa));
            effect.y = (double)((int)y - 0x32 - (WORD)Random(0, 0x14));
            effect.scale = 0;
            effect.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                effect.facing = facing;
            } else {
                effect.facing = -facing;
            }
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                ShakeScreen(4, 0x1e);
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 0x1e);
                effect.y = -160.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 < 0xc && frame == 7) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                DealDamage(0x157c, 500.0);
                (*m_opponent)->m_hitstop = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 4);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x1a4;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 1;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 5) {
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
    case k214214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 4);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x1a5;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 1;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 5) {
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
    case k214214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 4);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                effect.type = 0x1a6;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 1;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 5) {
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
    case k21436A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                m_storedSuperLevel = 1;
                m_playVoice = 0xa;
                effect.type = 0x1a7;
                effect.x = (double)((int)x + facing * 0x29);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 3) {
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
    case k21436B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                m_storedSuperLevel = 2;
                m_playVoice = 0xa;
                effect.type = 0x1a7;
                effect.x = (double)((int)x + facing * 0x29);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 3) {
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
    case k21436C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                m_storedSuperLevel = 3;
                m_playVoice = 0xa;
                effect.type = 0x1a7;
                effect.x = (double)((int)x + facing * 0x29);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 3) {
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
    case k21436Release1:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                m_storedSuperLevel = 0;
                effect.type = 0x1a8;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436Release2:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                m_storedSuperLevel = 0;
                effect.type = 0x1aa;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436Release3:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 3 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x + facing * 0x1f);
            effect.y = (double)((int)y - 0x34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                m_storedSuperLevel = 0;
                effect.type = 0x1ab;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436AMode:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                effect.type = 0x1a8;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 6) {
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
    case k21436BMode:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                effect.type = 0x1aa;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x19);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x2d);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 6) {
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
    case k21436CMode:
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)((int)x - facing * 0xb);
            effect.y = (double)((int)y - 0x65);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0xe;
            effect.sound = 4;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x3b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                effect.type = 0x1ab;
                effect.x = (double)(int)(*m_opponent)->x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x23);
                effect.y = -10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x46);
                effect.y = 0.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x + 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
                effect.type = 0x1a9;
                effect.x = (double)((int)(*m_opponent)->x - 0x28);
                effect.y = 10.0;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x1a7;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame == 0x10 && m_patternVar1 < 6) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
    }
}
