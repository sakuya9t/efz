// CMinagi (0x5a9fa0-0x5c857f): the character class whose files are in minagi\ in the game
// folder (minagi.dat sprites, minagi.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMinagi::CMinagi(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "minagi");
    lastSurface = 0x2b4;
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk2ad0[0] = -8;
    unk2af8[0] = -0x42;
    unk2ad0[1] = -0x13;
    unk2af8[1] = 0;
    unk2ad0[2] = 3;
    unk2af8[2] = -7;
    unk2ad0[3] = 9;
    unk2af8[3] = -2;
    unk2ad0[4] = 0x23;
    unk2af8[4] = -0x25;
    unk30f4 = 8;
    unk30f5[0] = 1;
    unk30f5[1] = 0;
    unk30f5[2] = 0xb;
    unk30f5[3] = 0x18;
    unk30f5[4] = 2;
    unk30f5[5] = 0x13;
    unk30f5[6] = 0x17;
    unk30f5[0xa] = 7;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3154[v4] = 0;
        unk3254[v4] = 0;
        unk3354[v4] = 0;
    }
}

void CMinagi::Reset()
{
    int l4c;

    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3144 = 0;
    unk3148 = 0;
    unk314c = 0;
    unk3150 = 0;
    unk2ad0[0] = -0xd;
    unk2af8[0] = -0x3c;
    unk2ad0[1] = 0xe;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x11;
    unk2af8[2] = -6;
    unk2ad0[3] = 7;
    unk2af8[3] = -0x19;
    unk2ad0[4] = 0x1b;
    unk2af8[4] = -0x19;
    l4c = 0;
    for (; l4c < 0x40; l4c++) {
        unk3154[l4c] = 0;
        unk3254[l4c] = 0;
        unk3354[l4c] = 0;
    }
    CPlayer::Reset();
    EffectDesc l48;
    CPlayer::InitEffectDesc((EffectDesc*)&l48);
    l48.type = 0x190;
    l48.x = (double)((int)x - facing * 0x28);
    l48.y = (double)(int)y;
    l48.scale = 0;
    l48.screen = 0;
    l48.layer = 0;
    l48.unk28 = 1;
    l48.unk0 = 1;
    l48.unk18 = facing;
    SpawnObject(&l48);
}

void CMinagi::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    CPlayer::StartPattern();
}

void CMinagi::RemoveObject(short p1)
{
    unk3154[p1] = 0;
    unk3254[p1] = 0;
    unk3354[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CMinagi::Move()
{
    CPlayer::Unk40e740();
}

void CMinagi::StartCommand()
{
    if (pattern < 0xc8) {
        m_bufferedPress = 0;
    }
    if (m_dashBufferTime <= 0) {
        m_dashBufferedPress = 0;
    } else {
        m_dashBufferTime--;
    }
    if (m_dashBufferedPress == 0) {
        m_dashBufferTime = 0;
    }
    if (m_command == 0x34 && (unk118 >= 500.0 || unk120 > 0) && m_attackResult > 1 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
        StartPattern();
        CPlayer::ClearBufferedPress();
        pattern = 0xa7;
        if (y < 0.0) {
            pattern = 0xab;
        }
        return;
    }
    if (unk15c < 2) {
        if (m_hp < 0xd05 && unk3148 != 4 && m_command == 0x5c && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x13b;
            return;
        }
        if (m_command == 0xac && y == 0.0 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x13a;
            return;
        }
        if (y == 0.0 && (m_command == 0xab || m_command == 0xac) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x139;
            return;
        }
        if (y == 0.0 && (m_command == 0xaa || m_command == 0xab || m_command == 0xac) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x138].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x138;
            return;
        }
        if (unk3148 != 4 && m_command == 0x70 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x131;
            if (y < 0.0) {
                pattern = 0x137;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x130].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x130;
            if (y < 0.0) {
                pattern = 0x136;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0x6e || m_command == 0x6f || m_command == 0x70) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x12f;
            if (y < 0.0) {
                pattern = 0x135;
            }
            return;
        }
        if (unk3148 != 4 && m_command == 0x66 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12e].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x12e;
            if (y < 0.0) {
                pattern = 0x134;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12d].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x12d;
            if (y < 0.0) {
                pattern = 0x133;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0x64 || m_command == 0x65 || m_command == 0x66) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12c].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x12c;
            if (y < 0.0) {
                pattern = 0x132;
            }
            return;
        }
        if (m_command == 0x52 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x108].unk0 && unk314c == 0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x108;
            return;
        }
        if ((m_command == 0x51 || m_command == 0x52) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x107].unk0 && unk314c == 0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x107;
            return;
        }
        if (m_command == 0x50 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x106].unk0 && unk314c == 0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x106;
            return;
        }
        if (unk3148 != 4 && m_command == 0x20 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x105].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x105;
            if (y < 0.0) {
                pattern = 0x112;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0x1f || m_command == 0x20) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x104].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x104;
            if (y < 0.0) {
                pattern = 0x111;
            }
            return;
        }
        if (unk3148 != 4 && m_command == 0x1e && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x103].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x103;
            if (y < 0.0) {
                pattern = 0x110;
            }
            return;
        }
        if (unk3148 != 4 && y == 0.0 && m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x115].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x115;
            return;
        }
        if (unk3148 != 4 && y == 0.0 && (m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x114].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x114;
            return;
        }
        if (unk3148 != 4 && y == 0.0 && m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x113].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x113;
            return;
        }
        if (unk3148 != 4 && m_command == 0x48 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x102;
            if (y < 0.0) {
                pattern = 0x10f;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0x47 || m_command == 0x48) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x101;
            if (y < 0.0) {
                pattern = 0x10e;
            }
            return;
        }
        if (unk3148 != 4 && m_command == 0x46 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0x100;
            if (y < 0.0) {
                pattern = 0x10d;
            }
            return;
        }
        if (unk3148 != 4 && m_command == 0xc && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xff;
            if (y < 0.0) {
                pattern = 0x10b;
            }
            return;
        }
        if (unk3148 != 4 && (m_command == 0xb || m_command == 0xc) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xfe;
            if (y < 0.0) {
                pattern = 0x10a;
            }
            return;
        }
        if (unk3148 != 4 && m_command == 0xa && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xfd;
            if (y < 0.0) {
                pattern = 0x109;
            }
            return;
        }
    }
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].unk2 <= m_patterns[0xa5].unk0 && pattern != 0xaa && y < -30.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && pattern != 0xfd) {
                if (pattern != 0xa5) {
                    StartPattern();
                }
                pattern = 0xa5;
                CPlayer::FaceOpponent();
                unk159++;
                unk15a++;
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && pattern != 0xaa && m_patterns[pattern].unk2 <= m_patterns[0xa6].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa6) {
                    StartPattern();
                }
                pattern = 0xa6;
                CPlayer::FaceOpponent();
                unk159++;
                unk15a++;
                m_bufferedPress = 0;
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
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].unk2 <= m_patterns[0xa4].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                if (pattern != 0xa4) {
                    StartPattern();
                }
                pattern = 0xa4;
                CPlayer::FaceOpponent();
                unk158++;
                m_bufferedPress = 0;
                return;
            }
        }
    }
    if (unk15c < 3 && m_command == 6 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y < 0.0 && unk15a < 1 && m_patterns[pattern].unk2 <= m_patterns[0xe].unk0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
        StartPattern();
        CPlayer::ClearBufferedPress();
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
    if (m_pressA == 1 || (m_bufferedPress & 0x10) != 0 || (m_dashBufferedPress & 0x10) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xe6;
            if (m_inputY == 1) {
                pattern = 0xe9;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xcf].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xcf;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcc].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xcc;
            return;
        }
        if ((m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) && m_patterns[pattern].unk2 <= m_patterns[0xc8].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xc8;
            return;
        }
    }
    if (m_pressB == 1 || (m_bufferedPress & 0x20) != 0 || (m_dashBufferedPress & 0x20) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xe7;
            if (m_inputY == 1) {
                pattern = 0xea;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xd0].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xd0;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xcd].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xcd;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if (m_patterns[pattern].unk2 <= m_patterns[0xc9].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && x - (*m_opponent)->x > -50.0 && x - (*m_opponent)->x < 50.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xc9;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xca].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xca;
                return;
            }
        }
    }
    if (m_pressC == 1 || (m_bufferedPress & 0x40) != 0 || (m_dashBufferedPress & 0x40) != 0) {
        if (pattern == 0xa3 && m_inputX != -facing) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xe8;
            if (m_inputY == 1) {
                pattern = 0xeb;
            }
            return;
        }
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].unk2 <= m_patterns[0xf8].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xf8;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xd1].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xd1;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xce].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xce;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if ((*m_opponent)->y == 0.0 && m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xdc;
                return;
            }
            if (m_patterns[pattern].unk2 <= m_patterns[0xcb].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
                StartPattern();
                CPlayer::ClearBufferedPress();
                pattern = 0xcb;
                return;
            }
        }
    }
    if (unk15c < 2 && (m_pressD == 1 || (m_bufferedPress & 0x80) != 0 || (m_dashBufferedPress & 0x80) != 0) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
        if ((unk3148 == 0 || unk3148 == 2 || unk3148 == 3) && m_inputX == 0) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xfa;
            return;
        }
        if (unk3148 == 0 && m_inputX == 1) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xfb;
            return;
        }
        if (unk3148 == 0 && m_inputX == -1) {
            StartPattern();
            CPlayer::ClearBufferedPress();
            pattern = 0xfc;
        }
    }
}

void CMinagi::DrawGauge()
{
}

void CMinagi::Vf8()
{
}

void CMinagi::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CMinagi::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 6) {
            m_command = 0x5c;
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
        if ((v5 & 0xf) == 0 && x6 == 0 && m_gauge == 0xbb8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
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
    v4 = m_inputPos + 0x6e;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4 && y == 0.0) {
            m_command = ((v5 & 0xe0) > 0) + 0x50 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            if ((v5 & 0xf0) != 0 && y == 0.0) {
                m_command = ((v5 & 0xe0) > 0) + 0x50 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
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
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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

void CMinagi::CpuInput()
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
    if (pattern == 0xa8 && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 45.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == 0xa8 || pattern == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 4.0f && unk118 > 500.0) {
                m_command = 0x20;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 2 && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5c;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && v10 < 80.0 && m_gauge >= 0x7d0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x65;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 3.0f && unk118 > 500.0) {
                m_command = 0xc;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && m_gauge == 0xbb8 && (*m_opponent)->pattern < 0xdc) {
                m_command = 0x5c;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)CPlayer::Random(0, 0x64) < unka8 * 1.0f && unk118 > 500.0) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1e;
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
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 80.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Random(0, 0x64) < unka8 * 2) {
            m_command = (WORD)CPlayer::Random(0, 2) + 0x1f;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x64);
        if (m_cpuRoll < 3 && unk118 > 500.0) {
            m_command = 0x20;
            return;
        }
        if (m_cpuRoll < 5 && unk118 > 500.0) {
            m_command = 0xc;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)CPlayer::Random(0, 3) + 0x64;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x14 && m_gauge == 0xbb8) {
            m_command = 0x5c;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == 0xa8 || (*m_opponent)->pattern == 0xa9 || (*m_opponent)->pattern == 0xaa) && y < 0.0 && (WORD)CPlayer::Random(0, 0x64) < 15.0f * unka8 && m_cpuAction != 2 && (*m_opponent)->unk14c == 0) {
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x64);
        if (m_cpuRoll < 2 && unk118 > 500.0) {
            m_command = 0x20;
            return;
        }
        if (m_cpuRoll > 0x3a) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((unk118 > 500.0 || unk120 > 0) && (WORD)CPlayer::Random(0, 0x64) < 8.0f * unka8 && (*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9d && (pattern == 0xfb || pattern == 0xe8 && (WORD)CPlayer::Random(0, 0xa) == 0 || pattern == 0xfa && (WORD)CPlayer::Random(0, 0x64) < 2 || pattern == 0xeb && (WORD)CPlayer::Random(0, 7) == 0)) {
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
        m_pressB = 1;
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
        m_pressC = 1;
        if (pattern == 0xe8) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0xd;
        }
        return;
    }
    if (m_cpuAction == 0xd && pattern == 0xa3) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == 0xe6) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xe && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0xf;
        }
        return;
    }
    if (m_cpuAction == 0xf && pattern == 0xa3) {
        m_pressB = 1;
        m_inputY = 1;
        if (pattern == 0xe7) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0x10 && pattern < 0x32) {
        m_command = facing == 1;
        if (pattern == 0xa3) {
            m_cpuAction = 0x11;
        }
        return;
    }
    if (m_cpuAction == 0x11 && pattern == 0xa3) {
        m_pressC = 1;
        m_inputY = 1;
        if (pattern == 0xe8) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0x14 && pattern < 0x32) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == 0xcc) {
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
            if ((*m_opponent)->y < 0.0 && v10 < 90.0 && m_cpuRoll < 0x258 && m_cpuRoll > 0x12c) {
                m_cpuAction = 6;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xc9) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x14;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x226 && m_cpuRoll < 0x258 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x64;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && v10 < 80.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xca) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0xc8 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x64;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x190) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                return;
            }
        }
        if (pattern == 0xcb) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x1e;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x12c && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && unk118 > 500.0) {
                m_command = 0x1f;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == 0xcc) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && v10 < 90.0 && m_cpuRoll < 0x258 && m_cpuRoll > 0x12c) {
                m_cpuAction = 6;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xcd) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = 0x1f;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x226 && m_cpuRoll < 0x258 && m_gauge >= 0x3e8) {
                m_command = (WORD)CPlayer::Random(0, 3) + 0x64;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x15e && m_cpuRoll < 0x226 && v10 < 90.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x276 && m_attackResult == 2) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)CPlayer::Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xce) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x258) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x258 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x320) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x320 && m_cpuRoll < 0x352 && unk118 > 500.0) {
                m_command = 0x1f;
                return;
            }
            if (m_cpuRoll > 0x384) {
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
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = 0xa;
                return;
            }
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
            if (m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)CPlayer::Random(0, 2) + 0x1f;
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
        if (pattern == 0xe7) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x190 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && unk118 > 500.0) {
                m_command = 0x1f;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xfa && m_cpuRoll > 0x258 && y == 0.0) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == 0xe9 && m_cpuRoll > 0x1f4) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == 0xea) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_attackResult == 3) {
                m_command = 0x14;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_command = 0xa;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x190 && unk118 > 350.0) {
                m_command = 0x34;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_command = 0x1e;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && unk118 > 500.0) {
                m_command = 0x1f;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)CPlayer::Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == 0xeb && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
            m_command = 0x1e;
            return;
        }
    }
    if ((WORD)CPlayer::Random(0, 0x64) < 25.0f * unka8) {
        m_cpuRoll = (WORD)CPlayer::Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != 0x63) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 50.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0xf) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 65.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 60.0 && v10 < 90.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x23 && m_cpuRoll > 0x1e) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 2 + 0x54 && m_cpuRoll > 0x50) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x46 < v10 && v10 < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x80 && m_cpuRoll > 0x78) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (v10 < 150.0 && v10 > 120.0 && m_cpuRoll < 0x7e && m_cpuRoll > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && m_cpuRoll < 0x91 && m_cpuRoll > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (0x50 - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x50 < v10 && v10 < 130.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0x9b && m_cpuRoll > 0x91) {
                        m_cpuAction = 0xe;
                        return;
                    }
                }
                if (0x5a - ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0x5a < v10 && v10 < 140.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c) * 0xf + 0xb4 && m_cpuRoll > 0xa5) {
                        m_cpuAction = 0xa;
                        return;
                    }
                }
                if (v10 > 110.0 && v10 < 160.0 && m_cpuRoll < 0xcd && m_cpuRoll > 0xc8) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xeb && m_cpuRoll > 0xdc && unk118 > 500.0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x20;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xf0 && m_cpuRoll > 0xeb && m_gauge >= 0x7d0 && (*m_opponent)->pattern > 0xc7) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x65;
                    return;
                }
                if (v10 < 100.0 && m_cpuRoll < 0xf2 && m_cpuRoll > 0xf0 && m_gauge == 0xbb8 && (*m_opponent)->pattern > 0xc7) {
                    m_command = 0x5c;
                    return;
                }
                if (v10 > 100.0 && v10 < 130.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c) {
                    m_command = 0xa;
                    return;
                }
                if (v10 > 130.0 && v10 < 180.0 && m_cpuRoll < 0x13b && m_cpuRoll > 0x136) {
                    m_command = 0xb;
                    return;
                }
                if (v10 > 90.0 && v10 < 140.0 && m_cpuRoll < 0x14a && m_cpuRoll > 0x140) {
                    m_command = 0x1e;
                    return;
                }
                if (v10 > 90.0 && v10 < 140.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x14a && unk118 > 500.0) {
                    m_command = 0x1f;
                    return;
                }
                if (m_cpuRoll < 0x2ee && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x9c && v10 > 100.0) {
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0 && v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 6 && (unk118 > 500.0 || unk120 > 0)) {
                        m_command = 0x16;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 140.0 && x8 > 100.0 && m_cpuRoll < 0x2d && m_cpuRoll > 0xa) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 170.0 && x8 > 150.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x2d) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 120.0 && v10 < 140.0 && x8 < 150.0 && x8 > 120.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x50) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 70.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xc8 && (*m_opponent)->y < -50.0 && x8 < 90.0 && m_gauge >= 0x7d0) {
                        m_command = (WORD)CPlayer::Random(0, 2) + 0x65;
                        return;
                    }
                    if (v10 < 100.0 && m_cpuRoll < 0x12e && m_cpuRoll > 0x12c && (*m_opponent)->y < -50.0 && x8 < 100.0 && m_gauge == 0xbb8) {
                        m_command = 0x5c;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x64 && m_cpuRoll < 0xb4) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 0.0 && x8 < 70.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
                    m_pressC = 1;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0xf2 && x8 > 80.0) {
                    m_command = (WORD)CPlayer::Random(0, 3) + 0x6e;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 90.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 0.0 && x8 < 50.0 && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < 0x32 && ((*m_opponent)->pattern > 0x95 && (*m_opponent)->pattern < 0x9c || (*m_opponent)->pattern > 0x31 && (*m_opponent)->pattern < 0x3b) && y == 0.0 && (WORD)CPlayer::Random(0, 0x64) < 4.0f * unka8 && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < 0x32 && (*m_opponent)->pattern < 0x32 && v10 > 800.0 && v10 < 120.0 && (WORD)CPlayer::Random(0, 0x64) < 2.0f * unka8 && x > 150.0 && x < 490.0) {
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

void CMinagi::UpdateObjects()
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
                unk3154[v4] = 0;
                m_objects[v4].unk84 = 0;
                if (m_objects[v4].x > (*m_opponent)->x) {
                    m_objects[v4].facing = -1;
                } else {
                    m_objects[v4].facing = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                unk3148 = 0;
                if (pattern == 0xfa && frame == 0) {
                    unk3148 = 1;
                    m_objects[v4].pattern = 0x191;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0xfb || pattern == 0xfc) {
                    unk3148 = 2;
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0xfd && frame == 2 || pattern == 0x109 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x194;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0xfe && frame == 2 || pattern == 0x10a && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x195;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0xff && frame == 2 || pattern == 0x10b && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x196;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x100 && frame == 2 || pattern == 0x10d && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x197;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x101 && frame == 2 || pattern == 0x10e && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x198;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x102 && frame == 2 || pattern == 0x10f && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x199;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x103 && frame == 2 || pattern == 0x110 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19a;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x104 && frame == 2 || pattern == 0x111 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19b;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x105 && frame == 2 || pattern == 0x112 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19c;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x113 && frame == 2) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1d2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x114 && frame == 2) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1d3;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x115 && frame == 2) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1d4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12c && frame == 2 || pattern == 0x132 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c6;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12d && frame == 2 || pattern == 0x133 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c7;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12e && frame == 2 || pattern == 0x134 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c8;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12f && frame == 2 || pattern == 0x135 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x130 && frame == 2 || pattern == 0x136 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x131 && frame == 2 || pattern == 0x137 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if ((pattern == 0x138 || pattern == 0x139 || pattern == 0x13a) && frame == 2) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1b5;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13b && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1be;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13c && frame == 2 || pattern == 0x13f && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c6;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13d && frame == 2 || pattern == 0x140 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c7;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13e && frame == 2 || pattern == 0x141 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c8;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x7b) {
                    unk3148 = 4;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].pattern = 0x1d5;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (x - m_objects[v4].x > 300.0 || x - m_objects[v4].x < -300.0) {
                    unk3148 = 2;
                    m_objects[v4].pattern = 0x1b4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    if (x > m_objects[v4].x) {
                        m_objects[v4].facing = 1;
                    }
                    if (x <= m_objects[v4].x) {
                        m_objects[v4].facing = -1;
                    }
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
                unk3154[v4] = 0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].vx = 0.0;
                m_objects[v4].unk84 = 0;
                if (m_objects[v4].x > (*m_opponent)->x) {
                    m_objects[v4].facing = -1;
                } else {
                    m_objects[v4].facing = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                unk3148 = 1;
                if (m_objects[v4].frame >= 8 && m_objects[v4].frame < 0x11) {
                    unk3148 = 3;
                    if (pattern == 0xfa && frame == 0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x11;
                        break;
                    }
                    if (pattern == 0xfd && frame == 2 || pattern == 0x109 && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1a6;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0xfe && frame == 2 || pattern == 0x10a && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1a7;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0xff && frame == 2 || pattern == 0x10b && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1a8;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x100 && frame == 2 || pattern == 0x10d && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x197;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x101 && frame == 2 || pattern == 0x10e && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x198;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x102 && frame == 2 || pattern == 0x10f && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x199;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x103 && frame == 2 || pattern == 0x110 && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1aa;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x104 && frame == 2 || pattern == 0x111 && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1ab;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x105 && frame == 2 || pattern == 0x112 && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1ac;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x113 && frame == 2) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1d2;
                        m_objects[v4].frame = 9;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x114 && frame == 2) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1d3;
                        m_objects[v4].frame = 9;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x115 && frame == 2) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1d4;
                        m_objects[v4].frame = 9;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x12c && frame == 2 || pattern == 0x132 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1c6;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x12d && frame == 2 || pattern == 0x133 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1c7;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x12e && frame == 2 || pattern == 0x134 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1c8;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x12f && frame == 2 || pattern == 0x135 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1a1;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x130 && frame == 2 || pattern == 0x136 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1a3;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x131 && frame == 2 || pattern == 0x137 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1a5;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if ((pattern == 0x138 || pattern == 0x139 || pattern == 0x13a) && frame == 2) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1b5;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x13b && frame == 3) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1be;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x13c && frame == 2 || pattern == 0x13f && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1c9;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x13d && frame == 2 || pattern == 0x140 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1ca;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x13e && frame == 2 || pattern == 0x141 && frame == 1) {
                        unk3148 = 4;
                        m_objects[v4].pattern = 0x1cb;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == 0x7b) {
                        unk3148 = 4;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].ay = 0.0;
                        m_objects[v4].pattern = 0x1d5;
                        m_objects[v4].frame = 0xb;
                        m_objects[v4].timer = 0;
                        break;
                    }
                }
                if (pattern == 0xfb || pattern == 0xfc) {
                    unk3148 = 1;
                    m_objects[v4].pattern = 0x192;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x11) {
                        m_objects[v4].frame = 8;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = 0x190;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x192:
                unk3148 = 2;
                m_objects[v4].unk84 = 0;
                if (m_objects[v4].frame < 0xb) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame > 0xa) {
                    if (m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx -= 0.035;
                    }
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (pattern == 0xfd && frame == 2 || pattern == 0x109 && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x194;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0xfe && frame == 2 || pattern == 0x10a && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x195;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0xff && frame == 2 || pattern == 0x10b && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x196;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x100 && frame == 2 || pattern == 0x10d && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x197;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x101 && frame == 2 || pattern == 0x10e && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x198;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x102 && frame == 2 || pattern == 0x10f && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x199;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x103 && frame == 2 || pattern == 0x110 && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19a;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x104 && frame == 2 || pattern == 0x111 && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19b;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x105 && frame == 2 || pattern == 0x112 && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19c;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x113 && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1d2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x114 && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1d3;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x115 && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1d4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x12c && frame == 2 || pattern == 0x132 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c6;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x12d && frame == 2 || pattern == 0x133 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c7;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x12e && frame == 2 || pattern == 0x134 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c8;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x12f && frame == 2 || pattern == 0x135 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x130 && frame == 2 || pattern == 0x136 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x131 && frame == 2 || pattern == 0x137 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if ((pattern == 0x138 || pattern == 0x139 || pattern == 0x13a) && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1b5;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x13b && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1be;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x13c && frame == 2 || pattern == 0x13f && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c6;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x13d && frame == 2 || pattern == 0x140 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c7;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x13e && frame == 2 || pattern == 0x141 && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c8;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (pattern == 0x7b) {
                    unk3148 = 4;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].pattern = 0x1d5;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (unk3154[v4] == 0) {
                    unk3154[v4] = 1;
                    if (pattern == 0xfb) {
                        m_objects[v4].facing = 1;
                    }
                    if (pattern == 0xfc) {
                        m_objects[v4].facing = -1;
                    }
                    break;
                }
                if (pattern == 0xfa) {
                    unk3148 = 1;
                    m_objects[v4].pattern = 0x191;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb && unk3154[v4] < 0) {
                        m_objects[v4].frame = 0;
                        unk3154[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = 0x190;
                        unk3154[v4] = 0;
                    }
                }
                break;
            case 0x193:
                unk3148 = 4;
                m_objects[v4].unk88 = 0;
                unk3154[v4] = 0;
                unk3254[v4] = 0;
                unk3354[v4] = 0;
                if (pattern == 0x7b) {
                    unk3148 = 4;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].pattern = 0x1d5;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 7) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 7;
                        CPlayer::ShakeScreen(3, 0);
                        l50.type = 3;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 0;
                        m_game->CreateEffect((EffectDesc*)&l50);
                        m_playSound = 7;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x194:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.9;
                    m_objects[v4].vy = -1.1;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].unk80 > 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a9;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x195:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].unk80 > 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a9;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x196:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].unk84 = 5;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].unk80 > 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1a9;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x197:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.2;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 9) {
                    if ((*m_opponent)->y < 0.0) {
                        m_objects[v4].unk84 = 1;
                    } else {
                        m_objects[v4].unk84 = 0;
                    }
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                    }
                }
                if (m_objects[v4].frame == 0x12 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0x17 && m_objects[v4].frame > 0x12) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x198:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 9) {
                    if ((*m_opponent)->y < 0.0) {
                        m_objects[v4].unk84 = 1;
                    } else {
                        m_objects[v4].unk84 = 0;
                    }
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                    }
                }
                if (m_objects[v4].frame == 0x12 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0x17 && m_objects[v4].frame > 0x12) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x199:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk84 = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.3;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.045;
                }
                if (m_objects[v4].frame == 9) {
                    if ((*m_opponent)->y < 0.0) {
                        m_objects[v4].unk84 = 1;
                    } else {
                        m_objects[v4].unk84 = 0;
                    }
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].vx > 0.0 && m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].frame < 0x11) {
                    m_objects[v4].vx -= 0.02;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        m_objects[v4].unk80 = 0;
                    }
                }
                if (m_objects[v4].frame == 0x12 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0x17 && m_objects[v4].frame > 0x12) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                        m_objects[v4].unk80 = 0;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19a:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    unk3154[v4] = 0;
                    unk3254[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].unk84 = 4;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19b:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    unk3154[v4] = 0;
                    unk3254[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -2.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].unk84 = 6;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19c:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    unk3154[v4] = 0;
                    unk3254[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].unk84 = 0xc;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.15) {
                        m_objects[v4].vy = 0.15;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19d:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12c && pattern != 0x132) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x14;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk84 = 0x63;
                        unk3254[v4] = 0;
                        unk3154[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && unk3254[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.2;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3154[v4] < 2) {
                        unk3154[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x14) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19e:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x14) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12d && pattern != 0x133) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk84 = 0x63;
                        unk3254[v4] = 0;
                        unk3154[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && unk3254[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3154[v4] < 3) {
                        unk3154[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x19f:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x17) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                    m_game->Unk4080c0(0xf);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12e && pattern != 0x134) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x1a;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk84 = 0x63;
                        unk3254[v4] = 0;
                        unk3154[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && unk3254[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3154[v4] < 4) {
                        unk3154[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x1a) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a0:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4] = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].unk80 == 3 && unk3154[v4] == 0) {
                    (*m_opponent)->unk14a = 0x2d;
                    m_objects[v4].unk86 = 0x2d;
                    unk3154[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a1:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame > 1 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].x - (*m_opponent)->x < 50.0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 6;
                    }
                    m_objects[v4].vx = 2.2;
                }
                if (m_objects[v4].frame > 5) {
                    m_objects[v4].vx -= 0.1;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4] = 0;
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].unk80 == 3 && unk3154[v4] == 0) {
                    (*m_opponent)->unk14a = 0x5a;
                    m_objects[v4].unk86 = 0x5a;
                    unk3154[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 6 && unk3254[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                        unk3254[v4] = 0;
                    }
                }
                break;
            case 0x1a2:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4] = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].unk80 == 3 && unk3154[v4] == 0) {
                    (*m_opponent)->unk14a = 0x4b;
                    m_objects[v4].unk86 = 0x4b;
                    unk3154[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a3:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame > 1 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].x - (*m_opponent)->x < 50.0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 6;
                    }
                    m_objects[v4].vx = 2.2;
                }
                if (m_objects[v4].frame > 5) {
                    m_objects[v4].vx -= 0.1;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4] = 0;
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].unk80 == 3 && unk3154[v4] == 0) {
                    (*m_opponent)->unk14a = 0x96;
                    m_objects[v4].unk86 = 0x96;
                    unk3154[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 6 && unk3254[v4] < 4) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                        unk3254[v4] = 0;
                    }
                }
                break;
            case 0x1a4:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                }
                m_game->Unk4080c0(0xf);
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4] = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].unk80 == 3 && unk3154[v4] == 0) {
                    (*m_opponent)->unk14a = 0x64;
                    m_objects[v4].unk86 = 0x64;
                    unk3154[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a5:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3154[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame > 1 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].x - (*m_opponent)->x < 50.0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 6;
                    }
                    m_objects[v4].vx = 2.2;
                }
                if (m_objects[v4].frame > 5) {
                    m_objects[v4].vx -= 0.1;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    unk3154[v4] = 0;
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].unk80 == 3 && unk3154[v4] == 0) {
                    (*m_opponent)->unk14a = 0xc8;
                    m_objects[v4].unk86 = 0xc8;
                    unk3154[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 6 && unk3254[v4] < 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                        unk3254[v4] = 0;
                    }
                }
                break;
            case 0x1a6:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.9;
                    m_objects[v4].vy = -1.1;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a7:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a8:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].unk84 = 5;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1a9:
                unk3148 = 4;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.025;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                    }
                }
                break;
            case 0x1aa:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    unk3154[v4] = 0;
                    unk3254[v4] = 0;
                }
                if (m_objects[v4].y < 0.0) {
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx = m_objects[v4].facing * 0.5;
                    } else {
                        m_objects[v4].vx = m_objects[v4].facing * -0.5;
                    }
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].unk84 = 4;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1ab:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    unk3154[v4] = 0;
                    unk3254[v4] = 0;
                }
                if (m_objects[v4].y < 0.0) {
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx = m_objects[v4].facing * 0.5;
                    } else {
                        m_objects[v4].vx = m_objects[v4].facing * -0.5;
                    }
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -2.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].unk84 = 6;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1ac:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    unk3154[v4] = 0;
                    unk3254[v4] = 0;
                }
                if (m_objects[v4].y < 0.0) {
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx = m_objects[v4].facing * 0.5;
                    } else {
                        m_objects[v4].vx = m_objects[v4].facing * -0.5;
                    }
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && unk3154[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].unk84 = 0xc;
                    unk3154[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.15) {
                        m_objects[v4].vy = 0.15;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1ad:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = 1.7;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                if (m_objects[v4].unk80 > 0 && unk3154[v4] == 0 && m_objects[v4].scale == 0) {
                    m_objects[v4].scale = 1;
                    unk3154[v4] = 0x1e;
                }
                if (m_objects[v4].scale == 1) {
                    unk3154[v4]--;
                    if (unk3154[v4] < 0) {
                        RemoveObject(v4);
                        unk314c = 0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3354[v4] > 0) {
                            RemoveObject(v4);
                            unk314c = 0;
                        } else {
                            unk3354[v4]++;
                        }
                    }
                }
                break;
            case 0x1ae:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = 2.1;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                if (m_objects[v4].unk80 > 0 && unk3154[v4] == 0 && m_objects[v4].scale == 0) {
                    m_objects[v4].scale = 1;
                    unk3154[v4] = 0x1e;
                }
                if (m_objects[v4].scale == 1) {
                    unk3154[v4]--;
                    if (unk3154[v4] < 0) {
                        RemoveObject(v4);
                        unk314c = 0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3354[v4] > 1) {
                            RemoveObject(v4);
                            unk314c = 0;
                        } else {
                            unk3354[v4]++;
                        }
                    }
                }
                break;
            case 0x1af:
                unk3150 = (int)m_objects[v4].x;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 2;
                    unk3254[v4]++;
                    m_objects[v4].vx = 2.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.6) {
                        m_objects[v4].vx = 0.6;
                    }
                }
                if (m_objects[v4].unk84 == 0 && unk3154[v4] == 0 && m_objects[v4].scale == 0) {
                    unk314c = 2;
                    m_objects[v4].scale = 1;
                    unk3154[v4] = 0x1e;
                }
                if (m_objects[v4].scale == 1) {
                    unk3154[v4]--;
                    if (unk3154[v4] < 0) {
                        RemoveObject(v4);
                        unk314c = 0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 0xc) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (unk3354[v4] > 2) {
                            RemoveObject(v4);
                            unk314c = 0;
                        } else {
                            unk3354[v4]++;
                        }
                    }
                }
                break;
            case 0x1b0:
                m_objects[v4].x = unk3150;
                if ((unk314c == 2 || unk314c == 0) && m_objects[v4].frame < 0x18) {
                    m_objects[v4].frame = 0x18;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x18) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1b4:
                unk3148 = 2;
                m_objects[v4].unk84 = 0;
                if (m_objects[v4].frame < 0xa) {
                    m_objects[v4].vx = 1.5;
                }
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (m_objects[v4].frame > 9) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (pattern == 0xfa && frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].pattern = 0x190;
                    break;
                }
                if (pattern == 0xfd && frame == 2 || pattern == 0x109 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x194;
                    m_objects[v4].frame = 8;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0xfe && frame == 2 || pattern == 0x10a && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x195;
                    m_objects[v4].frame = 8;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0xff && frame == 2 || pattern == 0x10b && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x196;
                    m_objects[v4].frame = 8;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x100 && frame == 2 || pattern == 0x10d && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x197;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x101 && frame == 2 || pattern == 0x10e && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x198;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x102 && frame == 2 || pattern == 0x10f && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x199;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x103 && frame == 2 || pattern == 0x110 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19a;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x104 && frame == 2 || pattern == 0x111 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19b;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x105 && frame == 2 || pattern == 0x112 && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x19c;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12c && frame == 2 || pattern == 0x132 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c6;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12d && frame == 2 || pattern == 0x133 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c7;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12e && frame == 2 || pattern == 0x134 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c8;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x12f && frame == 2 || pattern == 0x135 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x130 && frame == 2 || pattern == 0x136 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x131 && frame == 2 || pattern == 0x137 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1a4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if ((pattern == 0x138 || pattern == 0x139 || pattern == 0x13a) && frame == 2) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1b5;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13b && frame == 3) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1be;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13c && frame == 2 || pattern == 0x13f && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c6;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13d && frame == 2 || pattern == 0x140 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c7;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == 0x13e && frame == 2 || pattern == 0x141 && frame == 1) {
                    unk3148 = 4;
                    m_objects[v4].pattern = 0x1c8;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (unk3154[v4] == 0) {
                    unk3154[v4] = 1;
                    if (pattern == 0xfb) {
                        m_objects[v4].facing = 1;
                    }
                    if (pattern == 0xfc) {
                        m_objects[v4].facing = -1;
                    }
                    break;
                }
                if (pattern == 0xfa) {
                    unk3148 = 1;
                    m_objects[v4].pattern = 0x191;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa && (m_objects[v4].x < x && m_objects[v4].x - x < -200.0 || m_objects[v4].x > x && m_objects[v4].x - x > 200.0)) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = 0x190;
                        unk3154[v4] = 0;
                    }
                }
                break;
            case 0x1b5:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x138 && pattern != 0x139 && pattern != 0x13a) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    unk3354[v4]--;
                    if (unk3354[v4] <= 0) {
                        l50.type = 0x1bb;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x17);
                        l50.y = (double)((int)m_objects[v4].y - 0x21);
                        l50.scale = 2;
                        l50.unk18 = m_objects[v4].facing;
                        l50.layer = 1;
                        SpawnObject(&l50);
                        unk3354[v4] = 0x15;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 8 && unk3254[v4] < (pattern == 0x139) * 3 + 5 + (pattern == 0x13a) * 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        unk3148 = 0;
                        unk3254[v4] = 0;
                        m_objects[v4].unk88 = 0;
                    }
                }
                break;
            case 0x1b8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 1.2;
                    m_objects[v4].vy = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case 0x1b9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 1.6;
                    m_objects[v4].vy = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case 0x1ba:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 2.0;
                    m_objects[v4].vy = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case 0x1bb:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 0.5;
                    m_objects[v4].vy = (WORD)CPlayer::Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].unk80 > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case 0x1be:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    unk3254[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                    m_playVoice = 2;
                }
                if (pattern != 0x13b) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (m_objects[v4].frame > 9 && m_objects[v4].frame < 0x16) {
                    unk3354[v4]--;
                    if (unk3354[v4] <= 0) {
                        l50.type = 0x1bf;
                        l50.unk0 = 1;
                        l50.x = x - (WORD)CPlayer::Random(0, 0x1e0) + 240.0 - m_objects[v4].facing * 0x78;
                        l50.y = -480.0;
                        l50.scale = 2;
                        l50.unk18 = m_objects[v4].facing;
                        l50.layer = 1;
                        SpawnObject(&l50);
                        unk3354[v4] = 0x12;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x16 && unk3254[v4] < 0x11) {
                        m_objects[v4].frame = m_objects[v4].frame - 6;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        unk3148 = 0;
                        unk3254[v4] = 0;
                        m_objects[v4].unk88 = 0;
                    }
                }
                break;
            case 0x1bf:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3254[v4] == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3254[v4]++;
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = 3.0;
                }
                unk3354[v4]--;
                if (unk3354[v4] <= 0) {
                    l50.type = unk3254[v4] + 0x1c0;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 0;
                    SpawnObject(&l50);
                    unk3354[v4] = 6;
                    unk3254[v4]++;
                    if (unk3254[v4] > 4) {
                        unk3254[v4] = 0;
                    }
                }
                if (m_objects[v4].y > 200.0) {
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
            case 0x1c0:
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
            case 0x1c2:
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy = 3.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    (*m_opponent)->y = m_objects[v4].y;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = 0x62;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    CPlayer::DealDamage(0x4b0, 500.0);
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 3) {
                        m_objects[v4].scale = 1;
                    }
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1c6:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12c && pattern != 0x132) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.0035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame > 3 && m_objects[v4].frame < 9) {
                        l50.type = 0x1cf;
                        l50.x = m_objects[v4].x + (WORD)CPlayer::Random(0, 0x1e) * m_objects[v4].facing;
                        l50.y = m_objects[v4].y - (WORD)CPlayer::Random(0, 0x50) + 40.0 - 30.0;
                        l50.unk18 = m_objects[v4].facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk84 = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -0.5;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3154[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                    }
                }
                break;
            case 0x1c7:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12d && pattern != 0x133) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.0035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame > 3 && m_objects[v4].frame < 9) {
                        l50.type = ((WORD)CPlayer::Random(0, 0x64) > 0x32) + 0x1cf;
                        l50.x = m_objects[v4].x + (WORD)CPlayer::Random(0, 0x28) * m_objects[v4].facing;
                        l50.y = m_objects[v4].y - (WORD)CPlayer::Random(0, 0x78) + 60.0 - 30.0;
                        l50.unk18 = m_objects[v4].facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk84 = 0x63;
                        m_objects[v4].vx = 0.65;
                        m_objects[v4].vy = -0.52;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3154[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                    }
                }
                break;
            case 0x1c8:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12e && pattern != 0x134) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.003;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame > 3 && m_objects[v4].frame < 9) {
                        l50.type = ((WORD)CPlayer::Random(0, 0x64) > 0x46) + 0x1cf + ((WORD)CPlayer::Random(0, 0x64) > 0x1e);
                        l50.x = m_objects[v4].x + (WORD)CPlayer::Random(0, 0x28) * m_objects[v4].facing;
                        l50.y = m_objects[v4].y - (WORD)CPlayer::Random(0, 0x8c) + 70.0 - 30.0;
                        l50.unk18 = m_objects[v4].facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk84 = 0x63;
                        m_objects[v4].vx = 0.85;
                        m_objects[v4].vy = -0.55;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3154[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                        unk3154[v4] = 0;
                    }
                }
                break;
            case 0x1c9:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x13c && pattern != 0x13f) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk84 = 5;
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -1.4;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1ca:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x13d && pattern != 0x140) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk84 = 8;
                        m_objects[v4].vx = 1.8;
                        m_objects[v4].vy = -1.4;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1cb:
                unk3148 = 4;
                m_game->Unk4080c0(0xf);
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x13e && pattern != 0x141) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].unk84 = 0xc;
                        m_objects[v4].vx = 2.1;
                        m_objects[v4].vy = -1.4;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1cc:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12c && pattern != 0x132) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x14;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk84 = 0x63;
                        unk3254[v4] = 0;
                        unk3154[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && unk3254[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.2;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3154[v4] < 2) {
                        unk3154[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x14) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1cd:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x14) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12d && pattern != 0x133) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk84 = 0x63;
                        unk3254[v4] = 0;
                        unk3154[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && unk3254[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3154[v4] < 3) {
                        unk3154[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1ce:
                unk3148 = 4;
                if (m_objects[v4].frame < 0x17) {
                    (*m_opponent)->Unk410a80(0x32, 0x1e);
                    m_game->Unk4080c0(0xf);
                }
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].unk88 = 1;
                }
                if (pattern != 0x12e && pattern != 0x134) {
                    m_objects[v4].unk88 = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x1a;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].unk84 = 0x63;
                        unk3254[v4] = 0;
                        unk3154[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && unk3254[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        unk3254[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && unk3154[v4] < 4) {
                        unk3154[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x1a) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1cf:
                m_objects[v4].vx = 2.0;
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
            case 0x1d0:
                m_objects[v4].vx = 2.5;
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
            case 0x1d1:
                m_objects[v4].vx = 3.0;
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
            case 0x1d2:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0xb) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].frame < 0x10) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x10;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.0;
                    }
                    if (m_objects[v4].frame == 0x10) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1d3:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0xb) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].frame < 0x10) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x10;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.0;
                    }
                    if (m_objects[v4].frame == 0x10) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1d4:
                unk3148 = 4;
                if (m_objects[v4].unk80 == 4 || m_objects[v4].unk80 == 5) {
                    m_objects[v4].pattern = 0x193;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0xb) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].frame < 0x16) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x16;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].unk84 = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.0;
                    }
                    if (m_objects[v4].frame == 0xc && unk3154[v4] < 3) {
                        m_objects[v4].frame--;
                        unk3154[v4]++;
                    }
                    if (m_objects[v4].frame == 0x16) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
                    }
                }
                break;
            case 0x1d5:
                unk3148 = 4;
                m_objects[v4].unk88 = 0;
                unk3154[v4] = 0;
                unk3254[v4] = 0;
                unk3354[v4] = 0;
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    m_objects[v4].x = facing * 0x3c + x;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = 0x190;
                        m_objects[v4].frame = 0;
                        unk3148 = 0;
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
