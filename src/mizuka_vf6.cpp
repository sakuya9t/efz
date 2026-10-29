// CMizuka::UpdatePattern (0x4e7ec0-0x4f82ff), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMizuka's
// .rdata, which starts with its constructor's folder name (mizuka.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMizuka::UpdatePattern()
{
    WORD x8;
    WORD l4;

    if (unk14a > 0 || (*m_opponent)->unk14c > 0) {
        return;
    }
    EffectDesc l50;
    l4 = (short)anims[pattern].frames[frame].duration;
    x8 = anims[pattern].frameCount;
    InitEffectDesc((EffectDesc*)&l50);
    switch (pattern) {
    default:
        vx = 0.0;
        vy = 0.0;
        unk58 = 0;
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
        unk58 = 0;
        vx = 0.8;
        vy = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 2;
            }
        }
        break;
    case 2:
        unk158 = 0;
        unk58 = 0;
        vx = -0.8;
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
        unk58 = 0;
        unk158 = 0;
        FaceOpponent();
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
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.043;
            vy = -3.0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 5:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.043;
            vy = -3.0;
            vx = 1.0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 6:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.043;
            vy = -3.0;
            vx = -1.0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 7:
        unk58 = 0;
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        FaceOpponent();
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
        unk58 = 0;
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        FaceOpponent();
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
        unk58 = 0;
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
        unk58 = 0;
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        FaceOpponent();
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
    case 0xe:
        ay = 0.043;
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xf:
        ay = 0.043;
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 1.0;
            unk158 = 0;
        }
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
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x10:
        ay = 0.043;
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = -1.0;
            unk158 = 0;
        }
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
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)Unk40ff70() != 0) {
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)Unk40ff70() != 0) {
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)Unk40ff70() != 0) {
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame > 0 && (char)Unk40ff70() != 0) {
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = unkc0;
        vy = unkc8;
        if (vx * vx < vy * vy && frame == 0) {
            frame = 1;
        }
        timer++;
        if ((char)Unk40ff70() != 0) {
            pattern = 0x46;
            StartPattern();
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                frame = 0;
            }
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = unkc0;
        vy = unkc8;
        if (vx * vx < vy * vy && frame == 0) {
            frame = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                frame = 0;
            }
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
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
        unk58 = 0;
        if (unk120 != 0) {
            unk118 -= 0.8;
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x1f3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.facing = facing;
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
        unk58 = 0;
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
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
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
                FaceOpponent();
            }
        }
        break;
    case 0x54:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
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
                FaceOpponent();
            }
        }
        break;
    case 0x55:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
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
                FaceOpponent();
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
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            if (unk3144 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
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
            l50.facing = 1;
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
            if (frame == x8) {
                FaceOpponent();
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
        unk58 = 0;
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
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
        unk58 = 0;
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
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
        unk58 = 0;
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
            pattern = 0x60;
            StartPattern();
            unk158 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == x8) {
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0x60;
                StartPattern();
            }
        }
        break;
    case 0x96:
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
                FaceOpponent();
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
                FaceOpponent();
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
                FaceOpponent();
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
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x9a:
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
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x9b:
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
                FaceOpponent();
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
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            if (unk3458 > 0) {
                pattern = 0xb3;
            }
            StartPattern();
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
                pattern = 9;
                StartPattern();
            }
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            if (unk3458 > 0) {
                pattern = 0xb3;
            }
            StartPattern();
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 9) {
            unk313c++;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.5;
        }
        if (frame == 5 && timer == 0) {
            unk58 = 1;
        }
        if (frame == 6 && timer == 0) {
            unk58 = 3;
        }
        unk158 = 1;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 8;
                break;
            }
        }
        if (m_inputX == facing && unk313c >= 0x2a) {
            pattern = 0xb2;
            unk58 = 1;
            StartPattern();
        }
        if (m_inputX != facing && unk313c >= 0x18) {
            pattern = 0xb2;
            unk58 = 1;
            StartPattern();
        }
        break;
    case 0xa4:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        unk158 = 0;
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -2.5;
            vy = -1.3;
        }
        vy += 0.045;
        if (vy + y > 0.0 && frame < 0xc) {
            StopMoving();
            timer = 0;
            frame = 0xc;
            y = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                unk58 = 1;
            }
            if (frame == 5) {
                unk58 = 3;
            }
            if (frame == 7) {
                unk58 = 1;
            }
            if (frame == 8) {
                unk58 = 0;
            }
            if (frame == 0xc) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 7;
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 2.0;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            m_playSound = 0x11;
        }
        if (unk3458 > 0) {
            unk3458--;
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
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (unk3458 > 0) {
                pattern = 0xb3;
                frame = 7;
            }
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -2.0;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 0x11;
        }
        if (unk3458 > 0) {
            unk3458--;
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
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (unk3458 > 0) {
                pattern = 0xb3;
                frame = 7;
            }
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa7:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            if (unk120 == 1) {
                m_proration = 5.0 * unk118 + m_proration;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            FillBackground(0xb0, 3);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xa8:
        unk58 = 0;
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
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa9:
        unk58 = 0;
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
                FaceOpponent();
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xaa:
        unk58 = 0;
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
            StopMoving();
            y = 0.0;
            unk3458 = 0;
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
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
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
                m_proration = 5.0 * unk118 + m_proration;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            FillBackground(0xb0, 3);
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
                pattern = 9;
                vx = unk3138 * 0.01;
                vy = unk313c * 0.01;
                ay = 0.035;
                StartPattern();
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case 0xb2:
        vx -= 0.03;
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
            if (frame == 1) {
                unk58 = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                break;
            }
        }
        break;
    case 0xb3:
        unk159 = 0;
        if ((*m_opponent)->m_hp <= 0) {
            unk3458 = 0;
        }
        if (frame == 0 && timer == 0) {
            unk15a = 1;
            unk3458 = 0x3e8;
            vy = -2.5;
            vx = 0.0;
        }
        if (frame < 7) {
            vy += 0.035;
            if (vy > 0.0) {
                vy = 0.0;
            }
        }
        FaceOpponent();
        if (frame > 6) {
            unk3458--;
            if (unk3458 < 0) {
                ay = 0.035;
                StartPattern();
                pattern = 9;
                break;
            }
            vx = 0.0;
            vy = 0.0;
            if (m_inputY == 1) {
                vy = 1.0;
            }
            if (m_inputY == -1) {
                vy = -1.0;
            }
            if (m_inputX == facing) {
                StartPattern();
                pattern = 0xb4;
                break;
            }
            if (m_inputX == -facing) {
                StartPattern();
                pattern = 0xb5;
                break;
            }
            if (m_pressD == 1) {
                unk3458 = 0;
            }
        }
        unk58 = 0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case 0xb4:
        unk159 = 0;
        if ((*m_opponent)->m_hp <= 0) {
            unk3458 = 0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.5;
        }
        unk58 = 0;
        unk3458--;
        if (unk3458 < 0) {
            ay = 0.035;
            StartPattern();
            pattern = 9;
            break;
        }
        if (m_inputY == 1) {
            vy = 1.0;
        }
        if (m_inputY == 0) {
            vy = 0.0;
        }
        if (m_inputY == -1) {
            vy = -1.0;
        }
        if (m_inputX == 0) {
            StartPattern();
            frame = 7;
            pattern = 0xb3;
            break;
        }
        if (m_inputX == -facing) {
            StartPattern();
            pattern = 0xb5;
            break;
        }
        if (m_pressD == 1) {
            unk3458 = 0;
        }
        if (unk3458 < 0) {
            ay = 0.035;
            StartPattern();
            pattern = 9;
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
    case 0xb5:
        unk159 = 0;
        if ((*m_opponent)->m_hp <= 0) {
            unk3458 = 0;
        }
        if (frame == 0 && timer == 0) {
            vx = -1.5;
        }
        unk58 = 0;
        unk3458--;
        if (unk3458 < 0) {
            ay = 0.035;
            StartPattern();
            pattern = 9;
            break;
        }
        if (m_inputY == 1) {
            vy = 1.0;
        }
        if (m_inputY == -1) {
            vy = -1.0;
        }
        if (m_inputY == 0) {
            vy = 0.0;
        }
        if (m_inputX == 0) {
            StartPattern();
            frame = 7;
            pattern = 0xb3;
            break;
        }
        if (m_inputX == facing) {
            StartPattern();
            pattern = 0xb4;
            break;
        }
        if (m_pressD == 1) {
            unk3458 = 0;
        }
        if (unk3458 < 0) {
            ay = 0.035;
            StartPattern();
            pattern = 9;
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
    case 0xc8:
        unk58 = 0;
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
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                l50.type = 0x1b9;
                l50.x = (double)((int)x - facing * 0x28);
                l50.y = (double)((int)y - 0x21);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xc9:
        unk58 = 0;
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
            l50.type = 0x190;
            l50.x = (double)((int)x - facing * 0x15);
            l50.y = (double)((int)y - 0x1f);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xca:
        unk58 = 0;
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
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            l50.type = 0x191;
            l50.x = (double)((int)x - facing * 0x24);
            l50.y = (double)((int)y - 0x35);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcb:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playVoice = 0xa;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcc:
        unk58 = 0;
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
            l50.type = 0x1ba;
            l50.x = (double)((int)x - facing * 0x28);
            l50.y = (double)((int)y - 0xa);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcd:
        unk58 = 0;
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
            l50.type = 0x192;
            l50.x = (double)((int)x - facing * 0x1a);
            l50.y = (double)((int)y - 0x10);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xce:
        unk58 = 0;
        if (unk158 == 0 && frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (vx > 0.0 && unk158 == 1 && frame < 3) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0 && unk3138 == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            vx = 3.5;
            unk3138++;
        }
        if (vx > 0.0) {
            vx -= 0.036;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && vx > 0.6) {
                frame = 2;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcf:
        unk58 = 0;
        if (unk3458 == 0) {
            vy = vy + ay;
        }
        if (unk3458 > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && unk15a == 0 && unk15c < 3) {
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
            l50.type = 0x1bb;
            l50.x = (double)((int)x - facing * 7);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            unk3458 = 0;
            StartPattern();
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
                StartPattern();
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case 0xd0:
        unk58 = 0;
        if (unk3458 == 0) {
            vy = vy + ay;
        }
        if (unk3458 > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && unk15a == 0 && unk15c < 3) {
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
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = 2;
            l50.type = 0x194;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x48);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            unk3458 = 0;
            StartPattern();
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
                StartPattern();
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case 0xd1:
        unk58 = 0;
        if (unk3458 == 0) {
            vy = vy + ay;
        }
        if (unk3458 > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2 && unk15a == 0 && unk15c < 3) {
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 3;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            unk3458 = 0;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                l50.type = 0x195;
                l50.x = (double)((int)x + facing * 4);
                l50.y = (double)((int)y + 5);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame == 8 && unk3138 < 2) {
                frame = frame - 3;
                unk3138++;
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case 0xd2:
        unk58 = 0;
        if (unk3458 == 0) {
            vy = vy + ay;
        }
        if (unk3458 > 0) {
            if (vx > 0.1) {
                vx -= 0.025;
            }
            if (vx < -0.1) {
                vx += 0.025;
            }
            if (vx < 0.1 && vx > -0.1) {
                vx = 0.0;
            }
            if (vy > 0.1) {
                vy -= 0.025;
            }
            if (vy < -0.1) {
                vy += 0.025;
            }
            if (vy < 0.1 && vy > -0.1) {
                vy = 0.0;
            }
        }
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
            StartPattern();
            break;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xd;
            unk3458 = 0;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                l50.type = 0x1cc;
                l50.x = (double)((int)x + facing * 0x37);
                l50.y = (double)((int)y - 0x2c);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case 0xd3:
        if (m_inputY == -1 && frame > 0 && m_attackResult >= 2) {
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
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
            StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk2c = 7;
            m_game->CreateEffect((EffectDesc*)&l50);
            pattern = 0xd6;
            StartPattern();
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
                StartPattern();
            }
        }
        break;
    case 0xd6:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            ShakeScreen(3, 0);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        unk58 = 0;
        unk158 = 0;
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            StartPattern();
            StopMoving();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xdd:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->StopMoving();
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -2.5;
            (*m_opponent)->pattern = 0x3b;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1c8;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x50);
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.unk28 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c9;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.unk28 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1ca;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x50);
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.unk28 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 3) {
            FaceOpponent();
        }
        if ((*m_opponent)->pattern == 0x40 && frame == 3) {
            timer = 0;
            frame++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xe6:
        StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (unk58 == 3 || unk58 == 1) {
            unk13c = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 1) {
                l50.type = 0x1b9;
                l50.x = (double)((int)x - facing * 0x28);
                l50.y = (double)((int)y - 0x21);
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk58 == 1) {
                unk58 = 0;
            }
            if (unk58 == 3) {
                unk58 = 1;
            }
            if (frame >= x8) {
                unk58 = 0;
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe7:
        StartAfterimages(3);
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x190;
            l50.x = (double)((int)x - facing * 0x15);
            l50.y = (double)((int)y - 0x1f);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (unk58 == 3 || unk58 == 1) {
            unk13c = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (unk58 == 1) {
                unk58 = 0;
            }
            if (unk58 == 3) {
                unk58 = 1;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe8:
        StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 2.0;
            vy = 0.0;
        }
        if (frame == 5 && timer == 0) {
            l50.type = 3;
            l50.x = (double)((int)x + facing * 0x37);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playVoice = 0xa;
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (unk58 == 3 || unk58 == 1) {
            unk13c = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (unk58 == 1) {
                unk58 = 0;
            }
            if (unk58 == 3) {
                unk58 = 1;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xf9:
        if (frame == 0 && timer == 0) {
            unkdc = 4;
            unkde = -0x14;
            vx = 0.0;
            m_hitsLeft = 1;
            unk14e = 0;
            unk14c = 0x3c;
            l50.type = 0x28;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 0x13;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xfa:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1a1;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case 0xfb:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1a2;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x21);
            l50.scale = 2;
            m_playVoice = 0xb;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case 0xfc:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            StopMoving();
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
            unk3454 = 0;
        }
        if (frame == 5 && timer == 0) {
            l50.type = 0x1f;
            l50.facing = facing;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x64);
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.x = (double)((int)x - facing * 0x3c);
            l50.y = (double)((int)y - 0x64);
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0x64);
            l50.y = (double)((int)y - 0x28);
            SpawnObject(&l50);
            l50.x = (double)((int)x - facing * 0x64);
            l50.y = (double)((int)y - 0x28);
            m_playVoice = 0xb;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && unk3138 < 5) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfd:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = 0.0;
            l50.scale = 0;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case 0xfe:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0xa0);
            l50.y = 0.0;
            l50.scale = 0;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case 0xff:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
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
        if (frame == 6 && timer == 0) {
            l50.type = 0x198;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
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
    case 0x100:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1bc;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x33);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1bf;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x1f);
            SpawnObject(&l50);
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0xb);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x1bd;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x3a);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1bf;
            l50.x = (double)((int)x + facing * 0x12);
            l50.y = (double)((int)y - 0x26);
            SpawnObject(&l50);
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0x12);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x101:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1bc;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x33);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1bf;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x1f);
            SpawnObject(&l50);
            l50.type = 0x1be;
            l50.x = (double)((int)x + facing * 0x15);
            l50.y = (double)((int)y - 0xb);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x1c3;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x47);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x3d);
            SpawnObject(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x33);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x102:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0x1c3;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x47);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c2;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x3d);
            SpawnObject(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x33);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        if (frame == 0xe && timer == 0) {
            l50.type = 0x1c3;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x47);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x1c1;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = (double)((int)y - 0x3d);
            SpawnObject(&l50);
            l50.type = 0x1c0;
            l50.x = (double)((int)x + facing * 0x1a);
            l50.y = (double)((int)y - 0x33);
            SpawnObject(&l50);
            m_playVoice = 3;
            m_gauge = m_gauge + 0xf;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x103:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 4 && timer == 0) {
                l50.type = 0x1b5;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x2d;
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x104:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 4 && timer == 0) {
                l50.type = 0x1b5;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                m_gauge = m_gauge + 0x2d;
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x105:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 1;
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
            StopMoving();
            m_hitsLeft = 3;
        }
        if (frame == 5 && timer == 0 && unk3138 < 2) {
            l50.type = 0x1b5;
            l50.x = (double)((int)x + -0x23 + (WORD)Random(0, 0x46));
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame == 4 && unk3138 < 2) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x106:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1a1;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                if (unk3458 > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case 0x107:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1a4;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x26);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                if (unk3458 > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case 0x108:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            vx = 0.0;
            vy = 0.0;
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
            unk3454 = 0;
        }
        if (frame == 5 && timer == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x64);
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.x = (double)((int)x - facing * 0x3c);
            l50.y = (double)((int)y - 0x64);
            SpawnObject(&l50);
            l50.x = (double)((int)x + facing * 0x64);
            l50.y = (double)((int)y - 0x28);
            SpawnObject(&l50);
            l50.x = (double)((int)x - facing * 0x64);
            l50.y = (double)((int)y - 0x28);
            m_playVoice = 0xb;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xb && unk3138 < 2) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                if (unk3458 > 0) {
                    pattern = 0xb3;
                    frame = 7;
                }
            }
        }
        break;
    case 0x109:
        unk58 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1cb;
            l50.x = (double)((int)x + facing * 0x26);
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            m_playVoice = 0xb;
            l50.facing = facing;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                if (unk3458 > 0) {
                    frame = 7;
                    pattern = 0xb3;
                }
            }
        }
        break;
    case 0x12c:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            Unk410a80(0x32, 3);
        }
        if (frame == 5 && timer == 0 && unk313c < 7) {
            l50.unk0 = 1;
            l50.type = unk3138 + 0x19b;
            l50.x = (double)((int)x - ((WORD)Random(0, 0x14) + 0x154 + unk313c * 8) * facing);
            l50.y = (double)(4 - (WORD)Random(0, 4));
            l50.unk28 = 1;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            unk3138++;
            if (unk3138 > 5) {
                unk3138 = 0;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk313c < 0xa) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12d:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2) {
            Unk410a80(0x32, 3);
        }
        if (frame == 5 && timer == 0 && unk313c < 0x11) {
            l50.unk0 = 1;
            l50.type = unk3138 + 0x19b;
            l50.x = (double)((int)x - ((WORD)Random(0, 0x14) + 0x154 + unk313c * 8) * facing);
            l50.y = (double)(4 - (WORD)Random(0, 4));
            l50.unk28 = 1;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            unk3138++;
            if (unk3138 > 5) {
                unk3138 = 0;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk313c < 0x14) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12e:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 2) {
            Unk410a80(0x32, 3);
        }
        if (frame == 5 && timer == 0 && unk313c < 0x23) {
            l50.unk0 = 1;
            l50.type = unk3138 + 0x19b;
            l50.x = (double)((int)x - ((WORD)Random(0, 0x14) + 0x154 + unk313c * 8) * facing);
            l50.y = (double)(4 - (WORD)Random(0, 4));
            l50.unk28 = 1;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            unk3138++;
            if (unk3138 > 5) {
                unk3138 = 0;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk313c < 0x23) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12f:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            Unk410a80(0x32, 0x2d);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b8;
            l50.unk28 = 1;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = -480.0;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame > 7 && unk3448 == 1) {
            m_game->FlashWhite(9, 0x50, 9);
            StartPattern();
            pattern = 0x132;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x130:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            Unk410a80(0x32, 0x2d);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b8;
            l50.unk28 = 1;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = -480.0;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame > 7 && unk3448 == 1) {
            m_game->FlashWhite(9, 0x50, 9);
            StartPattern();
            pattern = 0x133;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x131:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 7 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            Unk410a80(0x32, 0x2d);
            m_playSound = 0x25;
        }
        if (frame > 6) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b8;
            l50.unk28 = 1;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = -480.0;
            l50.facing = facing;
            l50.scale = 0;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame > 7 && unk3448 == 1) {
            m_game->FlashWhite(9, 0x50, 9);
            StartPattern();
            pattern = 0x134;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x132:
        Unk410a80(0x32, 0xf);
        if (frame == 1 && timer == 0) {
            unk3448 = 2;
            x = 230.0;
            facing = 1;
            (*m_opponent)->pattern = 0x7a;
            (*m_opponent)->facing = 1;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->x = 420.0;
            (*m_opponent)->y = -17.0;
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0xa && timer == 0) {
            m_playVoice = 3;
            l50.type = 0x1c6;
            l50.scale = 0;
            l50.x = x + 20.0;
            l50.y = -50.0;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x11 && (unk3448 == 2 || unk3448 == 4 || unk313c > 0)) {
                frame = frame - 3;
                unk313c--;
            }
            if (frame == 0x11 && unk3448 == 5) {
                frame = 0x15;
            }
            if (frame >= x8) {
                pattern = 0;
                unk3448 = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x133:
        Unk410a80(0x32, 0xf);
        if (frame == 1 && timer == 0) {
            unk3448 = 2;
            x = 230.0;
            facing = 1;
            (*m_opponent)->pattern = 0x7a;
            (*m_opponent)->facing = 1;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->x = 420.0;
            (*m_opponent)->y = -17.0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b7;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = 0.0;
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0x10 && timer == 0) {
            m_playVoice = 3;
            l50.type = 0x1c6;
            if (unk3138 == 1) {
                l50.type = 0x1c7;
            }
            if (unk3138 == 2) {
                l50.type = 0x1c5;
            }
            l50.scale = 0;
            l50.x = x + 20.0;
            l50.y = -50.0;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xa) {
                frame = 0x10;
            }
            if (frame == 0xd) {
                frame = 0x10;
            }
            if (frame == 7) {
                if (unk3138 == 1) {
                    frame = 0xa;
                }
                if (unk3138 == 2) {
                    frame = 0xd;
                }
            }
            if (frame == 0x17 && (unk3448 == 2 || unk3448 == 4 || unk313c > 0)) {
                frame = frame - 3;
                unk313c--;
            }
            if (frame == 0x1e) {
                frame = 2;
                unk3448 = 2;
                unk3138++;
            }
            if (frame == 0x1b && unk3138 == 1) {
                frame = 0x1e;
            }
            if (frame == 0x17 && unk3448 == 5) {
                frame = 0x1e;
            }
            if (frame >= x8) {
                pattern = 0;
                unk3448 = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x134:
        Unk410a80(0x32, 0xf);
        m_game->Unk4080c0(0xf);
        if (frame == 1 && timer == 0) {
            unk3448 = 2;
            x = 230.0;
            facing = 1;
            (*m_opponent)->pattern = 0x7a;
            (*m_opponent)->facing = 1;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->x = 420.0;
            (*m_opponent)->y = -17.0;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b7;
            l50.x = (double)((int)x + (facing << 4));
            l50.y = 0.0;
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (frame == 6 && timer == 0) {
            m_playVoice = 2;
        }
        if (frame == 0x10 && timer == 0) {
            m_playVoice = 3;
            l50.type = 0x1c6;
            if (unk3138 == 1) {
                l50.type = 0x1c7;
            }
            if (unk3138 == 2) {
                l50.type = 0x1c5;
            }
            l50.scale = 0;
            l50.x = x + 20.0;
            l50.y = -50.0;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xa) {
                frame = 0x10;
            }
            if (frame == 0xd) {
                frame = 0x10;
            }
            if (frame == 7) {
                if (unk3138 == 1) {
                    frame = 0xa;
                }
                if (unk3138 == 2) {
                    frame = 0xd;
                }
            }
            if (frame == 0x17 && (unk3448 == 2 || unk3448 == 4 || unk313c > 0)) {
                frame = frame - 3;
                unk313c--;
            }
            if (frame == 0x1e) {
                frame = 2;
                unk3448 = 2;
                unk3138++;
            }
            if (frame == 0x1b && unk3138 == 2) {
                frame = 0x1e;
            }
            if (frame == 0x17 && unk3448 == 5) {
                frame = 0x1e;
            }
            if (frame >= x8) {
                pattern = 0;
                unk3448 = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x135:
        StartAfterimages(2);
        if (frame < 6) {
            Unk410a80(0x32, 3);
        }
        if (frame < 0xe && (*m_opponent)->pattern == 0x63) {
            (*m_opponent)->StartPattern();
        }
        if (frame > 8) {
            if (vy + y > 0.0 && frame < 0xe) {
                y = 0.0;
                frame = 0xe;
                timer = 0;
                StopMoving();
                ShakeScreen(0xf, 0xa);
                m_playSound = 0x16;
                DealDamage(0x320, 900.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x62;
                l50.type = 0x190;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                l50.type = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk14a = 0xb4;
                break;
            }
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->y = -98.0;
                (*m_opponent)->x = facing * 0x23 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -98.0;
                (*m_opponent)->x = facing * 0x21 + x;
                if (unk3138 > 0) {
                    timer = 0x96;
                }
            }
            if (frame == 3) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x21 + x;
                (*m_opponent)->facing = -facing;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x61;
                (*m_opponent)->unk12c = 1;
                DealDamage(0x12c, 980.0);
                if ((*m_opponent)->m_hp <= 0) {
                    (*m_opponent)->m_hp = 1;
                }
            }
            if (frame == 6 && unk3138 < 3) {
                unk3138++;
                frame = 0;
            }
            if (frame == 9) {
                vy = -7.0;
                vx = 0.3;
                ay = 0.15;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->StartPattern();
        }
        if (frame == 1 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            Unk410a80(0x32, 0x2d);
        }
        if (frame < 7) {
            Unk410a80(0x32, 0x2d);
            (*m_opponent)->unk14a = 3;
        }
        if (frame == 7) {
            Unk410a80(0, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 || frame == 6) {
                l50.type = 0;
                l50.unk2c = 2;
                l50.x = (double)((int)x + facing * 0x1d);
                l50.y = (double)((int)y - 0x53);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 1) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -101.0;
                (*m_opponent)->x = facing * 0x15 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
                m_playSound = 0x16;
                l50.type = 0x193;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0xfa);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.facing = facing;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame == 3) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 7 && unk3138 > 0xa) {
                (*m_opponent)->pattern = 0x3e;
                (*m_opponent)->unkc0 = 0.0;
                (*m_opponent)->unkc8 = -5.0;
                (*m_opponent)->ay = 0.035;
                DealDamage(0xdac, 700.0);
                (*m_opponent)->unk124 = 0xb4;
            }
            if (frame == 7 && unk3138 < 0xb) {
                unk3138++;
                frame = 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->StartPattern();
        }
        if (frame < 7) {
            Unk410a80(0x32, 0x2d);
            (*m_opponent)->unk14a = 3;
        }
        if (frame == 7) {
            Unk410a80(0, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 || frame == 6) {
                l50.type = 0;
                l50.unk2c = 2;
                l50.x = (double)((int)x + facing * 0x1d);
                l50.y = (double)((int)y - 0x53);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 1) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -101.0;
                (*m_opponent)->x = facing * 0x15 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
                m_playSound = 0x16;
                l50.type = 0x193;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0xfa);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.facing = facing;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame == 3) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 5) {
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 6) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->y = -99.0;
                (*m_opponent)->x = facing * 0xf + x;
            }
            if (frame == 7 && unk3138 > 8) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = 0.2;
                (*m_opponent)->unkc8 = -1.9;
                DealDamage(0x3e8, 1000.0);
                m_hitsLeft = 1;
            }
            if (frame == 7 && unk3138 < 9) {
                unk3138++;
                frame = 2;
            }
            if (frame == 0x10) {
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y + 4);
                l50.scale = 0;
                l50.unk0 = 1;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                ShakeScreen(0xa, 0x3c);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 2;
        }
        if (frame == 6 && timer == 0) {
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.facing = facing;
            l50.unk0 = 1;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y + 4);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.facing = facing;
            l50.unk0 = 1;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 2 && m_attackResult == 3) {
            ShakeScreen(6, 0x3c);
            (*m_opponent)->unk14a = 0x1f4;
        }
        if (frame == 0xa && timer == 0) {
            ShakeScreen(0xa, 0x3c);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_attackResult != 3 && frame == 6) {
                frame = 0xc;
            }
            if (frame == 9 || frame == 1) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            StopMoving();
            if (frame == 1 && timer == 0) {
                m_gauge = m_gauge - 0xbb8;
            }
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (m_attackResult == 6) {
            StartPattern();
            frame = 2;
            m_attackResult = 0;
            unk14c = 0x78;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                frame = 3;
                break;
            }
            if (frame == 3) {
                StartPattern();
                pattern = 0x138;
                break;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13a:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 1 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x17);
            l50.y = (double)((int)y - 0x33);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3138++;
            m_playSound = 0x25;
            m_hitsLeft = 1;
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 0) {
            Unk410a80(0x32, 3);
        }
        if (frame > 2 && frame < 8) {
            vy = vy + ay;
            if (frame == 7 && vy + y > 0.0) {
                timer = 0;
                frame = 9;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        if (frame == 0xc && timer == 0 && m_attackResult == 3) {
            m_game->FlashWhite(9, 0xf, 9);
        }
        if (frame == 0xd && timer == 0 && m_attackResult == 3) {
            StartPattern();
            pattern = 0x13b;
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
                vx = 2.0;
                vy = -2.0;
                ay = 0.08;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13b:
        unk13e = 3;
        if ((*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 2) {
            FillBackground(0xb0, 3);
        }
        if (frame < 2) {
            Unk410a80(0x32, 3);
        }
        if (frame < 2) {
            Unk410a40(0x32, 3);
        }
        if (frame == 0 && timer == 0) {
            x = 320.0;
            StopMoving();
            l50.type = 0x1b2;
            l50.screen = 1;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 0;
            l50.facing = 1;
            SpawnObject(&l50);
            l50.type = 0x1a5;
            l50.screen = 0;
            l50.x = 320.0;
            l50.y = 200.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            (*m_opponent)->x = 320.0;
            (*m_opponent)->y = -160.0;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x3b;
        }
        if (frame == 0) {
            unk3138++;
            if (unk3138 == 0x50) {
                l50.type = 0x1a6;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0xa0) {
                l50.type = 0x1a7;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0xf0) {
                l50.type = 0x1a8;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0x140) {
                l50.type = 0x1a9;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0x190) {
                l50.type = 0x1aa;
                l50.x = 320.0;
                l50.y = 200.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
        }
        if (frame == 0 && timer == l4 - 0x1e) {
            m_game->FlashBlack(9, 0x1e, 9);
            unk3138 = 0;
            (*m_opponent)->x = 320.0;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x79;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 1) {
            unk3138++;
            if (unk313c > 0) {
                frame = 2;
                timer = 0;
                facing = -(*m_opponent)->facing;
                x = unk313c;
                y = unk3140;
                vx = -0.9;
                vy = -1.5;
            }
            if (unk3138 == 0x96) {
                l50.type = 0x1b6;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0xae) {
                l50.type = 0x1ac;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0xc6) {
                l50.type = 0x1ad;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0xde) {
                l50.type = 0x1ae;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0xf6) {
                l50.type = 0x1af;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
            if (unk3138 == 0x10e) {
                l50.type = 0x1b0;
                l50.x = x - facing * 0xf0;
                l50.y = -20.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
            }
        }
        if (frame > 1) {
            vy += 0.035;
            if (vy + y > 0.0) {
                StartPattern();
                StopMoving();
                pattern = 0xd;
                y = 0.0;
                break;
            }
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
    case 0x13c:
        unk58 = 0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0 && unk3138 == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xe);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3138++;
            m_playSound = 0x25;
        }
        if (frame > 3) {
            m_game->Unk4080c0(0xf);
        }
        Unk410a80(0x32, 3);
        if (frame == 9 && timer == 0) {
            l50.unk0 = 1;
            l50.type = 0x1c4;
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = 15.0;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk3138 < 6) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
    }
}
