// CShiori::UpdatePattern (0x4136d0-0x422d6f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CShiori's
// .rdata, which starts with its constructor's folder name (shiori.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CShiori::UpdatePattern()
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.35;
            if (m_dashMomentum == 1) {
                vx = 0.3;
                m_dashMomentum = 0;
            }
        }
        if (frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.35;
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
            ay = 0.035;
            vy = -2.35;
            vx = -0.7;
        }
        if (frame > 2) {
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
                pattern = kStand;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case kAirJump:
        ay = 0.035;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.35;
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
        ay = 0.035;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.35;
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
        ay = 0.035;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.35;
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
        timer++;
        m_dashMomentum = 0;
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
        }
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
        if (frame == 2 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 6 && timer == 0) {
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
            if (frame == 0xf) {
                ay = 0.035;
            }
            if (frame >= x8) {
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
        vx = 1.5;
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= x8) {
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
        StartAfterimages(2);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -1.6;
            vy = -1.0;
            ay = 0.04;
        }
        if (frame > 1 && frame < 5) {
            vy = vy + ay;
        }
        if (frame > 2 && vy + y >= 0.0 && m_patternVar1 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            m_patternVar1++;
            m_playSound = 9;
            frame = 5;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 0x27) {
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
        if (y + vy > 0.0 && frame < 0xa) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xa;
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
            if (frame == 0xa) {
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
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
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.sound = 1;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar2 < 5) {
                m_patternVar2++;
                frame = frame - 2;
                if (m_patternVar2 == 3) {
                    m_hitsLeft = 0;
                }
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
            if (frame == 4 && m_patternVar1 == 0) {
                frame = frame - 2;
                m_patternVar1++;
            }
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
            m_playVoice = 2;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
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
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = kThrowConnected;
            (*m_opponent)->pattern = kThrownStandHigh2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
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
        if (frame == 1 && timer == 0 && m_patternVar3 == 8) {
            DealDamage(0x3e8, 750.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kEncasedSpin;
            (*m_opponent)->m_hitVx = -1.0;
            (*m_opponent)->m_hitVy = -4.0;
        }
        if (frame > 0xe) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                pattern = kLand;
                StartPattern();
                StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && m_patternVar3 < 0xe) {
                m_patternVar3++;
                frame = 0;
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
    case kDashC:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame > 0 && frame < 2) {
            vx -= 0.03;
        }
        if (frame == 6 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 0xb;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vx = 1.0;
                vy = -0.9;
                ay = 0.02;
                m_hitsLeft = 1;
            }
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
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kDash2B:
        StartAfterimages(3);
        m_dashMomentum = 0;
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
    case kDash2C:
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
    case kAirThrow:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_noAirRecovery = 1;
            StopMoving();
            StartPattern();
            l50.type = 0;
            l50.x = (double)((int)x + (facing << 5));
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = kAirThrowConnected;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (facing << 5) + x;
            (*m_opponent)->y = y - 57.0;
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
    case kAirThrowConnected:
        m_hideOffscreenMarker = 2;
        if (frame == 2 && timer == 0 && m_patternVar1 == 8) {
            DealDamage(0x44c, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kEncasedSpin;
            (*m_opponent)->m_hitVx = -1.0;
            (*m_opponent)->m_hitVy = -4.0;
        }
        if (frame > 3) {
            vy += 0.035;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 && m_patternVar1 < 0xf) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 5;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 5;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        vx = vx + ax;
        m_dashMomentum = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
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
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 6;
        }
        if (m_patternVar2 == 0x14) {
            l50.type = 0x1ab;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)((int)y - 0x14);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 5;
        }
        if (m_patternVar2 == 0x28) {
            l50.type = 0x1ab;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_playVoice = 5;
        }
        if (frame > 4) {
            m_patternVar2++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1ab;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.sound = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 5;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_patternVar1 = 6;
            m_hitsLeft = 5;
        }
        if (frame == 4 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 1;
        }
        if (frame == 6 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 4;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_patternVar1 = 8;
            m_hitsLeft = 9;
        }
        if (frame == 4 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 1;
        }
        if (frame == 6 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 4;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 0x12;
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
        if (frame == 3 && timer == 0 && m_patternVar1 == 0) {
            l50.type = 0x1a1;
            l50.facing = facing;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x30);
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 4 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 1;
        }
        if (frame == 6 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 7 && m_patternVar1 < 0xc) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir412A:
        if (frame == 0 && timer == 0) {
            vx *= 0.25;
            vy *= 0.25;
            ay = 0.01;
        }
        vy = vy + ay;
        timer++;
        if (vy > 0.2) {
            vy = 0.2;
        }
        if (y == 0.0 && vy >= 0.0) {
            vy = 0.0;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                ay = 0.01;
                m_playVoice = 1;
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xe);
                l50.y = (double)(int)y;
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 0;
                SpawnObject(&l50);
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = (double)((int)y - 0x10);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = kFall;
                ay = 0.028;
                StartPattern();
            }
        }
        break;
    case kAir412B:
        if (frame == 0 && timer == 0) {
            vx *= 0.25;
            vy *= 0.25;
            ay = 0.01;
        }
        vy = vy + ay;
        timer++;
        if (vy > 0.2) {
            vy = 0.2;
        }
        if (y == 0.0 && vy >= 0.0) {
            vy = 0.0;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                ay = 0.01;
                m_playVoice = 1;
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xe);
                l50.y = (double)(int)y;
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 0;
                SpawnObject(&l50);
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = (double)((int)y - 0x10);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = kFall;
                ay = 0.028;
                StartPattern();
            }
        }
        break;
    case kAir412C:
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
            vx *= 0.25;
            vy *= 0.25;
            ay = 0.01;
        }
        vy = vy + ay;
        if (vy > 0.2) {
            vy = 0.2;
        }
        timer++;
        if (y == 0.0 && vy >= 0.0) {
            vy = 0.0;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                ay = 0.01;
                m_playVoice = 1;
                l50.type = 0x194;
                l50.x = (double)((int)x + facing * 0xe);
                l50.y = (double)(int)y;
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 0;
                SpawnObject(&l50);
                l50.type = 0x194;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = (double)((int)y - 0x10);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = kFall;
                ay = 0.028;
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 2) {
                l50.type = 0x197;
                l50.x = (double)((int)x - facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 1) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 2 && timer == 0) {
                l50.type = 0x19a;
                l50.x = (double)((int)x - facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 1) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214C:
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
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 2 && timer == 0) {
                l50.type = 0x1c4;
                l50.x = (double)((int)x - facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kAir236A:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 4;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x24);
                l50.y = (double)((int)y - 0x30);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 5;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kAir236B:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x24);
                l50.y = (double)((int)y - 0x30);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 5;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
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
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 6;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
        }
        vy = vy + ay;
        if (m_patternVar2 == 0x14) {
            l50.type = 0x1ac;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            m_patternVar3 = 1;
            SpawnObject(&l50);
            m_playVoice = 5;
        }
        if (m_patternVar2 == 0x28) {
            l50.type = 0x1ac;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x48);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            m_patternVar3 = 2;
            SpawnObject(&l50);
            m_playVoice = 5;
        }
        if (frame > 4) {
            m_patternVar2++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1ac;
                l50.x = (double)((int)x + facing * 0x1d);
                l50.y = (double)((int)y - 0x34);
                l50.scale = 2;
                l50.sound = 1;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_playVoice = 5;
            }
            if (frame == 7 && m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case k412A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x64);
            l50.y = (double)((int)y - 0x1e0);
            l50.facing = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = (double)((int)y - 0x208);
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0x82);
            l50.y = (double)((int)y - 0x212);
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
                FaceOpponent();
            }
        }
        break;
    case k412B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0xb4);
            l50.y = (double)((int)y - 0x1e0);
            l50.facing = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0xa0);
            l50.y = (double)((int)y - 0x208);
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0xd2);
            l50.y = (double)((int)y - 0x212);
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
                FaceOpponent();
            }
        }
        break;
    case k412C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x104);
            l50.y = (double)((int)y - 0x1e0);
            l50.facing = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0xf0);
            l50.y = (double)((int)y - 0x208);
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0x122);
            l50.y = (double)((int)y - 0x212);
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
                FaceOpponent();
            }
        }
        break;
    case kAir214A:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 2 && timer == 0) {
                l50.type = 0x197;
                l50.x = (double)((int)x - facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
        }
        break;
    case kAir214B:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 2 && timer == 0) {
                l50.type = 0x1c2;
                l50.x = (double)((int)x - facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
        }
        break;
    case kAir214C:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 0;
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 2 && timer == 0) {
                l50.type = 0x1c4;
                l50.x = (double)((int)x - facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
        }
        break;
    case kUnusedSuperSummon:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 1) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a3;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x5f);
            l50.scale = 0;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = facing;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
        }
        if (frame == 0xa && timer == 0) {
            l50.keep = 1;
            l50.type = 0x19a;
            l50.x = (double)((int)x + facing * 0x47);
            l50.y = (double)((int)y - 0x36);
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8) {
                x = facing * 0x35 + x;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k641236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x1ad;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1ae;
            SpawnObject(&l50);
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 4;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 3;
        }
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (((WORD)Random(0, 0x1e0) > 0xf0 || frame == 1) && m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0xf;
            StopMoving();
        }
        if (m_patternVar1 == 0) {
            if (frame == 2 && timer == 0) {
                m_playVoice = 4;
            }
            if (frame == 3 && timer == 0) {
                m_playVoice = 3;
            }
        }
        if (frame > 1 && m_patternVar2 <= 0 && m_patternVar3 < 5) {
            l50.keep = 1;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            if (m_patternVar3 == 0) {
                l50.type = 0x1ae;
                SpawnObject(&l50);
            }
            l50.y = (double)(m_patternVar3 * -0x50);
            l50.type = 0x1ad;
            m_patternVar2 = 0xf;
            m_patternVar3++;
            SpawnObject(&l50);
        }
        m_patternVar2--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_patternVar1 < 1 && frame == 0xa) {
                frame = frame - 6;
                m_patternVar1++;
            }
            if (((WORD)Random(0, 0x1e0) > 0xf0 || frame == 1) && m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x1e;
            m_playSound = 0x25;
            StopMoving();
        }
        m_game->FlashNegative(0xf);
        if (m_patternVar1 == 0) {
            if (frame == 2 && timer == 0) {
                m_playVoice = 4;
            }
            if (frame == 3 && timer == 0) {
                m_playVoice = 3;
            }
        }
        if (frame > 1 && m_patternVar2 <= 0 && m_patternVar3 < 5) {
            l50.keep = 1;
            l50.type = 0x1ad;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            if (m_patternVar3 == 0) {
                l50.type = 0x1ae;
                SpawnObject(&l50);
                l50.type = 0x1af;
                SpawnObject(&l50);
            }
            l50.y = (double)(m_patternVar3 * -0x50);
            l50.type = 0x1ad;
            m_patternVar2 = 0xf;
            m_patternVar3++;
            SpawnObject(&l50);
        }
        m_patternVar2--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_patternVar1 < 3 && frame == 0xa) {
                frame = frame - 6;
                m_patternVar1++;
            }
            if (((WORD)Random(0, 0x1e0) > 0xf0 || frame == 1) && m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 3 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x - (facing << 1));
            l50.y = (double)((int)y - 0x43);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0 && m_patternVar1 == 0) {
            l50.keep = 1;
            l50.type = 0x1b5;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = 0.0;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
            m_patternVar1++;
        }
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && m_patternVar2 < 4) {
                m_patternVar2++;
                frame = frame - 3;
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
        }
        m_dashMomentum = 0;
        if (frame == 3 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)((int)x - (facing << 1));
            l50.y = (double)((int)y - 0x43);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0 && m_patternVar2 == 0) {
            l50.keep = 1;
            l50.type = 0x1b6;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = 0.0;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && m_patternVar2 < 4) {
                m_patternVar2++;
                frame = frame - 3;
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
        }
        m_dashMomentum = 0;
        if (frame == 3 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - (facing << 1));
            l50.y = (double)((int)y - 0x43);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 6 && timer == 0 && m_patternVar2 == 0) {
            l50.keep = 1;
            l50.type = 0x1b7;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = 0.0;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && m_patternVar2 < 3) {
                m_patternVar2++;
                frame = frame - 3;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5D:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 5 && timer == 0) {
            m_dObjectTime = 0xe10;
            l50.keep = 1;
            l50.type = 0x1a7;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
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
    case kUnused5DLv2:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 4 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
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
        if (frame == 5 && timer == 0) {
            m_dObjectTime = 0x12c0;
            l50.keep = 1;
            l50.type = 0x1a8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
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
    case kUnused5DLv3:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 4 && timer == 0) {
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
            m_playSound = 0x25;
        }
        if (frame > 3) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 5 && timer == 0) {
            m_dObjectTime = 0x12c0;
            l50.keep = 1;
            l50.type = 0x1a9;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
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
    case kAir21436A:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
        }
        if (frame != 1) {
            vy = vy + ay;
        }
        if (frame < 8 && vy > 0.2) {
            vy = 0.2;
        }
        if (frame == 1 && timer == 0) {
            m_patternVar2 = (int)(vx * 100.0);
            vx = 0.0;
            m_patternVar3 = (int)(vy * 100.0);
            vy = 0.0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vx = m_patternVar2 * 0.01;
            vy = m_patternVar3 * 0.01;
            m_patternVar1 = 0;
            m_patternVar2 = 0;
            m_patternVar3 = 0;
        }
        if (frame > 4 && frame < 8 && m_patternVar1 <= 0 && m_patternVar3 < 0xf) {
            l50.keep = 0;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 0x1e - facing * 0x30 * ((WORD)Random(0, 2) == 0));
            l50.y = (double)((int)y + -0x20 + (WORD)Random(0, 5));
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.facing = facing;
            l50.scale = 2;
            SpawnObject(&l50);
            m_patternVar1 = 6;
            m_patternVar3++;
        }
        if (frame == 8 && timer == 0) {
            ay = 0.035;
        }
        if (frame > 7 && y + vy > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        m_patternVar1--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 8 && m_patternVar2 < 5) {
                m_patternVar2++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kAir21436B:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
        }
        if (frame != 1) {
            vy = vy + ay;
        }
        if (frame < 8 && vy > 0.2) {
            vy = 0.2;
        }
        if (frame == 1 && timer == 0) {
            m_patternVar2 = (int)(vx * 100.0);
            vx = 0.0;
            m_patternVar3 = (int)(vy * 100.0);
            vy = 0.0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vx = m_patternVar2 * 0.01;
            vy = m_patternVar3 * 0.01;
            m_patternVar1 = 0;
            m_patternVar2 = 0;
            m_patternVar3 = 0;
        }
        if (frame > 4 && frame < 8 && m_patternVar1 <= 0 && m_patternVar3 < 0x1b) {
            l50.keep = 0;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 0x1e - facing * 0x30 * ((WORD)Random(0, 2) == 0));
            l50.y = (double)((int)y + -0x20 + (WORD)Random(0, 5));
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.facing = facing;
            l50.scale = 2;
            SpawnObject(&l50);
            m_patternVar1 = 6;
            m_patternVar3++;
        }
        if (frame == 8 && timer == 0) {
            ay = 0.035;
        }
        if (frame > 7 && y + vy > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        m_patternVar1--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 8 && m_patternVar2 < 8) {
                m_patternVar2++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kAir21436C:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
        }
        if (frame == 1 && timer == 0) {
            m_patternVar2 = (int)(vx * 100.0);
            vx = 0.0;
            m_patternVar3 = (int)(vy * 100.0);
            vy = 0.0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
            m_playSound = 0x25;
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame != 1) {
            vy = vy + ay;
        }
        if (frame < 8 && vy > 0.2) {
            vy = 0.2;
        }
        if (frame == 2 && timer == 0) {
            vx = m_patternVar2 * 0.01;
            vy = m_patternVar3 * 0.01;
            m_patternVar1 = 0;
            m_patternVar2 = 0;
            m_patternVar3 = 0;
        }
        if (frame > 4 && frame < 8 && m_patternVar1 <= 0 && m_patternVar3 < 0x32) {
            l50.keep = 0;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 0x1e - facing * 0x30 * ((WORD)Random(0, 2) == 0));
            l50.y = (double)((int)y + -0x20 + (WORD)Random(0, 5));
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.facing = facing;
            l50.scale = 2;
            SpawnObject(&l50);
            m_patternVar1 = 6;
            m_patternVar3++;
        }
        if (frame == 8 && timer == 0) {
            ay = 0.035;
        }
        if (frame > 7 && y + vy > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        m_patternVar1--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 8 && m_patternVar2 < 0xd) {
                m_patternVar2++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k21436A:
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
        }
        if (frame > 4 && frame < 8 && m_patternVar1 <= 0 && m_patternVar3 < 0xf) {
            l50.keep = 0;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 0x11 - facing * 0x30 * ((WORD)Random(0, 2) == 0));
            l50.y = (double)((int)y - 0x16);
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.facing = facing;
            l50.scale = 2;
            SpawnObject(&l50);
            m_patternVar1 = 6;
            m_patternVar3++;
        }
        m_patternVar1--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 8 && m_patternVar2 < 5) {
                m_patternVar2++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436B:
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
        }
        if (frame > 4 && frame < 8 && m_patternVar1 <= 0 && m_patternVar3 < 0x1b) {
            l50.keep = 0;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 0x11 - facing * 0x30 * ((WORD)Random(0, 2) == 0));
            l50.y = (double)((int)y - 0x16);
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.facing = facing;
            l50.scale = 2;
            SpawnObject(&l50);
            m_patternVar1 = 6;
            m_patternVar3++;
        }
        m_patternVar1--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 8 && m_patternVar2 < 8) {
                m_patternVar2++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k21436C:
        if (frame == 1 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
            m_playSound = 0x25;
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame > 4 && frame < 8 && m_patternVar1 <= 0 && m_patternVar3 < 0x32) {
            l50.keep = 0;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 0x11 - facing * 0x30 * ((WORD)Random(0, 2) == 0));
            l50.y = (double)((int)y - 0x16);
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.facing = facing;
            l50.scale = 2;
            SpawnObject(&l50);
            m_patternVar1 = 6;
            m_patternVar3++;
        }
        m_patternVar1--;
        if (0) {}
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 8 && m_patternVar2 < 0xd) {
                m_patternVar2++;
                frame = frame - 4;
            }
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
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 0;
            l50.keep = 1;
            l50.layer = 1;
            l50.facing = -facing;
            l50.movesInFreeze = 1;
            SpawnObject(&l50);
        }
        if (frame > 2) {
            m_game->FlashNegative(3);
            FillBackground(0xb0, 6);
        }
        if (frame == 4 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x1c);
            l50.y = (double)((int)y - 0x33);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0xb && timer == 0) {
            l50.keep = 1;
            l50.type = 0x1b8;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x34);
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
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
    case kLv4Connected:
        m_hideOffscreenMarker = 3;
        if (frame < 2) {
            FillBackground(0xb0, 3);
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 2;
        }
        if (frame == 1 && timer == 0) {
            x = (*m_opponent)->x;
            vy = -6.5;
        }
        if (frame == 1 && m_attackResult == 3) {
            ShakeScreen(5, 0);
            (*m_opponent)->x = facing + x;
            StopMoving();
            timer = 0;
            frame = 2;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->pattern = kThrownHidden;
            l50.keep = 1;
            l50.type = 0x1bd;
            l50.x = (*m_opponent)->x;
            l50.y = (*m_opponent)->y;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 0;
            SpawnObject(&l50);
        }
        if (frame == 2) {
            m_patternVar1--;
            m_patternVar2++;
            if (m_patternVar1 <= 0) {
                m_patternVar1 = 0x18;
                y--;
                (*m_opponent)->y--;
            }
            if (m_patternVar2 == 0x168) {
                timer = 0;
                frame = 3;
                m_attackResult = 0;
                vy = -3.5;
            }
        }
        if (frame == 3 && vy > 0.0) {
            timer = 0;
            frame = 4;
            m_game->SetGameSpeed(3);
        }
        if (frame >= 3) {
            (*m_opponent)->FocusCameraY(0x32, 3);
            if ((*m_opponent)->pattern == kLyingDown) {
                (*m_opponent)->timer = 0;
            }
            vy += 0.035;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
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
    }
}
