// CMishio (0x546480-0x5571ef): the character class whose files are in mishio\ in the game
// folder (mishio.dat sprites, mishio.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMishio::CMishio(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "mishio");
    lastSurface = 0x517;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    unk3158 = 0;
    unk315c = 0;
    unk3160 = 0;
    unk3164 = 0;
    unk3168 = 0;
    unk316c = 0;
    unk3170 = 0;
    unk2ad0[0] = -4;
    unk2af8[0] = -0x39;
    unk2ad0[1] = 0x12;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x15;
    unk2af8[2] = -0xc;
    unk2ad0[3] = 0x12;
    unk2af8[3] = -0xf;
    unk2ad0[4] = 0x26;
    unk2af8[4] = -0x27;
    unk30f4 = 7;
    unk30f5[0] = 3;
    unk30f5[0xa] = 0xf;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3174[v4] = 0;
        unk3274[v4] = 0;
        unk3374[v4] = 0;
    }
}

void CMishio::Reset()
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
    unk3158 = 0;
    unk315c = 0;
    unk3160 = 0;
    unk3164 = 0;
    unk3168 = 0;
    unk316c = 0;
    unk3170 = 0;
    unk2ad0[0] = -4;
    unk2af8[0] = -0x39;
    unk2ad0[1] = 0x12;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x15;
    unk2af8[2] = -0xc;
    unk2ad0[3] = 0x12;
    unk2af8[3] = -0xf;
    unk2ad0[4] = 0x26;
    unk2af8[4] = -0x27;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3174[v4] = 0;
        unk3274[v4] = 0;
        unk3374[v4] = 0;
    }
    CPlayer::Reset();
}

void CMishio::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CMishio::RemoveObject(short p1)
{
    unk3174[p1] = 0;
    unk3274[p1] = 0;
    unk3374[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CMishio::Move()
{
    CPlayer::Unk40e740();
}

void CMishio::StartCommand()
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
    if (m_command == 0x34 && (unk118 >= 500.0 && m_attackResult > 1 || unk120 > 0 && m_attackResult > 1 && m_attackResult != 6) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        StartPattern();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x62 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].unk2 <= m_patterns[0x13e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13e;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && m_command == 0x7a && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13a;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && (m_command == 0x7a || m_command == 0x79) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x139;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && (m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x138].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x138;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && m_command == 0x70 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && (m_command == 0x70 || m_command == 0x6f) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x130;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && (m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && m_command == 0x66 && m_gauge >= 0xbb8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13d;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && (m_command == 0x66 || m_command == 0x65) && m_gauge >= 0x7d0 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13c;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && (m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13b;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && m_command == 0x66 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && (m_command == 0x66 || m_command == 0x65) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && (m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && unk314c == 0 && m_command == 0x33 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x110].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x110;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && unk314c == 0 && m_command == 0x32 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10f].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10f;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && unk3148 == 0 && (unk118 >= 500.0 || unk120 > 0) && m_command == 0x2a && y == 0.0 && (unk118 >= 500.0 || unk120 > 0 || y == 0.0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10e;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && unk3148 == 0 && (m_command == 0x29 || m_command == 0x2a) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10d].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10d;
            return;
        }
        if ((unk3158 == 2 || unk3158 == 3) && unk3148 == 0 && m_command == 0x28 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10c;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            if (unk3158 == 0) {
                pattern = 0xfc;
            }
            if (unk3158 == 1) {
                pattern = 0x113;
            }
            if (unk3158 == 2) {
                pattern = 0x116;
            }
            if (unk3158 == 3) {
                pattern = 0x119;
            }
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            if (unk3158 == 0) {
                pattern = 0xfb;
            }
            if (unk3158 == 1) {
                pattern = 0x112;
            }
            if (unk3158 == 2) {
                pattern = 0x115;
            }
            if (unk3158 == 3) {
                pattern = 0x117;
            }
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            if (unk3158 == 0) {
                pattern = 0xfa;
            }
            if (unk3158 == 1) {
                pattern = 0x111;
            }
            if (unk3158 == 2) {
                pattern = 0x114;
            }
            if (unk3158 == 3) {
                pattern = 0x117;
            }
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && m_command == 0x20 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            if (y < 0.0) {
                pattern = 0x105;
            }
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && (m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x102;
            if (y < 0.0) {
                pattern = 0x104;
            }
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && m_command == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x101;
            if (y < 0.0) {
                pattern = 0x103;
            }
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && (m_command == 0xb || m_command == 0xc) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            return;
        }
        if ((unk3158 == 1 || unk3158 == 3) && pattern != 0xfe && m_command == 0xa && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfe;
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
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if ((unk3158 == 2 || unk3158 == 3) && m_inputX == facing && m_patterns[pattern].unk2 <= m_patterns[0xd2].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd2;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -90.0 && x - (*m_opponent)->x < 90.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xdc;
                return;
            }
            if ((unk3158 == 1 || unk3158 == 3) && m_patterns[pattern].unk2 <= m_patterns[0xd3].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd3;
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

void CMishio::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    unk3164++;
    if (unk3164 > 0x1d) {
        unk3164 = 0;
    }
    if (unk3158 == 0) {
        x1c = *anims[0x27].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3158 == 1) {
        x1c = anims[0x28].frames[unk3164 / 6];
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3158 == 2) {
        x1c = anims[0x29].frames[unk3164 / 6];
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3158 == 3) {
        x1c = anims[0x2a].frames[unk3164 / 6];
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3168 > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3168 > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, unk3168 * x1c.width / 0x1194, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3168 * x1c.width / 0x1194, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3168 * x1c.width / 0x1194, 0x1f - x1c.y, unk3168 * x1c.width / 0x1194, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CMishio::Vf8()
{
    EffectDesc v48;
    CPlayer::InitEffectDesc((EffectDesc*)&v48);
    if (unk3168 > 0 && unk3158 == 3) {
        if (pattern != 0x13e) {
            unk3168--;
        }
        if (unk3168 <= 0) {
            unk3158 = 0;
        }
    }
    if (unk3158 > 0) {
        unk315c--;
        if (unk3158 == 3) {
            unk3160++;
            if (unk3160 > 0x90) {
                unk3160 = 0;
            }
            if (unk3160 == 0x12) {
                CPlayer::Unk410ac0(0xd1, 0x1b);
            }
            if (unk3160 == 0x24) {
                CPlayer::Unk410ac0(0xd0, 0x1b);
            }
            if (unk3160 == 0x36) {
                CPlayer::Unk410ac0(0xcf, 0x1b);
            }
            if (unk3160 == 0x48) {
                CPlayer::Unk410ac0(0xb1, 0x1b);
            }
            if (unk3160 == 0x5a) {
                CPlayer::Unk410ac0(0xcf, 0x1b);
            }
            if (unk3160 == 0x6c) {
                CPlayer::Unk410ac0(0xd0, 0x1b);
            }
            if (unk3160 == 0x7e) {
                CPlayer::Unk410ac0(0xd1, 0x1b);
            }
            if (unk3160 == 0x90) {
                CPlayer::Unk410ac0(0xd2, 0x1b);
            }
        }
        if (unk315c <= 0 && (pattern < 0x32 || pattern > 0x95)) {
            if (unk3158 == 1) {
                v48.type = 0x22;
            }
            if (unk3158 == 2) {
                v48.type = 0x24;
            }
            if (unk3158 == 3) {
                if ((WORD)CPlayer::Random(0, 0x64) <= 0x32) {
                    v48.type = 0x22;
                } else {
                    v48.type = 0x24;
                }
            }
            v48.x = (double)((int)x + (0x14 - (WORD)CPlayer::Random(0, 0x28)) * facing);
            v48.y = (double)((int)y - (WORD)CPlayer::Random(0, 0x5a));
            v48.scale = 2;
            v48.layer = 1;
            m_game->CreateEffect((EffectDesc*)&v48);
            unk315c = 2;
        }
    }
}

void CMishio::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CMishio::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x10) != 0 && x6 == 6) {
            m_command = 0x62;
            return;
        }
        if ((v5 & 0x40) != 0 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xb0) != 0 && x6 == 4) {
            break;
        }
        if (v5 == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xd0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xd0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            m_command = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 3) {
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
    v4 = m_inputPos + 0x64;
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
        if ((v5 & 0xf) == 4 && x6 == 0) {
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

void CMishio::CpuInput()
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
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 20.0 && v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && v10 < 80.0 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && v10 < 150.0 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (v10 < 220.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (v10 > 220.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
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
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
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
            m_command = 0x16;
            return;
        }
        if (unk3110 < 4 && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
            return;
        }
        if (unk3110 > 0x55) {
            unk3114 = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 3 && unk118 > 500.0) {
            m_command = 0x16;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
            return;
        }
        if (unk3110 > 0x55) {
            unk3114 = 2;
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
    if (unk3114 == 0xc && pattern < 0x32) {
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
            if (unk3110 > 0x3ca) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 8;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x140 && unk3110 < 0x258 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
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
                    if (v10 > 80.0) {
                        unk3114 = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140) {
                m_command = 0xa;
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
                m_command = 0xa;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1ae && m_attackResult == 3 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
            if (unk3110 > 0x1ae && unk3110 < 0x21c && m_attackResult != 3) {
                m_command = 0x28;
                if (v10 > 120.0) {
                    m_command = 0x29;
                }
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
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                    return;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
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
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x1ae && unk3110 < 0x21c && m_attackResult != 3) {
                m_command = 0x28;
                if (v10 > 120.0) {
                    m_command = 0x29;
                }
                return;
            }
            if (unk3110 > 0x289) {
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
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xdc && v10 < 90.0 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x289 && (WORD)CPlayer::Random(0, 2) == 0) {
                unk3114 = 0xc;
                if (v10 > 110.0) {
                    unk3114 = 8;
                }
            }
        }
        if (pattern == 0xe8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1ae && m_attackResult == 3 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
            if (unk3110 > 0x1ae && unk3110 < 0x21c && m_attackResult != 3) {
                m_command = 0x28;
                if (v10 > 120.0) {
                    m_command = 0x29;
                }
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
                if (v10 < 50.0 && unk3110 < 0x17) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 75.0 && unk3110 < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x28 && unk3110 > 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x34 && unk3110 > 0x28 || v10 > 80.0 && v10 < 130.0 && unk3110 < 0x50 && unk3110 > 0x34) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && unk3110 < 0x64 && unk3110 > 0x50) {
                    unk3114 = 8;
                    return;
                }
                if (v10 > 70.0 && v10 < 120.0 && unk3110 < 0x78 && unk3110 > 0x64) {
                    unk3114 = 8;
                    return;
                }
                if (v10 < 90.0 && v10 > 70.0 && unk3110 < 0x82 && unk3110 > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && unk3110 < 0x91 && unk3110 > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 140.0 && unk3110 < 0x98 && unk3110 > 0x91) {
                    unk3114 = 0xa;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0xa5 && unk3110 > 0x91 && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x16;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0xaa && unk3110 > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > 0xc7) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                    return;
                }
                if (v10 > 200.0 && unk3110 < 0xaa && unk3110 > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > 0xc7) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x82;
                    return;
                }
                if (v10 > 200.0 && unk3110 < 0xbe && unk3110 > 0xaa) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && unk3110 < 0xd2 && unk3110 > 0xbe) {
                    m_command = 0x28;
                    return;
                }
                if (v10 > 140.0 && v10 < 180.0 && unk3110 < 0xd2 && unk3110 > 0xbe) {
                    m_command = 0x29;
                    return;
                }
                if (v10 > 200.0 && v10 < 240.0 && unk3110 < 0xd2 && unk3110 > 0xbe) {
                    m_command = 0x2a;
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
                    if (v10 < 80.0 && unk3110 < 0xf && m_gauge >= 0x3e8) {
                        m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && unk3110 < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x16;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 100.0 && unk3110 < 0x23 && unk3110 > 0xa) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 180.0 && x8 > 140.0 && unk3110 < 0x3c && unk3110 > 0x23) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 140.0 && x8 > 100.0 && unk3110 < 0x50 && unk3110 > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && unk3110 < 0x6e && unk3110 > 0x50 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)CPlayer::Random(0, 3) + 0x78;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && unk3110 < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && unk3110 > 0x32 && unk3110 < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && unk3110 > 0x78 && unk3110 < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)CPlayer::Random(0, 0x140) < v10 - 100.0 && x8 < 90.0 && unk3110 > 0xaa && unk3110 < 0xdc) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                    return;
                }
                if (v10 > 100.0 && unk3110 > 0xf0 && unk3110 < 0x14a && x8 + 40.0 > v10 && x8 - 40.0 < v10) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && unk3110 < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && unk3110 > 0x14 && unk3110 < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && unk3110 > 0x28 && unk3110 < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)CPlayer::Random(0, 0x140) < v10 - 100.0 && x8 < 180.0 && unk3110 > 0xaa && unk3110 < 0xf0) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 3.0f * unka8) {
        m_command = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 60.0 && v10 < 140.0 && (WORD)CPlayer::Random(0, 0x64) < 2.0f * unka8 && x > 120.0 && x < 520.0) {
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
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x2d;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x2d;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x1e) {
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

void CMishio::UpdateObjects()
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
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    m_objects[v4].vx = 2.5;
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame < 0x31) {
                    m_objects[v4].frame = 0x31;
                    m_objects[v4].timer = 0;
                    unk3148 = 0;
                    break;
                }
                if (m_objects[v4].frame > 0x31) {
                    m_objects[v4].vx -= 0.06;
                    if (m_objects[v4].vx < 0.3) {
                        m_objects[v4].vx = 0.3;
                    }
                }
                if (m_objects[v4].x > 700.0 || m_objects[v4].x < -60.0) {
                    RemoveObject(v4);
                    unk3148 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x31 && unk3174[v4] < 5) {
                        m_objects[v4].frame = 0x1d;
                        unk3174[v4]++;
                    }
                    if (m_objects[v4].frame == 0x31) {
                        unk3148 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x191:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 3;
                    unk3174[v4]++;
                    m_objects[v4].vx = 1.2;
                }
                if (m_objects[v4].frame > 0x31) {
                    m_objects[v4].vx -= 0.02;
                    if (m_objects[v4].vx < 0.3) {
                        m_objects[v4].vx = 0.3;
                    }
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame < 0x31) {
                    unk3274[v4]++;
                    if (m_objects[v4].unk84 == 0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x31;
                        unk3148 = 0;
                    }
                }
                if (m_objects[v4].x > 700.0 || m_objects[v4].x < -60.0) {
                    RemoveObject(v4);
                    unk3148 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (unk3274[v4] > 0x1e) {
                        m_objects[v4].unk80 = 0;
                        unk3274[v4] = 0;
                    }
                    if (m_objects[v4].frame == 0x31 && unk3174[v4] < 7) {
                        m_objects[v4].frame = 0x1d;
                        unk3174[v4]++;
                    }
                    if (m_objects[v4].frame == 0x31) {
                        unk3148 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x192:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 0x63;
                    unk3174[v4]++;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].vx += 0.0025;
                if (m_objects[v4].unk80 > 0) {
                    unk3274[v4]++;
                }
                if (m_objects[v4].x > 700.0 || m_objects[v4].x < -60.0) {
                    RemoveObject(v4);
                    unk3148 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (unk3274[v4] > 0xf) {
                        m_objects[v4].unk80 = 0;
                        unk3274[v4] = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x193:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                }
                if ((pattern != 0x102 && pattern != 0x106 || pattern == 0x106 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x194:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                }
                if ((pattern != 0x101 && pattern != 0x100 && pattern != 0x107 || pattern == 0x107 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x195:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                }
                if ((pattern != 0x103 && pattern != 0x108 || pattern == 0x108 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x196:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                }
                if ((pattern != 0x104 && pattern != 0x109 || pattern == 0x109 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x197:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                }
                if ((pattern != 0x105 && pattern != 0x10a || pattern == 0x10a && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x198:
                if (m_objects[v4].timer == 0) {
                    if (m_objects[v4].frame == 0) {
                        m_objects[v4].unk84 = 1;
                    }
                    if (m_objects[v4].frame == 0x12) {
                        m_objects[v4].unk84 = 1;
                    }
                }
                if (m_objects[v4].frame > 0x12) {
                    unk3174[v4]--;
                    if (unk3174[v4] <= 0) {
                        l50.type = 0x199;
                        l50.x = (double)((int)m_objects[v4].x + 0x32 - (WORD)CPlayer::Random(0, 0x64));
                        l50.y = (double)((int)m_objects[v4].y + 0x32 - (WORD)CPlayer::Random(0, 0x64));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        unk3174[v4] = 0xf;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x10) {
                        unk2c8 = 4;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        unk314c = 0;
                    }
                }
                break;
            case 0x199:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
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
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                    unk3174[v4]--;
                    if (unk3174[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x32) + 0x1e) * facing);
                        l50.y = (double)((int)y - 0x50 - (WORD)CPlayer::Random(0, 0x32));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        unk3174[v4] = 0xc;
                    }
                }
                if ((pattern != 0x132 || pattern == 0x132 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x19e:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                    unk3174[v4]--;
                    if (unk3174[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x32) + 7) * facing);
                        l50.y = (double)((int)y - 0x32 - (WORD)CPlayer::Random(0, 0x32));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        unk3174[v4] = 0xc;
                    }
                }
                if ((pattern != 0x12f && pattern != 0x130 && pattern != 0x131 && pattern != 0x133 || pattern == 0x133 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                    unk3174[v4]--;
                    if (unk3174[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x32) + 0x23) * facing);
                        l50.y = (double)((int)y - 0x14 - (WORD)CPlayer::Random(0, 0x32));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        unk3174[v4] = 0xc;
                    }
                }
                if ((pattern != 0x134 && pattern != 0x134 || pattern == 0x134 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                    unk3174[v4]--;
                    if (unk3174[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x32) + 0x14) * facing);
                        l50.y = (double)((int)y + 0x19 - (WORD)CPlayer::Random(0, 0x32));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        unk3174[v4] = 0xc;
                    }
                }
                if ((pattern != 0x135 && pattern != 0x135 || pattern == 0x135 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x1a0:
                if (m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = x;
                    m_objects[v4].y = y;
                    unk3174[v4]--;
                    if (unk3174[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)x + ((WORD)CPlayer::Random(0, 0x32) - 0x1e) * facing);
                        l50.y = (double)((int)y + 0x14 - (WORD)CPlayer::Random(0, 0x32));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                        unk3174[v4] = 0xc;
                    }
                }
                if ((pattern != 0x136 && pattern != 0x136 || pattern == 0x136 && frame < 6) && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
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
            case 0x1a1:
                if (pattern != 0x138 && pattern != 0x139 && pattern != 0x13a && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
                    m_objects[v4].unk84 = 0;
                    break;
                }
                if (pattern != 0x138 && pattern != 0x139 && pattern != 0x13a && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1a;
                    m_objects[v4].unk84 = 0;
                    break;
                }
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                }
                if (frame < 0xa && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = facing * 0xf + x;
                    m_objects[v4].y = y - 148.0;
                }
                if (frame == 0xb && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = (facing << 4) + x;
                    m_objects[v4].y = y - 147.0;
                    m_objects[v4].unk84 = 0;
                }
                if (frame == 0xc && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = facing * 0x68 + x;
                    m_objects[v4].y = y - 54.0;
                }
                if (frame > 0xc && frame < 0x12 && m_objects[v4].frame < 0x1a) {
                    m_objects[v4].x = facing * 0x68 + x;
                    m_objects[v4].y = y - 53.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x1a && unk313c < 4) {
                        m_objects[v4].frame = 0xb;
                        m_objects[v4].unk80 = 0;
                        unk2c8 = 7;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a2:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1a3:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1a4:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1a5:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a6:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(50.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 2;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x14) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a7:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(55.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 3;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x1e) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a8:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(45.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 3;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x1e) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a9:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(60.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 4;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x28) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1aa:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(55.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 4;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x28) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ab:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(45.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 4;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x28) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ac:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(40.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 4;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x28) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ad:
                if (pattern == 0x138 || pattern == 0x139 || pattern == 0x13a) {
                    m_objects[v4].x = facing * 0xf + x;
                    m_objects[v4].y = y - 148.0;
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
            case 0x1ae:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1af:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1b0:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1b1:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(50.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 3;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x1e) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b2:
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
                    (&m_objects[v4])->SetVelocity(50.0, 2.5);
                }
                if (m_objects[v4].frame < 0x1d && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1d;
                    m_objects[v4].unk84 = 4;
                    break;
                }
                if (m_objects[v4].frame < 0x2d && m_objects[v4].y == 0.0 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2d;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y < 0.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 0x1d) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                    }
                    if (m_objects[v4].frame == 0x2d && unk3274[v4] < 0x28) {
                        m_objects[v4].frame = m_objects[v4].frame - 0xa;
                        unk3274[v4]++;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b3:
                if (pattern == 0x13e) {
                    m_objects[v4].x = facing * 5 + x;
                    m_objects[v4].y = y - 45.0;
                }
                if (unk3174[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3174[v4]++;
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
            case 0x1b4:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b5:
                if (pattern < 0x111 || pattern > 0x113) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3174[v4] = 0;
                    unk3274[v4] = 0x14;
                }
                unk3174[v4] += unk3274[v4];
                unk3274[v4]--;
                if (unk3274[v4] < 1) {
                    unk3274[v4] = 1;
                }
                (&m_objects[v4])->SetVelocity((double)(unk3174[v4] - 0x78), (double)((WORD)CPlayer::Random(0, 0x1e) + 0x3c));
                l50.type = 0x19b;
                l50.x = (int)x + (m_objects[v4].vx + 20.0) * facing;
                l50.y = (int)y - 0x32 + m_objects[v4].vy;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b6:
                if (pattern < 0x114 || pattern > 0x116) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3174[v4] = 0;
                    unk3274[v4] = 0x14;
                }
                unk3174[v4] += unk3274[v4];
                unk3274[v4]--;
                if (unk3274[v4] < 1) {
                    unk3274[v4] = 1;
                }
                (&m_objects[v4])->SetVelocity((double)(unk3174[v4] - 0x78), (double)((WORD)CPlayer::Random(0, 0x1e) + 0x3c));
                l50.type = 0x1b7;
                l50.x = (int)x + (m_objects[v4].vx + 20.0) * facing;
                l50.y = (int)y - 0x32 + m_objects[v4].vy;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b7:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b8:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
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
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ba:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3174[v4] = 0;
                    m_objects[v4].unk84 = 5;
                }
                m_objects[v4].vx = 0.5;
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)((int)m_objects[v4].x + 0x32 - (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)((int)m_objects[v4].y + 0x32 - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3174[v4] < 5) {
                            m_objects[v4].frame = 1;
                            unk3174[v4]++;
                            m_objects[v4].unk80 = 0;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x1bb:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3174[v4] = 0;
                    m_objects[v4].unk84 = 0xa;
                }
                m_objects[v4].vx = 0.5;
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)((int)m_objects[v4].x + 0x32 - (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)((int)m_objects[v4].y + 0x32 - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3174[v4] < 0xa) {
                            m_objects[v4].frame = 1;
                            unk3174[v4]++;
                            m_objects[v4].unk80 = 0;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case 0x1bc:
                if (pattern < 0x111 || pattern > 0x113) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3174[v4] = 0;
                    unk3274[v4] = 0x14;
                }
                unk3174[v4] += unk3274[v4];
                unk3274[v4]--;
                if (unk3274[v4] < 1) {
                    unk3274[v4] = 1;
                }
                (&m_objects[v4])->SetVelocity((double)(0x78 - unk3174[v4]), (double)((WORD)CPlayer::Random(0, 0x1e) + 0x3c));
                l50.type = 0x19b;
                l50.x = (int)x + (m_objects[v4].vx + 20.0) * facing;
                l50.y = (int)y - 0x32 + m_objects[v4].vy;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1bd:
                if (pattern < 0x114 || pattern > 0x116) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3174[v4] = 0;
                    unk3274[v4] = 0x14;
                }
                unk3174[v4] += unk3274[v4];
                unk3274[v4]--;
                if (unk3274[v4] < 1) {
                    unk3274[v4] = 1;
                }
                (&m_objects[v4])->SetVelocity((double)(0x78 - unk3174[v4]), (double)((WORD)CPlayer::Random(0, 0x1e) + 0x3c));
                l50.type = 0x1b7;
                l50.x = (int)x + (m_objects[v4].vx + 20.0) * facing;
                l50.y = (int)y - 0x32 + m_objects[v4].vy;
                l50.scale = 2;
                l50.layer = 1;
                l50.unk18 = facing;
                SpawnObject(&l50);
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3174[v4] == 0) {
                    unk3274[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3174[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3274[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3274[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3274[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3174[v4] == 0) {
                    unk3274[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3174[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3274[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3274[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3274[v4]--;
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
