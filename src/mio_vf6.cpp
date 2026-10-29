// CMio::Vf6 (0x5736d0-0x58830f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMio's
// .rdata, which starts with its constructor's folder name (mio.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMio::Vf6()
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
        unk158 = 0;
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
        vx = 0.5;
        if (unk3150 == 0) {
            vx = 0.7;
        }
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
        vx = -0.5;
        if (unk3150 == 0) {
            vx = -0.7;
        }
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
        unk158 = 0;
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
            if (unk158 == 0) {
                CPlayer::Unk40e630();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.0;
            if (unk158 == 1) {
                vx = 0.4;
                unk158 = 0;
            }
            if (unk3150 == 1) {
                vy = -2.0;
                ay = 0.02;
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
            if (unk158 == 0) {
                CPlayer::Unk40e630();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.0;
            vx = 0.7;
            if (unk158 == 1) {
                vx = 1.1;
                unk158 = 0;
            }
            if (unk3150 == 1) {
                vy = -2.0;
                ay = 0.02;
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
            if (unk158 == 0) {
                CPlayer::Unk40e630();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.0;
            vx = -0.7;
            if (unk3150 == 1) {
                vy = -2.0;
                ay = 0.02;
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
    case 7:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
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
        unk158 = 0;
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
            unk2c9 = 9;
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xd:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        CPlayer::Unk40e630();
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
    case 0xe:
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 0.0;
            ay = 0.045;
            if (unk3150 == 1) {
                vy = -2.0;
                ay = 0.02;
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
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 0.7;
            ay = 0.045;
            if (unk3150 == 1) {
                vy = -2.0;
                ay = 0.02;
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
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = -0.7;
            ay = 0.045;
            if (unk3150 == 1) {
                vy = -2.0;
                ay = 0.02;
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
    case 0x11:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx *= 0.25;
            vy *= 0.25;
        }
        unk118--;
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x15;
        }
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x15;
        }
        if (m_inputY == 1 && unk3138 > 2) {
            pattern = 9;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                unk3138++;
                if (unk3138 < 2) {
                    frame = 0;
                }
            }
            if (frame >= x8) {
                frame = frame - 2;
                unk3138++;
                if (unk3138 > 0xf) {
                    Vf0();
                    pattern = 9;
                    break;
                }
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
    case 0x2f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
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
        unk158 = 0;
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
    case 0x33:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x34:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x35:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
        unk158 = 0;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x37:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x38:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0x39:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
        unk158 = 0;
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xb) {
                frame = 3;
            }
            if (frame == 4 && vy > -0.5) {
                frame = 0xb;
            }
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
                Vf0();
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
                Vf0();
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
                Vf0();
            }
        }
        break;
    case 0x4b:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
        unk158 = 0;
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
        unk158 = 0;
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
        unk158 = 0;
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
            if (frame == 0xf) {
                frame = 7;
            }
            if (frame == 8 && vy > -0.5) {
                frame = 0xf;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y + vy >= 0.0 && frame > 5) {
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
            if (unk3154 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3154 = 1;
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
            if (unk3154 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3154 = 1;
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
            if (unk3154 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3154 = 1;
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
            if (unk3154 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk3154 = 1;
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
            l50.unk21 = 0;
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
        if (y < 0.0) {
            vy += 0.04;
        }
        if (y + vy > 0.0 && frame > 1) {
            y = 0.0;
            vy = 0.0;
            timer = 0;
            frame = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                vy = -1.0;
            }
            if (frame == x8 - 1) {
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
        timer++;
        unk158 = 0;
        if (unk108 > 0 && timer > 0x63 && frame == 0) {
            pattern = 0x60;
            Vf0();
        }
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
            unk158 = 0;
            unk148 = unk148 + 0xa;
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
            unk158 = 0;
            unk148 = unk148 + 0xf;
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
            unk158 = 0;
            unk148 = unk148 + 0x14;
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
            unk158 = 0;
            unk148 = unk148 + 0xa;
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
            unk158 = 0;
            unk148 = unk148 + 0xf;
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
            unk158 = 0;
            unk148 = unk148 + 0x14;
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
            unk158 = 0;
            vy = -2.6;
            unk148 = unk148 + 0xf;
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
            unk158 = 0;
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
            unk158 = 0;
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
            l50.y = (double)((int)y - 0x3c);
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
        if (frame == 6 && timer == 0) {
            CPlayer::Unk40f1e0();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3c);
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
            if (frame == 0xc) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk4109d0(3);
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
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            ay = 0.0;
        }
        vx = 1.7;
        unk158 = 1;
        timer++;
        unk3138++;
        unk3140++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && unk3140 >= 100.0) {
            pattern = 0xb2;
            Vf0();
        }
        if (m_inputX != facing && unk3138 >= 0x3c) {
            pattern = 0xb2;
            Vf0();
        }
        break;
    case 0xa4:
        CPlayer::Unk4109d0(2);
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if ((frame == 5 || frame == 6) && vy + y > 0.0) {
            timer = 0;
            CPlayer::Unk40f1e0();
            frame = 7;
            y = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -2.0;
                vy = -1.3;
                unk2c8 = 1;
                ay = 0.04;
            }
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                CPlayer::Unk40e630();
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0) {
            vx = 1.2;
            vy = -0.4;
            CPlayer::Unk4109d0(3);
            ay = 0.0;
            unk2c9 = 0x14;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.8;
            vy = 0.0;
            CPlayer::Unk4109d0(3);
            ay = 0.0;
            unk2c9 = 0x14;
        }
        timer++;
        unk3138++;
        unk3140++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == facing && unk3140 >= 120.0) {
            pattern = 9;
            Vf0();
            vx = 0.9;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            vx = 0.9;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0) {
            vx = -1.2;
            vy = -0.4;
            ay = 0.0;
            CPlayer::Unk4109d0(3);
            unk2c9 = 0x14;
        }
        if (frame == 3 && timer == 0) {
            vx = -1.8;
            vy = 0.0;
            CPlayer::Unk4109d0(3);
            ay = 0.0;
            unk2c9 = 0x14;
        }
        timer++;
        unk3138++;
        unk3140++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (m_inputX == -facing && unk3140 >= 120.0) {
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
            unk158 = 0;
            m_game->Unk4080c0(0);
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
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
            unk3140 = (int)(vy * 100.0);
            vx = 0.0;
            vy = 0.0;
            unk14e = 0;
            unkb8 = 0.0;
            if (ay == 0.0) {
                ay = 0.035;
            }
            unk14c = 0x3c;
        }
        if (unk14c == 0 && unk3148 == 0.0) {
            unk3148++;
            vx = unk3138 * 0.01;
            vy = unk3140 * 0.01;
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
            unk3140 = (int)(vy * 100.0);
            vx = 0.0;
            vy = 0.0;
            if (unk120 == 1) {
                unk178 = unk118 * 5.0 + unk178;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x12;
            l50.type = 1;
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
                vx = unk3138 * 0.01;
                vy = unk3140 * 0.01;
                if (ay == 0.0) {
                    ay = 0.035;
                }
                Vf0();
            }
        }
        break;
    case 0xb2:
        vx -= 0.06;
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            unk158 = 0;
        }
        if (vx == 0.0) {
            pattern = 0;
            Vf0();
            break;
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
                frame = 0;
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
        if (y + vy > 0.0 && frame < 7) {
            CPlayer::Unk40f1e0();
            y = 0.0;
            timer = 0;
            frame = 7;
            unk2c9 = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                unk2c8 = 1;
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
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
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
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
            if (frame < 4) {
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
            vx -= 0.03;
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
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
        if (frame == 3 && timer == 0) {
            unk148 = unk148 + 0x23;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
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
            if (frame < 3) {
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
            unk148 = unk148 + 0xd;
            unk2c9 = 0x14;
            unk16c = 0x63;
        }
        if (frame == 3 && timer == 0) {
            unk2c9 = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 5 && unk3138 < 3) {
                unk3138++;
                frame = 3;
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
        unk158 = 0;
        if (frame == 2 && timer == 0) {
            vx += 1.7;
            unk148 = unk148 + 0x19;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        } else {
            vx = 0.0;
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
    case 0xcf:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk168 >= 2 && unk15a == 0 && unk15c < 3) {
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
            if (frame < 3) {
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
        if (m_inputY == -1 && frame > 0 && unk168 >= 2 && unk15a == 0 && unk15c < 3) {
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
            if (frame < 4) {
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
        if (m_inputY == -1 && frame > 0 && unk168 >= 2 && unk15a == 0 && unk15c < 3) {
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
            unk16c = 3;
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
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 6 && unk3138 < 1) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
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
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd3:
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
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd4:
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
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd5:
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
        if (frame == 3 && timer == 0) {
            unk148 = unk148 + 0x23;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd6:
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
            if (frame < 3) {
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
    case 0xd7:
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
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xd;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (frame == 3 && timer == 0) {
            unk2c9 = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
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
    case 0xd8:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0) {
            vx -= 0.04;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (frame == 0 && timer == 0) {
            unk16c = 7;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk2c9 = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 9 && unk3138 == 0) {
                unk3138++;
                frame = frame - 2;
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
    case 0xd9:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            CPlayer::Unk40e630();
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
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xda:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            CPlayer::Unk40e630();
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
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xdb:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            CPlayer::Unk40e630();
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
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            unk16c = 1;
        } else {
            unk16c = 0;
        }
        if (frame == 1 && unk168 == 3) {
            (*m_opponent)->Unk40f1e0();
            if ((*m_opponent)->x > 600.0) {
                (*m_opponent)->x = 600.0;
            }
            if ((*m_opponent)->x < 40.0) {
                (*m_opponent)->x = 40.0;
            }
            Vf0();
            (*m_opponent)->Vf0();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            x = (*m_opponent)->x - (*m_opponent)->unk2ad0[0] * facing;
            y = (*m_opponent)->unk2af8[0] + 0x39 + y;
            break;
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
    case 0xdd:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->pattern = 0x6b;
            x = (*m_opponent)->x - (*m_opponent)->unk2ad0[0] * facing;
            y = (*m_opponent)->unk2af8[0] + 0x39 + y;
            unk168 = 0;
        }
        if ((unk3138 > 0x258 && frame == 3 || (*m_opponent)->unk108 <= 0) && frame < 5) {
            facing = -facing;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->pattern = 0x62;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->Vf0();
            timer = 0;
            frame = 5;
            ay = 0.035;
            CPlayer::Unk4105a0(0x190, 1000.0);
            break;
        }
        if (frame > 2 && frame < 5) {
            unk3140++;
            unk3138++;
        }
        if (unk3140 > 70.0 && frame < 5 && (*m_opponent)->unk108 > 0) {
            unk3140 = 0.0;
            frame = 4;
            timer = 0;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            unk3140 = 0.0;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x36);
            l50.unk20 = 2;
            l50.unk2c = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4105a0(0x64, 1000.0);
        }
        if (frame > 4) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                CPlayer::Unk40f1e0();
                y = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 3) {
                l50.type = 0x1c6;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk20 = 0;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.unk21 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
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
    case 0xdf:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 2) {
                vx = 1.0;
                vy = 1.0;
                ay = 0.0;
                unk2c8 = 3;
                unk148 = unk148 + 0x14;
                unk16c = 1;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        if (y < 0.0 && vx > 0.0) {
            vx += 0.035;
            vy += 0.035;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            pattern = 0xe0;
            Vf0();
        }
        break;
    case 0xe0:
        vy = 0.0;
        unk168 = 3;
        vx -= 0.08;
        if (vx < 0.0) {
            vx = 0.0;
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
    case 0xe1:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            unk16c = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 2.0;
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
        }
        vx -= 0.05;
        if (vx < 0.0) {
            vx = 0.0;
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
    case 0xe3:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 == 3 && unk15a == 0) {
            CPlayer::Unk40e630();
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
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xe4:
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
        if (frame == 4 && timer == 0) {
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xe5:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && unk168 >= 2 && unk15a == 0) {
            CPlayer::Unk40e630();
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
    case 0xe6:
        CPlayer::Unk4109d0(3);
        vx -= 0.032;
        unk158 = 0;
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
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe7:
        CPlayer::Unk4109d0(3);
        vx -= 0.032;
        unk158 = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xa;
            unk2c9 = 0x14;
            unk16c = 1;
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
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe8:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xa;
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
                Vf0();
            }
        }
        break;
    case 0xe9:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
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
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xea:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 0 && timer == 0) {
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
    case 0xeb:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            unk16c = 1;
        }
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x15;
            vx = 2.3;
        }
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
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
    case 0xec:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
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
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xed:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
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
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xa;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xee:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xa;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xef:
        CPlayer::Unk4109d0(3);
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        unk158 = 0;
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
            if (frame < 3) {
                unk168 = 0;
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
    case 0xf0:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xa;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
                unk168 = 0;
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
    case 0xf1:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.032;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            unk16c = 7;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk2c9 = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 9 && unk3138 < 3) {
                unk3138++;
                frame = frame - 2;
            }
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
    case 0xf2:
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
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 5;
            unk2c9 = 0x15;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xf3:
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
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame == 2 && timer == 0) {
                unk148 = unk148 + 5;
                unk2c9 = 0x15;
                unk16c = 1;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xf7:
        vy = vy + ay;
        if (frame == 1 && unk168 == 3) {
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->Vf0();
            Vf0();
            CPlayer::Unk40f1e0();
            ay = 0.035;
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x3a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = (int)x + facing * 0x23;
            (*m_opponent)->y = (int)y - 0x3a;
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
            break;
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
                pattern = 0xdb;
                frame = 2;
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
            ay = 0.035;
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x3a);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = (int)x + facing * 0x23;
            (*m_opponent)->y = (int)y - 0x3a;
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
            break;
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
                frame = 1;
            }
        }
        break;
    case 0xf9:
        if (frame < 6) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 6) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            CPlayer::Unk40f1e0();
            y = 0.0;
            Vf0();
            pattern = 0xd;
            break;
        }
        if (frame == 0) {
            (*m_opponent)->y = y - 35.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = 0x64;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 59.0;
            (*m_opponent)->x = facing * 0x24 + x;
            (*m_opponent)->pattern = 0x64;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = facing * 0x23 + x;
            (*m_opponent)->pattern = 0x64;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x38);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x23 + x;
            (*m_opponent)->y = y - 56.0;
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -2.5;
            (*m_opponent)->unkc8 = -0.5;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->x = facing * 0xf + x;
            CPlayer::Unk4105a0(0x3e8, 500.0);
            (*m_opponent)->unk124 = (int)(200.0 * unk178 * 0.0001);
            (*m_opponent)->Vf0();
            l50.type = 0x1c2;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x38);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c3;
            Vf9(&l50);
            l50.type = 0x1c4;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            unk16c = 8;
        }
        if (frame > 1 && frame < 9) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            Vf0();
            frame = 9;
        }
        if (frame == 9 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -1.8;
                ay = 0.025;
                x = facing * 0xa + x;
            }
            if (vy > 0.0 && frame == 5) {
                frame = 6;
                break;
            }
            if (frame == 6) {
                frame = frame - 4;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                CPlayer::Unk40f1e0();
                pattern = 0;
            }
            unk168 = 0;
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            unk16c = 0xc;
        }
        if (frame > 1 && frame < 9) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            Vf0();
            frame = 9;
        }
        if (frame == 9 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -2.8;
                ay = 0.025;
                x = facing * 0xa + x;
            }
            if (vy > 0.0 && frame == 5) {
                frame = 6;
                break;
            }
            if (frame == 6) {
                frame = frame - 4;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                CPlayer::Unk40f1e0();
                pattern = 0;
            }
            unk168 = 0;
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            CPlayer::Unk40f1e0();
            unk16c = 0x14;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1bd;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = -facing;
            Vf9(&l50);
        }
        if (frame > 1 && frame < 9) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9) {
            Vf0();
            frame = 9;
        }
        if (frame == 9 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                vy = -2.8;
                ay = 0.015;
                x = facing * 0xa + x;
            }
            if (vy > 0.0 && frame == 5) {
                ay = 0.025;
                frame = 6;
                break;
            }
            if (frame == 6) {
                frame = frame - 4;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                CPlayer::Unk40f1e0();
                pattern = 0;
            }
            unk168 = 0;
        }
        break;
    case 0xfd:
        if (y + vy > 0.0 && frame < 3) {
            Vf0();
            frame = 3;
        }
        if (frame == 3 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
        }
        if (y < 0.0) {
            vy += 0.025;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 3) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfe:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        if (unk168 > 1 && unk262 == 0xa && frame == 6) {
            pattern = 0x100;
            unk168 = 0;
            Vf0();
            break;
        }
        if (unk262 == 0xb && frame == 6) {
            pattern = 0x111;
            unk168 = 0;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                break;
            }
        }
        break;
    case 0xff:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
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
        if (frame == 3 && timer == 0) {
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x5f);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x50);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x41);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x23);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x14);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 5);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                break;
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x14;
            unk148 = unk148 + 0xa;
            unk16c = 3;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x8a);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x64);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x3e);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x18);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
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
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x14;
            unk148 = unk148 + 0x23;
            unk16c = 1;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x198;
            l50.x = (double)((int)x - facing * 9);
            l50.y = (double)((int)y - 0x3a);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
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
    case 0x102:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            unk158 = 0;
            vy = 0.0;
            ay = 0.0;
            unk16c = 4;
        }
        if (frame == 2 && y + vy >= 0.0 && vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 1.7;
            frame = 3;
            timer = 0;
        }
        if (frame > 2) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        vy += 0.042;
        if (vy > 0.0 && y >= 0.0) {
            vy = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 1) {
                vx = 0.3;
                vy = -0.9;
                unk2c8 = 1;
            }
            if (frame == 5 && vx > 0.8) {
                frame = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            unk16c = 0xa;
        }
        if (frame == 2 && y + vy >= 0.0 && vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 2.4;
            frame = 3;
            timer = 0;
        }
        if (frame > 2) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        vy += 0.042;
        if (vy > 0.0 && y >= 0.0) {
            vy = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 1) {
                vx = 0.3;
                vy = -1.2;
                unk2c8 = 1;
            }
            if (frame == 5 && vx > 0.8) {
                frame = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            unk16c = 0xa;
        }
        if (frame == 2 && y + vy >= 0.0 && vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 2.4;
            frame = 3;
            timer = 0;
        }
        if (frame > 2) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        vy += 0.042;
        if (vy > 0.0 && y >= 0.0) {
            vy = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (unk16c > 0) {
                unk168 = 0;
            }
            if (frame == 1) {
                vx = 0.3;
                vy = -1.2;
                unk2c8 = 1;
            }
            if (frame == 5 && vx > 0.8) {
                frame = frame - 2;
            }
            if (frame == 7 && unk3138 < 5) {
                frame = frame - 2;
                unk3138++;
                unk16c = unk16c + 2;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (unk3148 > 2.5) {
            unk3140 = -0.06;
        }
        if (unk3148 < 0.0) {
            unk3140 = 0.06;
        }
        unk3148 = unk3148 + unk3140;
        if (frame == 3 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk3138 = 0;
            unk3140 = 0.05;
            vy = -1.1;
            vx = 0.0;
        }
        if (frame > 2 && frame < 8) {
            vy += 0.022;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.012;
            if (vy > 0.8) {
                vy = 0.8;
            }
        }
        if (frame == 8 && timer == 0 && unk3138 < 7) {
            l50.type = 0x194;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2f);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if ((frame == 8 || frame == 9) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 0xa;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame == 8) {
                unk2c8 = 3;
                vy -= 0.4;
            }
            if (frame == 0xa && unk3138 < 0x10) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame == 0xb && y < 0.0) {
                pattern = 9;
                Vf0();
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x106:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (unk3148 > 2.5) {
            unk3140 = -0.06;
        }
        if (unk3148 < 0.0) {
            unk3140 = 0.06;
        }
        unk3148 = unk3148 + unk3140;
        if (frame == 3 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk3140 = 0.05;
            unk3138 = 0;
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame > 2 && frame < 8) {
            vy += 0.022;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.012;
            if (vy > 0.8) {
                vy = 0.8;
            }
        }
        if (frame == 8 && timer == 0 && unk3138 < 0xc) {
            l50.type = 0x194;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2f);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if ((frame == 8 || frame == 9) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 0xa;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame == 8) {
                unk2c8 = 3;
                vx -= 0.5;
                vy -= 0.9;
            }
            if (frame == 0xa && unk3138 < 0x18) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame == 0xb && y < 0.0) {
                pattern = 9;
                Vf0();
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0 && unk3138 == 0x64) {
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
            unk3138 = 0;
        }
        if (unk3148 > 2.5) {
            unk3140 = -0.08;
        }
        if (unk3148 < 0.0) {
            unk3140 = 0.08;
        }
        unk3148 = unk3148 + unk3140;
        if (frame == 3 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk3138 = 0;
            unk3140 = 0.05;
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame > 2 && frame < 8) {
            vy += 0.022;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.008;
            if (vy > 0.6) {
                vy = 0.6;
            }
        }
        if (frame == 8 && timer == 0 && unk3138 < 0x10) {
            l50.type = 0x1bc;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2f);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if ((frame == 8 || frame == 9) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 0xa;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame == 8) {
                unk2c8 = 3;
                vx -= 0.5;
                vy -= 0.4;
            }
            if (frame == 0xa && unk3138 < 0xd) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame == 0xb && y < 0.0) {
                pattern = 9;
                Vf0();
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0x19;
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
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
    case 0x109:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0xf;
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
        }
        if (frame == 0xd && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0xf;
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
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
    case 0x10a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
            CPlayer::Unk40f1e0();
            facing = -facing;
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0x19;
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
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
    case 0x10b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0x19;
            l50.type = 0x1c5;
            l50.x = (double)((int)x + facing * 0x58);
            l50.y = -3.0;
            l50.unk18 = facing;
            l50.unk21 = 0;
            l50.unk20 = 0;
            l50.unk0 = 1;
            Vf9(&l50);
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
    case 0x10c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0x19;
            l50.type = 0x1c5;
            l50.x = (double)((int)x + (facing << 7));
            l50.y = -3.0;
            l50.unk18 = facing;
            l50.unk21 = 0;
            l50.unk20 = 0;
            l50.unk0 = 1;
            Vf9(&l50);
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
    case 0x10d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 4;
            unk148 = unk148 + 0x19;
            l50.type = 0x1c5;
            l50.x = (double)((int)x + facing * 0xbc);
            l50.y = -3.0;
            l50.unk18 = facing;
            l50.unk21 = 0;
            l50.unk20 = 0;
            l50.unk0 = 1;
            Vf9(&l50);
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
    case 0x10e:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        unk158 = 0;
        if (frame == 4 && timer == 0) {
            if (unk3150 == 0) {
                unk3150 = 1;
                timer++;
                break;
            }
            unk3150 = 0;
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
    case 0x10f:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        if (unk168 > 1 && unk262 == 0xa && frame == 6) {
            pattern = 0x110;
            unk168 = 0;
            Vf0();
            break;
        }
        if (unk262 == 0xb && frame == 6) {
            pattern = 0x111;
            unk168 = 0;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                break;
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x14;
            unk148 = unk148 + 0xa;
            unk16c = 5;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x8a);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x64);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x3e);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x18);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 7) {
                l50.type = 0x198;
                l50.x = (double)((int)x - facing * 9);
                l50.y = (double)((int)y - 0x3a);
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
            }
            if (frame == 8) {
                unk16c = 1;
                unk2c9 = 0x15;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            unk148 = unk148 + 0xa;
            l50.type = 0x1c8;
            l50.unk0 = 1;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x30);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
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
    case 0x12c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3150 = 1;
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
    case 0x12d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3150 = 0;
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
    case 0x12f:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if (frame == 4 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (unk168 == 3 && unk3138 == 0 && frame == 3) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0x78;
            unk3138++;
        }
        if (frame == 5 && timer < 0x64) {
            unk168 = 3;
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 1) {
                l50.type = 0x19b;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 3) {
                l50.type = 0x19d;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 7) {
                l50.type = 0x19c;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
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
    case 0x130:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if (frame == 4 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (unk168 == 3 && unk3138 == 0 && frame == 3) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0x78;
            unk3138++;
        }
        if (frame == 5 && timer < 0x91) {
            unk168 = 3;
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
                l50.type = 0x19b;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 3) {
                l50.type = 0x19d;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 6) {
                l50.type = 0x19c;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
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
    case 0x131:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        unk158 = 0;
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            unk16c = 1;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 1) {
            m_game->Unk4080c0(0xf);
        }
        if (unk168 == 3 && unk3138 == 0 && frame == 3) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0x78;
            unk3138++;
        }
        if (frame == 4 && timer < 0xc8) {
            unk168 = 3;
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 3) {
                l50.type = 0x19b;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 4) {
                l50.type = 0x19d;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 6) {
                l50.type = 0x19c;
                l50.x = (double)(int)(((WORD)CPlayer::Unk4108a0(0, 0x96) - 0x3c) * facing + x);
                l50.y = -480.0;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk20 = 0;
                Vf9(&l50);
                break;
            }
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
    case 0x132:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2 && frame < 7) {
            vy += 0.012;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.03;
        }
        if (frame == 5) {
            vy = 0.0;
        }
        if (frame == 9 && timer == 0 && unk3138 == 0) {
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2f);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if ((frame == 9 || frame == 0xa) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 0xb;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 9) {
                unk2c9 = 0x16;
                vx -= 0.7;
                vy -= 1.5;
            }
            if (frame == 0xb && unk3138 < 0x10) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame == 0xc && y < 0.0) {
                pattern = 9;
                Vf0();
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x133:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2 && frame < 7) {
            vy += 0.012;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.03;
        }
        if (frame == 5) {
            vy = 0.0;
        }
        if (frame == 9 && timer == 0 && unk3138 == 0) {
            l50.type = 0x1a8;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2f);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if ((frame == 9 || frame == 0xa) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 0xb;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 9) {
                unk2c9 = 0x16;
                vx -= 0.7;
                vy -= 1.5;
            }
            if (frame == 0xb && unk3138 < 0x10) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame == 0xc && y < 0.0) {
                pattern = 9;
                Vf0();
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x134:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.1;
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 4) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 2 && frame < 7) {
            vy += 0.012;
        }
        if (frame == 8 || frame == 9) {
            vy += 0.03;
        }
        if (frame == 5) {
            vy = 0.0;
        }
        if (frame == 9 && timer == 0 && unk3138 == 0) {
            l50.type = 0x1a9;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2f);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if ((frame == 9 || frame == 0xa) && vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            frame = 0xb;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 9) {
                unk2c9 = 0x16;
                vx -= 0.7;
                vy -= 1.5;
            }
            if (frame == 0xb && unk3138 < 0x10) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame == 0xc && y < 0.0) {
                pattern = 9;
                Vf0();
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x135:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x26);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 8;
        }
        if (frame > 2 && frame < 6 && unk3140 <= 0.0) {
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = (double)((int)y - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 0;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3140 = 21.0;
            unk2c8 = 6;
        }
        unk3140--;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6) {
                unk3138++;
                if (unk3138 > 5) {
                    unk16c = 0;
                }
                if (unk3138 < 8) {
                    frame = frame - 2;
                }
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x136:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x26);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 0xf;
        }
        if (frame > 2 && frame < 6 && unk3140 <= 0.0) {
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = (double)((int)y - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 0;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3140 = 15.0;
            unk2c8 = 6;
        }
        unk3140--;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6) {
                unk3138++;
                if (unk3138 < 7) {
                    frame = frame - 2;
                }
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x137:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x26);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
            unk2c9 = 0x25;
        }
        m_game->Unk4080c0(3);
        if (frame == 3 && timer == 0) {
            unk2c9 = 0x12;
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = (double)((int)y - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 0;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 6;
        }
        if (unk168 == 3 && unk3138 == 0) {
            (*m_opponent)->unk14a = (*m_opponent)->unk14a + 0xb4;
            unk3138++;
            l50.type = 0x1bf;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = (double)((int)(*m_opponent)->y - 0x32);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
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
    case 0x138:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0xc && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            l50.unk21 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            l50.unk21 = 0;
            Vf9(&l50);
        }
        if (frame == 0x10 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            Vf9(&l50);
        }
        if (frame == 0x14 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            l50.unk21 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            l50.unk21 = 0;
            Vf9(&l50);
        }
        if (frame == 0x18 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x13) {
                unk3138++;
                if (unk3138 < 1) {
                    frame = frame - 8;
                }
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x139:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0xc && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            l50.unk21 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            l50.unk21 = 0;
            Vf9(&l50);
        }
        if (frame == 0x10 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            Vf9(&l50);
        }
        if (frame == 0x14 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            l50.unk21 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            l50.unk21 = 0;
            Vf9(&l50);
        }
        if (frame == 0x18 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x13) {
                unk3138++;
                if (unk3138 < 2) {
                    frame = frame - 8;
                }
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13a:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 0xc && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            l50.unk21 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            l50.unk21 = 0;
            Vf9(&l50);
        }
        if (frame == 0x10 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            Vf9(&l50);
        }
        if (frame == 0x14 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            l50.unk21 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            l50.unk21 = 0;
            Vf9(&l50);
        }
        if (frame == 0x18 && timer == 0) {
            unk2c9 = 0x20;
            l50.type = 0x1aa;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x41);
            l50.unk18 = facing;
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2d);
            Vf9(&l50);
            l50.x = (double)((int)x - facing * 0x19);
            l50.y = (double)((int)y - 0x19);
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x13) {
                unk3138++;
                if (unk3138 < 4) {
                    frame = frame - 8;
                }
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13b:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x26);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
            unk2c9 = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        m_game->Unk4080c0(0xf);
        if (unk168 == 2 && frame > 1 && frame < 0xd) {
            frame = 0xd;
            timer = 0;
            break;
        }
        if (frame == 0xd && timer == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 2;
            l50.unk21 = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
        }
        if (frame > 0xc) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (unk16c == 0 && frame < 0xd && m_pressA == 1) {
            Vf0();
            pattern = 0x13c;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 7) {
                vx = 2.0;
            }
            if (frame == 0xd) {
                unk3138++;
                if (unk3138 < 3) {
                    frame = frame - 3;
                }
            }
            if (frame >= x8) {
                pattern = 0x60;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13c:
        m_game->Unk4080c0(0xf);
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (unk168 == 3 && frame > 1 && frame < 4 && m_pressB == 1) {
            Vf0();
            pattern = 0x13d;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13d:
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (unk168 == 3 && frame > 2 && frame < 5 && m_pressC == 1) {
            Vf0();
            pattern = 0x13e;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 3 && timer == 0) {
            unk2c9 = 0x15;
        }
        if (unk168 == 3 && frame > 5 && frame < 7 && m_pressA == 1) {
            Vf0();
            pattern = 0x13f;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x13f:
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (unk168 == 3 && frame > 0 && frame < 4 && m_pressB == 1) {
            Vf0();
            pattern = 0x140;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x140:
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (unk168 == 3 && frame > 1 && frame < 4 && m_pressC == 1) {
            Vf0();
            pattern = 0x141;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x141:
        if (frame == 0 && timer == 0) {
            unk16c = 4;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (unk16c == 0 && frame > 2 && frame < 5 && m_pressD == 1) {
            Vf0();
            pattern = 0x142;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 5 && unk3138 < 4) {
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
    case 0x142:
        if (frame == 0 && timer == 0) {
            unk16c = 1;
        }
        m_game->Unk4080c0(0x78);
        if (frame > 3) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (unk168 == 3 && frame > 2 && frame < 5 && unk262 == 0x16) {
            Vf0();
            pattern = 0x143;
            CPlayer::Unk40f1e0();
            break;
        }
        if (unk168 == 3 && frame > 2 && frame < 5 && unk262 == 0xc) {
            Vf0();
            pattern = 0x144;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x143:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0xf);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 2;
        }
        m_game->Unk4080c0(0xf);
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 0xc) {
            frame = 0xc;
            timer = 0;
            y = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 7) {
                vy = -1.0;
                ay = 0.035;
                vx = 4.0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x144:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xf);
            l50.y = (double)((int)y - 0x14);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        m_game->Unk4080c0(0xf);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                l50.type = 0x1ba;
                l50.x = (double)((int)x + facing * 0xb);
                l50.y = (double)((int)y - 0x35);
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (frame == 6) {
                unk3138++;
                if (unk3138 < 0xf) {
                    frame = frame - 2;
                }
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x14a:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x26);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk16c = 1;
            unk2c9 = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        m_game->Unk4080c0(0xf);
        if (unk168 == 3 && frame == 3) {
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0x14b;
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->pattern = 0x79;
            (*m_opponent)->y = 0.0;
            if ((*m_opponent)->x > 480.0) {
                (*m_opponent)->x = 480.0;
            }
            if ((*m_opponent)->x < 160.0) {
                (*m_opponent)->x = 160.0;
            }
            break;
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
    case 0x14b:
        unk128 = 1;
        CPlayer::Unk410a80(0x32, 3);
        (*m_opponent)->Unk410a40(0x32, 3);
        if ((*m_opponent)->pattern == 0x63 || (*m_opponent)->pattern == 0x79) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 6) {
            CPlayer::Unk410b10(0xb0, 3);
        } else {
            unk3148 = 1.0;
        }
        m_game->Unk4080c0(0xf);
        if (unk3140 == 1.0 && (*m_opponent)->pattern != 0x47) {
            CPlayer::Unk4105a0(0x1388, 800.0);
            (*m_opponent)->Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->pattern = 0x47;
            (*m_opponent)->unkc8 = -15.0;
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->y = -10.0;
            (*m_opponent)->vx = 0.0;
        }
        timer++;
        if (frame < 6 && timer >= l4 - 0x1e) {
            unk3148 = 1.0;
        }
        if (timer >= l4) {
            unk3148 = 0.0;
            timer = 0;
            frame++;
            if (frame == 1) {
                l50.type = 0x1ab;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0x1e);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b2;
                l50.x = (double)((int)(*m_opponent)->x - facing * 0x1e);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                (*m_opponent)->pattern = 0x63;
                unk2c8 = 9;
            }
            if (frame == 2) {
                l50.type = 0x1ac;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0x28);
                l50.y = -40.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.y = 0.0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b3;
                l50.x = (double)((int)(*m_opponent)->x - facing * 0x1e);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                (*m_opponent)->pattern = 0x63;
                unk2c8 = 9;
            }
            if (frame == 3) {
                l50.type = 0x1ad;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0x3c);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b4;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.x = (double)((int)(*m_opponent)->x - facing * 0x3c);
                l50.unk20 = 2;
                Vf9(&l50);
                (*m_opponent)->pattern = 0x63;
                unk2c8 = 9;
            }
            if (frame == 4) {
                l50.type = 0x1ae;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0x1e);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b5;
                l50.x = (double)((int)(*m_opponent)->x - facing * 0x1e);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                (*m_opponent)->pattern = 0x63;
                unk2c8 = 9;
            }
            if (frame == 5) {
                l50.type = 0x1af;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0x3c);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b6;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0xf);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.unk20 = 2;
                Vf9(&l50);
                l50.type = 0x1b9;
                l50.unk21 = 0;
                l50.x = (double)((int)(*m_opponent)->x - facing * 0x41);
                Vf9(&l50);
                (*m_opponent)->pattern = 0x63;
                unk2c8 = 9;
            }
            if (frame == 6) {
                l50.type = 0x1b0;
                l50.x = (double)((int)(*m_opponent)->x + facing * 0x3c);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                l50.type = 0x1b7;
                l50.x = (double)((int)(*m_opponent)->x - facing * 0x3c);
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.unk21 = 1;
                l50.unk20 = 0;
                l50.unk28 = 1;
                Vf9(&l50);
                (*m_opponent)->pattern = 0x63;
                unk2c8 = 9;
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0x47;
                CPlayer::Unk40e630();
                Vf0();
                CPlayer::Unk40f1e0();
                unkc8 = -3.0;
                unkc0 = 0.0;
                y = -640.0;
            }
        }
    }
}
