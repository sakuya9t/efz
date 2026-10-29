// CMishio::UpdatePattern (0x530bc0-0x54647f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMishio's
// .rdata, which starts with its constructor's folder name (mishio.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMishio::UpdatePattern()
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
        vx = 0.4;
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
        vx = -0.4;
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
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.04;
            vy = -2.45;
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
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.04;
            vy = -2.45;
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
        if (frame == 0 && timer == 0) {
            if (unk158 == 0) {
                FaceOpponent();
            }
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.04;
            vy = -2.45;
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
        FaceOpponent();
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
        ay = 0.04;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.45;
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
        ay = 0.04;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.45;
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
        ay = 0.04;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.45;
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
        if (unk120 != 0) {
            unk118 -= 1.5;
        }
        m_gauge = m_gauge + 3;
        vx = unkc0;
        vy = unkc8;
        timer++;
        if ((char)Unk40ff70() != 0) {
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
                FaceOpponent();
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
                FaceOpponent();
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
        timer++;
        unk158 = 0;
        if (m_hp > 0 && timer > 0x63 && frame == 0) {
            pattern = 0x60;
            StartPattern();
        }
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
                FaceOpponent();
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
                FaceOpponent();
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
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xa1:
        if (frame == 0 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_playSound = 0x3e;
            unk3138++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
                ay = 0.035;
            }
        }
        break;
    case 0xa2:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 6 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x3c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_playSound = 0x3e;
            m_gauge = m_gauge - 0x3e8;
            unk3138++;
        }
        vy = vy + ay;
        if (y + vy > 0.0) {
            pattern = 0xd;
            StartPattern();
            StartPattern();
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
            StartAfterimages(3);
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
        if (frame == 5 && timer == 0) {
            vx = 1.0;
        }
        unk158 = 1;
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
            pattern = 0xb2;
            StartPattern();
        }
        if (m_inputX != facing && unk3138 >= 0x3c) {
            pattern = 0xb2;
            StartPattern();
        }
        break;
    case 0xa4:
        StartAfterimages(2);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame > 0 && frame < 3) {
            vy = vy + ay;
        }
        if (frame > 0 && vy + y >= 0.0 && unk3138 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            unk3138++;
            m_playSound = 9;
            frame = 3;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                vx = -1.7;
                vy = -1.0;
                ay = 0.04;
            }
            if (frame == 3) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                FaceOpponent();
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 1.3;
            StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            m_playSound = 0x11;
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
        if (m_inputX != facing && unk3138 >= 0x27) {
            pattern = 9;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -1.3;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(3);
            m_playSound = 0x11;
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
        if (m_inputX != -facing && unk3138 >= 0x30) {
            pattern = 9;
            StartPattern();
            vx = -0.9;
            ay = 0.03;
            if (FaceOpponent() != 0) {
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
            StopMoving();
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
            FillBackground(0xb0, 3);
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
            StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 0xa) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xa;
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
            if (frame == 0xa) {
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
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
                FaceOpponent();
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
                pattern = 3;
                if (m_inputY != 1) {
                    pattern = 7;
                }
                FaceOpponent();
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcb:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
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
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x23;
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 4) {
                m_attackResult = 0;
            }
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
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
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                FaceOpponent();
                StartPattern();
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
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
            StartPattern();
            break;
        }
        if (frame == 2 && timer == 0) {
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
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xd2:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk158 = 0;
        }
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.035;
        }
        if (y + vy > 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                vx = 1.0;
                vy = -1.3;
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
    case 0xd3:
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
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
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3 && timer == 0) {
                m_gauge = m_gauge + 0x1e;
                m_playSound = 0x14;
                m_hitsLeft = 1;
            }
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
            m_playSound = 7;
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
        unk158 = 0;
        if (frame == 2 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
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
    case 0xdd:
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->pattern = 0x6c;
                (*m_opponent)->StartPattern();
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0xd + x;
                (*m_opponent)->pattern = 0x6c;
                (*m_opponent)->StartPattern();
            }
            if (frame == 3) {
                if ((char)Unk40ff70() != 0) {
                    x = facing * 5 + x;
                }
                (*m_opponent)->x = x - facing * 5;
                (*m_opponent)->pattern = 0x34;
                (*m_opponent)->StartPattern();
                (*m_opponent)->facing = -(*m_opponent)->facing;
            }
            if (frame == 5) {
                facing = -facing;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0xe6:
        StartAfterimages(3);
        unk158 = 0;
        vx -= 0.02;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
                StartPattern();
            }
        }
        break;
    case 0xe7:
        StartAfterimages(3);
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
            StartPattern();
            break;
        }
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
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
                StartPattern();
            }
        }
        break;
    case 0xe8:
        StartAfterimages(3);
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
            StartPattern();
            break;
        }
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
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
                StartPattern();
            }
        }
        break;
    case 0xe9:
        StartAfterimages(3);
        unk158 = 0;
        vx -= 0.02;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 1.0;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
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
                StartPattern();
            }
        }
        break;
    case 0xea:
        StartAfterimages(3);
        unk158 = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xeb:
        StartAfterimages(3);
        unk158 = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xf8:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->unk128 = 1;
            StopMoving();
            StartPattern();
            l50.type = 0;
            l50.x = (double)((int)x + (facing << 5));
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->y = y - 73.0;
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
        unk13e = 2;
        if (frame < 6) {
            Unk410a40(0x32, 3);
            Unk410a80(0x32, 3);
        }
        if (frame > 6) {
            (*m_opponent)->Unk410a80(0x32, 3);
        }
        if (frame == 4 && timer == 0) {
            DealDamage(0x47e, 500.0);
            (*m_opponent)->StartPattern();
        }
        if (frame > 1 && frame < 4) {
            vy += 0.05;
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = facing * 0x11 + x;
            (*m_opponent)->y = y + 11.0;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                frame = 4;
                timer = 0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x - facing * 6;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x62;
                l50.type = 0;
                l50.x = (double)((int)x - facing * 9);
                l50.y = (double)((int)y + 4);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk2c = 2;
                m_game->CreateEffect((EffectDesc*)&l50);
                break;
            }
        }
        if (frame > 6 && y < 0.0) {
            vy += 0.035;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                timer = 0;
                frame = 0x10;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x75;
                (*m_opponent)->y = y - 22.0;
                (*m_opponent)->x = facing * 0x27 + x;
            }
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame == 6) {
                facing = -facing;
            }
            if (frame == 7) {
                vx = -1.5;
                vy = -1.0;
            }
            if (frame == 0x10) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_attackResult > 0 && unk3158 == 0) {
                    if ((WORD)Random(0, 0x3e8) < 0x1f4) {
                        unk3158 = 1;
                    } else {
                        unk3158 = 2;
                    }
                }
                StartPattern();
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_attackResult > 0 && unk3158 == 0) {
                    if ((WORD)Random(0, 0x3e8) < 0x1f4) {
                        unk3158 = 1;
                    } else {
                        unk3158 = 2;
                    }
                }
                StartPattern();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            m_hitsLeft = 2;
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
        }
        if (m_attackResult > 0) {
            unk3138 = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 0xb) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame == 0xc) {
                m_playVoice = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3138 > 0 && unk3158 == 0) {
                    if ((WORD)Random(0, 0x3e8) < 0x1f4) {
                        unk3158 = 1;
                    } else {
                        unk3158 = 2;
                    }
                }
                StartPattern();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_hitsLeft = 6;
        }
        if (vx > 0.0) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 0xa || frame == 0xd || frame == 0x10 || frame == 0x13) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = 3.0;
            }
            if (frame == 7 && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 7 && m_attackResult == 0) {
                frame = 0x16;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_hitsLeft = 4;
        }
        if ((frame == 6 || frame == 9 || frame == 0xc || frame == 0xf) && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 5;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 6 || frame == 9 || frame == 0xc || frame == 0xf) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xff:
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
            unk158 = 0;
            StopMoving();
            m_hitsLeft = 0x63;
        }
        if (vx > 0.0) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 0xa || frame == 0xd || frame == 0x10 || frame == 0x13 || frame == 0x16 || frame == 0x19 || frame == 0x1c || frame == 0x1f) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = 3.2;
            }
            if (frame == 7 && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
                m_attackResult = 0;
                break;
            }
            if (frame == 7 && m_attackResult == 0) {
                frame = 0x1f;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 4 && frame < 7 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && timer == 0) {
                facing = -facing;
            }
            if (frame == 5 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_gauge = m_gauge + 0x14;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = 0x11a;
                StartPattern();
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 4 && frame < 7 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_gauge = m_gauge + 0x14;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = 0x11a;
                StartPattern();
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame > 4 && frame < 7 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-90.0, 2.2);
                m_gauge = m_gauge + 0x14;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x193;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = 0x11a;
                StartPattern();
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (frame > 2 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(0.0, 2.2);
                m_gauge = m_gauge + 0x14;
                l50.type = 0x195;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 5 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x11b;
                frame = 0;
            }
        }
        break;
    case 0x104:
        if (frame > 3 && frame < 6 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = 0x11b;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(45.0, 2.2);
                m_gauge = m_gauge + 0x14;
                l50.type = 0x196;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 6 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x11a;
                frame = 0;
            }
        }
        break;
    case 0x105:
        if (frame > 3 && frame < 6 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = 0x11b;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(90.0, 2.2);
                m_gauge = m_gauge + 0x14;
                l50.type = 0x197;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 6 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x11a;
                frame = 0;
            }
        }
        break;
    case 0x106:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-90.0, 2.2);
                m_gauge = m_gauge + 5;
                l50.type = 0x193;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x10b;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_gauge = m_gauge + 5;
                l50.type = 0x194;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x10b;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(0.0, 2.2);
                m_gauge = m_gauge + 5;
                l50.type = 0x195;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x10b;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x109:
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = 0x10b;
            break;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(45.0, 2.2);
                m_gauge = m_gauge + 5;
                l50.type = 0x196;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x10b;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x10a:
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = 0x10b;
            break;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 5;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(90.0, 2.2);
                m_gauge = m_gauge + 5;
                l50.type = 0x197;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x10b;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x10b:
        if (unk3140 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            unk3140++;
        }
        if (unk313c == 0 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    unk313c++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    unk313c++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
                FaceOpponent();
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x10c:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 7 && timer == 0) {
            m_playVoice = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + (facing << 6));
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk3148 = 1;
            m_gauge = m_gauge + 0x19;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 7 && timer == 0) {
            m_playVoice = 1;
            l50.type = 0x191;
            l50.x = (double)((int)x + (facing << 6));
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk3148 = 1;
            m_gauge = m_gauge + 0x19;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x10e:
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
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 7 && timer == 0) {
            m_playVoice = 2;
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x3c);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk3148 = 1;
            m_gauge = m_gauge + 0x19;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x10f:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 5 && timer == 0) {
            l50.type = 0x198;
            if (x - (*m_opponent)->x < 150.0 && x - (*m_opponent)->x > -150.0) {
                l50.x = (*m_opponent)->x;
            } else {
                if ((*m_opponent)->x > x) {
                    l50.x = x + 150.0;
                }
                if ((*m_opponent)->x < x) {
                    l50.x = x - 150.0;
                }
            }
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk314c = 1;
            m_gauge = m_gauge + 0x19;
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0xa && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        vy = vy + ay;
        if (frame == 5 && timer == 0) {
            l50.type = 0x198;
            if (x - (*m_opponent)->x > 150.0 || x - (*m_opponent)->x < -150.0) {
                l50.x = (*m_opponent)->x;
            } else {
                if ((*m_opponent)->x > x) {
                    l50.x = x + 150.0;
                }
                if ((*m_opponent)->x < x) {
                    l50.x = x - 150.0;
                }
            }
            l50.y = (double)(int)y;
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk314c = 1;
            m_gauge = m_gauge + 0x19;
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0xa && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                l50.type = 0x1b5;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 3) {
                m_playVoice = 5;
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
                StartPattern();
            }
        }
        break;
    case 0x112:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.04500000178813934;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 5;
                vx = 2.5;
                l50.type = 0x1b5;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
                StartPattern();
            }
        }
        break;
    case 0x113:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
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
            vx = 1.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (m_attackResult > 0) {
            unk3138 = 1;
        }
        if (vx > 0.0) {
            vx -= 0.02500000037252903;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 0xb) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 5;
                l50.type = 0x1bc;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 9) {
                m_hitsLeft = 1;
                m_attackResult = 0;
                m_playVoice = 5;
                l50.type = 0x1b5;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
                StartPattern();
            }
        }
        break;
    case 0x114:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 4;
                l50.type = 0x1b6;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
                StartPattern();
            }
        }
        break;
    case 0x115:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.04500000178813934;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 4;
                l50.type = 0x1b6;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1ba;
                l50.unk0 = 1;
                l50.x = (double)((int)x + facing * 0x5a);
                l50.y = (double)((int)y - 0x3c);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
                StartPattern();
            }
        }
        break;
    case 0x116:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
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
            vy = 0.0;
            ax = 0.0;
        }
        if (m_attackResult > 0) {
            unk3138 = 1;
        }
        if (vx > 0.0) {
            vx -= 0.02500000037252903;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 0xb) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 4;
                l50.type = 0x1bd;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 9) {
                m_hitsLeft = 1;
                m_attackResult = 0;
                m_playVoice = 4;
                l50.type = 0x1b6;
                l50.x = (double)((int)x + facing * 0x26);
                l50.y = (double)((int)y - 0x28);
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
                StartPattern();
            }
        }
        break;
    case 0x117:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x118:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            unk3138 = 5;
            m_hitsLeft = 1;
        }
        if (vx > 0.0) {
            vx -= 0.04500000178813934;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
                vx = 2.5;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x119:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_gauge = m_gauge + 0x2d;
            m_hitsLeft = 2;
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
            vy = 0.0;
            ax = 0.0;
        }
        if (m_attackResult > 0) {
            unk3138 = 1;
        }
        if (vx > 0.0) {
            vx -= 0.02500000037252903;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 || frame == 0xb) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_playVoice = 0;
            }
            if (frame == 0xc) {
                m_playVoice = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11a:
        if (unk3140 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            unk3140++;
        }
        if (unk313c == 0 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    unk313c++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    unk313c++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x11b:
        if (unk3140 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            unk3140++;
        }
        if (unk313c == 0 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x106;
                    unk313c++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x107;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x107;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x108;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x108;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x10a;
                    unk313c++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x109;
                    unk313c++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x109;
                    unk313c++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
                FaceOpponent();
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            unk3150 = 0;
            StopMoving();
        }
        if (vx > 0.0) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3 && unk3150 == 0) {
            (*m_opponent)->unk14a = 0xb4;
            unk14a = 0x5a;
            unk3150++;
        }
        if (m_attackResult == 3 && (*m_opponent)->y < 0.0 && frame < 0xa) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x37;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 0xd || frame == 0x10 || frame == 0x13 || frame == 0x16 || frame == 0x19 || frame == 0x1c || frame == 0x1f) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = 3.5;
            }
            if (frame == 0xa && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && m_attackResult != 3) {
                frame = 0x22;
                break;
            }
            if (frame == 0x14 && unk313c < 2) {
                frame = 0xb;
                unk313c++;
            }
            if (frame == 0x1f && unk3140 < 3) {
                frame = 0x16;
                unk3140++;
                m_attackResult = 0;
            }
            if (frame >= x8 || frame == 0x28) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            unk3150 = 0;
            StopMoving();
        }
        if (vx > 0.0) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3 && unk3150 == 0) {
            (*m_opponent)->unk14a = 0xb4;
            unk14a = 0x5a;
            unk3150++;
        }
        if (m_attackResult == 3 && (*m_opponent)->y < 0.0 && frame < 0xa) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x37;
            break;
        }
        if (frame > 0x15 && frame < 0x1f && (WORD)Random(0, 0x64) < 0xa) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + ((WORD)Random(0, 0x6e) - 0x14) * facing);
            l50.y = (double)((int)y - (WORD)Random(0, 0x5a));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 0xd || frame == 0x10 || frame == 0x13 || frame == 0x16 || frame == 0x19 || frame == 0x1c || frame == 0x1f) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = 4.0;
            }
            if (frame == 0xa && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && m_attackResult != 3) {
                frame = 0x28;
                break;
            }
            if (frame == 0x14 && unk313c < 3) {
                frame = 0xb;
                unk313c++;
            }
            if (frame == 0x1f && unk3140 < 4) {
                frame = 0x16;
                unk3140++;
                m_attackResult = 0;
            }
            if (frame >= x8 || frame == 0x28) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            unk3150 = 0;
            m_playSound = 0x25;
            StopMoving();
        }
        m_game->Unk4080c0(0xf);
        if (vx > 0.0) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult == 3 && unk3150 == 0) {
            (*m_opponent)->unk14a = 0xb4;
            unk14a = 0x5a;
            unk3150++;
            m_game->Unk4080c0(0x5d);
        }
        if (m_attackResult == 3 && (*m_opponent)->y < 0.0 && frame < 0xa) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x37;
            break;
        }
        if (frame > 0x15 && frame < 0x1f && (WORD)Random(0, 0x64) < 0xa) {
            l50.type = 0x19a;
            l50.x = (double)((int)x + ((WORD)Random(0, 0x6e) - 0x14) * facing);
            l50.y = (double)((int)y - (WORD)Random(0, 0x5a));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (frame > 0x15 && frame < 0x1f && (WORD)Random(0, 0x64) < 5) {
            l50.type = 0x19b;
            l50.x = (double)((int)x + ((WORD)Random(0, 0x6e) - 0x14) * facing);
            l50.y = (double)((int)y - (WORD)Random(0, 0x5a));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 2) {
                m_attackResult = 0;
            }
            if (frame == 0xd || frame == 0x10 || frame == 0x13 || frame == 0x16 || frame == 0x19 || frame == 0x1c || frame == 0x1f) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                l50.type = 0x1f;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = 5.0;
            }
            if (frame == 0xa && unk3138 < 2) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && m_attackResult != 3) {
                frame = 0x28;
                break;
            }
            if (frame == 0x14 && unk313c < 3) {
                frame = 0xb;
                unk313c++;
            }
            if (frame == 0x1f && unk3140 < 8) {
                frame = 0x16;
                unk3140++;
                m_attackResult = 0;
            }
            if (frame >= x8 || frame == 0x28) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            unk3154 = 1;
            unk3150 = 0;
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 8 && frame < 0xb && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && timer == 0) {
                m_playVoice = 0xa;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 0xb && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = 0x137;
                StartPattern();
            }
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            unk3154 = 2;
            unk3150 = 0;
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 8 && frame < 0xb && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && timer == 0) {
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                m_playVoice = 0xa;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 0xb && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = 0x137;
                StartPattern();
            }
        }
        break;
    case 0x131:
        m_game->Unk4080c0(0xf);
        if (frame == 0 && timer == 0) {
            unk3154 = 3;
            unk3150 = 0;
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 8 && frame < 0xb && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && timer == 0) {
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                unk13c = 0x2d;
                m_playVoice = 0xa;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 0xb && unk3138 < 4) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                frame = 0;
                pattern = 0x137;
                StartPattern();
            }
        }
        break;
    case 0x132:
        if (unk3154 == 3) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (frame > 6 && frame < 9 && unk3150 < unk3154 + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 0xa;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-90.0, 2.2);
                l50.type = 0x19c;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x137;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x133:
        if (unk3154 == 3) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (frame > 6 && frame < 9 && unk3150 < unk3154 + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 0xa;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(-45.0, 2.2);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x137;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x134:
        if (unk3154 == 3) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (frame > 6 && frame < 9 && unk3150 < unk3154 + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                m_playVoice = 0xa;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(0.0, 2.2);
                l50.type = 0x19d;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 9 && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x137;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x135:
        if (unk3154 == 3) {
            m_game->Unk4080c0(0xf);
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = 0x137;
            break;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (frame > 7 && frame < 0xa && unk3150 < unk3154 + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 0xa;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(45.0, 2.2);
                l50.type = 0x19f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x137;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x136:
        if (unk3154 == 3) {
            m_game->Unk4080c0(0xf);
        }
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            frame = 7;
            timer = 0;
            pattern = 0x137;
            break;
        }
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
        }
        if (frame > 7 && frame < 0xa && unk3150 < unk3154 + 1 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8 && timer == 0) {
                m_playVoice = 0xa;
                m_hitsLeft = 1;
                ObjBase::SetVelocity(90.0, 2.2);
                l50.type = 0x1a0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (frame == 4 && unk3138 < 0) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 0xa && unk3138 < 4) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame >= x8) {
                pattern = 0x137;
                frame = 0;
                unk313c++;
            }
        }
        break;
    case 0x137:
        if (unk3154 == 3) {
            m_game->Unk4080c0(0xf);
        }
        if (unk3140 == 0) {
            vx *= 0.5;
            if (vy < 0.0) {
                vy *= 0.75;
            }
            unk3140++;
        }
        if (unk3150 < unk3154 + 1 && frame < 5 && (m_pressA == 1 || m_pressB == 1 || m_pressC == 1 || m_pressD == 1)) {
            if (m_inputY == -1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x132;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x133;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x133;
                    facing = -facing;
                    unk3150++;
                    break;
                }
            }
            if (m_inputY == 0) {
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x134;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
            if (m_inputY == 1) {
                if (m_inputX == 0) {
                    StartPattern();
                    pattern = 0x136;
                    unk3150++;
                    break;
                }
                if (m_inputX == facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    break;
                }
                if (m_inputX == -facing) {
                    StartPattern();
                    pattern = 0x135;
                    unk3150++;
                    facing = -facing;
                    break;
                }
            }
        }
        if (frame < 7) {
            vy += 0.035;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
            }
        }
        if (frame > 6) {
            vx -= 0.05;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
                FaceOpponent();
                if (unk3158 == 1) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x43);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6) {
                m_playVoice = 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0xf);
                l50.y = (double)((int)y - 0x94);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1ad;
                l50.x = (double)((int)x + facing * 0xf);
                l50.y = (double)((int)y - 0x94);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xa) {
                if (unk3138 > 8) {
                    l50.type = 0x1a5;
                    l50.x = (double)((int)x + facing * 0xf);
                    l50.y = (double)((int)y - 0x94);
                    l50.scale = 2;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    break;
                }
                if (m_holdA > 0) {
                    unk3138++;
                    frame = frame - 4;
                }
            }
            if (frame == 0xd) {
                m_playVoice = 8;
            }
            if (frame == 0xf) {
                l50.type = 0x1a2;
                if (unk3138 > 8) {
                    l50.type = 0x1ae;
                }
                l50.x = (double)((int)x + facing * 0x68);
                l50.y = (double)((int)y - 0x32);
                if (unk313c == 1) {
                    l50.y = (double)((int)y - 0x3c);
                }
                if (unk313c == 2) {
                    l50.y = (double)((int)y - 0x28);
                }
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk313c < 2) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 0x12 && unk313c < 6) {
                unk313c++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x43);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6) {
                unk13c = 0xf;
                m_playVoice = 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0xf);
                l50.y = (double)((int)y - 0x94);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1ad;
                l50.x = (double)((int)x + facing * 0xf);
                l50.y = (double)((int)y - 0x94);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xa) {
                if (unk3138 > 8) {
                    l50.type = 0x1a5;
                    l50.x = (double)((int)x + facing * 0xf);
                    l50.y = (double)((int)y - 0x94);
                    l50.scale = 2;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    break;
                }
                if (m_holdB > 0) {
                    unk3138++;
                    frame = frame - 4;
                }
            }
            if (frame == 0xd) {
                m_playVoice = 8;
            }
            if (frame == 0xf) {
                l50.type = 0x1a3;
                if (unk3138 > 8) {
                    l50.type = 0x1af;
                }
                l50.x = (double)((int)x + facing * 0x68);
                l50.y = (double)((int)y - 0x32);
                if (unk313c == 1) {
                    l50.y = (double)((int)y - 0x3c);
                }
                if (unk313c == 2) {
                    l50.y = (double)((int)y - 0x28);
                }
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk313c < 2) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 0x12 && unk313c < 6) {
                unk313c++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x13a:
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x43);
            l50.y = (double)((int)y - 0x29);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6) {
                unk13c = 0x1e;
                m_playVoice = 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0xf);
                l50.y = (double)((int)y - 0x94);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1ad;
                l50.x = (double)((int)x + facing * 0xf);
                l50.y = (double)((int)y - 0x94);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xa) {
                if (unk3138 > 8) {
                    l50.type = 0x1a5;
                    l50.x = (double)((int)x + facing * 0xf);
                    l50.y = (double)((int)y - 0x94);
                    l50.scale = 2;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    break;
                }
                if (m_holdC > 0) {
                    unk3138++;
                    frame = frame - 4;
                }
            }
            if (frame == 0xd) {
                m_playVoice = 8;
            }
            if (frame == 0xf) {
                l50.type = 0x1a4;
                if (unk3138 > 8) {
                    l50.type = 0x1b0;
                }
                l50.x = (double)((int)x + facing * 0x68);
                l50.y = (double)((int)y - 0x32);
                if (unk313c == 1) {
                    l50.y = (double)((int)y - 0x3c);
                }
                if (unk313c == 2) {
                    l50.y = (double)((int)y - 0x28);
                }
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk313c < 2) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 0x12 && unk313c < 6) {
                unk313c++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0 && unk3140 == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - facing * 0x1f);
            l50.y = (double)((int)y - 0x61);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
            unk3140++;
        }
        if (frame > 9 && y < 0.0) {
            vy += 0.02;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 0x10;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 5 && unk3138 < 5) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame == 0xa) {
                m_playVoice = 9;
                vx = -1.3;
                vy = -0.8;
                l50.type = 0x1a6;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0x10) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x13c:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0 && unk3140 == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x - facing * 0x1f);
            l50.y = (double)((int)y - 0x61);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
            unk3140++;
        }
        if (frame > 9 && y < 0.0) {
            vy += 0.02;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 0x10;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 5 && unk3138 < 5) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame == 0xa) {
                m_playVoice = 9;
                vx = -1.3;
                vy = -0.8;
                l50.type = 0x1a8;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xe && unk313c < 2) {
                m_playVoice = 9;
                unk313c++;
                frame = frame - 4;
                if (unk313c == 1) {
                    l50.type = 0x1b1;
                }
                if (unk313c == 2) {
                    l50.type = 0x1a7;
                }
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0x10) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x13d:
        if (frame > 2) {
            m_game->Unk4080c0(3);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0 && unk3140 == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0x1f);
            l50.y = (double)((int)y - 0x61);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            StopMoving();
            unk3140++;
        }
        if (frame > 9 && y < 0.0) {
            vy += 0.02;
            if (y + vy > 0.0) {
                y = 0.0;
                StopMoving();
                timer = 0;
                frame = 0x10;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 5 && unk3138 < 5) {
                frame = frame - 3;
                unk3138++;
            }
            if (frame == 0xa) {
                m_playVoice = 9;
                vx = -1.3;
                vy = -0.8;
                l50.type = 0x1ac;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0xe && unk313c < 4) {
                m_playVoice = 9;
                unk313c++;
                frame = frame - 4;
                if (unk313c == 1) {
                    l50.type = 0x1ab;
                }
                if (unk313c == 2) {
                    l50.type = 0x1b2;
                }
                if (unk313c == 3) {
                    l50.type = 0x1aa;
                }
                if (unk313c == 4) {
                    l50.type = 0x1a9;
                }
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x20);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame == 0x10) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                if (unk3158 == 2) {
                    unk3158 = 0;
                }
            }
        }
        break;
    case 0x13e:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            Unk410a80(0x32, 3);
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1b4;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            l50.unk30 = 1;
            SpawnObject(&l50);
        }
        if (frame == 7 && timer == 0) {
            m_playVoice = 0xb;
            ShakeScreen(5, 0);
            unk3158 = 3;
            unk3168 = 0x1194;
            l50.type = 0x1b3;
            l50.x = (double)((int)x + facing * 5);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1ad;
            l50.x = (double)((int)x + facing * 5);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1ad;
            l50.x = (double)((int)x + facing * 0x2d);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 0;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1ad;
            l50.x = (double)((int)x - facing * 0x23);
            l50.y = (double)(int)y;
            l50.scale = 2;
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
            if (frame == 0xa && unk3138 < 5) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
    }
}
