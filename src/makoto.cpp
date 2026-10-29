// CMakoto (0x5f6d90-0x60792f): the character class whose files are in makoto\ in the game
// folder (makoto.dat sprites, makoto.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMakoto::CMakoto(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "makoto");
    lastSurface = 0x1cb;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk2ad0[0] = -7;
    unk2af8[0] = -0x33;
    unk2ad0[1] = 6;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x11;
    unk2af8[2] = -0xf;
    unk2ad0[3] = 0x13;
    unk2af8[3] = -0xb;
    unk2ad0[4] = 0x16;
    unk2af8[4] = -0x1e;
    unk30f4 = 5;
    unk30f5[0] = 1;
    unk30f5[1] = 5;
    unk30f5[0xa] = 3;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
}

void CMakoto::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk2ad0[0] = -7;
    unk2af8[0] = -0x33;
    unk2ad0[1] = 6;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x11;
    unk2af8[2] = -0xf;
    unk2ad0[3] = 0x13;
    unk2af8[3] = -0xb;
    unk2ad0[4] = 0x16;
    unk2af8[4] = -0x1e;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
    CPlayer::Reset();
}

void CMakoto::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CMakoto::RemoveObject(short p1)
{
    unk314c[p1] = 0;
    unk324c[p1] = 0;
    unk334c[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CMakoto::Move()
{
    CPlayer::Unk40e740();
}

void CMakoto::StartCommand()
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
    if (m_command == 0x34 && (unk118 >= 500.0 || unk120 > 0) && m_attackResult > 1 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        StartPattern();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x60 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if (m_command == 0x7a && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x134;
            return;
        }
        if ((m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x133;
            return;
        }
        if ((m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if (m_command == 0x65 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if (m_command == 0x64 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x131;
            if (y < 0.0) {
                frame = 3;
            }
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x130;
            if (y < 0.0) {
                frame = 3;
            }
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            if (y < 0.0) {
                frame = 3;
            }
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x102;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x101;
            return;
        }
        if ((m_command == 0x14 || m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x2a && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3148 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if ((m_command == 0x29 || m_command == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3148 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x104;
            return;
        }
        if ((m_command == 0x28 || m_command == 0x29 || m_command == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3148 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x103;
            return;
        }
        if (m_command == 0x20 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if ((m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            return;
        }
        if ((m_command == 0x1e || m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            if (y < 0.0) {
                pattern = 0x106;
            }
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
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
        if ((m_inputY == 0 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xd2].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xd2;
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
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
            if (m_patterns[pattern].unk2 <= m_patterns[0xd3].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd3;
                if (m_inputY > 0) {
                    pattern = 0xd1;
                }
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xce].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xce;
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

void CMakoto::DrawGauge()
{
}

void CMakoto::Vf8()
{
}

void CMakoto::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CMakoto::ReadCommand()
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
        if ((v5 & 0x80) != 0 && x6 == 3) {
            m_command = 0x60;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0x80) != 0) {
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

void CMakoto::CpuInput()
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
            if (v10 < 45.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 70.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f && unk118 > 500.0) {
                m_command = 0x14;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0x2a;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && m_gauge >= 0x7d0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x79;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && m_gauge >= 0x7d0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x79;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x28;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xb;
                return;
            }
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
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 50.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < -20.0 && y - (*m_opponent)->y > -90.0 && v10 < 110.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 3 && unk118 > 500.0 && v10 < 80.0) {
            m_command = 0x14;
            return;
        }
        if (unk3110 < 5 && unk118 > 500.0 && v10 < 80.0) {
            m_command = 0x16;
            return;
        }
        if (unk3110 < 0xa && unk3110 > 5 && unk118 > 500.0 && v10 < 150.0) {
            m_command = 0x2a;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8 && v10 < 100.0) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8 && v10 > 90.0) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
            return;
        }
        if (unk3110 > 0x41) {
            unk3114 = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8 && v10 > 50.0) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
            return;
        }
        if (unk3110 > 0x3c) {
            unk3114 = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x100 || pattern == 0xe8 && (WORD)CPlayer::Random(0, 0xa) == 0 || pattern == 0x101 || pattern == 0xee)) {
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
    if (unk3114 == 0xc && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0xd;
        }
        return;
    }
    if (unk3114 == 0xd && pattern == 0xa3) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == 0xe6) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 0xe && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0xf;
        }
        return;
    }
    if (unk3114 == 0xf && pattern == 0xa3) {
        m_pressB = 1;
        m_inputY = 1;
        if (pattern == 0xe7) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 0x10 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0x11;
        }
        return;
    }
    if (unk3114 == 0x11 && pattern == 0xa3) {
        m_pressC = 1;
        m_inputY = 1;
        if (pattern == 0xe8) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 0x14 && pattern < 0x32) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == 0xcc) {
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
            if (v10 < 45.0 && unk3110 > 0 && unk3110 < 0x12c) {
                m_pressA = 1;
                m_inputY = CPlayer::Random(0, 2);
                return;
            }
            if (v10 < 80.0 && unk3110 > 0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && unk3110 > 0x12c && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x3ca) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x258) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x15;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12c && unk3110 < 0x226) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x226 && unk3110 < 0x258 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x258 && unk3110 < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (unk3110 < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0x15e && v10 < 130.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x1c2 && unk3110 < 0x258 && v10 < 70.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (unk3110 > 0x3d4) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x1f4) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x96 && unk3110 < 0xc8 && m_gauge >= 0x3e8 && v10 < 120.0) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0x1f4) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x1f4) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xe;
                }
                return;
            }
        }
        if (pattern == 0xcb) {
            if (unk3110 > 0 && unk3110 < 0x12c) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x28;
                return;
            }
            if (unk3110 > 0x12c && unk3110 < 0x258) {
                m_command = 0xa;
                if (v10 > 160.0) {
                    m_command = 0xb;
                    if ((WORD)CPlayer::Random(0, 3) == 0) {
                        m_command = 0xc;
                    }
                }
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x28a) {
                m_command = 0x1e;
                return;
            }
            if (unk3110 > 0x28a && unk3110 < 0x29e && m_gauge >= 0x3e8) {
                m_command = 0x65;
                return;
            }
            if (unk3110 > 0x384) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 45.0 && unk3110 > 0 && unk3110 < 0x12c) {
                m_pressA = 1;
                m_inputY = CPlayer::Random(0, 2);
                return;
            }
            if (v10 < 90.0 && unk3110 > 0 && unk3110 < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 100.0 && unk3110 > 0x12c && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x3ca) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x258) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x15;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12c && unk3110 < 0x226) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x226 && unk3110 < 0x258 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x258 && unk3110 < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (unk3110 < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0x15e && v10 < 130.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x1c2 && unk3110 < 0x258 && v10 < 70.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (unk3110 > 0x3d4) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x1f4) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (unk3110 > 0x258 - (m_attackResult == 3) * 0x190 && unk3110 < 0x28a) {
                m_command = 0x1e;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x12c) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x28;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                return;
            }
            if (unk3110 > 0x12c && unk3110 < 0x258) {
                m_command = 0xa;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                if (v10 > 160.0) {
                    m_command = 0xb;
                    if ((WORD)CPlayer::Random(0, 3) == 0) {
                        m_command = 0xc;
                    }
                }
                return;
            }
            if (unk3110 > 0x28a && unk3110 < 0x29e && m_gauge >= 0x3e8) {
                m_command = 0x65;
                return;
            }
            if (unk3110 > 0x384) {
                unk3114 = 1;
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
            if (unk3110 > 0x14 && unk3110 < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0xa;
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
            if (unk3110 > 0 && unk3110 < 0xc8) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xd2 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0xdc && unk3110 < 0x12c) {
                m_command = 0x1e;
                return;
            }
            if (unk3110 > 0x12c && unk3110 < 0x154) {
                m_command = 0x29;
                return;
            }
            if (unk3110 > 0x190) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xea) {
            if (unk3110 > 0 && unk3110 < 0xc8) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xd2 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0xdc && unk3110 < 0x12c) {
                m_command = 0x1e;
                return;
            }
            if (unk3110 > 0x12c && unk3110 < 0x154) {
                m_command = 0x29;
                return;
            }
            if (unk3110 > 0x190) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xeb) {
            if (unk3110 > 0 && unk3110 < 0xc8) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xd2 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0xdc && unk3110 < 0x12c) {
                m_command = 0x1e;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                return;
            }
            if (unk3110 > 0x12c && unk3110 < 0x154) {
                m_command = 0x29;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                return;
            }
            if (unk3110 > 0x384) {
                unk3114 = 1;
            }
        }
        if (pattern == 0xe9 && unk3110 > 0x1f4) {
            unk3114 = 1;
            if (v10 < 50.0) {
                unk3114 = 0x14;
            }
            return;
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
                if (v10 < 60.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 45.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 50.0 && v10 < 80.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x41 && unk3110 > 0x28) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 95.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x14 + 0x50 && unk3110 > 0x46) {
                        unk3114 = 0xc;
                        return;
                    }
                }
                if (0x50 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 110.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x80 && unk3110 > 0x78) {
                        unk3114 = 8;
                        return;
                    }
                }
                if (v10 < 180.0 && v10 > 150.0 && unk3110 < 0xaa && unk3110 > 0x96) {
                    unk3114 = 0x10;
                    return;
                }
                if (v10 < 130.0 && v10 > 100.0 && unk3110 < 0xc3 && unk3110 > 0xaa) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (0x50 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x50 < v10 && v10 < 120.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0xb9 && unk3110 > 0xaa) {
                        unk3114 = 0xe;
                        return;
                    }
                }
                if (0x5a - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x5a < v10 && v10 < 120.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0xe1 && unk3110 > 0xd2) {
                        unk3114 = 0xa;
                        return;
                    }
                }
                if (v10 > 130.0 && v10 < 170.0 && unk3110 < 0x104 && unk3110 > 0xfa) {
                    unk3114 = 0xa;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x113 && unk3110 > 0x104 && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x16;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x118 && unk3110 > 0x113 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > 0xc7) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x65;
                    return;
                }
                if (v10 > 160.0 && unk3110 < 0x136 && unk3110 > 0x12c) {
                    m_command = 0x28;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && unk3110 < 0x140 && unk3110 > 0x136) {
                    m_command = 0x29;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && unk3110 < 0x145 && unk3110 > 0x140) {
                    m_command = 0x2a;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && unk3110 < 0x154 && unk3110 > 0x14a) {
                    m_command = 0xa;
                    return;
                }
                if (v10 > 160.0 && unk3110 < 0x168 && unk3110 > 0x154) {
                    m_command = 0xb;
                    return;
                }
                if (v10 > 160.0 && unk3110 < 0x168 && unk3110 > 0x154) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                    return;
                }
                if (unk3110 < 0x320 && unk3110 > 0x2bc && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c && v10 > 100.0) {
                    unk3114 = 5;
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
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && unk3110 < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x15;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && unk3110 < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x16;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && unk3110 < 0xf) {
                        m_command = 0x15;
                        return;
                    }
                    if (v10 < 120.0 && v10 > 80.0 && x8 < 140.0 && x8 > 80.0 && unk3110 < 0x19 && unk3110 > 0xf && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x2a;
                        return;
                    }
                    if (v10 < 160.0 && v10 > 120.0 && x8 < 300.0 && x8 > 160.0 && unk3110 < 0x28 && unk3110 > 0x1e) {
                        m_command = 0x28;
                        return;
                    }
                    if (v10 > 130.0 && v10 < 150.0 && x8 < 150.0 && x8 > 120.0 && unk3110 < 0x6e && unk3110 > 0x50) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 70.0 && unk3110 < 0xdc && unk3110 > 0xc8 && (*m_opponent)->y < -50.0 && x8 < 90.0 && m_gauge >= 0x7d0) {
                        m_command = (WORD)CPlayer::Random(0, 2) + 0x79;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && unk3110 < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 100.0 && x8 > 60.0 && x8 < 120.0 && unk3110 > 0xb4 && unk3110 < 0xf0) {
                    m_pressC = 1;
                    return;
                }
                if (v10 > 150.0 && unk3110 > 0xf0 && unk3110 < 0xf5 && x8 > 80.0) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && unk3110 < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 100.0 && x8 > 0.0 && x8 < 90.0 && (*m_opponent)->y < y && unk3110 > 0x14 && unk3110 < 0x3c) {
                    m_pressB = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 5.0f * unka8 && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 800.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < 3.0f * unka8 && x > 150.0 && x < 490.0) {
        m_command = -((facing == 1) - 1);
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
        if (v10 > 180.0 && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 2) {
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
    if ((WORD)CPlayer::Random(0, 0x64) < 0x32 && v10 < 120.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
        if (facing == 1) {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        } else {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        }
        return;
    }
    if (facing == -1) {
        unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        return;
    }
    unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
}

void CMakoto::UpdateObjects()
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
                unk324c[v4]--;
                if (m_objects[v4].frame < 6 && unk324c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk324c[v4] = 3;
                }
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -2.7;
                    m_objects[v4].ax = 0.18;
                    unk314c[v4]++;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 3) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 3;
                    break;
                }
                if (((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0xc7) && m_objects[v4].frame > 2 && m_objects[v4].frame < 6 && (m_objects[v4].x - (*m_opponent)->x < 25.0 && m_objects[v4].x - (*m_opponent)->x > -25.0 && (*m_opponent)->y > -20.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x96) || pattern > 0xf9 && pattern < 0xfd)) {
                    m_objects[v4].scale = 2;
                    unk2c8 = 0;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].frame = 6;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame > 2 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].ax = -0.18;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].ax = 0.18;
                    }
                    m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                    if (m_objects[v4].frame == 6 && unk314c[v4] < 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                        unk314c[v4]++;
                    }
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].scale = 2;
                        unk2c8 = 0;
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x194:
                unk324c[v4]--;
                if (m_objects[v4].frame < 6 && unk324c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk324c[v4] = 3;
                }
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 1.1;
                    m_objects[v4].vy = -2.2;
                    m_objects[v4].ax = 0.18;
                    unk314c[v4]++;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 3) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 3;
                    break;
                }
                if (((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0xc7) && m_objects[v4].frame > 2 && m_objects[v4].frame < 6 && (m_objects[v4].x - (*m_opponent)->x < 25.0 && m_objects[v4].x - (*m_opponent)->x > -25.0 && (*m_opponent)->y > -20.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x96) || pattern > 0xf9 && pattern < 0xfd)) {
                    m_objects[v4].scale = 2;
                    m_objects[v4].scale = 2;
                    unk2c8 = 0;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].frame = 6;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame > 2 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].ax = -0.18;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].ax = 0.18;
                    }
                    m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                    if (m_objects[v4].frame == 6 && unk314c[v4] < 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                        unk314c[v4]++;
                    }
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].scale = 2;
                        unk2c8 = 0;
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x195:
                unk324c[v4]--;
                if (m_objects[v4].frame < 6 && unk324c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk324c[v4] = 3;
                }
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xf) * 0.1 + 0.5;
                    m_objects[v4].vy = -1.5 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].ax = 0.18;
                    unk314c[v4]++;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 3) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 3;
                    break;
                }
                if (((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0xc7) && m_objects[v4].frame > 2 && m_objects[v4].frame < 6 && (m_objects[v4].x - (*m_opponent)->x < 25.0 && m_objects[v4].x - (*m_opponent)->x > -25.0 && (*m_opponent)->y > -20.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x96) || pattern > 0xf9 && pattern < 0xfd)) {
                    m_objects[v4].scale = 2;
                    m_objects[v4].scale = 2;
                    unk2c8 = 0;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].frame = 6;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame > 2 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].ax = -0.18;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].ax = 0.18;
                    }
                    m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                    if (m_objects[v4].frame == 6 && unk314c[v4] < 0x1e) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                        unk314c[v4]++;
                    }
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].scale = 2;
                        unk2c8 = 0;
                        m_objects[v4].unk84 = 1;
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x196:
                unk324c[v4]--;
                if ((m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5 || pattern < 0x100 && pattern > 0xfc && frame == 0) && m_objects[v4].frame < 3) {
                    m_objects[v4].frame = 3;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].scale = 1;
                    break;
                }
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 0.2;
                    m_objects[v4].vy = -0.5;
                    unk314c[v4]++;
                }
                if (m_objects[v4].frame == 2 && unk324c[v4] <= 0) {
                    l50.type = 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    unk324c[v4] = 0xf;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 3) {
                        if (unk314c[v4] < 3) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                        } else {
                            l50.type = 0x199;
                            l50.x = (double)(int)m_objects[v4].x;
                            l50.y = 5.0;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.unk18 = facing;
                            SpawnObject(&l50);
                            l50.x = (double)((int)m_objects[v4].x - 5);
                            l50.y = 0.0;
                            SpawnObject(&l50);
                            l50.x = (double)((int)m_objects[v4].x + 5);
                            l50.y = 0.0;
                            SpawnObject(&l50);
                            l50.x = (double)(int)m_objects[v4].x;
                            l50.y = -5.0;
                            SpawnObject(&l50);
                            RemoveObject(v4);
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x197:
                unk324c[v4]--;
                if ((m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5 || pattern < 0x100 && pattern > 0xfc && frame == 0) && m_objects[v4].frame < 3) {
                    m_objects[v4].frame = 3;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].scale = 1;
                    break;
                }
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 0.4;
                    m_objects[v4].vy = -0.5;
                    unk314c[v4]++;
                }
                if (m_objects[v4].frame == 2 && unk324c[v4] <= 0) {
                    l50.type = 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    unk324c[v4] = 0x15;
                }
                unk324c[v4]--;
                if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
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
                unk324c[v4]--;
                if ((m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5 || pattern < 0x100 && pattern > 0xfc && frame == 0) && m_objects[v4].frame < 3) {
                    m_objects[v4].frame = 3;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].scale = 1;
                    break;
                }
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 0.3;
                    m_objects[v4].vy = -0.5;
                    unk314c[v4]++;
                }
                if (m_objects[v4].frame == 2 && unk324c[v4] <= 0) {
                    l50.type = 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    unk324c[v4] = 0xf;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 3) {
                        if (unk314c[v4] < 6) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                        } else {
                            l50.type = 0x199;
                            l50.x = (double)(int)m_objects[v4].x;
                            l50.y = 5.0;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.unk18 = facing;
                            SpawnObject(&l50);
                            l50.x = (double)((int)m_objects[v4].x - 5);
                            l50.y = 0.0;
                            SpawnObject(&l50);
                            l50.x = (double)((int)m_objects[v4].x + 5);
                            l50.y = 0.0;
                            SpawnObject(&l50);
                            l50.x = (double)(int)m_objects[v4].x;
                            l50.y = -5.0;
                            SpawnObject(&l50);
                            RemoveObject(v4);
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x199:
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
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
                if (m_objects[v4].frame == 0 && unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].unk84 == 0) {
                    RemoveObject(v4);
                    unk3148 = 0;
                }
                if (m_objects[v4].facing == 1) {
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 1) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            unk2c8 = 1;
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame + 6;
                            unk314c[v4]++;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            unk2c8 = 1;
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 5) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 7) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame - 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                }
                if (m_objects[v4].facing == -1) {
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 1) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame + 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 5) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 7) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame - 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19b:
                if (m_objects[v4].frame == 0 && unk324c[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk324c[v4] = 1;
                    m_objects[v4].frame = 6;
                }
                if (m_objects[v4].unk84 == 0) {
                    RemoveObject(v4);
                    unk3148 = 0;
                }
                if (m_objects[v4].facing == 1) {
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 1) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame + 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 5) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 7) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame - 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                }
                if (m_objects[v4].facing == -1) {
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 1) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame + 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 5) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = 1.5;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 7) {
                        m_objects[v4].vx = -1.5;
                        m_objects[v4].vy = -1.5;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame - 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            if (unk314c[v4] > 3) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19c:
                if (m_objects[v4].frame == 0 && unk324c[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk324c[v4] = 1;
                }
                if (m_objects[v4].facing == 1) {
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 1) {
                        m_objects[v4].vx = 3.0;
                        m_objects[v4].vy = -3.0;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame + 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                        m_objects[v4].vx = 3.0;
                        m_objects[v4].vy = 3.0;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 5) {
                        m_objects[v4].vx = -3.0;
                        m_objects[v4].vy = 3.0;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            m_objects[v4].unk84 = 1;
                            unk2c8 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 7) {
                        m_objects[v4].vx = -3.0;
                        m_objects[v4].vy = -3.0;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame - 6;
                            unk314c[v4]++;
                            m_objects[v4].unk84 = 1;
                            unk2c8 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                }
                if (m_objects[v4].facing == -1) {
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 1) {
                        m_objects[v4].vx = 3.0;
                        m_objects[v4].vy = -3.0;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame + 6;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                        m_objects[v4].vx = 3.0;
                        m_objects[v4].vy = 3.0;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x < m_game->unk14248) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 5) {
                        m_objects[v4].vx = -3.0;
                        m_objects[v4].vy = 3.0;
                        if (m_objects[v4].y > m_game->unk14254) {
                            m_objects[v4].frame = m_objects[v4].frame + 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 7) {
                        m_objects[v4].vx = -3.0;
                        m_objects[v4].vy = -3.0;
                        if (m_objects[v4].y < m_game->unk1424c) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk314c[v4]++;
                            unk2c8 = 1;
                            m_objects[v4].unk84 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                        if (m_objects[v4].x > m_game->unk14250) {
                            m_objects[v4].frame = m_objects[v4].frame - 6;
                            unk314c[v4]++;
                            m_objects[v4].unk84 = 1;
                            unk2c8 = 1;
                            if (unk314c[v4] > 7) {
                                RemoveObject(v4);
                                unk3148 = 0;
                            }
                            break;
                        }
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19d:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        l50.type = 0x19e;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3c);
                        l50.y = 5.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19e:
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
                m_objects[v4].unk84 = 0x63;
                if (pattern != 0x12f || pattern == 0x12f && frame > 0x13) {
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
            case 0x1a0:
                m_objects[v4].unk84 = 0x63;
                if (pattern != 0x130 || pattern == 0x130 && frame > 0x13) {
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
            case 0x1a1:
                m_objects[v4].unk84 = 0x63;
                if (pattern != 0x131 || pattern == 0x131 && frame > 0x13) {
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
            case 0x1a2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 5;
                    m_objects[v4].vy = -0.45;
                    m_objects[v4].vx = 0.02;
                    unk314c[v4]++;
                }
                if (m_objects[v4].unk84 == 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].vy += 0.0012;
                m_objects[v4].vx -= 1e-05;
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (unk324c[v4] > 0x5a) {
                    m_objects[v4].unk80 = 0;
                    unk324c[v4] = 0;
                }
                unk324c[v4]++;
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
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
            case 0x1a3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 5;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].ay = 0.005;
                    unk314c[v4]++;
                }
                if (m_objects[v4].unk84 == 0) {
                    RemoveObject(v4);
                    break;
                }
                if (unk324c[v4] > 0x5a) {
                    m_objects[v4].unk80 = 0;
                    unk324c[v4] = 0;
                }
                unk324c[v4]++;
                if (m_objects[v4].vy > 0.3) {
                    m_objects[v4].ay = -0.005;
                }
                if (m_objects[v4].vy < -0.3) {
                    m_objects[v4].ay = 0.005;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk334c[v4] < 0xc) {
                            m_objects[v4].frame = 0;
                            unk334c[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x1a4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 5;
                    m_objects[v4].vy = -0.5;
                    m_objects[v4].vx = 0.3;
                    unk314c[v4]++;
                }
                if (m_objects[v4].unk84 == 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].vy += 0.0015;
                if (unk324c[v4] > 0x5a) {
                    m_objects[v4].unk80 = 0;
                    unk324c[v4] = 0;
                }
                unk324c[v4]++;
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
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
            case 0x1a5:
                if (unk314c[v4] == 0) {
                    m_objects[v4].vy = (WORD)CPlayer::Random(0, 0x14) * 0.01 + -2.6;
                    m_objects[v4].vx = -1.0 - (WORD)CPlayer::Random(0, 0x14) * 0.01;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    unk2c8 = 2;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    if (m_objects[v4].vy > -1.0) {
                        RemoveObject(v4);
                        break;
                    }
                }
                unk314c[v4]++;
                m_objects[v4].vy += 0.05;
                if (unk314c[v4] > 0xb4) {
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
                }
                break;
            case 0x1a6:
                if (unk314c[v4] == 0) {
                    m_objects[v4].vy = -3.2;
                    m_objects[v4].vx = -0.07;
                }
                if (m_objects[v4].unk80 == 5 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    unk313c = 2;
                    m_objects[v4].vx = facing * 1.5 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.5;
                    break;
                }
                if (m_objects[v4].y + m_objects[v4].vy > -70.0 && m_objects[v4].frame == 0) {
                    unk313c = 1;
                    RemoveObject(v4);
                    break;
                }
                unk314c[v4]++;
                m_objects[v4].vy += 0.035;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a7:
                if (m_objects[v4].frame < 0x1d) {
                    m_objects[v4].x = facing * 0xc + x;
                    m_objects[v4].y = y - 50.0;
                }
                if (m_objects[v4].frame < 0x1d && unk324c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)m_objects[v4].x + -m_objects[v4].facing * 0x2f + (WORD)CPlayer::Random(0, 0xa));
                    l50.y = (double)((int)m_objects[v4].y + 0xc + (WORD)CPlayer::Random(0, 0xa));
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk324c[v4] = 2;
                }
                if (m_objects[v4].frame < 0x1d && (WORD)CPlayer::Random(0, 0x64 - (pattern == 0x134) * 0x32) < 0xa && pattern > 0x132) {
                    l50.type = 0x1a8;
                    l50.x = (double)((int)m_objects[v4].x + -m_objects[v4].facing * 0x3c + (WORD)CPlayer::Random(0, 0x28));
                    l50.y = (double)((int)m_objects[v4].y + -0x20 + (WORD)CPlayer::Random(0, 0x3c));
                    l50.scale = 2;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                unk324c[v4]--;
                if (y + vy >= 0.0 && frame > 5 && unk314c[v4] == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    unk314c[v4]++;
                }
                if ((pattern < 0x132 || pattern > 0x134) && m_objects[v4].frame < 0x1d) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (unk14a > 0) {
                    m_objects[v4].timer--;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a8:
                m_objects[v4].timer++;
                if (unk14a > 0) {
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
