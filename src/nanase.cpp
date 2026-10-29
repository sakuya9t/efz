// CNanase (0x48a720-0x49d60f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNanase::CNanase(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "nanase");
    lastSurface = 0x29c;
    unk345c = new EffectAnim[0x1f9];
    unk3460 = new PatternData[0x1f9];
    unk3458 = 0;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk344c = 0;
    unk3450 = 0;
    unk3454 = 0;
    Unk48e140(0);
    unk2ad0[0] = -0xc;
    unk2af8[0] = -0x3a;
    unk2ad0[1] = 0x12;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x10;
    unk2af8[2] = -9;
    unk2ad0[3] = 0x15;
    unk2af8[3] = -0xe;
    unk2ad0[4] = 0x21;
    unk2af8[4] = -0x1a;
    unk30f4 = 5;
    unk30f5[0] = 6;
    unk30f5[1] = 2;
    unk30f5[2] = 5;
    unk30f5[3] = 0xc;
    unk30f5[0xa] = 0;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
}

void CNanase::Reset()
{
    int v4;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk344c = 0;
    unk3450 = 0;
    unk3454 = 0;
    Unk48e140(0);
    unk2ad0[0] = -0xc;
    unk2af8[0] = -0x3a;
    unk2ad0[1] = 0x12;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x10;
    unk2af8[2] = -9;
    unk2ad0[3] = 0x15;
    unk2af8[3] = -0xe;
    unk2ad0[4] = 0x21;
    unk2af8[4] = -0x1a;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk314c[v4] = 0;
        unk324c[v4] = 0;
        unk334c[v4] = 0;
    }
    CPlayer::Reset();
}

CNanase::~CNanase()
{
    anims = (EffectAnim*)unk3464;
    m_patterns = (PatternData*)unk3468;
    delete[] unk345c;
    delete[] unk3460;
    CPlayer::~CPlayer();
}

void CNanase::Load()
{
    Unk48d940();
    CPlayer::Load();
    unk3464 = (int)anims;
    unk3468 = (int)m_patterns;
}

void CNanase::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CNanase::RemoveObject(short p1)
{
    unk314c[p1] = 0;
    unk324c[p1] = 0;
    unk334c[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CNanase::Move()
{
    CPlayer::Unk40e740();
}

void CNanase::StartCommand()
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
        if (m_command == 0x99 && m_hp < 0xd05 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x133;
            return;
        }
        if (m_command == 0x98 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && (m_patterns[pattern].unk2 <= m_patterns[0x136].unk0 || pattern > 0xfc && pattern < 0x100 && m_attackResult == 3)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x136;
            return;
        }
        if ((m_command == 0x97 || m_command == 0x98) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && (m_patterns[pattern].unk2 <= m_patterns[0x135].unk0 || pattern > 0xfc && pattern < 0x100 && m_attackResult == 3)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if ((m_command == 0x96 || m_command == 0x97 || m_command == 0x98) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && (m_patterns[pattern].unk2 <= m_patterns[0x134].unk0 || pattern > 0xfc && pattern < 0x100 && m_attackResult == 3)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x134;
            return;
        }
        if (m_command == 0x66 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 1 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if ((m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 1 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x130;
            return;
        }
        if ((m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 1 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if (m_command == 0x70 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12e;
            return;
        }
        if ((m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12d;
            return;
        }
        if ((m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12c;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x102;
            if (y < 0.0) {
                frame = 9;
                unk3140 = 1;
                m_attackResult = 3;
            }
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x101;
            if (y < 0.0) {
                frame = 9;
                m_attackResult = 3;
            }
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            if (y < 0.0) {
                frame = 9;
                m_attackResult = 3;
            }
            return;
        }
        if (m_command == 0x20 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x105;
            return;
        }
        if ((m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x104;
            return;
        }
        if (m_command == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x103;
            return;
        }
        if (m_command == 0x48 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            if (unk344c == 0) {
                pattern = 0x108;
            }
            return;
        }
        if (m_command == 0x47 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            if (unk344c == 0) {
                pattern = 0x107;
            }
            return;
        }
        if (m_command == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            return;
        }
        if (m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            return;
        }
        if (m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && unk344c == 0 && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfd;
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

void CNanase::Unk48d940()
{
    int k2c;
    PatternFrame* v28;
    EffectFrame* x24;
    int x20;
    int n1c;
    int a18;
    int k14;
    int l4;

    CFile v10("nanase\\nanase2.pat", 1);
    l4 = v10.ReadInt();
    n1c = 0;
    for (; n1c < l4; n1c++) {
        k14 = v10.ReadInt();
        unk3460[k14].unk0 = v10.ReadInt();
        unk3460[k14].unk2 = v10.ReadInt();
        unk345c[k14].frameCount = v10.ReadInt();
        a18 = unk345c[k14].frameCount;
        ((PatternData*)((int)(char*)unk3460 + k14 * 8))->Alloc(a18);
        ((EffectAnim*)((int)(char*)unk345c + k14 * 8))->Alloc(a18);
        x20 = 0;
        for (; x20 < a18; x20++) {
            x24 = &unk345c[k14].frames[x20];
            v28 = &unk3460[k14].frames[x20];
            x24->duration = (short)v10.ReadInt() * 3;
            x24->surface = v10.ReadInt();
            x24->width = v10.ReadInt();
            x24->height = v10.ReadInt();
            x24->x = v10.ReadInt();
            x24->y = v10.ReadInt();
            v28->unka0 = v10.ReadInt();
            v28->flagsAA = v10.ReadInt();
            v28->unkac = v10.ReadInt();
            v28->flagsB0 = v10.ReadInt();
            v28->unkb2 = v10.ReadInt();
            v28->unka8 = v10.ReadInt();
            v28->unkb4 = v10.ReadInt();
            v28->unkb6 = v10.ReadInt();
            v28->unkbc = (short)v10.ReadShort();
            v28->unkbc = v28->unkbc / 1e+02f;
            v28->unkb8 = (short)v10.ReadShort();
            v28->unkb8 = v28->unkb8 / -1e+02f;
            v28->unkc1 = v10.ReadShort();
            v28->unkc0 = v10.ReadShort();
            v28->unkc2 = v10.ReadInt();
            v28->unkc4 = v10.ReadInt();
            v28->unka4 = v10.ReadInt();
            v28->unkae = v10.ReadInt();
            v10.Read((void*)&v28->box90.left, 0x10);
            k2c = 0;
            for (; k2c < 2; k2c++) {
                v10.Read((void*)((k2c << 4) + (char*)v28), 0x10);
            }
            v10.Read((void*)&v28->attackBoxes[0].left, 0x10);
            k2c = 2;
            for (; k2c < 5; k2c++) {
                v10.Read((void*)((k2c << 4) + (char*)v28), 0x10);
            }
            k2c = 1;
            for (; k2c < 4; k2c++) {
                v10.Read((void*)&v28->attackBoxes[k2c].left, 0x10);
            }
        }
    }
}

void CNanase::DrawGauge()
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
        v2c = MakeRect(0, 0, unk3148 * x1c.width / 0xbb8, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3148 * x1c.width / 0xbb8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3148 * x1c.width / 0xbb8, 0x1f - x1c.y, unk3148 * x1c.width / 0xbb8, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CNanase::Unk48e140(char p1)
{
    int v8;
    int v4;

    if (p1 == 1 && unk3458 == 0) {
        anims = (EffectAnim*)(int)unk345c;
        v4 = 0;
        for (; v4 < 0x40; v4++) {
            m_objects[v4].anims = (EffectAnim*)(int)unk345c;
        }
        m_patterns = (PatternData*)(int)unk3460;
        unk3458 = 1;
        return;
    }
    if (p1 == 0 && unk3458 == 1) {
        anims = (EffectAnim*)unk3464;
        v8 = 0;
        for (; v8 < 0x40; v8++) {
            m_objects[v8].anims = (EffectAnim*)unk3464;
        }
        m_patterns = (PatternData*)unk3468;
        unk3458 = 0;
    }
}

void CNanase::Vf8()
{
}

void CNanase::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CNanase::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 7) {
            m_command = ((v5 & 0xe0) > 0) + 0x96 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x96 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 8;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8 && unk344c == 0) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8 && unk344c == 1) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
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

void CNanase::CpuInput()
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
    if ((WORD)CPlayer::Random(0, 0x3e8) < 25.0f * unka8 + (y < 0.0) * 0x1e * unka8 + (m_cpuAction == 3) * 0x190 + (pattern == 0xaa) * 0x12c) {
        unk14e = 0x3c;
    }
    if ((WORD)CPlayer::Random(0, 0x7d0) < ((unk130 > 0) * 4.0 + 1.0) * 8.0 * unka8 * ((pattern > 0x95 && pattern < 0x9d) * 2 + 1)) {
        unk14e = 0x3c;
    }
    if ((WORD)CPlayer::Random(0, 0x3e8) < 4e+01f * unka8 && pattern > 0xc7) {
        unk14e = 0x3c;
    }
    if (unk170 == 1 && m_cpuAction == 2) {
        unk14e = 0x1e;
        if (pattern < 0xc8) {
            m_cpuAction = 0;
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
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
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
    if (pattern == 0xfb && unk344c == 0) {
        if ((*m_opponent)->vy > 0.0 && (*m_opponent)->y > -280.0 && (*m_opponent)->y < -20.0 && (WORD)CPlayer::Random(0, 0x3e8) < 2) {
            m_command = 0xa;
            return;
        }
        if ((*m_opponent)->vy > 0.0 && (*m_opponent)->y > -220.0 && (*m_opponent)->y < -20.0) {
            if ((WORD)CPlayer::Random(0, 0x3e8) < 0x1e) {
                m_command = 0xb;
            }
            if ((WORD)CPlayer::Random(0, 0x3e8) < 0xa && m_gauge == 0xbb8 && (*m_opponent)->y < -100.0) {
                m_command = 0xc;
            }
            return;
        }
    }
    if (pattern == 0xa8 && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 40.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && (*m_opponent)->y == 0.0) {
                m_command = 0x46;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk344c == 0) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk344c == 1) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && (*m_opponent)->y == 0.0 && v10 < 40.0 && (*m_opponent)->y == 0.0) {
                m_command = 0x46;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0 && unk344c == 0) {
                m_command = 0x14;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f + ((unk118 > 500.0) << 1) && unk344c == 0 && (*m_opponent)->y == 0.0) {
                m_command = 0xc;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f + ((unk118 > 500.0) << 1) && unk344c == 0) {
                m_command = ((WORD)CPlayer::Random(0, 1) == 1) + 0x1f;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && m_gauge >= 0x3e8 && unk344c == 0 && (*m_opponent)->y == 0.0) {
                m_command = 0x6e;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && v10 < 150.0 && m_gauge >= 0x3e8 && unk344c == 1 && (*m_opponent)->y == 0.0) {
                m_command = 0x64;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (v10 < 220.0 && v10 > 160.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
            return;
        }
        if (v10 > 220.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
            return;
        }
    }
    if (pattern == 0xaa && frame == 1 && timer == 0) {
        if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (x8 < 80.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f && unk344c == 0) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x64);
        if (m_cpuRoll < 3 && unk118 > 500.0 && unk344c == 0) {
            m_command = 0x14;
            return;
        }
        if (m_cpuRoll < 7 && unk118 > 500.0 && unk344c == 0) {
            m_command = 0xc;
            return;
        }
        if (m_cpuRoll < 0xa && unk118 > 500.0 && unk344c == 0) {
            m_command = 0x20;
            return;
        }
        if (m_cpuRoll < 0xd && unk118 > 500.0 && unk344c == 0) {
            m_command = 0x16;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && unk344c == 0) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x16 && m_gauge >= 0x3e8 && unk344c == 1) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0x64;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x64);
        if (m_cpuRoll < 0x14) {
            m_cpuAction = 2;
            return;
        }
        if (v10 < 200.0 && m_cpuRoll < 0x20 && (*m_opponent)->y == 0.0 && v10 * 0.5 > x8 && v10 * 0.3 < x8) {
            m_command = 0x16;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0x100 || pattern == 0x101 || pattern == 0x103 || pattern == 0x12c || pattern == 0x12d || pattern == 0x12e)) {
        m_command = 0x34;
        return;
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 1.0f * unka8 && m_attackResult == 3 && (pattern == 0xfd && frame == 0xd || pattern == 0xfe && frame == 0xd)) {
        m_command = 0x34;
        return;
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
    if (m_cpuAction == 4) {
        m_inputY = -1;
        m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
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
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 7;
        }
        return;
    }
    if (m_cpuAction == 7 && pattern == 0xa3) {
        m_pressA = 1;
        if (pattern == 0xe6) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 8 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 9;
        }
        return;
    }
    if (m_cpuAction == 9 && pattern == 0xa3) {
        m_pressA = 2;
        if (pattern == 0xe7) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0xb;
        }
        return;
    }
    if (m_cpuAction == 0xb && pattern == 0xa3) {
        m_pressA = 3;
        if (pattern == 0xe8) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < 0x32) {
        m_command = 0x46;
        if (pattern == 0xfa) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_attackResult > 1 && unk14a == 0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x3e8);
        if (pattern == 0xc8) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 40.0 && m_cpuRoll < 0xa) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x64 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1b8) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                if (m_attackResult == 3 && (WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && v10 < 100.0) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll < 0xc8 && m_attackResult == 3 && (*m_opponent)->y == 0.0 && v10 < 80.0) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll < 0x190 && m_attackResult == 3 && (*m_opponent)->y == 0.0 && v10 < 80.0) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll < 0x15e && (*m_opponent)->y == 0.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x226 && v10 < 90.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x226 && m_cpuRoll < 0x2bc) {
                m_pressC = 1;
                m_inputY = (WORD)CPlayer::Random(0, 1) == 0;
                return;
            }
            if (m_cpuRoll > 0x398) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = (WORD)CPlayer::Random(0, 1) == 0;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x190 && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x12c) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == 0xcb) {
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && unk344c == 1) {
                m_command = 0x46;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 135.0 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 1) == 0) {
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if (m_cpuRoll < 0x190 && v10 < 80.0 && m_attackResult == 3) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll < 0x64 && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xce) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && unk344c == 1) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0xa;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1c2 && m_attackResult == 3 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xcf) {
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
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == 0xd0) {
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == 0xd1) {
            if (m_cpuRoll > 0x3b6) {
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == 0xe7) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && unk344c == 1) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && unk118 > 500.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x2bc) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
                return;
            }
            if (m_cpuRoll > 0x289 && (WORD)CPlayer::Random(0, 3) == 0) {
                m_cpuAction = 6;
                if (v10 > 110.0) {
                    m_cpuAction = 8;
                }
            }
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 25.0f * unka8) {
        if (unk344c == 1) {
            m_pressD = 1;
        }
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 3) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 50.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 8) {
                    m_command = 0x46;
                    return;
                }
                if (0x64 - (unk344c == 1) * 0x1e > v10 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if ((unk344c == 1) * 0xa + 0x64 > v10 && v10 > 70.0 && m_cpuRoll < 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (0x8c - (unk344c == 1) * 0x28 > v10 && m_cpuRoll < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 160.0 && m_cpuRoll < 0x1a) {
                    m_cpuAction = 8;
                    return;
                }
                if (v10 > 160.0 && m_cpuRoll < 0x20) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (0xaa - (unk344c == 1) * 0x3c > v10 && 0x78 - (unk344c == 1) * 0x28 < v10 && m_cpuRoll < 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 220.0 && v10 > 70.0 && m_cpuRoll < 0x28) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x2a && m_cpuRoll > 0x28) {
                    m_command = 0x14;
                    return;
                }
                if (m_cpuRoll < 0x2a && m_cpuRoll > 0x32) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
                if (v10 > 180.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0xfc && m_gauge >= 0x3e8) {
                    m_command = (WORD)CPlayer::Random(0, 2) + 0x6e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 120.0 && m_cpuRoll < 0x1e && unk344c == 0) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 > 80.0 && v10 < 120.0 && x8 > 70.0 && m_cpuRoll < 0x1e && unk344c == 1) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 > 120.0 && v10 < 180.0 && x8 > 90.0 && m_cpuRoll < 0x1e && unk344c == 1) {
                        m_cpuAction = 0xa;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0x23) {
                        m_command = 0x15;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 120.0) {
                        if (m_cpuRoll < (unk118 > 500.0 || unk120 > 0) * 5 + 6) {
                            m_command = 0x14;
                            return;
                        }
                    }
                    if (v10 < 90.0 && x8 < 120.0 && x8 > 90.0 && m_cpuRoll < 0xf) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 < 120.0 && x8 < 100.0 && m_cpuRoll < 0x11 && m_gauge == 0xbb8) {
                        m_command = 0x99;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 100.0 && x8 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (v10 < 120.0 && x8 < 100.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 140.0 && v10 > 80.0 && x8 > 40.0 && x8 < 80.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 120.0 && x8 < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 0x6e) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 120.0 && x8 < 90.0 && m_cpuRoll < 0x136) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 100.0 && x8 < 90.0 && m_cpuRoll < 0x190) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 3.0f * unka8) {
        m_command = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 60.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < 1.0f * unka8) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x3e8) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 2) {
        if ((WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
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
    if ((WORD)CPlayer::Random(0, 0x64) < 0x32 && v10 < 120.0) {
        if (facing == 1) {
            unk1a4 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
        } else {
            unk1a0 = (WORD)CPlayer::Random(0, 0xc8) + 0x3c;
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

void CNanase::UpdateObjects()
{
    WORD v58;
    WORD v54;
    int v4;

    if (unk3458 == 1) {
        Unk497540();
        return;
    }
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
                if (unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vx = 3.0;
                m_objects[v4].vy = 1.8;
                if (m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                    l50.type = 0x192;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    m_playVoice = 2;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    break;
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
            case 0x191:
                if (unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vx = 3.0;
                m_objects[v4].vy = 1.8;
                if (m_objects[v4].y > 0.0) {
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
            case 0x195:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].vy = -2.0 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if ((m_objects[v4].vy + m_objects[v4].y > 0.0 || m_objects[v4].unk80 > 1) && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                    RemoveObject(v4);
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
            case 0x196:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 5) * 0.1;
                    m_objects[v4].vy = -2.3 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if ((m_objects[v4].vy + m_objects[v4].y > 0.0 || m_objects[v4].unk80 > 1) && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                    RemoveObject(v4);
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
            case 0x197:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 4) * 0.1;
                    m_objects[v4].vy = -2.5 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if ((m_objects[v4].vy + m_objects[v4].y > 0.0 || m_objects[v4].unk80 > 1) && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_playVoice = 1;
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
            case 0x198:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xd) * 0.1;
                    m_objects[v4].vy = -1.7 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if ((m_objects[v4].vy + m_objects[v4].y > 0.0 || m_objects[v4].unk80 > 1) && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                    RemoveObject(v4);
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
            case 0x199:
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].vy = -1.0 - (WORD)CPlayer::Random(0, 0xa) * 0.05;
                    unk314c[v4] = 1;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].scale = 1;
                    unk314c[v4] = 2;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 2) {
                    RemoveObject(v4);
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
            case 0x19a:
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xf) * 0.1;
                    m_objects[v4].vy = -1.0 - (WORD)CPlayer::Random(0, 0xf) * 0.05;
                    unk314c[v4] = 1;
                }
                m_objects[v4].vy += 0.045;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].scale = 1;
                    unk314c[v4] = 2;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 2) {
                    RemoveObject(v4);
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
                unk3450 = (int)m_objects[v4].x;
                unk3454 = (int)m_objects[v4].y;
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 1.0;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    l50.type = 0x1a6;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    unk3454 = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -8.5;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].scale = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1a4:
                unk3450 = (int)m_objects[v4].x;
                unk3454 = (int)m_objects[v4].y;
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.4;
                    m_objects[v4].vy = 0.8;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_playSound = 0x16;
                    l50.type = 0x1a9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x + facing * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x - facing * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    unk3454 = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.1;
                    m_objects[v4].vy = -5.5;
                    m_objects[v4].ay = 0.01;
                    m_objects[v4].scale = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1ac:
                unk3450 = (int)m_objects[v4].x;
                unk3454 = (int)m_objects[v4].y;
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.4;
                    m_objects[v4].vy = 0.4;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_playSound = 0x16;
                    l50.type = 0x1aa;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x + facing * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x - facing * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x + facing * 0x28);
                    l50.y = -80.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x - facing * 0x28);
                    l50.y = -80.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    unk3454 = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.1;
                    m_objects[v4].vy = -5.5;
                    m_objects[v4].ay = 0.01;
                    m_objects[v4].scale = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1a7:
                m_objects[v4].x = unk3450;
                m_objects[v4].y = unk3454;
                if (unk3454 == 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1ab:
                if (unk314c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)m_objects[v4].x + (0x14 - (WORD)CPlayer::Random(0, 0x28)) * facing);
                    l50.y = (double)((int)m_objects[v4].y + 0x14 - (WORD)CPlayer::Random(0, 0x28));
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk314c[v4] = 2;
                }
                unk314c[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_playVoice = 0;
                    l50.type = 0x19b;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk314c[v4] < 3) {
                            m_objects[v4].frame = 0;
                            unk314c[v4]++;
                            break;
                        }
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1af:
                unk138 = 2;
                unk13a = 2;
                unk3148--;
                CPlayer::Unk4109d0(1);
                m_defense = 0.5;
                if (unk3148 <= 0) {
                    unk3148 = 0;
                    RemoveObject(v4);
                    unk138 = 0;
                    unk13a = 0;
                    m_defense = 1.0;
                    break;
                }
                if (unk314c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)x + (0x14 - (WORD)CPlayer::Random(0, 0x28)) * facing);
                    l50.y = (double)((int)y - (WORD)CPlayer::Random(0, 0x5a));
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk314c[v4] = 2;
                }
                unk314c[v4]--;
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

void CNanase::Unk497540()
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
                if (unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 0x63;
                    unk314c[v4]++;
                    m_objects[v4].unk80 = 0;
                }
                if (unk324c[v4] >= 0xf) {
                    unk324c[v4] = 0;
                    m_objects[v4].unk80 = 0;
                }
                unk324c[v4]++;
                m_objects[v4].vx = 3.0;
                m_objects[v4].vy = 1.8;
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].y > 0.0) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.8;
                    m_objects[v4].vy = -3.1;
                    m_objects[v4].ay = 0.02;
                    l50.type = 0x192;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    m_playVoice = 2;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x191:
                l50.type = 0x22;
                l50.x = (double)((int)m_objects[v4].x + 0x28 - (WORD)CPlayer::Random(0, 0x50));
                l50.y = (double)((int)m_objects[v4].y + 0x14 - (WORD)CPlayer::Random(0, 0x28));
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                if (unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 0x63;
                    unk314c[v4]++;
                    m_objects[v4].unk80 = 0;
                }
                m_objects[v4].vx = 3.0;
                m_objects[v4].vy = 1.8;
                if (m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].unk80 = 0;
                    }
                }
                break;
            case 0x192:
                if (m_objects[v4].frame == 1) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 0xa) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.unk18 = facing;
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
            case 0x193:
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x194;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = -m_objects[v4].vx;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = -m_objects[v4].vx;
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
                if (m_objects[v4].x - x < 30.0 && m_objects[v4].x - x > -30.0 && m_pressD == 1 && pattern < 3) {
                    RemoveObject(v4);
                    pattern = 0x12b;
                    StartPattern();
                    Unk48e140(0);
                    unk344c = 0;
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
            case 0x195:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].vy = -2.0 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                    RemoveObject(v4);
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
            case 0x196:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 5) * 0.1;
                    m_objects[v4].vy = -2.3 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                    RemoveObject(v4);
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
            case 0x197:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 4) * 0.1;
                    m_objects[v4].vy = -2.5 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_playVoice = 1;
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
            case 0x198:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xd) * 0.1;
                    m_objects[v4].vy = 1.7 - (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].unk84 = 1;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    SpawnObject(&l50);
                    m_playVoice = 1;
                    RemoveObject(v4);
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
            case 0x199:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].vy = -1.0 - (WORD)CPlayer::Random(0, 0xa) * 0.05;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 1) {
                    RemoveObject(v4);
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
            case 0x19a:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].unk84 = 0;
                }
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1;
                    m_objects[v4].vy = -1.0 - (WORD)CPlayer::Random(0, 0xa) * 0.05;
                    unk314c[v4]++;
                }
                m_objects[v4].vy += 0.035;
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 0) {
                    m_objects[v4].vy = -m_objects[v4].vy * 0.5;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].scale = 1;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].scale == 1) {
                    RemoveObject(v4);
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
                if (unk314c[v4] == 0) {
                    m_objects[v4].unk84 = 0x63;
                    unk314c[v4]++;
                    m_objects[v4].unk80 = 0;
                }
                if (unk324c[v4] >= 0xf) {
                    unk324c[v4] = 0;
                    m_objects[v4].unk80 = 0;
                }
                unk324c[v4]++;
                m_objects[v4].vx = 3.0;
                m_objects[v4].vy = 1.8;
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].y > 0.0) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.8;
                    m_objects[v4].vy = -3.1;
                    m_objects[v4].ay = 0.02;
                    l50.type = 0x19e;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    m_playVoice = 2;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case 0x19e:
                m_objects[v4].unk84 = 1;
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0 && m_objects[v4].y > -10.0) {
                    l50.type = 0x19e;
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y - 4.0);
                    l50.unk18 = facing;
                    m_playVoice = 2;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 0xa) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.unk18 = facing;
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
            case 0x1a3:
                unk3450 = (int)m_objects[v4].x;
                unk3454 = (int)m_objects[v4].y;
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 1.2;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_playSound = 0x16;
                    l50.type = 0x1a6;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    unk3454 = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.1;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.01;
                    m_objects[v4].scale = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1a4:
                unk3450 = (int)m_objects[v4].x;
                unk3454 = (int)m_objects[v4].y;
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.4;
                    m_objects[v4].vy = 0.8;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_playSound = 0x16;
                    l50.type = 0x1a9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x + facing * 0x28);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x - facing * 0x28);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    unk3454 = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.1;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.01;
                    m_objects[v4].scale = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1ac:
                unk3450 = (int)m_objects[v4].x;
                unk3454 = (int)m_objects[v4].y;
                if (unk314c[v4] == 0) {
                    m_objects[v4].vx = 2.4;
                    m_objects[v4].vy = 0.4;
                    unk314c[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy + m_objects[v4].y > 0.0 && unk314c[v4] == 1) {
                    m_playSound = 0x16;
                    l50.type = 0x1aa;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x + facing * 0x3c);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x - facing * 0x3c);
                    l50.y = 15.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x + facing * 0x1e);
                    l50.y = -30.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(m_objects[v4].x - facing * 0x1e);
                    l50.y = -30.0;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    unk3454 = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a8;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.1;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.01;
                    m_objects[v4].scale = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1a5:
                if (m_objects[v4].frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 0xa) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.unk18 = facing;
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
            case 0x1a6:
                if (m_objects[v4].frame == 1) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.unk18 = facing;
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
            case 0x1a9:
                if (m_objects[v4].frame == 1) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.unk18 = facing;
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
            case 0x1aa:
                if (m_objects[v4].frame == 1) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame < 0xc && (WORD)CPlayer::Random(0, 0x64) < 0x14) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(m_objects[v4].x - 50.0 + (WORD)CPlayer::Random(0, 0x64));
                    l50.y = (double)(int)(m_objects[v4].y - (WORD)CPlayer::Random(0, 0x64));
                    l50.scale = 2;
                    l50.unk18 = facing;
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
            case 0x1a7:
                m_objects[v4].x = unk3450;
                m_objects[v4].y = unk3454;
                l50.type = 0x22;
                l50.x = (double)((int)m_objects[v4].x + 0x28 - (WORD)CPlayer::Random(0, 0x50));
                l50.y = (double)((int)m_objects[v4].y + 0x14 - (WORD)CPlayer::Random(0, 0x28));
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                if (unk3454 == 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5) {
                        m_objects[v4].unk84 = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case 0x1a8:
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x194;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].x = 620.0;
                    m_objects[v4].vx = -m_objects[v4].vx;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].x = 20.0;
                    m_objects[v4].vx = -m_objects[v4].vx;
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
                if (unk314c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)m_objects[v4].x + (0x14 - (WORD)CPlayer::Random(0, 0x28)) * facing);
                    l50.y = (double)((int)m_objects[v4].y + 0x14 - (WORD)CPlayer::Random(0, 0x28));
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk314c[v4] = 2;
                }
                unk314c[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_playVoice = 0;
                    l50.type = 0x19b;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 1) + 0x199;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                    l50.type = (WORD)CPlayer::Random(0, 4) + 0x195;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * (0x28 - (WORD)CPlayer::Random(0, 0x46)));
                    l50.y = (double)(int)m_objects[v4].y;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (unk314c[v4] < 3) {
                            m_objects[v4].frame = 0;
                            unk314c[v4]++;
                            break;
                        }
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1af:
                unk138 = 2;
                unk13a = 2;
                unk3148--;
                CPlayer::Unk4109d0(1);
                m_defense = 0.5;
                if (unk3148 <= 0) {
                    m_defense = 1.0;
                    unk3148 = 0;
                    RemoveObject(v4);
                    unk138 = 0;
                    unk13a = 0;
                    break;
                }
                if (unk314c[v4] <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)x + (0x14 - (WORD)CPlayer::Random(0, 0x28)) * facing);
                    l50.y = (double)((int)y - (WORD)CPlayer::Random(0, 0x5a));
                    l50.scale = 2;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    unk314c[v4] = 2;
                }
                unk314c[v4]--;
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
