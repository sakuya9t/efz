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
    int buffer; // operator new's block, then data
    int bmpFrame; // the same for the .bmp files, in the branch if (1) never takes
    char* data;
    int bytesRead;
    int size;
    int file; // the .dat file's handle
    int frame; // the frame loaded: MMM in its file name, and its surface
    char path[32];
    char num[8];

    if (1) {
        frame = 0;
        for (; frame <= m_lastFrame; frame++) {
            if (m_number >= 10) {
                strcpy(path, "system\\bg\\bg");
            } else {
                strcpy(path, "system\\bg\\bg0");
            }
            _itoa(m_number, num, 10);
            strcat(path, (const char*)num);
            if (frame >= 100) {
                strcat(path, "\\");
            } else if (frame >= 10) {
                strcat(path, "\\0");
            } else {
                strcat(path, "\\00");
            }
            _itoa(frame, num, 10);
            strcat(path, (const char*)num);
            strcat(path, ".dat");
            file = (int)CreateFileA((LPCSTR)path, 0x80000000, 0, 0, 3, 128, 0);
            size = GetFileSize((HANDLE)file, 0);
            buffer = TOINT(int, operator new(size));
            data = TOPTR(char*, buffer);
            ReadFile((HANDLE)file, (LPVOID)data, size, (LPDWORD)&bytesRead, 0);
            m_graphics->LoadSurface(&m_surfaces[frame], (BYTE*)(data + *(BYTE*)data * 3 + 1), 0, 1);
            CloseHandle((HANDLE)file);
            delete (char*)data;
        }
    } else {
        bmpFrame = 0;
        for (; bmpFrame <= m_lastFrame; bmpFrame++) {
            if (m_number >= 10) {
                strcpy(path, "system\\bg\\bg");
            } else {
                strcpy(path, "system\\bg\\bg0");
            }
            _itoa(m_number, num, 10);
            strcat(path, (const char*)num);
            if (bmpFrame >= 100) {
                strcat(path, "\\");
            } else if (bmpFrame >= 10) {
                strcat(path, "\\0");
            } else {
                strcat(path, "\\00");
            }
            _itoa(bmpFrame, num, 10);
            strcat(path, (const char*)num);
            strcat(path, ".bmp");
            m_graphics->LoadBmp(&m_surfaces[bmpFrame], (const char*)path, 1);
        }
    }
    m_colorKey = m_graphics->GetColorKey(*m_surfaces);
}

void CAnimBg::LoadAnims()
{
    int box; // the frame's ten 16-byte boxes, skipped
    int j; // the frame read
    int i; // the animation read
    int frameCount; // frames in the animation
    int animNumber; // the record's first int, unused; a character .pat has the pattern number there
    char path[32];
    int animCount;
    char num[8];
    int skip[4]; // where each box is read and thrown away

    if (m_number >= 10) {
        strcpy(path, "system\\bg\\bg");
    } else {
        strcpy(path, "system\\bg\\bg0");
    }
    _itoa(m_number, num, 10);
    strcat(path, (const char*)num);
    if (m_number >= 10) {
        strcat(path, "\\bg");
    } else {
        strcat(path, "\\bg0");
    }
    strcat(path, (const char*)num);
    strcat(path, ".pat");
    CFile file(path, 1);
    animCount = file.ReadInt();
    m_anims = new EffectAnim[animCount];
    i = 0;
    for (; i < animCount; i++) {
        animNumber = file.ReadInt();
        file.ReadInt();
        file.ReadInt();
        m_anims[i].frameCount = file.ReadInt();
        frameCount = m_anims[i].frameCount;
        (&m_anims[i])->Alloc(frameCount);
        j = 0;
        for (; j < frameCount; j++) {
            m_anims[i].frames[j].duration = file.ReadInt();
            m_anims[i].frames[j].surface = file.ReadInt();
            m_anims[i].frames[j].width = file.ReadInt();
            m_anims[i].frames[j].height = file.ReadInt();
            m_anims[i].frames[j].x = file.ReadInt();
            m_anims[i].frames[j].y = file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            file.ReadInt();
            box = 0;
            for (; box < 10; box++) {
                file.Read((void*)skip, 16);
            }
        }
    }
}

CBg01::CBg01(CGraphics* graphics)
    : CAnimBg()
{
    int objects; // the block for m_objects
    int surfaces; // the block for m_surfaces, a pointer per frame
    int i;

    m_graphics = graphics;
    m_number = 1;
    m_lastFrame = 57;
    surfaces = TOINT(int, operator new(0xe8));
    m_surfaces = TOPTR(PTR32(IDirectDrawSurface)*, surfaces);
    objects = TOINT(int, operator new(0xe0));
    m_objects = TOPTR(BgObject*, objects);
    m_anims = new EffectAnim[2];
    CAnimBg::Load();
    CAnimBg::LoadAnims();
    i = 0;
    for (; i < 2; i++) {
        m_objects[i].pattern = i;
        m_objects[i].x = 0.0;
        m_objects[i].y = -450.0;
        m_objects[i].frame = 0;
        m_objects[i].timer = 0;
        m_objects[i].facing = 1;
        m_objects[i].scale = 2;
        m_objects[i].layer = 0;
    }
}

CBg01::~CBg01()
{
    int i;

    i = 0;
    for (; i < 58; i++) {
        if ((int)m_surfaces[i] != 0) {
            m_surfaces[i]->Release();
            m_surfaces[i] = (IDirectDrawSurface*)0;
        }
    }
    delete (char*)m_surfaces;
    delete (char*)m_objects;
    delete m_anims;
}

void CBg01::Update()
{
    WORD frameCount; // frames in the object's animation
    WORD duration; // ticks the object's current frame lasts
    int i;

    i = 0;
    for (; i < 2; i++) {
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

void CBg01::Draw(int x, int y, char layer)
{
    int i;
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (layer == 1) {
        return;
    }
    i = 0;
    for (; i < 2; i++) {
        sprite = m_anims[m_objects[i].pattern].frames[m_objects[i].frame];
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_objects[i].facing == -1) {
            dst.left = (int)m_objects[i].x + x - (sprite.width - sprite.x);
            dst.top = y + (int)m_objects[i].y + 210 - sprite.y;
            dst.right = sprite.width + dst.left;
            dst.bottom = sprite.height + dst.top;
        } else {
            dst.left = (int)m_objects[i].x + x - sprite.x;
            dst.top = y + (int)m_objects[i].y + 210 - sprite.y;
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
