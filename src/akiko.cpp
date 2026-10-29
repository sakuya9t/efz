// CAkiko (0x7219a0-0x73070f): the character class whose files are in akiko\ in the game
// folder (akiko.dat sprites, akiko.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CAkiko::CAkiko(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "akiko");
    lastSurface = 0x25b;
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
    unk2ad0[0] = -6;
    unk2af8[0] = -0x48;
    unk2ad0[1] = -0x16;
    unk2af8[1] = 0;
    unk2ad0[2] = 0xc;
    unk2af8[2] = -0xe;
    unk2ad0[3] = 0x16;
    unk2af8[3] = -0x13;
    unk2ad0[4] = 0x1b;
    unk2af8[4] = -0x29;
    unk30f4 = 4;
    unk30f5[0] = 0x10;
    unk30f5[1] = 1;
    unk30f5[2] = 0xa;
    unk30f5[3] = 3;
    unk30f5[4] = 0x17;
    unk30f5[5] = 0x13;
    unk30f5[6] = 0x11;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3164[v4] = 0;
        unk3264[v4] = 0;
        unk3364[v4] = 0;
    }
}

void CAkiko::Vf12()
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
    unk2ad0[0] = -6;
    unk2af8[0] = -0x48;
    unk2ad0[1] = -0x16;
    unk2af8[1] = 0;
    unk2ad0[2] = 0xc;
    unk2af8[2] = -0xe;
    unk2ad0[3] = 0x16;
    unk2af8[3] = -0x13;
    unk2ad0[4] = 0x1b;
    unk2af8[4] = -0x29;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3164[v4] = 0;
        unk3264[v4] = 0;
        unk3364[v4] = 0;
    }
    CPlayer::Vf12();
}

void CAkiko::Vf0()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::Vf0();
}

void CAkiko::Vf10(short p1)
{
    unk3164[p1] = 0;
    unk3264[p1] = 0;
    unk3364[p1] = 0;
    CPlayer::Vf10(p1);
}

void CAkiko::Vf3()
{
    CPlayer::Unk40e740();
}

void CAkiko::Vf4()
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
    if (m_command == 0x34 && (unk118 >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || unk120 > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        Vf0();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x5d && m_gauge >= 0xbb8 && y == 0.0 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x13e].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x13e;
            return;
        }
        if (m_command == 0x7a && m_gauge >= 0xbb8 && unk160 == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x137].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x137;
            return;
        }
        if ((m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x7d0 && unk160 == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x137].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x136;
            return;
        }
        if ((m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && unk160 == 0 && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x133;
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if (m_command == 0x48 && (unk118 >= 500.0 || unk120 > 0) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x10b].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x10b;
            return;
        }
        if ((m_command == 0x47 || m_command == 0x48) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x109].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x109;
            return;
        }
        if (m_command == 0x46 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x107].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x107;
            return;
        }
        if (m_command == 0x16 && y == 0.0 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x101;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x14 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            return;
        }
        if (m_command == 0x20 && (unk118 >= 500.0 || unk120 > 0) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x106].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x106;
            return;
        }
        if ((m_command == 0x1f || m_command == 0x20) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if (m_command == 0x1e && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0x104;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            return;
        }
    }
    if (unk15c < 3 && m_command == 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk15a < 1 && m_patterns[pattern].unk2 <= m_patterns[0xe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < 2) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa5) {
                    Vf0();
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
                    Vf0();
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
                    Vf0();
                }
                pattern = 0xa3;
                CPlayer::FaceOpponent();
                unk158++;
                unk1a8 = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa4].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa4) {
                    Vf0();
                }
                pattern = 0xa4;
                CPlayer::FaceOpponent();
                unk158++;
                unk1a8 = 0;
                return;
            }
        }
    }
    if (m_pressA == 1 || (unk1a8 & 0x10) != 0 || (unk1a9 & 0x10) != 0) {
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xcf].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xcf;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcc].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xcc;
            return;
        }
        if ((m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) && m_patterns[pattern].unk2 <= m_patterns[0xc8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xc8;
            return;
        }
    }
    if (m_pressB == 1 || (unk1a8 & 0x20) != 0 || (unk1a9 & 0x20) != 0) {
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd0].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd0;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -70.0 && x - (*m_opponent)->x < 70.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xc9;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xca].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xca;
                return;
            }
        }
    }
    if (m_pressC == 1 || (unk1a8 & 0x40) != 0 || (unk1a9 & 0x40) != 0) {
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf0].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xf0;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xd1;
            }
            return;
        }
        if ((m_inputY == 1 || (unk1a8 & 4) != 0 || (unk1a9 & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xce].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            pattern = 0xce;
            return;
        }
        if (m_inputY == 0 || (unk1a8 & 4) == 0 || (unk1a9 & 4) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                pattern = 0xcb;
            }
        }
    }
}

void CAkiko::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (unk3148 > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3148 > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, unk3148 * x1c.width / 0x3e8, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3148 * x1c.width / 0x3e8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3148 * x1c.width / 0x3e8, 0x1f - x1c.y, unk3148 * x1c.width / 0x3e8, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk160 > 0) {
        x1c = anims[0x28].frames[unk3154];
        if (unk3160 > 0) {
            x1c = anims[0x28].frames[0xa];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x5c - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0x10d - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        x1c = anims[0x28].frames[unk3158];
        if (unk3160 > 0) {
            x1c = anims[0x28].frames[0xa];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x4a - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0xfb - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        x1c = anims[0x28].frames[unk315c];
        if (unk3160 > 0) {
            x1c = anims[0x28].frames[0xa];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x38 - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0xe9 - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        x1c = *anims[0x29].frames;
        if (unk3160 > 0) {
            x1c = anims[0x29].frames[1];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x24 - x1c.x, 0xb0 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0xd5 - x1c.x, 0xb0 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        if (unk3160 > 0) {
            x1c = *anims[0x2a].frames;
            v2c = MakeRect(0, 0, x1c.width, x1c.height);
            if (m_side == 0) {
                v10 = MakeRect((int)(unk3160 * 0.1) + 0x1f - x1c.x, 0xb9 - x1c.y, x1c.width, x1c.height);
            } else {
                v10 = MakeRect(0xda - (int)(unk3160 * 0.1) - x1c.x, 0xb9 - x1c.y, x1c.width, x1c.height);
            }
            m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        }
    }
}

void CAkiko::Vf8()
{
    if ((m_hp <= 0 || (*m_opponent)->m_hp <= 0) && unk3148 > 0) {
        unk3148 = 0;
        (*m_opponent)->unk15c = 0;
    }
    if ((m_hp <= 0 || (*m_opponent)->m_hp <= 0) && unk160 > 0) {
        if (pattern != 0x13f) {
            m_game->FadeMusic(0, 0x2710);
        }
        unk160 = 0;
        unk3160 = 0;
        unk315c = 0;
        unk3158 = 0;
        unk3154 = 0;
    }
    if (unk3148 > 0) {
        (*m_opponent)->Unk410ac0(0xcb, 3);
        unk3148--;
        if (unk3148 <= 0) {
            (*m_opponent)->unk15c = 0;
        }
    }
    if (unk160 > 0) {
        unk3154 = 4 - unk160 + unk3154;
        if (unk3160 == 0) {
            if (unk3154 > 9) {
                unk3154 -= 0xa;
                unk3158++;
            }
            if (unk3158 > 9) {
                unk3158 -= 0xa;
                unk315c++;
            }
            if (unk315c > 9) {
                unk315c -= 0xa;
                unk3160++;
            }
            m_game->Unk4080c0(3);
            if (unk314c == 2 || unk314c == 4 || unk314c == 6 || unk314c == 8 || unk314c == 0xa || unk314c == 0xc || unk314c == 0xe || unk314c == 0x10 || unk314c == 0x12 || unk314c == 0x14 || unk314c == 0x16 || unk314c == 0x18 || unk314c == 0x1a || unk314c == 0x1c || unk314c == 0x1e || unk314c == 0x20 || unk314c == 0x22 || unk314c == 0x24) {
                if (unk314c >= 0x24) {
                    unk314c = 0;
                    if ((*m_opponent)->unk160 == 0 || (*m_opponent)->unk160 == 4 || (*m_opponent)->unk160 != 0 && m_side == 0) {
                        unk2c8 = 0xf;
                    }
                }
                if ((*m_opponent)->unk160 == 0 || (*m_opponent)->unk160 == 4) {
                    unk14c = 1;
                }
            }
            unk314c++;
        }
        if (unk3160 > 0) {
            if (unk3160 == 1) {
                unk160 = 4;
                if ((*m_opponent)->unk160 == 0 || (*m_opponent)->unk160 == 4) {
                    m_game->FadeMusic(0, 0x2710);
                }
                unk2c8 = 0x12;
            }
            unk3160++;
            if (unk3160 > 0xb4) {
                unk3160 = 0;
                unk315c = 0;
                unk3158 = 0;
                unk3154 = 0;
                unk160 = 0;
            }
        }
        if (pattern > 0x31 && pattern < 0x96) {
            if ((*m_opponent)->unk160 == 0 || (*m_opponent)->unk160 == 4) {
                m_game->FadeMusic(0, 0x2710);
            }
            unk160 = 0;
            unk3160 = 0;
            unk315c = 0;
            unk3158 = 0;
            unk3154 = 0;
        }
    }
}

void CAkiko::Vf9(EffectDesc* p1)
{
    Vf10(unk2ca);
    CPlayer::Vf9(p1);
}

void CAkiko::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 6) {
            m_command = 0x5d;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 5) {
            x6 = 6;
        }
        if (v5 == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 3) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge == 0xbb8 && y == 0.0) {
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
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0 && y == 0.0) {
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

void CAkiko::Vf5()
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
    if ((WORD)CPlayer::Random(0, 0x7d0) < ((unk130 > 0) * 4.0 + 1.0) * 8.0 * unka8 * ((pattern > 0x95 && pattern < 0x9d) * 0x7d0 + 1)) {
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
                m_inputY = 0;
                return;
            }
            if (v10 > 80.0 && v10 < 140.0 && (WORD)CPlayer::Random(0, 0x12c) < unka8 * 3.0f) {
                m_command = 0x15;
                return;
            }
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Random(0, 0x12c) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x14;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x12c) < unka8 * 3.0f + ((unk118 > 500.0) << 1)) {
                m_command = 0x15;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x1f4) < unka8 * 4.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
        if (v10 > 220.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
            return;
        }
        if (v10 > 180.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x46;
            return;
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            unk3114 = 3;
            return;
        }
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 40.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -70.0 && y - (*m_opponent)->y < 70.0 && v10 < 130.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 3) {
            m_command = 0x15;
            return;
        }
        if (unk3110 < 4) {
            m_command = 0x14;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)CPlayer::Random(0, 3) * 0x6e;
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
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0xfa || pattern == 0xfb || pattern == 0x104 || pattern == 0x105 || pattern == 0x106 || pattern == 0x132 || pattern == 0x133 || pattern == 0x134 || pattern == 0x13b || pattern == 0x13c || pattern == 0x13d)) {
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
        unk3114 = 6;
        return;
    }
    if (unk3114 == 6 && pattern == 9) {
        unk3114 = 0;
        m_pressB = 1;
        return;
    }
    if (m_attackResult > 1 && unk14a == 0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 25.0f && unk3114 != 1 && unk3114 != 2) {
        unk3110 = (WORD)CPlayer::Random(0, 0x3e8);
        if (pattern > 0xfc && pattern < 0x103 && unk3110 < 0xfa) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x14;
            return;
        }
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
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
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 5;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x15;
                return;
            }
            if (unk3110 < 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 < 0x15e) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x398) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x1f3) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 5;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x64 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x15;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xc7 && unk3110 < 0x190) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x18f && unk3110 < 0x1f4 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x64;
                return;
            }
            if (unk3110 < (m_attackResult == 3) * 0xc8 + 0xc8) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 < 0x1f4 && m_attackResult == 3 && v10 < 100.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x1f3 && unk3110 < 0x226) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (unk3110 > 0x225 && unk3110 < 0x23a && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if (unk3110 > 0x257 && unk3110 < 0x28a) {
                m_command = 0x46;
                return;
            }
            if (unk3110 > 0x3b6) {
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
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x96 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x15;
                return;
            }
            if (unk3110 > 0 && unk3110 < (m_attackResult == 3) * 0xc8 + 0x64 && (unk118 > 500.0 || m_attackResult == 3)) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0x78) {
                m_command = 0x1e;
                return;
            }
            if (unk3110 > 0x78 && unk3110 < 0x96) {
                m_command = 0x46;
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x190 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x64;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x1cc && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x64;
                return;
            }
            if (unk3110 > 0x1cc && unk3110 < 0x1e0 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x78;
                return;
            }
            if (unk3110 > 0x38e) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x225) {
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
            if (v10 < 60.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
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
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 5;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if (unk3110 < 0x96 && m_attackResult == 3 && v10 < 100.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 < (m_attackResult == 3) * 0xc8 + 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x3b6) {
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
        if (pattern == 0xce) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0x15;
                return;
            }
            if (unk3110 > 0 && unk3110 < (m_attackResult == 3) * 0xc8 + 0x64 && (unk118 > 500.0 || m_attackResult == 3)) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0x96) {
                m_command = 0x1e;
                return;
            }
            if (unk3110 > 0x96 && unk3110 < 0xc8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1f;
                return;
            }
            if (unk3110 > 0x96 && unk3110 < 0xc8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x46;
                return;
            }
            if (unk3110 > 0xc8 && unk3110 < 0xfa && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (v10 < 100.0 && unk3110 > 0xfa && unk3110 < 0x104 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xcf) {
            if (unk3110 < 0x15e) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && unk3110 < 0x1c2) {
                m_pressA = 1;
                return;
            }
            if (v10 < 125.0 && unk3110 > 0x18f && unk3110 < 0x1f4) {
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
            if (unk3110 > 0x3c && unk3110 < 0x64) {
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
        if (pattern == 0xd1 && unk3110 > 0x289) {
            unk3114 = 3;
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
                if (v10 < 45.0 && unk3110 < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 60.0 && unk3110 < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 140.0 && v10 > 100.0 && unk3110 < 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && unk3110 < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 120.0 && v10 > 80.0 && unk3110 < 0x28 && unk3110 > 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 100.0 && v10 > 80.0 && unk3110 < 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 80.0 && unk3110 < 0x2a && unk3110 > 0x28) {
                    m_command = 0x1e;
                    return;
                }
                if (unk3110 < 0x37 && unk3110 > 0x2a) {
                    m_command = facing;
                    unk3114 = 5;
                    return;
                }
                if (v10 > 140.0 && unk3110 < 0x3c && unk3110 > 0x37) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x46;
                    return;
                }
                if (v10 > 120.0 && unk3110 < 0x42 && unk3110 > 0x3c) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                    return;
                }
                if (v10 > 180.0 && m_gauge >= 0xbb8 && unk3110 < 0x44 && unk3110 > 0x42) {
                    m_command = 0xc1;
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
                    if (v10 > 100.0 && v10 < 150.0 && unk3110 < 0xf) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && unk3110 < 0x11 && m_gauge >= 0x7d0) {
                        m_command = (WORD)CPlayer::Random(0, 1) + 0x79;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 40.0 && x8 < 120.0) {
                        if (unk3110 < (unk118 > 500.0 || unk120 > 0) * 5 + 6) {
                            m_command = 0x15;
                            return;
                        }
                    }
                    if (v10 > 100.0 && v10 < 150.0 && (*m_opponent)->y < -60.0 && unk3110 < 0x14) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 50.0 && x8 < 60.0 && unk3110 < 0x11 && m_gauge >= 0x3e8) {
                        m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && unk3114 != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 70.0 && x8 < 100.0) {
                    if (unk3110 < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressB = 1;
                        return;
                    }
                }
                if (v10 < 80.0 && x8 > 60.0 && x8 < 80.0 && vy > 0.0 && (*m_opponent)->y > y && unk3110 > 0xc8 && unk3110 < 0xdc) {
                    m_pressC = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 140.0 && (*m_opponent)->y > y && unk3110 < 0xa) {
                    m_pressC = 1;
                    m_inputY = 1;
                    m_inputX = 0;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 140.0 && x8 > 60.0 && unk3110 < 0xfa) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 120.0 && x8 < 90.0 && (*m_opponent)->y > y && unk3110 < 0x10e) {
                    m_pressC = 1;
                    return;
                }
                if (v10 < 140.0 && x8 > 60.0 && unk3110 < 0x15e) {
                    m_pressA = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 1.0f * unka8) {
        if (v10 < 100.0) {
            m_command = facing == 1;
        }
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
        if (v10 > 240.0 && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 80.0 && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 2) {
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
    if ((WORD)CPlayer::Random(0, 0x64) < 0x28 && v10 < 60.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x50) {
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

void CAkiko::Vf7()
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
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
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
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.05 + 1.25;
                    m_objects[v4].vy = 0.2 - (WORD)CPlayer::Random(0, 8) * 0.05;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].unk80 != 0) {
                    unk2c8 = 1;
                    m_objects[v4].pattern = 0x191;
                    m_objects[v4].unk58 = 0;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    unk3164[v4]--;
                    if (unk3164[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0xa);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        unk3164[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.005;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        unk2c8 = 1;
                        m_objects[v4].pattern = 0x191;
                        m_objects[v4].unk58 = 0;
                        m_objects[v4].unk50 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x193:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 5) * 0.05 + 1.4;
                    m_objects[v4].vy = 1.0 - (WORD)CPlayer::Random(0, 0x14) * 0.1;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].unk80 != 0 || m_objects[v4].y >= 0.0) {
                    unk2c8 = 1;
                    m_objects[v4].pattern = 0x191;
                    m_objects[v4].unk58 = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    unk3164[v4]--;
                    if (unk3164[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0xa);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        unk3164[v4] = 5;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        unk2c8 = 1;
                        m_objects[v4].pattern = 0x191;
                        m_objects[v4].unk58 = 0;
                        m_objects[v4].unk50 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x194:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.05 + 0.0;
                    m_objects[v4].vy = 0.5 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].unk80 != 0) {
                    unk2c8 = 1;
                    m_objects[v4].pattern = 0x191;
                    m_objects[v4].unk58 = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    unk3164[v4]--;
                    if (unk3164[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0xa);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        unk3164[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.015;
                if (m_objects[v4].vy < -0.1) {
                    m_objects[v4].vy += 0.01;
                }
                if (m_objects[v4].vy > 0.1) {
                    m_objects[v4].vy -= 0.01;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        unk2c8 = 1;
                        m_objects[v4].pattern = 0x191;
                        m_objects[v4].unk58 = 0;
                        m_objects[v4].unk50 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x195:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
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
            case 0x196:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.05 + 1.5;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].unk80 != 0) {
                    unk2c8 = 2;
                    m_objects[v4].pattern = 0x195;
                    m_objects[v4].unk58 = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    CPlayer::Unk410a10(3, 3);
                    l50.type = 0x1ae;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.type = 0x1af;
                    Vf9(&l50);
                    Vf9(&l50);
                    l50.type = 0x1b2;
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    l50.unk0 = 1;
                    l50.layer = 1;
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    break;
                }
                if (m_objects[v4].frame == 1) {
                    unk3164[v4]--;
                    if (unk3164[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0x4b);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        unk3164[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.005;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        unk2c8 = 2;
                        m_objects[v4].pattern = 0x195;
                        m_objects[v4].unk58 = 0;
                        m_objects[v4].unk50 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        l50.type = 0x1ae;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.unk0 = 1;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x197:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.05 + 0.0;
                    m_objects[v4].vy = 0.75 - (WORD)CPlayer::Random(0, 0xf) * 0.1;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].unk80 != 0) {
                    unk2c8 = 2;
                    m_objects[v4].pattern = 0x195;
                    m_objects[v4].unk58 = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    unk3164[v4]--;
                    if (unk3164[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0x14);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        unk3164[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.01;
                if (m_objects[v4].vy < -0.1) {
                    m_objects[v4].vy += 0.01;
                }
                if (m_objects[v4].vy > 0.1) {
                    m_objects[v4].vy -= 0.01;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        unk2c8 = 2;
                        m_objects[v4].pattern = 0x195;
                        m_objects[v4].unk58 = 0;
                        m_objects[v4].unk50 = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x198:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].vy += 0.015;
                if (m_objects[v4].frame == 0 && (m_objects[v4].unk80 != 0 || m_objects[v4].y + m_objects[v4].vy >= 0.0)) {
                    unk2c8 = 2;
                    m_objects[v4].pattern = 0x199;
                    m_objects[v4].unk58 = 0;
                    m_objects[v4].unk50 = 2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    l50.type = 0x1ae;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk0 = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    l50.type = 0x1af;
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    Vf9(&l50);
                    CPlayer::Unk410a10(5, 5);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        unk2c8 = 2;
                        m_objects[v4].unk50 = 2;
                        m_objects[v4].unk58 = 0;
                        m_objects[v4].pattern = 0x199;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        l50.type = 0x1ae;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.unk0 = 1;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.unk18 = m_objects[v4].facing;
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        CPlayer::Unk410a10(3, 3);
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x199:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
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
            case 0x19b:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19d:
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 1) {
                    Vf10(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19e:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -2.5;
                }
                m_objects[v4].vy += 0.035;
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 1) {
                    Vf10(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19f:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 5) {
                        l50.type = 0x1a0;
                        l50.unk0 = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 0x32;
                        l50.y = m_objects[v4].y + 15.0;
                        l50.unk18 = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        Vf9(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                    m_objects[v4].unk84 = 0;
                    unk3164[v4]++;
                }
                if (pattern == 0x104 && frame == 0) {
                    Vf10(v4);
                    break;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 45.0 - (WORD)CPlayer::Random(0, 0x5a));
                    l50.y = (double)(int)(m_objects[v4].y + 30.0 - (WORD)CPlayer::Random(0, 0x5a));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                if (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].x - (*m_opponent)->x > -50.0 && (*m_opponent)->y > -50.0) {
                    if (unk3364[v4] <= 0) {
                        (*m_opponent)->unk118--;
                        unk3364[v4] = 1;
                    } else {
                        unk3364[v4]--;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].unk84 = 0;
                        if (unk3264[v4] < 0xf) {
                            m_objects[v4].frame = 0;
                            unk3264[v4]++;
                        } else {
                            Vf10(v4);
                        }
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
                    if (m_objects[v4].frame == 5) {
                        l50.type = 0x1a3;
                        l50.unk0 = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 0x32;
                        l50.y = m_objects[v4].y + 15.0;
                        l50.unk18 = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        Vf9(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                    m_objects[v4].unk84 = 0;
                    unk3164[v4]++;
                    m_objects[v4].vx = 0.3;
                }
                if (pattern == 0x105 && frame == 0) {
                    Vf10(v4);
                    break;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 45.0 - (WORD)CPlayer::Random(0, 0x5a));
                    l50.y = (double)(int)(m_objects[v4].y + 30.0 - (WORD)CPlayer::Random(0, 0x5a));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                if (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].x - (*m_opponent)->x > -50.0 && (*m_opponent)->y > -50.0) {
                    if (unk3364[v4] <= 0) {
                        (*m_opponent)->unk118--;
                        unk3364[v4] = 1;
                    } else {
                        unk3364[v4]--;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].unk84 = 0;
                        if (unk3264[v4] < 0x1e) {
                            m_objects[v4].frame = 0;
                            unk3264[v4]++;
                        } else {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x1a4:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 5) {
                        l50.type = 0x1a5;
                        l50.unk0 = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 0x32;
                        l50.y = m_objects[v4].y + 15.0;
                        l50.unk18 = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        Vf9(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                    m_objects[v4].unk84 = 0xc;
                    unk3164[v4]++;
                    m_objects[v4].vx = 1.8;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 45.0 - (WORD)CPlayer::Random(0, 0x5a));
                    l50.y = (double)-(WORD)CPlayer::Random(0, 0x46);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3264[v4] < 0x1e) {
                            m_objects[v4].frame = 0;
                            unk3264[v4]++;
                            m_objects[v4].unk80 = 0;
                        } else {
                            Vf10(v4);
                        }
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a6:
                m_objects[v4].vx = 5.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                }
                if (pattern != 0x12c) {
                    unk3164[v4] = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                        Vf10(v4);
                        break;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a7:
                m_objects[v4].vx = -3.0;
                (*m_opponent)->facing = -m_objects[v4].facing;
                (*m_opponent)->vx = 3.0;
                if ((char)(*m_opponent)->Unk40ff70() != 0) {
                    (*m_opponent)->Vf0();
                    (*m_opponent)->pattern = 0x3b;
                    (*m_opponent)->facing = m_objects[v4].facing;
                    (*m_opponent)->unkc0 = 0.0;
                    (*m_opponent)->unkc8 = -2.0;
                    (*m_opponent)->ay = 0.035;
                    (*m_opponent)->y = -59.0;
                    (*m_opponent)->unk128 = 1;
                    CPlayer::DealDamage(0x4b0, 500.0);
                    CPlayer::Unk410a10(3, 3);
                    unk2c9 = 2;
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    Vf9(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    Vf9(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    Vf9(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    Vf9(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    Vf9(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    Vf9(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)CPlayer::Random(0, 0x78));
                    Vf9(&l50);
                    Vf10(v4);
                    break;
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
            case 0x1a8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 3.0;
                    (*m_opponent)->facing = -m_objects[v4].facing;
                }
                if (m_objects[v4].frame == 0) {
                    (*m_opponent)->pattern = 0x68;
                    (*m_opponent)->facing = -m_objects[v4].facing;
                    (*m_opponent)->x = m_objects[v4].x + 0.0;
                    (*m_opponent)->y = m_objects[v4].y;
                    (*m_opponent)->unk128 = 1;
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 1;
                        (*m_opponent)->x = m_objects[v4].x;
                        (*m_opponent)->y = m_objects[v4].y;
                        (*m_opponent)->Vf0();
                        (*m_opponent)->pattern = 0x62;
                        (*m_opponent)->facing = m_objects[v4].facing;
                        (*m_opponent)->unk128 = 1;
                        CPlayer::DealDamage(0x4b0, 750.0);
                        CPlayer::Unk410a10(3, 3);
                        unk2c9 = 2;
                        l50.type = 0;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        m_game->CreateEffect((EffectDesc*)&l50);
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].unk50 = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a9:
                m_objects[v4].unk8c = 3;
                m_objects[v4].timer++;
                if (pattern == 0x13f && frame > 1) {
                    Vf10(v4);
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
            case 0x1aa:
                m_objects[v4].unk8c = 3;
                m_objects[v4].timer++;
                if (pattern == 0x13f && frame > 2) {
                    Vf10(v4);
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
            case 0x1ab:
                m_objects[v4].vx = 5.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                }
                if (pattern != 0x12d) {
                    unk3164[v4] = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                        Vf10(v4);
                        break;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ac:
                m_objects[v4].vx = 5.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = 0;
                }
                if (pattern != 0x12e) {
                    unk3164[v4] = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                        Vf10(v4);
                        break;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ad:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = -(WORD)CPlayer::Random(0, 0xb4);
                    unk3264[v4] = (WORD)CPlayer::Random(0, 0x14) + 0x1e;
                    unk3364[v4] = 0;
                }
                (&m_objects[v4])->SetVelocity((double)unk3164[v4], unk3264[v4] * 0.1);
                unk3264[v4]--;
                if (unk3264[v4] <= 5) {
                    unk3264[v4] = 5;
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
            case 0x1ae:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = (WORD)CPlayer::Random(0, 0x168);
                    unk3264[v4] = (WORD)CPlayer::Random(0, 0x28) + 0x32;
                    unk3364[v4] = 0;
                }
                (&m_objects[v4])->SetVelocity((double)unk3164[v4], unk3264[v4] * 0.1);
                unk3264[v4]--;
                if (unk3264[v4] <= 0) {
                    unk3264[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3364[v4] < 6) {
                            unk3364[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x191;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.unk18 = m_objects[v4].facing;
                            Vf9(&l50);
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1af:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = (WORD)CPlayer::Random(0, 0x168);
                    unk3264[v4] = (WORD)CPlayer::Random(0, 0xf) + 0x1e;
                    unk3364[v4] = 0;
                }
                (&m_objects[v4])->SetVelocity((double)unk3164[v4], unk3264[v4] * 0.1);
                unk3264[v4]--;
                if (unk3264[v4] <= 5) {
                    unk3264[v4] = 5;
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
            case 0x1b0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = -(WORD)CPlayer::Random(0, 0xb4);
                    unk3264[v4] = (WORD)CPlayer::Random(0, 0x14) + 0x46;
                    unk3364[v4] = 0;
                }
                (&m_objects[v4])->SetVelocity((double)unk3164[v4], unk3264[v4] * 0.1);
                unk3264[v4]--;
                if (unk3264[v4] <= 0) {
                    unk3264[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3364[v4] < 0xa) {
                            unk3364[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x191;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.unk18 = m_objects[v4].facing;
                            Vf9(&l50);
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = -(WORD)CPlayer::Random(0, 0xb4);
                    unk3264[v4] = (WORD)CPlayer::Random(0, 0x14) + 0x46;
                    unk3364[v4] = 0;
                }
                (&m_objects[v4])->SetVelocity((double)unk3164[v4], unk3264[v4] * 0.1);
                unk3264[v4]--;
                if (unk3264[v4] <= 0) {
                    unk3264[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (unk3364[v4] < 7) {
                            unk3364[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x195;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.unk18 = m_objects[v4].facing;
                            Vf9(&l50);
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk3164[v4] = (WORD)CPlayer::Random(0, 0x168);
                    unk3264[v4] = (WORD)CPlayer::Random(0, 0xf) + 0x1e;
                    unk3364[v4] = 0;
                }
                (&m_objects[v4])->SetVelocity((double)unk3164[v4], unk3264[v4] * 0.1);
                unk3264[v4]--;
                if (unk3264[v4] <= 5) {
                    unk3264[v4] = 5;
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
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - (facing << 2));
                    l50.y = (double)((int)y - 6);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0xe);
                    l50.y = (double)((int)y - 0x1a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x28);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0x19);
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x23);
                    l50.y = (double)((int)y - 0x2a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x12);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + facing * 2);
                    l50.y = (double)((int)y - 0x41);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + (facing << 4));
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                    unk3264[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3164[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3264[v4] < 0xa) {
                    m_objects[v4].unk50 = 1;
                }
                if (unk3264[v4] < 0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3264[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3164[v4] == 0) {
                    unk3264[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3164[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3264[v4] < 0xa) {
                    m_objects[v4].unk50 = 1;
                }
                if (unk3264[v4] < 0) {
                    Vf10(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3264[v4]--;
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
