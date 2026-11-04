// CEXNanase::UpdatePattern (0x6be9c0-0x6cfbaf), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CEXNanase's
// .rdata, which starts with its constructor's folder name (exnanase.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CEXNanase::UpdatePattern()
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
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
            }
        }
        break;
    case kWalkForward:
        m_dashMomentum = 0;
        vx = (m_awakened == 1) * 0.15 + 0.9;
        vy = 0.0;
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
            }
        }
        break;
    case kWalkBack:
        m_dashMomentum = 0;
        vx = -0.9 - (m_awakened == 1) * 0.15;
        vy = 0.0;
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            ay = (m_awakened == 1) * 0.015 + 0.045;
            vy = -2.7 - (m_awakened == 1) * 0.6;
            if (m_dashMomentum == 1) {
                vx = 0.4;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            ay = (m_awakened == 1) * 0.015 + 0.045;
            vy = -2.7 - (m_awakened == 1) * 0.6;
            vx = (m_awakened == 1) * 0.1 + 0.8;
            if (m_dashMomentum == 1) {
                vx = 1.2;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            ay = (m_awakened == 1) * 0.015 + 0.045;
            vy = -2.7 - (m_awakened == 1) * 0.6;
            vx = -0.8 - (m_awakened == 1) * 0.1;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        ay = (m_awakened == 1) * 0.015 + 0.045;
        if (frame == 0 && timer == 0) {
            vy = -2.7 - (m_awakened == 1) * 0.6;
            vx = 0.0;
            m_dashMomentum = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        ay = (m_awakened == 1) * 0.015 + 0.045;
        if (frame == 0 && timer == 0) {
            vy = -2.7 - (m_awakened == 1) * 0.6;
            vx = (m_awakened == 1) * 0.1 + 0.8;
            m_dashMomentum = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        ay = (m_awakened == 1) * 0.015 + 0.045;
        if (frame == 0 && timer == 0) {
            vy = -2.7 - (m_awakened == 1) * 0.6;
            vx = -0.8 - (m_awakened == 1) * 0.1;
            m_dashMomentum = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            vx = 0.6;
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
            m_gauge = m_gauge + 30;
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
            m_gauge = m_gauge + 30;
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
            m_gauge = m_gauge + 30;
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
            m_gauge = m_gauge + 30;
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
        if (m_hp > 0 && timer > 99 && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
            m_dashMomentum = 0;
            break;
        }
        timer++;
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
        vx = (m_awakened == 1) * 0.2 + 1.7;
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 120) {
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
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -1.6 - (m_awakened == 1) * 0.2;
            vy = -1.0;
            ay = 0.04;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            m_playSound = 9;
            StopMoving();
            y = 0.0;
            frame = 9;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0) {
            m_playSound = 21;
            if (m_patternVar1 == 0) {
                vx = (m_awakened == 1) * 0.2 + 1.5;
                StartAfterimages(3);
                vy = 0.0;
                ay = 0.0;
            }
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 100) {
            pattern = kFall;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 48) {
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
        if (frame == 0 && timer == 0) {
            m_playSound = 21;
            if (m_patternVar1 == 0) {
                vx = -1.5 - (m_awakened == 1) * 0.2;
                vy = 0.0;
                ay = 0.0;
                StartAfterimages(3);
            }
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && m_patternVar2 >= 120) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && m_patternVar1 >= 40) {
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
            vx = 0.0;
            vy = 0.0;
            m_dashMomentum = 0;
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
            if (ay == 0.0) {
                ay = 0.035;
            }
            m_recoilGuardWindow = 0;
            m_cornerPushback = 0.0;
            m_freezeTime = 60;
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
        if (y + vy > 0.0 && frame < 9) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 9;
            m_playSound = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 9) {
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
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                x = facing * 10 + x;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5C:
        if (m_dashMomentum == 0 && frame < 2) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && m_dashMomentum == 1 && frame < 2) {
            vx -= 0.06;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
            vx = 2.0;
        }
        if (frame > 2 && vx > 0.0) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
    case k2C:
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
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            m_hitsLeft = 2;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kJumpA:
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
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
        if (frame == 3 && timer == 0) {
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
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kJump;
                StartPattern();
                frame = 7;
            }
        }
        break;
    case kJumpC:
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
        if (frame == 4 && timer == 0) {
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
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kJump;
                StartPattern();
                frame = 7;
            }
        }
        break;
    case k6C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 3.0;
        }
        vx -= 0.055;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 20;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
    case kUnusedD3:
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
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
    case kAirDiveUnused:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = kAirDiveRebound;
            StartPattern();
            StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.sound = 7;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
            pattern = kAirDiveLanding;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kAirDiveRebound:
        ay = 0.042;
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = -1.0;
            vy = -2.4;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kAirDiveLanding:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.sound = 7;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
            if (x > 580.0) {
                x = 580.0;
            }
            if (x < 60.0) {
                x = 60.0;
            }
            StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = kThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->x = facing * 40 + x;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
    case kThrowHit:
        FocusCameraY(50, 3);
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 1.0;
            vy = -2.0;
            ay = 0.04;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame == 4) {
            y = 0.0;
            StopMoving();
            frame = 5;
            timer = 0;
            break;
        }
        if (x > 600.0 || x < 40.0) {
            vx = 0.0;
        }
        if (frame == 1) {
            (*m_opponent)->x = facing * 35 + x;
        }
        if (frame == 2) {
            (*m_opponent)->x = facing * 30 + x;
            (*m_opponent)->y = y - 68.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
        }
        if (frame == 3) {
            (*m_opponent)->x = facing * 25 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
        }
        if (frame == 4) {
            (*m_opponent)->x = facing * 10 + x;
            (*m_opponent)->y = y - 90.0;
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->StartPattern();
        }
        if (frame == 5) {
            (*m_opponent)->x = facing * 30 + x;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->pattern = kThrownUpsideDown;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kKnockdown;
                (*m_opponent)->StartPattern();
                DealDamage(1200, 750.0);
            }
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
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 20;
            m_gauge = m_gauge + 20;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
    case kDashB:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 20;
            m_gauge = m_gauge + 20;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
    case kDashC:
        m_dashMomentum = 0;
        StartAfterimages(3);
        if (vx > 0.0 && frame > 3) {
            vx -= 0.035;
        } else {
            m_dashMomentum = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 20;
            m_gauge = m_gauge + 20;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 20;
            m_gauge = m_gauge + 20;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kDash2C:
        StartAfterimages(3);
        m_dashMomentum = 0;
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
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 20;
            m_gauge = m_gauge + 20;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
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
    case kAirThrow:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            frame = 0;
            timer = 0;
            pattern = kAirThrowHit;
            (*m_opponent)->x = facing * 25 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
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
                frame = 2;
            }
        }
        break;
    case kAirThrowHit:
        m_hideOffscreenMarker = 30;
        (*m_opponent)->m_hideOffscreenMarker = 30;
        FocusCameraY(50, 3);
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            vx = 1.0;
            vy = -2.0;
            ay = 0.04;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame == 1) {
            y = 0.0;
            StopMoving();
            frame = 2;
            timer = 0;
            break;
        }
        if (x > 600.0 || x < 40.0) {
            vx = 0.0;
        }
        if (frame == 0) {
            (*m_opponent)->x = facing * 25 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
        }
        if (frame == 1) {
            (*m_opponent)->x = facing * 10 + x;
            (*m_opponent)->y = y - 90.0;
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->StartPattern();
        }
        if (frame == 2) {
            (*m_opponent)->x = facing * 30 + x;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->pattern = kThrownUpsideDown;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kKnockdown;
                (*m_opponent)->StartPattern();
                DealDamage(1400, 500.0);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k41236C:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->m_hitstop = 90;
            (*m_opponent)->x = facing * 40 + x;
            (*m_opponent)->m_noAirRecovery = 1;
            (*m_opponent)->StopMoving();
            timer = 0;
            frame = 3;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)((int)y - 41);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kFirstGuard)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame == 4) {
                frame = 0;
                pattern = kGrabHold;
                frame = 1;
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -81.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                break;
            }
            if (frame == 3) {
                frame = 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kGrabFollowB:
        StopMoving();
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 11 + x;
                (*m_opponent)->y = -62.0;
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = x - facing * 11;
                (*m_opponent)->y = -57.0;
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                (*m_opponent)->x = x - facing * 11;
                (*m_opponent)->y = -52.0;
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = x - facing * 25;
                (*m_opponent)->y = -55.0;
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->StartPattern();
            }
            if (frame == 5) {
                (*m_opponent)->x = x - facing * 37;
                (*m_opponent)->y = -54.0;
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->m_hitVx = 0.5;
                (*m_opponent)->m_hitVy = -2.6;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k41236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (m_attackResult == 3) {
            FocusCameraY(50, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 50 + x;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = kGrabHold;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 5 && timer == 0) {
                x = facing * 15 + x;
            }
            if (frame == 6 && (*m_opponent)->y == 0.0) {
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
    case k41236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (m_attackResult == 3) {
            FocusCameraY(50, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 40 + x;
            (*m_opponent)->y = -80.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            StartPattern();
            pattern = kGrabHold;
            frame = 2;
            (*m_opponent)->m_noAirRecovery = 1;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6 && (*m_opponent)->y < 0.0) {
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
    case kGrabHold:
        FocusCameraY(50, 3);
        if (m_patternVar1 == 0 && frame == 2) {
            if ((*m_opponent)->m_pressA == 1) {
                m_patternVar1 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                m_patternVar1 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                m_patternVar1 = 3;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -81.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_noAirRecovery = 1;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -80.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_noAirRecovery = 1;
            }
            if (frame >= frameCount) {
                pattern = kGrabRelease;
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_noAirRecovery = 1;
                if (m_command == kCmd236A || m_command == kCmd214A) {
                    pattern = kGrabFollowA;
                    frame = 0;
                    timer = 0;
                    (*m_opponent)->pattern = kThrownDoubledOver;
                    if (m_patternVar1 == 3) {
                        StartPattern();
                        pattern = kGrabEscaped;
                        m_playSound = 26;
                        (*m_opponent)->pattern = kAirRecoveryBack;
                        (*m_opponent)->StartPattern();
                        (*m_opponent)->StopMoving();
                        break;
                    }
                    break;
                }
                if (m_command == kCmd236B || m_command == kCmd214B) {
                    if (m_patternVar1 == 2) {
                        StartPattern();
                        pattern = kGrabEscaped;
                        m_playSound = 26;
                        (*m_opponent)->pattern = kAirRecoveryBack;
                        (*m_opponent)->StartPattern();
                        (*m_opponent)->StopMoving();
                        break;
                    }
                    pattern = kGrabFollowB;
                    (*m_opponent)->pattern = kThrownDoubledOver;
                    frame = 1;
                    timer = 0;
                    (*m_opponent)->x = facing * 11 + x;
                    (*m_opponent)->y = -62.0;
                    (*m_opponent)->pattern = kThrownStandHigh;
                    break;
                }
                (*m_opponent)->y = -40.0;
                frame = 0;
                timer = 0;
            }
        }
        break;
    case kGrabFollowA:
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_patternVar1 = 0;
        }
        StopMoving();
        if (frame == 6 && timer == 0) {
            DealDamage(1500, 1000.0);
            m_playSound = 2;
            effect.type = 0;
            effect.x = (double)((int)x - facing * 7);
            effect.y = (double)((int)y + 7);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame < 10 && m_patternVar1 == 0) {
            if ((*m_opponent)->m_pressA == 1) {
                m_patternVar1 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                m_patternVar1 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                m_patternVar1 = 3;
            }
        }
        if (frame == 10 && timer == 0) {
            if ((m_command == kCmd236A || m_command == kCmd214A) && m_gauge >= 1000) {
                if (m_patternVar1 == 3) {
                    StartPattern();
                    pattern = kGrabEscaped;
                    m_playSound = 26;
                    (*m_opponent)->pattern = kAirRecoveryBack;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->StopMoving();
                    break;
                }
                frame = 0;
                timer = 0;
                pattern = kGrabFollowAA;
                break;
            }
            if ((m_command == kCmd236B || m_command == kCmd214B) && m_gauge >= 1000) {
                if (m_patternVar1 == 2) {
                    StartPattern();
                    pattern = kGrabEscaped;
                    m_playSound = 26;
                    (*m_opponent)->pattern = kAirRecoveryBack;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->StopMoving();
                    break;
                }
                frame = 0;
                timer = 0;
                pattern = kGrabFollowAB;
                facing = -facing;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 36 + x;
                (*m_opponent)->y = -78.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 43 + x;
                (*m_opponent)->y = -75.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                (*m_opponent)->x = facing * 45 + x;
                (*m_opponent)->y = -69.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = facing * 23 + x;
                (*m_opponent)->y = -66.0;
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->StartPattern();
                (*m_opponent)->facing = facing;
            }
            if (frame == 5) {
                (*m_opponent)->x = x - facing * 10;
                (*m_opponent)->y = -62.0;
                (*m_opponent)->pattern = kThrownUpsideDown;
                (*m_opponent)->StartPattern();
            }
            if (frame == 6) {
                (*m_opponent)->x = x - 0.0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kKnockdown;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kGrabFollowUnused:
        if (frame == 0 && timer == 0 && m_patternVar1 == 1) {
            StartPattern();
            pattern = kGrabEscaped;
            m_playSound = 26;
            (*m_opponent)->pattern = kAirRecoveryBack;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            break;
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = -3.0;
            (*m_opponent)->m_hitVy = -2.0;
            (*m_opponent)->x = facing * 30 + x;
            (*m_opponent)->y = -40.0;
            ShakeScreen(10, 10);
            DealDamage(1800, 700.0);
            m_attackResult = 3;
            m_playVoice = 2;
            effect.type = 0x190;
            effect.x = (double)((int)x + facing * 40);
            effect.y = (double)((int)y - 80);
            effect.scale = 2;
            effect.facing = facing;
            effect.keep = 1;
            effect.layer = 1;
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
    case kGrabRelease:
        FocusCameraY(50, 3);
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 30;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kGrabEscaped:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
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
    case kGrabExUnused:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x - facing * 10);
            effect.y = (double)((int)y - 56);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        if (frame > 5) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult == 3 && frame == 6) {
            StopMoving();
            FocusCameraY(50, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 50 + x;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = kGrabHold;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 69);
            effect.y = (double)((int)y - 35);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 3) {
                vx = 1.3;
            }
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
            vy = 0.0;
            m_dashMomentum = 0;
            m_attackResult = 0;
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 8) {
                m_playVoice = 1;
                effect.type = 0x191;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 58);
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 1;
                SpawnObject(&effect);
                m_gauge = m_gauge + 30;
            }
            if (frame == 10 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 2;
                if (m_patternVar1 == 2) {
                    m_attackResult = 3;
                }
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214B:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 8 && timer == 0) {
            m_playVoice = 1;
            effect.type = 0x192;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 58);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_gauge = m_gauge + 30;
            }
            if (frame == 10 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x - facing * 10);
            effect.y = (double)((int)y - 56);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 8 && timer == 0) {
            m_playVoice = 1;
            effect.type = 0x193;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 58);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_gauge = m_gauge + 30;
            }
            if (frame == 10 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 3) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 3) {
            if (m_attackResult > 0 && m_patternVar2 == 0) {
                m_patternVar3 = 45;
                m_patternVar2 = 1;
            }
            if (m_attackResult > 0 && m_patternVar3 > 0) {
                m_patternVar3--;
            }
            if (m_attackResult > 0 && m_patternVar3 <= 0 && m_patternVar2 > 0) {
                m_attackResult = 0;
                m_patternVar2 = 0;
            }
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 4) {
                effect.type = 0x194;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 0;
                SpawnObject(&effect);
                m_gauge = m_gauge + 30;
            }
            if (frame == 4) {
                vx = 2.5;
                m_hitsLeft = 3;
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 3) {
            vx -= 0.018;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 3) {
            if (m_attackResult > 0 && m_patternVar2 == 0) {
                m_patternVar3 = 45;
                m_patternVar2 = 1;
            }
            if (m_attackResult > 0 && m_patternVar3 > 0) {
                m_patternVar3--;
            }
            if (m_attackResult > 0 && m_patternVar3 <= 0 && m_patternVar2 > 0) {
                m_attackResult = 0;
                m_patternVar2 = 0;
            }
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 4) {
                effect.type = 0x195;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 0;
                SpawnObject(&effect);
                m_gauge = m_gauge + 30;
            }
            if (frame == 4) {
                vx = 2.8;
                m_hitsLeft = 3;
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar1 < 7) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x - facing * 10);
            effect.y = (double)((int)y - 56);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        if (frame > 7) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                m_invulTime = 60;
                effect.type = 0x196;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 0;
                SpawnObject(&effect);
                m_gauge = m_gauge + 30;
            }
            if (frame == 4) {
                m_hitsLeft = 15;
            }
            if (frame == 8 && m_patternVar1 < 5) {
                m_patternVar1++;
                frame = frame - 4;
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouchDown;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kGrabFollowAA:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            m_patternVar1 = 0;
        }
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 10 && m_patternVar1 == 0) {
            if ((*m_opponent)->m_pressA == 1) {
                m_patternVar1 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                m_patternVar1 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                m_patternVar1 = 3;
            }
        }
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 56);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame < 14) {
            m_koDelay = 3;
        }
        if ((frame == 2 || frame == 5 || frame == 8 || frame == 11 || frame == 14) && timer == 0) {
            m_playSound = 2;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y + 7);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (frame == 2 || frame == 5 || frame == 8 || frame == 11) {
                DealDamage(50, 1000.0);
                ShakeScreen(2, 2);
            }
            if (frame == 14) {
                DealDamage(500, 1000.0);
                ShakeScreen(10, 10);
                m_koDelay = 0;
            }
        }
        if (frame > 1 && frame < 8 && (m_command == kCmd236236A || m_command == kCmd214214A) && m_gauge >= 1000) {
            if (m_patternVar1 == 3) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 26;
                (*m_opponent)->pattern = kAirRecoveryBack;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = kGrabFollowAAA;
            break;
        }
        if (frame > 1 && frame < 8 && (m_command == kCmd236236B || m_command == kCmd214214B) && m_gauge >= 1000) {
            if (m_patternVar1 == 2) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 26;
                (*m_opponent)->pattern = kAirRecoveryBack;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = kGrabFollowAAB;
            facing = -facing;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && m_patternVar2 < 10) {
                m_patternVar2++;
                frame = 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kGrabFollowUnused2:
        if (frame == 0 && timer == 0) {
            if (m_patternVar1 == 1) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 26;
                (*m_opponent)->pattern = kAirRecoveryBack;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
        }
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        FocusCameraY(50, 3);
        if (frame == 2 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 6);
            effect.y = (double)((int)y - 36);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && timer == 0) {
            DealDamage(2400, 600.0);
            ShakeScreen(5, 5);
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = -3.0;
            (*m_opponent)->m_hitVy = -8.0;
            m_playVoice = 2;
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
    case kGrabFollowAAA:
        if (frame < 7) {
            m_koDelay = 3;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        if (frame == 6 && timer == 60) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 1800);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 87);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 6 && timer == 180) {
            effect.type = 0x19a;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 87);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = 1;
            SpawnObject(&effect);
            m_playVoice = 4;
        }
        if (frame == 6 && (timer == 270 || timer == 315 || timer == 360 || timer == 390 || timer == 420 || timer == 450 || timer == 465 || timer == 480)) {
            effect.type = 0x199;
            effect.x = (double)((int)x + ((WORD)Random(0, 80) + 7) * facing);
            effect.y = (double)((int)y - 57 - (WORD)Random(0, 80));
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = 1;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->facing = -facing;
                (*m_opponent)->x = facing * 46 + x;
                (*m_opponent)->y = -38.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = facing * 49 + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 5) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
                (*m_opponent)->StartPattern();
            }
            if (frame == 6) {
                (*m_opponent)->x = facing * 37 + x;
                (*m_opponent)->y = -87.0;
                (*m_opponent)->pattern = kThrownStandLow;
                (*m_opponent)->StartPattern();
            }
            if (frame == 7) {
                effect.type = 0x198;
                effect.x = (double)((int)x + facing * 37);
                effect.y = (double)((int)y - 87);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -6.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 30 + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(20, 10);
                DealDamage(4200, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                FillBackground(176, 0);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236Lv1Unused:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            FocusCameraY(50, 120);
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 19);
            effect.y = (double)((int)y - 34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame >= 1) {
            unkf2 = 10;
        }
        if (frame == 5 && timer == 0) {
            vx = 6.0;
        }
        if (frame > 8) {
            vx -= 0.2;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3) {
            ShakeScreen(10, 0);
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
    case k236236Lv2Unused:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            FocusCameraY(50, 120);
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 19);
            effect.y = (double)((int)y - 34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame >= 1) {
            unkf2 = 10;
        }
        if (frame == 5 && timer == 0) {
            vx = 6.0;
        }
        if (frame > 8) {
            vx -= 0.2;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3) {
            ShakeScreen(10, 0);
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
    case k236236Lv3Unused:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            FocusCameraY(50, 120);
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 19);
            effect.y = (double)((int)y - 34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame >= 4) {
            m_game->FlashNegative(15);
        }
        if (frame == 5 && timer == 0) {
            vx = 6.0;
        }
        if (frame > 8) {
            vx -= 0.2;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3) {
            ShakeScreen(10, 0);
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
    case kGrabFollowAB:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            m_patternVar1 = 0;
        }
        if (frame < 10 && m_patternVar1 == 0) {
            if ((*m_opponent)->m_pressA == 1) {
                m_patternVar1 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                m_patternVar1 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                m_patternVar1 = 3;
            }
        }
        if ((*m_opponent)->pattern == kLyingDown && frame < 9) {
            (*m_opponent)->timer = 0;
        }
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 56);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && timer == 0) {
            DealDamage(1800, 1000.0);
            ShakeScreen(10, 10);
            (*m_opponent)->m_hitstop = 180;
            m_playSound = 22;
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y + 8);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 8 && (m_command == kCmd236236A || m_command == kCmd214214A) && m_gauge >= 1000) {
            if (m_patternVar1 == 3) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 26;
                (*m_opponent)->pattern = kAirRecoveryBack;
                (*m_opponent)->m_hitstop = 0;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = kGrabFollowABA;
            break;
        }
        if (frame == 8 && (m_command == kCmd236236B || m_command == kCmd214214B) && m_gauge >= 1000) {
            if (m_patternVar1 == 2) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 26;
                (*m_opponent)->pattern = kAirRecoveryBack;
                (*m_opponent)->m_hitstop = 0;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = kGrabFollowABB;
            FaceOpponent();
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
            }
        }
        break;
    case kGrabFollowAAB:
        if ((*m_opponent)->pattern == kLyingDown && frame < 9) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 4 && vy > 0.0) {
            timer = 0;
            frame = 4;
        }
        if (y < 0.0 && m_freezeTime == 0) {
            vy = vy + ay;
        }
        if (frame == 4 && m_freezeTime == 0 && m_patternVar1 == 1) {
            vy = 10.0;
            m_patternVar1++;
        }
        if (frame == 4 && vy > 0.0 && y > -90.0 && m_patternVar1 == 0) {
            m_patternVar1++;
            vy = 0.0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 1800);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 25);
            effect.y = (double)((int)y - 60);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && y + vy > 0.0) {
            StopMoving();
            timer = 0;
            frame = 5;
            y = 0.0;
            DealDamage(4500, 1000.0);
            ShakeScreen(10, 10);
            (*m_opponent)->m_hitstop = 300;
            m_playSound = 22;
            effect.type = 0x19b;
            effect.x = (double)((int)x + facing * 17);
            effect.y = (double)((int)y + 11);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        FocusCameraY(-50, 3);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -10.0;
                ay = 0.045;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FillBackground(176, 0);
            }
        }
        break;
    case k236236Lv1:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
            m_dashMomentum = 0;
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 85);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 10) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 10 && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 10;
            break;
        }
        if (m_attackResult == 3 && frame == 12) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 1800;
            StopMoving();
            FocusCameraY(50, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 24 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = k236236Lv1Hit;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 69);
            effect.y = (double)((int)y - 35);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 1.3;
            }
            if (frame == 10 && m_patternVar1 < 2) {
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
    case k236236Lv1Hit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 28 + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 4) {
                effect.type = 0x190;
                effect.x = (double)((int)x + facing * 12);
                effect.y = (double)((int)y - 87);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -4.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 30 + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(10, 5);
                DealDamage(2300, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                (*m_opponent)->m_hitstop = 0;
                FillBackground(176, 0);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236Lv2:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
            m_dashMomentum = 0;
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 85);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 10) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 10 && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 10;
            break;
        }
        if (m_attackResult == 3 && frame == 12) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 1800;
            StopMoving();
            FocusCameraY(50, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 24 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = k236236Lv2Hit;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 69);
            effect.y = (double)((int)y - 35);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 1.7;
            }
            if (frame == 10 && m_patternVar1 < 4) {
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
    case k236236Lv2Hit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 28 + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 4) {
                effect.type = 0x198;
                effect.x = (double)((int)x + facing * 12);
                effect.y = (double)((int)y - 87);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -4.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 30 + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(15, 10);
                DealDamage(3300, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                (*m_opponent)->m_hitstop = 0;
                FillBackground(176, 0);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236Lv3:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
            m_dashMomentum = 0;
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 85);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 10) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 10 && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 10;
            break;
        }
        if (m_attackResult == 3 && frame == 12) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 1800;
            StopMoving();
            FocusCameraY(50, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 24 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = k236236Lv3Hit;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 69);
            effect.y = (double)((int)y - 35);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        m_game->FlashNegative(15);
        timer++;
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 2.1;
            }
            if (frame == 10 && m_patternVar1 < 6) {
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
    case k236236Lv3Hit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 4) {
            FillBackground(176, 3);
        }
        if (frame == 3 && timer == 180) {
            effect.type = 0x19a;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 87);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = 1;
            SpawnObject(&effect);
            m_playVoice = 4;
        }
        if (frame == 3 && (timer == 270 || timer == 315 || timer == 360 || timer == 390 || timer == 420 || timer == 450 || timer == 465 || timer == 480)) {
            effect.type = 0x199;
            effect.x = (double)((int)x + ((WORD)Random(0, 80) + 7) * facing);
            effect.y = (double)((int)y - 57 - (WORD)Random(0, 80));
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = 1;
            SpawnObject(&effect);
            m_playVoice = 3;
        }
        FocusCameraY(50, 3);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 28 + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 40 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 4) {
                effect.type = 0x198;
                effect.x = (double)((int)x + facing * 12);
                effect.y = (double)((int)y - 87);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -4.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 30 + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(20, 10);
                DealDamage(4900, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                (*m_opponent)->m_hitstop = 0;
                FillBackground(176, 0);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214Lv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 6);
            effect.y = (double)((int)y - 45);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && timer == 0) {
            ShakeScreen(5, 0);
            m_playSound = 22;
            effect.type = 0x19c;
            effect.x = (double)((int)x + facing * 60);
            if (facing * 60 + x > 620.0) {
                effect.x = 620.0;
            }
            if (facing * 60 + x < 20.0) {
                effect.x = 20.0;
            }
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x19f;
            effect.keep = 1;
            effect.layer = 0;
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
            }
        }
        break;
    case k214214Lv2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 6);
            effect.y = (double)((int)y - 45);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && (timer == 0 || timer == 60)) {
            ShakeScreen(5, 0);
            m_playSound = 22;
            effect.type = 0x19d;
            effect.x = (double)((int)x + (timer + 60) * facing);
            if ((timer + 60) * facing + x > 620.0) {
                effect.x = 620.0;
            }
            if ((timer + 60) * facing + x < 20.0) {
                effect.x = 20.0;
            }
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x19f;
            effect.keep = 1;
            effect.layer = 0;
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
            }
        }
        break;
    case k214214Lv3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 6);
            effect.y = (double)((int)y - 45);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 0) {
            m_game->FlashNegative(15);
        }
        if (frame == 5 && (timer == 0 || timer == 60 || timer == 120)) {
            ShakeScreen(5, 0);
            m_playSound = 22;
            effect.type = 0x19e;
            effect.x = (double)((int)x + (timer + 60) * facing);
            if ((timer + 60) * facing + x > 620.0) {
                effect.x = 620.0;
            }
            if ((timer + 60) * facing + x < 20.0) {
                effect.x = 20.0;
            }
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x19f;
            effect.keep = 1;
            effect.layer = 0;
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
            }
        }
        break;
    case kGrabFollowABA:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        if (frame == 3 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 23);
            effect.y = (double)((int)y - 57);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2) {
            m_game->FlashNegative(15);
        }
        if (frame > 4 && frame < 11) {
            (*m_opponent)->pattern = kLyingDown;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 40 + x;
            if (x > 610.0 || x < 30.0) {
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -6.0;
                (*m_opponent)->m_hitVy = -3.5;
                (*m_opponent)->y = -5.0;
                ShakeScreen(20, 10);
                DealDamage(3000, 1000.0);
                m_playVoice = 2;
                frame = 11;
                timer = 0;
                vx = -6.0;
                vy = -3.5;
                effect.type = 0x198;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)((int)y - 11);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
        }
        if ((frame == 6 || frame == 8 || frame == 10) && timer == 0) {
            effect.type = 0;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 2;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(80, 1000.0);
        }
        if (y < 0.0) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = kKnockdown;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 3.5;
                effect.type = 0x1a0;
                effect.x = (double)((int)x + facing * 80);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 11) {
                frame = frame - 6;
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kGrabFollowABB:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        FocusCameraY(50, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 6);
            effect.y = (double)((int)y - 45);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 0) {
            m_game->FlashNegative(15);
        }
        if (frame == 5 && (timer == 0 || timer == 60 || timer == 120)) {
            ShakeScreen(5, 0);
            m_playSound = 22;
            effect.type = 0x1a2;
            effect.x = (double)((int)x + (timer + 60) * facing);
            if ((timer + 60) * facing + x > 620.0) {
                effect.x = 620.0;
            }
            if ((timer + 60) * facing + x < 20.0) {
                effect.x = 20.0;
            }
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x19f;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 5 && timer == 15) {
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->y = -2.0;
            (*m_opponent)->m_hitVy = -1.0;
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
    case kAwaken:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame < 4) {
            m_patternVar1--;
        }
        if (frame == 0 && timer == 0) {
            m_awakened = 1;
            m_patternVar1 = 66;
            FocusCameraY(50, 120);
            m_freezeTime = 180;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 7);
            effect.y = (double)((int)y - 53);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
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
    }
}
