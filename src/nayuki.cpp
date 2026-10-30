// CNayuki (0x461090-0x46d96f): the character class whose files are in nayuki\ in the game
// folder (nayuki.dat sprites, nayuki.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNayuki::CNayuki(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "nayuki");
    lastSurface = 0x1fd;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 3;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    unk3158 = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3a;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0xe;
    m_pointY[2] = -0x11;
    m_pointX[3] = 0x14;
    m_pointY[3] = -0x19;
    m_pointX[4] = 0x24;
    m_pointY[4] = -0x2c;
    m_resultPictures = 7;
    m_rivals[0] = 1;
    m_rivals[1] = 6;
    m_rivals[2] = 0x10;
    m_rivals[0xa] = 0xa;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk315c[v4] = 0;
        unk325c[v4] = 0;
        unk335c[v4] = 0;
    }
}

void CNayuki::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 3;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    unk3158 = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3a;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0xe;
    m_pointY[2] = -0x11;
    m_pointX[3] = 0x14;
    m_pointY[3] = -0x19;
    m_pointX[4] = 0x24;
    m_pointY[4] = -0x2c;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk315c[v4] = 0;
        unk325c[v4] = 0;
        unk335c[v4] = 0;
    }
    CPlayer::Reset();
}

void CNayuki::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CNayuki::RemoveObject(short p1)
{
    unk315c[p1] = 0;
    unk325c[p1] = 0;
    unk335c[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CNayuki::Move()
{
    Unk40e740();
}

void CNayuki::StartCommand()
{
    if (pattern < 0xc8) {
        m_bufferedPress = 0;
    }
    if (m_dashBufferTime <= 0) {
        m_dashBufferedPress = 0;
    } else {
        m_dashBufferTime--;
    }
    if (m_dashBufferedPress == 0) {
        m_dashBufferTime = 0;
    }
    if (m_command == 0x34 && (unk118 >= 500.0 || unk120 > 0) && m_attackResult > 1 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        StartPattern();
        ClearBufferedPress();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x61 && m_gauge >= 0xbb8 && y == 0.0 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x131;
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x130;
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12f;
            return;
        }
        if (unk3148 > 0) {
            if (m_command == 0x48 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10a].unk0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0x10a;
                return;
            }
            if ((m_command == 0x47 || m_command == 0x48) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x109].unk0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0x109;
                return;
            }
            if (m_command == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x108].unk0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0x108;
                return;
            }
        }
        if ((m_command == 0x1e || m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && (m_patterns[pattern].unk2 <= m_patterns[0x10c].unk0 + (unk3148 > 6) * 0xa || pattern == 0x108 || pattern == 0x109)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x10c;
            return;
        }
        if (unk3148 > 1) {
            if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x106].unk0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0x106;
                return;
            }
            if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0x105;
                return;
            }
            if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0x104;
                return;
            }
        }
        if (m_command == 0xd && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x117].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x117;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfc;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfb;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfa;
            return;
        }
    }
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < (unk3148 > 2) + 1 + (unk3148 > 7)) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                pattern = 0xa5;
                FaceOpponent();
                unk159++;
                unk15a++;
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa6].unk0 && pattern != 0xaa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                pattern = 0xa6;
                FaceOpponent();
                unk159++;
                unk15a++;
                m_bufferedPress = 0;
                return;
            }
        }
        if (y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa3].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa3) {
                    StartPattern();
                }
                pattern = 0xa3;
                FaceOpponent();
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa4].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa4) {
                    StartPattern();
                }
                pattern = 0xa4;
                FaceOpponent();
                m_bufferedPress = 0;
                return;
            }
        }
    }
    if (unk15c < 3 && m_command == 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk15a < 1 && m_patterns[pattern].unk2 <= m_patterns[0xe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
        StartPattern();
        ClearBufferedPress();
        unk15a++;
        pattern = 0xe;
        if (m_inputX == facing) {
            pattern = 0xf;
        }
        if (m_inputX == -facing) {
            pattern = 0x10;
        }
        return;
    }
    if (m_pressA == 1 || (m_bufferedPress & 0x10) != 0 || (m_dashBufferedPress & 0x10) != 0) {
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xcf].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == 0xa3) {
                    pattern = 0xe6;
                    return;
                }
                pattern = 0xcf;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcc].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xcc;
            return;
        }
        if ((m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) && m_patterns[pattern].unk2 <= m_patterns[0xc8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xc8;
            return;
        }
    }
    if (m_pressB == 1 || (m_bufferedPress & 0x20) != 0 || (m_dashBufferedPress & 0x20) != 0) {
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd0].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == 0xa3) {
                    pattern = 0xe7;
                    return;
                }
                pattern = 0xd0;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && (m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && pattern != 0xc9 || m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 > 0) && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd2].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && unk3148 > 1 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xd2;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -80.0 && x - (*m_opponent)->x < 80.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xc9;
                return;
            }
            if (pattern == 0xcd && unk3148 > 1 || m_patterns[pattern].unk2 <= m_patterns[0xca].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xca;
                return;
            }
        }
    }
    if (m_pressC == 1 || (m_bufferedPress & 0x40) != 0 || (m_dashBufferedPress & 0x40) != 0) {
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf8].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == 0xa3) {
                    pattern = 0xe8;
                    return;
                }
                pattern = 0xf8;
                return;
            }
            if ((m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && pattern != 0xca || m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 > 4) && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == 0xa3) {
                    pattern = 0xe8;
                    return;
                }
                if (pattern == 0xca) {
                    pattern = 0xd6;
                    return;
                }
                pattern = 0xd1;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xce].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xce;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && (*m_opponent)->y == 0.0) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xcb;
                return;
            }
        }
    }
    if (unk15c < 2 && (m_pressD == 1 || (m_bufferedPress & 0x80) != 0 || (m_dashBufferedPress & 0x80) != 0) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 < 9 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
        StartPattern();
        ClearBufferedPress();
        pattern = 0x103;
        if (m_inputY == 1) {
            pattern = 0x118;
        }
    }
}

void CNayuki::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    x1c = *anims[0x2c].frames;
    v2c = MakeRect(0, 0, x1c.width, x1c.height);
    if (m_side == 0) {
        v10 = MakeRect(2 - x1c.x, 0xbf - x1c.y, x1c.width, x1c.height);
    } else {
        v10 = MakeRect(x1c.x + 0x118, 0xbf - x1c.y, x1c.width, x1c.height);
    }
    m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    x1c = *(EffectFrame*)PTRAT((char*)&anims[unk3148].frameCount + 0x114);
    v2c = MakeRect(0, 0, x1c.width, x1c.height);
    if (m_side == 0) {
        v10 = MakeRect(2 - x1c.x, 0xbf - x1c.y, x1c.width, x1c.height);
    } else {
        v10 = MakeRect(0x118 - x1c.x, 0xbf - x1c.y, x1c.width, x1c.height);
    }
    m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
}

void CNayuki::Vf8()
{
}

void CNayuki::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CNayuki::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            m_command = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            m_command = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 6) {
            m_command = 0x61;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 4 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0x40) != 0 && x6 == 0 && m_gauge == 0xbb8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0xaf;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 8) != 0 && x6 == 1) {
            m_command = 6;
            return;
        }
        if ((v5 & 8) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 4) {
            m_command = 0x35;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0 && pattern == 0x60) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 4) {
            m_command = 0x34;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x20) != 0 && x6 == 4) {
            m_command = 0x33;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x10) != 0 && x6 == 4) {
            m_command = 0x32;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf) == 1 && x6 == 3) {
            m_command = 1;
            return;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf) == 2 && x6 == 3) {
            m_command = 0;
            break;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
}

void CNayuki::CpuInput()
{
    double v10;
    double x8;

    m_command = 0x63;
    if (unk1a0 > 0) {
        unk1a0--;
    }
    if (unk1a4 > 0) {
        unk1a4--;
    }
    m_inputX = 0;
    m_inputY = 0;
    m_pressA = 0;
    m_pressB = 0;
    m_pressC = 0;
    m_pressD = 0;
    unk14e = 0;
    if ((WORD)Random(0, 0x3e8) < 25.0f * unka8 + (y < 0.0) * 0x1e * unka8 + (m_cpuAction == 3) * 0x190 + (pattern == 0xaa) * 0x12c) {
        unk14e = 0x3c;
    }
    if ((WORD)Random(0, 0x7d0) < ((unk130 > 0) * 4.0 + 1.0) * 8.0 * unka8 * ((pattern > 0x95 && pattern < 0x9d) * 2 + 1)) {
        unk14e = 0x3c;
    }
    if ((WORD)Random(0, 0x3e8) < 4e+01f * unka8 && pattern > 0xc7) {
        unk14e = 0x3c;
    }
    if (unk170 == 1 && m_cpuAction == 2) {
        unk14e = 0x1e;
        if (pattern < 0xc8) {
            m_cpuAction = 0;
        }
        return;
    }
    if ((*m_opponent)->pattern == 0x60) {
        return;
    }
    v10 = ((*m_opponent)->x - x) * facing;
    x8 = fabs(y - (*m_opponent)->y);
    if (pattern >= 0x32 && pattern <= 0x96 && timer == 0) {
        if ((WORD)Random(0, 0x64) < 8.0f * unka8) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        m_inputX = 1 - (((WORD)Random(0, 0x64) < 0x32) << 1);
        m_pressD = (WORD)Random(0, 0xf0) < x8;
        m_pressD = (WORD)Random(0, 0x140) < v10;
        if ((*m_opponent)->pattern > 0xc7 && (*m_opponent)->pattern < 0xfa && (*m_opponent)->frame < 3 && x8 < 100.0 && v10 < 150.0) {
            m_pressD = 0;
        }
        return;
    }
    if ((pattern >= 4 && pattern <= 6 || pattern >= 0xa && pattern <= 0xc) && y == 0.0) {
        return;
    }
    if ((*m_opponent)->pattern >= 0x32 && (*m_opponent)->pattern < 0x96 && pattern == 0x108 && m_hitsLeft > 1) {
        return;
    }
    if (pattern == 0xa8 && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 3.0f) {
            m_pressA = 1;
            m_inputY = 1;
            return;
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x48;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x61;
                return;
            }
        }
        if (v10 < 220.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0x48;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y > -40.0 && y - (*m_opponent)->y < 40.0 && v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (x8 < 50.0 && v10 < 50.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (x8 < 50.0 && v10 < 130.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 4 && unk118 > 500.0) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 0xa && unk118 > 500.0) {
            m_command = 0x16;
            return;
        }
        if (m_cpuRoll < 0xd && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 2) * 0x6e;
            return;
        }
        if (m_cpuRoll < 0x10 && m_cpuRoll > 0x12 && m_gauge == 0xbb8) {
            m_command = 0x61;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 0x3c) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x104 || pattern == 0x105 || pattern == 0x106 || pattern == 0x105 || pattern == 0x108 || pattern == 0x109)) {
        m_command = 0x34;
        return;
    }
    if (pattern == 0xa5 || pattern == 0xa6) {
        m_pressA = 1;
    }
    if (m_cpuAction > 0 && pattern > 0x31 && pattern < 0x9e) {
        m_cpuAction = 0;
    }
    if (m_cpuAction == 1 && pattern < 0xc8) {
        m_cpuAction = 0;
    }
    if (m_cpuAction == 2 && unk170 != 1) {
        m_cpuAction = 0;
        return;
    }
    if (m_cpuAction == 4) {
        m_inputY = -1;
        m_inputX = (WORD)Random(0, 2) - 1;
        if ((pattern == 4 || pattern == 5 || pattern == 6) && (y < -60.0 || unk3148 > 6)) {
            m_command = facing == 1;
            if (pattern == 0xa5) {
                m_cpuAction = 0;
            }
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (m_cpuAction == 5 && pattern < 0x32) {
        m_cpuAction = 6;
        return;
    }
    if (m_cpuAction == 6 && pattern == 9) {
        if (pattern == 0xd0) {
            m_cpuAction = 0;
        }
        m_pressB = 1;
        return;
    }
    if (m_cpuAction == 7 && pattern < 0x32) {
        m_cpuAction = 8;
        return;
    }
    if (m_cpuAction == 8 && pattern == 9) {
        if (pattern == 0xcf) {
            m_cpuAction = 0;
        }
        m_pressA = 1;
        return;
    }
    if (m_cpuAction == 9 && pattern < 0x32) {
        m_inputY = 1;
        m_pressC = 1;
        if (pattern == 0xce) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < 0x32) {
        m_inputY = 0;
        m_pressC = 1;
        if (pattern == 0xcb) {
            m_cpuAction = 0;
        }
        return;
    }
    if ((pattern == 0xfa || pattern == 0xfc) && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9d) {
        if (m_cpuRoll < 0x12c && (*m_opponent)->y == 0.0) {
            m_cpuAction = 7;
            return;
        }
        if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && (*m_opponent)->y == 0.0) {
            m_cpuAction = 4;
            return;
        }
        if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x226 && (*m_opponent)->y < 0.0 && v10 < 60.0) {
            m_cpuAction = 9;
            return;
        }
        if (m_cpuRoll > 0x226 && m_cpuRoll < 0x28a && (*m_opponent)->y < 0.0 && v10 < 100.0) {
            m_cpuAction = 0xa;
            return;
        }
    }
    if (pattern == 0x10c) {
        if (m_cpuRoll < 0x12c && v10 < 120.0 && ((*m_opponent)->pattern > 0xc7 || (*m_opponent)->y < 0.0)) {
            m_pressA = 1;
            return;
        }
        if (m_cpuRoll < 0x1c2 && m_cpuRoll > 0x12c && (*m_opponent)->y == 0.0 && v10 < 160.0) {
            m_pressB = 1;
            return;
        }
        if (m_cpuRoll < 0x258 && m_cpuRoll > 0x1c2 && (*m_opponent)->y == 0.0 && v10 < 100.0) {
            m_pressC = 1;
            return;
        }
        if (m_cpuRoll < 0x28a && m_cpuRoll > 0x258 && (*m_opponent)->y == 0.0 && unk3148 < 9) {
            m_pressD = 1;
            return;
        }
    }
    if (m_attackResult > 1 && unk14a == 0 && (WORD)Random(0, 0x64) < unka8 * 25.0f && m_cpuAction == 0 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x258) {
                m_pressD = 1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x257 && m_cpuRoll < 0x2bc) {
                m_inputY = -1;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll < 0x15e && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x1f4 && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && unk3148 > 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x257) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_pressC = 1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x140 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x6e;
                return;
            }
            if (m_cpuRoll < 0x96 && v10 < 80.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x96) {
                if (m_cpuRoll < (y < 0.0) * 0x96 + 0x15e) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < unk3148 * 0xa + 0x1c2) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x262 && y < 0.0) {
                m_command = 0x34;
                return;
            }
        }
        if (pattern == 0xcb) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0x12c) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x1f4 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + 0x6e;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x230 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + 0x64;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressB = 1;
                m_inputY = (WORD)Random(0, 2) == 0 ? 1 : 0;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if (m_cpuRoll < 0x15e && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x1f4 && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && unk3148 > 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x257) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x320 && m_attackResult == 3 && unk3148 < 9) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = 0xa;
                if ((*m_opponent)->y < 0.0) {
                    m_command = 0xb;
                }
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0x12c) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && (*m_opponent)->y == 0.0) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x64a && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + 0x64;
                return;
            }
        }
        if (pattern == 0xcf) {
            if (v10 < 60.0 && x8 < 30.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == 0xd1) {
            if (m_cpuRoll > 0x3b6) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 3;
                return;
            }
        }
    }
    if ((WORD)Random(0, 0x64) < 25.0f * unka8) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 35.0 && m_cpuRoll < 0xf) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 50.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 90.0 && v10 > 60.0 && m_cpuRoll < 0x4b && m_cpuRoll < 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 150.0 && 0x46 - (unk3148 > 6) * 0x14 < v10 && m_cpuRoll < 0x87 && m_cpuRoll < 0x4b) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 150.0 && 0x46 - (unk3148 > 6) * 0x14 < v10 && m_cpuRoll < 0x87 && m_cpuRoll < 0xa0 && unk3148 > 2) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 150.0 && v10 > 90.0 && m_cpuRoll < 0xf0 && m_cpuRoll > 0xa0) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 260.0 && v10 > 100.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x12c) {
                    m_command = (WORD)Random(0, 3) + 0xa;
                    return;
                }
                if (v10 < 200.0 && v10 > 70.0 && m_cpuRoll < unk3148 * 5 + 0x168 && m_cpuRoll > 0x15e) {
                    m_command = (WORD)Random(0, 3) + 0x46;
                    return;
                }
                if (v10 < 200.0 && v10 > 70.0 && m_cpuRoll < unk3148 * 5 + 0x1a4 && m_cpuRoll > 0x19a && unk3148 > 3 && unk118 > 500.0) {
                    m_command = 0x15;
                    return;
                }
                if (v10 < 200.0 && v10 < 100.0 && m_cpuRoll < unk3148 * 2 + 0x1e0 && m_cpuRoll > 0x1d6 && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x48;
                    return;
                }
                if (v10 < 200.0 && v10 < 70.0 && m_cpuRoll < unk3148 * 2 + 0x1fe && m_cpuRoll > 0x1f4 && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x16;
                    return;
                }
                if (m_cpuRoll > 0x212) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x3a && (*m_opponent)->pattern < 0x64 && (*m_opponent)->pattern != 0x60) * 0x96 + 0x212 + ((*m_opponent)->pattern > 0x5f && (*m_opponent)->pattern < 0x64 && (*m_opponent)->pattern != 0x60) * 0x12c + (v10 > 180.0) * 0x14 && unk3148 < 9) {
                        m_pressD = 1;
                        return;
                    }
                }
                if (m_cpuRoll < 0x2a && m_cpuRoll > 0x2f) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 70.0 && m_cpuRoll < 0x14) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 70.0 && x8 > 40.0 && x8 < 90.0 && m_cpuRoll < 0x32 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x14;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 150.0 && x8 > 80.0 && m_cpuRoll < 0x5a) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 < 150.0 && v10 > 100.0 && x8 < 120.0 && x8 > 90.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x5a) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 70.0 && x8 < 50.0 && m_cpuRoll < 0xc8) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 70.0 && x8 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0xfa) {
                        m_pressB = 1;
                        return;
                    }
                }
                if (v10 < 110.0 && x8 > 60.0 && x8 < 80.0 && vy > 0.0 && (*m_opponent)->y > y && m_cpuRoll > 0x1f4 && m_cpuRoll < 0x26c) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 60.0 && x8 > 60.0 && m_cpuRoll < 0x6e) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 100.0 && x8 < 80.0 && (*m_opponent)->y < y && m_cpuRoll < 0xfa && m_cpuRoll > 0x6e) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * unka8) {
        if (v10 < 150.0) {
            m_command = facing == 1;
        }
        return;
    }
    if (pattern < 0x32 && y == 0.0 && (WORD)Random(0, 0x64) < 1.0f * unka8 && v10 > 80.0 && v10 < 160.0) {
        if (v10 < 150.0) {
            m_command = facing == 1;
        }
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 4.0f * unka8) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (v10 > 240.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 80.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 140.0 && v10 > 100.0 && y == 0.0) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
    }
    if (unk1a0 > 0) {
        if ((char)Unk40ff70() != 0 && unk1a0 > 0xf) {
            unk1a0 = 0xf;
        }
        m_inputX = 1;
        return;
    }
    if (unk1a4 > 0) {
        if ((char)Unk40ff70() != 0 && unk1a4 > 0xf) {
            unk1a4 = 0xf;
        }
        m_inputX = -1;
        return;
    }
    if ((WORD)Random(0, 0x64) < 0x28 && v10 < 100.0) {
        if (facing == 1) {
            unk1a4 = (WORD)Random(0, 0xc8) + 0x5a;
        } else {
            unk1a0 = (WORD)Random(0, 0xc8) + 0x5a;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x50) {
        if (facing == 1) {
            unk1a0 = (WORD)Random(0, 0xc8) + 0x5a;
        } else {
            unk1a4 = (WORD)Random(0, 0xc8) + 0x5a;
        }
        return;
    }
    if (facing == -1) {
        unk1a0 = (WORD)Random(0, 0xc8) + 0x5a;
        return;
    }
    unk1a4 = (WORD)Random(0, 0xc8) + 0x5a;
}

void CNayuki::UpdateObjects()
{
    WORD v58;
    WORD v54;
    int v4;

    if ((*m_opponent)->unk14c > 0) {
        return;
    }
    v4 = m_objectTail;
    EffectDesc l50;
    while (v4 != m_objectHead) {
        if (m_objectActive[v4] != 0 && m_objects[v4].unk86 == 0 && (unk14c == 0 || unk14c > 0 && m_objects[v4].unk88 != 0)) {
            v54 = (short)anims[m_objects[v4].pattern].frames[m_objects[v4].frame].duration;
            v58 = anims[m_objects[v4].pattern].frameCount;
            InitEffectDesc((EffectDesc*)&l50);
            switch (m_objects[v4].pattern) {
            case 0x190:
                if (m_objects[v4].frame == 5 && unk3138 == 0) {
                    unk3138 = 1;
                    l50.type = 0;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x17);
                    l50.y = (double)((int)m_objects[v4].y - 9);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x191:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].layer = 1;
                    }
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].unk58 = 0;
                }
                if (m_objects[v4].scale == 0 && frame == 6 && pattern == 0xfa && m_objects[v4].frame < 5 && (x - m_objects[v4].x < 60.0 && x - m_objects[v4].x > 0.0 && facing == -1 || x - m_objects[v4].x > -60.0 && x - m_objects[v4].x < 0.0 && facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 5;
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].vx = 1.8;
                    m_objects[v4].vy = -0.9;
                    m_objects[v4].ay = 0.025;
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objects[v4].unk80 > 1) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].frame = 6;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 7) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame == 3) {
                        RemoveObject(v4);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x192:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].layer = 1;
                    }
                }
                if (frame == 6 && pattern == 0xfb && m_objects[v4].frame < 5 && (x - m_objects[v4].x < 60.0 && x - m_objects[v4].x > 0.0 && facing == -1 || x - m_objects[v4].x > -60.0 && x - m_objects[v4].x < 0.0 && facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 5;
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.025;
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objects[v4].unk80 > 1) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].frame = 6;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 7) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame == 3) {
                        RemoveObject(v4);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x193:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 5;
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].layer = 1;
                    }
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].unk58 = 0;
                }
                if (frame == 6 && pattern == 0xfc && m_objects[v4].frame < 5 && (x - m_objects[v4].x < 60.0 && x - m_objects[v4].x > 0.0 && facing == -1 || x - m_objects[v4].x > -60.0 && x - m_objects[v4].x < 0.0 && facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 5;
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].vx = 2.2;
                    m_objects[v4].vy = -1.6;
                    m_objects[v4].ay = 0.025;
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].unk80 > 1) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].frame = 6;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 7) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame == 3) {
                        RemoveObject(v4);
                    }
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x194:
                if (pattern == 0xfe) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                } else {
                    m_objects[v4].vx = 1.7;
                    m_objects[v4].vy = -1.7;
                }
                if (m_objects[v4].y < m_game->m_view.top - 0x28) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case 0x195:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x196:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].layer = 1;
                    }
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0x1e) {
                    ShakeScreen(5, 0);
                    l50.type = 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x197:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].layer = 1;
                    }
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0x18) {
                    ShakeScreen(0xa, 0);
                    l50.type = 0x19a;
                    l50.x = (double)((int)m_objects[v4].x + 0x28);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0x1e) {
                    l50.type = 0x19a;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.x = (double)((int)m_objects[v4].x - 0x28);
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x198:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].layer = 1;
                    }
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0x13) {
                    ShakeScreen(0xf, 0);
                    l50.type = 0x19b;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y + 0xf);
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0x18) {
                    l50.type = 0x19b;
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    l50.x = (double)((int)m_objects[v4].x + 0x32);
                    l50.y = (double)((int)m_objects[v4].y - 0xa);
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0x1e) {
                    l50.type = 0x19b;
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    l50.x = (double)((int)m_objects[v4].x - 0x32);
                    l50.y = (double)((int)m_objects[v4].y - 0xa);
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x199:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)Random(0, 0x64) < 0xe) {
                    l50.type = 0x19c;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)Random(0, 0x64));
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19a:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)Random(0, 0x64) < 0xc) {
                    l50.type = 0x19c;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)Random(0, 0x64));
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19b:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)Random(0, 0x64) < 0xa) {
                    l50.type = 0x19c;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)Random(0, 0x64));
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19c:
                if (unk315c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)m_objects[v4].x + (0x14 - (WORD)Random(0, 0x28)) * facing);
                    l50.y = (double)((int)m_objects[v4].y + 0x14 - (WORD)Random(0, 0x28));
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk315c[v4] = 2;
                }
                unk315c[v4]--;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19d:
                if ((pattern == 0x12f || pattern == 0x130 || pattern == 0x131) && frame < 8) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y - 80.0;
                } else {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x195;
                }
                unk314c = (int)m_objects[v4].x;
                unk3154 = (int)m_objects[v4].y;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk315c[v4] <= 0) {
                    l50.type = 0x19f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk315c[v4] = 3;
                    if (pattern == 0x130) {
                        unk315c[v4] = 2;
                    }
                    if (pattern == 0x131) {
                        unk315c[v4] = 1;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        unk315c[v4]--;
                    }
                }
                break;
            case 0x19e:
                if ((pattern == 0x12f || pattern == 0x130 || pattern == 0x131) && frame < 8) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                } else {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x195;
                }
                unk3150 = (int)m_objects[v4].x;
                unk3158 = (int)m_objects[v4].y;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk315c[v4] <= 0) {
                    l50.type = 0x1a0;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.facing = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk315c[v4] = 3;
                    if (pattern == 0x130) {
                        unk315c[v4] = 2;
                    }
                    if (pattern == 0x131) {
                        unk315c[v4] = 1;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        unk315c[v4]--;
                    }
                }
                break;
            case 0x19f:
                if (pattern == 0x12f || pattern == 0x130 || pattern == 0x131) {
                    m_objects[v4].x = unk314c;
                    m_objects[v4].y = unk3154;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_playVoice = 2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a0:
                if (pattern == 0x12f || pattern == 0x130 || pattern == 0x131) {
                    m_objects[v4].x = unk3150;
                    m_objects[v4].y = unk3158;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_playVoice = 2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a1:
                if (m_objects[v4].frame == 0 && unk315c[v4] == 0) {
                    unk315c[v4] = 1;
                    m_objects[v4].vx = -1.9;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ab:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.045;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].unk58 = 0;
                }
                if (m_objects[v4].unk80 > 1) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ac:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 0.8;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.045;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].unk58 = 0;
                }
                if (m_objects[v4].unk80 > 1) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ad:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 1.3;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.045;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].unk58 = 0;
                }
                if (m_objects[v4].unk80 > 1) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ae:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                }
                if (pattern != 0x7b || pattern == 0x7b && frame > 2) {
                    RemoveObject(v4);
                }
                m_objects[v4].vy += 0.02;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case 0x1ef:
                m_objects[v4].vx = -0.02;
                m_objects[v4].unk8c = 0x7530;
                m_objects[v4].timer++;
                if (pattern != 0x57) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1f0:
                if (pattern != 0x53 && pattern != 0x54 && pattern != 0x55 && pattern != 0x56 || pattern == 0x53 && frame > 1 || pattern == 0x54 && frame > 1) {
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x17);
                    l50.y = (double)((int)y - 4);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - (facing << 2));
                    l50.y = (double)((int)y - 6);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0xe);
                    l50.y = (double)((int)y - 0x1a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x28);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0x19);
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x23);
                    l50.y = (double)((int)y - 0x2a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x12);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + facing * 2);
                    l50.y = (double)((int)y - 0x41);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + (facing << 4));
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    m_playSound = 0x22;
                    RemoveObject(v4);
                    unk3144 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1f1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk315c[v4] == 0) {
                    unk325c[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk315c[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk325c[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk325c[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk325c[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1f2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk315c[v4] == 0) {
                    unk325c[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk315c[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk325c[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk325c[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk325c[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1f3:
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
            }
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}
