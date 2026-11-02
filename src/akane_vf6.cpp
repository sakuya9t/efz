// CAkane::UpdatePattern (0x6f2f20-0x7039cf), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CAkane's
// .rdata, which starts with its constructor's folder name (akane.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CAkane::UpdatePattern()
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
        vx = 0.7;
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
        vx = -0.7;
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
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.054;
            vy = -3.3;
            if (m_dashMomentum == 1) {
                vx = 0.4;
                m_dashMomentum = 0;
            }
        }
        if (frame > 3) {
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
            ay = 0.054;
            vy = -3.3;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
            }
        }
        if (frame > 3) {
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
            ay = 0.054;
            vy = -3.3;
            vx = -0.7;
        }
        if (frame > 3) {
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
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kAirJump:
        ay = 0.054;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 0.0;
            m_dashMomentum = 0;
        }
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
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpForward:
        ay = 0.054;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 0.7;
            m_dashMomentum = 0;
        }
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
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpBack:
        ay = 0.054;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = -0.9;
            m_dashMomentum = 0;
        }
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
        m_dashMomentum = 0;
        if (m_hp > 0 && timer > 0x63) {
            pattern = kWakeUp;
            StartPattern();
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
    case 0xa1:
        if (frame == 0 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_playSound = 0x3e;
            m_patternVar1++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (frame == 5 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_playSound = 0x3e;
            m_gauge = m_gauge - 0x3e8;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kDashForward:
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
            StopMoving();
        }
        vx = 1.65;
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar1 >= 0x78) {
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
        if (frame == 3 && timer == 0) {
            vx = -2.0;
            vy = -1.5;
            ay = 0.04;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 3 && vy + y >= 0.0 && m_patternVar1 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            m_patternVar1++;
            m_playSound = 9;
            frame = 0xd;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                FaceOpponent();
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = 2.0;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            m_playSound = 0x11;
        }
        timer++;
        m_patternVar1++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar1 >= 0x78) {
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
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = -2.0;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 0x11;
        }
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= l4) {
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
        if (m_inputX != -facing && m_patternVar1 >= 0x30) {
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
            m_dashMomentum = 0;
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
            m_recoilGuardWindow = 0;
            m_cornerPushback = 0.0;
            if (ay == 0.0) {
                ay = 0.035;
            }
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
        if (y + vy > 0.0 && frame < 0xd) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xd;
            m_playSound = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 0xd) {
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
            m_gauge = m_gauge + 0xf;
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
    case k5BFar:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
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
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 9;
            m_patternVar1 = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa && m_patternVar1 > 0) {
                m_patternVar1--;
                frame = 7;
            }
            if (frame < 0xa) {
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
        if (vx > 0.0 && m_dashMomentum == 1 && frame < 3) {
            vx -= 0.06;
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
        if (m_inputY == -1 && frame > 0 && m_attackResult == 3) {
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
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx += 1.5;
        }
        if (frame > 2) {
            vx -= 0.02;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
    case k2C:
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
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
        if (frame == 1 && timer == 0) {
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
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kUnusedAirDive:
        if (frame > 6) {
            vy = vy + ay;
        }
        if (frame == 2 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 3;
            vx = 1.0;
            vy = 1.0;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            StopMoving();
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xa) {
                frame = 7;
            }
        }
        break;
    case kJump6C:
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
        if (frame == 3 && timer == 0) {
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
    case kUnusedRebound:
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
    case kUnusedDiveLanding:
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
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = kThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x11);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 5 + x;
            (*m_opponent)->y = 0.0;
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
    case kThrowHit:
        if (frame == 0 && timer == 1) {
            m_hitsLeft = 1;
            m_attackResult = 0;
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->pattern = kHitStandHighLight;
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
    case kDashA:
        StartAfterimages(3);
        vx -= 0.06;
        m_dashMomentum = 0;
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
    case kDashB:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 3;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
    case kDashC:
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
    case kDash2A:
        StartAfterimages(3);
        vx -= 0.06;
        if (vx < 0.0) {
            vx = 0.0;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
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
            if (frame < 3) {
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
        if (frame == 2 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
            vx += 1.2;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
                StartPattern();
            }
        }
        break;
    case kDash2C:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (vx > 0.0 && frame < 3) {
            vx -= 0.03;
        } else {
            m_dashMomentum = 0;
        }
        if (frame == 0xd && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (frame > 2 && frame < 0x11) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                timer = 0;
                frame = 0x12;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 1.2;
                vy = -1.5;
                ay = 0.035;
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
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            StartPattern();
            vx = 1.0;
            vy = -2.5;
            ay = 0.035;
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x27);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
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
                pattern = kJump6C;
                frame = 1;
            }
        }
        break;
    case kAirThrowHit:
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (facing == 1 && x > 630.0) {
            x = 630.0;
            vx = 0.0;
        }
        if (facing == -1 && x < 30.0) {
            x = 30.0;
            vx = 0.0;
        }
        if (vy + y > 0.0 && frame == 4) {
            StopMoving();
            y = 0.0;
            frame = 5;
            timer = 0;
        }
        if (frame == 0) {
            (*m_opponent)->y = y - 35.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = kThrownStandHigh;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x15;
            (*m_opponent)->pattern = kThrownStandLowInverted;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = x - facing * 0x14;
            (*m_opponent)->pattern = kThrownAirborne;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 76.0;
            (*m_opponent)->x = x - facing * 0xf;
            (*m_opponent)->pattern = kThrownAirborne;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 77.0;
            (*m_opponent)->x = x - facing * 0xc;
            (*m_opponent)->pattern = kThrownAirborne;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x13;
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(4, 0);
            l50.type = 3;
            l50.sound = 7;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0xf + x;
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -2.0;
            (*m_opponent)->m_hitVy = -0.5;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->x = facing * 0xf + x;
            DealDamage(0x4b0, 500.0);
            (*m_opponent)->m_untechTime = (int)(200.0 * m_proration * 0.0001);
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
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
    case k236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_patternVar2 = 0;
            StopMoving();
        }
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            m_helperState = 1;
            if ((int)(x + (*m_opponent)->x) / 2 > 0x1e0) {
                m_patternVar3++;
                l50.shadow = 1;
                l50.type = 0x19e;
                l50.x = (double)((facing == 1) * 0x118 + (facing == -1) * 0x2a8);
                l50.y = -80.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if ((int)(x + (*m_opponent)->x) / 2 < 0xa0) {
                m_patternVar3++;
                l50.shadow = 1;
                l50.type = 0x19e;
                l50.x = (double)((facing == 1) * -0x28 + (facing == -1) * 0x168);
                l50.y = -80.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (m_patternVar3 == 0) {
                l50.type = 0x19e;
                l50.shadow = 1;
                l50.x = (x + (*m_opponent)->x) / 2.0 - facing * 0xa0;
                l50.y = -80.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            m_patternVar1++;
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
    case k236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_patternVar2 = 0;
            StopMoving();
        }
        if (frame == 1 && timer == 0 && m_patternVar1 == 0) {
            m_helperState = 1;
            if ((int)(x + (*m_opponent)->x) / 2 > 0x1e0) {
                m_patternVar3++;
                l50.shadow = 1;
                l50.type = 0x19f;
                l50.x = (double)((facing == 1) * 0x118 + (facing == -1) * 0x2a8);
                l50.y = 0.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if ((int)(x + (*m_opponent)->x) / 2 < 0xa0) {
                m_patternVar3++;
                l50.shadow = 1;
                l50.type = 0x19f;
                l50.x = (double)((facing == 1) * -0x28 + (facing == -1) * 0x168);
                l50.y = 0.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (m_patternVar3 == 0) {
                l50.shadow = 1;
                l50.type = 0x19f;
                l50.x = (x + (*m_opponent)->x) / 2.0 - facing * 0xa0;
                l50.y = 0.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            m_patternVar1++;
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
    case k236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
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
        }
        if (frame == 0 && timer == 0x1d && m_patternVar1 == 0) {
            m_helperState = 1;
            if ((int)(x + (*m_opponent)->x) / 2 > 0x1e0) {
                m_patternVar3++;
                l50.shadow = 1;
                l50.type = 0x199;
                l50.x = (double)((facing == -1) * 0x118 + (facing == 1) * 0x2a8);
                l50.y = 0.0;
                l50.facing = -facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if ((int)(x + (*m_opponent)->x) / 2 < 0xa0) {
                m_patternVar3++;
                l50.shadow = 1;
                l50.type = 0x199;
                l50.x = (double)((facing == -1) * -0x28 + (facing == 1) * 0x168);
                l50.y = 0.0;
                l50.facing = -facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (m_patternVar3 == 0) {
                l50.shadow = 1;
                l50.type = 0x199;
                l50.x = (x + (*m_opponent)->x) / 2.0 + facing * 0xa0;
                l50.y = 0.0;
                l50.facing = -facing;
                l50.scale = 0;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            m_patternVar1++;
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
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_gauge = m_gauge + 0x2d;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0 && m_patternVar1 == 0) {
            vx = 0.5;
            vy = -1.5;
            ay = 0.035;
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame > 6) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 7 && frame < 0xb) {
            y = 0.0;
            StopMoving();
            StartPattern();
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar1 < 2) {
                frame = 3;
                m_patternVar1++;
            }
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.8;
        }
        if (frame == 4 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 0.8;
            vy = -2.4;
            ay = 0.035;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 0xa && frame < 0xe) {
            y = 0.0;
            StartPattern();
            StopMoving();
            frame = 0xe;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_invulTime = 0xc;
            }
            if (frame == 1 || frame == 3 || frame == 4 || frame == 7 || frame == 9 || frame == 0xe) {
                m_attackResult = 0;
            }
            if (frame == 4 && m_patternVar2 < 1) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame == 0xa && m_patternVar3 < 1) {
                frame = frame - 4;
                m_patternVar3++;
            }
            if (frame == 0xe) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
            }
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
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.8;
        }
        if (frame == 4 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 0.8;
            vy = -2.4;
            ay = 0.035;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 0xa && frame < 0xe) {
            y = 0.0;
            StartPattern();
            StopMoving();
            frame = 0xe;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_invulTime = 0xc;
            }
            if (frame == 1 || frame == 3 || frame == 4 || frame == 7 || frame == 9 || frame == 0xe) {
                m_attackResult = 0;
            }
            if (frame == 4 && m_patternVar2 < 2) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame == 0xa && m_patternVar3 < 2) {
                frame = frame - 4;
                m_patternVar3++;
            }
            if (frame == 0xe) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = -3.5;
            ay = 0.055;
        }
        m_patternVar1++;
        if (m_patternVar1 > 0x34) {
            if (m_command == kCmd236A) {
                pattern = kLeap236A;
                StartPattern();
                break;
            }
            if (m_command == kCmd236B) {
                pattern = kLeap236B;
                StartPattern();
                break;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue == 1)) {
                pattern = kLeap236C;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = kLeapC;
                if (m_inputX != facing) {
                    FaceOpponent();
                }
                if (m_inputY == 0 && m_inputX == -facing) {
                    pattern = kLeap4C;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLandingAttack;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        if (frame == 3 && timer == 0) {
            vx = -0.5;
            vy = -2.8;
            ay = 0.037;
        }
        m_patternVar1++;
        if (m_patternVar1 > 0x34) {
            if (m_command == kCmd236A) {
                pattern = kLeap236A;
                StartPattern();
                break;
            }
            if (m_command == kCmd236B) {
                pattern = kLeap236B;
                StartPattern();
                break;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue == 1)) {
                pattern = kLeap236C;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = kLeapC;
                if (m_inputX != facing) {
                    FaceOpponent();
                }
                if (m_inputY == 0 && m_inputX == -facing) {
                    pattern = kLeap4C;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        if (frame == 3 && timer == 0) {
            vx = 1.5;
            vy = -2.8;
            ay = 0.037;
        }
        m_patternVar1++;
        if (m_patternVar1 > 0x34) {
            if (m_command == kCmd236A) {
                pattern = kLeap236A;
                StartPattern();
                break;
            }
            if (m_command == kCmd236B) {
                pattern = kLeap236B;
                StartPattern();
                break;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue == 1)) {
                pattern = kLeap236C;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = kLeapC;
                if (m_inputX != facing) {
                    FaceOpponent();
                }
                if (m_inputY == 0 && m_inputX == -facing) {
                    pattern = kLeap4C;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLandingAttack;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case k412A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        vx -= 0.2;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 4.5;
            vy = -3.0;
            ay = 0.035;
        }
        m_patternVar1++;
        if (m_patternVar1 > 0x34) {
            if (m_command == kCmd236A) {
                pattern = kLeap236A;
                StartPattern();
                break;
            }
            if (m_command == kCmd236B) {
                pattern = kLeap236B;
                StartPattern();
                break;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue == 1)) {
                pattern = kLeap236C;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = kLeapC;
                if (m_inputY == 1) {
                    pattern = kLeap2C;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case k412B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        vx -= 0.2;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 6.6;
            vy = -3.0;
            ay = 0.035;
        }
        m_patternVar1++;
        if (m_patternVar1 > 0x34) {
            if (m_command == kCmd236A) {
                pattern = kLeap236A;
                StartPattern();
                break;
            }
            if (m_command == kCmd236B) {
                pattern = kLeap236B;
                StartPattern();
                break;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue == 1)) {
                pattern = kLeap236C;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = kLeapC;
                if (m_inputY == 1) {
                    pattern = kLeap2C;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case k412C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        vx -= 0.2;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 7.9;
            vy = -3.0;
            ay = 0.035;
        }
        m_patternVar1++;
        if (m_patternVar1 > 0x34) {
            if (m_command == kCmd236A) {
                pattern = kLeap236A;
                StartPattern();
                break;
            }
            if (m_command == kCmd236B) {
                pattern = kLeap236B;
                StartPattern();
                break;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue == 1)) {
                pattern = kLeap236C;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = kLeapC;
                if (m_inputY == 1) {
                    pattern = kLeap2C;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case kLeap236A:
        if (frame == 3 && timer == 0) {
            FaceOpponent();
            m_gauge = m_gauge + 0x19;
            vx = -0.5;
            vy = -1.0;
            ay = 0.015;
            m_playVoice = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x36);
            l50.y = (double)((int)y - 0x18);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        if (y + vy >= 0.0) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        vy = vy + ay;
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
    case kLeap236B:
        if (frame == 3 && timer == 0) {
            FaceOpponent();
            m_gauge = m_gauge + 0x19;
            vx = -0.5;
            vy = -1.0;
            ay = 0.015;
            m_playVoice = 1;
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x36);
            l50.y = (double)((int)y - 0x18);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        if (y + vy >= 0.0) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        vy = vy + ay;
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
    case kLeap236C:
        if (frame == 0 && timer == 0) {
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
        if (frame == 3 && timer == 0) {
            FaceOpponent();
            m_gauge = m_gauge + 0x19;
            vx = -1.0;
            vy = -1.0;
            ay = 0.02;
            m_playVoice = 1;
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x36);
            l50.y = (double)((int)y - 0x18);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        if (y + vy >= 0.0) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = kLeapLanding;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        vy = vy + ay;
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
    case kLeapC:
        if (frame == 0 && timer == 0) {
            ay = 0.0;
            vy = 0.0;
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
            vx = 1.0;
            vy = 2.0;
        }
        if (y + vy >= 0.0 && frame < 2) {
            vx = 0.5;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            frame = 2;
            timer = 0;
            m_playSound = 9;
        }
        if (vx > 0.0 && y == 0.0) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                break;
            }
        }
        break;
    case kLeap2C:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 3;
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 2;
            vx = 0.0;
            vy = 2.1;
            ay = 0.0;
            m_playSound = 0x14;
            m_patternVar1 = 0x63;
        }
        if (y + vy >= 0.0 && frame < 6) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            frame = 6;
            timer = 0;
            m_playSound = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                break;
            }
        }
        break;
    case kLeap4C:
        vy = vy + ay;
        if (frame == 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            vx = 1.0;
            vy = -2.5;
            ay = 0.035;
            pattern = kLeap4CHit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x27);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
        }
        if (y + vy > 0.0 && frame < 4) {
            y = 0.0;
            vy = 0.0;
            vx = 0.0;
            frame = 4;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLeap4CHit:
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (facing == 1 && x > 630.0) {
            x = 630.0;
            vx = 0.0;
        }
        if (facing == -1 && x < 30.0) {
            x = 30.0;
            vx = 0.0;
        }
        if (vy + y > 0.0 && frame == 4) {
            StopMoving();
            y = 0.0;
            frame = 5;
            timer = 0;
        }
        if (frame == 0) {
            (*m_opponent)->y = y - 35.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = kThrownStandHigh;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x15;
            (*m_opponent)->pattern = kThrownStandLowInverted;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = x - facing * 0x14;
            (*m_opponent)->pattern = kThrownAirborne;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 76.0;
            (*m_opponent)->x = x - facing * 0xf;
            (*m_opponent)->pattern = kThrownAirborne;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 77.0;
            (*m_opponent)->x = x - facing * 0xc;
            (*m_opponent)->pattern = kThrownAirborne;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x13;
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(4, 0);
            l50.type = 3;
            l50.sound = 7;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0xf + x;
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -1.0;
            (*m_opponent)->m_hitVy = -3.0;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->x = facing * 0xf + x;
            DealDamage(0x3e8, 790.0);
            (*m_opponent)->m_untechTime = (int)(200.0 * m_proration * 0.0001);
            (*m_opponent)->StartPattern();
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
    case kLeapLanding:
        if (vx > 0.0) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        y = 0.0;
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
    case kLeapLandingAttack:
        if (frame == 0 && timer == 0) {
            vx = 1.0;
        }
        if (vx > 0.0) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        y = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kAir236A:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
            vx = -0.8;
            vy = -1.0;
            StopMoving();
            ay = 0.025;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if ((frame == 9 || frame == 0xd) && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame > 5 && frame < 0xe && y + vy > 0.0) {
            if (m_patternVar1 > 0) {
                y = 0.0;
                StopMoving();
                frame = 0xe;
                timer = 0;
                break;
            }
            if (m_patternVar1 == 0) {
                vx = -0.5;
                vy = -1.2;
                ay = 0.04;
                m_patternVar1++;
                y = 0.0;
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6 || frame == 7 || frame == 0xa) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                vx = 2.5;
                vy = 2.5;
            }
            if (frame == 0xe) {
                frame = frame - 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
                FaceOpponent();
            }
        }
        break;
    case kAir236B:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
            vx = -0.8;
            vy = -1.0;
            ay = 0.025;
        }
        vy = vy + ay;
        if ((frame == 9 || frame == 0xd) && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame > 5 && frame < 0xe && y + vy > 0.0) {
            if (m_patternVar1 > 0) {
                y = 0.0;
                StopMoving();
                frame = 0xe;
                timer = 0;
                break;
            }
            if (m_patternVar1 == 0) {
                vx = -0.5;
                vy = -1.5;
                ay = 0.04;
                m_patternVar1++;
                y = 0.0;
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6 || frame == 7 || frame == 0xa) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                vx = 3.2;
                vy = 2.2;
            }
            if (frame == 0xe) {
                frame = frame - 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
                FaceOpponent();
            }
        }
        break;
    case kAir236C:
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 0x63;
            vx = -0.8;
            vy = -1.0;
            ay = 0.025;
        }
        vy = vy + ay;
        if ((frame == 9 || frame == 0xd) && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame > 5 && frame < 0xe && y + vy > 0.0) {
            if (m_patternVar1 > 0) {
                y = 0.0;
                StopMoving();
                frame = 0xe;
                timer = 0;
                break;
            }
            if (m_patternVar1 == 0) {
                vx = -1.0;
                vy = -1.2;
                ay = 0.04;
                m_patternVar1++;
                y = 0.0;
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                vx = 2.5;
                vy = 2.5;
            }
            if (frame == 0xe) {
                frame = frame - 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
                FaceOpponent();
            }
        }
        break;
    case k236236A:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 4 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 0xa);
        }
        if (frame > 6 && frame < 0x10 && timer == 0 && m_patternVar1 < 2) {
            m_playVoice = 3;
            l50.type = 0x195;
            l50.x = (double)(int)((WORD)Random(0, 0x50) - 0x28 + x);
            l50.y = (double)((int)y - 0x8c);
            l50.scale = 2;
            l50.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                l50.layer = 0;
            }
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = 7;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236B:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 2 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 0xa);
        }
        if (frame > 6 && frame < 0x10 && timer == 0 && m_patternVar1 < 3) {
            m_playVoice = 3;
            l50.type = 0x195;
            l50.x = (double)(int)((WORD)Random(0, 0x50) - 0x28 + x);
            l50.y = (double)((int)y - 0x8c);
            l50.scale = 2;
            l50.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                l50.layer = 0;
            }
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = 7;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236C:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        m_game->FlashNegative(0xf);
        if (frame > 3) {
            FocusCameraY(0x32, 0xa);
        }
        if (frame > 6 && frame < 0x10 && timer == 0 && m_patternVar1 < 4) {
            m_playVoice = 3;
            l50.type = 0x195;
            l50.x = (double)(int)((WORD)Random(0, 0x50) - 0x28 + x);
            l50.y = (double)((int)y - 0x8c);
            l50.scale = 2;
            l50.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                l50.layer = 0;
            }
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = 7;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && m_patternVar1 == 0) {
                m_playVoice = 2;
                l50.type = 0x19c;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x32);
                l50.scale = 2;
                l50.facing = facing;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_attackResult = 0;
            if (frame == 8 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214B:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && m_patternVar1 == 0) {
                m_playVoice = 2;
                l50.type = 0x19c;
                l50.x = (double)((int)x + facing * 0x64);
                l50.y = (double)((int)y - 0x32);
                l50.scale = 2;
                l50.facing = facing;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_attackResult = 0;
            if (frame == 8 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && m_patternVar1 == 0) {
                m_playVoice = 2;
                l50.type = 0x19c;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x96);
                l50.scale = 2;
                l50.facing = facing;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_attackResult = 0;
            if (frame == 8 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236A:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a1;
            l50.x = (double)(int)(x - facing * 0x140);
            l50.y = (double)((int)y - 0x140);
            l50.scale = 0;
            l50.layer = 1;
            l50.keep = 1;
            l50.shadow = 1;
            l50.facing = facing;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            m_helperState = 2;
        }
        if (frame < 4) {
            FocusCameraY(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0xa && m_helperState > 1) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236B:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a2;
            l50.x = (double)(int)(x - facing * 0x140);
            l50.y = (double)((int)y - 0x140);
            l50.scale = 0;
            l50.layer = 1;
            l50.keep = 1;
            l50.shadow = 1;
            l50.facing = facing;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            m_helperState = 2;
        }
        if (frame < 4) {
            FocusCameraY(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0xa && m_helperState > 1) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236C:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a3;
            l50.x = (double)(int)(x - facing * 0x140);
            l50.y = (double)((int)y - 0x140);
            l50.scale = 0;
            l50.layer = 1;
            l50.keep = 1;
            l50.shadow = 1;
            l50.facing = facing;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
            m_helperState = 2;
            m_playSound = 0x25;
        }
        if (frame < 4) {
            FocusCameraY(0x32, 0xa);
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
    case kLv4:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_hitsLeft = 1;
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame < 4) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 1) {
            vx = 0.8;
            StartAfterimages(6);
        }
        if (frame >= 0) {
            FocusCameraY(0x32, 0xa);
        }
        if (frame > 0 && frame < 3 && m_attackResult == 3) {
            StartAfterimages(0);
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            frame = 3;
            (*m_opponent)->pattern = kThrownStandHigh2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x11);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
        }
        if (frame == 4) {
            (*m_opponent)->pattern = kThrownHidden;
            FillBackground(0xb0, 3);
            if (m_patternVar1 == 0) {
                m_comboHits++;
                m_shownHits++;
                l50.type = 0;
                l50.sound = 2;
                l50.x = (double)(int)(x + 50.0 - (WORD)Random(0, 0x64));
                l50.y = (double)((WORD)Random(0, 0x64) - 0x64);
                l50.facing = facing;
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_patternVar1++;
            if (m_patternVar1 == 0xd) {
                m_patternVar1 = 0;
            }
        }
        if (frame > 4 && frame < 8) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                (*m_opponent)->timer = 0;
                (*m_opponent)->pattern = kLyingDown;
                DealDamage(0x1194, 1000.0);
                if (m_roundsWon + 1 != m_game->m_roundsToWin) {
                    (*m_opponent)->m_koDelay = 0x7530;
                }
                if ((*m_opponent)->m_hp <= 0) {
                    l50.type = 0x1ac;
                    l50.x = 0.0;
                    l50.y = 0.0;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.keep = 1;
                    l50.shadow = 0;
                    l50.facing = 1;
                    l50.screen = 1;
                    SpawnObject(&l50);
                    m_playVoice = 4;
                }
            }
            m_attackResult = 0;
            if (frame == 8 && m_patternVar3 < 3) {
                (*m_opponent)->timer = 0;
                frame = 5;
                if ((*m_opponent)->m_hp > 0) {
                    m_patternVar3++;
                }
            }
            if (frame == 8) {
                (*m_opponent)->m_koDelay = 0;
            }
            if (frame == 3 && m_patternVar2 < 0xf) {
                m_patternVar2++;
                frame = 1;
                if (m_patternVar2 > 0xe) {
                    pattern = kStand;
                    FaceOpponent();
                    StartPattern();
                }
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedGrabSuper:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0;
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 0) {
            FocusCameraY(0x32, 0xa);
        }
        if (frame == 5 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            if (x > 560.0 && facing == 1) {
                x = 560.0;
            }
            if (x < 80.0 && facing == -1) {
                x = 80.0;
            }
            (*m_opponent)->x = (m_pointX[2] + 0x47) * facing + x;
            (*m_opponent)->y = 0.0;
            pattern = kUnusedGrabSuperHit;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                m_playVoice = 0x15;
                if ((*m_opponent)->y == 0.0) {
                    m_hitsLeft = 1;
                }
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedGrabSuperHit:
        if (frame == 1) {
            (*m_opponent)->x = (m_pointX[2] + 0x3c) * facing + x;
            (*m_opponent)->y = y - 13.0 - m_pointY[2];
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 2) {
            (*m_opponent)->x = (m_pointX[3] + 0x2e) * facing + x;
            (*m_opponent)->y = y - 16.0 - m_pointY[3];
            (*m_opponent)->pattern = kThrownAirRising;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 3) {
            (*m_opponent)->x = (m_pointX[4] + 0x1a) * facing + x;
            (*m_opponent)->y = y - 41.0 - m_pointY[4];
            (*m_opponent)->pattern = kThrownAirborne2;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 4) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -2.9;
            (*m_opponent)->pattern = kHitAirLaunch;
        }
        if (frame == 0xb && timer == 0) {
            m_freezeTime = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
        }
        if (frame > 0x10) {
            m_patternVar1++;
        }
        if (m_patternVar1 == 0x5a || m_patternVar1 == 0x12c) {
            l50.type = 0x1a5;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)(int)(*m_opponent)->y;
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0x96 || m_patternVar1 == 0x168) {
            l50.type = 0x1a6;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x40);
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0xf0 || m_patternVar1 == 0xc8) {
            l50.type = 0x1a7;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x80);
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0x78 || m_patternVar1 == 0x10e) {
            l50.type = 0x1a8;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)(int)(*m_opponent)->y;
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0xb4 || m_patternVar1 == 0x14a) {
            l50.type = 0x1a9;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x50);
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0xd2 || m_patternVar1 == 0x186) {
            l50.type = 0x1aa;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x7d);
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0x1f4) {
            l50.type = 0x1ab;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = 0.0;
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame < 0x10) {
            FocusCameraY(0x32, 3);
        }
        if (frame >= 0x10) {
            (*m_opponent)->FocusCameraY(0x32, 3);
        }
        if ((*m_opponent)->pattern == kLyingDown && frame < 0x14) {
            timer = 0;
            frame = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x14) {
                frame = frame - 3;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedAirSuper:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0, 0x28);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.025;
                m_playVoice = 1;
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= x8) {
                frame = 1;
            }
        }
    }
}
