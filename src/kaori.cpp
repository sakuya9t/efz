// CKaori (0x638d90-0x6429bf).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CKaori::CKaori(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "kaori");
    lastSurface = 0x1ae;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    m_pointX[0] = -8;
    m_pointY[0] = -0x35;
    m_pointX[1] = -0x19;
    m_pointY[1] = 0;
    m_pointX[2] = 0;
    m_pointY[2] = -5;
    m_pointX[3] = 2;
    m_pointY[3] = -0xd;
    m_pointX[4] = 0x1f;
    m_pointY[4] = -0x1d;
    m_resultPictures = 5;
    m_rivals[0] = 8;
    m_rivals[0xa] = 0xd;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
}

void CKaori::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    m_pointX[0] = -8;
    m_pointY[0] = -0x35;
    m_pointX[1] = -0x19;
    m_pointY[1] = 0;
    m_pointX[2] = 0;
    m_pointY[2] = -5;
    m_pointX[3] = 2;
    m_pointY[3] = -0xd;
    m_pointX[4] = 0x1f;
    m_pointY[4] = -0x1d;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
    CPlayer::Reset();
}

void CKaori::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CKaori::RemoveObject(short p1)
{
    unk314c[p1] = 0;
    unk324c[p1] = 0;
    unk334c[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CKaori::Move()
{
    Unk40e740();
}

void CKaori::StartCommand()
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
    if (m_command == 0x34 && (unk118 >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || unk120 > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        StartPattern();
        ClearBufferedPress();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x5d && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_attackResult != 6 && m_patterns[pattern].unk2 <= m_patterns[0x13b].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x13b;
            return;
        }
        if (m_command == 0x7a && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x13a;
            return;
        }
        if ((m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x139;
            return;
        }
        if ((m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x138].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x138;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x130;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x136].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x136;
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x134;
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x102;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x101;
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x20 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (unk118 >= 500.0 || unk120 > 0) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xff;
            return;
        }
        if (m_command == 0x1f && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfe;
            return;
        }
        if (m_command == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfd;
            return;
        }
    }
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -30.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xfa) {
                    StartPattern();
                }
                pattern = 0xfa;
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
                unk158++;
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
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -50.0 && x - (*m_opponent)->x < 50.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && (*m_opponent)->y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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

void CKaori::DrawGauge()
{
}

void CKaori::Vf8()
{
}

void CKaori::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CKaori::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 6) {
            m_command = 0x5d;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0 && m_gauge == 0xbb8) {
            x6 = 1;
        }
    }
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

void CKaori::CpuInput()
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
            if (v10 < 35.0 && (WORD)Random(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 50.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
            m_pressB = 1;
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 90.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x14;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2) {
                m_command = 0xb;
                return;
            }
            if (v10 < 40.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0x7d0) {
                m_command = 0x79;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && v10 < 30.0 && m_gauge == 0xbb8) {
                m_command = 0x5a;
                return;
            }
        }
        if (v10 < 130.0 && v10 > 90.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if (v10 < 110.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 2) {
                m_command = 0x2a;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f) {
                m_command = 0xb;
                return;
            }
        }
        if (v10 > 130.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_command = 0x2a;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f) {
                m_command = 0xb;
                return;
            }
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 90.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            m_inputX = facing;
            return;
        }
        if ((WORD)Random(0, 0x64) < unka8 * 2) {
            m_command = 0x2a;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 2 && unk118 > 500.0) {
            m_command = 0x16;
            return;
        }
        if (m_cpuRoll < 5 && m_cpuRoll > 2 && unk118 > 500.0) {
            m_command = 0x14;
            return;
        }
        if (m_cpuRoll < 8 && m_cpuRoll > 5) {
            m_command = 0xa;
            return;
        }
        if (m_cpuRoll < 0xc && m_cpuRoll > 8 && v10 < 50.0) {
            m_command = 0x2a;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x14 && v10 < 30.0 && m_gauge == 0xbb8) {
            m_command = 0x5a;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 2) {
            m_command = 0x2a;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0xfd || pattern == 0xfe || pattern == 0xff || pattern == 0x109 && y < -110.0 || pattern == 0x10f || pattern == 0x110 || pattern == 0x111)) {
        m_command = 0x34;
        return;
    }
    if (pattern > 0xff && pattern < 0x106 && (WORD)Random(0, 0x64) > 1e+01f * unka8) {
        if (x8 * 0.5 > v10) {
            m_pressC = 1;
            return;
        }
        if (v10 < 30.0 && x8 < 50.0) {
            m_pressC = 1;
            m_inputX = -facing;
            return;
        }
        if (v10 < 20.0 && x8 > 80.0) {
            m_pressC = 1;
            m_inputY = 1;
            return;
        }
        if (v10 > 120.0 && x8 < v10) {
            m_command = (WORD)Random(0, 2) + 0xb;
            return;
        }
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
            if (v10 < 60.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0x190 && m_cpuRoll < 0x2bc) {
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
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
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
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2ee) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xa;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = 0xb;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x1f4) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x258) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0xe;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x10;
                }
                return;
            }
        }
        if (pattern == 0xcb) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = 0xb;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
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
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0xfa && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0x1c2 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x226) {
                m_command = 0xb;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x28a) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xce) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x258) {
                m_command = 0xb;
                return;
            }
            if (m_cpuRoll > 0x320 && m_cpuRoll < 0x352 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x6e;
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
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputX = facing * ((WORD)Random(0, 2) == 0);
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
            if (m_cpuRoll < 0xc8) {
                m_command = 0x2a;
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
        if (pattern == 0xe7 || pattern == 0xe6 || pattern == 0xe8 || pattern == 0xe9 || pattern == 0xea) {
            if (m_cpuRoll < 0x1c2) {
                m_command = (WORD)Random(0, 3) + 0x28;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + 0x1e;
                }
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x28a) {
                m_command = 0xb;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xa;
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
        if (pattern == 0x109 && m_cpuRoll > 0x258 && y == 0.0) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == 0xeb && m_cpuRoll > 0x258 && y == 0.0) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == 0xfb && m_cpuRoll > 0x2bb) {
            if ((WORD)Random(0, 2) == 0) {
                m_cpuAction = 6;
            }
            if ((WORD)Random(0, 4) == 0) {
                m_cpuAction = 8;
            }
            if ((WORD)Random(0, 3) == 0) {
                m_cpuAction = 0xa;
            }
            if ((WORD)Random(0, 4) == 0) {
                m_cpuAction = 0xc;
            }
            if ((WORD)Random(0, 4) == 0) {
                m_cpuAction = 0xe;
            }
            if ((WORD)Random(0, 3) == 0) {
                m_cpuAction = 0x10;
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
                if (v10 < 40.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0x41) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 < 55.0 && m_cpuRoll > 0x5a) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0x8c) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 > 80.0 && v10 < 100.0 && m_cpuRoll < 0xa0 && m_cpuRoll > 0x8c) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x28 + 0xc8 && m_cpuRoll > 0xa0) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x28 + 0x118 && m_cpuRoll > 0xf0) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (v10 < 120.0 && v10 > 60.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x140) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 120.0 && v10 > 80.0 && m_cpuRoll < 0x17c && m_cpuRoll > 0x168) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 150.0 && m_cpuRoll < 0x1ae && m_cpuRoll > 0x17c) {
                    m_cpuAction = 0xe;
                    return;
                }
                if (0x5a - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x5a < v10 && v10 < 130.0 && m_cpuRoll < 0x1d6 && m_cpuRoll > 0x1ae) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 > 90.0 && v10 < 150.0 && m_cpuRoll < 0x212 && m_cpuRoll > 0x1d6) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 > 180.0 && m_cpuRoll < 0x230 && m_cpuRoll > 0x226) {
                    m_command = 0xa;
                    return;
                }
                if (v10 < 100.0 && m_cpuRoll < 0x23a && m_cpuRoll > 0x230) {
                    m_command = (WORD)Random(0, 3) + 0x65;
                    return;
                }
                if (v10 > 100.0 && m_cpuRoll < 0x24e && m_cpuRoll > 0x23a) {
                    m_command = 0xa;
                    return;
                }
                if (v10 > 100.0 && m_cpuRoll < 0x262 && m_cpuRoll > 0x24e) {
                    m_command = 0xb;
                    return;
                }
                if (m_cpuRoll < 0x2ee && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c && v10 > 100.0) {
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0 && v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 90.0 && m_cpuRoll < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x16;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 90.0) {
                        if (m_cpuRoll < (unk118 > 500.0 || unk120 > 0) * 8 + 0xa) {
                            m_command = 0x14;
                            return;
                        }
                    }
                    if (v10 < 60.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c && x8 > 100.0 && m_gauge == 0xbb8) {
                        m_command = 0x66;
                        return;
                    }
                    if (v10 < 60.0 && m_cpuRoll < 0x140 && m_cpuRoll > 0x136 && x8 > 200.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 2) + 0x64;
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
                if (v10 < 80.0 && x8 > 90.0 && x8 < 80.0 && (*m_opponent)->y < y && m_cpuRoll > 0x64 && m_cpuRoll < 0xb4) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 100.0 && x8 < 130.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && y < (*m_opponent)->y && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 90.0 && x8 > 90.0 && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 100.0 && x8 > 70.0 && x8 < 100.0 && y < (*m_opponent)->y && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if (v10 > 90.0 && v10 < 130.0 && x8 > 40.0 && x8 < 120.0 && y > (*m_opponent)->y && m_cpuRoll > 0x32 && m_cpuRoll < 0x41) {
                    m_pressC = 1;
                    m_inputX = facing;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)Random(0, 0x64) < 5.0f * unka8 && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 2 && v10 > 90.0) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 4) {
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
    if ((WORD)Random(0, 0x64) < 0x28 && v10 < 120.0) {
        if (facing == 1) {
            unk1a4 = (WORD)Random(0, 0xc8) + 0x1e;
        } else {
            unk1a0 = (WORD)Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x46) {
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

void CKaori::UpdateObjects()
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
                m_objects[v4].timer++;
                if (pattern != 0x100 && pattern != 0x101 && pattern != 0x102 && m_objects[v4].frame < 0x3e) {
                    m_objects[v4].frame = 0x3e;
                }
                if (m_objects[v4].frame < 0x3e) {
                    m_objects[v4].x = facing * 0x28 + x;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x191:
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
            case 0x192:
                m_objects[v4].timer++;
                if (pattern < 0x12c || pattern > 0x131 || frame > 0x15) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x193:
                m_objects[v4].timer++;
                if (pattern < 0x12c || pattern > 0x131 || frame > 0x15) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x194:
                m_objects[v4].timer++;
                if (pattern < 0x12c || pattern > 0x131 || frame > 0x15) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x195:
                m_objects[v4].timer++;
                if (pattern < 0x12c || pattern > 0x131) {
                    RemoveObject(v4);
                }
                if (frame == 0x16) {
                    RemoveObject(v4);
                    l50.type = 0x191;
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x24);
                    l50.y = -47.0;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x3f);
                    l50.y = -62.0;
                    SpawnObject(&l50);
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x5a);
                    l50.y = -77.0;
                    SpawnObject(&l50);
                    break;
                }
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
                m_objects[v4].timer++;
                if (pattern < 0x12c || pattern > 0x131) {
                    RemoveObject(v4);
                }
                if (frame == 0x16) {
                    RemoveObject(v4);
                    l50.type = 0x191;
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x1e);
                    l50.y = -59.0;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x36);
                    l50.y = -33.0;
                    SpawnObject(&l50);
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x4e);
                    l50.y = -7.0;
                    SpawnObject(&l50);
                    break;
                }
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
                m_objects[v4].timer++;
                if (pattern < 0x12c || pattern > 0x131) {
                    RemoveObject(v4);
                }
                if (frame == 0x16) {
                    RemoveObject(v4);
                    l50.type = 0x191;
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x1e);
                    l50.y = -32.0;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.x = (double)((int)m_objects[v4].x + (facing << 5));
                    l50.y = -72.0;
                    SpawnObject(&l50);
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x22);
                    l50.y = -112.0;
                    SpawnObject(&l50);
                    break;
                }
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
                m_objects[v4].timer++;
                m_objects[v4].unk8c = 0x7530;
                if (pattern == 0x13c && frame == 3) {
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
            case 0x199:
                m_objects[v4].vx = 0.08;
                m_objects[v4].unk8c = 0x7530;
                m_objects[v4].timer++;
                if (pattern == 0x13c && frame == 3) {
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
            case 0x19a:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 0xf;
                }
                m_objects[v4].timer++;
                if (pattern != 0x100 && m_objects[v4].frame < 0x3e) {
                    m_objects[v4].frame = 0x3e;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x1e) {
                        m_objects[v4].frame = 0x3e;
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xe || m_objects[v4].frame == 0x11 || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x17 || m_objects[v4].frame == 0x1a || m_objects[v4].frame == 0x1d) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19b:
                m_objects[v4].timer++;
                if (m_objects[v4].frame < 0x3e) {
                    m_objects[v4].x = facing * 0x28 + x;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x1e) {
                        m_objects[v4].frame = 0x3e;
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
                    unk3148 = 0;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    unk324c[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk314c[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk324c[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk324c[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk324c[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    unk324c[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk314c[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk324c[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk324c[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk324c[v4]--;
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
