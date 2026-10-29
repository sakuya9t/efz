// CSayuri::Vf6 (0x434060-0x4463df), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CSayuri's
// .rdata, which starts with its constructor's folder name (sayuri.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CSayuri::Vf6()
{
    WORD x8;
    WORD l4;

    if (unk14a > 0 || (*m_opponent)->unk14c > 0) {
        return;
    }
    EffectDesc l50;
    l4 = (short)anims[pattern].frames[frame].duration;
    x8 = anims[pattern].frameCount;
    CPlayer::Unk413090((EffectDesc*)&l50);
    switch (pattern) {
    default:
        vx = 0.0;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 1:
        unk158 = 0;
        vx = 0.7;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 2:
        unk158 = 0;
        vx = -0.7;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
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
        CPlayer::Unk40e630();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 4:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40e630();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.043;
            vy = -2.8;
            if (unk158 == 1) {
                vx = 0.4;
                unk158 = 0;
            }
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 5:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40e630();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.043;
            vy = -2.8;
            vx = 0.7;
            if (unk158 == 1) {
                vx = 1.1;
                unk158 = 0;
            }
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 6:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40e630();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.043;
            vy = -2.8;
            vx = -0.7;
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 7:
        vx = 0.0;
        vy = 0.0;
        CPlayer::Unk40e630();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 8:
        vx = 0.0;
        vy = 0.0;
        CPlayer::Unk40e630();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 9:
        vy = vy + ay;
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
            unk2c9 = 9;
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xd:
        vx = 0.0;
        vy = 0.0;
        CPlayer::Unk40e630();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0xe:
        ay = 0.043;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = 0.0;
            if (unk158 == 1) {
                vx = 0.4;
                unk158 = 0;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xf:
        ay = 0.043;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = 0.7;
            if (unk158 == 1) {
                vx = 1.1;
                unk158 = 0;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0x10:
        ay = 0.043;
        if (frame == 0 && timer == 0) {
            vy = -2.8;
            vx = -0.7;
            if (unk158 == 1) {
                unk158 = 0;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
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
            unk2c9 = 7;
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
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xa;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.1;
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
                Vf0();
            }
        }
        break;
    case 0x33:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xf;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.5;
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
                Vf0();
            }
        }
        break;
    case 0x34:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x14;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.8;
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
                Vf0();
            }
        }
        break;
    case 0x35:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xa;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.1;
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
                Vf0();
            }
        }
        break;
    case 0x36:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xf;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.5;
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
                Vf0();
            }
        }
        break;
    case 0x37:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x14;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.8;
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
                Vf0();
            }
        }
        break;
    case 0x38:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xa;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.1;
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
                Vf0();
            }
        }
        break;
    case 0x39:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xf;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.5;
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
                Vf0();
            }
        }
        break;
    case 0x3a:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x14;
            vx = (2.0 - (*m_opponent)->unk178 / 10000.0) * -1.8;
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
                Vf0();
            }
        }
        break;
    case 0x3b:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3c:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3d:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3e:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3f:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x40:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            Vf0();
            break;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x41:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            Vf0();
            break;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x42:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            Vf0();
            break;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x43:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            Vf0();
            break;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x44:
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        unk148 = unk148 + 3;
        vx = unkc0;
        vy = unkc8;
        timer++;
        if ((char)CPlayer::Unk40ff70() != 0) {
            pattern = 0x46;
            Vf0();
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x45:
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        unk148 = unk148 + 3;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x46:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            unk148 = unk148 + 0x1e;
            unk3138++;
            unk124 = unk124 + 0x78;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            unk2c9 = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x47:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x48:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
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
                Vf0();
            }
        }
        break;
    case 0x49:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
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
                Vf0();
            }
        }
        break;
    case 0x4a:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
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
                Vf0();
            }
        }
        break;
    case 0x4b:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            }
        }
        break;
    case 0x4c:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
            }
        }
        break;
    case 0x4d:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0x1e;
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
                Vf0();
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
            l50.unk21 = 1;
            Vf9(&l50);
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x52:
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            unk2c9 = 0x1e;
            vy = -0.45;
            vx = -0.1;
            unk3138++;
            unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x53:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
            unk2c9 = 0x21;
            vy = -1.5;
            vx = -0.8;
            unk148 = unk148 + 0x1e;
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
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x54:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
            unk2c9 = 0x21;
            vy = -1.5;
            vx = -0.8;
            unk148 = unk148 + 0x1e;
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
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x55:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
            unk2c9 = 0x21;
            vx = unkc0;
            vy = unkc8;
            unk148 = unk148 + 0x1e;
        }
        vy += 0.04;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            if (unk12c != 0) {
                pattern = 0x61;
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x56:
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3144 = 1;
            }
            if (unk3138 == 0) {
                if (unk120 != 0) {
                    unk118 -= 30.0;
                }
                unk2c9 = 0x21;
                vx = unkc0;
                vy = unkc8;
                unk148 = unk148 + 0x1e;
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
                Vf0();
            } else {
                pattern = 0x62;
                Vf0();
            }
        }
        break;
    case 0x57:
        if (frame == 0 && timer == 0) {
            l50.type = 0x1ef;
            l50.x = 60.0;
            l50.y = 40.0;
            l50.unk24 = 1;
            l50.unk18 = 1;
            l50.unk20 = 0;
            l50.unk21 = 1;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x60:
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8 - 1) {
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x61:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0x63;
                Vf0();
            }
        }
        break;
    case 0x62:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0x63;
                Vf0();
            }
        }
        break;
    case 0x63:
        if (unk108 > 0 && timer > 0x63) {
            pattern = 0x60;
            Vf0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 0x60;
                Vf0();
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
            unk148 = unk148 + 0xa;
            vx = -1.5;
            vy = 0.0;
            y = 0.0;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x38);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        if (unk3138 == 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && unk15c < 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x102;
            break;
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
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
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
            unk148 = unk148 + 0xf;
            vx = -1.8;
            vy = 0.0;
            y = 0.0;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x38);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        if (unk3138 == 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && unk15c < 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x102;
            break;
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
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
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
            unk148 = unk148 + 0x14;
            vx = -2.3;
            vy = 0.0;
            y = 0.0;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x38);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        if (unk3138 == 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && unk15c < 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x102;
            break;
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
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
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
            unk148 = unk148 + 0xa;
            vx = -1.5;
            vy = 0.0;
            y = 0.0;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x25);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        if (unk3138 == 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && unk15c < 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x102;
            break;
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
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
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
            unk148 = unk148 + 0xf;
            vx = -1.8;
            vy = 0.0;
            y = 0.0;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x25);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        if (unk3138 == 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && unk15c < 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x102;
            break;
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
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
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
            unk148 = unk148 + 0x14;
            vx = -2.3;
            vy = 0.0;
            y = 0.0;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x25);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        if (unk3138 == 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1) && unk15c < 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x102;
            break;
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
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x9c:
        if (frame == 0 && timer == 0) {
            vy = -2.6;
            unk148 = unk148 + 0xf;
            ay = 0.06;
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x43);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        vx = -1.2;
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
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
            l50.unk20 = 2;
            l50.unk21 = 0;
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
                Vf0();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
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
            l50.unk20 = 2;
            l50.unk21 = 0;
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
                Vf0();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xa1:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
            unk2c9 = 0x3e;
            unk3138++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
                ay = 0.035;
            }
        }
        break;
    case 0xa2:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            unk16c = 1;
        }
        if (frame == 8 && timer == 0) {
            CPlayer::Unk40f1e0();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
            unk2c9 = 0x3e;
            unk148 = unk148 - 0x3e8;
            unk3138++;
        }
        vy = vy + ay;
        if (y + vy > 0.0) {
            pattern = 0xd;
            Vf0();
            Vf0();
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x13) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            CPlayer::Unk4109d0(3);
        }
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = 1.5;
                vy = -1.5;
                unk2c9 = 0x11;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && unk313c >= 0x78) {
            pattern = 9;
            Vf0();
            vx = 0.5;
            vy = -0.7;
            ay = 0.03;
        }
        if (m_inputX != facing && unk3138 >= 0x27) {
            pattern = 9;
            Vf0();
            vx = 0.5;
            vy = -0.7;
            ay = 0.03;
        }
        break;
    case 0xa4:
        CPlayer::Unk4109d0(2);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 2 && vy + y >= 0.0 && unk3138 == 0) {
            CPlayer::Unk40f1e0();
            y = 0.0;
            unk3138++;
            unk2c9 = 9;
            frame = 5;
            timer = 0;
            unk3138++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -1.8;
                vy = -0.8;
                ay = 0.035;
            }
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                CPlayer::Unk40e630();
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 2.0;
            CPlayer::Unk4109d0(3);
            vy = 0.0;
            ay = 0.0;
            unk2c9 = 0x11;
        }
        timer++;
        unk3138++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && unk3138 >= 0x78) {
            pattern = 9;
            Vf0();
            vx = 1.3;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            vx = 1.3;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -2.0;
            vy = 0.0;
            ay = 0.0;
            CPlayer::Unk4109d0(3);
            unk2c9 = 0x11;
        }
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && unk313c >= 0x78) {
            pattern = 9;
            Vf0();
            vx = -0.9;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            vx = -0.9;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa7:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            if (unk120 == 1) {
                unk178 = unk118 * 5.0 + unk178;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x12;
            l50.type = 1;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 4;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xa8:
        if (frame == 0 && timer == 0) {
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
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x38);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xa9:
        if (frame == 0 && timer == 0) {
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
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            if (unk3148 == 0) {
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x1c);
                l50.y = (double)((int)y - 0x25);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3148 = 1;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                CPlayer::Unk40e630();
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
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
            CPlayer::Unk40f1e0();
            y = 0.0;
            pattern = 0xa9;
            break;
        }
        if (unk3148 == 0) {
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1c);
            l50.y = (double)((int)y - 0x43);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3148 = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
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
                unk178 = unk118 * 5.0 + unk178;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x12;
            l50.type = 1;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 4;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 9;
                CPlayer::Unk40e630();
                vx = unk3138 * 0.01;
                vy = unk313c * 0.01;
                ay = 0.035;
                Vf0();
            }
        }
        break;
    case 0xb2:
        vx -= 0.03;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_inputY == -1 && frame > 0) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                break;
            }
        }
        break;
    case 0xb4:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk4109d0(2);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 5) {
            CPlayer::Unk40f1e0();
            y = 0.0;
            timer = 0;
            frame = 5;
            unk2c9 = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
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
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xc9:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xca:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcb:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0x23;
            unk2c9 = 0x14;
            unk16c = 2;
            unk3138 = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 8) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcc:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xd;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xce:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 == 3) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcf:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd0:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xd;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd1:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            unk168 = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0x1e;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
        if (frame > 6) {
            vy = vy + ay;
        }
        if (frame == 2 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 6 && timer == 0) {
            unk148 = unk148 + 0x1e;
            unk2c9 = 0x14;
            unk16c = 3;
            vx = 1.0;
            vy = 1.0;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            CPlayer::Unk40f1e0();
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 0xa) {
                frame = 7;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd6:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk2c = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        if (frame == 2 && unk168 == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->unk14a = 0x3c;
            (*m_opponent)->x = facing * 0x28 + x;
            (*m_opponent)->facing = -facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x26);
            l50.y = (double)((int)y - 0x3a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 2 && (*m_opponent)->y == 0.0) {
                unk16c = 1;
            } else {
                unk16c = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xdd:
        CPlayer::Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x23 + x;
                (*m_opponent)->y = -57.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x15 + x;
                (*m_opponent)->y = -68.0;
                (*m_opponent)->pattern = 0x67;
            }
            if (frame == 3) {
                (*m_opponent)->x = x - facing * 0x1b;
                (*m_opponent)->y = -88.0;
                (*m_opponent)->pattern = 0x3b;
                CPlayer::Unk4105a0(0x47e, 750.0);
                (*m_opponent)->Vf0();
                (*m_opponent)->Unk40f1e0();
                (*m_opponent)->facing = facing;
                (*m_opponent)->unkc0 = -1.5;
                (*m_opponent)->unkc8 = -1.0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xe6:
        CPlayer::Unk4109d0(3);
        vx -= 0.06;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe7:
        CPlayer::Unk4109d0(3);
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            unk16c = 1;
            unk2c9 = 0x14;
            unk148 = unk148 + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe8:
        CPlayer::Unk4109d0(3);
        if (frame == 0 && timer == 0) {
            vx = 1.1;
            vy = -2.5;
        }
        vy += 0.055;
        if (y == 0.0 && frame > 0) {
            vy = 0.0;
        }
        if (frame == 0xb && timer == 0) {
            unk2c9 = 0x15;
            unk148 = unk148 + 0x23;
            unk16c = 1;
        }
        if (vy + y >= 0.0) {
            vy = 0.0;
            y = 0.0;
            pattern = 0x10d;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0xd;
                Vf0();
            }
        }
        break;
    case 0xf8:
        vy = vy + ay;
        if (frame == 1 && unk168 == 3) {
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->Vf0();
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x29);
            l50.y = (double)((int)y - 0x54);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x29 + x;
            (*m_opponent)->y = y - 84.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x95)) {
                unk16c = 1;
            } else {
                unk16c = 0;
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0xd1;
                frame = 2;
            }
        }
        break;
    case 0xf9:
        if (frame < 3) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0 && timer == 0) {
            if (unk3138 == 2) {
                l50.type = 0x1a6;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = (double)((int)y - 0x54);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk3138 > 2) {
                unk2c8 = 0xa;
            }
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 5) {
            CPlayer::Unk40f1e0();
            y = 0.0;
            Vf0();
            pattern = 0xd;
            break;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 68.0;
            (*m_opponent)->x = facing * 0x19 + x;
        }
        if (frame == 3 && timer == 0) {
            (*m_opponent)->unk14a = 0;
            (*m_opponent)->y = y - 31.0;
            (*m_opponent)->x = facing * 0x1f + x;
            (*m_opponent)->pattern = 0x45;
            CPlayer::Unk4105a0(0x4b0, 500.0);
            (*m_opponent)->Vf0();
            (*m_opponent)->unkc0 = -3.0;
            (*m_opponent)->unkc8 = 3.0;
        }
        if (frame == 5 && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 2 && unk3138 < 0xa) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 4 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x191;
            l50.x = facing * 0x23 + x;
            l50.y = -20.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 8);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 4 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x191;
            l50.x = facing * 0x23 + x;
            l50.y = -80.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.side = facing == 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 4 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x191;
            l50.x = facing * 0x23 + x;
            l50.y = -20.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 8);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 8 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x191;
            l50.x = facing * 0x23 + x;
            l50.y = -80.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.side = facing == 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if ((frame == 5 || frame == 6) && unk168 == 3) {
            frame = 7;
            timer = 0;
            unk168 = 0;
        }
        if (frame == 7 || frame == 8) {
            if (unk3140 <= 0) {
                l50.type = 0x22;
                l50.x = (double)((int)x + facing * 0xa - (WORD)CPlayer::Unk4108a0(0, 8));
                l50.y = (double)((int)y + 3 - (WORD)CPlayer::Unk4108a0(0, 6));
                l50.unk20 = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3140 = 2;
            }
            unk3140--;
            CPlayer::Unk410a80(0x32, 0x1e);
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = (27.0 + vx) * facing + x;
            (*m_opponent)->y = y - 50.0;
            (*m_opponent)->facing = -facing;
            if (x > 580.0 && facing == 1 || x < 60.0 && facing == -1) {
                if (x > 580.0 && facing == 1) {
                    x = 600.0;
                }
                if (x < 60.0 && facing == -1) {
                    x = 40.0;
                }
                timer = 0;
                frame = 9;
                CPlayer::Unk40f1e0();
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->x = (facing == 1) * 0x280;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = -0.9;
                CPlayer::Unk4105a0(0x3b6, 900.0);
                (*m_opponent)->unk14a = 0x5a;
                CPlayer::Unk410a10(6, 9);
                l50.type = 0;
                l50.x = facing * 0x19 + x;
                l50.y = -41.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk2c = 0x24;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk2c8 = 0;
                unk168 = 3;
            }
        }
        if (frame > 0xb && frame < 0x13) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vx *= 0.5;
                vy = 0.0;
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        if (frame > 0x12) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                vx = 1.8;
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0xa);
                l50.y = (double)((int)y + 4);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 7 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = 0x13;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame == 0xc) {
                vx = -2.0;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if ((frame == 5 || frame == 6) && unk168 == 3) {
            frame = 7;
            timer = 0;
            unk168 = 0;
        }
        if (frame == 7 || frame == 8) {
            if (unk3140 <= 0) {
                l50.type = 0x22;
                l50.x = (double)((int)x + facing * 0xa - (WORD)CPlayer::Unk4108a0(0, 8));
                l50.y = (double)((int)y + 3 - (WORD)CPlayer::Unk4108a0(0, 6));
                l50.unk20 = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3140 = 2;
            }
            unk3140--;
            CPlayer::Unk410a80(0x32, 0x1e);
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = (27.0 + vx) * facing + x;
            (*m_opponent)->y = y - 50.0;
            (*m_opponent)->facing = -facing;
            if (x > 580.0 && facing == 1 || x < 60.0 && facing == -1) {
                if (x > 580.0 && facing == 1) {
                    x = 600.0;
                }
                if (x < 60.0 && facing == -1) {
                    x = 40.0;
                }
                timer = 0;
                frame = 9;
                CPlayer::Unk40f1e0();
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->x = (facing == 1) * 0x280;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = -0.9;
                CPlayer::Unk4105a0(0x3b6, 900.0);
                (*m_opponent)->unk14a = 0x5a;
                CPlayer::Unk410a10(6, 9);
                l50.type = 0;
                l50.x = facing * 0x19 + x;
                l50.y = -41.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk2c = 0x24;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk2c8 = 0;
                unk168 = 3;
            }
        }
        if (frame > 0xb && frame < 0x13) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vx *= 0.5;
                vy = 0.0;
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        if (frame > 0x12) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                vx = 1.8;
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0xa);
                l50.y = (double)((int)y + 4);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 7 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = 0x13;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame == 0xc) {
                vx = -2.0;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if ((frame == 5 || frame == 6) && unk168 == 3) {
            frame = 7;
            timer = 0;
            unk168 = 0;
        }
        if ((frame == 5 || frame == 7) && unk313c <= 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk313c = 0xf;
        }
        unk313c--;
        if (frame == 7 || frame == 8) {
            if (unk3140 <= 0) {
                l50.type = 0x22;
                l50.x = (double)((int)x + facing * 0xa - (WORD)CPlayer::Unk4108a0(0, 8));
                l50.y = (double)((int)y + 3 - (WORD)CPlayer::Unk4108a0(0, 6));
                l50.unk20 = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3140 = 2;
            }
            unk3140--;
            CPlayer::Unk410a80(0x32, 0x1e);
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->x = (27.0 + vx) * facing + x;
            (*m_opponent)->y = y - 50.0;
            if (x > 580.0 && facing == 1 || x < 60.0 && facing == -1) {
                if (x > 580.0 && facing == 1) {
                    x = 600.0;
                }
                if (x < 60.0 && facing == -1) {
                    x = 40.0;
                }
                timer = 0;
                frame = 9;
                CPlayer::Unk40f1e0();
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x40;
                (*m_opponent)->x = (facing == 1) * 0x280;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = -0.9;
                CPlayer::Unk4105a0(0x546, 750.0);
                (*m_opponent)->unk14a = 0x5a;
                CPlayer::Unk410a10(6, 9);
                l50.type = 0;
                l50.x = facing * 0x19 + x;
                l50.y = -41.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk2c = 0x24;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk2c8 = 0;
                unk168 = 3;
            }
        }
        if (frame > 0xb && frame < 0x13) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vx *= 0.5;
                vy = 0.0;
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        if (frame > 0x12) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                vx = 2.9;
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = 0x13;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame == 0xc) {
                vx = -2.0;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk148 = unk148 + 0x23;
        }
        if (unk168 == 6 && frame < 6) {
            unk3150 = (*m_opponent)->pattern;
            Vf0();
            pattern = 0x12b;
            unk168 = 0;
            unk14c = 0xa0;
            unk2c9 = 3;
            unk2c8 = 2;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 9;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->unk128 = 1;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                Vf0();
                pattern = 0;
            }
        }
        break;
    case 0x101:
        if (frame == 1 && timer == 0) {
            unk16c = 3;
            unk148 = unk148 + 0x28;
        }
        if (frame == 4 && timer == 0) {
            vy = -3.0;
            ay = 0.045;
            vx = 2.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (y + vy > 0.0) {
                CPlayer::Unk40f1e0();
                y = 0.0;
                timer = 0;
                frame = 9;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x12b:
        CPlayer::Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 1) {
                (*m_opponent)->Vf0();
                (*m_opponent)->x = facing * 0x23 + x;
                (*m_opponent)->y = -57.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x15 + x;
                (*m_opponent)->y = -68.0;
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->Vf0();
            }
            if (frame == 3) {
                (*m_opponent)->x = x - facing * 0x1b;
                (*m_opponent)->y = -88.0;
                (*m_opponent)->pattern = 0x3b;
                CPlayer::Unk4105a0(0x258, 750.0);
                (*m_opponent)->Vf0();
                (*m_opponent)->Unk40f1e0();
                (*m_opponent)->facing = facing;
                (*m_opponent)->unkc0 = -0.8;
                (*m_opponent)->unkc8 = -2.0;
            }
            if (frame == 0xa) {
                facing = -facing;
            }
            if (frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x11) {
                unk2c9 = 0x14;
            }
            if (frame == 0x13) {
                unk2c9 = 0x1a;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            unk16c = 3;
            unk148 = unk148 + 0x28;
        }
        if (frame == 3 && timer == 0) {
            vy = -3.0;
            ay = 0.045;
            vx = 2.0;
        }
        if (y < 0.0) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
            vy = vy + ay;
            if (y + vy > 0.0) {
                CPlayer::Unk40f1e0();
                y = 0.0;
                timer = 0;
                frame = 0xb;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                l50.type = 0x1a5;
                l50.x = x;
                l50.y = y + 25.0;
                l50.unk18 = facing;
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                Vf9(&l50);
            }
            unk168 = 0;
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            unk2c8 = 8;
            CPlayer::Unk40f1e0();
            unk16c = 1;
            l50.type = 0x193;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 3 && timer == 0) {
            vx = 1.3;
            vy = 1.3;
            l50.type = 0x194;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (y + vy > 0.0 && frame > 3 && frame < 7) {
            CPlayer::Unk40f1e0();
            timer = 0;
            y = 0.0;
            frame = 7;
            unk2c9 = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 3 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 0;
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            unk2c8 = 8;
            CPlayer::Unk40f1e0();
            unk16c = 2;
            l50.type = 0x193;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame > 2 && unk168 == 2) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x10c;
            break;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.5;
            vy = 1.5;
            l50.type = 0x194;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (y + vy > 0.0 && frame > 3 && frame < 7) {
            CPlayer::Unk40f1e0();
            timer = 0;
            y = 0.0;
            frame = 7;
            unk2c9 = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 3 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 0;
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0 && unk313c == 0) {
            unk2c8 = 9;
            CPlayer::Unk40f1e0();
            unk16c = 1;
            l50.type = 0x193;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk313c++;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x194;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            vx = 1.7;
            vy = 1.7;
            unk16c = 2;
        }
        if (y + vy > 0.0 && frame > 3 && frame < 7) {
            CPlayer::Unk40f1e0();
            timer = 0;
            y = 0.0;
            frame = 7;
            unk2c9 = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 3 && unk3138 < 5) {
                frame = 1;
                unk3138++;
            }
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 3;
            }
        }
        break;
    case 0x106:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if (frame == 3 && timer == 0) {
            unk148 = unk148 + 0x28;
            unk2c8 = 6;
            vx = 4.0;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (vx > 0.0) {
            vx -= 0.14;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 6;
        }
        if (timer == 0 && (frame == 4 || frame == 8)) {
            unk148 = unk148 + 0x14;
            if (frame == 4) {
                vx = 1.0;
                vy = -1.5;
                ay = 0.05;
            }
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
        }
        if (frame > 2 && frame < 8) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                CPlayer::Unk40f1e0();
                timer = 0;
                frame = 8;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame == 7) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 3;
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 6;
        }
        if (timer == 0 && (frame == 4 || frame == 8)) {
            unk148 = unk148 + 0x14;
            if (frame == 4) {
                vx = 1.0;
                vy = -1.5;
                ay = 0.05;
            }
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
        }
        if (frame > 2 && frame < 8) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                CPlayer::Unk40f1e0();
                timer = 0;
                frame = 8;
                break;
            }
        }
        if (frame == 0xd && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if (frame == 0xf && timer == 0) {
            unk148 = unk148 + 0x14;
            unk2c9 = 0x15;
            vx = 4.0;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (vx > 0.0 && y == 0.0) {
            vx -= 0.14;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame == 7) {
                unk168 = 0;
            }
            if (frame == 0xe) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x109:
        vy = vy + ay;
        if (vy + y > 0.0 && vy > 0.0 && frame > 6) {
            Vf0();
            CPlayer::Unk40f1e0();
            frame = 9;
            y = 0.0;
            break;
        }
        if (frame == 5 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x192;
            l50.x = facing * 0x28 + x;
            l50.y = y - 60.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            vy = -1.4;
            ay = 0.025;
            vx = -0.5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame == 9 && unk313c < 3) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= 9) {
                Vf0();
                pattern = 9;
            }
        }
        break;
    case 0x10a:
        vy = vy + ay;
        if (vy + y > 0.0 && vy > 0.0 && frame > 6) {
            Vf0();
            CPlayer::Unk40f1e0();
            frame = 9;
            y = 0.0;
            break;
        }
        if (frame == 5 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x1a3;
            l50.x = facing * 0x28 + x;
            l50.y = y - 40.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            vy = -1.4;
            ay = 0.025;
            vx = -0.5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame == 9 && unk313c < 3) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= 9) {
                Vf0();
                pattern = 9;
            }
        }
        break;
    case 0x10b:
        vy = vy + ay;
        if (vy + y > 0.0 && vy > 0.0 && frame > 6) {
            Vf0();
            CPlayer::Unk40f1e0();
            frame = 9;
            y = 0.0;
            break;
        }
        if (frame == 5 && timer == 0) {
            unk2c8 = 1;
            l50.type = 0x1a4;
            l50.x = facing * 0x28 + x;
            l50.y = y - 40.0;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            unk314c++;
            vy = -1.4;
            ay = 0.025;
            vx = -0.5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame == 9 && unk313c < 3) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= 9) {
                Vf0();
                pattern = 9;
            }
        }
        break;
    case 0x10c:
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            unk15a = 1;
            unk159 = 1;
            vy = -1.4;
            vx = -0.6;
            if (unk158 == 1) {
                unk158 = 0;
            }
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0x12c:
        if (frame == 2 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x34);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if ((frame == 5 || frame == 6) && unk168 == 3) {
            frame = 7;
            timer = 0;
            unk168 = 0;
        }
        if (frame == 7 || frame == 8) {
            if (unk3140 <= 0) {
                l50.type = 0x22;
                l50.x = (double)((int)x + facing * 0xa - (WORD)CPlayer::Unk4108a0(0, 8));
                l50.y = (double)((int)y + 3 - (WORD)CPlayer::Unk4108a0(0, 6));
                l50.unk20 = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3140 = 2;
            }
            unk3140--;
            CPlayer::Unk410a80(0x32, 0x1e);
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = (27.0 + vx) * facing + x;
            (*m_opponent)->y = y - 50.0;
            (*m_opponent)->facing = -facing;
            if (x > 580.0 && facing == 1 || x < 60.0 && facing == -1) {
                if (x > 580.0 && facing == 1) {
                    x = 600.0;
                }
                if (x < 60.0 && facing == -1) {
                    x = 40.0;
                }
                timer = 0;
                frame = 9;
                CPlayer::Unk40f1e0();
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->x = (facing == 1) * 0x280;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = -2.9;
                CPlayer::Unk4105a0(0x8ca, 900.0);
                (*m_opponent)->unk14a = 0x5a;
                CPlayer::Unk410a10(0xa, 0xa);
                l50.type = 0x195;
                l50.x = x;
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                unk2c9 = 0x16;
                Vf9(&l50);
                unk2c8 = 0;
                unk168 = 3;
            }
        }
        if (frame > 0xb && frame < 0x13) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vx *= 0.5;
                vy = 0.0;
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        if (frame > 0x12) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                vx = 2.5;
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0xa);
                l50.y = (double)((int)y + 4);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 7 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = 0x13;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame == 0xc) {
                vx = -2.0;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x12d:
        if (frame == 2 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x34);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if ((frame == 5 || frame == 6) && unk168 == 3) {
            frame = 7;
            timer = 0;
            unk168 = 0;
        }
        if (frame == 7 || frame == 8) {
            if (unk3140 <= 0) {
                l50.type = 0x22;
                l50.x = (double)((int)x + facing * 0xa - (WORD)CPlayer::Unk4108a0(0, 8));
                l50.y = (double)((int)y + 3 - (WORD)CPlayer::Unk4108a0(0, 6));
                l50.unk20 = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3140 = 2;
            }
            unk3140--;
            CPlayer::Unk410a80(0x32, 0x1e);
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = (27.0 + vx) * facing + x;
            (*m_opponent)->y = y - 50.0;
            (*m_opponent)->facing = -facing;
            if (x > 580.0 && facing == 1 || x < 60.0 && facing == -1) {
                if (x > 580.0 && facing == 1) {
                    x = 600.0;
                }
                if (x < 60.0 && facing == -1) {
                    x = 40.0;
                }
                timer = 0;
                frame = 9;
                CPlayer::Unk40f1e0();
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->x = (facing == 1) * 0x280;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = -2.9;
                CPlayer::Unk4105a0(0x6d6, 900.0);
                if (unk313c == 0) {
                    (*m_opponent)->unk140 = 0x4650;
                }
                if (unk313c > 0) {
                    (*m_opponent)->unk140 = 0;
                }
                (*m_opponent)->unk14a = 0x5a;
                if (unk313c == 0) {
                    (*m_opponent)->unk14a = 0x12c;
                }
                CPlayer::Unk410a10(0xa, 0xa);
                l50.type = 0x195;
                l50.x = x;
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                unk2c9 = 0x16;
                Vf9(&l50);
                unk2c8 = 0;
                unk168 = 3;
            }
        }
        if (frame == 0xb && timer == 0x5a && unk313c == 0) {
            frame = 7;
            timer = 0;
            facing = -facing;
            vx = 2.7;
            unk313c = 1;
        }
        if (frame > 0xb && frame < 0x13) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vx *= 0.5;
                vy = 0.0;
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        if (frame > 0x12) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                vx = 3.0;
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0xa);
                l50.y = (double)((int)y + 4);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5) {
                unk13c = 9;
            }
            if (frame == 7 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = 0x13;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame == 0xc) {
                vx = -2.0;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x12e:
        if (frame == 2 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x34);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 1) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if ((frame == 5 || frame == 6) && unk168 == 3) {
            frame = 7;
            timer = 0;
            unk168 = 0;
        }
        if (frame == 7 || frame == 8) {
            if (unk3140 <= 0) {
                l50.type = 0x22;
                l50.x = (double)((int)x + facing * 0xa - (WORD)CPlayer::Unk4108a0(0, 8));
                l50.y = (double)((int)y + 3 - (WORD)CPlayer::Unk4108a0(0, 6));
                l50.unk20 = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3140 = 2;
            }
            unk3140--;
            CPlayer::Unk410a80(0x32, 0x1e);
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = (27.0 + vx) * facing + x;
            (*m_opponent)->y = y - 50.0;
            (*m_opponent)->facing = -facing;
            if (x > 580.0 && facing == 1 || x < 60.0 && facing == -1) {
                if (x > 580.0 && facing == 1) {
                    x = 600.0;
                }
                if (x < 60.0 && facing == -1) {
                    x = 40.0;
                }
                timer = 0;
                frame = 9;
                CPlayer::Unk40f1e0();
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->x = (facing == 1) * 0x280;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = -3.9;
                CPlayer::Unk4105a0(0x708, 900.0);
                if (unk313c < 2) {
                    (*m_opponent)->unk140 = 0x4650;
                } else {
                    (*m_opponent)->unk140 = 0;
                }
                (*m_opponent)->unk14a = 0x5a;
                if (unk313c < 2) {
                    (*m_opponent)->unk14a = 0x12c;
                }
                CPlayer::Unk410a10(0xa, 0xa);
                l50.type = 0x195;
                l50.x = x;
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                unk2c9 = 0x16;
                Vf9(&l50);
                unk2c8 = 0;
                unk168 = 3;
            }
        }
        if (frame == 0xb && timer == 0x5a && unk313c < 2) {
            frame = 7;
            timer = 0;
            facing = -facing;
            vx = 2.7;
            unk313c++;
        }
        if (frame > 0xb && frame < 0x13) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vx *= 0.5;
                vy = 0.0;
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        if (frame > 0x12) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                vx = 3.5;
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0xa);
                l50.y = (double)((int)y + 4);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5) {
                unk13c = 0x2d;
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 7) {
                frame = 0x13;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame == 0xc) {
                vx = -2.0;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x132:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            unk313c = 0;
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0x10 && frame < 0x16) {
            unk313c++;
            if (unk313c == 0x30) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y - 3);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x4e) {
                l50.type = 0x19b;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y + 6);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
        }
        if (frame == 0x11 && timer == 0) {
            l50.type = 0x196;
            unk2c8 = 3;
            l50.x = (double)((int)x + facing * 0x72);
            l50.y = (double)((int)y - 0x2a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3138++;
        }
        if (frame > 1) {
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 0x16 && unk3138 < 8) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x133:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            unk313c = 0;
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0x10 && frame < 0x16) {
            unk313c++;
            if (unk313c == 0x1e) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = (double)((int)y - 1);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x37) {
                l50.type = 0x19b;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y + 6);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x46) {
                l50.type = 0x199;
                l50.x = (double)((int)x - facing * 0xa);
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x55) {
                l50.type = 0x19c;
                l50.x = (double)((int)x - facing * 0x28);
                l50.y = (double)((int)y + 8);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
        }
        if (frame == 0x11 && timer == 0) {
            l50.type = 0x196;
            unk2c8 = 3;
            l50.x = (double)((int)x + facing * 0x72);
            l50.y = (double)((int)y - 0x2a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3138++;
        }
        if (frame > 1) {
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 0x16 && unk3138 < 0xc) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x134:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            unk313c = 0;
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 0x10 && frame < 0x16) {
            unk313c++;
            if (unk313c == 0x1e) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x50);
                l50.y = (double)((int)y - 1);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x37) {
                l50.type = 0x19b;
                l50.x = (double)((int)x + facing * 0x64);
                l50.y = (double)((int)y + 6);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x46) {
                l50.type = 0x199;
                l50.x = (double)((int)x - facing * 0xa);
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x55) {
                l50.type = 0x19c;
                l50.x = (double)((int)x - facing * 0x28);
                l50.y = (double)((int)y + 0xa);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x64) {
                l50.type = 0x19a;
                l50.x = (double)((int)x + facing * 0x37);
                l50.y = (double)((int)y + 5);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x73) {
                l50.type = 0x19d;
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = (double)((int)y + 2);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk28 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
        }
        if (frame == 0x11 && timer == 0) {
            l50.type = 0x196;
            unk2c8 = 3;
            l50.x = (double)((int)x + facing * 0x72);
            l50.y = (double)((int)y - 0x2a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3138++;
        }
        if (frame > 1) {
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 0x16 && unk3138 < 0x19) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0x18);
            l50.y = (double)((int)y - 0x35);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && unk168 == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            pattern = 0x136;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->x = facing * 0x12 + x;
            (*m_opponent)->y = -87.0;
            (*m_opponent)->facing = -facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x12);
            l50.y = (double)((int)y - 0x57);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 9 && frame < 0xc) {
            unk313c++;
            if (unk313c == 0xc) {
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x15) {
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
        }
        if (frame > 1) {
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 5 && (*m_opponent)->y == 0.0) {
                unk16c = 1;
            } else {
                unk16c = 0;
            }
            if (frame == 0xc && unk3138 < 8) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x136:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 4 || frame == 5) {
            unk313c++;
            if (unk313c == 0x1e && unk3138 < 7) {
                unk313c = 0;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + -0x3c + (WORD)CPlayer::Unk4108a0(0, 0x78));
                l50.y = (double)(-0xe6 - (WORD)CPlayer::Unk4108a0(0, 0x14));
                l50.unk20 = 2;
                l50.unk21 = l50.y > -240.0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.type = 0;
                l50.x = (double)((int)x + facing * 0x12);
                l50.y = (double)((int)y - 0x57);
                l50.unk20 = 2;
                l50.unk2c = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk14a = 0x1e;
                CPlayer::Unk410a10(3, 0);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 1) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -95.0;
                (*m_opponent)->pattern = 0x65;
                (*m_opponent)->Vf0();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->y = -98.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 3) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->y = -97.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 6 && unk3138 < 0xc) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
                (*m_opponent)->x = x;
                (*m_opponent)->y = -88.0;
                (*m_opponent)->pattern = 0x3b;
                CPlayer::Unk4105a0(0x546, 750.0);
                (*m_opponent)->Vf0();
                (*m_opponent)->Unk40f1e0();
                (*m_opponent)->facing = -facing;
                (*m_opponent)->unkc0 = -1.5;
                (*m_opponent)->unkc8 = -1.0;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)(int)x;
                l50.y = -225.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x + facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 9 && unk3140 < 0xf) {
                frame = frame - 2;
                unk3140++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0x18);
            l50.y = (double)((int)y - 0x35);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && unk168 == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            pattern = 0x138;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->x = facing * 0x12 + x;
            (*m_opponent)->y = -87.0;
            (*m_opponent)->facing = -facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x12);
            l50.y = (double)((int)y - 0x57);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 9 && frame < 0xc) {
            unk313c++;
            if (unk313c == 0xc) {
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x15) {
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
        }
        if (frame > 1) {
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 5 && (*m_opponent)->y == 0.0) {
                unk16c = 1;
            } else {
                unk16c = 0;
            }
            if (frame == 0xc && unk3138 < 8) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x138:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 4 || frame == 5) {
            unk313c++;
            if (unk313c == 0x1a && unk3138 < 0xf) {
                unk313c = 0;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + -0x50 + (WORD)CPlayer::Unk4108a0(0, 0xa0));
                l50.y = (double)(-0xe6 - (WORD)CPlayer::Unk4108a0(0, 0x14));
                l50.unk20 = 2;
                l50.unk21 = l50.y > -240.0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.type = 0;
                l50.x = (double)((int)x + facing * 0x12);
                l50.y = (double)((int)y - 0x57);
                l50.unk20 = 2;
                l50.unk2c = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk14a = 0x1e;
                CPlayer::Unk410a10(3, 0);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 1) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -95.0;
                (*m_opponent)->pattern = 0x65;
                (*m_opponent)->Vf0();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->y = -98.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 3) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->y = -97.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 6 && unk3138 < 0x12) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
                (*m_opponent)->x = x;
                (*m_opponent)->y = -88.0;
                (*m_opponent)->pattern = 0x3b;
                CPlayer::Unk4105a0(0x992, 750.0);
                (*m_opponent)->Vf0();
                (*m_opponent)->Unk40f1e0();
                (*m_opponent)->facing = -facing;
                (*m_opponent)->unkc0 = -1.5;
                (*m_opponent)->unkc8 = -1.0;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)(int)x;
                l50.y = -225.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x + facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x + facing * 0x5a);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x5a);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 9 && unk3140 < 0xf) {
                frame = frame - 2;
                unk3140++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x18);
            l50.y = (double)((int)y - 0x35);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 5 && unk168 == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            pattern = 0x13a;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->x = facing * 0x12 + x;
            (*m_opponent)->y = -87.0;
            (*m_opponent)->facing = -facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x12);
            l50.y = (double)((int)y - 0x57);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 9 && frame < 0xc) {
            unk313c++;
            if (unk313c == 0xc) {
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (unk313c == 0x15) {
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
        }
        if (frame > 1) {
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 5 && (*m_opponent)->y == 0.0) {
                unk16c = 1;
            } else {
                unk16c = 0;
            }
            if (frame == 0xc && unk3138 < 8) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13a:
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 4 || frame == 5) {
            unk313c++;
            if (unk313c == 0xf && unk3138 < 0x18) {
                unk313c = 0;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + -0x64 + (WORD)CPlayer::Unk4108a0(0, 0xc8));
                l50.y = (double)(-0xe6 - (WORD)CPlayer::Unk4108a0(0, 0x14));
                l50.unk20 = 2;
                l50.unk21 = l50.y > -240.0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.type = 0;
                l50.x = (double)((int)x + facing * 0x12);
                l50.y = (double)((int)y - 0x57);
                l50.unk20 = 2;
                l50.unk2c = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk14a = 0x1e;
                CPlayer::Unk410a10(3, 0);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 1) {
                (*m_opponent)->x = (facing << 4) + x;
                (*m_opponent)->y = -95.0;
                (*m_opponent)->pattern = 0x65;
                (*m_opponent)->Vf0();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->y = -98.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 3) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->y = -97.0;
                (*m_opponent)->pattern = 0x65;
            }
            if (frame == 6 && unk3138 < 0x1b) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
                (*m_opponent)->x = x;
                (*m_opponent)->y = -88.0;
                (*m_opponent)->pattern = 0x3b;
                CPlayer::Unk4105a0(0xd7a, 750.0);
                (*m_opponent)->Vf0();
                (*m_opponent)->Unk40f1e0();
                (*m_opponent)->facing = -facing;
                (*m_opponent)->unkc0 = -1.5;
                (*m_opponent)->unkc8 = -1.0;
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x32);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)(int)x;
                l50.y = -225.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x + facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = -210.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x + facing * 0x5a);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x5a);
                l50.y = -240.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x + facing * 0x64);
                l50.y = -230.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.x = (double)((int)x - facing * 0x64);
                l50.y = -230.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 9 && unk3140 < 0xf) {
                frame = frame - 2;
                unk3140++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x18);
            l50.y = (double)((int)y - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            m_game->Unk4080c0(0xf);
        }
        if ((frame == 0xb || frame == 0xc) && unk168 == 3) {
            CPlayer::Unk40f1e0();
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            pattern = 0x13c;
            (*m_opponent)->unk14a = 0x1e;
            (*m_opponent)->pattern = 0x6b;
            x = (*m_opponent)->x + ((*m_opponent)->unk2ad0[0] + 0xf) * facing;
            y = (*m_opponent)->y + 46.0 + (*m_opponent)->unk2af8[0];
            (*m_opponent)->facing = -facing;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x35);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame == 0xb || frame == 0xc) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                CPlayer::Unk40f1e0();
                timer = 0;
                frame = 0xd;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 0xa) {
                x = (*m_opponent)->x;
                y = (*m_opponent)->y - 100.0;
                l50.type = 0x19e;
                l50.x = (double)(int)x;
                l50.y = y - 60.0;
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 0xb) {
                ay = 0.035;
                vy = 1.0;
            }
            if (frame == 0xc || frame == 0xd) {
                unk16c = 1;
            } else {
                unk16c = 0;
            }
            if (frame == 0xd) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13c:
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if ((*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        (*m_opponent)->Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 2) {
                x = (*m_opponent)->x;
                y = 0.0;
                CPlayer::Unk410a10(6, 0);
                (*m_opponent)->pattern = 0x62;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->Unk40f1e0();
                (*m_opponent)->Vf0();
                l50.type = 0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 2;
                l50.unk2c = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 0xa || frame == 0x10 || frame == 0x16 || frame == 0x19 || frame == 0x1c) {
                l50.type = 0x19f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 0xa || frame == 0xd || frame == 0x10 || frame == 0x13 || frame == 0x16 || frame == 0x19) {
                CPlayer::Unk4105a0(0x64, 998.0);
                CPlayer::Unk410a10(2, 0);
                (*m_opponent)->unk140 = 0x4650;
                l50.type = 0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 2;
                l50.unk2c = 2;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk14a = 0x1e;
            }
            if (frame == 0xf && unk3138 < 0x16) {
                frame = frame - 6;
                unk3138++;
            }
            if (frame == 0x1c) {
                CPlayer::Unk4105a0(0x32, 999.0);
                (*m_opponent)->unk140 = 0;
                CPlayer::Unk410a10(6, 0);
                l50.type = 0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 2;
                l50.unk2c = 0x24;
                l50.unk21 = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk14a = 0x1e;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
    }
}
