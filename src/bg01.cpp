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
        for (; v30 <= *(short*)((char*)this + 6); v30++) {
            if (*(short*)((char*)this + 4) >= 0xa) {
                strcpy(v2c, "system\\bg\\bg");
            } else {
                strcpy(v2c, "system\\bg\\bg0");
            }
            _itoa(*(short*)((char*)this + 4), vc, 0xa);
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
            ((CGraphics*)*(int*)((char*)this + 8))->LoadSurface((IDirectDrawSurface**)(*(int*)((char*)this + 0xc) + v30 * 4), (BYTE*)(h40 + *(BYTE*)h40 * 3 + 1), 0, 1);
            CloseHandle((HANDLE)v34);
            delete (char*)h40;
        }
    } else {
        f44 = 0;
        for (; f44 <= *(short*)((char*)this + 6); f44++) {
            if (*(short*)((char*)this + 4) >= 0xa) {
                strcpy(v2c, "system\\bg\\bg");
            } else {
                strcpy(v2c, "system\\bg\\bg0");
            }
            _itoa(*(short*)((char*)this + 4), vc, 0xa);
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
            ((CGraphics*)*(int*)((char*)this + 8))->LoadBmp((IDirectDrawSurface**)(*(int*)((char*)this + 0xc) + f44 * 4), (const char*)v2c, 1);
        }
    }
    *((char*)this + 0x18) = ((CGraphics*)*(int*)((char*)this + 8))->GetColorKey((IDirectDrawSurface*)*(int*)*(char**)((char*)this + 0xc));
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

    if (*(short*)((char*)this + 4) >= 0xa) {
        strcpy(v4c, "system\\bg\\bg");
    } else {
        strcpy(v4c, "system\\bg\\bg0");
    }
    _itoa(*(short*)((char*)this + 4), v1c, 0xa);
    strcat(v4c, (const char*)v1c);
    if (*(short*)((char*)this + 4) >= 0xa) {
        strcat(v4c, "\\bg");
    } else {
        strcat(v4c, "\\bg0");
    }
    strcat(v4c, (const char*)v1c);
    strcat(v4c, ".pat");
    CFile l2c(v4c, 1);
    b20 = l2c.ReadInt();
    *(int*)((char*)this + 0x14) = (int)(char*)new EffectAnim[b20];
    l58 = 0;
    for (; l58 < b20; l58++) {
        l50 = l2c.ReadInt();
        l2c.ReadInt();
        l2c.ReadInt();
        *(*(char**)((char*)this + 0x14) + l58 * 8) = l2c.ReadInt();
        x54 = *(BYTE*)(*(char**)((char*)this + 0x14) + l58 * 8);
        ((EffectAnim*)(*(int*)((char*)this + 0x14) + l58 * 8))->Alloc(x54);
        l5c = 0;
        for (; l5c < x54; l5c++) {
            *(short*)(*(char**)(*(char**)((char*)this + 0x14) + 4 + l58 * 8) + l5c * 0xc) = l2c.ReadInt();
            *(short*)(*(char**)(*(char**)((char*)this + 0x14) + 4 + l58 * 8) + l5c * 0xc + 2) = l2c.ReadInt();
            *(short*)(*(char**)(*(char**)((char*)this + 0x14) + 4 + l58 * 8) + l5c * 0xc + 8) = l2c.ReadInt();
            *(short*)(*(char**)(*(char**)((char*)this + 0x14) + 4 + l58 * 8) + l5c * 0xc + 0xa) = l2c.ReadInt();
            *(short*)(*(char**)(*(char**)((char*)this + 0x14) + 4 + l58 * 8) + l5c * 0xc + 4) = l2c.ReadInt();
            *(short*)(*(char**)(*(char**)((char*)this + 0x14) + 4 + l58 * 8) + l5c * 0xc + 6) = l2c.ReadInt();
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

CBg01::CBg01(int p1)
    : CAnimBg()
{
    int xc;
    int v8;
    int v4;

    *(int*)((char*)this + 8) = p1;
    *(short*)((char*)this + 4) = 1;
    *(short*)((char*)this + 6) = 0x39;
    v8 = (int)operator new(0xe8);
    *(int*)((char*)this + 0xc) = v8;
    xc = (int)operator new(0xe0);
    *(int*)((char*)this + 0x10) = xc;
    *(int*)((char*)this + 0x14) = (int)(char*)new EffectAnim[2];
    CAnimBg::Load();
    CAnimBg::Unk751030();
    v4 = 0;
    for (; v4 < 2; v4++) {
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70) = v4;
        *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) = 0.0;
        *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x20) = -450.0;
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) = 0;
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) = 0;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x48) = 1;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x50) = 2;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x51) = 0;
    }
}

CBg01::~CBg01()
{
    int v4;

    v4 = 0;
    for (; v4 < 0x3a; v4++) {
        if (*(int*)(*(char**)((char*)this + 0xc) + v4 * 4) != 0) {
            ((IUnknown*)*(int*)(*(char**)((char*)this + 0xc) + v4 * 4))->Release();
            *(int*)(*(char**)((char*)this + 0xc) + v4 * 4) = 0;
        }
    }
    delete (char*)*(int*)((char*)this + 0xc);
    delete (char*)*(int*)((char*)this + 0x10);
    delete (EffectAnim*)*(int*)((char*)this + 0x14);
}

void CBg01::Vf0()
{
    WORD xc;
    WORD v8;
    int v4;

    v4 = 0;
    for (; v4 < 2; v4++) {
        v8 = *(short*)(*(char**)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) * 0xc);
        xc = *(BYTE*)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70) * 8);
        switch (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70)) {
        case 0:
        case 1:
            (*(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4))++;
            if (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) >= v8) {
                *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) = 0;
                (*(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2))++;
                if (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) >= xc) {
                    *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) = 0;
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
        x1c = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v30 * 0x70) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 2) * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x48) == -1) {
            v10.left = (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x18) + p1 - (x1c.width - x1c.x);
            v10.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        } else {
            v10.left = (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x18) + p1 - x1c.x;
            v10.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        }
        if (*(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x50) > 0) {
            ((CGraphics*)*(int*)((char*)this + 8))->BlitEx(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + x1c.surface * 4), v2c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x48) == -1, *(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x50) - 1);
        } else {
            ((CGraphics*)*(int*)((char*)this + 8))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + x1c.surface * 4), v2c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x48) == -1);
        }
    }
}
