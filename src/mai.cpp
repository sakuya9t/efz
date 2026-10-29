// CMai (0x6163b0-0x62a5df): the character class whose files are in mai\ in the game
// folder (mai.dat sprites, mai.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMai::CMai(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "mai");
    lastSurface = 0x3a0;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk2ad0[0] = -0x14;
    unk2af8[0] = -0x3a;
    unk2ad0[1] = -0x18;
    unk2af8[1] = 0;
    unk2ad0[2] = 4;
    unk2af8[2] = -8;
    unk2ad0[3] = 7;
    unk2af8[3] = -0xc;
    unk2ad0[4] = 0x1e;
    unk2af8[4] = -0x16;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    unk30f4 = 3;
    unk30f5[0] = 0;
    unk30f5[1] = 1;
    unk30f5[2] = 9;
    unk30f5[3] = 2;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3158[v4] = 0;
        unk3258[v4] = 0;
        unk3358[v4] = 0;
    }
}

void CMai::Vf12()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk2ad0[0] = -0x17;
    unk2af8[0] = -0x3a;
    unk2ad0[1] = -0x18;
    unk2af8[1] = 0;
    unk2ad0[2] = 4;
    unk2af8[2] = -8;
    unk2ad0[3] = 7;
    unk2af8[3] = -0xc;
    unk2ad0[4] = 0x1e;
    unk2af8[4] = -0x16;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk3154 = 0;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3158[v4] = 0;
        unk3258[v4] = 0;
        unk3358[v4] = 0;
    }
    CPlayer::Vf12();
}

void CMai::Vf0()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::Vf0();
}

void CMai::Vf10(short p1)
{
    unk3158[p1] = 0;
    unk3258[p1] = 0;
    unk3358[p1] = 0;
    CPlayer::Vf10(p1);
}

void CMai::Vf3()
{
    CPlayer::Unk40e740();
}

void CMai::Vf4()
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
        if (unk3148 > 0 && unk108 < 0xd05 && unk262 == 0x67 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 4 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x144].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x144;
            return;
        }
        if (unk108 < 0xd05 && unk262 == 0x67 && unk148 >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if (unk262 == 0x70 && unk148 >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (unk3144 == 0 || unk3144 == 1) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x142].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x142;
            if (unk3144 == 1) {
                pattern = 0x143;
            }
            return;
        }
        if ((unk262 == 0x6f || unk262 == 0x70) && unk148 >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (unk3144 == 0 || unk3144 == 1) && m_patterns[pattern].unk2 <= m_patterns[0x140].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x140;
            if (unk3144 == 1) {
                pattern = 0x141;
            }
            return;
        }
        if ((unk262 == 0x6e || unk262 == 0x6f || unk262 == 0x70) && unk148 >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (unk3144 == 0 || unk3144 == 1) && m_patterns[pattern].unk2 <= m_patterns[0x13e].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13e;
            if (unk3144 == 1) {
                pattern = 0x13f;
            }
            return;
        }
        if (unk262 == 0x66 && unk148 >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if ((unk262 == 0x65 || unk262 == 0x66) && unk148 >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x130;
            return;
        }
        if ((unk262 == 0x64 || unk262 == 0x65 || unk262 == 0x66) && unk148 >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if (unk262 == 0x16 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x10c].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10c;
            return;
        }
        if ((unk262 == 0x15 || unk262 == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x10b].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10b;
            return;
        }
        if (unk262 == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x10a].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10a;
            return;
        }
        if (unk262 == 0x16 && (unk118 >= 500.0 || unk120 > 0 || unk3144 == 4) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            return;
        }
        if ((unk262 == 0x15 || unk262 == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            return;
        }
        if (unk262 == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            return;
        }
        if (unk262 == 0x20 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (unk3144 == 0 || unk3144 == 4) && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x103].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x103;
            return;
        }
        if ((unk262 == 0x1f || unk262 == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (unk3144 == 0 || unk3144 == 4) && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x102].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x102;
            return;
        }
        if (unk262 == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (unk3144 == 0 || unk3144 == 4) && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x101].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x101;
            return;
        }
        if (unk262 == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x109].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x109;
            return;
        }
        if ((unk262 == 0xc || unk262 == 0xb) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x108].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x108;
            return;
        }
        if (unk262 == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x107].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x107;
            return;
        }
        if (unk262 == 0x2a && (unk3144 == 4 || unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0x100].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if ((unk262 == 0x29 || unk262 == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0xff].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if (unk262 == 0x28 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0 || pattern == 0xd4) && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            return;
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
    if (unk15c < 1 && (unk262 == 0 || unk262 == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (unk262 << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (unk262 << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -30.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
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
    if (m_pressA == 1 || (unk1a8 & 0x10) != 0 || (unk1a9 & 0x10) != 0) {
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
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (unk3144 == 4 && m_patterns[pattern].unk2 <= m_patterns[0xd5].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd5;
                return;
            }
            if (pattern != 0xd4 && m_patterns[pattern].unk2 <= m_patterns[0xd2].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd2;
                if (unk3144 == 4) {
                    pattern = 0xd5;
                }
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xc8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xc8;
                return;
            }
        }
    }
    if (m_pressB == 1 || (unk1a8 & 0x20) != 0 || (unk1a9 & 0x20) != 0) {
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
            if (unk3144 == 4 && m_patterns[pattern].unk2 <= m_patterns[0xd6].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd6;
                return;
            }
            if (pattern != 0xd4 && m_patterns[pattern].unk2 <= m_patterns[0xd3].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd3;
                if (unk3144 == 4) {
                    pattern = 0xd6;
                }
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
        if (y < -10.0 && pattern == 0xa3) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xe8;
            return;
        }
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf0].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xf0;
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
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xd8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8) && m_inputX == facing) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xd8;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xdc;
                return;
            }
            if (unk3144 == 4 && m_patterns[pattern].unk2 <= m_patterns[0xd7].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd7;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd4].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd4;
                if (unk3144 == 4) {
                    pattern = 0xd7;
                }
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == -facing && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd8;
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
    if (unk15c < 2 && m_inputY == 0 && m_pressD == 1) {
        if (m_patterns[pattern].unk2 <= m_patterns[0x104].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 0 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x104;
            if (m_inputX == facing) {
                unk3140 = 1;
            }
            if (m_inputX == -facing) {
                unk3140 = 2;
            }
            return;
        }
        if (unk262 == 0x63 && m_patterns[pattern].unk2 <= m_patterns[0x10d].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk3144 == 1 && y == 0.0 && (pattern >= 0xc8 && unk168 >= 2 && unk168 != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10d;
        }
    }
}

void CMai::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (unk3148 > 0 && unk3144 != 3) {
        x1c = *anims[0x29].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3144 == 3) {
        x1c = *anims[0x2a].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3148 > 0 && unk3144 != 3) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width * unk3148 / 0x2710, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3148 * x1c.width / 0x2710, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3148 * x1c.width / 0x2710, 0x1f - x1c.y, unk3148 * x1c.width / 0x2710, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3144 == 3) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, unk3148 * x1c.width / 0x4b0, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3148 * x1c.width / 0x4b0, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3148 * x1c.width / 0x4b0, 0x1f - x1c.y, unk3148 * x1c.width / 0x4b0, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CMai::Vf8()
{
    EffectDesc v48;
    CPlayer::Unk413090((EffectDesc*)&v48);
    if (unk3148 > 0) {
        unk3148--;
        if (unk3144 == 3) {
            unk3148--;
        }
        if (unk3150 == 1) {
            unk3148 -= 4;
        }
        if (unk3150 == 2) {
            unk3148++;
        }
        if (unk3150 == 3) {
            unk3148--;
        }
        if (unk3150 == 4) {
            unk3148--;
        }
    }
    if (unk3144 == 4) {
        unk148 = 0;
        m_game->Unk4080c0(3);
    }
    if (unk3148 <= 0) {
        if (unk3144 == 3) {
            v48.type = 1;
            v48.unk2c = 0xb;
            v48.x = (double)(int)x;
            v48.y = (double)(int)(y - 40.0);
            v48.unk20 = 2;
            v48.unk21 = 1;
            m_game->CreateEffect((EffectDesc*)&v48);
            unk3144 = 0;
            unk3148 = 0;
            unk314c = 0;
            unk3150 = 0;
        }
        if (unk3144 == 4 && pattern != 0x144 && pattern != 0x145) {
            unk3148 = 0x4b0;
            unk3144 = 3;
            unk314c = 0;
            unk3150 = 2;
        }
    }
}

void CMai::Vf9(EffectDesc* p1)
{
    Vf10(unk2ca);
    CPlayer::Vf9(p1);
}

void CMai::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    unk262 = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
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
        if ((v5 & 0xf) == 4 && x6 == 0 && unk148 >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
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

void CMai::Vf5()
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
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->unk16c == 0) {
            if (v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                unk262 = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk148 >= 0x3e8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 120.0) {
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk148 >= 0x3e8) {
                unk262 = 0x6e;
                return;
            }
            if (v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                unk262 = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk148 >= 0x3e8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
        }
        if (v10 < 160.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk148 >= 0x3e8) {
                unk262 = 0x6e;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                unk262 = 0x2a;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                unk262 = 0x20;
                return;
            }
        }
        if (v10 < 220.0 && v10 > 160.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2 && unk148 == 0xbb8) {
                unk262 = 0x66;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2) {
                unk262 = 0x28;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && y == 0.0) {
                m_pressB = 1;
                m_inputX = facing;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 3.0f && y == 0.0) {
                m_pressC = 1;
                m_inputX = facing;
                return;
            }
        }
        if (v10 > 220.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 2) {
            unk262 = 0x28;
            return;
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            unk3114 = 3;
            return;
        }
        if (x8 < 70.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f && unk118 > 500.0) {
            unk262 = 0x16;
            return;
        }
        if (x8 < 60.0 && v10 < 70.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            unk262 = 0x14;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (x8 < 40.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (unk3110 < 3 && unk118 > 500.0 && v10 < 90.0 && (*m_opponent)->y == 0.0) {
            unk262 = 0x48;
            return;
        }
        if (unk3110 < 7 && unk118 > 500.0 && v10 < 70.0) {
            unk262 = 0x20;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && unk148 >= 0x3e8 && v10 < 140.0) {
            unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
            return;
        }
        if (unk3110 < 0x12 && unk3110 > 0x16 && unk148 >= 0x3e8 && v10 < 100.0) {
            unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
            return;
        }
        if (unk3110 < 0x1e) {
            unk3114 = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (unk3110 < 0x1e) {
            unk3114 = 2;
            return;
        }
        if (v10 < 100.0 && unk3110 < 0x16 && unk118 > 500.0) {
            unk262 = 0x16;
            return;
        }
        if (v10 < 100.0 && unk3110 < 0x2a) {
            unk262 = 0x14;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0xfa || pattern == 0xfb || pattern == 0xfc || pattern == 0x100 || pattern == 0x12f || pattern == 0x130 || pattern == 0x131)) {
        unk262 = 0x34;
        return;
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1.0f * unka8 && unk168 == 3 && (pattern == 0x100 || pattern == 0xd4 && v10 < 60.0)) {
        unk262 = 0x34;
        return;
    }
    if ((pattern == 0xfe || pattern == 0xff) && unk3144 == 0 && unk314c == 1 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * unka8) {
        m_pressD = 1;
        m_inputX = facing;
        return;
    }
    if (pattern == 0x60 && v10 < 120.0 && unk3144 == 0 && unk314c == 1 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * unka8) {
        m_pressD = 1;
        m_inputX = facing;
        return;
    }
    if ((*m_opponent)->pattern > 0x3a && (*m_opponent)->pattern < 0x9d && unk314c == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * unka8) {
        m_pressD = 1;
        m_inputX = 0;
        m_inputY = 0;
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
        unk262 = facing == 1;
        if (pattern == 0xa3) {
            unk3114 = 0;
        }
        return;
    }
    if (unk3114 == 6) {
        if (y == 0.0) {
            m_inputY = -1;
            m_inputX = facing;
        }
        if (y < 0.0) {
            unk262 = 0x14;
        }
        if (pattern == 0xfa) {
            unk3114 = 0;
            if (unk3144 == 0 && unk314c == 1) {
                m_pressD = 1;
                m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
            }
        }
        return;
    }
    if (unk168 > 1 && unk14a == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < unka8 * 25.0f && unk3114 != 1 && unk3114 != 2) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 160.0 && unk3110 < 0xa) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 125.0 && unk3110 > 0x64 && unk3110 < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1b8) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x384 - (unk3144 == 0 && unk314c == 0) * 0xc8) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb - (unk3144 == 0 && unk314c == 1) * 0x12c) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xc8 && unk168 == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (v10 < 50.0 && unk168 == 2 && unk3110 < 0x96 && (WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                unk3114 = 6;
                m_inputY = 0;
                m_pressA = 0;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xc8 && unk3110 < 0x1f4) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x82 && unk314c == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x82 && unk3110 < 0x190 && v10 < 140.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1cc && v10 < 140.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x23a - (unk314c == 1) * 0x96 && unk3110 < 0x2a8) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (unk168 == 3 && unk118 > 500.0) {
                    unk262 = 0x2a;
                }
                return;
            }
            if (unk3110 > 0x1cc && unk3110 < 0x230 && (*m_opponent)->y == 0.0 && v10 < 100.0 && unk314c == 0) {
                unk262 = 0x1e;
                return;
            }
            if (unk3110 > 0x384 - (unk3144 == 0 && unk314c == 0) * 0xc8) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
                return;
            }
            if (unk3110 > 0x2bc - (unk3144 == 0 && unk314c == 0) * 0xc8) {
                unk3114 = 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && v10 < 90.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12c && unk3110 < 0x1f4 && v10 > 150.0) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x1f4 && unk3110 < 0x258 && unk314c == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (unk3110 < 0x64 && v10 < 110.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x12c && unk3110 < 0x1c2 && (*m_opponent)->y == 0.0) {
                unk262 = 0x1e;
                if (v10 > 120.0) {
                    unk262 = 0x1f;
                }
                return;
            }
            if (unk3110 > 0x23a && unk3110 < 0x26c) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 1) + 0x28;
                if (unk168 == 3 && unk118 > 500.0) {
                    unk262 = 0x2a;
                }
                return;
            }
            if (unk3110 > 0x384 - (unk3144 == 0 && unk314c == 0) * 0xc8) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == 0xcb) {
            if (unk3110 > 0xc8 && unk3110 < 0x1f4 && unk314c == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x12c && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputX = facing;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x1f4 && unk3110 < 0x226 && (*m_opponent)->y == 0.0) {
                unk262 = 0x1e;
                if (v10 > 120.0) {
                    unk262 = 0x1f;
                }
                return;
            }
            if (unk3110 > 0x28a && unk3110 < 0x2bc) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 1) + 0x28;
                if (unk168 == 3 && unk118 > 500.0) {
                    unk262 = 0x2a;
                }
                return;
            }
            if (unk3110 > 0x28a && unk3110 < 0x2bc) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (unk168 == 3 && unk118 > 500.0) {
                    unk262 = 0x2a;
                }
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && v10 < 50.0) {
                m_pressA = 1;
                m_inputY = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    unk3114 = 6;
                    m_inputY = 0;
                    m_pressA = 0;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && unk3110 < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x384 - (unk3144 == 0 && unk314c == 0) * 0x64) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
                return;
            }
            if (unk3110 > 0x320) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xcd) {
            if (unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 < 0x190 && v10 > 140.0 && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 < 0x190 && unk3110 < 0x1f4 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x226 - (unk314c == 1) * 0x96 && unk3110 < 0x2bc) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (unk168 == 3 && unk118 > 500.0) {
                    unk262 = 0x2a;
                }
                return;
            }
            if (unk3110 > 0x384 - (unk3144 == 0 && unk314c == 0) * 0xc8 && unk168 == 3) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x384 - (unk3144 == 0 && unk314c == 0) * 0xc8) {
                unk3114 = 1;
                if (unk3144 == 0 && unk314c == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * facing;
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (unk3110 > 0xc8 && unk3110 < 0x1f4 && unk314c == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x12c) {
                unk262 = 0x1f;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x190 && unk118 > 500.0) {
                unk262 = 0x34;
                return;
            }
            if (unk3110 > 0x226 - (unk314c == 1) * 0x96 && unk3110 < 0x2bc) {
                unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (unk168 == 3 && unk118 > 500.0) {
                    unk262 = 0x2a;
                }
                return;
            }
            if (unk3110 > 0x2bc) {
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
            if (unk3110 > 0x2bb - (unk3144 == 0 && unk314c == 1) * 0x12c) {
                unk3114 = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    unk3114 = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
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
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * unka8) {
        unk3110 = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && unk3110 < 3) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 60.0 && (*m_opponent)->pattern < 0x32 && (*m_opponent)->pattern < 0xa8 && unk3110 < 5) {
                    unk3114 = 6;
                    return;
                }
                if (v10 < 50.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d) * 0x32 + 0x19 && (*m_opponent)->pattern < 0xc8) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 80.0 && unk3110 < 0xa && unk148 >= 0x3e8 && (*m_opponent)->pattern > 0xc7) {
                    unk262 = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && unk3110 < 0x14) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 130.0 && v10 > 80.0 && unk3110 < 0x1e && unk3110 > 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 90.0 && unk3110 < 0x1e && unk3110 > 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 200.0 && v10 > 160.0 && unk3110 < 0x2d && unk3110 > 0x1e) {
                    m_pressB = 1;
                    if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                        m_pressB = 0;
                        m_pressC = 1;
                    }
                    m_inputY = 0;
                    m_inputX = facing;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 180.0 && x8 > 90.0 && unk3110 < 0x1e) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 > 130.0 && x8 < 180.0 && x8 > 90.0 && unk3110 > 0x1e && unk3110 < 0x46) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 150.0 && v10 > 60.0 && unk3110 > 0x46 && unk3110 < 0x6e) {
                        m_pressA = 1;
                        m_inputX = facing;
                        m_inputY = 0;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 180.0 && x8 > 90.0 && unk3110 < 0x1e) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 > 130.0 && x8 < 180.0 && x8 > 90.0 && unk3110 > 0x1e && unk3110 < 0x46) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 150.0 && v10 > 60.0 && x8 > 130.0 && unk3110 > 0x46 && unk3110 < 0x6e) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 < 100.0 && x8 > 160.0 && x8 < 240.0 && unk3110 > 0 && unk3110 < 0x8c) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 140.0 && v10 > 90.0 && x8 > 90.0 && unk3110 > 0xa0 && unk3110 < 0xdc) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 130.0 && x8 < 80.0 && unk3110 > 0xdc && unk3110 < 0x12c && unk118 > 500.0) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 100.0 && x8 < 100.0) {
                    if (unk3110 < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 < 80.0 && unk3110 > 0xc8 && unk3110 < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 140.0 && v10 > 80.0 && x8 > 40.0 && x8 < 80.0 && unk3110 > 0x104 && unk3110 < 0x109) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 120.0 && x8 < 90.0 && (*m_opponent)->y > y && unk3110 < 0x6e) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 140.0 && x8 < 90.0 && unk3110 < 0xd2) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 100.0 && x8 < 90.0 && (*m_opponent)->y > y && unk3110 < 0x9c4) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < ((unk3144 == 1 && unk314c == 1 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b)) * 2 + (((*m_opponent)->pattern == 0x63) << 2) + 1) * unka8 && v10 > 80.0) {
            unk262 = facing == 1;
            return;
        }
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 60.0 && v10 < 140.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * unka8 && x > 120.0 && x < 520.0 && unk314c == 0) {
        unk262 = -((facing == 1) - 1);
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < (unk314c == 1) + 2) {
        unk3114 = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * unka8) {
            unk3114 = 3;
        } else {
            unk3114 = 0;
        }
        if (v10 > 160.0 && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && y == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2 && (*m_opponent)->pattern < 0xa8) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x3c && v10 < 150.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        } else {
            unk1a0 = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
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

void CMai::Vf7()
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
            case 0x191:
                unk3144 = 1;
                if (m_objects[v4].frame > 2) {
                    if (m_objects[v4].vx >= 0.1) {
                        m_objects[v4].vx -= 0.02;
                    }
                    if (m_objects[v4].vx <= -0.1) {
                        m_objects[v4].vx += 0.02;
                    }
                    if (m_objects[v4].vy >= 0.1) {
                        m_objects[v4].vy -= 0.02;
                    }
                    if (m_objects[v4].vy <= -0.1) {
                        m_objects[v4].vy += 0.02;
                    }
                    if (m_objects[v4].vx < 0.1 && m_objects[v4].vx > -0.1) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].vy < 0.1 && m_objects[v4].vy > -0.1) {
                        m_objects[v4].vy = 0.0;
                    }
                    if (unk3150 == 1) {
                        unk3150 = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        if (m_objects[v4].y > -30.0) {
                            l50.type = 0x1f;
                            l50.x = (double)(int)m_objects[v4].x;
                            l50.y = (double)(int)m_objects[v4].y;
                            l50.unk20 = 0;
                            l50.unk21 = 0;
                            l50.side = m_objects[v4].facing == -1;
                            m_game->CreateEffect((EffectDesc*)&l50);
                        }
                    }
                    if (unk3148 <= 0) {
                        m_objects[v4].pattern = 0x193;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3144 = 2;
                        break;
                    }
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    }
                    if (m_objects[v4].x <= (*m_opponent)->x) {
                        m_objects[v4].facing = 1;
                    }
                    if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                        m_objects[v4].pattern = 0x192;
                        unk3144 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x10d) {
                        m_objects[v4].pattern = 0x194;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        break;
                    }
                    if (pattern == 0x143 && frame == 3 && timer == 0) {
                        m_objects[v4].pattern = 0x1bf;
                        unk3144 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x141 && frame == 3 && timer == 0) {
                        m_objects[v4].pattern = 0x1bb;
                        unk3144 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x13f && frame == 3 && timer == 0) {
                        m_objects[v4].pattern = 0x1b7;
                        unk3144 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if ((pattern < 0x96 || pattern > 0x9c) && pattern != 0xa8 && pattern != 0xa9 && pattern != 0xaa && pattern != 0x104 && pattern != 0x10d) {
                        if (unk262 == 0x21) {
                            m_objects[v4].pattern = 0x1c3;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            unk3144 = 2;
                            break;
                        }
                        if (unk262 == 0x2b) {
                            m_objects[v4].pattern = 0x1b4;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            unk3144 = 2;
                            break;
                        }
                        if (unk262 == 0xd) {
                            m_objects[v4].pattern = 0x1af;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            unk3144 = 2;
                            break;
                        }
                        if (unk262 == 0x35) {
                            m_objects[v4].pattern = 0x19e;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            unk3144 = 2;
                            break;
                        }
                    }
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 3;
                    }
                }
                break;
            case 0x192:
                unk3144 = 2;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = -2.0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].ax = 0.05;
                    unk3158[v4] = 1;
                }
                m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ax;
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 1) {
                    Vf10(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3258[v4] < 5) {
                        unk3258[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        unk314c = 0;
                        unk3148 = 0x4b0;
                        unk3144 = 3;
                        unk3258[v4] = 0;
                        unk3158[v4] = 0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x193:
                unk3144 = 2;
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3148 = 0x4b0;
                        unk3144 = 3;
                        unk3150 = 0;
                        unk314c = 0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x194:
                unk3144 = 2;
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3148 = 0x4b0;
                        unk3144 = 3;
                        unk3150 = 1;
                        Vf10(v4);
                    }
                }
                break;
            case 0x196:
                unk3148--;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].x > 590.0 && m_objects[v4].facing == 1) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 50.0 && m_objects[v4].facing == -1) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    if (unk3148 > 1) {
                        unk3148 -= 0x1388;
                    } else {
                        unk3148 = 0;
                    }
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].ax = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.5;
                    m_objects[v4].ax = -0.015;
                    unk3158[v4] = 6;
                    m_objects[v4].vy = 0.9;
                    m_objects[v4].ay = -0.035;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xb && unk3158[v4] > 0) {
                        m_objects[v4].frame = 7;
                        unk3158[v4]--;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x191;
                        unk3144 = 0;
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x197:
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0 && unk3258[v4] == 0) {
                    unk3148 = 0;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0 && unk3258[v4] != 1) {
                    l50.type = 0x198;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                    l50.y = (double)(int)(m_objects[v4].y - 49.0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                    unk3258[v4] = 1;
                    unk3158[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 8 && unk3158[v4] < 5) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x193;
                        unk3144 = 0;
                        m_objects[v4].frame = 0;
                        unk3258[v4] = 0;
                        unk3158[v4] = 0;
                    }
                }
                break;
            case 0x198:
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0 && unk3158[v4] <= 0) {
                    if (unk3258[v4] == 0) {
                        m_objects[v4].unk84 = 1;
                    }
                    if (unk3258[v4] < 3 && m_objects[v4].unk84 > 0) {
                        unk3358[v4] = (int)((ObjBase*)&pattern)->AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - 50.0 - m_objects[v4].y);
                        (&m_objects[v4])->SetVelocity((double)unk3358[v4], -0.00875);
                        m_objects[v4].ax = m_objects[v4].vx;
                        m_objects[v4].ay = m_objects[v4].vy;
                        (&m_objects[v4])->SetVelocity((double)unk3358[v4], 1.4);
                        if (m_objects[v4].facing == -1) {
                            m_objects[v4].ax = -m_objects[v4].ax;
                            m_objects[v4].vx = -m_objects[v4].vx;
                        }
                        unk3358[v4] = 0xa0;
                        unk3258[v4]++;
                        unk3158[v4] = 0xf0;
                    }
                }
                if (unk3358[v4] > 0) {
                    m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    unk3358[v4]--;
                }
                unk3158[v4]--;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if ((unk3258[v4] > 2 || m_objects[v4].unk84 == 0) && unk3158[v4] <= 0) {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x199:
                unk3144 = 1;
                if (pattern == 0x13d) {
                    m_game->Unk4080c0(0xf);
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk88 = 1;
                    if (pattern == 0x13b) {
                        unk148 = unk148 - 0x3e8;
                    }
                    if (pattern == 0x13c) {
                        unk148 = unk148 - 0x7d0;
                    }
                    if (pattern == 0x13d) {
                        unk148 = unk148 - 0xbb8;
                    }
                    unk3140 = 0;
                    unk3158[v4] = 0;
                    unk14c = 0x78;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 9;
                    l50.unk2c = 5;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 52.0);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk2c9 = 0x25;
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].frame < 0xc && unk14c == 0) {
                    if (unk3358[v4] == 0) {
                        unk2c8 = 6;
                        unk3358[v4]++;
                    }
                    if (unk3258[v4] >= 0xf) {
                        unk3258[v4] = 0;
                        if (pattern == 0x13b && unk3140 < 3) {
                            l50.type = 0x19a;
                            l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                            l50.y = (double)(int)(m_objects[v4].y - 49.0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = m_objects[v4].facing;
                            l50.unk18 = l50.unk18;
                            Vf9(&l50);
                            unk3140++;
                        }
                        if (pattern == 0x13c && unk3140 < 5) {
                            l50.type = 0x1a7;
                            l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                            l50.y = (double)(int)(m_objects[v4].y - 49.0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = m_objects[v4].facing;
                            l50.unk18 = l50.unk18;
                            Vf9(&l50);
                            unk3140++;
                        }
                        if (pattern == 0x13d && unk3140 < 0xa) {
                            l50.type = 0x1a9;
                            l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                            l50.y = (double)(int)(m_objects[v4].y - 49.0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = m_objects[v4].facing;
                            l50.unk18 = l50.unk18;
                            Vf9(&l50);
                            unk3140++;
                        }
                    }
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                unk3258[v4]++;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xc && unk3158[v4] < 5) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x193;
                        unk3144 = 0;
                        m_objects[v4].unk88 = 0;
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x19a:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = unk3140;
                    unk3158[v4]++;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x19b;
                    unk2c9 = 0x12;
                }
                break;
            case 0x19b:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 7;
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
            case 0x19c:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 6;
                    unk3258[v4] = 0xb4;
                }
                if (m_objects[v4].frame > 5) {
                    unk3258[v4] -= 4;
                }
                if (unk3258[v4] < 0xf) {
                    unk3258[v4] = 0xf;
                }
                if (m_objects[v4].frame > 4) {
                    (&m_objects[v4])->SetVelocity(-60.0, unk3258[v4] * 0.01);
                }
                if (m_objects[v4].frame > 8) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 8) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 8 && unk3158[v4] < 8) {
                        unk3158[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk314c = 0;
                        unk3148 = 0x4b0;
                        unk3150 = 1;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x19d:
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 4;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].vx = 0.6;
                    }
                    if (m_objects[v4].frame == 4 && unk3158[v4] < 0x14) {
                        unk3158[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].vy = -0.1;
                        m_objects[v4].vx = 0.0;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3158[v4] < 0xe) {
                            unk3158[v4]++;
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            break;
                        }
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = 0x19e;
                        break;
                    }
                }
                break;
            case 0x19e:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 6;
                    unk3258[v4] = 0xb4;
                }
                if (m_objects[v4].frame > 1) {
                    unk3258[v4] -= 2;
                }
                if (unk3258[v4] < 0x1e) {
                    unk3258[v4] = 0x1e;
                }
                if (m_objects[v4].frame > 0) {
                    (&m_objects[v4])->SetVelocity(-30.0, unk3258[v4] * 0.01);
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 4) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4 && unk3158[v4] < 0xc) {
                        unk3158[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk314c = 0;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x19f:
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
            case 0x1a0:
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
            case 0x1a1:
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
            case 0x1a2:
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
            case 0x1a3:
                if (pattern != 0x134) {
                    if (unk3158[v4] < 9) {
                        m_objects[v4].unk50 = 1;
                        unk3158[v4]++;
                        break;
                    }
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                }
                break;
            case 0x1a4:
                if (pattern != 0x134) {
                    if (unk3158[v4] < 9) {
                        m_objects[v4].unk50 = 1;
                        unk3158[v4]++;
                        break;
                    }
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                }
                break;
            case 0x1a5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.1;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.04;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].unk80 == 1 || m_objects[v4].y >= 0.0) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].unk50 = 1;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a6:
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.8;
                    m_objects[v4].vy = -0.5;
                    m_objects[v4].ay = 0.03;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 50.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a7:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = unk3140;
                    unk3158[v4]++;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    unk2c9 = 0x12;
                }
                break;
            case 0x1a8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 7;
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
            case 0x1a9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = unk3140 - (unk3140 > 5) * 5;
                    unk3158[v4]++;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1aa;
                }
                break;
            case 0x1aa:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 7;
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
            case 0x1ab:
                m_game->Unk4080c0(0xf);
                unk14c = 2;
                CPlayer::Unk410b10(0xb0, 1);
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].vy > -0.1) {
                    m_objects[v4].vy = -0.1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].vy = -1.5;
                        m_objects[v4].vx = 0.0;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3158[v4] < 6) {
                            unk3158[v4]++;
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            break;
                        }
                        unk2c8 = 4;
                        l50.type = 1;
                        l50.unk2c = 0;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)(m_objects[v4].y - 40.0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        m_game->CreateEffect((EffectDesc*)&l50);
                        unk3148 = 0x2710;
                        unk3144 = 4;
                        unk14c = 0x3c;
                        CPlayer::Unk410b10(0xb0, 0x14);
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x1ac:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 4;
                    m_objects[v4].vx = 1.7;
                }
                m_objects[v4].vx -= 0.035;
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x > 600.0 && m_objects[v4].facing == 1) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0 && m_objects[v4].facing == -1) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && unk3158[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 9 && unk3258[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3258[v4]++;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk314c = 0;
                        unk3148 = 0x4b0;
                        unk3150 = 1;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ad:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 4;
                    m_objects[v4].vx = 1.7;
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                if (m_objects[v4].x > 600.0 && m_objects[v4].facing == 1) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0 && m_objects[v4].facing == -1) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && unk3158[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        if (unk3258[v4] < 2) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk3258[v4]++;
                            break;
                        }
                        m_objects[v4].pattern = 0x191;
                        unk3144 = 1;
                        unk3148 = 0x2710;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 3;
                    }
                }
                break;
            case 0x1ae:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 0x10;
                    m_objects[v4].vx = 2.0;
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 0.4) {
                    m_objects[v4].vx = 0.4;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && unk3158[v4] < 7) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        if (unk3258[v4] < 5) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            unk3258[v4]++;
                            break;
                        }
                        m_objects[v4].pattern = 0x191;
                        unk3144 = 1;
                        unk3148 = 0x2710;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 3;
                    }
                }
                break;
            case 0x1af:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 8;
                    m_objects[v4].vx = 1.3;
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && unk3158[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame == 9 && unk3258[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3258[v4]++;
                        break;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b0:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c5;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x3c);
                    l50.y = (double)(int)(m_objects[v4].y - 50.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 5 && unk3158[v4] < 4) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 3;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = 0x191;
                        unk3158[v4] = 0;
                        unk3148 = 0x2710;
                        unk3144 = 1;
                    }
                }
                break;
            case 0x1b1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
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
            case 0x1b3:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 5.25;
                }
                if (m_objects[v4].frame > 3) {
                    m_objects[v4].vx -= 0.4;
                    if (m_objects[v4].vx < 0.2) {
                        m_objects[v4].vx = 0.2;
                    }
                }
                if ((*m_opponent)->x - m_objects[v4].x < 120.0 && m_objects[v4].facing == 1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x - (*m_opponent)->x < 120.0 && m_objects[v4].facing == -1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3150 = 1;
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b4:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c6;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x24);
                    l50.y = (double)(int)(m_objects[v4].y - 60.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && unk3158[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3150 = 1;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 3;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].vx = 0.7;
                    unk3158[v4]++;
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x28) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x28;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x28 && m_objects[v4].unk84 > 1) {
                        m_objects[v4].frame = 0x12;
                        m_objects[v4].unk84--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b6:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx += 0.03;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b8;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b7:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk14c = 0x78;
                    unk148 = unk148 - 0x3e8;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 0x44;
                    l50.unk2c = 0x13;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0x32);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk88 = 0x78;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3258[v4] < 1) {
                        m_objects[v4].frame = 5;
                        unk3258[v4]++;
                    }
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 5;
                    m_objects[v4].vx = 2.8;
                    unk3158[v4]++;
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x15) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x15;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x15) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 4.0;
                    unk3158[v4]++;
                }
                m_objects[v4].vx -= 0.035;
                if (m_objects[v4].vx < 1.0) {
                    m_objects[v4].vx = 1.0;
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0xb) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ba:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx += 0.03;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1bc;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bb:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk14c = 0x78;
                    unk148 = unk148 - 0x7d0;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 0x45;
                    l50.unk2c = 5;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0x32);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk88 = 0x78;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    if (unk3258[v4] == 0) {
                        l50.y = (double)(int)(m_objects[v4].y - 27.0);
                    }
                    if (unk3258[v4] == 1) {
                        l50.y = (double)(int)(m_objects[v4].y - 87.0);
                    }
                    if (unk3258[v4] == 2) {
                        l50.y = (double)(int)(m_objects[v4].y - 27.0);
                    }
                    if (unk3258[v4] == 3) {
                        l50.y = (double)(int)(m_objects[v4].y - 87.0);
                    }
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3258[v4] < 3) {
                        m_objects[v4].frame = 5;
                        unk3258[v4]++;
                    }
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bc:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 7;
                    m_objects[v4].vx = 3.5;
                    unk3158[v4]++;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
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
                break;
            case 0x1bd:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 2;
                    m_objects[v4].vx = 1.3;
                    unk3158[v4]++;
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0xb) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1be:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx += 0.03;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c0;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bf:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk14c = 0x78;
                    unk148 = unk148 - 0xbb8;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 0x46;
                    l50.unk2c = 0x40;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0x32);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk88 = 0x78;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 107.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3258[v4] < 5) {
                        m_objects[v4].frame = 5;
                        unk3258[v4]++;
                    }
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 0xa;
                    m_objects[v4].vx = 4.2;
                    unk3158[v4]++;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
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
                break;
            case 0x1c1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3158[v4] == 0) {
                    m_objects[v4].unk84 = 3;
                    m_objects[v4].vx = 1.9;
                    unk3158[v4]++;
                }
                if (m_objects[v4].unk80 > 0 && m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0xb) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c2:
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
            case 0x1c3:
                unk3144 = 2;
                if (pattern > 0x31 && pattern < 0x96 || m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                }
                if (m_objects[v4].frame > 3) {
                    m_objects[v4].vx -= 0.15;
                    if (m_objects[v4].vx < 0.2) {
                        m_objects[v4].vx = 0.2;
                    }
                }
                if ((*m_opponent)->x - m_objects[v4].x < 120.0 && m_objects[v4].facing == 1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x - (*m_opponent)->x < 120.0 && m_objects[v4].facing == -1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && unk3158[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        unk3158[v4]++;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        unk3144 = 3;
                        unk3150 = 4;
                        unk3148 = 0x4b0;
                        unk3158[v4] = 0;
                        unk3258[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c5:
                if ((pattern > 0x31 && pattern < 0x96 || unk3144 == 3) && m_objects[v4].frame < 0x1e) {
                    m_objects[v4].frame = 0x1e;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 0x12) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c6:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk80 = 0;
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
                    unk3154 = 0;
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
                    m_objects[v4].unk50 = 1;
                }
                if (unk3258[v4] < 0) {
                    Vf10(v4);
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
                    m_objects[v4].unk50 = 1;
                }
                if (unk3258[v4] < 0) {
                    Vf10(v4);
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
