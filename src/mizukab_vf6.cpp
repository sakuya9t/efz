// CMizukaB::UpdatePattern (0x4c04b0-0x4d284f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMizukaB's
// .rdata, which starts with its constructor's folder name (mizukab.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMizukaB::UpdatePattern()
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        vx = 0.8;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 2;
            }
        }
        break;
    case kWalkBack:
        m_dashMomentum = 0;
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.043;
            vy = -3.0;
            if (m_dashMomentum == 1) {
                vx = 0.4;
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
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.043;
            vy = -3.0;
            vx = 1.0;
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
                frame = frame - 2;
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
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            if (m_dashMomentum == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.043;
            vy = -3.0;
            vx = -1.0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        vy = vy + ay;
        m_dashMomentum = 0;
        if (ay == 0.0) {
            ay = 0.035;
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
        m_drawMode = 0;
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
        ay = 0.043;
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
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
        ay = 0.043;
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 1.0;
            m_dashMomentum = 0;
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
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpBack:
        ay = 0.043;
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = -1.0;
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
    case 0x14:
        m_drawMode = 0;
        vy = vy + ay;
        m_dashMomentum = 0;
        if (ay == 0.0) {
            ay = 0.035;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        if (m_rfBlue != 0) {
            m_rfGauge -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = m_hitVx;
        vy = m_hitVy;
        if (vx * vx < vy * vy && frame == 0) {
            frame = 1;
        }
        timer++;
        if ((char)AtScreenEdge() != 0) {
            pattern = kHitWallBounce;
            StartPattern();
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                frame = 0;
            }
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
        m_drawMode = 0;
        if (m_rfBlue != 0) {
            m_rfGauge -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = m_hitVx;
        vy = m_hitVy;
        if (vx * vx < vy * vy && frame == 0) {
            frame = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                frame = 0;
            }
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
                if (m_command == kCmd22D && m_gauge >= 0x3e8) {
                    pattern = kWakeUpAttack;
                }
                StartPattern();
            }
        }
        break;
    case kKnockdownHittable:
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
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
            if (m_flying > 0) {
                pattern = 0xb3;
            }
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
            if (m_flying > 0) {
                pattern = 0xb3;
            }
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
        if (frame == 3 && timer == 0) {
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
            if (frame == 0x12) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 9) {
            m_patternVar2++;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.5;
        }
        if (frame == 5 && timer == 0) {
            m_drawMode = 1;
        }
        if (frame == 6 && timer == 0) {
            m_drawMode = 3;
        }
        m_dashMomentum = 1;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 8;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x2a) {
            pattern = kDashStop;
            m_drawMode = 1;
            StartPattern();
        }
        if (m_inputX != facing && m_patternVar2 >= 0x18) {
            pattern = kDashStop;
            m_drawMode = 1;
            StartPattern();
        }
        break;
    case kDashBack:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        m_dashMomentum = 0;
        if (frame == 3 && timer == 0 && m_patternVar1 == 0) {
            vx = -2.5;
            vy = -1.3;
        }
        if (y < 0.0) {
            vy += 0.045;
        }
        if (vy + y > 0.0 && frame < 0xc) {
            StopMoving();
            timer = 0;
            frame = 0xc;
            y = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                m_drawMode = 1;
            }
            if (frame == 5) {
                m_drawMode = 3;
            }
            if (frame == 7) {
                m_drawMode = 1;
            }
            if (frame == 8) {
                m_drawMode = 0;
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStandUp;
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
        if (m_inputX != facing && m_patternVar1 >= 0x30) {
            pattern = kFall;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (m_flying > 0) {
                pattern = 0xb3;
                frame = 7;
            }
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
            if (m_flying > 0) {
                pattern = 0xb3;
                frame = 7;
            }
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kInstantCharge:
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            if (m_rfBlue == 1) {
                m_proration = 5.0 * m_rfGauge + m_proration;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
            m_flying = 0;
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
                if (m_flying > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
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
                m_proration = 5.0 * m_rfGauge + m_proration;
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
                if (m_flying > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
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
            if (frame == 1) {
                m_drawMode = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                break;
            }
        }
        break;
    case 0xb3:
        m_airDashes = 0;
        if ((*m_opponent)->m_hp <= 0) {
            m_flying = 0;
        }
        if (frame == 0 && timer == 0) {
            m_airActions = 1;
            m_flying = 1;
            vy = -2.0;
            vx = 0.0;
        }
        if (frame < 7) {
            vy += 0.035;
            if (vy > 0.0) {
                vy = 0.0;
            }
            if (y < -360.0) {
                vy = 0.0;
            }
        }
        FaceOpponent();
        if (frame > 6) {
            if (m_flying <= 0) {
                ay = 0.035;
                StartPattern();
                pattern = kFall;
                break;
            }
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -1.0;
            }
            if (y < -360.0) {
                vy = 0.0;
            }
            if (m_inputY == 1) {
                vy = 1.0;
            }
            if (m_inputX == facing) {
                StartPattern();
                pattern = 0xb4;
                break;
            }
            if (m_inputX == -facing) {
                StartPattern();
                pattern = 0xb5;
                break;
            }
            if (m_pressD == 1) {
                m_flying = 0;
            }
        }
        m_drawMode = 0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case 0xb4:
        m_airDashes = 0;
        if ((*m_opponent)->m_hp <= 0) {
            m_flying = 0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.5;
        }
        m_drawMode = 0;
        if (m_flying <= 0) {
            ay = 0.035;
            StartPattern();
            pattern = kFall;
            break;
        }
        if (m_inputY == 0) {
            vy = 0.0;
        }
        if (m_inputY == -1) {
            vy = -1.0;
        }
        if (y < -360.0) {
            vy = 0.0;
        }
        if (m_inputY == 1) {
            vy = 1.0;
        }
        if (m_inputX == 0) {
            StartPattern();
            frame = 7;
            pattern = 0xb3;
            break;
        }
        if (m_inputX == -facing) {
            StartPattern();
            pattern = 0xb5;
            break;
        }
        if (m_pressD == 1) {
            m_flying = 0;
        }
        if (m_flying <= 0) {
            ay = 0.035;
            StartPattern();
            pattern = kFall;
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
    case 0xb5:
        m_airDashes = 0;
        if ((*m_opponent)->m_hp <= 0) {
            m_flying = 0;
        }
        if (frame == 0 && timer == 0) {
            vx = -1.5;
        }
        m_drawMode = 0;
        if (m_flying <= 0) {
            ay = 0.035;
            StartPattern();
            pattern = kFall;
            break;
        }
        if (m_inputY == -1) {
            vy = -1.0;
        }
        if (y < -360.0) {
            vy = 0.0;
        }
        if (m_inputY == 1) {
            vy = 1.0;
        }
        if (m_inputY == 0) {
            vy = 0.0;
        }
        if (m_inputX == 0) {
            StartPattern();
            frame = 7;
            pattern = 0xb3;
            break;
        }
        if (m_inputX == facing) {
            StartPattern();
            pattern = 0xb4;
            break;
        }
        if (m_pressD == 1) {
            m_flying = 0;
        }
        if (m_flying <= 0) {
            ay = 0.035;
            StartPattern();
            pattern = kFall;
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
    case 0xb6:
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
        m_drawMode = 0;
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
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                l50.type = 0x1b9;
                l50.x = (double)((int)x - facing * 0x28);
                l50.y = (double)((int)y - 0x21);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k5BClose:
        m_drawMode = 0;
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
            l50.type = 0x190;
            l50.x = (double)((int)x - facing * 0x15);
            l50.y = (double)((int)y - 0x1f);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
        m_drawMode = 0;
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            l50.type = 0x191;
            l50.x = (double)((int)x - facing * 0x24);
            l50.y = (double)((int)y - 0x35);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case k5C:
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 3) {
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
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playVoice = 0xa;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
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
    case k2A:
        m_drawMode = 0;
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
            l50.type = 0x1ba;
            l50.x = (double)((int)x - facing * 0x28);
            l50.y = (double)((int)y - 0xa);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case k2B:
        m_drawMode = 0;
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
            l50.type = 0x192;
            l50.x = (double)((int)x - facing * 0x1a);
            l50.y = (double)((int)y - 0x10);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case k2C:
        m_drawMode = 0;
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 3) {
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
        if (frame == 3 && timer == 0 && m_patternVar1 == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            vx = 2.5;
            m_patternVar1++;
        }
        if (vx > 0.0) {
            vx -= 0.036;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && vx > 0.6) {
                frame = 2;
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
        m_drawMode = 0;
        if (m_flying == 0) {
            vy = vy + ay;
        }
        if (m_flying > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
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
            l50.type = 0x1bb;
            l50.x = (double)((int)x - facing * 7);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            m_flying = 0;
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
                if (m_flying > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case kJumpB:
        m_drawMode = 0;
        if (m_flying == 0) {
            vy = vy + ay;
        }
        if (m_flying > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
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
            m_hitsLeft = 2;
            l50.type = 0x194;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x48);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            m_flying = 0;
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
                if (m_flying > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case kJumpC:
        m_drawMode = 0;
        if (m_flying == 0) {
            vy = vy + ay;
        }
        if (m_flying > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 3;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            m_flying = 0;
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
            if (frame == 5) {
                l50.type = 0x195;
                l50.x = (double)((int)x + facing * 4);
                l50.y = (double)((int)y + 5);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame == 8 && m_patternVar1 < 2) {
                frame = frame - 3;
                m_patternVar1++;
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
                if (m_flying > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case kJump6C:
        m_drawMode = 0;
        if (m_flying == 0) {
            vy = vy + ay;
        }
        if (m_flying > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
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
        if (frame == 7 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            m_flying = 0;
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
            if (frame == 5) {
                l50.type = 0x1cc;
                l50.x = (double)((int)x + facing * 0x37);
                l50.y = (double)((int)y - 0x2c);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
                if (m_flying > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case kUnusedD3:
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
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = kUnusedAirDiveRebound;
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
            pattern = kUnusedAirDiveLanding;
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
    case kUnusedAirDiveRebound:
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
    case kUnusedAirDiveLanding:
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
        m_drawMode = 0;
        m_dashMomentum = 0;
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
            pattern = kThrowHit;
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
    case kThrowHit:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -2.5;
            (*m_opponent)->pattern = kHitAir;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1c8;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x50);
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c9;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1ca;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x50);
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 3) {
            FaceOpponent();
        }
        if ((*m_opponent)->pattern == kHitAirWallBounce && frame == 3) {
            timer = 0;
            frame++;
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
    case kDashA:
        StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                l50.type = 0x1b9;
                l50.x = (double)((int)x - facing * 0x28);
                l50.y = (double)((int)y - 0x21);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
            }
            if (frame >= x8) {
                m_drawMode = 0;
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
            vx = 2.0;
            vy = 0.0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x190;
            l50.x = (double)((int)x - facing * 0x15);
            l50.y = (double)((int)y - 0x1f);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kDashC:
        StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 5 && timer == 0) {
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playVoice = 0xa;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kDash2A:
        StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
            l50.type = 0x1ba;
            l50.x = (double)((int)x - facing * 0x28);
            l50.y = (double)((int)y - 0xa);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
            }
            if (frame >= x8) {
                m_drawMode = 0;
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kDash2B:
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
            vx = 2.0;
            vy = 0.0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            l50.type = 0x192;
            l50.x = (double)((int)x - facing * 0x1a);
            l50.y = (double)((int)y - 0x10);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
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
        if (frame == 0 && timer == 0) {
            vx = 1.5;
            vy = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 3) {
            frame = 0;
            timer = 0;
            pattern = kLand;
            break;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 3;
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (frame == 2) {
                vy = -1.3;
                vx = 1.0;
                ay = 0.02;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
            }
            if (frame >= x8) {
                frame = frame - 2;
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
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownAirRising;
            (*m_opponent)->y = y;
            (*m_opponent)->x = facing * 0x14 + x;
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
                pattern = kJump6C;
                frame = 2;
            }
        }
        break;
    case kAirThrowHit:
        m_dashMomentum = 0;
        if (frame >= 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                StartPattern();
                StopMoving();
                y = 0.0;
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->y = y - 1.0;
                (*m_opponent)->x = facing * 0x1d + x;
            }
            if (frame == 4) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirHigh;
                (*m_opponent)->m_hitVx = 3.0;
                (*m_opponent)->m_hitVy = -1.0;
                (*m_opponent)->ay = 0.035;
                DealDamage(0x3e8, 500.0);
                m_comboHits--;
                m_shownHits--;
                (*m_opponent)->m_noAirRecovery = 1;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k236A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1a1;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
        }
        if (frame == 0xa && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x12) {
                StartPattern();
                pattern = kStand;
            }
            if (frame == 0xb) {
                frame = 0x12;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x5f);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
        }
        if (frame == 0xa && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x12) {
                StartPattern();
                pattern = kStand;
            }
            if (frame == 0xb) {
                frame = 0x12;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
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
            m_homingOrbHit = 0;
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
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
    case k214A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = 0.0;
            l50.scale = 0;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case k214B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0xa0);
            l50.y = 0.0;
            l50.scale = 0;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case k214C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
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
        if (frame == 6 && timer == 0) {
            l50.type = 0x198;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case k41236A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x1bd;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x3a);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1bf;
            l50.x = (double)((int)x + facing * 0x12);
            l50.y = (double)((int)y - 0x26);
            SpawnObject(&l50);
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x12);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 9 && timer == 0) {
                l50.type = 0x1bc;
                l50.x = (double)((int)x + facing * 0x1f);
                l50.y = (double)((int)y - 0x33);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                l50.type = 0x1bf;
                l50.x = (double)((int)x + facing * 0x1a);
                l50.y = (double)((int)y - 0x1f);
                SpawnObject(&l50);
                l50.type = 0x1be;
                l50.x = (double)((int)x + facing * 0x15);
                l50.y = (double)((int)y - 0xb);
                SpawnObject(&l50);
                m_playVoice = 3;
                m_gauge = m_gauge + 0xf;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k41236B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x1c3;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x47);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x3d);
            SpawnObject(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x33);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 9 && timer == 0) {
                l50.type = 0x1bc;
                l50.x = (double)((int)x + facing * 0x1f);
                l50.y = (double)((int)y - 0x33);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                l50.type = 0x1bf;
                l50.x = (double)((int)x + facing * 0x1a);
                l50.y = (double)((int)y - 0x1f);
                SpawnObject(&l50);
                l50.type = 0x1be;
                l50.x = (double)((int)x + facing * 0x15);
                l50.y = (double)((int)y - 0xb);
                SpawnObject(&l50);
                m_playVoice = 3;
                m_gauge = m_gauge + 0xf;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k41236C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x1c3;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x47);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x3d);
            SpawnObject(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x33);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 9 && timer == 0) {
                l50.type = 0x1c3;
                l50.x = (double)((int)x + facing * 6);
                l50.y = (double)((int)y - 0x47);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                l50.type = 0x1c2;
                l50.x = (double)((int)x + (facing << 4));
                l50.y = (double)((int)y - 0x3d);
                SpawnObject(&l50);
                l50.type = 0x1c0;
                l50.x = (double)((int)x + facing * 0x1a);
                l50.y = (double)((int)y - 0x33);
                SpawnObject(&l50);
                m_playVoice = 3;
                m_gauge = m_gauge + 0xf;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k623A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 4 && timer == 0) {
                l50.type = 0x1b5;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x2d;
            }
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
                if (m_patternVar1 > 1) {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 4 && timer == 0) {
                l50.type = 0x1b5;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x2d;
            }
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
                if (m_patternVar1 > 1) {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
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
            m_hitsLeft = 3;
        }
        if (frame == 5 && timer == 0 && m_patternVar1 < 2) {
            l50.type = 0x1b5;
            l50.x = (double)((int)x + -0x23 + (WORD)Random(0, 0x46));
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame == 4 && m_patternVar1 < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir236A:
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1a1;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
        }
        if (frame == 8 && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xb) {
                StartPattern();
                pattern = 0x14;
                break;
            }
            if (frame >= x8) {
                pattern = 0x14;
                StartPattern();
                if (m_flying > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case kAir236B:
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x5f);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
        }
        if (frame == 8 && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xb) {
                StartPattern();
                pattern = 0x14;
                break;
            }
            if (frame >= x8) {
                pattern = 0x14;
                StartPattern();
                if (m_flying > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case kAir236C:
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            vx = 0.0;
            vy = 0.0;
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
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)((int)y - 0x26);
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
            m_playVoice = 0xb;
            m_gauge = m_gauge + 0x1e;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0x14;
                ay = 0.035;
                StartPattern();
                if (m_flying > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case kUnusedAir214:
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1cb;
            l50.x = (double)((int)x + facing * 0x26);
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.layer = 1;
            l50.keep = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
                if (m_flying > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case k421A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 8 && timer == 0) {
            m_drawMode = 2;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 0xe;
        }
        if (frame == 0xf && timer == 0) {
            vx = 13.0;
        }
        if (frame == 0x10 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 0x17 && timer == 0) {
            m_drawMode = 0;
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
    case k421B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 8 && timer == 0) {
            m_drawMode = 2;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 0xe;
        }
        if (frame == 0xf && timer == 0) {
            vx = -13.0;
        }
        if (frame == 0x10 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 0x17 && timer == 0) {
            m_drawMode = 0;
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
    case k421C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 8 && timer == 0) {
            m_drawMode = 2;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 0xe;
        }
        if (frame == 0x10 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 0x17 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                x = (*m_opponent)->x - facing * 0xa;
                y = -130.0;
            }
            if (frame >= x8) {
                pattern = kFall;
                ay = 0.035;
                StartPattern();
            }
        }
        break;
    case kAir421A:
        m_drawMode = 0;
        m_airDashes = 1;
        m_airActions = 1;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 8 && timer == 0) {
            m_drawMode = 2;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 0xe;
        }
        if (frame == 0xf && timer == 0) {
            vx = 13.0;
        }
        if (frame == 0x10 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 0x17 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
                if (m_flying > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case kAir421B:
        m_drawMode = 0;
        m_airDashes = 1;
        m_airActions = 1;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 8 && timer == 0) {
            m_drawMode = 2;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 0xe;
        }
        if (frame == 0xf && timer == 0) {
            vx = -13.0;
        }
        if (frame == 0x10 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 0x17 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = kFall;
                StartPattern();
                if (m_flying > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case kAir421C:
        m_drawMode = 0;
        m_airDashes = 1;
        m_airActions = 1;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 8 && timer == 0) {
            m_drawMode = 2;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 0xe;
        }
        if (frame == 0x10 && timer == 0) {
            vx = 0.0;
            m_flying = 0;
        }
        if (frame == 0x17 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                x = (*m_opponent)->x - facing * 0x3c;
                y = 0.0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 5 && timer == 0 && m_patternVar2 == 0) {
            l50.keep = 1;
            l50.type = 0x1cd;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.keep = 1;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            m_playVoice = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 0xa) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 5 && timer == 0 && m_patternVar2 == 0) {
            l50.keep = 1;
            l50.type = 0x1ce;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.keep = 1;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            m_playVoice = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 0xa) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnused12e:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 5 && timer == 0 && m_patternVar2 == 0) {
            l50.keep = 1;
            l50.type = 0x1cf;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.keep = 1;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
            m_playVoice = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 0xa) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k463214A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
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
            FocusCameraY(0x32, 0x2d);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b8;
            l50.shadow = 1;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = -480.0;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame > 7 && m_catchState == 1) {
            m_game->FlashWhite(9, 0x50, 9);
            StartPattern();
            pattern = k463214AHit;
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
    case k463214B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
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
            FocusCameraY(0x32, 0x2d);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b8;
            l50.shadow = 1;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = -480.0;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame > 7 && m_catchState == 1) {
            m_game->FlashWhite(9, 0x50, 9);
            StartPattern();
            pattern = k463214BHit;
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
    case k463214C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
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
            FocusCameraY(0x32, 0x2d);
            m_playSound = 0x25;
        }
        if (frame > 6) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b8;
            l50.shadow = 1;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = -480.0;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame > 7 && m_catchState == 1) {
            m_game->FlashWhite(9, 0x50, 9);
            StartPattern();
            pattern = k463214CHit;
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
    case k463214AHit:
        FocusCameraY(0x32, 0xf);
        if (frame == 1 && timer == 0) {
            m_catchState = 2;
            x = 230.0;
            facing = 1;
            (*m_opponent)->pattern = kHeadOnly;
            (*m_opponent)->facing = 1;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->x = 420.0;
            (*m_opponent)->y = -17.0;
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0xa && timer == 0) {
            m_playVoice = 3;
            l50.type = 0x1c6;
            l50.scale = 0;
            l50.x = x + 20.0;
            l50.y = -50.0;
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
            if (frame == 0x11 && (m_catchState == 2 || m_catchState == 4 || m_patternVar2 > 0)) {
                frame = frame - 3;
                m_patternVar2--;
            }
            if (frame == 0x11 && m_catchState == 5) {
                frame = 0x15;
            }
            if (frame >= x8) {
                pattern = kStand;
                m_catchState = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k463214BHit:
        FocusCameraY(0x32, 0xf);
        if (frame == 1 && timer == 0) {
            m_catchState = 2;
            x = 230.0;
            facing = 1;
            (*m_opponent)->pattern = kHeadOnly;
            (*m_opponent)->facing = 1;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->x = 420.0;
            (*m_opponent)->y = -17.0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b7;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = 0.0;
            l50.scale = 0;
            l50.keep = 1;
            l50.shadow = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0x10 && timer == 0) {
            m_playVoice = 3;
            l50.type = 0x1c6;
            if (m_patternVar1 == 1) {
                l50.type = 0x1c7;
            }
            if (m_patternVar1 == 2) {
                l50.type = 0x1c5;
            }
            l50.scale = 0;
            l50.x = x + 20.0;
            l50.y = -50.0;
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
            if (frame == 0xa) {
                frame = 0x10;
            }
            if (frame == 0xd) {
                frame = 0x10;
            }
            if (frame == 7) {
                if (m_patternVar1 == 1) {
                    frame = 0xa;
                }
                if (m_patternVar1 == 2) {
                    frame = 0xd;
                }
            }
            if (frame == 0x17 && (m_catchState == 2 || m_catchState == 4 || m_patternVar2 > 0)) {
                frame = frame - 3;
                m_patternVar2--;
            }
            if (frame == 0x1e) {
                frame = 2;
                m_catchState = 2;
                m_patternVar1++;
            }
            if (frame == 0x1b && m_patternVar1 == 1) {
                frame = 0x1e;
            }
            if (frame == 0x17 && m_catchState == 5) {
                frame = 0x1e;
            }
            if (frame >= x8) {
                pattern = kStand;
                m_catchState = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k463214CHit:
        FocusCameraY(0x32, 0xf);
        m_game->FlashNegative(0xf);
        if (frame == 1 && timer == 0) {
            m_catchState = 2;
            x = 230.0;
            facing = 1;
            (*m_opponent)->pattern = kHeadOnly;
            (*m_opponent)->facing = 1;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->x = 420.0;
            (*m_opponent)->y = -17.0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b7;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = 0.0;
            l50.scale = 0;
            l50.keep = 1;
            l50.shadow = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0x10 && timer == 0) {
            m_playVoice = 3;
            l50.type = 0x1c6;
            if (m_patternVar1 == 1) {
                l50.type = 0x1c7;
            }
            if (m_patternVar1 == 2) {
                l50.type = 0x1c5;
            }
            l50.scale = 0;
            l50.x = x + 20.0;
            l50.y = -50.0;
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
            if (frame == 0xa) {
                frame = 0x10;
            }
            if (frame == 0xd) {
                frame = 0x10;
            }
            if (frame == 7) {
                if (m_patternVar1 == 1) {
                    frame = 0xa;
                }
                if (m_patternVar1 == 2) {
                    frame = 0xd;
                }
            }
            if (frame == 0x17 && (m_catchState == 2 || m_catchState == 4 || m_patternVar2 > 0)) {
                frame = frame - 3;
                m_patternVar2--;
            }
            if (frame == 0x1e) {
                frame = 2;
                m_catchState = 2;
                m_patternVar1++;
            }
            if (frame == 0x1b && m_patternVar1 == 2) {
                frame = 0x1e;
            }
            if (frame == 0x17 && m_catchState == 5) {
                frame = 0x1e;
            }
            if (frame >= x8) {
                pattern = kStand;
                m_catchState = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnused135:
        StartAfterimages(2);
        if (frame < 6) {
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xe && (*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->StartPattern();
        }
        if (frame > 8) {
            if (vy + y > 0.0 && frame < 0xe) {
                y = 0.0;
                frame = 0xe;
                timer = 0;
                StopMoving();
                ShakeScreen(0xf, 0xa);
                m_playSound = 0x16;
                DealDamage(0x320, 900.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kKnockdown;
                l50.type = 0x190;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                l50.type = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->m_hitstop = 0xb4;
                break;
            }
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -98.0;
                (*m_opponent)->x = facing * 0x23 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -98.0;
                (*m_opponent)->x = facing * 0x21 + x;
                if (m_patternVar1 > 0) {
                    timer = 0x96;
                }
            }
            if (frame == 3) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x21 + x;
                (*m_opponent)->facing = -facing;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kKnockdownHittable;
                (*m_opponent)->m_landHittable = 1;
                DealDamage(0x12c, 980.0);
                if ((*m_opponent)->m_hp <= 0) {
                    (*m_opponent)->m_hp = 1;
                }
            }
            if (frame == 6 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = 0;
            }
            if (frame == 9) {
                vy = -7.0;
                vx = 0.3;
                ay = 0.15;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnused136:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->StartPattern();
        }
        if (frame == 1 && timer == 0) {
            StopMoving();
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
            FocusCameraY(0x32, 0x2d);
        }
        if (frame < 7) {
            FocusCameraY(0x32, 0x2d);
            (*m_opponent)->m_hitstop = 3;
        }
        if (frame == 7) {
            FocusCameraY(0, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 || frame == 6) {
                l50.type = 0;
                l50.sound = 2;
                l50.x = (double)((int)x + facing * 0x1d);
                l50.y = (double)((int)y - 0x53);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -101.0;
                (*m_opponent)->x = facing * 0x15 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
                m_playSound = 0x16;
                l50.type = 0x193;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0xfa);
                l50.scale = 2;
                l50.keep = 1;
                l50.facing = facing;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame == 3) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 7 && m_patternVar1 > 0xa) {
                (*m_opponent)->pattern = kHitAirCarry;
                (*m_opponent)->m_hitVx = 0.0;
                (*m_opponent)->m_hitVy = -5.0;
                (*m_opponent)->ay = 0.035;
                DealDamage(0xdac, 700.0);
                (*m_opponent)->m_untechTime = 0xb4;
            }
            if (frame == 7 && m_patternVar1 < 0xb) {
                m_patternVar1++;
                frame = 2;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kUnused137:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->StartPattern();
        }
        if (frame < 7) {
            FocusCameraY(0x32, 0x2d);
            (*m_opponent)->m_hitstop = 3;
        }
        if (frame == 7) {
            FocusCameraY(0, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 || frame == 6) {
                l50.type = 0;
                l50.sound = 2;
                l50.x = (double)((int)x + facing * 0x1d);
                l50.y = (double)((int)y - 0x53);
                l50.scale = 2;
                l50.keep = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -101.0;
                (*m_opponent)->x = facing * 0x15 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
                m_playSound = 0x16;
                l50.type = 0x193;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0xfa);
                l50.scale = 2;
                l50.keep = 1;
                l50.facing = facing;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame == 3) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 7 && m_patternVar1 > 8) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = 0.2;
                (*m_opponent)->m_hitVy = -1.9;
                DealDamage(0x3e8, 1000.0);
                m_hitsLeft = 1;
            }
            if (frame == 7 && m_patternVar1 < 9) {
                m_patternVar1++;
                frame = 2;
            }
            if (frame == 0x10) {
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y + 4);
                l50.scale = 0;
                l50.keep = 1;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.keep = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                ShakeScreen(0xa, 0x3c);
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kUnused138:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 2;
        }
        if (frame == 6 && timer == 0) {
            FocusCameraY(0x32, 0x2d);
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
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.facing = facing;
            l50.keep = 1;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.scale = 0;
            l50.keep = 1;
            l50.facing = facing;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.facing = facing;
            l50.keep = 1;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 2 && m_attackResult == 3) {
            ShakeScreen(6, 0x3c);
            (*m_opponent)->m_hitstop = 0x1f4;
        }
        if (frame == 0xa && timer == 0) {
            ShakeScreen(0xa, 0x3c);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_attackResult != 3 && frame == 6) {
                frame = 0xc;
            }
            if (frame == 9 || frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnused139:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_hitsLeft = 1;
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0xa);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 3) {
            m_game->FlashNegative(0xf);
        }
        if (frame > 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame > 0x15 && frame < 0x19) {
            m_hp += 0xa;
            if (m_hp > 0x270f) {
                m_hp = 0x270f;
            }
            m_hitsLeft = 0;
            vy = -0.08;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                if (m_hp < 0x270f) {
                    frame = frame - 3;
                } else {
                    pattern = 0x14;
                    ay = 0.035;
                    FaceOpponent();
                    StartPattern();
                }
            }
        }
        break;
    case kLv4:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0x18);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_patternVar1++;
            m_playSound = 0x25;
            m_hitsLeft = 1;
        }
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame > 0) {
            FocusCameraY(0x32, 3);
        }
        if (frame > 2 && frame < 8) {
            vy = vy + ay;
            if (frame == 7 && vy + y > 0.0) {
                timer = 0;
                frame = 9;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        if (frame == 0xc && timer == 0 && m_attackResult == 3) {
            m_game->FlashWhite(9, 0xf, 9);
        }
        if (frame == 0xd && timer == 0 && m_attackResult == 3) {
            StartPattern();
            pattern = kLv4Hit;
            break;
        }
        if (frame > 0xb && m_attackResult == 3) {
            (*m_opponent)->m_noAirRecovery = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 2.0;
                vy = -2.0;
                ay = 0.08;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4Hit:
        m_hideOffscreenMarker = 3;
        if (frame > 0xb && m_attackResult == 3) {
            (*m_opponent)->m_noAirRecovery = 1;
        }
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 2) {
            FillBackground(0xb0, 3);
        }
        if (frame < 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame < 2) {
            FocusCameraX(0x32, 3);
        }
        if (frame == 0 && timer == 0) {
            x = 320.0;
            StopMoving();
            l50.type = 0x1b2;
            l50.screen = 1;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.facing = 1;
            SpawnObject(&l50);
            l50.type = 0x1a5;
            l50.screen = 0;
            l50.x = 320.0;
            l50.y = 200.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            (*m_opponent)->x = 320.0;
            (*m_opponent)->y = -160.0;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kHitAir;
        }
        if (frame == 0) {
            m_patternVar1++;
            if (m_patternVar1 == 0x50) {
                l50.type = 0x1a6;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0xa0) {
                l50.type = 0x1a7;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0xf0) {
                l50.type = 0x1a8;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0x140) {
                l50.type = 0x1a9;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0x190) {
                l50.type = 0x1aa;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
        }
        if (frame == 0 && timer == l4 - 0x1e) {
            m_game->FlashBlack(9, 0x1e, 9);
            m_patternVar1 = 0;
            (*m_opponent)->x = 320.0;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kThrownHidden;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 1) {
            m_patternVar1++;
            if (m_patternVar2 > 0) {
                frame = 2;
                timer = 0;
                facing = -(*m_opponent)->facing;
                x = m_patternVar2;
                y = m_patternVar3;
                vx = -0.9;
                vy = -1.5;
            }
            if (m_patternVar1 == 0x96) {
                l50.type = 0x1b6;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0xae) {
                l50.type = 0x1ac;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0xc6) {
                l50.type = 0x1ad;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0xde) {
                l50.type = 0x1ae;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0xf6) {
                l50.type = 0x1af;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (m_patternVar1 == 0x10e) {
                l50.type = 0x1b0;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
        }
        if (frame > 1) {
            vy += 0.035;
            if (vy + y > 0.0) {
                StartPattern();
                StopMoving();
                pattern = kLand;
                y = 0.0;
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
        break;
    case kUnused13c:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0 && m_patternVar1 == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.sound = 5;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_patternVar1++;
            m_playSound = 0x25;
        }
        if (frame > 3) {
            m_game->FlashNegative(0xf);
        }
        FocusCameraY(0x32, 3);
        if (frame == 9 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x1c4;
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = 15.0;
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
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kAir236236A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame > 0x13) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = kLand;
                break;
            }
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 4 && frame < 6) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 6 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x1d0;
            l50.movesInFreeze = 1;
            l50.x = (facing << 1) + x;
            l50.y = y - 29.0;
            l50.keep = 1;
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
            if (frame == 0x18) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kAir236236B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame > 0x13) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = kLand;
                break;
            }
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 4 && frame < 6) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 6 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x1d2;
            l50.movesInFreeze = 1;
            l50.x = (facing << 1) + x;
            l50.y = y - 29.0;
            l50.keep = 1;
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
            if (frame == 0x18) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kAir236236C:
        if (frame > 4) {
            m_game->FlashNegative(0xf);
        }
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame > 0x13) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = kLand;
                break;
            }
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            StopMoving();
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 4 && frame < 6) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 6 && timer == 0) {
            l50.keep = 1;
            l50.type = 0x1d5;
            l50.movesInFreeze = 1;
            l50.x = (facing << 1) + x;
            l50.y = y - 29.0;
            l50.keep = 1;
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
            if (frame == 0x18) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
    }
}
