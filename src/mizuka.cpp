// CMizuka (0x4f8300-0x50c4af): the character class whose files are in mizuka\ in the game
// folder (mizuka.dat sprites, mizuka.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMizuka::CMizuka(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "mizuka");
    lastSurface = 0x29c;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk2ad0[0] = -0xd;
    unk2af8[0] = -0x3c;
    unk2ad0[1] = 0xe;
    unk2af8[1] = 0;
    unk3448 = 0;
    unk344c = 0;
    unk3450 = 0;
    unk3454 = 0;
    unk3458 = 0;
    unk30f4 = 6;
    unk30f5[0] = 6;
    unk30f5[1] = 1;
    unk30f5[2] = 7;
    unk30f5[0xa] = 0x12;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3148[v4] = 0;
        unk3248[v4] = 0;
        unk3348[v4] = 0;
    }
}

void CMizuka::Vf12()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk2ad0[0] = -0xd;
    unk2af8[0] = -0x3c;
    unk2ad0[1] = 0xe;
    unk2af8[1] = 0;
    unk3448 = 0;
    unk344c = 0;
    unk3450 = 0;
    unk3454 = 0;
    unk3458 = 0;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3148[v4] = 0;
        unk3248[v4] = 0;
        unk3348[v4] = 0;
    }
    CPlayer::Vf12();
}

void CMizuka::Vf0()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::Vf0();
}

void CMizuka::Vf10(short p1)
{
    unk3148[p1] = 0;
    unk3248[p1] = 0;
    unk3348[p1] = 0;
    CPlayer::Vf10(p1);
}

void CMizuka::Vf3()
{
    CPlayer::Unk40e740();
}

void CMizuka::Vf4()
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
    if (y == 0.0) {
        unk3458 = 0;
    }
    if (unk262 == 0x34 && (unk118 >= 500.0 || unk120 > 0) && unk168 > 1 && unk168 != 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        Vf0();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (unk262 == 0x84 && unk148 >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13c].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13c;
            return;
        }
        if (unk262 == 0x70 && unk148 >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13a;
            return;
        }
        if (unk262 == 0x66 && unk148 >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((unk262 == 0x65 || unk262 == 0x66) && unk148 >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((unk262 == 0x64 || unk262 == 0x65 || unk262 == 0x66) && unk148 >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (unk262 == 0x7a && unk148 >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if ((unk262 == 0x79 || unk262 == 0x7a) && unk148 >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x130;
            return;
        }
        if ((unk262 == 0x78 || unk262 == 0x79 || unk262 == 0x7a) && unk148 >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if (unk262 == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if ((unk262 == 0x14 || unk262 == 0x15 || unk262 == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x103;
            return;
        }
        if ((unk262 == 0x20 || unk262 == 0x1f || unk262 == 0x1e) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x109].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x109;
            return;
        }
        if (unk262 == 0x20 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if ((unk262 == 0x1f || unk262 == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            return;
        }
        if (unk262 == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            return;
        }
        if (unk262 == 0x48 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x102;
            return;
        }
        if (unk262 == 0x47 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x101;
            return;
        }
        if (unk262 == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if (unk262 == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            if (y < 0.0) {
                pattern = 0x108;
            }
            return;
        }
        if ((unk262 == 0xb || unk262 == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            if (y < 0.0) {
                pattern = 0x107;
            }
            return;
        }
        if (unk262 == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            if (y < 0.0) {
                pattern = 0x106;
            }
            return;
        }
    }
    if (unk15c < 1 && (unk262 == 0 || unk262 == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (unk262 << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (unk262 << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && (y < -40.0 || unk3458 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                if (pattern != 0xa5) {
                    Vf0();
                }
                pattern = 0xa5;
                CPlayer::Unk40e630();
                unk159++;
                unk15a++;
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
                unk15a++;
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
                unk158++;
                unk1a8 = 0;
                return;
            }
        }
    }
    if (unk15c < 3 && unk262 == 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk15a < 1 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xe].unk0) {
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
        if (pattern == 0xa3 && m_inputX != -facing) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xe6;
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
        if (pattern == 0xa3 && m_inputX != -facing) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xe7;
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
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
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
        if (pattern == 0xa3 && m_inputX != -facing) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xe8;
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd2].unk0 && m_inputX == facing && m_inputY == 0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd2;
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -40.0 && x - (*m_opponent)->x < 40.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xcb;
                return;
            }
        }
    }
    if (unk15c < 2 && (m_pressD == 1 || (unk1a8 & 0x80) != 0 || (unk1a9 & 0x80) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xb3].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && unk3458 <= 0) {
        Vf0();
        CPlayer::Unk40f170();
        pattern = 0xb3;
    }
}

void CMizuka::Vf1()
{
}

void CMizuka::Vf8()
{
}

void CMizuka::Vf9(EffectDesc* p1)
{
    Vf10(unk2ca);
    CPlayer::Vf9(p1);
}

void CMizuka::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    unk262 = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 5) {
            unk262 = 0x5a;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xd0) != 0 && x6 == 4) {
            break;
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
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xe0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xe0) != 0 && x6 == 5) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 5) {
            unk262 = 0x5b;
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 6) {
            unk262 = 0x5c;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 0 && x6 == 4) {
            x6 = 5;
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
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 5) {
            unk262 = 0x5d;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xd0) != 0 && x6 == 4) {
            break;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xe0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x20) != 0 && x6 == 5) {
            unk262 = 0x5e;
            return;
        }
        if ((v5 & 0x10) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xe0) != 0 && x6 == 4) {
            break;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
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
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 7) {
            unk262 = 0x5f;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0x20) != 0) {
                x6 = 7;
            } else {
                x6 = 6;
            }
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
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 6) {
            unk262 = 0x61;
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
        if ((v5 & 0x40) != 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x10) != 0 && x6 == 5) {
            unk262 = 0x62;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xd0) != 0 && x6 == 4) {
            break;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xe0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            unk262 = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            unk262 = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
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
            unk262 = ((v5 & 0xe0) > 0) + 0x96 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x96 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
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
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            unk262 = ((v5 & 0xe0) > 0) + 0x8c + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 5;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 3) {
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
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            unk262 = ((v5 & 0xe0) > 0) + 0x82 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x82 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            unk262 = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
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
    v4 = m_inputPos + 0x64;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            unk262 = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
    v4 = m_inputPos + 0x6e;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            unk262 = ((v5 & 0xe0) > 0) + 0x50 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x50 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x6e;
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
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x6e;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 3) {
            unk262 = 0x60;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0x40) != 0) {
                unk262 = 0x60;
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x6e;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            unk262 = ((v5 & 0xe0) > 0) + 0x50 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x50 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x6e;
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x6e;
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
    v4 = m_inputPos + 0x6e;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            unk262 = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
    v4 = m_inputPos + 0x6e;
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
        if ((v5 & 0xf) == 0 && x6 == 0) {
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
    v4 = m_inputPos + 0x5a;
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
    v4 = m_inputPos + 0x5a;
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
    v4 = m_inputPos + 0x7d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            unk262 = ((v5 & 0xe0) > 0) + 0x3c + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                unk262 = ((v5 & 0xe0) > 0) + 0x3c + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 1) {
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

void CMizuka::Vf5()
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
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->unk16c == 0) {
            if (v10 > 20.0 && v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                unk262 = 0x14;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                unk262 = 0x16;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                unk262 = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2 && v10 < 80.0 && unk148 >= 0xbb8) {
                unk262 = 0x70;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f && v10 < 150.0 && unk148 == 0xbb8) {
                unk262 = 0x84;
                return;
            }
        }
        if (v10 < 320.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                unk262 = 0x20;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 1.0f && unk148 == 0xbb8) {
                unk262 = 0x84;
                return;
            }
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            unk3114 = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            m_inputX = facing;
            return;
        }
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2) {
            unk262 = 0xc;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (unk3110 < 3 && unk118 > 500.0) {
            unk262 = 0x14;
            return;
        }
        if (unk3110 < 4 && unk118 > 500.0) {
            unk262 = 0xc;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && unk148 >= 0xbb8) {
            unk262 = 0x70;
            return;
        }
        if (unk3110 < 0x1e && unk3110 > 0x11 && unk148 >= 0xbb8) {
            unk262 = 0x84;
            return;
        }
        if (unk3110 > 0x32) {
            unk3114 = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (unk3110 < 3 && unk118 > 500.0) {
            unk262 = 0x16;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && unk148 >= 0x3e8) {
            unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
            return;
        }
        if (unk3110 > 0x55) {
            unk3114 = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x103 || pattern == 0x104 || pattern == 0x105 || pattern == 0x13a)) {
        unk262 = 0x34;
        return;
    }
    if (unk3458 > 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if ((*m_opponent)->y == 0.0) {
            if (v10 < 110.0 && x8 < 60.0 && unk3110 < 0x32) {
                m_pressA = 1;
                return;
            }
            if (v10 > 50.0 && v10 < 100.0 && x8 < 80.0 && unk3110 > 0x32 && unk3110 < 0x78) {
                m_pressB = 1;
                return;
            }
            if (v10 < 70.0 && x8 > 60.0 && x8 < 90.0 && unk3110 > 0x78 && unk3110 < 0xaa) {
                m_pressC = 1;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && unk3110 > 0xaa && unk3110 < 0xdc) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if (v10 > 100.0 && unk3110 > 0xf0 && unk3110 < 0x14a && x8 < 40.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
        }
        if ((*m_opponent)->y < 0.0) {
            if (v10 < 110.0 && x8 < 100.0 && unk3110 < 0x32) {
                m_pressA = 1;
                return;
            }
            if (v10 > 50.0 && v10 < 100.0 && x8 < 100.0 && unk3110 > 0x32 && unk3110 < 0x78) {
                m_pressB = 1;
                return;
            }
            if (v10 < 90.0 && x8 > 100.0 && x8 < 180.0 && unk3110 > 0x78 && unk3110 < 0xaa) {
                m_pressC = 1;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && unk3110 > 0xaa && unk3110 < 0xdc) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if (v10 > 100.0 && unk3110 > 0xf0 && unk3110 < 0x14a && x8 < 60.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
        }
        if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3.0f * unka8) {
            unk262 = facing == 1;
            return;
        }
        if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 60.0 && v10 < 140.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * unka8 && x > 120.0 && x < 520.0) {
            unk262 = -((facing == 1) - 1);
            return;
        }
        if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 1) {
            unk3114 = 4;
            return;
        }
        m_inputY = 1;
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) {
            m_inputY = -1;
        }
        if (x8 > 200.0) {
            m_inputY = 1;
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
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32 && v10 < 120.0) {
            if (facing == 1) {
                unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
            } else {
                unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
            }
        }
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) {
            if (facing == 1) {
                unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
            } else {
                unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
            }
        } else if (facing == -1) {
            unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        } else {
            unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        }
        return;
    }
    if (unk3114 == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 && (pattern > 0x95 && pattern < 0x9d || pattern == 0x60)) {
        unk3114 = 0xd;
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
        unk262 = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 6 && pattern < 0x32) {
        unk262 = facing == 1;
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
        unk262 = facing == 1;
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
        unk262 = facing == 1;
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
    if (unk3114 == 0xd) {
        unk262 = 0x14;
        if (pattern == 0x103) {
            unk3114 = 0;
        }
    }
    if (unk168 > 1 && unk14a == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 25.0f && unk3114 != 1 && unk3114 != 2) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 50.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (unk168 == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
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
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    unk3114 = 8;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && unk168 == 3) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140 && unk148 >= 0x3e8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x140 && unk3110 < 0x258 && unk168 == 3) {
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
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
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
                unk262 = 0xa;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x140 && unk3110 < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 < 0x1f4 && unk168 == 3 && v10 < 80.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && unk168 == 3) {
                unk262 = 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x131 && unk148 >= 0xbb8 && v10 < 90.0 && unk168 == 3) {
                unk262 = 0x84;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0x15e) {
                unk262 = 0x1e;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x1f4) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if (unk3110 > 0x1f4 && unk3110 < 0x258) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x29e && unk3110 < 0x2bc) {
                m_pressD = 1;
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
                if (unk168 == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
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
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
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
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    unk3114 = 6;
                    if (v10 > 110.0) {
                        unk3114 = 8;
                    }
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && unk168 == 3) {
                unk262 = 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x131 && unk148 >= 0xbb8 && v10 < 90.0 && unk168 == 3) {
                unk262 = 0x84;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x131 && unk3110 < 0x15e && unk148 >= 0x3e8 && unk168 == 3) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0x15e) {
                unk262 = 0x1e;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x1f4) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if (unk3110 > 0x1f4 && unk3110 < 0x258) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0x29e && unk3110 < 0x2bc) {
                m_pressD = 1;
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
            if (unk3110 > 0x14 && unk3110 < 0x3c && unk168 == 3 && (*m_opponent)->y < 0.0) {
                unk262 = 0xa;
                return;
            }
            if (unk3110 > 0x50 && unk3110 < 0x12c) {
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
            if (unk3110 > 0x3b6) {
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 3;
                return;
            }
        }
        if (pattern == 0xe7) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && unk168 == 3) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xdc && v10 < 90.0 && unk168 == 3 && unk148 >= 0x3e8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                unk262 = 0x34;
                return;
            }
            if (unk3110 > 0x289 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                unk3114 = 0xc;
                if (v10 > 110.0) {
                    unk3114 = 8;
                }
            }
        }
        if (pattern == 0xe8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && unk168 == 3) {
                unk262 = 0xa;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12b && unk3110 < 0x140 && unk148 >= 0x3e8 && v10 < 90.0) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0xc8 && unk168 == 3) {
                unk262 = 0xa;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                unk262 = 0x34;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1ae && unk168 == 3 && unk148 == 0xbb8) {
                unk262 = 0x5f;
                return;
            }
            if (unk3110 > 0x1ae && unk3110 < 0x21c && unk168 != 3) {
                unk262 = 0x28;
                if (v10 > 120.0) {
                    unk262 = 0x29;
                }
                return;
            }
            if (unk3110 > 0x38e && unk168 == 3) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 1;
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
                if (v10 < 50.0 && unk3110 < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 75.0 && unk3110 < 0x19) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 120.0 && unk3110 < 0x3c && unk3110 > 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x34 && unk3110 > 0x28 || v10 > 90.0 && v10 < 150.0 && unk3110 < 0x50 && unk3110 > 0x34) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && unk3110 < 0x55 && unk3110 > 0x50) {
                    unk3114 = 8;
                    return;
                }
                if (v10 > 70.0 && v10 < 120.0 && unk3110 < 0x78 && unk3110 > 0x5a) {
                    unk3114 = 8;
                    return;
                }
                if (v10 < 160.0 && v10 > 70.0 && unk3110 < 0x82 && unk3110 > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 100.0 && v10 > 70.0 && unk3110 < 0x91 && unk3110 > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 140.0 && unk3110 < 0x98 && unk3110 > 0x91) {
                    unk3114 = 0xa;
                    return;
                }
                if (v10 < 70.0 && unk3110 < 0xb9 && unk3110 > 0x91 && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    unk262 = 0x14;
                    return;
                }
                if (v10 < 100.0 && v10 > 40.0 && unk3110 < 0xbe && unk3110 > 0xb9 && unk148 >= 0xbb8 && (*m_opponent)->pattern > 0xc7) {
                    unk262 = 0x84;
                    return;
                }
                if (v10 > 120.0 && unk3110 < 0xc8 && unk3110 > 0xbe && unk148 >= 0xbb8 && (*m_opponent)->pattern > 0xc7) {
                    unk262 = 0x70;
                    return;
                }
                if (v10 > 200.0 && unk3110 < 0xbe && unk3110 > 0xaa) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 180.0 && unk3110 < 0xc8 && unk3110 > 0xbe) {
                    unk262 = 0x46;
                    return;
                }
                if (v10 > 180.0 && unk3110 < 0xd2 && unk3110 > 0xc8) {
                    unk262 = 0x47;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && unk3110 < 0xdc && unk3110 > 0xd2) {
                    unk262 = 0x1e;
                    return;
                }
                if (v10 > 140.0 && v10 < 180.0 && unk3110 < 0xf0 && unk3110 > 0xe6) {
                    unk262 = 0x1f;
                    return;
                }
                if ((unk118 > 500.0 || unk120 == 1) && unk3110 < 0xf5 && unk3110 > 0xf0) {
                    unk262 = 0x20;
                    return;
                }
                if (v10 > 140.0 && unk3110 < 0x104 && unk3110 > 0xfa && unk148 >= 0x3e8) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
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
                    if (v10 < 150.0 && v10 > 50.0 && unk3110 < 0x28 && unk148 >= 0xbb8) {
                        unk262 = 0x84;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && unk3110 < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        unk262 = 0x16;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && unk3110 < 0x1e) {
                        unk262 = 0x16;
                        return;
                    }
                    if (v10 < 80.0 && v10 > 30.0 && x8 < 140.0 && x8 > 100.0 && unk3110 < 0x41 && unk3110 > 0x1e) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 140.0 && x8 > 100.0 && unk3110 < 0x50 && unk3110 > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 160.0 && v10 > 30.0 && unk3110 < 0x6e && unk3110 > 0x50 && (*m_opponent)->y < -50.0 && unk148 >= 0xbb8) {
                        unk262 = 0x84;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 110.0 && x8 < 100.0 && unk3110 < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 50.0 && v10 < 100.0 && x8 < 100.0 && unk3110 > 0x32 && unk3110 < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 90.0 && x8 > 100.0 && x8 < 180.0 && unk3110 > 0x78 && unk3110 < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && x8 < 90.0 && unk3110 > 0xaa && unk3110 < 0xdc) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 100.0 && unk3110 > 0xf0 && unk3110 < 0x14a && x8 + 40.0 > v10 && x8 - 40.0 < v10) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 110.0 && x8 < 100.0 && unk3110 < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 50.0 && v10 < 100.0 && x8 < 100.0 && unk3110 > 0x32 && unk3110 < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 90.0 && x8 > 100.0 && x8 < 180.0 && unk3110 > 0x78 && unk3110 < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && x8 < 90.0 && unk3110 > 0xaa && unk3110 < 0xdc) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 100.0 && unk3110 > 0xf0 && unk3110 < 0x14a && x8 + 40.0 > v10 && x8 - 40.0 < v10) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3.0f * unka8) {
        unk262 = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 60.0 && v10 < 140.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * unka8 && x > 120.0 && x < 520.0) {
        unk262 = -((facing == 1) - 1);
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 1) {
        unk3114 = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8) {
            unk3114 = 3;
        } else {
            unk3114 = 0;
        }
        if (v10 > 180.0 && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32 && v10 < 120.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        } else {
            unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) {
        if (facing == 1) {
            unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        } else {
            unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        }
        return;
    }
    if (facing == -1) {
        unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        return;
    }
    unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
}

void CMizuka::Vf7()
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
            case 0x191:
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
            case 0x192:
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
            case 0x193:
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
            case 0x194:
                if (pattern != 0xd0) {
                    Vf10(v4);
                }
                m_objects[v4].x = facing * 0x25 + x;
                m_objects[v4].y = y - 72.0;
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
            case 0x195:
                m_objects[v4].x = (facing << 2) + x;
                m_objects[v4].y = y + 5.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 4 && pattern == 0xd1 && frame < 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x196:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x198:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0 && m_objects[v4].x > 0.0 && m_objects[v4].x < 640.0) {
                    l50.type = 0x199;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3c);
                    l50.y = 0.0;
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x199:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0 && m_objects[v4].x > 0.0 && m_objects[v4].x < 640.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3c);
                    l50.y = 0.0;
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19a:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0 && m_objects[v4].x > 0.0 && m_objects[v4].x < 640.0) {
                    l50.type = 0x198;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3c);
                    l50.y = 0.0;
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19b:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.7;
                    m_objects[v4].unk84 = 1;
                    unk3148[v4]++;
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
                if (m_objects[v4].x < -30.0 && m_objects[v4].facing == -1 || m_objects[v4].x > 670.0 && m_objects[v4].facing == 1) {
                    Vf10(v4);
                }
                break;
            case 0x19c:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.7;
                    m_objects[v4].unk84 = 1;
                    unk3148[v4]++;
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
                if (m_objects[v4].x < -30.0 && m_objects[v4].facing == -1 || m_objects[v4].x > 670.0 && m_objects[v4].facing == 1) {
                    Vf10(v4);
                }
                break;
            case 0x19d:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.7;
                    m_objects[v4].unk84 = 1;
                    unk3148[v4]++;
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
                if (m_objects[v4].x < -30.0 && m_objects[v4].facing == -1 || m_objects[v4].x > 670.0 && m_objects[v4].facing == 1) {
                    Vf10(v4);
                }
                break;
            case 0x19e:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.7;
                    m_objects[v4].unk84 = 1;
                    unk3148[v4]++;
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
                if (m_objects[v4].x < -30.0 && m_objects[v4].facing == -1 || m_objects[v4].x > 670.0 && m_objects[v4].facing == 1) {
                    Vf10(v4);
                }
                break;
            case 0x19f:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.7;
                    m_objects[v4].unk84 = 1;
                    unk3148[v4]++;
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
                if (m_objects[v4].x < -30.0 && m_objects[v4].facing == -1 || m_objects[v4].x > 670.0 && m_objects[v4].facing == 1) {
                    Vf10(v4);
                }
                break;
            case 0x1a0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3148[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.7;
                    m_objects[v4].unk84 = 1;
                    unk3148[v4]++;
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
                if (m_objects[v4].x < -30.0 && m_objects[v4].facing == -1 || m_objects[v4].x > 670.0 && m_objects[v4].facing == 1) {
                    Vf10(v4);
                }
                break;
            case 0x1a1:
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].unk80 == 3 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x25;
                    m_objects[v4].vx = 0.0;
                    unk2c8 = 0xc;
                    break;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x28;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].unk80 == 3) {
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x79;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x25) {
                        if (unk3148[v4] < 6) {
                            m_objects[v4].frame = 4;
                            unk3148[v4]++;
                        } else {
                            m_objects[v4].vx = 0.0;
                            m_objects[v4].frame = 0x28;
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                        if ((*m_opponent)->pattern == 0x79) {
                            (*m_opponent)->Vf0();
                            (*m_opponent)->Unk40f1e0();
                            (*m_opponent)->y = -480.0;
                            (*m_opponent)->x = x;
                            (*m_opponent)->pattern = 0x3b;
                        }
                    }
                }
                break;
            case 0x1a2:
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.35;
                    m_objects[v4].vy = -0.35;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].unk80 == 3 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x25;
                    m_objects[v4].vx = 0.0;
                    unk2c8 = 0xc;
                    break;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x28;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].unk80 == 3) {
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x79;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x25) {
                        if (unk3148[v4] < 6) {
                            m_objects[v4].frame = 4;
                            unk3148[v4]++;
                        } else {
                            m_objects[v4].vx = 0.0;
                            m_objects[v4].frame = 0x28;
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                        if ((*m_opponent)->pattern == 0x79) {
                            (*m_opponent)->Vf0();
                            (*m_opponent)->Unk40f1e0();
                            (*m_opponent)->y = -480.0;
                            (*m_opponent)->x = x;
                            (*m_opponent)->pattern = 0x3b;
                        }
                    }
                }
                break;
            case 0x1a3:
                if (m_objects[v4].frame >= 4 && m_objects[v4].frame < 0x25) {
                    unk3348[v4] = (int)AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - 50.0 - m_objects[v4].y);
                    (&m_objects[v4])->SetVelocity((double)unk3348[v4], -0.00875);
                    m_objects[v4].ax = m_objects[v4].vx;
                    m_objects[v4].ay = m_objects[v4].vy;
                    (&m_objects[v4])->SetVelocity((double)unk3348[v4], 1.4);
                    if (m_objects[v4].facing == -1) {
                        m_objects[v4].ax = -m_objects[v4].ax;
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].unk80 == 3 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x25;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3454 = 1;
                    unk2c8 = 0xc;
                    break;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x28;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].unk80 == 3) {
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x79;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x25) {
                        if (unk3148[v4] < 6) {
                            m_objects[v4].frame = 4;
                            unk3148[v4]++;
                        } else {
                            m_objects[v4].vx = 0.0;
                            m_objects[v4].frame = 0x28;
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                        if ((*m_opponent)->pattern == 0x79) {
                            (*m_opponent)->Vf0();
                            (*m_opponent)->Unk40f1e0();
                            (*m_opponent)->y = -480.0;
                            (*m_opponent)->x = x;
                            (*m_opponent)->pattern = 0x3b;
                        }
                    }
                }
                if (unk3454 == 1 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].frame = 0x25;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                break;
            case 0x1a4:
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.35;
                    m_objects[v4].vy = 0.35;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].unk80 == 3 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x25;
                    m_objects[v4].vx = 0.0;
                    unk2c8 = 0xc;
                    break;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].frame < 0x25) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x28;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].unk80 == 3) {
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x79;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x25) {
                        if (unk3148[v4] < 6) {
                            m_objects[v4].frame = 4;
                            unk3148[v4]++;
                        } else {
                            m_objects[v4].vx = 0.0;
                            m_objects[v4].frame = 0x28;
                        }
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                        if ((*m_opponent)->pattern == 0x79) {
                            (*m_opponent)->Vf0();
                            (*m_opponent)->Unk40f1e0();
                            (*m_opponent)->y = -480.0;
                            (*m_opponent)->x = x;
                            (*m_opponent)->pattern = 0x3b;
                        }
                    }
                }
                break;
            case 0x1b5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    if (unk3148[v4] == 0) {
                        m_objects[v4].vy = -1.1;
                        m_objects[v4].vx = 0.3;
                        unk3148[v4]++;
                    }
                }
                if (frame == 1 && unk3138 == 0x1e) {
                    Vf10(v4);
                }
                m_objects[v4].vx -= 0.002;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    if (unk3148[v4] == 0) {
                        m_objects[v4].vy = -1.1;
                        m_objects[v4].vx = 0.3;
                        unk3148[v4]++;
                    }
                }
                if (frame == 1 && unk3138 == 0x1e) {
                    Vf10(v4);
                }
                m_objects[v4].vx -= 0.002;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    if (unk3148[v4] == 0) {
                        m_objects[v4].vy = -1.1;
                        m_objects[v4].vx = 0.3;
                        unk3148[v4]++;
                    }
                }
                if (frame == 1 && unk3138 == 0x1e) {
                    Vf10(v4);
                }
                m_objects[v4].vx -= 0.002;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    if (unk3148[v4] == 0) {
                        m_objects[v4].vy = -1.1;
                        m_objects[v4].vx = 0.3;
                        unk3148[v4]++;
                    }
                }
                if (frame == 1 && unk3138 == 0x1e) {
                    Vf10(v4);
                }
                m_objects[v4].vx -= 0.002;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    if (unk3148[v4] == 0) {
                        m_objects[v4].vy = -1.1;
                        m_objects[v4].vx = 0.3;
                        unk3148[v4]++;
                    }
                }
                if (frame == 1 && unk3138 == 0x1e) {
                    Vf10(v4);
                }
                m_objects[v4].vx -= 0.002;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    if (unk3148[v4] == 0) {
                        m_objects[v4].vy = -1.1;
                        m_objects[v4].vx = 0.3;
                        unk3148[v4]++;
                    }
                }
                if (frame == 1 && unk3138 == 0x1e) {
                    Vf10(v4);
                }
                m_objects[v4].vx -= 0.002;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].vx = 2.5;
                }
                if (unk3140 == 1 && unk3348[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3148[v4] = (int)(m_objects[v4].vx * 100.0);
                    unk3248[v4] = (int)(m_objects[v4].vy * 100.0);
                    unk3348[v4] = 1;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (unk3140 == 0 && unk3348[v4] == 1) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = unk3148[v4] * 0.01;
                    m_objects[v4].vy = unk3248[v4] * 0.01;
                    unk3348[v4] = 2;
                }
                if (frame > 1) {
                    Vf10(v4);
                }
                if (unk3140 != 1) {
                    m_objects[v4].vy -= 0.01;
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
            case 0x1ad:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].vx = 2.5;
                }
                if (unk3140 == 1 && unk3348[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3148[v4] = (int)(m_objects[v4].vx * 100.0);
                    unk3248[v4] = (int)(m_objects[v4].vy * 100.0);
                    unk3348[v4] = 1;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (unk3140 == 0 && unk3348[v4] == 1) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = unk3148[v4] * 0.01;
                    m_objects[v4].vy = unk3248[v4] * 0.01;
                    unk3348[v4] = 2;
                }
                if (frame > 1) {
                    Vf10(v4);
                }
                if (unk3140 != 1) {
                    m_objects[v4].vy -= 0.01;
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
            case 0x1ae:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].vx = 2.5;
                }
                if (unk3140 == 1 && unk3348[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3148[v4] = (int)(m_objects[v4].vx * 100.0);
                    unk3248[v4] = (int)(m_objects[v4].vy * 100.0);
                    unk3348[v4] = 1;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (unk3140 == 0 && unk3348[v4] == 1) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = unk3148[v4] * 0.01;
                    m_objects[v4].vy = unk3248[v4] * 0.01;
                    unk3348[v4] = 2;
                }
                if (frame > 1) {
                    Vf10(v4);
                }
                if (unk3140 != 1) {
                    m_objects[v4].vy -= 0.01;
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
            case 0x1af:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].vx = 2.5;
                }
                if (unk3140 == 1 && unk3348[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3148[v4] = (int)(m_objects[v4].vx * 100.0);
                    unk3248[v4] = (int)(m_objects[v4].vy * 100.0);
                    unk3348[v4] = 1;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (unk3140 == 0 && unk3348[v4] == 1) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = unk3148[v4] * 0.01;
                    m_objects[v4].vy = unk3248[v4] * 0.01;
                    unk3348[v4] = 2;
                }
                if (frame > 1) {
                    Vf10(v4);
                }
                if (unk3140 != 1) {
                    m_objects[v4].vy -= 0.01;
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
            case 0x1b0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].vx = 2.5;
                }
                if (unk3140 == 1 && unk3348[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3148[v4] = (int)(m_objects[v4].vx * 100.0);
                    unk3248[v4] = (int)(m_objects[v4].vy * 100.0);
                    unk3348[v4] = 1;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (unk3140 == 0 && unk3348[v4] == 1) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = unk3148[v4] * 0.01;
                    m_objects[v4].vy = unk3248[v4] * 0.01;
                    unk3348[v4] = 2;
                }
                if (frame > 1) {
                    Vf10(v4);
                }
                if (unk3140 != 1) {
                    m_objects[v4].vy -= 0.01;
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
            case 0x1b2:
                if (frame == 1) {
                    Vf10(v4);
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].vx = 2.5;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3148[v4] = (int)(m_objects[v4].vx * 100.0);
                    unk3248[v4] = (int)(m_objects[v4].vy * 100.0);
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    (*m_opponent)->pattern = 0x45;
                    (*m_opponent)->y = m_objects[v4].y - 81.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    (*m_opponent)->Vf0();
                    (*m_opponent)->Unk40f1e0();
                    (*m_opponent)->unkc0 = -6.0;
                    (*m_opponent)->unkc8 = 4.0;
                    (*m_opponent)->facing = -m_objects[v4].facing;
                }
                if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                    unk3138--;
                }
                if ((*m_opponent)->y == 0.0 && unk3348[v4] == 0 && m_objects[v4].frame == 2) {
                    CPlayer::Unk4105a0(0x170c, 500.0);
                    unk3348[v4]++;
                    unk2c9 = 0x16;
                }
                if ((*m_opponent)->pattern == 0x63) {
                    (*m_opponent)->timer = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = unk3148[v4] * 0.01;
                    m_objects[v4].vy = unk3248[v4] * 0.01;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == v54 - 0xc && (unkac == 0 || unkac == 1 && (*m_opponent)->unk108 > 0)) {
                    m_game->FlashWhite(9, 3, 0xc);
                }
                if (m_objects[v4].frame != 2) {
                    m_objects[v4].vy -= 0.01;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        unk3140 = 1;
                    }
                    if (m_objects[v4].frame == 4) {
                        unk3140 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                        unk313c = (int)m_objects[v4].x;
                        unk3140 = (int)(m_objects[v4].y - 130.0);
                    }
                }
                break;
            case 0x1b7:
                if (pattern == 0x132 || pattern == 0x133 || pattern == 0x134) {
                    if (frame == 0x1c) {
                        m_objects[v4].frame = 2;
                    }
                    if (frame != 0x1c && m_objects[v4].frame == 2) {
                        m_objects[v4].frame = 1;
                    }
                }
                if ((pattern < 0x132 || pattern > 0x134) && m_objects[v4].frame < 4) {
                    m_objects[v4].frame = 4;
                    m_objects[v4].timer = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b8:
                if (pattern < 0x132 || pattern > 0x134) {
                    unk3448 = 0;
                }
                if (m_objects[v4].frame == 9) {
                    (*m_opponent)->frame = 1;
                }
                if (m_objects[v4].frame == 0xa) {
                    (*m_opponent)->frame = 2;
                }
                if (m_objects[v4].frame == 0xc) {
                    (*m_opponent)->frame = 3;
                }
                if (m_objects[v4].frame == 0xd) {
                    (*m_opponent)->frame = 4;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vy = 1.5;
                    unk2c8 = 5;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].unk80 == 3 && (*m_opponent)->unk108 > 0) {
                        m_objects[v4].unk51 = 0;
                        unk3448 = 1;
                        m_objects[v4].unk86 = 0x3c;
                        (*m_opponent)->unk14a = 0x3c;
                        m_objects[v4].unk80 = 0;
                        break;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].frame = 1;
                        m_objects[v4].timer = 0;
                    }
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = -0.8;
                }
                if (m_objects[v4].frame == 2 || m_objects[v4].frame == 3) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].frame = 4;
                        m_objects[v4].timer = 0;
                    }
                }
                if (pattern == 0x132 || pattern == 0x133 || pattern == 0x134) {
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                        m_objects[v4].x = 420.0;
                        m_objects[v4].frame = 7;
                        m_objects[v4].timer = 0;
                        m_objects[v4].facing = facing;
                    }
                    if (m_objects[v4].frame == 7 && unk344c == 1) {
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (m_objects[v4].frame == 0xa && unk344c == 1) {
                        m_objects[v4].frame = 0xb;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (m_objects[v4].frame == 0xd && unk344c == 1) {
                        m_objects[v4].frame = 0xe;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (unk344c == 1 && (m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xe)) {
                        m_objects[v4].unk86 = 0x1e;
                        (*m_opponent)->unk14a = 0x1e;
                        unk344c = 0;
                        if (m_objects[v4].frame == 0xe) {
                            unk2c8 = 9;
                        }
                    }
                    if ((m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb) && m_objects[v4].timer == 0xd2 || m_objects[v4].frame == 0xe && m_objects[v4].timer == 0x294) {
                        if ((WORD)CPlayer::Unk4108a0(0, 9) < 5) {
                            unk2c8 = 6;
                            unk3448 = 3;
                            m_objects[v4].timer++;
                            break;
                        }
                        unk2c8 = 7;
                        unk3448 = 4;
                    }
                    if ((m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb) && m_objects[v4].timer == 0x14a || m_objects[v4].frame == 0xe && m_objects[v4].timer == 0x30c) {
                        if (unk3448 == 4) {
                            l50.type = 0;
                            l50.x = (double)(int)(*m_opponent)->x;
                            l50.y = -80.0;
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk2c = 0x16;
                            m_game->CreateEffect((EffectDesc*)&l50);
                            unk3448 = 5;
                            m_objects[v4].unk51 = 1;
                            (*m_opponent)->pattern = 0x47;
                            (*m_opponent)->Vf0();
                            (*m_opponent)->unkc8 = -13.0;
                            (*m_opponent)->unkc0 = 0.0;
                            if (m_objects[v4].frame == 8) {
                                CPlayer::Unk4105a0(0x708, 50.0);
                                m_objects[v4].frame = 0xf;
                            }
                            if (m_objects[v4].frame == 0xb) {
                                CPlayer::Unk4105a0(0xdac, 50.0);
                                m_objects[v4].frame = 0x12;
                            }
                            if (m_objects[v4].frame == 0xe) {
                                CPlayer::Unk4105a0(0x1964, 50.0);
                                m_objects[v4].frame = 0x15;
                            }
                            m_objects[v4].timer = 0;
                            unk313c = 0xb;
                        }
                        if (unk3448 == 3 && (pattern == 0x132 || pattern == 0x133 && unk3138 == 1 || pattern == 0x134 && unk3138 == 2)) {
                            m_objects[v4].unk50 = 1;
                            (*m_opponent)->pattern = 0x3b;
                            (*m_opponent)->Vf0();
                            (*m_opponent)->unkc8 = -2.0;
                            (*m_opponent)->unkc0 = 0.0;
                        }
                    }
                    if (((m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb) && m_objects[v4].timer == 0x159 || m_objects[v4].frame == 0xe && m_objects[v4].timer == 0x31b) && m_objects[v4].unk50 == 1) {
                        Vf10(v4);
                        break;
                    }
                    if ((pattern == 0x133 || pattern == 0x134) && frame == 0x1c && timer == 0) {
                        unk2c8 = 8;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame++;
                    }
                }
                m_objects[v4].timer++;
                if ((m_objects[v4].frame == 0x11 || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x17) && m_objects[v4].timer == v54 - 0xf) {
                    m_objects[v4].unk50 = 1;
                }
                if ((m_objects[v4].frame == 0x11 || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x17) && m_objects[v4].timer == v54) {
                    Vf10(v4);
                    unk3448 = 5;
                    break;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].unk50 = 1;
                    }
                    if (m_objects[v4].frame == 7) {
                        Vf10(v4);
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
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
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ba:
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
            case 0x1bb:
                m_objects[v4].x = x - facing * 7;
                m_objects[v4].y = y - 41.0;
                if (pattern != 0xcf) {
                    Vf10(v4);
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
            case 0x1bc:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1bd:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1be:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1bf:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1c0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(-35.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1c1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(-60.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1c2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(-60.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1c3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    (&m_objects[v4])->SetVelocity(-85.0, 3.6);
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = -0.9;
                    m_objects[v4].vy = -2.7;
                    break;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].vy += 0.045;
                }
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = -0.5 * m_objects[v4].vy;
                    if (m_objects[v4].unk50 == 0) {
                        m_objects[v4].unk50 = 1;
                    } else {
                        Vf10(v4);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0 || m_objects[v4].y < -510.0) {
                    Vf10(v4);
                }
                break;
            case 0x1c4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 4;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0 && frame < 0xc && unk3148[v4] == 2) {
                    l50.type = 0x1c4;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3c);
                    l50.y = m_objects[v4].y;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5 && unk3148[v4] < 4) {
                        unk3148[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].x > 370.0) {
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x14);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    Vf10(v4);
                    unk344c = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1c6:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].x > 370.0) {
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x14);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    Vf10(v4);
                    unk344c = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1c7:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    (&m_objects[v4])->SetVelocity(0.0, 3.6);
                }
                if (m_objects[v4].x > 370.0) {
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x14);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk2c = 2;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    Vf10(v4);
                    unk344c = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1c8:
                m_objects[v4].facing = *(char*)&unk3450;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -2.3;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].frame == 1 && (*m_opponent)->pattern == 0x71) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 3;
                    m_objects[v4].timer = 0;
                }
                if (m_objects[v4].frame > 2 && m_objects[v4].frame < 6 && unk3148[v4] == 0) {
                    m_objects[v4].vx = 2.1;
                    if ((*m_opponent)->pattern == 0x40) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 6;
                        m_objects[v4].timer = 0;
                    }
                }
                if (m_objects[v4].frame > 7) {
                    m_objects[v4].vx = 3.1;
                }
                if ((m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0) && m_objects[v4].frame > 7) {
                    Vf10(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                }
                break;
            case 0x1c9:
                unk3450 = m_objects[v4].facing;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -2.3;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].frame == 1 && (*m_opponent)->y - m_objects[v4].y > 0.0) {
                    l50.type = 0;
                    l50.x = (double)((int)x + facing * 0x25);
                    l50.y = (double)((int)y - 0x2a);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk2c9 = 0x1a;
                    (*m_opponent)->pattern = 0x71;
                    (*m_opponent)->timer = 0;
                    (*m_opponent)->frame = 0;
                    (*m_opponent)->Unk40f1e0();
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                }
                if (m_objects[v4].frame == 2) {
                    (*m_opponent)->y = m_objects[v4].y - 50.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 3;
                        m_objects[v4].timer = 0;
                        m_objects[v4].facing = 1;
                        unk3450 = 1;
                        if (m_objects[v4].x > 320.0) {
                            m_objects[v4].facing = -1;
                            unk3450 = -1;
                        }
                    }
                }
                if (m_objects[v4].frame > 2 && m_objects[v4].frame < 6 && unk3148[v4] == 0) {
                    m_objects[v4].vx = 2.1;
                    (*m_opponent)->y = m_objects[v4].y - 50.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    if (m_objects[v4].x - x > 160.0 || m_objects[v4].x - x < -160.0) {
                        m_objects[v4].frame = 6;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        (*m_opponent)->frame = 0;
                        (*m_opponent)->timer = 0;
                        (*m_opponent)->facing = -m_objects[v4].facing;
                        (*m_opponent)->unkc0 = -2.1;
                        (*m_opponent)->unkc8 = -1.5;
                        (*m_opponent)->pattern = 0x40;
                        CPlayer::Unk4105a0(0x4b0, 750.0);
                    }
                }
                if (m_objects[v4].frame > 7) {
                    m_objects[v4].vx = 3.1;
                }
                if ((m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0) && m_objects[v4].frame > 7) {
                    Vf10(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                }
                break;
            case 0x1ca:
                m_objects[v4].facing = *(char*)&unk3450;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                    m_objects[v4].vy = -2.3;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].frame == 1 && (*m_opponent)->pattern == 0x71) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].vy + m_objects[v4].y > 0.0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 3;
                    m_objects[v4].timer = 0;
                }
                if (m_objects[v4].frame > 2 && m_objects[v4].frame < 6 && unk3148[v4] == 0) {
                    m_objects[v4].vx = 2.1;
                    if ((*m_opponent)->pattern == 0x40) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].frame = 6;
                        m_objects[v4].timer = 0;
                    }
                }
                if (m_objects[v4].frame > 7) {
                    m_objects[v4].vx = 3.1;
                }
                if ((m_objects[v4].x < -30.0 || m_objects[v4].x > 670.0) && m_objects[v4].frame > 7) {
                    Vf10(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 3;
                    }
                }
                break;
            case 0x1cb:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 0x63;
                    unk2c8 = 0xd;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1cc:
                m_objects[v4].x = facing * 0x38 + x;
                m_objects[v4].y = y - 44.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 4 && pattern == 0xd2 && frame < 9) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
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
