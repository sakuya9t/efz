// CNagamori::UpdatePattern (0x49d610-0x4add8f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CNagamori's
// .rdata, which starts with its constructor's folder name (nagamori.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CNagamori::UpdatePattern()
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
        vx = 1.0;
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
        vx = -1.0;
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
            ay = 0.045;
            vy = -2.9;
            if (m_dashMomentum == 1) {
                vx = 0.4;
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
            ay = 0.045;
            vy = -2.9;
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
            ay = 0.045;
            vy = -2.9;
            vx = -0.7;
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
        ay = 0.045;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
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
        ay = 0.045;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = 0.9;
            if (m_dashMomentum == 1) {
                vx = 1.4;
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
        ay = 0.045;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = -0.9;
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
        timer++;
        m_dashMomentum = 0;
        if (m_hp > 0 && timer > 99 && frame == 0) {
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
        m_dashMomentum = 0;
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
        m_dashMomentum = 0;
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
        m_dashMomentum = 0;
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
        m_dashMomentum = 0;
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
        m_dashMomentum = 0;
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
        m_dashMomentum = 0;
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
            effect.y = (double)((int)y - 60);
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
        if (frame == 6 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 60);
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
            if (frame == 17) {
                ay = 0.035;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
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
        m_dashMomentum = 0;
        StartAfterimages(2);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -1.8;
            vy = -0.9;
        }
        if (frame > 1) {
            vy += 0.038;
        }
        if (frame > 2 && vy + y >= 0.0 && m_patternVar1 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_patternVar1++;
            y = 0.0;
            m_playSound = 9;
            timer = 0;
            frame = 11;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                FaceOpponent();
                pattern = kStand;
                StartPattern();
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
                m_playSound = 17;
            }
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
            vx = -1.8;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            if (m_patternVar1 == 0) {
                m_playSound = 17;
            }
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
        if (m_inputX != -facing && m_patternVar1 >= 42) {
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
            m_dashMomentum = 0;
            m_patternVar1 = (int)(vx * 100.0);
            m_patternVar2 = (int)(vy * 100.0);
            if (ay == 0.0) {
                ay = 0.035;
            }
            vx = 0.0;
            vy = 0.0;
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
        if (frame == 0 && timer == 0 && m_patternVar3 == 0) {
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
            m_playSound = 18;
            effect.type = 1;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
                m_patternVar3++;
                if (m_patternVar3 < 5) {
                    frame = 0;
                    break;
                }
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
            if (frame == 2) {
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
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
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
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
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 5) {
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            m_hitsLeft = 6;
        }
        if (frame == 1 && timer == 0) {
            effect.type = 0x194;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 30);
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            TriggerObjectsNear((int)x, -10, 90, 50);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
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
            if (frame == 4 && m_patternVar1 < 3) {
                frame = 2;
                m_patternVar1++;
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
        if (frame == 2 && timer == 0) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kHopAttackUnused:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.08;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                if (y + vy < 0.0) {
                    frame--;
                } else {
                    y = 0.0;
                }
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
            m_dashMomentum = 0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 20;
            m_playSound = 20;
            m_hitsLeft = 1;
            vx = 1.5;
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
            if (frame < 5) {
                m_attackResult = 0;
            }
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
        if (timer >= duration) {
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
    case k2CShotOut:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 || frame == 4) {
            vy = vy + ay;
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (vy + y > 0.0) {
                frame = 5;
                timer = 0;
                ShakeScreen(3, 0);
                effect.type = 3;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 0;
                m_game->CreateEffect((EffectDesc*)&effect);
                m_playSound = 7;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -0.8;
                ay = 0.035;
            }
            if (frame == 5) {
                frame = 3;
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
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = kThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
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
    case kThrowHit:
        if (frame == 0 && timer == 1) {
            (*m_opponent)->m_koDelay = 10000;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = facing * 35 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
        }
        if (frame == 5 && timer == 45) {
            frame = 6;
            timer = 0;
            break;
        }
        if (frame == 6 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            m_patternVar2 = 0;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 24);
            effect.scale = 2;
            effect.sound = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(75, 1000.0);
        }
        if (frame == 10 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 24);
            effect.scale = 2;
            effect.sound = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->m_koDelay = 0;
            DealDamage(800, 750.0);
            (*m_opponent)->pattern = kKnockdownHittable;
            (*m_opponent)->StartPattern();
        }
        if (frame > 14) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownLying2;
                if (facing == 1 && x + 20.0 < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-17 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 7 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 14) {
                vx = -0.7;
                vy = -1.7;
                ay = 0.037;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
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
            vx = 1.9;
            vy = 0.0;
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
                StartPattern();
            }
        }
        break;
    case kDashB:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.9;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
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
                StartPattern();
            }
        }
        break;
    case kDashC:
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
        m_dashMomentum = 0;
        StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.9;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 10;
            m_playSound = 20;
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
            vx = 1.9;
            vy = 0.0;
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
                StartPattern();
            }
        }
        break;
    case kDash2B:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.1;
            vy = -1.2;
            ay = 0.034;
        }
        if (frame == 6 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_playSound = 20;
        }
        vy = vy + ay;
        if (y + vy > 0.0) {
            pattern = kLand;
            y = 0.0;
            StartPattern();
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 9) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kDash2C:
        StartAfterimages(3);
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 || frame == 4) {
            vy = vy + ay;
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (vy + y > 0.0) {
                m_hitsLeft = 1;
                frame = 5;
                timer = 0;
                ShakeScreen(3, 0);
                vx *= 0.3;
                effect.type = 3;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 0;
                m_game->CreateEffect((EffectDesc*)&effect);
                m_playSound = 7;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.5;
                vy = -0.8;
                ay = 0.035;
            }
            if (frame == 5) {
                frame = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
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
            effect.x = (double)((int)x + facing * 29);
            effect.y = (double)((int)y - 49);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 29 + x;
            (*m_opponent)->y = y - 49.0;
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
        if (frame < 6) {
            FocusCameraX(50, 3);
        }
        if (frame < 6) {
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
        if (frame == 2) {
            (*m_opponent)->y = y - 69.0;
            (*m_opponent)->x = facing * 33 + x;
            (*m_opponent)->pattern = kThrownStandLow;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 11 + x;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 49.0;
            (*m_opponent)->x = facing * 26 + x;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 46.0;
            (*m_opponent)->x = facing * 25 + x;
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6) {
            (*m_opponent)->y = y - 72.0;
            (*m_opponent)->x = x + 0.0;
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 && timer == 0) {
            (*m_opponent)->y = y - 40.0;
            (*m_opponent)->x = x - facing * 20;
            (*m_opponent)->pattern = kHitAirLaunch;
            DealDamage(1200, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitVx = -2.0;
            (*m_opponent)->m_hitVy = 0.0;
        }
        if (frame == 8 && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                facing = -facing;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
            if (y < 0.0) {
                frame = 1;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 30;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            TriggerObjectsNear((int)x + facing * 51, (int)y - 63, 36, 80);
        }
        if (frame == 6 && vy + y > 0.0) {
            timer = 0;
            y = 0.0;
            frame = 7;
            StopMoving();
            break;
        }
        if (frame > 1) {
            vy = vy + ay;
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
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 2;
            if (y < 0.0) {
                frame = 1;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            TriggerObjectsNear((int)x + facing * 51, (int)y - 63, 36, 80);
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 15;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            TriggerObjectsNear((int)x + facing * 51, (int)y - 63, 36, 80);
        }
        if (frame == 10 && vy + y > 0.0) {
            timer = 0;
            y = 0.0;
            frame = 11;
            StopMoving();
            break;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 8) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 3;
            StopMoving();
            if (y < 0.0) {
                frame = 1;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            TriggerObjectsNear((int)x + facing * 51, (int)y - 63, 36, 80);
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 15;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            TriggerObjectsNear((int)x + facing * 51, (int)y - 63, 36, 80);
        }
        if (frame == 11 && timer == 0) {
            m_gauge = m_gauge + 15;
            vx = 1.1;
            vy = -2.8;
            ay = 0.05;
        }
        if ((frame == 21 || frame == 20) && vy + y > 0.0) {
            timer = 0;
            y = 0.0;
            frame = 22;
            StopMoving();
            break;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 14) {
                m_attackResult = 0;
            }
            if (frame == 22 && y < 0.0) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kHopBombUnused:
        if (frame == 0 && timer == 0) {
            vx = -0.9;
            vy = -2.1;
            ay = 0.07;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 10);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kHopPlaceUnused:
        if (frame == 0 && timer == 0) {
            vx = -0.9;
            vy = -2.1;
            ay = 0.05;
            m_playVoice = 1;
            effect.type = 0x190;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge - 50;
            m_bombsPlaced++;
            effect.type = 0x190;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            m_playVoice = 1;
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
    case k214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge - 50;
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            m_playVoice = 1;
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
    case k214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge - 50;
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            m_playVoice = 1;
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
    case kAir236A:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 50;
            m_playVoice = 1;
            effect.type = 0x190;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (y + vy > 0.0) {
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            vx = 0.0;
            StartPattern();
            pattern = kAir236Landing;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir236B:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 50;
            m_playVoice = 1;
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (y + vy > 0.0) {
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            vx = 0.0;
            StartPattern();
            pattern = kAir236Landing;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir236C:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 50;
            m_playVoice = 1;
            effect.type = 0x198;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (y + vy > 0.0) {
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            vx = 0.0;
            StartPattern();
            pattern = kAir236Landing;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir236Landing:
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
    case kUnused109:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            m_playVoice = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8) {
                if (m_patternVar1 > 1) {
                    m_patternVar1--;
                    frame = 1;
                } else {
                    pattern = kStand;
                    StartPattern();
                    FaceOpponent();
                }
            }
        }
        break;
    case kUnused10a:
        if (frame == 0 && timer == 0) {
            vx = -0.9;
            vy = -2.1;
            ay = 0.04;
            m_playVoice = 1;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_shotOrder = 0;
        }
        if (frame == 5 && timer == 0 && m_patternVar1 == 0) {
            m_playSound = 32;
            m_shotState = 1;
            effect.keep = 1;
            effect.type = 0x19b;
            effect.x = (double)((int)x + facing * 33);
            effect.y = (double)((int)y - 56);
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
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_shotOrder = 0;
        }
        if (frame == 4 && timer == 0 && m_patternVar1 == 0) {
            m_playSound = 32;
            m_shotState = 1;
            effect.keep = 1;
            effect.type = 0x19c;
            effect.x = (double)((int)x + facing * 33);
            effect.y = (double)((int)y - 56);
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
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_shotOrder = 0;
            StopMoving();
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
        if (frame == 5 && timer == 0 && m_patternVar1 == 0) {
            m_playSound = 32;
            m_shotState = 1;
            effect.keep = 1;
            effect.type = 0x19d;
            effect.x = (double)((int)x + facing * 33);
            effect.y = (double)((int)y - 56);
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
            }
        }
        break;
    case k412A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 2;
        }
        if (frame > 3 && frame < 6) {
            vy = vy + ay;
            if (y < 0.0) {
                TriggerObjectsNear((int)x - facing * 34, (int)y - 66, 39, 42);
            }
            if (vy + y > 0.0) {
                y = 0.0;
                frame = 6;
                timer = 0;
                StopMoving();
                m_playSound = 35;
                TriggerObjectsNear((int)x + facing * 39, (int)y - 35, 70, 75);
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.5;
                vy = -1.4;
                ay = 0.09;
            }
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k412B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 2;
        }
        if (frame > 3 && frame < 6) {
            vy = vy + ay;
            if (y < 0.0) {
                TriggerObjectsNear((int)x - facing * 34, (int)y - 66, 39, 42);
            }
            if (vy + y > 0.0) {
                y = 0.0;
                frame = 6;
                timer = 0;
                StopMoving();
                m_playSound = 35;
                m_bombsPlaced++;
                effect.type = 0x190;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 30);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x19e;
                SpawnObject(&effect);
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 0.8;
                vy = -3.3;
                ay = 0.09;
            }
            if (frame == 3 || frame == 7) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k412C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
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
        if (frame == 2 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 1;
            effect.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
        }
        if (frame > 3 && frame < 6) {
            vy = vy + ay;
            if (y < 0.0) {
                TriggerObjectsNear((int)x - facing * 34, (int)y - 66, 39, 42);
            }
            if (vy + y > 0.0) {
                y = 0.0;
                frame = 6;
                timer = 0;
                StopMoving();
                m_playSound = 35;
                m_hitsLeft = 1;
                m_bombsPlaced++;
                effect.type = 0x190;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 30);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
                effect.type = 0x19e;
                SpawnObject(&effect);
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.8;
                vy = -1.0;
                ay = 0.03;
            }
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir214A:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 50;
            vx = -0.9;
            vy = -1.5;
            ay = 0.05;
            m_playVoice = 1;
            effect.type = 0x190;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir214B:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 50;
            vx = -0.9;
            vy = -1.5;
            ay = 0.05;
            m_playVoice = 1;
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir214C:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 50;
            vx = -0.9;
            vy = -1.5;
            ay = 0.05;
            m_playVoice = 1;
            effect.type = 0x198;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case k236AShotUp:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            m_shotOrder = 1;
            m_playVoice = 4;
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
    case k236BShotDown:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            m_shotOrder = -1;
            m_playVoice = 3;
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
    case k236CShotForward:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_shotOrder = 2;
            m_playVoice = 3;
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
    case k236236Lv1:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
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
        if (frame > 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            pattern = k236236Lv1Hit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            break;
        }
        if (frame > 2 && m_attackResult == 2) {
            timer = 0;
            frame = 11;
            m_attackResult = 0;
        }
        if (frame == 12 && timer == 0) {
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
        }
        if (frame > 10) {
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 2.0;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236Lv2:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
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
        if (frame > 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            pattern = k236236Lv2Hit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            break;
        }
        if (frame > 2 && m_attackResult == 2) {
            timer = 0;
            frame = 19;
            m_attackResult = 0;
        }
        if (frame == 20 && timer == 0) {
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
        }
        if (frame > 18) {
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 2.0;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236Lv3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 1;
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
        if (frame > 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            pattern = k236236Lv3Hit;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            break;
        }
        if (frame > 2 && m_attackResult == 2) {
            timer = 0;
            frame = 19;
            m_attackResult = 0;
        }
        if (frame == 20 && timer == 0) {
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
        }
        if (frame > 18) {
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 2.0;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236Lv1Hit:
        if (frame == 0) {
            (*m_opponent)->m_koDelay = 30000;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = facing * 35 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
            m_patternVar1 = 8;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = kThrownLying2;
            if (facing == 1 && x < 40.0) {
                x = 40.0;
            }
            if (facing == -1 && x > 620.0) {
                x = 620.0;
            }
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
        }
        if (frame < 2) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        } else {
            vx = 0.0;
        }
        unkf2 = 3;
        if (frame == 6 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(100, 980.0);
        }
        if (frame == 9 && timer == 0) {
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 22;
            ShakeScreen(10, 10);
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->m_koDelay = 0;
            DealDamage(2000, 800.0);
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitstop = 180;
        }
        if (frame > 11) {
            (*m_opponent)->pattern = kLyingDown;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
        }
        if (frame > 14) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownLying2;
                if (facing == 1 && x < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-17 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 6 && m_patternVar1 == 0) {
                frame = 7;
            }
            if (frame == 7) {
                if (m_patternVar1 > 0) {
                    frame = frame - 2;
                    m_patternVar1--;
                } else {
                    m_patternVar1 = 20;
                }
            }
            if (frame == 14) {
                vx = -1.0;
                vy = -1.7;
                ay = 0.037;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k236236Lv2Hit:
        if (frame == 0) {
            (*m_opponent)->m_koDelay = 30000;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = facing * 35 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
            m_patternVar1 = 8;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = kThrownLying2;
            if (facing == 1 && x < 40.0) {
                x = 40.0;
            }
            if (facing == -1 && x > 620.0) {
                x = 620.0;
            }
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
        }
        if (frame < 2) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        } else {
            vx = 0.0;
        }
        unkf2 = 3;
        if (frame == 6 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(100, 990.0);
        }
        if (frame == 10 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(100, 990.0);
        }
        if (frame == 15 && timer == 0) {
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 22;
            ShakeScreen(10, 10);
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(2000, 800.0);
            (*m_opponent)->m_koDelay = 0;
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitstop = 180;
        }
        if (frame > 19) {
            (*m_opponent)->pattern = kLyingDown;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
        }
        if (frame > 19) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownLying2;
                if (facing == 1 && x < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-17 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 6 && m_patternVar1 == 0) {
                frame = 7;
            }
            if (frame == 7) {
                if (m_patternVar1 > 0) {
                    frame = frame - 2;
                    m_patternVar1--;
                } else {
                    m_patternVar1 = 20;
                }
            }
            if (frame == 12) {
                if (m_patternVar1 > 0) {
                    frame = frame - 5;
                    m_patternVar1--;
                } else {
                    m_patternVar1 = 3;
                }
            }
            if (frame == 19) {
                vx = -1.0;
                vy = -1.7;
                ay = 0.037;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k236236Lv3Hit:
        m_game->FlashNegative(15);
        if (frame == 0) {
            (*m_opponent)->m_koDelay = 30000;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = facing * 35 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
            m_patternVar1 = 8;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = kThrownLying2;
            if (facing == 1 && x < 40.0) {
                x = 40.0;
            }
            if (facing == -1 && x > 620.0) {
                x = 620.0;
            }
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
        }
        if (frame < 2) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        } else {
            vx = 0.0;
        }
        unkf2 = 3;
        if (frame == 6 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(100, 990.0);
        }
        if (frame == 10 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(100, 990.0);
        }
        if (frame == 15 && timer == 0) {
            (*m_opponent)->m_hitstop = 30;
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(150, 990.0);
        }
        if (frame == 20 && timer == 0) {
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 22;
            ShakeScreen(10, 10);
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(2500, 800.0);
            (*m_opponent)->m_koDelay = 0;
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitstop = 180;
        }
        if (frame > 24) {
            (*m_opponent)->pattern = kLyingDown;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
        }
        if (frame > 24) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownLying2;
                if (facing == 1 && x < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-17 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 6 && m_patternVar1 == 0) {
                frame = 7;
            }
            if (frame == 7) {
                if (m_patternVar1 > 0) {
                    frame = frame - 2;
                    m_patternVar1--;
                } else {
                    m_patternVar1 = 20;
                }
            }
            if (frame == 12) {
                if (m_patternVar1 > 0) {
                    frame = frame - 5;
                    m_patternVar1--;
                } else {
                    m_patternVar1 = 3;
                }
            }
            if (frame == 17 && m_patternVar1 > 0) {
                frame = frame - 5;
                m_patternVar1--;
            }
            if (frame == 24) {
                vx = -1.0;
                vy = -1.7;
                ay = 0.037;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k214214B:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame == 3 && timer == 0) {
            m_playVoice = 1;
            effect.keep = 0;
            effect.type = 0x193;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.movesInFreeze = 1;
            SpawnObject(&effect);
        }
        if (0) {}
        if (0) {}
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
    case k214214A:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame == 3 && timer == 0) {
            m_playVoice = 1;
            effect.keep = 0;
            effect.type = 0x192;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 30);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (0) {}
        if (0) {}
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
    case k214214C:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - (facing << 5));
            effect.y = (double)((int)y - 75);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && timer == 0) {
            m_playVoice = 1;
            effect.keep = 1;
            effect.type = 0x191;
            effect.x = (double)((int)x + facing * 50);
            effect.y = (double)((int)y - 60);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (0) {}
        if (0) {}
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
    case kAir214214B:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x + facing * 23);
            effect.y = (double)((int)y - 30);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.05;
                m_playVoice = 1;
                effect.type = 0x193;
                effect.x = (double)((int)x + facing * 30);
                effect.y = (double)((int)y - 30);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
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
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir214214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x + facing * 23);
            effect.y = (double)((int)y - 30);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.05;
                m_playVoice = 1;
                effect.type = 0x192;
                effect.x = (double)((int)x + facing * 30);
                effect.y = (double)((int)y - 30);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
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
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kAir214214C:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 23);
            effect.y = (double)((int)y - 30);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.05;
                m_playVoice = 1;
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 30);
                effect.y = (double)((int)y - 30);
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
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
            if (frame >= frameCount) {
                frame = 1;
            }
        }
        break;
    case kLv4:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (m_patternVar2 == 45) {
            effect.keep = 1;
            effect.type = 0x1bf;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.movesInFreeze = 1;
            SpawnObject(&effect);
        }
        m_patternVar2++;
        if (frame == 6 && timer == 0) {
            m_freezeTime = 160;
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
        if (frame == 7 && timer == 0) {
            m_playVoice = 0;
            m_game->FlashWhite(20, 15, 10);
            m_freezeTime = 300;
        }
        if (frame == 8 && timer == 0) {
            if (m_patternVar3 == 0) {
                m_freezeTime = 1200;
                FillBackground(177, 3);
                effect.keep = 1;
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 30);
                effect.y = (double)((int)y - 30);
                effect.facing = facing;
                effect.scale = 0;
                effect.layer = 0;
                effect.movesInFreeze = 1;
                m_playVoice = 2;
                SpawnObject(&effect);
            }
            if (m_patternVar3 == 5) {
                (*m_opponent)->pattern = kHitAir;
                (*m_opponent)->m_noAirRecovery = 1;
                (*m_opponent)->StartPattern();
            }
            m_patternVar3++;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && m_patternVar1 == 0) {
                frame = frame - 2;
            }
            if (frame == 4 && m_patternVar1 == 1) {
                frame = frame - 2;
            }
            if (frame == 6 && m_patternVar1 < 12) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 10 && m_patternVar1 < 24) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                m_lv4Time = 1200;
                FillBackground(177, 3);
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k6413Lv1:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 115);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(10, 5);
            effect.type = 0x1c2;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 55);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c5;
            effect.keep = 0;
            SpawnObject(&effect);
            m_keepBombs = 1;
            TriggerObjectsNear((int)x, (int)y, 1000, 1000);
            m_playVoice = 1;
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
    case k6413Lv2:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 115);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(10, 5);
            effect.type = 0x1c3;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 55);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c5;
            effect.keep = 0;
            SpawnObject(&effect);
            m_keepBombs = 1;
            TriggerObjectsNear((int)x, (int)y, 1000, 1000);
            m_playVoice = 1;
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
    case k6413Lv3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 115);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(10, 5);
            effect.type = 0x1c4;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 55);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c5;
            effect.keep = 0;
            SpawnObject(&effect);
            m_keepBombs = 1;
            TriggerObjectsNear((int)x, (int)y, 1000, 1000);
            m_playVoice = 1;
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
    }
}
