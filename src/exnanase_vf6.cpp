// CEXNanase::UpdatePattern (0x6be9c0-0x6cfbaf), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CEXNanase's
// .rdata, which starts with its constructor's folder name (exnanase.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CEXNanase::UpdatePattern()
{
    WORD x8;
    WORD l4;

    if (unk14a > 0 || (*m_opponent)->unk14c > 0) {
        return;
    }
    EffectDesc l50;
    l4 = (short)anims[pattern].frames[frame].duration;
    x8 = anims[pattern].frameCount;
    CPlayer::InitEffectDesc((EffectDesc*)&l50);
    switch (pattern) {
    default:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 1:
        unk158 = 0;
        vx = (unk3454 == 1) * 0.15 + 0.9;
        vy = 0.0;
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 2:
        unk158 = 0;
        vx = -0.9 - (unk3454 == 1) * 0.15;
        vy = 0.0;
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 3:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        CPlayer::FaceOpponent();
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 4:
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = (unk3454 == 1) * 0.015 + 0.045;
            vy = -2.7 - (unk3454 == 1) * 0.6;
            if (unk158 == 1) {
                vx = 0.4;
                unk158 = 0;
            }
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 5:
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = (unk3454 == 1) * 0.015 + 0.045;
            vy = -2.7 - (unk3454 == 1) * 0.6;
            vx = (unk3454 == 1) * 0.1 + 0.8;
            if (unk158 == 1) {
                vx = 1.2;
                unk158 = 0;
            }
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 6:
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = (unk3454 == 1) * 0.015 + 0.045;
            vy = -2.7 - (unk3454 == 1) * 0.6;
            vx = -0.8 - (unk3454 == 1) * 0.1;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 7:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        CPlayer::FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 8:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        CPlayer::FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 9:
        vy = vy + ay;
        unk158 = 0;
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
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xd:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        CPlayer::FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0xe:
        ay = (unk3454 == 1) * 0.015 + 0.045;
        if (frame == 0 && timer == 0) {
            vy = -2.7 - (unk3454 == 1) * 0.6;
            vx = 0.0;
            unk158 = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xf:
        ay = (unk3454 == 1) * 0.015 + 0.045;
        if (frame == 0 && timer == 0) {
            vy = -2.7 - (unk3454 == 1) * 0.6;
            vx = (unk3454 == 1) * 0.1 + 0.8;
            unk158 = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x10:
        ay = (unk3454 == 1) * 0.015 + 0.045;
        if (frame == 0 && timer == 0) {
            vy = -2.7 - (unk3454 == 1) * 0.6;
            vx = -0.8 - (unk3454 == 1) * 0.1;
            unk158 = 0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x2f:
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
    case 0x32:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.1;
            if (unk120 != 0) {
                unk118 -= 10.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x33:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.5;
            if (unk120 != 0) {
                unk118 -= 20.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x34:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.8;
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x35:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.1;
            if (unk120 != 0) {
                unk118 -= 10.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x36:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.5;
            if (unk120 != 0) {
                unk118 -= 20.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x37:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.8;
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x38:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.1;
            if (unk120 != 0) {
                unk118 -= 10.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x39:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.5;
            if (unk120 != 0) {
                unk118 -= 20.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x3a:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            vx = (2.0 - (*m_opponent)->m_proration / 10000.0) * -1.8;
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
        }
        vy = 0.0;
        y = 0.0;
        vx += 0.06;
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - (y < 0.0) * 0.2) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x3b:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x3c:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x3d:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x3e:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x3f:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x40:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x41:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x42:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = vy * 0.75 + unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x43:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x44:
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = unkc0;
        vy = unkc8;
        timer++;
        if ((char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x45:
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = unkc0;
        vy = unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x46:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            m_gauge = m_gauge + 0x1e;
            unk3138++;
            unk124 = unk124 + 0x78;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x47:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x48:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        unk158 = 0;
        vx = 0.0;
        vy = 0.0;
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x49:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        unk158 = 0;
        vx = 0.0;
        vy = 0.0;
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x4a:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        unk158 = 0;
        vx = 0.0;
        vy = 0.0;
        if (x - 20.0 <= 0.0 || x + 20.0 >= 639.0) {
            unkb8 = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x4b:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            if (unk120 != 0) {
                unk118 -= 30.0;
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
            unkb8 = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x4c:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            if (unk120 != 0) {
                unk118 -= 30.0;
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
            unkb8 = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x4d:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            if (unk120 != 0) {
                unk118 -= 30.0;
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
            unkb8 = (1.0 - ((*m_opponent)->y < 0.0) * 0.25) * vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x51:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x1f3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x1e;
            vx = unkc0;
            vy = unkc8;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x52:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            m_playSound = 0x1e;
            vy = -0.45;
            vx = -0.1;
            unk3138++;
            m_gauge = m_gauge + 0x1e;
        }
        if (frame == 4 && timer == 0) {
            vx = unkc0;
            vy = unkc8;
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
            if (frame == 4 && unk3138 < 8) {
                frame = 0;
                unk3138++;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 4) {
            y = 0.0;
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x53:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
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
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x54:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
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
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x55:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
            m_playSound = 0x21;
            vx = unkc0;
            vy = unkc8;
            m_gauge = m_gauge + 0x1e;
        }
        vy += 0.04;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x56:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                unk3144 = 1;
            }
            if (unk3138 == 0) {
                if (unk120 != 0) {
                    unk118 -= 30.0;
                }
                m_playSound = 0x21;
                vx = unkc0;
                vy = unkc8;
                m_gauge = m_gauge + 0x1e;
                unk3138++;
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
            if (unk12c != 0) {
                pattern = 0x61;
                StartPattern();
            } else {
                pattern = 0x62;
                StartPattern();
            }
        }
        break;
    case 0x57:
        if (frame == 0 && timer == 0) {
            l50.type = 0x1ef;
            l50.x = 60.0;
            l50.y = 40.0;
            l50.screen = 1;
            l50.unk18 = 1;
            l50.scale = 0;
            l50.layer = 0;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x60:
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8 - 1) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x61:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::ShakeScreen(3, 0);
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
                pattern = 0x63;
                StartPattern();
            }
        }
        break;
    case 0x62:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::ShakeScreen(3, 0);
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
                pattern = 0x63;
                StartPattern();
            }
        }
        break;
    case 0x63:
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
            pattern = 0x60;
            StartPattern();
            unk158 = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0x60;
                StartPattern();
            }
        }
        break;
    case 0x96:
        if (m_inputY == 1) {
            pattern = 0x99;
        }
        if (m_inputY != 1) {
            pattern = 0x96;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            unkb8 = vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x97:
        if (m_inputY == 1) {
            pattern = 0x9a;
        }
        if (m_inputY != 1) {
            pattern = 0x97;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            unkb8 = vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x98:
        if (m_inputY == 1) {
            pattern = 0x9b;
        }
        if (m_inputY != 1) {
            pattern = 0x98;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            unkb8 = vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0x99:
        if (m_inputY == 1) {
            pattern = 0x99;
        }
        if (m_inputY != 1) {
            pattern = 0x96;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            unkb8 = vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x9a:
        if (m_inputY == 1) {
            pattern = 0x9a;
        }
        if (m_inputY != 1) {
            pattern = 0x97;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            unkb8 = vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x9b:
        if (m_inputY == 1) {
            pattern = 0x9b;
        }
        if (m_inputY != 1) {
            pattern = 0x98;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            unkb8 = vx;
        } else {
            unkb8 = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x9c:
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
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x9d:
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
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x9e:
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
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            CPlayer::StartAfterimages(3);
        }
        if (m_inputY == -1 && frame > 0) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            ay = 0.0;
        }
        vx = (unk3454 == 1) * 0.2 + 1.7;
        unk158 = 1;
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && unk313c >= 0x78) {
            pattern = 0xb2;
            StartPattern();
        }
        if (m_inputX != facing && unk3138 >= 0x3c) {
            pattern = 0xb2;
            StartPattern();
        }
        break;
    case 0xa4:
        CPlayer::StartAfterimages(2);
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -1.6 - (unk3454 == 1) * 0.2;
            vy = -1.0;
            ay = 0.04;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            m_playSound = 9;
            CPlayer::StopMoving();
            y = 0.0;
            frame = 9;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0) {
            m_playSound = 0x15;
            if (unk3138 == 0) {
                vx = (unk3454 == 1) * 0.2 + 1.5;
                CPlayer::StartAfterimages(3);
                vy = 0.0;
                ay = 0.0;
            }
        }
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && unk313c >= 0x64) {
            pattern = 9;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
            pattern = 9;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0) {
            m_playSound = 0x15;
            if (unk3138 == 0) {
                vx = -1.5 - (unk3454 == 1) * 0.2;
                vy = 0.0;
                ay = 0.0;
                CPlayer::StartAfterimages(3);
            }
        }
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && unk313c >= 0x78) {
            pattern = 9;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa7:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk158 = 0;
            if (unk120 == 1) {
                m_proration = unk118 * 5.0 + m_proration;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            CPlayer::FillBackground(0xb0, 3);
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
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xa8:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            unk14e = 0;
            unkb8 = 0.0;
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
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa9:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            unk14e = 0;
            unkb8 = 0.0;
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
                CPlayer::FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xaa:
        if (frame == 0 && timer == 0) {
            unk3138 = (int)(vx * 100.0);
            unk313c = (int)(vy * 100.0);
            vx = 0.0;
            vy = 0.0;
            if (ay == 0.0) {
                ay = 0.035;
            }
            unk14e = 0;
            unkb8 = 0.0;
            unk14c = 0x3c;
        }
        if (unk14c == 0 && unk3140 == 0) {
            unk3140++;
            vx = unk3138 * 0.01;
            vy = unk313c * 0.01;
        }
        if (unk14c == 0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            pattern = 0xa9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xab:
        if (frame == 0 && timer == 0) {
            unk3138 = (int)(vx * 100.0);
            unk313c = (int)(vy * 100.0);
            vx = 0.0;
            vy = 0.0;
            if (unk120 == 1) {
                m_proration = unk118 * 5.0 + m_proration;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            CPlayer::FillBackground(0xb0, 3);
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
                pattern = 9;
                vx = unk3138 * 0.01;
                vy = unk313c * 0.01;
                ay = 0.035;
                StartPattern();
            }
        }
        break;
    case 0xb2:
        vx -= 0.03;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                break;
            }
        }
        break;
    case 0xb4:
        if (frame == 0 && timer == 0) {
            CPlayer::StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 9;
            m_playSound = 9;
        }
        timer++;
        if (timer >= l4) {
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
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
            }
        }
        break;
    case 0xc8:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xc9:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xca:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult == 3) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                x = facing * 0xa + x;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcb:
        if (unk158 == 0 && frame < 2) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1 && frame < 2) {
            vx -= 0.06;
        } else {
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 2.0;
        }
        if (frame > 2 && vx > 0.0) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcc:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
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
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcd:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
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
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xce:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult == 3) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 2;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcf:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            CPlayer::FaceOpponent();
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xd0:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            CPlayer::FaceOpponent();
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 4;
                StartPattern();
                frame = 7;
            }
        }
        break;
    case 0xd1:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            CPlayer::FaceOpponent();
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
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
            pattern = 0xd;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 4;
                StartPattern();
                frame = 7;
            }
        }
        break;
    case 0xd2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 3.0;
        }
        vx -= 0.055;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xd3:
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
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
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xd4:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = 0xd5;
            StartPattern();
            CPlayer::StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            CPlayer::ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk2c = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
            pattern = 0xd6;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xd5:
        ay = 0.042;
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = -1.0;
            vy = -2.4;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xd6:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk2c = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
            }
            if (x < 60.0) {
                x = 60.0;
            }
            CPlayer::StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->x = facing * 0x28 + x;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
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
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xdd:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 1.0;
            vy = -2.0;
            ay = 0.04;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame == 4) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 5;
            timer = 0;
            break;
        }
        if (x > 600.0 || x < 40.0) {
            vx = 0.0;
        }
        if (frame == 1) {
            (*m_opponent)->x = facing * 0x23 + x;
        }
        if (frame == 2) {
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = y - 68.0;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->StartPattern();
        }
        if (frame == 3) {
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->StartPattern();
        }
        if (frame == 4) {
            (*m_opponent)->x = facing * 0xa + x;
            (*m_opponent)->y = y - 90.0;
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->StartPattern();
        }
        if (frame == 5) {
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->pattern = 0x69;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = 0x62;
                (*m_opponent)->StartPattern();
                CPlayer::DealDamage(0x4b0, 750.0);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xe6:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe7:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe8:
        unk158 = 0;
        CPlayer::StartAfterimages(3);
        if (vx > 0.0 && frame > 3) {
            vx -= 0.035;
        } else {
            unk158 = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe9:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xea:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xeb:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            StartPattern();
            break;
        }
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xf8:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            CPlayer::StopMoving();
            (*m_opponent)->unk128 = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = 0xf9;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x95)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0xd1;
                frame = 2;
            }
        }
        break;
    case 0xf9:
        unk13e = 0x1e;
        (*m_opponent)->unk13e = 0x1e;
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 0 && timer == 0) {
            vx = 1.0;
            vy = -2.0;
            ay = 0.04;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame == 1) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 2;
            timer = 0;
            break;
        }
        if (x > 600.0 || x < 40.0) {
            vx = 0.0;
        }
        if (frame == 0) {
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->StartPattern();
        }
        if (frame == 1) {
            (*m_opponent)->x = facing * 0xa + x;
            (*m_opponent)->y = y - 90.0;
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->StartPattern();
        }
        if (frame == 2) {
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->pattern = 0x69;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = 0x62;
                (*m_opponent)->StartPattern();
                CPlayer::DealDamage(0x578, 500.0);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xfa:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->unk14a = 0x5a;
            (*m_opponent)->x = facing * 0x28 + x;
            (*m_opponent)->unk128 = 1;
            (*m_opponent)->StopMoving();
            timer = 0;
            frame = 3;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)((int)y - 0x29);
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
            if (frame == 2 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x96)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame == 4) {
                frame = 0;
                pattern = 0xfe;
                frame = 1;
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -81.0;
                (*m_opponent)->pattern = 0x67;
                break;
            }
            if (frame == 3) {
                frame = 4;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xfb:
        CPlayer::StopMoving();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = -62.0;
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = x - facing * 0xb;
                (*m_opponent)->y = -57.0;
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                (*m_opponent)->x = x - facing * 0xb;
                (*m_opponent)->y = -52.0;
                (*m_opponent)->pattern = 0x68;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = x - facing * 0x19;
                (*m_opponent)->y = -55.0;
                (*m_opponent)->pattern = 0x68;
                (*m_opponent)->StartPattern();
            }
            if (frame == 5) {
                (*m_opponent)->x = x - facing * 0x25;
                (*m_opponent)->y = -54.0;
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->unkc0 = 0.5;
                (*m_opponent)->unkc8 = -2.6;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (m_attackResult == 3) {
            CPlayer::Unk410a80(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 0x32 + x;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk128 = 1;
            StartPattern();
            pattern = 0xfe;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 5 && timer == 0) {
                x = facing * 0xf + x;
            }
            if (frame == 6 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (m_attackResult == 3) {
            CPlayer::Unk410a80(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 0x28 + x;
            (*m_opponent)->y = -80.0;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            StartPattern();
            pattern = 0xfe;
            frame = 2;
            (*m_opponent)->unk128 = 1;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6 && (*m_opponent)->y < 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xfe:
        CPlayer::Unk410a80(0x32, 3);
        if (unk3138 == 0 && frame == 2) {
            if ((*m_opponent)->m_pressA == 1) {
                unk3138 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                unk3138 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                unk3138 = 3;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -81.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unk128 = 1;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -80.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unk128 = 1;
            }
            if (frame >= x8) {
                pattern = 0x101;
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unk128 = 1;
                if (m_command == 0xa || m_command == 0x1e) {
                    pattern = 0xff;
                    frame = 0;
                    timer = 0;
                    (*m_opponent)->pattern = 0x67;
                    if (unk3138 == 3) {
                        StartPattern();
                        pattern = 0x102;
                        m_playSound = 0x1a;
                        (*m_opponent)->pattern = 0x9e;
                        (*m_opponent)->StartPattern();
                        (*m_opponent)->StopMoving();
                        break;
                    }
                    break;
                }
                if (m_command == 0xb || m_command == 0x1f) {
                    if (unk3138 == 2) {
                        StartPattern();
                        pattern = 0x102;
                        m_playSound = 0x1a;
                        (*m_opponent)->pattern = 0x9e;
                        (*m_opponent)->StartPattern();
                        (*m_opponent)->StopMoving();
                        break;
                    }
                    pattern = 0xfb;
                    (*m_opponent)->pattern = 0x67;
                    frame = 1;
                    timer = 0;
                    (*m_opponent)->x = facing * 0xb + x;
                    (*m_opponent)->y = -62.0;
                    (*m_opponent)->pattern = 0x64;
                    break;
                }
                (*m_opponent)->y = -40.0;
                frame = 0;
                timer = 0;
            }
        }
        break;
    case 0xff:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk3138 = 0;
        }
        CPlayer::StopMoving();
        if (frame == 6 && timer == 0) {
            CPlayer::DealDamage(0x5dc, 1000.0);
            m_playSound = 2;
            l50.type = 0;
            l50.x = (double)((int)x - facing * 7);
            l50.y = (double)((int)y + 7);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame < 0xa && unk3138 == 0) {
            if ((*m_opponent)->m_pressA == 1) {
                unk3138 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                unk3138 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                unk3138 = 3;
            }
        }
        if (frame == 0xa && timer == 0) {
            if ((m_command == 0xa || m_command == 0x1e) && m_gauge >= 0x3e8) {
                if (unk3138 == 3) {
                    StartPattern();
                    pattern = 0x102;
                    m_playSound = 0x1a;
                    (*m_opponent)->pattern = 0x9e;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->StopMoving();
                    break;
                }
                frame = 0;
                timer = 0;
                pattern = 0x12c;
                break;
            }
            if ((m_command == 0xb || m_command == 0x1f) && m_gauge >= 0x3e8) {
                if (unk3138 == 2) {
                    StartPattern();
                    pattern = 0x102;
                    m_playSound = 0x1a;
                    (*m_opponent)->pattern = 0x9e;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->StopMoving();
                    break;
                }
                frame = 0;
                timer = 0;
                pattern = 0x132;
                facing = -facing;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x24 + x;
                (*m_opponent)->y = -78.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x2b + x;
                (*m_opponent)->y = -75.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                (*m_opponent)->x = facing * 0x2d + x;
                (*m_opponent)->y = -69.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = facing * 0x17 + x;
                (*m_opponent)->y = -66.0;
                (*m_opponent)->pattern = 0x68;
                (*m_opponent)->StartPattern();
                (*m_opponent)->facing = facing;
            }
            if (frame == 5) {
                (*m_opponent)->x = x - facing * 0xa;
                (*m_opponent)->y = -62.0;
                (*m_opponent)->pattern = 0x69;
                (*m_opponent)->StartPattern();
            }
            if (frame == 6) {
                (*m_opponent)->x = x - 0.0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = 0x62;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0 && unk3138 == 1) {
            StartPattern();
            pattern = 0x102;
            m_playSound = 0x1a;
            (*m_opponent)->pattern = 0x9e;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            break;
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->StopMoving();
            (*m_opponent)->unkc0 = -3.0;
            (*m_opponent)->unkc8 = -2.0;
            (*m_opponent)->x = facing * 0x1e + x;
            (*m_opponent)->y = -40.0;
            CPlayer::ShakeScreen(0xa, 0xa);
            CPlayer::DealDamage(0x708, 700.0);
            m_attackResult = 3;
            m_playVoice = 2;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x50);
            l50.scale = 2;
            l50.unk18 = facing;
            l50.unk0 = 1;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x101:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
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
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x102:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        if (frame > 5) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult == 3 && frame == 6) {
            CPlayer::StopMoving();
            CPlayer::Unk410a80(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->x = facing * 0x32 + x;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk128 = 1;
            StartPattern();
            pattern = 0xfe;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 3) {
                vx = 1.3;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x10f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk158 = 0;
            m_attackResult = 0;
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 8) {
                m_playVoice = 1;
                l50.type = 0x191;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x3a);
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 1;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xa && unk3138 < 3) {
                unk3138++;
                frame = frame - 2;
                if (unk3138 == 2) {
                    m_attackResult = 3;
                }
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x110:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 8 && timer == 0) {
            m_playVoice = 1;
            l50.type = 0x192;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3a);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xa && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 8 && timer == 0) {
            m_playVoice = 1;
            l50.type = 0x193;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3a);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 8) {
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xa && unk3138 < 3) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x112:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 3) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 3) {
            if (m_attackResult > 0 && unk313c == 0) {
                unk3140 = 0x2d;
                unk313c = 1;
            }
            if (m_attackResult > 0 && unk3140 > 0) {
                unk3140--;
            }
            if (m_attackResult > 0 && unk3140 <= 0 && unk313c > 0) {
                m_attackResult = 0;
                unk313c = 0;
            }
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 4) {
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 0;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 4) {
                vx = 2.5;
                m_hitsLeft = 3;
                m_attackResult = 0;
            }
            if (frame == 8 && unk3138 < 4) {
                unk3138++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x113:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 3) {
            vx -= 0.018;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 3) {
            if (m_attackResult > 0 && unk313c == 0) {
                unk3140 = 0x2d;
                unk313c = 1;
            }
            if (m_attackResult > 0 && unk3140 > 0) {
                unk3140--;
            }
            if (m_attackResult > 0 && unk3140 <= 0 && unk313c > 0) {
                m_attackResult = 0;
                unk313c = 0;
            }
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            if (frame == 4) {
                l50.type = 0x195;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 0;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 4) {
                vx = 2.8;
                m_hitsLeft = 3;
                m_attackResult = 0;
            }
            if (frame == 8 && unk3138 < 7) {
                unk3138++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x114:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        if (frame > 7) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4 - ((unk3454 == 1) << 1)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                unk13c = 0x3c;
                l50.type = 0x196;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 0;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 4) {
                m_hitsLeft = 0xf;
            }
            if (frame == 8 && unk3138 < 5) {
                unk3138++;
                frame = frame - 4;
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 8;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            unk3138 = 0;
        }
        if ((*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 0xa && unk3138 == 0) {
            if ((*m_opponent)->m_pressA == 1) {
                unk3138 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                unk3138 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                unk3138 = 3;
            }
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame < 0xe) {
            unk140 = 3;
        }
        if ((frame == 2 || frame == 5 || frame == 8 || frame == 0xb || frame == 0xe) && timer == 0) {
            m_playSound = 2;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 7);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (frame == 2 || frame == 5 || frame == 8 || frame == 0xb) {
                CPlayer::DealDamage(0x32, 1000.0);
                CPlayer::ShakeScreen(2, 2);
            }
            if (frame == 0xe) {
                CPlayer::DealDamage(0x1f4, 1000.0);
                CPlayer::ShakeScreen(0xa, 0xa);
                unk140 = 0;
            }
        }
        if (frame > 1 && frame < 8 && (m_command == 0x64 || m_command == 0x6e) && m_gauge >= 0x3e8) {
            if (unk3138 == 3) {
                StartPattern();
                pattern = 0x102;
                m_playSound = 0x1a;
                (*m_opponent)->pattern = 0x9e;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = 0x12e;
            break;
        }
        if (frame > 1 && frame < 8 && (m_command == 0x65 || m_command == 0x6f) && m_gauge >= 0x3e8) {
            if (unk3138 == 2) {
                StartPattern();
                pattern = 0x102;
                m_playSound = 0x1a;
                (*m_opponent)->pattern = 0x9e;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = 0x133;
            facing = -facing;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && unk313c < 0xa) {
                unk313c++;
                frame = 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            if (unk3138 == 1) {
                StartPattern();
                pattern = 0x102;
                m_playSound = 0x1a;
                (*m_opponent)->pattern = 0x9e;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
        }
        if ((*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x24);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            CPlayer::DealDamage(0x960, 600.0);
            CPlayer::ShakeScreen(5, 5);
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unkc0 = -3.0;
            (*m_opponent)->unkc8 = -8.0;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12e:
        if (frame < 7) {
            unk140 = 3;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 6 && timer == 0x3c) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 0x708);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x57);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0xb4) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x57);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = 1;
            SpawnObject(&l50);
            m_playVoice = 4;
        }
        if (frame == 6 && (timer == 0x10e || timer == 0x13b || timer == 0x168 || timer == 0x186 || timer == 0x1a4 || timer == 0x1c2 || timer == 0x1d1 || timer == 0x1e0)) {
            l50.type = 0x199;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x50) + 7) * facing);
            l50.y = (double)((int)y - 0x39 - (WORD)CPlayer::Random(0, 0x50));
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = 1;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->facing = -facing;
                (*m_opponent)->x = facing * 0x2e + x;
                (*m_opponent)->y = -38.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
            }
            if (frame == 4) {
                (*m_opponent)->x = facing * 0x31 + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
            }
            if (frame == 5) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = 0x65;
                (*m_opponent)->StartPattern();
            }
            if (frame == 6) {
                (*m_opponent)->x = facing * 0x25 + x;
                (*m_opponent)->y = -87.0;
                (*m_opponent)->pattern = 0x65;
                (*m_opponent)->StartPattern();
            }
            if (frame == 7) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x25);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -6.0;
                (*m_opponent)->unkc8 = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                CPlayer::ShakeScreen(0x14, 0xa);
                CPlayer::DealDamage(0x1068, 850.0);
                m_playVoice = 2;
                unk140 = 0;
                CPlayer::FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12f:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            CPlayer::Unk410a80(0x32, 0x78);
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x13);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if (frame == 5 && timer == 0) {
            vx = 6.0;
        }
        if (frame > 8) {
            vx -= 0.2;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3) {
            CPlayer::ShakeScreen(0xa, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x130:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            CPlayer::Unk410a80(0x32, 0x78);
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x13);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if (frame == 5 && timer == 0) {
            vx = 6.0;
        }
        if (frame > 8) {
            vx -= 0.2;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3) {
            CPlayer::ShakeScreen(0xa, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x131:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            CPlayer::Unk410a80(0x32, 0x78);
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x13);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame >= 4) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 5 && timer == 0) {
            vx = 6.0;
        }
        if (frame > 8) {
            vx -= 0.2;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3) {
            CPlayer::ShakeScreen(0xa, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x132:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            unk3138 = 0;
        }
        if (frame < 0xa && unk3138 == 0) {
            if ((*m_opponent)->m_pressA == 1) {
                unk3138 = 1;
            }
            if ((*m_opponent)->m_pressB == 1) {
                unk3138 = 2;
            }
            if ((*m_opponent)->m_pressC == 1) {
                unk3138 = 3;
            }
        }
        if ((*m_opponent)->pattern == 0x63 && frame < 9) {
            (*m_opponent)->timer = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 4 && timer == 0) {
            CPlayer::DealDamage(0x708, 1000.0);
            CPlayer::ShakeScreen(0xa, 0xa);
            (*m_opponent)->unk14a = 0xb4;
            m_playSound = 0x16;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y + 8);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (frame == 8 && (m_command == 0x64 || m_command == 0x6e) && m_gauge >= 0x3e8) {
            if (unk3138 == 3) {
                StartPattern();
                pattern = 0x102;
                m_playSound = 0x1a;
                (*m_opponent)->pattern = 0x9e;
                (*m_opponent)->unk14a = 0;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = 0x13e;
            break;
        }
        if (frame == 8 && (m_command == 0x65 || m_command == 0x6f) && m_gauge >= 0x3e8) {
            if (unk3138 == 2) {
                StartPattern();
                pattern = 0x102;
                m_playSound = 0x1a;
                (*m_opponent)->pattern = 0x9e;
                (*m_opponent)->unk14a = 0;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                break;
            }
            StartPattern();
            pattern = 0x13f;
            CPlayer::FaceOpponent();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x133:
        if ((*m_opponent)->pattern == 0x63 && frame < 9) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 4 && vy > 0.0) {
            timer = 0;
            frame = 4;
        }
        if (y < 0.0 && unk14c == 0) {
            vy = vy + ay;
        }
        if (frame == 4 && unk14c == 0 && unk3138 == 1) {
            vy = 10.0;
            unk3138++;
        }
        if (frame == 4 && vy > 0.0 && y > -90.0 && unk3138 == 0) {
            unk3138++;
            vy = 0.0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 0x708);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 4 && y + vy > 0.0) {
            CPlayer::StopMoving();
            timer = 0;
            frame = 5;
            y = 0.0;
            CPlayer::DealDamage(0x1194, 1000.0);
            CPlayer::ShakeScreen(0xa, 0xa);
            (*m_opponent)->unk14a = 0x12c;
            m_playSound = 0x16;
            l50.type = 0x19b;
            l50.x = (double)((int)x + facing * 0x11);
            l50.y = (double)((int)y + 0xb);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        CPlayer::Unk410a80(-0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -10.0;
                ay = 0.045;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FillBackground(0xb0, 0);
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
            unk158 = 0;
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x55);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0xa) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 0xa && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 0xa;
            break;
        }
        if (m_attackResult == 3 && frame == 0xc) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0x708;
            CPlayer::StopMoving();
            CPlayer::Unk410a80(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 0x18 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk128 = 1;
            StartPattern();
            pattern = 0x136;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 1.3;
            }
            if (frame == 0xa && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1c + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = 0x67;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 4) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0xc);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -4.0;
                (*m_opponent)->unkc8 = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                CPlayer::ShakeScreen(0xa, 5);
                CPlayer::DealDamage(0x8fc, 850.0);
                m_playVoice = 2;
                unk140 = 0;
                (*m_opponent)->unk14a = 0;
                CPlayer::FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
            unk158 = 0;
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x55);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0xa) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 0xa && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 0xa;
            break;
        }
        if (m_attackResult == 3 && frame == 0xc) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0x708;
            CPlayer::StopMoving();
            CPlayer::Unk410a80(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 0x18 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk128 = 1;
            StartPattern();
            pattern = 0x138;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 1.7;
            }
            if (frame == 0xa && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1c + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = 0x67;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0xc);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -4.0;
                (*m_opponent)->unkc8 = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                CPlayer::ShakeScreen(0xf, 0xa);
                CPlayer::DealDamage(0xce4, 850.0);
                m_playVoice = 2;
                unk140 = 0;
                (*m_opponent)->unk14a = 0;
                CPlayer::FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
            unk158 = 0;
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x55);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 0xa) {
            vx -= 0.015;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame < 0xa && frame > 5 && ((*m_opponent)->x - x < 80.0 && facing == 1 || x - (*m_opponent)->x < 80.0 && facing == -1)) {
            timer = 0;
            frame = 0xa;
            break;
        }
        if (m_attackResult == 3 && frame == 0xc) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0x708;
            CPlayer::StopMoving();
            CPlayer::Unk410a80(0x32, 3);
            m_attackResult = 0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = facing * 0x18 + x;
            (*m_opponent)->y = -40.0;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk128 = 1;
            StartPattern();
            pattern = 0x13a;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x45);
            l50.y = (double)((int)y - 0x23);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        m_game->Unk4080c0(0xf);
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 0;
            frame++;
            if (frame == 6) {
                vx = 2.1;
            }
            if (frame == 0xa && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13a:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 4) {
            CPlayer::FillBackground(0xb0, 3);
        }
        if (frame == 3 && timer == 0xb4) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x57);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = 1;
            SpawnObject(&l50);
            m_playVoice = 4;
        }
        if (frame == 3 && (timer == 0x10e || timer == 0x13b || timer == 0x168 || timer == 0x186 || timer == 0x1a4 || timer == 0x1c2 || timer == 0x1d1 || timer == 0x1e0)) {
            l50.type = 0x199;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x50) + 7) * facing);
            l50.y = (double)((int)y - 0x39 - (WORD)CPlayer::Random(0, 0x50));
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = 1;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        CPlayer::Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1c + x;
                (*m_opponent)->y = -56.0;
                (*m_opponent)->pattern = 0x67;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x28 + x;
                (*m_opponent)->y = -93.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 3) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -92.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0xc);
                l50.y = (double)((int)y - 0x57);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -4.0;
                (*m_opponent)->unkc8 = -2.0;
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = -40.0;
                CPlayer::ShakeScreen(0x14, 0xa);
                CPlayer::DealDamage(0x1324, 850.0);
                m_playVoice = 2;
                unk140 = 0;
                (*m_opponent)->unk14a = 0;
                CPlayer::FillBackground(0xb0, 0);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            CPlayer::ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x19c;
            l50.x = (double)((int)x + facing * 0x3c);
            if (facing * 0x3c + x > 620.0) {
                l50.x = 620.0;
            }
            if (facing * 0x3c + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && (timer == 0 || timer == 0x3c)) {
            CPlayer::ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x19d;
            l50.x = (double)((int)x + (timer + 0x3c) * facing);
            if ((timer + 0x3c) * facing + x > 620.0) {
                l50.x = 620.0;
            }
            if ((timer + 0x3c) * facing + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 5 && (timer == 0 || timer == 0x3c || timer == 0x78)) {
            CPlayer::ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x19e;
            l50.x = (double)((int)x + (timer + 0x3c) * facing);
            if ((timer + 0x3c) * facing + x > 620.0) {
                l50.x = 620.0;
            }
            if ((timer + 0x3c) * facing + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x17);
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 4 && frame < 0xb) {
            (*m_opponent)->pattern = 0x63;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x28 + x;
            if (x > 610.0 || x < 30.0) {
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -6.0;
                (*m_opponent)->unkc8 = -3.5;
                (*m_opponent)->y = -5.0;
                CPlayer::ShakeScreen(0x14, 0xa);
                CPlayer::DealDamage(0xbb8, 1000.0);
                m_playVoice = 2;
                frame = 0xb;
                timer = 0;
                vx = -6.0;
                vy = -3.5;
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y - 0xb);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
        }
        if ((frame == 6 || frame == 8 || frame == 0xa) && timer == 0) {
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x50, 1000.0);
        }
        if (y < 0.0) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x62;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 3.5;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x50);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xb) {
                frame = frame - 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x13f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 6);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 5 && (timer == 0 || timer == 0x3c || timer == 0x78)) {
            CPlayer::ShakeScreen(5, 0);
            m_playSound = 0x16;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + (timer + 0x3c) * facing);
            if ((timer + 0x3c) * facing + x > 620.0) {
                l50.x = 620.0;
            }
            if ((timer + 0x3c) * facing + x < 20.0) {
                l50.x = 20.0;
            }
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x19f;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (frame == 5 && timer == 0xf) {
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->y = -2.0;
            (*m_opponent)->unkc8 = -1.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x140:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame < 4) {
            unk3138--;
        }
        if (frame == 0 && timer == 0) {
            unk3454 = 1;
            unk3138 = 0x42;
            CPlayer::Unk410a80(0x32, 0x78);
            unk14c = 0xb4;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x35);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
    }
}
