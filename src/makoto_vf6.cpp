// CMakoto::Vf6 (0x5e85f0-0x5f6d8f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMakoto's
// .rdata, which starts with its constructor's folder name (makoto.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMakoto::Vf6()
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
        unk158 = 0;
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
        unk158 = 0;
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
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.042;
            vy = -2.9;
            if (unk158 == 1) {
                vx = 0.4;
                unk158 = 0;
            }
        }
        if (frame > 2) {
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 5:
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.042;
            vy = -2.9;
            vx = 0.7;
            if (unk158 == 1) {
                vx = 1.1;
                unk158 = 0;
            }
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
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
    case 6:
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.042;
            vy = -2.9;
            vx = -0.7;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 2;
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
                Vf0();
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
                Vf0();
            }
        }
        break;
    case 0xe:
        ay = 0.042;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = 0.0;
            unk158 = 0;
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
        ay = 0.042;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = 0.7;
            unk158 = 0;
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
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            Vf0();
        }
        break;
    case 0x10:
        ay = 0.042;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = -0.7;
            unk158 = 0;
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
            l50.layer = 0;
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
        unk158 = 0;
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
        unk158 = 0;
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
                frame = frame - 2;
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
        unk158 = 0;
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
                frame = frame - 2;
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
            l50.y = (double)((int)y - 0x3c);
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
            l50.y = (double)((int)y - 0x3c);
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
            if (frame == 0x12) {
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
            m_attackResult = 0;
            Vf0();
            break;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            ay = 0.0;
        }
        vx = 2.2;
        unk158 = 1;
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 6;
                break;
            }
        }
        if (m_inputX == facing && unk313c >= 0x50 && frame < 4) {
            pattern = 0xb2;
            Vf0();
        }
        if (m_inputX != facing && unk3138 >= 0x3c && frame < 4) {
            pattern = 0xb2;
            Vf0();
        }
        break;
    case 0xa4:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = -2.2;
        }
        vx += 0.02;
        if (vx > 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                CPlayer::FaceOpponent();
                pattern = 0;
                Vf0();
                CPlayer::StopMoving();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 1.9;
            vy = 1.3;
            CPlayer::Unk4109d0(3);
            ax = -0.015;
            ay = -0.038;
            unk2c9 = 0x11;
        }
        vy = vy + ay;
        vx = vx + ax;
        if (vx < 0.5) {
            vx = 0.5;
        }
        if (vy < -1.5) {
            vy = -1.5;
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
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -1.9;
            vy = 1.3;
            CPlayer::Unk4109d0(3);
            ax = 0.015;
            ay = -0.038;
            unk2c9 = 0x11;
        }
        vy = vy + ay;
        vx = vx + ax;
        if (vx > -0.5) {
            vx = -0.5;
        }
        if (vy < -1.5) {
            vy = -1.5;
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
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa7:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
        if (frame == 0 && timer == 0) {
            unk2c9 = 0x12;
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
                pattern = 7;
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
        if (y + vy > 0.0 && frame < 0xa) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xa;
            unk2c9 = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                vx = -0.5;
                vy = -1.0;
                ay = 0.028;
            }
            if (frame == 0xa) {
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
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
            if (frame == 4) {
                unk2c8 = 0;
                l50.type = 0x19d;
                l50.x = (double)((int)x + facing * 0x22);
                l50.y = (double)((int)y - 0x1f);
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                Vf9(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 0xa && m_pressC == 1 && unk3138 < 2) {
            unk2c8 = 0;
            timer = 0;
            frame = 6;
            unk2c8 = 0;
            m_attackResult = 0;
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0xf;
            unk3138++;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x5a);
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_hitsLeft = 1;
                unk2c8 = 0;
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x5a);
                l50.y = (double)((int)y - 0x32);
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                Vf9(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
    case 0xce:
        if (frame < 2) {
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
        }
        if (vx > 0.0) {
            unk158 = 0;
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                vx = 1.9;
            }
            if (frame == 6 && unk3138 < 4) {
                frame = frame - 3;
                unk3138++;
                if (unk3138 > 2) {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= x8) {
                pattern = 3;
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            unk2c9 = 0x14;
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
        if (frame > 4 && m_pressC == 1 && unk3138 < 2) {
            timer = 0;
            frame = 3;
            unk3138++;
            m_attackResult = 0;
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
            if (frame == 4) {
                m_gauge = m_gauge + 0xf;
                unk2c9 = 0x14;
                m_hitsLeft = 1;
                unk2c8 = 0;
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x1b);
                l50.y = (double)((int)y - 0x1c);
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                Vf9(&l50);
            }
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xd2:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.6;
            vy = -1.4;
            ay = 0.036;
        }
        if (frame == 6 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 9 && frame > 3) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 9;
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
                pattern = 3;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xd3:
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
            if (frame == 5) {
                m_gauge = m_gauge + 0xf;
                unk2c9 = 0x14;
                m_hitsLeft = 1;
                unk2c8 = 0;
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x2d);
                l50.y = (double)((int)y - 0x3e);
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                Vf9(&l50);
            }
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xd4:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
            vx = vx / 2.0;
            ay = 0.07;
        }
        if (m_attackResult > 1) {
            pattern = 0xd5;
            Vf0();
            CPlayer::StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk2c = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 7;
            pattern = 0xd6;
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
            m_attackResult = 0;
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
            l50.scale = 2;
            l50.layer = 0;
            l50.unk2c = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                Vf0();
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
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x33);
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
    case 0xdd:
        if (frame == 1 && timer == 0) {
            (*m_opponent)->Vf0();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x32;
        }
        if (frame > 2) {
            vy = vy + ay;
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 9 && frame > 2 && vy + y > 0.0) {
            frame = 9;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                vx = 1.5;
                vy = -1.6;
                ay = 0.05;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 4) {
                unk2c9 = 0x15;
                m_hitsLeft = 1;
                m_gauge = m_gauge + 0x1e;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe6:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe7:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
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
                Vf0();
            }
        }
        break;
    case 0xe8:
        unk158 = 0;
        CPlayer::Unk4109d0(3);
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            unk2c9 = 0x14;
        }
        if (frame == 3) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                timer = 0;
                frame = 4;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 1.8;
                vy = -1.5;
                ay = 0.045;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xe9:
        unk158 = 0;
        CPlayer::Unk4109d0(3);
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xea:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xeb:
        unk158 = 0;
        CPlayer::Unk4109d0(3);
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.01;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            unk2c9 = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6 && unk3138 < 4) {
                frame = frame - 3;
                unk3138++;
                if (unk3138 > 2) {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xf8:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->Vf0();
            CPlayer::StopMoving();
            (*m_opponent)->unk128 = 1;
            frame = 0;
            timer = 0;
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x6e;
            (*m_opponent)->y = y;
            (*m_opponent)->x = facing * 0x13 + x;
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
                pattern = 0xd3;
                frame = 1;
            }
        }
        break;
    case 0xf9:
        unk13e = 0x1e;
        (*m_opponent)->unk13e = 0x1e;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = -2.5;
            vy = -4.5;
            ay = 0.045;
        }
        vy = vy + ay;
        if (frame < 8) {
            vx += 0.035;
            if (vx > 0.0) {
                vx = 0.0;
            }
            (*m_opponent)->y = y;
            (*m_opponent)->x = facing * 0x13 + x;
            if (vy + y > 0.0) {
                y = 0.0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
                timer = 0;
                frame = 8;
                l50.type = 0;
                l50.unk2c = 2;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->Vf0();
                (*m_opponent)->pattern = 0x62;
                break;
            }
        }
        if (frame == 8 && timer == 0) {
            unk14a = 0x3c;
            (*m_opponent)->unk14a = 0x3c;
            CPlayer::DealDamage(0x44c, 500.0);
        }
        if (frame == 9 && timer == 0) {
            vy = -1.5;
            vx = -1.3;
            ay = 0.035;
        }
        if (frame > 9 && y + vy > 0.0) {
            Vf0();
            CPlayer::StopMoving();
            y = 0.0;
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                (*m_opponent)->pattern = 0x79;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 3) {
                l50.type = 0x193;
                l50.x = (double)((int)x + facing * 0x17);
                l50.y = (double)((int)y - 0x4c);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c9 = 0x15;
                unk2c8 = 5;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 3) {
                l50.type = 0x194;
                l50.x = (double)((int)x + facing * 0x17);
                l50.y = (double)((int)y - 0x4c);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c9 = 0x15;
                unk2c8 = 5;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_gauge = m_gauge + 0x2d;
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
        if (frame == 3) {
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x4c);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c9 = 0x15;
            unk2c8 = 5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 3) {
                l50.type = 0x195;
                l50.x = (double)((int)x + facing * 0x17);
                l50.y = (double)((int)y - 0x4c);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c9 = 0x15;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x196;
                l50.x = (double)((int)x + facing * 0x11);
                l50.y = (double)((int)y - 0x1a);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk28 = 1;
                Vf9(&l50);
                unk2c9 = 0x15;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x197;
                l50.x = (double)((int)x + facing * 0x11);
                l50.y = (double)((int)y - 0x1a);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk28 = 1;
                Vf9(&l50);
                unk2c9 = 0x15;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_gauge = m_gauge + 0x2d;
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
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                l50.type = 0x198;
                l50.x = (double)((int)x + facing * 0x11);
                l50.y = (double)((int)y - 0x1a);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk28 = 1;
                Vf9(&l50);
                unk2c9 = 0x15;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 8 && frame > 1 && vy + y > 0.0) {
            frame = 8;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                vx = 1.5;
                vy = -1.5;
                ay = 0.05;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 3) {
                unk2c9 = 0x15;
                m_hitsLeft = 1;
                m_gauge = m_gauge + 0x1e;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 8 && frame > 1 && vy + y > 0.0) {
            frame = 8;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                vx = 1.5;
                vy = -1.8;
                ay = 0.05;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 3) {
                unk2c9 = 0x15;
                m_hitsLeft = 1;
                m_gauge = m_gauge + 0x1e;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 8 && frame > 1 && vy + y > 0.0) {
            frame = 8;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        if (frame < 0x13 && frame > 0xc && vy + y > 0.0) {
            frame = 0x13;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                vx = 0.9;
                vy = -1.0;
                ay = 0.05;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 3) {
                unk2c9 = 0x15;
                m_hitsLeft = 1;
                m_gauge = m_gauge + 0x1e;
            }
            if (frame == 0xc) {
                vx = 1.4;
                vy = -2.9;
                ay = 0.05;
                m_attackResult = 0;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 0xd) {
                unk2c9 = 0x15;
                m_hitsLeft = 1;
                m_gauge = m_gauge + 0x1e;
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
            CPlayer::StopMoving();
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x4e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x4e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            unk2c8 = 0;
            unk3148 = 1;
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
    case 0x104:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x19b;
            l50.x = (double)((int)x - facing * 0x24);
            l50.y = (double)((int)y - 0x4e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x - facing * 0x24);
            l50.y = (double)((int)y - 0x4e);
            l50.unk18 = -facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            unk2c8 = 0;
            unk3148 = 1;
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
    case 0x105:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 4 && timer == 0) {
            l50.type = 0x19c;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x4e);
            l50.unk0 = 1;
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x4e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            unk2c8 = 0;
            unk3148 = 1;
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
    case 0x106:
        if (frame == 0 && timer == 0) {
            vx *= 0.25;
            vy *= 0.25;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4) {
                m_gauge = m_gauge + 0x2d;
                l50.type = 0x196;
                l50.x = (double)((int)x + facing * 0xe);
                l50.y = (double)((int)y - 0x23);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk28 = 1;
                Vf9(&l50);
                unk2c9 = 0x15;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if (frame == 5 && timer == 0 && unk3138 == 0) {
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x4d);
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                unk14c = 0x78;
                m_gauge = m_gauge - 0x3e8;
                CPlayer::Unk410b10(0xb0, 3);
                l50.type = 0x44;
                l50.unk2c = 0x13;
                l50.x = (double)((int)x + facing * 0x2f);
                l50.y = (double)((int)y - 0x2b);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5 && unk14c > 0) {
                frame = frame - 3;
            }
            if (frame == 8 && unk3138 < 3) {
                frame = frame - 3;
                unk3138++;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if (frame == 5 && timer == 0 && unk3138 == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 0x4d);
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                unk14c = 0x78;
                m_gauge = m_gauge - 0x3e8;
                CPlayer::Unk410b10(0xb0, 3);
                l50.type = 0x44;
                l50.unk2c = 0x13;
                l50.x = (double)((int)x + facing * 0x2f);
                l50.y = (double)((int)y - 0x2b);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5 && unk14c > 0) {
                frame = frame - 3;
            }
            if (frame == 8 && unk3138 < 3) {
                frame = frame - 3;
                unk3138++;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if (frame == 5 && timer == 0 && unk3138 == 0) {
            l50.type = 0x1a4;
            l50.x = (double)((int)x + facing * 0x4d);
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                unk14c = 0x78;
                m_gauge = m_gauge - 0x3e8;
                CPlayer::Unk410b10(0xb0, 3);
                l50.type = 0x44;
                l50.unk2c = 0x13;
                l50.x = (double)((int)x + facing * 0x2f);
                l50.y = (double)((int)y - 0x2b);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5 && unk14c > 0) {
                frame = frame - 3;
            }
            if (frame == 8 && unk3138 < 3) {
                frame = frame - 3;
                unk3138++;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 3 && timer == 0) {
            vy = -2.4;
            vx = -0.4;
            ay = 0.029;
            m_hitsLeft = 0x63;
        }
        if (frame == 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame > 0xb) {
            (*m_opponent)->Unk410a80(0x32, 3);
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
        if (frame == 0xb && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 0xc && timer == 0) {
            vx = -0.2;
            vy = -0.8;
            ay = 0.015;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 3;
            l50.x = (double)(int)(facing * (WORD)CPlayer::Random(0, 0xb4) + x);
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.unk0 = 1;
            l50.type = 0x19f;
            l50.x = (double)(int)x;
            l50.y = 0.0;
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            Vf9(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1b);
            l50.y = (double)((int)y - 0x1c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x1a5;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x2b);
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x33);
            l50.layer = 0;
            Vf9(&l50);
            unk2c8 = 0;
        }
        if (frame == 0x12 && timer == 0) {
            l50.unk0 = 0;
            l50.type = 3;
            l50.x = (double)(int)(facing * (WORD)CPlayer::Random(0, 0xb4) + x);
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1b);
            l50.y = (double)((int)y - 0x1c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x1a5;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x2b);
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x33);
            l50.layer = 0;
            Vf9(&l50);
            unk2c8 = 0;
        }
        vy = vy + ay;
        if (frame < 0x14 && vy > 0.15) {
            vy = 0.15;
        }
        if (frame > 0xe && frame < 0x16 && vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x16;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x14 && unk3138 < 8) {
                unk3138++;
                frame = frame - 3;
            }
            if (frame == 0x16) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                Vf0();
            }
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 3 && timer == 0) {
            vy = -2.4;
            vx = -0.4;
            ay = 0.029;
            m_hitsLeft = 0x63;
        }
        if (frame == 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame > 0xb) {
            (*m_opponent)->Unk410a80(0x32, 3);
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
        if (frame == 0xb && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 0xc && timer == 0) {
            vx = -0.2;
            vy = -0.8;
            ay = 0.015;
        }
        if (frame == 0xe && timer == 0) {
            l50.unk0 = 0;
            l50.type = 3;
            l50.x = (double)(int)(facing * (WORD)CPlayer::Random(0, 0xf0) + x);
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.unk0 = 1;
            l50.type = 0x1a0;
            l50.x = (double)(int)x;
            l50.y = 0.0;
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            Vf9(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1b);
            l50.y = (double)((int)y - 0x1c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x1a5;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x2b);
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x33);
            l50.layer = 0;
            Vf9(&l50);
            unk2c8 = 0;
        }
        if (frame == 0x12 && timer == 0) {
            l50.unk0 = 0;
            l50.type = 3;
            l50.x = (double)(int)(facing * (WORD)CPlayer::Random(0, 0xf0) + x);
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1b);
            l50.y = (double)((int)y - 0x1c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x1a5;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x2b);
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x33);
            l50.layer = 0;
            Vf9(&l50);
            unk2c8 = 0;
        }
        vy = vy + ay;
        if (frame < 0x14 && vy > 0.15) {
            vy = 0.15;
        }
        if (frame > 0xe && frame < 0x16 && vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x16;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x14 && unk3138 < 0xf) {
                unk3138++;
                frame = frame - 3;
            }
            if (frame == 0x16) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                Vf0();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 3 && timer == 0) {
            vy = -2.4;
            vx = -0.4;
            ay = 0.029;
            m_hitsLeft = 0x63;
        }
        if (frame == 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame > 0xb) {
            (*m_opponent)->Unk410a80(0x32, 3);
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
        if (frame == 0xb && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0xa) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0xc && timer == 0) {
            vx = -0.2;
            vy = -0.8;
            ay = 0.015;
        }
        if (frame == 0xe && timer == 0) {
            l50.unk0 = 0;
            l50.type = 3;
            l50.x = (double)(int)(facing * (WORD)CPlayer::Random(0, 0x140) + x);
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.unk0 = 1;
            l50.type = 0x1a1;
            l50.x = (double)(int)x;
            l50.y = 0.0;
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            Vf9(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1b);
            l50.y = (double)((int)y - 0x1c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x1a5;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x2b);
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x33);
            l50.layer = 0;
            Vf9(&l50);
            unk2c8 = 0;
        }
        if (frame == 0x12 && timer == 0) {
            l50.unk0 = 0;
            l50.type = 3;
            l50.x = (double)(int)(facing * (WORD)CPlayer::Random(0, 0x140) + x);
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1b);
            l50.y = (double)((int)y - 0x1c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.type = 0x1a5;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x2b);
            l50.layer = 1;
            l50.scale = 0;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x33);
            l50.layer = 0;
            Vf9(&l50);
            unk2c8 = 0;
        }
        vy = vy + ay;
        if (frame < 0x14 && vy > 0.15) {
            vy = 0.15;
        }
        if (frame > 0xe && frame < 0x16 && vy + y > 0.0) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x16;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x14 && unk3138 < 0x19) {
                unk3138++;
                frame = frame - 3;
            }
            if (frame == 0x16) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                Vf0();
            }
        }
        break;
    case 0x132:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3138 == 0) {
                unk14c = 0x78;
                m_gauge = m_gauge - 0x3e8;
                CPlayer::Unk410b10(0xb0, 3);
                l50.type = 0x44;
                l50.unk2c = 0x13;
                l50.x = (double)((int)x + facing * 5);
                l50.y = (double)((int)y - 0x2b);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3138++;
                m_hitsLeft = 5;
            }
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1a7;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = -facing;
            Vf9(&l50);
        }
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 5) {
            vy += 0.01;
        }
        if (frame == 5 && y + vy > 0.0) {
            frame = 6;
            timer = 0;
            y = 0.0;
            vy = 0.0;
        }
        if (frame > 5) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 && unk313c < 9) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 5) {
                vx = 1.9;
                vy = -0.4;
                x = facing * 0x1e + x;
                unk2c8 = 4;
            }
            if (frame == 6) {
                frame--;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x133:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3138 == 0) {
                unk14c = 0x78;
                m_gauge = m_gauge - 0x7d0;
                CPlayer::Unk410b10(0xb0, 3);
                l50.type = 0x45;
                l50.unk2c = 5;
                l50.x = (double)((int)x + facing * 5);
                l50.y = (double)((int)y - 0x2b);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3138++;
                m_hitsLeft = 0xc;
            }
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1a7;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = -facing;
            Vf9(&l50);
        }
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 5) {
            vy += 0.01;
        }
        if (frame == 5 && y + vy > 0.0) {
            frame = 6;
            timer = 0;
            y = 0.0;
            vy = 0.0;
        }
        if (frame > 5) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 && unk313c < 9) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 5) {
                unk13c = 3;
                vx = 2.3;
                vy = -0.65;
                x = facing * 0x1e + x;
                unk2c8 = 4;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = -((facing == 1) - 1);
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 6) {
                frame--;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x134:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3138 == 0) {
                unk14c = 0x78;
                m_gauge = m_gauge - 0xbb8;
                CPlayer::Unk410b10(0xb0, 3);
                l50.type = 0x46;
                l50.unk2c = 0x40;
                l50.x = (double)((int)x + facing * 5);
                l50.y = (double)((int)y - 0x2b);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk3138++;
                m_hitsLeft = 0x13;
                unk2c9 = 0x25;
            }
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        m_game->Unk4080c0(0xf);
        if (frame == 5 && unk3140 < 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3140 = 0xc;
        }
        unk3140--;
        if (frame == 4 && timer == 0) {
            l50.type = 0x1a7;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = -facing;
            Vf9(&l50);
        }
        if (frame < 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 5) {
            vy += 0.01;
        }
        if (frame == 5 && y + vy > 0.0) {
            frame = 6;
            timer = 0;
            y = 0.0;
            vy = 0.0;
        }
        if (frame > 5) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 && unk313c < 9) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 5) {
                vx = 2.5;
                vy = -0.8;
                x = facing * 0x1e + x;
                unk2c8 = 4;
            }
            if (frame == 6) {
                frame--;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x135:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
            unk2c9 = 0x25;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 5);
            l50.y = (double)((int)y - 0x38);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3138++;
            m_hitsLeft = 0x13;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        m_game->Unk4080c0(0xf);
        vx = 0.0;
        vy = 0.0;
        ay = 0.0;
        (*m_opponent)->unkd0 = 0;
        unkd0 = 0;
        if (unk313c == 1 && frame == 5) {
            frame = 6;
            unk2c8 = 3;
            timer = 0;
            break;
        }
        if (unk313c == 2 && frame == 5) {
            Vf0();
            pattern = 0x136;
            break;
        }
        if (frame > 8 && frame < 0xd) {
            m_hp += 0x14;
        }
        if (m_hp > 0x2710) {
            m_hp = 0x2710;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                l50.type = 0x1a6;
                l50.x = (double)((int)x + facing * 6);
                l50.y = (double)((int)y - 0x50);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 6) {
                frame = frame - 1;
            }
            if (frame == 0xd && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x136:
        vx = 0.0;
        vy = 0.0;
        ay = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 && unk3138 < 8) {
                unk3138++;
                frame = frame - 2;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
    }
}
