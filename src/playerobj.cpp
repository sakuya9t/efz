// Seventh object of efz.exe (0x412b10-0x4136cf): CPlayer's table of 64 objects
// (projectiles and other things a character spawns), with the slots used and freed in
// a ring, and drawing them.
#include <stdlib.h>
#include <string.h>
#include "efz.h"

void CPlayer::Vf9(EffectDesc* p1)
{
    unk3d0[unk2ca] = 1;
    unk2d0[unk2ca] = p1->unk0;
    m_objects[unk2ca].pattern = p1->type;
    m_objects[unk2ca].frame = 0;
    m_objects[unk2ca].timer = 0;
    m_objects[unk2ca].x = p1->x;
    m_objects[unk2ca].y = p1->y;
    m_objects[unk2ca].vx = 0.0;
    m_objects[unk2ca].vy = 0.0;
    m_objects[unk2ca].ax = 0.0;
    m_objects[unk2ca].ay = 0.0;
    m_objects[unk2ca].facing = (char)p1->unk18;
    m_objects[unk2ca].unk4c = p1->side;
    m_objects[unk2ca].unk50 = (char)p1->unk20;
    m_objects[unk2ca].unk6c = (char)p1->unk2c;
    m_objects[unk2ca].unk54 = p1->unk24;
    m_objects[unk2ca].unk51 = (char)p1->unk21;
    m_objects[unk2ca].unk58 = p1->unk28;
    m_objects[unk2ca].unk88 = p1->unk30;
    m_objects[unk2ca].unk8c = 0;
    m_objects[unk2ca].unk5c = *(tagRECT*)&p1->unk34;
    m_objects[unk2ca].unk80 = 0;
    m_objects[unk2ca].unk84 = 0;
    m_objects[unk2ca].unk86 = 0;
    m_objects[unk2ca].unk70 = 0.0;
    m_objects[unk2ca].unk78 = 0.0;
    Unk412f10();
}

void CPlayer::Vf10(short p1)
{
    unk3d0[p1] = 0;
    unk2d0[p1] = 0;
    if (p1 == unk2cc) {
        while (unk2cc != unk2ca && unk3d0[unk2cc] == 0) {
            unk2cc++;
            if (unk2cc >= 0x40) {
                unk2cc = 0;
            }
        }
    }
}

void CPlayer::Unk412f10()
{
    int v4;

    v4 = 0;
    do {
        unk2ca++;
        if (unk2ca >= 0x40) {
            unk2ca = 0;
        }
        if (unk2ca == unk2cc) {
            unk2cc++;
            if (unk2cc >= 0x40) {
                unk2cc = 0;
            }
            while (unk2cc != unk2ca && unk3d0[unk2cc] == 0) {
                unk2cc++;
                if (unk2cc >= 0x40) {
                    unk2cc = 0;
                }
            }
        }
        v4++;
    } while (unk2d0[unk2ca] != 0 && v4 < 0x3f);
}

void CPlayer::Unk413040()
{
    int v4;

    v4 = 0;
    for (; v4 < 0x40; v4++) {
        unk3d0[v4] = 0;
        unk2d0[v4] = 0;
    }
}

void CPlayer::Unk413090(EffectDesc* p1)
{
    p1->unk0 = 0;
    p1->unk20 = 0;
    p1->unk2c = -1;
    p1->unk24 = 0;
    p1->unk28 = 0;
    p1->unk30 = 0;
    p1->unk38 = 0;
    p1->unk40 = 0;
    p1->unk34 = 0;
    p1->unk3c = 0;
}

void CPlayer::Unk413100(int p1, int p2, BYTE p3)
{
    RECT v28;
    char* v18;
    RECT v14;
    int l4;

    l4 = unk2cc;
    while (l4 != unk2ca) {
        if (unk3d0[l4] != 0 && p3 == (unsigned char)m_objects[l4].unk51 && (m_objects[l4].unk8c != 0 || m_game->unk1420e == 0)) {
            v18 = (char*)&anims[m_objects[l4].pattern].frames[m_objects[l4].frame].duration;
            v28 = MakeRect(0, 0, *(short*)(v18 + 8), *(short*)(v18 + 0xa));
            if (m_objects[l4].facing == -1) {
                v14.left = (int)m_objects[l4].x + (m_objects[l4].unk54 == 0) * p1 - (*(short*)(v18 + 8) - *(short*)(v18 + 4));
                v14.top = (p2 + 0xd2) * (m_objects[l4].unk54 == 0) + (int)m_objects[l4].y - *(short*)(v18 + 6);
                v14.right = *(short*)(v18 + 8) + v14.left;
                v14.bottom = *(short*)(v18 + 0xa) + v14.top;
            } else {
                v14.left = (int)m_objects[l4].x + (m_objects[l4].unk54 == 0) * p1 - *(short*)(v18 + 4);
                v14.top = (p2 + 0xd2) * (m_objects[l4].unk54 == 0) + (int)m_objects[l4].y - *(short*)(v18 + 6);
                v14.right = *(short*)(v18 + 8) + v14.left;
                v14.bottom = *(short*)(v18 + 0xa) + v14.top;
            }
            if (m_objects[l4].unk5c.top != m_objects[l4].unk5c.bottom) {
                if (v14.left < m_objects[l4].unk5c.left) {
                    v28.left = m_objects[l4].unk5c.left - v14.left + v28.left;
                    v14.left = m_objects[l4].unk5c.left;
                }
                if (v14.right > m_objects[l4].unk5c.right) {
                    v28.right -= v14.right - m_objects[l4].unk5c.right;
                    v14.right = m_objects[l4].unk5c.right;
                }
                if (v14.top < m_objects[l4].unk5c.top) {
                    v28.top = m_objects[l4].unk5c.top - v14.top + v28.top;
                    v14.top = m_objects[l4].unk5c.top;
                }
                if (v14.bottom > m_objects[l4].unk5c.bottom) {
                    v28.bottom -= v14.bottom - m_objects[l4].unk5c.bottom;
                    v14.bottom = m_objects[l4].unk5c.bottom;
                }
            }
            if (m_objects[l4].unk50 == 3) {
                m_graphics->BlitSmear(v14, surfaces[*(WORD*)(v18 + 2)], v28, colorKey, m_objects[l4].facing == -1);
            } else if (m_objects[l4].unk50 > 0) {
                m_graphics->BlitEx(v14, surfaces[*(WORD*)(v18 + 2)], v28, colorKey, m_objects[l4].facing == -1, m_objects[l4].unk50 - 1);
            } else {
                m_graphics->Blit(v14, surfaces[*(WORD*)(v18 + 2)], v28, colorKey, m_objects[l4].facing == -1);
            }
        }
        l4++;
        if (l4 >= 0x40) {
            l4 = 0;
        }
    }
}
