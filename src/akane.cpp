// CAkane (0x7039d0-0x7124ff): the character class whose files are in akane\ in the game
// folder (akane.dat sprites, akane.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CAkane::CAkane(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "akane");
    lastSurface = 0x26b;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk2ad0[0] = -8;
    unk2af8[0] = -0x35;
    unk2ad0[1] = 0x15;
    unk2af8[1] = 0;
    unk2ad0[2] = 0;
    unk2af8[2] = -5;
    unk2ad0[3] = 2;
    unk2af8[3] = -0xd;
    unk2ad0[4] = 0x1f;
    unk2af8[4] = -0x1d;
    unk30f4 = 4;
    unk30f5[0] = 2;
    unk30f5[1] = 0xb;
    unk30f5[2] = 1;
    unk30f5[3] = 0x12;
    unk30f5[4] = 4;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
}

void CAkane::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk2ad0[0] = -8;
    unk2af8[0] = -0x35;
    unk2ad0[1] = 0x15;
    unk2af8[1] = 0;
    unk2ad0[2] = 0;
    unk2af8[2] = -5;
    unk2ad0[3] = 2;
    unk2af8[3] = -0xd;
    unk2ad0[4] = 0x1f;
    unk2af8[4] = -0x1d;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
    CPlayer::Reset();
}

void CAkane::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CAkane::RemoveObject(short p1)
{
    unk314c[p1] = 0;
    unk324c[p1] = 0;
    unk334c[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CAkane::Move()
{
    CPlayer::Unk40e740();
}

void CAkane::StartCommand()
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
        StartPattern();
        CPlayer::Unk40f170();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && m_command == 0x5a && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_attackResult != 6 && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if (m_command == 0x7a && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x134;
            return;
        }
        if ((m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x133;
            return;
        }
        if ((m_command == 0x78 || m_command == 0x79 || m_command == 0x7a) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x6e && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if (m_command == 0x6f && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x130;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x111].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x111;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x110].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x110;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0x10f].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x10f;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            return;
        }
        if (m_command == 0x20 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x102;
            return;
        }
        if (m_command == 0x1f && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x101;
            return;
        }
        if (m_command == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x2a && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if (m_command == 0x29 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x104;
            return;
        }
        if (m_command == 0x28 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x103;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && unk3144 == 0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk3144 == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
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
                unk158++;
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
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf0].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xf0;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd3].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_inputX == facing && m_inputY != 1 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xd3;
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && (*m_opponent)->y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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

void CAkane::DrawGauge()
{
}

void CAkane::Vf8()
{
}

void CAkane::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CAkane::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 5) {
            m_command = 0x5a;
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
        if ((v5 & 0x10) != 0 && x6 == 0 && m_gauge == 0xbb8 && y == 0.0) {
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && y == 0.0) {
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

void CAkane::CpuInput()
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
            if (v10 < 35.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 50.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
            m_pressB = 1;
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 90.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0x14;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_command = 0xb;
                return;
            }
            if (v10 < 40.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0x7d0) {
                m_command = 0x79;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && v10 < 30.0 && m_gauge == 0xbb8) {
                m_command = 0x5a;
                return;
            }
        }
        if (v10 < 130.0 && v10 > 90.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = 0x16;
                return;
            }
            if (v10 < 110.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_command = 0x2a;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_command = 0xb;
                return;
            }
        }
        if (v10 > 130.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_command = 0x2a;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_command = 0xb;
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
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 90.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            m_inputX = facing;
            return;
        }
        if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
            m_command = 0x2a;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 2 && unk118 > 500.0) {
            m_command = 0x16;
            return;
        }
        if (unk3110 < 5 && unk3110 > 2 && unk118 > 500.0) {
            m_command = 0x14;
            return;
        }
        if (unk3110 < 8 && unk3110 > 5) {
            m_command = 0xa;
            return;
        }
        if (unk3110 < 0xc && unk3110 > 8 && v10 < 50.0) {
            m_command = 0x2a;
            return;
        }
        if (unk3110 < 0x12 && unk3110 > 0x14 && v10 < 30.0 && m_gauge == 0xbb8) {
            m_command = 0x5a;
            return;
        }
        if (unk3110 > 0x41) {
            unk3114 = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 2) {
            m_command = 0x2a;
            return;
        }
        if (unk3110 > 0x41) {
            unk3114 = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0xfd || pattern == 0xfe || pattern == 0xff || pattern == 0x109 && y < -110.0 || pattern == 0x10f || pattern == 0x110 || pattern == 0x111)) {
        m_command = 0x34;
        return;
    }
    if (pattern > 0xff && pattern < 0x106 && (WORD)CPlayer::Random(0, 0x64) > 1e+01f * unka8) {
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
            m_command = (WORD)CPlayer::Random(0, 2) + 0xb;
            return;
        }
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
            if (v10 < 60.0 && unk3110 > 0 && unk3110 < 0x12c) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && unk3110 > 0 && unk3110 < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && unk3110 > 0x190 && unk3110 < 0x2bc) {
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
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12c && unk3110 < 0x226) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
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
            if (unk3110 > 0x64 && unk3110 < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x258) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x258 && unk3110 < 0x2ee && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2ee) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 0xa;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && unk3110 > 0 && unk3110 < 0x12c) {
                m_command = 0xb;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x12c && unk3110 < 0x1f4) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
            }
            if (unk3110 > 0x1f4 && unk3110 < 0x258) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x258) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0xe;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0x10;
                }
                return;
            }
        }
        if (pattern == 0xcb) {
            if (unk3110 > 0 && unk3110 < 0x12c) {
                m_command = 0xb;
                return;
            }
            if (unk3110 > 0x15e && unk3110 < 0x258) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
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
            if (unk3110 > 0x258 && unk3110 < 0x28a) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
                return;
            }
            if (v10 < 70.0 && unk3110 > 0 && unk3110 < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 80.0 && unk3110 > 0xc8 && unk3110 < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x3ca) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x2bc) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xc;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if (unk3110 < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (unk3110 > 0x64 && unk3110 < 0xfa && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xfa && unk3110 < 0x1c2 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (unk3110 > 0x1c2 && unk3110 < 0x226) {
                m_command = 0xb;
                return;
            }
            if (unk3110 > 0x226 && unk3110 < 0x28a) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
                return;
            }
            if (unk3110 > 0x3b6) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x320) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xce) {
            if (unk3110 > 0 && unk3110 < 0x190) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x258) {
                m_command = 0xb;
                return;
            }
            if (unk3110 > 0x320 && unk3110 < 0x352 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
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
            if (unk3110 > 0x50 && unk3110 < 0x12c) {
                m_pressC = 1;
                m_inputX = facing * ((WORD)CPlayer::Random(0, 2) == 0);
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
            if (unk3110 < 0xc8) {
                m_command = 0x2a;
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
        if (pattern == 0xe7 || pattern == 0xe6 || pattern == 0xe8 || pattern == 0xe9 || pattern == 0xea) {
            if (unk3110 < 0x1c2) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x28;
                if ((WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                }
                return;
            }
            if (unk3110 > 0x1c2 && unk3110 < 0x28a) {
                m_command = 0xb;
                return;
            }
            if (unk3110 > 0x2bb) {
                unk3114 = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 6;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    unk3114 = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    unk3114 = 0xa;
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
        if (pattern == 0x109 && unk3110 > 0x258 && y == 0.0) {
            unk3114 = 1;
            if (v10 < 50.0) {
                unk3114 = 0x14;
            }
            return;
        }
        if (pattern == 0xeb && unk3110 > 0x258 && y == 0.0) {
            unk3114 = 1;
            if (v10 < 50.0) {
                unk3114 = 0x14;
            }
            return;
        }
        if (pattern == 0xfb && unk3110 > 0x2bb) {
            if ((WORD)CPlayer::Random(0, 2) == 0) {
                unk3114 = 6;
            }
            if ((WORD)CPlayer::Random(0, 4) == 0) {
                unk3114 = 8;
            }
            if ((WORD)CPlayer::Random(0, 3) == 0) {
                unk3114 = 0xa;
            }
            if ((WORD)CPlayer::Random(0, 4) == 0) {
                unk3114 = 0xc;
            }
            if ((WORD)CPlayer::Random(0, 4) == 0) {
                unk3114 = 0xe;
            }
            if ((WORD)CPlayer::Random(0, 3) == 0) {
                unk3114 = 0x10;
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
                if (v10 < 40.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0x41) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 < 55.0 && unk3110 > 0x5a) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x19 + 0x8c) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 > 80.0 && v10 < 100.0 && unk3110 < 0xa0 && unk3110 > 0x8c) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 100.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x28 + 0xc8 && unk3110 > 0xa0) {
                        unk3114 = 8;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 100.0) {
                    if (unk3110 < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x28 + 0x118 && unk3110 > 0xf0) {
                        unk3114 = 0xc;
                        return;
                    }
                }
                if (v10 < 120.0 && v10 > 60.0 && unk3110 < 0x168 && unk3110 > 0x140) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 120.0 && v10 > 80.0 && unk3110 < 0x17c && unk3110 > 0x168) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 150.0 && unk3110 < 0x1ae && unk3110 > 0x17c) {
                    unk3114 = 0xe;
                    return;
                }
                if (0x5a - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x5a < v10 && v10 < 130.0 && unk3110 < 0x1d6 && unk3110 > 0x1ae) {
                    unk3114 = 0xa;
                    return;
                }
                if (v10 > 90.0 && v10 < 150.0 && unk3110 < 0x212 && unk3110 > 0x1d6) {
                    unk3114 = 0xa;
                    return;
                }
                if (v10 > 180.0 && unk3110 < 0x230 && unk3110 > 0x226) {
                    m_command = 0xa;
                    return;
                }
                if (v10 < 100.0 && unk3110 < 0x23a && unk3110 > 0x230) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x65;
                    return;
                }
                if (v10 > 100.0 && unk3110 < 0x24e && unk3110 > 0x23a) {
                    m_command = 0xa;
                    return;
                }
                if (v10 > 100.0 && unk3110 < 0x262 && unk3110 > 0x24e) {
                    m_command = 0xb;
                    return;
                }
                if (unk3110 < 0x2ee && unk3110 > 0x2bc && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c && v10 > 100.0) {
                    unk3114 = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0 && v10 < 80.0 && x8 < 120.0 && unk3110 < 0xa) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 90.0 && unk3110 < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x16;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 90.0) {
                        if (unk3110 < (unk118 > 500.0 || unk120 > 0) * 8 + 0xa) {
                            m_command = 0x14;
                            return;
                        }
                    }
                    if (v10 < 60.0 && unk3110 < 0x136 && unk3110 > 0x12c && x8 > 100.0 && m_gauge == 0xbb8) {
                        m_command = 0x66;
                        return;
                    }
                    if (v10 < 60.0 && unk3110 < 0x140 && unk3110 > 0x136 && x8 > 200.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)CPlayer::Random(0, 2) + 0x64;
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
                if (v10 < 80.0 && x8 > 90.0 && x8 < 80.0 && (*m_opponent)->y < y && unk3110 > 0x64 && unk3110 < 0xb4) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 100.0 && x8 < 130.0 && unk3110 > 0xb4 && unk3110 < 0xf0) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && y < (*m_opponent)->y && unk3110 < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 90.0 && x8 > 90.0 && unk3110 > 0x14 && unk3110 < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 100.0 && x8 > 70.0 && x8 < 100.0 && y < (*m_opponent)->y && unk3110 > 0x28 && unk3110 < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if (v10 > 90.0 && v10 < 130.0 && x8 > 40.0 && x8 < 120.0 && y > (*m_opponent)->y && unk3110 > 0x32 && unk3110 < 0x41) {
                    m_pressC = 1;
                    m_inputX = facing;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 5.0f * unka8 && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x3e8) < 2 && v10 > 90.0) {
        unk3114 = 4;
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 4) {
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
    if ((WORD)CPlayer::Random(0, 0x64) < 0x28 && v10 < 120.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x46) {
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

void CAkane::UpdateObjects()
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 2.0;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].timer++;
                if ((m_objects[v4].unk80 == 3 || m_objects[v4].y >= 0.0) && unk314c[v4] == 0) {
                    m_objects[v4].frame = 1;
                    unk314c[v4] = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].unk80 == 2 || m_objects[v4].unk80 == 4) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].pattern = 0x194;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case 0x191:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 1.3;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].timer++;
                if ((m_objects[v4].unk80 == 3 || m_objects[v4].y >= 0.0) && unk314c[v4] == 0) {
                    m_objects[v4].frame = 1;
                    unk314c[v4] = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].unk80 == 2 || m_objects[v4].unk80 == 4) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].pattern = 0x194;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case 0x192:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 2.0;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].timer++;
                if ((m_objects[v4].unk80 == 3 || m_objects[v4].y >= 0.0) && unk314c[v4] == 0) {
                    m_objects[v4].frame = 1;
                    unk314c[v4] = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].unk80 == 4) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].pattern = 0x194;
                }
                if (m_objects[v4].unk80 == 2) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = 0.2;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].pattern = 0x193;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case 0x193:
                m_objects[v4].vy += 0.04;
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].unk84 = 1;
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
                if (m_objects[v4].unk80 > 1 || m_objects[v4].y > 0.0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].pattern = 0x194;
                }
                break;
            case 0x194:
                m_objects[v4].vy += 0.05;
                m_objects[v4].scale = 1;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                }
                break;
            case 0x195:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -8.0;
                if (m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < -1000.0) {
                    m_objects[v4].scale = 0;
                    if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                        m_objects[v4].unk80 = 0;
                        m_objects[v4].pattern = 0x197;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].x = (int)((*m_opponent)->x + m_objects[v4].facing * ((m_objects[v4].y - (*m_opponent)->y) / 2.0) + ((WORD)CPlayer::Random(0, 0x8c) - 0x46));
                        break;
                    }
                    if ((WORD)CPlayer::Random(0, 2) == 0) {
                        m_objects[v4].pattern = 0x198;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].x = (int)((*m_opponent)->x + m_objects[v4].facing * 0x64 + m_objects[v4].facing * (m_objects[v4].y - (*m_opponent)->y * 0.5) + ((WORD)CPlayer::Random(0, 0x8c) - 0x46));
                        break;
                    }
                    m_objects[v4].pattern = 0x196;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].x = (int)((*m_opponent)->x + m_objects[v4].facing * ((m_objects[v4].y - (*m_opponent)->y) / 4.0) + ((WORD)CPlayer::Random(0, 0x8c) - 0x46));
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
                m_objects[v4].vx = 2.0;
                m_objects[v4].vy = 8.0;
                if (unk314c[v4] == 0) {
                    unk314c[v4] = (WORD)CPlayer::Random(1, 0x14);
                }
                if (m_objects[v4].frame >= 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y >= unk314c[v4] - 0xf && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
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
                m_objects[v4].vx = 4.0;
                m_objects[v4].vy = 8.0;
                if (unk314c[v4] == 0) {
                    unk314c[v4] = (WORD)CPlayer::Random(1, 0x14);
                }
                if (m_objects[v4].frame >= 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y >= unk314c[v4] - 0xf && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
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
                m_objects[v4].vx = 7.0;
                m_objects[v4].vy = 8.0;
                if (unk314c[v4] == 0) {
                    unk314c[v4] = (WORD)CPlayer::Random(1, 0x14);
                }
                if (m_objects[v4].frame >= 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y >= unk314c[v4] - 0xf && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
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
            case 0x199:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    if (unk314c[v4] == 0) {
                        m_objects[v4].unk84 = 1;
                        unk314c[v4]++;
                    }
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == -1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    l50.type = 0x19b;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.scale = 0;
                    l50.unk0 = 1;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
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
                if ((m_objects[v4].x < -100.0 || m_objects[v4].x > 740.0) && pattern != 0xfc) {
                    RemoveObject(v4);
                    unk3144 = 0;
                }
                break;
            case 0x19a:
                if (m_objects[v4].frame < 6) {
                    m_objects[v4].vy += 0.04;
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0 && m_objects[v4].frame < 6) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 6;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].y = 0.0;
                    unke8 = 1.5;
                    l50.type = 3;
                    l50.unk2c = 7;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = 0x19d;
                        break;
                    }
                }
                break;
            case 0x19b:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -0.7;
                    m_objects[v4].vy = -1.5;
                }
                m_objects[v4].vy += 0.03;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case 0x19c:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    unk314c[v4] = 0;
                    unk324c[v4] = 0;
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].vx -= 0.05;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                if (m_objects[v4].frame < 0x1a && m_objects[v4].unk84 == 0) {
                    m_objects[v4].frame = 0x1a;
                    m_objects[v4].timer = 0;
                    if (m_objects[v4].unk80 == 3) {
                        (*m_opponent)->unk14a = 0x5a;
                    }
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (unk324c[v4] < 3 && m_objects[v4].frame == 0x19) {
                        unk324c[v4]++;
                        m_objects[v4].frame = 0xa;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19d:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 3) {
                        m_objects[v4].vx = -6.0;
                        m_objects[v4].vy = -4.0;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                if (m_objects[v4].x < -80.0 || m_objects[v4].x > 720.0) {
                    RemoveObject(v4);
                    unk3144 = 0;
                }
                break;
            case 0x19e:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.3;
                    m_objects[v4].vy = 0.8;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy -= 0.015;
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if ((m_objects[v4].x < -150.0 || m_objects[v4].x > 790.0) && pattern != 0x12c) {
                    RemoveObject(v4);
                    unk3144 = 0;
                }
                break;
            case 0x19f:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 3.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 0;
                    unk314c[v4]++;
                }
                if (m_objects[v4].x - (*m_opponent)->x < 60.0 && m_objects[v4].x - (*m_opponent)->x > -60.0 && m_objects[v4].frame < 3) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a0;
                    break;
                }
                if (m_objects[v4].frame > 2) {
                    m_objects[v4].vx -= 0.033;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 3 && unk314c[v4] < 0xa) {
                        unk314c[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x19d;
                        break;
                    }
                }
                break;
            case 0x1a0:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                m_objects[v4].vx -= 0.04;
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x19d;
                        break;
                    }
                }
                break;
            case 0x1a1:
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
                    unk3144 = 1;
                    break;
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].unk88 = 0;
                }
                if (pattern != 0x132 && m_objects[v4].frame < 0x12) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x12;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 0xb;
                    unk314c[v4]++;
                }
                if (m_objects[v4].frame < 2 && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 2;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].y = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 4 && unk14c == 0) {
                    m_objects[v4].frame = 5;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].timer == 0 && (m_objects[v4].frame == 6 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0xe)) {
                    m_objects[v4].vx = 0.0;
                    unk2c9 = 0x14;
                }
                if (m_objects[v4].vx < 0.0 && m_objects[v4].frame < 0x14) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame < 2) {
                    m_objects[v4].vy += 0.085;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xc && unk324c[v4] < 3) {
                        m_objects[v4].frame = 5;
                        if (unk324c[v4] > 1) {
                            unk3144 = 1;
                        }
                        unk324c[v4]++;
                    }
                    if (m_objects[v4].frame == 0x15) {
                        m_objects[v4].vx = -4.4;
                        m_objects[v4].vy = -3.8;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                if ((m_objects[v4].x < m_game->unk14248 - 0x32 && m_objects[v4].facing == 1 || m_objects[v4].x > m_game->unk14250 + 0x32 && m_objects[v4].facing == -1) && m_objects[v4].frame > 0x14) {
                    RemoveObject(v4);
                    unk3144 = 0;
                }
                break;
            case 0x1a2:
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
                    unk3144 = 1;
                    break;
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].unk88 = 0;
                }
                if (pattern != 0x133 && m_objects[v4].frame < 0x19) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x19;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 0x63;
                    unk314c[v4]++;
                }
                if (m_objects[v4].frame < 2 && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 2;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].y = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 4 && unk14c == 0) {
                    m_objects[v4].frame = 5;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0x15) {
                    m_objects[v4].vx = 2.2;
                    unk2c9 = 0x14;
                }
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 7 && m_objects[v4].frame == 0xc) {
                    unk2c9 = 0x14;
                }
                if (m_objects[v4].vx > 0.0 && m_objects[v4].frame > 4) {
                    m_objects[v4].vx -= 0.105;
                }
                if (m_objects[v4].vx < 0.0 && m_objects[v4].frame < 0x14) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame < 2) {
                    m_objects[v4].vy += 0.085;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x14 && unk324c[v4] < 6) {
                        m_objects[v4].frame = 5;
                        if (unk324c[v4] > 4) {
                            unk3144 = 1;
                        }
                        unk324c[v4]++;
                    }
                    if (m_objects[v4].frame == 0x1c) {
                        m_objects[v4].vx = -4.4;
                        m_objects[v4].vy = -3.8;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                if ((m_objects[v4].x < m_game->unk14248 - 0x32 && m_objects[v4].facing == 1 || m_objects[v4].x > m_game->unk14250 + 0x32 && m_objects[v4].facing == -1) && m_objects[v4].frame > 0x14) {
                    RemoveObject(v4);
                    unk3144 = 0;
                }
                break;
            case 0x1a3:
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].unk80 = 0;
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].pattern = 0x19a;
                    break;
                }
                m_game->Unk4080c0(0xf);
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk314c[v4] == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                if (m_objects[v4].frame < 2 && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 2;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].y = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 4 && unk14c == 0) {
                    m_objects[v4].frame = 5;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 7 && m_objects[v4].frame == 0xc) {
                    unk2c9 = 0x14;
                }
                if (m_objects[v4].frame == 0x16 && m_objects[v4].unk80 == 3) {
                    m_objects[v4].vx = 0.05;
                    m_objects[v4].vy = -0.2;
                    (*m_opponent)->unk14a = 0x78;
                    m_objects[v4].unk80 = 0;
                    l50.type = 0x1a4;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.unk0 = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame == 0x16 && (*m_opponent)->unk14a == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -6.0;
                }
                if (m_objects[v4].frame < 2) {
                    m_objects[v4].vy += 0.085;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x14 && unk324c[v4] < 0xa) {
                        m_objects[v4].frame = 5;
                        unk324c[v4]++;
                    }
                    if (m_objects[v4].frame == 0x16) {
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -6.0;
                        unk2c9 = 0x14;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                if (m_objects[v4].y < -640.0 && m_objects[v4].frame > 0x14) {
                    RemoveObject(v4);
                    unk3144 = 0;
                }
                break;
            case 0x1a4:
                m_objects[v4].vx = 0.05;
                m_objects[v4].vy = -0.2;
                if ((*m_opponent)->unk14a == 0) {
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
            case 0x1a5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -10.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].x > m_game->unk14250 + 0x3c && m_objects[v4].facing == -1 || m_objects[v4].x < m_game->unk14248 - 0x3c && m_objects[v4].facing == 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -9.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].x > m_game->unk14250 + 0x3c && m_objects[v4].facing == -1 || m_objects[v4].x < m_game->unk14248 - 0x3c && m_objects[v4].facing == 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -9.6;
                    m_objects[v4].vy = -3.8;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].x > m_game->unk14250 + 0x3c && m_objects[v4].facing == -1 || m_objects[v4].x < m_game->unk14248 - 0x3c && m_objects[v4].facing == 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 10.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].x > m_game->unk14250 + 0x3c && m_objects[v4].facing == 1 || m_objects[v4].x < m_game->unk14248 - 0x3c && m_objects[v4].facing == -1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 9.8;
                    m_objects[v4].vy = -2.46;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].x > m_game->unk14250 + 0x3c && m_objects[v4].facing == 1 || m_objects[v4].x < m_game->unk14248 - 0x3c && m_objects[v4].facing == -1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 10.0;
                    m_objects[v4].vy = -4.0;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].x > m_game->unk14250 + 0x3c && m_objects[v4].facing == 1 || m_objects[v4].x < m_game->unk14248 - 0x3c && m_objects[v4].facing == -1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -10.0;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < (*m_opponent)->y - 180.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].timer > 0xb4) {
                    m_objects[v4].scale = 1;
                }
                if (m_objects[v4].timer > 0xc3) {
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
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x38 && (*m_opponent)->unk140 > 0) {
                        m_game->FlashWhite(0x14, 0x78, 0x14);
                    }
                    if (m_objects[v4].frame >= v58) {
                        if (unkac + 1 != m_game->unk134e) {
                            RemoveObject(v4);
                            unk3140 = 0xa;
                        }
                        if (unkac + 1 == m_game->unk134e) {
                            m_objects[v4].frame = m_objects[v4].frame - 1;
                            (*m_opponent)->unk140 = 0;
                        }
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
