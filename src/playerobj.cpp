// Seventh object of efz.exe (0x412b10-0x4136cf): CPlayer's table of 64 objects
// (projectiles and other things a character spawns), with the slots used and freed in
// a ring, and drawing them.
#include <stdlib.h>
#include <string.h>
#include "efz.h"

void CPlayer::SpawnObject(EffectDesc* p1)
{
    m_objectActive[m_objectHead] = 1;
    unk2d0[m_objectHead] = p1->unk0;
    m_objects[m_objectHead].pattern = p1->type;
    m_objects[m_objectHead].frame = 0;
    m_objects[m_objectHead].timer = 0;
    m_objects[m_objectHead].x = p1->x;
    m_objects[m_objectHead].y = p1->y;
    m_objects[m_objectHead].vx = 0.0;
    m_objects[m_objectHead].vy = 0.0;
    m_objects[m_objectHead].ax = 0.0;
    m_objects[m_objectHead].ay = 0.0;
    m_objects[m_objectHead].facing = (char)p1->unk18;
    m_objects[m_objectHead].side = p1->side;
    m_objects[m_objectHead].scale = (char)p1->scale;
    m_objects[m_objectHead].unk6c = (char)p1->unk2c;
    m_objects[m_objectHead].screen = p1->screen;
    m_objects[m_objectHead].layer = (char)p1->layer;
    m_objects[m_objectHead].unk58 = p1->unk28;
    m_objects[m_objectHead].unk88 = p1->unk30;
    m_objects[m_objectHead].unk8c = 0;
    m_objects[m_objectHead].clip = *(tagRECT*)&p1->unk34;
    m_objects[m_objectHead].unk80 = 0;
    m_objects[m_objectHead].unk84 = 0;
    m_objects[m_objectHead].unk86 = 0;
    m_objects[m_objectHead].unk70 = 0.0;
    m_objects[m_objectHead].unk78 = 0.0;
    AdvanceObjectHead();
}

void CPlayer::RemoveObject(short p1)
{
    m_objectActive[p1] = 0;
    unk2d0[p1] = 0;
    if (p1 == m_objectTail) {
        while (m_objectTail != m_objectHead && m_objectActive[m_objectTail] == 0) {
            m_objectTail++;
            if (m_objectTail >= 0x40) {
                m_objectTail = 0;
            }
        }
    }
}

void CPlayer::AdvanceObjectHead()
{
    int v4;

    v4 = 0;
    do {
        m_objectHead++;
        if (m_objectHead >= 0x40) {
            m_objectHead = 0;
        }
        if (m_objectHead == m_objectTail) {
            m_objectTail++;
            if (m_objectTail >= 0x40) {
                m_objectTail = 0;
            }
            while (m_objectTail != m_objectHead && m_objectActive[m_objectTail] == 0) {
                m_objectTail++;
                if (m_objectTail >= 0x40) {
                    m_objectTail = 0;
                }
            }
        }
        v4++;
    } while (unk2d0[m_objectHead] != 0 && v4 < 0x3f);
}

void CPlayer::ClearObjects()
{
    int v4;

    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectActive[v4] = 0;
        unk2d0[v4] = 0;
    }
}

void CPlayer::InitEffectDesc(EffectDesc* p1)
{
    p1->unk0 = 0;
    p1->scale = 0;
    p1->unk2c = -1;
    p1->screen = 0;
    p1->unk28 = 0;
    p1->unk30 = 0;
    p1->unk38 = 0;
    p1->unk40 = 0;
    p1->unk34 = 0;
    p1->unk3c = 0;
}

void CPlayer::DrawObjects(int p1, int p2, BYTE p3)
{
    RECT v28;
    char* v18;
    RECT v14;
    int l4;

    l4 = m_objectTail;
    while (l4 != m_objectHead) {
        if (m_objectActive[l4] != 0 && p3 == (unsigned char)m_objects[l4].layer && (m_objects[l4].unk8c != 0 || m_game->unk1420e == 0)) {
            v18 = (char*)&anims[m_objects[l4].pattern].frames[m_objects[l4].frame].duration;
            v28 = MakeRect(0, 0, *(short*)(v18 + 8), *(short*)(v18 + 0xa));
            if (m_objects[l4].facing == -1) {
                v14.left = (int)m_objects[l4].x + (m_objects[l4].screen == 0) * p1 - (*(short*)(v18 + 8) - *(short*)(v18 + 4));
                v14.top = (p2 + 0xd2) * (m_objects[l4].screen == 0) + (int)m_objects[l4].y - *(short*)(v18 + 6);
                v14.right = *(short*)(v18 + 8) + v14.left;
                v14.bottom = *(short*)(v18 + 0xa) + v14.top;
            } else {
                v14.left = (int)m_objects[l4].x + (m_objects[l4].screen == 0) * p1 - *(short*)(v18 + 4);
                v14.top = (p2 + 0xd2) * (m_objects[l4].screen == 0) + (int)m_objects[l4].y - *(short*)(v18 + 6);
                v14.right = *(short*)(v18 + 8) + v14.left;
                v14.bottom = *(short*)(v18 + 0xa) + v14.top;
            }
            if (m_objects[l4].clip.top != m_objects[l4].clip.bottom) {
                if (v14.left < m_objects[l4].clip.left) {
                    v28.left = m_objects[l4].clip.left - v14.left + v28.left;
                    v14.left = m_objects[l4].clip.left;
                }
                if (v14.right > m_objects[l4].clip.right) {
                    v28.right -= v14.right - m_objects[l4].clip.right;
                    v14.right = m_objects[l4].clip.right;
                }
                if (v14.top < m_objects[l4].clip.top) {
                    v28.top = m_objects[l4].clip.top - v14.top + v28.top;
                    v14.top = m_objects[l4].clip.top;
                }
                if (v14.bottom > m_objects[l4].clip.bottom) {
                    v28.bottom -= v14.bottom - m_objects[l4].clip.bottom;
                    v14.bottom = m_objects[l4].clip.bottom;
                }
            }
            if (m_objects[l4].scale == 3) {
                m_graphics->BlitSmear(v14, surfaces[*(WORD*)(v18 + 2)], v28, colorKey, m_objects[l4].facing == -1);
            } else if (m_objects[l4].scale > 0) {
                m_graphics->BlitEx(v14, surfaces[*(WORD*)(v18 + 2)], v28, colorKey, m_objects[l4].facing == -1, m_objects[l4].scale - 1);
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
