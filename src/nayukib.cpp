// CNayukiB (0x73e790-0x750d2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNayukiB::CNayukiB(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "nayukiB");
    lastSurface = 0x281;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3d;
    m_pointX[1] = 8;
    m_pointY[1] = 0;
    m_pointX[2] = 0x11;
    m_pointY[2] = -0xf;
    m_pointX[3] = 0x13;
    m_pointY[3] = -0xb;
    m_pointX[4] = 0x16;
    m_pointY[4] = -0x1e;
    m_resultPictures = 7;
    m_rivals[0] = 0x11;
    m_rivals[1] = 1;
    m_rivals[2] = 0xd;
    m_rivals[3] = 0x10;
    m_rivals[4] = 0xa;
    m_rivals[5] = 3;
    m_rivals[6] = 6;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3158[v4] = 0;
        unk3258[v4] = 0;
        unk3358[v4] = 0;
    }
}

void CNayukiB::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3d;
    m_pointX[1] = 8;
    m_pointY[1] = 0;
    m_pointX[2] = 0x11;
    m_pointY[2] = -0xf;
    m_pointX[3] = 0x13;
    m_pointY[3] = -0xb;
    m_pointX[4] = 0x16;
    m_pointY[4] = -0x1e;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3158[v4] = 0;
        unk3258[v4] = 0;
        unk3358[v4] = 0;
    }
    CPlayer::Reset();
}

void CNayukiB::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CNayukiB::RemoveObject(short p1)
{
    unk3158[p1] = 0;
    unk3258[p1] = 0;
    unk3358[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CNayukiB::Move()
{
    Unk40e740();
}

void CNayukiB::StartCommand()
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
        if (m_hp < 0xd05 && m_command == 0x67 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x135;
            return;
        }
        if (m_command == 0x7a && m_gauge >= 0xbb8 && unk3150 <= 0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x134;
            return;
        }
        if ((m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x7d0 && unk3150 <= 0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x133;
            return;
        }
        if ((m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x3e8 && unk3150 <= 0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x131;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x130;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12f;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && y < 0.0 && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && y < 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfc;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfb;
            return;
        }
        if ((m_command == 0x14 || m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfa;
            return;
        }
        if (m_command == 0x2a && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x102;
            if (y < 0.0) {
                frame = 2;
            }
            return;
        }
        if ((m_command == 0x29 || m_command == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x101;
            if (y < 0.0) {
                frame = 2;
            }
            return;
        }
        if ((m_command == 0x28 || m_command == 0x29 || m_command == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x100;
            if (y < 0.0) {
                frame = 2;
            }
            return;
        }
        if (m_command == 0x20 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x105;
            if (y < 0.0) {
                pattern = 0x108;
            }
            return;
        }
        if ((m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x104;
            if (y < 0.0) {
                pattern = 0x107;
            }
            return;
        }
        if ((m_command == 0x1e || m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x103;
            if (y < 0.0) {
                pattern = 0x106;
            }
            return;
        }
        if (m_command == 0xc && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xff;
            return;
        }
        if (m_command == 0xb && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfe;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfd;
            return;
        }
    }
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa5) {
                    StartPattern();
                }
                pattern = 0xa5;
                FaceOpponent();
                unk159++;
                unk15a++;
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa6].unk0 && pattern != 0xaa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa6) {
                    StartPattern();
                }
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
                unk158++;
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
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xe6;
            if (m_inputY == 1) {
                pattern = 0xe9;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xcf].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
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
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xe7;
            if (m_inputY == 1) {
                pattern = 0xea;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd0].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xd0;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -70.0 && x - (*m_opponent)->x < 70.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xc9;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xca].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xca;
                return;
            }
        }
    }
    if (m_pressC == 1 || (m_bufferedPress & 0x40) != 0 || (m_dashBufferedPress & 0x40) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xe8;
            if (m_inputY == 1) {
                pattern = 0xeb;
            }
            return;
        }
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf8].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xf8;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
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
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                ClearBufferedPress();
                pattern = 0xcb;
            }
        }
    }
}

void CNayukiB::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (unk314c > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk314c > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, unk3150 * x1c.width / 0xbb8, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3150 * x1c.width / 0xbb8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3150 * x1c.width / 0xbb8, 0x1f - x1c.y, unk3150 * x1c.width / 0xbb8, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CNayukiB::Vf8()
{
    if (unk3150 <= 0 || m_hp <= 0 || (*m_opponent)->m_hp <= 0 || pattern > 0x31 && pattern < 0x96) {
        unk3150 = 0;
        unk314c = 0;
    }
    if (unk3150 > 0) {
        unk3148 += unk3154;
        if (unk3148 > 0x167) {
            unk3148 -= 0x168;
        }
        unk3150 -= 2;
        if (unk3150 <= 0) {
            unk3150 = 0;
            unk314c = 0;
        }
    }
}

void CNayukiB::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CNayukiB::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x69;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            m_command = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_gauge >= 0x3e8) {
            x6 = 1;
        }
    }
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
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 3) {
            m_command = 0x60;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0x40) != 0) {
                m_command = 0x60;
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge == 0xbb8) {
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

void CNayukiB::CpuInput()
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
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 45.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 70.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 5.0f && unk118 > 500.0) {
                m_command = 0x14;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0x2a;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x64;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2 && m_gauge >= 0x7d0) {
                m_command = (WORD)Random(0, 2) + 0x6f;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = 0x2a;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_command = (WORD)Random(0, 2) + 0xa;
                return;
            }
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if (y - (*m_opponent)->y < -20.0 && y - (*m_opponent)->y > -80.0 && v10 < 150.0 && (WORD)Random(0, 0xc8) < unka8 * 5.0f && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + 0x6e;
            return;
        }
        if ((WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 90.0 && y - (*m_opponent)->y > 20.0 && v10 < 110.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && unk118 > 500.0 && v10 < 80.0) {
            m_command = 0x14;
            return;
        }
        if (m_cpuRoll < 5 && unk118 > 500.0 && v10 < 80.0) {
            m_command = 0x16;
            return;
        }
        if (m_cpuRoll < 0xa && m_cpuRoll > 5 && unk118 > 500.0 && v10 < 100.0) {
            m_command = 0x2a;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 < 100.0) {
            m_command = (WORD)Random(0, 3) + 0x78;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 > 90.0) {
            m_command = (WORD)Random(0, 3) + 0x6e;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 > 50.0) {
            m_command = (WORD)Random(0, 3) + 0x6e;
            return;
        }
        if (m_cpuRoll > 0x3c) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x100 || pattern == 0xe8 && (WORD)Random(0, 0xa) == 0 || pattern == 0x101 || pattern == 0xee)) {
        m_command = 0x34;
        return;
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
        if (pattern == 4 || pattern == 5 || pattern == 6) {
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
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 6 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 7;
        }
        return;
    }
    if (m_cpuAction == 7 && pattern == 0xa3) {
        m_pressA = 1;
        if (pattern == 0xe6) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 8 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 9;
        }
        return;
    }
    if (m_cpuAction == 9 && pattern == 0xa3) {
        m_pressB = 1;
        if (pattern == 0xe7) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0xb;
        }
        return;
    }
    if (m_cpuAction == 0xb && pattern == 0xa3) {
        m_pressC = 1;
        if (pattern == 0xe8) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0xd;
        }
        return;
    }
    if (m_cpuAction == 0xd && pattern == 0xa3) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == 0xe6) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xe && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0xf;
        }
        return;
    }
    if (m_cpuAction == 0xf && pattern == 0xa3) {
        m_pressB = 1;
        m_inputY = 1;
        if (pattern == 0xe7) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0x10 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0x11;
        }
        return;
    }
    if (m_cpuAction == 0x11 && pattern == 0xa3) {
        m_pressC = 1;
        m_inputY = 1;
        if (pattern == 0xe8) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0x14 && pattern < 0x32) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == 0xcc) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_attackResult > 1 && unk14a == 0 && (WORD)Random(0, 0x64) < unka8 * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xa && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + 0x6e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + 0x15;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x190) {
                m_command = (WORD)Random(0, 3) + 0x28;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x190 && m_cpuRoll < 0x1c2 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 150.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && v10 < 70.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0xc8 && m_gauge >= 0x3e8 && v10 < 120.0) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x190) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 2) + 0xa;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 2) + 0x1e;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                return;
            }
        }
        if (pattern == 0xcb) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + 0x28;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1c2) {
                m_command = ((WORD)Random(0, 2) == 0) + 0xa;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && m_gauge >= 0x3e8) {
                m_command = 0x78;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (v10 < 90.0 && m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 100.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 2) + 0x28;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x64) {
                m_command = (WORD)Random(0, 2) + 0x1e;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + 0x28;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && v10 < 140.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && v10 < 70.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + 0x1e;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x15e) {
                m_command = (WORD)Random(0, 2) + 0x28;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x29e && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + 0x78;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xcf) {
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
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
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
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == 0xe7) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x15e) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1f4) {
                m_command = 0x28;
                return;
            }
            if (m_cpuRoll > 0x190) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xea) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x15e) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1f4) {
                m_command = 0x28;
                return;
            }
            if (m_cpuRoll > 0x190) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xeb) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xd2 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x15e) {
                m_command = (WORD)Random(0, 3) + 0x28;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
            }
        }
        if (pattern == 0xe9 && m_cpuRoll > 0x1f4) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
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
                if (v10 < 60.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 45.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 50.0 && v10 < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x41 && m_cpuRoll > 0x28) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 95.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x14 + 0x50 && m_cpuRoll > 0x46) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (0x50 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 110.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x80 && m_cpuRoll > 0x78) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (v10 < 180.0 && v10 > 200.0 && m_cpuRoll < 0xfa && m_cpuRoll > 0x96) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (v10 < 130.0 && v10 > 100.0 && m_cpuRoll < 0xc3 && m_cpuRoll > 0xaa) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (0x50 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x50 < v10 && v10 < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0xb9 && m_cpuRoll > 0xaa) {
                        m_cpuAction = 0xe;
                        return;
                    }
                }
                if (0x5a - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x5a < v10 && v10 < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0xe1 && m_cpuRoll > 0xd2) {
                        m_cpuAction = 0xa;
                        return;
                    }
                }
                if (v10 > 130.0 && v10 < 170.0 && m_cpuRoll < 0x104 && m_cpuRoll > 0xfa) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x113 && m_cpuRoll > 0x104 && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x16;
                    return;
                }
                if (v10 < 150.0 && m_cpuRoll < 0x118 && m_cpuRoll > 0x113 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > 0xc7) {
                    m_command = (WORD)Random(0, 2) + 0x65;
                    return;
                }
                if (v10 > 150.0 && m_cpuRoll < 0x11d && m_cpuRoll > 0x118 && m_gauge >= 0xbb8) {
                    m_command = 0x67;
                    return;
                }
                if (v10 > 160.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c) {
                    m_command = 0x28;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && m_cpuRoll < 0x140 && m_cpuRoll > 0x136) {
                    m_command = 0x29;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && m_cpuRoll < 0x145 && m_cpuRoll > 0x140) {
                    m_command = 0x2a;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x14a) {
                    m_command = 0xa;
                    return;
                }
                if (v10 > 160.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = 0xb;
                    return;
                }
                if (v10 > 40.0 && v10 < 120.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = 0x1e;
                    return;
                }
                if (v10 > 140.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = 0x1f;
                    return;
                }
                if (m_cpuRoll < 0x320 && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c && v10 > 100.0) {
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
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x15;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x16;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 0xf) {
                        m_command = 0x15;
                        return;
                    }
                    if (v10 < 160.0 && v10 > 80.0 && x8 < 300.0 && x8 > 160.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x1e) {
                        m_command = 0xc;
                        return;
                    }
                    if (v10 < 150.0 && m_cpuRoll < 0xdc && m_cpuRoll > 0xc8 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + 0x64;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 100.0 && x8 > 60.0 && x8 < 120.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
                    m_pressC = 1;
                    return;
                }
                if (m_cpuRoll > 0xf0 && m_cpuRoll < 0xfa) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                    return;
                }
                if (m_cpuRoll > 0xfa && m_cpuRoll < 0x104) {
                    m_command = 0x28;
                    return;
                }
                if (v10 > 150.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109 && x8 > 150.0) {
                    m_command = (WORD)Random(0, 3) + 0x6e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 100.0 && x8 > 0.0 && x8 < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x3c) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 50.0 && v10 < 130.0 && x8 > 0.0 && x8 < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 0x3c && m_cpuRoll < 0x64) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)Random(0, 0x64) < 5.0f * unka8 && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 800.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < 3.0f * unka8 && x > 150.0 && x < 490.0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 8.0f * unka8) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (v10 > 180.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 140.0 && y == 0.0 && (*m_opponent)->pattern < 0x32) {
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
    if ((WORD)Random(0, 0x64) < 0x32 && v10 < 120.0) {
        if (facing == 1) {
            unk1a4 = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            unk1a0 = (WORD)Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x32) {
        if (facing == 1) {
            unk1a0 = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            unk1a4 = (WORD)Random(0, 0xc8) + 0x3c;
        }
        return;
    }
    if (facing == -1) {
        unk1a0 = (WORD)Random(0, 0xc8) + 0x3c;
        return;
    }
    unk1a4 = (WORD)Random(0, 0xc8) + 0x3c;
}

void CNayukiB::UpdateObjects()
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].unk84 = 3;
                    unk3158[v4]++;
                }
                if (m_objects[v4].y < -600.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk80 = 0;
                    }
                }
                break;
            case 0x191:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].unk84 = 6;
                    unk3158[v4]++;
                    unk3258[v4] = 0;
                }
                unk3258[v4]++;
                if (unk3258[v4] > 0xa) {
                    unk3258[v4] = 0;
                    l50.type = 0x193;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].y < -600.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 5 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0xf) {
                        m_objects[v4].unk80 = 0;
                    }
                }
                break;
            case 0x192:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].unk84 = 0xf;
                    unk3158[v4]++;
                    unk3258[v4] = 0;
                }
                unk3258[v4]++;
                if (unk3258[v4] > 3) {
                    unk3258[v4] = 0;
                    l50.type = 0x193;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].y < -600.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 4 || m_objects[v4].frame == 8 || m_objects[v4].frame == 0xc || m_objects[v4].frame == 0x10) {
                        m_objects[v4].unk80 = 0;
                    }
                }
                break;
            case 0x193:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = 1.0;
                    m_objects[v4].vy = -2.2;
                    m_objects[v4].unk84 = 0;
                    unk3158[v4]++;
#ifdef EFZ_NATIVE
                    // The original computes the arguments right to left, so the speed draws first.
                    {
                        double speed = (double)((WORD)Random(0, 3) + 2);
                        m_objects[v4].SetVelocity((double)(WORD)Random(0, 0x168), speed);
                    }
#else
                    m_objects[v4].SetVelocity((double)(WORD)Random(0, 0x168), (double)((WORD)Random(0, 3) + 2));
#endif
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x194:
                if (unk3150 <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)unk3148, 50.0);
                m_objects[v4].x = m_objects[v4].vx * unk3154 + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].pattern = 0x196;
                    m_objects[v4].scale = 2;
                    unk3150 -= 0x3e8 - unk314c * 0x15e;
                    break;
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
                if (unk3150 <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)(unk3148 + 0xb4), 50.0);
                m_objects[v4].x = m_objects[v4].vx * unk3154 + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].pattern = 0x197;
                    m_objects[v4].scale = 2;
                    unk3150 -= 0x3e8 - unk314c * 0x15e;
                    break;
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
            case 0x196:
                if (unk3150 <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)unk3148, 50.0);
                m_objects[v4].x = m_objects[v4].vx * unk3154 + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x198;
                        m_objects[v4].scale = 2;
                    }
                }
                break;
            case 0x197:
                if (unk3150 <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)(unk3148 + 0xb4), 50.0);
                m_objects[v4].x = m_objects[v4].vx * unk3154 + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x199;
                        m_objects[v4].scale = 2;
                    }
                }
                break;
            case 0x198:
                if (unk3150 <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].SetVelocity((double)unk3148, 50.0);
                m_objects[v4].x = m_objects[v4].vx * unk3154 + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x194;
                        m_objects[v4].scale = 0;
                        m_objects[v4].facing = facing;
                        l50.type = 0x19b;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_playVoice = 8;
                    }
                }
                break;
            case 0x199:
                if (unk3150 <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].SetVelocity((double)(unk3148 + 0xb4), 50.0);
                m_objects[v4].x = m_objects[v4].vx * unk3154 + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x195;
                        m_objects[v4].scale = 0;
                        m_objects[v4].facing = facing;
                        l50.type = 0x19b;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_playVoice = 8;
                    }
                }
                break;
            case 0x19b:
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 9;
                    }
                    if (m_objects[v4].frame == 0xd && unk3158[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19d:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xa;
                    }
                    if (m_objects[v4].frame == 0xd && unk3158[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19e:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xb;
                    }
                    if (m_objects[v4].frame == 0xd && unk3158[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19f:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                    unk3258[v4] = 0;
                    unk3358[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    if (unk3358[v4] == 6) {
                        unk3258[v4] = 0;
                        unk3358[v4] = 0;
                        m_objects[v4].frame = 7;
                        m_objects[v4].timer = 0;
                        l50.type = 0x1ab;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 25.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk0 = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        l50.type = 0x1ad;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                        m_playSound = 0x16;
                        ShakeScreen(5, 5);
                        break;
                    }
                    if (unk3258[v4] == 0xf) {
                        if (unk3358[v4] < 5) {
                            l50.type = unk3358[v4] + 0x1b1;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y - 50.0;
                            l50.scale = 0;
                            l50.layer = 1;
                            l50.facing = 1;
                            SpawnObject(&l50);
                        }
                        unk3358[v4]++;
                        unk3258[v4] = 0;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].frame = 5;
                        unk3258[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xc) {
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xc;
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objects[v4].frame == 0xd && unk3158[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0xd) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_playVoice = 0x10;
                        l50.type = 0x1ae;
                        l50.x = m_objects[v4].x;
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0x10 && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = 0xf;
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                        unk3158[v4]++;
                        l50.type = 0x1ae;
                        l50.x = m_objects[v4].x;
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    l50.type = 0x1af;
                    l50.x = m_objects[v4].x + (m_objects[v4].facing << 2);
                    l50.y = m_objects[v4].y - 38.0;
                    l50.unk0 = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xf;
                    }
                    if (m_objects[v4].frame == 0xd && unk3158[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 0;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -((WORD)Random(0, 0x14) * 0.1 + 0.25);
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    l50.type = 0x1af;
                    l50.x = m_objects[v4].x - (m_objects[v4].facing << 2);
                    l50.y = m_objects[v4].y - 38.0;
                    l50.unk0 = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = -m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * -1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xf;
                    }
                    if (m_objects[v4].frame == 0xd && unk3158[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 0;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 * facing + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xe;
                        l50.type = 0x1a6;
                        l50.x = m_objects[v4].x;
                        l50.y = 0.0;
                        l50.unk0 = 1;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a6:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = -0.5;
                    unk3158[v4] = 0;
                    unk3258[v4] = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].unk84 = 1;
                }
                unk3158[v4]++;
                if (unk3158[v4] == 2) {
                    l50.type = 0x1ac;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y - 10.0;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    unk3158[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].unk84 = 1;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3258[v4] < 0xa) {
                            unk3258[v4]++;
                            m_objects[v4].frame = m_objects[v4].frame - 4;
                            break;
                        }
                        l50.type = 0x1ab;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 25.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk0 = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        l50.type = 0x1ad;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        m_playSound = 0x16;
                        ShakeScreen(5, 5);
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a7:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0x10) {
                        l50.type = 0x1a8;
                        l50.unk0 = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 5;
                        l50.y = m_objects[v4].y - 10.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_playVoice = 0x12;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3158[v4] < 8) {
                        m_objects[v4].frame = 0xf;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -1.0;
                    unk3158[v4]++;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].y >= 0.0) {
                    if (m_objects[v4].frame < 2) {
                        m_objects[v4].frame = m_objects[v4].frame + 2;
                    }
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 1.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].x > 650.0 || m_objects[v4].x < -10.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1a9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    unk3158[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].unk80 = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = 0x1b1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = 0x1b2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = 0x1b3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = 0x1b4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0x10 && unk3158[v4] < 0xf) {
                        m_objects[v4].frame = 0xc;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].unk80 = 0;
                        m_playVoice = 0x11;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ab:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3158[v4] = (WORD)Random(0, 0x168);
                    unk3258[v4] = (WORD)Random(0, 0x64);
                }
                unk3258[v4] -= 3;
                if (unk3258[v4] < 0xa) {
                    unk3258[v4] = 0xa;
                }
                m_objects[v4].SetVelocity((double)unk3158[v4], unk3258[v4] * 0.1);
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ac:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3158[v4] = (WORD)Random(0, 0x168);
                    unk3258[v4] = (WORD)Random(0, 0x1e);
                }
                unk3258[v4] -= 4;
                if (unk3258[v4] < 5) {
                    unk3258[v4] = 5;
                }
                m_objects[v4].SetVelocity((double)unk3158[v4], unk3258[v4] * 0.1);
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ad:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0xa0) * 0.1 + -8.0;
                    m_objects[v4].vy = -8.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3158[v4] < 0x10) {
                            unk3158[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x1ac;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.facing = m_objects[v4].facing;
                            SpawnObject(&l50);
                            break;
                        }
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ae:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
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
            case 0x1af:
                m_objects[v4].vx = 2.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
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
            case 0x1b1:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b2:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b3:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b4:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b5:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    unk3258[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3158[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3258[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3258[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3258[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    unk3258[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3158[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3258[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3258[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3258[v4]--;
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
