// CKano::UpdatePattern (0x6429c0-0x653a1f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CKano's
// .rdata, which starts with its constructor's folder name (kano.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CKano::UpdatePattern()
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
        vx = 0.6;
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
        vx = -0.6;
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
            ay = 0.025;
            vy = -2.2;
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
            ay = 0.025;
            vy = -2.2;
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
            ay = 0.025;
            vy = -2.2;
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
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
        m_dashMomentum = 0;
        if (frame == 0 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
            m_gauge = m_gauge + 0x1e;
            m_patternVar1++;
            m_untechTime = m_untechTime + 0x78;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            m_playSound = 0x1f;
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
            m_playSound = 0x21;
            vx = m_hitVx;
            vy = m_hitVy;
            m_gauge = m_gauge + 0x1e;
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
                m_playSound = 0x21;
                vx = m_hitVx;
                vy = m_hitVy;
                m_gauge = m_gauge + 0x1e;
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
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
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
            m_gauge = m_gauge + 0xf;
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
            effect.y = (double)((int)y - 0x46);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 1;
            m_playSound = 0x3e;
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
        if (frame == 4 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x46);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 0xf) {
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
        if (frame > 3) {
            vx = 1.5;
        }
        m_dashMomentum = 1;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = frame - 3;
                break;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 0x50) {
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
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            StopMoving();
            vx = -3.1;
            vy = 0.0;
            ay = 0.0;
            m_patternVar1 = 1;
            m_playSound = 0x11;
        }
        if (frame > -1) {
            vx += 0.04;
        }
        if (vx >= 0.0 && frame > -1) {
            vx = 0.0;
            vy = 0.0;
            pattern = kStand;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                frame = 0;
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = 1.1;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            m_playSound = 0x11;
        }
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
        if (m_inputX == facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = 0.9;
            ay = 0.02;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && m_patternVar1 >= 0x30) {
            pattern = kFall;
            StartPattern();
            vx = 0.9;
            ay = 0.02;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case kAirDashBack:
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            vx = -1.1;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 0x11;
        }
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
        if (m_inputX == -facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.02;
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
            m_freezeTime = 0x5a;
            FillBackground(0xb0, 3);
        }
        if (frame == 0 && timer == 0) {
            m_playSound = 0x12;
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
                if (ay == 0.0) {
                    ay = 0.02;
                }
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
        if (y + vy > 0.0 && frame < 9) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 9;
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
            if (frame == 9) {
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
            m_playSound = 0x15;
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
        if (m_inputY == -1 && frame > 0 && m_sealLevel < 3 && m_attackResult > 0 && m_attackResult != 6) {
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
            m_playSound = 0x14;
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
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 4 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 6) {
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
        if (frame == 4 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 6) {
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
            m_playSound = 0x15;
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
            m_playSound = 0x14;
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
            vx -= 0.03;
        } else {
            vx = 0.0;
            m_dashMomentum = 0;
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
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
        if (frame == 3 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 2;
        }
        if (frame == 8 && timer == 0) {
            m_playSound = 0x14;
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
            if (frame == 4 || frame == 9) {
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
            m_hitsLeft = 5;
        }
        if (frame == 7 && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
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
            if (frame == 7 || frame == 9 || frame == 0xb || frame == 0xd) {
                m_attackResult = 0;
            }
            if (frame == 0xe && m_patternVar1 < 1) {
                m_patternVar1++;
                frame = frame - 7;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case k6C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame == 8 && timer == 0) {
            effect.type = 0x199;
            effect.x = (double)((int)x + facing * 0x96);
            effect.y = -40.0;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar1++;
            m_playVoice = 2;
            m_gauge = m_gauge - 0x14;
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
    case kUnusedD3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.2;
            vy = 1.2;
        }
        if (frame == 1 && timer == 0) {
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
            if (frame >= frameCount) {
                frame = frame - 1;
            }
        }
        break;
    case k3C:
        if (frame == 0) {
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
        }
        if (frame == 1 && timer == 0) {
            vx = 2.6;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame > 0) {
            vx -= 0.03;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 4 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 2;
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
    case kJump2A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0 && frame < 5) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 5;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                ObjBase::SetVelocity(30.0, 2.2);
            }
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStandUp;
                FaceOpponent();
            }
        }
        break;
    case kJump2B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0 && frame < 5) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 5;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                ObjBase::SetVelocity(45.0, 1.7);
            }
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStandUp;
                FaceOpponent();
            }
        }
        break;
    case kJump2C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0 && frame < 5) {
            y = 0.0;
            StopMoving();
            timer = 0;
            frame = 5;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                ObjBase::SetVelocity(60.0, 1.5);
            }
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStandUp;
                FaceOpponent();
            }
        }
        break;
    case k6B:
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
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
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
        if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
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
            effect.y = -52.0;
            effect.x = (double)(int)(facing * 0x23 + x);
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
    case kThrowConnected:
        if (frame == 2 && timer == 0) {
            (*m_opponent)->m_hitstop = 0x1e;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x4a);
            effect.y = (double)((int)y - 0x36);
            effect.scale = 2;
            effect.sound = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(0x3e8, 750.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->m_hitVx = -2.0;
            (*m_opponent)->m_hitVy = -1.5;
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
    case kDashA:
        StartAfterimages(3);
        m_dashMomentum = 0;
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x15;
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 4 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 6) {
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x14;
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x15;
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 6;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
            StartPattern();
            StopMoving();
            pattern = kAirThrowConnected;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x1d);
            effect.y = (double)((int)y - 0x3e);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->y = y - 62.0;
            FocusCameraX(0x32, 3);
            FocusCameraY(0x32, 3);
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
        if (frame < 5) {
            FocusCameraX(0x32, 3);
        }
        if (frame < 5) {
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
        if (frame == 2) {
            (*m_opponent)->y = y - 47.0;
            (*m_opponent)->x = facing * 0x1c + x;
            (*m_opponent)->pattern = kThrownStandLow;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 38.0;
            (*m_opponent)->x = facing * 0x14 + x;
            (*m_opponent)->pattern = kThrownStandLow;
            (*m_opponent)->facing = facing;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 62.0;
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->pattern = kThrownStandHigh;
            (*m_opponent)->facing = facing;
        }
        if (frame == 5 && timer == 0) {
            (*m_opponent)->y = y - 72.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = kHitAirLaunch;
            (*m_opponent)->facing = facing;
            DealDamage(0x4b0, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_hitVx = -1.0;
            (*m_opponent)->m_hitVy = -2.3;
        }
        if (frame == 0xc && timer == 0) {
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
    case k5D:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
            m_patternVar1++;
            if (m_chargeGauge > 0x2710) {
                m_chargeGauge = 0x2710;
            }
        }
        if (frame > 2 && frame < 7 && m_pressD == 1 || m_chargeGauge >= 0x2710 && frame < 7) {
            timer = 0;
            frame = 7;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (0) {}
            if (0) {}
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236D:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_hitsLeft = 1;
                if (m_rfBlue == 0) {
                    m_rfGauge -= 500.0;
                } else {
                    m_rfGauge -= 250.0;
                }
                m_chargeGauge = 0x2710;
                effect.type = 0x198;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 0x28);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x197;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.layer = 0;
                effect.facing = facing;
                SpawnObject(&effect);
                m_playVoice = 1;
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
            m_playVoice = 0;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x1d4c;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xf && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && m_patternVar1 < 1) {
                effect.type = 0x1bb;
                effect.x = (double)((int)x + (facing * 0x96 + m_inputX * 0x46));
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_playVoice = 3;
                m_eruptionsOut++;
            }
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
            m_playVoice = 0;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x1388;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xf && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && m_patternVar1 < 1) {
                effect.type = 0x1bc;
                effect.x = (double)((int)x + (facing * 0x96 + m_inputX * 0x46));
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_playVoice = 3;
                m_eruptionsOut++;
                m_gauge = m_gauge - 0x14;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x9c4;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xf && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && m_patternVar1 < 1) {
                effect.type = 0x1bd;
                effect.x = (double)((int)x + (facing * 0x96 + m_inputX * 0x46));
                effect.y = 0.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                m_playVoice = 3;
                m_eruptionsOut++;
                m_gauge = m_gauge - 0x32;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x1d4c;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0x10 && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x11 && m_patternVar1 < 1) {
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 0x26);
                effect.y = (double)((int)y - 0x2d);
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                effect.keep = 1;
                SpawnObject(&effect);
                m_playVoice = 5;
                m_shotsOut++;
            }
            if (frame == 0x13 && m_patternVar1 < 1) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x1388;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0x10 && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x11) {
                if (m_patternVar1 == 0) {
                    effect.type = 0x191;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x2d);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playVoice = 5;
                    m_shotsOut++;
                    m_gauge = m_gauge - 7;
                }
                if (m_patternVar1 == 1) {
                    effect.type = 0x191;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    effect.keep = 1;
                    SpawnObject(&effect);
                    m_shotsOut++;
                    m_gauge = m_gauge - 7;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x46);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    effect.keep = 1;
                    SpawnObject(&effect);
                    m_playVoice = 5;
                    m_shotsOut++;
                    m_gauge = m_gauge - 7;
                }
            }
            if (frame == 0x13 && m_patternVar1 < 2) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x9c4;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0x10 && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x11) {
                if (m_patternVar1 == 0) {
                    effect.type = 0x191;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x2d);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    effect.keep = 1;
                    SpawnObject(&effect);
                    m_playVoice = 5;
                    m_shotsOut++;
                    m_gauge = m_gauge - 0xa;
                }
                if (m_patternVar1 == 1) {
                    effect.type = 0x191;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_shotsOut++;
                    m_gauge = m_gauge - 0xa;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x46);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    effect.keep = 1;
                    SpawnObject(&effect);
                    m_playVoice = 5;
                    m_shotsOut++;
                    m_gauge = m_gauge - 0xa;
                }
                if (m_patternVar1 == 2) {
                    effect.type = 0x191;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y + 5);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    effect.keep = 1;
                    SpawnObject(&effect);
                    m_shotsOut++;
                    m_gauge = m_gauge - 0xa;
                    effect.x = (double)((int)x + facing * 0x26);
                    effect.y = (double)((int)y - 0x5f);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    effect.keep = 1;
                    SpawnObject(&effect);
                    m_playVoice = 5;
                    m_shotsOut++;
                    m_gauge = m_gauge - 0xa;
                }
            }
            if (frame == 0x13 && m_patternVar1 < 3) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k421A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x1d4c;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xb && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && timer == 0) {
                effect.type = 0x1b8;
                effect.x = x;
                effect.y = -80.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                effect.keep = 1;
                SpawnObject(&effect);
                m_orbsOut++;
                m_playVoice = 4;
                m_patternVar2 = 0x15;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k421B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x1388;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xb && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && timer == 0) {
                effect.type = 0x1b9;
                effect.x = x;
                effect.y = -80.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                effect.keep = 1;
                SpawnObject(&effect);
                m_playVoice = 4;
                m_orbsOut++;
                m_patternVar2 = 0x15;
                m_patternVar1++;
                m_gauge = m_gauge - 0x14;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k421C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x4b;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0x9c4;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xb && m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0)) {
            StartPattern();
            StopMoving();
            pattern = k236D;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && timer == 0) {
                effect.type = 0x1ba;
                effect.x = x;
                effect.y = -80.0;
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                effect.keep = 1;
                SpawnObject(&effect);
                m_orbsOut++;
                m_playVoice = 4;
                m_patternVar2 = 0x15;
                m_patternVar1++;
                m_gauge = m_gauge - 0x32;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnused107:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 6 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 6) {
            m_chargeGauge += 0x12c;
        }
        if (frame > 2 && frame < 6 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 0xf) {
            m_patternVar2--;
        }
        if (frame == 0xc && m_patternVar1 < 1) {
            effect.type = 0x199;
            effect.x = (double)((int)x + facing * 0x6e);
            effect.y = -40.0;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar1++;
            m_playVoice = 2;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 6) {
                frame = frame - 3;
            }
            if (frame == 0x10 && m_patternVar1 < 2) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnused108:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 6 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 6) {
            m_chargeGauge += 0x12c;
        }
        if (frame > 2 && frame < 6 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 0xf) {
            m_patternVar2--;
        }
        if (frame == 0xc && m_patternVar1 < 1) {
            effect.type = 0x199;
            effect.x = (double)((int)x + facing * 0xa0);
            effect.y = -40.0;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar1++;
            m_playVoice = 2;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 6) {
                frame = frame - 3;
            }
            if (frame == 0x10 && m_patternVar1 < 2) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnused109:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 6;
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 0x64);
            effect.y = (double)((int)y - 0x1e0);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0x50);
            effect.y = (double)((int)y - 0x208);
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0x82);
            effect.y = (double)((int)y - 0x212);
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
    case kUnused10a:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 6;
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 0xb4);
            effect.y = (double)((int)y - 0x1e0);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0xa0);
            effect.y = (double)((int)y - 0x208);
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0xd2);
            effect.y = (double)((int)y - 0x212);
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
    case kUnused10b:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_patternVar1 = 2;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 6;
            effect.type = 0x1a2;
            effect.x = (double)((int)x + facing * 0x104);
            effect.y = (double)((int)y - 0x1e0);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0xf0);
            effect.y = (double)((int)y - 0x208);
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0x122);
            effect.y = (double)((int)y - 0x212);
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
    case kUnused10c:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
        }
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x - facing * 0x1e);
            effect.y = (double)((int)y - 0x1e);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
        }
        break;
    case kUnused10d:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
        }
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x - facing * 0x1e);
            effect.y = (double)((int)y - 0x1e);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
        }
        break;
    case kUnused10e:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            m_patternVar1 = 3;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            effect.type = 0x197;
            effect.x = (double)((int)x - facing * 0x1e);
            effect.y = (double)((int)y - 0x1e);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (frame > 1) {
            m_patternVar2++;
        }
        if (m_patternVar2 == 0x10) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 0x1e);
            effect.y = (double)((int)y - 0x1e);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (m_patternVar2 == 0x20) {
            effect.type = 0x197;
            effect.x = (double)((int)x + facing * 0x14);
            effect.y = (double)((int)y - 0xa);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        if (m_patternVar2 == 0x30) {
            effect.type = 0x197;
            effect.x = (double)((int)x - facing * 0x14);
            effect.y = (double)((int)y - 0xa);
            effect.facing = facing;
            effect.layer = 1;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
                break;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kFall;
                ay = 0.035;
            }
        }
        break;
    case k641236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 0xd && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x64);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x64;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0x10 && timer == 0) {
            m_playVoice = 0x1d;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && timer == 0 && m_patternVar1 < 1) {
                effect.type = 0x1c7;
                effect.x = (double)((int)x + facing * 0x4b);
                effect.y = 0.0;
                if (m_patternVar1 == 1) {
                    effect.x = facing * 0x1e + x;
                }
                if (m_patternVar1 == 2) {
                    effect.x = facing * 0x78 + x;
                }
                if (m_patternVar1 == 3) {
                    effect.x = facing * 0x50 + x;
                }
                if (m_patternVar1 == 4) {
                    effect.x = facing * 0x91 + x;
                }
                effect.scale = 2;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame == 0x12 && m_patternVar1 < 3) {
                frame--;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k641236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 0xd && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x64);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x64;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xf && timer == 0) {
            effect.type = 0x1a3;
            effect.x = (double)((int)x + facing * 0x28);
            effect.y = (double)((int)y - 0x28);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x13 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k641236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        FocusCameraY(0x32, 3);
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x64;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xa && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 0xa4);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x2b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        if (frame == 0xd && timer == 0) {
            effect.type = 0x1c1;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.facing = facing;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            effect.movesInFreeze = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 0xd && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x64);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x64;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xe && timer == 0) {
            effect.type = 0x19c;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x6e);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 9 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 0xe);
            effect.y = (double)((int)y - 0x40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x96;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xd && timer == 0) {
            effect.type = 0x1ad;
            effect.x = (double)((int)x + facing * 0x3c);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0x2d);
            effect.y = (double)((int)y + 0xa);
            effect.keep = 1;
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0x4b);
            effect.y = (double)((int)y - 0xa);
            effect.keep = 1;
            SpawnObject(&effect);
            effect.x = (double)((int)x + facing * 0x3c);
            effect.y = (double)(int)y;
            effect.keep = 1;
            effect.type = 0x19d;
            SpawnObject(&effect);
            ShakeScreen(4, 0);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        FocusCameraY(0x32, 3);
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x64;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 9 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x2b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        if (frame == 0xd && timer == 0) {
            effect.type = 0x1c2;
            effect.x = (double)((int)x + facing * 0xa);
            effect.y = (double)((int)y - 0x37);
            effect.facing = facing;
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            SpawnObject(&effect);
            m_meteorsPending++;
            m_meteorTimer = 0x258;
            m_meteorFacing = facing;
        }
        if (frame > 0xd) {
            m_game->FlashNegative(0xf);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && m_patternVar3 < 8) {
                frame = frame - 2;
                m_patternVar3++;
            }
            if (frame == 0x11 && m_patternVar2 < 5) {
                frame = frame - 4;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k21436A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 0xd) {
            m_chargeGauge += 0xc8;
            if (m_chargeGauge > 0x2710) {
                m_chargeGauge = 0x2710;
            }
        }
        if (frame > 0xf && frame < 0x13) {
            m_patternVar2--;
        }
        if (m_patternVar2 <= 0 && m_patternVar3 < 3 && frame > 0xf) {
            m_chargeGauge = 0;
            m_playVoice = 0xe;
            effect.type = 0x19e;
            effect.x = (double)((int)x + facing * 0x1e);
            effect.y = (double)((int)y - 0x28);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar2 = 0x1e;
            m_patternVar3++;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                m_invulTime = 0xf;
            }
            if (frame == 0x13 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k21436B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 0xd) {
            m_chargeGauge += 0xc8;
            if (m_chargeGauge > 0x2710) {
                m_chargeGauge = 0x2710;
            }
        }
        if (frame > 0xf && frame < 0x13) {
            m_patternVar2--;
        }
        if (m_patternVar2 <= 0 && m_patternVar3 < 4 && frame > 0xf) {
            m_chargeGauge = 0;
            m_playVoice = 0xe;
            effect.type = 0x19f;
            effect.x = (double)((int)x + facing * 0x1e);
            effect.y = (double)((int)y - 0x28);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar2 = 0x1e;
            m_patternVar3++;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                m_invulTime = 0x2d;
            }
            if (frame == 0x13 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k21436C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame > 2) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 2 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 5;
            StopMoving();
            m_playSound = 0x25;
        }
        if (frame == 6 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 0xd) {
            m_chargeGauge += 0xc8;
            if (m_chargeGauge > 0x2710) {
                m_chargeGauge = 0x2710;
            }
        }
        if (frame > 0xf && frame < 0x13) {
            m_patternVar2--;
        }
        if (m_patternVar2 <= 0 && m_patternVar3 < 5 && frame > 0xf) {
            m_chargeGauge = 0;
            m_playVoice = 0xe;
            effect.type = 0x1a0;
            effect.x = (double)((int)x + facing * 0x1e);
            effect.y = (double)((int)y - 0x28);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_patternVar2 = 0x1e;
            m_patternVar3++;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                m_invulTime = 0xb4;
            }
            if (frame == 0x13 && m_patternVar1 < 6) {
                frame = frame - 3;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k22B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 9 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 0xe);
            effect.y = (double)((int)y - 0x40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x96;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xc && timer == 0) {
            effect.type = 0x1ae;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0x12;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 0xd && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)((int)x - facing * 0xe);
            effect.y = (double)((int)y - 0x40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x96;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0x11 && timer == 0) {
            effect.type = 0x1a7;
            effect.x = (double)((int)x + facing * 0x1e);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0x11;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214B:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        if (frame == 9 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x - facing * 0xe);
            effect.y = (double)((int)y - 0x40);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StopMoving();
        }
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x96;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 0xc && timer == 0) {
            effect.type = 0x1ac;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x3c);
            effect.scale = 2;
            effect.layer = 1;
            effect.keep = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_playVoice = 0xf;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214C:
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
        }
        FocusCameraY(0x32, 3);
        if (frame == 7 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 7) {
            m_chargeGauge += 0x64;
        }
        if (frame > 2 && frame < 7 && m_chargeGauge >= 0x2710) {
            m_chargeGauge = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 0x196;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            effect.type = 0x197;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame == 8 && timer == 0) {
            m_freezeTime = 0x78;
            m_hitsLeft = 1;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 0xa4);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x2b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        if (frame == 0xd && timer == 0) {
            effect.type = 0x1b2;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
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
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kLv4:
        FocusCameraY(0x32, 3);
        if (frame == 0 && timer == 0) {
            m_dashMomentum = 0;
            StopMoving();
            m_playVoice = 0;
            m_freezeTime = 0x78;
            m_hitsLeft = 1;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x2b);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 7 && m_attackResult == 3) {
            frame = 0;
            pattern = kLv4Connected;
            (*m_opponent)->StopMoving();
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->pattern = kThrownStandHigh2;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
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
    case kLv4Connected:
        FocusCameraY(0x32, 3);
        if (frame == 0 && timer == 0) {
            m_playVoice = 0x1b;
        }
        if (frame > 0x11 && (*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->x = facing * 0x37 + x;
                (*m_opponent)->y = -61.0;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->x = facing * 0x2e + x;
                (*m_opponent)->y = -74.0;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->x = facing * 0x21 + x;
                (*m_opponent)->y = -86.0;
            }
            if (frame == 7) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->x = (facing << 5) + x;
                (*m_opponent)->y = -87.0;
                effect.type = 0x1c8;
                effect.x = 0.0;
                effect.y = 200.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.keep = 1;
                effect.facing = 1;
                effect.screen = 1;
                effect.movesInFreeze = 1;
                SpawnObject(&effect);
            }
            if (frame == 8) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = -87.0;
            }
            if (frame == 0xb && m_patternVar1 == 0) {
                frame = frame - 3;
            }
            if (frame == 0x11) {
                (*m_opponent)->m_hitstop = 0;
                (*m_opponent)->pattern = kHitAir;
                (*m_opponent)->y = -20.0;
                (*m_opponent)->ay = 0.035;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
    }
}
