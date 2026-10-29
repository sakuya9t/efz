// CAkane::UpdatePattern (0x6f2f20-0x7039cf), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CAkane's
// .rdata, which starts with its constructor's folder name (akane.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CAkane::UpdatePattern()
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
        if (frame == 3 && timer == 0) {
            ay = 0.054;
            vy = -3.3;
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
        if (frame == 3 && timer == 0) {
            ay = 0.054;
            vy = -3.3;
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
            ay = 0.054;
            vy = -3.3;
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
                pattern = 7;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                StartPattern();
            }
        }
        break;
    case 0xe:
        ay = 0.054;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
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
        ay = 0.054;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 0.7;
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
        ay = 0.054;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = -0.9;
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
            if (unk3148 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                unk3148 = 1;
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
            if (unk3148 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                unk3148 = 1;
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
            if (unk3148 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                unk3148 = 1;
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
            if (unk3148 == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk0 = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                unk3148 = 1;
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
            if (frame == x8 - 1) {
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
        unk158 = 0;
        if (m_hp > 0 && timer > 0x63) {
            pattern = 0x60;
            StartPattern();
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
        if (frame == 3 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
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
            if (frame == 0xc) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa3:
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
            StopMoving();
        }
        vx = 1.65;
        unk158 = 1;
        timer++;
        unk3138++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = 0;
                break;
            }
        }
        if (m_inputX == facing && unk3138 >= 0x78) {
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
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = -2.0;
            vy = -1.5;
            ay = 0.04;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 3 && vy + y >= 0.0 && unk3138 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            unk3138++;
            m_playSound = 9;
            frame = 0xd;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                FaceOpponent();
                pattern = 3;
                StartPattern();
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
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
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
            vx = -2.0;
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
            vx = 0.0;
            unk158 = 0;
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
            vx = 0.0;
            vy = 0.0;
            unk14e = 0;
            unkb8 = 0.0;
            if (ay == 0.0) {
                ay = 0.035;
            }
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
        if (y + vy > 0.0 && frame < 0xd) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xd;
            m_playSound = 9;
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
            if (frame == 0xd) {
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
        if (frame == 1 && timer == 0) {
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
        if (unk158 == 0) {
            vx = 0.0;
            vy = 0.0;
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
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
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
        if (vx > 0.0 && unk158 == 1) {
            vx -= 0.06;
        } else {
            vx = 0.0;
            unk158 = 0;
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 9;
            unk3138 = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa && unk3138 > 0) {
                unk3138--;
                frame = 7;
            }
            if (frame < 0xa) {
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcd:
        if (vx > 0.0 && unk158 == 1 && frame < 3) {
            vx -= 0.06;
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
        if (m_inputY == -1 && frame > 0 && m_attackResult == 3) {
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
            m_gauge = m_gauge + 0xd;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx += 1.5;
        }
        if (frame > 2) {
            vx -= 0.02;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
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
        if (frame == 2 && timer == 0) {
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
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xd2:
        if (frame > 6) {
            vy = vy + ay;
        }
        if (frame == 2 && timer == 0) {
            StopMoving();
        }
        if (frame == 6 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            m_playSound = 0x14;
            m_hitsLeft = 3;
            vx = 1.0;
            vy = 1.0;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            StopMoving();
            pattern = 0xd;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xa) {
                frame = 7;
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
            StartPattern();
            break;
        }
        if (frame == 3 && timer == 0) {
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
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
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
        if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x11);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 5 + x;
            (*m_opponent)->y = 0.0;
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
        if (frame == 0 && timer == 1) {
            m_hitsLeft = 1;
            m_attackResult = 0;
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->pattern = 0x32;
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
    case 0xe6:
        StartAfterimages(3);
        vx -= 0.06;
        unk158 = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 3;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (vx < 0.0) {
            vx = 0.0;
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
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 5) {
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
        vx -= 0.06;
        if (vx < 0.0) {
            vx = 0.0;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
        if (vx > 0.0) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
            vx += 1.2;
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
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xeb:
        StartAfterimages(3);
        unk158 = 0;
        if (vx > 0.0 && frame < 3) {
            vx -= 0.03;
        } else {
            unk158 = 0;
        }
        if (frame == 0xd && timer == 0) {
            m_hitsLeft = 1;
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x14;
        }
        if (frame > 2 && frame < 0x11) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                timer = 0;
                frame = 0x12;
                y = 0.0;
                StopMoving();
                break;
            }
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 1.2;
                vy = -1.5;
                ay = 0.035;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xf0:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            StartPattern();
            vx = 1.0;
            vy = -2.5;
            ay = 0.035;
            pattern = 0xf1;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x27);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
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
    case 0xf1:
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (facing == 1 && x > 630.0) {
            x = 630.0;
            vx = 0.0;
        }
        if (facing == -1 && x < 30.0) {
            x = 30.0;
            vx = 0.0;
        }
        if (vy + y > 0.0 && frame == 4) {
            StopMoving();
            y = 0.0;
            frame = 5;
            timer = 0;
        }
        if (frame == 0) {
            (*m_opponent)->y = y - 35.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = 0x64;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x15;
            (*m_opponent)->pattern = 0x73;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = x - facing * 0x14;
            (*m_opponent)->pattern = 0x68;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 76.0;
            (*m_opponent)->x = x - facing * 0xf;
            (*m_opponent)->pattern = 0x68;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 77.0;
            (*m_opponent)->x = x - facing * 0xc;
            (*m_opponent)->pattern = 0x68;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x13;
            (*m_opponent)->pattern = 0x75;
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(4, 0);
            l50.type = 3;
            l50.unk2c = 7;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0xf + x;
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -2.0;
            (*m_opponent)->unkc8 = -0.5;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->x = facing * 0xf + x;
            DealDamage(0x4b0, 500.0);
            (*m_opponent)->unk124 = (int)(200.0 * m_proration * 0.0001);
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
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
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk313c = 0;
            StopMoving();
        }
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            unk3144 = 1;
            if ((int)(x + (*m_opponent)->x) / 2 > 0x1e0) {
                unk3140++;
                l50.unk28 = 1;
                l50.type = 0x19e;
                l50.x = (double)((facing == 1) * 0x118 + (facing == -1) * 0x2a8);
                l50.y = -80.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if ((int)(x + (*m_opponent)->x) / 2 < 0xa0) {
                unk3140++;
                l50.unk28 = 1;
                l50.type = 0x19e;
                l50.x = (double)((facing == 1) * -0x28 + (facing == -1) * 0x168);
                l50.y = -80.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (unk3140 == 0) {
                l50.type = 0x19e;
                l50.unk28 = 1;
                l50.x = (x + (*m_opponent)->x) / 2.0 - facing * 0xa0;
                l50.y = -80.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            unk3138++;
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
    case 0xfb:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk313c = 0;
            StopMoving();
        }
        if (frame == 1 && timer == 0 && unk3138 == 0) {
            unk3144 = 1;
            if ((int)(x + (*m_opponent)->x) / 2 > 0x1e0) {
                unk3140++;
                l50.unk28 = 1;
                l50.type = 0x19f;
                l50.x = (double)((facing == 1) * 0x118 + (facing == -1) * 0x2a8);
                l50.y = 0.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if ((int)(x + (*m_opponent)->x) / 2 < 0xa0) {
                unk3140++;
                l50.unk28 = 1;
                l50.type = 0x19f;
                l50.x = (double)((facing == 1) * -0x28 + (facing == -1) * 0x168);
                l50.y = 0.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (unk3140 == 0) {
                l50.unk28 = 1;
                l50.type = 0x19f;
                l50.x = (x + (*m_opponent)->x) / 2.0 - facing * 0xa0;
                l50.y = 0.0;
                l50.facing = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            unk3138++;
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
    case 0xfc:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
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
        if (frame == 0 && timer == 0x1d && unk3138 == 0) {
            unk3144 = 1;
            if ((int)(x + (*m_opponent)->x) / 2 > 0x1e0) {
                unk3140++;
                l50.unk28 = 1;
                l50.type = 0x199;
                l50.x = (double)((facing == -1) * 0x118 + (facing == 1) * 0x2a8);
                l50.y = 0.0;
                l50.facing = -facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if ((int)(x + (*m_opponent)->x) / 2 < 0xa0) {
                unk3140++;
                l50.unk28 = 1;
                l50.type = 0x199;
                l50.x = (double)((facing == -1) * -0x28 + (facing == 1) * 0x168);
                l50.y = 0.0;
                l50.facing = -facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (unk3140 == 0) {
                l50.unk28 = 1;
                l50.type = 0x199;
                l50.x = (x + (*m_opponent)->x) / 2.0 + facing * 0xa0;
                l50.y = 0.0;
                l50.facing = -facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            unk3138++;
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
    case 0xfd:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            m_gauge = m_gauge + 0x2d;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0 && unk3138 == 0) {
            vx = 0.5;
            vy = -1.5;
            ay = 0.035;
        }
        if (frame == 3 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            m_hitsLeft = 1;
        }
        if (frame > 6) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 7 && frame < 0xb) {
            y = 0.0;
            StopMoving();
            StartPattern();
            frame = 0xb;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk3138 < 2) {
                frame = 3;
                unk3138++;
            }
            if (frame == 0xb) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                FaceOpponent();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.8;
        }
        if (frame == 4 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 0.8;
            vy = -2.4;
            ay = 0.035;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 0xa && frame < 0xe) {
            y = 0.0;
            StartPattern();
            StopMoving();
            frame = 0xe;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                unk13c = 0xc;
            }
            if (frame == 1 || frame == 3 || frame == 4 || frame == 7 || frame == 9 || frame == 0xe) {
                m_attackResult = 0;
            }
            if (frame == 4 && unk313c < 1) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 0xa && unk3140 < 1) {
                frame = frame - 4;
                unk3140++;
            }
            if (frame == 0xe) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                FaceOpponent();
            }
        }
        break;
    case 0xff:
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
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            StopMoving();
            m_hitsLeft = 0x63;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.8;
        }
        if (frame == 4 && timer == 0) {
            vx = 0.0;
        }
        if (frame == 6 && timer == 0) {
            vx = 0.8;
            vy = -2.4;
            ay = 0.035;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame > 0xa && frame < 0xe) {
            y = 0.0;
            StartPattern();
            StopMoving();
            frame = 0xe;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                unk13c = 0xc;
            }
            if (frame == 1 || frame == 3 || frame == 4 || frame == 7 || frame == 9 || frame == 0xe) {
                m_attackResult = 0;
            }
            if (frame == 4 && unk313c < 2) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame == 0xa && unk3140 < 2) {
                frame = frame - 4;
                unk3140++;
            }
            if (frame == 0xe) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                FaceOpponent();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = -3.5;
            ay = 0.055;
        }
        unk3138++;
        if (unk3138 > 0x34) {
            if (m_command == 0xa) {
                pattern = 0x106;
                StartPattern();
                break;
            }
            if (m_command == 0xb) {
                pattern = 0x107;
                StartPattern();
                break;
            }
            if (m_command == 0xc && (unk118 >= 500.0 || unk120 == 1)) {
                pattern = 0x108;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = 0x109;
                if (m_inputX != facing) {
                    FaceOpponent();
                }
                if (m_inputY == 0 && m_inputX == -facing) {
                    pattern = 0x10b;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10e;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        if (frame == 3 && timer == 0) {
            vx = -0.5;
            vy = -2.8;
            ay = 0.037;
        }
        unk3138++;
        if (unk3138 > 0x34) {
            if (m_command == 0xa) {
                pattern = 0x106;
                StartPattern();
                break;
            }
            if (m_command == 0xb) {
                pattern = 0x107;
                StartPattern();
                break;
            }
            if (m_command == 0xc && (unk118 >= 500.0 || unk120 == 1)) {
                pattern = 0x108;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = 0x109;
                if (m_inputX != facing) {
                    FaceOpponent();
                }
                if (m_inputY == 0 && m_inputX == -facing) {
                    pattern = 0x10b;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        if (frame == 3 && timer == 0) {
            vx = 1.5;
            vy = -2.8;
            ay = 0.037;
        }
        unk3138++;
        if (unk3138 > 0x34) {
            if (m_command == 0xa) {
                pattern = 0x106;
                StartPattern();
                break;
            }
            if (m_command == 0xb) {
                pattern = 0x107;
                StartPattern();
                break;
            }
            if (m_command == 0xc && (unk118 >= 500.0 || unk120 == 1)) {
                pattern = 0x108;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = 0x109;
                if (m_inputX != facing) {
                    FaceOpponent();
                }
                if (m_inputY == 0 && m_inputX == -facing) {
                    pattern = 0x10b;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10e;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        vx -= 0.2;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 4.5;
            vy = -3.0;
            ay = 0.035;
        }
        unk3138++;
        if (unk3138 > 0x34) {
            if (m_command == 0xa) {
                pattern = 0x106;
                StartPattern();
                break;
            }
            if (m_command == 0xb) {
                pattern = 0x107;
                StartPattern();
                break;
            }
            if (m_command == 0xc && (unk118 >= 500.0 || unk120 == 1)) {
                pattern = 0x108;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = 0x109;
                if (m_inputY == 1) {
                    pattern = 0x10a;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        vx -= 0.2;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 6.6;
            vy = -3.0;
            ay = 0.035;
        }
        unk3138++;
        if (unk3138 > 0x34) {
            if (m_command == 0xa) {
                pattern = 0x106;
                StartPattern();
                break;
            }
            if (m_command == 0xb) {
                pattern = 0x107;
                StartPattern();
                break;
            }
            if (m_command == 0xc && (unk118 >= 500.0 || unk120 == 1)) {
                pattern = 0x108;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = 0x109;
                if (m_inputY == 1) {
                    pattern = 0x10a;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            if (y < 0.0) {
                frame = 3;
            }
        }
        vx -= 0.2;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            vx = 7.9;
            vy = -3.0;
            ay = 0.035;
        }
        unk3138++;
        if (unk3138 > 0x34) {
            if (m_command == 0xa) {
                pattern = 0x106;
                StartPattern();
                break;
            }
            if (m_command == 0xb) {
                pattern = 0x107;
                StartPattern();
                break;
            }
            if (m_command == 0xc && (unk118 >= 500.0 || unk120 == 1)) {
                pattern = 0x108;
                StartPattern();
                break;
            }
            if (m_pressC == 1) {
                pattern = 0x109;
                if (m_inputY == 1) {
                    pattern = 0x10a;
                }
                StartPattern();
                break;
            }
        }
        vy = (frame > 2) * ay + vy;
        if (y + vy >= 0.0 && frame > 3) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                frame = 6;
            }
        }
        break;
    case 0x106:
        if (frame == 3 && timer == 0) {
            FaceOpponent();
            m_gauge = m_gauge + 0x19;
            vx = -0.5;
            vy = -1.0;
            ay = 0.015;
            m_playVoice = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x36);
            l50.y = (double)((int)y - 0x18);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        if (y + vy >= 0.0) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        vy = vy + ay;
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
    case 0x107:
        if (frame == 3 && timer == 0) {
            FaceOpponent();
            m_gauge = m_gauge + 0x19;
            vx = -0.5;
            vy = -1.0;
            ay = 0.015;
            m_playVoice = 1;
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x36);
            l50.y = (double)((int)y - 0x18);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        if (y + vy >= 0.0) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        vy = vy + ay;
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
    case 0x108:
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
        if (frame == 3 && timer == 0) {
            FaceOpponent();
            m_gauge = m_gauge + 0x19;
            vx = -1.0;
            vy = -1.0;
            ay = 0.02;
            m_playVoice = 1;
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x28);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x36);
            l50.y = (double)((int)y - 0x18);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        if (y + vy >= 0.0) {
            vx = 0.5;
            vy = 0.0;
            ay = 0.0;
            pattern = 0x10d;
            StartPattern();
            m_playSound = 9;
            break;
        }
        timer++;
        vy = vy + ay;
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
    case 0x109:
        if (frame == 0 && timer == 0) {
            ay = 0.0;
            vy = 0.0;
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
            vx = 1.0;
            vy = 2.0;
        }
        if (y + vy >= 0.0 && frame < 2) {
            vx = 0.5;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            frame = 2;
            timer = 0;
            m_playSound = 9;
        }
        if (vx > 0.0 && y == 0.0) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                break;
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 3;
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 2;
            vx = 0.0;
            vy = 2.1;
            ay = 0.0;
            m_playSound = 0x14;
            unk3138 = 0x63;
        }
        if (y + vy >= 0.0 && frame < 6) {
            vx = 0.0;
            vy = 0.0;
            y = 0.0;
            ay = 0.0;
            frame = 6;
            timer = 0;
            m_playSound = 9;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                break;
            }
        }
        break;
    case 0x10b:
        vy = vy + ay;
        if (frame == 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            vx = 1.0;
            vy = -2.5;
            ay = 0.035;
            pattern = 0x10c;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x27);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
        }
        if (y + vy > 0.0 && frame < 4) {
            y = 0.0;
            vy = 0.0;
            vx = 0.0;
            frame = 4;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x10c:
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (facing == 1 && x > 630.0) {
            x = 630.0;
            vx = 0.0;
        }
        if (facing == -1 && x < 30.0) {
            x = 30.0;
            vx = 0.0;
        }
        if (vy + y > 0.0 && frame == 4) {
            StopMoving();
            y = 0.0;
            frame = 5;
            timer = 0;
        }
        if (frame == 0) {
            (*m_opponent)->y = y - 35.0;
            (*m_opponent)->x = x;
            (*m_opponent)->pattern = 0x64;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x15;
            (*m_opponent)->pattern = 0x73;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = x - facing * 0x14;
            (*m_opponent)->pattern = 0x68;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 76.0;
            (*m_opponent)->x = x - facing * 0xf;
            (*m_opponent)->pattern = 0x68;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 77.0;
            (*m_opponent)->x = x - facing * 0xc;
            (*m_opponent)->pattern = 0x68;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 55.0;
            (*m_opponent)->x = x - facing * 0x13;
            (*m_opponent)->pattern = 0x75;
        }
        if (frame == 6 && timer == 0) {
            ShakeScreen(4, 0);
            l50.type = 3;
            l50.unk2c = 7;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0xf + x;
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -1.0;
            (*m_opponent)->unkc8 = -3.0;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->x = facing * 0xf + x;
            DealDamage(0x3e8, 790.0);
            (*m_opponent)->unk124 = (int)(200.0 * m_proration * 0.0001);
            (*m_opponent)->StartPattern();
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
    case 0x10d:
        if (vx > 0.0) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        y = 0.0;
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
    case 0x10e:
        if (frame == 0 && timer == 0) {
            vx = 1.0;
        }
        if (vx > 0.0) {
            vx -= 0.015;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 1 && timer == 0) {
            m_hitsLeft = 1;
        }
        y = 0.0;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x10f:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
            vx = -0.8;
            vy = -1.0;
            StopMoving();
            ay = 0.025;
        }
        if (frame > 5) {
            vy = vy + ay;
        }
        if ((frame == 9 || frame == 0xd) && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame > 5 && frame < 0xe && y + vy > 0.0) {
            if (unk3138 > 0) {
                y = 0.0;
                StopMoving();
                frame = 0xe;
                timer = 0;
                break;
            }
            if (unk3138 == 0) {
                vx = -0.5;
                vy = -1.2;
                ay = 0.04;
                unk3138++;
                y = 0.0;
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6 || frame == 7 || frame == 0xa) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                vx = 2.5;
                vy = 2.5;
            }
            if (frame == 0xe) {
                frame = frame - 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                FaceOpponent();
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
            vx = -0.8;
            vy = -1.0;
            ay = 0.025;
        }
        vy = vy + ay;
        if ((frame == 9 || frame == 0xd) && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame > 5 && frame < 0xe && y + vy > 0.0) {
            if (unk3138 > 0) {
                y = 0.0;
                StopMoving();
                frame = 0xe;
                timer = 0;
                break;
            }
            if (unk3138 == 0) {
                vx = -0.5;
                vy = -1.5;
                ay = 0.04;
                unk3138++;
                y = 0.0;
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6 || frame == 7 || frame == 0xa) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                vx = 3.2;
                vy = 2.2;
            }
            if (frame == 0xe) {
                frame = frame - 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                FaceOpponent();
            }
        }
        break;
    case 0x111:
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
            m_hitsLeft = 0x63;
            vx = -0.8;
            vy = -1.0;
            ay = 0.025;
        }
        vy = vy + ay;
        if ((frame == 9 || frame == 0xd) && timer == 0) {
            m_playSound = 0x14;
        }
        if (frame > 5 && frame < 0xe && y + vy > 0.0) {
            if (unk3138 > 0) {
                y = 0.0;
                StopMoving();
                frame = 0xe;
                timer = 0;
                break;
            }
            if (unk3138 == 0) {
                vx = -1.0;
                vy = -1.2;
                ay = 0.04;
                unk3138++;
                y = 0.0;
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                vx = 2.5;
                vy = 2.5;
            }
            if (frame == 0xe) {
                frame = frame - 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                FaceOpponent();
            }
        }
        break;
    case 0x12c:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 4 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            Unk410a80(0x32, 0xa);
        }
        if (frame > 6 && frame < 0x10 && timer == 0 && unk3138 < 2) {
            m_playVoice = 3;
            l50.type = 0x195;
            l50.x = (double)(int)((WORD)Random(0, 0x50) - 0x28 + x);
            l50.y = (double)((int)y - 0x8c);
            l50.scale = 2;
            l50.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                l50.layer = 0;
            }
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && unk3138 < 2) {
                unk3138++;
                frame = 7;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12d:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 2 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            Unk410a80(0x32, 0xa);
        }
        if (frame > 6 && frame < 0x10 && timer == 0 && unk3138 < 3) {
            m_playVoice = 3;
            l50.type = 0x195;
            l50.x = (double)(int)((WORD)Random(0, 0x50) - 0x28 + x);
            l50.y = (double)((int)y - 0x8c);
            l50.scale = 2;
            l50.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                l50.layer = 0;
            }
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && unk3138 < 3) {
                unk3138++;
                frame = 7;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12e:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        m_game->Unk4080c0(0xf);
        if (frame > 3) {
            Unk410a80(0x32, 0xa);
        }
        if (frame > 6 && frame < 0x10 && timer == 0 && unk3138 < 4) {
            m_playVoice = 3;
            l50.type = 0x195;
            l50.x = (double)(int)((WORD)Random(0, 0x50) - 0x28 + x);
            l50.y = (double)((int)y - 0x8c);
            l50.scale = 2;
            l50.layer = 1;
            if ((WORD)Random(0, 0x64) < 0x32) {
                l50.layer = 0;
            }
            l50.facing = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && unk3138 < 3) {
                unk3138++;
                frame = 7;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && unk3138 == 0) {
                m_playVoice = 2;
                l50.type = 0x19c;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x32);
                l50.scale = 2;
                l50.facing = facing;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_attackResult = 0;
            if (frame == 8 && unk3138 < 0) {
                unk3138++;
                frame = 4;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && unk3138 == 0) {
                m_playVoice = 2;
                l50.type = 0x19c;
                l50.x = (double)((int)x + facing * 0x64);
                l50.y = (double)((int)y - 0x32);
                l50.scale = 2;
                l50.facing = facing;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_attackResult = 0;
            if (frame == 8 && unk3138 < 0) {
                unk3138++;
                frame = 4;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 3) {
            Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && unk3138 == 0) {
                m_playVoice = 2;
                l50.type = 0x19c;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x96);
                l50.scale = 2;
                l50.facing = facing;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 8;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.facing = facing;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            m_attackResult = 0;
            if (frame == 8 && unk3138 < 0) {
                unk3138++;
                frame = 4;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x132:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a1;
            l50.x = (double)(int)(x - facing * 0x140);
            l50.y = (double)((int)y - 0x140);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.facing = facing;
            l50.unk30 = 1;
            SpawnObject(&l50);
            unk3144 = 2;
        }
        if (frame < 4) {
            Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0xa && unk3144 > 1) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x133:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a2;
            l50.x = (double)(int)(x - facing * 0x140);
            l50.y = (double)((int)y - 0x140);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.facing = facing;
            l50.unk30 = 1;
            SpawnObject(&l50);
            unk3144 = 2;
        }
        if (frame < 4) {
            Unk410a80(0x32, 0xa);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 0xa && unk3144 > 1) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x134:
        vx = 0.0;
        vy = 0.0;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1a3;
            l50.x = (double)(int)(x - facing * 0x140);
            l50.y = (double)((int)y - 0x140);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.facing = facing;
            l50.unk30 = 1;
            SpawnObject(&l50);
            unk3144 = 2;
            m_playSound = 0x25;
        }
        if (frame < 4) {
            Unk410a80(0x32, 0xa);
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
    case 0x135:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            m_hitsLeft = 1;
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame < 4) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 1) {
            vx = 0.8;
            StartAfterimages(6);
        }
        if (frame >= 0) {
            Unk410a80(0x32, 0xa);
        }
        if (frame > 0 && frame < 3 && m_attackResult == 3) {
            StartAfterimages(0);
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            frame = 3;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x11);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = x;
            (*m_opponent)->y = 0.0;
        }
        if (frame == 4) {
            (*m_opponent)->pattern = 0x79;
            FillBackground(0xb0, 3);
            if (unk3138 == 0) {
                m_comboHits++;
                m_shownHits++;
                l50.type = 0;
                l50.unk2c = 2;
                l50.x = (double)(int)(x + 50.0 - (WORD)Random(0, 0x64));
                l50.y = (double)((WORD)Random(0, 0x64) - 0x64);
                l50.facing = facing;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            unk3138++;
            if (unk3138 == 0xd) {
                unk3138 = 0;
            }
        }
        if (frame > 4 && frame < 8) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                (*m_opponent)->timer = 0;
                (*m_opponent)->pattern = 0x63;
                DealDamage(0x1194, 1000.0);
                if (unkac + 1 != m_game->unk134e) {
                    (*m_opponent)->unk140 = 0x7530;
                }
                if ((*m_opponent)->m_hp <= 0) {
                    l50.type = 0x1ac;
                    l50.x = 0.0;
                    l50.y = 0.0;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.unk0 = 1;
                    l50.unk28 = 0;
                    l50.facing = 1;
                    l50.screen = 1;
                    SpawnObject(&l50);
                    m_playVoice = 4;
                }
            }
            m_attackResult = 0;
            if (frame == 8 && unk3140 < 3) {
                (*m_opponent)->timer = 0;
                frame = 5;
                if ((*m_opponent)->m_hp > 0) {
                    unk3140++;
                }
            }
            if (frame == 8) {
                (*m_opponent)->unk140 = 0;
            }
            if (frame == 3 && unk313c < 0xf) {
                unk313c++;
                frame = 1;
                if (unk313c > 0xe) {
                    pattern = 0;
                    FaceOpponent();
                    StartPattern();
                }
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0;
            StopMoving();
            unk158 = 0;
        }
        if (frame == 2 && timer == 0) {
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
        }
        if (frame >= 0) {
            Unk410a80(0x32, 0xa);
        }
        if (frame == 5 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            (*m_opponent)->pattern = 0x6b;
            if (x > 560.0 && facing == 1) {
                x = 560.0;
            }
            if (x < 80.0 && facing == -1) {
                x = 80.0;
            }
            (*m_opponent)->x = (m_pointX[2] + 0x47) * facing + x;
            (*m_opponent)->y = 0.0;
            pattern = 0x138;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5) {
                m_playVoice = 0x15;
                if ((*m_opponent)->y == 0.0) {
                    m_hitsLeft = 1;
                }
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x138:
        if (frame == 1) {
            (*m_opponent)->x = (m_pointX[2] + 0x3c) * facing + x;
            (*m_opponent)->y = y - 13.0 - m_pointY[2];
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 2) {
            (*m_opponent)->x = (m_pointX[3] + 0x2e) * facing + x;
            (*m_opponent)->y = y - 16.0 - m_pointY[3];
            (*m_opponent)->pattern = 0x6e;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 3) {
            (*m_opponent)->x = (m_pointX[4] + 0x1a) * facing + x;
            (*m_opponent)->y = y - 41.0 - m_pointY[4];
            (*m_opponent)->pattern = 0x6f;
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
        }
        if (frame == 4) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unkc0 = 0.0;
            (*m_opponent)->unkc8 = -2.9;
            (*m_opponent)->pattern = 0x3f;
        }
        if (frame == 0xb && timer == 0) {
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
            m_hitsLeft = 1;
        }
        if (frame > 0x10) {
            unk3138++;
        }
        if (unk3138 == 0x5a || unk3138 == 0x12c) {
            l50.type = 0x1a5;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)(int)(*m_opponent)->y;
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (unk3138 == 0x96 || unk3138 == 0x168) {
            l50.type = 0x1a6;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x40);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (unk3138 == 0xf0 || unk3138 == 0xc8) {
            l50.type = 0x1a7;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x80);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (unk3138 == 0x78 || unk3138 == 0x10e) {
            l50.type = 0x1a8;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)(int)(*m_opponent)->y;
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (unk3138 == 0xb4 || unk3138 == 0x14a) {
            l50.type = 0x1a9;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x50);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (unk3138 == 0xd2 || unk3138 == 0x186) {
            l50.type = 0x1aa;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x7d);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (unk3138 == 0x1f4) {
            l50.type = 0x1ab;
            l50.x = (double)(int)(*m_opponent)->x;
            l50.y = 0.0;
            l50.scale = 0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame < 0x10) {
            Unk410a80(0x32, 3);
        }
        if (frame >= 0x10) {
            (*m_opponent)->Unk410a80(0x32, 3);
        }
        if ((*m_opponent)->pattern == 0x63 && frame < 0x14) {
            timer = 0;
            frame = 0x14;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x14) {
                frame = frame - 3;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            FillBackground(0, 0x28);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.025;
                m_playVoice = 1;
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.facing = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
            }
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                ay = 0.0;
                vx = 0.0;
                StartPattern();
                pattern = 0xd;
                break;
            }
            if (frame >= x8) {
                frame = 1;
            }
        }
    }
}
