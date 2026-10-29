// CMayu::UpdatePattern (0x5c8580-0x5dddef), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMayu's
// .rdata, which starts with its constructor's folder name (mayu.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMayu::UpdatePattern()
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
        vx = 0.9;
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
        vx = -0.9;
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
            ay = 0.055;
            vy = -2.8;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
            CPlayer::FaceOpponent();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.055;
            vy = -2.8;
            vx = 1.0;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
            CPlayer::FaceOpponent();
            vx = 0.0;
        }
        if (frame == 3 && timer == 0) {
            ay = 0.055;
            vy = -2.8;
            vx = -1.0;
            m_playVoice = 1;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
    case 0xa:
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
            m_playSound = 9;
            pattern = 0xd;
            StartPattern();
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
                StartPattern();
            }
        }
        break;
    case 0xe:
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 0.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = 1.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        ay = 0.055;
        if (frame == 0 && timer == 0) {
            vy = -3.2;
            vx = -1.0;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 4;
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
        if (frame < 9) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vy = -1.8;
                ay = 0.05;
            }
            if (frame == 9) {
                frame = frame - 4;
            }
            if (frame < 9 && frame > 4 && y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                frame = 9;
            }
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
            CPlayer::Unk410a10(3, 0);
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
            CPlayer::Unk410a10(3, 0);
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
        if (m_hp > 0 && timer > 0x45 && frame == 0) {
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
        if (frame == 3 && timer == 0) {
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
            if (frame == 0xc) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case 0xa3:
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            ay = 0.0;
        }
        vy = vy + ay;
        if (frame == 6) {
            vx -= 0.05;
            if (vx < 0.5) {
                vx = 0.5;
            }
        }
        if (frame == 2 && timer == 0) {
            vx = 2.5;
            vy = -1.6;
            ay = 0.05;
        }
        if (frame == 6 && timer == 0) {
            ay = 0.08;
        }
        if (y + vy > 0.0) {
            pattern = 0xb2;
            StartPattern();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 6) {
                if (m_inputX == -facing) {
                    ay = 0.08;
                    break;
                }
                unk3138++;
                if (unk3138 < 7) {
                    frame = frame - 2;
                    unk3138++;
                }
            }
        }
        break;
    case 0xa4:
        if (frame == 0 && timer == 0) {
            CPlayer::Unk4109d0(2);
            vx = 0.0;
            vy = 0.0;
        }
        if (frame > 0) {
            vx += 0.055;
        }
        if (vx > 0.0) {
            vx = 0.0;
        }
        if (y + vy > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            StartPattern();
            pattern = 0xd;
            break;
        }
        vy = vy + ay;
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = -3.5;
                vy = -1.5;
                ay = 0.05;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0) {
            vx = 1.8;
            CPlayer::Unk4109d0(3);
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
            CPlayer::Unk4109d0(3);
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
        if (m_inputX != -facing && unk3138 >= 0x30) {
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
            if (ay == 0.0) {
                ay = 0.035;
            }
            if (unk120 == 1) {
                m_proration = unk118 * 5.0 + m_proration;
            }
            unk118 = 0.0;
            unk14c = 0x5a;
            CPlayer::Unk410b10(0xb0, 3);
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
                if (ay == 0.0) {
                    ay = 0.035;
                }
                StartPattern();
            }
        }
        break;
    case 0xb2:
        vx -= 0.08;
        if (vx < 0.0) {
            vx = 0.0;
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
        if (y + vy > 0.0 && frame < 0xc) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
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
            if (frame == 0xc) {
                frame = frame - 4;
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
                CPlayer::FaceOpponent();
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
    case 0xca:
        vx -= 0.02;
        if (vx <= 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (frame == 2 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
            vx = 1.2;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 2;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x14;
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
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xcd:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
        if (vx > 0.0) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                vx = 1.5;
            }
            if (frame == 6 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
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
                StartPattern();
            }
        }
        break;
    case 0xce:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            m_gauge = m_gauge + 0x19;
            vx = 3.0;
        }
        if (frame > 1) {
            vx -= 0.07;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if (vx == 0.0) {
                m_hitsLeft = 0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                m_playSound = 0x14;
                m_hitsLeft = 1;
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 1) {
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
                StartPattern();
                pattern = 9;
            }
        }
        break;
    case 0xd0:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 1) {
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
            m_gauge = m_gauge + 0xd;
            m_hitsLeft = 1;
            m_playSound = 0x14;
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
            if (frame < 2) {
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 1) {
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
        if (frame == 4 && timer == 0) {
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
        if (vx <= 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 5;
                break;
            }
        }
        if (frame > 4) {
            vx -= 0.036;
            if (vx < 0.0) {
                vx = 0.0;
            }
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
            if (frame == 1) {
                vx = 1.0;
                vy = -2.6;
                ay = 0.065;
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
    case 0xd3:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
            if (frame < 2) {
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
    case 0xdc:
        vx = 0.0;
        vy = 0.0;
        if (frame == 1 && m_attackResult == 3) {
            CPlayer::StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = 0xdd;
            (*m_opponent)->pattern = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x25);
            l50.y = (double)((int)y - 0x30);
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
            if (frame == 1 && timer == 0 && (*m_opponent)->y == 0.0) {
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
    case 0xdd:
        if (frame == 0 && timer == 0) {
            x = (*m_opponent)->x - (*m_opponent)->unk2ad0[0] * facing;
            y = (*m_opponent)->unk2af8[0] + 0x1e;
        }
        if (frame == 3 && timer == 0) {
            (*m_opponent)->pattern = 0x3b;
            (*m_opponent)->StartPattern();
            (*m_opponent)->unkc0 = -2.5;
            (*m_opponent)->unkc8 = -1.0;
            (*m_opponent)->ay = 0.035;
            vx = -1.8;
            vy = -1.9;
            ay = 0.04;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x2d);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::DealDamage(0x3e8, 750.0);
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xe6:
        vy = vy + ay;
        CPlayer::Unk4109d0(3);
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 1) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xe9;
            StartPattern();
            frame = 2;
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
                pattern = 0xa;
                StartPattern();
            }
        }
        break;
    case 0xe7:
        vy = vy + ay;
        CPlayer::Unk4109d0(3);
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 1) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xd;
            m_hitsLeft = 2;
            m_playSound = 0x14;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xe9;
            StartPattern();
            frame = 1;
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
                pattern = 0xa;
                StartPattern();
            }
        }
        break;
    case 0xe8:
        vy = vy + ay;
        CPlayer::Unk4109d0(3);
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 1) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.5;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 0xa;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (y + vy >= 0.0) {
            y = 0.0;
            pattern = 0xe9;
            StartPattern();
            frame = 1;
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
                pattern = 0xa;
                StartPattern();
            }
        }
        break;
    case 0xe9:
        vx = 0.0;
        vy = 0.0;
        CPlayer::FaceOpponent();
        timer++;
        if (timer >= l4) {
            timer = 0;
            m_attackResult = 3;
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
    case 0xf8:
        vy = vy + ay;
        if (frame == 2 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->unk128 = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x36);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            frame = 0;
            timer = 0;
            pattern = 0xf9;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 2 && (*m_opponent)->y < 0.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x95)) {
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
        if (frame < 0xb) {
            if (x > 6100.0 && facing == 1) {
                x = 6100.0;
                vx = 0.0;
            }
            if (x < 30.0 && facing == -1) {
                x = 30.0;
                vx = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame < 0xa || frame > 0xb && frame < 0xf) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xa) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    CPlayer::DealDamage(0x3e8, 500.0);
                    l50.type = 0;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    timer = 0;
                    frame = 0xa;
                    m_playSound = 2;
                    break;
                }
                if (frame == 0xe) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    timer = 0;
                    frame = 0xf;
                    break;
                }
            }
        }
        if (frame < 1) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 1) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 2) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 3) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 4) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xa) {
                frame = frame - 8;
            }
            if (frame == 0xc) {
                vx = -0.8;
                vy = -1.0;
                ay = 0.035;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 0;
        }
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x6b;
            StartPattern();
            pattern = 0xfd;
            y = unk2af8[0] + 0x32;
            x = (*m_opponent)->x + (-unk2ad0[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 8) {
            if ((*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
        }
        if (frame == 6) {
            unk3140 = 1;
        }
        if (frame > 7) {
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
            if (frame == 1) {
                m_hitsLeft = 0;
            }
            if (frame == 3) {
                vx = 1.8;
            }
            if (frame == 8) {
                frame = 3;
                unk3138++;
            }
            if (frame == 6 && unk3138 > 1) {
                frame = 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 0;
        }
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x6b;
            StartPattern();
            pattern = 0xfd;
            y = unk2af8[0] + 0x32;
            x = (*m_opponent)->x + (-unk2ad0[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 8 && unk3140 > 0) {
            if ((*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
        }
        if (frame == 6) {
            unk3140 = 1;
        }
        if (frame > 7) {
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
            if (frame == 1) {
                m_hitsLeft = 0;
            }
            if (frame == 3) {
                vx = 2.4;
            }
            if (frame == 8) {
                frame = 3;
                unk3138++;
            }
            if (frame == 6 && unk3138 > 2) {
                frame = 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0;
            CPlayer::StopMoving();
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
        if (frame > 2 && frame < 8 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x6b;
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0xfe;
            y = unk2af8[0] + 0x32;
            x = (*m_opponent)->x + (-unk2ad0[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 8) {
            if ((*m_opponent)->y == 0.0) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
        }
        if (frame == 6) {
            unk3140 = 1;
        }
        if (frame > 7) {
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
            if (frame == 1) {
                m_hitsLeft = 0;
            }
            if (frame == 3) {
                vx = 1.8;
            }
            if (frame == 8) {
                frame = 3;
                unk3138++;
            }
            if (frame == 6 && unk3138 > 1) {
                frame = 8;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0xfd:
        if (frame < 3) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if ((char)(*m_opponent)->Unk40ff70() != 0) {
                CPlayer::StopMoving();
                (*m_opponent)->StopMoving();
            }
            if ((char)(*m_opponent)->Unk40ff70() == 0) {
                (*m_opponent)->x = (unk2ad0[0] + 0x14) * facing + x;
            }
        }
        if (frame == 3) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -69.0 + vy + y;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 3 && vy + y > 0.0) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 3;
            y = 0.0;
            break;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x3f;
            (*m_opponent)->x = (-31.0 + vx) * facing + x;
            (*m_opponent)->y = -33.0 + vy + y;
            CPlayer::DealDamage(0x1f4, 750.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->unkc0 = 0.8;
            (*m_opponent)->unkc8 = -3.2;
        }
        if (frame < 4) {
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 3) {
                vx = -1.0;
                vy = -1.3;
                ay = 0.03;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfe:
        if (frame < 3) {
            vx -= 0.035;
            if (vx < 0.0) {
                vx = 0.0;
            }
            if ((char)(*m_opponent)->Unk40ff70() != 0) {
                CPlayer::StopMoving();
                (*m_opponent)->StopMoving();
            }
            if ((char)(*m_opponent)->Unk40ff70() == 0) {
                (*m_opponent)->x = (unk2ad0[0] + 0x14) * facing + x;
            }
        }
        if (frame == 3) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -69.0 + vy + y;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        if (frame > 3 && vy + y > 0.0) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 3;
            y = 0.0;
            break;
        }
        if (frame == 4 && timer == 0) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x43;
            (*m_opponent)->x = (-41.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            CPlayer::DealDamage(0x3e8, 800.0);
            m_comboHits--;
            m_shownHits--;
            (*m_opponent)->facing = facing;
            (*m_opponent)->unkc0 = -4.0;
            (*m_opponent)->unkc8 = -0.8;
        }
        if (frame < 4) {
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = -1.0;
                vy = -2.1;
                ay = 0.025;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            vx *= 0.3;
            vy *= 0.5;
            ay = 0.035;
            m_hitsLeft = 9;
        }
        if ((frame == 1 || frame == 3 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
        }
        if (frame > 0xa) {
            vy = vy + ay;
        }
        if (y + vy > 0.0) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x102;
            y = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5 && unk3138 < 3) {
                unk3138++;
                frame = 0;
            }
        }
        if (frame >= x8) {
            frame = frame - 4;
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = 3.0;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            CPlayer::StopMoving();
            pattern = 0x101;
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
                frame = frame - 2;
            }
        }
        break;
    case 0x101:
        vx -= 0.04;
        if (vx < 0.0) {
            vx = 0.0;
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
    case 0x102:
        vx -= 0.04;
        if (vx < 0.0) {
            vx = 0.0;
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
    case 0x103:
        if (frame > 8 && frame < 0xf && m_holdA > 0) {
            StartPattern();
            pattern = 0x106;
            break;
        }
        if (frame > 8 && frame < 0xf && m_holdB > 0) {
            StartPattern();
            pattern = 0x107;
            break;
        }
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 7) {
            vx -= 0.02;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 7 && timer == 0) {
            m_hitsLeft = 1;
            vx = 3.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 0xc && unk3138 < 3) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        vy = vy + ay;
        if (frame > 0xd) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_command == 0xa && frame > 0xd) {
            StartPattern();
            pattern = 0x122;
            break;
        }
        if (y < 0.0 && vy > 0.0 && m_pressA == 1) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x100;
            break;
        }
        if (vy + y > 0.0 && frame > 5 && frame < 0xa) {
            frame = 0xe;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        if (vy + y > 0.0 && frame > 9 && frame < 0xe) {
            frame = 0xe;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
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
                vx = 1.2;
                vy = -3.3;
                ay = 0.055;
                m_hitsLeft = 1;
            }
            if (frame == 0xa) {
                frame = frame - 4;
            }
            if (frame == 0xe) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x105:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
            y -= 25.0;
            vx = 3.0;
            m_hitsLeft = 1;
        }
        vy = vy + ay;
        if (frame > 9) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (m_attackResult > 1 && frame > 1 && frame < 6) {
            frame = 6;
            timer = 0;
            vx = -vx * 0.1;
            vy = -1.5;
            ay = 0.036;
            break;
        }
        if (vy + y > 0.0 && frame > 5 && frame < 0xa) {
            frame = 0xa;
            timer = 0;
            y = 0.0;
            vy = 0.0;
            ay = 0.0;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                if (unk3138 < 4) {
                    frame = frame - 4;
                    unk3138++;
                } else {
                    frame = 0xa;
                    y = 0.0;
                    break;
                }
            }
            if (frame == 0xa) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x106:
        vx -= 0.035;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 4 && frame < 0xf && y + vy > 0.0) {
            timer = 0;
            frame = 0xf;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                vy = -3.3;
                m_hitsLeft = 3;
            }
            if (frame == 0xf) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        vy = vy + ay;
        if (frame > 0xa) {
            vx -= 0.03;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y < 0.0 && vy > 0.0 && m_pressA == 1) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x100;
            break;
        }
        if (vy + y > 0.0 && frame > 2 && frame < 0xa) {
            StartPattern();
            CPlayer::StopMoving();
            y = 0.0;
            pattern = 0x102;
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
                vx = 0.8;
                vy = -3.1;
                ay = 0.055;
                m_hitsLeft = 1;
            }
            if (frame >= x8) {
                frame = frame - 4;
            }
        }
        break;
    case 0x108:
        vx -= 0.05;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                CPlayer::StopMoving();
            }
        }
        break;
    case 0x109:
        vx -= 0.05;
        if (vx < 0.0) {
            vx = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
                CPlayer::StopMoving();
            }
        }
        break;
    case 0x10a:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame == 7) {
            frame = 8;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                ay = 0.09;
                vy = -3.0;
                vx = 3.0;
            }
            if (frame == 6 && unk3138 < 1) {
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
    case 0x10b:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.06;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame == 7) {
            frame = 8;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                ay = 0.11;
                vy = -4.5;
                vx = 4.0;
            }
            if (frame == 6 && unk3138 < 1) {
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
    case 0x10c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
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
        if (frame == 2 && timer == 0) {
            m_playSound = 0x15;
            m_gauge = m_gauge + 0x23;
            m_hitsLeft = 1;
        }
        if (frame > 1) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (y + vy > 0.0 && frame > 8 && frame < 0xd) {
            frame = 0xd;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                ay = 0.09;
                vy = -4.0;
                vx = 2.0;
            }
            if (frame == 6 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 0xd) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
            }
        }
        break;
    case 0x10d:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = 3.0;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            CPlayer::StopMoving();
            pattern = 0x108;
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
                frame = frame - 2;
            }
        }
        break;
    case 0x10e:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 2.2;
            vy = 2.2;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            CPlayer::StopMoving();
            pattern = 0x108;
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
                frame = frame - 2;
            }
        }
        break;
    case 0x10f:
        if (frame == 0 && timer == 0) {
            m_gauge = m_gauge + 0x28;
            m_hitsLeft = 4;
        }
        if (frame > 9 && frame < 0xe) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                frame = 0xe;
                break;
            }
        }
        if (frame < 7) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                y = 0.0;
                vy = 0.0;
                StartPattern();
                unk3138 = (int)(vx * 100.0);
                vx = 0.0;
                frame = 7;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 || frame == 0xe) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 9) {
                vx = unk3138 * 0.005;
                vy = -0.8;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x110:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0x13 && m_command == 0xa) {
            StartPattern();
            pattern = 0x106;
            break;
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -2.0;
            vx = -3.0;
        }
        if (frame > 0xf && frame < 0x14) {
            if (m_inputX == facing) {
                vx += 0.015;
            }
            if (m_inputX == -facing) {
                vx -= 0.015;
            }
            if (vx < -2.5) {
                vx = -2.5;
            } else if (vx > 2.5) {
                vx = 2.5;
            }
            if (m_pressA == 1) {
                StartPattern();
                pattern = 0x10d;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                pattern = 0x10e;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                pattern = 0x10f;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x14) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 0x14) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                vx = 1.5;
                vy = -2.5;
                ay = 0.035;
            }
            if (frame == 0x14) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x111:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -1.5;
            vx = -3.0;
        }
        if (frame == 0x12 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame == 0x12 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x6b;
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x113;
            y = unk2af8[0] + 0x32;
            x = (*m_opponent)->x + (-unk2ad0[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 7);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x13) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 0xf && frame < 0x13) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                vx = 2.2;
                vy = -0.5;
                ay = 0.035;
            }
            if (frame == 0x13) {
                frame--;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x112:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame > 0x13 && m_command == 0xa) {
            StartPattern();
            pattern = 0x106;
            break;
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -2.0;
            vx = 3.0;
        }
        if (frame > 0xf && frame < 0x14) {
            if (m_inputX == facing) {
                vx += 0.015;
            }
            if (m_inputX == -facing) {
                vx -= 0.015;
            }
            if (vx < -2.5) {
                vx = -2.5;
            } else if (vx > 2.5) {
                vx = 2.5;
            }
            if (m_pressA == 1) {
                StartPattern();
                pattern = 0x10d;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressB == 1) {
                StartPattern();
                pattern = 0x10e;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
            if (m_pressC == 1) {
                StartPattern();
                pattern = 0x10f;
                if (m_inputX == -facing) {
                    facing = -facing;
                }
                break;
            }
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x14) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 4 && frame < 0x14) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            facing = -facing;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                vx = 1.5;
                vy = -2.5;
                ay = 0.035;
            }
            if (frame == 0x14) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x113:
        CPlayer::Unk410a40(0x32, 3);
        CPlayer::Unk410a80(0x32, 3);
        if (frame == 4) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -54.0 + vy + y;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-31.0 + vx) * facing + x;
            (*m_opponent)->y = -62.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-34.0 + vx) * facing + x;
            (*m_opponent)->y = -34.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (-6.0 + vx) * facing + x;
            (*m_opponent)->y = -3.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (-4.0 + vx) * facing + x;
            (*m_opponent)->y = -2.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa && timer == 0) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x62;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            CPlayer::DealDamage(0x4b0, 960.0);
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk2c = 2;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 0x13 && y + vy > 0.0) {
            StartPattern();
            CPlayer::StopMoving();
            y = 0.0;
            pattern = 0xd;
            break;
        }
        if (frame > 0xf) {
            vy = vy + ay;
        }
        if (frame > 0xd && (*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0x10) {
                vx = -0.5;
                vy = -1.3;
                ay = 0.05;
            }
            if (frame >= x8) {
                frame--;
            }
        }
        break;
    case 0x118:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 0xc;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            vx *= 0.15;
            vy *= 0.15;
            StartPattern();
            pattern = 0x123;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 0.7;
                vy = 2.0;
            }
            if (frame == 6) {
                frame--;
            }
            if (frame == 0xc) {
                frame = frame - 6;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x119:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 0xc;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            vx *= 0.15;
            vy *= 0.15;
            StartPattern();
            pattern = 0x123;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 2.0;
                vy = 2.0;
            }
            if (frame == 6) {
                frame--;
            }
            if (frame == 0xc) {
                frame = frame - 6;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x11a:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            CPlayer::StopMoving();
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
            unk3138++;
        }
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
            m_hitsLeft = 1;
        }
        if (y + vy > 0.0 && frame > 4) {
            timer = 0;
            frame = 0xc;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        if (frame == 5 && m_attackResult == 3) {
            timer = 0;
            frame = 8;
            m_hitsLeft = 0x63;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 5) {
                vx = 2.0;
                vy = 2.0;
            }
            if (frame == 6) {
                frame--;
            }
            if (frame == 0xc) {
                frame = frame - 6;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x11b:
        vx = 0.0;
        vy = 0.0;
        if (frame == 2 && m_attackResult == 3) {
            CPlayer::StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            pattern = 0x11c;
            (*m_opponent)->pattern = 0x6b;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2 && timer == 0 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x95)) {
                m_hitsLeft = 1;
            } else {
                m_hitsLeft = 0;
            }
            if (frame == 2) {
                m_gauge = m_gauge + 0x19;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x11c:
        CPlayer::Unk410a80(-0x32, 3);
        (*m_opponent)->unk14a = 3;
        timer++;
        if (frame > 3) {
            vx = 1.0;
            vy += 0.025;
        }
        if (frame > 3 && vy + y > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            StartPattern();
            (*m_opponent)->StartPattern();
            pattern = 0xd;
            (*m_opponent)->pattern = 0x48;
            break;
        }
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                x = (*m_opponent)->x - (*m_opponent)->unk2ad0[0] * facing;
                y = (*m_opponent)->y + (*m_opponent)->unk2af8[0] - 20.0;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x11d:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 0.5;
            vy = 3.0;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (m_attackResult > 0) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x120;
            break;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            CPlayer::StopMoving();
            pattern = 0x109;
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
                frame = frame - 2;
            }
        }
        break;
    case 0x11e:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 2.2;
            vy = 2.2;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (m_attackResult > 0) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x120;
            break;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            CPlayer::StopMoving();
            pattern = 0x109;
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
                frame = frame - 2;
            }
        }
        break;
    case 0x11f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 4.0;
            vy = 1.5;
            m_hitsLeft = 1;
            m_playSound = 0x23;
            m_gauge = m_gauge + 0x23;
        }
        if (m_attackResult > 0) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x120;
            break;
        }
        if (y + vy > 0.0 && frame > 2) {
            timer = 0;
            frame = 0;
            y = 0.0;
            CPlayer::StopMoving();
            pattern = 0x109;
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
                frame = frame - 2;
            }
        }
        break;
    case 0x120:
        if (frame == 0 && timer == 0) {
            vx = -0.4;
            vy = -0.9;
            ay = 0.045;
        }
        vy = vy + ay;
        if (y + vy > 0.0 && frame < 8) {
            timer = 0;
            frame = 8;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 8) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x121:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        if (frame == 4 && timer == 0) {
            ay = 0.03;
            vy = -1.5;
            vx = -3.0;
        }
        if (frame == 0x12 && (*m_opponent)->y == 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        if (frame > 4 && frame < 0xc || frame > 0xf && frame < 0x13) {
            vy = vy + ay;
        }
        if (frame > 0xb && frame < 0x10) {
            if (facing == 1) {
                x = m_game->m_view.left + 0xf;
            }
            if (facing == -1) {
                x = m_game->m_view.right - 0xf;
            }
        }
        if (y + vy >= 0.0 && frame > 0xf && frame < 0x13) {
            y = 0.0;
            CPlayer::StopMoving();
            frame = 0x14;
            timer = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && frame > 4 && frame < 0xc) {
            vx = 0.0;
            vy = 0.0;
            frame = 0xc;
            timer = 0;
            m_playSound = 0x1a;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame == 0x10) {
                StartPattern();
                CPlayer::StopMoving();
                pattern = 0x11f;
                if (x - (*m_opponent)->x < 140.0 && x - (*m_opponent)->x > -140.0) {
                    pattern = 0x11e;
                }
                if (x - (*m_opponent)->x < 70.0 && x - (*m_opponent)->x > -70.0) {
                    pattern = 0x11d;
                }
                break;
            }
            if (frame == 0x13) {
                frame--;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x122:
        vx -= 0.035;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 4 && frame < 0xf && y + vy > 0.0) {
            timer = 0;
            frame = 0xf;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 7) {
                m_attackResult = 0;
            }
            if (frame == 4) {
                vy = -3.3;
                m_hitsLeft = 3;
            }
            if (frame == 0xf) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 3;
            }
        }
        break;
    case 0x123:
        if (frame == 0 && timer == 0) {
            CPlayer::FaceOpponent();
            CPlayer::StopMoving();
            m_hitsLeft = 5;
        }
        if (frame > 0xe) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                timer = 0;
                frame = 0x16;
                y = 0.0;
                CPlayer::StopMoving();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xe) {
                vx = 0.5;
                vy = 0.0;
                ay = 0.045;
            }
            if (frame == 0x16) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
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
            unk13c = 0x7e;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame == 0x10 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                unk13c = 9;
            }
            if (frame == 6) {
                x = facing * 0xf + x;
            }
            if (frame == 7) {
                x = facing * 0xf + x;
            }
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                if (unk3138 > 1) {
                    frame = 0xc;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xc && unk3138 < 1) {
                frame = 2;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
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
            unk13c = 0x84;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (frame >= 1) {
            unkf2 = 0xa;
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame == 0xe && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 0x15 && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame > 0x14 && frame < 0x1c) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0x14 && frame < 0x1c && y + vy > 0.0) {
            frame = 0x1c;
            timer = 0;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                unk13c = 0x1e;
            }
            if (frame == 6) {
                x = facing * 0xf + x;
            }
            if (frame == 7) {
                x = facing * 0xf + x;
            }
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                if (unk3138 > 2) {
                    frame = 0xc;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xc && unk3138 < 2) {
                frame = 2;
                unk3138++;
            }
            if (frame == 0x14) {
                ay = 0.06;
                vy = -3.0;
                vx = 2.0;
            }
            if (frame == 0x1c) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 0xa;
                StartPattern();
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
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
            unk13c = 0x84;
            CPlayer::Unk410a80(0x32, 0x78);
            m_playSound = 0x25;
        }
        if (frame > 1) {
            m_game->Unk4080c0(0xf);
        }
        if ((frame == 2 || frame == 7) && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
        }
        if (frame == 0xe && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 0x12 && timer == 0) {
            m_playSound = 0x15;
            m_hitsLeft = 1;
            vx = 3.0;
        }
        if (frame > 0x12 && frame < 0x17) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0x14 && frame < 0x17 || frame > 0x1c) {
            vy = vy + ay;
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame == 0x18 && timer == 0) {
            vx = 1.8;
            m_hitsLeft = 0x63;
        }
        if (frame == 0x20 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (m_hitsLeft > 0 || frame < 0x22 && frame > 0x1b) {
                m_attackResult = 0;
            }
            if (frame == 2) {
                unk13c = 0x3c;
            }
            if (frame == 6) {
                x = facing * 0xf + x;
            }
            if (frame == 7) {
                x = facing * 0xf + x;
            }
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                if (unk3138 > 3) {
                    frame = 0xc;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xc && unk3138 < 3) {
                frame = 2;
                unk3138++;
            }
            if (frame == 0x1c && unk3138 < 8) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 1) {
            m_game->Unk4080c0(0xf);
        }
        if (frame >= 0 && frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 6 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x6b;
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x131;
            y = unk2af8[0] + 0x32;
            x = (*m_opponent)->x + (-unk2ad0[0] - 0x14) * facing;
            l50.type = 0;
            l50.x = (double)((int)(*m_opponent)->x + unk2ad0[0]);
            l50.y = (double)((int)(*m_opponent)->y + unk2af8[0]);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 2 && frame < 7) {
            vy = vy + ay;
        }
        if (frame == 6 && y + vy > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 7;
            break;
        }
        if (frame == 6 && (*m_opponent)->y >= 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 1.5;
                vy = -2.0;
                ay = 0.045;
            }
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x130:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
            m_playSound = 0x25;
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        m_game->Unk4080c0(0xf);
        if (frame >= 0 && frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 4 && m_attackResult == 3) {
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x6b;
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x132;
            (*m_opponent)->unk14a = 0x78;
            (*m_opponent)->x = facing * 0x1e + x;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 7);
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
            if (frame == 4 && (*m_opponent)->y >= 0.0) {
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
    case 0x131:
        CPlayer::Unk410a40(0x32, 3);
        CPlayer::Unk410a80(0x32, 3);
        m_game->Unk4080c0(0xf);
        if (frame > 3) {
            vy = vy + ay;
        }
        if (frame == 4) {
            (*m_opponent)->unk140 = 0x7530;
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -52.0 + vy + y;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-31.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-36.0 + vx) * facing + x;
            (*m_opponent)->y = -32.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (-7.0 + vx) * facing + x;
            (*m_opponent)->y = -8.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 0xa) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (-4.0 + vx) * facing + x;
            (*m_opponent)->y = -6.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame > 8 && vy + y > 0.0) {
            CPlayer::StopMoving();
            StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x62;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = x;
            y = 0.0;
            pattern = 0x133;
            CPlayer::DealDamage(0x3e8, 960.0);
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk2c = 2;
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
            if (frame == 4) {
                vx = (1 - ((x > 320.0) << 1)) * 0.6 * facing;
                vy = -5.0;
                ay = 0.06;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x132:
        CPlayer::Unk410a40(0x32, 3);
        CPlayer::Unk410a80(0x32, 3);
        m_game->Unk4080c0(0xf);
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                StartPattern();
                pattern = 0x131;
                frame = 4;
                (*m_opponent)->unk14a = 0;
                vx = (1 - ((x > 320.0) << 1)) * 0.6 * facing;
                vy = -5.0;
                ay = 0.06;
            }
        }
        break;
    case 0x133:
        (*m_opponent)->Unk410a80(0x32, 3);
        m_game->Unk4080c0(0xf);
        unk13e = 2;
        if ((*m_opponent)->pattern == 0x63) {
            (*m_opponent)->timer = 0;
        }
        if (unk3138 > 0x78 && unk3138 < 0x2d0 && frame > 5 && frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 5) {
            l50.type = 0x195;
            l50.x = x + 80.0 - (WORD)CPlayer::Random(0, 0xa0);
            l50.y = (double)-(WORD)CPlayer::Random(0, 0x32);
            l50.scale = 0;
            l50.layer = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (frame > 3) {
            vy = vy + ay;
        }
        if (frame > 5) {
            unk3138++;
        }
        if (unk3138 == 0x50) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = -320.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.unk18 = facing;
            SpawnObject(&l50);
        }
        if (unk3138 == 0x78) {
            l50.type = 0x192;
            l50.x = (double)((int)x - facing * 0x14);
            l50.y = -320.0;
            l50.scale = 0;
            l50.layer = 1;
            l50.unk28 = 1;
            l50.unk18 = facing;
            l50.unk0 = 1;
            SpawnObject(&l50);
        }
        if (frame == 9 && vy + y > 0.0) {
            CPlayer::StopMoving();
            timer = 0;
            frame = 0xa;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x62;
            y = 0.0;
            (*m_opponent)->unk140 = 0x7530;
            CPlayer::DealDamage(0x12c, 960.0);
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk2c = 2;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame == 0xf && vy + y > 0.0) {
            CPlayer::StopMoving();
            timer = 0;
            frame = 0x10;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x62;
            y = 0.0;
            CPlayer::DealDamage(0x578, 960.0);
            (*m_opponent)->unk140 = 0;
            CPlayer::Unk410a10(0xa, 0xa);
            (*m_opponent)->unk14a = 0x78;
            l50.type = 0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.unk2c = 0x16;
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame == 0x14 && vy + y > 0.0) {
            CPlayer::StopMoving();
            timer = 0;
            frame = 0x15;
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            y = 0.0;
            break;
        }
        if (frame == 0xb && unk3138 > 0x334) {
            frame = 0xc;
            timer = 0;
            vy = -5.0;
            ay = 0.06;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                vx = 0.0;
                vy = -3.9;
                ay = 0.08;
            }
            if (frame == 0xc) {
                if (unk3138 <= 0x2da) {
                    frame = 6;
                    vx = 0.0;
                    vy = -3.9;
                    ay = 0.08;
                } else {
                    frame = 0xb;
                }
            }
            if (frame == 0x12) {
                vx = -0.6;
                vy = -1.5;
                ay = 0.038;
            }
            if (frame == 0x1f && unk313c < 4) {
                frame = frame - 2;
                unk313c++;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 0;
                CPlayer::FaceOpponent();
            }
        }
        break;
    case 0x134:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
        if (frame >= 0 && frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 3 || frame == 4) && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = 0x137;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 4 && frame < 0x70) {
            vy = vy + ay;
        }
        if (frame < 0xc && y + vy > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                unk13c = 6;
            }
            if (frame == 5 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
        if (frame >= 0 && frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 3 || frame == 4) && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = 0x138;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 4 && frame < 0x70) {
            vy = vy + ay;
        }
        if (frame < 0xc && y + vy > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                unk13c = 0xc;
            }
            if (frame == 5 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
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
            m_playSound = 0x25;
        }
        m_game->Unk4080c0(0xf);
        if (frame >= 0 && frame < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((frame == 3 || frame == 4) && m_attackResult == 3) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            (*m_opponent)->StartPattern();
            (*m_opponent)->StopMoving();
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
            StartPattern();
            ay = 0.025;
            pattern = 0x139;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x2c);
            l50.y = (double)((int)y - 0x2c);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (frame > 6) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame > 4 && frame < 0x70) {
            vy = vy + ay;
        }
        if (frame < 0xc && y + vy > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 0xc;
            break;
        }
        if ((frame == 3 || frame == 4) && (*m_opponent)->y < 0.0) {
            m_hitsLeft = 1;
        } else {
            m_hitsLeft = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vx = 2.0;
                vy = -3.2;
                ay = 0.035;
                unk13c = 0x12;
            }
            if (frame == 5 && unk3138 < 5) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
                vy *= 0.5;
            }
            if (frame == 0xc) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x137:
        unk13e = 2;
        if (frame < 0xe) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame < 0xd || frame > 0xe && frame < 0x12) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xd) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->unk14a = 0x7e;
                    CPlayer::DealDamage(0x92e, 750.0);
                    CPlayer::Unk410a10(0xa, 0);
                    timer = 0;
                    frame = 0xd;
                    m_playSound = 0x16;
                    break;
                }
                if (frame == 0x11) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    timer = 0;
                    frame = 0x12;
                    break;
                }
            }
        }
        if (frame < 0xd) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xb) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xc) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd) {
                frame = frame - 8;
            }
            if (frame == 0xf) {
                (*m_opponent)->unk14a = 3;
                vx = -1.2;
                vy = -2.0;
                ay = 0.035;
                (*m_opponent)->y = -1.0;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -1.2;
                (*m_opponent)->unkc8 = -2.0;
                (*m_opponent)->pattern = 0x3b;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x138:
        unk13e = 2;
        if (frame < 0x19) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame < 0xd || frame > 0xe && frame < 0x19 || frame > 0x1a && frame < 0x1e) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xd) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->unk14a = 0x96;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    CPlayer::DealDamage(0x3e8, 980.0);
                    CPlayer::Unk410a10(0xa, 0);
                    (*m_opponent)->unk140 = 0x7530;
                    timer = 0;
                    frame = 0xd;
                    m_playSound = 0x16;
                    break;
                }
                if (frame > 0xe && frame < 0x19) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->unk14a = 0x7e;
                    CPlayer::Unk410a10(0xf, 0);
                    CPlayer::DealDamage(0x834, 980.0);
                    (*m_opponent)->unk140 = 0;
                    timer = 0;
                    frame = 0x19;
                    m_playSound = 0x16;
                    break;
                }
                if (frame == 0x1d) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    timer = 0;
                    frame = 0x1e;
                    break;
                }
            }
        }
        if (frame < 0xd) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0xe && frame < 0x19) {
            vx += 0.025;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4 || frame == 0xf || frame == 0x10) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5 || frame == 0x11) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6 || frame == 0x12) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 || frame == 0x13) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8 || frame == 0x14) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 0x15) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa || frame == 0x16) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xb || frame == 0x17) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xc || frame == 0x18) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd || frame == 0x19) {
                frame = frame - 8;
            }
            if (frame == 0xf) {
                vx = -4.0;
                vy = -4.0;
                ay = 0.025;
                (*m_opponent)->unk14a = 3;
            }
            if (frame == 0x1b) {
                vx = -1.8;
                vy = -2.3;
                ay = 0.035;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -1.8;
                (*m_opponent)->unkc8 = -2.3;
                (*m_opponent)->pattern = 0x3b;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x139:
        unk13e = 2;
        m_game->Unk4080c0(0xf);
        if (frame < 0x19) {
            if (x > 580.0) {
                x = 580.0;
                vx = 0.0;
            }
            if (x < 60.0) {
                x = 60.0;
                vx = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame < 0xd || frame > 0xe && frame < 0x19 || frame > 0x1a && frame < 0x1e) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                if (frame < 0xd) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->unk14a = 0x96;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    CPlayer::DealDamage(0x3e8, 980.0);
                    CPlayer::Unk410a10(0xa, 0);
                    (*m_opponent)->unk140 = 0x7530;
                    timer = 0;
                    frame = 0xd;
                    m_playSound = 0x16;
                    break;
                }
                if (frame > 0xe && frame < 0x19) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = facing + x;
                    (*m_opponent)->facing = -facing;
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->unk14a = 0xba;
                    CPlayer::DealDamage(0xed8, 980.0);
                    (*m_opponent)->unk140 = 0;
                    CPlayer::Unk410a10(0x14, 0x1e);
                    timer = 0;
                    frame = 0x19;
                    m_playSound = 0x16;
                    break;
                }
                if (frame == 0x1d) {
                    y = 0.0;
                    CPlayer::StopMoving();
                    timer = 0;
                    frame = 0x1e;
                    break;
                }
            }
        }
        if (frame < 0xd) {
            vx -= 0.025;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        if (frame > 0xe && frame < 0x19) {
            vx += 0.025;
            if (vx > 0.0) {
                vx = 0.0;
            }
        }
        if (frame < 4) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 52.0;
        }
        if (frame == 4 || frame == 0xf || frame == 0x10) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (15.0 + vx) * facing + x;
            (*m_opponent)->y = -70.0 + vy + y;
        }
        if (frame == 5 || frame == 0x11) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-25.0 + vx) * facing + x;
            (*m_opponent)->y = -65.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 6 || frame == 0x12) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-28.0 + vx) * facing + x;
            (*m_opponent)->y = -43.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 7 || frame == 0x13) {
            (*m_opponent)->pattern = 0x75;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -29.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        if (frame == 8 || frame == 0x14) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (12.0 + vx) * facing + x;
            (*m_opponent)->y = -23.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 9 || frame == 0x15) {
            (*m_opponent)->pattern = 0x68;
            (*m_opponent)->x = (23.0 + vx) * facing + x;
            (*m_opponent)->y = -36.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xa || frame == 0x16) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (28.0 + vx) * facing + x;
            (*m_opponent)->y = -58.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xb || frame == 0x17) {
            (*m_opponent)->pattern = 0x67;
            (*m_opponent)->x = (14.0 + vx) * facing + x;
            (*m_opponent)->y = -73.0 + vy + y;
            (*m_opponent)->facing = -facing;
        }
        if (frame == 0xc || frame == 0x18) {
            (*m_opponent)->pattern = 0x76;
            (*m_opponent)->x = (-12.0 + vx) * facing + x;
            (*m_opponent)->y = -78.0 + vy + y;
            (*m_opponent)->facing = facing;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd || frame == 0x19) {
                frame = frame - 8;
            }
            if (frame == 0xf) {
                vx = -4.0;
                vy = -7.0;
                ay = 0.025;
                (*m_opponent)->unk14a = 3;
            }
            if (frame == 0x1b) {
                vx = -1.8;
                vy = -2.3;
                ay = 0.035;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->unkc0 = -1.8;
                (*m_opponent)->unkc8 = -2.3;
                (*m_opponent)->pattern = 0x3b;
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::FaceOpponent();
                pattern = 3;
            }
        }
        break;
    case 0x13a:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk410a80(0x32, 0x78);
            m_hitsLeft = 0xc;
        }
        if (timer == 0 && (frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf)) {
            m_playSound = 0x15;
        }
        if (frame > 7 && frame < 0x10) {
            if (m_inputX == facing) {
                vx += 0.012;
            }
            if (m_inputX == -facing) {
                vx -= 0.012;
            }
            if (vx < -1.2) {
                vx = -1.2;
            } else if (vx > 1.2) {
                vx = 1.2;
            }
        }
        if (frame > 0xf) {
            if (vx > 0.0) {
                vx -= 0.01;
                if (vx < 0.0) {
                    vx = 0.0;
                }
            }
            if (vx < 0.0) {
                vx += 0.01;
                if (vx > 0.0) {
                    vx = 0.0;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x10 && unk3138 < 3) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 1 || frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x10) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13b:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk410a80(0x32, 0x78);
            m_hitsLeft = 0x63;
        }
        if (timer == 0 && (frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf)) {
            m_playSound = 0x15;
        }
        if (frame > 7 && frame < 0x10) {
            if (m_inputX == facing) {
                vx += 0.012;
            }
            if (m_inputX == -facing) {
                vx -= 0.012;
            }
            if (vx < -1.3) {
                vx = -1.3;
            } else if (vx > 1.3) {
                vx = 1.3;
            }
        }
        if (frame > 0xf) {
            if (vx > 0.0) {
                vx -= 0.01;
                if (vx < 0.0) {
                    vx = 0.0;
                }
            }
            if (vx < 0.0) {
                vx += 0.01;
                if (vx > 0.0) {
                    vx = 0.0;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x10 && unk3138 < 5) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 1 || frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x10) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 0) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 1 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0xf);
            l50.y = (double)((int)y - 0x22);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk410a80(0x32, 0x78);
            m_hitsLeft = 0x63;
            m_playSound = 0x25;
        }
        if (timer == 0 && (frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf)) {
            m_playSound = 0x15;
        }
        if (frame > 7 && frame < 0x10) {
            if (m_inputX == facing) {
                vx += 0.012;
            }
            if (m_inputX == -facing) {
                vx -= 0.012;
            }
            if (vx < -1.4) {
                vx = -1.4;
            } else if (vx > 1.4) {
                vx = 1.4;
            }
        }
        if (frame > 0xf) {
            if (vx > 0.0) {
                vx -= 0.01;
                if (vx < 0.0) {
                    vx = 0.0;
                }
            }
            if (vx < 0.0) {
                vx += 0.01;
                if (vx > 0.0) {
                    vx = 0.0;
                }
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0x10 && unk3138 < 0xa) {
                frame = frame - 4;
                unk3138++;
            }
            if (frame == 1 || frame == 9 || frame == 0xb || frame == 0xd || frame == 0xf || frame == 0x10) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 1;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (frame > 0xd && frame < 0x12 && m_attackResult == 3) {
            StartPattern();
            CPlayer::StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk14a = 0xb4;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x49;
            (*m_opponent)->x = facing * 0x1e + x;
            pattern = 0x13e;
            (*m_opponent)->facing = -facing;
            break;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult > 0 && frame < 0x12 && frame > 0xd) {
            timer = 0;
            frame = 0x12;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xe) {
                vx = 3.2;
            }
            if (frame == 0x12 && unk3138 < 2) {
                unk3138++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
        }
        if ((frame == 5 || frame == 0xa) && timer == 0) {
            m_playSound = 0x15;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 0x12 && frame < 0x1f && y + vy > 0.0) {
            timer = 0;
            frame = 0x1f;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                x = facing * 0xf + x;
            }
            if (frame == 0xc) {
                x = facing * 0xf + x;
            }
            if (frame == 0xd) {
                if (unk3138 > 1) {
                    frame = 0xf;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xf && unk3138 < 1) {
                frame = 5;
                unk3138++;
            }
            if (frame == 0x13) {
                vy = -3.3;
                vx = 1.5;
                m_hitsLeft = 3;
            }
            if (frame == 0x1f) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x13f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 1;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (frame > 0xd && frame < 0x12 && m_attackResult == 3) {
            StartPattern();
            CPlayer::StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk14a = 0xb4;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x49;
            (*m_opponent)->x = facing * 0x1e + x;
            pattern = 0x140;
            (*m_opponent)->facing = -facing;
            break;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult > 0 && frame < 0x12 && frame > 0xd) {
            timer = 0;
            frame = 0x12;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xe) {
                vx = 4.0;
            }
            if (frame == 0x12 && unk3138 < 3) {
                unk3138++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x140:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
        }
        if ((frame == 5 || frame == 0xa) && timer == 0) {
            m_playSound = 0x15;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.055;
            vy = vy + ay;
        }
        if (frame > 0x19 && frame < 0x26 && y + vy > 0.0) {
            timer = 0;
            frame = 0x26;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                x = facing * 0xf + x;
            }
            if (frame == 0xc) {
                x = facing * 0xf + x;
            }
            if (frame == 0xd) {
                if (unk3138 > 1) {
                    frame = 0xf;
                    break;
                }
                x = facing * 0xf + x;
            }
            if (frame == 0xf && unk3138 < 2) {
                frame = 5;
                unk3138++;
            }
            if (frame == 0x19) {
                vy = -4.0;
                vx = 1.6;
                m_hitsLeft = 4;
            }
            if (frame == 0x26) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x141:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        m_game->Unk4080c0(0xf);
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
            m_hitsLeft = 1;
            CPlayer::Unk410a80(0x32, 0x78);
            m_playSound = 0x25;
        }
        if (frame > 0xd && frame < 0x12 && m_attackResult == 3) {
            StartPattern();
            CPlayer::StopMoving();
            (*m_opponent)->StopMoving();
            (*m_opponent)->unk14a = 0xb4;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->pattern = 0x49;
            (*m_opponent)->x = facing * 0x1e + x;
            pattern = 0x142;
            (*m_opponent)->facing = -facing;
            break;
        }
        if (vx > 0.0) {
            vx -= 0.035;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (m_attackResult > 0 && frame < 0x12 && frame > 0xd) {
            timer = 0;
            frame = 0x12;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 0xe) {
                vx = 4.5;
            }
            if (frame == 0x12 && unk3138 < 3) {
                unk3138++;
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0x142:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 0x63;
        }
        if ((frame == 5 || frame == 0xa) && timer == 0) {
            m_playSound = 0x15;
        }
        if (vx > 0.0) {
            vx -= 0.025;
        }
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (y < 0.0) {
            ay = 0.045;
            vy = vy + ay;
        }
        if (frame > 0x1b && frame < 0x21 && y + vy > 0.0) {
            timer = 0;
            frame = 0x21;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        if (frame > 0x25 && frame < 0x2a && y + vy > 0.0) {
            timer = 0;
            frame = 0x2a;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        if (frame > 0x2c && frame < 0x43 && y + vy > 0.0) {
            timer = 0;
            frame = 0x43;
            y = 0.0;
            CPlayer::StopMoving();
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 9) {
                x = facing * 0xf + x;
            }
            if (frame == 0xa) {
                x = facing * 0xf + x;
            }
            if (frame == 0xc) {
                x = facing * 0xf + x;
            }
            if (frame == 0xd) {
                x = facing * 0xf + x;
            }
            if (frame == 0xf && unk3138 < 0xa) {
                unk3138++;
                frame = 5;
            }
            if (frame == 0x13) {
                x = facing * 0xf + x;
            }
            if (frame == 0x14) {
                x = facing * 0xf + x;
            }
            if (frame == 0x16) {
                x = facing * 0xf + x;
            }
            if (frame == 0xf && unk3138 < 8) {
                frame = 5;
                unk3138++;
            }
            if (frame == 0x1c) {
                vy = -1.8;
                vx = 1.5;
                m_hitsLeft = 1;
            }
            if (frame == 0x25) {
                vy = -2.6;
                vx = 1.5;
                m_hitsLeft = 1;
            }
            if (frame == 0x2d) {
                vy = -4.5;
                vx = 2.2;
                m_hitsLeft = 8;
            }
            if (frame == 0x43) {
                frame = frame - 4;
            }
            if (frame >= x8) {
                pattern = 3;
                StartPattern();
            }
        }
    }
}
