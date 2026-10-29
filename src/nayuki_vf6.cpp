// CNayuki::Vf6 (0x451850-0x46108f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CNayuki's
// .rdata, which starts with its constructor's folder name (nayuki.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CNayuki::Vf6()
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
        vx = unk3148 * 0.02 + 0.6;
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
        vx = -0.6 - unk3148 * 0.02;
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
        CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.024;
            vy = -2.0;
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
        if (y + vy >= 0.0 && frame > 4) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 5:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.024;
            vy = -2.0;
            vx = 0.5;
            if (unk158 == 1) {
                vx = 0.7;
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
        if (y + vy >= 0.0 && frame > 4) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 6:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.024;
            vy = -2.0;
            vx = -0.5;
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
        if (y + vy >= 0.0 && frame > 4) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 7:
        vx = 0.0;
        vy = 0.0;
        CPlayer::FaceOpponent();
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
        CPlayer::FaceOpponent();
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
        CPlayer::FaceOpponent();
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
        ay = 0.024;
        if (frame == 0 && timer == 0) {
            vy = -2.0;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xf:
        ay = 0.024;
        if (frame == 0 && timer == 0) {
            vy = -2.0;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0x10:
        ay = 0.024;
        if (frame == 0 && timer == 0) {
            vy = -2.0;
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
            CPlayer::FaceOpponent();
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
                Vf0();
            }
        }
        break;
    case 0x33:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x34:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x35:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x36:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x37:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x38:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x39:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x3a:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
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
        m_gauge = m_gauge + 3;
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
            m_gauge = m_gauge + 0x1e;
            unk3138++;
            unk124 = unk124 + 0x78;
            vx = 0.5;
            vy = -2.5;
            ay = 0.025;
            unk2c9 = 0x1f;
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
                Vf0();
            }
        }
        break;
    case 0x4c:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
                Vf0();
            }
        }
        break;
    case 0x4d:
        if (unk120 != 0) {
            unk118 -= 0.6;
        }
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
            l50.layer = 1;
            Vf9(&l50);
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
                l50.scale = 0;
                l50.layer = 0;
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
                Vf0();
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
                Vf9(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
            unk2c9 = 0x21;
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
                Vf0();
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
                Vf9(&l50);
                unk3144 = 1;
            }
            if (unk120 != 0) {
                unk118 -= 30.0;
            }
            unk2c9 = 0x21;
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
                Vf0();
                CPlayer::FaceOpponent();
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
                l50.scale = 0;
                l50.layer = 0;
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
            l50.screen = 1;
            l50.unk18 = 1;
            l50.scale = 0;
            l50.layer = 1;
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
        if (frame == 1 && timer == 0 && unk3148 > 0) {
            unk3148--;
        }
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
            l50.scale = 2;
            l50.layer = 0;
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
            l50.scale = 2;
            l50.layer = 0;
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
        if (m_hp > 0 && timer > 0x63) {
            pattern = 0x60;
            Vf0();
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
                Vf0();
            }
        }
        break;
    case 0x7b:
        vx = 0.0;
        vy = 0.0;
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
    case 0x96:
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
                Vf0();
            }
        }
        break;
    case 0x97:
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
                Vf0();
            }
        }
        break;
    case 0x98:
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
                Vf0();
            }
        }
        break;
    case 0x99:
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
                Vf0();
            }
        }
        break;
    case 0x9a:
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
                Vf0();
            }
        }
        break;
    case 0x9b:
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
                Vf0();
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
                Vf0();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
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
                Vf0();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
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
                Vf0();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0xa1:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
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
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 7 && timer == 0) {
            CPlayer::StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            unk2c9 = 0x3e;
            m_gauge = m_gauge - 0x3e8;
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
            if (frame == 0xd) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk4109d0(1);
            CPlayer::StopMoving();
        }
        if (frame < 0xb && frame > 4) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 0xb) {
            timer = 0;
            CPlayer::StopMoving();
            frame = 0xb;
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                vx = 1.4;
                vy = -0.75;
                ay = 0.015;
            }
            if (frame == 0xb) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
                break;
            }
        }
        break;
    case 0xa4:
        CPlayer::Unk4109d0(2);
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 3) {
            vx += 0.02;
            vy += 0.035;
        }
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (y + vy > 0.0 && frame < 0xb) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                vx = -2.0 - unk3148 * 0.1;
                vy = -1.2;
            }
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 3;
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0) {
            if (unk3148 > 7) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            CPlayer::StopMoving();
            l50.type = 0x190;
            l50.x = (double)((int)x - facing * 0x24);
            l50.y = (double)((int)y - 0x3e);
            l50.unk18 = facing;
            l50.layer = 0;
            l50.scale = 0;
            Vf9(&l50);
        }
        if (unk3138 == 1 && frame == 0) {
            vx = 1.9;
            vy = -0.2;
            ay = 0.035;
            timer = 0;
            frame = 1;
            break;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            Vf0();
            pattern = 0xb3;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            if (unk3148 > 4) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x3e);
            l50.unk18 = -facing;
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
        }
        if (unk3138 == 1 && frame == 0) {
            vx = -1.9;
            vy = -0.2;
            ay = 0.035;
            timer = 0;
            frame = 1;
            break;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            Vf0();
            pattern = 0xb3;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa7:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            if (unk120 == 1) {
                m_proration = unk118 * 5.0 + m_proration;
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
                m_proration = unk118 * 5.0 + m_proration;
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
                pattern = 9;
                CPlayer::FaceOpponent();
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
            m_attackResult = 0;
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
    case 0xb3:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
        }
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
        if (y + vy > 0.0 && frame < 0xb) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xb;
            unk2c9 = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 0xb) {
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
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            unk2c9 = 0x15;
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
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && frame == 2 && unk3148 > 4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 4;
            }
            if (frame == 2 && unk3148 > 3) {
                frame = 3;
            }
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xca:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 0;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            unk2c9 = 0x14;
            if (unk3148 > 5) {
                m_hitsLeft = 1;
            }
        }
        if (frame == 5 && timer == 0) {
            m_hitsLeft = 8;
        }
        if (frame < 0xa && frame > 5) {
            vy = vy + ay;
        }
        if (vy + y > 0.0) {
            y = 0.0;
            timer = 0;
            if (frame < 0xa && frame > 5) {
                frame = 0xa;
                CPlayer::Unk410a10(3, 0);
                l50.type = 3;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk2c9 = 7;
            }
            vy = 0.0;
        }
        if (frame >= 0xa) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                vy = -1.5;
                vx = unk3148 * 0.05 + 1.0;
                ay = 0.06;
            }
            if (frame == 0xa) {
                frame = frame - 4;
            }
            if (frame == 0xb) {
                if (unk3148 > 4) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame == 4 || frame == 5 || frame == 7 || frame == 9 || frame == 0xb) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xcb:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk3148 > 4 && y == 0.0 && unk15c < 3 && m_attackResult >= 2 && unk3148 > 6) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            unk2c9 = 0x14;
            if (unk3148 > 5) {
                m_hitsLeft = 1;
            }
        }
        if (frame == 0xa && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame > 0xd) {
            vy = vy + ay;
        }
        if (frame > 0xd && vy + y > 0.0) {
            Vf0();
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa) {
                unk2c8 = 3;
            }
            if (frame < 9) {
                m_attackResult = 0;
            }
            if (frame == 8 || frame == 9 || frame == 0xa) {
                x = facing * 0x28 + x;
            }
            if (frame == 0xe) {
                vy = -1.0;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= x8) {
                frame--;
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
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            unk2c9 = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                frame = 4;
            }
            if (frame == 2 && unk3148 > 4) {
                frame = 3;
            }
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2) {
            pattern = 4;
            if (m_inputX == facing) {
                pattern = 5;
            }
            if (m_inputX == -facing) {
                pattern = 6;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 || timer >= 3 && (frame == 1 && unk3148 > 0 || frame == 2 && unk3148 > 1 || frame == 3 && unk3148 > 3 || frame == 4 && unk3148 > 5)) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                x = facing * 0xf + x;
            }
            if (frame == 2) {
                x = facing * 0xf + x;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::FaceOpponent();
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
            Vf0();
            break;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && frame < unk3148 - 4 && frame < 4) {
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
                Vf0();
            }
        }
        break;
    case 0xcf:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            unk2c9 = 0x15;
            m_hitsLeft = 1;
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
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd0:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            unk2c9 = 0x14;
            m_hitsLeft = unk3148 / 2 + 2;
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
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd1:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 3;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && frame < unk3148 - 3 && frame < 4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 4 && timer == 0) {
            ay = 0.055;
            vy = -1.7;
            vx = 0.5;
            m_hitsLeft = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        if (frame == 8 && timer == 0) {
            unk2c9 = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                Vf0();
                pattern = 3;
                CPlayer::FaceOpponent();
                break;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 0xb) {
            y = 0.0;
            unk2c9 = 9;
            frame = 0xb;
            timer = 0;
            CPlayer::StopMoving();
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
            Vf0();
            break;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xd4:
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
            vy -= -1.0;
            ay = 0.035;
        }
        vy = vy + ay;
        if (m_attackResult > 1) {
            timer = 0;
            frame = 0;
            pattern = 0x101;
            vx = -vx;
            vy = -2.5;
            ay = 0.025;
            break;
        }
        if (vy + y > 0.0 && frame < 5 && frame > 1) {
            y = 0.0;
            timer = 0;
            frame = 5;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
            vx = 0.0;
            vy = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                frame--;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 7;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xd5:
        ay = 0.04;
        vx = 0.0;
        vy = vy + ay;
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0x61;
            CPlayer::StopMoving();
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xd6:
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 3;
        }
        if (y + vy > 0.0) {
            y = 0.0;
            timer = 0;
            CPlayer::StopMoving();
            frame = 0xa;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 7;
                Vf0();
            }
        }
        break;
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            if (x > 600.0) {
                x = 600.0;
            }
            if (x < 40.0) {
                x = 40.0;
            }
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->x = facing * 0xf + x;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x16);
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
                Vf0();
            }
        }
        break;
    case 0xdd:
        if (frame == 4 && timer == 0) {
            CPlayer::DealDamage(0x3e8, 750.0);
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->Vf0();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unkc0 = 1.0;
            (*m_opponent)->unkc8 = -2.5;
            (*m_opponent)->y = -50.0;
            (*m_opponent)->x = x;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->x = (*m_opponent)->x - facing;
            }
            if (frame == 2) {
                (*m_opponent)->x = (*m_opponent)->x - facing;
            }
            if (frame == 3) {
                (*m_opponent)->x = (*m_opponent)->x - facing;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xe6:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 5;
            unk2c9 = 0x15;
            m_hitsLeft = 1;
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
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xe7:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            unk2c9 = 0x14;
            m_hitsLeft = unk3148 / 2 + 2;
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
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xe8:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && unk15a == 0) {
            unk15a++;
            pattern = 0xe;
            if (m_inputX == facing) {
                pattern = 0xf;
            }
            if (m_inputX == -facing) {
                pattern = 0x10;
            }
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 3;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - 3 && frame < unk3148 - 3 && frame < 4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xf8:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->Vf0();
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x21);
            l50.y = (double)((int)y - 0x33);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x21 + x;
            (*m_opponent)->y = y - 61.0;
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
        if (frame < 7) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 7) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 5) {
            CPlayer::StopMoving();
            y = 0.0;
            Vf0();
            pattern = 0xd;
            break;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 66.0;
            (*m_opponent)->x = facing * 0x17 + x;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 69.0;
            (*m_opponent)->x = facing * 0x15 + x;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 73.0;
            (*m_opponent)->x = facing * 0x13 + x;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 74.0;
            (*m_opponent)->x = facing * 0x13 + x;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 0x11 + x;
        }
        if (frame == 6) {
            (*m_opponent)->y = y - 70.0;
            (*m_opponent)->x = (facing << 4) + x;
        }
        if (frame == 7 && timer == 0) {
            (*m_opponent)->facing = facing;
            (*m_opponent)->y = y - 60.0;
            (*m_opponent)->x = x - facing * 0x25;
            (*m_opponent)->pattern = 0x3f;
            CPlayer::DealDamage(0x514, 500.0);
            (*m_opponent)->Vf0();
            (*m_opponent)->unkc0 = -2.0;
            (*m_opponent)->unkc8 = -1.0;
        }
        if (frame == 0xb && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xb) {
                facing = -facing;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.unk28 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * unk3148 * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.unk28 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * unk3148 * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x193;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.unk28 = 1;
            l50.scale = 0;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * unk3148 * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 2;
        }
        if (y < 0.0) {
            vy = vy + ay;
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                unk2c9 = 0x14;
                m_gauge = m_gauge + 0x2d;
                vx = 1.2;
                vy = -2.5;
                ay = 0.03;
            }
            if (frame >= x8) {
                pattern = 0x100;
                if (m_inputY == 1) {
                    pattern = 0x102;
                }
                Vf0();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                unk2c9 = 0x14;
                m_gauge = m_gauge + 0x2d;
                vx = 1.7;
                vy = -1.7;
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame >= x8) {
                pattern = 0x102;
                Vf0();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            vx = 2.4;
            m_hitsLeft = 1;
            vy = 0.0;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && unk313c == 0) {
            vx = -0.7;
            vy = -2.0;
            ay = 0.035;
            pattern = 0x101;
            unk2c9 = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk313c++;
            break;
        }
        if (m_hitsLeft == 0) {
            vx = -0.7;
            vy = -2.0;
            ay = 0.035;
            pattern = 0x101;
            break;
        }
        timer++;
        if (y == 0.0 && vy >= 0.0) {
            vy = 0.0;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case 0x101:
        vy = vy + ay;
        CPlayer::Unk40f170();
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                Vf0();
                pattern = 9;
            }
        }
        break;
    case 0x102:
        ay = 0.04;
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0x61;
            CPlayer::StopMoving();
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x103:
        CPlayer::StopMoving();
        if (frame == 0 && timer == 0) {
            unk2c8 = 4;
        }
        if (frame == 0xa && timer == 0) {
            unk3148++;
        }
        if (frame == 0xa && timer == 0) {
            unk2c8 = 5;
        }
        if (unk3148 > 9) {
            unk3148 = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                Vf0();
                pattern = 7;
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            ay = 0.035;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame > 8 && vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 0xc;
        }
        if (frame > 4 && frame < 9) {
            vx -= 0.025;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk313c++;
            m_attackResult = 0;
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.8;
                vy = -1.9;
                if (unk3148 > 2) {
                    vx = 2.1;
                    vy = -2.0;
                }
                if (unk3148 > 5) {
                    vx = 2.4;
                    vy = -2.1;
                }
                if (unk3148 > 8) {
                    vx = 3.0;
                    vy = -2.2;
                }
            }
            if (frame == 5) {
                if (unk3148 > 2) {
                    frame = 6;
                }
                if (unk3148 > 5) {
                    frame = 7;
                }
                if (unk3148 > 8) {
                    frame = 8;
                }
                break;
            }
            if (frame > 5 && frame < 9) {
                frame = 9;
            }
            if (frame == 9) {
                ay = 0.035;
                vx *= 0.3;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 3;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame > 5 && vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk313c++;
            if (frame == 5 || frame == 9 || frame == 0xd) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.2;
                vy = -1.2;
                ay = 0.03;
                if (unk3148 > 6) {
                    vy = -2.2;
                }
            }
            if (frame == 8 && unk3148 < 5 || frame == 0xb && unk3148 < 7) {
                frame = 0xf;
            }
            if (frame == 0xf) {
                if (vy < 0.0) {
                    vy *= 0.5;
                }
                vx *= 0.5;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x106:
        if (frame == 0 && timer == 0) {
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = unk3148 + 1;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 0x63;
        }
        vy = vy + ay;
        if (frame > 0xb && vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 0x10;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk313c++;
            if (frame == 5 || frame == 9 || frame == 0xd) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 0.8;
                vy = -1.5;
                ay = 0.035;
                unk13c = unk3148 * 0xc + 0x1e;
            }
            if (frame == 7 || frame == 0xb) {
                vy = -1.4;
            }
            if (frame == 0xc) {
                frame = 4;
            }
            if ((frame == 0xb || frame == 8) && unk3138 > unk3148) {
                frame = 0xc;
            }
            if (frame == 0xb || frame == 8) {
                unk3138++;
            }
            if (frame == 0xf && vy < 0.0) {
                vy *= 0.5;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = unk3148 + 6;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame > 0xf) {
            vx -= 0.028;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 6 || frame == 0xb) && timer == 0) {
            unk2c9 = 0x14;
        }
        if (y + vx > 0.0 && frame > 5 && frame < 0x10) {
            timer = 0;
            y = 0.0;
            vy = 0.0;
            frame = 0x10;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk313c++;
            if (unk313c > 2) {
                m_attackResult = 0;
                unk313c = 0;
            }
            if (frame == 5) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.8;
                vy = -1.7;
                ay = 0.035;
                if (unk3138 == 1) {
                    vx = 0.6;
                    vy = -3.2;
                    ay = 0.024;
                }
            }
            if (frame == 0x10) {
                frame = 5;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 2;
        }
        if (frame > 9) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            unk2c9 = 0x15;
        }
        timer++;
        if (timer >= 0x18 && unk3148 > 3 && frame == 0xb) {
            frame++;
            timer = 0;
            m_attackResult = 0;
        }
        if (timer >= l4 || timer >= l4 - unk3148 * 3 && frame == 0xb || timer >= l4 - 3 && frame == 1 && unk3148 > 2 || timer >= l4 - 3 && frame == 2 && unk3148 > 4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 2.2;
                if (unk3138 == 1) {
                    vx = 3.4;
                }
            }
            if (frame == 7 && unk313c < 2) {
                frame = 4;
                unk313c++;
            }
            if (frame == 7 && unk3138 == 1 && unk313c < 4) {
                frame = 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x109:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 2;
        }
        if (frame > 9) {
            vx += 0.08;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            unk2c9 = 0x15;
        }
        timer++;
        if (timer >= 0x18 && unk3148 > 3 && frame == 0xb) {
            frame++;
            timer = 0;
            m_attackResult = 0;
        }
        if (timer >= l4 || timer >= l4 - unk3148 * 3 && frame == 0xb || timer >= l4 - 3 && frame == 1 && unk3148 > 2 || timer >= l4 - 3 && frame == 2 && unk3148 > 4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = -2.2;
            }
            if (frame == 7 && unk313c < 2) {
                frame = 4;
                unk313c++;
            }
            if (frame == 7 && unk3138 == 1 && unk313c < 4) {
                frame = 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = unk3148 + 1;
        }
        if (frame > 9) {
            vx -= 0.3;
            m_hitsLeft = 1;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            unk2c9 = 0x15;
        }
        timer++;
        if (timer >= l4 || timer >= l4 - unk3148 * 3 && frame == 0xb || timer >= l4 - 3 && frame == 1 && unk3148 > 2 || timer >= l4 - 3 && frame == 2 && unk3148 > 4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 2.5;
            }
            if (frame == 7 && unk313c < 2) {
                frame = 4;
                unk313c++;
            }
            if (frame == 7 && unk3138 == 1 && unk313c < 4) {
                frame = 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x10b:
        if (frame == 0 && timer == 0) {
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 0x63;
        }
        if (frame > 9) {
            vx -= 0.3;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            unk2c9 = 0x15;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xb) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                vx = 2.8;
            }
            if (frame == 7 && unk313c < 2) {
                frame = 4;
                unk313c++;
            }
            if (frame == 7 && unk3138 == 1 && unk313c < 4) {
                frame = 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x10c:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 7) {
            if (m_command == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xa3;
                if (facing == -1) {
                    pattern = 0xa4;
                }
                break;
            }
            if (m_command == 0) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xa4;
                if (facing == -1) {
                    pattern = 0xa3;
                }
                break;
            }
            if (m_command == 0xa && unk3148 > 0) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xfa;
                break;
            }
            if (m_command == 0xb && unk3148 > 0) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xfb;
                break;
            }
            if (m_command == 0x14 && unk3148 > 0) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x104;
                break;
            }
            if (m_pressA == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x113;
                if (unk3148 > 4) {
                    pattern = 0x10d;
                }
                break;
            }
            if (m_pressB == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x112;
                break;
            }
            if (m_pressC == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x114;
                if (m_inputY == 1) {
                    pattern = 0x119;
                }
                break;
            }
            if (m_pressD == 1) {
                if (m_inputX == facing) {
                    Vf0();
                    CPlayer::Unk40f170();
                    pattern = 0x115;
                    if (unk3148 > 4) {
                        pattern = 0x115;
                    }
                    break;
                }
                if (m_inputX == -facing) {
                    Vf0();
                    CPlayer::Unk40f170();
                    pattern = 0x116;
                    if (unk3148 > 4) {
                        pattern = 0x116;
                    }
                    break;
                }
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x10f;
                if (m_inputY == 1) {
                    pattern = 0x118;
                }
                if (unk3148 == 9) {
                    pattern = 0x10c;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            unk313c++;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::StopMoving();
                Vf0();
                break;
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vx > 0.0 && frame > 2 && frame < 8) {
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            frame = 8;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.4;
                vy = -2.1;
                ay = 0.045;
            }
            if (frame == 8) {
                frame--;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                CPlayer::StopMoving();
                Vf0();
            }
        }
        break;
    case 0x10e:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            unk2c9 = 0x14;
        }
        if (frame > 8) {
            vy = vy + ay;
        }
        if (frame > 8 && vy + y > 0.0) {
            Vf0();
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                unk2c8 = 3;
                m_hitsLeft = 1;
            }
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3 || frame == 4 || frame == 5) {
                x = facing * 0x28 + x;
            }
            if (frame == 9) {
                vy = -1.0;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case 0x10f:
        CPlayer::StopMoving();
        if (frame == 5 && timer == 0) {
            unk2c8 = 5;
        }
        if (frame == 5 && timer == 0) {
            unk3148++;
        }
        if (unk3148 > 9) {
            unk3148 = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                Vf0();
                pattern = 7;
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            vx = 1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            unk2c9 = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x113;
                if (unk3148 > 4) {
                    pattern = 0x10d;
                }
                break;
            }
            if (m_pressB == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x112;
                break;
            }
            if (m_pressC == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x114;
                if (m_inputY == 1) {
                    pattern = 0x119;
                }
                break;
            }
            if (m_pressD == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x10f;
                if (m_inputY == 1) {
                    pattern = 0x118;
                }
                if (unk3148 == 9) {
                    pattern = 0x10c;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && unk313c < 3) {
                frame = frame - 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0x10c;
                CPlayer::StopMoving();
                Vf0();
                frame = 8;
                break;
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            vx = -1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            unk2c9 = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x113;
                if (unk3148 > 4) {
                    pattern = 0x10d;
                }
                break;
            }
            if (m_pressB == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x112;
                break;
            }
            if (m_pressC == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x114;
                if (m_inputY == 1) {
                    pattern = 0x119;
                }
                break;
            }
            if (m_pressD == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x10f;
                if (m_inputY == 1) {
                    pattern = 0x118;
                }
                if (unk3148 == 9) {
                    pattern = 0x10c;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && unk313c < 3) {
                frame = frame - 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0x10c;
                CPlayer::StopMoving();
                Vf0();
                frame = 8;
                break;
            }
        }
        break;
    case 0x112:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4 - (frame == 9) * unk3148 * 3) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                l50.type = 0x1ac;
                if (m_inputX == facing) {
                    l50.type = 0x1ad;
                }
                if (m_inputX == -facing) {
                    l50.type = 0x1ab;
                }
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x32);
                l50.scale = 0;
                l50.unk28 = 1;
                l50.layer = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c8 = 0;
                m_gauge = m_gauge + 0x2d;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x113:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vx > 0.0 && frame > 2 && frame < 8) {
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            frame = 8;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                m_gauge = m_gauge + 0x2d;
                vx = 1.4;
                vy = -2.1;
                ay = 0.045;
            }
            if (frame == 8) {
                frame--;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                CPlayer::StopMoving();
                Vf0();
            }
        }
        break;
    case 0x114:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            unk2c9 = 0x14;
        }
        if (frame > 8) {
            vy = vy + ay;
        }
        if (frame > 8 && vy + y > 0.0) {
            Vf0();
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4 || frame == 1 && timer == 0x27 - unk3148 * 3) {
            timer = 0;
            frame++;
            if (frame == 5) {
                unk2c8 = 3;
                m_hitsLeft = 1;
            }
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3 || frame == 4 || frame == 5) {
                x = facing * 0x28 + x;
            }
            if (frame == 9) {
                vy = -0.7;
                vx = 0.7;
                ay = 0.033;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case 0x115:
        if (frame == 0 && timer == 0) {
            vx = 1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            unk2c9 = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x113;
                if (unk3148 > 4) {
                    pattern = 0x10d;
                }
                break;
            }
            if (m_pressB == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x112;
                break;
            }
            if (m_pressC == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x114;
                if (m_inputY == 1) {
                    pattern = 0x119;
                }
                break;
            }
            if (m_pressD == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x10f;
                if (m_inputY == 1) {
                    pattern = 0x118;
                }
                if (unk3148 == 9) {
                    pattern = 0x10c;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && unk313c < 3) {
                frame = frame - 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0x10c;
                CPlayer::StopMoving();
                Vf0();
                frame = 8;
                break;
            }
        }
        break;
    case 0x116:
        if (frame == 0 && timer == 0) {
            vx = -1.4;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame > 3) {
            vx -= 0.08;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((frame == 1 || frame == 3) && timer == 0) {
            unk2c9 = 0x15;
        }
        if (frame < 4) {
            if (m_pressA == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x113;
                if (unk3148 > 4) {
                    pattern = 0x10d;
                }
                break;
            }
            if (m_pressB == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x112;
                break;
            }
            if (m_pressC == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x114;
                if (m_inputY == 1) {
                    pattern = 0x119;
                }
                break;
            }
            if (m_pressD == 1) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0x10f;
                if (m_inputY == 1) {
                    pattern = 0x118;
                }
                if (unk3148 == 9) {
                    pattern = 0x10c;
                    frame = 8;
                }
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && unk313c < 3) {
                frame = frame - 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0x10c;
                CPlayer::StopMoving();
                Vf0();
                frame = 8;
                break;
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 2) {
            unkf2 = 0xa;
        }
        if (frame == 4 && timer == 0) {
            l50.unk0 = 1;
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.layer = 0;
            l50.unk28 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
        }
        timer++;
        if (timer >= l4 || frame == 5 && timer == l4 - unk3148 * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x117:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.unk28 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4 - (frame == 4) * unk3148 * 3) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x118:
        CPlayer::StopMoving();
        if (frame == 0 && timer == 0) {
            unk2c8 = 4;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                Vf0();
                pattern = 0;
            }
        }
        break;
    case 0x119:
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            unk2c9 = 0x14;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame >= 2) {
            unkf2 = 0xa;
        }
        if (frame == 4 && timer == 0) {
            l50.unk0 = 1;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.layer = 0;
            l50.unk28 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
        }
        timer++;
        if (timer >= l4 || frame == 5 && timer == l4 - unk3148 * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 4 && timer == 0) {
            l50.unk0 = 1;
            l50.type = 0x198;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 0;
            l50.layer = 0;
            l50.unk28 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0;
        }
        timer++;
        if (timer >= l4 || frame == 5 && timer == l4 - unk3148 * 6) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 || frame == 7) {
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -0.5;
            }
            if (m_inputY == 1) {
                vy = 0.5;
            }
            if (m_inputX == facing) {
                vx = 0.5;
            }
            if (m_inputX == -facing) {
                vx = -0.5;
            }
        }
        if (frame > 7) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 7 && frame < 0xc) {
            CPlayer::StopMoving();
            y = 0.0;
            frame = 0xc;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                l50.unk0 = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x50);
                l50.unk18 = facing;
                l50.scale = 0;
                l50.layer = 1;
                Vf9(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)y;
                Vf9(&l50);
            }
            if (frame == 8) {
                if (unk3138 < 0xe) {
                    frame = frame - 2;
                    unk3138++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 || frame == 7) {
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -0.65;
            }
            if (m_inputY == 1) {
                vy = 0.65;
            }
            if (m_inputX == facing) {
                vx = 0.65;
            }
            if (m_inputX == -facing) {
                vx = -0.65;
            }
        }
        if (frame > 7) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 7 && frame < 0xc) {
            CPlayer::StopMoving();
            y = 0.0;
            frame = 0xc;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                l50.unk0 = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x50);
                l50.unk18 = facing;
                l50.scale = 0;
                l50.layer = 1;
                Vf9(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)y;
                Vf9(&l50);
            }
            if (frame == 8) {
                if (unk3138 < 0x14) {
                    frame = frame - 2;
                    unk3138++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame > 3) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 6 || frame == 7) {
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == -1) {
                vy = -0.8;
            }
            if (m_inputY == 1) {
                vy = 0.8;
            }
            if (m_inputX == facing) {
                vx = 0.8;
            }
            if (m_inputX == -facing) {
                vx = -0.8;
            }
        }
        if (frame > 7) {
            vy = vy + ay;
        }
        if (vy + y > 0.0 && frame > 7 && frame < 0xc) {
            CPlayer::StopMoving();
            y = 0.0;
            frame = 0xc;
            timer = 0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                l50.unk0 = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x50);
                l50.unk18 = facing;
                l50.scale = 0;
                l50.layer = 1;
                Vf9(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)y;
                Vf9(&l50);
            }
            if (frame == 8) {
                if (unk3138 < 0x14) {
                    frame = frame - 2;
                    unk3138++;
                } else {
                    ay = 0.015;
                }
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0x132:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 0x63;
        }
        if (frame > 0xe) {
            vx += 0.035;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 0xa && frame < 0xf) {
            CPlayer::Unk410a10(3, 0xa);
        }
        if ((char)CPlayer::Unk40ff70() != 0 && frame > 0xe && vx > 4.0) {
            vx = -2.7;
            vy = -3.5;
            ay = 0.035;
            pattern = 0x101;
            Vf0();
            unk2c9 = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x19b;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x19b;
            l50.x = (double)((int)x - facing * 0x32);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            break;
        }
        if (frame == 0xc && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0xf && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf) {
                if (unk3138 < 0xa) {
                    frame = frame - 4;
                    unk3138++;
                } else {
                    l50.type = 0x34;
                    l50.x = (double)(int)x;
                    l50.y = (double)((int)y - 0x19);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk2c = 0x16;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    vx = 0.5;
                    CPlayer::Unk410a10(0xf, 0xa);
                    l50.unk0 = 1;
                    l50.type = 0x1a1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.unk28 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                }
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
    }
}
