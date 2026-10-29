// First of the scene objects (0x750d30-0x751a3f): CAnimBg, the animated stage
// backgrounds' base, which loads the frames (system\bg\bgNN\MMM.dat) and the animation
// table (system\bg\bgNN\bgNN.pat), and stage 01's background, CBg01. The inline
// methods it uses first follow it (0x7519f0-0x751a3f): CAnimBg's constructor and
// FUNCTION: 0x751a10 ??_GEffectAnim@@QAEPAXI@Z
//   EffectAnim's scalar deleting destructor, for `delete` of the animation table
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CAnimBg::Load()
{
    int v48;
    int f44;
    char* h40;
    int a3c;
    int v38;
    int v34;
    int v30;
    char v2c[32];
    char vc[8];

    if (1) {
        v30 = 0;
        for (; v30 <= m_lastFrame; v30++) {
            if (m_number >= 0xa) {
                strcpy(v2c, "system\\bg\\bg");
            } else {
                strcpy(v2c, "system\\bg\\bg0");
            }
            _itoa(m_number, vc, 0xa);
            strcat(v2c, (const char*)vc);
            if (v30 >= 0x64) {
                strcat(v2c, "\\");
            } else if (v30 >= 0xa) {
                strcat(v2c, "\\0");
            } else {
                strcat(v2c, "\\00");
            }
            _itoa(v30, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, ".dat");
            v34 = (int)CreateFileA((LPCSTR)v2c, 0x80000000, 0, 0, 3, 0x80, 0);
            v38 = GetFileSize((HANDLE)v34, 0);
            v48 = (int)operator new(v38);
            h40 = (char*)v48;
            ReadFile((HANDLE)v34, (LPVOID)h40, v38, (LPDWORD)&a3c, 0);
            m_graphics->LoadSurface(&m_surfaces[v30], (BYTE*)(h40 + *(BYTE*)h40 * 3 + 1), 0, 1);
            CloseHandle((HANDLE)v34);
            delete (char*)h40;
        }
    } else {
        f44 = 0;
        for (; f44 <= m_lastFrame; f44++) {
            if (m_number >= 0xa) {
                strcpy(v2c, "system\\bg\\bg");
            } else {
                strcpy(v2c, "system\\bg\\bg0");
            }
            _itoa(m_number, vc, 0xa);
            strcat(v2c, (const char*)vc);
            if (f44 >= 0x64) {
                strcat(v2c, "\\");
            } else if (f44 >= 0xa) {
                strcat(v2c, "\\0");
            } else {
                strcat(v2c, "\\00");
            }
            _itoa(f44, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, ".bmp");
            m_graphics->LoadBmp(&m_surfaces[f44], (const char*)v2c, 1);
        }
    }
    m_colorKey = m_graphics->GetColorKey(*m_surfaces);
}

void CAnimBg::Unk751030()
{
    int h60;
    int l5c;
    int l58;
    int x54;
    int l50;
    char v4c[32];
    int b20;
    char v1c[8];
    int n10[4];

    if (m_number >= 0xa) {
        strcpy(v4c, "system\\bg\\bg");
    } else {
        strcpy(v4c, "system\\bg\\bg0");
    }
    _itoa(m_number, v1c, 0xa);
    strcat(v4c, (const char*)v1c);
    if (m_number >= 0xa) {
        strcat(v4c, "\\bg");
    } else {
        strcat(v4c, "\\bg0");
    }
    strcat(v4c, (const char*)v1c);
    strcat(v4c, ".pat");
    CFile l2c(v4c, 1);
    b20 = l2c.ReadInt();
    m_anims = new EffectAnim[b20];
    l58 = 0;
    for (; l58 < b20; l58++) {
        l50 = l2c.ReadInt();
        l2c.ReadInt();
        l2c.ReadInt();
        m_anims[l58].frameCount = l2c.ReadInt();
        x54 = m_anims[l58].frameCount;
        (&m_anims[l58])->Alloc(x54);
        l5c = 0;
        for (; l5c < x54; l5c++) {
            m_anims[l58].frames[l5c].duration = l2c.ReadInt();
            m_anims[l58].frames[l5c].surface = l2c.ReadInt();
            m_anims[l58].frames[l5c].width = l2c.ReadInt();
            m_anims[l58].frames[l5c].height = l2c.ReadInt();
            m_anims[l58].frames[l5c].x = l2c.ReadInt();
            m_anims[l58].frames[l5c].y = l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            l2c.ReadInt();
            h60 = 0;
            for (; h60 < 0xa; h60++) {
                l2c.Read((void*)n10, 0x10);
            }
        }
    }
}

CBg01::CBg01(CGraphics* p1)
    : CAnimBg()
{
    int xc;
    int v8;
    int v4;

    m_graphics = p1;
    m_number = 1;
    m_lastFrame = 0x39;
    v8 = (int)operator new(0xe8);
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
        m_objects[v4].layer = 0;
    }
}

CBg01::~CBg01()
{
    int v4;

    v4 = 0;
    for (; v4 < 0x3a; v4++) {
        if ((int)m_surfaces[v4] != 0) {
            m_surfaces[v4]->Release();
            m_surfaces[v4] = (IDirectDrawSurface*)0;
        }
    }
    delete (char*)m_surfaces;
    delete (char*)m_objects;
    delete m_anims;
}

void CBg01::Vf0()
{
    WORD xc;
    WORD v8;
    int v4;

    v4 = 0;
    for (; v4 < 2; v4++) {
        v8 = (short)m_anims[m_objects[v4].pattern].frames[m_objects[v4].frame].duration;
        xc = m_anims[m_objects[v4].pattern].frameCount;
        switch (m_objects[v4].pattern) {
        case 0:
        case 1:
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

void CBg01::Vf1(int p1, int p2, char p3)
{
    int v30;
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (p3 == 1) {
        return;
    }
    v30 = 0;
    for (; v30 < 2; v30++) {
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
