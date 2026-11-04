// Stage 10's animated background, CBg10 (0x751a40-0x7520af). Like the other three, CScene2
// makes it when the stage needs one.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CBg10::CBg10(CGraphics* graphics)
    : CAnimBg()
{
    int objects; // the block for m_objects
    int surfaces; // the block for m_surfaces, a pointer per frame
    int i;

    m_graphics = graphics;
    m_number = 0xa;
    m_lastFrame = 4;
    surfaces = TOINT(int, operator new(0x14));
    m_surfaces = TOPTR(PTR32(IDirectDrawSurface)*, surfaces);
    objects = TOINT(int, operator new(0x70));
    m_objects = TOPTR(BgObject*, objects);
    m_anims = new EffectAnim[1];
    CAnimBg::Load();
    CAnimBg::LoadAnims();
    i = 0;
    for (; i < 1; i++) {
        m_objects[i].pattern = i;
        m_objects[i].x = 0.0;
        m_objects[i].y = -450.0;
        m_objects[i].frame = 0;
        m_objects[i].timer = 0;
        m_objects[i].facing = 1;
        m_objects[i].scale = 2;
        m_objects[i].layer = 1;
    }
}

CBg10::~CBg10()
{
    int i;

    i = 0;
    for (; i < 5; i++) {
        if ((int)m_surfaces[i] != 0) {
            m_surfaces[i]->Release();
            m_surfaces[i] = (IDirectDrawSurface*)0;
        }
    }
    delete (char*)m_surfaces;
    delete (char*)m_objects;
    delete m_anims;
}

void CBg10::Update()
{
    WORD frameCount; // frames in the object's animation
    WORD duration; // ticks the object's current frame lasts
    int i;

    i = 0;
    for (; i < 1; i++) {
        duration = (short)m_anims[m_objects[i].pattern].frames[m_objects[i].frame].duration;
        frameCount = m_anims[m_objects[i].pattern].frameCount;
        switch (m_objects[i].pattern) {
        case kStand:
        case kWalkForward:
            m_objects[i].timer++;
            if (m_objects[i].timer >= duration) {
                m_objects[i].timer = 0;
                m_objects[i].frame++;
                if (m_objects[i].frame >= frameCount) {
                    m_objects[i].frame = 0;
                }
            }
        }
    }
}

void CBg10::Draw(int x, int y, char layer)
{
    int i;
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (layer == 0) {
        return;
    }
    i = 0;
    for (; i < 1; i++) {
        sprite = m_anims[m_objects[i].pattern].frames[m_objects[i].frame];
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_objects[i].facing == -1) {
            dst.left = (int)m_objects[i].x + x - (sprite.width - sprite.x);
            dst.top = y + (int)m_objects[i].y + 0xd2 - sprite.y;
            dst.right = sprite.width + dst.left;
            dst.bottom = sprite.height + dst.top;
        } else {
            dst.left = (int)m_objects[i].x + x - sprite.x;
            dst.top = y + (int)m_objects[i].y + 0xd2 - sprite.y;
            dst.right = sprite.width + dst.left;
            dst.bottom = sprite.height + dst.top;
        }
        if (m_objects[i].scale > 0) {
            m_graphics->BlitEx(dst, m_surfaces[sprite.surface], src, m_colorKey, m_objects[i].facing == -1, m_objects[i].scale - 1);
        } else {
            m_graphics->Blit(dst, m_surfaces[sprite.surface], src, m_colorKey, m_objects[i].facing == -1);
        }
    }
}
