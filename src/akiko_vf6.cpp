// CAkiko::UpdatePattern (0x712500-0x72199f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CAkiko's
// .rdata, which starts with its constructor's folder name (akiko.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CAkiko::UpdatePattern()
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
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
            unk2c9 = 9;
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
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
            unk2c9 = 9;
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
        if (frame == 2 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
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
            unk2c9 = 9;
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
            CPlayer::StopMoving();
            unk2c9 = 9;
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xd:
        CPlayer::StopMoving();
        y = 0.0;
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
        if (frame == 0 && timer == 0) {
            ay = 0.048;
            vx = 0.0;
            vy = -3.2;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0xf:
        if (frame == 0 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x10:
        if (frame == 0 && timer == 0) {
            ay = 0.048;
            vy = -3.2;
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
            pattern = 0xd;
            StartPattern();
        }
        break;
    case 0x28:
        if (frame == 0 && timer == 0 && unk3138 == 0) {
            unk3138++;
            unk118 -= 100.0;
            if (vy > 0.0) {
                vy *= 0.5;
            }
        }
        unk118--;
        if (frame == 2 && timer == 0) {
            unk2c9 = 0x11;
        }
        vy += 0.03;
        vx = m_inputX * 0.045 * facing + vx;
        vy = m_inputY * 0.015 + vy;
        if (vy < -3.0) {
            vy = -3.0;
        } else if (vy > 1.0) {
            vy = 1.0;
        }
        if (vx < -1.0) {
            vx = -1.0;
        } else if (vx > 1.0) {
            vx = 1.0;
        }
        if (m_inputY == 1) {
            pattern = 9;
            StartPattern();
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
        if (y + vy >= 0.0 && frame > 2) {
            y = 0.0;
            unk2c9 = 9;
            CPlayer::FaceOpponent();
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
            unk2c9 = 7;
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
                CPlayer::FaceOpponent();
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
            unk2c9 = 9;
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
            unk2c9 = 9;
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
            unk2c9 = 9;
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
            unk2c9 = 0x3e;
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
        if (frame == 3 && timer == 0) {
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            unk3138 = 0;
        }
        if (frame > 7) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                pattern = 0xd;
                StartPattern();
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == -1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk2c9 = 0x11;
            }
            if (frame == 4) {
                vx = 2.0;
                vy = -1.0;
                ay = 0.01;
            }
            if (frame == 5 && m_inputX == facing && unk3138 < 2) {
                unk3138++;
                frame = 4;
            }
            if (frame == 8) {
                vy = -0.2;
                vx = 1.0;
                ay = 0.03;
            }
            if (frame >= x8) {
                pattern = 9;
                StartPattern();
            }
        }
        break;
    case 0xa4:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 3) {
                unk2c9 = 0x11;
                l50.type = 0x1f;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 0;
                l50.side = facing == 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                vx = -3.0;
            }
            if (frame == 6) {
                CPlayer::StopMoving();
            }
            if (frame >= x8) {
                StartPattern();
                CPlayer::StopMoving();
                pattern = 0;
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0 && unk3140 == 0) {
            vx = 1.8;
            vy = 0.0;
            unk2c9 = 0x11;
            unk3140++;
            CPlayer::Unk4109d0(3);
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
        if (frame == 0 && timer == 0 && unk3140 == 0) {
            vx = -1.8;
            vy = 0.0;
            unk2c9 = 0x11;
            unk3140++;
            CPlayer::Unk4109d0(3);
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
                StartPattern();
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
        if (y + vy > 0.0 && frame < 7) {
            CPlayer::StopMoving();
            y = 0.0;
            timer = 0;
            frame = 7;
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
        if (frame == 2 && timer == 0) {
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
                StartPattern();
            }
        }
        break;
    case 0xcb:
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            unk2c9 = 0x14;
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
            m_hitsLeft = 3;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                m_attackResult = 0;
                unk2c9 = 0x14;
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
        if (frame == 2 && timer == 0) {
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
            if (frame == 5) {
                CPlayer::StopMoving();
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
            unk2c9 = 0x15;
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
            m_hitsLeft = 5;
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
            if (frame == 2) {
                unk2c9 = 0x15;
                m_attackResult = 0;
            }
            if (frame == 3) {
                unk2c9 = 0x15;
                m_attackResult = 0;
            }
            if (frame == 4) {
                unk2c9 = 0x15;
                m_attackResult = 0;
            }
            if (frame == 5) {
                unk2c9 = 0x15;
                m_attackResult = 0;
            }
            if (frame == 7) {
                unk2c9 = 0x14;
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
            unk3138 = 0;
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
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
            if (frame < 5) {
                m_attackResult = 0;
            }
            if (frame == 8 && unk3138 < 2) {
                frame = 5;
                m_attackResult = 0;
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
            unk2c9 = 0x14;
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
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xd3:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
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
            m_gauge = m_gauge + 0x1e;
            unk2c9 = 0x14;
            m_hitsLeft = 1;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 9) {
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
            unk2c9 = 0x14;
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
            CPlayer::StopMoving();
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
            l50.x = (double)((int)x + facing * 0x28);
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
            if (frame >= x8) {
                pattern = 0;
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xdd:
        if (frame == 0 && timer == 0) {
            (*m_opponent)->pattern = 0x64;
            (*m_opponent)->StopMoving();
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x2a + x;
            (*m_opponent)->StartPattern();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x79;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x;
            }
            if (frame == 2) {
                (*m_opponent)->pattern = 0x7a;
                (*m_opponent)->frame = 2;
                (*m_opponent)->timer = 0;
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = x - facing * 0x28;
                l50.unk28 = 1;
                l50.type = 0x1a7;
                l50.x = x - facing * 0x28;
                l50.y = 0.0;
                l50.unk18 = facing;
                l50.scale = 0;
                l50.unk0 = 1;
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
    case 0xe6:
        vy = vy + ay;
        if (frame == 0 && timer == 0) {
            vx = 0.5;
            ay = 0.03;
        }
        if (frame == 1 && timer == 0) {
            m_gauge = m_gauge + 5;
            unk2c9 = 0x15;
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
            unk2c9 = 0x15;
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
            unk2c9 = 0x14;
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
    case 0xf0:
        vy = vy + ay;
        if (frame == 1 && m_attackResult == 3) {
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0xf1;
            (*m_opponent)->pattern = 0x64;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x16);
            l50.y = (double)((int)y - 0x44);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            (*m_opponent)->x = facing * 0x16 + x;
            (*m_opponent)->y = y - 68.0;
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
    case 0xf1:
        if (frame < 2) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (frame < 2) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0 && timer == 1) {
            (*m_opponent)->facing = -facing;
        }
        vy = vy + ay;
        if (vy + y > 0.0) {
            CPlayer::StopMoving();
            y = 0.0;
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 2) {
                l50.unk28 = 1;
                l50.type = 0x1a8;
                l50.x = facing * 0x25 + x;
                l50.y = -56.0;
                l50.unk18 = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame == 3) {
                ay = 0.035;
            }
            if (frame >= x8) {
                frame = frame - 2;
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
                CPlayer::FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xfa:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                unk2c8 = 0;
                m_gauge = m_gauge + 0x14;
                l50.unk0 = 1;
                l50.scale = 0;
                unk3138 = (WORD)CPlayer::Random(0, 9);
                if (unk3150 == 0) {
                    l50.type = 0x193;
                    unk3150 = 1;
                    unk313c = 5;
                } else if (unk3150 == 1) {
                    l50.type = 0x194;
                    unk3150 = 2;
                    unk313c = 3;
                } else if (unk3150 == 2) {
                    l50.type = 0x192;
                    unk3150 = 0;
                    unk313c = 3;
                }
                unk3140 = 0;
                for (; unk3140 < unk313c; unk3140++) {
                    l50.x = facing * 0x28 + x;
                    l50.y = y + -57.0 - (WORD)CPlayer::Random(0, 0x14);
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.unk28 = 1;
                    SpawnObject(&l50);
                }
                l50.type = 0x190;
                l50.x = facing * 0x1e + x;
                l50.y = y + -65.0;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk28 = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfb:
        if (frame == 0 && timer == 0) {
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                unk2c8 = 0;
                m_gauge = m_gauge + 0x14;
                l50.unk0 = 1;
                l50.scale = 0;
                unk3138 = (WORD)CPlayer::Random(0, 9);
                if (unk3150 == 0) {
                    l50.x = facing * 0x46 + x;
                    l50.type = 0x196;
                    unk3150 = 1;
                    unk313c = 1;
                } else if (unk3150 == 1) {
                    l50.type = 0x197;
                    l50.x = facing * 0x28 + x;
                    unk3150 = 2;
                    unk313c = 3;
                } else if (unk3150 == 2) {
                    l50.type = 0x198;
                    l50.x = facing * 0x28 + x;
                    unk3150 = 0;
                    unk313c = 1;
                }
                unk3140 = 0;
                for (; unk3140 < unk313c; unk3140++) {
                    l50.y = y + -67.0;
                    if (unk3150 == 0) {
                        l50.y = y + -57.0 - (WORD)CPlayer::Random(0, 0x14);
                    }
                    l50.unk28 = 1;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                l50.type = 0x190;
                l50.x = facing * 0x1e + x;
                l50.y = y + -65.0;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk28 = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfc:
        if (frame == 0 && timer == 0) {
            if (y == 0.0) {
                CPlayer::StopMoving();
            }
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
            unk3140 = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 3;
            if (frame == 4 && timer == 0) {
                unk2c8 = 0;
                m_gauge = m_gauge + 0xa;
                l50.unk0 = 1;
                l50.scale = 0;
                unk3138 = (WORD)CPlayer::Random(0, 9);
                if (unk3138 < 4) {
                    l50.x = facing * 0x46 + x;
                    l50.type = 0x196;
                    unk313c = 1;
                }
                if (unk3138 < 8 && unk3138 > 3) {
                    l50.x = facing * 0x28 + x;
                    l50.type = 0x197;
                    unk313c = 3;
                }
                if (unk3138 > 7) {
                    l50.x = facing * 0x28 + x;
                    l50.type = 0x198;
                    unk313c = 1;
                }
                unk3140 = 0;
                for (; unk3140 < unk313c; unk3140++) {
                    l50.y = y + -67.0;
                    if (unk3138 < 8 && unk3138 > 3) {
                        l50.y = y + -57.0 - (WORD)CPlayer::Random(0, 0x14);
                    }
                    l50.unk18 = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                l50.type = 0x190;
                l50.x = facing * 0x1e + x;
                l50.y = y + -65.0;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk28 = 0;
                SpawnObject(&l50);
            }
            if (frame == 8 && timer == 0) {
                unk2c8 = 0;
                m_gauge = m_gauge + 0xa;
                l50.unk0 = 1;
                unk3138 = (WORD)CPlayer::Random(0, 9);
                if (unk3138 < 4) {
                    l50.x = facing * 0x46 + x;
                    l50.type = 0x196;
                    unk313c = 1;
                }
                if (unk3138 < 8 && unk3138 > 3) {
                    l50.x = facing * 0x28 + x;
                    l50.type = 0x197;
                    unk313c = 3;
                }
                if (unk3138 > 7) {
                    l50.x = facing * 0x28 + x;
                    l50.type = 0x198;
                    unk313c = 1;
                }
                unk3140 = 0;
                for (; unk3140 < unk313c; unk3140++) {
                    l50.y = y + -67.0;
                    if (unk3138 < 8 && unk3138 > 3) {
                        l50.y = y + -57.0 - (WORD)CPlayer::Random(0, 0x14);
                    }
                    l50.unk18 = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                l50.type = 0x190;
                l50.x = facing * 0x1e + x;
                l50.y = y + -65.0;
                l50.unk18 = facing;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk28 = 0;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfd:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && (m_command == 0x14 || m_command == 0x15)) {
            StartPattern();
            pattern = 0xff;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 2.0;
                vy = -0.85;
                ay = 0.035;
                unk2c8 = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && unk3138 < 3) {
                frame = 9;
                unk3138++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xfe:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            m_hitsLeft = 1;
            vx = -vx;
            ay = 0.035;
        }
        if (frame > 3 && y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0xd;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3 && timer == 0) {
                vy = -1.0;
                unk2c8 = 4;
                if (y - (*m_opponent)->y - 50.0 < 3.0 && y - (*m_opponent)->y - 50.0 > -3.0) {
                    break;
                }
                if (y - (*m_opponent)->y - 50.0 < 10.0 && y - (*m_opponent)->y - 50.0 > -10.0) {
                    frame = 4;
                } else {
                    frame = 5;
                }
                break;
            }
            if (frame == 4 && timer == 0) {
                frame = 6;
            }
            if (frame == 5 && timer == 0) {
                frame = 6;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0xff:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && (m_command == 0x14 || m_command == 0x15)) {
            StartPattern();
            pattern = 0x103;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 3.5;
                vy = -1.4;
                ay = 0.035;
                unk2c8 = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && unk3138 < 3) {
                frame = 9;
                unk3138++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x100:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && (m_command == 0x14 || m_command == 0x15)) {
            StartPattern();
            pattern = 0xff;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 3.0;
                vy = -1.25;
                ay = 0.035;
                unk2c8 = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && unk3138 < 3) {
                frame = 9;
                unk3138++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            unk313c = 0;
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4109d0(3);
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && m_command == 0x16) {
            StartPattern();
            pattern = 0x102;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 9.0;
                vy = -3.6;
                ay = 0.035;
                unk2c8 = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && unk3138 < 3) {
                frame = 9;
                unk3138++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x102:
        if (frame == 0 && timer == 0) {
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if ((frame == 9 || frame == 0xa) && m_attackResult == 3 && m_command == 0x16) {
            if (unk313c < 3) {
                facing = -facing;
                unk313c++;
                unk3138 = 0;
                frame = 0;
                timer = 0;
                break;
            }
            StartPattern();
            pattern = 0xfe;
            facing = -facing;
            break;
        }
        if (frame < 0x13 && y < 0.0) {
            if (frame > 0xa) {
                vy = vy + ay;
            }
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                frame = 0x13;
                timer = 0;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 6) {
                m_gauge = m_gauge + 0x19;
                vx = 9.0;
                vy = -3.6;
                ay = 0.035;
                unk2c8 = 3;
            }
            if (frame == 7) {
                vx = 0.5;
                vy = -0.2;
            }
            if (frame == 0xb && unk3138 < 3) {
                frame = 9;
                unk3138++;
            }
            if (frame == 0x13) {
                frame = 0x11;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x103:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            m_hitsLeft = 1;
            vx = -vx;
            ay = 0.035;
        }
        if (frame > 3 && y < 0.0) {
            vy = vy + ay;
            if (y + vy >= 0.0) {
                y = 0.0;
                CPlayer::StopMoving();
                StartPattern();
                pattern = 0xd;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1) {
                m_attackResult = 0;
            }
            if (frame == 3 && timer == 0) {
                vy = -1.0;
                unk2c8 = 4;
                if (y - (*m_opponent)->y - 40.0 < 8.0 && y - (*m_opponent)->y - 40.0 > -8.0) {
                    frame = 4;
                } else {
                    frame = 5;
                }
                break;
            }
            if (frame == 4 && timer == 0) {
                frame = 6;
            }
            if (frame == 5 && timer == 0) {
                frame = 6;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x104:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 8;
            l50.type = 0x19f;
            l50.unk0 = 1;
            l50.x = (double)((int)x + facing * 0x29);
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
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
    case 0x105:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 8;
            l50.type = 0x1a2;
            l50.unk0 = 1;
            l50.x = (double)((int)x + facing * 0x29);
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
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
    case 0x106:
        if (frame == 0 && timer == 0) {
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4109d0(3);
            vx = 0.0;
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 8;
            l50.type = 0x1a4;
            l50.unk0 = 1;
            l50.x = (double)((int)x + facing * 0x29);
            l50.y = (double)((int)y - 0x37);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk18 = facing;
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
    case 0x107:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 5;
        }
        if (frame > 4 && frame < 7) {
            unk3138 += 3;
            if (unk3138 > 0x5b) {
                unk3138 = 0x5a;
            }
            unkd0 = 1;
            if ((*m_opponent)->x > facing * 0x39 + x && facing == 1) {
                unkb8 = unk3138 * 0.01 * -(*m_opponent)->facing;
            }
            if ((*m_opponent)->x < facing * 0x39 + x && facing == -1) {
                unkb8 = unk3138 * 0.01 * (*m_opponent)->facing;
            }
        }
        if (frame > 4 && m_attackResult == 3) {
            if (facing == 1 && x < 100.0) {
                x = 100.0;
            }
            if (facing == -1 && x > 540.0) {
                x = 540.0;
            }
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            (*m_opponent)->unk128 = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x39);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            pattern = 0x108;
            (*m_opponent)->pattern = 0x79;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x39 + x;
            (*m_opponent)->facing = facing;
            break;
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
    case 0x108:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0xb || frame == 0xc) {
            vy += 0.03;
            if (y + vy >= 0.0) {
                CPlayer::StopMoving();
                y = 0.0;
                StartPattern();
                pattern = 0xd;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                unk2c8 = 6;
            }
            if (frame == 0xb && timer == 0) {
                CPlayer::Unk410a10(4, 0xa);
                vx = 1.2;
                vy = -1.25;
                (*m_opponent)->y = -50.0;
                (*m_opponent)->x = x - facing * 0x46;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = 0.0;
                (*m_opponent)->unkc8 = -2.5;
                CPlayer::DealDamage(0x5dc, 500.0);
                unk2c8 = 7;
                (*m_opponent)->unk128 = 1;
                l50.type = 0x48;
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = (double)((int)y - 0x3c);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19d;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x109:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 5;
        }
        if (frame > 4 && frame < 7) {
            unk3138 += 4;
            if (unk3138 > 0x79) {
                unk3138 = 0x78;
            }
            unkd0 = 1;
            if ((*m_opponent)->x > facing * 0x39 + x && facing == 1) {
                unkb8 = unk3138 * 0.01 * -(*m_opponent)->facing;
            }
            if ((*m_opponent)->x < facing * 0x39 + x && facing == -1) {
                unkb8 = unk3138 * 0.01 * (*m_opponent)->facing;
            }
        }
        if (frame > 4 && m_attackResult == 3) {
            if (facing == 1 && x < 100.0) {
                x = 100.0;
            }
            if (facing == -1 && x > 540.0) {
                x = 540.0;
            }
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            (*m_opponent)->unk128 = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x39);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            pattern = 0x10a;
            (*m_opponent)->pattern = 0x79;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x39 + x;
            (*m_opponent)->facing = facing;
            break;
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
    case 0x10a:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0xb || frame == 0xc) {
            vy += 0.03;
            if (y + vy >= 0.0) {
                CPlayer::StopMoving();
                y = 0.0;
                StartPattern();
                pattern = 0xd;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                unk2c8 = 6;
            }
            if (frame == 0xb && timer == 0) {
                CPlayer::Unk410a10(4, 0xa);
                vx = 1.2;
                vy = -1.25;
                (*m_opponent)->y = -50.0;
                (*m_opponent)->x = x - facing * 0x46;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = 0.0;
                (*m_opponent)->unkc8 = -2.5;
                CPlayer::DealDamage(0x5dc, 500.0);
                unk2c8 = 7;
                (*m_opponent)->unk128 = 1;
                l50.type = 0x48;
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = (double)((int)y - 0x3c);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19d;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x10b:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 4;
            unk3138 = 0;
            unk313c = 0;
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x32);
            l50.scale = 2;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4109d0(3);
            if (unk120 == 0) {
                unk118 -= 500.0;
            } else {
                unk118 -= 250.0;
            }
        }
        if (frame == 3 && timer == 0) {
            unk2c8 = 5;
        }
        if (frame > 4 && frame < 7) {
            unk3138 += 6;
            if (unk3138 > 0x96) {
                unk3138 = 0x96;
            }
            unkd0 = 1;
            if ((*m_opponent)->x > facing * 0x39 + x && facing == 1) {
                unkb8 = unk3138 * 0.01 * -(*m_opponent)->facing;
            }
            if ((*m_opponent)->x < facing * 0x39 + x && facing == -1) {
                unkb8 = unk3138 * 0.01 * (*m_opponent)->facing;
            }
        }
        if (frame > 4 && m_attackResult == 3) {
            if (facing == 1 && x < 100.0) {
                x = 100.0;
            }
            if (facing == -1 && x > 540.0) {
                x = 540.0;
            }
            (*m_opponent)->StopMoving();
            (*m_opponent)->StartPattern();
            StartPattern();
            (*m_opponent)->unk128 = 1;
            l50.type = 0;
            l50.x = (double)((int)x + facing * 0x39);
            l50.y = (double)((int)y - 0x2f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            pattern = 0x10c;
            (*m_opponent)->pattern = 0x79;
            (*m_opponent)->y = 0.0;
            (*m_opponent)->x = facing * 0x39 + x;
            (*m_opponent)->facing = facing;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && unk313c < 3) {
                unk313c++;
                frame--;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x10c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
        }
        if (frame == 0xb || frame == 0xc) {
            vy += 0.03;
            if (y + vy >= 0.0) {
                CPlayer::StopMoving();
                y = 0.0;
                StartPattern();
                pattern = 0xd;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                unk2c8 = 6;
            }
            if (frame == 0xb && timer == 0) {
                CPlayer::Unk410a10(4, 0xa);
                vx = 1.2;
                vy = -1.25;
                (*m_opponent)->y = -50.0;
                (*m_opponent)->x = x - facing * 0x46;
                (*m_opponent)->StartPattern();
                (*m_opponent)->StopMoving();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = 0.0;
                (*m_opponent)->unkc8 = -3.5;
                CPlayer::DealDamage(0x6d6, 500.0);
                unk2c8 = 7;
                (*m_opponent)->unk128 = 1;
                l50.type = 0x48;
                l50.x = (double)((int)x - facing * 0x46);
                l50.y = (double)((int)y - 0x3c);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19d;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x12c:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
            l50.type = 0x1a6;
            l50.unk28 = 1;
            l50.x = x - facing * 0x168;
            l50.y = 0.0;
            l50.unk18 = facing;
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk2c8 = 9;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x19, 0xa);
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x42);
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
            if (frame == 7 && timer == 0) {
                unk2c8 = 0xc;
                CPlayer::Unk410a10(7, 0xa);
                l50.type = 0x1ad;
                l50.x = (double)((int)x + facing * 0x6e);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1af;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1ae;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
            }
            if (frame == 0xa && timer == 0 && unk3138 < 6) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12d:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
            l50.type = 0x1ab;
            l50.unk28 = 1;
            l50.x = x - facing * 0x168;
            l50.y = 0.0;
            l50.unk18 = facing;
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk2c8 = 9;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x19, 0xa);
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x42);
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
            if (frame == 7 && timer == 0) {
                unk2c8 = 0xc;
                CPlayer::Unk410a10(7, 0xa);
                l50.type = 0x1ad;
                l50.x = (double)((int)x + facing * 0x82);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1af;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1b0;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
            }
            if (frame == 0xa && timer == 0 && unk3138 < 6) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12e:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
            l50.type = 0x1ac;
            l50.unk28 = 1;
            l50.x = x - facing * 0x168;
            l50.y = 0.0;
            l50.unk18 = facing;
            l50.scale = 0;
            l50.layer = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            unk2c8 = 9;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x19, 0xa);
        }
        if (frame > 4) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 4 && timer == 0) {
            unk3138 = 0;
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x42);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 7 && timer == 0) {
                unk2c8 = 0xc;
                CPlayer::Unk410a10(7, 0xa);
                l50.type = 0x1ad;
                l50.x = (double)((int)x + facing * 0xc8);
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.unk0 = 1;
                l50.unk18 = facing;
                l50.layer = 1;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1af;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1b0;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
                l50.type = 0x1b1;
                SpawnObject(&l50);
                SpawnObject(&l50);
                SpawnObject(&l50);
            }
            if (frame == 0xa && timer == 0 && unk3138 < 6) {
                unk3138++;
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x12f:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x19, 0xa);
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x42);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && m_attackResult == 3) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x130;
            (*m_opponent)->unk14a = 0x1c2;
            break;
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
    case 0x130:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk2c8 = 0x13;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                CPlayer::Unk410a10(5, 5);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -3.5;
                (*m_opponent)->unkc8 = -1.5;
                (*m_opponent)->ay = 0.035;
                CPlayer::DealDamage(0x3e8, 500.0);
                (*m_opponent)->unk128 = 1;
                l50.type = 0x34;
                unk2c9 = 0x16;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y - 0x46);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk15c = 1;
                unk3148 = 0x3e8;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x131:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x19, 0xa);
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x42);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame == 5 && m_attackResult == 3) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x132;
            (*m_opponent)->unk14a = 0x1c2;
            break;
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
    case 0x132:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk2c8 = 0x13;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                CPlayer::Unk410a10(5, 5);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -3.5;
                (*m_opponent)->unkc8 = -1.5;
                (*m_opponent)->ay = 0.035;
                CPlayer::DealDamage(0x3e8, 500.0);
                (*m_opponent)->unk128 = 1;
                l50.type = 0x34;
                unk2c9 = 0x16;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y - 0x46);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk15c = 2;
                unk3148 = 0x3e8;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x133:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            m_hitsLeft = 1;
        }
        if (frame < 3) {
            CPlayer::Unk410a80(0x19, 0xa);
        }
        if (frame > 1) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x42);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            unk2c9 = 0x25;
        }
        if (frame == 5 && m_attackResult == 3) {
            StartPattern();
            CPlayer::StopMoving();
            pattern = 0x134;
            (*m_opponent)->unk14a = 0x1c2;
            break;
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
    case 0x134:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            unk2c8 = 0x13;
        }
        if (frame < 2) {
            m_game->Unk4080c0(0xf);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 1 && timer == 0) {
                CPlayer::Unk410a10(5, 5);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x3f;
                (*m_opponent)->unkc0 = -3.5;
                (*m_opponent)->unkc8 = -1.5;
                (*m_opponent)->ay = 0.035;
                CPlayer::DealDamage(0x3e8, 500.0);
                (*m_opponent)->unk128 = 1;
                l50.type = 0x34;
                unk2c9 = 0x16;
                l50.x = (double)((int)x + facing * 0x28);
                l50.y = (double)((int)y - 0x46);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                (*m_opponent)->unk15c = 3;
                unk3148 = 0x3e8;
            }
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && unk3138 < 2) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
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
                m_game->FadeMusic(-0x2710, 0x64);
                unk3138 = 0;
            }
            if (frame == 8 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 8) {
                unk160 = 1;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && unk3138 < 0) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 6) {
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
                m_game->FadeMusic(-0x2710, 0x64);
                unk3138 = 0;
            }
            if (frame == 8 && unk3138 < 3) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 8) {
                unk160 = 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x137:
        if (frame == 0 && timer == 0) {
            unk3138 = 0;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            CPlayer::StopMoving();
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6 && unk3138 < 0) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 2) {
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
                unk3138 = 0;
                unk2c9 = 0x25;
                m_game->FadeMusic(-0x2710, 0x64);
            }
            if (frame == 8 && unk3138 < 1) {
                frame = frame - 2;
                unk3138++;
            }
            if (frame == 8) {
                unk160 = 3;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x13e:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame > 6) {
            m_game->Unk4080c0(0xf);
        }
        if (frame > 5) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (frame == 0xa && m_attackResult == 3) {
            StartPattern();
            pattern = 0x13f;
            (*m_opponent)->StartPattern();
            (*m_opponent)->pattern = 0x79;
            CPlayer::Unk410b10(0xb0, 0x1770);
            m_game->FadeMusic(-0x2710, 0x3e8);
            m_game->unk1420e = 0x7530;
            (*m_opponent)->m_game->unk1420e = 0x7530;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 6) {
                x = (*m_opponent)->x + facing * 0x28;
                facing = -facing;
                unk14c = 0x96;
                m_gauge = m_gauge - 0xbb8;
                CPlayer::Unk410b10(0xb0, 0xa);
                l50.type = 0x46;
                l50.unk2c = 0x40;
                l50.x = (double)(int)x;
                l50.y = (double)((int)y - 0x3f);
                l50.scale = 2;
                l50.unk0 = 1;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                unk2c9 = 0x25;
                l50.type = 0x47;
                m_game->CreateEffect((EffectDesc*)&l50);
            }
            if (frame == 0xa) {
                if ((*m_opponent)->y == 0.0) {
                    m_hitsLeft = 1;
                } else {
                    m_hitsLeft = 0;
                }
            }
            if (frame >= x8) {
                CPlayer::FaceOpponent();
                StartPattern();
                pattern = 0;
            }
        }
        break;
    case 0x13f:
        if (frame == 0 && timer == 0) {
            m_game->Unk4080c0(0);
            if (x > 450.0 && facing == 1) {
                x = 450.0;
            }
            if (x < 190.0 && facing == -1) {
                x = 190.0;
            }
            (*m_opponent)->x = facing * 0x3c + x;
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            unk3138 = 0;
        }
        if (frame > 2) {
            (*m_opponent)->timer = 0;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                CPlayer::Unk410b10(0xb0, 0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x7b;
                (*m_opponent)->facing = facing;
                l50.type = 0x1a9;
                l50.x = (double)((int)x + facing * 0x3c);
                l50.y = (double)(int)y;
                l50.unk18 = facing;
                l50.scale = 0;
                l50.unk0 = 1;
                l50.layer = 0;
                SpawnObject(&l50);
                unk2c8 = 0x11;
            }
            if (frame == 2) {
                m_game->unk1420e = 0x7530;
                (*m_opponent)->m_game->unk1420e = 0x7530;
                m_game->unk1420c = 0x7530;
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x79;
                l50.type = 0x1aa;
                l50.x = 0.0;
                l50.y = 0.0;
                l50.scale = 0;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.unk28 = 0;
                l50.unk18 = 1;
                l50.screen = 1;
                SpawnObject(&l50);
                unk2c8 = 0x10;
            }
            if (frame == 3) {
                m_game->unk1420e = 0;
                (*m_opponent)->m_game->unk1420e = 0;
                m_game->unk1420c = 0;
                unk2c8 = 0xe;
                CPlayer::DealDamage(0x157c, 1000.0);
                (*m_opponent)->StartPattern();
                (*m_opponent)->pattern = 0x63;
            }
            if (frame == 5 && unk3138 < 0x14) {
                unk3138++;
                frame = 3;
            }
            if (frame == 5) {
                if ((*m_opponent)->m_hp <= 0 && unkac == m_game->unk134e) {
                } else {
                    m_game->FadeMusic(0, 0x3e8);
                }
            }
            if (frame >= x8) {
                CPlayer::FaceOpponent();
                StartPattern();
                pattern = 0;
            }
        }
    }
}
