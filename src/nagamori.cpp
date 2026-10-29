// CNagamori (0x4add90-0x4c04af).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNagamori::CNagamori(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "nagamori");
    lastSurface = 0x2d7;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3148 = 0;
    unk3144 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3158 = 0;
    unk3160 = 0;
    unk315c = 0;
    unk3164 = 0;
    unk3168 = 0;
    unk2ad0[0] = -2;
    unk2af8[0] = -0x3d;
    unk2ad0[1] = 0x15;
    unk2af8[1] = 0;
    unk2ad0[2] = 0xc;
    unk2af8[2] = -5;
    unk2ad0[3] = 0x16;
    unk2af8[3] = -0x12;
    unk2ad0[4] = 0x19;
    unk2af8[4] = -0x17;
    unk30f4 = 5;
    unk30f5[0] = 0;
    unk30f5[1] = 5;
    unk30f5[2] = 0xa;
    unk30f5[3] = 1;
    unk30f5[0xa] = 6;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk316c[v4] = 0;
        unk31ac[v4] = 0;
        unk32ac[v4] = 0;
        unk33ac[v4] = 0;
    }
}

void CNagamori::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3148 = 0;
    unk3144 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3158 = 0;
    unk3160 = 0;
    unk315c = 0;
    unk3164 = 0;
    unk3168 = 0;
    unk2ad0[0] = -2;
    unk2af8[0] = -0x3d;
    unk2ad0[1] = 0x15;
    unk2af8[1] = 0;
    unk2ad0[2] = 0xc;
    unk2af8[2] = -5;
    unk2ad0[3] = 0x16;
    unk2af8[3] = -0x12;
    unk2ad0[4] = 0x19;
    unk2af8[4] = -0x17;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk316c[v4] = 0;
        unk31ac[v4] = 0;
        unk32ac[v4] = 0;
        unk33ac[v4] = 0;
    }
    CPlayer::Reset();
}

void CNagamori::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CNagamori::RemoveObject(short p1)
{
    unk316c[p1] = 0;
    unk31ac[p1] = 0;
    unk32ac[p1] = 0;
    unk33ac[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CNagamori::Unk4ae1d0(short p1, short p2, short p3, short p4)
{
    int v4;

    v4 = m_objectTail;
    while (v4 != m_objectHead) {
        if (m_objectActive[v4] != 0 && fabs(p1 - m_objects[v4].x) < p3 && fabs(p2 - m_objects[v4].y) < p4) {
            unk316c[v4] = 1;
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}

void CNagamori::Move()
{
    CPlayer::Unk40e740();
}

void CNagamori::StartCommand()
{
    if (pattern < 0xc8) {
        unk1a8 = 0;
    }
    if (unk1aa <= 0) {
        unk1a9 = 0;
    } else {
        unk1aa--;
    }
    if (unk1a9 == 0) {
        unk1aa = 0;
    }
    if (m_command == 0x34 && (unk118 >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || unk120 > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3150 == 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        StartPattern();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x5b && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].unk2 <= m_patterns[0x138].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x138;
            return;
        }
        if (m_command == 0x7a && m_gauge >= 0xbb8 && unk3148 == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x13b].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13b;
            return;
        }
        if ((m_command == 0x79 || m_command == 0x7a) && unk3148 == 0 && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13a;
            return;
        }
        if ((m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && unk3148 == 0 && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x139;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && unk3168 == 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x134;
            if (y < 0.0) {
                pattern = 0x137;
            }
            return;
        }
        if (m_command == 0x6f && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x132;
            if (y < 0.0) {
                pattern = 0x135;
            }
            return;
        }
        if (m_command == 0x6e && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x133;
            if (y < 0.0) {
                pattern = 0x136;
            }
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x2a && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0x110].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x110;
            return;
        }
        if ((m_command == 0x29 || m_command == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0x10f].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10f;
            return;
        }
        if (m_command == 0x28 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0x10e].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10e;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            return;
        }
        if (m_command == 0x20 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_gauge > 0x32 && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x101;
            if (y < 0.0) {
                pattern = 0x115;
            }
            return;
        }
        if (m_command == 0x1f && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_gauge > 0x32 && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            if (y < 0.0) {
                pattern = 0x114;
            }
            return;
        }
        if (m_command == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3148 == 0 && m_gauge > 0x32 && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            if (y < 0.0) {
                pattern = 0x113;
            }
            return;
        }
        if (m_command == 0xc && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk3148 == 0 && m_gauge > 0x32 && m_patterns[pattern].unk2 <= m_patterns[0x106].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x106;
            return;
        }
        if (m_command == 0xb && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk3148 == 0 && m_gauge > 0x32 && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk3148 == 0 && m_gauge > 0x32 && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x104;
            return;
        }
        if (m_command == 0xc && unk3148 == 0 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x10d].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10d;
            return;
        }
        if (m_command == 0xc && unk3148 != 0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x118].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x118;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x10c].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10c;
            if (unk3148 != 0) {
                pattern = 0x117;
            }
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x10b].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10b;
            if (unk3148 != 0) {
                pattern = 0x116;
            }
            return;
        }
    }
    if (unk15c < 3 && m_command == 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk15a < 1 && m_patterns[pattern].unk2 <= m_patterns[0xe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
        StartPattern();
        CPlayer::Unk40f170();
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
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa5) {
                    StartPattern();
                }
                pattern = 0xa5;
                CPlayer::FaceOpponent();
                unk159++;
                unk15a++;
                unk1a8 = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa6].unk0 && pattern != 0xaa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa6) {
                    StartPattern();
                }
                pattern = 0xa6;
                CPlayer::FaceOpponent();
                unk159++;
                unk15a++;
                unk1a8 = 0;
                return;
            }
        }
        if (y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa3].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa3) {
                    StartPattern();
                }
                pattern = 0xa3;
                CPlayer::FaceOpponent();
                unk158++;
                unk1a8 = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa4].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa4) {
                    StartPattern();
                }
                pattern = 0xa4;
                CPlayer::FaceOpponent();
                unk1a8 = 0;
                return;
            }
        }
    }
    if (m_pressA == 1 || (unk1a8 & 0x10) != 0 || (unk1a9 & 0x10) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xe6;
            if (m_inputY == 1) {
                pattern = 0xe9;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xcf].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xcf;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcc].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xcc;
            return;
        }
        if ((m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) && m_patterns[pattern].unk2 <= m_patterns[0xc8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xc8;
            return;
        }
    }
    if (m_pressB == 1 || (unk1a8 & 0x20) != 0 || (unk1a9 & 0x20) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xe7;
            if (m_inputY == 1) {
                pattern = 0xea;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd0].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd0;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd8;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -70.0 && x - (*m_opponent)->x < 70.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xc9;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xca].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xca;
                return;
            }
        }
    }
    if (m_pressC == 1 || (unk1a8 & 0x40) != 0 || (unk1a9 & 0x40) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xe8;
            if (m_inputY == 1) {
                pattern = 0xeb;
            }
            return;
        }
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf8].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xf8;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd1;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xce].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xce;
            if (unk3148 > 0) {
                pattern = 0xd7;
            }
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xcb;
            }
        }
    }
}

void CNagamori::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (unk3150 > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3150 > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, unk3150 * x1c.width / 0x4b0, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3150 * x1c.width / 0x4b0, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3150 * x1c.width / 0x4b0, 0x1f - x1c.y, unk3150 * x1c.width / 0x4b0, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CNagamori::Vf8()
{
    if (unk315c > 0) {
        unk315c--;
    }
}

void CNagamori::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CNagamori::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xe0) != 0 && x6 == 5) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 5) {
            m_command = 0x5b;
            return;
        }
        if (v5 == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xd0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_gauge == 0xbb8 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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

void CNagamori::CpuInput()
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
    if ((WORD)CPlayer::Random(0, 0x3e8) < 25.0f * unka8 + (y < 0.0) * 0x1e * unka8 + (unk3114 == 3) * 0x190 + (pattern == 0xaa) * 0x12c) {
        unk14e = 0x3c;
    }
    if ((WORD)CPlayer::Random(0, 0x7d0) < ((unk130 > 0) * 4.0 + 1.0) * 8.0 * unka8 * ((pattern > 0x95 && pattern < 0x9d) * 2 + 1)) {
        unk14e = 0x3c;
    }
    if ((WORD)CPlayer::Random(0, 0x3e8) < 4e+01f * unka8 && pattern > 0xc7) {
        unk14e = 0x3c;
    }
    if (unk170 == 1 && unk3114 == 2) {
        unk14e = 0x1e;
        if (pattern < 0xc8) {
            unk3114 = 0;
        }
        return;
    }
    if ((*m_opponent)->pattern == 0x60) {
        return;
    }
    v10 = ((*m_opponent)->x - x) * facing;
    x8 = fabs(y - (*m_opponent)->y);
    if (pattern >= 0x32 && pattern <= 0x96 && timer == 0) {
        if ((WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8) {
            unk3114 = 3;
        } else {
            unk3114 = 0;
        }
        m_inputX = 1 - (((WORD)CPlayer::Random(0, 0x64) < 0x32) << 1);
        m_pressD = (WORD)CPlayer::Random(0, 0xf0) < x8;
        m_pressD = (WORD)CPlayer::Random(0, 0x140) < v10;
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
            if (v10 < 40.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f + ((unk118 > 500.0) << 1)) {
                m_command = 0x48;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f + ((unk118 > 500.0) << 1)) {
                m_command = ((WORD)CPlayer::Random(0, 1) == 1) * 2 + 0x14;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && v10 < 60.0 && m_gauge >= 0x7d0) {
                m_command = 0x65;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && v10 < 150.0 && m_gauge == 0xbb8) {
                m_command = 0x66;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (v10 < 220.0 && v10 > 160.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0x46;
            return;
        }
        if (v10 > 220.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
            return;
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            unk3114 = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 0.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && x8 < 60.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
            m_command = 0x16;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 3 && unk118 > 500.0) {
            m_command = 0x48;
            return;
        }
        if (unk3110 < 7 && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (unk3110 < 0xa && unk118 > 500.0) {
            m_command = 0x14;
            return;
        }
        if (unk3110 < 0xd && unk118 > 500.0) {
            m_command = 0x16;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x7d0) {
            m_command = (WORD)CPlayer::Random(0, 1) + 0x65;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 0x14) {
            unk3114 = 2;
            return;
        }
        if (v10 < 100.0 && unk3110 < 0x16) {
            m_command = 0x16;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0xfa || pattern == 0xfb || pattern == 0xfc || pattern == 0x10e || pattern == 0x10f || pattern == 0x110)) {
        m_command = 0x34;
        return;
    }
    if (unk3114 > 0 && pattern > 0x31 && pattern < 0x9e) {
        unk3114 = 0;
    }
    if (unk3114 == 1 && pattern < 0xc8) {
        unk3114 = 0;
    }
    if (unk3114 == 2 && unk170 != 1) {
        unk3114 = 0;
        return;
    }
    if (unk3114 == 4) {
        m_inputY = -1;
        m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
        if (pattern == 4 || pattern == 5 || pattern == 6) {
            m_command = facing == 1;
            if (pattern == 0xa5) {
                unk3114 = 0;
            }
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (unk3114 == 5 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 6 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 7;
        }
        return;
    }
    if (unk3114 == 7 && pattern == 0xa3) {
        m_pressA = 1;
        if (pattern == 0xe6) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 8 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 9;
        }
        return;
    }
    if (unk3114 == 9 && pattern == 0xa3) {
        m_pressB = 1;
        if (pattern == 0xe7) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 0xa && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0xb;
        }
        return;
    }
    if (unk3114 == 0xb && pattern == 0xa3) {
        m_pressC = 1;
        if (pattern == 0xe8) {
            unk3114 = 0;
        }
        return;
    }
    if (m_attackResult > 1 && unk14a == 0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 25.0f && unk3114 != 1 && unk3114 != 2) {
        unk3110 = (WORD)CPlayer::Random(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 40.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)CPlayer::Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 125.0 && unk3110 > 0x18f && unk3110 < 0x2bc) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1b8 && m_attackResult == 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    unk3114 = 6;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x140 && unk3110 < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 < 0xc8) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0x1c2 && v10 < 90.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x1c2 && unk3110 < 0x2bc) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x398) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x140 && unk3110 < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 < 0x1f4 && m_attackResult == 3 && v10 < 80.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x1f3 && unk3110 < 0x226) {
                m_command = (((WORD)CPlayer::Random(0, 2) == 0) << 1) * (unk118 > 500.0) + 0xa;
                return;
            }
            if (unk3110 > 0x225 && unk3110 < 0x2a8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140) {
                m_command = 0x1f;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8) {
                m_command = (((WORD)CPlayer::Random(0, 3) == 0) << 1) * (unk118 > 500.0) + 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa && v10 < 90.0 && m_attackResult == 3) {
                m_command = 0x14;
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x15e && v10 < 120.0 && unk118 > 500.0) {
                m_command = 0x48;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1ae && m_attackResult == 3 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x64;
                return;
            }
            if (unk3110 > 0x1ae && unk3110 < 0x21c) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                return;
            }
            if (unk3110 > 0x21c && unk3110 < 0x23a && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                return;
            }
            if (unk3110 > 0x38e && m_attackResult == 3) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 40.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 135.0 && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    unk3114 = 5;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x140 && unk3110 < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0x12c && v10 < 100.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12c && unk3110 < 0x258) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x384) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (unk3110 > 0 && unk3110 < 0x96) {
                m_command = (((WORD)CPlayer::Random(0, 3) == 0) << 1) * (unk118 > 500.0) + 0xa;
                return;
            }
            if (unk3110 > 0x96 && unk3110 < 0x15e && v10 < 90.0 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1c2 && m_attackResult == 3 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x64;
                return;
            }
            if (unk3110 > 0x1c2 && unk3110 < 0x280) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                return;
            }
            if (unk3110 > 0x280 && unk3110 < 0x2bc && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                }
                return;
            }
        }
        if (pattern == 0xcf) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && unk3110 < 0x190) {
                m_pressA = 1;
                return;
            }
            if (v10 < 125.0 && unk3110 > 0x18f && unk3110 < 0x2bc) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
            if (unk3110 < 0x14 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0x14;
                return;
            }
            if (unk3110 > 0x14 && unk3110 < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0x1f;
                return;
            }
            if (unk3110 > 0x3c && unk3110 < 0x50 && m_gauge >= 0x3e8 && (*m_opponent)->y < 0.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                return;
            }
            if (unk3110 > 0x50 && unk3110 < 0x12c) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x3b6) {
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 3;
                return;
            }
        }
        if (pattern == 0xd1) {
            if (unk3110 < 0x14 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0x14;
                return;
            }
            if (unk3110 > 0x14 && unk3110 < 0x5a && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0x1f;
                return;
            }
            if (unk3110 > 0x3b6) {
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 3;
                return;
            }
        }
        if (pattern == 0xe7) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140) {
                m_command = 0x1f;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8) {
                m_command = (((WORD)CPlayer::Random(0, 3) == 0) << 1) * (unk118 > 500.0) + 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa && v10 < 90.0 && m_attackResult == 3) {
                m_command = 0x14;
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x15e && v10 < 120.0 && unk118 > 500.0) {
                m_command = 0x48;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x2bc) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                return;
            }
            if (unk3110 > 0x2bc && unk3110 < 0x2da && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                return;
            }
            if (unk3110 > 0x289 && (WORD)CPlayer::Random(0, 3) == 0) {
                unk3114 = 6;
                if (v10 > 110.0) {
                    unk3114 = 8;
                }
            }
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 25.0f * unka8) {
        unk3110 = (WORD)CPlayer::Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && unk3110 < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 55.0 && unk3110 < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 70.0 && unk3110 < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 100.0 && v10 > 70.0 && unk3110 < 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && unk3110 < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 120.0 && unk3110 < 0x1e) {
                    unk3114 = 8;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x50 && unk3110 > 0x25 && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9d) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 90.0 && v10 > 60.0 && unk3110 < 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 100.0 && v10 > 70.0 && unk3110 < 0x28) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x2a && unk3110 > 0x28) {
                    m_command = 0x14;
                    return;
                }
                if (unk3110 < 0x2a && unk3110 > 0x32) {
                    m_command = facing;
                    unk3114 = 5;
                    return;
                }
                if ((WORD)CPlayer::Random(0, 0x140) < v10 - 70.0 && vy > 0.0 && (*m_opponent)->y > y && unk3110 > 0xeb && unk3110 < 0xfa) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                    return;
                }
                if (v10 > 180.0 && unk3110 > 0xfa && unk3110 < 0xfc && m_gauge >= 0x3e8) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && unk3110 < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 80.0 && unk3110 < 0xf) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && unk3110 < 0x11) {
                        m_command = 0x15;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 120.0) {
                        if (unk3110 < (unk118 > 500.0 || unk120 > 0) * 5 + 6) {
                            m_command = 0x15;
                            return;
                        }
                    }
                    if (v10 < 90.0 && x8 < 120.0 && x8 > 90.0 && unk3110 < 0xf) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 120.0 && x8 < 100.0 && unk3110 < 0x11 && m_gauge >= 0x7d0) {
                        m_command = (WORD)CPlayer::Random(0, 1) + 0x65;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 70.0 && x8 < 100.0) {
                    if (unk3110 < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (v10 < 120.0 && x8 > 50.0 && x8 < 60.0 && unk3110 > 0xc8 && unk3110 < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 130.0 && x8 > 40.0 && x8 < 80.0 && unk3110 > 0x104 && unk3110 < 0x109) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)CPlayer::Random(0, 0x140) < v10 - 70.0 && unk3110 > 0x10e && unk3110 < 0x15e) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                    return;
                }
                if (v10 > 180.0 && unk3110 > 0x15e && unk3110 < 0x160 && m_gauge >= 0x3e8) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 80.0 && (*m_opponent)->y < y) {
                    if (unk3110 < (unk118 > 500.0 || unk120 > 0) * 0x14 + 6) {
                        m_command = 0x14;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 > 90.0 && unk3110 < 0x6e) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 150.0 && x8 < 90.0 && unk3110 < 0xc8) {
                    m_pressC = 1;
                    return;
                }
                if (v10 > 180.0 && unk3110 > 0xeb && unk3110 < 0xfa) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                    return;
                }
                if (v10 > 180.0 && unk3110 > 0xfa && unk3110 < 0xfc && m_gauge >= 0x3e8) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 3.0f * unka8) {
        m_command = facing == 1;
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x3e8) < 2) {
        unk3114 = 4;
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 2) {
        if ((WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8) {
            unk3114 = 3;
        } else {
            unk3114 = 0;
        }
        if (v10 > 160.0 && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 120.0 && y == 0.0) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
    }
    if (unk1a0 > 0) {
        if ((char)CPlayer::Unk40ff70() != 0 && unk1a0 > 0xf) {
            unk1a0 = 0xf;
        }
        m_inputX = 1;
        return;
    }
    if (unk1a4 > 0) {
        if ((char)CPlayer::Unk40ff70() != 0 && unk1a4 > 0xf) {
            unk1a4 = 0xf;
        }
        m_inputX = -1;
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x32 && v10 < 100.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x3c) {
        if (facing == 1) {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        } else {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        }
        return;
    }
    if (facing == -1) {
        unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        return;
    }
    unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
}

void CNagamori::UpdateObjects()
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
            CPlayer::InitEffectDesc((EffectDesc*)&l50);
            switch (m_objects[v4].pattern) {
            case 0x190:
                if (unk33ac[v4] == 0) {
                    unk33ac[v4] = unk3158 + 0xa;
                }
                if (m_objects[v4].ay == 0.0) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy > 0.7) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy < -0.7) {
                    m_objects[v4].ay = 0.015;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x191:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.75;
                    m_objects[v4].vy = -2.5;
                    unk3164 = 0;
                    unk3168 = 1;
                }
                m_objects[v4].vy += 0.045;
                if (m_objects[v4].vy + m_objects[v4].y >= 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                    m_objects[v4].y = 0.0;
                }
                if (m_objects[v4].timer == 0 && unk33ac[v4] >= 0x14) {
                    l50.unk0 = 0;
                    l50.type = 0x19a;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    unk33ac[v4] = 0;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    unk3168 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    unk33ac[v4]++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 9;
                    }
                }
                break;
            case 0x192:
                unk32ac[v4]--;
                if (m_objects[v4].ay == 0.0) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy > 0.7) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy < -0.7) {
                    m_objects[v4].ay = 0.015;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0xc) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x193:
                if (unk33ac[v4] == 0) {
                    unk33ac[v4] = unk3158 + 0xa;
                }
                if (m_objects[v4].ay == 0.0) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy > 0.7) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy < -0.7) {
                    m_objects[v4].ay = 0.015;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0) {
                    l50.unk0 = 0;
                    l50.type = 0x1c6;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
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
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    unk2c8 = 1;
                }
                if (m_objects[v4].frame == 0xe && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    Unk4ae1d0((int)m_objects[v4].x, (int)m_objects[v4].y, 0x5a, 0x5a);
                    unk316c[v4] = 0;
                }
                if (m_objects[v4].unk80 == 3) {
                    unk31ac[v4] = (int)AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y - 50.0);
                    (*m_opponent)->SetVelocity((double)unk31ac[v4], 2.2);
                    if ((*m_opponent)->facing == 1) {
                        (*m_opponent)->vx *= -1.0;
                    }
                    m_objects[v4].unk80 = 1;
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
            case 0x196:
                if (unk33ac[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (unk33ac[v4] == 0) {
                    m_objects[v4].vx = 1.8;
                    unk33ac[v4] = 1;
                }
                if (unk33ac[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        unk33ac[v4] = 2;
                    }
                }
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0 && unk33ac[v4] == 2) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x197:
                if (unk33ac[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (unk33ac[v4] == 0) {
                    m_objects[v4].vx = 1.8;
                    m_objects[v4].vy = -1.8;
                    unk33ac[v4] = 1;
                }
                if (unk33ac[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    m_objects[v4].vy += 0.015;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        unk33ac[v4] = 2;
                    }
                }
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0 && unk33ac[v4] == 2) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x198:
                if (unk33ac[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (unk33ac[v4] == 0) {
                    m_objects[v4].vx = 1.8;
                    m_objects[v4].vy = 1.8;
                    unk33ac[v4] = 1;
                }
                if (unk33ac[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    m_objects[v4].vy -= 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        unk33ac[v4] = 2;
                    }
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        unk33ac[v4] = 2;
                    }
                }
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0 && unk33ac[v4] == 2) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x199:
                if (unk33ac[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (unk33ac[v4] == 0) {
                    m_objects[v4].vy = -1.2;
                    unk33ac[v4] = 1;
                }
                if (unk33ac[v4] == 1) {
                    m_objects[v4].vy += 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        unk33ac[v4] = 2;
                    }
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        unk33ac[v4] = 2;
                    }
                }
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0 && unk33ac[v4] == 2) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0xa) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x19a:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    unk2c8 = 1;
                }
                if (m_objects[v4].frame == 6 && m_objects[v4].timer == 0) {
                    unk3164++;
                    if (unk3164 > 2) {
                        unk3164 = 0;
                    }
                    l50.unk0 = 0;
                    l50.type = 0x1c1;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.type = 0x19f;
                    SpawnObject(&l50);
                    l50.type = 0x199;
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
                Unk4ae1d0((int)m_objects[v4].x, (int)m_objects[v4].y, 0x1e, 0x1e);
                if (unk3154 == 1) {
                    m_objects[v4].vy -= 2.5;
                    if (unk31ac[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    unk3154 = 0;
                }
                if (unk3154 == -1) {
                    m_objects[v4].vy += 2.5;
                    if (unk31ac[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    unk3154 = 0;
                }
                if (unk3154 == 2) {
                    unk3148 = 1;
                    unk31ac[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    if (facing != m_objects[v4].facing) {
                        m_objects[v4].facing = facing;
                    }
                    unk3154 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk31ac[v4] == 0) {
                    m_objects[v4].vx = 4.2;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                    unk31ac[v4] = 1;
                }
                if (unk31ac[v4] == 1) {
                    m_objects[v4].vx -= 0.045;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].vx == 0.0 && unk31ac[v4] == 1) {
                    unk31ac[v4] = 2;
                    unk3148 = 2;
                    m_objects[v4].unk84 = 0;
                }
                if (unk31ac[v4] >= 2) {
                    if (m_objects[v4].y < y - 50.0) {
                        m_objects[v4].vy += 0.06;
                    }
                    if (m_objects[v4].y > y - 70.0) {
                        m_objects[v4].vy -= 0.06;
                    }
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx += m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].x > x) {
                        m_objects[v4].vx = m_objects[v4].vx - m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].vy < -2.0) {
                        m_objects[v4].vy = -2.0;
                    } else if (m_objects[v4].vy > 2.0) {
                        m_objects[v4].vy = 2.0;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].vx = -2.0;
                    } else if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objects[v4].y > y - 70.0 && m_objects[v4].y < y - 20.0 && m_objects[v4].x > x - 10.0 && m_objects[v4].x < x + 10.0 && unk3148 >= 2) {
                        RemoveObject(v4);
                        unk3148 = 0;
                        unk2c9 = 0x1a;
                        break;
                    }
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
            case 0x19c:
                Unk4ae1d0((int)m_objects[v4].x, (int)m_objects[v4].y, 0x1e, 0x1e);
                if (unk3154 == 1) {
                    m_objects[v4].vy -= 2.5;
                    if (unk31ac[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    unk3154 = 0;
                }
                if (unk3154 == -1) {
                    m_objects[v4].vy += 2.5;
                    if (unk31ac[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    unk3154 = 0;
                }
                if (unk3154 == 2) {
                    unk3148 = 1;
                    unk31ac[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    if (facing != m_objects[v4].facing) {
                        m_objects[v4].facing = facing;
                    }
                    unk3154 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk31ac[v4] == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -2.3;
                    m_objects[v4].unk84 = 1;
                    unk31ac[v4] = 1;
                }
                if (unk31ac[v4] == 1) {
                    m_objects[v4].vx -= 0.03;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].vx == 0.0 && unk31ac[v4] == 1) {
                    unk31ac[v4] = 2;
                    unk3148 = 2;
                    m_objects[v4].unk84 = 0;
                }
                if (unk31ac[v4] >= 2) {
                    if (m_objects[v4].y < y - 50.0) {
                        m_objects[v4].vy += 0.06;
                    }
                    if (m_objects[v4].y > y - 70.0) {
                        m_objects[v4].vy -= 0.06;
                    }
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx += m_objects[v4].facing * 0.06;
                    }
                    if (m_objects[v4].x > x) {
                        m_objects[v4].vx = m_objects[v4].vx - m_objects[v4].facing * 0.06;
                    }
                    if (m_objects[v4].vy < -2.0) {
                        m_objects[v4].vy = -2.0;
                    } else if (m_objects[v4].vy > 2.0) {
                        m_objects[v4].vy = 2.0;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].vx = -2.0;
                    } else if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objects[v4].y > y - 70.0 && m_objects[v4].y < y - 20.0 && m_objects[v4].x > x - 10.0 && m_objects[v4].x < x + 10.0 && unk3148 >= 2) {
                        RemoveObject(v4);
                        unk3148 = 0;
                        unk2c9 = 0x1a;
                        break;
                    }
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
            case 0x19d:
                if (unk3154 == 1) {
                    m_objects[v4].vy -= 2.5;
                    if (unk31ac[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    unk3154 = 0;
                }
                if (unk3154 == -1) {
                    m_objects[v4].vy += 2.5;
                    if (unk31ac[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    unk3154 = 0;
                }
                if (unk3154 == 2) {
                    unk3148 = 1;
                    unk31ac[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    if (facing != m_objects[v4].facing) {
                        m_objects[v4].facing = facing;
                    }
                    unk3154 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk31ac[v4] == 0) {
                    m_objects[v4].vx = 2.7;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                    unk31ac[v4] = 1;
                }
                if (unk31ac[v4] == 1) {
                    m_objects[v4].vx -= 0.02;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].vx == 0.0 && unk31ac[v4] == 1) {
                    unk31ac[v4] = 2;
                    unk3148 = 2;
                    m_objects[v4].unk84 = 0;
                }
                if (unk31ac[v4] >= 2) {
                    if (m_objects[v4].y < y - 50.0) {
                        m_objects[v4].vy += 0.06;
                    }
                    if (m_objects[v4].y > y - 70.0) {
                        m_objects[v4].vy -= 0.06;
                    }
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx += m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].x > x) {
                        m_objects[v4].vx = m_objects[v4].vx - m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].vy < -2.0) {
                        m_objects[v4].vy = -2.0;
                    } else if (m_objects[v4].vy > 2.0) {
                        m_objects[v4].vy = 2.0;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].vx = -2.0;
                    } else if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].vx = 2.0;
                    }
                    if (unk31ac[v4] > 1 && unk32ac[v4] > 0x59 && unk33ac[v4] < 5) {
                        l50.unk0 = 0;
                        l50.type = 0x190;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.unk18 = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        SpawnObject(&l50);
                        l50.type = 0x19e;
                        SpawnObject(&l50);
                        unk32ac[v4] = 0;
                        unk33ac[v4]++;
                    }
                    if (m_objects[v4].y > y - 70.0 && m_objects[v4].y < y - 20.0 && m_objects[v4].x > x - 10.0 && m_objects[v4].x < x + 10.0 && unk3148 >= 2) {
                        RemoveObject(v4);
                        unk3148 = 0;
                        unk2c9 = 0x1a;
                        break;
                    }
                }
                m_objects[v4].timer++;
                unk32ac[v4]++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x19e:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    unk2c8 = 1;
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
                if (unk33ac[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (unk33ac[v4] == 0) {
                    m_objects[v4].vx = -1.2;
                    m_objects[v4].vy = 1.2;
                    unk33ac[v4] = 1;
                }
                if (unk33ac[v4] == 1) {
                    m_objects[v4].vx += 0.015;
                    m_objects[v4].vy -= 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        unk33ac[v4] = 2;
                    }
                    if (m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        unk33ac[v4] = 2;
                    }
                }
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0 && unk33ac[v4] == 2) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0xa) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x1a0:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    unk2c8 = 1;
                    unk314c = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        unk314c = 0;
                    }
                }
                break;
            case 0x1a1:
                unk3150--;
                unk14c = 0x4b0;
                (*m_opponent)->unk13a = 1;
                unk13c = 1;
                m_gauge = 0;
                (*m_opponent)->unk140 = 2;
                if (unk3150 == 0) {
                    unk14c = 0;
                    (*m_opponent)->unk13a = 0;
                    RemoveObject(v4);
                    unk2c9 = 0x16;
                    (*m_opponent)->pattern = 0x3b;
                    (*m_opponent)->unk140 = 0;
                    unk13c = 0;
                    (*m_opponent)->unk128 = 1;
                    if ((*m_opponent)->m_hp == 1) {
                        (*m_opponent)->m_hp = 0;
                    }
                    (*m_opponent)->unkc0 = -4.0;
                    (*m_opponent)->unkc8 = -1.0;
                    break;
                }
                if (unk3150 == 0x47e) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a2;
                    l50.x = 0.0;
                    l50.y = 80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x474) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a3;
                    l50.x = 190.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x46a) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a4;
                    l50.x = 320.0;
                    l50.y = 170.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x460) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a5;
                    l50.x = 0.0;
                    l50.y = 120.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x456) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a6;
                    l50.x = 60.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x44c) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a7;
                    l50.x = 320.0;
                    l50.y = 40.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x438) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a8;
                    l50.x = 240.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x424) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1a9;
                    l50.x = 180.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x410) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1aa;
                    l50.x = 0.0;
                    l50.y = 80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x3fc) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1ab;
                    l50.x = 180.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x3e8) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1ac;
                    l50.x = 320.0;
                    l50.y = 210.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x3d4) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1ad;
                    l50.x = 80.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x3ca) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1ae;
                    l50.x = 240.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x3b6) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1af;
                    l50.x = 0.0;
                    l50.y = 60.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x3a2) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b0;
                    l50.x = 160.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x38e) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b1;
                    l50.x = 320.0;
                    l50.y = 80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x37a) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b2;
                    l50.x = 180.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x366) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b3;
                    l50.x = 0.0;
                    l50.y = 160.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x352) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b4;
                    l50.x = 60.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x33e) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b5;
                    l50.x = 320.0;
                    l50.y = 50.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x32a) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b6;
                    l50.x = 0.0;
                    l50.y = 170.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x316) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b7;
                    l50.x = 320.0;
                    l50.y = 160.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x302) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b8;
                    l50.x = 160.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x2ee) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1b9;
                    l50.x = 60.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x2da) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1ba;
                    l50.x = 0.0;
                    l50.y = 120.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x2c6) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1bb;
                    l50.x = 190.0;
                    l50.y = 320.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x2b2) {
                    l50.unk0 = 0;
                    l50.screen = 1;
                    l50.type = 0x1bc;
                    l50.x = 120.0;
                    l50.y = -80.0;
                    l50.unk18 = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x21c) {
                    l50.unk0 = 1;
                    l50.screen = 1;
                    l50.type = 0x1bd;
                    l50.x = 0.0;
                    l50.y = 120.0;
                    l50.unk18 = 1;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.unk30 = 1;
                    SpawnObject(&l50);
                }
                if (unk3150 == 0x12c) {
                    l50.unk0 = 1;
                    l50.screen = 1;
                    l50.type = 0x1be;
                    l50.x = 320.0;
                    l50.y = 160.0;
                    l50.unk18 = 1;
                    l50.scale = 0;
                    l50.layer = 0;
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
            case 0x1a2:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a3:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a4:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a5:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a6:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a7:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a8:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1a9:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1aa:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1ab:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1ac:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1ad:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1ae:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1af:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b0:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b1:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b2:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b3:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b4:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b8:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1b9:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1ba:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case 0x1bb:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x96) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0xb4) {
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
            case 0x1bc:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x96) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0xb4) {
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
            case 0x1bd:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x17) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x1fe) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x21c) {
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
            case 0x1be:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1a) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x10e) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x12c) {
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
            case 0x1bf:
                if (pattern != 0x138) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].frame == 0x19) {
                    if (unk3138 == 0) {
                        unk2c8 = 3;
                        Unk4ae1d0((int)x, (int)y, 0x140, 0x140);
                        m_game->FlashWhite(3, 6, 9);
                    }
                    unk3138 = 1;
                }
                if (m_objects[v4].frame == 0x28) {
                    if (unk3138 == 1) {
                        unk2c8 = 4;
                    }
                    unk3138 = 2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x1c0;
                    }
                }
                break;
            case 0x1c0:
                if (pattern != 0x138) {
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
            case 0x1c1:
                if (unk33ac[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (unk33ac[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = 1.2;
                    unk33ac[v4] = 1;
                }
                if (unk33ac[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    m_objects[v4].vy -= 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        unk33ac[v4] = 2;
                    }
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        unk33ac[v4] = 2;
                    }
                }
                if (unk316c[v4] == 1 && unk32ac[v4] <= 0 && unk33ac[v4] == 2) {
                    l50.unk0 = 0;
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    unk316c[v4] = 0;
                    unk32ac[v4] = 0x78;
                    if (unk314c == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                unk316c[v4] = 0;
                m_objects[v4].timer++;
                unk32ac[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk31ac[v4] < 0xa) {
                            m_objects[v4].frame = 0;
                            unk31ac[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x1c2:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.unk0 = 1;
                    l50.type = 0x1c5;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
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
            case 0x1c3:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.unk0 = 1;
                    l50.type = 0x1c5;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
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
            case 0x1c4:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.unk0 = 1;
                    l50.type = 0x1c5;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
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
            case 0x1c5:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    unk314c = 0;
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
            case 0x1c6:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    unk2c8 = 1;
                }
                if (m_objects[v4].frame == 0xd && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    Unk4ae1d0((int)m_objects[v4].x, (int)m_objects[v4].y, 0x78, 0x78);
                    unk316c[v4] = 0;
                }
                if (m_objects[v4].unk80 == 3) {
                    unk31ac[v4] = (int)AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y - 50.0);
                    (*m_opponent)->SetVelocity((double)unk31ac[v4], 2.2);
                    if ((*m_opponent)->facing == 1) {
                        (*m_opponent)->vx *= -1.0;
                    }
                    m_objects[v4].unk80 = 1;
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
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - (facing << 2));
                    l50.y = (double)((int)y - 6);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0xe);
                    l50.y = (double)((int)y - 0x1a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x28);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0x19);
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x23);
                    l50.y = (double)((int)y - 0x2a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x12);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + facing * 2);
                    l50.y = (double)((int)y - 0x41);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + (facing << 4));
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    unk2c9 = 0x22;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk31ac[v4] == 0) {
                    unk32ac[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk31ac[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk32ac[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk32ac[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk32ac[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk31ac[v4] == 0) {
                    unk32ac[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk31ac[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk32ac[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk32ac[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk32ac[v4]--;
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
