// CAkiko::UpdatePattern (0x712500-0x72199f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CAkiko's
// .rdata, which starts with its constructor's folder name (akiko.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CAkiko::UpdatePattern()
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
        vx = 0.8;
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
            ay = 0.048;
            vy = -3.2;
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
            ay = 0.048;
            vy = -3.2;
            vx = 0.9;
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
            ay = 0.048;
            vy = -3.2;
            vx = -0.9;
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
            StopMoving();
            m_playSound = 9;
            pattern = kLand;
            StartPattern();
        }
        break;
    case kLand:
        StopMoving();
        y = 0.0;
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
        if (frame == 0 && timer == 0) {
            ay = 0.048;
            vx = 0.0;
            vy = -3.2;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpForward:
        if (frame == 0 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
            vx = 0.9;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kAirJumpBack:
        if (frame == 0 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
            vx = -0.9;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case 0x28:
        if (frame == 0 && timer == 0 && m_patternVar1 == 0) {
            m_patternVar1++;
            m_rfGauge -= 100.0;
            if (vy > 0.0) {
                vy *= 0.5;
            }
        }
        m_rfGauge--;
        if (frame == 2 && timer == 0) {
            m_playSound = 0x11;
        }
        vy += 0.03;
        vx = m_inputX * 0.045 * facing + vx;
        vy = m_inputY * 0.015 + vy;
        if (vy < -3.0) {
            vy = -3.0;
        } else if (vy > 1.0) {
            vy = 1.0;
        }
        if (vx < -1.0) {
            vx = -1.0;
        } else if (vx > 1.0) {
            vx = 1.0;
        }
        if (m_inputY == 1) {
            pattern = kFall;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = kLand;
            StartPattern();
        }
        break;
    case kResultLoserFall:
        if (frame == 0 && timer == 0) {
            vx = 0.3;
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
    case kThrownDoubledOver:
        break;
    case kThrownStandHigh2:
        break;
    case kThrownLying2:
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
            effect.y = (double)((int)y - 0x3c);
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
        if (frame == 2 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            effect.type = 9;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x3c);
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
            if (frame == 0xc) {
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
            ay = 0.0;
            m_patternVar1 = 0;
        }
        if (frame > 7) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                pattern = kLand;
                StartPattern();
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
                m_playSound = 0x11;
            }
            if (frame == 4) {
                vx = 2.0;
                vy = -1.0;
                ay = 0.01;
            }
            if (frame == 5 && m_inputX == facing && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = 4;
            }
            if (frame == 8) {
                vy = -0.2;
                vx = 1.0;
                ay = 0.03;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kDashBack:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_playSound = 0x11;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                vx = -3.0;
            }
            if (frame == 6) {
                StopMoving();
            }
            if (frame >= frameCount) {
                StartPattern();
                StopMoving();
                pattern = kStand;
            }
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0 && m_patternVar3 == 0) {
            vx = 1.8;
            vy = 0.0;
            m_playSound = 0x11;
            m_patternVar3++;
            StartAfterimages(3);
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
        if (frame == 0 && timer == 0 && m_patternVar3 == 0) {
            vx = -1.8;
            vy = 0.0;
            m_playSound = 0x11;
            m_patternVar3++;
            StartAfterimages(3);
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
        if (m_inputX == -facing && m_patternVar2 >= 0x78) {
            pattern = kFall;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && m_patternVar1 >= 0x2a) {
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
            if (frame == 1) {
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
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
    case k5C:
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            m_hitsLeft = 3;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_attackResult = 0;
                m_playSound = 0x14;
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
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                StopMoving();
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
            m_gauge = m_gauge + 0xd;
            m_hitsLeft = 5;
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
            if (frame == 2) {
                m_playSound = 0x15;
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playSound = 0x15;
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_playSound = 0x15;
                m_attackResult = 0;
            }
            if (frame == 5) {
                m_playSound = 0x15;
                m_attackResult = 0;
            }
            if (frame == 7) {
                m_playSound = 0x14;
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
        if (frame == 3 && timer == 0) {
            m_patternVar1 = 0;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame == 8 && m_patternVar1 < 2) {
                frame = 5;
                m_attackResult = 0;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kUnused6B:
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
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
            if (frame < 6) {
                m_attackResult = 0;
            }
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
    case kUnused6C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult == 3) {
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
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 9) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedJump2C:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = kUnusedJump2CRebound;
            StartPattern();
            StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            StopMoving();
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
            pattern = kUnusedJump2CLanding;
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
    case kUnusedJump2CRebound:
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
    case kUnusedJump2CLanding:
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
            pattern = kThrowHit;
            (*m_opponent)->pattern = kThrownAirRising;
            (*m_opponent)->m_noAirRecovery = 1;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x28);
            effect.y = (double)((int)y - 0x41);
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
    case kThrowHit:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->pattern = kThrownStandHigh;
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x2a + x;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownHidden;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                (*m_opponent)->pattern = kHeadOnly;
                (*m_opponent)->frame = 2;
                (*m_opponent)->timer = 0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x - facing * 0x28;
                effect.shadow = 1;
                effect.type = 0x1a7;
                effect.x = x - facing * 0x28;
                effect.y = 0.0;
                effect.facing = facing;
                effect.scale = 0;
                effect.keep = 1;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kUnusedE6:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
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
    case kUnusedE7:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
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
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kFall;
                StartPattern();
            }
        }
        break;
    case kUnusedE8:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xa;
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
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x16);
            effect.y = (double)((int)y - 0x44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 68.0;
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
    case kAirThrowHit:
        if (frame < 2) {
            FocusCameraX(0x32, 3);
        }
        if (frame < 2) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0) {
            StopMoving();
            y = 0.0;
            StartPattern();
            StopMoving();
            pattern = kLand;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                effect.shadow = 1;
                effect.type = 0x1a8;
                effect.x = facing * 0x25 + x;
                effect.y = -56.0;
                effect.facing = facing;
                effect.scale = 0;
                effect.keep = 1;
                effect.layer = 1;
                SpawnObject(&effect);
            }
            if (frame == 3) {
                ay = 0.035;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kUnusedF9:
        if (frame == 0 && timer == 0) {
            unkdc = 4;
            unkde = -0x14;
            vx = 0.0;
            m_hitsLeft = 1;
            m_recoilGuardWindow = 0;
            m_freezeTime = 0x3c;
            effect.type = 0x28;
            effect.x = (double)((int)x + facing * 0xa);
            effect.y = (double)((int)y - 0x28);
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = 0x13;
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
    case k236A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                m_playVoice = 0;
                m_gauge = m_gauge + 0x14;
                effect.keep = 1;
                effect.scale = 0;
                m_patternVar1 = (WORD)Random(0, 9);
                if (m_nextShot == 0) {
                    effect.type = 0x193;
                    m_nextShot = 1;
                    m_patternVar2 = 5;
                } else if (m_nextShot == 1) {
                    effect.type = 0x194;
                    m_nextShot = 2;
                    m_patternVar2 = 3;
                } else if (m_nextShot == 2) {
                    effect.type = 0x192;
                    m_nextShot = 0;
                    m_patternVar2 = 3;
                }
                m_patternVar3 = 0;
                for (; m_patternVar3 < m_patternVar2; m_patternVar3++) {
                    effect.x = facing * 0x28 + x;
                    effect.y = y + -57.0 - (WORD)Random(0, 0x14);
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.shadow = 1;
                    SpawnObject(&effect);
                }
                effect.type = 0x190;
                effect.x = facing * 0x1e + x;
                effect.y = y + -65.0;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 1;
                effect.shadow = 0;
                SpawnObject(&effect);
            }
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
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                m_playVoice = 0;
                m_gauge = m_gauge + 0x14;
                effect.keep = 1;
                effect.scale = 0;
                m_patternVar1 = (WORD)Random(0, 9);
                if (m_nextShot == 0) {
                    effect.x = facing * 0x46 + x;
                    effect.type = 0x196;
                    m_nextShot = 1;
                    m_patternVar2 = 1;
                } else if (m_nextShot == 1) {
                    effect.type = 0x197;
                    effect.x = facing * 0x28 + x;
                    m_nextShot = 2;
                    m_patternVar2 = 3;
                } else if (m_nextShot == 2) {
                    effect.type = 0x198;
                    effect.x = facing * 0x28 + x;
                    m_nextShot = 0;
                    m_patternVar2 = 1;
                }
                m_patternVar3 = 0;
                for (; m_patternVar3 < m_patternVar2; m_patternVar3++) {
                    effect.y = y + -67.0;
                    if (m_nextShot == 0) {
                        effect.y = y + -57.0 - (WORD)Random(0, 0x14);
                    }
                    effect.shadow = 1;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                effect.type = 0x190;
                effect.x = facing * 0x1e + x;
                effect.y = y + -65.0;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 1;
                effect.shadow = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                StopMoving();
            }
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
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_patternVar3 = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                m_playVoice = 0;
                m_gauge = m_gauge + 0xa;
                effect.keep = 1;
                effect.scale = 0;
                m_patternVar1 = (WORD)Random(0, 9);
                if (m_patternVar1 < 4) {
                    effect.x = facing * 0x46 + x;
                    effect.type = 0x196;
                    m_patternVar2 = 1;
                }
                if (m_patternVar1 < 8 && m_patternVar1 > 3) {
                    effect.x = facing * 0x28 + x;
                    effect.type = 0x197;
                    m_patternVar2 = 3;
                }
                if (m_patternVar1 > 7) {
                    effect.x = facing * 0x28 + x;
                    effect.type = 0x198;
                    m_patternVar2 = 1;
                }
                m_patternVar3 = 0;
                for (; m_patternVar3 < m_patternVar2; m_patternVar3++) {
                    effect.y = y + -67.0;
                    if (m_patternVar1 < 8 && m_patternVar1 > 3) {
                        effect.y = y + -57.0 - (WORD)Random(0, 0x14);
                    }
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                effect.type = 0x190;
                effect.x = facing * 0x1e + x;
                effect.y = y + -65.0;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 1;
                effect.shadow = 0;
                SpawnObject(&effect);
            }
            if (frame == 8 && timer == 0) {
                m_playVoice = 0;
                m_gauge = m_gauge + 0xa;
                effect.keep = 1;
                m_patternVar1 = (WORD)Random(0, 9);
                if (m_patternVar1 < 4) {
                    effect.x = facing * 0x46 + x;
                    effect.type = 0x196;
                    m_patternVar2 = 1;
                }
                if (m_patternVar1 < 8 && m_patternVar1 > 3) {
                    effect.x = facing * 0x28 + x;
                    effect.type = 0x197;
                    m_patternVar2 = 3;
                }
                if (m_patternVar1 > 7) {
                    effect.x = facing * 0x28 + x;
                    effect.type = 0x198;
                    m_patternVar2 = 1;
                }
                m_patternVar3 = 0;
                for (; m_patternVar3 < m_patternVar2; m_patternVar3++) {
                    effect.y = y + -67.0;
                    if (m_patternVar1 < 8 && m_patternVar1 > 3) {
                        effect.y = y + -57.0 - (WORD)Random(0, 0x14);
                    }
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                effect.type = 0x190;
                effect.x = facing * 0x1e + x;
                effect.y = y + -65.0;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 1;
                effect.shadow = 0;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623A:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && (m_command == kCmd623A || m_command == kCmd623B)) {
            StartPattern();
            pattern = k623Second;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 2.0;
                vy = -0.85;
                ay = 0.035;
                m_playVoice = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && m_patternVar1 < 3) {
                frame = 9;
                m_patternVar1++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623CFinish:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            m_hitsLeft = 1;
            vx = -vx;
            ay = 0.035;
        }
        if (frame > 3 && y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3 && timer == 0) {
                vy = -1.0;
                m_playVoice = 4;
                if (y - (*m_opponent)->y - 50.0 < 3.0 && y - (*m_opponent)->y - 50.0 > -3.0) {
                    break;
                }
                if (y - (*m_opponent)->y - 50.0 < 10.0 && y - (*m_opponent)->y - 50.0 > -10.0) {
                    frame = 4;
                } else {
                    frame = 5;
                }
                break;
            }
            if (frame == 4 && timer == 0) {
                frame = 6;
            }
            if (frame == 5 && timer == 0) {
                frame = 6;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k623Second:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && (m_command == kCmd623A || m_command == kCmd623B)) {
            StartPattern();
            pattern = k623Finish;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 3.5;
                vy = -1.4;
                ay = 0.035;
                m_playVoice = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && m_patternVar1 < 3) {
                frame = 9;
                m_patternVar1++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && (m_command == kCmd623A || m_command == kCmd623B)) {
            StartPattern();
            pattern = k623Second;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 3.0;
                vy = -1.25;
                ay = 0.035;
                m_playVoice = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && m_patternVar1 < 3) {
                frame = 9;
                m_patternVar1++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623C:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            m_patternVar2 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StartAfterimages(3);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && m_command == kCmd623C) {
            StartPattern();
            pattern = k623CRepeat;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 9.0;
                vy = -3.6;
                ay = 0.035;
                m_playVoice = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && m_patternVar1 < 3) {
                frame = 9;
                m_patternVar1++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623CRepeat:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && m_command == kCmd623C) {
            if (m_patternVar2 < 3) {
                facing = -facing;
                m_patternVar2++;
                m_patternVar1 = 0;
                frame = 0;
                timer = 0;
                break;
            }
            StartPattern();
            pattern = k623CFinish;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 9.0;
                vy = -3.6;
                ay = 0.035;
                m_playVoice = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && m_patternVar1 < 3) {
                frame = 9;
                m_patternVar1++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623Finish:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            m_hitsLeft = 1;
            vx = -vx;
            ay = 0.035;
        }
        if (frame > 3 && y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3 && timer == 0) {
                vy = -1.0;
                m_playVoice = 4;
                if (y - (*m_opponent)->y - 40.0 < 8.0 && y - (*m_opponent)->y - 40.0 > -8.0) {
                    frame = 4;
                } else {
                    frame = 5;
                }
                break;
            }
            if (frame == 4 && timer == 0) {
                frame = 6;
            }
            if (frame == 5 && timer == 0) {
                frame = 6;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 8;
            effect.type = 0x19f;
            effect.keep = 1;
            effect.x = (double)((int)x + facing * 0x29);
            effect.y = (double)((int)y - 0x37);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
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
    case k214B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 8;
            effect.type = 0x1a2;
            effect.keep = 1;
            effect.x = (double)((int)x + facing * 0x29);
            effect.y = (double)((int)y - 0x37);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
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
    case k214C:
        if (frame == 0 && timer == 0) {
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StartAfterimages(3);
            vx = 0.0;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 8;
            effect.type = 0x1a4;
            effect.keep = 1;
            effect.x = (double)((int)x + facing * 0x29);
            effect.y = (double)((int)y - 0x37);
            effect.scale = 2;
            effect.layer = 1;
            effect.facing = facing;
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
    case k41236A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 5;
        }
        if (frame > 4 && frame < 7) {
            m_patternVar1 += 3;
            if (m_patternVar1 > 0x5b) {
                m_patternVar1 = 0x5a;
            }
            m_hitByBody = 1;
            if ((*m_opponent)->x > facing * 0x39 + x && facing == 1) {
                m_cornerPushback = m_patternVar1 * 0.01 * -(*m_opponent)->facing;
            }
            if ((*m_opponent)->x < facing * 0x39 + x && facing == -1) {
                m_cornerPushback = m_patternVar1 * 0.01 * (*m_opponent)->facing;
            }
        }
        if (frame > 4 && m_attackResult == 3) {
            if (facing == 1 && x < 100.0) {
                x = 100.0;
            }
            if (facing == -1 && x > 540.0) {
                x = 540.0;
            }
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            (*m_opponent)->m_noAirRecovery = 1;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x39);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            pattern = k41236AHit;
            (*m_opponent)->pattern = kThrownHidden;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x39 + x;
            (*m_opponent)->facing = facing;
            break;
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
    case k41236AHit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0xb || frame == 0xc) {
            vy += 0.03;
            if (y + vy >= 0.0) {
                StopMoving();
                y = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 6;
            }
            if (frame == 0xb && timer == 0) {
                ShakeScreen(4, 0xa);
                vx = 1.2;
                vy = -1.25;
                (*m_opponent)->y = -50.0;
                (*m_opponent)->x = x - facing * 0x46;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = 0.0;
                (*m_opponent)->m_hitVy = -2.5;
                DealDamage(0x5dc, 500.0);
                m_playVoice = 7;
                (*m_opponent)->m_noAirRecovery = 1;
                effect.type = 0x48;
                effect.x = (double)((int)x - facing * 0x46);
                effect.y = (double)((int)y - 0x3c);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x19d;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k41236B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 5;
        }
        if (frame > 4 && frame < 7) {
            m_patternVar1 += 4;
            if (m_patternVar1 > 0x79) {
                m_patternVar1 = 0x78;
            }
            m_hitByBody = 1;
            if ((*m_opponent)->x > facing * 0x39 + x && facing == 1) {
                m_cornerPushback = m_patternVar1 * 0.01 * -(*m_opponent)->facing;
            }
            if ((*m_opponent)->x < facing * 0x39 + x && facing == -1) {
                m_cornerPushback = m_patternVar1 * 0.01 * (*m_opponent)->facing;
            }
        }
        if (frame > 4 && m_attackResult == 3) {
            if (facing == 1 && x < 100.0) {
                x = 100.0;
            }
            if (facing == -1 && x > 540.0) {
                x = 540.0;
            }
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            (*m_opponent)->m_noAirRecovery = 1;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x39);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            pattern = k41236BHit;
            (*m_opponent)->pattern = kThrownHidden;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x39 + x;
            (*m_opponent)->facing = facing;
            break;
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
    case k41236BHit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0xb || frame == 0xc) {
            vy += 0.03;
            if (y + vy >= 0.0) {
                StopMoving();
                y = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 6;
            }
            if (frame == 0xb && timer == 0) {
                ShakeScreen(4, 0xa);
                vx = 1.2;
                vy = -1.25;
                (*m_opponent)->y = -50.0;
                (*m_opponent)->x = x - facing * 0x46;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = 0.0;
                (*m_opponent)->m_hitVy = -2.5;
                DealDamage(0x5dc, 500.0);
                m_playVoice = 7;
                (*m_opponent)->m_noAirRecovery = 1;
                effect.type = 0x48;
                effect.x = (double)((int)x - facing * 0x46);
                effect.y = (double)((int)y - 0x3c);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x19d;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k41236C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 4;
            m_patternVar1 = 0;
            m_patternVar2 = 0;
            effect.type = 0x21;
            effect.sound = 0xb;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x32);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            StartAfterimages(3);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 5;
        }
        if (frame > 4 && frame < 7) {
            m_patternVar1 += 6;
            if (m_patternVar1 > 0x96) {
                m_patternVar1 = 0x96;
            }
            m_hitByBody = 1;
            if ((*m_opponent)->x > facing * 0x39 + x && facing == 1) {
                m_cornerPushback = m_patternVar1 * 0.01 * -(*m_opponent)->facing;
            }
            if ((*m_opponent)->x < facing * 0x39 + x && facing == -1) {
                m_cornerPushback = m_patternVar1 * 0.01 * (*m_opponent)->facing;
            }
        }
        if (frame > 4 && m_attackResult == 3) {
            if (facing == 1 && x < 100.0) {
                x = 100.0;
            }
            if (facing == -1 && x > 540.0) {
                x = 540.0;
            }
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            (*m_opponent)->m_noAirRecovery = 1;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 0x39);
            effect.y = (double)((int)y - 0x2f);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            pattern = k41236CHit;
            (*m_opponent)->pattern = kThrownHidden;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x39 + x;
            (*m_opponent)->facing = facing;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && m_patternVar2 < 3) {
                m_patternVar2++;
                frame--;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k41236CHit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0xb || frame == 0xc) {
            vy += 0.03;
            if (y + vy >= 0.0) {
                StopMoving();
                y = 0.0;
                StartPattern();
                pattern = kLand;
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 6;
            }
            if (frame == 0xb && timer == 0) {
                ShakeScreen(4, 0xa);
                vx = 1.2;
                vy = -1.25;
                (*m_opponent)->y = -50.0;
                (*m_opponent)->x = x - facing * 0x46;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = 0.0;
                (*m_opponent)->m_hitVy = -3.5;
                DealDamage(0x6d6, 500.0);
                m_playVoice = 7;
                (*m_opponent)->m_noAirRecovery = 1;
                effect.type = 0x48;
                effect.x = (double)((int)x - facing * 0x46);
                effect.y = (double)((int)y - 0x3c);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                effect.type = 0x19d;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
                effect.type = 0x19e;
                effect.keep = 1;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 1;
                effect.facing = facing;
                SpawnObject(&effect);
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case k236236A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
            effect.type = 0x1a6;
            effect.shadow = 1;
            effect.x = x - facing * 0x168;
            effect.y = 0.0;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            effect.keep = 1;
            SpawnObject(&effect);
            m_playVoice = 9;
        }
        if (frame < 3) {
            FocusCameraY(0x19, 0xa);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 0xc;
                ShakeScreen(7, 0xa);
                effect.type = 0x1ad;
                effect.x = (double)((int)x + facing * 0x6e);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1af;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1ae;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
            }
            if (frame == 0xa && timer == 0 && m_patternVar1 < 6) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
            effect.type = 0x1ab;
            effect.shadow = 1;
            effect.x = x - facing * 0x168;
            effect.y = 0.0;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            effect.keep = 1;
            SpawnObject(&effect);
            m_playVoice = 9;
        }
        if (frame < 3) {
            FocusCameraY(0x19, 0xa);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 0xc;
                ShakeScreen(7, 0xa);
                effect.type = 0x1ad;
                effect.x = (double)((int)x + facing * 0x82);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1af;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1b0;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
            }
            if (frame == 0xa && timer == 0 && m_patternVar1 < 6) {
                m_patternVar1++;
                frame = frame - 2;
            }
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
            m_hitsLeft = 1;
            effect.type = 0x1ac;
            effect.shadow = 1;
            effect.x = x - facing * 0x168;
            effect.y = 0.0;
            effect.facing = facing;
            effect.scale = 0;
            effect.layer = 1;
            effect.keep = 1;
            SpawnObject(&effect);
            m_playVoice = 9;
        }
        if (frame < 3) {
            FocusCameraY(0x19, 0xa);
        }
        if (frame > 4) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 4 && timer == 0) {
            m_patternVar1 = 0;
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 0xc;
                ShakeScreen(7, 0xa);
                effect.type = 0x1ad;
                effect.x = (double)((int)x + facing * 0xc8);
                effect.y = (double)(int)y;
                effect.scale = 2;
                effect.keep = 1;
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1af;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1b0;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
                effect.type = 0x1b1;
                SpawnObject(&effect);
                SpawnObject(&effect);
                SpawnObject(&effect);
            }
            if (frame == 0xa && timer == 0 && m_patternVar1 < 6) {
                m_patternVar1++;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            FocusCameraY(0x19, 0xa);
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            effect.type = 0x44;
            effect.sound = 0x13;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            pattern = k214214AHit;
            (*m_opponent)->m_hitstop = 0x1c2;
            break;
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
    case k214214AHit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_playVoice = 0x13;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                ShakeScreen(5, 5);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -3.5;
                (*m_opponent)->m_hitVy = -1.5;
                (*m_opponent)->ay = 0.035;
                DealDamage(0x3e8, 500.0);
                (*m_opponent)->m_noAirRecovery = 1;
                effect.type = 0x34;
                m_playSound = 0x16;
                effect.x = (double)((int)x + facing * 0x28);
                effect.y = (double)((int)y - 0x46);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                (*m_opponent)->m_sealLevel = 1;
                m_sealTime = 0x3e8;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            FocusCameraY(0x19, 0xa);
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 5 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            pattern = k214214BHit;
            (*m_opponent)->m_hitstop = 0x1c2;
            break;
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
    case k214214BHit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_playVoice = 0x13;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                ShakeScreen(5, 5);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -3.5;
                (*m_opponent)->m_hitVy = -1.5;
                (*m_opponent)->ay = 0.035;
                DealDamage(0x3e8, 500.0);
                (*m_opponent)->m_noAirRecovery = 1;
                effect.type = 0x34;
                m_playSound = 0x16;
                effect.x = (double)((int)x + facing * 0x28);
                effect.y = (double)((int)y - 0x46);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                (*m_opponent)->m_sealLevel = 2;
                m_sealTime = 0x3e8;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k214214C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            FocusCameraY(0x19, 0xa);
        }
        if (frame > 1) {
            m_game->FlashNegative(0xf);
        }
        if (frame == 0 && timer == 0) {
            m_freezeTime = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            effect.type = 0x46;
            effect.sound = 0x40;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 0x42);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 0x25;
        }
        if (frame == 5 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            pattern = k214214CHit;
            (*m_opponent)->m_hitstop = 0x1c2;
            break;
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
    case k214214CHit:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_playVoice = 0x13;
        }
        if (frame < 2) {
            m_game->FlashNegative(0xf);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                ShakeScreen(5, 5);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kHitAirLaunch;
                (*m_opponent)->m_hitVx = -3.5;
                (*m_opponent)->m_hitVy = -1.5;
                (*m_opponent)->ay = 0.035;
                DealDamage(0x3e8, 500.0);
                (*m_opponent)->m_noAirRecovery = 1;
                effect.type = 0x34;
                m_playSound = 0x16;
                effect.x = (double)((int)x + facing * 0x28);
                effect.y = (double)((int)y - 0x46);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                (*m_opponent)->m_sealLevel = 3;
                m_sealTime = 0x3e8;
            }
            m_attackResult = 0;
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k641236A:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 2) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
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
                m_game->FadeMusic(-0x2710, 0x64);
                m_patternVar1 = 0;
            }
            if (frame == 8 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 8) {
                m_timerSuper = 1;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k641236B:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 0) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
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
                m_game->FadeMusic(-0x2710, 0x64);
                m_patternVar1 = 0;
            }
            if (frame == 8 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 8) {
                m_timerSuper = 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k641236C:
        if (frame == 0 && timer == 0) {
            m_patternVar1 = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && m_patternVar1 < 0) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 2) {
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
                m_patternVar1 = 0;
                m_playSound = 0x25;
                m_game->FadeMusic(-0x2710, 0x64);
            }
            if (frame == 8 && m_patternVar1 < 1) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 8) {
                m_timerSuper = 3;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kLv4:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 6) {
            m_game->FlashNegative(0xf);
        }
        if (frame > 5) {
            FocusCameraY(0x32, 3);
        }
        if (frame == 0xa && m_attackResult == 3) {
            StartPattern();
            pattern = kLv4Hit;
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kThrownHidden;
            FillBackground(0xb0, 0x1770);
            m_game->FadeMusic(-0x2710, 0x3e8);
            m_game->m_hideObjectsTime = 0x7530;
            (*m_opponent)->m_game->m_hideObjectsTime = 0x7530;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                x = (*m_opponent)->x + facing * 0x28;
                facing = -facing;
                m_freezeTime = 0x96;
                m_gauge = m_gauge - 0xbb8;
                FillBackground(0xb0, 0xa);
                effect.type = 0x46;
                effect.sound = 0x40;
                effect.x = (double)(int)x;
                effect.y = (double)((int)y - 0x3f);
                effect.scale = 2;
                effect.keep = 1;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                m_playSound = 0x25;
                effect.type = 0x47;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            if (frame == 0xa) {
                if ((*m_opponent)->y == 0.0) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= frameCount) {
                FaceOpponent();
                StartPattern();
                pattern = kStand;
            }
        }
        break;
    case kLv4Hit:
        if (frame == 0 && timer == 0) {
            m_game->FlashNegative(0);
            if (x > 450.0 && facing == 1) {
                x = 450.0;
            }
            if (x < 190.0 && facing == -1) {
                x = 190.0;
            }
            (*m_opponent)->x = facing * 0x3c + x;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_patternVar1 = 0;
        }
        if (frame > 2) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                FillBackground(0xb0, 0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kEatingJam;
                (*m_opponent)->facing = facing;
                effect.type = 0x1a9;
                effect.x = (double)((int)x + facing * 0x3c);
                effect.y = (double)(int)y;
                effect.facing = facing;
                effect.scale = 0;
                effect.keep = 1;
                effect.layer = 0;
                SpawnObject(&effect);
                m_playVoice = 0x11;
            }
            if (frame == 2) {
                m_game->m_hideObjectsTime = 0x7530;
                (*m_opponent)->m_game->m_hideObjectsTime = 0x7530;
                m_game->m_hideHudTime = 0x7530;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kThrownHidden;
                effect.type = 0x1aa;
                effect.x = 0.0;
                effect.y = 0.0;
                effect.scale = 0;
                effect.layer = 1;
                effect.keep = 1;
                effect.shadow = 0;
                effect.facing = 1;
                effect.screen = 1;
                SpawnObject(&effect);
                m_playVoice = 0x10;
            }
            if (frame == 3) {
                m_game->m_hideObjectsTime = 0;
                (*m_opponent)->m_game->m_hideObjectsTime = 0;
                m_game->m_hideHudTime = 0;
                m_playVoice = 0xe;
                DealDamage(0x157c, 1000.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = kLyingDown;
            }
            if (frame == 5 && m_patternVar1 < 0x14) {
                m_patternVar1++;
                frame = 3;
            }
            if (frame == 5) {
                if ((*m_opponent)->m_hp <= 0 && m_roundsWon == m_game->m_roundsToWin) {
                } else {
                    m_game->FadeMusic(0, 0x3e8);
                }
            }
            if (frame >= frameCount) {
                FaceOpponent();
                StartPattern();
                pattern = kStand;
            }
        }
    }
}
