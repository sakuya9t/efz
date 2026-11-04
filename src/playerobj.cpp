// Seventh object of efz.exe (0x412b10-0x4136cf): CPlayer's table of 64 objects
// (projectiles and other things a character spawns), with the slots used and freed in
// a ring, and drawing them.
#include <stdlib.h>
#include <string.h>
#include "efz.h"

void CPlayer::SpawnObject(EffectDesc* desc)
{
    m_objectActive[m_objectHead] = 1;
    m_objectKeep[m_objectHead] = desc->keep;
    m_objects[m_objectHead].pattern = desc->type;
    m_objects[m_objectHead].frame = 0;
    m_objects[m_objectHead].timer = 0;
    m_objects[m_objectHead].x = desc->x;
    m_objects[m_objectHead].y = desc->y;
    m_objects[m_objectHead].vx = 0.0;
    m_objects[m_objectHead].vy = 0.0;
    m_objects[m_objectHead].ax = 0.0;
    m_objects[m_objectHead].ay = 0.0;
    m_objects[m_objectHead].facing = (char)desc->facing;
    m_objects[m_objectHead].side = desc->side;
    m_objects[m_objectHead].scale = (char)desc->scale;
    m_objects[m_objectHead].sound = (char)desc->sound;
    m_objects[m_objectHead].screen = desc->screen;
    m_objects[m_objectHead].layer = (char)desc->layer;
    m_objects[m_objectHead].shadow = desc->shadow;
    m_objects[m_objectHead].movesInFreeze = desc->movesInFreeze;
    m_objects[m_objectHead].drawnWhileHidden = 0;
    m_objects[m_objectHead].clip = desc->clip;
    m_objects[m_objectHead].attackResult = 0;
    m_objects[m_objectHead].hitsLeft = 0;
    m_objects[m_objectHead].hitstop = 0;
    m_objects[m_objectHead].unk70 = 0.0;
    m_objects[m_objectHead].unk78 = 0.0;
    AdvanceObjectHead();
}

void CPlayer::RemoveObject(short slot)
{
    m_objectActive[slot] = 0;
    m_objectKeep[slot] = 0;
    if (slot == m_objectTail) {
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
    int tries; // slots stepped over, at most 63

    tries = 0;
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
        tries++;
    } while (m_objectKeep[m_objectHead] != 0 && tries < 0x3f);
}

void CPlayer::ClearObjects()
{
    int i;

    i = 0;
    for (; i < 0x40; i++) {
        m_objectActive[i] = 0;
        m_objectKeep[i] = 0;
    }
}

void CPlayer::InitEffectDesc(EffectDesc* effect)
{
    effect->keep = 0;
    effect->scale = 0;
    effect->sound = -1;
    effect->screen = 0;
    effect->shadow = 0;
    effect->movesInFreeze = 0;
    effect->clip.top = 0;
    effect->clip.bottom = 0;
    effect->clip.left = 0;
    effect->clip.right = 0;
}

void CPlayer::DrawObjects(int drawX, int drawY, BYTE layer)
{
    RECT src; // the part of the sprite drawn
    EffectFrame* sprite; // the frame drawn
    RECT dst; // where on the screen
    int slot; // the object drawn, an index into m_objects

    slot = m_objectTail;
    while (slot != m_objectHead) {
        if (m_objectActive[slot] != 0 && layer == (unsigned char)m_objects[slot].layer && (m_objects[slot].drawnWhileHidden != 0 || m_game->m_hideObjectsTime == 0)) {
            sprite = &anims[m_objects[slot].pattern].frames[m_objects[slot].frame];
            src = MakeRect(0, 0, sprite->width, sprite->height);
            if (m_objects[slot].facing == -1) {
                dst.left = (int)m_objects[slot].x + (m_objects[slot].screen == 0) * drawX - (sprite->width - sprite->x);
                dst.top = (drawY + 0xd2) * (m_objects[slot].screen == 0) + (int)m_objects[slot].y - sprite->y;
                dst.right = sprite->width + dst.left;
                dst.bottom = sprite->height + dst.top;
            } else {
                dst.left = (int)m_objects[slot].x + (m_objects[slot].screen == 0) * drawX - sprite->x;
                dst.top = (drawY + 0xd2) * (m_objects[slot].screen == 0) + (int)m_objects[slot].y - sprite->y;
                dst.right = sprite->width + dst.left;
                dst.bottom = sprite->height + dst.top;
            }
            if (m_objects[slot].clip.top != m_objects[slot].clip.bottom) {
                if (dst.left < m_objects[slot].clip.left) {
                    src.left = m_objects[slot].clip.left - dst.left + src.left;
                    dst.left = m_objects[slot].clip.left;
                }
                if (dst.right > m_objects[slot].clip.right) {
                    src.right -= dst.right - m_objects[slot].clip.right;
                    dst.right = m_objects[slot].clip.right;
                }
                if (dst.top < m_objects[slot].clip.top) {
                    src.top = m_objects[slot].clip.top - dst.top + src.top;
                    dst.top = m_objects[slot].clip.top;
                }
                if (dst.bottom > m_objects[slot].clip.bottom) {
                    src.bottom -= dst.bottom - m_objects[slot].clip.bottom;
                    dst.bottom = m_objects[slot].clip.bottom;
                }
            }
            if (m_objects[slot].scale == 3) {
                m_graphics->BlitSmear(dst, surfaces[sprite->surface], src, colorKey, m_objects[slot].facing == -1);
            } else if (m_objects[slot].scale > 0) {
                m_graphics->BlitEx(dst, surfaces[sprite->surface], src, colorKey, m_objects[slot].facing == -1, m_objects[slot].scale - 1);
            } else {
                m_graphics->Blit(dst, surfaces[sprite->surface], src, colorKey, m_objects[slot].facing == -1);
            }
        }
        slot++;
        if (slot >= 0x40) {
            slot = 0;
        }
    }
}
