// CAyu::UpdatePattern (0x6d93f0-0x6e812f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CAyu's
// .rdata, which starts with its constructor's folder name (ayu.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CAyu::UpdatePattern()
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
        if ((frame == 2 || frame == 6) && timer == 0) {
            m_playVoice = 0;
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
    case kWalkBack:
        vx = -1.1;
        vy = 0.0;
        if ((frame == 2 || frame == 6) && timer == 0) {
            m_playVoice = 0;
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
            m_playVoice = 1;
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
            m_playVoice = 1;
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
            m_playVoice = 1;
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
            m_playVoice = 1;
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
            m_playVoice = 1;
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
            m_playVoice = 1;
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
            m_rfGauge -= 50.0;
            if (vy > 0.0) {
                vy *= 0.5;
            }
        }
        m_rfGauge--;
        if (frame == 2 && timer == 0) {
            m_playSound = 17;
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
            StartAfterimages(2);
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 0 && timer == 0) {
            if (rand() > 10000) {
                effect.type = 0x191;
                effect.x = (double)((int)x - facing * 11);
                effect.y = (double)((int)y - 50);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 20000) {
                effect.type = 0x192;
                effect.x = (double)((int)x - facing * 25);
                effect.y = (double)((int)y - 70);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 15000) {
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 6);
                effect.y = (double)((int)y - 80);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
        }
        vy = vy + ay;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
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
                vx = 1.8;
                vy = -1.3;
                ay = 0.01;
                m_playSound = 17;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && m_patternVar2 >= 120) {
            pattern = kFall;
            StartPattern();
            vx = 0.5;
            ay = 0.03;
        }
        if (m_inputX != facing && m_patternVar1 >= 39) {
            pattern = kFall;
            StartPattern();
            vx = 0.5;
            ay = 0.03;
        }
        break;
    case kDashBack:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(2);
        }
        if (frame > 0 && timer == 0) {
            if (rand() > 10000) {
                effect.type = 0x191;
                effect.x = (double)((int)x - facing * 70);
                effect.y = (double)((int)y - 37);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 15000) {
                effect.type = 0x192;
                effect.x = (double)((int)x - facing * 34);
                effect.y = (double)((int)y - 58);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 20000) {
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 24);
                effect.y = (double)((int)y - 46);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
        }
        vy = vy + ay;
        timer++;
        m_patternVar1++;
        m_patternVar2++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 1) {
                vx = -1.8;
                vy = -1.3;
                ay = 0.01;
                m_playSound = 17;
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == 1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        if (m_inputX != -facing) {
            m_patternVar1 = 0;
        }
        if (m_patternVar2 > 39 && m_inputX != -facing || m_patternVar2 >= 120) {
            pattern = kFall;
            StartPattern();
            vx = -0.5;
            ay = 0.03;
        }
        break;
    case kAirDashForward:
        if (frame == 0 && timer == 0 && m_patternVar3 == 0) {
            vx = 1.8;
            vy = -0.3;
            m_playSound = 17;
            m_patternVar3++;
        }
        if (timer == 0) {
            if (rand() > 10000) {
                effect.type = 0x191;
                effect.x = (double)((int)x - facing * 11);
                effect.y = (double)((int)y - 50);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 20000) {
                effect.type = 0x192;
                effect.x = (double)((int)x - facing * 25);
                effect.y = (double)((int)y - 70);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 15000) {
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 6);
                effect.y = (double)((int)y - 80);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
        }
        vy += 0.01;
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
        if (frame == 0 && timer == 0 && m_patternVar3 == 0) {
            vx = -1.8;
            vy = -0.3;
            m_playSound = 17;
            m_patternVar3++;
        }
        if (timer == 0) {
            if (rand() > 10000) {
                effect.type = 0x191;
                effect.x = (double)((int)x - facing * 70);
                effect.y = (double)((int)y - 37);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 15000) {
                effect.type = 0x192;
                effect.x = (double)((int)x - facing * 34);
                effect.y = (double)((int)y - 58);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
            if (rand() > 20000) {
                effect.type = 0x191;
                effect.x = (double)((int)x + facing * 24);
                effect.y = (double)((int)y - 46);
                effect.facing = facing;
                effect.layer = 0;
                SpawnObject(&effect);
            }
        }
        vy += 0.01;
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
                if (m_patternVar3 < 7) {
                    frame = frame - 2;
                    m_patternVar3++;
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
            vx = 0.5;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
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
    case k5C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            effect.type = 3;
            effect.x = (double)((int)x + facing * 55);
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playVoice = 8;
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 13;
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 25;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            effect.type = 0;
            effect.x = (double)((int)x + facing * 70);
            effect.y = (double)((int)y - 10);
            effect.scale = 2;
            effect.sound = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            if (frame < 2) {
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
            if (frame < 5) {
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
    case k6C:
        if (frame == 0 && timer == 0) {
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
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
    case kJump2C:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 30;
            m_playSound = 20;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = kJump2CRebound;
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
            pattern = kJump2CLanding;
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
    case kJump2CRebound:
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
    case kJump2CLanding:
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
            effect.x = (double)((int)x + facing * 41);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 2 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
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
    case kThrowHit:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->pattern = kThrownStandHigh;
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 42 + x;
            (*m_opponent)->StartPattern();
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kHitAir;
            (*m_opponent)->m_hitVx = 1.0;
            (*m_opponent)->m_hitVy = -2.0;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->y = -59.0;
            (*m_opponent)->x = facing * 15 + x;
            (*m_opponent)->m_noAirRecovery = 1;
            DealDamage(1200, 750.0);
            m_comboHits--;
            m_shownHits--;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = kThrownStandHigh;
                (*m_opponent)->y = -33.0;
                (*m_opponent)->x = facing * 30 + x;
            }
            if (frame == 2) {
                (*m_opponent)->pattern = kThrownAirborne;
                (*m_opponent)->y = -27.0;
                (*m_opponent)->x = facing * 34 + x;
            }
            if (frame == 3) {
                (*m_opponent)->y = -54.0;
                (*m_opponent)->x = facing * 14 + x;
            }
            if (frame >= frameCount) {
                pattern = kKnockdown;
                FaceOpponent();
                StartPattern();
                frame = 2;
                x = x - facing * 20;
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
    case kUnusedE7:
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
    case kUnusedE8:
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
            pattern = kAirThrowHit;
            (*m_opponent)->pattern = kThrownStandHigh;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 19);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            (*m_opponent)->x = facing * 19 + x;
            (*m_opponent)->y = y - 50.0;
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
        if (vy > 0.0 && frame == 1) {
            frame = 2;
            timer = 0;
            break;
        }
        if (vy + y > 0.0 && frame == 4) {
            StopMoving();
            y = 0.0;
            frame = 5;
            timer = 0;
            ShakeScreen(4, 0);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kKnockdown;
            DealDamage(1100, 500.0);
            (*m_opponent)->StartPattern();
        }
        if (vy + y > 0.0 && frame > 8) {
            StopMoving();
            StartPattern();
            y = 0.0;
            pattern = kLand;
            break;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 86.0;
            (*m_opponent)->x = facing * 38 + x;
            (*m_opponent)->pattern = kThrownDoubledOver;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 15.0;
            (*m_opponent)->x = facing * 25 + x;
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
        }
        if (frame == 3) {
            (*m_opponent)->y = y;
            (*m_opponent)->x = facing * 15 + x;
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
        }
        if (frame == 4) {
            (*m_opponent)->y = y + 1.0;
            (*m_opponent)->x = facing * 13 + x;
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vy = -3.5;
                ay = 0.045;
            }
            if (frame == 5) {
                frame--;
            }
            if (frame == 6) {
                vx = -1.0;
                vy = -2.0;
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
    case k623A:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                StopMoving();
            }
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            if (y == 0.0) {
                effect.type = 0x1f;
                effect.x = x;
                effect.y = y;
                effect.side = facing == -1;
                effect.scale = 0;
                effect.layer = 0;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            vx = 0.5;
            vy = -2.5;
            ay = 0.03428571428571429;
            m_playVoice = 4;
            m_gauge = m_gauge + 30;
            effect.type = 0x190;
            effect.x = facing * 40 + x;
            effect.y = y + -54.0;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 8 && frame > 5) {
            frame = 8;
            y = 0.0;
            StopMoving();
            m_playSound = 9;
        }
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame == 8 && y < 0.0) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623C:
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
            effect.sound = 11;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 2;
        }
        if (frame == 5 && timer == 0) {
            if (y == 0.0) {
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            vx = 0.5;
            vy = -2.5;
            ay = 0.03428571428571429;
            m_playVoice = 4;
            m_gauge = m_gauge + 30;
            effect.keep = 0;
            effect.type = 0x198;
            effect.x = (double)((int)x + facing * 40);
            effect.y = (double)((int)y - 54);
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (y + vy > 0.0 && frame < 8 && frame > 5) {
            frame = 8;
            y = 0.0;
            StopMoving();
            m_playSound = 9;
        }
        timer++;
        vy = vy + ay;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame == 8 && y < 0.0) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k623B:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                StopMoving();
            }
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            if (y == 0.0) {
                effect.type = 0x1f;
                effect.x = x;
                effect.y = y;
                effect.side = facing == -1;
                effect.scale = 0;
                effect.layer = 0;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
            vx = 0.5;
            vy = -2.5;
            ay = 0.03428571428571429;
            m_playVoice = 4;
            m_gauge = m_gauge + 30;
            effect.type = 0x190;
            effect.x = facing * 40 + x;
            effect.y = y + -54.0;
            effect.facing = facing;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 8 && frame > 5) {
            frame = 8;
            y = 0.0;
            StopMoving();
            m_playSound = 9;
        }
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame == 8 && y < 0.0) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedFd:
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 6;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 2 || frame == 3) {
            if (m_pressD == 1 && m_patternVar1 > 0) {
                StartPattern();
                pattern = kUnusedFf;
                break;
            }
            if ((m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && m_patternVar1 > 0) {
                timer = 0;
                frame = 4;
                break;
            }
        }
        if (frame == 6 && timer == 0) {
            vx = 2.5;
            ax = -0.03;
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedFe:
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x - facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame >= 2 && frame <= 3 && m_hitsLeft == 7) {
            frame = 4;
            timer = 0;
        }
        if (frame == 6 && timer == 0) {
            vx = m_hitsLeft * 0.2 + 1.3;
            ax = -0.03;
        }
        if (frame == 6 && timer == 0) {
            vx = 2.5;
            ax = -0.03;
            m_gauge = m_gauge + 45;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                frame = 2;
                m_hitsLeft = m_hitsLeft + 2;
                break;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kUnusedFf:
        vx = 0.0;
        vy = 0.0;
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
    case k214A:
        if (frame == 0 && timer == 0) {
            m_attackResult = 3;
            if (y == 0.0) {
                vx = 0.0;
                vy = 0.0;
            }
            m_hitsLeft = 1;
            if (y < 0.0) {
                frame = 2;
                m_patternVar2 = 1;
            }
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 3) {
            y = 0.0;
            frame = 7;
            timer = 0;
            vy = 0.0;
            ay = 0.0;
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
        if (m_attackResult > 0 && frame > 3 && frame < 7) {
            StartPattern();
            pattern = k214Rebound;
            break;
        }
        if (vy > 0.0 && frame == 4) {
            timer = 0;
            frame = 5;
            m_attackResult = 0;
            break;
        }
        if (frame > 6) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame > 3) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_gauge = m_gauge + 35;
                vx = 1.5;
                vy = -3.0;
                ay = 0.065;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214B:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                vx = 0.0;
                vy = 0.0;
            }
            m_hitsLeft = 1;
            if (y < 0.0) {
                frame = 2;
                m_patternVar2 = 1;
            }
            m_attackResult = 3;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 3) {
            y = 0.0;
            frame = 7;
            timer = 0;
            vy = 0.0;
            ay = 0.0;
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
        if (m_attackResult > 0 && frame > 3 && frame < 7) {
            StartPattern();
            pattern = k214Rebound;
            break;
        }
        if (vy > 0.0 && frame == 4) {
            timer = 0;
            frame = 5;
            m_attackResult = 0;
            break;
        }
        if (frame > 6) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame > 3) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_gauge = m_gauge + 35;
                vx = 1.5;
                vy = -4.0;
                ay = 0.065;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214C:
        if (frame == 0 && timer == 0) {
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            vx = 0.0;
            if (m_rfBlue == 0) {
                m_rfGauge -= 500.0;
            } else {
                m_rfGauge -= 250.0;
            }
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 99;
            if (y < 0.0) {
                frame = 2;
            }
        }
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                vx = 0.0;
                vy = 0.0;
            }
            m_hitsLeft = 99;
            if (y < 0.0) {
                frame = 2;
                m_patternVar2 = 1;
            }
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 3) {
            y = 0.0;
            frame = 7;
            timer = 0;
            vy = 0.0;
            ay = 0.0;
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
        if (vy > 0.0 && frame == 4) {
            timer = 0;
            frame = 5;
            m_attackResult = 0;
            break;
        }
        if (frame > 6) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_gauge = m_gauge + 35;
                vx = 1.5;
                vy = -4.0;
                ay = 0.065;
            }
            if (frame == 5) {
                frame--;
            }
            if (frame == 7) {
                frame--;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214Rebound:
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 9) {
            y = 0.0;
            m_playSound = 9;
            StartPattern();
            StopMoving();
            frame = 9;
            break;
        }
        if (frame == 0 && timer == 0) {
            vx = -vx * 0.3;
            if (vy > -2.0) {
                vy = -2.0;
            }
            if (vy < -2.5) {
                vy = -2.5;
            }
            ay = 0.035;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k236A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            if (m_patternVar1 == 0) {
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
        }
        if (frame == 6 && timer == 0 && m_patternVar1 == 0) {
            m_hitsLeft = 1;
            m_patternVar1++;
        }
        if (m_attackResult > 1 || m_patternVar1 > 1) {
            StartPattern();
            pattern = k236End;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 8;
                m_patternVar1++;
            }
        }
        break;
    case k236B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 2.3;
            if (m_patternVar1 == 0) {
                effect.type = 0x1f;
                effect.x = (double)(int)x;
                effect.y = (double)(int)y;
                effect.scale = 0;
                effect.layer = 0;
                effect.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&effect);
            }
        }
        if (frame == 6 && timer == 0 && m_patternVar1 == 0) {
            m_hitsLeft = 1;
            m_patternVar1++;
        }
        if (m_attackResult > 1 || m_patternVar1 > 1) {
            StartPattern();
            pattern = k236End;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                frame = frame - 8;
                m_patternVar1++;
            }
        }
        break;
    case k236C:
        if (frame == 0 && timer == 0) {
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 50);
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
        if (timer == 0 && (frame == 3 || frame == 7)) {
            vx = 2.3;
            effect.type = 0x1f;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 0;
            effect.layer = 0;
            effect.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 6 && timer == 0 && m_patternVar1 == 0) {
            m_hitsLeft = 1;
            m_patternVar1++;
        }
        if (m_attackResult > 1 || m_patternVar1 > 2) {
            StartPattern();
            pattern = k236End;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_invulTime = 27;
            }
            if (frame >= frameCount) {
                frame = frame - 8;
                m_patternVar1++;
            }
        }
        break;
    case k236End:
        if (frame == 3 && timer == 0) {
            ShakeScreen(3, 0);
            effect.type = 3;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.scale = 2;
            effect.layer = 0;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_playSound = 7;
            m_hitsLeft = 1;
        }
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStandUp;
                m_inputY = 1;
                if (1) {
                    pattern = kCrouch;
                }
            }
        }
        break;
    case kAir623C:
        if (frame == 0 && timer == 0) {
            vy *= 0.25;
            vx *= 0.25;
            if (y == 0.0) {
                StopMoving();
            }
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
        if (y + vy > 0.0 && frame < 9 && frame > 6) {
            frame = 9;
            y = 0.0;
            StopMoving();
            m_playSound = 9;
        }
        timer++;
        if (frame > 5) {
            vy = vy + ay;
        }
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 3;
            }
            if (frame == 6 && timer == 0) {
                vx = -0.5;
                vy = -2.5;
                ay = 0.03428571428571429;
                m_playVoice = 4;
                m_gauge = m_gauge + 30;
                effect.keep = 0;
                effect.type = 0x199;
                effect.x = (double)((int)x + facing * 20);
                effect.y = (double)((int)y + 30);
                effect.facing = facing;
                effect.layer = 1;
                SpawnObject(&effect);
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStandUp;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k214214A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(50, 3);
        }
        if (frame == 1 && timer == 0) {
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
            effect.keep = 1;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 42);
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
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(50, 3);
        }
        if (frame == 1 && timer == 0) {
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
            effect.keep = 1;
            effect.type = 0x1a3;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 42);
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
            ay = 0.0;
        }
        if (frame < 3) {
            FocusCameraY(50, 3);
        }
        if (frame == 1 && timer == 0) {
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
        if (frame == 4 && timer == 0) {
            m_shotSpeed = 45;
            effect.keep = 1;
            effect.type = 0x1a4;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 22);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 13 && timer == 0) {
            m_shotSpeed = 30;
            effect.keep = 1;
            effect.type = 0x1a4;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 62);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 22 && timer == 0) {
            m_shotSpeed = 15;
            effect.keep = 1;
            effect.type = 0x1a4;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 42);
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
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case kAir214214A:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            FocusCameraY(25, 10);
        }
        if (frame == 1 && timer == 0) {
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
            vx = -1.9;
            vy = -1.5;
            effect.keep = 1;
            effect.type = 0x195;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 42);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (frame > 2) {
            vy = vy + ay;
            vx += 0.05;
            if (vx > -0.5) {
                vx = -0.5;
            }
        }
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
    case kAir214214B:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            FocusCameraY(25, 10);
        }
        if (frame == 1 && timer == 0) {
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
        if (frame == 3 && timer == 0) {
            vx = -1.9;
            vy = -1.5;
            effect.keep = 1;
            effect.type = 0x1a3;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 42);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (frame > 2) {
            vy = vy + ay;
            vx += 0.05;
            if (vx > -0.5) {
                vx = -0.5;
            }
        }
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
    case kAir214214C:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            FocusCameraY(25, 10);
        }
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 5;
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
        if (frame == 4 && timer == 0) {
            vx = -1.2;
            vy = -1.0;
            m_shotSpeed = 50;
            effect.keep = 1;
            effect.type = 0x1a4;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 22);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 13 && timer == 0) {
            vx = -1.2;
            vy = -1.0;
            m_shotSpeed = 35;
            effect.keep = 1;
            effect.type = 0x1a4;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 62);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        if (frame == 22 && timer == 0) {
            vx = -1.9;
            vy = -2.3;
            m_shotSpeed = 20;
            effect.keep = 1;
            effect.type = 0x1a4;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 42);
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
        }
        timer++;
        if (frame > 2) {
            vy += 0.025;
            vx += 0.05;
            if (vx > -0.5) {
                vx = -0.5;
            }
        }
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
    case k641236A:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_patternVar1 = 4;
        }
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 1;
        }
        if (frame > 6 && frame < 12) {
            FocusCameraY(50, 3);
        }
        if (frame == 8 && timer == 0) {
            ShakeScreen(3, 20);
            effect.type = 0x1a5;
            effect.x = facing * 40 + x - 30.0;
            effect.y = y;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.x = x - facing * 40 - 30.0;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playSound = 18;
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
    case k641236C:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_patternVar1 = 8;
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
            m_hitsLeft = 99;
            m_playSound = 37;
        }
        if (frame > 0) {
            m_game->FlashNegative(15);
        }
        if (frame > 0 && frame < 12) {
            FocusCameraY(50, 3);
        }
        if (frame == 8 && timer == 0) {
            m_hitsLeft = 1;
            ShakeScreen(3, 10);
            effect.type = 0x1a5;
            effect.x = facing * 10 + x;
            effect.y = y;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.x = x - facing * 10;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playSound = 18;
        }
        if (frame == 24 && timer == 0) {
            m_hitsLeft = 1;
            ShakeScreen(5, 20);
            effect.type = 0x196;
            effect.x = facing * 10 + x;
            effect.y = y;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.x = x - facing * 10;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playSound = 18;
        }
        if (frame == 40 && timer == 0) {
            m_hitsLeft = 99;
            ShakeScreen(6, 60);
            effect.type = 0x197;
            effect.x = facing * 10 + x;
            effect.y = y;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.x = x - facing * 10;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playSound = 18;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 44 && m_patternVar1 != 0) {
                m_patternVar1--;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236B:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_patternVar1 = 8;
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
            m_hitsLeft = 99;
        }
        if (frame > 0 && frame < 12) {
            FocusCameraY(50, 3);
        }
        if (frame == 8 && timer == 0) {
            ShakeScreen(6, 60);
            effect.type = 0x196;
            effect.x = facing * 10 + x;
            effect.y = y;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            SpawnObject(&effect);
            effect.x = x - facing * 10;
            effect.facing = -facing;
            SpawnObject(&effect);
            m_playSound = 18;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 10) {
                m_invulTime = 45;
            }
            if (frame == 12 && m_patternVar1 != 0) {
                m_patternVar1--;
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k236236A:
        if (frame > 0) {
            vx = vx + ax;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            StartAfterimages(5);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 2 && timer == 0 && m_patternVar1 == 0) {
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
            m_hitsLeft = 5;
            m_patternVar1++;
        }
        if (frame == 6 && timer == 0) {
            effect.type = 0x1a2;
            effect.x = facing * 68 + x;
            effect.y = y - 63.0;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = -1;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            vx = 3.0;
            ax = -0.03;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && m_freezeTime > 0) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236B:
        if (frame > 0) {
            vx = vx + ax;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            StartAfterimages(5);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 2 && timer == 0 && m_patternVar1 == 0) {
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
            m_hitsLeft = 99;
            m_patternVar1++;
        }
        if (frame == 6 && timer == 0) {
            effect.type = 0x1a2;
            effect.x = facing * 68 + x;
            effect.y = y - 63.0;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = -1;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            vx = 4.0;
            ax = -0.05;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && m_freezeTime > 0) {
                frame = frame - 2;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                StartPattern();
            }
        }
        break;
    case k236236C:
        if (frame > 0) {
            vx = vx + ax;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            StartAfterimages(5);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 1 && timer == 0 && m_patternVar1 == 0) {
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
            m_hitsLeft = 99;
            m_patternVar1++;
            m_playSound = 37;
        }
        if (frame > 1) {
            m_game->FlashNegative(15);
        }
        if (frame == 6 && timer == 0) {
            effect.type = 0x1a2;
            effect.x = facing * 68 + x;
            effect.y = y - 63.0;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = -1;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        if (frame == 6 && timer == 0) {
            vx = 4.0;
            ax = -0.04;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && m_patternVar3 < 8) {
                frame = frame - 2;
                m_patternVar3++;
            }
            if (frame == 14 && m_patternVar2 < 1) {
                frame = frame - 2;
                m_patternVar2++;
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
        if (frame == 2 && timer == 6) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 4000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 29);
            effect.y = (double)((int)y - 63);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_hitsLeft = 99;
            m_playSound = 37;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2) {
            m_game->FlashNegative(15);
        }
        if (frame == 2 && timer == 92) {
            effect.type = 0x19e;
            effect.x = x - (facing << 2);
            effect.y = y - 45.0;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 0;
            effect.sound = -1;
            effect.movesInFreeze = 1;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        if (frame == 5 && timer == 0) {
            m_playVoice = 5;
            vy = -0.1;
        }
        if (frame == 7 && timer == 0) {
            effect.type = 0x19f;
            effect.x = x;
            effect.y = y - 45.0;
            effect.facing = facing;
            effect.scale = 2;
            effect.layer = 1;
            effect.sound = -1;
            SpawnObject(&effect);
        }
        if (frame > 3) {
            FocusCameraY(50, 3);
        }
        if ((frame == 15 || frame == 16) && (WORD)Random(0, 100) > m_patternVar1 * 7.3 + 20.0) {
            effect.type = 0x1a0;
            effect.layer = 1;
            if ((WORD)Random(0, 100) > 50) {
                effect.type = 0x1a1;
                effect.layer = 0;
            }
            effect.x = x - facing * 300;
            effect.y = (double)((WORD)Random(0, 320) - 320);
            effect.facing = facing;
            effect.scale = 2;
            SpawnObject(&effect);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
                if (m_patternVar1 < 13) {
                    frame = frame - 5;
                    m_patternVar1++;
                    break;
                }
                pattern = kFall;
                effect.type = 0x19f;
                effect.x = x;
                effect.y = y - 45.0;
                effect.facing = facing;
                effect.scale = 2;
                effect.layer = 1;
                effect.sound = -1;
                SpawnObject(&effect);
                ay = 0.015;
                FaceOpponent();
                StartPattern();
            }
        }
    }
}
