// CMishio::UpdatePattern (0x530bc0-0x54647f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMishio's
// .rdata, which starts with its constructor's folder name (mishio.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMishio::UpdatePattern()
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
        vx = 0.4;
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
        vx = -0.4;
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
            ay = 0.04;
            vy = -2.45;
            if (m_dashMomentum == 1) {
                vx = 0.3;
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
            ay = 0.04;
            vy = -2.45;
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
            ay = 0.04;
            vy = -2.45;
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
        ay = 0.04;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.45;
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
        ay = 0.04;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.45;
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
        ay = 0.04;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.45;
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
            if (frame == 15) {
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
        if (frame == 5 && timer == 0) {
            vx = 1.0;
        }
        m_dashMomentum = 1;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame > 0 && frame < 3) {
            vy = vy + ay;
        }
        if (frame > 0 && vy + y >= 0.0 && m_patternVar1 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            m_patternVar1++;
            m_playSound = 9;
            frame = 3;
            timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                vx = -1.7;
                vy = -1.0;
                ay = 0.04;
            }
            if (frame == 3) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 39) {
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
        if (y + vy > 0.0 && frame < 10) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 10;
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
            if (frame == 10) {
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
                pattern = kCrouch;
                if (m_inputY != 1) {
                    pattern = kStandUp;
                }
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
        if (frame == 2 && timer == 0) {
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
    case k5C:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
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
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 35;
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
            if (frame < 3) {
                m_attackResult = 0;
            }
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
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
                pattern = kStandUp;
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
        if (frame == 1 && timer == 0) {
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
            if (frame < 3) {
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
            if (m_hitsLeft > 0) {
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
            vx = 0.0;
            vy = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.035;
        }
        if (y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 12;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                vx = 1.0;
                vy = -1.3;
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
    case k6C:
        if (m_dashMomentum == 0) {
            vx = 0.0;
            vy = 0.0;
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
        if (vx > 0.0 && m_dashMomentum == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3 && timer == 0) {
                m_gauge = m_gauge + 30;
                m_playSound = 20;
                m_hitsLeft = 1;
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
            pattern = kAirDiveBounce;
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
    case kAirDiveBounce:
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
    case kThrow:
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            m_cornerPushback = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = kThrowConnected;
            (*m_opponent)->pattern = kThrownStandHigh2;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 36);
            effect.y = (double)((int)y - 46);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
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
    case kThrowConnected:
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 1) {
                (*m_opponent)->x = facing * 30 + x;
                (*m_opponent)->pattern = kThrownStandLow2;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 13 + x;
                (*m_opponent)->pattern = kThrownStandLow2;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                if ((char)AtScreenEdge() != 0) {
                    x = facing * 5 + x;
                }
                (*m_opponent)->x = x - facing * 5;
                (*m_opponent)->pattern = kHitStandHighHeavy;
                (*m_opponent)->StartPattern();
                (*m_opponent)->facing = -(*m_opponent)->facing;
            }
            if (frame == 5) {
                facing = -facing;
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
        vx -= 0.02;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.0;
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
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kDashC:
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
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            if (frame < 3) {
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
        vx -= 0.02;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.0;
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
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kDash2B:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            if (frame < 3) {
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
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            effect.type = 0;
            effect.x = (double)((int)x + (facing << 5));
            effect.y = (double)((int)y - 57);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            frame = 0;
            timer = 0;
            pattern = kAirThrowConnected;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 29 + x;
            (*m_opponent)->y = y - 73.0;
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
    case kAirThrowConnected:
        m_hideOffscreenMarker = 2;
        if (frame < 6) {
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        if (frame > 6) {
            (*m_opponent)->FocusCameraY(50, 3);
        }
        if (frame == 4 && timer == 0) {
            DealDamage(1150, 500.0);
            (*m_opponent)->StartPattern();
        }
        if (frame > 1 && frame < 4) {
            vy += 0.05;
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = facing * 17 + x;
            (*m_opponent)->y = y + 11.0;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                frame = 4;
                timer = 0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x - facing * 6;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kKnockdown;
                effect.type = 0;
                effect.x = (double)((int)x - facing * 9);
                effect.y = (double)((int)y + 4);
                effect.scale = 2;
                effect.layer = 1;
                effect.sound = 2;
                m_game->CreateEffect((EffectDesc*)&effect);
                break;
            }
        }
        if (frame > 6 && y < 0.0) {
            vy += 0.035;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                timer = 0;
                frame = 16;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownDoubledOverInverted;
                (*m_opponent)->y = y - 22.0;
                (*m_opponent)->x = facing * 39 + x;
            }
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame == 6) {
                facing = -facing;
            }
            if (frame == 7) {
                vx = -1.5;
                vy = -1.0;
            }
            if (frame == 16) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_attackResult > 0 && m_powerUp == 0) {
                    if ((WORD)Random(0, 1000) < 500) {
                        m_powerUp = 1;
                    } else {
                        m_powerUp = 2;
                    }
                }
                StartPattern();
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_attackResult > 0 && m_powerUp == 0) {
                    if ((WORD)Random(0, 1000) < 500) {
                        m_powerUp = 1;
                    } else {
                        m_powerUp = 2;
                    }
                }
                StartPattern();
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_hitsLeft = 2;
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
        }
        if (m_attackResult > 0) {
            m_patternVar1 = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 11) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame == 12) {
                m_playVoice = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_patternVar1 > 0 && m_powerUp == 0) {
                    if ((WORD)Random(0, 1000) < 500) {
                        m_powerUp = 1;
                    } else {
                        m_powerUp = 2;
                    }
                }
                StartPattern();
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 6;
        }
        if (vx > 0.0) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 10 || frame == 13 || frame == 16 || frame == 19) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                effect.type = 0x1f;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                vx = 3.0;
            }
            if (frame == 7 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 7 && m_attackResult == 0) {
                frame = 22;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 4;
        }
        if ((frame == 6 || frame == 9 || frame == 12 || frame == 15) && timer == 0) {
            m_playSound = 21;
            m_gauge = m_gauge + 5;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 6 || frame == 9 || frame == 12 || frame == 15) {
                m_attackResult = 0;
            }
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
            m_dashMomentum = 0;
            StopMoving();
            m_hitsLeft = 99;
        }
        if (vx > 0.0) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 10 || frame == 13 || frame == 16 || frame == 19 || frame == 22 || frame == 25 || frame == 28 || frame == 31) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                effect.type = 0x1f;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                vx = 3.2;
            }
            if (frame == 7 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
                m_attackResult = 0;
                break;
            }
            if (frame == 7 && m_attackResult == 0) {
                frame = 31;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 4 && frame < 7 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && timer == 0) {
                facing = -facing;
            }
            if (frame == 5 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_gauge = m_gauge + 20;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x194;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                frame = 0;
                pattern = k214Recovery;
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 4 && frame < 7 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_gauge = m_gauge + 20;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x194;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                frame = 0;
                pattern = k214Recovery;
                StartPattern();
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 4 && frame < 7 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-90.0, 2.2);
                m_gauge = m_gauge + 20;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x193;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 7 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                frame = 0;
                pattern = k214Recovery;
                StartPattern();
            }
        }
        break;
    case kAir214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(0.0, 2.2);
                m_gauge = m_gauge + 20;
                effect.type = 0x195;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 5 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214Recovery2;
                frame = 0;
            }
        }
        break;
    case kAir214B:
        if (frame > 3 && frame < 6 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = k214Recovery2;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(45.0, 2.2);
                m_gauge = m_gauge + 20;
                effect.type = 0x196;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 6 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214Recovery;
                frame = 0;
            }
        }
        break;
    case kAir214C:
        if (frame > 3 && frame < 6 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = k214Recovery2;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(90.0, 2.2);
                m_gauge = m_gauge + 20;
                effect.type = 0x197;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 6 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214Recovery;
                frame = 0;
            }
        }
        break;
    case k214Follow8:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-90.0, 2.2);
                m_gauge = m_gauge + 5;
                effect.type = 0x193;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214FollowRecovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214Follow9:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_gauge = m_gauge + 5;
                effect.type = 0x194;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214FollowRecovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214Follow6:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(0.0, 2.2);
                m_gauge = m_gauge + 5;
                effect.type = 0x195;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214FollowRecovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214Follow3:
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = k214FollowRecovery;
            break;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(45.0, 2.2);
                m_gauge = m_gauge + 5;
                effect.type = 0x196;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214FollowRecovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214Follow2:
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = k214FollowRecovery;
            break;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(90.0, 2.2);
                m_gauge = m_gauge + 5;
                effect.type = 0x197;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214FollowRecovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214FollowRecovery:
        if (m_patternVar3 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            m_patternVar3++;
        }
        if (m_patternVar2 == 0 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
                FaceOpponent();
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k412A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 7 && timer == 0) {
            m_playVoice = 1;
            effect.type = 0x190;
            effect.x = (double)((int)x + (facing << 6));
            effect.y = (double)(int)y;
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            effect.keep = 1;
            SpawnObject(&effect);
            m_shotOut = 1;
            m_gauge = m_gauge + 25;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case k412B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 7 && timer == 0) {
            m_playVoice = 1;
            effect.type = 0x191;
            effect.x = (double)((int)x + (facing << 6));
            effect.y = (double)(int)y;
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            effect.keep = 1;
            SpawnObject(&effect);
            m_shotOut = 1;
            m_gauge = m_gauge + 25;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k412C:
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
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 7 && timer == 0) {
            m_playVoice = 2;
            effect.type = 0x192;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 60);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            effect.keep = 1;
            SpawnObject(&effect);
            m_shotOut = 1;
            m_gauge = m_gauge + 25;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k22A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 5 && timer == 0) {
            effect.type = 0x198;
            if (x - (*m_opponent)->x < 150.0 && x - (*m_opponent)->x > -150.0) {
                effect.x = (*m_opponent)->x;
            } else {
                if ((*m_opponent)->x > x) {
                    effect.x = x + 150.0;
                }
                if ((*m_opponent)->x < x) {
                    effect.x = x - 150.0;
                }
            }
            effect.y = (double)(int)y;
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            effect.keep = 1;
            SpawnObject(&effect);
            m_fieldOut = 1;
            m_gauge = m_gauge + 25;
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 10 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k22B:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 5 && timer == 0) {
            effect.type = 0x198;
            if (x - (*m_opponent)->x > 150.0 || x - (*m_opponent)->x < -150.0) {
                effect.x = (*m_opponent)->x;
            } else {
                if ((*m_opponent)->x > x) {
                    effect.x = x + 150.0;
                }
                if ((*m_opponent)->x < x) {
                    effect.x = x - 150.0;
                }
            }
            effect.y = (double)(int)y;
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            effect.keep = 1;
            SpawnObject(&effect);
            m_fieldOut = 1;
            m_gauge = m_gauge + 25;
            m_playVoice = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 10 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k623APower1:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                effect.type = 0x1b5;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 3) {
                m_playVoice = 5;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
                StartPattern();
            }
        }
        break;
    case k623BPower1:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.04500000178813934;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 5;
                vx = 2.5;
                effect.type = 0x1b5;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
                StartPattern();
            }
        }
        break;
    case k623CPower1:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_hitsLeft = 1;
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
            vx = 1.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (m_attackResult > 0) {
            m_patternVar1 = 1;
        }
        if (vx > 0.0) {
            vx -= 0.02500000037252903;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 11) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 5;
                effect.type = 0x1bc;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 9) {
                m_hitsLeft = 1;
                m_attackResult = 0;
                m_playVoice = 5;
                effect.type = 0x1b5;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
                StartPattern();
            }
        }
        break;
    case k623APower2:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 4;
                effect.type = 0x1b6;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1b8;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
                StartPattern();
            }
        }
        break;
    case k623BPower2:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.04500000178813934;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 4;
                effect.type = 0x1b6;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1b8;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1ba;
                effect.keep = 1;
                effect.x = (double)((int)x + facing * 90);
                effect.y = (double)((int)y - 60);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
                StartPattern();
            }
        }
        break;
    case k623CPower2:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_hitsLeft = 1;
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
            vy = 0.0;
            ax = 0.0;
        }
        if (m_attackResult > 0) {
            m_patternVar1 = 1;
        }
        if (vx > 0.0) {
            vx -= 0.02500000037252903;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 11) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 4;
                effect.type = 0x1bd;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1b8;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 9) {
                m_hitsLeft = 1;
                m_attackResult = 0;
                m_playVoice = 4;
                effect.type = 0x1b6;
                effect.x = (double)((int)x + facing * 38);
                effect.y = (double)((int)y - 40);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1b8;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
                StartPattern();
            }
        }
        break;
    case k623APower3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623BPower3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_patternVar1 = 5;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.04500000178813934;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
                vx = 2.5;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623CPower3:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_gauge = m_gauge + 45;
            m_hitsLeft = 2;
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
            vy = 0.0;
            ax = 0.0;
        }
        if (m_attackResult > 0) {
            m_patternVar1 = 1;
        }
        if (vx > 0.0) {
            vx -= 0.02500000037252903;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 11) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame == 12) {
                m_playVoice = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214Recovery:
        if (m_patternVar3 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            m_patternVar3++;
        }
        if (m_patternVar2 == 0 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214Recovery2:
        if (m_patternVar3 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            m_patternVar3++;
        }
        if (m_patternVar2 == 0 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow8;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow9;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow6;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214Follow2;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    m_patternVar2++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214Follow3;
                    m_patternVar2++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k236236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 99;
            m_superCounter = 0;
            StopMoving();
        }
        if (vx > 0.0) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3 && m_superCounter == 0) {
            (*m_opponent)->m_hitstop = 180;
            m_hitstop = 90;
            m_superCounter++;
        }
        if (m_attackResult == 3 && (*m_opponent)->y < 0.0 && frame < 10) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHeavy;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 13 || frame == 16 || frame == 19 || frame == 22 || frame == 25 || frame == 28 || frame == 31) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                effect.type = 0x1f;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                vx = 3.5;
            }
            if (frame == 10 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_attackResult != 3) {
                frame = 34;
                break;
            }
            if (frame == 20 && m_patternVar2 < 2) {
                frame = 11;
                m_patternVar2++;
            }
            if (frame == 31 && m_patternVar3 < 3) {
                frame = 22;
                m_patternVar3++;
                m_attackResult = 0;
            }
            if (frame >= frameCount || frame == 40) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k236236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 99;
            m_superCounter = 0;
            StopMoving();
        }
        if (vx > 0.0) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3 && m_superCounter == 0) {
            (*m_opponent)->m_hitstop = 180;
            m_hitstop = 90;
            m_superCounter++;
        }
        if (m_attackResult == 3 && (*m_opponent)->y < 0.0 && frame < 10) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHeavy;
            break;
        }
        if (frame > 21 && frame < 31 && (WORD)Random(0, 100) < 10) {
            effect.type = 0x19a;
            effect.x = (double)((int)x + ((WORD)Random(0, 110) - 20) * facing);
            effect.y = (double)((int)y - (WORD)Random(0, 90));
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 13 || frame == 16 || frame == 19 || frame == 22 || frame == 25 || frame == 28 || frame == 31) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                effect.type = 0x1f;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                vx = 4.0;
            }
            if (frame == 10 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_attackResult != 3) {
                frame = 40;
                break;
            }
            if (frame == 20 && m_patternVar2 < 3) {
                frame = 11;
                m_patternVar2++;
            }
            if (frame == 31 && m_patternVar3 < 4) {
                frame = 22;
                m_patternVar3++;
                m_attackResult = 0;
            }
            if (frame >= frameCount || frame == 40) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k236236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 99;
            m_superCounter = 0;
            m_playSound = 37;
            StopMoving();
        }
        m_game->FlashNegative(15);
        if (vx > 0.0) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3 && m_superCounter == 0) {
            (*m_opponent)->m_hitstop = 180;
            m_hitstop = 90;
            m_superCounter++;
            m_game->FlashNegative(93);
        }
        if (m_attackResult == 3 && (*m_opponent)->y < 0.0 && frame < 10) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHeavy;
            break;
        }
        if (frame > 21 && frame < 31 && (WORD)Random(0, 100) < 10) {
            effect.type = 0x19a;
            effect.x = (double)((int)x + ((WORD)Random(0, 110) - 20) * facing);
            effect.y = (double)((int)y - (WORD)Random(0, 90));
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame > 21 && frame < 31 && (WORD)Random(0, 100) < 5) {
            effect.type = 0x19b;
            effect.x = (double)((int)x + ((WORD)Random(0, 110) - 20) * facing);
            effect.y = (double)((int)y - (WORD)Random(0, 90));
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 13 || frame == 16 || frame == 19 || frame == 22 || frame == 25 || frame == 28 || frame == 31) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                effect.type = 0x1f;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                vx = 5.0;
            }
            if (frame == 10 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_attackResult != 3) {
                frame = 40;
                break;
            }
            if (frame == 20 && m_patternVar2 < 3) {
                frame = 11;
                m_patternVar2++;
            }
            if (frame == 31 && m_patternVar3 < 8) {
                frame = 22;
                m_patternVar3++;
                m_attackResult = 0;
            }
            if (frame >= frameCount || frame == 40) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            m_superLevel = 1;
            m_superCounter = 0;
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 8 && frame < 11 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && timer == 0) {
                m_playVoice = 10;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 11 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                frame = 0;
                pattern = k214214Recovery;
                StartPattern();
            }
        }
        break;
    case k214214B:
        if (frame == 0 && timer == 0) {
            m_superLevel = 2;
            m_superCounter = 0;
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 8 && frame < 11 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && timer == 0) {
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_playVoice = 10;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 11 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                frame = 0;
                pattern = k214214Recovery;
                StartPattern();
            }
        }
        break;
    case k214214C:
        m_game->FlashNegative(15);
        if (frame == 0 && timer == 0) {
            m_superLevel = 3;
            m_superCounter = 0;
            StopMoving();
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 8 && frame < 11 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && timer == 0) {
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_invulTime = 45;
                m_playVoice = 10;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 11 && m_patternVar1 < 4) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                frame = 0;
                pattern = k214214Recovery;
                StartPattern();
            }
        }
        break;
    case k214214Follow8:
        if (m_superLevel == 3) {
            m_game->FlashNegative(15);
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 6 && frame < 9 && m_superCounter < m_superLevel + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 10;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-90.0, 2.2);
                effect.type = 0x19c;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214214Recovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214214Follow9:
        if (m_superLevel == 3) {
            m_game->FlashNegative(15);
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 6 && frame < 9 && m_superCounter < m_superLevel + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 10;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214214Recovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214214Follow6:
        if (m_superLevel == 3) {
            m_game->FlashNegative(15);
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 6 && frame < 9 && m_superCounter < m_superLevel + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 10;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(0.0, 2.2);
                effect.type = 0x19d;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214214Recovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214214Follow3:
        if (m_superLevel == 3) {
            m_game->FlashNegative(15);
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = k214214Recovery;
            break;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 7 && frame < 10 && m_superCounter < m_superLevel + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 10;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(45.0, 2.2);
                effect.type = 0x19f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.keep = 1;
                effect.layer = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214214Recovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214214Follow2:
        if (m_superLevel == 3) {
            m_game->FlashNegative(15);
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = k214214Recovery;
            break;
        }
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 7 && frame < 10 && m_superCounter < m_superLevel + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 10;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(90.0, 2.2);
                effect.type = 0x1a0;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.layer = 1;
                effect.keep = 1;
                effect.scale = 2;
                SpawnObject(&effect);
            }
            if (frame == 4 && m_patternVar1 < 0) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame == 10 && m_patternVar1 < 4) {
                m_patternVar1++;
                frame = frame - 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = k214214Recovery;
                frame = 0;
                m_patternVar2++;
            }
        }
        break;
    case k214214Recovery:
        if (m_superLevel == 3) {
            m_game->FlashNegative(15);
        }
        if (m_patternVar3 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            m_patternVar3++;
        }
        if (m_superCounter < m_superLevel + 1 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow8;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow9;
                    facing = -facing;
                    m_superCounter++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow6;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = k214214Follow2;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = k214214Follow3;
                    m_superCounter++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                if (m_inputY == 1) {
                    pattern = kCrouch;
                }
                StartPattern();
                FaceOpponent();
                if (m_powerUp == 1) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k641236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x + facing * 67);
            effect.y = (double)((int)y - 41);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 6) {
                m_playVoice = 6;
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 15);
                effect.y = (double)((int)y - 148);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1ad;
                effect.x = (double)((int)x + facing * 15);
                effect.y = (double)((int)y - 148);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 10) {
                if (m_patternVar1 > 8) {
                    effect.type = 0x1a5;
                    effect.x = (double)((int)x + facing * 15);
                    effect.y = (double)((int)y - 148);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    break;
                }
                if (m_holdA > 0) {
                    m_patternVar1++;
                    frame = frame - 4;
                }
            }
            if (frame == 13) {
                m_playVoice = 8;
            }
            if (frame == 15) {
                effect.type = 0x1a2;
                if (m_patternVar1 > 8) {
                    effect.type = 0x1ae;
                }
                effect.x = (double)((int)x + facing * 104);
                effect.y = (double)((int)y - 50);
                if (m_patternVar2 == 1) {
                    effect.y = (double)((int)y - 60);
                }
                if (m_patternVar2 == 2) {
                    effect.y = (double)((int)y - 40);
                }
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 16 && m_patternVar2 < 2) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame == 18 && m_patternVar2 < 6) {
                m_patternVar2++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k641236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 67);
            effect.y = (double)((int)y - 41);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 6) {
                m_invulTime = 15;
                m_playVoice = 6;
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 15);
                effect.y = (double)((int)y - 148);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1ad;
                effect.x = (double)((int)x + facing * 15);
                effect.y = (double)((int)y - 148);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 10) {
                if (m_patternVar1 > 8) {
                    effect.type = 0x1a5;
                    effect.x = (double)((int)x + facing * 15);
                    effect.y = (double)((int)y - 148);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    break;
                }
                if (m_holdB > 0) {
                    m_patternVar1++;
                    frame = frame - 4;
                }
            }
            if (frame == 13) {
                m_playVoice = 8;
            }
            if (frame == 15) {
                effect.type = 0x1a3;
                if (m_patternVar1 > 8) {
                    effect.type = 0x1af;
                }
                effect.x = (double)((int)x + facing * 104);
                effect.y = (double)((int)y - 50);
                if (m_patternVar2 == 1) {
                    effect.y = (double)((int)y - 60);
                }
                if (m_patternVar2 == 2) {
                    effect.y = (double)((int)y - 40);
                }
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 16 && m_patternVar2 < 2) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame == 18 && m_patternVar2 < 6) {
                m_patternVar2++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case k641236C:
        if (frame > 2) {
            m_game->FlashNegative(15);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 67);
            effect.y = (double)((int)y - 41);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 6) {
                m_invulTime = 30;
                m_playVoice = 6;
                effect.type = 0x1a1;
                effect.x = (double)((int)x + facing * 15);
                effect.y = (double)((int)y - 148);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1ad;
                effect.x = (double)((int)x + facing * 15);
                effect.y = (double)((int)y - 148);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 10) {
                if (m_patternVar1 > 8) {
                    effect.type = 0x1a5;
                    effect.x = (double)((int)x + facing * 15);
                    effect.y = (double)((int)y - 148);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    break;
                }
                if (m_holdC > 0) {
                    m_patternVar1++;
                    frame = frame - 4;
                }
            }
            if (frame == 13) {
                m_playVoice = 8;
            }
            if (frame == 15) {
                effect.type = 0x1a4;
                if (m_patternVar1 > 8) {
                    effect.type = 0x1b0;
                }
                effect.x = (double)((int)x + facing * 104);
                effect.y = (double)((int)y - 50);
                if (m_patternVar2 == 1) {
                    effect.y = (double)((int)y - 60);
                }
                if (m_patternVar2 == 2) {
                    effect.y = (double)((int)y - 40);
                }
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 16 && m_patternVar2 < 2) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame == 18 && m_patternVar2 < 6) {
                m_patternVar2++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case kAir236236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0 && m_patternVar3 == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 31);
            effect.y = (double)((int)y - 97);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
            m_patternVar3++;
        }
        if (frame > 9 && y < 0.0) {
            vy += 0.02;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 16;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 5 && m_patternVar1 < 5) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame == 10) {
                m_playVoice = 9;
                vx = -1.3;
                vy = -0.8;
                effect.type = 0x1a6;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a5;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 16) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case kAir236236B:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0 && m_patternVar3 == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 31);
            effect.y = (double)((int)y - 97);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
            m_patternVar3++;
        }
        if (frame > 9 && y < 0.0) {
            vy += 0.02;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 16;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 5 && m_patternVar1 < 5) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame == 10) {
                m_playVoice = 9;
                vx = -1.3;
                vy = -0.8;
                effect.type = 0x1a8;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a5;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 14 && m_patternVar2 < 2) {
                m_playVoice = 9;
                m_patternVar2++;
                frame = frame - 4;
                if (m_patternVar2 == 1) {
                    effect.type = 0x1b1;
                }
                if (m_patternVar2 == 2) {
                    effect.type = 0x1a7;
                }
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a5;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 16) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case kAir236236C:
        if (frame > 2) {
            m_game->FlashNegative(3);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_dashMomentum = 0;
        }
        if (frame == 2 && timer == 0 && m_patternVar3 == 0) {
            m_dashMomentum = 0;
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 31);
            effect.y = (double)((int)y - 97);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
            StopMoving();
            m_patternVar3++;
        }
        if (frame > 9 && y < 0.0) {
            vy += 0.02;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 16;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 5 && m_patternVar1 < 5) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame == 10) {
                m_playVoice = 9;
                vx = -1.3;
                vy = -0.8;
                effect.type = 0x1ac;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a5;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 14 && m_patternVar2 < 4) {
                m_playVoice = 9;
                m_patternVar2++;
                frame = frame - 4;
                if (m_patternVar2 == 1) {
                    effect.type = 0x1ab;
                }
                if (m_patternVar2 == 2) {
                    effect.type = 0x1b2;
                }
                if (m_patternVar2 == 3) {
                    effect.type = 0x1aa;
                }
                if (m_patternVar2 == 4) {
                    effect.type = 0x1a9;
                }
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1a5;
                effect.x = (double)((int)x + facing * 50);
                effect.y = (double)((int)y - 32);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 16) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
                if (m_powerUp == 2) {
                    m_powerUp = 0;
                }
            }
        }
        break;
    case kLv4:
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            FocusCameraY(50, 3);
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 13);
            effect.y = (double)((int)y - 52);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x1b4;
            effect.x = (double)((int)x + facing * 13);
            effect.y = (double)((int)y - 52);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.facing = facing;
            effect.movesInFreeze = 1;
            SpawnObject(&effect);
        }
        if (frame == 7 && timer == 0) {
            m_playVoice = 11;
            ShakeScreen(5, 0);
            m_powerUp = 3;
            m_powerUpTime = 4500;
            effect.type = 0x1b3;
            effect.x = (double)((int)x + facing * 5);
            effect.y = (double)((int)y - 45);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1ad;
            effect.x = (double)((int)x + facing * 5);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1ad;
            effect.x = (double)((int)x + facing * 45);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1ad;
            effect.x = (double)((int)x - facing * 35);
            effect.y = (double)(int)y;
            effect.scale = 2;
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
            if (frame == 10 && m_patternVar1 < 5) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
    }
}
