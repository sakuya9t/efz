// CNagamori::UpdatePattern (0x49d610-0x4add8f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CNagamori's
// .rdata, which starts with its constructor's folder name (nagamori.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CNagamori::UpdatePattern()
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
        vx = 1.0;
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
        vx = -1.0;
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
            ay = 0.045;
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
            ay = 0.045;
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
            ay = 0.045;
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
        ay = 0.045;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
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
        ay = 0.045;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = 0.9;
            if (unk158 == 1) {
                vx = 1.4;
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
        ay = 0.045;
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vy = -2.9;
            vx = -0.9;
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
        unk158 = 0;
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
        unk158 = 0;
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
        unk158 = 0;
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
        unk158 = 0;
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
        unk158 = 0;
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
        unk158 = 0;
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
            CPlayer::StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vy = -1.5;
            ay = 0.025;
            m_hitsLeft = 1;
        }
        if (frame == 6 && timer == 0) {
            CPlayer::StopMoving();
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
            if (frame == 0x11) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            CPlayer::StartAfterimages(3);
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
        vx = 1.5;
        unk158 = 1;
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
            pattern = 0xb2;
            StartPattern();
        }
        if (m_inputX != facing && unk3138 >= 0x3c) {
            pattern = 0xb2;
            StartPattern();
        }
        break;
    case 0xa4:
        unk158 = 0;
        CPlayer::StartAfterimages(2);
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            vx = -1.8;
            vy = -0.9;
        }
        if (frame > 1) {
            vy += 0.038;
        }
        if (frame > 2 && vy + y >= 0.0 && unk3138 == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            unk3138++;
            y = 0.0;
            m_playSound = 9;
            timer = 0;
            frame = 0xb;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                CPlayer::FaceOpponent();
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0) {
            vx = 1.8;
            CPlayer::StartAfterimages(3);
            vy = 0.0;
            ay = 0.0;
            if (unk3138 == 0) {
                m_playSound = 0x11;
            }
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
            if (CPlayer::FaceOpponent() != 0) {
                vx = -vx;
            }
        }
        if (m_inputX != facing && unk3138 >= 0x30) {
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
        if (frame == 0 && timer == 0) {
            vx = -1.8;
            vy = 0.0;
            ay = 0.0;
            CPlayer::StartAfterimages(3);
            if (unk3138 == 0) {
                m_playSound = 0x11;
            }
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
        if (m_inputX != -facing && unk3138 >= 0x2a) {
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
            unk158 = 0;
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
        if (frame == 0 && timer == 0 && unk3140 == 0) {
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
            m_playSound = 0x12;
            l50.type = 1;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
                unk3140++;
                if (unk3140 < 5) {
                    frame = 0;
                    break;
                }
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
            CPlayer::StartAfterimages(2);
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
            if (frame == 0xb) {
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
            m_gauge = m_gauge + 0x23;
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
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
            m_hitsLeft = 6;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x194;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
            Unk4ae1d0((int)x, -0xa, 0x5a, 0x32);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
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
            if (frame == 4 && unk3138 < 3) {
                frame = 2;
                unk3138++;
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
            if (frame < 4) {
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
            if (frame < 4) {
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
            m_attackResult = 0;
            if (frame == 5) {
                if (y + vy < 0.0) {
                    frame--;
                } else {
                    y = 0.0;
                }
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xd8:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk158 = 0;
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x14;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.5;
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
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
            CPlayer::StopMoving();
            break;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            vy = 0.0;
            CPlayer::ShakeScreen(3, 0);
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
    case 0xd7:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 || frame == 4) {
            vy = vy + ay;
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (vy + y > 0.0) {
                frame = 5;
                timer = 0;
                CPlayer::ShakeScreen(3, 0);
                l50.type = 3;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                m_playSound = 7;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -0.8;
                ay = 0.035;
            }
            if (frame == 5) {
                frame = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = 0xdd;
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
        if (frame == 0 && timer == 1) {
            (*m_opponent)->unk140 = 0x2710;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = facing * 0x23 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
        }
        if (frame == 5 && timer == 0x2d) {
            frame = 6;
            timer = 0;
            break;
        }
        if (frame == 6 && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            unk313c = 0;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x18);
            l50.scale = 2;
            l50.unk2c = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x4b, 1000.0);
        }
        if (frame == 0xa && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x18);
            l50.scale = 2;
            l50.unk2c = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->unk140 = 0;
            CPlayer::DealDamage(0x320, 750.0);
            (*m_opponent)->pattern = 0x61;
            (*m_opponent)->StartPattern();
        }
        if (frame > 0xe) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                pattern = 0xd;
                StartPattern();
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x71;
                if (facing == 1 && x + 20.0 < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-0x11 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 7 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 0xe) {
                vx = -0.7;
                vy = -1.7;
                ay = 0.037;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xe6:
        CPlayer::StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 1.9;
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.9;
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
            if (frame < 4) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe8:
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
        unk158 = 0;
        CPlayer::StartAfterimages(3);
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 1.9;
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
            if (frame < 4) {
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
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            vx = 1.9;
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
    case 0xea:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            vx = 1.1;
            vy = -1.2;
            ay = 0.034;
        }
        if (frame == 6 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            m_playSound = 0x14;
        }
        vy = vy + ay;
        if (y + vy > 0.0) {
            pattern = 0xd;
            y = 0.0;
            StartPattern();
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 9) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xeb:
        CPlayer::StartAfterimages(3);
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 3 || frame == 4) {
            vy = vy + ay;
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (vy + y > 0.0) {
                m_hitsLeft = 1;
                frame = 5;
                timer = 0;
                CPlayer::ShakeScreen(3, 0);
                vx *= 0.3;
                l50.type = 3;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 0;
                m_game->CreateEffect((EffectDesc*)&l50);
                m_playSound = 7;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.5;
                vy = -0.8;
                ay = 0.035;
            }
            if (frame == 5) {
                frame = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
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
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x31);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x1d + x;
            (*m_opponent)->y = y - 49.0;
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
        if (frame < 6) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 6) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0 && frame > 5) {
            CPlayer::StopMoving();
            y = 0.0;
            StartPattern();
            pattern = 0xd;
            break;
        }
        if (frame == 2) {
            (*m_opponent)->y = y - 69.0;
            (*m_opponent)->x = facing * 0x21 + x;
            (*m_opponent)->pattern = 0x65;
        }
        if (frame == 3) {
            (*m_opponent)->y = y - 71.0;
            (*m_opponent)->x = facing * 0xb + x;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 4) {
            (*m_opponent)->y = y - 49.0;
            (*m_opponent)->x = facing * 0x1a + x;
            (*m_opponent)->pattern = 0x65;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 5) {
            (*m_opponent)->y = y - 46.0;
            (*m_opponent)->x = facing * 0x19 + x;
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6) {
            (*m_opponent)->y = y - 72.0;
            (*m_opponent)->x = x + 0.0;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 && timer == 0) {
            (*m_opponent)->y = y - 40.0;
            (*m_opponent)->x = x - facing * 0x14;
            (*m_opponent)->pattern = 0x3f;
            CPlayer::DealDamage(0x4b0, 500.0);
            (*m_opponent)->StartPattern();
            (*m_opponent)->unkc0 = -2.0;
            (*m_opponent)->unkc8 = 0.0;
        }
        if (frame == 8 && timer == 0) {
            ay = 0.035;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                facing = -facing;
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
            m_hitsLeft = 1;
            if (y < 0.0) {
                frame = 1;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0x1e;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            Unk4ae1d0((int)x + facing * 0x33, (int)y - 0x3f, 0x24, 0x50);
        }
        if (frame == 6 && vy + y > 0.0) {
            timer = 0;
            y = 0.0;
            frame = 7;
            CPlayer::StopMoving();
            break;
        }
        if (frame > 1) {
            vy = vy + ay;
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
    case 0xfb:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 2;
            if (y < 0.0) {
                frame = 1;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            Unk4ae1d0((int)x + facing * 0x33, (int)y - 0x3f, 0x24, 0x50);
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            Unk4ae1d0((int)x + facing * 0x33, (int)y - 0x3f, 0x24, 0x50);
        }
        if (frame == 0xa && vy + y > 0.0) {
            timer = 0;
            y = 0.0;
            frame = 0xb;
            CPlayer::StopMoving();
            break;
        }
        if (frame > 1) {
            vy = vy + ay;
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
                StartPattern();
            }
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
            l50.x = (double)((int)x + facing * 0x14);
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 3;
            CPlayer::StopMoving();
            if (y < 0.0) {
                frame = 1;
            }
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            Unk4ae1d0((int)x + facing * 0x33, (int)y - 0x3f, 0x24, 0x50);
        }
        if (frame == 5 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = 1.1;
            vy = -2.2;
            ay = 0.05;
            Unk4ae1d0((int)x + facing * 0x33, (int)y - 0x3f, 0x24, 0x50);
        }
        if (frame == 0xb && timer == 0) {
            m_gauge = m_gauge + 0xf;
            vx = 1.1;
            vy = -2.8;
            ay = 0.05;
        }
        if ((frame == 0x15 || frame == 0x14) && vy + y > 0.0) {
            timer = 0;
            y = 0.0;
            frame = 0x16;
            CPlayer::StopMoving();
            break;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0xe) {
                m_attackResult = 0;
            }
            if (frame == 0x16 && y < 0.0) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            vx = -0.9;
            vy = -2.1;
            ay = 0.07;
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0xa);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            vx = -0.9;
            vy = -2.1;
            ay = 0.05;
            m_playVoice = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            unk3160++;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 1;
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
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 1;
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
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            l50.type = 0x197;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 1;
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
    case 0x104:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            m_playVoice = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
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
            pattern = 0x107;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            m_playVoice = 1;
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
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
            pattern = 0x107;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x106:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            m_playVoice = 1;
            l50.type = 0x198;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
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
            pattern = 0x107;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x107:
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
    case 0x109:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            unk3138 = 2;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
            m_playVoice = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 8) {
                if (unk3138 > 1) {
                    unk3138--;
                    frame = 1;
                } else {
                    pattern = 0;
                    StartPattern();
                    CPlayer::FaceOpponent();
                }
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            vx = -0.9;
            vy = -2.1;
            ay = 0.04;
            m_playVoice = 1;
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x10b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk3154 = 0;
        }
        if (frame == 5 && timer == 0 && unk3138 == 0) {
            m_playSound = 0x20;
            unk3148 = 1;
            l50.unk0 = 1;
            l50.type = 0x19b;
            l50.x = (double)((int)x + facing * 0x21);
            l50.y = (double)((int)y - 0x38);
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
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
    case 0x10c:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            unk3154 = 0;
        }
        if (frame == 4 && timer == 0 && unk3138 == 0) {
            m_playSound = 0x20;
            unk3148 = 1;
            l50.unk0 = 1;
            l50.type = 0x19c;
            l50.x = (double)((int)x + facing * 0x21);
            l50.y = (double)((int)y - 0x38);
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
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
    case 0x10d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            unk3154 = 0;
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
        if (frame == 5 && timer == 0 && unk3138 == 0) {
            m_playSound = 0x20;
            unk3148 = 1;
            l50.unk0 = 1;
            l50.type = 0x19d;
            l50.x = (double)((int)x + facing * 0x21);
            l50.y = (double)((int)y - 0x38);
            l50.unk18 = facing;
            l50.layer = 1;
            SpawnObject(&l50);
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
    case 0x10e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 2;
        }
        if (frame > 3 && frame < 6) {
            vy = vy + ay;
            if (y < 0.0) {
                Unk4ae1d0((int)x - facing * 0x22, (int)y - 0x42, 0x27, 0x2a);
            }
            if (vy + y > 0.0) {
                y = 0.0;
                frame = 6;
                timer = 0;
                CPlayer::StopMoving();
                m_playSound = 0x23;
                Unk4ae1d0((int)x + facing * 0x27, (int)y - 0x23, 0x46, 0x4b);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.5;
                vy = -1.4;
                ay = 0.09;
            }
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10f:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 2;
        }
        if (frame > 3 && frame < 6) {
            vy = vy + ay;
            if (y < 0.0) {
                Unk4ae1d0((int)x - facing * 0x22, (int)y - 0x42, 0x27, 0x2a);
            }
            if (vy + y > 0.0) {
                y = 0.0;
                frame = 6;
                timer = 0;
                CPlayer::StopMoving();
                m_playSound = 0x23;
                unk3160++;
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x1e);
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
                l50.type = 0x19e;
                SpawnObject(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 7) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 0.8;
                vy = -3.3;
                ay = 0.09;
            }
            if (frame == 3 || frame == 7) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                frame = frame - 2;
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
        if (frame == 2 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
        }
        if (frame > 3 && frame < 6) {
            vy = vy + ay;
            if (y < 0.0) {
                Unk4ae1d0((int)x - facing * 0x22, (int)y - 0x42, 0x27, 0x2a);
            }
            if (vy + y > 0.0) {
                y = 0.0;
                frame = 6;
                timer = 0;
                CPlayer::StopMoving();
                m_playSound = 0x23;
                m_hitsLeft = 1;
                unk3160++;
                l50.type = 0x190;
                l50.x = (double)((int)x + facing * 0x32);
                l50.y = (double)((int)y - 0x1e);
                l50.unk18 = facing;
                l50.layer = 1;
                l50.scale = 2;
                SpawnObject(&l50);
                l50.type = 0x19e;
                SpawnObject(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.8;
                vy = -1.0;
                ay = 0.03;
            }
            if (frame == 6) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x113:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            vx = -0.9;
            vy = -1.5;
            ay = 0.05;
            m_playVoice = 1;
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x114:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            vx = -0.9;
            vy = -1.5;
            ay = 0.05;
            m_playVoice = 1;
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x115:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge - 0x32;
            vx = -0.9;
            vy = -1.5;
            ay = 0.05;
            m_playVoice = 1;
            l50.type = 0x198;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.layer = 1;
            l50.scale = 2;
            SpawnObject(&l50);
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
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
        break;
    case 0x116:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 2 && timer == 0) {
            unk3154 = 1;
            m_playVoice = 4;
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
        if (frame == 2 && timer == 0) {
            unk3154 = -1;
            m_playVoice = 3;
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
    case 0x118:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 4 && timer == 0) {
            unk3154 = 2;
            m_playVoice = 3;
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
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            pattern = 0x12f;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            break;
        }
        if (frame > 2 && m_attackResult == 2) {
            timer = 0;
            frame = 0xb;
            m_attackResult = 0;
        }
        if (frame == 0xc && timer == 0) {
            CPlayer::ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
        }
        if (frame > 0xa) {
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 2.0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            pattern = 0x130;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            break;
        }
        if (frame > 2 && m_attackResult == 2) {
            timer = 0;
            frame = 0x13;
            m_attackResult = 0;
        }
        if (frame == 0x14 && timer == 0) {
            CPlayer::ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
        }
        if (frame > 0x12) {
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 2.0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            pattern = 0x131;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x2a);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            break;
        }
        if (frame > 2 && m_attackResult == 2) {
            timer = 0;
            frame = 0x13;
            m_attackResult = 0;
        }
        if (frame == 0x14 && timer == 0) {
            CPlayer::ShakeScreen(3, 0);
            l50.type = 3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 0;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 7;
        }
        if (frame > 0x12) {
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 2.0;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x12f:
        if (frame == 0) {
            (*m_opponent)->unk140 = 0x7530;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = facing * 0x23 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
            unk3138 = 8;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = 0x71;
            if (facing == 1 && x < 40.0) {
                x = 40.0;
            }
            if (facing == -1 && x > 620.0) {
                x = 620.0;
            }
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
        }
        if (frame < 2) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        } else {
            vx = 0.0;
        }
        unkf2 = 3;
        if (frame == 6 && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x64, 980.0);
        }
        if (frame == 9 && timer == 0) {
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 0x16;
            CPlayer::ShakeScreen(0xa, 0xa);
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->unk140 = 0;
            CPlayer::DealDamage(0x7d0, 800.0);
            (*m_opponent)->pattern = 0x62;
            (*m_opponent)->StartPattern();
            (*m_opponent)->unk14a = 0xb4;
        }
        if (frame > 0xb) {
            (*m_opponent)->pattern = 0x63;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
        }
        if (frame > 0xe) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                pattern = 0xd;
                StartPattern();
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x71;
                if (facing == 1 && x < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-0x11 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 6 && unk3138 == 0) {
                frame = 7;
            }
            if (frame == 7) {
                if (unk3138 > 0) {
                    frame = frame - 2;
                    unk3138--;
                } else {
                    unk3138 = 0x14;
                }
            }
            if (frame == 0xe) {
                vx = -1.0;
                vy = -1.7;
                ay = 0.037;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x130:
        if (frame == 0) {
            (*m_opponent)->unk140 = 0x7530;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = facing * 0x23 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
            unk3138 = 8;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = 0x71;
            if (facing == 1 && x < 40.0) {
                x = 40.0;
            }
            if (facing == -1 && x > 620.0) {
                x = 620.0;
            }
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
        }
        if (frame < 2) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        } else {
            vx = 0.0;
        }
        unkf2 = 3;
        if (frame == 6 && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x64, 990.0);
        }
        if (frame == 0xa && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x64, 990.0);
        }
        if (frame == 0xf && timer == 0) {
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 0x16;
            CPlayer::ShakeScreen(0xa, 0xa);
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x7d0, 800.0);
            (*m_opponent)->unk140 = 0;
            (*m_opponent)->pattern = 0x62;
            (*m_opponent)->StartPattern();
            (*m_opponent)->unk14a = 0xb4;
        }
        if (frame > 0x13) {
            (*m_opponent)->pattern = 0x63;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
        }
        if (frame > 0x13) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                pattern = 0xd;
                StartPattern();
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x71;
                if (facing == 1 && x < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-0x11 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 6 && unk3138 == 0) {
                frame = 7;
            }
            if (frame == 7) {
                if (unk3138 > 0) {
                    frame = frame - 2;
                    unk3138--;
                } else {
                    unk3138 = 0x14;
                }
            }
            if (frame == 0xc) {
                if (unk3138 > 0) {
                    frame = frame - 5;
                    unk3138--;
                } else {
                    unk3138 = 3;
                }
            }
            if (frame == 0x13) {
                vx = -1.0;
                vy = -1.7;
                ay = 0.037;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x131:
        m_game->Unk4080c0(0xf);
        if (frame == 0) {
            (*m_opponent)->unk140 = 0x7530;
            m_hitsLeft = 1;
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = facing * 0x23 + x;
            (*m_opponent)->y = -35.0;
            m_attackResult = 0;
            unk3138 = 8;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = 0x71;
            if (facing == 1 && x < 40.0) {
                x = 40.0;
            }
            if (facing == -1 && x > 620.0) {
                x = 620.0;
            }
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
        }
        if (frame < 2) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        } else {
            vx = 0.0;
        }
        unkf2 = 3;
        if (frame == 6 && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x64, 990.0);
        }
        if (frame == 0xa && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x64, 990.0);
        }
        if (frame == 0xf && timer == 0) {
            (*m_opponent)->unk14a = 0x1e;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x96, 990.0);
        }
        if (frame == 0x14 && timer == 0) {
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk2c = 0x16;
            CPlayer::ShakeScreen(0xa, 0xa);
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x9c4, 800.0);
            (*m_opponent)->unk140 = 0;
            (*m_opponent)->pattern = 0x62;
            (*m_opponent)->StartPattern();
            (*m_opponent)->unk14a = 0xb4;
        }
        if (frame > 0x18) {
            (*m_opponent)->pattern = 0x63;
            (*m_opponent)->frame = 0;
            (*m_opponent)->timer = 0;
        }
        if (frame > 0x18) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                pattern = 0xd;
                StartPattern();
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x71;
                if (facing == 1 && x < 40.0) {
                    x = 40.0;
                }
                if (facing == -1 && x > 620.0) {
                    x = 620.0;
                }
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                x = (*m_opponent)->x + (-0x11 - (*m_opponent)->m_pointX[1]) * facing;
            }
            if (frame == 6 && unk3138 == 0) {
                frame = 7;
            }
            if (frame == 7) {
                if (unk3138 > 0) {
                    frame = frame - 2;
                    unk3138--;
                } else {
                    unk3138 = 0x14;
                }
            }
            if (frame == 0xc) {
                if (unk3138 > 0) {
                    frame = frame - 5;
                    unk3138--;
                } else {
                    unk3138 = 3;
                }
            }
            if (frame == 0x11 && unk3138 > 0) {
                frame = frame - 5;
                unk3138--;
            }
            if (frame == 0x18) {
                vx = -1.0;
                vy = -1.7;
                ay = 0.037;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x132:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 1;
            l50.unk0 = 0;
            l50.type = 0x193;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
        }
        if (0) {}
        if (0) {}
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
    case 0x133:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 2 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 3 && timer == 0) {
            m_playVoice = 1;
            l50.unk0 = 0;
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x1e);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (0) {}
        if (0) {}
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
    case 0x134:
        unk158 = 0;
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x - (facing << 5));
            l50.y = (double)((int)y - 0x4b);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && timer == 0) {
            m_playVoice = 1;
            l50.unk0 = 1;
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x32);
            l50.y = (double)((int)y - 0x3c);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (0) {}
        if (0) {}
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
    case 0x135:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.05;
                m_playVoice = 1;
                l50.type = 0x193;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.unk18 = facing;
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
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0x17);
            l50.y = (double)((int)y - 0x1e);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
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
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                vx = -0.9;
                vy = -2.1;
                ay = 0.05;
                m_playVoice = 1;
                l50.type = 0x192;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.unk18 = facing;
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
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
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
                ay = 0.05;
                m_playVoice = 1;
                l50.type = 0x191;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.unk18 = facing;
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
        break;
    case 0x138:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (unk313c == 0x2d) {
            l50.unk0 = 1;
            l50.type = 0x1bf;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.unk18 = facing;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
        }
        unk313c++;
        if (frame == 6 && timer == 0) {
            unk14c = 0xa0;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 7 && timer == 0) {
            m_playVoice = 0;
            m_game->FlashWhite(0x14, 0xf, 0xa);
            unk14c = 0x12c;
        }
        if (frame == 8 && timer == 0) {
            if (unk3140 == 0) {
                unk14c = 0x4b0;
                CPlayer::FillBackground(0xb1, 3);
                l50.unk0 = 1;
                l50.type = 0x1a1;
                l50.x = (double)((int)x + facing * 0x1e);
                l50.y = (double)((int)y - 0x1e);
                l50.unk18 = facing;
                l50.scale = 0;
                l50.layer = 0;
                l50.unk30 = 1;
                m_playVoice = 2;
                SpawnObject(&l50);
            }
            if (unk3140 == 5) {
                (*m_opponent)->pattern = 0x3b;
                (*m_opponent)->unk128 = 1;
                (*m_opponent)->StartPattern();
            }
            unk3140++;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && unk3138 == 0) {
                frame = frame - 2;
            }
            if (frame == 4 && unk3138 == 1) {
                frame = frame - 2;
            }
            if (frame == 6 && unk3138 < 0xc) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 0xa && unk3138 < 0x18) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame >= x8) {
                unk3150 = 0x4b0;
                CPlayer::FillBackground(0xb1, 3);
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x139:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 5 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x73);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0) {
            CPlayer::ShakeScreen(0xa, 5);
            l50.type = 0x1c2;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1c5;
            l50.unk0 = 0;
            SpawnObject(&l50);
            unk314c = 1;
            Unk4ae1d0((int)x, (int)y, 0x3e8, 0x3e8);
            m_playVoice = 1;
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
    case 0x13a:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 5 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x73);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0) {
            CPlayer::ShakeScreen(0xa, 5);
            l50.type = 0x1c3;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1c5;
            l50.unk0 = 0;
            SpawnObject(&l50);
            unk314c = 1;
            Unk4ae1d0((int)x, (int)y, 0x3e8, 0x3e8);
            m_playVoice = 1;
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
    case 0x13b:
        if (frame == 0 && timer == 0) {
            unk158 = 0;
            CPlayer::StopMoving();
        }
        if (frame == 5 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x73);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 6 && timer == 0) {
            CPlayer::ShakeScreen(0xa, 5);
            l50.type = 0x1c4;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
            l50.type = 0x1c5;
            l50.unk0 = 0;
            SpawnObject(&l50);
            unk314c = 1;
            Unk4ae1d0((int)x, (int)y, 0x3e8, 0x3e8);
            m_playVoice = 1;
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
    }
}
