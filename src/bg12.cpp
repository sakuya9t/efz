// Stage 12's animated background, CBg12 (0x7520b0-0x7528ff): two layers that scroll
// sideways, each drawn twice to wrap around.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CBg12::CBg12(CGraphics* p1)
    : CAnimBg()
{
    int xc;
    int v8;
    int v4;

    m_graphics = p1;
    m_number = 0xc;
    m_lastFrame = 1;
    v8 = (int)operator new(8);
    m_surfaces = (IDirectDrawSurface**)v8;
    xc = (int)operator new(0xe0);
    m_objects = (BgObject*)xc;
    m_anims = new EffectAnim[2];
    CAnimBg::Load();
    CAnimBg::Unk751030();
    v4 = 0;
    for (; v4 < 2; v4++) {
        m_objects[v4].pattern = v4;
        m_objects[v4].x = 0.0;
        m_objects[v4].y = -450.0;
        m_objects[v4].frame = 0;
        m_objects[v4].timer = 0;
        m_objects[v4].facing = 1;
        m_objects[v4].scale = 2;
        m_objects[v4].layer = 1 - v4;
    }
}

CBg12::~CBg12()
{
    int v4;

    v4 = 0;
    for (; v4 < 2; v4++) {
        if ((int)m_surfaces[v4] != 0) {
            m_surfaces[v4]->Release();
            m_surfaces[v4] = (IDirectDrawSurface*)0;
        }
    }
    delete (char*)m_surfaces;
    delete (char*)m_objects;
    delete m_anims;
}

void CBg12::Vf0()
{
    short xc;
    short v8;
    int v4;

    v4 = 0;
    for (; v4 < 2; v4++) {
        v8 = (short)m_anims[m_objects[v4].pattern].frames[m_objects[v4].frame].duration;
        xc = m_anims[m_objects[v4].pattern].frameCount;
        switch (m_objects[v4].pattern) {
        case 0:
            m_objects[v4].x += 0.5;
            if (m_objects[v4].x >= 640.0) {
                m_objects[v4].x = 0.0;
            }
        case 1:
            m_objects[v4].x += 0.25;
            if (m_objects[v4].x >= 640.0) {
                m_objects[v4].x = 0.0;
            }
        }
    }
}

void CBg12::Vf1(int p1, int p2, char p3)
{
    int l40;
    RECT v3c;
    EffectFrame v2c;
    RECT v20;
    RECT v10;

    l40 = 0;
    for (; l40 < 2; l40++) {
        if (p3 != (unsigned char)m_objects[l40].layer) {
            continue;
        }
        v2c = m_anims[m_objects[l40].pattern].frames[m_objects[l40].frame];
        v3c = MakeRect(0, 0, v2c.width, v2c.height);
        if (m_objects[l40].facing == -1) {
            v20.left = (int)m_objects[l40].x + p1 - (v2c.width - v2c.x);
            v20.top = p2 + (int)m_objects[l40].y + 0xd2 - v2c.y;
            v20.right = v2c.width + v20.left;
            v20.bottom = v2c.height + v20.top;
            v10.left = (int)m_objects[l40].x + p1 - (v2c.width - v2c.x) - 0x280;
            v10.top = p2 + (int)m_objects[l40].y + 0xd2 - v2c.y;
            v10.right = v2c.width + v10.left;
            v10.bottom = v2c.height + v10.top;
        } else {
            v20.left = (int)m_objects[l40].x + p1 - v2c.x;
            v20.top = p2 + (int)m_objects[l40].y + 0xd2 - v2c.y;
            v20.right = v2c.width + v20.left;
            v20.bottom = v2c.height + v20.top;
            v10.left = (int)m_objects[l40].x + p1 - v2c.x - 0x280;
            v10.top = p2 + (int)m_objects[l40].y + 0xd2 - v2c.y;
            v10.right = v2c.width + v10.left;
            v10.bottom = v2c.height + v10.top;
        }
        if (m_objects[l40].scale > 0) {
            m_graphics->BlitEx(v20, m_surfaces[v2c.surface], v3c, m_colorKey, m_objects[l40].facing == -1, m_objects[l40].scale - 1);
            m_graphics->BlitEx(v10, m_surfaces[v2c.surface], v3c, m_colorKey, m_objects[l40].facing == -1, m_objects[l40].scale - 1);
        } else {
            m_graphics->Blit(v20, m_surfaces[v2c.surface], v3c, m_colorKey, m_objects[l40].facing == -1);
            m_graphics->Blit(v10, m_surfaces[v2c.surface], v3c, m_colorKey, m_objects[l40].facing == -1);
        }
    }
}
