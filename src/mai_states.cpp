// CMai::UpdatePattern (0x607930-0x6163af), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMai's
// .rdata, which starts with its constructor's folder name (mai.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMai::UpdatePattern()
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
        vx = 0.5;
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
        vx = -0.5;
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.7;
        }
        if (frame > 1) {
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
        if (y + vy >= 0.0 && frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.7;
            vx = 0.6;
        }
        if (frame > 1) {
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
        if (y + vy >= 0.0 && frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.7;
            vx = -0.6;
        }
        if (frame > 1) {
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
        if (y + vy >= 0.0 && frame > 2) {
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
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            vy = -2.7;
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
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpForward:
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            vy = -2.7;
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
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpBack:
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            vy = -2.7;
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
            if (m_bounceDebrisOut == 0) {
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_bounceDebrisOut = 1;
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
            if (m_bounceDebrisOut == 0) {
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_bounceDebrisOut = 1;
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
            if (m_bounceDebrisOut == 0) {
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_bounceDebrisOut = 1;
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
            if (m_bounceDebrisOut == 0) {
                effect.type = 0x1f0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_bounceDebrisOut = 1;
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
        if (m_hp > 0 && timer > 99 && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
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
        if (frame == 2 && timer == 0) {
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
            vx = 0.0;
            vy = 0.0;
            StartAfterimages(3);
        }
        if (frame == 2 && timer == 0) {
            vx = 2.5;
            vy = -0.3;
            ay = 0.02;
            if (m_familiarState == 4) {
                vx = 3.2;
                vy = -0.25;
                ay = 0.025;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 2 && frame < 5) {
            y = 0.0;
            frame = 5;
            timer = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 5) {
                frame = 3;
            }
            if (frame >= frameCount) {
                FaceOpponent();
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kDashBack:
        if (frame == 0 && timer == 0) {
            StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -2.0;
            vy = -1.0;
        }
        if (frame > 1) {
            vy += 0.04;
        }
        if (frame > 3 && frame < 7 && vy + y >= 0.0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                FaceOpponent();
                pattern = kCrouch;
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
            m_playSound = 17;
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
        if (m_inputX == facing && m_patternVar2 >= 120) {
            pattern = kFall;
            StartPattern();
            vx = 1.1;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 48) {
            pattern = kFall;
            StartPattern();
            vx = 1.1;
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
            m_playSound = 17;
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
        if (m_inputX == -facing && m_patternVar2 >= 120) {
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
            vx = 0.0;
            vy = 0.0;
            StartAfterimages(10);
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
            StartAfterimages(10);
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
                vx = m_patternVar1 * 0.01;
                vy = m_patternVar2 * 0.01;
                ay = 0.035;
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
            if (frame == 2) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame >= frameCount) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 9 && timer == 0) {
            m_playVoice = 2;
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
    case k5C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 10 && timer == 0) {
            m_playVoice = 2;
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
        vx = 0.0;
        vy = 0.0;
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
            m_gauge = m_gauge + 13;
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
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k2C:
        vx = 0.0;
        vy = 0.0;
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
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 10 && timer == 0) {
            m_playVoice = 2;
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
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            StartPattern();
            break;
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                m_gauge = m_gauge + 13;
                m_playSound = 20;
                m_hitsLeft = 1;
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
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
    case k6A:
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
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 1;
            m_gauge = m_gauge + 25;
            effect.type = 0x19f;
            effect.x = (double)((int)x - facing * 28);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
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
    case k6B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 1;
            m_gauge = m_gauge + 25;
            effect.type = 0x1a0;
            effect.x = (double)((int)x - facing * 21);
            effect.y = (double)((int)y - 63);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
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
    case k6C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 1;
            m_gauge = m_gauge + 25;
            effect.type = 0x1a1;
            effect.x = (double)((int)x - facing * 5);
            effect.y = (double)((int)y - 61);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
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
    case k6AAwakened:
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
            m_hitsLeft = 1;
            m_familiarGauge -= 1000;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 1;
            m_gauge = m_gauge + 25;
            effect.type = 0x19f;
            effect.x = (double)((int)x - facing * 28);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
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
    case k6BAwakened:
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
            m_hitsLeft = 1;
            m_familiarGauge -= 1000;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 1;
            m_gauge = m_gauge + 25;
            effect.type = 0x1a0;
            effect.x = (double)((int)x - facing * 21);
            effect.y = (double)((int)y - 63);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
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
    case k6CAwakened:
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
            m_hitsLeft = 1;
            m_familiarGauge -= 1000;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 1;
            m_gauge = m_gauge + 25;
            effect.type = 0x1a1;
            effect.x = (double)((int)x - facing * 5);
            effect.y = (double)((int)y - 61);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
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
    case k4C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.08;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playSound = 21;
                m_gauge = m_gauge + 25;
                vx = 3.0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kThrow:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kThrownStandLow2;
            pattern = kThrowHold;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 49);
            effect.y = (double)((int)y - 43);
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
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
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
    case kThrowHold:
        FocusCameraY(50, 3);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                if (facing == 1 && x + 20.0 < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -150.0;
                (*m_opponent)->x = facing * 41 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -100.0;
                (*m_opponent)->x = facing * 47 + x;
            }
            if (frame == 3) {
                (*m_opponent)->y = -81.0;
                (*m_opponent)->x = x - facing * 92;
                (*m_opponent)->facing = -facing;
                (*m_opponent)->pattern = kThrownDoubledOverInverted;
            }
            if (frame == 4) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x - facing * 97;
                DealDamage(1200, 750.0);
                (*m_opponent)->pattern = kKnockdownHittable;
                (*m_opponent)->m_landHittable = 1;
                m_attackResult = 3;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kDashHopA:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
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
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kDashHopB:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 10;
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
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kDashHopC:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 10;
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
            m_attackResult = 0;
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
            pattern = kAirThrowHold;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 31);
            effect.y = (double)((int)y - 82);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 31 + x;
            (*m_opponent)->y = y - 82.0;
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
    case kAirThrowHold:
        if (frame < 4) {
            FocusCameraX(50, 3);
        }
        if (frame < 4) {
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
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->x = facing * 29 + x;
            (*m_opponent)->pattern = kThrownDoubledOver;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 11 + x;
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->facing = facing;
        }
        if (frame == 3 && timer == 0) {
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = x - facing * 37;
            (*m_opponent)->pattern = kHitBlownAway;
            DealDamage(1300, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitVx = -3.0;
            (*m_opponent)->m_hitVy = 3.0;
        }
        if (frame == 5 && timer == 0) {
            ay = 0.035;
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
    case 0xf9:
        if (frame == 0 && timer == 0) {
            unkdc = 4;
            unkde = -20;
            vx = 0.0;
            m_hitsLeft = 1;
            m_recoilGuardWindow = 0;
            m_freezeTime = 60;
            effect.type = 0x28;
            effect.x = (double)((int)x + facing * 10);
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 19;
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
    case kAir623A:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                vx = 0.0;
                ay = 0.0;
            }
            if (y < 0.0) {
                m_patternVar1 = 1;
            }
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_hitsLeft = 1;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.025;
        }
        if (frame > 1 && vy + y >= 0.0) {
            timer = 0;
            frame = 0;
            pattern = kAir623Landing;
            break;
        }
        timer++;
        vy = vy + ay;
        if (timer >= duration || timer >= duration - 3 && m_patternVar1 == 1) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = 11;
            }
        }
        break;
    case kAir623B:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                vx = 0.0;
                ay = 0.0;
            }
            if (y < 0.0) {
                m_patternVar1 = 1;
            }
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_hitsLeft = 1;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.035;
        }
        if (frame > 1 && vy + y >= 0.0) {
            timer = 0;
            frame = 0;
            pattern = kAir623Landing;
            m_patternVar2 = 1;
            break;
        }
        timer++;
        vy = vy + ay;
        if (timer >= duration || timer >= duration - 3 && m_patternVar1 == 1) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir623C:
        if (frame == 0 && timer == 0) {
            if (y < 0.0) {
                m_patternVar1 = 1;
            }
            if (y == 0.0) {
                vx = 0.0;
                ay = 0.0;
            }
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 20);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StartAfterimages(3);
            if (m_familiarState == 4) {
                m_familiarGauge -= 1000;
                if (m_familiarGauge < 0) {
                    m_familiarGauge = 0;
                }
            } else if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_hitsLeft = 2;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.025;
        }
        if (frame == 7 && timer == 0) {
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame > 1 && vy + y >= 0.0) {
            frame = 0;
            timer = 0;
            pattern = kAir623Landing;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration || timer >= duration - 3 && m_patternVar1 == 1) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir623Landing:
        vx = 0.0;
        vy = 0.0;
        FaceOpponent();
        timer++;
        if (timer >= duration || frame == 2 && m_patternVar2 == 1 && timer == 21) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
            }
        }
        break;
    case k412A:
        m_attackResult = 2;
        if (m_holdA > 0) {
            m_patternVar2++;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 0;
            effect.type = 0x20;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.facing = -facing;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && timer == 0) {
            StopMoving();
            if (m_patternVar2 > 30) {
                m_patternVar1 = 1;
            }
        }
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 5 && timer == 20 && m_patternVar1 == 0) {
            vx = -3.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 1.5;
            ax = -0.05;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 6 && m_patternVar1 == 1) {
                frame = 0;
                timer = 0;
                pattern = k412AHeld;
                break;
            }
            if (frame == 6) {
                x = (*m_opponent)->x - facing * 60;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k412B:
        m_attackResult = 2;
        if (m_holdB > 0) {
            m_patternVar2++;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 0;
            effect.type = 0x20;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.facing = -facing;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && timer == 0) {
            StopMoving();
            if (m_patternVar2 > 30) {
                m_patternVar1 = 1;
            }
        }
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 5 && timer == 20 && m_patternVar1 == 0) {
            x = (*m_opponent)->x - facing * 180;
        }
        if (frame == 6 && timer == 0) {
            vx = 1.5;
            ax = -0.05;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (0) {}
            if (0) {}
            if (frame == 6 && m_patternVar1 == 1) {
                frame = 0;
                timer = 0;
                pattern = k412BHeld;
                x = (*m_opponent)->x - facing * 100;
                if (x > 540.0 && facing == 1) {
                    x = 540.0;
                }
                if (x < 100.0 && facing == -1) {
                    x = 100.0;
                }
                y = -100.0;
                break;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k412C:
        if (frame == 0 && timer == 0) {
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 20);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StartAfterimages(3);
            if (m_familiarState == 4) {
                m_familiarGauge -= 1000;
                if (m_familiarGauge < 0) {
                    m_familiarGauge = 0;
                }
            } else if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playVoice = 0;
            effect.type = 0x20;
            effect.x = (double)((int)x + facing * 60);
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.facing = -facing;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 4 && m_attackResult == 2) {
            timer = 0;
            frame = 6;
            break;
        }
        if (frame == 5 && timer == 0) {
            StopMoving();
        }
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 5 && timer == 20) {
            vx = 8.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 3.5;
            ax = -0.05;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                FaceOpponent();
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214A:
        m_attackResult = 2;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            if (m_familiarState != 4) {
                m_familiarState = 2;
                effect.type = 0x19c;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.keep = 1;
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            } else {
                m_familiarGauge -= 1000;
                if (m_familiarGauge < 0) {
                    m_familiarGauge = 0;
                }
                effect.type = 0x1a8;
                effect.x = (double)((int)x + facing * 80);
                effect.y = (double)(int)y;
                effect.keep = 1;
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214B:
        m_attackResult = 2;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            if (m_familiarState != 4) {
                m_familiarState = 2;
                effect.type = 0x19c;
                effect.x = (double)((int)x + facing * 120);
                effect.y = (double)(int)y;
                effect.keep = 1;
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            } else {
                effect.type = 0x1a8;
                m_familiarGauge -= 1000;
                if (m_familiarGauge < 0) {
                    m_familiarGauge = 0;
                }
                effect.x = (double)((int)x + facing * 160);
                effect.y = (double)(int)y;
                effect.keep = 1;
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214C:
        m_attackResult = 2;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            if (m_familiarState != 4) {
                m_familiarState = 2;
                effect.type = 0x19c;
                effect.x = (double)((int)x + facing * 200);
                effect.y = (double)(int)y;
                effect.keep = 1;
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            } else {
                effect.type = 0x1a8;
                m_familiarGauge -= 1000;
                if (m_familiarGauge < 0) {
                    m_familiarGauge = 0;
                }
                effect.x = (double)((int)x + facing * 240);
                effect.y = (double)(int)y;
                effect.keep = 1;
                effect.scale = 2;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case kSummonFamiliar:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_playVoice = 5;
            m_familiarGauge = 10000;
            m_familiarSummoned = 1;
            m_familiarRate = 1;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x191;
            effect.x = (double)(int)x;
            if (m_patternVar3 == 1) {
                effect.x = (double)((int)x + facing * 60);
                if ((int)x + facing * 60 > 600) {
                    effect.x = 600.0;
                }
                if ((int)x + facing * 60 < 40) {
                    effect.x = 40.0;
                }
            }
            if (m_patternVar3 == 2) {
                effect.x = (double)((int)x - facing * 60);
                if ((int)x - facing * 60 > 600) {
                    effect.x = 600.0;
                }
                if ((int)x - facing * 60 < 40) {
                    effect.x = 40.0;
                }
            }
            effect.y = (double)((int)y - 17);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
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
                FaceOpponent();
            }
        }
        break;
    case k412AHeld:
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            m_hitsLeft = 1;
        }
        if (frame > 6) {
            vx -= 0.055;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
    case k412BHeld:
        if (frame == 0 && timer == 0) {
            vx = 1.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (0) {}
        if (frame > 2) {
            vy += 0.035;
        }
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
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_familiarState = 2;
            m_playVoice = 5;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1ac;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 20);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
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
                FaceOpponent();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_familiarState = 2;
            m_playVoice = 5;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1ad;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 20);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
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
                FaceOpponent();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 40);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StartAfterimages(3);
            if (m_familiarState == 4) {
                m_familiarGauge -= 1000;
                if (m_familiarGauge < 0) {
                    m_familiarGauge = 0;
                }
            } else if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        if (frame == 3 && timer == 0) {
            m_familiarState = 2;
            m_playVoice = 5;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1ae;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 20);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
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
                FaceOpponent();
            }
        }
        break;
    case k623A:
        m_attackResult = 2;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_familiarState = 2;
            effect.type = 0x1b0;
            effect.x = (double)((int)x + facing * 80);
            effect.y = (double)((int)y - 20);
            effect.keep = 1;
            effect.scale = 2;
            effect.facing = facing;
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
                FaceOpponent();
            }
        }
        break;
    case k623B:
        m_attackResult = 2;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_familiarState = 2;
            effect.type = 0x1b0;
            effect.x = (double)((int)x + facing * 160);
            effect.y = (double)((int)y - 20);
            effect.keep = 1;
            effect.scale = 2;
            effect.facing = facing;
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
                FaceOpponent();
            }
        }
        break;
    case k623C:
        m_attackResult = 2;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_familiarState = 2;
            effect.type = 0x1b0;
            effect.x = (double)((int)x + facing * 240);
            effect.y = (double)((int)y - 20);
            effect.keep = 1;
            effect.scale = 2;
            effect.facing = facing;
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
                FaceOpponent();
            }
        }
        break;
    case kRecallFamiliar:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_playVoice = 5;
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
    case k236236Lv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 2) {
            FocusCameraY(50, 3);
        }
        if (frame == 2 && timer == 0) {
            m_hitsLeft = 1;
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
        if (frame == 4 && timer == 0) {
            m_playVoice = 0;
        }
        if (frame == 8 && timer == 0) {
            vx = 5.0;
        }
        if (frame == 9 && timer == 0) {
            vx = 1.8;
            ax = -0.05;
        }
        if (frame > 8) {
            vx = vx + ax;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 8) {
            if (m_attackResult == 2 || m_attackResult == 5) {
                timer = 0;
                frame = 9;
                break;
            }
            if (m_attackResult == 3) {
                (*m_opponent)->m_hitstop = 9999;
                StartPattern();
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kThrownStandLow2;
                pattern = k236236Lv1Flurry;
                break;
            }
        }
        if (frame > 0 && frame < 18) {
            FocusCameraY(50, 3);
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
    case k236236Lv2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 2) {
            FocusCameraY(50, 3);
        }
        if (frame == 2 && timer == 0) {
            m_hitsLeft = 1;
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
        if (frame == 4 && timer == 0) {
            m_playVoice = 0;
        }
        if (frame == 8 && timer == 0) {
            vx = 7.0;
        }
        if (frame == 9 && timer == 0) {
            vx = 1.8;
            ax = -0.05;
        }
        if (frame > 8) {
            vx = vx + ax;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 8) {
            if (m_attackResult == 2 || m_attackResult == 5) {
                timer = 0;
                frame = 9;
                break;
            }
            if (m_attackResult == 3) {
                (*m_opponent)->m_hitstop = 9999;
                StartPattern();
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kThrownStandLow2;
                pattern = k236236Lv2Flurry;
                break;
            }
        }
        if (frame > 0 && frame < 18) {
            FocusCameraY(50, 3);
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
    case k236236Lv3:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
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
        if (frame > 1) {
            m_game->FlashNegative(15);
        }
        if (frame <= 2) {
            FocusCameraY(50, 3);
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 0;
        }
        if (frame == 8 && timer == 0) {
            vx = 10.0;
        }
        if (frame == 9 && timer == 0) {
            vx = 1.8;
            ax = -0.05;
        }
        if (frame > 8) {
            vx = vx + ax;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 8) {
            if (m_attackResult == 2 || m_attackResult == 5) {
                timer = 0;
                frame = 9;
                break;
            }
            if (m_attackResult == 3) {
                (*m_opponent)->m_hitstop = 9999;
                StartPattern();
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = kThrownStandLow2;
                pattern = k236236Lv3Flurry;
                effect.type = 0x1a3;
                effect.x = 0.0;
                effect.y = 20.0;
                effect.scale = 0;
                effect.keep = 1;
                effect.facing = 1;
                effect.layer = 0;
                effect.movesInFreeze = 1;
                SpawnObject(&effect);
                effect.type = 0x1a4;
                effect.x = 0.0;
                effect.y = 38.0;
                effect.scale = 0;
                effect.keep = 1;
                effect.facing = 1;
                effect.layer = 1;
                effect.movesInFreeze = 1;
                SpawnObject(&effect);
                break;
            }
        }
        if (frame > 0 && frame < 18) {
            FocusCameraY(50, 3);
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
    case k236236Lv1Flurry:
        if (frame == 0 && timer == 0) {
            vx = 0.3;
            x = (*m_opponent)->x + facing * 30;
            m_attackResult = 0;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 11 && timer == 0) {
            m_playSound = 20;
        }
        if (frame == 15 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 15 && timer == 90) {
            (*m_opponent)->pattern = kHitAirHeavy;
            (*m_opponent)->m_hitstop = 0;
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -4.0;
            m_attackResult = 2;
            DealDamage(2400, 400.0);
            effect.type = 0x34;
            effect.x = (*m_opponent)->x;
            effect.sound = 22;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 0 && frame < 15) {
            FocusCameraY(50, 10);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 9) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 9) {
                x = facing * 80 + x;
                m_patternVar1 = 0;
            }
            if (frame == 13 && m_patternVar1 < 12) {
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
    case k236236Lv2Flurry:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            vx = 0.3;
            x = (*m_opponent)->x + facing * 30;
            m_attackResult = 0;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 11 && timer == 0) {
            m_playSound = 20;
        }
        if (frame == 14 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 15 && timer == 0 && m_patternVar1 == 7) {
            (*m_opponent)->pattern = kHitAirHeavy;
            (*m_opponent)->m_hitstop = 0;
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -4.0;
            m_attackResult = 2;
            DealDamage(3200, 400.0);
            effect.type = 0x34;
            effect.x = (*m_opponent)->x;
            effect.sound = 22;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 0 && frame < 15) {
            FocusCameraY(50, 10);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 9) {
                frame = 4;
                m_patternVar1++;
            }
            if (frame == 9) {
                x = facing * 80 + x;
                m_patternVar1 = 0;
            }
            if (frame == 13 && m_patternVar1 < 12) {
                frame = 11;
                m_patternVar1++;
            }
            if (frame == 14) {
                m_patternVar1 = 12;
            }
        }
        if (frame >= frameCount) {
            if (m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            } else {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236Lv3Flurry:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            vx = 0.3;
            x = (*m_opponent)->x + facing * 30;
            m_attackResult = 0;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 11 && timer == 0) {
            m_playSound = 20;
        }
        if (frame == 14 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 15 && timer == 0 && m_patternVar1 == 7) {
            (*m_opponent)->pattern = kHitAirHeavy;
            (*m_opponent)->m_hitstop = 0;
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -4.0;
            m_attackResult = 2;
            DealDamage(4500, 400.0);
            (*m_opponent)->m_untechTime = (int)(200.0 * m_proration / 10000.0);
            effect.type = 0x34;
            effect.x = (*m_opponent)->x;
            effect.sound = 22;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 0 && frame < 15) {
            FocusCameraY(50, 10);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 9) {
                frame = 4;
                m_patternVar1++;
            }
            if (frame == 9) {
                x = facing * 80 + x;
                m_patternVar1 = 0;
            }
            if (frame == 13 && m_patternVar1 < 12) {
                frame = 11;
                m_patternVar1++;
            }
            if (frame == 14) {
                m_patternVar1 = 12;
            }
        }
        if (frame >= frameCount) {
            if (m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            } else {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kLv4Awaken:
        FocusCameraY(50, 3);
        if (frame == 0 && timer == 0) {
            m_playVoice = 3;
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
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
            effect.type = 0x1ab;
            effect.x = (double)((int)x + facing * 20);
            effect.y = 0.0;
            effect.movesInFreeze = 1;
            effect.facing = facing;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_freezeTime > 0) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedFlurry:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            vx = 0.3;
            x = (*m_opponent)->x + facing * 30;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 11 && timer == 0) {
            m_playSound = 20;
        }
        if (frame == 14 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 15 && timer == 0 && m_patternVar1 == 7) {
            (*m_opponent)->pattern = kHitAirHeavy;
            (*m_opponent)->m_hitstop = 0;
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -8.0;
            DealDamage(4200, 750.0);
            (*m_opponent)->m_untechTime = (int)(200.0 * m_proration / 10000.0);
            effect.type = 0x34;
            effect.x = (*m_opponent)->x;
            effect.sound = 22;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 0 && frame < 15) {
            FocusCameraY(50, 10);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 9) {
                frame = 4;
                m_patternVar1++;
            }
            if (frame == 9) {
                x = facing * 80 + x;
                m_patternVar1 = 0;
            }
            if (frame == 13 && m_patternVar1 < 12) {
                frame = 11;
                m_patternVar1++;
            }
            if (frame == 14) {
                m_patternVar1 = 12;
            }
        }
        if (frame >= frameCount) {
            if (m_patternVar1 > 0) {
                frame = frame - 2;
                m_patternVar1--;
            } else {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedSuperLv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_familiarGauge = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_familiarState == 1) {
                    frame = 0;
                    break;
                }
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedSuperLv2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_familiarGauge = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_familiarState == 1) {
                    frame = 0;
                    break;
                }
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedSuperLv3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_familiarGauge = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_familiarState == 1) {
                    frame = 0;
                    break;
                }
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214Lv1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 13);
            effect.y = (double)((int)y - 51);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1b6;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 15);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            effect.movesInFreeze = 300;
            SpawnObject(&effect);
            m_familiarState = 2;
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
    case k214214Lv1Familiar:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
        }
        if (frame == 3 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 13);
            effect.y = (double)((int)y - 51);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1ba;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 15);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            effect.movesInFreeze = 300;
            SpawnObject(&effect);
            m_familiarState = 2;
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
    case k214214Lv2Familiar:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
        }
        if (frame == 3 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 13);
            effect.y = (double)((int)y - 51);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1be;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 15);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            effect.movesInFreeze = 300;
            SpawnObject(&effect);
            m_familiarState = 2;
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
    case k214214Lv3Familiar:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
    case kAwakened236236D:
        if (frame < 5) {
            FocusCameraY(50, 3);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 19);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
            m_hitsLeft = 0;
        }
        if (frame == 4 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = kAwakened236236DHit;
            (*m_opponent)->pattern = kThrownHidden;
            FillBackground(176, 3);
        }
        if (frame == 5 && timer == 0) {
            m_familiarGauge = 0;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                if ((*m_opponent)->y == 0.0) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAwakened236236DHit:
        FocusCameraY(50, 3);
        if (frame < 2) {
            FillBackground(176, 3);
        }
        if (frame > 1 && frame < 10) {
            FillBackground(177, 3);
            (*m_opponent)->Tint(176, 3);
        }
        if (frame == 1 && timer == 0) {
            m_playVoice = 3;
            effect.type = 0x1c2;
            effect.x = 0.0;
            effect.y = 0.0;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.screen = 1;
            effect.facing = 1;
            SpawnObject(&effect);
        }
        if (frame == 2 && timer == 0) {
            (*m_opponent)->pattern = kThrownStandHigh2;
        }
        if (frame == 11 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 12 && timer == 0) {
            (*m_opponent)->pattern = kHitAirHeavy;
            (*m_opponent)->m_hitVx = 0.0;
            (*m_opponent)->m_hitVy = -5.0;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->m_noAirRecovery = 1;
            DealDamage((int)(m_familiarGauge * 0.15 + 3500.0), 500.0);
            m_playSound = 22;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->m_hitstop = 0;
            effect.type = 0x34;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (double)((int)(*m_opponent)->y - 40);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_familiarGauge = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 4) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
    }
}
