// CSayuri (0x4463e0-0x45184f): the character class whose files are in sayuri\ in the game
// folder (sayuri.dat sprites, sayuri.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CSayuri::CSayuri(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "sayuri");
    lastSurface = 0x240;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk314c = 0;
    unk3148 = 0;
    unk3150 = 0x3e7;
    unk2ad0[0] = 0;
    unk2af8[0] = -0x40;
    unk2ad0[1] = 0x13;
    unk2af8[1] = 0;
    unk2ad0[2] = -0x18;
    unk2af8[2] = -0xd;
    unk2ad0[3] = 0xc;
    unk2af8[3] = -0x10;
    unk2ad0[4] = 0x15;
    unk2af8[4] = -0x2f;
    unk30f4 = 5;
    unk30f5[0] = 1;
    unk30f5[1] = 2;
    unk30f5[0xa] = 9;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3154[v4] = 0;
        unk3254[v4] = 0;
        unk3354[v4] = 0;
    }
}

void CSayuri::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk314c = 0;
    unk3148 = 0;
    unk3150 = 0x3e7;
    unk2ad0[0] = 0;
    unk2af8[0] = -0x40;
    unk2ad0[1] = 0x13;
    unk2af8[1] = 0;
    unk2ad0[2] = -0x18;
    unk2af8[2] = -0xd;
    unk2ad0[3] = 0xc;
    unk2af8[3] = -0x10;
    unk2ad0[4] = 0x15;
    unk2af8[4] = -0x2f;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3154[v4] = 0;
        unk3254[v4] = 0;
        unk3354[v4] = 0;
    }
    CPlayer::Reset();
}

void CSayuri::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CSayuri::RemoveObject(short p1)
{
    unk3154[p1] = 0;
    unk3254[p1] = 0;
    unk3354[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CSayuri::Move()
{
    CPlayer::Unk40e740();
}

void CSayuri::StartCommand()
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
    if (unk15c < 2 && pattern > 0x95 && pattern < 0x9c && frame == 0 && timer == 0) {
        if ((*m_opponent)->pattern == unk3150) {
            unk3138 = 1;
            CPlayer::Unk410ac0(0xb1, 0xa);
        } else {
            unk3138 = 0;
        }
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
        if (m_hp < 0xd05 && m_command == 0x62 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13b].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13b;
            return;
        }
        if (m_command == 0xac && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0xab || m_command == 0xac) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0xaa || m_command == 0xab || m_command == 0xac) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0xa2 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x139;
            return;
        }
        if ((m_command == 0xa1 || m_command == 0xa2) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x137].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x137;
            return;
        }
        if ((m_command == 0xa0 || m_command == 0xa1 || m_command == 0xa2) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x134].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x134;
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x133;
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x132].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x132;
            return;
        }
        if (m_command == 0x2a && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if ((m_command == 0x29 || m_command == 0x2a) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && pattern != 0x10c && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x104;
            return;
        }
        if (m_command == 0x28 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x103;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x108].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x108;
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x107].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x107;
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x106].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x106;
            return;
        }
        if ((m_command == 0x1e || m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x48 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if ((m_command == 0x47 || m_command == 0x48) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            return;
        }
        if (m_command == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0 || y < 0.0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk314c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            if (y < 0.0) {
                pattern = 0x10b;
            }
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk314c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            if (y < 0.0) {
                pattern = 0x10a;
            }
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk314c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            if (y < 0.0) {
                pattern = 0x109;
            }
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
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::Unk40f170();
                pattern = 0xcb;
            }
        }
    }
}

void CSayuri::DrawGauge()
{
}

void CSayuri::Vf8()
{
    if (frame == 0 && timer == 0 && pattern > 0x95 && pattern < 0x9c && (*m_opponent)->m_attackResult == 2 && (*m_opponent)->pattern == unk3150) {
        unk3138 = 1;
        CPlayer::Unk410ac0(0xb1, 0xa);
    }
}

void CSayuri::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CSayuri::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 5) {
            m_command = 0x62;
            return;
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
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            m_command = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 8) {
            m_command = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 7) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 8;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && y == 0.0) {
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
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == 4 && x6 == 0 && y == 0.0) {
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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
        if ((v5 & 0xf) == 4 && x6 == 0 && y == 0.0) {
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
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0 && y < 0.0) {
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

void CSayuri::CpuInput()
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
            if (v10 < 140.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_command = 0x14;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 40.0 && v10 < 90.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
            m_pressB = 1;
            m_inputY = 1;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 80.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = 0x20;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 + ((unk118 > 500.0) << 1)) {
                m_command = 0xc;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_command = 0x14;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 4.0f && m_gauge >= 0x7d0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xab;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 + ((unk118 > 500.0) << 1)) {
                m_command = 0xc;
                return;
            }
        }
        if (v10 < 135.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 + ((unk118 > 500.0) << 1)) {
                m_command = 0x20;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_command = 0x14;
                return;
            }
        }
        if (v10 > 220.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
                m_command = 0xb;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x96) < unka8 * 1.0f && m_gauge >= 0xbb8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                return;
            }
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
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 0.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -80.0 && y - (*m_opponent)->y < 30.0 && x8 > 30.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
            m_command = 0x2a;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && unk3114 != 2 && (*m_opponent)->unk14c == 0) {
        unk3110 = (WORD)CPlayer::Random(0, 0x64);
        if (unk3110 < 4 && unk118 > 500.0) {
            m_command = 0x20;
            return;
        }
        if (unk3110 < 0xa && unk118 > 500.0) {
            m_command = 0x14;
            return;
        }
        if (unk3110 < 0xd && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (unk3110 < 0x11 && unk3110 > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)CPlayer::Random(0, 2) * 0xaa;
            return;
        }
        if (unk3110 < 0x10 && unk3110 > 0x12 && m_gauge == 0xbb8) {
            m_command = 0x5d;
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
    if (unk3114 == 7) {
        m_inputY = -1;
        m_inputX = facing;
        if (y < -30.0) {
            m_command = 0x28;
            unk3114 = 0;
        }
        return;
    }
    if (m_attackResult > 1 && unk14a == 0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 25.0f && unk3114 != 1 && unk3114 != 2) {
        unk3110 = (WORD)CPlayer::Random(0, 0x3e8);
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
            }
            if (v10 < 125.0 && unk3110 > 0x18f && unk3110 < 0x226) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 135.0 && unk3110 > 0x226 && unk3110 < 0x2bc) {
                m_pressB = 1;
                m_inputY = 1;
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
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0x1e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xc8 && unk3110 < 0x1c2) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x1c2 && unk3110 < 0x1f4 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xaa;
                return;
            }
            if (unk3110 < 0xc8) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x12b && unk3110 < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x352) {
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 7;
                }
                m_inputY = -1;
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
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0x1e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xc7 && unk3110 < 0x190) {
                m_command = 0xb;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x18f && unk3110 < 0x1f4 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xaa;
                return;
            }
            if (unk3110 < 0x190 && v10 < 100.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x2bc) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 1;
                return;
            }
        }
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xfa && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x15e && m_gauge >= 0x3e8 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xaa;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x28a) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (unk3110 > 0x28a && unk3110 < 0x2bc && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x2bc && unk3110 < (m_attackResult == 3) * 0x14 + 0x2da && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
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
            if (v10 < 60.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && unk3110 < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
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
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xc8 && m_attackResult == 3) {
                m_command = 0x1e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0xc7 && unk3110 < 0x190) {
                m_command = 0xb;
                return;
            }
            if ((*m_opponent)->y < 0.0 && unk3110 > 0x18f && unk3110 < 0x1f4 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xaa;
                return;
            }
            if (unk3110 < 0x190 && v10 < 100.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (unk3110 > 0x190 && unk3110 < 0x2bc) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xa;
                return;
            }
            if (unk3110 > 0x352) {
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 7;
                }
                m_inputY = -1;
                return;
            }
            if (unk3110 > 0x398) {
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
            if ((*m_opponent)->y < 0.0 && unk3110 < 0xfa && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (unk3110 > 0xfa && unk3110 < 0x15e && m_gauge >= 0x3e8 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xaa;
                return;
            }
            if (unk3110 > 0 && unk3110 < 0x28a) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (unk3110 > 0x352 && m_attackResult == 3) {
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    unk3114 = 7;
                }
                m_inputY = -1;
                return;
            }
            if (unk3110 > 0x398 && m_attackResult == 3) {
                unk3114 = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (unk3110 > 0x28a && unk3110 < 0x2bc && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (unk3110 > 0x2bc && unk3110 < (m_attackResult == 3) * 0x14 + 0x2da && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                return;
            }
            if (unk3110 > 0x2ee && unk3110 < 0x320 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0xaa;
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
            if (unk3110 > 0x3c && unk3110 < 0x12c) {
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
            if (vy < 0.0 && unk3110 < 0x12c) {
                m_command = 0x28;
                return;
            }
            if (unk3110 > 0x289) {
                unk3114 = 3;
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
                if (v10 < 110.0 && unk3110 < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 150.0 && v10 > 110.0 && unk3110 < 0x2a && unk3110 > 0x28) {
                    m_command = 0x1e;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x30 && unk3110 > 0x2d && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x14;
                    return;
                }
                if (v10 < 80.0 && unk3110 < 0x35 && unk3110 > 0x32 && (*m_opponent)->pattern > 0xc7 && m_gauge >= 0x7d0) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0xab;
                    return;
                }
                if (v10 > 220.0 && unk3110 < 0x37 && unk3110 > 0x35 && (*m_opponent)->pattern > 0xc7 && m_gauge >= 0xbb8) {
                    m_command = 0x62;
                    return;
                }
                if (unk3110 < 0x2a && unk3110 > 0x2f) {
                    m_command = facing;
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
                    if (v10 < 130.0 && v10 > 90.0 && x8 < 40.0 && unk3110 < 0x23) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && unk3110 < ((*m_opponent)->pattern > 0xc7) * 0xf + 5) {
                        m_command = 0x14;
                        return;
                    }
                    if (v10 < 130.0 && v10 > 90.0 && x8 < 100.0 && unk3110 < 0x23) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 < 80.0 && v10 > 30.0 && x8 < 120.0 && v10 > 80.0 && unk3110 < 0x32) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 100.0 && unk3110 > 0x28 && unk3110 < 0x2d && m_gauge >= 0x7d0) {
                        m_command = (WORD)CPlayer::Random(0, 2) + 0xab;
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
                if (v10 < 80.0 && x8 < 80.0 && (*m_opponent)->y < y) {
                    if (unk3110 < (unk118 > 500.0 || unk120 > 0) * 0x14 + 6) {
                        m_command = 0x14;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 > 60.0 && unk3110 < 0x6e) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 120.0 && x8 < 90.0 && (*m_opponent)->y > y && unk3110 < 0x78) {
                    m_pressC = 1;
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
    if ((WORD)CPlayer::Random(0, 0x64) < 0x32 && v10 < 90.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 0x50) {
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

void CSayuri::UpdateObjects()
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
                if (pattern > 0x95 && pattern < 0x9d || pattern > 0xa7 && pattern < 0xab) {
                    if (pattern > 0x95 && pattern < 0x99 || pattern == 0xa8) {
                        m_objects[v4].y = y - 56.0;
                        m_objects[v4].x = facing * 0x1c + x;
                    }
                    if (pattern > 0x98 && pattern < 0x9c || pattern == 0xa9) {
                        m_objects[v4].y = y - 37.0;
                        m_objects[v4].x = facing * 0x1c + x;
                    }
                    if (pattern == 0x9c || pattern == 0xaa) {
                        m_objects[v4].y = y - 64.0;
                        m_objects[v4].x = facing * 0x1c + x;
                    }
                } else {
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
            case 0x191:
                if (m_objects[v4].frame == 0 && unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4] = 1;
                    m_objects[v4].vx = 0.1;
                }
                if (unk3154[v4] < 6) {
                    m_objects[v4].vx += 0.013;
                }
                if (unk3154[v4] == 6) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].vx > 2.0) {
                    m_objects[v4].vx = 2.0;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].unk80 = 0;
                    unk3154[v4] = 6;
                }
                if (m_objects[v4].x < m_game->unk14248 - 0x14 || m_objects[v4].x > m_game->unk14250 + 0x14 || m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                    unk314c--;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3154[v4] < 5) {
                            unk3154[v4]++;
                        }
                    }
                }
                break;
            case 0x192:
                if (m_objects[v4].frame == 0 && unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4] = 1;
                    m_objects[v4].vx = 0.1;
                }
                if (unk3154[v4] < 6) {
                    m_objects[v4].vx += 0.013;
                }
                if (unk3154[v4] == 6) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].vx > 2.0) {
                    m_objects[v4].vx = 2.0;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].unk80 = 0;
                    unk3154[v4] = 6;
                }
                if (m_objects[v4].x < m_game->unk14248 - 0x14 || m_objects[v4].x > m_game->unk14250 + 0x14 || m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                    unk314c--;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3154[v4] < 5) {
                            unk3154[v4]++;
                        }
                    }
                }
                break;
            case 0x193:
                m_objects[v4].y = y;
                m_objects[v4].x = x;
                if (pattern != 0x103 && pattern != 0x104 && pattern != 0x105 || frame > 2) {
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
            case 0x194:
                m_objects[v4].y = y;
                m_objects[v4].x = x;
                if (pattern != 0x103 && pattern != 0x104 && pattern != 0x105 || y >= 0.0) {
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
                if (unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4]++;
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
                if ((pattern < 0x132 || pattern > 0x134 || frame > 0x15) && m_objects[v4].frame < 0xa) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x197;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3f);
                    l50.y = (double)((int)m_objects[v4].y - 0x5d);
                    l50.scale = 2;
                    l50.unk2c = 4;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0x16) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x199:
                if ((pattern < 0x132 || pattern > 0x134 || frame > 0x15) && m_objects[v4].frame < 0xa) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x197;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3f);
                    l50.y = (double)((int)m_objects[v4].y - 0x5d);
                    l50.scale = 2;
                    l50.unk2c = 4;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0x16) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19a:
                if ((pattern < 0x132 || pattern > 0x134 || frame > 0x15) && m_objects[v4].frame < 0xa) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x197;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x3f);
                    l50.y = (double)((int)m_objects[v4].y - 0x5d);
                    l50.scale = 2;
                    l50.unk2c = 4;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0x16) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19b:
                if ((pattern < 0x132 || pattern > 0x134 || frame > 0x15) && m_objects[v4].frame < 0xa) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x197;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x30);
                    l50.y = (double)((int)m_objects[v4].y - 0x35);
                    l50.scale = 2;
                    l50.unk2c = 4;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0x16) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19c:
                if ((pattern < 0x132 || pattern > 0x134 || frame > 0x15) && m_objects[v4].frame < 0xa) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x197;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x30);
                    l50.y = (double)((int)m_objects[v4].y - 0x35);
                    l50.scale = 2;
                    l50.unk2c = 4;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0x16) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19d:
                if ((pattern < 0x132 || pattern > 0x134 || frame > 0x15) && m_objects[v4].frame < 0xa) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xa;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x197;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x2b);
                    l50.y = (double)((int)m_objects[v4].y - 0x35);
                    l50.scale = 2;
                    l50.unk2c = 4;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 9 && frame < 0x16) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
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
                if (unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 5;
                    unk3154[v4]++;
                }
                if (m_objects[v4].frame == 3 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    l50.type = 0x1a1;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y + 0xa0);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk18 = m_objects[v4].facing;
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
            case 0x1a1:
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
            case 0x1a3:
                if (m_objects[v4].frame == 0 && unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4] = 1;
                    m_objects[v4].vx = 0.1;
                }
                if (unk3154[v4] < 6) {
                    m_objects[v4].vx += 0.01;
                }
                if (unk3154[v4] < 6) {
                    m_objects[v4].vy += 0.006;
                }
                if (unk3154[v4] == 6) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].vx > 2.0) {
                    m_objects[v4].vx = 2.0;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].unk80 = 0;
                    unk3154[v4] = 6;
                }
                if (m_objects[v4].x < m_game->unk14248 - 0x14 || m_objects[v4].x > m_game->unk14250 + 0x14 || m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                    unk314c--;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3154[v4] < 5) {
                            unk3154[v4]++;
                        }
                    }
                }
                break;
            case 0x1a4:
                if (m_objects[v4].frame == 0 && unk3154[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3154[v4] = 1;
                    m_objects[v4].vx = 0.1;
                }
                if (unk3154[v4] < 6) {
                    m_objects[v4].vx += 0.007;
                }
                if (unk3154[v4] < 6) {
                    m_objects[v4].vy += 0.012;
                }
                if (unk3154[v4] == 6) {
                    m_objects[v4].vy += 0.035;
                }
                if (m_objects[v4].vx > 2.0) {
                    m_objects[v4].vx = 2.0;
                }
                if (m_objects[v4].unk80 > 1 && m_objects[v4].unk84 == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -1.5;
                    m_objects[v4].unk80 = 0;
                    unk3154[v4] = 6;
                }
                if (m_objects[v4].x < m_game->unk14248 - 0x14 || m_objects[v4].x > m_game->unk14250 + 0x14 || m_objects[v4].y > 60.0) {
                    RemoveObject(v4);
                    unk314c--;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3154[v4] < 5) {
                            unk3154[v4]++;
                        }
                    }
                }
                break;
            case 0x1a5:
                if (unk3154[v4] == 0) {
                    unk3154[v4]++;
                    unk2c8 = 7;
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y + 25.0;
                if (pattern != 0x102) {
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
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a6:
                if (frame > 1) {
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
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
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
