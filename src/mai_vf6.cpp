// CMai::Vf6 (0x607930-0x6163af), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMai's
// .rdata, which starts with its constructor's folder name (mai.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMai::Vf6()
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
        vx = 0.5;
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
        vx = -0.5;
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.7;
        }
        if (frame > 1) {
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
        if (y + vy >= 0.0 && frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.7;
            vx = 0.6;
        }
        if (frame > 1) {
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
        if (y + vy >= 0.0 && frame > 2) {
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
        if (frame == 2 && timer == 0) {
            ay = 0.035;
            vy = -2.7;
            vx = -0.6;
        }
        if (frame > 1) {
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
        if (y + vy >= 0.0 && frame > 2) {
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
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            vy = -2.7;
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
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xf:
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            vy = -2.7;
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
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::Unk40e630();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0x10:
        ay = 0.035;
        if (frame == 0 && timer == 0) {
            vy = -2.7;
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
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
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
        if (unk108 > 0 && timer > 0x63 && frame == 0) {
            pattern = 0x60;
            Vf0();
            break;
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
        if (frame == 2 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            unk16c = 1;
        }
        if (frame == 7 && timer == 0) {
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
            vx = 0.0;
            vy = 0.0;
            CPlayer::Unk4109d0(3);
        }
        if (frame == 2 && timer == 0) {
            vx = 2.5;
            vy = -0.3;
            ay = 0.02;
            if (unk3144 == 4) {
                vx = 3.2;
                vy = -0.25;
                ay = 0.025;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 2 && frame < 5) {
            y = 0.0;
            frame = 5;
            timer = 0;
            CPlayer::Unk40f1e0();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                frame = 3;
            }
            if (frame >= x8) {
                CPlayer::Unk40e630();
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xa4:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk4109d0(2);
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -2.0;
            vy = -1.0;
        }
        if (frame > 1) {
            vy += 0.04;
        }
        if (frame > 3 && frame < 7 && vy + y >= 0.0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                CPlayer::Unk40e630();
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 1.3;
            CPlayer::Unk4109d0(3);
            vy = 0.0;
            ay = 0.0;
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
        if (m_inputX == facing && unk313c >= 0x78) {
            pattern = 9;
            Vf0();
            vx = 1.1;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            vx = 1.1;
            ay = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -1.3;
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
            CPlayer::Unk4109d0(0xa);
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
            CPlayer::Unk4109d0(0xa);
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
                vx = unk3138 * 0.01;
                vy = unk313c * 0.01;
                ay = 0.035;
                Vf0();
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
            if (frame == 2) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 0;
            }
        }
        break;
    case 0xc8:
        vx = 0.0;
        vy = 0.0;
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
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xc9:
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
    case 0xca:
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
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xf;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (frame == 9 && timer == 0) {
            unk2c8 = 2;
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
    case 0xcb:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0x23;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (frame == 0xa && timer == 0) {
            unk2c8 = 2;
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
    case 0xcc:
        vx = 0.0;
        vy = 0.0;
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
        vx = 0.0;
        vy = 0.0;
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
            unk148 = unk148 + 0xd;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xce:
        vx = 0.0;
        vy = 0.0;
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
            unk148 = unk148 + 0x19;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (frame == 0xa && timer == 0) {
            unk2c8 = 2;
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
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            Vf0();
            break;
        }
        if (frame == 4 && timer == 0) {
            unk2c8 = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                unk168 = 0;
            }
            if (frame == 1) {
                unk148 = unk148 + 0xd;
                unk2c9 = 0x14;
                unk16c = 1;
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
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0x1e;
            unk2c9 = 0x14;
            unk16c = 1;
        }
        if (frame == 4 && timer == 0) {
            unk2c8 = 2;
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
            vx = 0.0;
            vy = 0.0;
            unk16c = 1;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 1;
            unk148 = unk148 + 0x19;
            l50.type = 0x19f;
            l50.x = (double)((int)x - facing * 0x1c);
            l50.y = (double)((int)y - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 2;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk16c = 1;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 1;
            unk148 = unk148 + 0x19;
            l50.type = 0x1a0;
            l50.x = (double)((int)x - facing * 0x15);
            l50.y = (double)((int)y - 0x3f);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 2;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk16c = 1;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 1;
            unk148 = unk148 + 0x19;
            l50.type = 0x1a1;
            l50.x = (double)((int)x - facing * 5);
            l50.y = (double)((int)y - 0x3d);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 2;
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
    case 0xd5:
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk16c = 1;
            unk3148 -= 0x3e8;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 1;
            unk148 = unk148 + 0x19;
            l50.type = 0x19f;
            l50.x = (double)((int)x - facing * 0x1c);
            l50.y = (double)((int)y - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 2;
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
    case 0xd6:
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk16c = 1;
            unk3148 -= 0x3e8;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 1;
            unk148 = unk148 + 0x19;
            l50.type = 0x1a0;
            l50.x = (double)((int)x - facing * 0x15);
            l50.y = (double)((int)y - 0x3f);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 2;
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
    case 0xd7:
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk16c = 1;
            unk3148 -= 0x3e8;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 1;
            unk148 = unk148 + 0x19;
            l50.type = 0x1a1;
            l50.x = (double)((int)x - facing * 5);
            l50.y = (double)((int)y - 0x3d);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 6 && timer == 0) {
            unk2c8 = 2;
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
    case 0xd8:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk16c = 1;
        }
        if (vx > 0.0) {
            vx -= 0.08;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame == 3) {
                unk2c9 = 0x15;
                unk148 = unk148 + 0x19;
                vx = 3.0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && unk168 == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->Vf0();
            (*m_opponent)->pattern = 0x6c;
            pattern = 0xdd;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x31);
            l50.y = (double)((int)y - 0x2b);
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
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                unk16c = 1;
            } else {
                unk16c = 0;
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
    case 0xdd:
        CPlayer::Unk410a80(0x32, 3);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 1) {
                if (facing == 1 && x + 20.0 < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->y = -150.0;
                (*m_opponent)->x = facing * 0x29 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -100.0;
                (*m_opponent)->x = facing * 0x2f + x;
            }
            if (frame == 3) {
                (*m_opponent)->y = -81.0;
                (*m_opponent)->x = x - facing * 0x5c;
                (*m_opponent)->facing = -facing;
                (*m_opponent)->pattern = 0x75;
            }
            if (frame == 4) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x - facing * 0x61;
                CPlayer::Unk4105a0(0x4b0, 750.0);
                (*m_opponent)->pattern = 0x61;
                (*m_opponent)->unk12c = 1;
                unk168 = 3;
                (*m_opponent)->Vf0();
                (*m_opponent)->Unk40f1e0();
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xe6:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
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
            unk168 = 0;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xe7:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 2 && timer == 0) {
            unk148 = unk148 + 0xa;
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
            unk168 = 0;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xe8:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0xa;
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
            unk168 = 0;
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xf0:
        vy = vy + ay;
        if (frame == 1 && unk168 == 3) {
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->Vf0();
            Vf0();
            CPlayer::Unk40f1e0();
            pattern = 0xf1;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x52);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x1f + x;
            (*m_opponent)->y = y - 82.0;
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
    case 0xf1:
        if (frame < 4) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 4) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 5) {
            CPlayer::Unk40f1e0();
            y = 0.0;
            Vf0();
            pattern = 0xd;
            break;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 80.0;
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->pattern = 0x67;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 0xb + x;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->facing = facing;
        }
        if (frame == 3 && timer == 0) {
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = x - facing * 0x25;
            (*m_opponent)->pattern = 0x45;
            CPlayer::Unk4105a0(0x514, 500.0);
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
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xf9:
        if (frame == 0 && timer == 0) {
            unkdc = 4;
            unkde = -0x14;
            vx = 0.0;
            unk16c = 1;
            unk14e = 0;
            unk14c = 0x3c;
            l50.type = 0x28;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk2c = 0x13;
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
    case 0xfa:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                vx = 0.0;
                ay = 0.0;
            }
            if (y < 0.0) {
                unk3138 = 1;
            }
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk16c = 1;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.025;
        }
        if (frame > 1 && vy + y >= 0.0) {
            timer = 0;
            frame = 0;
            pattern = 0xfd;
            break;
        }
        timer++;
        vy = vy + ay;
        if (timer >= l4 || timer >= l4 - 3 && unk3138 == 1) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                frame = 0xb;
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                vx = 0.0;
                ay = 0.0;
            }
            if (y < 0.0) {
                unk3138 = 1;
            }
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk16c = 1;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.035;
        }
        if (frame > 1 && vy + y >= 0.0) {
            timer = 0;
            frame = 0;
            pattern = 0xfd;
            unk313c = 1;
            break;
        }
        timer++;
        vy = vy + ay;
        if (timer >= l4 || timer >= l4 - 3 && unk3138 == 1) {
            timer = 0;
            frame++;
            if (frame == 1) {
                unk168 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            if (y < 0.0) {
                unk3138 = 1;
            }
            if (y == 0.0) {
                vx = 0.0;
                ay = 0.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x14);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4109d0(3);
            if (unk3144 == 4) {
                unk3148 -= 0x3e8;
                if (unk3148 < 0) {
                    unk3148 = 0;
                }
            } else if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        if (frame == 1 && timer == 0) {
            unk148 = unk148 + 0x19;
            unk16c = 2;
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.025;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk18 = facing;
            l50.unk21 = 1;
            Vf9(&l50);
        }
        if (frame > 1 && vy + y >= 0.0) {
            frame = 0;
            timer = 0;
            pattern = 0xfd;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && unk3138 == 1) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfd:
        vx = 0.0;
        vy = 0.0;
        CPlayer::Unk40e630();
        timer++;
        if (timer >= l4 || frame == 2 && unk313c == 1 && timer == 0x15) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                Vf0();
            }
        }
        break;
    case 0xfe:
        unk168 = 2;
        if (m_holdA > 0) {
            unk313c++;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 0;
            l50.type = 0x20;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk18 = -facing;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            CPlayer::Unk40f1e0();
            if (unk313c > 0x1e) {
                unk3138 = 1;
            }
        }
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 5 && timer == 0x14 && unk3138 == 0) {
            vx = -3.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 1.5;
            ax = -0.05;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6 && unk3138 == 1) {
                frame = 0;
                timer = 0;
                pattern = 0x105;
                break;
            }
            if (frame == 6) {
                x = (*m_opponent)->x - facing * 0x3c;
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xff:
        unk168 = 2;
        if (m_holdB > 0) {
            unk313c++;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 0;
            l50.type = 0x20;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk18 = -facing;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            CPlayer::Unk40f1e0();
            if (unk313c > 0x1e) {
                unk3138 = 1;
            }
        }
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 5 && timer == 0x14 && unk3138 == 0) {
            x = (*m_opponent)->x - facing * 0xb4;
        }
        if (frame == 6 && timer == 0) {
            vx = 1.5;
            ax = -0.05;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (0) {}
            if (0) {}
            if (frame == 6 && unk3138 == 1) {
                frame = 0;
                timer = 0;
                pattern = 0x106;
                x = (*m_opponent)->x - facing * 0x64;
                if (x > 540.0 && facing == 1) {
                    x = 540.0;
                }
                if (x < 100.0 && facing == -1) {
                    x = 100.0;
                }
                y = -100.0;
                break;
            }
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x14);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4109d0(3);
            if (unk3144 == 4) {
                unk3148 -= 0x3e8;
                if (unk3148 < 0) {
                    unk3148 = 0;
                }
            } else if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            unk16c = 1;
        }
        if (frame == 2 && timer == 0) {
            unk2c8 = 0;
            l50.type = 0x20;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk18 = -facing;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 4 && unk168 == 2) {
            timer = 0;
            frame = 6;
            break;
        }
        if (frame == 5 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        vx = vx + ax;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 5 && timer == 0x14) {
            vx = 8.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 3.5;
            ax = -0.05;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                unk168 = 0;
            }
            if (frame >= x8) {
                CPlayer::Unk40e630();
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x101:
        unk168 = 2;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            if (unk3144 != 4) {
                unk3144 = 2;
                l50.type = 0x19c;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.unk0 = 1;
                l50.unk20 = 2;
                l50.unk18 = facing;
                l50.unk21 = 1;
                Vf9(&l50);
            } else {
                unk3148 -= 0x3e8;
                if (unk3148 < 0) {
                    unk3148 = 0;
                }
                l50.type = 0x1a8;
                l50.x = (double)((int)x + facing * 0x50);
                l50.y = (double)(int)y;
                l50.unk0 = 1;
                l50.unk20 = 2;
                l50.unk18 = facing;
                l50.unk21 = 1;
                Vf9(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x102:
        unk168 = 2;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            if (unk3144 != 4) {
                unk3144 = 2;
                l50.type = 0x19c;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = (double)(int)y;
                l50.unk0 = 1;
                l50.unk20 = 2;
                l50.unk18 = facing;
                l50.unk21 = 1;
                Vf9(&l50);
            } else {
                l50.type = 0x1a8;
                unk3148 -= 0x3e8;
                if (unk3148 < 0) {
                    unk3148 = 0;
                }
                l50.x = (double)((int)x + facing * 0xa0);
                l50.y = (double)(int)y;
                l50.unk0 = 1;
                l50.unk20 = 2;
                l50.unk18 = facing;
                l50.unk21 = 1;
                Vf9(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x103:
        unk168 = 2;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            if (unk3144 != 4) {
                unk3144 = 2;
                l50.type = 0x19c;
                l50.x = (double)((int)x + facing * 0xc8);
                l50.y = (double)(int)y;
                l50.unk0 = 1;
                l50.unk20 = 2;
                l50.unk18 = facing;
                l50.unk21 = 1;
                Vf9(&l50);
            } else {
                l50.type = 0x1a8;
                unk3148 -= 0x3e8;
                if (unk3148 < 0) {
                    unk3148 = 0;
                }
                l50.x = (double)((int)x + facing * 0xf0);
                l50.y = (double)(int)y;
                l50.unk0 = 1;
                l50.unk20 = 2;
                l50.unk18 = facing;
                l50.unk21 = 1;
                Vf9(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk2c8 = 5;
            unk3148 = 0x2710;
            unk314c = 1;
            unk3150 = 1;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x191;
            l50.x = (double)(int)x;
            if (unk3140 == 1) {
                l50.x = (double)((int)x + facing * 0x3c);
                if ((int)x + facing * 0x3c > 0x258) {
                    l50.x = 600.0;
                }
                if ((int)x + facing * 0x3c < 0x28) {
                    l50.x = 40.0;
                }
            }
            if (unk3140 == 2) {
                l50.x = (double)((int)x - facing * 0x3c);
                if ((int)x - facing * 0x3c > 0x258) {
                    l50.x = 600.0;
                }
                if ((int)x - facing * 0x3c < 0x28) {
                    l50.x = 40.0;
                }
            }
            l50.y = (double)((int)y - 0x11);
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            unk16c = 1;
        }
        if (frame > 6) {
            vx -= 0.055;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
    case 0x106:
        if (frame == 0 && timer == 0) {
            vx = 1.0;
            vy = 0.0;
            unk16c = 1;
        }
        if (0) {}
        if (frame > 2) {
            vy += 0.035;
        }
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
            if (frame >= x8) {
                pattern = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk3144 = 2;
            unk2c8 = 5;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1ac;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x14);
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk21 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk3144 = 2;
            unk2c8 = 5;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1ad;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x14);
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk21 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x109:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4109d0(3);
            if (unk3144 == 4) {
                unk3148 -= 0x3e8;
                if (unk3148 < 0) {
                    unk3148 = 0;
                }
            } else if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        if (frame == 3 && timer == 0) {
            unk3144 = 2;
            unk2c8 = 5;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1ae;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x14);
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk21 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10a:
        unk168 = 2;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk3144 = 2;
            l50.type = 0x1b0;
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = (double)((int)y - 0x14);
            l50.unk0 = 1;
            l50.unk20 = 2;
            l50.unk18 = facing;
            l50.unk21 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10b:
        unk168 = 2;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk3144 = 2;
            l50.type = 0x1b0;
            l50.x = (double)((int)x + facing * 0xa0);
            l50.y = (double)((int)y - 0x14);
            l50.unk0 = 1;
            l50.unk20 = 2;
            l50.unk18 = facing;
            l50.unk21 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10c:
        unk168 = 2;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 3 && timer == 0) {
            unk3144 = 2;
            l50.type = 0x1b0;
            l50.x = (double)((int)x + facing * 0xf0);
            l50.y = (double)((int)y - 0x14);
            l50.unk0 = 1;
            l50.unk20 = 2;
            l50.unk18 = facing;
            l50.unk21 = 1;
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
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk2c8 = 5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 2) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            unk16c = 1;
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
        if (frame == 4 && timer == 0) {
            unk2c8 = 0;
        }
        if (frame == 8 && timer == 0) {
            vx = 5.0;
        }
        if (frame == 9 && timer == 0) {
            vx = 1.8;
            ax = -0.05;
        }
        if (frame > 8) {
            vx = vx + ax;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 8) {
            if (unk168 == 2 || unk168 == 5) {
                timer = 0;
                frame = 9;
                break;
            }
            if (unk168 == 3) {
                (*m_opponent)->unk14a = 0x270f;
                Vf0();
                (*m_opponent)->Vf0();
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = 0x6c;
                pattern = 0x132;
                break;
            }
        }
        if (frame > 0 && frame < 0x12) {
            CPlayer::Unk410a80(0x32, 3);
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
    case 0x130:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 2) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            unk16c = 1;
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
        if (frame == 4 && timer == 0) {
            unk2c8 = 0;
        }
        if (frame == 8 && timer == 0) {
            vx = 7.0;
        }
        if (frame == 9 && timer == 0) {
            vx = 1.8;
            ax = -0.05;
        }
        if (frame > 8) {
            vx = vx + ax;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 8) {
            if (unk168 == 2 || unk168 == 5) {
                timer = 0;
                frame = 9;
                break;
            }
            if (unk168 == 3) {
                (*m_opponent)->unk14a = 0x270f;
                Vf0();
                (*m_opponent)->Vf0();
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = 0x6c;
                pattern = 0x133;
                break;
            }
        }
        if (frame > 0 && frame < 0x12) {
            CPlayer::Unk410a80(0x32, 3);
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
    case 0x131:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
        }
        if (frame == 2 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            unk16c = 1;
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
        if (frame > 1) {
            m_game->Unk4080c0(0xf);
        }
        if (frame <= 2) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 4 && timer == 0) {
            unk2c8 = 0;
        }
        if (frame == 8 && timer == 0) {
            vx = 10.0;
        }
        if (frame == 9 && timer == 0) {
            vx = 1.8;
            ax = -0.05;
        }
        if (frame > 8) {
            vx = vx + ax;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 8) {
            if (unk168 == 2 || unk168 == 5) {
                timer = 0;
                frame = 9;
                break;
            }
            if (unk168 == 3) {
                (*m_opponent)->unk14a = 0x270f;
                Vf0();
                (*m_opponent)->Vf0();
                (*m_opponent)->y = 0.0;
                (*m_opponent)->pattern = 0x6c;
                pattern = 0x134;
                l50.type = 0x1a3;
                l50.x = 0.0;
                l50.y = 20.0;
                l50.unk20 = 0;
                l50.unk0 = 1;
                l50.unk18 = 1;
                l50.unk21 = 0;
                l50.unk30 = 1;
                Vf9(&l50);
                l50.type = 0x1a4;
                l50.x = 0.0;
                l50.y = 38.0;
                l50.unk20 = 0;
                l50.unk0 = 1;
                l50.unk18 = 1;
                l50.unk21 = 1;
                l50.unk30 = 1;
                Vf9(&l50);
                break;
            }
        }
        if (frame > 0 && frame < 0x12) {
            CPlayer::Unk410a80(0x32, 3);
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
    case 0x132:
        if (frame == 0 && timer == 0) {
            vx = 0.3;
            x = (*m_opponent)->x + facing * 0x1e;
            unk168 = 0;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 0xb && timer == 0) {
            unk2c9 = 0x14;
        }
        if (frame == 0xf && timer == 0) {
            unk2c8 = 2;
        }
        if (frame == 0xf && timer == 0x5a) {
            (*m_opponent)->pattern = 0x47;
            (*m_opponent)->unk14a = 0;
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -4.0;
            unk168 = 2;
            CPlayer::Unk4105a0(0x960, 400.0);
            l50.type = 0x34;
            l50.x = (*m_opponent)->x;
            l50.unk2c = 0x16;
            l50.y = (*m_opponent)->y - 40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0 && frame < 0xf) {
            CPlayer::Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6 && unk3138 < 9) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 9) {
                x = facing * 0x50 + x;
                unk3138 = 0;
            }
            if (frame == 0xd && unk3138 < 0xc) {
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
    case 0x133:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            vx = 0.3;
            x = (*m_opponent)->x + facing * 0x1e;
            unk168 = 0;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 0xb && timer == 0) {
            unk2c9 = 0x14;
        }
        if (frame == 0xe && timer == 0) {
            unk2c8 = 2;
        }
        if (frame == 0xf && timer == 0 && unk3138 == 7) {
            (*m_opponent)->pattern = 0x47;
            (*m_opponent)->unk14a = 0;
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -4.0;
            unk168 = 2;
            CPlayer::Unk4105a0(0xc80, 400.0);
            l50.type = 0x34;
            l50.x = (*m_opponent)->x;
            l50.unk2c = 0x16;
            l50.y = (*m_opponent)->y - 40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0 && frame < 0xf) {
            CPlayer::Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6 && unk3138 < 9) {
                frame = 4;
                unk3138++;
            }
            if (frame == 9) {
                x = facing * 0x50 + x;
                unk3138 = 0;
            }
            if (frame == 0xd && unk3138 < 0xc) {
                frame = 0xb;
                unk3138++;
            }
            if (frame == 0xe) {
                unk3138 = 0xc;
            }
        }
        if (frame >= x8) {
            if (unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            } else {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x134:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            vx = 0.3;
            x = (*m_opponent)->x + facing * 0x1e;
            unk168 = 0;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 0xb && timer == 0) {
            unk2c9 = 0x14;
        }
        if (frame == 0xe && timer == 0) {
            unk2c8 = 2;
        }
        if (frame == 0xf && timer == 0 && unk3138 == 7) {
            (*m_opponent)->pattern = 0x47;
            (*m_opponent)->unk14a = 0;
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -4.0;
            unk168 = 2;
            CPlayer::Unk4105a0(0x1194, 400.0);
            (*m_opponent)->unk124 = (int)(200.0 * unk178 / 10000.0);
            l50.type = 0x34;
            l50.x = (*m_opponent)->x;
            l50.unk2c = 0x16;
            l50.y = (*m_opponent)->y - 40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0 && frame < 0xf) {
            CPlayer::Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6 && unk3138 < 9) {
                frame = 4;
                unk3138++;
            }
            if (frame == 9) {
                x = facing * 0x50 + x;
                unk3138 = 0;
            }
            if (frame == 0xd && unk3138 < 0xc) {
                frame = 0xb;
                unk3138++;
            }
            if (frame == 0xe) {
                unk3138 = 0xc;
            }
        }
        if (frame >= x8) {
            if (unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            } else {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x135:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 0 && timer == 0) {
            unk2c8 = 3;
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
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
            l50.type = 0x1ab;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = 0.0;
            l50.unk30 = 1;
            l50.unk18 = facing;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6 && unk14c > 0) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            vx = 0.3;
            x = (*m_opponent)->x + facing * 0x1e;
        }
        if (frame == 9 && timer == 0) {
            x += 0.0;
            vx = 0.0;
        }
        if (frame == 0xb && timer == 0) {
            unk2c9 = 0x14;
        }
        if (frame == 0xe && timer == 0) {
            unk2c8 = 2;
        }
        if (frame == 0xf && timer == 0 && unk3138 == 7) {
            (*m_opponent)->pattern = 0x47;
            (*m_opponent)->unk14a = 0;
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -8.0;
            CPlayer::Unk4105a0(0x1068, 750.0);
            (*m_opponent)->unk124 = (int)(200.0 * unk178 / 10000.0);
            l50.type = 0x34;
            l50.x = (*m_opponent)->x;
            l50.unk2c = 0x16;
            l50.y = (*m_opponent)->y - 40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 0 && frame < 0xf) {
            CPlayer::Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6 && unk3138 < 9) {
                frame = 4;
                unk3138++;
            }
            if (frame == 9) {
                x = facing * 0x50 + x;
                unk3138 = 0;
            }
            if (frame == 0xd && unk3138 < 0xc) {
                frame = 0xb;
                unk3138++;
            }
            if (frame == 0xe) {
                unk3138 = 0xc;
            }
        }
        if (frame >= x8) {
            if (unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            } else {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk3148 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                if (unk3144 == 1) {
                    frame = 0;
                    break;
                }
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk3148 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                if (unk3144 == 1) {
                    frame = 0;
                    break;
                }
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk3148 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame >= x8) {
                if (unk3144 == 1) {
                    frame = 0;
                    break;
                }
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0xd);
            l50.y = (double)((int)y - 0x33);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1b6;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0xf);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = facing;
            l50.unk30 = 0x12c;
            Vf9(&l50);
            unk3144 = 2;
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
    case 0x13f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
    case 0x140:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0xd);
            l50.y = (double)((int)y - 0x33);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1ba;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0xf);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = facing;
            l50.unk30 = 0x12c;
            Vf9(&l50);
            unk3144 = 2;
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
    case 0x141:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
    case 0x142:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xd);
            l50.y = (double)((int)y - 0x33);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1be;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0xf);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = facing;
            l50.unk30 = 0x12c;
            Vf9(&l50);
            unk3144 = 2;
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
    case 0x143:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
    case 0x144:
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::Unk40f1e0();
            unk14c = 0x78;
            unk148 = unk148 - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x13);
            l50.y = (double)((int)y - 0x32);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
            unk16c = 0;
        }
        if (frame == 4 && unk168 == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Unk40f1e0();
            (*m_opponent)->Vf0();
            pattern = 0x145;
            (*m_opponent)->pattern = 0x79;
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (frame == 5 && timer == 0) {
            unk3148 = 0;
            unk16c = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 4) {
                if ((*m_opponent)->y == 0.0) {
                    unk16c = 1;
                } else {
                    unk16c = 0;
                }
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x145:
        CPlayer::Unk410a80(0x32, 3);
        if (frame < 2) {
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (frame > 1 && frame < 0xa) {
            CPlayer::Unk410b10(0xb1, 3);
            (*m_opponent)->Unk410ac0(0xb0, 3);
        }
        if (frame == 1 && timer == 0) {
            unk2c8 = 3;
            l50.type = 0x1c2;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            l50.unk24 = 1;
            l50.unk18 = 1;
            Vf9(&l50);
        }
        if (frame == 2 && timer == 0) {
            (*m_opponent)->pattern = 0x6b;
        }
        if (frame == 0xb && timer == 0) {
            unk2c8 = 2;
        }
        if (frame == 0xc && timer == 0) {
            (*m_opponent)->pattern = 0x47;
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -5.0;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->unk128 = 1;
            CPlayer::Unk4105a0((int)(unk3148 * 0.15 + 3500.0), 500.0);
            unk2c9 = 0x16;
            (*m_opponent)->facing = -facing;
            (*m_opponent)->unk14a = 0;
            l50.type = 0x34;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = (double)((int)(*m_opponent)->y - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3148 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk168 = 0;
            if (frame == 6 && unk3138 < 4) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
    }
}
