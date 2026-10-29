// Sixth object of efz.exe (0x40e630-0x412b0f): CPlayer, the base of the character
// classes. Movement and facing, guard and damage, the per-character .pal/.dat/.pat/.wav
// loaders and the state reset at the start of a round. The inline methods of
// PatternData and Afterimages it uses follow it (0x412820-0x412b0f), with
// FUNCTION: 0x412870 ??_EPatternData@@QAEPAXI@Z
//   PatternData's vector deleting destructor, for `delete[]` in ~CPlayer
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

int CPlayer::Unk40e630()
{
    char v1;

    v1 = facing;
    if (x < (*m_opponent)->x) {
        facing = 1;
        return facing != v1;
    }
    if (x > (*m_opponent)->x) {
        facing = -1;
        return facing != v1;
    }
    return 0;
}

int CPlayer::Unk40e6c0(double p1)
{
    char v1;

    v1 = facing;
    if (x < p1) {
        facing = 1;
        return facing != v1;
    }
    if (x > p1) {
        facing = -1;
        return facing != v1;
    }
    return 0;
}

void CPlayer::Unk40e740()
{
    if (y == 0.0) {
        unk159 = 0;
        unk15a = 0;
    }
    if (y >= 0.0 && pattern != 4 && pattern != 5 && pattern != 6 && pattern != 0xa && pattern != 0xb && pattern != 0xc) {
        if (unk15c < 3 && m_inputY == -1) {
            Unk40e630();
            if (unk262 >= 3 && unk262 <= 5) {
                if (unk262 == 3) {
                    if (pattern != 0xa) {
                        Vf0();
                    }
                    pattern = 0xa;
                    return;
                }
                if (unk262 == 4) {
                    if (pattern != 0xb) {
                        Vf0();
                    }
                    pattern = 0xb;
                    return;
                }
                if (unk262 == 5) {
                    if (pattern != 0xc) {
                        Vf0();
                    }
                    pattern = 0xc;
                    return;
                }
            } else {
                if (m_inputX == 0) {
                    if (pattern != 4) {
                        Vf0();
                    }
                    pattern = 4;
                    return;
                }
                if (m_inputX == facing) {
                    if (pattern != 5) {
                        Vf0();
                    }
                    pattern = 5;
                    return;
                }
                if (m_inputX == -facing) {
                    if (pattern != 6) {
                        Vf0();
                    }
                    pattern = 6;
                    return;
                }
            }
        }
        if (m_inputY == 1) {
            if (pattern != 8 && pattern != 3) {
                pattern = 8;
                Vf0();
                Unk40e630();
                return;
            }
            if (pattern != 8) {
                pattern = 3;
                Unk40e630();
                return;
            }
            return;
        }
        if (m_inputX != 0) {
            Unk40e630();
            if (m_inputX == facing) {
                if (pattern != 1) {
                    Vf0();
                }
                pattern = 1;
                return;
            }
            if (pattern != 2) {
                Vf0();
            }
            pattern = 2;
            return;
        }
        if (pattern == 3 || pattern == 8) {
            pattern = 7;
            Unk40e630();
            Vf0();
            return;
        }
        if (pattern == 7 || pattern == 0xd) {
            Unk40e630();
            return;
        }
        if (pattern != 0) {
            Vf0();
        }
        pattern = 0;
        Unk40e630();
    }
}

CPlayer::CPlayer(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : m_opponent((CPlayer**)p1)
{
    int v4;

    m_game = (CGame*)p2;
    m_graphics = (CGraphics*)p3;
    m_input = (CInput*)p4;
    m_sound = (CSound*)p5;
    m_side = p6;
    unk8d = 0;
    m_paletteIndex = 0;
    v4 = 0;
    for (; v4 < 0x32; v4++) {
        unk264[v4] = 0x96;
    }
    v4 = 0;
    for (; v4 < 0x14; v4++) {
        unk30f5[v4] = -1;
    }
    surfaces = (IDirectDrawSurface**)0;
    anims = (EffectAnim*)(int)(char*)new EffectAnim[0x1f9];
    m_patterns = (PatternData*)(int)(char*)new PatternData[0x1f9];
    unk30c8 = 0;
    unk30cc = 0;
    unk30d0 = 0;
    unk30d4 = 0;
    unk30d8 = 0;
    unk30e8 = 0;
}

CPlayer::~CPlayer()
{
    int v4;

    if ((int)surfaces != 0) {
        v4 = 0;
        for (; v4 < lastSurface + 1; v4++) {
            if ((int)surfaces[v4] != 0) {
                surfaces[v4]->Release();
                surfaces[v4] = (IDirectDrawSurface*)0;
            }
        }
        delete (char*)surfaces;
    }
    v4 = 0;
    for (; v4 < 0x32; v4++) {
        if ((unsigned short)unk264[v4] != 0x96) {
            m_sound->Release(unk264[v4]);
        }
    }
    delete[] anims;
    delete[] m_patterns;
}

void CPlayer::Vf12()
{
    int v4;

    x = m_side * 0xa0 + 0xf0;
    y = 0.0;
    facing = 1 - (m_side << 1);
    Unk40f1e0();
    unkb0 = 0.0;
    unkd0 = 0;
    pattern = 0;
    frame = 0;
    timer = 0;
    unk30bc = 0;
    unk30c4 = 0;
    unk108 = 0x270f;
    unk10c = 0x270f;
    unk110 = 0x270f;
    unk148 = 0;
    unk118 = 0.0;
    unk120 = 0;
    unk14c = 0;
    unk159 = 0;
    unk158 = 0;
    unk15a = 0;
    unk14e = 0;
    unk150 = 0;
    unkac = 0;
    unk138 = 0;
    unk13a = 0;
    unk13c = 0;
    unk13e = 0;
    unk140 = 0;
    unk15c = 0;
    unk160 = 0;
    unk168 = 0;
    unk14a = 0;
    *(int*)&unk134 = 0;
    unk174 = 0;
    unkf4 = 0;
    unk104 = 0;
    unk178 = 10000.0;
    unkf8 = 10000.0;
    unk170 = 0;
    unk180 = 1.0;
    unk1a8 = 0;
    unk1a9 = 0;
    unk262 = 0x63;
    m_inputPos = 0;
    v4 = 0;
    for (; v4 < 0xb4; v4++) {
        m_inputHistory[v4] = 0;
    }
    unk2c8 = -1;
    unk2c9 = -1;
    unk2ca = 0;
    unk2cc = 0;
    Unk413040();
    m_afterimages.pos = 0;
    m_afterimages.unk0 = 0;
    m_afterimages.unk2 = 0;
    unk30f0 = 0;
    unk30ec = 0;
    unk58 = 0;
    unk60 = 1;
    unk30dc = 0;
    unk30d4 = 0;
    unk30d8 = 0;
}

void CPlayer::Vf0()
{
    frame = 0;
    timer = 0;
    unkb8 = 0.0;
    unk168 = 0;
    unk170 = 0;
    (&m_afterimages)->Unk412910();
}

void CPlayer::Unk40f170()
{
    unk1a8 = 0;
    unk1a9 = 0;
}

void CPlayer::Unk40f190()
{
    int v4;

    v4 = 0;
    for (; v4 < 0xb4; v4++) {
        m_inputHistory[v4] = 0;
    }
    unk262 = 0x63;
}

void CPlayer::Unk40f1e0()
{
    vx = 0.0;
    vy = 0.0;
    ax = 0.0;
    ay = 0.0;
    unkb8 = 0.0;
}

void CPlayer::Unk40f230()
{
    if (unk14a == 0 && (*m_opponent)->unk14c == 0) {
        if (pattern < 0x32 || pattern > 0x96 || pattern == 0x60) {
            unk124 = 0;
            unk12c = 0;
            (*m_opponent)->unk174 = 0;
            if ((*m_opponent)->unk178 > 10000.0) {
                (*m_opponent)->unk178 -= 20.0;
            } else {
                (*m_opponent)->unk178 = 10000.0;
            }
        }
        if (pattern < 0x32) {
            Vf3();
            unkb8 = 0.0;
            (*m_opponent)->unkb8 = 0.0;
            if (unk30ec != 0 && (*m_opponent)->pattern < 0x32) {
                unk148 = 0xbb8;
                unk108 = unk30ee;
                if (unk30ec > 0) {
                    if (unk30ec < 0x3e8) {
                        unk118 = unk30ec;
                        unk120 = 0;
                    } else {
                        unk118 = 0x7d0 - unk30ec;
                        unk120 = 1;
                    }
                }
            }
        }
        if (pattern >= 0x32 && pattern < 0x96 && unk134 <= 0.0f && (m_patterns[pattern].frames[frame].flagsAA & 0x400) == 0) {
            Unk40f470();
        }
        Vf4();
    }
}

void CPlayer::Unk40f470()
{
    if (unk124 > 0) {
        unk124--;
        return;
    }
    if (y < 0.0 && unk128 == 0 && (m_pressA != 0 || m_pressB != 0 || m_pressC != 0 || m_pressD != 0)) {
        if (m_inputX == facing) {
            if (pattern != 0x9d) {
                Vf0();
            }
            pattern = 0x9d;
            return;
        }
        if (m_inputX == -facing) {
            if (pattern != 0x9e) {
                Vf0();
            }
            pattern = 0x9e;
        }
    }
}

void CPlayer::Unk40f580()
{
    int v4;

    v4 = unk2cc;
    if (unk14a == 0 && (*m_opponent)->unk14c == 0) {
        if ((char)Unk40ff70() * facing * (vx + unkb0 + (*m_opponent)->unkb8 * ((*m_opponent)->unkd0 != 0 && unk14c == 0)) >= 0.0) {
            x = (vx + unkb0 + (*m_opponent)->unkb8 * ((*m_opponent)->unkd0 != 0 && unk14c == 0)) * facing + x;
        }
        if (((char)(*m_opponent)->Unk40ff70() == 1 && (*m_opponent)->x <= 20.0) + 0x14 > x) {
            x = ((char)(*m_opponent)->Unk40ff70() == 1 && (*m_opponent)->x <= 20.0) + 0x14;
        } else if (0x26b - ((char)(*m_opponent)->Unk40ff70() == -1 && (*m_opponent)->x >= 619.0) < x) {
            x = 0x26b - ((char)(*m_opponent)->Unk40ff70() == -1 && (*m_opponent)->x >= 619.0);
        }
        y = y + vy;
        if (y > 0.0) {
            y = 0.0;
        }
    }
    while (v4 != unk2ca) {
        if (unk3d0[v4] != 0 && (unk14c <= 0 || m_objects[v4].unk88 != 0) && m_objects[v4].unk86 == 0 && (*m_opponent)->unk14c == 0) {
            m_objects[v4].x += (m_objects[v4].vx + 0.0 * m_objects[v4].unk70) * m_objects[v4].facing;
            m_objects[v4].y = m_objects[v4].y + m_objects[v4].vy;
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}

void CPlayer::Unk40f980()
{
    int v4;

    if ((*m_opponent)->unk14c > 0) {
    } else {
        if (unk14a > 0) {
            unk14a--;
        } else {
            unk14a = 0;
        }
        if (Unk410340() == 0) {
            if (Unk4103a0() != 0) {
                unk134 = unk134 - (float)(1.0 / ((y == 0.0) * 4 + 1));
            } else {
                unk134 -= 0.075f;
            }
            if (unk134 < 0.0f) {
                *(int*)&unk134 = 0;
            }
        }
        if (unk130 > 0) {
            unk130--;
        } else {
            unk130 = 0;
        }
        if ((m_patterns[pattern].frames[frame].flagsB0 & 0x40) > 0) {
            unk130 = 0x1b;
        }
        if (unk138 > 0) {
            unk138--;
        } else {
            unk138 = 0;
        }
        if (unk13a > 0) {
            unk13a--;
        } else {
            unk13a = 0;
        }
        if (unk13c > 0) {
            unk13c--;
        } else {
            unk13c = 0;
        }
        if (unk13e > 0) {
            unk13e--;
        } else {
            unk13e = 0;
        }
        if (unk140 > 0) {
            unk140--;
        } else {
            unk140 = 0;
        }
        unk118 = (Unk410340() + 1) * (Unk4103a0() == 0 && unk120 == 0) * ((unk118 < 500.0) * 2 + 1) / 10.0 + unk118;
        if (unk118 >= 1000.0 && unk120 == 0) {
            unk120 = 1;
            unk118 = 1000.0;
        } else if (unk118 <= 0.0) {
            unk120 = 0;
            unk118 = 0.0;
        }
        v4 = unk2cc;
        while (v4 != unk2ca) {
            if (unk3d0[v4] != 0) {
                if (m_objects[v4].unk86 > 0) {
                    m_objects[v4].unk86--;
                } else {
                    m_objects[v4].unk86 = 0;
                }
            }
            v4++;
            if (v4 >= 0x40) {
                v4 = 0;
            }
        }
        if ((*m_opponent)->Unk4103a0() != 0) {
            unk30e4 = 0x384;
            unk30e0 = 0xc;
        }
        if (((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern >= 0xc8) && (char)m_game->unk1350 == 0 && m_game->unk1354 == 0) {
            if ((unsigned long)unk30e4 > 0) {
                unk30e4--;
            } else {
                if ((unsigned long)unk30e0 > 1) {
                    unk30e0--;
                }
                if ((unsigned long)unk30d0 > 0) {
                    unk30d0--;
                }
                unk30e4 = unk30e0 * 5 * 3;
            }
        }
    }
    if (unk148 < 0) {
        unk148 = 0;
    } else if (unk148 > 0xbb8) {
        unk148 = 0xbb8;
    }
    if (unk118 < 0.0) {
        unk118 = 0.0;
    } else if (unk118 > 1000.0) {
        unk118 = 1000.0;
    }
    unk30f0--;
    if (unk30f0 <= 0) {
        unk30f0 = 0x3138;
    }
    if (unk104 > 0 && unk174 == 0) {
        unk104--;
    }
}

char CPlayer::Unk40ff70()
{
    if (x - 20.0 <= ((*m_opponent)->x <= 20.0) || (*m_opponent)->x - x > 280.0) {
        return 1;
    }
    if (x + 20.0 >= 0x27f - ((*m_opponent)->x >= 619.0) || x - (*m_opponent)->x > 280.0) {
        return -1;
    }
    return 0;
}

int CPlayer::Unk410050(int p1, int p2)
{
    if (unk13a > 0) {
        return 0;
    }
    if ((*(WORD*)((char*)p1 + 0xaa) & 0x80) > 0) {
        return 0;
    }
    if ((*(WORD*)((char*)p2 + 0xb0) & 0x10) == 0) {
        return 0;
    }
    if ((*(WORD*)((char*)p1 + 0xaa) & 4) == 0 && y < 0.0 && unk14e < 0x1e) {
        return 0;
    }
    if (Unk4100f0(p1) == 0) {
        return 0;
    }
    return 1;
}

int CPlayer::Unk4100f0(int p1)
{
    if (unka4 != 0) {
        if (m_game->unk1364 == 1) {
            if (m_game->unk1348 == 0) {
                return 0;
            }
        } else {
            if (rand() > unka8 * 1e+04f) {
                return 0;
            }
            if ((*(WORD*)((char*)p1 + 0xaa) & 1) == 0) {
                m_inputY = 1;
            } else if ((*(WORD*)((char*)p1 + 0xaa) & 2) == 0) {
                m_inputY = 0;
            }
        }
        if ((*(WORD*)((char*)p1 + 0xaa) & 2) == 0 && m_inputY == 1 && y == 0.0 || (*(WORD*)((char*)p1 + 0xaa) & 1) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    } else {
        if (m_inputX != 1 - (((*m_opponent)->x - x > 0.0) << 1) && (Unk410340() == 0 || m_inputX == 0)) {
            return 0;
        }
        if ((*(WORD*)((char*)p1 + 0xaa) & 2) == 0 && m_inputY == 1 && y == 0.0 || (*(WORD*)((char*)p1 + 0xaa) & 1) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    }
    return 1;
}

int CPlayer::Unk4102e0()
{
    return unk124 <= 0 && y < 0.0 && unk128 == 0 && Unk4103a0() != 0;
}

int CPlayer::Unk410340()
{
    return pattern >= 0x96 && pattern <= 0x9c || pattern >= 0xa8 && pattern <= 0xab;
}

int CPlayer::Unk4103a0()
{
    return pattern >= 0x32 && pattern < 0x96 && (*m_opponent)->pattern != 0x61 && (*m_opponent)->pattern != 0x62 && (*m_opponent)->pattern != 0x63 && (*m_opponent)->pattern != 0x60;
}

int CPlayer::Unk410420()
{
    return pattern == 0xa3 || pattern == 0xa4 || pattern == 0xa5 || pattern == 0xa6;
}

double CPlayer::Unk410480()
{
    if (m_game->unk1364 == 2) {
        return unk118 / 10000.0 + 1.0;
    }
    if ((char)m_game->unk1370 == 1) {
        return (unk118 / 10000.0 + 1.0) / 2.0;
    }
    if ((char)m_game->unk1370 == 2) {
        return unk118 / 10000.0 + 1.0;
    }
    return (unk118 / 10000.0 + 1.0) * 2;
}

double CPlayer::Unk410530()
{
    return (unk108 * 0.5 / 10000.0 + 0.5) * unk180;
}

double CPlayer::Unk410560()
{
    if (unk178 / 10000.0 > 1.0) {
        return 1.0;
    }
    return unk178 / 10000.0;
}

void CPlayer::Unk4105a0(int p1, double p2)
{
    if (unk174 == 0) {
        (*m_opponent)->unk10c = (*m_opponent)->unk108;
    }
    (*m_opponent)->unk108 -= (int)((double)p1 * this->Unk410480() * (*m_opponent)->Unk410530() * this->Unk410560());
    unkf8 = unk178 / 100.0;
    unk178 = p2 / 1000.0 * unk178;
    if (unk178 > 10000.0) {
        unk178 = p2 / 1000.0 * unk178;
    }
    unk174++;
    unkf4 = unk174;
    unk104 = 0xb4;
    unk100 = (*m_opponent)->unk10c - (*m_opponent)->unk108;
    if ((DWORD)unk174 > unk30d4) {
        unk30d4 = unk174;
    }
    if ((unsigned long)unk100 > unk30d8) {
        unk30d8 = unk100;
    }
    unk30d0++;
    Unk410840(p1 / 0x64 * unk30d0 * unk30d4 * unk174);
}

void CPlayer::Unk410790(int p1)
{
    if ((DWORD)unk174 > unk30d4) {
        unk30d4 = unk174;
    }
    if ((unsigned long)unk100 > unk30d8) {
        unk30d8 = unk100;
    }
    unk30d0++;
    Unk410840(*(short*)((char*)p1 + 0xa0) / 0x64 * unk30d0 * unk30d4 * unk174);
}

void CPlayer::Unk410840(int p1)
{
    unk30c8 += p1;
    while ((unsigned long)unk30c8 >= 0x5f5e100) {
        unk30c8 -= 0x5f5e100;
        unk30cc++;
    }
}

short CPlayer::Unk4108a0(short p1, short p2)
{
    WORD v8;
    short v4;

    v8 = rand();
    if (m_game->unk14283 == 1) {
        v8 = (&m_game->m_replay)->Read();
    } else if (m_game->unk14283 == 2) {
        (&m_game->m_replay)->Write(v8);
    }
    v4 = p1 + (p2 - p1) * v8 / 0x8000;
    return v4;
}

void CPlayer::Unk410940()
{
    if ((*m_opponent)->unk14c == 0) {
        if (m_afterimages.unk0 > 0) {
            (&m_afterimages)->Unk412930((ObjBase*)this);
            m_afterimages.unk2 = 0;
            return;
        }
        if (m_afterimages.unk2 > 0) {
            m_afterimages.unk2--;
        }
    }
}

void CPlayer::Unk4109d0(BYTE p1)
{
    (&m_afterimages)->Unk412a10((ObjBase*)this, p1);
}

void CPlayer::Unk410a10(int p1, int p2)
{
    m_game->m_shake = p1;
    m_game->m_shakeHold = p2;
}

void CPlayer::Unk410a40(int p1, int p2)
{
    m_game->unk14238 = (1 - (m_side << 1)) * p1;
    m_game->unk14240 = p2;
}

void CPlayer::Unk410a80(int p1, int p2)
{
    m_game->unk1423c = (1 - (m_side << 1)) * p1;
    m_game->unk14244 = p2;
}

void CPlayer::Unk410ac0(BYTE p1, int p2)
{
    unk30b8 = p1;
    unk30bc = p2;
    if (m_game->unk136c == 0) {
        unk30bc = unk30bc / 2;
    }
}

void CPlayer::Unk410b10(BYTE p1, int p2)
{
    unk30c0 = p1;
    unk30c4 = p2;
    if (m_game->unk136c == 0) {
        unk30c4 = unk30c4 / 2;
    }
    m_game->unkf33 = m_side;
}

void CPlayer::Vf11()
{
    char v2c[32];
    char vc[8];

    if (unk30e8 == 0) {
        Unk411080();
        Unk4116a0();
        Unk411ae0();
        unk30e8 = 1;
    } else if (1) {
        if (m_game->unk1338[m_side] != 0) {
            strcpy(v2c, m_name);
            strcat(v2c, "\\");
            strcat(v2c, m_name);
            _itoa(m_paletteIndex + 1, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, ".pal");
            if (m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, 0, m_side * 0x28 + 0x5f, 0x28) == 0) {
                strcpy(v2c, m_name);
                strcat(v2c, "\\");
                strcat(v2c, m_name);
                strcat(v2c, ".dat");
                m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
            }
        } else {
            strcpy(v2c, m_name);
            strcat(v2c, "\\");
            strcat(v2c, m_name);
            strcat(v2c, ".dat");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    } else if (m_game->unk1338[m_side] != 0) {
        strcpy(v2c, m_name);
        strcat(v2c, "\\");
        strcat(v2c, m_name);
        _itoa(m_paletteIndex + 1, vc, 0xa);
        strcat(v2c, (const char*)vc);
        strcat(v2c, ".pal");
        if (m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, 0, m_side * 0x28 + 0x5f, 0x28) == 0) {
            strcpy(v2c, m_name);
            strcat(v2c, "\\000.bmp");
            m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    } else {
        strcpy(v2c, m_name);
        strcat(v2c, "\\000.bmp");
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
    }
    Vf12();
    if (unka4 == 0) {
        if ((m_game->unk1364 == 0 || m_game->unk1364 == 2) && m_game->unk1358 == 1) {
            ((CharRecord*)&unk3118)->Load(m_name);
            unk3118++;
            ((CharRecord*)&unk3118)->Save(m_name);
            return;
        }
        if (m_game->unk1364 == 1 || m_game->unk1364 == 3 || m_game->unk1364 == 4) {
            ((CharRecord*)&unk3118)->Load(m_name);
            unk3118++;
            ((CharRecord*)&unk3118)->Save(m_name);
        }
    }
}

void CPlayer::Unk411080()
{
    int x74;
    int v70;
    int a6c;
    char v68[32];
    int l48;
    char* x44;
    int v40;
    int h3c;
    int n38;
    int a34;
    int d30;
    char x2c[32];
    char bc[8];

    v70 = (int)operator new(lastSurface * 4 + 4);
    surfaces = (IDirectDrawSurface**)v70;
    if (1) {
        n38 = 0;
        strcpy(x2c, m_name);
        strcat(x2c, "\\");
        strcat(x2c, m_name);
        strcat(x2c, ".dat");
        d30 = (int)CreateFileA((LPCSTR)x2c, 0x80000000, 0, 0, 3, 0x80, 0);
        h3c = GetFileSize((HANDLE)d30, 0);
        x74 = (int)operator new(h3c);
        x44 = (char*)x74;
        ReadFile((HANDLE)d30, (LPVOID)x44, h3c, (LPDWORD)&v40, 0);
        n38 = *(BYTE*)x44 * 3 + 1;
        l48 = 0;
        for (; l48 <= lastSurface; l48++) {
            a34 = m_graphics->LoadSurfaceHigh(&surfaces[l48], (BYTE*)(x44 + n38), 0x80, m_side * 0x28 + 0x5f);
            if (a34 == 0) {
                _itoa(l48, v68, 0xa);
                MessageBoxA(0, (LPCSTR)v68, 0, 0);
            } else {
                n38 += a34;
            }
        }
        CloseHandle((HANDLE)d30);
        delete (char*)x44;
        if (m_game->unk1338[m_side] != 0) {
            strcpy(x2c, m_name);
            strcat(x2c, "\\");
            strcat(x2c, m_name);
            _itoa(m_paletteIndex + 1, bc, 0xa);
            strcat(x2c, (const char*)bc);
            strcat(x2c, ".pal");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)x2c, 0, m_side * 0x28 + 0x5f, 0x28);
        } else {
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)x2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    } else {
        a6c = 0;
        for (; a6c <= lastSurface; a6c++) {
            strcpy(x2c, m_name);
            strcat(x2c, "\\");
            if (a6c >= 0x3e8) {
                strcat(x2c, "A");
                _itoa(a6c, bc, 0xa);
                strcat(x2c, (const char*)bc);
                strcat(x2c, ".bmp");
                m_graphics->LoadBmpHigh(&surfaces[a6c], (const char*)x2c, m_side * 0x28 + 0x5f);
            } else {
                if (a6c < 0x64) {
                    strcat(x2c, "0");
                }
                if (a6c < 0xa) {
                    strcat(x2c, "0");
                }
                _itoa(a6c, bc, 0xa);
                strcat(x2c, (const char*)bc);
                strcat(x2c, ".bmp");
                m_graphics->LoadBmpHigh(&surfaces[a6c], (const char*)x2c, m_side * 0x28 + 0x5f);
            }
        }
        if (m_game->unk1338[m_side] != 0) {
            strcpy(x2c, m_name);
            strcat(x2c, "\\");
            strcat(x2c, m_name);
            _itoa(m_paletteIndex + 1, bc, 0xa);
            strcat(x2c, (const char*)bc);
            strcat(x2c, ".pal");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)x2c, 0, m_side * 0x28 + 0x5f, 0x28);
        } else {
            strcpy(x2c, m_name);
            strcat(x2c, "\\000.bmp");
            m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)x2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    }
    colorKey = m_graphics->GetColorKey(*surfaces);
}

void CPlayer::Unk4116a0()
{
    int c50;
    char* l4c;
    char* l48;
    int x44;
    int v40;
    int f3c;
    int x38;
    char x34[32];
    int l4;

    strcpy(x34, m_name);
    strcat(x34, "\\");
    strcat(x34, m_name);
    strcat(x34, ".pat");
    CFile k10(x34, 1);
    l4 = k10.ReadInt();
    v40 = 0;
    for (; v40 < l4; v40++) {
        x38 = k10.ReadInt();
        m_patterns[x38].unk0 = k10.ReadInt();
        m_patterns[x38].unk2 = k10.ReadInt();
        anims[x38].frameCount = k10.ReadInt();
        f3c = anims[x38].frameCount;
        (&m_patterns[x38])->Alloc(f3c);
        (&anims[x38])->Alloc(f3c);
        x44 = 0;
        for (; x44 < f3c; x44++) {
            l48 = (char*)&anims[x38].frames[x44].duration;
            l4c = (char*)&m_patterns[x38].frames[x44].boxes[0].left;
            *(short*)l48 = (short)k10.ReadInt() * 3;
            *(short*)(l48 + 2) = k10.ReadInt();
            *(short*)(l48 + 8) = k10.ReadInt();
            *(short*)(l48 + 0xa) = k10.ReadInt();
            *(short*)(l48 + 4) = k10.ReadInt();
            *(short*)(l48 + 6) = k10.ReadInt();
            *(short*)(l4c + 0xa0) = k10.ReadInt();
            *(short*)(l4c + 0xaa) = k10.ReadInt();
            *(short*)(l4c + 0xac) = k10.ReadInt();
            *(short*)(l4c + 0xb0) = k10.ReadInt();
            *(short*)(l4c + 0xb2) = k10.ReadInt();
            *(short*)(l4c + 0xa8) = k10.ReadInt();
            *(short*)(l4c + 0xb4) = k10.ReadInt();
            *(short*)(l4c + 0xb6) = k10.ReadInt();
            *(float*)(l4c + 0xbc) = (short)k10.ReadShort();
            *(float*)(l4c + 0xbc) = *(float*)(l4c + 0xbc) / 1e+02f;
            *(float*)(l4c + 0xb8) = (short)k10.ReadShort();
            *(float*)(l4c + 0xb8) = *(float*)(l4c + 0xb8) / -1e+02f;
            *(l4c + 0xc1) = k10.ReadShort();
            *(l4c + 0xc0) = k10.ReadShort();
            *(short*)(l4c + 0xc2) = k10.ReadInt();
            *(short*)(l4c + 0xc4) = k10.ReadInt();
            *(float*)(l4c + 0xa4) = k10.ReadInt();
            *(short*)(l4c + 0xae) = k10.ReadInt();
            k10.Read((void*)(l4c + 0x90), 0x10);
            c50 = 0;
            for (; c50 < 2; c50++) {
                k10.Read((void*)((c50 << 4) + l4c), 0x10);
            }
            k10.Read((void*)(l4c + 0x50), 0x10);
            c50 = 2;
            for (; c50 < 5; c50++) {
                k10.Read((void*)((c50 << 4) + l4c), 0x10);
            }
            c50 = 1;
            for (; c50 < 4; c50++) {
                k10.Read((void*)(l4c + (c50 << 4) + 0x50), 0x10);
            }
        }
    }
    v40 = 0;
    for (; v40 < 0x40; v40++) {
        m_objects[v40].anims = anims;
    }
}

void CPlayer::Unk411ae0()
{
    int v30;
    char v2c[32];
    char vc[8];

    v30 = 0;
    for (; v30 < 0x32; v30++) {
        strcpy(v2c, m_name);
        strcat(v2c, "\\wave\\");
        if (v30 < 0xa) {
            strcat(v2c, "0");
        }
        _itoa(v30, vc, 0xa);
        strcat(v2c, (const char*)vc);
        strcat(v2c, ".wav");
        unk264[v30] = m_sound->Load((const char*)v2c);
        m_sound->SetVolume(unk264[v30], -0x1f4);
    }
}

void CPlayer::Unk411be0()
{
    BYTE v1;

    if (unka4 != 0) {
        if (m_game->unk1364 == 1) {
            m_pressA = 0;
            m_pressB = 0;
            m_pressC = 0;
            m_pressD = 0;
            m_inputX = 0;
            if ((char)m_game->unk1346 == 1) {
                m_inputY = -1;
            } else if ((char)m_game->unk1346 == 2) {
                m_inputY = 1;
            } else {
                m_inputY = 0;
            }
            return;
        }
        Vf5();
        if ((char)m_game->unk1350 != 0 || m_game->unk1354 != 0) {
            m_pressA = 0;
            m_pressB = 0;
            m_pressC = 0;
            m_pressD = 0;
            unk262 = 0x63;
        }
        return;
    }
    v1 = m_input->GetInput(m_side);
    if (m_game->unk14283 == 1) {
        v1 = (&m_game->m_replay)->Read();
    } else if (m_game->unk14283 == 2) {
        (&m_game->m_replay)->Write(v1);
    }
    m_inputX = 0;
    m_inputY = 0;
    m_pressA = 0;
    m_pressB = 0;
    m_pressC = 0;
    m_pressD = 0;
    if ((v1 & 8) > 0) {
        m_inputY = -1;
    } else if ((v1 & 4) > 0) {
        m_inputY = 1;
    }
    if (facing > 0) {
        if ((v1 & 2) > 0) {
            m_inputX = -1;
        } else if ((v1 & 1) > 0) {
            m_inputX = 1;
        }
    } else if ((v1 & 1) > 0) {
        m_inputX = 1;
    } else if ((v1 & 2) > 0) {
        m_inputX = -1;
    }
    if ((v1 & 0x10) > 0) {
        m_pressA = m_holdA == 0;
        m_holdA = 1;
    } else {
        m_holdA = 0;
    }
    if ((v1 & 0x20) > 0) {
        m_pressB = m_holdB == 0;
        m_holdB = 1;
    } else {
        m_holdB = 0;
    }
    if ((v1 & 0x40) > 0) {
        m_pressC = m_holdC == 0;
        m_holdC = 1;
    } else {
        m_holdC = 0;
    }
    if ((v1 & 0x80) > 0) {
        m_pressD = m_holdD == 0;
        m_holdD = 1;
    } else {
        m_holdD = 0;
    }
    if ((char)m_game->unk1350 != 0 || m_game->unk1354 != 0) {
        m_pressA = 0;
        m_pressB = 0;
        m_pressC = 0;
        m_pressD = 0;
        unk262 = 0x63;
    }
    m_inputHistory[m_inputPos] = (m_inputX == 1) + (m_inputX == -1) * 2 + (m_inputY == 1) * 4 + (m_inputY == -1) * 8 + (m_pressA << 4) + (m_pressB << 5) + (m_pressC << 6) + (m_pressD << 7);
    if ((unsigned char)m_inputHistory[m_inputPos] >= 0x10) {
        if (pattern >= 0xc8) {
            unk1a8 = m_inputHistory[m_inputPos];
        }
        if (pattern >= 0xa3 && pattern <= 0xa6) {
            unk1a9 = m_inputHistory[m_inputPos];
            unk1aa = 0xf;
        }
    }
    m_inputPos++;
    if (m_inputPos >= 0xb4) {
        m_inputPos = 0;
    }
    if (m_inputX == 1 - (((*m_opponent)->x - x > 0.0) << 1) && unk14e == 0 && unk150 == 0) {
        unk14e = 0x3c;
    }
    if ((*m_opponent)->unk14a == 0 && unk14e > 0) {
        unk14e--;
    }
    if (m_inputX == 0) {
        unk150 = 0;
    } else {
        unk150 = 1;
    }
    Vf2();
}

void CPlayer::Unk4121a0(int p1, int p2)
{
    int v34;
    RECT v30;
    EffectFrame v20;
    RECT v14;
    int l4;

    if (m_afterimages.unk0 > 0 || m_afterimages.unk2 > 0) {
        v34 = m_afterimages.pos - (m_afterimages.unk0 * 3 + m_afterimages.unk2);
        l4 = 0;
        for (; l4 < m_afterimages.unk2 + m_afterimages.unk0 * 3; l4 = m_afterimages.unk1 + l4) {
            if (v34 >= 0x3c) {
                v34 -= 0x3c;
            }
            if (v34 < 0) {
                v34 += 0x3c;
            }
            v20 = anims[m_afterimages.pattern[v34]].frames[m_afterimages.frame[v34]];
            v30.left = 0;
            v30.top = 0;
            v30.right = v20.width;
            v30.bottom = v20.height;
            v14.left = (int)m_afterimages.x[v34] + p1 - v20.x * (m_afterimages.facing[v34] == 1) - (v20.width - v20.x) * (m_afterimages.facing[v34] == -1);
            v14.top = (int)m_afterimages.y[v34] + 0xd2 - (m_afterimages.y[v34] < 0.0) - v20.y + p2;
            v14.right = v20.width + v14.left;
            v14.bottom = v20.height + v14.top;
            m_graphics->BlitEx(v14, surfaces[v20.surface], v30, colorKey, m_afterimages.facing[v34] == -1, 0);
            v34 = m_afterimages.unk1 + v34;
        }
    }
    v20 = anims[pattern].frames[frame];
    v30.left = 0;
    v30.top = 0;
    v30.right = v20.width;
    v30.bottom = v20.height;
    v14.left = (int)x + p1 - v20.x * (facing == 1) - (v20.width - v20.x) * (facing == -1);
    v14.top = (int)y + 0xd2 - (y < 0.0) - v20.y + p2;
    v14.right = v20.width + v14.left;
    v14.bottom = v20.height + v14.top;
    if (v14.top < 0xf0) {
        if (unk30bc == 0) {
            if (unk58 == 3) {
                m_graphics->BlitSmear(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
            } else if (unk58 > 0) {
                m_graphics->BlitEx(v14, surfaces[v20.surface], v30, colorKey, facing == -1, unk58 - 1);
            } else {
                m_graphics->Blit(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
            }
        } else {
            m_graphics->BlitTint(v14, surfaces[v20.surface], v30, colorKey, facing == -1, unk30b8);
            unk30bc--;
        }
        return;
    }
    if (unk13e == 0) {
        v20 = *anims[0x31].frames;
        v30.left = 0;
        v30.top = 0;
        v30.right = v20.width;
        v30.bottom = v20.height;
        v14.left = (int)x + p1 - v20.x * (facing == 1) - (v20.width - v20.x) * (facing == -1);
        v14.top = 0xef - v20.y;
        v14.right = v20.width + v14.left;
        v14.bottom = v20.height + v14.top;
        m_graphics->Blit(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
    }
}
