// CKanna::UpdatePattern (0x667570-0x675c7f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CKanna's
// .rdata, which starts with its constructor's folder name (kanna.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CKanna::UpdatePattern()
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
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                    break;
                }
                StartPattern();
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            m_playVoice = 0;
        }
        if (frame > 4) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
            FaceOpponent();
            vx = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = 1.5;
            m_playVoice = 0;
        }
        if (frame > 6) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
            FaceOpponent();
            vx = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = -1.5;
            m_playVoice = 0;
        }
        if (frame > 6) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
        unk3140++;
        if (unk3140 > 0) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
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
        unk158 = 0;
        if (unk3138 == 0) {
            vx *= 0.3;
            unk3138++;
        }
        if (vy > 0.4) {
            vy = 0.4;
        }
        if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
        if (m_inputY == 1) {
            pattern = 9;
            StartPattern();
            if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                unk15a++;
                if (m_inputX == facing) {
                    pattern = 0x12;
                }
                if (m_inputX == -facing) {
                    pattern = 0x14;
                }
                m_attackResult = 0;
                StartPattern();
                break;
            }
        }
        if (unk15a < 2 && unk15c < 3) {
            if (m_inputX == facing) {
                pattern = 0x11;
                unk15a++;
                StartPattern();
                m_attackResult = 0;
                break;
            }
            if (m_inputX == -facing) {
                pattern = 0x13;
                unk15a++;
                StartPattern();
                m_attackResult = 0;
                break;
            }
        }
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -3.5;
            vx = 0.0;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = 1.5;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -2.5;
            vx = -1.5;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
    case 0x11:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = 2.0;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
    case 0x12:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = 1.5;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
    case 0x13:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = -2.0;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
    case 0x14:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = -1.5;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy = vy + ay;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
        if (m_hp > 0 && timer > 0x3c && frame == 0) {
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
    case 0xa3:
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            StopMoving();
        }
        if (frame == 3 && timer == 0) {
            vx = 2.0;
            vy = -1.0;
            ay = 0.02;
            m_playVoice = 0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                vy = 0.0;
                timer = 0;
                frame = 7;
                break;
            }
        }
        if (frame > 6) {
            vx -= 0.04;
            if (vx < 0.0) {
                vx = 0.0;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame == 7) {
                frame = frame - 2;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
                break;
            }
        }
        break;
    case 0xa4:
        if (frame == 0 && timer == 0) {
            StartAfterimages(3);
            StopMoving();
        }
        if (frame == 2 && timer == 0) {
            vx = -2.0;
            vy = -1.0;
            ay = 0.035;
            m_playVoice = 0;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (y + vy > 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = 0xd;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                frame = frame - 1;
                break;
            }
        }
        break;
    case 0xa5:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 3 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = 2.0;
            m_playVoice = 0;
        }
        if (frame > 2) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
    case 0xa6:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
        }
        unk3140++;
        if (unk3140 > unk3148) {
            if (m_inputY == -1 && unk15c < 3 && unk15a < 2) {
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
            if (m_inputY == 1) {
                pattern = 9;
                StartPattern();
                if (unk15a < 2 && m_inputX != 0 && unk15c < 3) {
                    unk15a++;
                    if (m_inputX == facing) {
                        pattern = 0x12;
                    }
                    if (m_inputX == -facing) {
                        pattern = 0x14;
                    }
                    m_attackResult = 0;
                    StartPattern();
                }
                break;
            }
            if (unk15a < 2 && unk15c < 3) {
                if (m_inputX == facing) {
                    pattern = 0x11;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
                if (m_inputX == -facing) {
                    pattern = 0x13;
                    unk15a++;
                    StartPattern();
                    m_attackResult = 0;
                    break;
                }
            }
        }
        if (frame == 2 && timer == 0) {
            ay = 0.045;
            vy = -0.5;
            vx = -2.0;
            m_playVoice = 0;
        }
        if (frame > 1) {
            vy += 0.01;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame >= x8) {
                pattern = 0xa;
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
        vx = vx;
        if (vx < 0.0) {
            vx = 0.0;
            unk158 = 0;
        }
        if (m_inputY == -1 && frame > 0 && unk15c < 3) {
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
        if (frame == 1 && timer == 0) {
            l50.type = 0x1a4;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0xf;
            m_playSound = 0x14;
            m_hitsLeft = 1;
        }
        if (frame == 3 && timer == 0) {
            l50.type = 0x1a5;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            l50.unk0 = 1;
            SpawnObject(&l50);
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
        if (frame == 4 && timer == 0) {
            m_gauge = m_gauge + 0x23;
            m_playSound = 0x23;
            m_hitsLeft = 1;
        }
        if (frame == 6 && timer == 0) {
            l50.type = 0x1a8;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
        if (frame == 1 && timer == 0) {
            l50.type = 0x1a6;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case 0xce:
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
            unk3138++;
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
    case 0xcf:
        vy = vy + ay;
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 2) {
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
        if (m_inputY == 0 && m_inputX != 0 && frame > 0 && m_attackResult >= 2 && unk15a < 2 && unk15c < 3) {
            unk15a++;
            if (m_inputX == facing) {
                pattern = 0xa5;
            }
            if (m_inputX == -facing) {
                pattern = 0xa6;
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 2) {
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
        if (m_inputY == 0 && m_inputX != 0 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 2) {
            unk15a++;
            if (m_inputX == facing) {
                pattern = 0xa5;
            }
            if (m_inputX == -facing) {
                pattern = 0xa6;
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
        if (frame == 3 && timer == 0) {
            l50.type = 0x1a7;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
        if (m_inputY == -1 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 2) {
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
        if (m_inputY == 0 && m_inputX != 0 && frame > 0 && unk15c < 3 && m_attackResult >= 2 && unk15a < 2) {
            unk15a++;
            if (m_inputX == facing) {
                pattern = 0xa5;
            }
            if (m_inputX == -facing) {
                pattern = 0xa6;
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
        if (frame == 1 && timer == 0) {
            l50.type = 0x1a9;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xd3:
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
            (*m_opponent)->StartPattern();
            pattern = 0xdd;
            (*m_opponent)->unk128 = 1;
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
        if (frame == 4 && timer == 0) {
            DealDamage(0x4e2, 750.0);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 1) {
                (*m_opponent)->pattern = 0x67;
                (*m_opponent)->StopMoving();
                (*m_opponent)->StartPattern();
                (*m_opponent)->y = -86.0;
                (*m_opponent)->x = facing * 0x29 + x;
            }
            if (frame == 2) {
                (*m_opponent)->y = -97.0;
                (*m_opponent)->x = facing * 0x24 + x;
            }
            if (frame == 3) {
                (*m_opponent)->y = -97.0;
                (*m_opponent)->x = facing * 0x22 + x;
                (*m_opponent)->facing = -facing;
            }
            if (frame == 4) {
                (*m_opponent)->y = 0.0;
                (*m_opponent)->x = facing * 0x24 + x;
                (*m_opponent)->facing = -facing;
                ShakeScreen(3, 0);
                (*m_opponent)->pattern = 0x61;
                (*m_opponent)->StopMoving();
                (*m_opponent)->StartPattern();
            }
            if (frame >= x8) {
                pattern = 0;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0xe6:
        StartAfterimages(3);
        unk158 = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 2.0;
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
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0xe7:
        StartAfterimages(3);
        unk158 = 0;
        vx -= 0.03;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 2.0;
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
        if (frame < 3) {
            if (unk158 == 0) {
                vx = 0.0;
            }
            if (vx > 0.0 && unk158 == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                unk158 = 0;
            }
        }
        if (frame == 3 && timer == 0) {
            m_playSound = 0x14;
            vx = 3.0;
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x23;
        }
        vx = vx - (vx > 0.0) * 0.07;
        if (vx < 0.0) {
            vx = 0.0;
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
        vx -= 0.03;
        unk158 = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vx = 2.0;
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
            if (frame < 5) {
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
        vx -= 0.03;
        unk158 = 0;
        if (vx < 0.0) {
            vx = 0.0;
        }
        if (frame == 0 && timer == 0) {
            vy = 0.0;
            vx = 2.0;
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
                pattern = 3;
                StartPattern();
            }
        }
        break;
    case 0xeb:
        StartAfterimages(3);
        unk158 = 0;
        if (frame < 3) {
            if (unk158 == 0) {
                vx = 0.0;
            }
            if (vx > 0.0 && unk158 == 1) {
                vx -= 0.06;
            } else {
                vx = 0.0;
                unk158 = 0;
            }
        }
        if (frame > 2 && frame < 0xf) {
            vy = vy + ay;
            if (vy + y > 0.0) {
                timer = 0;
                StopMoving();
                y = 0.0;
                frame = 0xf;
            }
        }
        if (frame == 7 && timer == 0) {
            m_playSound = 0x14;
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x23;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 3) {
                m_attackResult = 0;
            }
            if (frame == 3) {
                vx = 1.5;
                vy = -1.5;
                ay = 0.032;
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
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 1;
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x194;
            l50.x = (double)((int)x - facing * 0x50);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case 0xfb:
        if (frame == 0 && timer == 0) {
            StopMoving();
            StartAfterimages(3);
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
            m_hitsLeft = 1;
            vx = 0.0;
            vy = 0.0;
            ax = 0.0;
            m_hitsLeft = 1;
            if (y < 0.0) {
                frame = 6;
            }
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 1;
        }
        if (frame == 2 && timer == 0) {
            l50.type = 0x1ab;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case 0xfd:
        if (frame == 0 && timer == 0) {
            vx *= 0.3;
            vy *= 0.3;
        }
        vy += 0.01;
        if (vy > 0.3) {
            vy = 0.3;
        }
        if (frame == 4 && timer == 0) {
            m_hitsLeft = 1;
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 1;
        }
        if (frame == 4 && timer == 0) {
            l50.type = 0x194;
            l50.x = (double)((int)x - facing * 0x50);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
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
    case 0x100:
        if (frame == 0 && timer == 0) {
            StopMoving();
            m_hitsLeft = 2;
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (vy + y >= 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = 0x103;
                break;
            }
        }
        if (0) {}
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3) {
                vy = -2.5;
                ay = 0.045;
                l50.type = 0x1b9;
                l50.x = x;
                l50.y = y;
                l50.unk0 = 1;
                l50.facing = facing;
                l50.scale = 2;
                l50.layer = 1;
                SpawnObject(&l50);
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x101:
        if (frame == 0 && timer == 0) {
            StartAfterimages(1);
            if (unk313c == 0) {
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
                unk313c++;
            }
            m_hitsLeft = 1;
        }
        if (frame == 1 && timer == 0) {
            l50.type = 0x1b9;
            l50.x = x;
            l50.y = y;
            l50.unk0 = 1;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            SpawnObject(&l50);
        }
        if (y < 0.0) {
            vy = vy + ay;
            if (vy + y >= 0.0) {
                y = 0.0;
                StartPattern();
                StopMoving();
                pattern = 0x103;
                break;
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 3 && unk313c == 1) {
                vy = -3.5;
                ay = 0.015;
                unk313c++;
            }
            if (frame == 8 && unk3138 < 5) {
                frame = 0;
                unk3138++;
            }
            if (frame == 9) {
                m_hitsLeft = 1;
            }
            if (frame >= x8) {
                StartPattern();
                pattern = 9;
            }
        }
        break;
    case 0x103:
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 3;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x107:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x190;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.unk28 = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame > 9) {
                m_attackResult = 0;
            }
            if (frame >= x8) {
                pattern = 0;
                StartPattern();
            }
        }
        break;
    case 0x108:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 0 && timer == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.unk28 = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame > 9) {
                m_attackResult = 0;
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
        if (frame == 0 && timer == 0) {
            l50.type = 0x192;
            l50.x = (double)((int)x + facing * 0x1e);
            l50.y = (double)((int)y - 0x28);
            l50.scale = 0;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.unk28 = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame > 9) {
                m_attackResult = 0;
            }
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
        if (frame == 7 && timer == 0) {
            l50.type = 0x195;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.unk28 = 0;
            l50.unk0 = 1;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x196;
            l50.x = (double)((int)x + facing * 0x50);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.layer = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.unk28 = 0;
            l50.unk0 = 1;
            SpawnObject(&l50);
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
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
            StartAfterimages(3);
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
        if (frame == 7 && timer == 0) {
            l50.type = 0x1ad;
            l50.x = (double)((int)x + facing * 0x23);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.side = -((facing == 1) - 1);
            l50.facing = facing;
            l50.unk28 = 0;
            SpawnObject(&l50);
        }
        if (frame == 8 && timer == 0) {
            m_gauge = m_gauge + 0x2d;
            m_playVoice = 2;
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
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0xc6;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)x + facing * 0x1d);
            l50.y = (double)((int)y - 0x3f);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            m_playSound = 0x25;
        }
        if (frame > 2) {
            m_game->Unk4080c0(0xf);
        }
        if (frame == 7 && timer == 0) {
            l50.type = 0x19f;
            l50.x = x - facing * 0x23;
            l50.y = y - 67.0;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk2c = -1;
            l50.unk30 = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
        }
        if (frame > 3) {
            Unk410a80(0x32, 3);
        }
        if (frame == 0xd && timer == 0) {
            m_playVoice = 5;
        }
        if (frame > 0xd && frame < 0x11) {
            unk313c++;
            if ((WORD)Random(0, 0x64) > unk313c * 0.08 + 60.0) {
                l50.type = 0x1a1;
                l50.layer = 1;
                l50.unk0 = 1;
                if ((WORD)Random(0, 0x64) > 0x32) {
                    l50.type = 0x1a0;
                    l50.layer = 0;
                }
                l50.x = x - facing * 0x12c;
                l50.y = (double)((WORD)Random(0, 0x140) - 0x140);
                l50.facing = facing;
                l50.scale = 2;
                SpawnObject(&l50);
            }
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (unk3138 < 0xd && frame == 0x11) {
                frame = frame - 3;
                unk3138++;
                break;
            }
            if (frame >= x8) {
                FaceOpponent();
                StartPattern();
                pattern = 0;
                if (y < 0.0) {
                    pattern = 9;
                    ay = 0.035;
                }
            }
        }
        break;
    case 0x12f:
        vx = 0.0;
        vy = 0.0;
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
            unk3138 = 0xa;
        }
        if (frame == 0 && timer == 0) {
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
            m_hitsLeft = 0x63;
        }
        if (frame > 6 && frame < 0xc) {
            Unk410a80(0x32, 3);
        }
        if (frame == 8 && timer == 0) {
            ShakeScreen(3, 0x14);
            l50.type = 0x1a2;
            l50.x = x + 0.0 - 30.0;
            l50.y = y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
            l50.x = x - facing * 0x28 - 30.0;
            l50.facing = -facing;
            SpawnObject(&l50);
            m_playSound = 0x12;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame == 0xd && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
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
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.035;
        }
        if (frame == 0 && timer == 0) {
            unk14c = 0x78;
            m_gauge = m_gauge - 0xbb8;
            FillBackground(0xb0, 0x21);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
        }
        if (frame > 6 && frame < 0xc) {
            Unk410a80(0x32, 3);
        }
        if (frame == 8 && timer == 0) {
            l50.type = 0x1aa;
            l50.x = x;
            l50.y = y;
            l50.facing = facing;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            SpawnObject(&l50);
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            m_attackResult = 0;
            if (frame >= x8) {
                pattern = 9;
                FaceOpponent();
                StartPattern();
            }
        }
        break;
    case 0x135:
        if (frame == 0 && timer == 0) {
            StopMoving();
        }
        if (frame == 4 && timer == 0) {
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
            l50.type = 0x47;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
        }
        if (frame == 5 && timer == 0) {
            l50.type = 0x1b2;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.facing = facing;
            l50.unk0 = 1;
            SpawnObject(&l50);
        }
        if (frame == 0x10 && timer == 0) {
            l50.type = 0x1b3;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
        }
        if ((frame == 8 || frame == 0x12) && m_attackResult == 3) {
            (*m_opponent)->unk14a = 0x10e;
        }
        if (frame == 0x20 && timer == 0) {
            l50.type = 0x1b0;
            l50.x = (double)(int)x;
            l50.y = (double)(int)y;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = facing;
            SpawnObject(&l50);
            (*m_opponent)->unk140 = 0x7530;
        }
        if (frame == 0x2c && timer == 0) {
            unk14c = 0x23a;
            FillBackground(0xb0, 0xbb8);
            l50.type = 9;
            l50.unk2c = 5;
            l50.x = (double)(int)x;
            l50.y = (double)((int)y - 0x28);
            l50.scale = 2;
            l50.unk0 = 1;
            l50.layer = 1;
            m_game->CreateEffect((EffectDesc*)&l50);
            m_hitsLeft = 0x63;
            (*m_opponent)->x = x;
            m_playVoice = 0xa;
            m_game->unk1420e = 0x7530;
        }
        if (frame == 0x33 && timer == 0) {
            vy = -7.5;
            ay = 0.035;
            l50.type = 0x1b4;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk0 = 1;
            l50.screen = 1;
            l50.facing = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
            l50.type = 0x1b5;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 0;
            l50.unk0 = 1;
            l50.screen = 1;
            l50.facing = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
            l50.type = 0x1b6;
            l50.x = 0.0;
            l50.y = 0.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.screen = 1;
            l50.facing = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
            m_playVoice = 0xb;
        }
        if (frame == 0x35 && m_attackResult == 3) {
            timer = 0;
            frame = 0x36;
            (*m_opponent)->unk14a = 0xbb8;
            vy = -0.05;
            ay = 0.0;
            FillBackground(0xb0, 3);
            m_playVoice = 0xc;
            l50.type = 0x1b7;
            l50.x = x;
            l50.y = y - 160.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
            (*m_opponent)->m_game->unk1420e = 0;
        }
        if (frame == 0x37 && timer == 0) {
            vy = -7.0;
            ay = 0.03;
            l50.type = 0x1c0;
            l50.x = x;
            l50.y = y - 150.0;
            l50.scale = 2;
            l50.layer = 1;
            l50.unk0 = 1;
            l50.facing = 1;
            l50.unk30 = 1;
            SpawnObject(&l50);
            l50.x = x + 40.0;
            l50.y = y - 140.0;
            SpawnObject(&l50);
            l50.x = x - 50.0;
            l50.y = y - 150.0;
            SpawnObject(&l50);
            l50.type = 0x1b8;
            l50.x = x;
            l50.y = y - 150.0;
            SpawnObject(&l50);
        }
        if (frame == 0x37 && m_attackResult == 3) {
            (*m_opponent)->unk140 = 0;
        }
        if (frame > 0 && frame < 0x37) {
            Unk410a80(0x32, 3);
        }
        if (frame > 0x25 && frame < 0x37) {
            Unk410a40(0x32, 3);
        }
        if (y < 0.0) {
            vy = vy + ay;
        }
        if (frame == 0x35 && vy > 1.0) {
            vy = 1.0;
        }
        if (frame > 0x37 && y + vy > 0.0) {
            StopMoving();
            StartPattern();
            y = 0.0;
            pattern = 0xd;
            break;
        }
        timer++;
        if (timer >= l4) {
            timer = 0;
            frame++;
            if (frame < 0x12 || frame == 0x23 || frame > 0x32) {
                m_attackResult = 0;
            }
            if (frame == 0xe && unk3138 > 0) {
                frame = frame - 2;
                unk3138--;
            }
            if (frame == 0x1b && (m_attackResult != 3 || (*m_opponent)->m_hp <= 0)) {
                StartPattern();
                FaceOpponent();
                pattern = 0;
                break;
            }
            if (frame == 0x24 && m_attackResult != 3) {
                StartPattern();
                pattern = 0x136;
            }
            if (frame == 0x2b) {
                l50.type = 0x1b1;
                l50.x = (double)(int)x;
                l50.y = (double)(int)y;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk0 = 1;
                l50.facing = facing;
                l50.unk30 = 1;
                SpawnObject(&l50);
            }
            if (frame == 0x35) {
                m_playVoice = 9;
            }
            if (frame == 0x36) {
                frame--;
            }
            if (frame >= x8) {
                frame = frame - 2;
            }
        }
        break;
    case 0x136:
        if (frame == 0 && timer == 0) {
            vx = 0.0;
            vy = 0.0;
            ay = 0.0;
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
    }
}
