// CKanna (0x675c80-0x68354f): the character class whose files are in kanna\ in the game
// folder (kanna.dat sprites, kanna.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CKanna::CKanna(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "kanna");
    lastSurface = 0x4db;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0x3c;
    m_pointX[0] = -4;
    m_pointY[0] = -0x3b;
    m_pointX[1] = 0x1b;
    m_pointY[1] = 0;
    m_pointX[2] = 0xb;
    m_pointY[2] = -0x12;
    m_pointX[3] = 0xb;
    m_pointY[3] = -0xd;
    m_pointX[4] = 0x21;
    m_pointY[4] = -0x23;
    m_resultPictures = 4;
    m_rivals[0] = 1;
    m_rivals[1] = 6;
    m_rivals[2] = 0x17;
    m_rivals[3] = 0x10;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3154[v4] = 0;
        unk3254[v4] = 0;
        unk3354[v4] = 0;
    }
}

void CKanna::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0x3c;
    m_pointX[0] = -0xd;
    m_pointY[0] = -0x3c;
    m_pointX[1] = 0xe;
    m_pointY[1] = 0;
    m_pointX[2] = 0x11;
    m_pointY[2] = -6;
    m_pointX[3] = 7;
    m_pointY[3] = -0x19;
    m_pointX[4] = 0x1b;
    m_pointY[4] = -0x19;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3154[v4] = 0;
        unk3254[v4] = 0;
        unk3354[v4] = 0;
    }
    CPlayer::Reset();
}

void CKanna::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CKanna::RemoveObject(short p1)
{
    unk3154[p1] = 0;
    unk3254[p1] = 0;
    unk3354[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CKanna::Move()
{
    if (y == 0.0) {
        unk159 = 0;
        unk15a = 0;
    }
    if (y >= 0.0 && pattern != 4 && pattern != 5 && pattern != 6 && pattern != 0xa && pattern != 0xb && pattern != 0xc) {
        if (unk15c < 3 && m_inputY == -1) {
            FaceOpponent();
            if (m_command >= 3 && m_command <= 5) {
                if (m_command == 3) {
                    if (pattern != 0xa) {
                        StartPattern();
                    }
                    pattern = 0xa;
                    return;
                }
                if (m_command == 4) {
                    if (pattern != 0xb) {
                        StartPattern();
                    }
                    pattern = 0xb;
                    return;
                }
                if (m_command == 5) {
                    if (pattern != 0xc) {
                        StartPattern();
                    }
                    pattern = 0xc;
                    return;
                }
            } else {
                if (m_inputX == 0) {
                    if (pattern != 4) {
                        StartPattern();
                    }
                    pattern = 4;
                    return;
                }
                if (m_inputX == facing) {
                    if (pattern != 5) {
                        StartPattern();
                    }
                    pattern = 5;
                    return;
                }
                if (m_inputX == -facing) {
                    if (pattern != 6) {
                        StartPattern();
                    }
                    pattern = 6;
                    return;
                }
            }
        }
        if (m_inputY == 1) {
            if (pattern != 8 && pattern != 3) {
                pattern = 8;
                StartPattern();
                FaceOpponent();
                return;
            }
            if (pattern != 8) {
                pattern = 3;
                FaceOpponent();
                return;
            }
            return;
        }
        if (m_inputX != 0) {
            FaceOpponent();
            if (m_inputX == facing) {
                if (pattern != 0 && pattern != 1 && pattern != 2) {
                    StartPattern();
                }
                pattern = 1;
                return;
            }
            if (pattern != 0 && pattern != 1 && pattern != 2) {
                StartPattern();
            }
            pattern = 2;
            return;
        }
        if (pattern == 3 || pattern == 8) {
            pattern = 7;
            FaceOpponent();
            StartPattern();
            return;
        }
        if (pattern == 7 || pattern == 0xd) {
            FaceOpponent();
            return;
        }
        if (pattern != 0 && pattern != 1 && pattern != 2) {
            StartPattern();
        }
        pattern = 0;
        FaceOpponent();
    }
}

void CKanna::StartCommand()
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
        if (m_command == 0x66 && m_gauge >= 0xbb8 && m_hp < 0xd05 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x135;
            return;
        }
        if (m_command == 0x65 && m_gauge >= 0xbb8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x64 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x65 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x12f;
            return;
        }
        if (m_command == 0x48 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10b].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x10b;
            return;
        }
        if ((m_command == 0x47 || m_command == 0x48) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10a].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x10a;
            return;
        }
        if (m_command == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10a].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x10a;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x101;
            return;
        }
        if ((m_command == 0x14 || m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x20 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x109].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x109;
            return;
        }
        if (m_command == 0x1f && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x108].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x108;
            return;
        }
        if (m_command == 0x1e && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x107].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x107;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfb;
            return;
        }
        if ((m_command == 0xa || m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xfa;
            if (y < 0.0) {
                pattern = 0xfd;
            }
            return;
        }
    }
    if (unk15c < 1 && (m_command == 0 || m_command == 1) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0) {
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
            unk158++;
            m_bufferedPress = 0;
            return;
        }
    }
    if (m_pressA == 1 || (m_bufferedPress & 0x10) != 0 || (m_dashBufferedPress & 0x10) != 0) {
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
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -110.0 && x - (*m_opponent)->x < 110.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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
        if (y < 0.0) {
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
        if ((m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) && m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0xcb;
        }
    }
}

void CKanna::DrawGauge()
{
}

void CKanna::Vf8()
{
}

void CKanna::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CKanna::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x6e;
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
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
        if ((v5 & 0xf) == 0 && x6 == 0) {
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
    v4 = m_inputPos + 0x5a;
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
    v4 = m_inputPos + 0x5a;
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

void CKanna::CpuInput()
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
    unk314c--;
    unk3150--;
    if (unk314c < 0) {
        unk314c = 0;
    }
    if (pattern > 0x31 && pattern < 0xa1) {
        unk314c = 0xb4;
    }
    if (unk3150 < 0) {
        unk3150 = 0;
    }
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
    if (pattern == 0xa8 && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 45.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if ((WORD)Random(0, 0x1f40) < unka8 * unka8 * 4.0f && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (v10 < 20.0) {
            if ((WORD)Random(0, 0x708) < unka8 * 4.0f && unk118 > 500.0) {
                m_command = 0x14;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5c;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && v10 < 120.0 && m_gauge >= 0x7d0) {
                m_command = 0x65;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if (v10 < 120.0 && (WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8 && (*m_opponent)->pattern < 0xdc) {
                m_command = 0x64;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)Random(0, 0x64) < unka8 * 1.0f) {
                m_command = 0x64;
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
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < unka8 * 2) {
            m_command = (WORD)Random(0, 2) + 0xa;
            return;
        }
        if ((WORD)Random(0, 0x3e8) < unka8 * 2) {
            m_command = 0x64;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && unk118 > 500.0) {
            m_command = 0x16;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0xbb8) {
            m_command = 0x64;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x14 && m_gauge == 0xbb8) {
            m_command = 0x65;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (m_cpuRoll < 2 && m_gauge >= 0xbb8) {
            m_command = 0x64;
            return;
        }
        if (m_cpuRoll < 4 && m_gauge >= 0xbb8) {
            m_command = 0x65;
            return;
        }
        if (m_cpuRoll > 0x3a) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x100 || pattern == 0xe8 && (WORD)Random(0, 0xa) == 0 || pattern == 0xeb && (WORD)Random(0, 7) == 0)) {
        m_command = 0x34;
        return;
    }
    if (y == 0.0 && pattern < 4 && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x96 && m_cpuAction == 0) {
        if ((*m_opponent)->y < 0.0 && x8 < 100.0 && v10 < 130.0 && ((*m_opponent)->unk124 > 0x18 || (*m_opponent)->unk128 == 1 || (*m_opponent)->pattern == 0x52 && (*m_opponent)->frame < 4)) {
            m_cpuAction = 0x1f;
            return;
        }
        if ((*m_opponent)->y < 0.0 && x8 < 50.0 && v10 < 70.0 && ((*m_opponent)->unk124 > 0x12 || (*m_opponent)->unk128 == 1 || (*m_opponent)->pattern == 0x52 && (*m_opponent)->frame < 4)) {
            m_cpuAction = 0x1e;
            return;
        }
        if ((*m_opponent)->pattern == 0x46 && m_gauge >= 0xbb8 && (WORD)Random(0, 0) != 0) {
            if (v10 < 150.0) {
                m_command = 0x65;
                return;
            }
            if (v10 > 150.0) {
                m_command = 0x64;
                return;
            }
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
    if (m_cpuAction == 3 && pattern == 0xd) {
        m_cpuAction = 0;
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
        m_inputX = 0;
        m_inputY = -1;
        if (pattern == 4) {
            m_cpuAction = 8;
        }
        return;
    }
    if (m_cpuAction == 7 && pattern < 0x32) {
        m_inputX = facing;
        m_inputY = -1;
        if (pattern == 5) {
            m_cpuAction = 8;
        }
        return;
    }
    if (m_cpuAction == 8 && pattern < 0x32) {
        m_inputX = facing;
        m_inputY = 1;
        if (pattern == 0x12) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 9 && pattern < 0x32) {
        m_inputX = facing;
        m_inputY = -1;
        if (pattern == 5) {
            m_cpuAction = 0xa;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < 0x32) {
        m_pressB = 1;
        if (pattern == 0xd0 || y == 0.0) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xb && pattern < 0x32) {
        m_inputX = 0;
        m_inputY = -1;
        if (pattern == 4) {
            m_cpuAction = 0xc;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < 0x32) {
        m_pressA = 1;
        if (pattern == 0xcf || y == 0.0) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xd && pattern < 0x32) {
        m_pressA = 1;
        if (pattern == 0xd0 || y == 0.0) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xe) {
        m_inputY = -1;
        m_inputX = facing;
        if (pattern == 5) {
            m_cpuAction = 0xf;
        }
        return;
    }
    if (m_cpuAction == 0xf) {
        if ((*m_opponent)->unk124 <= 0) {
            m_cpuAction = 0;
        }
        if (x8 < 80.0 && (*m_opponent)->y < y) {
            m_pressA = 1;
            if (pattern == 0xcf) {
                m_cpuAction = 0x10;
                return;
            }
        }
        if (x8 < 100.0) {
            m_pressB = 1;
            if ((*m_opponent)->unk124 < 0x18) {
                m_pressA = 1;
            }
            if (pattern == 0xd0 || pattern == 0xcf) {
                m_cpuAction = 0x10;
                return;
            }
        }
        return;
    }
    if (m_cpuAction == 0x10) {
        if ((*m_opponent)->unk124 <= 0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xcf && m_attackResult == 3) {
            m_pressB = 1;
            return;
        }
        if (pattern == 0xd0) {
            m_cpuAction = 0x11;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x11) {
        if ((*m_opponent)->unk124 <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if ((WORD)Random(0, 0xc8) == 1 && m_gauge == 0xbb8) {
            m_command = 0x65;
            return;
        }
        if (pattern == 0xd1) {
            m_cpuAction = 0;
            return;
        }
        if (pattern == 0xfd) {
            m_cpuAction = 0;
            return;
        }
        if (pattern == 0xa5) {
            m_cpuAction = 0x14;
            return;
        }
        if (pattern == 0xf) {
            m_cpuAction = 0x14;
            return;
        }
        if (pattern == 0xd0 && m_attackResult == 3 && frame > 5) {
            if (v10 > 80.0 && vx < 0.0 && (*m_opponent)->y - y > -40.0) {
                m_command = 0xa;
                return;
            }
            if ((*m_opponent)->unk124 < 0x2d && unk15a > 0 && x8 < 40.0 && (*m_opponent)->y - y < 0.0) {
                m_command = 0xa;
                return;
            }
            if ((*m_opponent)->unk124 < 0x2d && vx >= 0.0) {
                m_pressC = 1;
                return;
            }
            if ((x8 < 20.0 && (*m_opponent)->y > y || (*m_opponent)->y < y) && (*m_opponent)->unk124 > 0x54 && unk15a < 2) {
                m_inputX = facing;
                m_inputY = 0;
                return;
            }
            if (x8 > 90.0 && (*m_opponent)->y < y && (*m_opponent)->unk124 > 0x2d && unk15a < 2) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
        }
        return;
    }
    if (m_cpuAction == 0x14) {
        if ((*m_opponent)->unk124 <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xd0) {
            m_cpuAction = 0x11;
            return;
        }
        if (v10 < 130.0) {
            m_pressB = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x15) {
        if ((*m_opponent)->unk124 <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xd0) {
            m_cpuAction = 0x16;
            return;
        }
        if (v10 < 130.0) {
            m_pressB = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x16) {
        if ((*m_opponent)->unk124 <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xd1) {
            m_cpuAction = 0;
            return;
        }
        if (v10 < 130.0) {
            m_pressC = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x1e) {
        if ((*m_opponent)->unk124 <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xc8) {
            m_cpuAction = 0x1f;
            return;
        }
        if (v10 < 130.0) {
            m_pressA = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x1f) {
        if ((*m_opponent)->unk124 <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xc9 || pattern == 0xca) {
            m_cpuAction = 0x20;
            return;
        }
        m_pressB = 1;
        return;
    }
    if (m_cpuAction == 0x20) {
        if ((*m_opponent)->unk124 <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xcb) {
            m_cpuAction = 0x21;
            return;
        }
        if ((*m_opponent)->unk124 < 0x3c) {
            m_pressC = 1;
            return;
        }
        m_cpuAction = 0xe;
        return;
    }
    if (m_cpuAction == 0x21) {
        if ((*m_opponent)->unk124 <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xfa || pattern == 0xfb || pattern == 0x12f) {
            m_cpuAction = 0;
            return;
        }
        if ((WORD)Random(0, 0x64) < 2 && m_gauge >= 0xbb8) {
            m_command = 0x65;
            return;
        }
        if ((WORD)Random(0, 0x64) < 4 && (unk118 > 500.0 || unk120 > 0)) {
            m_command = 0xc;
            return;
        }
        if ((WORD)Random(0, 0x64) < 0xa) {
            m_command = 0xa;
            return;
        }
    }
    if (m_cpuAction == 0x22) {
        if (pattern > 4) {
            m_cpuAction = 0;
        }
        if (v10 < 50.0) {
            m_pressA = 1;
            m_inputY = 1;
            return;
        }
        if (v10 < 90.0) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
    }
    if (m_cpuAction == 0x24) {
        if (pattern < 4) {
            m_cpuAction = 0;
        }
        if (pattern == 0xab || pattern == 0xa7) {
            m_cpuAction = 0x25;
            return;
        }
        m_command = 0x34;
        return;
    }
    if (m_cpuAction == 0x25) {
        if (y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == 0xd0) {
            m_cpuAction = 0;
            return;
        }
        m_pressB = 1;
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
            if (v10 < 130.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 100.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3 && (*m_opponent)->unk124 > 0x3c) {
                m_cpuAction = 0xe;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3 && (*m_opponent)->unk124 <= 0x3c) {
                m_cpuAction = 0x1e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                m_cpuAction = 0xd;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_attackResult == 2 && m_cpuRoll > 0x15e && m_cpuRoll < 0x163) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 0x64) < 0x32) {
                    m_cpuAction = 6;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x2bc && v10 < 150.0) {
                m_pressC = 1;
                return;
            }
        }
        if (pattern == 0xca) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xa) {
                m_command = (WORD)Random(1, 3) + 0x46;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0xff && m_gauge >= 0xbb8 && m_attackResult == 3) {
                m_command = 0x65;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x258 && v10 < 140.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
        }
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + 0xa;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 5) + 0x46;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258 && m_attackResult == 2) {
                m_command = 0x1f;
                if (v10 < 120.0) {
                    m_command = 0x1e;
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
            if (v10 < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 130.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
        }
        if (pattern == 0xcd) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 0x1f4) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && v10 < 120.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x28a) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x276) {
                m_command = (WORD)Random(0, 5) + 0x46;
                return;
            }
        }
        if (pattern == 0xce) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x32) {
                m_command = (WORD)Random(0, 3) + 0x46;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x320 && m_attackResult == 3 && (unk118 > 500.0 || unk120 == 1)) {
                m_command = 0x16;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xcf) {
            if (m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_cpuAction = 0x10;
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
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
            if (m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_cpuAction = 0x11;
                return;
            }
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6 && m_attackResult != 3) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll > 0x15e && m_cpuRoll < 0x28a && y > -40.0 && m_attackResult == 3) {
                m_cpuAction = 0x22;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == 0xd1) {
            if (m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + 0x1f;
                return;
            }
            if (m_cpuRoll > 0x384 && m_attackResult != 3) {
                m_inputX = facing;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll < 0x15e && (unk118 > 500.0 || unk120 > 0) && m_attackResult == 3 && timer < 3 && frame == 4) {
                m_cpuAction = 0x24;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0x28a && y > -70.0 && m_attackResult == 3) {
                m_cpuAction = 0x22;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == 0xfa && v10 < 120.0 && unk118 > 500.0 && frame == 5 && m_cpuRoll < 0x64) {
            m_command = 0x34;
            return;
        }
        if (pattern > 0x106 && pattern < 0x10b && (WORD)Random(0, 0x64) < 0x28) {
            m_cpuAction = 5;
            return;
        }
    }
    if ((WORD)Random(0, 0x100) < unka8 * unka8 * unka8 * unka8) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (v10 < 40.0 && x8 < 90.0 && (*m_opponent)->pattern > 0xc7 && (WORD)Random(0, 0x9c4) < 0xa) {
            m_command = 0x14;
            return;
        }
        if (x8 < 90.0 && (*m_opponent)->pattern > 0xc7 && (WORD)Random(0, 0x2710) < 0xa && (unk118 > 500.0 || unk120 == 1)) {
            m_command = 0xc;
            return;
        }
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0xf && unk314c == 0) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 75.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x14 && unk314c == 0) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 40.0 && v10 < 140.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x2d && m_cpuRoll > 0x1e && unk314c == 0) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 140.0 && v10 > 60.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x50 && unk314c == 0) {
                    m_pressB = 1;
                    m_inputY = (WORD)Random(0, 0xa) < 5 ? 1 : 0;
                    return;
                }
                if (v10 < 70.0 && m_cpuRoll < 0x87 && m_cpuRoll > 0x82 && unk314c == 0) {
                    m_cpuAction = 9;
                    return;
                }
                if (v10 < 120.0 && m_cpuRoll < 0x96 && m_cpuRoll > 0x91 && unk314c == 0) {
                    m_cpuAction = 0xb;
                    return;
                }
                if (v10 > 50.0 && v10 < 180.0 && x8 < 50.0 && m_cpuRoll < 0x12c && m_cpuRoll > 0xfa && unk314c == 0) {
                    m_command = 0xa;
                    return;
                }
                if (x8 < 90.0 && m_cpuRoll < ((*m_opponent)->pattern > 0xc7) * 0xf + 0x131 && m_cpuRoll > 0x12c && unk314c == 0 && unk118 > 500.0) {
                    m_command = 0xc;
                    return;
                }
                if (v10 > 130.0 && m_cpuRoll < 0x145 && m_cpuRoll > 0x136 && unk314c == 0) {
                    m_command = 0x46;
                    return;
                }
                if (v10 > 130.0 && m_cpuRoll < 0x14a && m_cpuRoll > 0x145 && unk314c == 0) {
                    m_command = 0x48;
                    return;
                }
                if (v10 < 130.0 && m_cpuRoll < 0x159 && m_cpuRoll > 0x154 && unk314c == 0 && unk118 > 500.0) {
                    m_command = 0x48;
                    return;
                }
                if (v10 > 200.0 && v10 < 240.0 && m_cpuRoll < 0x172 && m_cpuRoll > 0x16d && unk314c == 0) {
                    m_command = 0x1e;
                    return;
                }
                if (v10 > 180.0 && v10 < 320.0 && m_cpuRoll < 0x17c && m_cpuRoll > 0x172 && unk314c == 0) {
                    m_command = 0x1f;
                    return;
                }
                if (v10 > 240.0 && v10 < 320.0 && m_cpuRoll < 0x190 && m_cpuRoll > 0x17c && unk314c == 0) {
                    m_command = 0x20;
                    return;
                }
                if (v10 < 120.0 && m_cpuRoll < 0x195 && m_cpuRoll > 0x190 && unk314c == 0 && m_gauge >= 0xbb8 && (*m_opponent)->unkac != 0) {
                    m_command = 0x5c;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && unk118 > 500.0 && m_cpuRoll < 2) {
                    m_command = 0x16;
                    return;
                }
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 40.0 && x8 < 120.0 && m_cpuRoll < 0x1e) {
                        m_inputY = 0;
                        m_pressB = 1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && m_cpuRoll < ((*m_opponent)->pattern > 0xc7) * 0x2d + 0xf && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x14;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 170.0 && x8 > 80.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 60.0 && x8 < 210.0 && x8 > 120.0 && m_cpuRoll < 0xb4 && m_cpuRoll > 0x64) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if (v10 < 180.0 && x8 < 180.0 && (*m_opponent)->pattern > 0xc8 && m_cpuRoll < 5 && m_gauge >= 0xbb8) {
                m_command = 0x65;
                return;
            }
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 100.0 && x8 < 100.0 && m_cpuRoll > 0 && m_cpuRoll < 0x258) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 110.0 && x8 < 180.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x28a) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0xc8 && (*m_opponent)->y < y) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 140.0 && x8 > 60.0 && x8 < 140.0 && (*m_opponent)->y > y && m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa) {
                    m_pressB = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)Random(0, 0x1388) < 4.0f * unka8 * unka8 * unka8 && unk314c == 0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 80.0 && v10 < 120.0 && (WORD)Random(0, 0x2710) < unka8 * unka8 * unka8 && x > 150.0 && x < 490.0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if (pattern == 9 || pattern == 0xa || pattern > 0xd && pattern < 0x15) {
        if (v10 > 100.0) {
            if ((WORD)Random(0, 0x44c) < 2 && unk3150 == 0) {
                unk3150 = 0xb4;
            }
            if ((WORD)Random(0, 0x64) < 2 && y > -180.0 && unk3150 == 0) {
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < 4 && unk3150 == 0) {
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < 2 && unk3150 == 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0) != 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
        }
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x3e8) < 2) {
                m_inputY = 1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((WORD)Random(0, 0x1f4) < 2 && unk3150 == 0) {
                m_inputX = -facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < 2 && unk3150 == 0) {
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < 4 && unk3150 == 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
        }
    }
    if ((WORD)Random(0, 0x1f4) < 0xa && y == 0.0) {
        if ((WORD)Random(0, 0x64) < 4) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 > 40.0 && v10 < 150.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_cpuAction = 6;
            return;
        }
        if (v10 > 150.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_cpuAction = 7;
            return;
        }
        if (v10 > 200.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_inputX = -facing;
            m_inputY = -1;
            return;
        }
    }
    if (y == 0.0) {
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
        if ((WORD)Random(0, 0x3e8) < 2) {
            if (facing == 1) {
                unk1a4 = (WORD)Random(0, 0xc8) + 0x3c;
            } else {
                unk1a0 = (WORD)Random(0, 0xc8) + 0x3c;
            }
        }
        if ((WORD)Random(0, 0x64) < 2) {
            if (facing == 1) {
                unk1a0 = (WORD)Random(0, 0x190) + 0x3c;
                return;
            }
            unk1a4 = (WORD)Random(0, 0x190) + 0x3c;
        }
    }
}

void CKanna::UpdateObjects()
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
                if (unk3154[v4] == 0) {
                    unk3154[v4]++;
                    m_objects[v4].vy = -3.0;
                }
                if (m_objects[v4].vy < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.105;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].frame < 8 && pattern > 0x31 && pattern < 0x9d) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 8) {
                    m_objects[v4].vy += 0.055;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 9;
                        l50.type = 0x193;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x32);
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.unk28 = 1;
                        l50.unk0 = 1;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 8 && unk3254[v4] < 1) {
                        m_objects[v4].frame = 0;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].vy = 7.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x191:
                if (unk3154[v4] == 0) {
                    unk3154[v4]++;
                    m_objects[v4].vy = -3.0;
                }
                if (m_objects[v4].vy < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.105;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].frame < 8 && pattern > 0x31 && pattern < 0x9d) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 8) {
                    m_objects[v4].vy += 0.055;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 9;
                        l50.type = 0x193;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x7d);
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.unk28 = 1;
                        l50.unk0 = 1;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 8 && unk3254[v4] < 1) {
                        m_objects[v4].frame = 0;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].vy = 7.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x192:
                if (unk3154[v4] == 0) {
                    unk3154[v4]++;
                    m_objects[v4].vy = -3.0;
                }
                if (m_objects[v4].vy < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.105;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].frame < 8 && pattern > 0x31 && pattern < 0x9d) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 8) {
                    m_objects[v4].vy += 0.055;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 9;
                        l50.type = 0x193;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0xc8);
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.unk28 = 1;
                        l50.unk0 = 1;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 8 && unk3254[v4] < 1) {
                        m_objects[v4].frame = 0;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].vy = 7.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x193:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    ShakeScreen(5, 0);
                    m_playVoice = 3;
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
            case 0x194:
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 0x63;
                    m_objects[v4].vx = 3.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4]++;
                }
                if (m_objects[v4].unk80 >= 2) {
                    m_objects[v4].pattern = 0x199;
                    m_objects[v4].unk84 = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].frame > 0x2e4) {
                    RemoveObject(v4);
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 1.2) {
                    m_objects[v4].vx = 1.2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x197:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 3.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].unk80 >= 2 || pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].pattern = 0x19a;
                    m_objects[v4].unk84 = 0;
                    break;
                }
                m_objects[v4].vx -= 0.015;
                if (m_objects[v4].vx < 0.4) {
                    m_objects[v4].vx = 0.4;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x198:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x199:
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
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 2.5;
                    m_objects[v4].vy = -1.2 - (WORD)Random(0, 0x14) * 0.1;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0 && m_objects[v4].frame == 1) {
                    RemoveObject(v4);
                    break;
                }
                if ((m_objects[v4].y >= 0.0 || m_objects[v4].unk80 > 1) && m_objects[v4].frame == 0) {
                    m_objects[v4].y--;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    l50.type = 0x19c;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
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
            case 0x19c:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 1.5;
                    m_objects[v4].vy = -1.5;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
                    break;
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
            case 0x19d:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 1.7;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.1;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0 && m_objects[v4].frame == 1) {
                    RemoveObject(v4);
                    break;
                }
                if ((m_objects[v4].y >= 0.0 || m_objects[v4].unk80 > 1) && m_objects[v4].frame == 0) {
                    m_objects[v4].y--;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    l50.type = 0x19e;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
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
            case 0x19e:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 1.5;
                    m_objects[v4].vy = -1.5;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
                    break;
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
            case 0x19f:
                if (unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4]++;
                    m_objects[v4].vx = -3.0;
                    m_objects[v4].vy = 0.5;
                }
                m_objects[v4].vy = m_objects[v4].vy - m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].x > 680.0 && m_objects[v4].facing == 1 || m_objects[v4].x < -60.0 && m_objects[v4].facing == -1 || m_objects[v4].y < -320.0) {
                    RemoveObject(v4);
                    break;
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
            case 0x1a0:
                if (unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0x64) * 0.01 + 1.0;
                    m_objects[v4].ay = (WORD)Random(0, 0x64) * 0.0002;
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].frame = Random(0, 0xf);
                }
                m_objects[v4].vy = m_objects[v4].vy - m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].x > 680.0 && m_objects[v4].facing == 1 || m_objects[v4].x < -60.0 && m_objects[v4].facing == -1 || m_objects[v4].y < -320.0) {
                    RemoveObject(v4);
                    break;
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
            case 0x1a1:
                if (unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0x64) * 0.01 + 3.5;
                    m_objects[v4].ay = (WORD)Random(0, 0x64) * 0.00015;
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].frame = Random(0, 0xf);
                }
                m_objects[v4].vy = m_objects[v4].vy - m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].x > 680.0 && m_objects[v4].facing == 1 || m_objects[v4].x < -60.0 && m_objects[v4].facing == -1 || m_objects[v4].y < -320.0) {
                    RemoveObject(v4);
                    break;
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
            case 0x1a2:
                if (pattern == 0x12f) {
                    m_objects[v4].x = m_objects[v4].facing * 0xa + x + 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0xd && pattern == 0x12f) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a3:
                m_objects[v4].timer++;
                if (pattern == 0x100 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1a4:
                if (pattern != 0xc9) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0xc9 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1a5:
                if (pattern != 0xca) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0xca && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1a6:
                if (pattern != 0xcd) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0xcd && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1a7:
                if (pattern != 0xd0) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0xd0 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1a8:
                if (pattern != 0xcb) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0xcb && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1a9:
                if (pattern != 0xd1) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0xd1 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1aa:
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
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
            case 0x1ab:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 4) {
                        l50.type = 0x1ac;
                        l50.x = (double)m_game->m_view.left;
                        l50.y = (double)((int)m_objects[v4].y - 0x3c);
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ac:
                m_objects[v4].x = m_game->m_view.left;
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
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 4) {
                        l50.type = 0x1ae;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        l50.unk0 = 1;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ae:
                if (unk3154[v4] == 0) {
                    unk3154[v4]++;
                    m_objects[v4].unk84 = 1;
                    if (unk3138 == 0) {
                        m_objects[v4].SetVelocity(-140.0, 3.0);
                    }
                    if (unk3138 == 1) {
                        m_objects[v4].SetVelocity(-165.0, 3.0);
                    }
                    if (unk3138 == 2) {
                        m_objects[v4].SetVelocity(-170.0, 3.0);
                    }
                    if (unk3138 == 3) {
                        m_objects[v4].SetVelocity(140.0, 3.0);
                    }
                    if (unk3138 == 4) {
                        m_objects[v4].SetVelocity(165.0, 3.0);
                    }
                    if (unk3138 == 5) {
                        m_objects[v4].SetVelocity(170.0, 3.0);
                    }
                    unk3138++;
                    if (unk3138 == 6) {
                        unk3138 = 0;
                    }
                }
                m_objects[v4].vx += 0.025;
                if (m_objects[v4].y > (*m_opponent)->y - 45.0) {
                    m_objects[v4].vy -= 0.015;
                }
                if (m_objects[v4].y < (*m_opponent)->y - 45.0) {
                    m_objects[v4].vy += 0.015;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1af;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x > 900.0 || m_objects[v4].x < -360.0 || m_objects[v4].unk80 > 0) {
                    m_objects[v4].pattern = 0x1af;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
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
            case 0x1af:
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
            case 0x1b0:
                if (pattern != 0x135) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0x135 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1b1:
                if (pattern != 0x135) {
                    RemoveObject(v4);
                }
                m_objects[v4].unk8c = 0x7530;
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (frame == 0x37 && m_objects[v4].frame < 0x50) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x50;
                    break;
                }
                if (frame > 0x37) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x50 && frame < 0x37) {
                        m_objects[v4].frame = 0x38;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0x6c;
                    }
                }
                break;
            case 0x1b2:
                if (pattern != 0x135) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0x135 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1b3:
                if (pattern != 0x135) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == 0x135 && unk14a > 0) {
                    m_objects[v4].timer--;
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
            case 0x1b4:
                m_objects[v4].unk8c = 0x7530;
                if (pattern != 0x135 || frame > 0x35) {
                    RemoveObject(v4);
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
            case 0x1b5:
                m_objects[v4].unk8c = 0x7530;
                if (pattern != 0x135 || frame > 0x35) {
                    RemoveObject(v4);
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
            case 0x1b6:
                m_objects[v4].unk8c = 0x7530;
                if (pattern != 0x135 || frame > 0x35) {
                    RemoveObject(v4);
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
            case 0x1b7:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                unk3154[v4]++;
                if (unk3154[v4] == 0x96) {
                    l50.type = 0x1ba;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.facing = 1;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3154[v4] == 0xd2) {
                    l50.type = 0x1bb;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.facing = 1;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3154[v4] == 0x10e) {
                    l50.type = 0x1bc;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.facing = 1;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3154[v4] == 0x12c) {
                    l50.type = 0x1bd;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.facing = 1;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3154[v4] == 0x14a) {
                    l50.type = 0x1be;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.facing = 1;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3154[v4] == 0x153) {
                    l50.type = 0x1bf;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.facing = 1;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
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
            case 0x1b8:
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
            case 0x1b9:
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
            case 0x1ba:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1bb:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1bc:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1bd:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1be:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1bf:
                if (pattern != 0x135 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x1c0:
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    unk3254[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3154[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3254[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3254[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3254[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    unk3254[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3154[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3254[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3254[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3254[v4]--;
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
