// CMisuzu::UpdatePattern (0x50c4b0-0x519dff), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMisuzu's
// .rdata, which starts with its constructor's folder name (misuzu.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMisuzu::UpdatePattern()
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
        vx = 0.8;
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
            FaceOpponent();
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -3.0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 5:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -3.0;
            vx = 0.9;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            m_playSound = 9;
            FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 6:
        if (frame == 0 && timer == 0) {
            FaceOpponent();
            vx = 0.0;
        }
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -3.0;
            vx = -0.9;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 2) {
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
            StopMoving();
            m_playSound = 9;
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xd:
        StopMoving();
        y = 0.0;
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
        ay = 0.048;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 0.0;
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
        ay = 0.048;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = 0.9;
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
        ay = 0.048;
        if (frame == 0 && timer == 0) {
            vy = -3.0;
            vx = -0.9;
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
            vx = 0.3;
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
        timer++;
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
    case 0x67:
        break;
    case 0x6b:
        break;
    case 0x71:
        break;
    case 0x96:
        if (m_inputY == 1) {
            pattern = 0x99;
        }
        if (m_inputY != 1) {
            pattern = 0x96;
        }
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
            l50.y = (double)((int)y - 0x46);
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
        if (frame == 7 && timer == 0) {
            StopMoving();
            l50.type = 9;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x46);
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 3 && timer == 0 && y >= 0.0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == -1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 1.8;
            vy = -1.2;
            ay = 0.01;
            m_playSound = 0x11;
        }
        vy = vy + ay;
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
            vx = 0.5;
            ay = 0.03;
        }
        if (m_inputX != facing && unk3138 >= 0x27) {
            pattern = 9;
            StartPattern();
            vx = 0.5;
            ay = 0.03;
        }
        break;
    case 0xa4:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            StartAfterimages(2);
        }
        if (frame == 3 && timer == 0 && y == 0.0) {
            vx = -1.8;
            vy = -1.3;
            ay = 0.01;
            m_playSound = 0x11;
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 0;
            l50.side = facing == 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        vy = vy + ay;
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
        if (m_inputX != -facing) {
            unk3138 = 0;
        }
        if (unk313c > 0x27 && m_inputX != -facing || unk313c >= 0x78) {
            pattern = 9;
            StartPattern();
            vx = -0.5;
            ay = 0.03;
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3140 == 0) {
            vx = 1.8;
            vy = -0.3;
            m_playSound = 0x11;
            unk3140++;
        }
        vy += 0.01;
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
        if (frame == 0 && timer == 0 && unk3140 == 0) {
            vx = -1.8;
            vy = -0.3;
            m_playSound = 0x11;
            unk3140++;
        }
        vy += 0.01;
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
        if (y + vy > 0.0 && frame < 5) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 5;
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
            if (frame == 5) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
            }
        }
        break;
    case 0xc8:
        vx = 0.0;
        vy = 0.0;
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
        if (frame == 1 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xca:
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
            if (frame < 4) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 4 && timer == 0) {
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
        vx = 0.0;
        vy = 0.0;
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
        vx = 0.0;
        vy = 0.0;
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
            m_gauge = m_gauge + 0xd;
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
                if (m_inputY == 1) {
                    pattern = 3;
                }
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xce:
        vx = 0.0;
        vy = 0.0;
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                l50.type = 0;
                l50.x = (double)((int)x + facing * 0x25);
                l50.y = (double)((int)y - 2);
                l50.scale = 2;
                m_playVoice = 3;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
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
    case 0xcf:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a == 0) {
            pattern = 0xe;
            unk15a++;
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
            if (frame < 5) {
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
            if (frame < 8) {
                m_attackResult = 0;
            }
            if (frame == 7 && unk3138 < 1) {
                frame = frame - 3;
                unk3138++;
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
        }
        if (frame == 1 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.08;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 0) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 6) {
                m_attackResult = 0;
            }
            if (frame == 5) {
                if (y + vy < 0.0) {
                    frame--;
                } else {
                    y = 0.0;
                }
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xd3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.055;
            if (y + vy > 0.0) {
                StopMoving();
                y = 0.0;
                timer = 0;
                frame = 8;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 7) {
                vx = 0.5;
                vy = -1.2;
            }
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
            StopMoving();
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
            (*m_opponent)->pattern = 0x6e;
            (*m_opponent)->unk128 = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x24);
            l50.y = (double)((int)y - 0x2c);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xdd:
        Unk410a80(0x32, 0xa);
        if (frame == 0 && timer == 0) {
            (*m_opponent)->pattern = 0x64;
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x2a + x;
            (*m_opponent)->StartPattern();
        }
        if (frame == 5 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x3b;
            (*m_opponent)->unkc0 = 2.0;
            (*m_opponent)->unkc8 = -1.0;
            (*m_opponent)->ay = 0.035;
            (*m_opponent)->y = -59.0;
            (*m_opponent)->x = facing * 0xf + x;
            (*m_opponent)->unk128 = 1;
            DealDamage(0x4b0, 750.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->facing = -facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x6c;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x24 + x;
            }
            if (frame == 2) {
                (*m_opponent)->pattern = 0x6c;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x23 + x;
            }
            if (frame == 3) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x22 + x;
            }
            if (frame == 4) {
                (*m_opponent)->pattern = 0x68;
                (*m_opponent)->y = -32.0;
                (*m_opponent)->x = x - (facing << 1);
                (*m_opponent)->facing = facing;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
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
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
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
            m_gauge = m_gauge + 0xa;
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
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
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
            m_gauge = m_gauge + 0xa;
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
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xf8:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            StopMoving();
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x40);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x1f + x;
            (*m_opponent)->y = y - 64.0;
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
        if (frame < 4) {
            Unk410a40(0x32, 3);
        }
        if (frame < 4) {
            Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 5) {
            StopMoving();
            y = 0.0;
            StartPattern();
            pattern = 0xd;
            break;
        }
        if (frame == 1) {
            (*m_opponent)->y = y - 64.0;
            (*m_opponent)->x = facing * 0x1e + x;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 64.0;
            (*m_opponent)->x = facing * 0x1d + x;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 96.0;
            (*m_opponent)->x = facing * 0xb + x;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->facing = facing;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->y = y - 39.0;
            (*m_opponent)->x = x - facing * 0x21;
            (*m_opponent)->pattern = 0x3f;
            DealDamage(0x4b0, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->unkc0 = -2.0;
            (*m_opponent)->unkc8 = 0.0;
        }
        if (frame == 7 && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8) {
                facing = -facing;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            l50.type = 0x193;
            l50.x = x;
            l50.y = y - 80.0;
            l50.facing = facing;
            l50.unk0 = 1;
            l50.layer = 1;
            m_playVoice = 1;
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
    case 0xfb:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            l50.type = 0x194;
            l50.x = x;
            l50.y = y - 80.0;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.layer = 1;
            m_playVoice = 1;
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
    case 0xfc:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                StopMoving();
            }
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            l50.type = 0x195;
            l50.x = x;
            l50.y = y - 80.0;
            l50.facing = facing;
            l50.unk0 = 1;
            l50.layer = 1;
            m_playVoice = 1;
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
    case 0xfd:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
                if (unk3138 == 1) {
                    m_gauge = m_gauge + 0xf;
                    l50.type = 0x196;
                    l50.x = facing * 0x1e + x;
                    l50.y = y;
                    l50.facing = facing;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
                if (unk3138 == 1) {
                    m_gauge = m_gauge + 0xf;
                    l50.type = 0x197;
                    l50.x = facing * 0x1e + x;
                    l50.y = y;
                    l50.facing = facing;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                StopMoving();
            }
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 5 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
                if (unk3138 == 1) {
                    m_gauge = m_gauge + 0xf;
                    l50.type = 0x198;
                    l50.x = facing * 0x1e + x;
                    l50.y = y;
                    l50.facing = facing;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
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
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0xf;
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
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0xf;
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
    case 0x102:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                StopMoving();
            }
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0xf;
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
    case 0x103:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            if (y == 0.0) {
                vx = 0.0;
                vy = 0.0;
            }
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 1.2;
            vy = -1.6;
            ay = 0.035;
            m_hitsLeft = 1;
        }
        if (y + vx < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (frame > 8 && y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 0.0;
            frame = 0x11;
            timer = 0;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa) {
                m_playVoice = 9;
            }
            if (frame == 0x11) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            if (y == 0.0) {
                vx = 0.0;
                vy = 0.0;
            }
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 1.4;
            vy = -1.5;
            ay = 0.035;
            m_hitsLeft = 1;
        }
        if (y + vx < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (frame > 8 && y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 0.0;
            frame = 0x11;
            timer = 0;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa) {
                m_playVoice = 9;
            }
            if (frame == 0x11) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            if (y == 0.0) {
                vx = 0.0;
                vy = 0.0;
            }
        }
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
        if (frame == 8 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            vx = 1.8;
            vy = -1.6;
            ay = 0.035;
            m_hitsLeft = 1;
        }
        if (y + vx < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (frame > 8 && y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 0.0;
            frame = 0x11;
            timer = 0;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xa) {
                m_playVoice = 0xa;
            }
            if (frame == 0x11) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x106:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.2;
            vy = -1.3;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (y + vx < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 0.0;
            frame = 9;
            timer = 0;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_playVoice = 9;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.2;
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (y + vx < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 0.0;
            frame = 9;
            timer = 0;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_playVoice = 9;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
        }
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
            vx = 1.8;
            vy = -1.3;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (y + vx < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (y + vy > 0.0) {
            vy = 0.0;
            y = 0.0;
            vx = 0.0;
            frame = 9;
            timer = 0;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                m_playVoice = 0xa;
            }
            if (frame == 9) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x109:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0xc && timer == 0) {
            m_gauge = m_gauge + 0xf;
            l50.type = 0x19d;
            l50.x = x;
            l50.y = y;
            l50.facing = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 6;
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
    case 0x10a:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0xc && timer == 0) {
            m_gauge = m_gauge + 0xf;
            l50.type = 0x1a0;
            l50.x = x;
            l50.y = y;
            l50.facing = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 6;
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
    case 0x10b:
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
        if (frame == 0xc && timer == 0) {
            m_gauge = m_gauge + 0xf;
            l50.type = 0x1a3;
            l50.x = x;
            l50.y = y;
            l50.facing = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 6;
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
    case 0x12c:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_gauge = m_gauge - 0x3e8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (m_attackResult == 6 && frame == 7) {
            StartPattern();
            frame = 8;
            m_attackResult = 0;
            unk14c = 0x9f;
            m_playSound = 3;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
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
            if (frame == 8) {
                frame = 9;
                break;
            }
            if (frame == 9) {
                StartPattern();
                pattern = 0x12f;
                l50.type = 0x1a9;
                l50.x = (double)((int)x - facing * 0xf);
                l50.y = (double)((int)y - 0x2c);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                break;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12d:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_gauge = m_gauge - 0x7d0;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (m_attackResult == 6 && frame == 7) {
            StartPattern();
            frame = 8;
            m_attackResult = 0;
            unk14c = 0x9f;
            m_playSound = 3;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
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
            if (frame == 8) {
                frame = 9;
                break;
            }
            if (frame == 9) {
                StartPattern();
                pattern = 0x12f;
                l50.type = 0x1aa;
                l50.x = (double)((int)x - facing * 0xf);
                l50.y = (double)((int)y - 0x2c);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                break;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12e:
        m_game->Unk4080c0(0xf);
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_gauge = m_gauge - 0xbb8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (m_attackResult == 6 && frame == 7) {
            StartPattern();
            frame = 8;
            m_attackResult = 0;
            unk14c = 0x9f;
            m_playSound = 3;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
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
            if (frame == 8) {
                frame = 9;
                break;
            }
            if (frame == 9) {
                StartPattern();
                pattern = 0x12f;
                l50.type = 0x1ab;
                l50.x = (double)((int)x - facing * 0xf);
                l50.y = (double)((int)y - 0x2c);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                break;
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
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2) {
                y = 0.0;
                vy = -2.9;
                ay = 0.035;
            }
            if (frame == 0xa) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                break;
            }
        }
        if (y + vy > 0.0 && frame > 3 && frame < 0xa) {
            y = 0.0;
            frame = 0xa;
            ay = 0.0;
            StopMoving();
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            unk3138 = (int)(vx * 100.0);
            unk313c = (int)(vy * 100.0);
            unk3140 = (int)(ay * 1000.0);
            StopMoving();
            m_gauge = m_gauge - 0x3e8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0) {
            vx = unk3138 * 0.01;
            vy = unk313c * 0.01;
            ay = unk3140 * 0.001;
            unk3138 = 0;
        }
        if (frame > 5 && frame < 0xb && frame != 8) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && y < 0.0) {
            StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xb;
        }
        if (m_attackResult == 6 && (frame == 7 || frame == 6)) {
            StopMoving();
            StartPattern();
            frame = 8;
            m_attackResult = 0;
            unk14c = 0x9f;
            m_playSound = 3;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x28);
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
            if (frame == 8) {
                if (unk3138 < 1) {
                    frame = 9;
                    break;
                }
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 9) {
                StartPattern();
                pattern = 0x12f;
                l50.type = 0x1a9;
                l50.x = (double)((int)x - facing * 0xf);
                l50.y = (double)((int)y - 0x2c);
                l50.scale = 0;
                l50.layer = 1;
                l50.facing = facing;
                SpawnObject(&l50);
                break;
            }
            if (frame >= x8) {
                pattern = 3;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x133:
        unk158 = 0;
        StopMoving();
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge - 0x3e8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1b4;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            l50.unk30 = 1;
            l50.unk28 = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && unk3138 < 6) {
                unk3138++;
                frame = frame - 3;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x134:
        unk158 = 0;
        StopMoving();
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge - 0x7d0;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1b6;
            l50.x = (double)((int)x + facing * 0x3c);
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 0;
            l50.layer = 1;
            l50.facing = facing;
            l50.unk30 = 1;
            l50.unk28 = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && unk3138 < 5) {
                unk3138++;
                frame = frame - 3;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x135:
        unk158 = 0;
        if (frame > 3) {
            m_game->Unk4080c0(0xf);
        }
        StopMoving();
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge - 0xbb8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x1b8;
            l50.x = (double)((int)x - facing * 0x32);
            l50.y = (double)((int)y + 0xc8);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.unk30 = 1;
            l50.unk28 = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9 && unk3138 < 0xa) {
                unk3138++;
                frame = frame - 3;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x136:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_gauge = m_gauge - 0x3e8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            unk3464++;
            if (unk3464 > 3) {
                unk3464 = 3;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && unk3138 < 1) {
                frame = frame - 4;
                unk3138++;
                break;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x137:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_gauge = m_gauge - 0x7d0;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 9 && timer == 0) {
            unk3464 += 2;
            if (unk3464 > 3) {
                unk3464 = 3;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && unk3138 < 1) {
                frame = frame - 4;
                unk3138++;
                break;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x138:
        unk158 = 0;
        if (frame > 3) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_gauge = m_gauge - 0xbb8;
            Unk410a80(0x32, 0x2d);
            unk14c = 0x78;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame == 9 && timer == 0) {
            unk3464 += 3;
            if (unk3464 > 3) {
                unk3464 = 3;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xf && unk3138 < 1) {
                frame = frame - 4;
                unk3138++;
                break;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x139:
        unk158 = 0;
        if (frame == 2 && timer == 0) {
            StopMoving();
            Unk410a80(0x32, 3);
            unk14c = 0xb4;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3464--;
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
    case 0x13a:
        unk158 = 0;
        if (frame == 2 && timer == 0) {
            StopMoving();
            Unk410a80(0x32, 3);
            unk14c = 0xb4;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3464--;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13b:
        unk158 = 0;
        if (frame == 1 && timer == 0) {
            StopMoving();
            Unk410a80(0x32, 3);
            unk14c = 0xb4;
            FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x39);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk3464--;
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
    case 0x13c:
        unk158 = 0;
        StopMoving();
        if (frame == 0 && timer == 0) {
            l50.type = 0x1c2;
            l50.x = facing * 7 + x;
            l50.y = -42.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
        }
        if (frame > 6 && frame < 0x2a) {
            unk14c = 2;
        }
        if (frame == 7 && timer == 0) {
            m_gauge = m_gauge - 0xbb8;
            Unk410a80(0x32, 0x2d);
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0xa && timer == 0) {
            vy = -0.9;
        }
        if (frame == 0xc && timer == 0) {
            vy = 0.7;
            FillBackground(0xb1, 3);
            m_game->unk1420e = 0x7530;
            (*m_opponent)->m_game->unk1420e = 0x7530;
            m_game->unk1420c = 0x7530;
        }
        if (frame == 0x26) {
            m_game->unk1420e = 0x7530;
            (*m_opponent)->m_game->unk1420e = 0x7530;
            m_game->unk1420c = 0x7530;
        }
        if (frame > 0xb && frame < 0xe && vy + y > 0.0) {
            timer = 0;
            frame = 0xe;
            y = 0.0;
            vy = 0.0;
        }
        if (frame == 0x25 && m_attackResult == 3) {
            frame = 0x26;
            timer = 0;
            (*m_opponent)->pattern = 0x6b;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
            (*m_opponent)->StopMoving();
        }
        if (frame == 0x26 && timer == 0x3c) {
            m_game->FlashWhite(0xf, 0x78, 0x78);
        }
        if (frame == 0x26 && timer == 0x78) {
            l50.type = 0x1c1;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = 1;
            l50.screen = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
        }
        if (frame == 0x29 && timer == 0) {
            m_game->unk1420e = 0;
            (*m_opponent)->m_game->unk1420e = 0;
            m_game->unk1420c = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk3140 < 1) {
                frame = frame - 4;
                unk3140++;
            }
            if (frame == 0xc) {
                if (unk3138 == 5) {
                    m_game->FlashWhite(0xf, 0x2d, 0xb4);
                    m_game->FadeMusic(-0x2710, 0xa);
                }
                if (unk3138 < 0xa) {
                    unk3138++;
                    frame = frame - 2;
                }
            }
            if (frame == 0xe) {
                frame = frame - 2;
            }
            if (frame == 0x25) {
                if (((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x95) && (*m_opponent)->y == 0.0) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame == 0x26) {
                frame = 0x27;
            }
            if (frame == 0x29) {
                x = facing * 0x61 + x;
                ShakeScreen(3, 0);
                l50.type = 3;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                m_playSound = 7;
                m_game->FadeMusic(0, 0x3e8);
            }
            if (frame >= x8) {
                pattern = 0x60;
                StartPattern();
            }
        }
        break;
    case 0x13d:
        unk158 = 0;
        if (frame < 4) {
            (*m_opponent)->timer = 0;
        }
        if (frame == 0 && timer == 0 && unk313c == 0) {
            m_game->FadeMusic(0, 0x14);
            unk313c++;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->unk140 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 4 && unk313c < 0x13) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
    }
}
