// CEXNanase::UpdatePattern (0x6be9c0-0x6cfbaf), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CEXNanase's
// .rdata, which starts with its constructor's folder name (exnanase.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CEXNanase::UpdatePattern()
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
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case kWalkForward:
        m_dashMomentum = 0;
        vx = (m_awakened == 1) * 0.15 + 0.9;
        vy = 0.0;
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case kWalkBack:
        m_dashMomentum = 0;
        vx = -0.9 - (m_awakened == 1) * 0.15;
        vy = 0.0;
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        m_dashMomentum = 0;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
            m_dashMomentum = 0;
            break;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x78) {
            pattern = kDashStop;
            StartPattern();
        }
        if (m_inputX != facing && m_patternVar1 >= 0x3c) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0) {
            m_playSound = 0x15;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x64) {
            pattern = kFall;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 0x30) {
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
            m_playSound = 0x15;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
            vx = 0.0;
            vy = 0.0;
            m_dashMomentum = 0;
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
        if (frame == 0 && timer == 0) {
            m_playSound = 0x12;
            l50.type = 1;
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
        if (timer >= l4) {
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
            if (frame >= x8) {
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
            m_playSound = 0x15;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                x = facing * 0xa + x;
            }
            if (frame >= x8) {
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
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 2;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
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
            m_gauge = m_gauge + 0xd;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_gauge = m_gauge + 0x1e;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_gauge = m_gauge + 0x14;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
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
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
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
    case kAirDiveUnused:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
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
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.sound = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
            pattern = kAirDiveLanding;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.sound = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
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
            (*m_opponent)->x = facing * 0x28 + x;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kThrowHit:
        FocusCameraY(0x32, 3);
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
            (*m_opponent)->x = facing * 0x23 + x;
        }
        if (frame == 2) {
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = y - 68.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
        }
        if (frame == 3) {
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
        }
        if (frame == 4) {
            (*m_opponent)->x = facing * 0xa + x;
            (*m_opponent)->y = y - 90.0;
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->StartPattern();
        }
        if (frame == 5) {
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->pattern = kThrownUpsideDown;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kKnockdown;
                (*m_opponent)->StartPattern();
                DealDamage(0x4b0, 750.0);
            }
            if (frame >= x8) {
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
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = kAirThrowHit;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kJumpC;
                frame = 2;
            }
        }
        break;
    case kAirThrowHit:
        m_hideOffscreenMarker = 0x1e;
        (*m_opponent)->m_hideOffscreenMarker = 0x1e;
        FocusCameraY(0x32, 3);
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
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->StartPattern();
        }
        if (frame == 1) {
            (*m_opponent)->x = facing * 0xa + x;
            (*m_opponent)->y = y - 90.0;
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->StartPattern();
        }
        if (frame == 2) {
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->pattern = kThrownUpsideDown;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kKnockdown;
                (*m_opponent)->StartPattern();
                DealDamage(0x578, 500.0);
            }
            if (frame >= x8) {
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
            (*m_opponent)->m_hitstop = 0x5a;
            (*m_opponent)->x = facing * 0x28 + x;
            (*m_opponent)->m_noAirRecovery = 1;
            (*m_opponent)->StopMoving();
            timer = 0;
            frame = 3;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)((int)y - 0x29);
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
            if (frame == 2 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kFirstGuard)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame == 4) {
                frame = 0;
                pattern = kGrabHold;
                frame = 1;
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -81.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                break;
            }
            if (frame == 3) {
                frame = 4;
            }
            if (frame >= x8) {
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = -62.0;
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = x - facing * 0xb;
                (*m_opponent)->y = -57.0;
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                (*m_opponent)->x = x - facing * 0xb;
                (*m_opponent)->y = -52.0;
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = x - facing * 0x19;
                (*m_opponent)->y = -55.0;
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->StartPattern();
            }
            if (frame == 5) {
                (*m_opponent)->x = x - facing * 0x25;
                (*m_opponent)->y = -54.0;
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->m_hitVx = 0.5;
                (*m_opponent)->m_hitVy = -2.6;
            }
            if (frame >= x8) {
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
            FocusCameraY(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 0x32 + x;
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
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 5 && timer == 0) {
                x = facing * 0xf + x;
            }
            if (frame == 6 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
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
            FocusCameraY(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 0x28 + x;
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
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6 && (*m_opponent)->y < 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kGrabHold:
        FocusCameraY(0x32, 3);
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -81.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_noAirRecovery = 1;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -80.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_noAirRecovery = 1;
            }
            if (frame >= x8) {
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
                        m_playSound = 0x1a;
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
                        m_playSound = 0x1a;
                        (*m_opponent)->pattern = kAirRecoveryBack;
                        (*m_opponent)->StartPattern();
                        (*m_opponent)->StopMoving();
                        break;
                    }
                    pattern = kGrabFollowB;
                    (*m_opponent)->pattern = kThrownDoubledOver;
                    frame = 1;
                    timer = 0;
                    (*m_opponent)->x = facing * 0xb + x;
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_patternVar1 = 0;
        }
        StopMoving();
        if (frame == 6 && timer == 0) {
            DealDamage(0x5dc, 1000.0);
            m_playSound = 2;
            l50.type = 0;
            l50.x = (double)((int)x - facing * 7);
            l50.y = (double)((int)y + 7);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame < 0xa && m_patternVar1 == 0) {
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
        if (frame == 0xa && timer == 0) {
            if ((m_command == kCmd236A || m_command == kCmd214A) && m_gauge >= 0x3e8) {
                if (m_patternVar1 == 3) {
                    StartPattern();
                    pattern = kGrabEscaped;
                    m_playSound = 0x1a;
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
            if ((m_command == kCmd236B || m_command == kCmd214B) && m_gauge >= 0x3e8) {
                if (m_patternVar1 == 2) {
                    StartPattern();
                    pattern = kGrabEscaped;
                    m_playSound = 0x1a;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x24 + x;
                (*m_opponent)->y = -78.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x2b + x;
                (*m_opponent)->y = -75.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                (*m_opponent)->x = facing * 0x2d + x;
                (*m_opponent)->y = -69.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = facing * 0x17 + x;
                (*m_opponent)->y = -66.0;
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->StartPattern();
                (*m_opponent)->facing = facing;
            }
            if (frame == 5) {
                (*m_opponent)->x = x - facing * 0xa;
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
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kGrabFollowUnused:
        if (frame == 0 && timer == 0 && m_patternVar1 == 1) {
            StartPattern();
            pattern = kGrabEscaped;
            m_playSound = 0x1a;
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
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = -40.0;
            ShakeScreen(0xa, 0xa);
            DealDamage(0x708, 700.0);
            m_attackResult = 3;
            m_playVoice = 2;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x50);
            l50.scale = 2;
            l50.facing = facing;
            l50.keep = 1;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kGrabRelease:
        FocusCameraY(0x32, 3);
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
    case kGrabExUnused:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
            FocusCameraY(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 0x32 + x;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = kGrabHold;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 3) {
                vx = 1.3;
            }
            if (frame >= x8) {
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 8) {
                m_playVoice = 1;
                l50.type = 0x191;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x3a);
                l50.facing = facing;
                l50.scale = 2;
                l50.layer = 1;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xa && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 2;
                if (m_patternVar1 == 2) {
                    m_attackResult = 3;
                }
            }
            if (frame >= x8) {
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
            l50.type = 0x192;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3a);
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xa && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= x8) {
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
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
            l50.type = 0x193;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3a);
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xa && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= x8) {
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
                m_patternVar3 = 0x2d;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 4) {
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.facing = facing;
                l50.scale = 2;
                l50.layer = 0;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
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
            if (frame >= x8) {
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
                m_patternVar3 = 0x2d;
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 4) {
                l50.type = 0x195;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.facing = facing;
                l50.scale = 2;
                l50.layer = 0;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
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
            if (frame >= x8) {
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
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
        if (timer >= l4 - ((m_awakened == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                m_invulTime = 0x3c;
                l50.type = 0x196;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.facing = facing;
                l50.scale = 2;
                l50.layer = 0;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 4) {
                m_hitsLeft = 0xf;
            }
            if (frame == 8 && m_patternVar1 < 5) {
                m_patternVar1++;
                frame = frame - 4;
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
        if (frame < 0xa && m_patternVar1 == 0) {
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame < 0xe) {
            m_koDelay = 3;
        }
        if ((frame == 2 || frame == 5 || frame == 8 || frame == 0xb || frame == 0xe) && timer == 0) {
            m_playSound = 2;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 7);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (frame == 2 || frame == 5 || frame == 8 || frame == 0xb) {
                DealDamage(0x32, 1000.0);
                ShakeScreen(2, 2);
            }
            if (frame == 0xe) {
                DealDamage(0x1f4, 1000.0);
                ShakeScreen(0xa, 0xa);
                m_koDelay = 0;
            }
        }
        if (frame > 1 && frame < 8 && (m_command == kCmd236236A || m_command == kCmd214214A) && m_gauge >= 0x3e8) {
            if (m_patternVar1 == 3) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 0x1a;
                (*m_opponent)->pattern = kAirRecoveryBack;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = kGrabFollowAAA;
            break;
        }
        if (frame > 1 && frame < 8 && (m_command == kCmd236236B || m_command == kCmd214214B) && m_gauge >= 0x3e8) {
            if (m_patternVar1 == 2) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 0x1a;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && m_patternVar2 < 0xa) {
                m_patternVar2++;
                frame = 2;
            }
            if (frame >= x8) {
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
                m_playSound = 0x1a;
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
        FocusCameraY(0x32, 3);
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x24);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            DealDamage(0x960, 600.0);
            ShakeScreen(5, 5);
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = -3.0;
            (*m_opponent)->m_hitVy = -8.0;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        if (frame == 6 && timer == 0x3c) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 0x708);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x57);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0xb4) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x57);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = 1;
            SpawnObject(&l50);
            m_playVoice = 4;
        }
        if (frame == 6 && (timer == 0x10e || timer == 0x13b || timer == 0x168 || timer == 0x186 || timer == 0x1a4 || timer == 0x1c2 || timer == 0x1d1 || timer == 0x1e0)) {
            l50.type = 0x199;
            l50.x = (double)((int)x + ((WORD)Random(0, 0x50) + 7) * facing);
            l50.y = (double)((int)y - 0x39 - (WORD)Random(0, 0x50));
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = 1;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->facing = -facing;
                (*m_opponent)->x = facing * 0x2e + x;
                (*m_opponent)->y = -38.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = facing * 0x31 + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
            }
            if (frame == 5) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
                (*m_opponent)->StartPattern();
            }
            if (frame == 6) {
                (*m_opponent)->x = facing * 0x25 + x;
                (*m_opponent)->y = -87.0;
                (*m_opponent)->pattern = kThrownStandLow;
                (*m_opponent)->StartPattern();
            }
            if (frame == 7) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x25);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -6.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(0x14, 0xa);
                DealDamage(0x1068, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
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
            FocusCameraY(0x32, 0x78);
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x13);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
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
            ShakeScreen(0xa, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
            FocusCameraY(0x32, 0x78);
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x13);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
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
            ShakeScreen(0xa, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
            FocusCameraY(0x32, 0x78);
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x13);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame >= 4) {
            m_game->FlashNegative(0xf);
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
            ShakeScreen(0xa, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
        if (frame < 0xa && m_patternVar1 == 0) {
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 4 && timer == 0) {
            DealDamage(0x708, 1000.0);
            ShakeScreen(0xa, 0xa);
            (*m_opponent)->m_hitstop = 0xb4;
            m_playSound = 0x16;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y + 8);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 8 && (m_command == kCmd236236A || m_command == kCmd214214A) && m_gauge >= 0x3e8) {
            if (m_patternVar1 == 3) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 0x1a;
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
        if (frame == 8 && (m_command == kCmd236236B || m_command == kCmd214214B) && m_gauge >= 0x3e8) {
            if (m_patternVar1 == 2) {
                StartPattern();
                pattern = kGrabEscaped;
                m_playSound = 0x1a;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 0x708);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 4 && y + vy > 0.0) {
            StopMoving();
            timer = 0;
            frame = 5;
            y = 0.0;
            DealDamage(0x1194, 1000.0);
            ShakeScreen(0xa, 0xa);
            (*m_opponent)->m_hitstop = 0x12c;
            m_playSound = 0x16;
            l50.type = 0x19b;
            l50.x = (double)((int)x + facing * 0x11);
            l50.y = (double)((int)y + 0xb);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        FocusCameraY(-0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -10.0;
                ay = 0.045;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FillBackground(0xb0, 0);
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
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x55);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0xa) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 0xa && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 0xa;
            break;
        }
        if (m_attackResult == 3 && frame == 0xc) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 0x708;
            StopMoving();
            FocusCameraY(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 0x18 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = k236236Lv1Hit;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 1.3;
            }
            if (frame == 0xa && m_patternVar1 < 2) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1c + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 4) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0xc);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -4.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(0xa, 5);
                DealDamage(0x8fc, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                (*m_opponent)->m_hitstop = 0;
                FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
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
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x55);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0xa) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 0xa && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 0xa;
            break;
        }
        if (m_attackResult == 3 && frame == 0xc) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 0x708;
            StopMoving();
            FocusCameraY(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 0x18 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = k236236Lv2Hit;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 1.7;
            }
            if (frame == 0xa && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1c + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0xc);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -4.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(0xf, 0xa);
                DealDamage(0xce4, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                (*m_opponent)->m_hitstop = 0;
                FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
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
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x55);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 0xa) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 0xa && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 0xa;
            break;
        }
        if (m_attackResult == 3 && frame == 0xc) {
            (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 0x708;
            StopMoving();
            FocusCameraY(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 0x18 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_noAirRecovery = 1;
            StartPattern();
            pattern = k236236Lv3Hit;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        m_game->FlashNegative(0xf);
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 2.1;
            }
            if (frame == 0xa && m_patternVar1 < 6) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
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
            FillBackground(0xb0, 3);
        }
        if (frame == 3 && timer == 0xb4) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x57);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = 1;
            SpawnObject(&l50);
            m_playVoice = 4;
        }
        if (frame == 3 && (timer == 0x10e || timer == 0x13b || timer == 0x168 || timer == 0x186 || timer == 0x1a4 || timer == 0x1c2 || timer == 0x1d1 || timer == 0x1e0)) {
            l50.type = 0x199;
            l50.x = (double)((int)x + ((WORD)Random(0, 0x50) + 7) * facing);
            l50.y = (double)((int)y - 0x39 - (WORD)Random(0, 0x50));
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = 1;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        FocusCameraY(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1c + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = kThrownDoubledOver;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = kThrownStandLow;
            }
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0xc);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -4.0;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                ShakeScreen(0x14, 0xa);
                DealDamage(0x1324, 850.0);
                m_playVoice = 2;
                m_koDelay = 0;
                (*m_opponent)->m_hitstop = 0;
                FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x19c;
            l50.x = (double)((int)x + facing * 0x3c);
            if (facing * 0x3c + x > 620.0) {
                l50.x = 620.0;
            }
            if (facing * 0x3c + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.keep = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && (timer == 0 || timer == 0x3c)) {
            ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x19d;
            l50.x = (double)((int)x + (timer + 0x3c) * facing);
            if ((timer + 0x3c) * facing + x > 620.0) {
                l50.x = 620.0;
            }
            if ((timer + 0x3c) * facing + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.keep = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 5 && (timer == 0 || timer == 0x3c || timer == 0x78)) {
            ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x19e;
            l50.x = (double)((int)x + (timer + 0x3c) * facing);
            if ((timer + 0x3c) * facing + x > 620.0) {
                l50.x = 620.0;
            }
            if ((timer + 0x3c) * facing + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.keep = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        if (frame == 3 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - facing * 0x17);
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame > 4 && frame < 0xb) {
            (*m_opponent)->pattern = kLyingDown;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x28 + x;
            if (x > 610.0 || x < 30.0) {
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -6.0;
                (*m_opponent)->m_hitVy = -3.5;
                (*m_opponent)->y = -5.0;
                ShakeScreen(0x14, 0xa);
                DealDamage(0xbb8, 1000.0);
                m_playVoice = 2;
                frame = 0xb;
                timer = 0;
                vx = -6.0;
                vy = -3.5;
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y - 0xb);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
        }
        if ((frame == 6 || frame == 8 || frame == 0xa) && timer == 0) {
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.sound = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            DealDamage(0x50, 1000.0);
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 3.5;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x50);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xb) {
                frame = frame - 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
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
        FocusCameraY(0x32, 3);
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 5 && (timer == 0 || timer == 0x3c || timer == 0x78)) {
            ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + (timer + 0x3c) * facing);
            if ((timer + 0x3c) * facing + x > 620.0) {
                l50.x = 620.0;
            }
            if ((timer + 0x3c) * facing + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.keep = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 5 && timer == 0xf) {
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->y = -2.0;
            (*m_opponent)->m_hitVy = -1.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
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
            m_patternVar1 = 0x42;
            FocusCameraY(0x32, 0x78);
            m_freezeTime = 0xb4;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x35);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
    }
}
