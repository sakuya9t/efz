// CMayu::UpdatePattern (0x5c8580-0x5dddef), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMayu's
// .rdata, which starts with its constructor's folder name (mayu.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMayu::UpdatePattern()
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
        vx = 0.9;
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
        vx = -0.9;
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
            ay = 0.055;
            vy = -2.8;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        if (frame == 3 && timer == 0) {
            ay = 0.055;
            vy = -2.8;
            vx = 1.0;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        if (frame == 3 && timer == 0) {
            ay = 0.055;
            vy = -2.8;
            vx = -1.0;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
    case kSuperJump:
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
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 0.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 1.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = -1.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
            if (m_bounceDebrisOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_bounceDebrisOut = 1;
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
            if (m_bounceDebrisOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_bounceDebrisOut = 1;
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
            if (m_bounceDebrisOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_bounceDebrisOut = 1;
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
            if (m_bounceDebrisOut == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.keep = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_bounceDebrisOut = 1;
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
        if (frame < 9) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vy = -1.8;
                ay = 0.05;
            }
            if (frame == 9) {
                frame = frame - 4;
            }
            if (frame < 9 && frame > 4 && y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                frame = 9;
            }
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
        if (m_hp > 0 && timer > 0x45 && frame == 0) {
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
        if (frame == 3 && timer == 0) {
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
            if (frame == 0xc) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case kDashForward:
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            ay = 0.0;
        }
        vy = vy + ay;
        if (frame == 6) {
            vx -= 0.05;
            if (vx < 0.5) {
                vx = 0.5;
            }
        }
        if (frame == 2 && timer == 0) {
            vx = 2.5;
            vy = -1.6;
            ay = 0.05;
        }
        if (frame == 6 && timer == 0) {
            ay = 0.08;
        }
        if (y + vy > 0.0) {
            pattern = kDashStop;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6) {
                if (m_inputX == -facing) {
                    ay = 0.08;
                    break;
                }
                m_patternVar1++;
                if (m_patternVar1 < 7) {
                    frame = frame - 2;
                    m_patternVar1++;
                }
            }
        }
        break;
    case kDashBack:
        if (frame == 0 && timer == 0) {
            StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
        }
        if (frame > 0) {
            vx += 0.055;
        }
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            StartPattern();
            pattern = kLand;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -3.5;
                vy = -1.5;
                ay = 0.05;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0) {
            vx = 1.8;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            if (m_patternVar1 == 0) {
                m_playSound = 0x11;
            }
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
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0) {
            vx = -1.8;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            if (m_patternVar1 == 0) {
                m_playSound = 0x11;
            }
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
            if (ay == 0.0) {
                ay = 0.035;
            }
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
                if (ay == 0.0) {
                    ay = 0.035;
                }
                StartPattern();
            }
        }
        break;
    case kDashStop:
        vx -= 0.08;
        if (vx < 0.0) {
            vx = 0.0;
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
        if (y + vy > 0.0 && frame < 0xc) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
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
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case k5A:
        vx = 0.0;
        vy = 0.0;
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
        if (frame == 2 && timer == 0) {
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
        vx -= 0.02;
        if (vx <= 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.2;
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
    case k5C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 2;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
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
    case k2A:
        vx = 0.0;
        vy = 0.0;
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
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (vx > 0.0) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 1.5;
            }
            if (frame == 6 && m_patternVar1 < 1) {
                frame = frame - 2;
                m_patternVar1++;
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
    case k2C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            vx = 3.0;
        }
        if (frame > 1) {
            vx -= 0.07;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (vx == 0.0) {
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_playSound = 0x14;
                m_hitsLeft = 1;
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 1) {
            pattern = kAirJump;
            m_airActions++;
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
                StartPattern();
                pattern = kFall;
            }
        }
        break;
    case kJumpB:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 1) {
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
            m_hitsLeft = 1;
            m_playSound = 0x14;
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
    case kJumpC:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 1) {
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
    case k6B:
        if (vx <= 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 5;
                break;
            }
        }
        if (frame > 4) {
            vx -= 0.036;
            if (vx < 0.0) {
                vx = 0.0;
            }
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
            if (frame == 1) {
                vx = 1.0;
                vy = -2.6;
                ay = 0.065;
            }
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
    case k1B:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
    case kThrow:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && m_attackResult == 3) {
            StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = kThrowHold;
            (*m_opponent)->pattern = kThrownStandHigh2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x30);
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
            if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
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
    case kThrowHold:
        if (frame == 0 && timer == 0) {
            x = (*m_opponent)->x - (*m_opponent)->m_pointX[0] * facing;
            y = (*m_opponent)->m_pointY[0] + 0x1e;
        }
        if (frame == 3 && timer == 0) {
            (*m_opponent)->pattern = kHitAir;
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitVx = -2.5;
            (*m_opponent)->m_hitVy = -1.0;
            (*m_opponent)->ay = 0.035;
            vx = -1.8;
            vy = -1.9;
            ay = 0.04;
            l50.type = 0;
            l50.sound = 2;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            DealDamage(0x3e8, 750.0);
        }
        if (frame > 2) {
            vy = vy + ay;
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
    case kDashHopA:
        vy = vy + ay;
        StartAfterimages(3);
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 1) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kDashHopLanding;
            StartPattern();
            frame = 2;
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
                pattern = kSuperJump;
                StartPattern();
            }
        }
        break;
    case kDashHopB:
        vy = vy + ay;
        StartAfterimages(3);
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 1) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            m_hitsLeft = 2;
            m_playSound = 0x14;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kDashHopLanding;
            StartPattern();
            frame = 1;
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
                pattern = kSuperJump;
                StartPattern();
            }
        }
        break;
    case kDashHopC:
        vy = vy + ay;
        StartAfterimages(3);
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult >= 2 && m_airActions < 1) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kDashHopLanding;
            StartPattern();
            frame = 1;
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
                pattern = kSuperJump;
                StartPattern();
            }
        }
        break;
    case kDashHopLanding:
        vx = 0.0;
        vy = 0.0;
        FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 3;
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
    case kAirThrow:
        vy = vy + ay;
        if (frame == 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_noAirRecovery = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = kAirThrowHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
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
    case kAirThrowHold:
        m_hideOffscreenMarker = 2;
        if (frame < 0xb) {
            if (x > 6100.0 && facing == 1) {
                x = 6100.0;
                vx = 0.0;
            }
            if (x < 30.0 && facing == -1) {
                x = 30.0;
                vx = 0.0;
            }
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xa || frame > 0xb && frame < 0xf) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xa) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    DealDamage(0x3e8, 500.0);
                    l50.type = 0;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    timer = 0;
                    frame = 0xa;
                    m_playSound = 2;
                    break;
                }
                if (frame == 0xe) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 0xf;
                    break;
                }
            }
        }
        if (frame < 1) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 2) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 3) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 4) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xa) {
                frame = frame - 8;
            }
            if (frame == 0xc) {
                vx = -0.8;
                vy = -1.0;
                ay = 0.035;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k41236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 0;
        }
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            pattern = k41236Throw;
            y = m_pointY[0] + 0x32;
            x = (*m_opponent)->x + (-m_pointX[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 8) {
            if ((*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
        }
        if (frame == 6) {
            m_patternVar3 = 1;
        }
        if (frame > 7) {
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
            if (frame == 1) {
                m_hitsLeft = 0;
            }
            if (frame == 3) {
                vx = 1.8;
            }
            if (frame == 8) {
                frame = 3;
                m_patternVar1++;
            }
            if (frame == 6 && m_patternVar1 > 1) {
                frame = 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
            }
        }
        break;
    case k41236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 0;
        }
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            pattern = k41236Throw;
            y = m_pointY[0] + 0x32;
            x = (*m_opponent)->x + (-m_pointX[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 8 && m_patternVar3 > 0) {
            if ((*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
        }
        if (frame == 6) {
            m_patternVar3 = 1;
        }
        if (frame > 7) {
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
            if (frame == 1) {
                m_hitsLeft = 0;
            }
            if (frame == 3) {
                vx = 2.4;
            }
            if (frame == 8) {
                frame = 3;
                m_patternVar1++;
            }
            if (frame == 6 && m_patternVar1 > 2) {
                frame = 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
            }
        }
        break;
    case k41236C:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0;
            StopMoving();
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = k41236CThrow;
            y = m_pointY[0] + 0x32;
            x = (*m_opponent)->x + (-m_pointX[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 8) {
            if ((*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
        }
        if (frame == 6) {
            m_patternVar3 = 1;
        }
        if (frame > 7) {
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
            if (frame == 1) {
                m_hitsLeft = 0;
            }
            if (frame == 3) {
                vx = 1.8;
            }
            if (frame == 8) {
                frame = 3;
                m_patternVar1++;
            }
            if (frame == 6 && m_patternVar1 > 1) {
                frame = 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
            }
        }
        break;
    case k41236Throw:
        if (frame < 3) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if ((char)(*m_opponent)->AtScreenEdge() != 0) {
                StopMoving();
                (*m_opponent)->StopMoving();
            }
            if ((char)(*m_opponent)->AtScreenEdge() == 0) {
                (*m_opponent)->x = (m_pointX[0] + 0x14) * facing + x;
            }
        }
        if (frame == 3) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -69.0 + vy + y;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 3 && vy + y > 0.0) {
            StartPattern();
            StopMoving();
            pattern = kCrouch;
            y = 0.0;
            break;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->x = (-31.0 + vx) * facing + x;
            (*m_opponent)->y = -33.0 + vy + y;
            DealDamage(0x1f4, 750.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->m_hitVx = 0.8;
            (*m_opponent)->m_hitVy = -3.2;
        }
        if (frame < 4) {
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 3) {
                vx = -1.0;
                vy = -1.3;
                ay = 0.03;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k41236CThrow:
        if (frame < 3) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if ((char)(*m_opponent)->AtScreenEdge() != 0) {
                StopMoving();
                (*m_opponent)->StopMoving();
            }
            if ((char)(*m_opponent)->AtScreenEdge() == 0) {
                (*m_opponent)->x = (m_pointX[0] + 0x14) * facing + x;
            }
        }
        if (frame == 3) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -69.0 + vy + y;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 3 && vy + y > 0.0) {
            StartPattern();
            StopMoving();
            pattern = kCrouch;
            y = 0.0;
            break;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunchWallBounce;
            (*m_opponent)->x = (-41.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            DealDamage(0x3e8, 800.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->facing = facing;
            (*m_opponent)->m_hitVx = -4.0;
            (*m_opponent)->m_hitVy = -0.8;
        }
        if (frame < 4) {
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = -1.0;
                vy = -2.1;
                ay = 0.025;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedAirSpin:
        if (frame == 0 && timer == 0) {
            vx *= 0.3;
            vy *= 0.5;
            ay = 0.035;
            m_hitsLeft = 9;
        }
        if ((frame == 1 || frame == 3 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
        }
        if (frame > 0xa) {
            vy = vy + ay;
        }
        if (y + vy > 0.0) {
            StartPattern();
            StopMoving();
            pattern = k236JumpLanding;
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = 0;
            }
        }
        if (frame >= x8) {
            frame = frame - 4;
        }
        break;
    case k236Dive:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = 3.0;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            StopMoving();
            pattern = k236DiveLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k236DiveLanding:
        vx -= 0.04;
        if (vx < 0.0) {
            vx = 0.0;
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
    case k236JumpLanding:
        vx -= 0.04;
        if (vx < 0.0) {
            vx = 0.0;
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
    case k236A:
        if (frame > 8 && frame < 0xf && m_holdA > 0) {
            StartPattern();
            pattern = kRisingStrike;
            break;
        }
        if (frame > 8 && frame < 0xf && m_holdB > 0) {
            StartPattern();
            pattern = k236AJump;
            break;
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 7) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 7 && timer == 0) {
            m_hitsLeft = 1;
            vx = 3.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 0xc && m_patternVar1 < 3) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame > 0xd) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_command == kCmd236A && frame > 0xd) {
            StartPattern();
            pattern = kRisingStrike236B;
            break;
        }
        if (y < 0.0 && vy > 0.0 && m_pressA == 1) {
            StartPattern();
            StopMoving();
            pattern = k236Dive;
            break;
        }
        if (vy + y > 0.0 && frame > 5 && frame < 0xa) {
            frame = 0xe;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        if (vy + y > 0.0 && frame > 9 && frame < 0xe) {
            frame = 0xe;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.2;
                vy = -3.3;
                ay = 0.055;
                m_hitsLeft = 1;
            }
            if (frame == 0xa) {
                frame = frame - 4;
            }
            if (frame == 0xe) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            y -= 25.0;
            vx = 3.0;
            m_hitsLeft = 1;
        }
        vy = vy + ay;
        if (frame > 9) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult > 1 && frame > 1 && frame < 6) {
            frame = 6;
            timer = 0;
            vx = -vx * 0.1;
            vy = -1.5;
            ay = 0.036;
            break;
        }
        if (vy + y > 0.0 && frame > 5 && frame < 0xa) {
            frame = 0xa;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                if (m_patternVar1 < 4) {
                    frame = frame - 4;
                    m_patternVar1++;
                } else {
                    frame = 0xa;
                    y = 0.0;
                    break;
                }
            }
            if (frame == 0xa) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kRisingStrike:
        vx -= 0.035;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 4 && frame < 0xf && y + vy > 0.0) {
            timer = 0;
            frame = 0xf;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                vy = -3.3;
                m_hitsLeft = 3;
            }
            if (frame == 0xf) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
            }
        }
        break;
    case k236AJump:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame > 0xa) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y < 0.0 && vy > 0.0 && m_pressA == 1) {
            StartPattern();
            StopMoving();
            pattern = k236Dive;
            break;
        }
        if (vy + y > 0.0 && frame > 2 && frame < 0xa) {
            StartPattern();
            StopMoving();
            y = 0.0;
            pattern = k236JumpLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 0.8;
                vy = -3.1;
                ay = 0.055;
                m_hitsLeft = 1;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case kWallJumpDiveLanding:
        vx -= 0.05;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                StopMoving();
            }
        }
        break;
    case k214BDiveLanding:
        vx -= 0.05;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
                StopMoving();
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame == 7) {
            frame = 8;
            timer = 0;
            y = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                ay = 0.09;
                vy = -3.0;
                vx = 3.0;
            }
            if (frame == 6 && m_patternVar1 < 1) {
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
    case k623B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame == 7) {
            frame = 8;
            timer = 0;
            y = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                ay = 0.11;
                vy = -4.5;
                vx = 4.0;
            }
            if (frame == 6 && m_patternVar1 < 1) {
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
    case k623C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame > 8 && frame < 0xd) {
            frame = 0xd;
            timer = 0;
            y = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                ay = 0.09;
                vy = -4.0;
                vx = 2.0;
            }
            if (frame == 6 && m_patternVar1 < 1) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 0xd) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case kWallJumpA:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = 3.0;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            StopMoving();
            pattern = kWallJumpDiveLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kWallJumpB:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 2.2;
            vy = 2.2;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            StopMoving();
            pattern = kWallJumpDiveLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kWallJumpC:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x28;
            m_hitsLeft = 4;
        }
        if (frame > 9 && frame < 0xe) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                frame = 0xe;
                break;
            }
        }
        if (frame < 7) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vy = 0.0;
                StartPattern();
                m_patternVar1 = (int)(vx * 100.0);
                vx = 0.0;
                frame = 7;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 || frame == 0xe) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 9) {
                vx = m_patternVar1 * 0.005;
                vy = -0.8;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 0x13 && m_command == kCmd236A) {
            StartPattern();
            pattern = kRisingStrike;
            break;
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -2.0;
            vx = -3.0;
        }
        if (frame > 0xf && frame < 0x14) {
            if (m_inputX == facing) {
                vx += 0.015;
            }
            if (m_inputX == -facing) {
                vx -= 0.015;
            }
            if (vx < -2.5) {
                vx = -2.5;
            } else if (vx > 2.5) {
                vx = 2.5;
            }
            if (m_pressA == 1) {
                StartPattern();
                pattern = kWallJumpA;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                pattern = kWallJumpB;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                pattern = kWallJumpC;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x14) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 0x14) {
            y = 0.0;
            StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                vx = 1.5;
                vy = -2.5;
                ay = 0.035;
            }
            if (frame == 0x14) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214D:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -1.5;
            vx = -3.0;
        }
        if (frame == 0x12 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 0x12 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = k214DThrow;
            y = m_pointY[0] + 0x32;
            x = (*m_opponent)->x + (-m_pointX[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x13) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 0xf && frame < 0x13) {
            y = 0.0;
            StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                vx = 2.2;
                vy = -0.5;
                ay = 0.035;
            }
            if (frame == 0x13) {
                frame--;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 0x13 && m_command == kCmd236A) {
            StartPattern();
            pattern = kRisingStrike;
            break;
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -2.0;
            vx = 3.0;
        }
        if (frame > 0xf && frame < 0x14) {
            if (m_inputX == facing) {
                vx += 0.015;
            }
            if (m_inputX == -facing) {
                vx -= 0.015;
            }
            if (vx < -2.5) {
                vx = -2.5;
            } else if (vx > 2.5) {
                vx = 2.5;
            }
            if (m_pressA == 1) {
                StartPattern();
                pattern = kWallJumpA;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                pattern = kWallJumpB;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                pattern = kWallJumpC;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x14) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 0x14) {
            y = 0.0;
            StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            facing = -facing;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                vx = 1.5;
                vy = -2.5;
                ay = 0.035;
            }
            if (frame == 0x14) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214DThrow:
        FocusCameraX(0x32, 3);
        FocusCameraY(0x32, 3);
        if (frame == 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -54.0 + vy + y;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-31.0 + vx) * facing + x;
            (*m_opponent)->y = -62.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-34.0 + vx) * facing + x;
            (*m_opponent)->y = -34.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (-6.0 + vx) * facing + x;
            (*m_opponent)->y = -3.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (-4.0 + vx) * facing + x;
            (*m_opponent)->y = -2.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa && timer == 0) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            DealDamage(0x4b0, 960.0);
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.sound = 2;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0x13 && y + vy > 0.0) {
            StartPattern();
            StopMoving();
            y = 0.0;
            pattern = kLand;
            break;
        }
        if (frame > 0xf) {
            vy = vy + ay;
        }
        if (frame > 0xd && (*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x10) {
                vx = -0.5;
                vy = -1.3;
                ay = 0.05;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case kAir236A:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 0xc;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            vx *= 0.15;
            vy *= 0.15;
            StartPattern();
            pattern = kAir236Hit;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 0.7;
                vy = 2.0;
            }
            if (frame == 6) {
                frame--;
            }
            if (frame == 0xc) {
                frame = frame - 6;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case kAir236B:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 0xc;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            vx *= 0.15;
            vy *= 0.15;
            StartPattern();
            pattern = kAir236Hit;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 2.0;
                vy = 2.0;
            }
            if (frame == 6) {
                frame--;
            }
            if (frame == 0xc) {
                frame = frame - 6;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case kAir236C:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            StopMoving();
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            l50.type = 0x21;
            l50.sound = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_patternVar1++;
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 0xc;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            timer = 0;
            frame = 8;
            m_hitsLeft = 0x63;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 2.0;
                vy = 2.0;
            }
            if (frame == 6) {
                frame--;
            }
            if (frame == 0xc) {
                frame = frame - 6;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k41236D:
        vx = 0.0;
        vy = 0.0;
        if (frame == 2 && m_attackResult == 3) {
            StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = k41236DRide;
            (*m_opponent)->pattern = kThrownStandHigh2;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame == 2) {
                m_gauge = m_gauge + 0x19;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k41236DRide:
        FocusCameraY(-0x32, 3);
        (*m_opponent)->m_hitstop = 3;
        timer++;
        if (frame > 3) {
            vx = 1.0;
            vy += 0.025;
        }
        if (frame > 3 && vy + y > 0.0) {
            StopMoving();
            y = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            pattern = kLand;
            (*m_opponent)->pattern = kHitStandHighHold;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                x = (*m_opponent)->x - (*m_opponent)->m_pointX[0] * facing;
                y = (*m_opponent)->y + (*m_opponent)->m_pointY[0] - 20.0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k214BDiveNear:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = 3.0;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (m_attackResult > 0) {
            StartPattern();
            StopMoving();
            pattern = k214BDiveRebound;
            break;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            StopMoving();
            pattern = k214BDiveLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k214BDiveMid:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 2.2;
            vy = 2.2;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (m_attackResult > 0) {
            StartPattern();
            StopMoving();
            pattern = k214BDiveRebound;
            break;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            StopMoving();
            pattern = k214BDiveLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k214BDiveFar:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 4.0;
            vy = 1.5;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (m_attackResult > 0) {
            StartPattern();
            StopMoving();
            pattern = k214BDiveRebound;
            break;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            StopMoving();
            pattern = k214BDiveLanding;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case k214BDiveRebound:
        if (frame == 0 && timer == 0) {
            vx = -0.4;
            vy = -0.9;
            ay = 0.045;
        }
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 8) {
            timer = 0;
            frame = 8;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -1.5;
            vx = -3.0;
        }
        if (frame == 0x12 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x13) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 0xf && frame < 0x13) {
            y = 0.0;
            StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                StartPattern();
                StopMoving();
                pattern = k214BDiveFar;
                if (x - (*m_opponent)->x < 140.0 && x - (*m_opponent)->x > -140.0) {
                    pattern = k214BDiveMid;
                }
                if (x - (*m_opponent)->x < 70.0 && x - (*m_opponent)->x > -70.0) {
                    pattern = k214BDiveNear;
                }
                break;
            }
            if (frame == 0x13) {
                frame--;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kRisingStrike236B:
        vx -= 0.035;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 4 && frame < 0xf && y + vy > 0.0) {
            timer = 0;
            frame = 0xf;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                vy = -3.3;
                m_hitsLeft = 3;
            }
            if (frame == 0xf) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kCrouch;
            }
        }
        break;
    case kAir236Hit:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            StopMoving();
            m_hitsLeft = 5;
        }
        if (frame > 0xe) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 0x16;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                vx = 0.5;
                vy = 0.0;
                ay = 0.045;
            }
            if (frame == 0x16) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case kUnusedSuperLv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
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
            m_invulTime = 0x7e;
            FocusCameraY(0x32, 0x78);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame == 0x10 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                m_invulTime = 9;
            }
            if (frame == 6) {
                x = facing * 0xf + x;
            }
            if (frame == 7) {
                x = facing * 0xf + x;
            }
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                if (m_patternVar1 > 1) {
                    frame = 0xc;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xc && m_patternVar1 < 1) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kUnusedSuperLv2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
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
            m_invulTime = 0x84;
            FocusCameraY(0x32, 0x78);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame == 0xe && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 0x15 && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame > 0x14 && frame < 0x1c) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0x14 && frame < 0x1c && y + vy > 0.0) {
            frame = 0x1c;
            timer = 0;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                m_invulTime = 0x1e;
            }
            if (frame == 6) {
                x = facing * 0xf + x;
            }
            if (frame == 7) {
                x = facing * 0xf + x;
            }
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                if (m_patternVar1 > 2) {
                    frame = 0xc;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xc && m_patternVar1 < 2) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame == 0x14) {
                ay = 0.06;
                vy = -3.0;
                vx = 2.0;
            }
            if (frame == 0x1c) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kSuperJump;
                StartPattern();
            }
        }
        break;
    case kUnusedSuperLv3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
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
            m_invulTime = 0x84;
            FocusCameraY(0x32, 0x78);
            m_playSound = 0x25;
        }
        if (frame > 1) {
            m_game->FlashNegative(0xf);
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame == 0xe && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 0x12 && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
            vx = 3.0;
        }
        if (frame > 0x12 && frame < 0x17) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0x14 && frame < 0x17 || frame > 0x1c) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 0x18 && timer == 0) {
            vx = 1.8;
            m_hitsLeft = 0x63;
        }
        if (frame == 0x20 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0 || frame < 0x22 && frame > 0x1b) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                m_invulTime = 0x3c;
            }
            if (frame == 6) {
                x = facing * 0xf + x;
            }
            if (frame == 7) {
                x = facing * 0xf + x;
            }
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                if (m_patternVar1 > 3) {
                    frame = 0xc;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xc && m_patternVar1 < 3) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame == 0x1c && m_patternVar1 < 8) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kLv4Grab:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame > 1) {
            m_game->FlashNegative(0xf);
        }
        if (frame >= 0 && frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 6 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = kLv4Slam;
            y = m_pointY[0] + 0x32;
            x = (*m_opponent)->x + (-m_pointX[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)(*m_opponent)->x + m_pointX[0]);
            l50.y = (double)((int)(*m_opponent)->y + m_pointY[0]);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 7) {
            vy = vy + ay;
        }
        if (frame == 6 && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 7;
            break;
        }
        if (frame == 6 && (*m_opponent)->y >= 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 1.5;
                vy = -2.0;
                ay = 0.045;
            }
            if (frame >= x8) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4GrabClose:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        m_game->FlashNegative(0xf);
        if (frame >= 0 && frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 4 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = kLv4GrabCloseHold;
            (*m_opponent)->m_hitstop = 0x78;
            (*m_opponent)->x = facing * 0x1e + x;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 7);
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
            if (frame == 4 && (*m_opponent)->y >= 0.0) {
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
    case kLv4Slam:
        FocusCameraX(0x32, 3);
        FocusCameraY(0x32, 3);
        m_game->FlashNegative(0xf);
        if (frame > 3) {
            vy = vy + ay;
        }
        if (frame == 4) {
            (*m_opponent)->m_koDelay = 0x7530;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -52.0 + vy + y;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-31.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-36.0 + vx) * facing + x;
            (*m_opponent)->y = -32.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (-7.0 + vx) * facing + x;
            (*m_opponent)->y = -8.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 0xa) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (-4.0 + vx) * facing + x;
            (*m_opponent)->y = -6.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame > 8 && vy + y > 0.0) {
            StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            y = 0.0;
            pattern = kLv4Stomps;
            DealDamage(0x3e8, 960.0);
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.sound = 2;
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
            if (frame == 4) {
                vx = (1 - ((x > 320.0) << 1)) * 0.6 * facing;
                vy = -5.0;
                ay = 0.06;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case kLv4GrabCloseHold:
        FocusCameraX(0x32, 3);
        FocusCameraY(0x32, 3);
        m_game->FlashNegative(0xf);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = kLv4Slam;
                frame = 4;
                (*m_opponent)->m_hitstop = 0;
                vx = (1 - ((x > 320.0) << 1)) * 0.6 * facing;
                vy = -5.0;
                ay = 0.06;
            }
        }
        break;
    case kLv4Stomps:
        (*m_opponent)->FocusCameraY(0x32, 3);
        m_game->FlashNegative(0xf);
        m_hideOffscreenMarker = 2;
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        if (m_patternVar1 > 0x78 && m_patternVar1 < 0x2d0 && frame > 5 && frame < 0xc && (WORD)Random(0, 0x64) < 5) {
            l50.type = 0x195;
            l50.x = x + 80.0 - (WORD)Random(0, 0xa0);
            l50.y = (double)-(WORD)Random(0, 0x32);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        if (frame > 5) {
            m_patternVar1++;
        }
        if (m_patternVar1 == 0x50) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = -320.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.keep = 1;
            l50.shadow = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (m_patternVar1 == 0x78) {
            l50.type = 0x192;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = -320.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.shadow = 1;
            l50.facing = facing;
            l50.keep = 1;
            SpawnObject(&l50);
        }
        if (frame == 9 && vy + y > 0.0) {
            StopMoving();
            timer = 0;
            frame = 0xa;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            y = 0.0;
            (*m_opponent)->m_koDelay = 0x7530;
            DealDamage(0x12c, 960.0);
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.sound = 2;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame == 0xf && vy + y > 0.0) {
            StopMoving();
            timer = 0;
            frame = 0x10;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            y = 0.0;
            DealDamage(0x578, 960.0);
            (*m_opponent)->m_koDelay = 0;
            ShakeScreen(0xa, 0xa);
            (*m_opponent)->m_hitstop = 0x78;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.sound = 0x16;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame == 0x14 && vy + y > 0.0) {
            StopMoving();
            timer = 0;
            frame = 0x15;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            y = 0.0;
            break;
        }
        if (frame == 0xb && m_patternVar1 > 0x334) {
            frame = 0xc;
            timer = 0;
            vy = -5.0;
            ay = 0.06;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                vx = 0.0;
                vy = -3.9;
                ay = 0.08;
            }
            if (frame == 0xc) {
                if (m_patternVar1 <= 0x2da) {
                    frame = 6;
                    vx = 0.0;
                    vy = -3.9;
                    ay = 0.08;
                } else {
                    frame = 0xb;
                }
            }
            if (frame == 0x12) {
                vx = -0.6;
                vy = -1.5;
                ay = 0.038;
            }
            if (frame == 0x1f && m_patternVar2 < 4) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = kStand;
                FaceOpponent();
            }
        }
        break;
    case k641236Lv1:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame >= 0 && frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 3 || frame == 4) && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = k641236Lv1Throw;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 4 && frame < 0x70) {
            vy = vy + ay;
        }
        if (frame < 0xc && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                m_invulTime = 6;
            }
            if (frame == 5 && m_patternVar1 < 1) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236Lv2:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame >= 0 && frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 3 || frame == 4) && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = k641236Lv2Throw;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 4 && frame < 0x70) {
            vy = vy + ay;
        }
        if (frame < 0xc && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                m_invulTime = 0xc;
            }
            if (frame == 5 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236Lv3:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        m_game->FlashNegative(0xf);
        if (frame >= 0 && frame < 3) {
            FocusCameraY(0x32, 3);
        }
        if ((frame == 3 || frame == 4) && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = k641236Lv3Throw;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame > 4 && frame < 0x70) {
            vy = vy + ay;
        }
        if (frame < 0xc && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                m_invulTime = 0x12;
            }
            if (frame == 5 && m_patternVar1 < 5) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236Lv1Throw:
        m_hideOffscreenMarker = 2;
        if (frame < 0xe) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xd || frame > 0xe && frame < 0x12) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xd) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 0x7e;
                    DealDamage(0x92e, 750.0);
                    ShakeScreen(0xa, 0);
                    timer = 0;
                    frame = 0xd;
                    m_playSound = 0x16;
                    break;
                }
                if (frame == 0x11) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 0x12;
                    break;
                }
            }
        }
        if (frame < 0xd) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xb) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xc) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd) {
                frame = frame - 8;
            }
            if (frame == 0xf) {
                (*m_opponent)->m_hitstop = 3;
                vx = -1.2;
                vy = -2.0;
                ay = 0.035;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -1.2;
                (*m_opponent)->m_hitVy = -2.0;
                (*m_opponent)->pattern = kHitAir;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k641236Lv2Throw:
        m_hideOffscreenMarker = 2;
        if (frame < 0x19) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xd || frame > 0xe && frame < 0x19 || frame > 0x1a && frame < 0x1e) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xd) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 0x96;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    DealDamage(0x3e8, 980.0);
                    ShakeScreen(0xa, 0);
                    (*m_opponent)->m_koDelay = 0x7530;
                    timer = 0;
                    frame = 0xd;
                    m_playSound = 0x16;
                    break;
                }
                if (frame > 0xe && frame < 0x19) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 0x7e;
                    ShakeScreen(0xf, 0);
                    DealDamage(0x834, 980.0);
                    (*m_opponent)->m_koDelay = 0;
                    timer = 0;
                    frame = 0x19;
                    m_playSound = 0x16;
                    break;
                }
                if (frame == 0x1d) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 0x1e;
                    break;
                }
            }
        }
        if (frame < 0xd) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0xe && frame < 0x19) {
            vx += 0.025;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4 || frame == 0xf || frame == 0x10) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5 || frame == 0x11) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6 || frame == 0x12) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 || frame == 0x13) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8 || frame == 0x14) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 0x15) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa || frame == 0x16) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xb || frame == 0x17) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xc || frame == 0x18) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd || frame == 0x19) {
                frame = frame - 8;
            }
            if (frame == 0xf) {
                vx = -4.0;
                vy = -4.0;
                ay = 0.025;
                (*m_opponent)->m_hitstop = 3;
            }
            if (frame == 0x1b) {
                vx = -1.8;
                vy = -2.3;
                ay = 0.035;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -1.8;
                (*m_opponent)->m_hitVy = -2.3;
                (*m_opponent)->pattern = kHitAir;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k641236Lv3Throw:
        m_hideOffscreenMarker = 2;
        m_game->FlashNegative(0xf);
        if (frame < 0x19) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
        }
        if (frame < 0xd || frame > 0xe && frame < 0x19 || frame > 0x1a && frame < 0x1e) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xd) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 0x96;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    DealDamage(0x3e8, 980.0);
                    ShakeScreen(0xa, 0);
                    (*m_opponent)->m_koDelay = 0x7530;
                    timer = 0;
                    frame = 0xd;
                    m_playSound = 0x16;
                    break;
                }
                if (frame > 0xe && frame < 0x19) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 0xba;
                    DealDamage(0xed8, 980.0);
                    (*m_opponent)->m_koDelay = 0;
                    ShakeScreen(0x14, 0x1e);
                    timer = 0;
                    frame = 0x19;
                    m_playSound = 0x16;
                    break;
                }
                if (frame == 0x1d) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 0x1e;
                    break;
                }
            }
        }
        if (frame < 0xd) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0xe && frame < 0x19) {
            vx += 0.025;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4 || frame == 0xf || frame == 0x10) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5 || frame == 0x11) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6 || frame == 0x12) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 || frame == 0x13) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8 || frame == 0x14) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 0x15) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa || frame == 0x16) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xb || frame == 0x17) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xc || frame == 0x18) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd || frame == 0x19) {
                frame = frame - 8;
            }
            if (frame == 0xf) {
                vx = -4.0;
                vy = -7.0;
                ay = 0.025;
                (*m_opponent)->m_hitstop = 3;
            }
            if (frame == 0x1b) {
                vx = -1.8;
                vy = -2.3;
                ay = 0.035;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -1.8;
                (*m_opponent)->m_hitVy = -2.3;
                (*m_opponent)->pattern = kHitAir;
            }
            if (frame >= x8) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k214214Lv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.sound = 0x13;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            FocusCameraY(0x32, 0x78);
            m_hitsLeft = 0xc;
        }
        if (timer == 0 && (frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf)) {
            m_playSound = 0x15;
        }
        if (frame > 7 && frame < 0x10) {
            if (m_inputX == facing) {
                vx += 0.012;
            }
            if (m_inputX == -facing) {
                vx -= 0.012;
            }
            if (vx < -1.2) {
                vx = -1.2;
            } else if (vx > 1.2) {
                vx = 1.2;
            }
        }
        if (frame > 0xf) {
            if (vx > 0.0) {
                vx -= 0.01;
                if (vx < 0.0) {
                    vx = 0.0;
                }
            }
            if (vx < 0.0) {
                vx += 0.01;
                if (vx > 0.0) {
                    vx = 0.0;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x10 && m_patternVar1 < 3) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 1 || frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x10) {
                m_attackResult = 0;
            }
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
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.sound = 5;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            FocusCameraY(0x32, 0x78);
            m_hitsLeft = 0x63;
        }
        if (timer == 0 && (frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf)) {
            m_playSound = 0x15;
        }
        if (frame > 7 && frame < 0x10) {
            if (m_inputX == facing) {
                vx += 0.012;
            }
            if (m_inputX == -facing) {
                vx -= 0.012;
            }
            if (vx < -1.3) {
                vx = -1.3;
            } else if (vx > 1.3) {
                vx = 1.3;
            }
        }
        if (frame > 0xf) {
            if (vx > 0.0) {
                vx -= 0.01;
                if (vx < 0.0) {
                    vx = 0.0;
                }
            }
            if (vx < 0.0) {
                vx += 0.01;
                if (vx > 0.0) {
                    vx = 0.0;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x10 && m_patternVar1 < 5) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 1 || frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x10) {
                m_attackResult = 0;
            }
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
        if (frame > 0) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 1 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.sound = 0x40;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.keep = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            FocusCameraY(0x32, 0x78);
            m_hitsLeft = 0x63;
            m_playSound = 0x25;
        }
        if (timer == 0 && (frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf)) {
            m_playSound = 0x15;
        }
        if (frame > 7 && frame < 0x10) {
            if (m_inputX == facing) {
                vx += 0.012;
            }
            if (m_inputX == -facing) {
                vx -= 0.012;
            }
            if (vx < -1.4) {
                vx = -1.4;
            } else if (vx > 1.4) {
                vx = 1.4;
            }
        }
        if (frame > 0xf) {
            if (vx > 0.0) {
                vx -= 0.01;
                if (vx < 0.0) {
                    vx = 0.0;
                }
            }
            if (vx < 0.0) {
                vx += 0.01;
                if (vx > 0.0) {
                    vx = 0.0;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x10 && m_patternVar1 < 0xa) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 1 || frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x10) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k21436Lv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 1;
            FocusCameraY(0x32, 0x78);
        }
        if (frame > 0xd && frame < 0x12 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitstop = 0xb4;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHold;
            (*m_opponent)->x = facing * 0x1e + x;
            pattern = k21436Lv1Hit;
            (*m_opponent)->facing = -facing;
            break;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult > 0 && frame < 0x12 && frame > 0xd) {
            timer = 0;
            frame = 0x12;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xe) {
                vx = 3.2;
            }
            if (frame == 0x12 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv1Hit:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
        }
        if ((frame == 5 || frame == 0xa) && timer == 0) {
            m_playSound = 0x15;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 0x12 && frame < 0x1f && y + vy > 0.0) {
            timer = 0;
            frame = 0x1f;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                x = facing * 0xf + x;
            }
            if (frame == 0xc) {
                x = facing * 0xf + x;
            }
            if (frame == 0xd) {
                if (m_patternVar1 > 1) {
                    frame = 0xf;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xf && m_patternVar1 < 1) {
                frame = 5;
                m_patternVar1++;
            }
            if (frame == 0x13) {
                vy = -3.3;
                vx = 1.5;
                m_hitsLeft = 3;
            }
            if (frame == 0x1f) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 1;
            FocusCameraY(0x32, 0x78);
        }
        if (frame > 0xd && frame < 0x12 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitstop = 0xb4;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHold;
            (*m_opponent)->x = facing * 0x1e + x;
            pattern = k21436Lv2Hit;
            (*m_opponent)->facing = -facing;
            break;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult > 0 && frame < 0x12 && frame > 0xd) {
            timer = 0;
            frame = 0x12;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xe) {
                vx = 4.0;
            }
            if (frame == 0x12 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv2Hit:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
        }
        if ((frame == 5 || frame == 0xa) && timer == 0) {
            m_playSound = 0x15;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 0x19 && frame < 0x26 && y + vy > 0.0) {
            timer = 0;
            frame = 0x26;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                x = facing * 0xf + x;
            }
            if (frame == 0xc) {
                x = facing * 0xf + x;
            }
            if (frame == 0xd) {
                if (m_patternVar1 > 1) {
                    frame = 0xf;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xf && m_patternVar1 < 2) {
                frame = 5;
                m_patternVar1++;
            }
            if (frame == 0x19) {
                vy = -4.0;
                vx = 1.6;
                m_hitsLeft = 4;
            }
            if (frame == 0x26) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        m_game->FlashNegative(0xf);
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
            m_hitsLeft = 1;
            FocusCameraY(0x32, 0x78);
            m_playSound = 0x25;
        }
        if (frame > 0xd && frame < 0x12 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitstop = 0xb4;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHold;
            (*m_opponent)->x = facing * 0x1e + x;
            pattern = k21436Lv3Hit;
            (*m_opponent)->facing = -facing;
            break;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult > 0 && frame < 0x12 && frame > 0xd) {
            timer = 0;
            frame = 0x12;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xe) {
                vx = 4.5;
            }
            if (frame == 0x12 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv3Hit:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
        }
        if ((frame == 5 || frame == 0xa) && timer == 0) {
            m_playSound = 0x15;
        }
        if (vx > 0.0) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.045;
            vy = vy + ay;
        }
        if (frame > 0x1b && frame < 0x21 && y + vy > 0.0) {
            timer = 0;
            frame = 0x21;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame > 0x25 && frame < 0x2a && y + vy > 0.0) {
            timer = 0;
            frame = 0x2a;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame > 0x2c && frame < 0x43 && y + vy > 0.0) {
            timer = 0;
            frame = 0x43;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                x = facing * 0xf + x;
            }
            if (frame == 0xc) {
                x = facing * 0xf + x;
            }
            if (frame == 0xd) {
                x = facing * 0xf + x;
            }
            if (frame == 0xf && m_patternVar1 < 0xa) {
                m_patternVar1++;
                frame = 5;
            }
            if (frame == 0x13) {
                x = facing * 0xf + x;
            }
            if (frame == 0x14) {
                x = facing * 0xf + x;
            }
            if (frame == 0x16) {
                x = facing * 0xf + x;
            }
            if (frame == 0xf && m_patternVar1 < 8) {
                frame = 5;
                m_patternVar1++;
            }
            if (frame == 0x1c) {
                vy = -1.8;
                vx = 1.5;
                m_hitsLeft = 1;
            }
            if (frame == 0x25) {
                vy = -2.6;
                vx = 1.5;
                m_hitsLeft = 1;
            }
            if (frame == 0x2d) {
                vy = -4.5;
                vx = 2.2;
                m_hitsLeft = 8;
            }
            if (frame == 0x43) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = kCrouch;
                StartPattern();
            }
        }
    }
}
