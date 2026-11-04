// CNayuki::UpdatePattern (0x451850-0x46108f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CNayuki's
// .rdata, which starts with its constructor's folder name (nayuki.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CNayuki::UpdatePattern()
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
        vx = m_warmUp * 0.02 + 0.6;
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
        vx = -0.6 - m_warmUp * 0.02;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        FaceOpponent();
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
            effect.layer = 1;
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
        if (frame == 1 && timer == 0 && m_warmUp > 0) {
            m_warmUp--;
        }
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
        if (m_hp > 0 && timer > 99) {
            pattern = kWakeUp;
            StartPattern();
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
    case kEatingJam:
        vx = 0.0;
        vy = 0.0;
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
    case kGuardStandLight:
        if (frame == 0 && timer == 0) {
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
        if (frame == 0 && timer == 0) {
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
        if (frame == 0 && timer == 0) {
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
        if (frame == 0 && timer == 0) {
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
        if (frame == 0 && timer == 0) {
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
        if (frame == 0 && timer == 0) {
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
    case 0xa1:
        if (frame == 0 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 70);
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
        if (frame == 7 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 70);
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
            if (frame == 13) {
                ay = 0.035;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kDashForward:
        if (frame == 0 && timer == 0) {
            StartAfterimages(1);
            StopMoving();
        }
        if (frame < 11 && frame > 4) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 11) {
            timer = 0;
            StopMoving();
            frame = 11;
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 5) {
                vx = 1.4;
                vy = -0.75;
                ay = 0.015;
            }
            if (frame == 11) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        if (y + vy > 0.0 && frame < 11) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 11;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
                vx = -2.0 - m_warmUp * 0.1;
                vy = -1.2;
            }
            if (frame == 11) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x190;
            effect.x = (double)((int)x - facing * 36);
            effect.y = (double)((int)y - 62);
            effect.facing = facing;
            effect.layer = 0;
            effect.scale = 0;
            SpawnObject(&effect);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            effect.type = 0x190;
            effect.x = (double)((int)x + facing * 36);
            effect.y = (double)((int)y - 62);
            effect.facing = -facing;
            effect.layer = 1;
            effect.scale = 0;
            SpawnObject(&effect);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
    case 0xb3:
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
        if (y + vy > 0.0 && frame < 11) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 11;
            m_playSound = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 4) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 11) {
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
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
        if (timer >= duration || timer >= duration - 3 && frame == 2 && m_warmUp > 4) {
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
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            if (m_warmUp > 5) {
                m_hitsLeft = 1;
            }
        }
        if (frame == 5 && timer == 0) {
            m_hitsLeft = 8;
        }
        if (frame < 10 && frame > 5) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            if (frame < 10 && frame > 5) {
                frame = 10;
                ShakeScreen(3, 0);
                effect.type = 3;
                effect.x = (double)((int)x + facing * 30);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 0;
                m_game->CreateEffect((EffectDesc*)&effect);
                m_playSound = 7;
            }
            vy = 0.0;
        }
        if (frame >= 10) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 5) {
                vy = -1.5;
                vx = m_warmUp * 0.05 + 1.0;
                ay = 0.06;
            }
            if (frame == 10) {
                frame = frame - 4;
            }
            if (frame == 11) {
                if (m_warmUp > 4) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame == 4 || frame == 5 || frame == 7 || frame == 9 || frame == 11) {
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
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            if (m_warmUp > 5) {
                m_hitsLeft = 1;
            }
        }
        if (frame == 10 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame > 13) {
            vy = vy + ay;
        }
        if (frame > 13 && vy + y > 0.0) {
            StartPattern();
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 10) {
                m_playVoice = 3;
            }
            if (frame < 9) {
                m_attackResult = 0;
            }
            if (frame == 8 || frame == 9 || frame == 10) {
                x = facing * 40 + x;
            }
            if (frame == 14) {
                vy = -1.0;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= frameCount) {
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
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
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
        if (timer >= duration || timer >= 3 && (frame == 1 && m_warmUp > 0 || frame == 2 && m_warmUp > 1 || frame == 3 && m_warmUp > 3 || frame == 4 && m_warmUp > 5)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                x = facing * 15 + x;
            }
            if (frame == 2) {
                x = facing * 15 + x;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration || timer >= duration - 3 && frame < m_warmUp - 4 && frame < 4) {
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
            m_hitsLeft = m_warmUp / 2 + 2;
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
            if (frame < 6) {
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
        if (timer >= duration || timer >= duration - 3 && frame < m_warmUp - 3 && frame < 4) {
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
            m_playSound = 20;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                StartPattern();
                pattern = kCrouch;
                FaceOpponent();
                break;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 11) {
            y = 0.0;
            m_playSound = 9;
            frame = 11;
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
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
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
    case kUnusedAirDive:
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
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
            effect.type = 3;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
            vx = 0.0;
            vy = 0.0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 5) {
                frame--;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            m_playSound = 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k5BFarC:
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 3;
        }
        if (y + vy > 0.0) {
            y = 0.0;
            timer = 0;
            StopMoving();
            frame = 10;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            (*m_opponent)->x = facing * 15 + x;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 22);
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
        if (frame == 4 && timer == 0) {
            DealDamage(1000, 750.0);
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitVx = 1.0;
            (*m_opponent)->m_hitVy = -2.5;
            (*m_opponent)->y = -50.0;
            (*m_opponent)->x = x;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = m_warmUp / 2 + 2;
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
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration || timer >= duration - 3 && frame < m_warmUp - 3 && frame < 4) {
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
    case kAirThrow:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 33);
            effect.y = (double)((int)y - 51);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 33 + x;
            (*m_opponent)->y = y - 61.0;
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
        if (frame < 7) {
            FocusCameraX(50, 3);
        }
        if (frame < 7) {
            FocusCameraY(50, 3);
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
            (*m_opponent)->x = facing * 23 + x;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 69.0;
            (*m_opponent)->x = facing * 21 + x;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 73.0;
            (*m_opponent)->x = facing * 19 + x;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 74.0;
            (*m_opponent)->x = facing * 19 + x;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 17 + x;
        }
        if (frame == 6) {
            (*m_opponent)->y = y - 70.0;
            (*m_opponent)->x = (facing << 4) + x;
        }
        if (frame == 7 && timer == 0) {
            (*m_opponent)->facing = facing;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = x - facing * 37;
            (*m_opponent)->pattern = kHitAirLaunch;
            DealDamage(1300, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitVx = -2.0;
            (*m_opponent)->m_hitVy = -1.0;
        }
        if (frame == 11 && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 11) {
                facing = -facing;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x191;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.scale = 0;
            effect.shadow = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
            effect.type = 0x192;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.scale = 0;
            effect.shadow = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x193;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.shadow = 1;
            effect.scale = 0;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                m_playSound = 20;
                m_gauge = m_gauge + 45;
                vx = 1.2;
                vy = -2.5;
                ay = 0.03;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                m_playSound = 20;
                m_gauge = m_gauge + 45;
                vx = 1.7;
                vy = -1.7;
                effect.type = 0x194;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
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
            m_playSound = 31;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 4;
            }
        }
        break;
    case kRebound:
        vy = vy + ay;
        ClearBufferedPress();
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k5D:
        StopMoving();
        if (frame == 0 && timer == 0) {
            m_playVoice = 4;
        }
        if (frame == 10 && timer == 0) {
            m_warmUp++;
        }
        if (frame == 10 && timer == 0) {
            m_playVoice = 5;
        }
        if (m_warmUp > 9) {
            m_warmUp = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
            frame = 12;
        }
        if (frame > 4 && frame < 9) {
            vx -= 0.025;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_patternVar2++;
            m_attackResult = 0;
            if (frame == 4) {
                m_gauge = m_gauge + 45;
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
            if (frame >= frameCount) {
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
            frame = 16;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (frame == 5 || frame == 9 || frame == 13) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 45;
                vx = 1.2;
                vy = -1.2;
                ay = 0.03;
                if (m_warmUp > 6) {
                    vy = -2.2;
                }
            }
            if (frame == 8 && m_warmUp < 5 || frame == 11 && m_warmUp < 7) {
                frame = 15;
            }
            if (frame == 15) {
                if (vy < 0.0) {
                    vy *= 0.5;
                }
                vx *= 0.5;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = m_warmUp + 1;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 99;
        }
        vy = vy + ay;
        if (frame > 11 && vy + y > 0.0) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 16;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (frame == 5 || frame == 9 || frame == 13) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 45;
                vx = 0.8;
                vy = -1.5;
                ay = 0.035;
                m_invulTime = m_warmUp * 12 + 30;
            }
            if (frame == 7 || frame == 11) {
                vy = -1.4;
            }
            if (frame == 12) {
                frame = 4;
            }
            if ((frame == 11 || frame == 8) && m_patternVar1 > m_warmUp) {
                frame = 12;
            }
            if (frame == 11 || frame == 8) {
                m_patternVar1++;
            }
            if (frame == 15 && vy < 0.0) {
                vy *= 0.5;
            }
            if (frame >= frameCount) {
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
        if (frame > 15) {
            vx -= 0.028;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 6 || frame == 11) && timer == 0) {
            m_playSound = 20;
        }
        if (y + vx > 0.0 && frame > 5 && frame < 16) {
            timer = 0;
            y = 0.0;
            vy = 0.0;
            frame = 16;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (m_patternVar2 > 2) {
                m_attackResult = 0;
                m_patternVar2 = 0;
            }
            if (frame == 5) {
                m_gauge = m_gauge + 45;
                vx = 1.8;
                vy = -1.7;
                ay = 0.035;
                if (m_patternVar1 == 1) {
                    vx = 0.6;
                    vy = -3.2;
                    ay = 0.024;
                }
            }
            if (frame == 16) {
                frame = 5;
            }
            if (frame >= frameCount) {
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
            m_playSound = 21;
        }
        timer++;
        if (timer >= 24 && m_warmUp > 3 && frame == 11) {
            frame++;
            timer = 0;
            m_attackResult = 0;
        }
        if (timer >= duration || timer >= duration - m_warmUp * 3 && frame == 11 || timer >= duration - 3 && frame == 1 && m_warmUp > 2 || timer >= duration - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame < 11) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 45;
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
            if (frame >= frameCount) {
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
            m_playSound = 21;
        }
        timer++;
        if (timer >= 24 && m_warmUp > 3 && frame == 11) {
            frame++;
            timer = 0;
            m_attackResult = 0;
        }
        if (timer >= duration || timer >= duration - m_warmUp * 3 && frame == 11 || timer >= duration - 3 && frame == 1 && m_warmUp > 2 || timer >= duration - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame < 11) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 45;
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
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            m_playSound = 21;
        }
        timer++;
        if (timer >= duration || timer >= duration - m_warmUp * 3 && frame == 11 || timer >= duration - 3 && frame == 1 && m_warmUp > 2 || timer >= duration - 3 && frame == 2 && m_warmUp > 4) {
            timer = 0;
            frame++;
            if (frame < 11) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 45;
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
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 99;
        }
        if (frame > 9) {
            vx -= 0.3;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            m_playSound = 21;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 11) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 45;
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
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_patternVar2++;
            if (frame >= frameCount) {
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
            effect.type = 3;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_gauge = m_gauge + 45;
                vx = 1.4;
                vy = -2.1;
                ay = 0.045;
            }
            if (frame == 8) {
                frame--;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 35;
            m_playSound = 20;
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
        if (timer >= duration) {
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
                x = facing * 40 + x;
            }
            if (frame == 9) {
                vy = -1.0;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
            m_playSound = 21;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
            m_playSound = 21;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration - (frame == 9) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                effect.type = 0x1ac;
                if (m_inputX == facing) {
                    effect.type = 0x1ad;
                }
                if (m_inputX == -facing) {
                    effect.type = 0x1ab;
                }
                effect.x = (double)((int)x + facing * 30);
                effect.y = (double)((int)y - 50);
                effect.scale = 0;
                effect.shadow = 1;
                effect.layer = 0;
                effect.facing = facing;
                SpawnObject(&effect);
                m_playVoice = 0;
                m_gauge = m_gauge + 45;
            }
            if (frame >= frameCount) {
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
            effect.type = 3;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_gauge = m_gauge + 45;
                vx = 1.4;
                vy = -2.1;
                ay = 0.045;
            }
            if (frame == 8) {
                frame--;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 35;
            m_playSound = 20;
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
        if (timer >= duration || frame == 1 && timer == 39 - m_warmUp * 3) {
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
                x = facing * 40 + x;
            }
            if (frame == 9) {
                vy = -0.7;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= frameCount) {
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
            m_playSound = 21;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
            m_playSound = 21;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && m_patternVar2 < 3) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
            FocusCameraY(50, 3);
        }
        if (frame == 2 && timer == 0) {
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
        if (frame >= 2) {
            unkf2 = 10;
        }
        if (frame == 4 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.scale = 0;
            effect.layer = 0;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
        }
        timer++;
        if (timer >= duration || frame == 5 && timer == duration - m_warmUp * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            effect.type = 0x191;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.scale = 0;
            effect.shadow = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration - (frame == 4) * m_warmUp * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 25;
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
    case k236236B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(50, 3);
        }
        if (frame == 2 && timer == 0) {
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
        if (frame >= 2) {
            unkf2 = 10;
        }
        if (frame == 4 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.scale = 0;
            effect.layer = 0;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
        }
        timer++;
        if (timer >= duration || frame == 5 && timer == duration - m_warmUp * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            FocusCameraY(50, 3);
        }
        if (frame == 2 && timer == 0) {
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
        if (frame > 2) {
            m_game->FlashNegative(15);
        }
        if (frame == 4 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x198;
            effect.x = (double)((int)x + facing * 14);
            effect.y = (double)((int)y - 41);
            effect.scale = 0;
            effect.layer = 0;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0;
        }
        timer++;
        if (timer >= duration || frame == 5 && timer == duration - m_warmUp * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
        if (vy + y > 0.0 && frame > 7 && frame < 12) {
            StopMoving();
            y = 0.0;
            frame = 12;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                effect.keep = 1;
                effect.type = 0x19d;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 80);
                effect.facing = facing;
                effect.scale = 0;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x19e;
                effect.y = (double)(int)y;
                SpawnObject(&effect);
            }
            if (frame == 8) {
                if (m_patternVar1 < 14) {
                    frame = frame - 2;
                    m_patternVar1++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 12) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
        if (vy + y > 0.0 && frame > 7 && frame < 12) {
            StopMoving();
            y = 0.0;
            frame = 12;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                effect.keep = 1;
                effect.type = 0x19d;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 80);
                effect.facing = facing;
                effect.scale = 0;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x19e;
                effect.y = (double)(int)y;
                SpawnObject(&effect);
            }
            if (frame == 8) {
                if (m_patternVar1 < 20) {
                    frame = frame - 2;
                    m_patternVar1++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 12) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
        if (frame > 3) {
            m_game->FlashNegative(15);
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
        if (vy + y > 0.0 && frame > 7 && frame < 12) {
            StopMoving();
            y = 0.0;
            frame = 12;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                effect.keep = 1;
                effect.type = 0x19d;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 80);
                effect.facing = facing;
                effect.scale = 0;
                effect.layer = 1;
                SpawnObject(&effect);
                effect.type = 0x19e;
                effect.y = (double)(int)y;
                SpawnObject(&effect);
            }
            if (frame == 8) {
                if (m_patternVar1 < 20) {
                    frame = frame - 2;
                    m_patternVar1++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 12) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
            m_hitsLeft = 99;
        }
        if (frame > 14) {
            vx += 0.035;
        }
        FocusCameraY(50, 3);
        if (frame == 0 && timer == 0) {
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
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2) {
            m_game->FlashNegative(15);
        }
        if (frame > 10 && frame < 15) {
            ShakeScreen(3, 10);
        }
        if ((char)AtScreenEdge() != 0 && frame > 14 && vx > 4.0) {
            vx = -2.7;
            vy = -3.5;
            ay = 0.035;
            pattern = kRebound;
            StartPattern();
            m_playSound = 31;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x19b;
            effect.x = (double)((int)x + facing * 50);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x19b;
            effect.x = (double)((int)x - facing * 50);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            break;
        }
        if (frame == 12 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 15 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 15) {
                if (m_patternVar1 < 10) {
                    frame = frame - 4;
                    m_patternVar1++;
                } else {
                    effect.type = 0x34;
                    effect.x = (double)(int)x;
                    effect.y = (double)((int)y - 25);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 22;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    vx = 0.5;
                    ShakeScreen(15, 10);
                    effect.keep = 1;
                    effect.type = 0x1a1;
                    effect.x = (double)(int)x;
                    effect.y = (double)(int)y;
                    effect.scale = 0;
                    effect.layer = 0;
                    effect.shadow = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
            }
            if (frame >= frameCount) {
                frame = frame - 4;
            }
        }
    }
}
