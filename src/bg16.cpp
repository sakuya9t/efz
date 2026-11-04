// Stage 16's animated background, CBg16 (0x752900-0x75325f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CBg16::CBg16(CGraphics* graphics)
    : CAnimBg()
{
    int objects; // the block for m_objects
    int surfaces; // the block for m_surfaces, a pointer per frame
    int i;

    m_graphics = graphics;
    m_number = 16;
    m_lastFrame = 3;
    surfaces = TOINT(int, operator new(0x10));
    m_surfaces = TOPTR(PTR32(IDirectDrawSurface)*, surfaces);
    objects = TOINT(int, operator new(0x1c0));
    m_objects = TOPTR(BgObject*, objects);
    m_anims = new EffectAnim[4];
    CAnimBg::Load();
    CAnimBg::LoadAnims();
    i = 0;
    for (; i < 4; i++) {
        m_objects[i].pattern = i;
        m_objects[i].x = 0.0;
        m_objects[i].y = -450.0;
        m_objects[i].frame = 0;
        m_objects[i].timer = 0;
        m_objects[i].facing = 1;
        m_objects[i].scale = 2;
        m_objects[i].layer = i > 1;
    }
}

CBg16::~CBg16()
{
    int i;

    i = 0;
    for (; i < 4; i++) {
        if ((int)m_surfaces[i] != 0) {
            m_surfaces[i]->Release();
            m_surfaces[i] = (IDirectDrawSurface*)0;
        }
    }
    delete (char*)m_surfaces;
    delete (char*)m_objects;
    delete m_anims;
}

void CBg16::Update()
{
    short frameCount; // frames in the object's animation; unused too
    short duration; // ticks the object's current frame lasts; unused, the objects only scroll
    int i;

    i = 0;
    for (; i < 4; i++) {
        duration = (short)m_anims[m_objects[i].pattern].frames[m_objects[i].frame].duration;
        frameCount = m_anims[m_objects[i].pattern].frameCount;
        switch (m_objects[i].pattern) {
        case kStand:
            m_objects[i].x++;
            if (m_objects[i].x >= 850.0) {
                m_objects[i].x -= 850.0;
            }
            break;
        case kWalkForward:
            m_objects[i].x += 1.4;
            if (m_objects[i].x >= 806.0) {
                m_objects[i].x -= 806.0;
            }
            break;
        case kWalkBack:
            m_objects[i].x += 1.8;
            if (m_objects[i].x >= 789.0) {
                m_objects[i].x -= 789.0;
            }
            break;
        case kCrouch:
            m_objects[i].x += 2.2;
            if (m_objects[i].x >= 947.0) {
                m_objects[i].x = 947.0;
            }
        }
    }
}

void CBg16::Draw(int x, int y, char layer)
{
    int i;
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen
    RECT wrapDst; // a second copy left of dst, so the scrolling layer wraps around

    i = 0;
    for (; i < 4; i++) {
        if (layer != (unsigned char)m_objects[i].layer) {
            continue;
        }
        sprite = m_anims[m_objects[i].pattern].frames[m_objects[i].frame];
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_objects[i].facing == -1) {
            dst.left = (int)m_objects[i].x + x - (sprite.width - sprite.x);
            dst.top = y + (int)m_objects[i].y + 210 - sprite.y;
            dst.right = sprite.width + dst.left;
            dst.bottom = sprite.height + dst.top;
            wrapDst.left = (int)m_objects[i].x + x - (sprite.width - sprite.x) - sprite.width;
            wrapDst.top = y + (int)m_objects[i].y + 210 - sprite.y;
            wrapDst.right = sprite.width + wrapDst.left;
            wrapDst.bottom = sprite.height + wrapDst.top;
        } else {
            dst.left = (int)m_objects[i].x + x - sprite.x;
            dst.top = y + (int)m_objects[i].y + 210 - sprite.y;
            dst.right = sprite.width + dst.left;
            dst.bottom = sprite.height + dst.top;
            wrapDst.left = (int)m_objects[i].x + x - sprite.x - sprite.width;
            wrapDst.top = y + (int)m_objects[i].y + 210 - sprite.y;
            wrapDst.right = sprite.width + wrapDst.left;
            wrapDst.bottom = sprite.height + wrapDst.top;
        }
        if (m_objects[i].scale > 0) {
            m_graphics->BlitEx(dst, m_surfaces[sprite.surface], src, m_colorKey, m_objects[i].facing == -1, m_objects[i].scale - 1);
            m_graphics->BlitEx(wrapDst, m_surfaces[sprite.surface], src, m_colorKey, m_objects[i].facing == -1, m_objects[i].scale - 1);
        } else {
            m_graphics->Blit(dst, m_surfaces[sprite.surface], src, m_colorKey, m_objects[i].facing == -1);
            m_graphics->Blit(wrapDst, m_surfaces[sprite.surface], src, m_colorKey, m_objects[i].facing == -1);
        }
    }
}
