// CKano::Vf6 (0x6429c0-0x653a1f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CKano's
// .rdata, which starts with its constructor's folder name (kano.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CKano::Vf6()
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
        vx = 0.6;
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
        vx = -0.6;
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
        if (frame == 2 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
            if (unk158 == 1) {
                vx = 0.3;
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
        if (frame == 2 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
    case 6:
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                CPlayer::FaceOpponent();
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
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            ay = 0.025;
            vy = -2.2;
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
        timer++;
        unk158 = 0;
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
            pattern = 0x60;
            Vf0();
        }
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
        if (frame == 4 && timer == 0) {
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
            if (frame == 0xf) {
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
        if (frame > 3) {
            vx = 1.5;
        }
        unk158 = 1;
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 3;
                break;
            }
        }
        if (m_inputX == facing && unk313c >= 0x50) {
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
        unk158 = 0;
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            CPlayer::StopMoving();
            vx = -3.1;
            vy = 0.0;
            ay = 0.0;
            unk3138 = 1;
            unk2c9 = 0x11;
        }
        if (frame > -1) {
            vx += 0.04;
        }
        if (vx >= 0.0 && frame > -1) {
            vx = 0.0;
            vy = 0.0;
            pattern = 0;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 1.1;
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
                frame = 0;
            }
        }
        if (m_inputX == facing && unk313c >= 0x78) {
            pattern = 9;
            Vf0();
            vx = 0.9;
            ay = 0.02;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            vx = 0.9;
            ay = 0.02;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -1.1;
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
                frame = 0;
            }
        }
        if (m_inputX == -facing && unk313c >= 0x78) {
            pattern = 9;
            Vf0();
            vx = -0.9;
            ay = 0.02;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x30) {
            pattern = 9;
            Vf0();
            vx = -0.9;
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
            if (ay == 0.0) {
                ay = 0.035;
            }
            vx = 0.0;
            vy = 0.0;
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
                if (ay == 0.0) {
                    ay = 0.02;
                }
                Vf0();
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
        if (y + vy > 0.0 && frame < 9) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 9;
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
            if (frame == 9) {
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
            unk2c9 = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult > 0 && m_attackResult != 6) {
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
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
        if (frame == 4 && timer == 0) {
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
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
            Vf0();
            break;
        }
        if (frame == 4 && timer == 0) {
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
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
            unk2c9 = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
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
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
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
        if (frame == 1 && timer == 0) {
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
            if (frame < 3) {
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
            unk2c9 = 0x14;
            m_hitsLeft = 2;
        }
        if (frame == 8 && timer == 0) {
            unk2c9 = 0x14;
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
            if (frame == 4 || frame == 9) {
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
            m_hitsLeft = 5;
        }
        if (frame == 7 && timer == 0) {
            unk2c9 = 0x14;
        }
        if (frame == 0xa && timer == 0) {
            unk2c9 = 0x14;
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
            if (frame == 7 || frame == 9 || frame == 0xb || frame == 0xd) {
                m_attackResult = 0;
            }
            if (frame == 0xe && unk3138 < 1) {
                unk3138++;
                frame = frame - 7;
            }
            if (frame >= x8) {
                pattern = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x199;
            l50.x = (double)((int)x + facing * 0x96);
            l50.y = -40.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3138++;
            unk2c8 = 2;
            m_gauge = m_gauge - 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 8) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xd3:
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
            pattern = 0xd;
            Vf0();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 1;
            }
        }
        break;
    case 0xd4:
        if (frame == 0) {
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
        if (frame == 1 && timer == 0) {
            vx = 2.6;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        if (frame > 0) {
            vx -= 0.03;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 4 && unk3138 < 3) {
                unk3138++;
                frame = frame - 2;
            }
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
    case 0xd5:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0 && frame < 5) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 5;
            break;
        }
        timer++;
        if (timer >= l4) {
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
            if (frame >= x8) {
                Vf0();
                pattern = 7;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xd6:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0 && frame < 5) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 5;
            break;
        }
        timer++;
        if (timer >= l4) {
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
            if (frame >= x8) {
                Vf0();
                pattern = 7;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xd7:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0 && frame < 5) {
            y = 0.0;
            CPlayer::StopMoving();
            timer = 0;
            frame = 5;
            break;
        }
        timer++;
        if (timer >= l4) {
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
            if (frame >= x8) {
                Vf0();
                pattern = 7;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xd9:
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
        if (frame == 4 && timer == 0) {
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            Vf0();
            (*m_opponent)->Vf0();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.y = -52.0;
            l50.x = (double)(int)(facing * 0x23 + x);
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
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                Vf0();
            }
        }
        break;
    case 0xdd:
        if (frame == 2 && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x4a);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.unk2c = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x3e8, 750.0);
            (*m_opponent)->Vf0();
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -2.0;
            (*m_opponent)->unkc8 = -1.5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xe6:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0xe7:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult == 3) {
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 4 && timer == 0) {
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult == 3) {
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 1 && timer == 0) {
            unk2c9 = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
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
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                Vf0();
            }
        }
        break;
    case 0xeb:
        CPlayer::Unk4109d0(3);
        unk158 = 0;
        vx -= 0.01;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.2;
        }
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x15;
            m_hitsLeft = 6;
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
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x3e);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->y = y - 62.0;
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
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
        if (frame < 5) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 5) {
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
        if (frame == 2) {
            (*m_opponent)->y = y - 47.0;
            (*m_opponent)->x = facing * 0x1c + x;
            (*m_opponent)->pattern = 0x65;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 38.0;
            (*m_opponent)->x = facing * 0x14 + x;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->facing = facing;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 62.0;
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->pattern = 0x64;
            (*m_opponent)->facing = facing;
        }
        if (frame == 5 && timer == 0) {
            (*m_opponent)->y = y - 72.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->facing = facing;
            CPlayer::DealDamage(0x4b0, 500.0);
            (*m_opponent)->Vf0();
            (*m_opponent)->unkc0 = -1.0;
            (*m_opponent)->unkc8 = -2.3;
        }
        if (frame == 0xc && timer == 0) {
            ay = 0.035;
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
    case 0xfa:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
            unk3138++;
            if (unk3150 > 0x2710) {
                unk3150 = 0x2710;
            }
        }
        if (frame > 2 && frame < 7 && m_pressD == 1 || unk3150 >= 0x2710 && frame < 7) {
            timer = 0;
            frame = 7;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (0) {}
            if (0) {}
            if (frame == 7) {
                frame = frame - 4;
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
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_hitsLeft = 1;
                if (unk120 == 0) {
                    unk118 -= 500.0;
                } else {
                    unk118 -= 250.0;
                }
                unk3150 = 0x2710;
                l50.type = 0x198;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                l50.type = 0x197;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 0;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c8 = 1;
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
            unk2c8 = 0;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x1d4c;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xf && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && unk3138 < 1) {
                l50.type = 0x1bb;
                l50.x = (double)((int)x + (facing * 0x96 + m_inputX * 0x46));
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c8 = 3;
                unk3170++;
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
            unk2c8 = 0;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x1388;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xf && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && unk3138 < 1) {
                l50.type = 0x1bc;
                l50.x = (double)((int)x + (facing * 0x96 + m_inputX * 0x46));
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c8 = 3;
                unk3170++;
                m_gauge = m_gauge - 0x14;
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
            unk2c8 = 0;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x9c4;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xf && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && unk3138 < 1) {
                l50.type = 0x1bd;
                l50.x = (double)((int)x + (facing * 0x96 + m_inputX * 0x46));
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                Vf9(&l50);
                unk2c8 = 3;
                unk3170++;
                m_gauge = m_gauge - 0x32;
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
            unk2c8 = 0;
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x1d4c;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0x10 && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x11 && unk3138 < 1) {
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x2d);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk0 = 1;
                Vf9(&l50);
                unk2c8 = 5;
                unk316c++;
            }
            if (frame == 0x13 && unk3138 < 1) {
                frame = frame - 3;
                unk3138++;
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
            unk2c8 = 0;
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x1388;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0x10 && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x11) {
                if (unk3138 == 0) {
                    l50.type = 0x191;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x2d);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    unk2c8 = 5;
                    unk316c++;
                    m_gauge = m_gauge - 7;
                }
                if (unk3138 == 1) {
                    l50.type = 0x191;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    l50.unk0 = 1;
                    Vf9(&l50);
                    unk316c++;
                    m_gauge = m_gauge - 7;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x46);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    l50.unk0 = 1;
                    Vf9(&l50);
                    unk2c8 = 5;
                    unk316c++;
                    m_gauge = m_gauge - 7;
                }
            }
            if (frame == 0x13 && unk3138 < 2) {
                frame = frame - 3;
                unk3138++;
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
            unk2c8 = 0;
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x9c4;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0x10 && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x11) {
                if (unk3138 == 0) {
                    l50.type = 0x191;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x2d);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    l50.unk0 = 1;
                    Vf9(&l50);
                    unk2c8 = 5;
                    unk316c++;
                    m_gauge = m_gauge - 0xa;
                }
                if (unk3138 == 1) {
                    l50.type = 0x191;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    unk316c++;
                    m_gauge = m_gauge - 0xa;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x46);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    l50.unk0 = 1;
                    Vf9(&l50);
                    unk2c8 = 5;
                    unk316c++;
                    m_gauge = m_gauge - 0xa;
                }
                if (unk3138 == 2) {
                    l50.type = 0x191;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y + 5);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    l50.unk0 = 1;
                    Vf9(&l50);
                    unk316c++;
                    m_gauge = m_gauge - 0xa;
                    l50.x = (double)((int)x + facing * 0x26);
                    l50.y = (double)((int)y - 0x5f);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    l50.unk0 = 1;
                    Vf9(&l50);
                    unk2c8 = 5;
                    unk316c++;
                    m_gauge = m_gauge - 0xa;
                }
            }
            if (frame == 0x13 && unk3138 < 3) {
                frame = frame - 3;
                unk3138++;
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
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x1d4c;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xb && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && timer == 0) {
                l50.type = 0x1b8;
                l50.x = x;
                l50.y = -80.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk0 = 1;
                Vf9(&l50);
                unk3168++;
                unk2c8 = 4;
                unk313c = 0x15;
                unk3138++;
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
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x1388;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xb && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && timer == 0) {
                l50.type = 0x1b9;
                l50.x = x;
                l50.y = -80.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk0 = 1;
                Vf9(&l50);
                unk2c8 = 4;
                unk3168++;
                unk313c = 0x15;
                unk3138++;
                m_gauge = m_gauge - 0x14;
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
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x4b;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0x9c4;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame > 0xb && m_command == 0xd && (unk118 >= 500.0 || unk120 > 0)) {
            Vf0();
            CPlayer::StopMoving();
            pattern = 0xfb;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && timer == 0) {
                l50.type = 0x1ba;
                l50.x = x;
                l50.y = -80.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                l50.unk0 = 1;
                Vf9(&l50);
                unk3168++;
                unk2c8 = 4;
                unk313c = 0x15;
                unk3138++;
                m_gauge = m_gauge - 0x32;
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
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 6 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 6) {
            unk3150 += 0x12c;
        }
        if (frame > 2 && frame < 6 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 0xf) {
            unk313c--;
        }
        if (frame == 0xc && unk3138 < 1) {
            l50.type = 0x199;
            l50.x = (double)((int)x + facing * 0x6e);
            l50.y = -40.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3138++;
            unk2c8 = 2;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 6) {
                frame = frame - 3;
            }
            if (frame == 0x10 && unk3138 < 2) {
                frame = frame - 3;
                unk3138++;
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
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 6 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 6) {
            unk3150 += 0x12c;
        }
        if (frame > 2 && frame < 6 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 0xf) {
            unk313c--;
        }
        if (frame == 0xc && unk3138 < 1) {
            l50.type = 0x199;
            l50.x = (double)((int)x + facing * 0xa0);
            l50.y = -40.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk3138++;
            unk2c8 = 2;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 6) {
                frame = frame - 3;
            }
            if (frame == 0x10 && unk3138 < 2) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x109:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk3138 = 2;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x64);
            l50.y = (double)((int)y - 0x1e0);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = (double)((int)y - 0x208);
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x82);
            l50.y = (double)((int)y - 0x212);
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk3138 = 2;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0xb4);
            l50.y = (double)((int)y - 0x1e0);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0xa0);
            l50.y = (double)((int)y - 0x208);
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0xd2);
            l50.y = (double)((int)y - 0x212);
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x10b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk3138 = 2;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x104);
            l50.y = (double)((int)y - 0x1e0);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0xf0);
            l50.y = (double)((int)y - 0x208);
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x122);
            l50.y = (double)((int)y - 0x212);
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                Vf0();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x10c:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            unk3138 = 3;
        }
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x - facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk3138 < 3) {
                unk3138++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 9;
                ay = 0.035;
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            unk3138 = 3;
        }
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x - facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk3138 < 3) {
                unk3138++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 9;
                ay = 0.035;
            }
        }
        break;
    case 0x10e:
        if (frame == 0 && timer == 0) {
            vx *= 0.5;
            vy *= 0.5;
            ay = 0.01;
            m_gauge = m_gauge + 0x2d;
            unk3138 = 3;
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
        vy = vy + ay;
        if (frame == 2 && timer == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)x - facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        if (frame > 1) {
            unk313c++;
        }
        if (unk313c == 0x10) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        if (unk313c == 0x20) {
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0xa);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        if (unk313c == 0x30) {
            l50.type = 0x197;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0xa);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk3138 < 3) {
                unk3138++;
                frame = frame - 4;
                break;
            }
            if (frame >= x8) {
                Vf0();
                pattern = 9;
                ay = 0.035;
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 0xd && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x64);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x64;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0x10 && timer == 0) {
            unk2c8 = 0x1d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x10 && timer == 0 && unk3138 < 1) {
                l50.type = 0x1c7;
                l50.x = (double)((int)x + facing * 0x4b);
                l50.y = 0.0;
                if (unk3138 == 1) {
                    l50.x = facing * 0x1e + x;
                }
                if (unk3138 == 2) {
                    l50.x = facing * 0x78 + x;
                }
                if (unk3138 == 3) {
                    l50.x = facing * 0x50 + x;
                }
                if (unk3138 == 4) {
                    l50.x = facing * 0x91 + x;
                }
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                Vf9(&l50);
            }
            if (frame == 0x12 && unk3138 < 3) {
                frame--;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 0xd && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x64);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x64;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0xf && timer == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0x13 && unk3138 < 6) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x64;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0xa && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 0xa4);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame == 0xd && timer == 0) {
            l50.type = 0x1c1;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk30 = 1;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 4;
            }
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
            unk2c8 = 0;
        }
        if (frame == 0xd && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x64);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x64;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x19c;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x6e);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 9 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x40);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x96;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0xd && timer == 0) {
            l50.type = 0x1ad;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)((int)y + 0xa);
            l50.unk0 = 1;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x4b);
            l50.y = (double)((int)y - 0xa);
            l50.unk0 = 1;
            Vf9(&l50);
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.unk0 = 1;
            l50.type = 0x19d;
            Vf9(&l50);
            CPlayer::Unk410a10(4, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x64;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 9 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame == 0xd && timer == 0) {
            l50.type = 0x1c2;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x37);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            Vf9(&l50);
            unk315c++;
            unk3160 = 0x258;
            unk3164 = facing;
        }
        if (frame > 0xd) {
            m_game->Unk4080c0(0xf);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame == 0xc && unk3140 < 8) {
                frame = frame - 2;
                unk3140++;
            }
            if (frame == 0x11 && unk313c < 5) {
                frame = frame - 4;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x132:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
        }
        if (frame == 6 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 0xd) {
            unk3150 += 0xc8;
            if (unk3150 > 0x2710) {
                unk3150 = 0x2710;
            }
        }
        if (frame > 0xf && frame < 0x13) {
            unk313c--;
        }
        if (unk313c <= 0 && unk3140 < 3 && frame > 0xf) {
            unk3150 = 0;
            unk2c8 = 0xe;
            l50.type = 0x19e;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk313c = 0x1e;
            unk3140++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                unk13c = 0xf;
            }
            if (frame == 0x13 && unk3138 < 6) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x133:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
        }
        if (frame == 6 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 0xd) {
            unk3150 += 0xc8;
            if (unk3150 > 0x2710) {
                unk3150 = 0x2710;
            }
        }
        if (frame > 0xf && frame < 0x13) {
            unk313c--;
        }
        if (unk313c <= 0 && unk3140 < 4 && frame > 0xf) {
            unk3150 = 0;
            unk2c8 = 0xe;
            l50.type = 0x19f;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk313c = 0x1e;
            unk3140++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                unk13c = 0x2d;
            }
            if (frame == 0x13 && unk3138 < 6) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x134:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 5;
            CPlayer::StopMoving();
            unk2c9 = 0x25;
        }
        if (frame == 6 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 0xd) {
            unk3150 += 0xc8;
            if (unk3150 > 0x2710) {
                unk3150 = 0x2710;
            }
        }
        if (frame > 0xf && frame < 0x13) {
            unk313c--;
        }
        if (unk313c <= 0 && unk3140 < 5 && frame > 0xf) {
            unk3150 = 0;
            unk2c8 = 0xe;
            l50.type = 0x1a0;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk313c = 0x1e;
            unk3140++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0x10) {
                unk13c = 0xb4;
            }
            if (frame == 0x13 && unk3138 < 6) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 9 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x40);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x96;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0xc && timer == 0) {
            l50.type = 0x1ae;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0x12;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 0xd && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x40);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x96;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0x11 && timer == 0) {
            l50.type = 0x1a7;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0x11;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        if (frame == 9 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x40);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x96;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 8;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 0xc && timer == 0) {
            l50.type = 0x1ac;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            unk2c8 = 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 7 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame > 2 && frame < 7) {
            unk3150 += 0x64;
        }
        if (frame > 2 && frame < 7 && unk3150 >= 0x2710) {
            unk3150 = 0;
            frame = 7;
            timer = 0;
            break;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk18 = facing;
            Vf9(&l50);
        }
        if (frame == 8 && timer == 0) {
            unk14c = 0x78;
            m_hitsLeft = 1;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 0xa4);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame == 0xd && timer == 0) {
            l50.type = 0x1b2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            Vf9(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13b:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk2c8 = 0;
            unk14c = 0x78;
            m_hitsLeft = 1;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 7 && m_attackResult == 3) {
            frame = 0;
            pattern = 0x13c;
            (*m_opponent)->StopMoving();
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->pattern = 0x6b;
            break;
        }
        timer++;
        if (timer >= l4) {
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
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
        break;
    case 0x13c:
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 0 && timer == 0) {
            unk2c8 = 0x1b;
        }
        if (frame > 0x11 && (*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->x = facing * 0x37 + x;
                (*m_opponent)->y = -61.0;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->x = facing * 0x2e + x;
                (*m_opponent)->y = -74.0;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->x = facing * 0x21 + x;
                (*m_opponent)->y = -86.0;
            }
            if (frame == 7) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->x = (facing << 5) + x;
                (*m_opponent)->y = -87.0;
                l50.type = 0x1c8;
                l50.x = 0.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = 1;
                l50.screen = 1;
                l50.unk30 = 1;
                Vf9(&l50);
            }
            if (frame == 8) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = -87.0;
            }
            if (frame == 0xb && unk3138 == 0) {
                frame = frame - 3;
            }
            if (frame == 0x11) {
                (*m_opponent)->unk14a = 0;
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->y = -20.0;
                (*m_opponent)->ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 0;
                Vf0();
            }
        }
    }
}
