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
        for (; v30 <= unk6; v30++) {
            if (unk4 >= 0xa) {
                strcpy(v2c, "system\\bg\\bg");
            } else {
                strcpy(v2c, "system\\bg\\bg0");
            }
            _itoa(unk4, vc, 0xa);
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
            ((CGraphics*)unk8)->LoadSurface((IDirectDrawSurface**)((int)unkc + v30 * 4), (BYTE*)(h40 + *(BYTE*)h40 * 3 + 1), 0, 1);
            CloseHandle((HANDLE)v34);
            delete (char*)h40;
        }
    } else {
        f44 = 0;
        for (; f44 <= unk6; f44++) {
            if (unk4 >= 0xa) {
                strcpy(v2c, "system\\bg\\bg");
            } else {
                strcpy(v2c, "system\\bg\\bg0");
            }
            _itoa(unk4, vc, 0xa);
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
            ((CGraphics*)unk8)->LoadBmp((IDirectDrawSurface**)((int)unkc + f44 * 4), (const char*)v2c, 1);
        }
    }
    unk18 = ((CGraphics*)unk8)->GetColorKey((IDirectDrawSurface*)*(int*)unkc);
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

    if (unk4 >= 0xa) {
        strcpy(v4c, "system\\bg\\bg");
    } else {
        strcpy(v4c, "system\\bg\\bg0");
    }
    _itoa(unk4, v1c, 0xa);
    strcat(v4c, (const char*)v1c);
    if (unk4 >= 0xa) {
        strcat(v4c, "\\bg");
    } else {
        strcat(v4c, "\\bg0");
    }
    strcat(v4c, (const char*)v1c);
    strcat(v4c, ".pat");
    CFile l2c(v4c, 1);
    b20 = l2c.ReadInt();
    unk14 = (char*)new EffectAnim[b20];
    l58 = 0;
    for (; l58 < b20; l58++) {
        l50 = l2c.ReadInt();
        l2c.ReadInt();
        l2c.ReadInt();
        *(unk14 + l58 * 8) = l2c.ReadInt();
        x54 = *(BYTE*)(unk14 + l58 * 8);
        ((EffectAnim*)((int)unk14 + l58 * 8))->Alloc(x54);
        l5c = 0;
        for (; l5c < x54; l5c++) {
            *(short*)(*(char**)(unk14 + 4 + l58 * 8) + l5c * 0xc) = l2c.ReadInt();
            *(short*)(*(char**)(unk14 + 4 + l58 * 8) + l5c * 0xc + 2) = l2c.ReadInt();
            *(short*)(*(char**)(unk14 + 4 + l58 * 8) + l5c * 0xc + 8) = l2c.ReadInt();
            *(short*)(*(char**)(unk14 + 4 + l58 * 8) + l5c * 0xc + 0xa) = l2c.ReadInt();
            *(short*)(*(char**)(unk14 + 4 + l58 * 8) + l5c * 0xc + 4) = l2c.ReadInt();
            *(short*)(*(char**)(unk14 + 4 + l58 * 8) + l5c * 0xc + 6) = l2c.ReadInt();
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

    unk8 = p1;
    unk4 = 1;
    unk6 = 0x39;
    v8 = (int)operator new(0xe8);
    unkc = (char*)v8;
    xc = (int)operator new(0xe0);
    unk10 = (char*)xc;
    unk14 = (char*)new EffectAnim[2];
    CAnimBg::Load();
    CAnimBg::Unk751030();
    v4 = 0;
    for (; v4 < 2; v4++) {
        *(short*)(unk10 + v4 * 0x70) = v4;
        *(double*)(unk10 + v4 * 0x70 + 0x18) = 0.0;
        *(double*)(unk10 + v4 * 0x70 + 0x20) = -450.0;
        *(short*)(unk10 + v4 * 0x70 + 2) = 0;
        *(short*)(unk10 + v4 * 0x70 + 4) = 0;
        *(unk10 + v4 * 0x70 + 0x48) = 1;
        *(unk10 + v4 * 0x70 + 0x50) = 2;
        *(unk10 + v4 * 0x70 + 0x51) = 0;
    }
}

CBg01::~CBg01()
{
    int v4;

    v4 = 0;
    for (; v4 < 0x3a; v4++) {
        if (*(int*)(unkc + v4 * 4) != 0) {
            ((IUnknown*)*(int*)(unkc + v4 * 4))->Release();
            *(int*)(unkc + v4 * 4) = 0;
        }
    }
    delete unkc;
    delete unk10;
    delete (EffectAnim*)unk14;
}

void CBg01::Vf0()
{
    WORD xc;
    WORD v8;
    int v4;

    v4 = 0;
    for (; v4 < 2; v4++) {
        v8 = *(short*)(*(char**)(unk14 + *(WORD*)(unk10 + v4 * 0x70) * 8 + 4) + *(WORD*)(unk10 + v4 * 0x70 + 2) * 0xc);
        xc = *(BYTE*)(unk14 + *(WORD*)(unk10 + v4 * 0x70) * 8);
        switch (*(WORD*)(unk10 + v4 * 0x70)) {
        case 0:
        case 1:
            (*(short*)(unk10 + v4 * 0x70 + 4))++;
            if (*(WORD*)(unk10 + v4 * 0x70 + 4) >= v8) {
                *(short*)(unk10 + v4 * 0x70 + 4) = 0;
                (*(short*)(unk10 + v4 * 0x70 + 2))++;
                if (*(WORD*)(unk10 + v4 * 0x70 + 2) >= xc) {
                    *(short*)(unk10 + v4 * 0x70 + 2) = 0;
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
        x1c = *(EffectFrame*)(char*)(*(int*)(unk14 + *(WORD*)(unk10 + v30 * 0x70) * 8 + 4) + *(WORD*)(unk10 + v30 * 0x70 + 2) * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*(unk10 + v30 * 0x70 + 0x48) == -1) {
            v10.left = (int)*(double*)(unk10 + v30 * 0x70 + 0x18) + p1 - (x1c.width - x1c.x);
            v10.top = p2 + (int)*(double*)(unk10 + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        } else {
            v10.left = (int)*(double*)(unk10 + v30 * 0x70 + 0x18) + p1 - x1c.x;
            v10.top = p2 + (int)*(double*)(unk10 + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        }
        if (*(unk10 + v30 * 0x70 + 0x50) > 0) {
            ((CGraphics*)unk8)->BlitEx(v10, (IDirectDrawSurface*)*(int*)(unkc + x1c.surface * 4), v2c, unk18, *(unk10 + v30 * 0x70 + 0x48) == -1, *(unk10 + v30 * 0x70 + 0x50) - 1);
        } else {
            ((CGraphics*)unk8)->Blit(v10, (IDirectDrawSurface*)*(int*)(unkc + x1c.surface * 4), v2c, unk18, *(unk10 + v30 * 0x70 + 0x48) == -1);
        }
    }
}
