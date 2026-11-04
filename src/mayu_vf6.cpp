// CMayu::UpdatePattern (0x5c8580-0x5dddef), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMayu's
// .rdata, which starts with its constructor's folder name (mayu.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMayu::UpdatePattern()
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
        vx = 0.9;
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
        vx = -0.9;
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
            ay = 0.055;
            vy = -2.8;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
    case kSuperJump:
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
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 0.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (frame < 9) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
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
        if (m_hp > 0 && timer > 69 && frame == 0) {
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
        if (frame == 3 && timer == 0) {
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
            if (frame == 12) {
                ay = 0.035;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -3.5;
                vy = -1.5;
                ay = 0.05;
            }
            if (frame >= frameCount) {
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
            if (ay == 0.0) {
                ay = 0.035;
            }
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (y + vy > 0.0 && frame < 12) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 12;
            m_playSound = 9;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 12) {
                frame = frame - 4;
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
            vx = 1.2;
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
            m_hitsLeft = 2;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 35;
            m_playSound = 20;
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
            m_gauge = m_gauge + 13;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= duration) {
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 25;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_playSound = 20;
                m_hitsLeft = 1;
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
            m_gauge = m_gauge + 13;
            m_hitsLeft = 1;
            m_playSound = 20;
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
            m_gauge = m_gauge + 15;
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 13;
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
            effect.type = 0;
            effect.x = (double)((int)x + facing * 37);
            effect.y = (double)((int)y - 48);
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
            if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kThrowHold:
        if (frame == 0 && timer == 0) {
            x = (*m_opponent)->x - (*m_opponent)->m_pointX[0] * facing;
            y = (*m_opponent)->m_pointY[0] + 30;
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
            effect.type = 0;
            effect.sound = 2;
            effect.x = (double)(int)x;
            effect.y = (double)((int)y - 45);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            DealDamage(1000, 750.0);
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            m_playSound = 21;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_gauge = m_gauge + 13;
            m_hitsLeft = 2;
            m_playSound = 20;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = kDashHopLanding;
            StartPattern();
            frame = 1;
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
            m_gauge = m_gauge + 10;
            m_playSound = 20;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            m_attackResult = 3;
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
    case kAirThrow:
        vy = vy + ay;
        if (frame == 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->m_noAirRecovery = 1;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 22);
            effect.y = (double)((int)y - 54);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            frame = 0;
            timer = 0;
            pattern = kAirThrowHold;
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 22 + x;
            (*m_opponent)->y = y - 52.0;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 2 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
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
    case kAirThrowHold:
        m_hideOffscreenMarker = 2;
        if (frame < 11) {
            if (x > 6100.0 && facing == 1) {
                x = 6100.0;
                vx = 0.0;
            }
            if (x < 30.0 && facing == -1) {
                x = 30.0;
                vx = 0.0;
            }
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        if (frame < 10 || frame > 11 && frame < 15) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 10) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    DealDamage(1000, 500.0);
                    effect.type = 0;
                    effect.x = (double)(int)x;
                    effect.y = (double)(int)y;
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    timer = 0;
                    frame = 10;
                    m_playSound = 2;
                    break;
                }
                if (frame == 14) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 15;
                    break;
                }
            }
        }
        if (frame < 1) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 22 + x;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 10) {
                frame = frame - 8;
            }
            if (frame == 12) {
                vx = -0.8;
                vy = -1.0;
                ay = 0.035;
            }
            if (frame >= frameCount) {
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
            y = m_pointY[0] + 50;
            x = (*m_opponent)->x + (-m_pointX[0] - 20) * facing;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 7);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            y = m_pointY[0] + 50;
            x = (*m_opponent)->x + (-m_pointX[0] - 20) * facing;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 7);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = k41236CThrow;
            y = m_pointY[0] + 50;
            x = (*m_opponent)->x + (-m_pointX[0] - 20) * facing;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 7);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
                (*m_opponent)->x = (m_pointX[0] + 20) * facing + x;
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
            DealDamage(500, 750.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->m_hitVx = 0.8;
            (*m_opponent)->m_hitVy = -3.2;
        }
        if (frame < 4) {
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 3) {
                vx = -1.0;
                vy = -1.3;
                ay = 0.03;
            }
            if (frame >= frameCount) {
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
                (*m_opponent)->x = (m_pointX[0] + 20) * facing + x;
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
            DealDamage(1000, 800.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->facing = facing;
            (*m_opponent)->m_hitVx = -4.0;
            (*m_opponent)->m_hitVy = -0.8;
        }
        if (frame < 4) {
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = -1.0;
                vy = -2.1;
                ay = 0.025;
            }
            if (frame >= frameCount) {
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
            m_playSound = 21;
        }
        if (frame > 10) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = 0;
            }
        }
        if (frame >= frameCount) {
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
            m_playSound = 35;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k236A:
        if (frame > 8 && frame < 15 && m_holdA > 0) {
            StartPattern();
            pattern = kRisingStrike;
            break;
        }
        if (frame > 8 && frame < 15 && m_holdB > 0) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 12 && m_patternVar1 < 3) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
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
        if (frame > 13) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_command == kCmd236A && frame > 13) {
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
        if (vy + y > 0.0 && frame > 5 && frame < 10) {
            frame = 14;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        if (vy + y > 0.0 && frame > 9 && frame < 14) {
            frame = 14;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
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
                vx = 1.2;
                vy = -3.3;
                ay = 0.055;
                m_hitsLeft = 1;
            }
            if (frame == 10) {
                frame = frame - 4;
            }
            if (frame == 14) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (vy + y > 0.0 && frame > 5 && frame < 10) {
            frame = 10;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        timer++;
        if (timer >= duration) {
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
                    frame = 10;
                    y = 0.0;
                    break;
                }
            }
            if (frame == 10) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        if (frame > 4 && frame < 15 && y + vy > 0.0) {
            timer = 0;
            frame = 15;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                vy = -3.3;
                m_hitsLeft = 3;
            }
            if (frame == 15) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        if (frame > 10) {
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
        if (vy + y > 0.0 && frame > 2 && frame < 10) {
            StartPattern();
            StopMoving();
            y = 0.0;
            pattern = k236JumpLanding;
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
                vx = 0.8;
                vy = -3.1;
                ay = 0.055;
                m_hitsLeft = 1;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
            m_playSound = 21;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            m_playSound = 21;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
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
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 21;
            m_gauge = m_gauge + 35;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame > 8 && frame < 13) {
            frame = 13;
            timer = 0;
            y = 0.0;
            StopMoving();
        }
        timer++;
        if (timer >= duration) {
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
            if (frame == 13) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
            m_playSound = 35;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_playSound = 35;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kWallJumpC:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 40;
            m_hitsLeft = 4;
        }
        if (frame > 9 && frame < 14) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                StopMoving();
                StartPattern();
                frame = 14;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 || frame == 14) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 9) {
                vx = m_patternVar1 * 0.005;
                vy = -0.8;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k214A:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 19 && m_command == kCmd236A) {
            StartPattern();
            pattern = kRisingStrike;
            break;
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -2.0;
            vx = -3.0;
        }
        if (frame > 15 && frame < 20) {
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
        if (frame > 4 && frame < 12 || frame > 15 && frame < 20) {
            vy = vy + ay;
        }
        if (frame > 11 && frame < 16) {
            if (facing == 1) {
                x = m_game->m_view.left + 15;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 15;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 20) {
            y = 0.0;
            StopMoving();
            frame = 20;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 12) {
            vx = 0.0;
            vy = 0.0;
            frame = 12;
            timer = 0;
            m_playSound = 26;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame == 16) {
                vx = 1.5;
                vy = -2.5;
                ay = 0.035;
            }
            if (frame == 20) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        if (frame == 18 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 18 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = k214DThrow;
            y = m_pointY[0] + 50;
            x = (*m_opponent)->x + (-m_pointX[0] - 20) * facing;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 7);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        if (frame > 4 && frame < 12 || frame > 15 && frame < 19) {
            vy = vy + ay;
        }
        if (frame > 11 && frame < 16) {
            if (facing == 1) {
                x = m_game->m_view.left + 15;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 15;
            }
        }
        if (y + vy >= 0.0 && frame > 15 && frame < 19) {
            y = 0.0;
            StopMoving();
            frame = 20;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 12) {
            vx = 0.0;
            vy = 0.0;
            frame = 12;
            timer = 0;
            m_playSound = 26;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame == 16) {
                vx = 2.2;
                vy = -0.5;
                ay = 0.035;
            }
            if (frame == 19) {
                frame--;
            }
            if (frame >= frameCount) {
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
        if (frame > 19 && m_command == kCmd236A) {
            StartPattern();
            pattern = kRisingStrike;
            break;
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -2.0;
            vx = 3.0;
        }
        if (frame > 15 && frame < 20) {
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
        if (frame > 4 && frame < 12 || frame > 15 && frame < 20) {
            vy = vy + ay;
        }
        if (frame > 11 && frame < 16) {
            if (facing == 1) {
                x = m_game->m_view.left + 15;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 15;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 20) {
            y = 0.0;
            StopMoving();
            frame = 20;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 12) {
            vx = 0.0;
            vy = 0.0;
            facing = -facing;
            frame = 12;
            timer = 0;
            m_playSound = 26;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame == 16) {
                vx = 1.5;
                vy = -2.5;
                ay = 0.035;
            }
            if (frame == 20) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case k214DThrow:
        FocusCameraX(50, 3);
        FocusCameraY(50, 3);
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
        if (frame == 10 && timer == 0) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            DealDamage(1200, 960.0);
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.sound = 2;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame == 19 && y + vy > 0.0) {
            StartPattern();
            StopMoving();
            y = 0.0;
            pattern = kLand;
            break;
        }
        if (frame > 15) {
            vy = vy + ay;
        }
        if (frame > 13 && (*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 16) {
                vx = -0.5;
                vy = -1.3;
                ay = 0.05;
            }
            if (frame >= frameCount) {
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
            frame = 12;
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
        if (timer >= duration) {
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
            if (frame == 12) {
                frame = frame - 6;
            }
            if (frame >= frameCount) {
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
            frame = 12;
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
        if (timer >= duration) {
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
            if (frame == 12) {
                frame = frame - 6;
            }
            if (frame >= frameCount) {
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
            effect.type = 0x21;
            effect.sound = 11;
            effect.x = (double)((int)x + facing * 20);
            effect.y = (double)((int)y - 50);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_patternVar1++;
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 12;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            timer = 0;
            frame = 8;
            m_hitsLeft = 99;
            break;
        }
        timer++;
        if (timer >= duration) {
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
            if (frame == 12) {
                frame = frame - 6;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastHitReaction)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame == 2) {
                m_gauge = m_gauge + 25;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k41236DRide:
        FocusCameraY(-50, 3);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                x = (*m_opponent)->x - (*m_opponent)->m_pointX[0] * facing;
                y = (*m_opponent)->y + (*m_opponent)->m_pointY[0] - 20.0;
            }
            if (frame >= frameCount) {
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
            m_playSound = 35;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_playSound = 35;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            m_playSound = 35;
            m_gauge = m_gauge + 35;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        if (frame == 18 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame > 4 && frame < 12 || frame > 15 && frame < 19) {
            vy = vy + ay;
        }
        if (frame > 11 && frame < 16) {
            if (facing == 1) {
                x = m_game->m_view.left + 15;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 15;
            }
        }
        if (y + vy >= 0.0 && frame > 15 && frame < 19) {
            y = 0.0;
            StopMoving();
            frame = 20;
            timer = 0;
            break;
        }
        if ((char)AtScreenEdge() != 0 && frame > 4 && frame < 12) {
            vx = 0.0;
            vy = 0.0;
            frame = 12;
            timer = 0;
            m_playSound = 26;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame == 16) {
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
            if (frame == 19) {
                frame--;
            }
            if (frame >= frameCount) {
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
        if (frame > 4 && frame < 15 && y + vy > 0.0) {
            timer = 0;
            frame = 15;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                vy = -3.3;
                m_hitsLeft = 3;
            }
            if (frame == 15) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        if (frame > 14) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 22;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 14) {
                vx = 0.5;
                vy = 0.0;
                ay = 0.045;
            }
            if (frame == 22) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
            m_invulTime = 126;
            FocusCameraY(50, 120);
        }
        if (frame >= 1) {
            unkf2 = 10;
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (frame == 16 && timer == 0) {
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                m_invulTime = 9;
            }
            if (frame == 6) {
                x = facing * 15 + x;
            }
            if (frame == 7) {
                x = facing * 15 + x;
            }
            if (frame == 9) {
                x = facing * 15 + x;
            }
            if (frame == 10) {
                if (m_patternVar1 > 1) {
                    frame = 12;
                    break;
                }
                x = facing * 15 + x;
            }
            if (frame == 12 && m_patternVar1 < 1) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
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
            m_invulTime = 132;
            FocusCameraY(50, 120);
        }
        if (frame >= 1) {
            unkf2 = 10;
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (frame == 14 && timer == 0) {
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 21 && timer == 0) {
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (frame > 20 && frame < 28) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 20 && frame < 28 && y + vy > 0.0) {
            frame = 28;
            timer = 0;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                m_invulTime = 30;
            }
            if (frame == 6) {
                x = facing * 15 + x;
            }
            if (frame == 7) {
                x = facing * 15 + x;
            }
            if (frame == 9) {
                x = facing * 15 + x;
            }
            if (frame == 10) {
                if (m_patternVar1 > 2) {
                    frame = 12;
                    break;
                }
                x = facing * 15 + x;
            }
            if (frame == 12 && m_patternVar1 < 2) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame == 20) {
                ay = 0.06;
                vy = -3.0;
                vx = 2.0;
            }
            if (frame == 28) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
            m_invulTime = 132;
            FocusCameraY(50, 120);
            m_playSound = 37;
        }
        if (frame > 1) {
            m_game->FlashNegative(15);
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 21;
            m_hitsLeft = 1;
        }
        if (frame == 14 && timer == 0) {
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        if (frame == 18 && timer == 0) {
            m_playSound = 21;
            m_hitsLeft = 1;
            vx = 3.0;
        }
        if (frame > 18 && frame < 23) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 20 && frame < 23 || frame > 28) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 24 && timer == 0) {
            vx = 1.8;
            m_hitsLeft = 99;
        }
        if (frame == 32 && timer == 0) {
            m_playSound = 20;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0 || frame < 34 && frame > 27) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                m_invulTime = 60;
            }
            if (frame == 6) {
                x = facing * 15 + x;
            }
            if (frame == 7) {
                x = facing * 15 + x;
            }
            if (frame == 9) {
                x = facing * 15 + x;
            }
            if (frame == 10) {
                if (m_patternVar1 > 3) {
                    frame = 12;
                    break;
                }
                x = facing * 15 + x;
            }
            if (frame == 12 && m_patternVar1 < 3) {
                frame = 2;
                m_patternVar1++;
            }
            if (frame == 28 && m_patternVar1 < 8) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case kLv4Grab:
        if (frame == 0 && timer == 0) {
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
            m_playSound = 37;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        if (frame > 1) {
            m_game->FlashNegative(15);
        }
        if (frame >= 0 && frame < 3) {
            FocusCameraY(50, 3);
        }
        if (frame == 6 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = kLv4Slam;
            y = m_pointY[0] + 50;
            x = (*m_opponent)->x + (-m_pointX[0] - 20) * facing;
            effect.type = 0;
            effect.x = (double)((int)(*m_opponent)->x + m_pointX[0]);
            effect.y = (double)((int)(*m_opponent)->y + m_pointY[0]);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 1.5;
                vy = -2.0;
                ay = 0.045;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4GrabClose:
        if (frame == 0 && timer == 0) {
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
            m_playSound = 37;
            effect.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
        m_game->FlashNegative(15);
        if (frame >= 0 && frame < 3) {
            FocusCameraY(50, 3);
        }
        if (frame == 4 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = kThrownStandHigh2;
            StartPattern();
            StopMoving();
            pattern = kLv4GrabCloseHold;
            (*m_opponent)->m_hitstop = 120;
            (*m_opponent)->x = facing * 30 + x;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 44);
            effect.y = (double)((int)y - 7);
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
            if (frame == 4 && (*m_opponent)->y >= 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= frameCount) {
                pattern = kStand;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case kLv4Slam:
        FocusCameraX(50, 3);
        FocusCameraY(50, 3);
        m_game->FlashNegative(15);
        if (frame > 3) {
            vy = vy + ay;
        }
        if (frame == 4) {
            (*m_opponent)->m_koDelay = 30000;
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
        if (frame == 9 || frame == 10) {
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
            DealDamage(1000, 960.0);
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.sound = 2;
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
            if (frame == 4) {
                vx = (1 - ((x > 320.0) << 1)) * 0.6 * facing;
                vy = -5.0;
                ay = 0.06;
            }
            if (frame >= frameCount) {
                frame = frame - 2;
            }
        }
        break;
    case kLv4GrabCloseHold:
        FocusCameraX(50, 3);
        FocusCameraY(50, 3);
        m_game->FlashNegative(15);
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= frameCount) {
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
        (*m_opponent)->FocusCameraY(50, 3);
        m_game->FlashNegative(15);
        m_hideOffscreenMarker = 2;
        if ((*m_opponent)->pattern == kLyingDown) {
            (*m_opponent)->timer = 0;
        }
        if (m_patternVar1 > 120 && m_patternVar1 < 720 && frame > 5 && frame < 12 && (WORD)Random(0, 100) < 5) {
            effect.type = 0x195;
            effect.x = x + 80.0 - (WORD)Random(0, 160);
            effect.y = (double)-(WORD)Random(0, 50);
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        if (frame > 5) {
            m_patternVar1++;
        }
        if (m_patternVar1 == 80) {
            effect.type = 0x191;
            effect.x = (double)((int)x + facing * 30);
            effect.y = -320.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.keep = 1;
            effect.shadow = 1;
            effect.facing = facing;
            SpawnObject(&effect);
        }
        if (m_patternVar1 == 120) {
            effect.type = 0x192;
            effect.x = (double)((int)x - facing * 20);
            effect.y = -320.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.shadow = 1;
            effect.facing = facing;
            effect.keep = 1;
            SpawnObject(&effect);
        }
        if (frame == 9 && vy + y > 0.0) {
            StopMoving();
            timer = 0;
            frame = 10;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            y = 0.0;
            (*m_opponent)->m_koDelay = 30000;
            DealDamage(300, 960.0);
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.sound = 2;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        if (frame == 15 && vy + y > 0.0) {
            StopMoving();
            timer = 0;
            frame = 16;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = kKnockdown;
            y = 0.0;
            DealDamage(1400, 960.0);
            (*m_opponent)->m_koDelay = 0;
            ShakeScreen(10, 10);
            (*m_opponent)->m_hitstop = 120;
            effect.type = 0;
            effect.x = (double)(int)x;
            effect.y = (double)(int)y;
            effect.sound = 22;
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        if (frame == 20 && vy + y > 0.0) {
            StopMoving();
            timer = 0;
            frame = 21;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            y = 0.0;
            break;
        }
        if (frame == 11 && m_patternVar1 > 820) {
            frame = 12;
            timer = 0;
            vy = -5.0;
            ay = 0.06;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                vx = 0.0;
                vy = -3.9;
                ay = 0.08;
            }
            if (frame == 12) {
                if (m_patternVar1 <= 730) {
                    frame = 6;
                    vx = 0.0;
                    vy = -3.9;
                    ay = 0.08;
                } else {
                    frame = 11;
                }
            }
            if (frame == 18) {
                vx = -0.6;
                vy = -1.5;
                ay = 0.038;
            }
            if (frame == 31 && m_patternVar2 < 4) {
                frame = frame - 2;
                m_patternVar2++;
            }
            if (frame >= frameCount) {
                StartPattern();
                pattern = kStand;
                FaceOpponent();
            }
        }
        break;
    case k641236Lv1:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame >= 0 && frame < 3) {
            FocusCameraY(50, 3);
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
            (*m_opponent)->x = facing * 22 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = k641236Lv1Throw;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 44);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        if (frame > 4 && frame < 112) {
            vy = vy + ay;
        }
        if (frame < 12 && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 12;
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
        if (timer >= duration) {
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
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236Lv2:
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame >= 0 && frame < 3) {
            FocusCameraY(50, 3);
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
            (*m_opponent)->x = facing * 22 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = k641236Lv2Throw;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 44);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        if (frame > 4 && frame < 112) {
            vy = vy + ay;
        }
        if (frame < 12 && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 12;
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                m_invulTime = 12;
            }
            if (frame == 5 && m_patternVar1 < 3) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236Lv3:
        if (frame == 0 && timer == 0) {
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
            m_playSound = 37;
        }
        m_game->FlashNegative(15);
        if (frame >= 0 && frame < 3) {
            FocusCameraY(50, 3);
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
            (*m_opponent)->x = facing * 22 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = k641236Lv3Throw;
            effect.type = 0;
            effect.x = (double)((int)x + facing * 44);
            effect.y = (double)((int)y - 44);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame > 4 && frame < 112) {
            vy = vy + ay;
        }
        if (frame < 12 && y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 12;
            break;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                m_invulTime = 18;
            }
            if (frame == 5 && m_patternVar1 < 5) {
                frame = frame - 2;
                m_patternVar1++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 12) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case k641236Lv1Throw:
        m_hideOffscreenMarker = 2;
        if (frame < 14) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        if (frame < 13 || frame > 14 && frame < 18) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 13) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 126;
                    DealDamage(2350, 750.0);
                    ShakeScreen(10, 0);
                    timer = 0;
                    frame = 13;
                    m_playSound = 22;
                    break;
                }
                if (frame == 17) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 18;
                    break;
                }
            }
        }
        if (frame < 13) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 22 + x;
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
        if (frame == 10) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 11) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 12) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 13) {
                frame = frame - 8;
            }
            if (frame == 15) {
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
            if (frame >= frameCount) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k641236Lv2Throw:
        m_hideOffscreenMarker = 2;
        if (frame < 25) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        if (frame < 13 || frame > 14 && frame < 25 || frame > 26 && frame < 30) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 13) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 150;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    DealDamage(1000, 980.0);
                    ShakeScreen(10, 0);
                    (*m_opponent)->m_koDelay = 30000;
                    timer = 0;
                    frame = 13;
                    m_playSound = 22;
                    break;
                }
                if (frame > 14 && frame < 25) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 126;
                    ShakeScreen(15, 0);
                    DealDamage(2100, 980.0);
                    (*m_opponent)->m_koDelay = 0;
                    timer = 0;
                    frame = 25;
                    m_playSound = 22;
                    break;
                }
                if (frame == 29) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 30;
                    break;
                }
            }
        }
        if (frame < 13) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 14 && frame < 25) {
            vx += 0.025;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 22 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4 || frame == 15 || frame == 16) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5 || frame == 17) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6 || frame == 18) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 || frame == 19) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8 || frame == 20) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 21) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 10 || frame == 22) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 11 || frame == 23) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 12 || frame == 24) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 13 || frame == 25) {
                frame = frame - 8;
            }
            if (frame == 15) {
                vx = -4.0;
                vy = -4.0;
                ay = 0.025;
                (*m_opponent)->m_hitstop = 3;
            }
            if (frame == 27) {
                vx = -1.8;
                vy = -2.3;
                ay = 0.035;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -1.8;
                (*m_opponent)->m_hitVy = -2.3;
                (*m_opponent)->pattern = kHitAir;
            }
            if (frame >= frameCount) {
                StartPattern();
                FaceOpponent();
                pattern = kCrouch;
            }
        }
        break;
    case k641236Lv3Throw:
        m_hideOffscreenMarker = 2;
        m_game->FlashNegative(15);
        if (frame < 25) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            FocusCameraX(50, 3);
            FocusCameraY(50, 3);
        }
        if (frame < 13 || frame > 14 && frame < 25 || frame > 26 && frame < 30) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 13) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 150;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    DealDamage(1000, 980.0);
                    ShakeScreen(10, 0);
                    (*m_opponent)->m_koDelay = 30000;
                    timer = 0;
                    frame = 13;
                    m_playSound = 22;
                    break;
                }
                if (frame > 14 && frame < 25) {
                    y = 0.0;
                    StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitstop = 186;
                    DealDamage(3800, 980.0);
                    (*m_opponent)->m_koDelay = 0;
                    ShakeScreen(20, 30);
                    timer = 0;
                    frame = 25;
                    m_playSound = 22;
                    break;
                }
                if (frame == 29) {
                    y = 0.0;
                    StopMoving();
                    timer = 0;
                    frame = 30;
                    break;
                }
            }
        }
        if (frame < 13) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 14 && frame < 25) {
            vx += 0.025;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = facing * 22 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4 || frame == 15 || frame == 16) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5 || frame == 17) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6 || frame == 18) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 || frame == 19) {
            (*m_opponent)->pattern = kThrownDoubledOverInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8 || frame == 20) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 21) {
            (*m_opponent)->pattern = kThrownAirborne;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 10 || frame == 22) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 11 || frame == 23) {
            (*m_opponent)->pattern = kThrownDoubledOver;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 12 || frame == 24) {
            (*m_opponent)->pattern = kThrownAirborneInverted;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 13 || frame == 25) {
                frame = frame - 8;
            }
            if (frame == 15) {
                vx = -4.0;
                vy = -7.0;
                ay = 0.025;
                (*m_opponent)->m_hitstop = 3;
            }
            if (frame == 27) {
                vx = -1.8;
                vy = -2.3;
                ay = 0.035;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->m_hitVx = -1.8;
                (*m_opponent)->m_hitVy = -2.3;
                (*m_opponent)->pattern = kHitAir;
            }
            if (frame >= frameCount) {
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
            m_freezeTime = 120;
            m_gauge = m_gauge - 1000;
            FillBackground(176, 3);
            effect.type = 0x44;
            effect.sound = 19;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            FocusCameraY(50, 120);
            m_hitsLeft = 12;
        }
        if (timer == 0 && (frame == 9 || frame == 11 || frame == 13 || frame == 15)) {
            m_playSound = 21;
        }
        if (frame > 7 && frame < 16) {
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
        if (frame > 15) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 16 && m_patternVar1 < 3) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 1 || frame == 9 || frame == 11 || frame == 13 || frame == 15 || frame == 16) {
                m_attackResult = 0;
            }
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
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 2000;
            FillBackground(176, 3);
            effect.type = 0x45;
            effect.sound = 5;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            FocusCameraY(50, 120);
            m_hitsLeft = 99;
        }
        if (timer == 0 && (frame == 9 || frame == 11 || frame == 13 || frame == 15)) {
            m_playSound = 21;
        }
        if (frame > 7 && frame < 16) {
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
        if (frame > 15) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 16 && m_patternVar1 < 5) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 1 || frame == 9 || frame == 11 || frame == 13 || frame == 15 || frame == 16) {
                m_attackResult = 0;
            }
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
            ay = 0.0;
        }
        if (frame > 0) {
            m_game->FlashNegative(15);
        }
        if (frame == 1 && timer == 0) {
            m_freezeTime = 120;
            m_gauge = m_gauge - 3000;
            FillBackground(176, 3);
            effect.type = 0x46;
            effect.sound = 64;
            effect.x = (double)((int)x + facing * 15);
            effect.y = (double)((int)y - 34);
            effect.scale = 2;
            effect.keep = 1;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            FocusCameraY(50, 120);
            m_hitsLeft = 99;
            m_playSound = 37;
        }
        if (timer == 0 && (frame == 9 || frame == 11 || frame == 13 || frame == 15)) {
            m_playSound = 21;
        }
        if (frame > 7 && frame < 16) {
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
        if (frame > 15) {
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
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 16 && m_patternVar1 < 10) {
                frame = frame - 4;
                m_patternVar1++;
            }
            if (frame == 1 || frame == 9 || frame == 11 || frame == 13 || frame == 15 || frame == 16) {
                m_attackResult = 0;
            }
            if (frame >= frameCount) {
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
            FocusCameraY(50, 120);
        }
        if (frame > 13 && frame < 18 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitstop = 180;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHold;
            (*m_opponent)->x = facing * 30 + x;
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
        if (m_attackResult > 0 && frame < 18 && frame > 13) {
            timer = 0;
            frame = 18;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 14) {
                vx = 3.2;
            }
            if (frame == 18 && m_patternVar1 < 2) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv1Hit:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 99;
        }
        if ((frame == 5 || frame == 10) && timer == 0) {
            m_playSound = 21;
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
        if (frame > 18 && frame < 31 && y + vy > 0.0) {
            timer = 0;
            frame = 31;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 15 + x;
            }
            if (frame == 10) {
                x = facing * 15 + x;
            }
            if (frame == 12) {
                x = facing * 15 + x;
            }
            if (frame == 13) {
                if (m_patternVar1 > 1) {
                    frame = 15;
                    break;
                }
                x = facing * 15 + x;
            }
            if (frame == 15 && m_patternVar1 < 1) {
                frame = 5;
                m_patternVar1++;
            }
            if (frame == 19) {
                vy = -3.3;
                vx = 1.5;
                m_hitsLeft = 3;
            }
            if (frame == 31) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
            m_hitsLeft = 1;
            FocusCameraY(50, 120);
        }
        if (frame > 13 && frame < 18 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitstop = 180;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHold;
            (*m_opponent)->x = facing * 30 + x;
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
        if (m_attackResult > 0 && frame < 18 && frame > 13) {
            timer = 0;
            frame = 18;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 14) {
                vx = 4.0;
            }
            if (frame == 18 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv2Hit:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 99;
        }
        if ((frame == 5 || frame == 10) && timer == 0) {
            m_playSound = 21;
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
        if (frame > 25 && frame < 38 && y + vy > 0.0) {
            timer = 0;
            frame = 38;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 15 + x;
            }
            if (frame == 10) {
                x = facing * 15 + x;
            }
            if (frame == 12) {
                x = facing * 15 + x;
            }
            if (frame == 13) {
                if (m_patternVar1 > 1) {
                    frame = 15;
                    break;
                }
                x = facing * 15 + x;
            }
            if (frame == 15 && m_patternVar1 < 2) {
                frame = 5;
                m_patternVar1++;
            }
            if (frame == 25) {
                vy = -4.0;
                vx = 1.6;
                m_hitsLeft = 4;
            }
            if (frame == 38) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
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
        m_game->FlashNegative(15);
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
            m_hitsLeft = 1;
            FocusCameraY(50, 120);
            m_playSound = 37;
        }
        if (frame > 13 && frame < 18 && m_attackResult == 3) {
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->m_hitstop = 180;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = kHitStandLowHold;
            (*m_opponent)->x = facing * 30 + x;
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
        if (m_attackResult > 0 && frame < 18 && frame > 13) {
            timer = 0;
            frame = 18;
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            if (frame == 14) {
                vx = 4.5;
            }
            if (frame == 18 && m_patternVar1 < 3) {
                m_patternVar1++;
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
        break;
    case k21436Lv3Hit:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 99;
        }
        if ((frame == 5 || frame == 10) && timer == 0) {
            m_playSound = 21;
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
        if (frame > 27 && frame < 33 && y + vy > 0.0) {
            timer = 0;
            frame = 33;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame > 37 && frame < 42 && y + vy > 0.0) {
            timer = 0;
            frame = 42;
            y = 0.0;
            StopMoving();
            break;
        }
        if (frame > 44 && frame < 67 && y + vy > 0.0) {
            timer = 0;
            frame = 67;
            y = 0.0;
            StopMoving();
            break;
        }
        timer++;
        if (timer >= duration) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 15 + x;
            }
            if (frame == 10) {
                x = facing * 15 + x;
            }
            if (frame == 12) {
                x = facing * 15 + x;
            }
            if (frame == 13) {
                x = facing * 15 + x;
            }
            if (frame == 15 && m_patternVar1 < 10) {
                m_patternVar1++;
                frame = 5;
            }
            if (frame == 19) {
                x = facing * 15 + x;
            }
            if (frame == 20) {
                x = facing * 15 + x;
            }
            if (frame == 22) {
                x = facing * 15 + x;
            }
            if (frame == 15 && m_patternVar1 < 8) {
                frame = 5;
                m_patternVar1++;
            }
            if (frame == 28) {
                vy = -1.8;
                vx = 1.5;
                m_hitsLeft = 1;
            }
            if (frame == 37) {
                vy = -2.6;
                vx = 1.5;
                m_hitsLeft = 1;
            }
            if (frame == 45) {
                vy = -4.5;
                vx = 2.2;
                m_hitsLeft = 8;
            }
            if (frame == 67) {
                frame = frame - 4;
            }
            if (frame >= frameCount) {
                pattern = kCrouch;
                StartPattern();
            }
        }
    }
}
