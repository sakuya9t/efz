// CMizukaB::UpdatePattern (0x4c04b0-0x4d284f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMizukaB's
// .rdata, which starts with its constructor's folder name (mizukab.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMizukaB::UpdatePattern()
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
        m_drawMode = 0;
        m_dashMomentum = 0;
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
        m_drawMode = 0;
        vx = 0.8;
        vy = 0.0;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        m_drawMode = 0;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        vy = vy + ay;
        m_dashMomentum = 0;
        if (ay == 0.0) {
            ay = 0.035;
        }
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
        m_drawMode = 0;
        vx = 0.0;
        vy = 0.0;
        m_dashMomentum = 0;
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
        ay = 0.043;
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 0.0;
            m_dashMomentum = 0;
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
        ay = 0.043;
        m_drawMode = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 1.0;
            m_dashMomentum = 0;
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
    case 0x14:
        m_drawMode = 0;
        vy = vy + ay;
        m_dashMomentum = 0;
        if (ay == 0.0) {
            ay = 0.035;
        }
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                frame = 0;
            }
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                frame = 0;
            }
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
        m_drawMode = 0;
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
                if (m_command == kCmd22D && m_gauge >= 1000) {
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
        m_drawMode = 0;
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
        m_drawMode = 0;
        if (m_hp > 0 && timer > 99 && frame == 0) {
            pattern = kWakeUp;
            StartPattern();
            m_dashMomentum = 0;
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
        m_dashMomentum = 0;
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
            if (m_flying > 0) {
                pattern = 0xb3;
            }
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
        if (frame == 3 && timer == 0) {
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
            if (frame == 18) {
                ay = 0.035;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 8;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 42) {
            pattern = kDashStop;
            m_drawMode = 1;
            StartPattern();
        }
        if (m_inputX != facing && m_patternVar2 >= 24) {
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
        if (vy + y > 0.0 && frame < 12) {
            StopMoving();
            timer = 0;
            frame = 12;
            y = 0.0;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame == 12) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
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
        if (m_inputX != facing && m_patternVar1 >= 48) {
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
            m_flying = 0;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_drawMode = 0;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                effect.type = 0x1b9;
                effect.x = (double)((int)x - facing * 40);
                effect.y = (double)((int)y - 33);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
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
            effect.type = 0x190;
            effect.x = (double)((int)x - facing * 21);
            effect.y = (double)((int)y - 31);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
            effect.type = 0x191;
            effect.x = (double)((int)x - facing * 36);
            effect.y = (double)((int)y - 53);
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
            if (frame >= frameCount) {
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
            effect.type = 3;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playVoice = 10;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 35;
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
            m_playSound = 21;
            m_hitsLeft = 1;
            effect.type = 0x1ba;
            effect.x = (double)((int)x - facing * 40);
            effect.y = (double)((int)y - 10);
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
            effect.type = 0x192;
            effect.x = (double)((int)x - facing * 26);
            effect.y = (double)((int)y - 16);
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
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            vx = 2.5;
            m_patternVar1++;
        }
        if (vx > 0.0) {
            vx -= 0.036;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && vx > 0.6) {
                frame = 2;
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
            m_playSound = 21;
            m_hitsLeft = 1;
            effect.type = 0x1bb;
            effect.x = (double)((int)x - facing * 7);
            effect.y = (double)((int)y - 47);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            m_flying = 0;
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 2;
            effect.type = 0x194;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 72);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kLand;
            m_flying = 0;
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
            m_gauge = m_gauge + 30;
            m_playSound = 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                effect.type = 0x195;
                effect.x = (double)((int)x + facing * 4);
                effect.y = (double)((int)y + 5);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 8 && m_patternVar1 < 2) {
                frame = frame - 3;
                m_patternVar1++;
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 30;
            m_playSound = 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                effect.type = 0x1cc;
                effect.x = (double)((int)x + facing * 55);
                effect.y = (double)((int)y - 44);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
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
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
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
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.sound = 7;
            m_game->CreateEffect((EffectDesc*)&effect);
            pattern = kUnusedAirDiveLanding;
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
    case kUnusedAirDiveRebound:
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
    case kUnusedAirDiveLanding:
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
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 42);
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
            effect.type = 0x1c8;
            effect.x = (double)((int)(*m_opponent)->x - facing * 80);
            effect.y = 0.0;
            effect.scale = 0;
            effect.layer = 0;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c9;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = 0.0;
            effect.scale = 0;
            effect.layer = 0;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1ca;
            effect.x = (double)((int)(*m_opponent)->x + facing * 80);
            effect.y = 0.0;
            effect.scale = 0;
            effect.layer = 0;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 3) {
            FaceOpponent();
        }
        if ((*m_opponent)->pattern == kHitAirWallBounce && frame == 3) {
            timer = 0;
            frame++;
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
            m_gauge = m_gauge + 15;
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                effect.type = 0x1b9;
                effect.x = (double)((int)x - facing * 40);
                effect.y = (double)((int)y - 33);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_drawMode == 1) {
                m_drawMode = 0;
            }
            if (m_drawMode == 3) {
                m_drawMode = 1;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x190;
            effect.x = (double)((int)x - facing * 21);
            effect.y = (double)((int)y - 31);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            effect.type = 3;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playVoice = 10;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= duration) {
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
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 21;
            m_hitsLeft = 1;
            effect.type = 0x1ba;
            effect.x = (double)((int)x - facing * 40);
            effect.y = (double)((int)y - 10);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
            effect.type = 0x192;
            effect.x = (double)((int)x - facing * 26);
            effect.y = (double)((int)y - 16);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (m_drawMode == 3 || m_drawMode == 1) {
            m_invulTime = 2;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            effect.type = 0;
            effect.x = (double)((int)x + facing * 30);
            effect.y = (double)((int)y - 60);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            frame = 0;
            timer = 0;
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownAirRising;
            (*m_opponent)->y = y;
            (*m_opponent)->x = facing * 20 + x;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->y = y - 1.0;
                (*m_opponent)->x = facing * 29 + x;
            }
            if (frame == 4) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirHigh;
                (*m_opponent)->m_hitVx = 3.0;
                (*m_opponent)->m_hitVy = -1.0;
                (*m_opponent)->ay = 0.035;
                DealDamage(1000, 500.0);
                m_comboHits--;
                m_shownHits--;
                (*m_opponent)->m_noAirRecovery = 1;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 9 && timer == 0) {
            effect.type = 0x1a1;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            m_playVoice = 11;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 30;
        }
        if (frame == 10 && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 11;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 18) {
                StartPattern();
                pattern = kStand;
            }
            if (frame == 11) {
                frame = 18;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 9 && timer == 0) {
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 95);
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            m_playVoice = 11;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 30;
        }
        if (frame == 10 && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 11;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 18) {
                StartPattern();
                pattern = kStand;
            }
            if (frame == 11) {
                frame = 18;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_homingOrbHit = 0;
        }
        if (frame == 9 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 9 && timer == 0) {
            effect.type = 0x1a3;
            effect.x = (double)((int)x + facing * 25);
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            m_playVoice = 11;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 30;
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
    case k214A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 60);
            effect.y = 0.0;
            effect.scale = 0;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
            m_gauge = m_gauge + 45;
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
    case k214B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)((int)x + facing * 160);
            effect.y = 0.0;
            effect.scale = 0;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
            m_gauge = m_gauge + 45;
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 6 && timer == 0) {
            effect.type = 0x198;
            effect.x = (double)((int)x + facing * 60);
            effect.y = 0.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 45;
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
    case k41236A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 14 && timer == 0) {
            effect.type = 0x1bd;
            effect.x = (double)((int)x + facing * 13);
            effect.y = (double)((int)y - 58);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1bf;
            effect.x = (double)((int)x + facing * 18);
            effect.y = (double)((int)y - 38);
            SpawnObject(&effect);
            effect.type = 0x1be;
            effect.x = (double)((int)x + facing * 21);
            effect.y = (double)((int)y - 18);
            SpawnObject(&effect);
            m_playVoice = 3;
            m_gauge = m_gauge + 15;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 9 && timer == 0) {
                effect.type = 0x1bc;
                effect.x = (double)((int)x + facing * 31);
                effect.y = (double)((int)y - 51);
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1bf;
                effect.x = (double)((int)x + facing * 26);
                effect.y = (double)((int)y - 31);
                SpawnObject(&effect);
                effect.type = 0x1be;
                effect.x = (double)((int)x + facing * 21);
                effect.y = (double)((int)y - 11);
                SpawnObject(&effect);
                m_playVoice = 3;
                m_gauge = m_gauge + 15;
            }
            if (frame >= frameCount) {
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
        if (frame == 14 && timer == 0) {
            effect.type = 0x1c3;
            effect.x = (double)((int)x + facing * 6);
            effect.y = (double)((int)y - 71);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c1;
            effect.x = (double)((int)x + (facing << 4));
            effect.y = (double)((int)y - 61);
            SpawnObject(&effect);
            effect.type = 0x1c0;
            effect.x = (double)((int)x + facing * 26);
            effect.y = (double)((int)y - 51);
            SpawnObject(&effect);
            m_playVoice = 3;
            m_gauge = m_gauge + 15;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 9 && timer == 0) {
                effect.type = 0x1bc;
                effect.x = (double)((int)x + facing * 31);
                effect.y = (double)((int)y - 51);
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1bf;
                effect.x = (double)((int)x + facing * 26);
                effect.y = (double)((int)y - 31);
                SpawnObject(&effect);
                effect.type = 0x1be;
                effect.x = (double)((int)x + facing * 21);
                effect.y = (double)((int)y - 11);
                SpawnObject(&effect);
                m_playVoice = 3;
                m_gauge = m_gauge + 15;
            }
            if (frame >= frameCount) {
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
        if (frame == 14 && timer == 0) {
            effect.type = 0x1c3;
            effect.x = (double)((int)x + facing * 6);
            effect.y = (double)((int)y - 71);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x1c1;
            effect.x = (double)((int)x + (facing << 4));
            effect.y = (double)((int)y - 61);
            SpawnObject(&effect);
            effect.type = 0x1c0;
            effect.x = (double)((int)x + facing * 26);
            effect.y = (double)((int)y - 51);
            SpawnObject(&effect);
            m_playVoice = 3;
            m_gauge = m_gauge + 15;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 9 && timer == 0) {
                effect.type = 0x1c3;
                effect.x = (double)((int)x + facing * 6);
                effect.y = (double)((int)y - 71);
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x1c2;
                effect.x = (double)((int)x + (facing << 4));
                effect.y = (double)((int)y - 61);
                SpawnObject(&effect);
                effect.type = 0x1c0;
                effect.x = (double)((int)x + facing * 26);
                effect.y = (double)((int)y - 51);
                SpawnObject(&effect);
                m_playVoice = 3;
                m_gauge = m_gauge + 15;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 4 && timer == 0) {
                effect.type = 0x1b5;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_gauge = m_gauge + 45;
            }
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
                if (m_patternVar1 > 1) {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 4 && timer == 0) {
                effect.type = 0x1b5;
                effect.x = (double)(int)x;
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_gauge = m_gauge + 45;
            }
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
                if (m_patternVar1 > 1) {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= frameCount) {
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
            m_hitsLeft = 3;
        }
        if (frame == 5 && timer == 0 && m_patternVar1 < 2) {
            effect.type = 0x1b5;
            effect.x = (double)((int)x + -35 + (WORD)Random(0, 70));
            effect.y = 0.0;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 20;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame == 4 && m_patternVar1 < 2) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x1a1;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            m_playVoice = 11;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 30;
        }
        if (frame == 8 && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 11;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 11) {
                StartPattern();
                pattern = 0x14;
                break;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 95);
            effect.y = (double)((int)y - 38);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            m_playVoice = 11;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 30;
        }
        if (frame == 8 && m_command > 9 && m_command < 0xd) {
            timer = 0;
            frame = 11;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 11) {
                StartPattern();
                pattern = 0x14;
                break;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 7 && timer == 0) {
            effect.type = 0x1a3;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)((int)y - 38);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            m_playVoice = 11;
            m_gauge = m_gauge + 30;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            effect.type = 0x1cb;
            effect.x = (double)((int)x + facing * 38);
            effect.y = (double)((int)y - 55);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            m_playVoice = 11;
            effect.facing = facing;
            SpawnObject(&effect);
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            m_playVoice = 14;
        }
        if (frame == 15 && timer == 0) {
            vx = 13.0;
        }
        if (frame == 16 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 23 && timer == 0) {
            m_drawMode = 0;
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
            m_playVoice = 14;
        }
        if (frame == 15 && timer == 0) {
            vx = -13.0;
        }
        if (frame == 16 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 23 && timer == 0) {
            m_drawMode = 0;
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
            m_playVoice = 14;
        }
        if (frame == 16 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 23 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 16) {
                x = (*m_opponent)->x - facing * 10;
                y = -130.0;
            }
            if (frame >= frameCount) {
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
            m_playVoice = 14;
        }
        if (frame == 15 && timer == 0) {
            vx = 13.0;
        }
        if (frame == 16 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 23 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_playVoice = 14;
        }
        if (frame == 15 && timer == 0) {
            vx = -13.0;
        }
        if (frame == 16 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 23 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
            m_playVoice = 14;
        }
        if (frame == 16 && timer == 0) {
            vx = 0.0;
            m_flying = 0;
        }
        if (frame == 23 && timer == 0) {
            m_drawMode = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 16) {
                x = (*m_opponent)->x - facing * 60;
                y = 0.0;
            }
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2) {
            FocusCameraY(50, 3);
        }
        if (frame == 5 && timer == 0 && m_patternVar2 == 0) {
            effect.keep = 1;
            effect.type = 0x1cd;
            effect.x = 0.0;
            effect.y = 0.0;
            effect.keep = 1;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            SpawnObject(&effect);
            m_playVoice = 16;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 10) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2) {
            FocusCameraY(50, 3);
        }
        if (frame == 5 && timer == 0 && m_patternVar2 == 0) {
            effect.keep = 1;
            effect.type = 0x1ce;
            effect.x = 0.0;
            effect.y = 0.0;
            effect.keep = 1;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            SpawnObject(&effect);
            m_playVoice = 16;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 10) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 2) {
            FocusCameraY(50, 3);
        }
        if (frame == 5 && timer == 0 && m_patternVar2 == 0) {
            effect.keep = 1;
            effect.type = 0x1cf;
            effect.x = 0.0;
            effect.y = 0.0;
            effect.keep = 1;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            SpawnObject(&effect);
            m_playVoice = 16;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 10) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
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
            FocusCameraY(50, 45);
        }
        if (frame == 8 && timer == 0) {
            effect.type = 0x1b8;
            effect.shadow = 1;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = -480.0;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame > 7 && m_catchState == 1) {
            m_game->FlashWhite(9, 80, 9);
            StartPattern();
            pattern = k463214AHit;
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
    case k463214B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
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
            FocusCameraY(50, 45);
        }
        if (frame == 8 && timer == 0) {
            effect.type = 0x1b8;
            effect.shadow = 1;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = -480.0;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame > 7 && m_catchState == 1) {
            m_game->FlashWhite(9, 80, 9);
            StartPattern();
            pattern = k463214BHit;
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
    case k463214C:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
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
            FocusCameraY(50, 45);
            m_playSound = 37;
        }
        if (frame > 6) {
            m_game->FlashNegative(15);
        }
        if (frame == 8 && timer == 0) {
            effect.type = 0x1b8;
            effect.shadow = 1;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = -480.0;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame > 7 && m_catchState == 1) {
            m_game->FlashWhite(9, 80, 9);
            StartPattern();
            pattern = k463214CHit;
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
    case k463214AHit:
        FocusCameraY(50, 15);
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
        if (frame == 10 && timer == 0) {
            m_playVoice = 3;
            effect.type = 0x1c6;
            effect.scale = 0;
            effect.x = x + 20.0;
            effect.y = -50.0;
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
            if (frame == 17 && (m_catchState == 2 || m_catchState == 4 || m_patternVar2 > 0)) {
                frame = frame - 3;
                m_patternVar2--;
            }
            if (frame == 17 && m_catchState == 5) {
                frame = 21;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                m_catchState = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k463214BHit:
        FocusCameraY(50, 15);
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
            effect.type = 0x1b7;
            effect.x = (double)((int)x + (facing << 4));
            effect.y = 0.0;
            effect.scale = 0;
            effect.keep = 1;
            effect.shadow = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 16 && timer == 0) {
            m_playVoice = 3;
            effect.type = 0x1c6;
            if (m_patternVar1 == 1) {
                effect.type = 0x1c7;
            }
            if (m_patternVar1 == 2) {
                effect.type = 0x1c5;
            }
            effect.scale = 0;
            effect.x = x + 20.0;
            effect.y = -50.0;
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
            if (frame == 10) {
                frame = 16;
            }
            if (frame == 13) {
                frame = 16;
            }
            if (frame == 7) {
                if (m_patternVar1 == 1) {
                    frame = 10;
                }
                if (m_patternVar1 == 2) {
                    frame = 13;
                }
            }
            if (frame == 23 && (m_catchState == 2 || m_catchState == 4 || m_patternVar2 > 0)) {
                frame = frame - 3;
                m_patternVar2--;
            }
            if (frame == 30) {
                frame = 2;
                m_catchState = 2;
                m_patternVar1++;
            }
            if (frame == 27 && m_patternVar1 == 1) {
                frame = 30;
            }
            if (frame == 23 && m_catchState == 5) {
                frame = 30;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                m_catchState = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k463214CHit:
        FocusCameraY(50, 15);
        m_game->FlashNegative(15);
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
            effect.type = 0x1b7;
            effect.x = (double)((int)x + (facing << 4));
            effect.y = 0.0;
            effect.scale = 0;
            effect.keep = 1;
            effect.shadow = 1;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 16 && timer == 0) {
            m_playVoice = 3;
            effect.type = 0x1c6;
            if (m_patternVar1 == 1) {
                effect.type = 0x1c7;
            }
            if (m_patternVar1 == 2) {
                effect.type = 0x1c5;
            }
            effect.scale = 0;
            effect.x = x + 20.0;
            effect.y = -50.0;
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
            if (frame == 10) {
                frame = 16;
            }
            if (frame == 13) {
                frame = 16;
            }
            if (frame == 7) {
                if (m_patternVar1 == 1) {
                    frame = 10;
                }
                if (m_patternVar1 == 2) {
                    frame = 13;
                }
            }
            if (frame == 23 && (m_catchState == 2 || m_catchState == 4 || m_patternVar2 > 0)) {
                frame = frame - 3;
                m_patternVar2--;
            }
            if (frame == 30) {
                frame = 2;
                m_catchState = 2;
                m_patternVar1++;
            }
            if (frame == 27 && m_patternVar1 == 2) {
                frame = 30;
            }
            if (frame == 23 && m_catchState == 5) {
                frame = 30;
            }
            if (frame >= frameCount) {
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
            FocusCameraY(50, 3);
        }
        if (frame < 14 && (*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->StartPattern();
        }
        if (frame > 8) {
            if (vy + y > 0.0 && frame < 14) {
                y = 0.0;
                frame = 14;
                timer = 0;
                StopMoving();
                ShakeScreen(15, 10);
                m_playSound = 22;
                DealDamage(800, 900.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kKnockdown;
                effect.type = 0x190;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0;
                m_game->CreateEffect((EffectDesc*)&effect);
                (*m_opponent)->m_hitstop = 180;
                break;
            }
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -98.0;
                (*m_opponent)->x = facing * 35 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -98.0;
                (*m_opponent)->x = facing * 33 + x;
                if (m_patternVar1 > 0) {
                    timer = 150;
                }
            }
            if (frame == 3) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 33 + x;
                (*m_opponent)->facing = -facing;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kKnockdownHittable;
                (*m_opponent)->m_landHittable = 1;
                DealDamage(300, 980.0);
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
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 23);
            effect.y = (double)((int)y - 30);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            FocusCameraY(50, 45);
        }
        if (frame < 7) {
            FocusCameraY(50, 45);
            (*m_opponent)->m_hitstop = 3;
        }
        if (frame == 7) {
            FocusCameraY(0, 0);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 || frame == 6) {
                effect.type = 0;
                effect.sound = 2;
                effect.x = (double)((int)x + facing * 29);
                effect.y = (double)((int)y - 83);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -101.0;
                (*m_opponent)->x = facing * 21 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
                m_playSound = 22;
                effect.type = 0x193;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 250);
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            }
            if (frame == 3) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 7 && m_patternVar1 > 10) {
                (*m_opponent)->pattern = kHitAirCarry;
                (*m_opponent)->m_hitVx = 0.0;
                (*m_opponent)->m_hitVy = -5.0;
                (*m_opponent)->ay = 0.035;
                DealDamage(3500, 700.0);
                (*m_opponent)->m_untechTime = 180;
            }
            if (frame == 7 && m_patternVar1 < 11) {
                m_patternVar1++;
                frame = 2;
            }
            if (frame >= frameCount) {
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
            FocusCameraY(50, 45);
            (*m_opponent)->m_hitstop = 3;
        }
        if (frame == 7) {
            FocusCameraY(0, 0);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 || frame == 6) {
                effect.type = 0;
                effect.sound = 2;
                effect.x = (double)((int)x + facing * 29);
                effect.y = (double)((int)y - 83);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -101.0;
                (*m_opponent)->x = facing * 21 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
                m_playSound = 22;
                effect.type = 0x193;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 250);
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            }
            if (frame == 3) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = kThrownDoubledOver;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 15 + x;
            }
            if (frame == 7 && m_patternVar1 > 8) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = 0.2;
                (*m_opponent)->m_hitVy = -1.9;
                DealDamage(1000, 1000.0);
                m_hitsLeft = 1;
            }
            if (frame == 7 && m_patternVar1 < 9) {
                m_patternVar1++;
                frame = 2;
            }
            if (frame == 16) {
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y + 4);
                effect.scale = 0;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 40);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.facing = facing;
                effect.keep = 1;
                effect.layer = 1;
                SpawnObject(&effect);
                ShakeScreen(10, 60);
            }
            if (frame >= frameCount) {
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
            FocusCameraY(50, 45);
            m_freezeTime = 120;
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
        if (frame == 2 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y + 4);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = facing;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x192;
            effect.x = (double)((int)x + facing * 45);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.facing = facing;
            effect.keep = 1;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 8 && timer == 0) {
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y + 4);
            effect.scale = 0;
            effect.keep = 1;
            effect.facing = facing;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x191;
            effect.x = (double)((int)x + facing * 40);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.facing = facing;
            effect.keep = 1;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 2 && m_attackResult == 3) {
            ShakeScreen(6, 60);
            (*m_opponent)->m_hitstop = 500;
        }
        if (frame == 10 && timer == 0) {
            ShakeScreen(10, 60);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_attackResult != 3 && frame == 6) {
                frame = 12;
            }
            if (frame == 9 || frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 10);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 3) {
            m_game->FlashNegative(15);
        }
        if (frame > 3) {
            FocusCameraY(50, 3);
        }
        if (frame > 21 && frame < 25) {
            m_hp += 10;
            if (m_hp > 9999) {
                m_hp = 9999;
            }
            m_hitsLeft = 0;
            vy = -0.08;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_hp < 9999) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 24);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            m_game->CreateEffect((EffectDesc*)&effect);
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_patternVar1++;
            m_playSound = 37;
            m_hitsLeft = 1;
        }
        if (frame > 0) {
            m_game->FlashNegative(15);
        }
        if (frame > 0) {
            FocusCameraY(50, 3);
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
        if (frame == 12 && timer == 0 && m_attackResult == 3) {
            m_game->FlashWhite(9, 15, 9);
        }
        if (frame == 13 && timer == 0 && m_attackResult == 3) {
            StartPattern();
            pattern = kLv4Hit;
            break;
        }
        if (frame > 11 && m_attackResult == 3) {
            (*m_opponent)->m_noAirRecovery = 1;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4Hit:
        m_hideOffscreenMarker = 3;
        if (frame > 11 && m_attackResult == 3) {
            (*m_opponent)->m_noAirRecovery = 1;
        }
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 2) {
            FillBackground(176, 3);
        }
        if (frame < 2) {
            FocusCameraY(50, 3);
        }
        if (frame < 2) {
            FocusCameraX(50, 3);
        }
        if (frame == 0 && timer == 0) {
            x = 320.0;
            StopMoving();
            effect.type = 0x1b2;
            effect.screen = 1;
            effect.x = 0.0;
            effect.y = 0.0;
            effect.scale = 0;
            effect.layer = 0;
            effect.facing = 1;
            SpawnObject(&effect);
            effect.type = 0x1a5;
            effect.screen = 0;
            effect.x = 320.0;
            effect.y = 200.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            (*m_opponent)->x = 320.0;
            (*m_opponent)->y = -160.0;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kHitAir;
        }
        if (frame == 0) {
            m_patternVar1++;
            if (m_patternVar1 == 80) {
                effect.type = 0x1a6;
                effect.x = 320.0;
                effect.y = 200.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 160) {
                effect.type = 0x1a7;
                effect.x = 320.0;
                effect.y = 200.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 240) {
                effect.type = 0x1a8;
                effect.x = 320.0;
                effect.y = 200.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 320) {
                effect.type = 0x1a9;
                effect.x = 320.0;
                effect.y = 200.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 400) {
                effect.type = 0x1aa;
                effect.x = 320.0;
                effect.y = 200.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
        }
        if (frame == 0 && timer == duration - 30) {
            m_game->FlashBlack(9, 30, 9);
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
            if (m_patternVar1 == 150) {
                effect.type = 0x1b6;
                effect.x = x - facing * 240;
                effect.y = -20.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 174) {
                effect.type = 0x1ac;
                effect.x = x - facing * 240;
                effect.y = -20.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 198) {
                effect.type = 0x1ad;
                effect.x = x - facing * 240;
                effect.y = -20.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 222) {
                effect.type = 0x1ae;
                effect.x = x - facing * 240;
                effect.y = -20.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 246) {
                effect.type = 0x1af;
                effect.x = x - facing * 240;
                effect.y = -20.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (m_patternVar1 == 270) {
                effect.type = 0x1b0;
                effect.x = x - facing * 240;
                effect.y = -20.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 9;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_patternVar1++;
            m_playSound = 37;
        }
        if (frame > 3) {
            m_game->FlashNegative(15);
        }
        FocusCameraY(50, 3);
        if (frame == 9 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x1c4;
            effect.x = (double)((int)x + facing * 80);
            effect.y = 15.0;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kAir236236A:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame > 19) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 4 && frame < 6) {
            FocusCameraY(50, 3);
        }
        if (frame == 6 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x1d0;
            effect.movesInFreeze = 1;
            effect.x = (facing << 1) + x;
            effect.y = y - 29.0;
            effect.keep = 1;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 24) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kAir236236B:
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame > 19) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 4 && frame < 6) {
            FocusCameraY(50, 3);
        }
        if (frame == 6 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x1d2;
            effect.movesInFreeze = 1;
            effect.x = (facing << 1) + x;
            effect.y = y - 29.0;
            effect.keep = 1;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 24) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kAir236236C:
        if (frame > 4) {
            m_game->FlashNegative(15);
        }
        m_drawMode = 0;
        m_dashMomentum = 0;
        if (frame > 19) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x - facing * 14);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 37;
        }
        if (frame > 4 && frame < 6) {
            FocusCameraY(50, 3);
        }
        if (frame == 6 && timer == 0) {
            effect.keep = 1;
            effect.type = 0x1d5;
            effect.movesInFreeze = 1;
            effect.x = (facing << 1) + x;
            effect.y = y - 29.0;
            effect.keep = 1;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 24) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
    }
}
