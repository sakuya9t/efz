// CIkumi::UpdatePattern and Unk694d00 (0x683550-0x6a59bf): the per-state update, and the second one
// it hands over to while the byte at 0x3460 is 1. They are a file of their own, as in
// the original: their floating-point constants precede the rest of CIkumi's .rdata,
// which starts with its constructor's folder name (ikumi.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CIkumi::UpdatePattern()
{
    WORD x8;
    WORD l4;

    if (unk3460 == 1) {
        Unk694d00();
        return;
    }
    if (unk14a > 0 || (*m_opponent)->unk14c > 0) {
        return;
    }
    EffectDesc l50;
    l4 = (short)anims[pattern].frames[frame].duration;
    x8 = anims[pattern].frameCount;
    CPlayer::InitEffectDesc((EffectDesc*)&l50);
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
        unk158 = 0;
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
            ay = 0.048;
            vy = -2.8;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
            ay = 0.048;
            vy = -2.8;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
            ay = 0.048;
            vy = -2.8;
            vx = -0.9;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
                StartPattern();
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
                StartPattern();
            }
        }
        break;
    case 0xe:
        ay = 0.048;
        unk158 = 0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xf:
        ay = 0.048;
        unk158 = 0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x10:
        ay = 0.048;
        unk158 = 0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if ((char)CPlayer::Unk40ff70() != 0) {
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
            CPlayer::ShakeScreen(3, 0);
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
            CPlayer::ShakeScreen(3, 0);
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            CPlayer::StartAfterimages(1);
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
        vx = 2.5;
        unk158 = 1;
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                break;
            }
        }
        if (m_inputX == facing && unk313c >= 0x50 && frame < 4) {
            pattern = 0xb2;
            StartPattern();
        }
        if (m_inputX != facing && unk3138 >= 0x3c && frame < 4) {
            pattern = 0xb2;
            StartPattern();
        }
        break;
    case 0xa4:
        CPlayer::StartAfterimages(3);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = -1.9;
            vy = -1.0;
            ay = 0.04;
        }
        if (frame > 0 && frame < 4) {
            vy = vy + ay;
        }
        if (frame > 1 && vy + y >= 0.0 && unk3138 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            unk3138++;
            m_playSound = 9;
            frame = 4;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                CPlayer::FaceOpponent();
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 1.3;
            CPlayer::StartAfterimages(3);
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
            vx = 1.6;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -1.3;
            vy = 0.0;
            ay = 0.0;
            CPlayer::StartAfterimages(3);
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
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
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
            CPlayer::FillBackground(0xb0, 3);
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
            CPlayer::FillBackground(0xb0, 3);
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
        CPlayer::StartAfterimages(1);
        vx -= 0.07;
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
            CPlayer::StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 4) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 4;
            m_playSound = 9;
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
            if (frame == 4) {
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
                CPlayer::FaceOpponent();
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                x = facing * 5 + x;
            }
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcb:
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
        if (frame < 2) {
            if (vx > 0.0 && unk158 == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                unk158 = 0;
            }
        }
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.0;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 1) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
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
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xce:
        if (frame < 2) {
            if (vx > 0.0 && unk158 == 1) {
                vx -= 0.03;
            } else {
                vx = 0.0;
                unk158 = 0;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.5;
        }
        if (frame > 4) {
            vx -= 0.035;
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
            if (frame == 5 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
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
            m_gauge = m_gauge + 7;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 7;
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
            if (frame == 1 || frame == 5) {
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
            m_hitsLeft = 3;
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
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -68.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x44);
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
                StartPattern();
            }
        }
        break;
    case 0xdd:
        if (frame < 2) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->unk14a = 0x3c;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x44);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x384, 750.0);
            m_playVoice = 0;
        }
        if (frame == 2 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -1.2;
            (*m_opponent)->unkc8 = -1.0;
            (*m_opponent)->y = -15.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xe6:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        vx -= 0.03;
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
        CPlayer::StartAfterimages(3);
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
        CPlayer::StartAfterimages(1);
        unk158 = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 4 && timer == 0) {
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
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe9:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        vx -= 0.03;
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
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xea:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
        if (m_inputY == -1 && frame > 0 && m_attackResult == 3 && unk15a == 0 && unk15c < 3) {
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
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (frame == 0) {
            vx -= 0.03;
        }
        if (vx < 0.0 && frame == 0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vy = -1.2;
            vx = 1.0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.025;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 0xb;
                y = 0.0;
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 0xb) {
                frame = frame - 2;
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
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x67;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x27);
            l50.y = (double)((int)y - 0x4b);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x27 + x;
            (*m_opponent)->y = y - 75.0;
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
                frame = 1;
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
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 4) {
            CPlayer::StopMoving();
            StartPattern();
            y = 0.0;
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                (*m_opponent)->y = y - 70.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->unk14a = 0x3c;
                l50.type = 0xe;
                l50.unk2c = 4;
                l50.x = (double)((int)x + facing * 0x2a);
                l50.y = (double)((int)y - 0x48);
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5 && unk3138 < 5) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 5) {
                CPlayer::ShakeScreen(4, 0);
                (*m_opponent)->y = y - 40.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = 0x3f;
                CPlayer::DealDamage(0x4b0, 500.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = 0.0;
                ay = 0.035;
                vy = -0.5;
                vx = -2.0;
                l50.type = 0x199;
                l50.x = (double)((int)x + facing * 0x2a);
                l50.y = (double)((int)y - 0x46);
                l50.scale = 2;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                m_playVoice = 5;
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
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x193;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
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
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x193;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xb4);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x193;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
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
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
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
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.1;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x103;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 7) {
                m_attackResult = 2;
            }
            if (frame == 8) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x103;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.2;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x103;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
    case 0x107:
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
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x108;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
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
                StartPattern();
            }
        }
        break;
    case 0x108:
        if (frame == 3 && timer == 0) {
            (*m_opponent)->unk14a = 0x5dc;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0xfa, 1000.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x6c;
            (*m_opponent)->x = facing * 0x28 + x;
            m_playVoice = 4;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1d6;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (frame == 0xc && timer == 0x5a) {
            (*m_opponent)->unk14a = 0;
            l50.type = 0x199;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 2;
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            CPlayer::DealDamage(0xfa, 600.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -0.8;
            (*m_opponent)->unkc8 = -2.8;
            l50.type = 0x1dd;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1dd;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = -facing;
            SpawnObject(&l50);
            m_playVoice = 5;
            CPlayer::ShakeScreen(4, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 2;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
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
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 3;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
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
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.6;
            vy = -1.3;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x112;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x112;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x112:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
    case 0x114:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x116;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x115:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.0;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x116;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x116:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
    case 0x117:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19a;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
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
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19a;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
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
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xb4);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19a;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19c;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19c;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xb4);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19c;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 4 && timer == 0) {
            l50.type = 0x19e;
            l50.x = (double)((int)x - facing * 5);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            CPlayer::ShakeScreen(0xa, 0);
            m_playVoice = 6;
            m_playVoice = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                if (unk3140 < 8) {
                    unk3140++;
                    frame = frame - 2;
                    break;
                }
                pattern = 0;
                StartPattern();
                unk3150 = 0x4ec;
                unk314c = 0xa;
                Unk6ab6a0(1);
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x58);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x130;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x41);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x130:
        if (frame < 0xb) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            l50.type = 0;
            (*m_opponent)->unk14a = 0x1e;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x28) + 0xa) * facing);
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1d6;
            l50.x = (double)((int)(*m_opponent)->x + -5 + (WORD)CPlayer::Random(0, 0xa));
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 0;
            l50.layer = 1;
            if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                l50.unk18 = facing;
            } else {
                l50.unk18 = -facing;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                CPlayer::ShakeScreen(3, 0x1e);
                l50.type = 0x19f;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19f;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = -160.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (unk3138 < 8 && frame == 7) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                CPlayer::DealDamage(0x7d0, 500.0);
                (*m_opponent)->unk14a = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x58);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x132;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x41);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x132:
        if (frame < 0xb) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            l50.type = 0;
            (*m_opponent)->unk14a = 0x1e;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x28) + 0xa) * facing);
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1d6;
            l50.x = (double)((int)(*m_opponent)->x + -5 + (WORD)CPlayer::Random(0, 0xa));
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 0;
            l50.layer = 1;
            if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                l50.unk18 = facing;
            } else {
                l50.unk18 = -facing;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                CPlayer::ShakeScreen(3, 0x1e);
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = -160.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (unk3138 < 0xc && frame == 7) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                CPlayer::DealDamage(0xbb8, 500.0);
                (*m_opponent)->unk14a = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x133:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x58);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x134;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x41);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x134:
        if (frame < 0xb) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame < 0xb) {
            m_game->Unk4080c0(0xf);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            l50.type = 0;
            (*m_opponent)->unk14a = 0x1e;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x28) + 0xa) * facing);
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1de;
            l50.x = (double)((int)(*m_opponent)->x + -5 + (WORD)CPlayer::Random(0, 0xa));
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                CPlayer::ShakeScreen(4, 0x1e);
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = -160.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (unk3138 < 0xc && frame == 7) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                CPlayer::DealDamage(0x1004, 500.0);
                (*m_opponent)->unk14a = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 4);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1a4;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 4);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1a5;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 4);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1a6;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                unk315c = 1;
                m_playVoice = 0xa;
                l50.type = 0x1a7;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
                m_attackResult = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                unk315c = 2;
                m_playVoice = 0xa;
                l50.type = 0x1a7;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
                m_attackResult = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13a:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                unk315c = 3;
                m_playVoice = 0xa;
                l50.type = 0x1a7;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
                m_attackResult = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                unk315c = 0;
                l50.type = 0x1a8;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13c:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                unk315c = 0;
                l50.type = 0x1aa;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13d:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 3 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                unk315c = 0;
                l50.type = 0x1ab;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                l50.type = 0x1a8;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                l50.type = 0x1aa;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x140:
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xb);
            l50.y = (double)((int)y - 0x65);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                l50.type = 0x1ab;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x141:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            m_hitsLeft = 1;
            CPlayer::StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x12);
            l50.y = (double)((int)y - 0x19);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
        }
        m_game->Unk4080c0(0xf);
        if (frame < 4) {
            CPlayer::Unk410a80(0x32, 0xa);
        }
        if (frame == 0xd && m_attackResult == 3) {
            CPlayer::StartAfterimages(0);
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x142;
            unk13e = 3;
            unk140 = 3;
            break;
        }
        if (frame == 0xd && m_attackResult != 3 && m_attackResult > 0) {
            CPlayer::StartAfterimages(0);
            timer = 0;
            frame = 0xe;
            break;
        }
        if (frame == 0xd && timer == 0) {
            vx = 5.0;
        }
        if (frame == 0xe && timer == 0) {
            vx = 1.5;
        }
        if (frame > 3 && vx > 0.0) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x142:
        unk13e = 3;
        if (unk313c == 0) {
            (*m_opponent)->unk140 = 3;
        }
        if (frame == 0 && timer == 0) {
            x = (*m_opponent)->x;
        }
        if ((*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        if (frame < 6) {
            (*m_opponent)->Unk410a80(0x32, 5);
            (*m_opponent)->Unk410a40(0x32, 5);
        }
        if (frame > 5) {
            CPlayer::Unk410a80(0x32, 5);
            CPlayer::Unk410a40(0x32, 5);
        }
        if (frame < 6) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 6 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 6);
            l50.y = (double)((int)y - 0x30);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1af;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0xa0);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1b0;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0x140);
            l50.y = (double)((int)(*m_opponent)->y + 0x78);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = -facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x1b1;
            l50.x = (double)((int)(*m_opponent)->x - facing * 0xa0);
            l50.y = (double)((int)(*m_opponent)->y + 0x118);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1b2;
            l50.x = (double)((int)(*m_opponent)->x + facing * 0xa0);
            l50.y = (double)((int)(*m_opponent)->y + 0x118);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = -facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 0x15 && timer == 0) {
            l50.type = 0x1b3;
            l50.x = (double)((int)x - facing * 0x186);
            l50.y = (double)((int)y - 0x14a);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = facing;
            l50.unk28 = 1;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b4;
            l50.x = (double)((int)x - facing * 0xc3);
            l50.y = (double)((int)y - 0x1ef);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = facing;
            l50.unk28 = 1;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b5;
            l50.x = (double)((int)x + facing * 0x186);
            l50.y = (double)((int)y - 0x14a);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = -facing;
            l50.unk28 = 1;
            l50.layer = 1;
            SpawnObject(&l50);
            l50.type = 0x1b6;
            l50.x = (double)((int)x + facing * 0xc3);
            l50.y = (double)((int)y - 0x1ef);
            l50.scale = 0;
            l50.unk0 = 1;
            l50.unk18 = -facing;
            l50.unk28 = 1;
            l50.layer = 0;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1b7;
            l50.x = (double)((int)x + facing * 0xe);
            l50.y = (double)((int)y + 8);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (frame == 0x16 && unk3138 == 1) {
            frame = 0x17;
            timer = 0;
            unk3138 = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc && unk3138 < 5) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                unk13e = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
    }
}

void CIkumi::Unk694d00()
{
    WORD x8;
    WORD l4;

    if (unk14a > 0 || (*m_opponent)->unk14c > 0) {
        return;
    }
    EffectDesc l50;
    l4 = (short)anims[pattern].frames[frame].duration;
    x8 = anims[pattern].frameCount;
    CPlayer::InitEffectDesc((EffectDesc*)&l50);
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
        unk158 = 0;
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
            ay = 0.048;
            vy = -2.8;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
            ay = 0.048;
            vy = -2.8;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
            ay = 0.048;
            vy = -2.8;
            vx = -0.9;
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
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
                StartPattern();
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
                StartPattern();
            }
        }
        break;
    case 0xe:
        ay = 0.048;
        unk158 = 0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xf:
        ay = 0.048;
        unk158 = 0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x10:
        ay = 0.048;
        unk158 = 0;
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
                StartPattern();
            }
        }
        if (y + vy >= 0.0 && frame > 3) {
            y = 0.0;
            m_playSound = 9;
            CPlayer::FaceOpponent();
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if (frame > 0 && (char)CPlayer::Unk40ff70() != 0) {
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
        if ((char)CPlayer::Unk40ff70() != 0) {
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
            CPlayer::ShakeScreen(3, 0);
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
            CPlayer::ShakeScreen(3, 0);
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
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
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            CPlayer::StartAfterimages(1);
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
        vx = 2.5;
        unk158 = 1;
        timer++;
        unk3138++;
        unk313c++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                break;
            }
        }
        if (m_inputX == facing && unk313c >= 0x50 && frame < 4) {
            pattern = 0xb2;
            StartPattern();
        }
        if (m_inputX != facing && unk3138 >= 0x3c && frame < 4) {
            pattern = 0xb2;
            StartPattern();
        }
        break;
    case 0xa4:
        CPlayer::StartAfterimages(3);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vx = -1.9;
            vy = -1.0;
            ay = 0.04;
        }
        if (frame > 0 && frame < 4) {
            vy = vy + ay;
        }
        if (frame > 1 && vy + y >= 0.0 && unk3138 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            y = 0.0;
            unk3138++;
            m_playSound = 9;
            frame = 4;
            timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 4) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                CPlayer::FaceOpponent();
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = 1.3;
            CPlayer::StartAfterimages(3);
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
            vx = 1.6;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
            vx = 1.3;
            ay = 0.03;
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        break;
    case 0xa6:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            vx = -1.3;
            vy = 0.0;
            ay = 0.0;
            CPlayer::StartAfterimages(3);
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
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != -facing && unk3138 >= 0x28) {
            pattern = 9;
            StartPattern();
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
            CPlayer::FillBackground(0xb0, 3);
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
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
            CPlayer::FillBackground(0xb0, 3);
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
        CPlayer::StartAfterimages(1);
        vx -= 0.07;
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
            CPlayer::StartAfterimages(2);
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (y + vy > 0.0 && frame < 4) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 4;
            m_playSound = 9;
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
            if (frame == 4) {
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
                CPlayer::FaceOpponent();
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                x = facing * 5 + x;
            }
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcb:
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
        if (frame < 2) {
            if (vx > 0.0 && unk158 == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                unk158 = 0;
            }
        }
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
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.0;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 1) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
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
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xce:
        if (frame < 2) {
            if (vx > 0.0 && unk158 == 1) {
                vx -= 0.03;
            } else {
                vx = 0.0;
                unk158 = 0;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.5;
        }
        if (frame > 4) {
            vx -= 0.035;
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
            if (frame == 5 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                if (m_inputY == 1) {
                    pattern = 3;
                }
                CPlayer::FaceOpponent();
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
            m_gauge = m_gauge + 7;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 7;
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
            if (frame == 1 || frame == 5) {
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
            m_hitsLeft = 3;
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
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -68.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x44);
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
                StartPattern();
            }
        }
        break;
    case 0xdd:
        if (frame < 2) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 1 && timer == 0) {
            (*m_opponent)->unk14a = 0x3c;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x19);
            l50.y = (double)((int)y - 0x44);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x384, 750.0);
            m_playVoice = 0;
        }
        if (frame == 2 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -1.2;
            (*m_opponent)->unkc8 = -1.0;
            (*m_opponent)->y = -15.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xe6:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        vx -= 0.03;
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
        CPlayer::StartAfterimages(3);
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
        CPlayer::StartAfterimages(1);
        unk158 = 0;
        vx -= 0.045;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 4 && timer == 0) {
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
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe9:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        vx -= 0.03;
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
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xea:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
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
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (frame == 0) {
            vx -= 0.03;
        }
        if (vx < 0.0 && frame == 0) {
            vx = 0.0;
        }
        if (frame == 1 && timer == 0) {
            vy = -1.2;
            vx = 1.0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y < 0.0) {
            vy += 0.025;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 0xb;
                y = 0.0;
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 0xb) {
                frame = frame - 2;
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
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x67;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x27);
            l50.y = (double)((int)y - 0x4b);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x27 + x;
            (*m_opponent)->y = y - 75.0;
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
                frame = 1;
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
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 4) {
            CPlayer::StopMoving();
            StartPattern();
            y = 0.0;
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                (*m_opponent)->y = y - 70.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = 0x64;
                (*m_opponent)->unk14a = 0x3c;
                l50.type = 0xe;
                l50.unk2c = 4;
                l50.x = (double)((int)x + facing * 0x2a);
                l50.y = (double)((int)y - 0x48);
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 5 && unk3138 < 5) {
                unk3138++;
                frame = frame - 2;
                break;
            }
            if (frame == 5) {
                CPlayer::ShakeScreen(4, 0);
                (*m_opponent)->y = y - 40.0;
                (*m_opponent)->x = facing * 0x2a + x;
                (*m_opponent)->pattern = 0x3f;
                CPlayer::DealDamage(0x578, 500.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->unkc0 = -2.0;
                (*m_opponent)->unkc8 = 0.0;
                ay = 0.035;
                vy = -0.5;
                vx = -2.0;
                l50.type = 0x199;
                l50.x = (double)((int)x + facing * 0x2a);
                l50.y = (double)((int)y - 0x46);
                l50.scale = 2;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                m_playVoice = 5;
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
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x193;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
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
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x193;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xb4);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x193;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
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
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 1;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
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
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.1;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x103;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.4;
            vy = -1.5;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x103;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.2;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x103;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
    case 0x107:
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
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x108;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
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
                StartPattern();
            }
        }
        break;
    case 0x108:
        if (frame == 3 && timer == 0) {
            (*m_opponent)->unk14a = 0x5dc;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0xfa, 1000.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x6c;
            (*m_opponent)->x = facing * 0x28 + x;
            m_playVoice = 4;
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x1d6;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (frame == 0xc && timer == 0x5a) {
            (*m_opponent)->unk14a = 0;
            l50.type = 0x199;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 2;
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
            CPlayer::DealDamage(0x1f4, 700.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->unkc0 = -0.8;
            (*m_opponent)->unkc8 = -2.8;
            l50.type = 0x1dd;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1dd;
            l50.x = (double)((int)x + facing * 0x2b);
            l50.y = (double)((int)y - 0x2e);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = -facing;
            SpawnObject(&l50);
            m_playVoice = 5;
            CPlayer::ShakeScreen(4, 0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 2;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
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
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
            m_hitsLeft = 3;
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vy = 0.0;
            vx = 2.5;
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
        if (frame == 4 && timer == 0) {
            unk3138 = 1;
        }
        if (frame == 0xa && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x191;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 2;
        }
        if (frame > 0xb) {
            vx -= 0.045;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if ((x - (*m_opponent)->x < 150.0 && facing == -1 || (*m_opponent)->x - x < 150.0 && facing == 1) && unk3138 != 0 && frame < 8) {
            timer = 0;
            frame = 8;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk313c < 1) {
                frame = 0;
                unk313c++;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.6;
            vy = -1.3;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x112;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x112;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x112:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
    case 0x114:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.1;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x116;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x115:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
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
        if (frame == 3 && timer == 0) {
            vx = 1.7;
            vy = -1.0;
            ay = 0.025;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0x116;
                break;
            }
        }
        if (frame == 9 && timer == 0) {
            m_playSound = 0x14;
            m_gauge = m_gauge + 0x23;
            l50.type = 0x190;
            l50.x = (double)(int)x;
            l50.y = y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            m_playVoice = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x116:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
    case 0x117:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19a;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
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
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19a;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
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
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xb4);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19a;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19c;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x78);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19c;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x11c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0xb4);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19c;
                SpawnObject(&l50);
                CPlayer::ShakeScreen(2, 0);
            }
            if (frame == 7 && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            m_hitsLeft = 1;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 4 && timer == 0) {
            l50.type = 0x19e;
            l50.x = (double)((int)x - facing * 5);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            CPlayer::ShakeScreen(0xa, 0);
            m_playVoice = 6;
            m_playVoice = 7;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                if (unk3140 < 8) {
                    unk3140++;
                    frame = frame - 2;
                    break;
                }
                pattern = 0;
                StartPattern();
                unk3150 = 0x4ec;
                unk314c = 0xa;
                Unk6ab6a0(1);
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x58);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x130;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x41);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x130:
        if (frame < 0xb) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            l50.type = 0;
            (*m_opponent)->unk14a = 0x1e;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x28) + 0xa) * facing);
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1d6;
            l50.x = (double)((int)(*m_opponent)->x + -5 + (WORD)CPlayer::Random(0, 0xa));
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 0;
            l50.layer = 1;
            if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                l50.unk18 = facing;
            } else {
                l50.unk18 = -facing;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                CPlayer::ShakeScreen(3, 0x1e);
                l50.type = 0x19f;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19f;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = -160.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (unk3138 < 8 && frame == 7) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                CPlayer::DealDamage(0xaf0, 500.0);
                (*m_opponent)->unk14a = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x58);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x132;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x41);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x132:
        if (frame < 0xb) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            l50.type = 0;
            (*m_opponent)->unk14a = 0x1e;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x28) + 0xa) * facing);
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1d6;
            l50.x = (double)((int)(*m_opponent)->x + -5 + (WORD)CPlayer::Random(0, 0xa));
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 0;
            l50.layer = 1;
            if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                l50.unk18 = facing;
            } else {
                l50.unk18 = -facing;
            }
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                CPlayer::ShakeScreen(3, 0x1e);
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a0;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = -160.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (unk3138 < 0xc && frame == 7) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                CPlayer::DealDamage(0xed8, 500.0);
                (*m_opponent)->unk14a = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x133:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x58);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 1 && m_attackResult == 3) {
            vx = 0.0;
            vy = 0.0;
            unkb8 = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            pattern = 0x134;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->y = -84.0;
            CPlayer::Unk410a80(0x32, 0x1e);
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0xd);
            l50.y = (double)((int)y - 0x41);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1 && (*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x134:
        if (frame < 0xb) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame < 0xb) {
            m_game->Unk4080c0(0xf);
        }
        if ((frame == 4 || frame == 6) && timer == 0) {
            l50.type = 0;
            (*m_opponent)->unk14a = 0x1e;
            l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x28) + 0xa) * facing);
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 2;
            m_game->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1de;
            l50.x = (double)((int)(*m_opponent)->x + -5 + (WORD)CPlayer::Random(0, 0xa));
            l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x14));
            l50.scale = 0;
            l50.layer = 1;
            if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                l50.unk18 = facing;
            } else {
                l50.unk18 = -facing;
            }
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->x = facing * 0x1e + x;
                (*m_opponent)->y = y - 87.0;
            }
            if (frame == 2) {
                (*m_opponent)->x = facing * 0x1f + x;
                (*m_opponent)->y = y - 88.0;
            }
            if (frame == 3) {
                m_playVoice = 8;
                CPlayer::ShakeScreen(4, 0x1e);
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = 0.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = -160.0;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (unk3138 < 0xc && frame == 7) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 0xb) {
                (*m_opponent)->x = facing * 0xb + x;
                (*m_opponent)->y = y - 75.0;
            }
            if (frame == 0xc) {
                (*m_opponent)->x = facing * 0xa + x;
                (*m_opponent)->y = y - 74.0;
            }
            if (frame == 0xd) {
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -0.5;
                (*m_opponent)->y = -40.0;
                (*m_opponent)->x = facing * 0x1e + x;
                CPlayer::DealDamage(0x157c, 500.0);
                (*m_opponent)->unk14a = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 4);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1a4;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 5) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 4);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1a5;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 5) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 4);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                l50.type = 0x1a6;
                l50.x = (double)(int)x;
                l50.y = 0.0;
                l50.scale = 1;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 7 && unk3138 < 5) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                unk315c = 1;
                m_playVoice = 0xa;
                l50.type = 0x1a7;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                unk315c = 2;
                m_playVoice = 0xa;
                l50.type = 0x1a7;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13a:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                unk315c = 3;
                m_playVoice = 0xa;
                l50.type = 0x1a7;
                l50.x = (double)((int)x + facing * 0x29);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                unk315c = 0;
                l50.type = 0x1a8;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13c:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                unk315c = 0;
                l50.type = 0x1aa;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13d:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 3 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x1f);
            l50.y = (double)((int)y - 0x34);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                unk315c = 0;
                l50.type = 0x1ab;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                l50.type = 0x1a8;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x13f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                l50.type = 0x1aa;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x19);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x2d);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x140:
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 1 && timer == 0) {
            unk158 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x - facing * 0xb);
            l50.y = (double)((int)y - 0x65);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0xe;
            l50.unk2c = 4;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x3b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                l50.type = 0x1ab;
                l50.x = (double)(int)(*m_opponent)->x;
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x23);
                l50.y = -10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x46);
                l50.y = 0.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x + 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
                l50.type = 0x1a9;
                l50.x = (double)((int)(*m_opponent)->x - 0x28);
                l50.y = 10.0;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                l50.type = 0x1a7;
                l50.layer = 0;
                SpawnObject(&l50);
            }
            if (frame == 0x10 && unk3138 < 6) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
    }
}
