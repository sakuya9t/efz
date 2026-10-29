// CMayu (0x5dddf0-0x5e85ef): the character class whose files are in mayu\ in the game
// folder (mayu.dat sprites, mayu.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMayu::CMayu(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "mayu");
    lastSurface = 0x182;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk2ad0[0] = -8;
    unk2af8[0] = -0x2e;
    unk2ad0[1] = -0x10;
    unk2af8[1] = 0;
    unk2ad0[2] = 0xe;
    unk2af8[2] = -5;
    unk2ad0[3] = 0x19;
    unk2af8[3] = -0x13;
    unk2ad0[4] = 0x1c;
    unk2af8[4] = -0x23;
    unk30f4 = 5;
    unk30f5[0] = 0;
    unk30f5[1] = 6;
    unk30f5[2] = 3;
    unk30f5[3] = 2;
    unk30f5[3] = 4;
    unk30f5[0xa] = 5;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3148[v4] = 0;
        unk3248[v4] = 0;
        unk3348[v4] = 0;
    }
}

void CMayu::Vf12()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk2ad0[0] = -8;
    unk2af8[0] = -0x2e;
    unk2ad0[1] = -0x10;
    unk2af8[1] = 0;
    unk2ad0[2] = 0xe;
    unk2af8[2] = -5;
    unk2ad0[3] = 0x19;
    unk2af8[3] = -0x13;
    unk2ad0[4] = 0x1c;
    unk2af8[4] = -0x23;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3148[v4] = 0;
        unk3248[v4] = 0;
        unk3348[v4] = 0;
    }
    CPlayer::Vf12();
}

void CMayu::Vf0()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::Vf0();
}

void CMayu::Vf10(short p1)
{
    unk3148[p1] = 0;
    unk3248[p1] = 0;
    unk3348[p1] = 0;
    CPlayer::Vf10(p1);
}

void CMayu::Vf3()
{
    CPlayer::Unk40e740();
}

void CMayu::Vf4()
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
    if (unk262 == 0x34 && (unk118 >= 500.0 && unk168 > 1 && unk168 != 6 || unk120 > 0 && unk168 > 1) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        Vf0();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (unk108 < 0xd05 && unk262 == 0x62 && unk148 >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk168 != 6 && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            if (x - (*m_opponent)->x < 60.0 && x - (*m_opponent)->x > -60.0) {
                pattern = 0x130;
            }
            return;
        }
        if (unk262 == 0x70 && unk148 >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13c].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13c;
            return;
        }
        if ((unk262 == 0x6f || unk262 == 0x70) && unk148 >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13b].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13b;
            return;
        }
        if ((unk262 == 0x6e || unk262 == 0x6f || unk262 == 0x70) && unk148 >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13a;
            return;
        }
        if (unk262 == 0x7a && unk148 >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x136].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x136;
            return;
        }
        if ((unk262 == 0x79 || unk262 == 0x7a) && unk148 >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if ((unk262 == 0x78 || unk262 == 0x79 || unk262 == 0x7a) && unk148 >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x134;
            return;
        }
        if (unk262 == 0xac && unk148 >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x141].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x141;
            return;
        }
        if ((unk262 == 0xab || unk262 == 0xac) && unk148 >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13f].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13f;
            return;
        }
        if ((unk262 == 0xaa || unk262 == 0xab || unk262 == 0xac) && unk148 >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13d].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13d;
            return;
        }
        if (unk262 == 0x48 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            return;
        }
        if ((unk262 == 0x47 || unk262 == 0x48) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            return;
        }
        if (unk262 == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            return;
        }
        if (unk262 == 0x49 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x11b].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x11b;
            return;
        }
        if (unk262 == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10c].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10c;
            return;
        }
        if ((unk262 == 0x15 || unk262 == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10b].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10b;
            return;
        }
        if (unk262 == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10a].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10a;
            return;
        }
        if (unk262 == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x105;
            if (y < 0.0) {
                pattern = 0x11a;
            }
            return;
        }
        if ((unk262 == 0xb || unk262 == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x104;
            if (y < 0.0) {
                pattern = 0x119;
            }
            return;
        }
        if (unk262 == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x103;
            if (y < 0.0) {
                pattern = 0x118;
            }
            return;
        }
        if (unk262 == 0x21 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x111].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x111;
            if (y < 0.0) {
                frame = 4;
            }
            return;
        }
        if (unk262 == 0x20 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x112].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x112;
            if (y < 0.0) {
                frame = 4;
            }
            return;
        }
        if (unk262 == 0x1f && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x121].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x121;
            if (y < 0.0) {
                frame = 4;
            }
            return;
        }
        if (unk262 == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x110].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x110;
            if (y < 0.0) {
                frame = 4;
            }
            return;
        }
    }
    if (unk15c < 1 && (unk262 == 0 || unk262 == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (unk262 << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (unk262 << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                if (pattern != 0xa5) {
                    Vf0();
                }
                pattern = 0xa5;
                CPlayer::Unk40e630();
                unk159++;
                unk1a8 = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (unk262 << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (unk262 << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa6].unk0 && pattern != 0xaa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                if (pattern != 0xa6) {
                    Vf0();
                }
                pattern = 0xa6;
                CPlayer::Unk40e630();
                unk159++;
                unk1a8 = 0;
                return;
            }
        }
        if (y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0) {
            if ((((*m_opponent)->x - x) * (1 - (unk262 << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (unk262 << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa3].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                if (pattern != 0xa3) {
                    Vf0();
                }
                pattern = 0xa3;
                CPlayer::Unk40e630();
                unk158++;
                unk1a8 = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (unk262 << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (unk262 << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa4].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                if (pattern != 0xa4) {
                    Vf0();
                }
                pattern = 0xa4;
                CPlayer::Unk40e630();
                unk1a8 = 0;
                return;
            }
        }
    }
    if (unk15c < 3 && unk262 == 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk15a < 1 && m_patterns[pattern].unk2 <= m_patterns[0xe].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
        Vf0();
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
        if (y < 0.0 && pattern == 0xa3 && frame > 5) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xe6].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xe6;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xcf].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xcf;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcc].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xcc;
            return;
        }
        if ((m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) && m_patterns[pattern].unk2 <= m_patterns[0xc8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xc8;
            return;
        }
    }
    if (m_pressB == 1 || (unk1a8 & 0x20) != 0 || (unk1a9 & 0x20) != 0) {
        if (y < 0.0 && pattern == 0xa3 && frame > 5) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xe7].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xe7;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd0].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd0;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_inputX == -facing && m_patterns[pattern].unk2 <= m_patterns[0xd3].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xd3;
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_inputX == facing && m_patterns[pattern].unk2 <= m_patterns[0xd2].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd2;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -70.0 && x - (*m_opponent)->x < 70.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xc9;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xca].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xca;
                return;
            }
        }
    }
    if (m_pressC == 1 || (unk1a8 & 0x40) != 0 || (unk1a9 & 0x40) != 0) {
        if (y < 0.0 && pattern == 0xa3 && frame > 5) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xe8].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xe8;
            }
            return;
        }
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf8].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xf8;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd1;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xce].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xce;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xcb;
            }
        }
    }
}

void CMayu::Vf1()
{
}

void CMayu::Vf8()
{
}

void CMayu::Vf9(EffectDesc* p1)
{
    Vf10(unk2ca);
    CPlayer::Vf9(p1);
}

void CMayu::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    unk262 = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 5) {
            unk262 = 0x62;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 4) {
            if ((v5 & 0x80) != 0) {
                unk262 = 0x62;
                return;
            }
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 9 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && unk148 == 0xbb8 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            unk262 = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == 4 && x6 == 0 && unk148 >= 0x3e8 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x69;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x70) != 0 && x6 == 4) {
            unk262 = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 3) {
            if ((v5 & 0x70) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && unk148 >= 0x3e8 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            unk262 = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            unk262 = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0 && y == 0.0 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            unk262 = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            unk262 = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
            unk262 = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
            unk262 = 6;
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
            unk262 = 0x35;
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
            unk262 = 0x34;
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
            unk262 = 0x33;
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
            unk262 = 0x32;
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
            unk262 = 1;
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
            unk262 = 0;
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

void CMayu::Vf5()
{
    double v10;
    double x8;

    unk262 = 0x63;
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 25.0f * unka8 + (y < 0.0) * 0x1e * unka8 + (unk3114 == 3) * 0x190 + (pattern == 0xaa) * 0x12c) {
        unk14e = 0x3c;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x7d0) < ((unk130 > 0) * 4.0 + 1.0) * 8.0 * unka8 * ((pattern > 0x95 && pattern < 0x9d) * 2 + 1)) {
        unk14e = 0x3c;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 4e+01f * unka8 && pattern > 0xc7) {
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
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8) {
            unk3114 = 3;
        } else {
            unk3114 = 0;
        }
        m_inputX = 1 - (((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) << 1);
        m_pressD = (WORD)CPlayer::Unk4108a0(0, 0xf0) < x8;
        m_pressD = (WORD)CPlayer::Unk4108a0(0, 0x140) < v10;
        if ((*m_opponent)->pattern > 0xc7 && (*m_opponent)->pattern < 0xfa && (*m_opponent)->frame < 3 && x8 < 100.0 && v10 < 150.0) {
            m_pressD = 0;
        }
        return;
    }
    if ((pattern >= 4 && pattern <= 6 || pattern >= 0xa && pattern <= 0xc) && y == 0.0) {
        return;
    }
    if ((*m_opponent)->pattern >= 0x32 && (*m_opponent)->pattern < 0x96 && pattern == 0x108 && unk16c > 1) {
        return;
    }
    if (pattern == 0xa8 && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->unk16c == 0) {
            if (v10 < 40.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->unk16c == 0 && v10 > 60.0 && v10 < 70.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 80.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                unk262 = 0x16;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f + ((unk118 > 500.0) << 1)) {
                unk262 = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 4.0f && unk148 >= 0x3e8 && (*m_opponent)->y == 0.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk148 == 0xbb8 && (*m_opponent)->y < -30.0) {
                unk262 = 0x7a;
                return;
            }
        }
        if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
            unk262 = 0xc;
            return;
        }
        if (v10 > 120.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                unk262 = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 0) * 2 + 0x1e;
                return;
            }
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            unk3114 = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -40.0 && y - (*m_opponent)->y < 0.0 && v10 < 70.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -60.0 && y - (*m_opponent)->y < 30.0 && x8 > 80.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f) {
            unk262 = 0x1e;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (unk3110 < 4 && unk118 > 500.0) {
            unk262 = 0x16;
            return;
        }
        if (unk3110 < 0xa && unk118 > 500.0) {
            unk262 = 0xc;
            return;
        }
        if (unk3110 < 0xd && v10 > 100.0) {
            unk262 = 0x1e;
            return;
        }
        if (unk3110 < 0xd && v10 < 90.0) {
            unk262 = 0x20;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && unk148 >= 0x3e8 && v10 < 80.0) {
            unk262 = (WORD)CPlayer::Unk4108a0(0, 2) * 0x64;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (unk3110 < 0x14) {
            unk3114 = 2;
            return;
        }
        if (v10 < 100.0 && unk3110 < 0x16) {
            unk262 = 0x1e;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x103 || pattern == 0x104 || pattern == 0x10a || pattern == 0x10b || pattern == 0x12d || pattern == 0x12e)) {
        unk262 = 0x34;
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
        m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
        if (pattern == 4 || pattern == 5 || pattern == 6) {
            unk262 = facing == 1;
            if (pattern == 0xa5) {
                unk3114 = 0;
            }
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (unk3114 == 5 && pattern < 0x32) {
        unk3114 = 0;
        unk262 = facing == 1;
        return;
    }
    if (unk3114 == 6 && pattern < 0x32) {
        unk3114 = 7;
        unk262 = facing == 1;
        return;
    }
    if (unk3114 == 7 && pattern == 0xa3) {
        m_inputX = -facing;
        m_pressB = 1;
        if (pattern == 0xe7) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 8 && pattern < 0x32) {
        unk262 = facing == 1;
        unk3114 = 9;
        return;
    }
    if (unk3114 == 9 && pattern == 0xa3) {
        m_inputX = -facing;
        m_pressA = 1;
        if (pattern == 0xe6) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 0xa && pattern < 0x32) {
        m_inputY = 0;
        m_pressA = 1;
        if (pattern == 0xc8) {
            unk3114 = 0;
        }
        return;
    }
    if (unk168 > 1 && unk14a == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 25.0f && unk3114 != 0 && unk3114 != 2) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x96) {
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
                if (unk168 == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 100.0 && unk3110 > 0x96 && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x258) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    unk3114 = 5;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    unk3114 = 6;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x190 && unk168 == 3) {
                unk262 = 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x190 && unk3110 < 0x1f4 && unk148 >= 0x3e8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x190 && unk3110 < 0x2bc && v10 < 90.0) {
                m_inputY = -1;
                m_inputX = facing;
                return;
            }
            if (unk3110 < 0x96) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x96 && unk3110 < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x226) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x226 && unk3110 < 0x258) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x26c && v10 > 80.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x398) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x1f3) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 5;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    unk3114 = 8;
                }
                if (v10 < 45.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 0xa;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && (*m_opponent)->y < -50.0 && v10 < 70.0 && unk3110 < 0xc8 && unk168 == 3 && unk148 == 0xbb8) {
                unk262 = 0x7a;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xc7 && unk3110 < 0x190) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x190 && unk3110 < 0x1f4) {
                unk262 = 0xb;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x18f && unk3110 < 0x1f4 && unk168 == 3) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x190 && v10 < 90.0) {
                m_pressC = 1;
                m_inputY = 0;
                if ((WORD)CPlayer::Unk4108a0(0, 0xa) < 7) {
                    m_inputY = 1;
                }
                return;
            }
            if (unk3110 > 0x1e0 && unk3110 < 0x226 && unk168 == 3 && unk148 >= 0x3e8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xaa;
                return;
            }
            if (unk3110 > 0x226 && unk3110 < 0x258) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x26c && v10 > 80.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x26c) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 5;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    unk3114 = 8;
                }
                if (v10 < 45.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 0xa;
                }
                return;
            }
        }
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xc8 && unk168 == 3 && x8 < 70.0 && unk118 > 500.0) {
                unk262 = 0xc;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x64 && unk168 != 3 && unk118 > 500.0) {
                unk262 = 0xa;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk262 = 0xb;
                }
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x226) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x226 && unk3110 < 0x258 && unk168 == 3 && unk148 >= 0x3e8 && v10 < 90.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xaa;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x2a8 && v10 > 80.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x31f) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x96) {
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
                if (unk168 == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 100.0 && unk3110 > 0x96 && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x1f4) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    unk3114 = 5;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 8;
                }
                if (v10 < 45.0 && (WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    unk3114 = 0xa;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x190 && unk168 == 3) {
                unk262 = 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x190 && unk3110 < 0x2bc && v10 < 90.0) {
                m_inputY = -1;
                m_inputX = facing;
                return;
            }
            if (unk3110 < 0xc8) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0x15e) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x226) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x226 && unk3110 < 0x258) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x26c && v10 > 80.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x398) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x28a) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    unk3114 = 5;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 8;
                }
                if (v10 < 45.0 && (WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    unk3114 = 0xa;
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (unk3110 < 0xc8 && unk168 == 3 && unk118 > 500.0) {
                unk262 = 0xc;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x64 && unk168 != 3 && unk118 > 500.0) {
                unk262 = 0xa;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk262 = 0xb;
                }
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x226) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x226 && unk3110 < 0x258 && unk168 == 3 && unk148 >= 0x3e8 && v10 < 70.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0x258 && unk3110 < 0x2a8 && v10 > 80.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x31f) {
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
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    unk3114 = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
            if (unk3110 > 0x14 && unk3110 < (unk168 != 3) * 0x32 + 0x32 && (*m_opponent)->y < 0.0) {
                unk262 = 0x1e;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk262 = 0x20;
                }
                return;
            }
            if (unk3110 > 0x3c && unk3110 < 0x12c) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x3b6) {
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 3;
                return;
            }
        }
        if (pattern == 0xd1) {
            if (unk3110 > 0x14 && unk3110 < (unk168 != 3) * 0x32 + 0x32 && (*m_opponent)->y < 0.0) {
                unk262 = 0x1e;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk262 = 0x20;
                }
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 3;
                return;
            }
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * unka8) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && unk3110 < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 35.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x1e + 0x19 + ((*m_opponent)->pattern < 0x31) * 0x14) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 50.0 && unk3110 > 0x3c) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x1e + 0x50 + ((*m_opponent)->pattern < 0x31) * 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 < 70.0 && unk3110 > 0x82) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x1e + 0x91 + ((*m_opponent)->pattern < 0x31) * 0x14) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 100.0 && unk3110 > 0xc8) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x1e + 0xeb + ((*m_opponent)->pattern < 0x31) * 0x14) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 < 120.0 && v10 > 100.0 && unk3110 > 0x12c && unk3110 < 0x136) {
                    m_pressC = 1;
                    return;
                }
                if (v10 > 80.0 && unk3110 < 0x154 && unk3110 > 0x140) {
                    unk262 = 0x1e;
                    return;
                }
                if (v10 > 150.0 && unk3110 < 0x172 && unk3110 > 0x15e) {
                    unk262 = 0x20;
                    return;
                }
                if (unk3110 < 0x190 && unk3110 > 0x1a4 && v10 > 150.0) {
                    unk262 = facing;
                    unk3114 = 5;
                    return;
                }
                if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x64 + 0x1e0 + ((*m_opponent)->pattern < 0x31) * 0x14 && unk3110 > 0x1c2 && v10 < 100.0) {
                    unk3114 = 6;
                    return;
                }
                if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x64 + 0x276 + ((*m_opponent)->pattern < 0x31) * 0x14 && unk3110 > 0x258 && v10 < 100.0) {
                    unk3114 = 6;
                    return;
                }
                if (v10 < 220.0 && unk3110 < 0x2bc && unk3110 > 0x2c6 && unk118 > 500.0) {
                    unk262 = 0xc;
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
                    if (x8 * 0.5 > v10 && x8 > 50.0 && x8 < 180.0 && unk3110 > 0x28 && unk3110 < 0x46 && unk148 >= 0x3e8) {
                        unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 140.0 && x8 < 110.0 && x8 > 80.0 && unk3110 < 0x28) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (x8 * 0.5 > v10 && x8 > 50.0 && x8 < 180.0 && unk3110 > 0x28 && unk3110 < 0x46 && unk148 >= 0x3e8) {
                        unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                        return;
                    }
                    if (v10 < 80.0 && x8 > 130.0 && x8 < 160.0 && unk3110 > 0x46 && unk3110 < 0x50) {
                        unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x14;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 70.0 && x8 < 60.0 && y < (*m_opponent)->y && unk3110 < 0xc8) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 50.0 && x8 < 100.0 && unk3110 < 0x190) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 40.0 && x8 < 60.0 && (*m_opponent)->y > y && unk3110 > 0x190 && unk3110 < 0x26c) {
                    m_pressC = 1;
                    return;
                }
                if (unk3110 > 0x28a && unk3110 < 0x294) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 70.0 && x8 < 60.0 && y < (*m_opponent)->y && unk3110 < 0xc8) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 50.0 && x8 < 100.0 && unk3110 < 0x190) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 40.0 && x8 < 60.0 && (*m_opponent)->y > y && unk3110 > 0x190 && unk3110 < 0x26c) {
                    m_pressC = 1;
                    return;
                }
                if (unk3110 > 0x28a && unk3110 < 0x2bc) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1.0f * unka8) {
        if (v10 < 100.0) {
            unk262 = facing == 1;
        }
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 2) {
        unk3114 = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8) {
            unk3114 = 3;
        } else {
            unk3114 = 0;
        }
        if (v10 > 240.0 && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 80.0 && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 140.0 && y == 0.0) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28 && v10 < 60.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        } else {
            unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x50) {
        if (facing == 1) {
            unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        } else {
            unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        }
        return;
    }
    if (facing == -1) {
        unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        return;
    }
    unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
}

void CMayu::Vf7()
{
    WORD v58;
    WORD v54;
    int v4;

    if ((*m_opponent)->unk14c > 0) {
        return;
    }
    v4 = unk2cc;
    EffectDesc l50;
    while (v4 != unk2ca) {
        if (unk3d0[v4] != 0 && m_objects[v4].unk86 == 0 && (unk14c == 0 || unk14c > 0 && m_objects[v4].unk88 != 0)) {
            v54 = (short)anims[m_objects[v4].pattern].frames[m_objects[v4].frame].duration;
            v58 = anims[m_objects[v4].pattern].frameCount;
            CPlayer::Unk413090((EffectDesc*)&l50);
            switch (m_objects[v4].pattern) {
            case 0x190:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 2.0;
                    unk3148[v4]++;
                }
                m_objects[v4].vx -= 0.03;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0) {
                    Vf10(v4);
                }
                break;
            case 0x191:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -3.1;
                    m_objects[v4].ay = 0.08;
                }
                if (m_objects[v4].frame < 0xb) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objects[v4].frame == 3 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    m_objects[v4].ay = 0.0;
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x62;
                    m_objects[v4].y = 0.0;
                    CPlayer::Unk4105a0(0x12c, 960.0);
                    if ((*m_opponent)->unk108 <= 0) {
                        (*m_opponent)->unk108 = 1;
                    }
                    l50.type = 0;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk2c = 2;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    break;
                }
                if (m_objects[v4].frame == 5 && unk3138 > 0x334) {
                    m_objects[v4].frame = 6;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vy = -5.0;
                    m_objects[v4].ay = 0.06;
                    break;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 6) {
                        if (unk3138 <= 0x2da) {
                            m_objects[v4].frame = 0;
                            m_objects[v4].vx = 0.0;
                            m_objects[v4].vy = -3.1;
                            m_objects[v4].ay = 0.08;
                        } else {
                            m_objects[v4].frame = 5;
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x193;
                    }
                }
                break;
            case 0x192:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].ay = 0.07;
                }
                if (m_objects[v4].frame < 0xb) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objects[v4].frame == 3 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x62;
                    m_objects[v4].y = 0.0;
                    CPlayer::Unk4105a0(0x12c, 960.0);
                    if ((*m_opponent)->unk108 <= 0) {
                        (*m_opponent)->unk108 = 1;
                    }
                    l50.type = 0;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk2c = 2;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    break;
                }
                if (m_objects[v4].frame == 5 && unk3138 > 0x334) {
                    m_objects[v4].frame = 6;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vy = -5.0;
                    m_objects[v4].ay = 0.06;
                    break;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 6) {
                        if (unk3138 <= 0x2da) {
                            m_objects[v4].frame = 0;
                            m_objects[v4].vx = 0.0;
                            m_objects[v4].vy = -2.1;
                            m_objects[v4].ay = 0.07;
                        } else {
                            m_objects[v4].frame = 5;
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x194;
                    }
                }
                break;
            case 0x193:
                if (unk3140 == 1 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    unk2c9 = 0x1a;
                    m_objects[v4].vx = 1.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 740.0) {
                    Vf10(v4);
                }
                break;
            case 0x194:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.8;
                    m_objects[v4].vy = -2.0;
                }
                m_objects[v4].vy += 0.043;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                        unk3140 = 1;
                    }
                }
                break;
            case 0x195:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x196:
                m_objects[v4].x = x;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 7 && frame <= 0xb) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    } else if (m_objects[v4].frame >= v58 || pattern != 0x132) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x197:
                m_objects[v4].x = x;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 7 && frame <= 0xb) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    } else if (m_objects[v4].frame >= v58 || pattern != 0x132) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x198:
                m_objects[v4].vx = 2.0;
                m_objects[v4].vy = -4.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 4;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].y > -480.0) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                }
                if (m_objects[v4].y < -680.0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x199;
                    m_objects[v4].x = (*m_opponent)->x + m_objects[v4].facing * ((m_objects[v4].y - (*m_opponent)->y) / 2.0);
                    return;
                }
                break;
            case 0x199:
                m_objects[v4].vx = 3.0;
                m_objects[v4].vy = 6.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 4;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                }
                if (m_objects[v4].y > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].pattern = 0x19a;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                break;
            case 0x19a:
                m_objects[v4].unk84 = 1;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk2c8 = 3;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ef:
                m_objects[v4].vx = -0.02;
                m_objects[v4].unk8c = 0x7530;
                m_objects[v4].timer++;
                if (pattern != 0x57) {
                    Vf10(v4);
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
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - (facing << 2));
                    l50.y = (double)((int)y - 6);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0xe);
                    l50.y = (double)((int)y - 0x1a);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0x19);
                    l50.y = (double)((int)y - 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x23);
                    l50.y = (double)((int)y - 0x2a);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x12);
                    l50.y = (double)((int)y - 0x14);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + facing * 2);
                    l50.y = (double)((int)y - 0x41);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + (facing << 4));
                    l50.y = (double)((int)y - 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    unk2c9 = 0x22;
                    Vf10(v4);
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    unk3248[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3148[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3248[v4] < 0xa) {
                    m_objects[v4].unk50 = 1;
                }
                if (unk3248[v4] < 0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3248[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    unk3248[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3148[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3248[v4] < 0xa) {
                    m_objects[v4].unk50 = 1;
                }
                if (unk3248[v4] < 0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3248[v4]--;
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
                        Vf10(v4);
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
