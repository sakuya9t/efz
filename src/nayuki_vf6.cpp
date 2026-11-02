// CNayuki::UpdatePattern (0x451850-0x46108f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CNayuki's
// .rdata, which starts with its constructor's folder name (nayuki.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CNayuki::UpdatePattern()
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
        vx = m_warmUp * 0.02 + 0.6;
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
        vx = -0.6 - m_warmUp * 0.02;
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
        if (frame == 3 && timer == 0) {
            ay = 0.024;
            vy = -2.0;
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
        if (y + vy >= 0.0 && frame > 4) {
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
        if (frame == 3 && timer == 0) {
            ay = 0.024;
            vy = -2.0;
            vx = 0.5;
            if (m_dashMomentum == 1) {
                vx = 0.7;
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
        if (y + vy >= 0.0 && frame > 4) {
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
        if (frame == 3 && timer == 0) {
            ay = 0.024;
            vy = -2.0;
            vx = -0.5;
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
        if (y + vy >= 0.0 && frame > 4) {
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
        ay = 0.024;
        if (frame == 0 && timer == 0) {
            vy = -2.0;
            vx = 0.0;
            if (m_dashMomentum == 1) {
                vx = 0.4;
                m_dashMomentum = 0;
            }
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
        ay = 0.024;
        if (frame == 0 && timer == 0) {
            vy = -2.0;
            vx = 0.7;
            if (m_dashMomentum == 1) {
                vx = 1.1;
                m_dashMomentum = 0;
            }
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
        ay = 0.024;
        if (frame == 0 && timer == 0) {
            vy = -2.0;
            vx = -0.7;
            if (m_dashMomentum == 1) {
                m_dashMomentum = 0;
            }
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
            l50.layer = 1;
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
        if (frame == 1 && timer == 0 && m_warmUp > 0) {
            m_warmUp--;
        }
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
    case kEatingJam:
        vx = 0.0;
        vy = 0.0;
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
    case kGuardStandLight:
        if (frame == 0 && timer == 0) {
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
    case 0xa1:
        if (frame == 0 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
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
        if (frame == 7 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
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
            if (frame == 0xd) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StartAfterimages(1);
            StopMoving();
        }
        if (frame < 0xb && frame > 4) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 0xb) {
            timer = 0;
            StopMoving();
            frame = 0xb;
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                vx = 1.4;
                vy = -0.75;
                ay = 0.015;
            }
            if (frame == 0xb) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                break;
            }
        }
        break;
    case kDashBack:
        StartAfterimages(2);
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 3) {
            vx += 0.02;
            vy += 0.035;
        }
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (y + vy > 0.0 && frame < 0xb) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                vx = -2.0 - m_warmUp * 0.1;
                vy = -1.2;
            }
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0) {
            if (m_warmUp > 7) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            StopMoving();
            l50.type = 0x190;
            l50.x = (double)((int)x - facing * 0x24);
            l50.y = (double)((int)y - 0x3e);
            l50.facing = facing;
            l50.layer = 0;
            l50.scale = 0;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 1 && frame == 0) {
            vx = 1.9;
            vy = -0.2;
            ay = 0.035;
            timer = 0;
            frame = 1;
            break;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            StopMoving();
            StartPattern();
            pattern = 0xb3;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0) {
            StopMoving();
            if (m_warmUp > 4) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x3e);
            l50.facing = -facing;
            l50.layer = 1;
            l50.scale = 0;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 1 && frame == 0) {
            vx = -1.9;
            vy = -0.2;
            ay = 0.035;
            timer = 0;
            frame = 1;
            break;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            StopMoving();
            StartPattern();
            pattern = 0xb3;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kInstantCharge:
        if (frame == 0 && timer == 0) {
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
                FaceOpponent();
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
    case 0xb3:
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
        if (y + vy > 0.0 && frame < 0xb) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xb;
            m_playSound = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 0xb) {
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
        if (timer >= l4 || timer >= l4 - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 4;
            }
            if (frame == 2 && m_warmUp > 3) {
                frame = 3;
            }
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
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            if (m_warmUp > 5) {
                m_hitsLeft = 1;
            }
        }
        if (frame == 5 && timer == 0) {
            m_hitsLeft = 8;
        }
        if (frame < 0xa && frame > 5) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            if (frame < 0xa && frame > 5) {
                frame = 0xa;
                ShakeScreen(3, 0);
                l50.type = 3;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                m_playSound = 7;
            }
            vy = 0.0;
        }
        if (frame >= 0xa) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                vy = -1.5;
                vx = m_warmUp * 0.05 + 1.0;
                ay = 0.06;
            }
            if (frame == 0xa) {
                frame = frame - 4;
            }
            if (frame == 0xb) {
                if (m_warmUp > 4) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame == 4 || frame == 5 || frame == 7 || frame == 9 || frame == 0xb) {
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
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 0;
        }
        if (m_inputY == -1 && frame > 0 && m_warmUp > 4 && y == 0.0 && m_sealLevel < 3 && m_attackResult >= 2 && m_warmUp > 6) {
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
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            if (m_warmUp > 5) {
                m_hitsLeft = 1;
            }
        }
        if (frame == 0xa && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame > 0xd) {
            vy = vy + ay;
        }
        if (frame > 0xd && vy + y > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa) {
                m_playVoice = 3;
            }
            if (frame < 9) {
                m_attackResult = 0;
            }
            if (frame == 8 || frame == 9 || frame == 0xa) {
                x = facing * 0x28 + x;
            }
            if (frame == 0xe) {
                vy = -1.0;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= x8) {
                frame--;
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
            if (frame == 3) {
                frame = 4;
            }
            if (frame == 2 && m_warmUp > 4) {
                frame = 3;
            }
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
        if (timer >= l4 || timer >= 3 && (frame == 1 && m_warmUp > 0 || frame == 2 && m_warmUp > 1 || frame == 3 && m_warmUp > 3 || frame == 4 && m_warmUp > 5)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                x = facing * 0xf + x;
            }
            if (frame == 2) {
                x = facing * 0xf + x;
            }
            if (frame >= x8) {
                pattern = kCrouch;
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
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && frame < m_warmUp - 4 && frame < 4) {
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
        if (timer >= l4) {
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
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = m_warmUp / 2 + 2;
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
            if (frame < 6) {
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
            m_hitsLeft = 3;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && frame < m_warmUp - 3 && frame < 4) {
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
    case k6B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            ay = 0.055;
            vy = -1.7;
            vx = 0.5;
            m_hitsLeft = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        if (frame == 8 && timer == 0) {
            m_playSound = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
                break;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 0xb) {
            y = 0.0;
            m_playSound = 9;
            frame = 0xb;
            timer = 0;
            StopMoving();
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
    case kUnusedAirDive:
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vy -= -1.0;
            ay = 0.035;
        }
        vy = vy + ay;
        if (m_attackResult > 1) {
            timer = 0;
            frame = 0;
            pattern = kRebound;
            vx = -vx;
            vy = -2.5;
            ay = 0.025;
            break;
        }
        if (vy + y > 0.0 && frame < 5 && frame > 1) {
            y = 0.0;
            timer = 0;
            frame = 5;
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
            vx = 0.0;
            vy = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                frame--;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStandUp;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedD5:
        ay = 0.04;
        vx = 0.0;
        vy = vy + ay;
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kKnockdownHittable;
            StopMoving();
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
    case k5BFarC:
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 3;
        }
        if (y + vy > 0.0) {
            y = 0.0;
            timer = 0;
            StopMoving();
            frame = 0xa;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStandUp;
                StartPattern();
            }
        }
        break;
    case kThrow:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            if (x > 600.0) {
                x = 600.0;
            }
            if (x < 40.0) {
                x = 40.0;
            }
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = kThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            (*m_opponent)->x = facing * 0xf + x;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x16);
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
        if (frame == 4 && timer == 0) {
            DealDamage(0x3e8, 750.0);
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = 1.0;
            (*m_opponent)->m_hitVy = -2.5;
            (*m_opponent)->y = -50.0;
            (*m_opponent)->x = x;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = (*m_opponent)->x - facing;
            }
            if (frame == 2) {
                (*m_opponent)->x = (*m_opponent)->x - facing;
            }
            if (frame == 3) {
                (*m_opponent)->x = (*m_opponent)->x - facing;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kDashJumpA:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && m_airActions == 0) {
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
        if (timer >= l4) {
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
    case kDashJumpB:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && m_airActions == 0) {
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
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = m_warmUp / 2 + 2;
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
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kDashJumpC:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && m_airActions == 0) {
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
        if (timer >= l4 || timer >= l4 - 3 && frame < m_warmUp - 3 && frame < 4) {
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
    case kAirThrow:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x21);
            l50.y = (double)((int)y - 0x33);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x21 + x;
            (*m_opponent)->y = y - 61.0;
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
        if (frame < 7) {
            FocusCameraX(0x32, 3);
        }
        if (frame < 7) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 5) {
            StopMoving();
            y = 0.0;
            StartPattern();
            pattern = kLand;
            break;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 66.0;
            (*m_opponent)->x = facing * 0x17 + x;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 69.0;
            (*m_opponent)->x = facing * 0x15 + x;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 73.0;
            (*m_opponent)->x = facing * 0x13 + x;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 74.0;
            (*m_opponent)->x = facing * 0x13 + x;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 0x11 + x;
        }
        if (frame == 6) {
            (*m_opponent)->y = y - 70.0;
            (*m_opponent)->x = (facing << 4) + x;
        }
        if (frame == 7 && timer == 0) {
            (*m_opponent)->facing = facing;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = x - facing * 0x25;
            (*m_opponent)->pattern = kHitAirLaunch;
            DealDamage(0x514, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitVx = -2.0;
            (*m_opponent)->m_hitVy = -1.0;
        }
        if (frame == 0xb && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xb) {
                facing = -facing;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.shadow = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.shadow = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
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
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x193;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.shadow = 1;
            l50.scale = 0;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedFd:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 2;
        }
        if (y < 0.0) {
            vy = vy + ay;
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                m_playSound = 0x14;
                m_gauge = m_gauge + 0x2d;
                vx = 1.2;
                vy = -2.5;
                ay = 0.03;
            }
            if (frame >= x8) {
                pattern = kUnused100;
                if (m_inputY == 1) {
                    pattern = kUnused102;
                }
                StartPattern();
            }
        }
        break;
    case kUnusedFe:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                m_playSound = 0x14;
                m_gauge = m_gauge + 0x2d;
                vx = 1.7;
                vy = -1.7;
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = kUnused102;
                StartPattern();
            }
        }
        break;
    case kUnused100:
        if (frame == 0 && timer == 0) {
            vx = 2.4;
            m_hitsLeft = 1;
            vy = 0.0;
        }
        if ((char)AtScreenEdge() != 0 && m_patternVar2 == 0) {
            vx = -0.7;
            vy = -2.0;
            ay = 0.035;
            pattern = kRebound;
            m_playSound = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_patternVar2++;
            break;
        }
        if (m_hitsLeft == 0) {
            vx = -0.7;
            vy = -2.0;
            ay = 0.035;
            pattern = kRebound;
            break;
        }
        timer++;
        if (y == 0.0 && vy >= 0.0) {
            vy = 0.0;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case kRebound:
        vy = vy + ay;
        ClearBufferedPress();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                StartPattern();
                pattern = kFall;
            }
        }
        break;
    case kUnused102:
        ay = 0.04;
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kKnockdownHittable;
            StopMoving();
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
    case k5D:
        StopMoving();
        if (frame == 0 && timer == 0) {
            m_playVoice = 4;
        }
        if (frame == 0xa && timer == 0) {
            m_warmUp++;
        }
        if (frame == 0xa && timer == 0) {
            m_playVoice = 5;
        }
        if (m_warmUp > 9) {
            m_warmUp = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                StartPattern();
                pattern = kStandUp;
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            ay = 0.035;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame > 8 && vy + y > 0.0) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 0xc;
        }
        if (frame > 4 && frame < 9) {
            vx -= 0.025;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_patternVar2++;
            m_attackResult = 0;
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.8;
                vy = -1.9;
                if (m_warmUp > 2) {
                    vx = 2.1;
                    vy = -2.0;
                }
                if (m_warmUp > 5) {
                    vx = 2.4;
                    vy = -2.1;
                }
                if (m_warmUp > 8) {
                    vx = 3.0;
                    vy = -2.2;
                }
            }
            if (frame == 5) {
                if (m_warmUp > 2) {
                    frame = 6;
                }
                if (m_warmUp > 5) {
                    frame = 7;
                }
                if (m_warmUp > 8) {
                    frame = 8;
                }
                break;
            }
            if (frame > 5 && frame < 9) {
                frame = 9;
            }
            if (frame == 9) {
                ay = 0.035;
                vx *= 0.3;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 3;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame > 5 && vy + y > 0.0) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (frame == 5 || frame == 9 || frame == 0xd) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.2;
                vy = -1.2;
                ay = 0.03;
                if (m_warmUp > 6) {
                    vy = -2.2;
                }
            }
            if (frame == 8 && m_warmUp < 5 || frame == 0xb && m_warmUp < 7) {
                frame = 0xf;
            }
            if (frame == 0xf) {
                if (vy < 0.0) {
                    vy *= 0.5;
                }
                vx *= 0.5;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case k623C:
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
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = m_warmUp + 1;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 0x63;
        }
        vy = vy + ay;
        if (frame > 0xb && vy + y > 0.0) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (frame == 5 || frame == 9 || frame == 0xd) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 0.8;
                vy = -1.5;
                ay = 0.035;
                m_invulTime = m_warmUp * 0xc + 0x1e;
            }
            if (frame == 7 || frame == 0xb) {
                vy = -1.4;
            }
            if (frame == 0xc) {
                frame = 4;
            }
            if ((frame == 0xb || frame == 8) && m_patternVar1 > m_warmUp) {
                frame = 0xc;
            }
            if (frame == 0xb || frame == 8) {
                m_patternVar1++;
            }
            if (frame == 0xf && vy < 0.0) {
                vy *= 0.5;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case kUnused107:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = m_warmUp + 6;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame > 0xf) {
            vx -= 0.028;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 6 || frame == 0xb) && timer == 0) {
            m_playSound = 0x14;
        }
        if (y + vx > 0.0 && frame > 5 && frame < 0x10) {
            timer = 0;
            y = 0.0;
            vy = 0.0;
            frame = 0x10;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (m_patternVar2 > 2) {
                m_attackResult = 0;
                m_patternVar2 = 0;
            }
            if (frame == 5) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.8;
                vy = -1.7;
                ay = 0.035;
                if (m_patternVar1 == 1) {
                    vx = 0.6;
                    vy = -3.2;
                    ay = 0.024;
                }
            }
            if (frame == 0x10) {
                frame = 5;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
            }
        }
        break;
    case k41236A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 2;
        }
        if (frame > 9) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            m_playSound = 0x15;
        }
        timer++;
        if (timer >= 0x18 && m_warmUp > 3 && frame == 0xb) {
            frame++;
            timer = 0;
            m_attackResult = 0;
        }
        if (timer >= l4 || timer >= l4 - m_warmUp * 3 && frame == 0xb || timer >= l4 - 3 && frame == 1 && m_warmUp > 2 || timer >= l4 - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 2.2;
                if (m_patternVar1 == 1) {
                    vx = 3.4;
                }
            }
            if (frame == 7 && m_patternVar2 < 2) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame == 7 && m_patternVar1 == 1 && m_patternVar2 < 4) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case k41236B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 2;
        }
        if (frame > 9) {
            vx += 0.08;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            m_playSound = 0x15;
        }
        timer++;
        if (timer >= 0x18 && m_warmUp > 3 && frame == 0xb) {
            frame++;
            timer = 0;
            m_attackResult = 0;
        }
        if (timer >= l4 || timer >= l4 - m_warmUp * 3 && frame == 0xb || timer >= l4 - 3 && frame == 1 && m_warmUp > 2 || timer >= l4 - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = -2.2;
            }
            if (frame == 7 && m_patternVar2 < 2) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame == 7 && m_patternVar1 == 1 && m_patternVar2 < 4) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case k41236C:
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
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = m_warmUp + 1;
        }
        if (frame > 9) {
            vx -= 0.3;
            m_hitsLeft = 1;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            m_playSound = 0x15;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - m_warmUp * 3 && frame == 0xb || timer >= l4 - 3 && frame == 1 && m_warmUp > 2 || timer >= l4 - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 2.5;
            }
            if (frame == 7 && m_patternVar2 < 2) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame == 7 && m_patternVar1 == 1 && m_patternVar2 < 4) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case kUnused10b:
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
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 0x63;
        }
        if (frame > 9) {
            vx -= 0.3;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            m_playSound = 0x15;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 2.8;
            }
            if (frame == 7 && m_patternVar2 < 2) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame == 7 && m_patternVar1 == 1 && m_patternVar2 < 4) {
                frame = 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case k214Stance:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 7) {
            if (m_command == kCmdDashRight) {
                StartPattern();
                ClearBufferedPress();
                pattern = kDashForward;
                if (facing == -1) {
                    pattern = kDashBack;
                }
                break;
            }
            if (m_command == kCmdDashLeft) {
                StartPattern();
                ClearBufferedPress();
                pattern = kDashBack;
                if (facing == -1) {
                    pattern = kDashForward;
                }
                break;
            }
            if (m_command == kCmd236A && m_warmUp > 0) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236A;
                break;
            }
            if (m_command == kCmd236B && m_warmUp > 0) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236B;
                break;
            }
            if (m_command == kCmd623A && m_warmUp > 0) {
                StartPattern();
                ClearBufferedPress();
                pattern = k623A;
                break;
            }
            if (m_pressA == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceA;
                if (m_warmUp > 4) {
                    pattern = kStanceAWarm;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceB;
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceC;
                if (m_inputY == 1) {
                    pattern = kStance2C;
                }
                break;
            }
            if (m_pressD == 1) {
                if (m_inputX == facing) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kStance6D;
                    if (m_warmUp > 4) {
                        pattern = kStance6D;
                    }
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kStance4D;
                    if (m_warmUp > 4) {
                        pattern = kStance4D;
                    }
                    break;
                }
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceD;
                if (m_inputY == 1) {
                    pattern = k2D;
                }
                if (m_warmUp == 9) {
                    pattern = k214Stance;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (frame >= x8) {
                pattern = kStand;
                StopMoving();
                StartPattern();
                break;
            }
        }
        break;
    case kStanceAWarm:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vx > 0.0 && frame > 2 && frame < 8) {
            timer = 0;
            y = 0.0;
            StopMoving();
            frame = 8;
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.4;
                vy = -2.1;
                ay = 0.045;
            }
            if (frame == 8) {
                frame--;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StopMoving();
                StartPattern();
            }
        }
        break;
    case kUnused10e:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
        }
        if (frame > 8) {
            vy = vy + ay;
        }
        if (frame > 8 && vy + y > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                m_playVoice = 3;
                m_hitsLeft = 1;
            }
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3 || frame == 4 || frame == 5) {
                x = facing * 0x28 + x;
            }
            if (frame == 9) {
                vy = -1.0;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case kStanceD:
        StopMoving();
        if (frame == 5 && timer == 0) {
            m_playVoice = 5;
        }
        if (frame == 5 && timer == 0) {
            m_warmUp++;
        }
        if (m_warmUp > 9) {
            m_warmUp = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                StartPattern();
                pattern = kStandUp;
            }
        }
        break;
    case kUnused110:
        if (frame == 0 && timer == 0) {
            vx = 1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            m_playSound = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceA;
                if (m_warmUp > 4) {
                    pattern = kStanceAWarm;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceB;
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceC;
                if (m_inputY == 1) {
                    pattern = kStance2C;
                }
                break;
            }
            if (m_pressD == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceD;
                if (m_inputY == 1) {
                    pattern = k2D;
                }
                if (m_warmUp == 9) {
                    pattern = k214Stance;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = k214Stance;
                StopMoving();
                StartPattern();
                frame = 8;
                break;
            }
        }
        break;
    case kUnused111:
        if (frame == 0 && timer == 0) {
            vx = -1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            m_playSound = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceA;
                if (m_warmUp > 4) {
                    pattern = kStanceAWarm;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceB;
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceC;
                if (m_inputY == 1) {
                    pattern = kStance2C;
                }
                break;
            }
            if (m_pressD == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceD;
                if (m_inputY == 1) {
                    pattern = k2D;
                }
                if (m_warmUp == 9) {
                    pattern = k214Stance;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = k214Stance;
                StopMoving();
                StartPattern();
                frame = 8;
                break;
            }
        }
        break;
    case kStanceB:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        timer++;
        if (timer >= l4 - (frame == 9) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                l50.type = 0x1ac;
                if (m_inputX == facing) {
                    l50.type = 0x1ad;
                }
                if (m_inputX == -facing) {
                    l50.type = 0x1ab;
                }
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x32);
                l50.scale = 0;
                l50.shadow = 1;
                l50.layer = 0;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 0;
                m_gauge = m_gauge + 0x2d;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kStanceA:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vx > 0.0 && frame > 2 && frame < 8) {
            timer = 0;
            y = 0.0;
            StopMoving();
            frame = 8;
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.4;
                vy = -2.1;
                ay = 0.045;
            }
            if (frame == 8) {
                frame--;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StopMoving();
                StartPattern();
            }
        }
        break;
    case kStanceC:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
        }
        if (frame > 8) {
            vy = vy + ay;
        }
        if (frame > 8 && vy + y > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= l4 || frame == 1 && timer == 0x27 - m_warmUp * 3) {
            timer = 0;
            frame++;
            if (frame == 5) {
                m_playVoice = 3;
                m_hitsLeft = 1;
            }
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3 || frame == 4 || frame == 5) {
                x = facing * 0x28 + x;
            }
            if (frame == 9) {
                vy = -0.7;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case kStance6D:
        if (frame == 0 && timer == 0) {
            vx = 1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            m_playSound = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceA;
                if (m_warmUp > 4) {
                    pattern = kStanceAWarm;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceB;
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceC;
                if (m_inputY == 1) {
                    pattern = kStance2C;
                }
                break;
            }
            if (m_pressD == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceD;
                if (m_inputY == 1) {
                    pattern = k2D;
                }
                if (m_warmUp == 9) {
                    pattern = k214Stance;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = k214Stance;
                StopMoving();
                StartPattern();
                frame = 8;
                break;
            }
        }
        break;
    case kStance4D:
        if (frame == 0 && timer == 0) {
            vx = -1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            m_playSound = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceA;
                if (m_warmUp > 4) {
                    pattern = kStanceAWarm;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceB;
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceC;
                if (m_inputY == 1) {
                    pattern = kStance2C;
                }
                break;
            }
            if (m_pressD == 1) {
                StartPattern();
                ClearBufferedPress();
                pattern = kStanceD;
                if (m_inputY == 1) {
                    pattern = k2D;
                }
                if (m_warmUp == 9) {
                    pattern = k214Stance;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = k214Stance;
                StopMoving();
                StartPattern();
                frame = 8;
                break;
            }
        }
        break;
    case k236236A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 2) {
            unkf2 = 0xa;
        }
        if (frame == 4 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.layer = 0;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
        }
        timer++;
        if (timer >= l4 || frame == 5 && timer == l4 - m_warmUp * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236D:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.shadow = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k2D:
        StopMoving();
        if (frame == 0 && timer == 0) {
            m_playVoice = 4;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case kStance2C:
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
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
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 2) {
            unkf2 = 0xa;
        }
        if (frame == 4 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.layer = 0;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
        }
        timer++;
        if (timer >= l4 || frame == 5 && timer == l4 - m_warmUp * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
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
            m_playSound = 0x25;
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 4 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x198;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.layer = 0;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 0;
        }
        timer++;
        if (timer >= l4 || frame == 5 && timer == l4 - m_warmUp * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 || frame == 7) {
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -0.5;
            }
            if (m_inputY == 1) {
                vy = 0.5;
            }
            if (m_inputX == facing) {
                vx = 0.5;
            }
            if (m_inputX == -facing) {
                vx = -0.5;
            }
        }
        if (frame > 7) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 7 && frame < 0xc) {
            StopMoving();
            y = 0.0;
            frame = 0xc;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                l50.keep = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x50);
                l50.facing = facing;
                l50.scale = 0;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)y;
                SpawnObject(&l50);
            }
            if (frame == 8) {
                if (m_patternVar1 < 0xe) {
                    frame = frame - 2;
                    m_patternVar1++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 || frame == 7) {
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -0.65;
            }
            if (m_inputY == 1) {
                vy = 0.65;
            }
            if (m_inputX == facing) {
                vx = 0.65;
            }
            if (m_inputX == -facing) {
                vx = -0.65;
            }
        }
        if (frame > 7) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 7 && frame < 0xc) {
            StopMoving();
            y = 0.0;
            frame = 0xc;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                l50.keep = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x50);
                l50.facing = facing;
                l50.scale = 0;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)y;
                SpawnObject(&l50);
            }
            if (frame == 8) {
                if (m_patternVar1 < 0x14) {
                    frame = frame - 2;
                    m_patternVar1++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
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
            m_playSound = 0x25;
        }
        if (frame > 3) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 6 || frame == 7) {
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -0.8;
            }
            if (m_inputY == 1) {
                vy = 0.8;
            }
            if (m_inputX == facing) {
                vx = 0.8;
            }
            if (m_inputX == -facing) {
                vx = -0.8;
            }
        }
        if (frame > 7) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 7 && frame < 0xc) {
            StopMoving();
            y = 0.0;
            frame = 0xc;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                l50.keep = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x50);
                l50.facing = facing;
                l50.scale = 0;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)y;
                SpawnObject(&l50);
            }
            if (frame == 8) {
                if (m_patternVar1 < 0x14) {
                    frame = frame - 2;
                    m_patternVar1++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = kStandUp;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 0x63;
        }
        if (frame > 0xe) {
            vx += 0.035;
        }
        FocusCameraY(0x32, 3);
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
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame > 0xa && frame < 0xf) {
            ShakeScreen(3, 0xa);
        }
        if ((char)AtScreenEdge() != 0 && frame > 0xe && vx > 4.0) {
            vx = -2.7;
            vy = -3.5;
            ay = 0.035;
            pattern = kRebound;
            StartPattern();
            m_playSound = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x19b;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x19b;
            l50.x = (double)((int)x - facing * 0x32);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            break;
        }
        if (frame == 0xc && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0xf && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf) {
                if (m_patternVar1 < 0xa) {
                    frame = frame - 4;
                    m_patternVar1++;
                } else {
                    l50.type = 0x34;
                    l50.x = (double)(int)x;
                    l50.y = (double)((int)y - 0x19);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.sound = 0x16;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    vx = 0.5;
                    ShakeScreen(0xf, 0xa);
                    l50.keep = 1;
                    l50.type = 0x1a1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.shadow = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
    }
}
