// CIkumi (0x6a59c0-0x6be9bf).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CIkumi::CIkumi(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    unk3464 = (char*)new EffectAnim[0x1f9];
    unk3468 = (char*)new PatternData[0x1f9];
    Unk6ab6a0(0);
    unk3460 = 0;
    strcpy(m_name, "ikumi");
    lastSurface = 0x47c;
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
    unk2ad0[0] = -0x16;
    unk2af8[0] = -0x32;
    unk2ad0[1] = -0x19;
    unk2af8[1] = 0;
    unk2ad0[2] = -0x19;
    unk2af8[2] = -0xa;
    unk2ad0[3] = 5;
    unk2af8[3] = -9;
    unk2ad0[4] = 0x20;
    unk2af8[4] = -0x1b;
    unk30f4 = 7;
    unk30f5[0] = 8;
    unk30f5[1] = 0xd;
    unk30f5[0xa] = 0xe;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3160[v4] = 0;
        unk3260[v4] = 0;
        unk3360[v4] = 0;
    }
}

void CIkumi::Reset()
{
    int v4;

    Unk6ab6a0(0);
    unk3460 = 0;
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
    unk2ad0[0] = -4;
    unk2af8[0] = -0x39;
    unk2ad0[1] = -0x19;
    unk2af8[1] = 0;
    unk2ad0[2] = 0x15;
    unk2af8[2] = -0xc;
    unk2ad0[3] = 0x12;
    unk2af8[3] = -0xf;
    unk2ad0[4] = 0x26;
    unk2af8[4] = -0x27;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3160[v4] = 0;
        unk3260[v4] = 0;
        unk3360[v4] = 0;
    }
    CPlayer::Reset();
}

CIkumi::~CIkumi()
{
    anims = (EffectAnim*)unk346c;
    m_patterns = (PatternData*)unk3470;
    delete[] (EffectAnim*)unk3464;
    delete[] (PatternData*)unk3468;
    CPlayer::~CPlayer();
}

void CIkumi::Load()
{
    Unk6a5eb0();
    CPlayer::Load();
    unk346c = (int)anims;
    unk3470 = (int)m_patterns;
}

void CIkumi::Unk6a5eb0()
{
    int k2c;
    char* v28;
    char* x24;
    int x20;
    int n1c;
    int a18;
    int k14;
    int l4;

    CFile v10("ikumi\\ikumi2.pat", 1);
    l4 = v10.ReadInt();
    n1c = 0;
    for (; n1c < l4; n1c++) {
        k14 = v10.ReadInt();
        *(short*)(unk3468 + k14 * 8) = v10.ReadInt();
        *(short*)(unk3468 + 2 + k14 * 8) = v10.ReadInt();
        *(unk3464 + k14 * 8) = v10.ReadInt();
        a18 = *(BYTE*)(unk3464 + k14 * 8);
        ((PatternData*)((int)unk3468 + k14 * 8))->Alloc(a18);
        ((EffectAnim*)((int)unk3464 + k14 * 8))->Alloc(a18);
        x20 = 0;
        for (; x20 < a18; x20++) {
            x24 = (char*)(*(int*)(unk3464 + 4 + k14 * 8) + x20 * 0xc);
            v28 = (char*)(*(int*)(unk3468 + 4 + k14 * 8) + x20 * 0xc8);
            *(short*)x24 = (short)v10.ReadInt() * 3;
            *(short*)(x24 + 2) = v10.ReadInt();
            *(short*)(x24 + 8) = v10.ReadInt();
            *(short*)(x24 + 0xa) = v10.ReadInt();
            *(short*)(x24 + 4) = v10.ReadInt();
            *(short*)(x24 + 6) = v10.ReadInt();
            *(short*)(v28 + 0xa0) = v10.ReadInt();
            *(short*)(v28 + 0xaa) = v10.ReadInt();
            *(short*)(v28 + 0xac) = v10.ReadInt();
            *(short*)(v28 + 0xb0) = v10.ReadInt();
            *(short*)(v28 + 0xb2) = v10.ReadInt();
            *(short*)(v28 + 0xa8) = v10.ReadInt();
            *(short*)(v28 + 0xb4) = v10.ReadInt();
            *(short*)(v28 + 0xb6) = v10.ReadInt();
            *(float*)(v28 + 0xbc) = (short)v10.ReadShort();
            *(float*)(v28 + 0xbc) = *(float*)(v28 + 0xbc) / 1e+02f;
            *(float*)(v28 + 0xb8) = (short)v10.ReadShort();
            *(float*)(v28 + 0xb8) = *(float*)(v28 + 0xb8) / -1e+02f;
            *(v28 + 0xc1) = v10.ReadShort();
            *(v28 + 0xc0) = v10.ReadShort();
            *(short*)(v28 + 0xc2) = v10.ReadInt();
            *(short*)(v28 + 0xc4) = v10.ReadInt();
            *(float*)(v28 + 0xa4) = v10.ReadInt();
            *(short*)(v28 + 0xae) = v10.ReadInt();
            v10.Read((void*)(v28 + 0x90), 0x10);
            k2c = 0;
            for (; k2c < 2; k2c++) {
                v10.Read((void*)((k2c << 4) + v28), 0x10);
            }
            v10.Read((void*)(v28 + 0x50), 0x10);
            k2c = 2;
            for (; k2c < 5; k2c++) {
                v10.Read((void*)((k2c << 4) + v28), 0x10);
            }
            k2c = 1;
            for (; k2c < 4; k2c++) {
                v10.Read((void*)(v28 + (k2c << 4) + 0x50), 0x10);
            }
        }
    }
}

void CIkumi::StartPattern()
{
    unk3138 = 0;
    unk313c = 0;
    unk3140 = 0;
    unk3154 = 0;
    CPlayer::StartPattern();
}

void CIkumi::RemoveObject(short p1)
{
    unk3160[p1] = 0;
    unk3260[p1] = 0;
    unk3360[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CIkumi::Move()
{
    CPlayer::Unk40e740();
}

void CIkumi::StartCommand()
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
        if (m_command == 0x5e && m_gauge >= 0xbb8 && m_hp < 0xd05 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && m_attackResult != 6 && unk3150 == 0 && m_patterns[pattern].unk2 <= m_patterns[0x141].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x141;
            return;
        }
        if (unk3150 == 0 && m_command == 0x70 && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x137].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x137;
            return;
        }
        if (unk3150 == 0 && m_command == 0x6f && y == 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x136].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x136;
            return;
        }
        if (unk3150 == 0 && m_command == 0x6e && y == 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x135].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x135;
            return;
        }
        if (unk3150 > 0 && m_command == 0xac && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x140].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x140;
            return;
        }
        if (unk3150 > 0 && (m_command == 0xab || m_command == 0xac) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13f].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13f;
            return;
        }
        if (unk3150 > 0 && (m_command == 0xaa || m_command == 0xab || m_command == 0xac) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13e].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13e;
            return;
        }
        if ((m_command == 0xaa || m_command == 0xab || m_command == 0xac) && unk315c > 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13b].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13b;
            if (unk315c == 2) {
                pattern = 0x13c;
            }
            if (unk315c == 3) {
                pattern = 0x13d;
            }
            return;
        }
        if (m_command == 0xac && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x13a].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x13a;
            return;
        }
        if ((m_command == 0xab || m_command == 0xac) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x139].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x139;
            return;
        }
        if ((m_command == 0xaa || m_command == 0xab || m_command == 0xac) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x138].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x138;
            return;
        }
        if (m_command == 0x98 && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x133].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x133;
            return;
        }
        if ((m_command == 0x98 || m_command == 0x97) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x131].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x131;
            return;
        }
        if ((m_command == 0x96 || m_command == 0x97 || m_command == 0x98) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x12f].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x12f;
            return;
        }
        if (m_command == 0x48 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x107].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x107;
            return;
        }
        if (m_command == 0x16 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x102].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x102;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x115;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x111;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if ((m_command == 0x15 || m_command == 0x16) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x101].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x101;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x114;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x110;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if (m_command == 0x14 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && y == 0.0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0x100].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0x100;
            return;
        }
        if (m_command == 0x20 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfc].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfc;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x11c;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x119;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if (m_command == 0x1f && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfb].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfb;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x11b;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x118;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if (m_command == 0x1e && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfa].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfa;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x11a;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x117;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if (m_command == 0xc && y == 0.0 && (unk118 >= 500.0 || unk120 > 0) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xff].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xff;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x10e;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x10b;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if ((m_command == 0xb || m_command == 0xc) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfe].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfe;
            if (unk314c > 5 || unk3150 > 0) {
                pattern = 0x10d;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            if (unk314c > 2) {
                pattern = 0x10a;
                if (unk3150 == 0) {
                    unk314c--;
                }
                return;
            }
            return;
        }
        if (m_command == 0xa && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8) && m_patterns[pattern].unk2 <= m_patterns[0xfd].unk0) {
            StartPattern();
            CPlayer::Unk40f170();
            pattern = 0xfd;
            return;
        }
    }
    if (unk15c < 1 && (m_command == 0 || m_command == 1)) {
        if (y < 0.0 && unk159 < 2) {
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].unk2 <= m_patterns[0xdc].unk0 && ((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern > 0x9c) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && (pattern >= 0xc8 && m_attackResult >= 2 && m_attackResult != 6 || pattern < 0xc8)) {
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

void CIkumi::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (unk3150 == 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3150 > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3150 > 0) {
        x1c = *anims[0x2a].frames;
        v2c = MakeRect(0, 0, unk3150 * x1c.width / 0x4ec, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, unk3150 * x1c.width / 0x4ec, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - unk3150 * x1c.width / 0x4ec, 0x1f - x1c.y, unk3150 * x1c.width / 0x4ec, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (unk3150 == 0) {
        x1c = *anims[0x26].frames;
        v2c = MakeRect(0, 0, unk3148 * x1c.width / 0x64, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(unk314c * 8 + 0x32 - x1c.x, 0x1f - x1c.y, unk3148 * x1c.width / 0x64, x1c.height);
        } else {
            v10 = MakeRect(0x10e - (unk314c << 3) + x1c.x - x1c.width * unk3148 / 0x64, 0x1f - x1c.y, unk3148 * x1c.width / 0x64, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        if (unk314c > 0) {
            if (unk314c > 0) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x32 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0x10e - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 1) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x3a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0x106 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 2) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x42 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xfe - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 3) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x4a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xf6 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 4) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x52 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xee - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 5) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x5a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xe6 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 6) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x62 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xde - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (unk314c > 7) {
                if (unk314c < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (unk314c < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (unk314c < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x6a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xd6 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
        }
    }
}

void CIkumi::Vf8()
{
    EffectDesc v48;
    CPlayer::InitEffectDesc((EffectDesc*)&v48);
    if (unk314c == 8 && y == 0.0 && pattern < 8 && pattern != 0x12c) {
        StartPattern();
        CPlayer::StopMoving();
        pattern = 0x12c;
    }
    if (unk314c == 0xa) {
        unk3158++;
        if (unk3158 > 0xb9) {
            unk3158 = 0;
        }
        unk3150--;
        unk138 = 2;
        unk13a = 2;
        CPlayer::Unk4109d0(2);
        if (unk3158 == 6) {
            CPlayer::Unk410ac0(0xd5, 9);
        }
        if (unk3158 == 0xc) {
            CPlayer::Unk410ac0(0xd6, 9);
        }
        if (unk3158 == 0x12) {
            CPlayer::Unk410ac0(0xea, 9);
        }
        if (unk3158 == 0x18) {
            CPlayer::Unk410ac0(0xe9, 9);
        }
        if (unk3158 == 0x1e) {
            CPlayer::Unk410ac0(0xe8, 9);
        }
        if (unk3158 == 0x24) {
            CPlayer::Unk410ac0(0xe7, 9);
        }
        if (unk3158 == 0x2a) {
            CPlayer::Unk410ac0(0xe6, 9);
        }
        if (unk3158 == 0x30) {
            CPlayer::Unk410ac0(0xe5, 9);
        }
        if (unk3158 == 0x36) {
            CPlayer::Unk410ac0(0xe4, 9);
        }
        if (unk3158 == 0x3c) {
            CPlayer::Unk410ac0(0xe5, 9);
        }
        if (unk3158 == 0x42) {
            CPlayer::Unk410ac0(0xe6, 9);
        }
        if (unk3158 == 0x48) {
            CPlayer::Unk410ac0(0xe7, 9);
        }
        if (unk3158 == 0x4e) {
            CPlayer::Unk410ac0(0xe8, 9);
        }
        if (unk3158 == 0x54) {
            CPlayer::Unk410ac0(0xe9, 9);
        }
        if (unk3158 == 0x5a) {
            CPlayer::Unk410ac0(0xea, 9);
        }
        if (unk3158 == 0x60) {
            CPlayer::Unk410ac0(0xd6, 9);
        }
        if (unk3158 == 0x66) {
            CPlayer::Unk410ac0(0xd5, 9);
        }
        if (unk3150 <= 0) {
            unk314c = 0;
            unk3148 = 0;
            Unk6ab6a0(0);
        }
    }
    if (m_attackResult == 3 && unk3154 == 0) {
        if (pattern == 0xc9 || pattern == 0xca || pattern == 0xcd || pattern == 0xd0) {
            v48.type = 0x1d6;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.unk18 = facing;
            SpawnObject(&v48);
            unk3154++;
        }
        if (pattern == 0xe7 || pattern == 0xea) {
            v48.type = 0x1de;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.unk18 = facing;
            SpawnObject(&v48);
            unk3154++;
        }
        if (pattern == 0xfd || pattern == 0xfe || pattern == 0x100 || pattern == 0x101) {
            v48.type = 0x1d7;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.unk18 = facing;
            SpawnObject(&v48);
            unk3154++;
        }
        if (pattern == 0x10a || pattern == 0xff || pattern == 0x10b || pattern == 0x102 || pattern == 0x110 || pattern == 0x111) {
            v48.type = 0x1df;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.unk18 = facing;
            SpawnObject(&v48);
            unk3154++;
        }
        if (pattern == 0x10d || pattern == 0x10e || pattern == 0x114 || pattern == 0x115) {
            v48.type = 0x1e0;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.unk18 = facing;
            SpawnObject(&v48);
            unk3154++;
        }
    }
}

void CIkumi::Unk6ab6a0(char p1)
{
    int v8;
    int v4;

    if (p1 == 1 && unk3460 == 0) {
        anims = (EffectAnim*)(int)unk3464;
        v4 = 0;
        for (; v4 < 0x40; v4++) {
            m_objects[v4].anims = (EffectAnim*)(int)unk3464;
        }
        m_patterns = (PatternData*)(int)unk3468;
        unk3460 = 1;
        return;
    }
    if (p1 == 0 && unk3460 == 1) {
        anims = (EffectAnim*)unk346c;
        v8 = 0;
        for (; v8 < 0x40; v8++) {
            m_objects[v8].anims = (EffectAnim*)unk346c;
        }
        m_patterns = (PatternData*)unk3470;
        unk3460 = 0;
    }
}

void CIkumi::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CIkumi::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = 0x63;
    x6 = 0;
    v4 = m_inputPos + 0x46;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 9) {
            m_command = 0x5e;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 8) {
            if ((v5 & 0x40) != 0) {
                m_command = 0x5e;
                return;
            }
            x6 = 9;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 7) {
            x6 = 8;
        }
        if ((v5 & 0xf) == 4 && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && (m_gauge >= 0x3e8 || unk315c > 0)) {
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
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
        if ((v5 & 0xf) == 0 && x6 == 0) {
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

void CIkumi::CpuInput()
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

void CIkumi::UpdateObjects()
{
    WORD v58;
    WORD v54;
    int v4;

    if (unk3460 == 1) {
        Unk6b7900();
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x196;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3160[v4] = 0;
                }
                if (m_objects[v4].unk80 == 3 && unk3160[v4] == 0) {
                    unk3160[v4] = 1;
                    l50.type = 0x1de;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
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
            case 0x199:
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x19b;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
            case 0x19b:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3160[v4] = 0;
                }
                if (m_objects[v4].unk80 == 3 && unk3160[v4] == 0) {
                    unk3160[v4] = 1;
                    l50.type = 0x1de;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x2f && unk3160[v4] == 0) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 0x20;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19c:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x19d;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 2;
                    unk3160[v4] = 0;
                    unk3260[v4] = 0;
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                if (m_objects[v4].unk80 == 3 && unk3260[v4] == 0) {
                    unk3260[v4] = 1;
                    l50.type = 0x1de;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && unk3160[v4] < 3) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].unk80 = 0;
                        unk3260[v4] = 0;
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
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a0:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a1:
                if (m_objects[v4].timer == 0 && (m_objects[v4].frame == 0 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x1e)) {
                    l50.type = 0x1a2;
                    if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                        l50.type = 0x1a3;
                    }
                    l50.x = (double)((int)m_objects[v4].x + -0x3c + (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)((int)m_objects[v4].y - (WORD)CPlayer::Random(0, 0xa0));
                    l50.unk18 = m_objects[v4].facing;
                    if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                        l50.unk18 = -m_objects[v4].facing;
                    }
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a2:
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
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x1ae;
                    break;
                }
                if (m_objects[v4].frame == 0x1b && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 2.5;
                    m_objects[v4].unk84 = 3;
                }
                if (m_objects[v4].frame == 0x1b && m_objects[v4].timer == 0) {
                    unk3260[v4] = 1;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].timer == 0) {
                    unk2c9 = 0x14;
                    l50.type = 0x191;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                    unk2c8 = 2;
                }
                if (m_objects[v4].frame > 0x26) {
                    m_objects[v4].vx -= 0.07;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 150.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 150.0 && m_objects[v4].facing == 1) && unk3260[v4] != 0 && m_objects[v4].frame < 0x23) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x23;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3160[v4] < 0) {
                        unk3160[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = 0x1b;
                    }
                    if (m_objects[v4].frame == 0x1b && unk3160[v4] < 0) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x23 && unk3360[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 8;
                        unk3360[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = 0x1ae;
                    }
                }
                break;
            case 0x1a5:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x1ae;
                    break;
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].frame < 0x1b && (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1b;
                    break;
                }
                if ((m_objects[v4].frame == 0x1e || m_objects[v4].frame == 0x26 || m_objects[v4].frame == 0x2f) && m_objects[v4].timer == 0) {
                    unk2c9 = 0x15;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 0x37) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x37;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3160[v4] < 8) {
                        unk3160[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x1b && unk3160[v4] < 0xd) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x2d) {
                        m_objects[v4].vx = 1.0;
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].frame == 0x37) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = 0x1ae;
                    }
                }
                break;
            case 0x1a6:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x1ae;
                    break;
                }
                if (m_objects[v4].frame == 6) {
                    m_objects[v4].vx = 0.6;
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1) && m_objects[v4].frame > 5 && m_objects[v4].frame < 0xe) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3160[v4] < 8) {
                        unk3160[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xe && unk3260[v4] < 5) {
                        unk3260[v4]++;
                        m_objects[v4].frame = 6;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame == 0x15) {
                        l50.type = 0x1ac;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x32);
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk0 = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = 0x1ae;
                    }
                }
                break;
            case 0x1a7:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 9;
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
            case 0x1a9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 0;
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
            case 0x1aa:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 9;
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
            case 0x1ab:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 9;
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
            case 0x1ac:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x1ad;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
            case 0x1ad:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 4;
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && unk3160[v4] < 3) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ae:
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case 0x1b2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case 0x1b3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    unk3138 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case 0x1b5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    unk3138 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
            case 0x1b6:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case 0x1b7:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].unk80 > 0) {
                    unk313c = 1;
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
            case 0x1d6:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
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
            case 0x1d7:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case 0x1d8:
                m_objects[v4].vy += 0.035;
                if (unk3160[v4] == 0) {
                    unk3160[v4]++;
                    unk3260[v4] = (WORD)CPlayer::Random(0x5a, 0x61);
                    (&m_objects[v4])->SetVelocity((double)-unk3260[v4], (WORD)CPlayer::Random(0, 5) * 0.1 + 3.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1db;
                    if (unk314c < 8) {
                        unk3148 += 0xa;
                    }
                    if (unk3148 >= 0x64) {
                        unk3148 = 0;
                        unk314c++;
                        if (unk314c > 8) {
                            unk314c = 8;
                        }
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1dc;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case 0x1d9:
                m_objects[v4].vy += 0.035;
                if (unk3160[v4] == 0) {
                    unk3160[v4]++;
                    unk3260[v4] = (WORD)CPlayer::Random(0x5a, 0x64);
                    (&m_objects[v4])->SetVelocity((double)-unk3260[v4], (WORD)CPlayer::Random(0, 5) * 0.1 + 2.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1db;
                    if (unk314c < 8) {
                        unk3148 += 0x1e;
                    }
                    if (unk3148 >= 0x64) {
                        unk3148 = 0;
                        unk314c++;
                        if (unk314c > 8) {
                            unk314c = 8;
                        }
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1dc;
                    m_objects[v4].layer = 0;
                    break;
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
            case 0x1da:
                m_objects[v4].vy += 0.035;
                if (unk3160[v4] == 0) {
                    unk3160[v4]++;
                    unk3260[v4] = (WORD)CPlayer::Random(0x5a, 0x64);
                    (&m_objects[v4])->SetVelocity((double)-unk3260[v4], (WORD)CPlayer::Random(0, 5) * 0.1 + 2.8);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1db;
                    if (unk314c < 8) {
                        unk3148 += 0x32;
                    }
                    if (unk3148 >= 0x64) {
                        unk3148 = 0;
                        unk314c++;
                        if (unk314c > 8) {
                            unk314c = 8;
                        }
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1dc;
                    m_objects[v4].layer = 0;
                    break;
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
            case 0x1db:
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
            case 0x1dc:
                if (m_objects[v4].frame == 4 && m_objects[v4].x - x > -15.0 && m_objects[v4].x - x < 15.0 && y == 0.0) {
                    if (unk314c < 8) {
                        unk3148 += 8;
                    }
                    if (unk3148 >= 0x64) {
                        unk3148 = 0;
                        unk314c++;
                        if (unk314c > 8) {
                            unk314c = 8;
                        }
                    }
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 7;
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
            case 0x1dd:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1da;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case 0x1de:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case 0x1df:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1da;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case 0x1e0:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1da;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3160[v4] == 0) {
                    unk3260[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3160[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3260[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3260[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3260[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3160[v4] == 0) {
                    unk3260[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3160[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3260[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3260[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3260[v4]--;
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

void CIkumi::Unk6b7900()
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x196;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3160[v4] = 0;
                }
                if (m_objects[v4].unk80 == 3 && unk3160[v4] == 0) {
                    unk3160[v4] = 1;
                    l50.type = 0x1de;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
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
            case 0x199:
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x19b;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
            case 0x19b:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                    unk3160[v4] = 0;
                }
                if (m_objects[v4].unk80 == 3 && unk3160[v4] == 0) {
                    unk3160[v4] = 1;
                    l50.type = 0x1de;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 0x2f && unk3160[v4] == 0) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 0x20;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x19c:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x19d;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 2;
                    unk3160[v4] = 0;
                    unk3260[v4] = 0;
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                if (m_objects[v4].unk80 == 3 && unk3260[v4] == 0) {
                    unk3260[v4] = 1;
                    l50.type = 0x1de;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.unk18 = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && unk3160[v4] < 3) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].unk80 = 0;
                        unk3260[v4] = 0;
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
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a0:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a1:
                if (m_objects[v4].timer == 0 && (m_objects[v4].frame == 0 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x1e)) {
                    l50.type = 0x1a2;
                    if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                        l50.type = 0x1a3;
                    }
                    l50.x = (double)((int)m_objects[v4].x + -0x3c + (WORD)CPlayer::Random(0, 0x78));
                    l50.y = (double)((int)m_objects[v4].y - (WORD)CPlayer::Random(0, 0xa0));
                    l50.unk18 = m_objects[v4].facing;
                    if ((WORD)CPlayer::Random(0, 0x64) < 0x32) {
                        l50.unk18 = -m_objects[v4].facing;
                    }
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a2:
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
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x1ae;
                    break;
                }
                if (m_objects[v4].frame == 0x1b && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 2.5;
                    m_objects[v4].unk84 = 3;
                }
                if (m_objects[v4].frame == 0x1f && m_objects[v4].timer == 0) {
                    unk3260[v4] = 1;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].timer == 0) {
                    unk2c9 = 0x14;
                    l50.type = 0x191;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.unk0 = 1;
                    l50.unk18 = m_objects[v4].facing;
                    SpawnObject(&l50);
                    unk2c8 = 2;
                }
                if (m_objects[v4].frame > 0x26) {
                    m_objects[v4].vx -= 0.045;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 150.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 150.0 && m_objects[v4].facing == 1) && unk3260[v4] != 0 && m_objects[v4].frame < 0x23) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x23;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3160[v4] < 8) {
                        unk3160[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x1b && unk3160[v4] < 1) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x23 && unk3360[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 8;
                        unk3360[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = 0x1ae;
                    }
                }
                break;
            case 0x1a5:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x1ae;
                    break;
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].frame < 0x1b && (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1b;
                    break;
                }
                if ((m_objects[v4].frame == 0x1e || m_objects[v4].frame == 0x26 || m_objects[v4].frame == 0x2f) && m_objects[v4].timer == 0) {
                    unk2c9 = 0x15;
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 0x37) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x37;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3160[v4] < 8) {
                        unk3160[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x1b && unk3160[v4] < 0xd) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x2d) {
                        m_objects[v4].vx = 1.0;
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].frame == 0x37) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = 0x1ae;
                    }
                }
                break;
            case 0x1a6:
                if (pattern > 0x31 && pattern < 0x96) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = 0x1ae;
                    break;
                }
                if (m_objects[v4].frame == 6) {
                    m_objects[v4].vx = 0.6;
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1) && m_objects[v4].frame > 5 && m_objects[v4].frame < 0xe) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 2 && unk3160[v4] < 8) {
                        unk3160[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xe && unk3260[v4] < 5) {
                        unk3260[v4]++;
                        m_objects[v4].frame = 6;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame == 0x15) {
                        l50.type = 0x1ac;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x32);
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.unk0 = 1;
                        l50.unk18 = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = 0x1ae;
                    }
                }
                break;
            case 0x1a7:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1a8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 9;
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
            case 0x1a9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 0;
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
            case 0x1aa:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 9;
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
            case 0x1ab:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    unk2c8 = 9;
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
            case 0x1ac:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x1ad;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.unk0 = 1;
                    SpawnObject(&l50);
                    unk2c8 = 1;
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
            case 0x1ad:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].unk84 = 2;
                }
                if (m_objects[v4].unk84 == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && unk3160[v4] < 3) {
                        unk3160[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].unk80 = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case 0x1ae:
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case 0x1b2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case 0x1b3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    unk3138 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case 0x1b5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    unk3138 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
            case 0x1b6:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case 0x1b7:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].unk84 = 1;
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
            case 0x1d6:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
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
            case 0x1d7:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case 0x1d8:
                m_objects[v4].vy += 0.035;
                if (unk3160[v4] == 0) {
                    unk3160[v4]++;
                    unk3260[v4] = (WORD)CPlayer::Random(0x5a, 0x61);
                    (&m_objects[v4])->SetVelocity((double)-unk3260[v4], (WORD)CPlayer::Random(0, 5) * 0.1 + 3.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1db;
                    unk3150 += 0xa;
                    if (unk3150 > 0x4ec) {
                        unk3150 = 0x4ec;
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1dc;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].unk80 = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case 0x1d9:
                m_objects[v4].vy += 0.035;
                if (unk3160[v4] == 0) {
                    unk3160[v4]++;
                    unk3260[v4] = (WORD)CPlayer::Random(0x5a, 0x64);
                    (&m_objects[v4])->SetVelocity((double)-unk3260[v4], (WORD)CPlayer::Random(0, 5) * 0.1 + 2.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1db;
                    unk3150 += 0x1e;
                    if (unk3150 > 0x4ec) {
                        unk3150 = 0x4ec;
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1dc;
                    m_objects[v4].layer = 0;
                    break;
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
            case 0x1da:
                m_objects[v4].vy += 0.035;
                if (unk3160[v4] == 0) {
                    unk3160[v4]++;
                    unk3260[v4] = (WORD)CPlayer::Random(0x5a, 0x64);
                    (&m_objects[v4])->SetVelocity((double)-unk3260[v4], (WORD)CPlayer::Random(0, 5) * 0.1 + 2.8);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1db;
                    unk3150 += 0x32;
                    if (unk3150 > 0x4ec) {
                        unk3150 = 0x4ec;
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = 0x1dc;
                    m_objects[v4].layer = 0;
                    break;
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
            case 0x1db:
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
            case 0x1dc:
                if (m_objects[v4].frame == 4 && m_objects[v4].x - x > -15.0 && m_objects[v4].x - x < 15.0 && y == 0.0) {
                    unk3150 += 5;
                    if (unk3150 > 0x4ec) {
                        unk3150 = 0x4ec;
                    }
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 7;
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
            case 0x1dd:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1da;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case 0x1de:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case 0x1df:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1da;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case 0x1e0:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1d8;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1d9;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1da;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.unk18 = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3160[v4] == 0) {
                    unk3260[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    unk3160[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3260[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3260[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3260[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && unk3160[v4] == 0) {
                    unk3260[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    unk3160[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (unk3260[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (unk3260[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                unk3260[v4]--;
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
