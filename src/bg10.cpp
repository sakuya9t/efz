// Stage 10's animated background, CBg10 (0x751a40-0x7520af). Like the other three, CScene2
// makes it when the stage needs one.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CBg10::CBg10(CGraphics* p1)
    : CAnimBg()
{
    int xc;
    int v8;
    int v4;

    m_graphics = p1;
    m_number = 0xa;
    m_lastFrame = 4;
    v8 = TOINT(int, operator new(0x14));
    m_surfaces = TOPTR(PTR32(IDirectDrawSurface)*, v8);
    xc = TOINT(int, operator new(0x70));
    m_objects = TOPTR(BgObject*, xc);
    m_anims = new EffectAnim[1];
    CAnimBg::Load();
    CAnimBg::LoadAnims();
    v4 = 0;
    for (; v4 < 1; v4++) {
        m_objects[v4].pattern = v4;
        m_objects[v4].x = 0.0;
        m_objects[v4].y = -450.0;
        m_objects[v4].frame = 0;
        m_objects[v4].timer = 0;
        m_objects[v4].facing = 1;
        m_objects[v4].scale = 2;
        m_objects[v4].layer = 1;
    }
}

CBg10::~CBg10()
{
    int v4;

    v4 = 0;
    for (; v4 < 5; v4++) {
        if ((int)m_surfaces[v4] != 0) {
            m_surfaces[v4]->Release();
            m_surfaces[v4] = (IDirectDrawSurface*)0;
        }
    }
    delete (char*)m_surfaces;
    delete (char*)m_objects;
    delete m_anims;
}

void CBg10::Update()
{
    WORD xc;
    WORD v8;
    int v4;

    v4 = 0;
    for (; v4 < 1; v4++) {
        v8 = (short)m_anims[m_objects[v4].pattern].frames[m_objects[v4].frame].duration;
        xc = m_anims[m_objects[v4].pattern].frameCount;
        switch (m_objects[v4].pattern) {
        case kStand:
        case kWalkForward:
            m_objects[v4].timer++;
            if (m_objects[v4].timer >= v8) {
                m_objects[v4].timer = 0;
                m_objects[v4].frame++;
                if (m_objects[v4].frame >= xc) {
                    m_objects[v4].frame = 0;
                }
            }
        }
    }
}

void CBg10::Draw(int p1, int p2, char p3)
{
    int v30;
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (p3 == 0) {
        return;
    }
    v30 = 0;
    for (; v30 < 1; v30++) {
        x1c = m_anims[m_objects[v30].pattern].frames[m_objects[v30].frame];
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_objects[v30].facing == -1) {
            v10.left = (int)m_objects[v30].x + p1 - (x1c.width - x1c.x);
            v10.top = p2 + (int)m_objects[v30].y + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        } else {
            v10.left = (int)m_objects[v30].x + p1 - x1c.x;
            v10.top = p2 + (int)m_objects[v30].y + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        }
        if (m_objects[v30].scale > 0) {
            m_graphics->BlitEx(v10, m_surfaces[x1c.surface], v2c, m_colorKey, m_objects[v30].facing == -1, m_objects[v30].scale - 1);
        } else {
            m_graphics->Blit(v10, m_surfaces[x1c.surface], v2c, m_colorKey, m_objects[v30].facing == -1);
        }
    }
}
