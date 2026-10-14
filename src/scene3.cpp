// CScene3 (0x7633a0-0x76c6ef), scene 3: the fight itself. Each frame it runs both
// players and their objects, checks every pair of boxes (CollisionInfo snapshots of
// the current frame, position and facing), pushes the players apart, scrolls the
// camera and draws the gauges, timer and background (with the helpers in
// scene3_draw.cpp). A replay's inputs are written here, or read back when one is
// playing.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

// GLOBAL: 0x7b1290
// Set while one of F5-F8 is held, so that each press acts once (Vf2).
int g_fkeyHeld = 0;

CScene3::CScene3(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    *(int*)((char*)this + 0x440) = 0;
    *(int*)((char*)this + 0x444) = -0x32;
    *(int*)((char*)this + 0x448) = *(int*)((char*)this + 0x440);
    *(int*)((char*)this + 0x44c) = *(int*)((char*)this + 0x444);
    *(int*)((char*)this + 0x450) = 5;
    *(int*)((char*)this + 0x454) = -0xa0;
    *(int*)((char*)this + 0x458) = 0;
    *((char*)this + 0x2c) = 1;
    *((char*)this + 0x2d) = 0;
    *(short*)((char*)this + 0x574) = 0;
    *(short*)((char*)this + 0x576) = 0x270f;
    *((char*)this + 0x578) = 3;
    *(int*)((char*)this + 0x588) = 0;
    *(double*)((char*)this + 0x580) = 0.0;
    *(int*)((char*)this + 0x58c) = 0;
    *(int*)((char*)this + 0x590) = 0;
    *(int*)((char*)this + 0x434) = 0;
    *(int*)((char*)this + 0x438) = 0;
    *(int*)((char*)this + 0x43c) = 0;
    *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 0;
    *(*(char**)((char*)this + 0x1c) + 0x1350) = 1;
    *(RECT*)((char*)this + 0x464) = MakeRect(0, 0xea, 8, 0xa);
    *(RECT*)((char*)this + 0x474) = MakeRect(0, 0xd2, 0x10, 0xf);
    *(RECT*)((char*)this + 0x484) = MakeRect(0, 0xe1, 7, 9);
    *(RECT*)((char*)this + 0x494) = MakeRect(0, 0x11a, 0xe, 0x16);
    *(RECT*)((char*)this + 0x4a4) = MakeRect(0, 0x160, 8, 0xc);
    *(RECT*)((char*)this + 0x4b4) = MakeRect(0, 0x154, 8, 0xc);
    *(RECT*)((char*)this + 0x4c4) = MakeRect(0, 0x148, 8, 0xc);
    *(RECT*)((char*)this + 0x4d4) = MakeRect(0, 0x13c, 8, 0xc);
    *(RECT*)((char*)this + 0x4e4) = MakeRect(0, 0x130, 8, 0xc);
    *(RECT*)((char*)this + 0x4f4) = MakeRect(0, 0x16c, 7, 0xa);
    *(RECT*)((char*)this + 0x504) = MakeRect(0, 0x176, 7, 0xa);
    *(RECT*)((char*)this + 0x514) = MakeRect(0, 0x180, 7, 0xa);
    *(RECT*)((char*)this + 0x524) = MakeRect(0, 0x18a, 7, 0xa);
    *(RECT*)((char*)this + 0x534) = MakeRect(0, 0x194, 7, 0xa);
    *(RECT*)((char*)this + 0x544) = MakeRect(0, 0x19e, 7, 0xa);
    *(RECT*)((char*)this + 0x554) = MakeRect(0, 0x1a8, 7, 0xa);
    *(RECT*)((char*)this + 0x564) = MakeRect(0, 0x1b2, 7, 0xa);
}

CScene3::~CScene3()
{
}

BYTE CScene3::Update()
{
    int v4;

    if ((DWORD)(timeGetTime() - *(int*)((char*)this + 0x438)) >= 0x3e8) {
        *(int*)((char*)this + 0x438) = timeGetTime();
        *(int*)((char*)this + 0x43c) = *(int*)((char*)this + 0x434);
        *(int*)((char*)this + 0x434) = 0;
    }
    (*(int*)((char*)this + 0x434))++;
    if (*((char*)this + 0x2c) == 1) {
        *(*(char**)((char*)this + 0x1c) + 0x1350) = 1;
        *(int*)((char*)this + 0xc) = *(int*)*(char**)((char*)this + 0x14);
        *(int*)((char*)this + 0x10) = *(int*)*(char**)((char*)this + 0x18);
        *(int*)((char*)this + 0x440) = 0;
        *(int*)((char*)this + 0x444) = -0x32;
        *(int*)((char*)this + 0x448) = *(int*)((char*)this + 0x440);
        *(int*)((char*)this + 0x44c) = *(int*)((char*)this + 0x444);
        *(int*)((char*)this + 0x450) = 5;
        *(int*)((char*)this + 0x454) = -0xa0;
        *(int*)((char*)this + 0x458) = 0;
        *((char*)this + 0x578) = 3;
        *(short*)((char*)this + 0x574) = 0;
        *(short*)((char*)this + 0x576) = 0x270f;
        Unk7647b0();
        Draw();
        CScene::Unk759e20((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), 0);
        *((char*)this + 0x2c) = 0;
    } else if (*((char*)this + 0x2d) == 1) {
        CScene::Unk759c90((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), 1, 0, 0x64);
        delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
        *(int*)*(char**)((char*)this + 0x14) = 0;
        delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
        *(int*)*(char**)((char*)this + 0x18) = 0;
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0x137c) != 0) {
            delete (char*)*(int*)(*(char**)((char*)this + 0x1c) + 0x137c);
            *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = 0;
        }
        *((char*)this + 0x2d) = 0;
        *((char*)this + 0x2c) = 1;
        if (*(*(char**)((char*)this + 0x1c) + 0x14283) > 0) {
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Close();
            *(*(char**)((char*)this + 0x1c) + 0x14283) = 0;
            ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
            return 8;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 6) {
            return 0;
        }
        return 1;
    }
    Vf2();
    if (*(int*)((char*)this + 0x588) != 0) {
        return 3;
    }
    if (*((char*)this + 0x2d) == 2) {
        *((char*)this + 0x578) = 1;
        if (Unk765fa0() != 0) {
            *((char*)this + 0x2d) = 0;
            *((char*)this + 0x2c) = 1;
            if (*(*(char**)((char*)this + 0x1c) + 0x14283) > 0) {
                ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Close();
                *(*(char**)((char*)this + 0x1c) + 0x14283) = 0;
                ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
                delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
                *(int*)*(char**)((char*)this + 0x14) = 0;
                delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
                *(int*)*(char**)((char*)this + 0x18) = 0;
                if (*(int*)(*(char**)((char*)this + 0x1c) + 0x137c) != 0) {
                    delete (char*)*(int*)(*(char**)((char*)this + 0x1c) + 0x137c);
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = 0;
                }
                return 8;
            }
            return 5;
        }
    } else if (*(int*)(*(char**)((char*)this + 0x1c) + 0x1427c) != 0) {
        *((char*)this + 0x578) = *(*(char**)((char*)this + 0x1c) + 0x14280);
        *(int*)(*(char**)((char*)this + 0x1c) + 0x1427c) = 0;
    }
    v4 = 0;
    for (; v4 < *(BYTE*)((char*)this + 0x578); v4++) {
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk411be0();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk411be0();
        Unk766070();
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f230();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f230();
        ((CPlayer*)*(int*)((char*)this + 0xc))->Vf8();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Vf8();
        ((CPlayer*)*(int*)((char*)this + 0xc))->Vf6();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Vf6();
        ((CPlayer*)*(int*)((char*)this + 0xc))->Vf7();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Vf7();
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0x1354) == 0 && *(*(char**)((char*)this + 0x1c) + 0x1350) == 0) {
            Unk766480();
        }
        Unk766b50();
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f580();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f580();
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14c) > 0) {
            (*(short*)(*(char**)((char*)this + 0xc) + 0x14c))--;
        } else {
            *(short*)(*(char**)((char*)this + 0xc) + 0x14c) = 0;
        }
        if (*(short*)(*(char**)((char*)this + 0x10) + 0x14c) > 0) {
            (*(short*)(*(char**)((char*)this + 0x10) + 0x14c))--;
        } else {
            *(short*)(*(char**)((char*)this + 0x10) + 0x14c) = 0;
        }
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f980();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f980();
        Unk764db0();
        Unk764f10();
        Unk765040();
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateFade();
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateTimers();
    Unk7647b0();
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x136c) != 0 || *(int*)(*(char**)((char*)this + 0x1c) + 0x136c) == 0 && *(int*)(*(char**)((char*)this + 0x1c) + 0x1368) != 0) {
        Draw();
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateEffects();
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x137c) != 0) {
        ((CAnimBg*)*(int*)(*(char**)((char*)this + 0x1c) + 0x137c))->Vf0();
    }
    return 3;
}

void CScene3::Draw()
{
    ((CPlayer*)*(int*)((char*)this + 0xc))->Unk410940();
    ((CPlayer*)*(int*)((char*)this + 0x10))->Unk410940();
    Unk75dd50();
    Unk75e240();
    Unk762c50();
    ((CGame*)*(int*)((char*)this + 0x1c))->DrawEffects(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 0);
    ((CPlayer*)*(int*)((char*)this + 0xc))->Unk413100(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 0);
    ((CPlayer*)*(int*)((char*)this + 0x10))->Unk413100(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 0);
    if (*(WORD*)(*(char**)((char*)this + 0x10) + 8) >= 0xc8) {
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk4121a0(*(int*)((char*)this + 0x45c) + ((CPlayer*)*(int*)((char*)this + 0xc))->Unk4103a0() * (*(short*)(*(char**)((char*)this + 0xc) + 0x14a) % 2) * 2, *(int*)((char*)this + 0x460));
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk4121a0(*(int*)((char*)this + 0x45c) + ((CPlayer*)*(int*)((char*)this + 0x10))->Unk4103a0() * (*(short*)(*(char**)((char*)this + 0x10) + 0x14a) % 2) * 2, *(int*)((char*)this + 0x460));
    } else {
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk4121a0(*(int*)((char*)this + 0x45c) + ((CPlayer*)*(int*)((char*)this + 0x10))->Unk4103a0() * (*(short*)(*(char**)((char*)this + 0x10) + 0x14a) % 2) * 2, *(int*)((char*)this + 0x460));
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk4121a0(*(int*)((char*)this + 0x45c) + ((CPlayer*)*(int*)((char*)this + 0xc))->Unk4103a0() * (*(short*)(*(char**)((char*)this + 0xc) + 0x14a) % 2) * 2, *(int*)((char*)this + 0x460));
    }
    ((CPlayer*)*(int*)((char*)this + 0xc))->Unk413100(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 1);
    ((CPlayer*)*(int*)((char*)this + 0x10))->Unk413100(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 1);
    ((CGame*)*(int*)((char*)this + 0x1c))->DrawEffects(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 1);
    ((CGame*)*(int*)((char*)this + 0x1c))->DrawEffects(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 2);
    ((CGame*)*(int*)((char*)this + 0x1c))->DrawEffects(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 3);
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x137c) != 0 && *(int*)(*(char**)((char*)this + 0xc) + 0x30c4) == 0 && *(int*)(*(char**)((char*)this + 0x10) + 0x30c4) == 0 && *(int*)(*(char**)((char*)this + 0x1c) + 0x14278) == 0) {
        ((CAnimBg*)*(int*)(*(char**)((char*)this + 0x1c) + 0x137c))->Vf1(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 1);
    }
    if (*(short*)(*(char**)((char*)this + 0x1c) + 0x1420c) == 0) {
        ((CPlayer*)*(int*)((char*)this + 0xc))->Vf1();
        ((CPlayer*)*(int*)((char*)this + 0x10))->Vf1();
    }
    Unk760060();
    if (*(short*)(*(char**)((char*)this + 0xc) + 0xf4) > 1 && *(short*)(*(char**)((char*)this + 0xc) + 0x104) > 0) {
        Unk7623b0(*(int*)((char*)this + 0xc));
    }
    if (*(short*)(*(char**)((char*)this + 0x10) + 0xf4) > 1 && *(short*)(*(char**)((char*)this + 0x10) + 0x104) > 0) {
        Unk7623b0(*(int*)((char*)this + 0x10));
    }
    if (*(int*)((char*)this + 0x58c) != 0) {
        if (*(int*)((char*)this + 0x590) % 2 == 0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Screenshot(*(int*)((char*)this + 0x590) / 2, (PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35));
        }
        (*(int*)((char*)this + 0x590))++;
    }
    if (0) {
        Unk75db70(0x50, 0x64, *(int*)(*(char**)((char*)this + 0xc) + 0x108), 2, 0, 0);
        Unk75db70(0x50, 0x6e, *(WORD*)(*(char**)((char*)this + 0xc) + 8), 2, 0, 0);
        Unk75db70(0x50, 0x78, *(WORD*)(*(char**)((char*)this + 0xc) + 0xa), 2, 0, 0);
        Unk75db70(0x50, 0x82, *(WORD*)(*(char**)((char*)this + 0xc) + 0xc), 2, 0, 0);
        Unk75db70(0x118, 0x64, *(int*)(*(char**)((char*)this + 0x10) + 0x108), 2, 0, 0);
        Unk75db70(0x118, 0x6e, *(WORD*)(*(char**)((char*)this + 0x10) + 8), 2, 0, 0);
        Unk75db70(0x118, 0x78, *(WORD*)(*(char**)((char*)this + 0x10) + 0xa), 2, 0, 0);
        Unk75db70(0x118, 0x82, *(WORD*)(*(char**)((char*)this + 0x10) + 0xc), 2, 0, 0);
    }
    Unk7631f0();
}

void CScene3::Unk7647b0()
{
    int v8;
    int v4;

    *(int*)((char*)this + 0x448) = *(int*)((char*)this + 0x440);
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x14240) > 0) {
        *(int*)((char*)this + 0x448) = *(int*)(*(char**)((char*)this + 0x1c) + 0x14238);
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14a) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14a) == 0 && *(short*)(*(char**)((char*)this + 0xc) + 0x14c) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14c) == 0) {
            (*(int*)(*(char**)((char*)this + 0x1c) + 0x14240))--;
        }
    }
    v4 = 0xa0 - (int)((*(double*)(*(char**)((char*)this + 0xc) + 0x20) * (*(int*)((char*)this + 0x448) + 0x32) + *(double*)(*(char**)((char*)this + 0x10) + 0x20) * (0x32 - *(int*)((char*)this + 0x448))) / 100.0);
    if (v4 < -0x13f) {
        v4 = -0x13f;
    } else if (v4 > 0) {
        v4 = 0;
    }
    if (*(int*)((char*)this + 0x454) < v4) {
        *(int*)((char*)this + 0x454) -= (*(int*)((char*)this + 0x454) - v4) / 0xf - 1;
        if (*(int*)((char*)this + 0x454) > v4) {
            *(int*)((char*)this + 0x454) = v4;
        }
    } else {
        *(int*)((char*)this + 0x454) -= (*(int*)((char*)this + 0x454) - v4) / 0xf + 1;
        if (*(int*)((char*)this + 0x454) < v4) {
            *(int*)((char*)this + 0x454) = v4;
        }
    }
    if (*(int*)((char*)this + 0x44c) < *(int*)((char*)this + 0x444)) {
        *(int*)((char*)this + 0x44c) += *(int*)((char*)this + 0x450);
        if (*(int*)((char*)this + 0x44c) > *(int*)((char*)this + 0x444)) {
            *(int*)((char*)this + 0x44c) = *(int*)((char*)this + 0x444);
        }
    } else {
        *(int*)((char*)this + 0x44c) += *(int*)((char*)this + 0x450);
        if (*(int*)((char*)this + 0x44c) > *(int*)((char*)this + 0x444)) {
            *(int*)((char*)this + 0x44c) = *(int*)((char*)this + 0x444);
        }
    }
    if (*(double*)(*(char**)((char*)this + 0xc) + 0x28) < -240.0 || *(double*)(*(char**)((char*)this + 0x10) + 0x28) < -240.0) {
        *(int*)((char*)this + 0x44c) = *(int*)((char*)this + 0x444);
    } else {
        *(int*)((char*)this + 0x44c) = 0x14;
    }
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x14244) > 0) {
        *(int*)((char*)this + 0x44c) = *(int*)(*(char**)((char*)this + 0x1c) + 0x1423c) * (1 - ((*(double*)(*(char**)((char*)this + 0xc) + 0x28) < *(double*)(*(char**)((char*)this + 0x10) + 0x28)) << 1));
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14a) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14a) == 0 && *(short*)(*(char**)((char*)this + 0xc) + 0x14c) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14c) == 0) {
            (*(int*)(*(char**)((char*)this + 0x1c) + 0x14244))--;
        }
    }
    if ((v8 = -(((int)*(double*)(*(char**)((char*)this + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + 0xc) + 0x28) < 0.0) + (int)*(double*)(*(char**)((char*)this + 0x10) + 0x28) - (*(double*)(*(char**)((char*)this + 0x10) + 0x28) < 0.0)) / 2) + ((int)*(double*)(*(char**)((char*)this + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + 0xc) + 0x28) < 0.0) - (int)*(double*)(*(char**)((char*)this + 0x10) + 0x28) + (*(double*)(*(char**)((char*)this + 0x10) + 0x28) < 0.0)) * *(int*)((char*)this + 0x44c) / 0x64 * ((*(double*)(*(char**)((char*)this + 0xc) + 0x28) - *(double*)(*(char**)((char*)this + 0x10) + 0x28) < 0.0) * 2 + -1)) < 0) {
        v8 = 0;
    } else if (v8 > 0xf0) {
        v8 = 0xf0;
    }
    if (*(int*)((char*)this + 0x458) < v8) {
        *(int*)((char*)this + 0x458) -= (*(int*)((char*)this + 0x458) - v8) / 0xa - 1;
        if (*(int*)((char*)this + 0x458) > v8) {
            *(int*)((char*)this + 0x458) = v8;
        }
    } else {
        *(int*)((char*)this + 0x458) -= (*(int*)((char*)this + 0x458) - v8) / 0xa + 1;
        if (*(int*)((char*)this + 0x458) < v8) {
            *(int*)((char*)this + 0x458) = v8;
        }
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateShake();
    *(RECT*)(char*)(*(int*)((char*)this + 0x1c) + 0x14248) = MakeRect(-*(int*)((char*)this + 0x454), -*(int*)((char*)this + 0x458) - 0xd2, 0x140, 0xf0);
    *(int*)((char*)this + 0x45c) = *(int*)((char*)this + 0x454) + *(int*)(*(char**)((char*)this + 0x1c) + 0x1421c);
    *(int*)((char*)this + 0x460) = *(int*)((char*)this + 0x458) + *(int*)(*(char**)((char*)this + 0x1c) + 0x14220);
}

void CScene3::Unk764db0()
{
    int v8;
    int v4;

    if (*((char*)this + 0x2d) == 2) {
        v4 = 0;
        for (; v4 < 2; v4++) {
            *(*(char**)((char*)this + v4 * 4 + 0xc) + 0x2c9) = -1;
            *(*(char**)((char*)this + v4 * 4 + 0xc) + 0x2c8) = -1;
        }
        return;
    }
    v8 = 0;
    for (; v8 < 2; v8++) {
        if (*(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c9) >= 0 && *(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c9) < 0x41) {
            ((CSound*)*(int*)((char*)this + 0x28))->Play(*(short*)(*(char**)((char*)this + 0x1c) + 0xea4 + *(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c9) * 2), 0);
            *(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c9) = -1;
        }
        if (*(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c8) >= 0 && *(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c8) < 0x32) {
            ((CSound*)*(int*)((char*)this + 0x28))->Play(*(short*)(*(char**)((char*)this + v8 * 4 + 0xc) + 0x264 + *(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c8) * 2), 0);
            *(*(char**)((char*)this + v8 * 4 + 0xc) + 0x2c8) = -1;
        }
    }
}

void CScene3::Unk764f10()
{
    int v8;
    int v4;

    if (*((char*)this + 0x2d) == 2) {
        v8 = *(short*)(*(char**)((char*)this + 0x1c) + 0x1382);
        while (v8 != *(short*)(*(char**)((char*)this + 0x1c) + 0x1380)) {
            *(*(char**)((char*)this + 0x1c) + 0x2a74 + v8 * 0x70) = -1;
            v8++;
            if (v8 >= 0x280) {
                v8 = 0;
            }
        }
        return;
    }
    v4 = *(short*)(*(char**)((char*)this + 0x1c) + 0x1382);
    while (v4 != *(short*)(*(char**)((char*)this + 0x1c) + 0x1380)) {
        if (*(*(char**)((char*)this + 0x1c) + 0x2a74 + v4 * 0x70) >= 0 && *(*(char**)((char*)this + 0x1c) + 0x2a74 + v4 * 0x70) < 0x41) {
            ((CSound*)*(int*)((char*)this + 0x28))->Play(*(short*)(*(char**)((char*)this + 0x1c) + 0xea4 + *(*(char**)((char*)this + 0x1c) + 0x2a74 + v4 * 0x70) * 2), 0);
            *(*(char**)((char*)this + 0x1c) + 0x2a74 + v4 * 0x70) = -1;
        }
        v4++;
        if (v4 >= 0x280) {
            v4 = 0;
        }
    }
}

void CScene3::Unk765040()
{
    if (*(short*)((char*)this + 0x574) != 0) {
        return;
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 1) {
        return;
    }
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x1354) != 0) {
        *(*(char**)((char*)this + 0xc) + 0x18a) = 0;
        *(*(char**)((char*)this + 0xc) + 0x18b) = 0;
        *(*(char**)((char*)this + 0xc) + 0x18c) = 0;
        *(*(char**)((char*)this + 0xc) + 0x18d) = 0;
        *(*(char**)((char*)this + 0x10) + 0x18a) = 0;
        *(*(char**)((char*)this + 0x10) + 0x18b) = 0;
        *(*(char**)((char*)this + 0x10) + 0x18c) = 0;
        *(*(char**)((char*)this + 0x10) + 0x18d) = 0;
        if (*(WORD*)(*(char**)((char*)this + 0xc) + 8) >= 0x32 && ((CPlayer*)*(int*)((char*)this + 0xc))->Unk410420() == 0 || *(WORD*)(*(char**)((char*)this + 0x10) + 8) >= 0x32 && ((CPlayer*)*(int*)((char*)this + 0x10))->Unk410420() == 0 || *((char*)this + 0x2d) == 2) {
            return;
        }
        *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 0;
        *(int*)(*(char**)((char*)this + 0xc) + 0x108) = 0x270f;
        *(int*)(*(char**)((char*)this + 0x10) + 0x108) = 0x270f;
        *(*(char**)((char*)this + 0x1c) + 0x1350) = 2;
        return;
    }
    EffectDesc v48;
    if (*(int*)(*(char**)((char*)this + 0xc) + 0x108) <= 0 && *(int*)(*(char**)((char*)this + 0x10) + 0x108) <= 0) {
        (*(*(char**)((char*)this + 0xc) + 0xac))++;
        (*(*(char**)((char*)this + 0x10) + 0xac))++;
        if (*(*(char**)((char*)this + 0xc) + 0xac) >= *(*(char**)((char*)this + 0x1c) + 0x134e)) {
            (*(*(char**)((char*)this + 0xc) + 0xac))--;
        }
        if (*(*(char**)((char*)this + 0x10) + 0xac) >= *(*(char**)((char*)this + 0x1c) + 0x134e)) {
            (*(*(char**)((char*)this + 0x10) + 0xac))--;
        }
        *(short*)(*(char**)((char*)this + 0xc) + 8) = 0x3b;
        ((CPlayer*)*(int*)((char*)this + 0xc))->Vf0();
        *(short*)(*(char**)((char*)this + 0x10) + 8) = 0x3b;
        ((CPlayer*)*(int*)((char*)this + 0x10))->Vf0();
        *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 1;
        if (*(*(char**)((char*)this + 0x1c) + 0x134d) < 9) {
            (*(*(char**)((char*)this + 0x1c) + 0x134d))++;
        }
        return;
    }
    if (*(int*)(*(char**)((char*)this + 0xc) + 0x108) <= 0 && *(short*)(*(char**)((char*)this + 0xc) + 0x140) == 0) {
        *(int*)(*(char**)((char*)this + 0x10) + 0x30dc) += *(int*)(*(char**)((char*)this + 0x10) + 0x108);
        if (*(*(char**)((char*)this + 0x10) + 0xac) < *(*(char**)((char*)this + 0x1c) + 0x134e) - 1) {
            (*(*(char**)((char*)this + 0x10) + 0xac))++;
            *(short*)(*(char**)((char*)this + 0xc) + 0x14c) = *(short*)(*(char**)((char*)this + 0xc) + 0x14c) + 0xb4;
            *(short*)(*(char**)((char*)this + 0x10) + 0x14c) = *(short*)(*(char**)((char*)this + 0x10) + 0x14c) + 0xb4;
            ((CPlayer*)*(int*)((char*)this + 0xc))->Vf0();
            v48.unk0 = 0;
            v48.x = 80.0;
            v48.y = 100.0;
            v48.side = 0;
            v48.unk20 = 0;
            v48.unk21 = 2;
            v48.unk24 = 1;
            v48.type = 0x13;
            v48.unk2c = 0x1d;
            ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&v48);
            *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 1;
            if (*(*(char**)((char*)this + 0x1c) + 0x134d) < 9) {
                (*(*(char**)((char*)this + 0x1c) + 0x134d))++;
            }
        } else {
            (*(*(char**)((char*)this + 0x10) + 0xac))++;
            ((CPlayer*)*(int*)((char*)this + 0xc))->Vf0();
            *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 1;
            *((char*)this + 0x2d) = 2;
            *(double*)((char*)this + 0x580) = 0.0;
            *(*(char**)((char*)this + 0x1c) + 0x134c) = 1;
        }
        return;
    }
    if (*(int*)(*(char**)((char*)this + 0x10) + 0x108) <= 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x140) == 0) {
        *(int*)(*(char**)((char*)this + 0xc) + 0x30dc) += *(int*)(*(char**)((char*)this + 0xc) + 0x108);
        if (*(*(char**)((char*)this + 0xc) + 0xac) < *(*(char**)((char*)this + 0x1c) + 0x134e) - 1) {
            (*(*(char**)((char*)this + 0xc) + 0xac))++;
            *(short*)(*(char**)((char*)this + 0xc) + 0x14c) = *(short*)(*(char**)((char*)this + 0xc) + 0x14c) + 0xb4;
            *(short*)(*(char**)((char*)this + 0x10) + 0x14c) = *(short*)(*(char**)((char*)this + 0x10) + 0x14c) + 0xb4;
            v48.unk0 = 0;
            v48.x = 240.0;
            v48.y = 100.0;
            v48.side = 0;
            v48.unk20 = 0;
            v48.unk21 = 2;
            v48.unk24 = 1;
            v48.type = 0x13;
            v48.unk2c = 0x1d;
            ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&v48);
            ((CPlayer*)*(int*)((char*)this + 0x10))->Vf0();
            *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 1;
            if (*(*(char**)((char*)this + 0x1c) + 0x134d) < 9) {
                (*(*(char**)((char*)this + 0x1c) + 0x134d))++;
            }
            return;
        }
        (*(*(char**)((char*)this + 0xc) + 0xac))++;
        ((CPlayer*)*(int*)((char*)this + 0x10))->Vf0();
        *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) = 1;
        *((char*)this + 0x2d) = 2;
        *(double*)((char*)this + 0x580) = 0.0;
        *(*(char**)((char*)this + 0x1c) + 0x134c) = 0;
    }
}

void CScene3::Vf2()
{
    int l10c;
    char v108[256];

    l10c = ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->Acquire();
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x14283) == 1 && *(int*)(*(char**)((char*)this + 0x1c) + 0x14284) != 0) {
        *(int*)(*(char**)((char*)this + 0x1c) + 0x14284) = 0;
        *((char*)this + 0x2d) = 1;
    }
    if (*((char*)this + 0x2d) == 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) == 6) {
        ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
        if (*(*(char**)((char*)this + 0x1c) + 0x10) != 0 || *(*(char**)((char*)this + 0x1c) + 0x11) != 0 || *(*(char**)((char*)this + 0x1c) + 0x12) != 0 || *(*(char**)((char*)this + 0x1c) + 0x13) != 0 || (v108[1] & 0x80) != 0) {
            *((char*)this + 0x2d) = 1;
            ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
            *(int*)((char*)this + 0x588) = 0;
        }
    }
    if (*((char*)this + 0x2d) == 0 && (v108[1] & 0x80) != 0) {
        *((char*)this + 0x2d) = 1;
        *(int*)((char*)this + 0x588) = 0;
    }
    if ((v108[62] & 0x80) != 0 && *(*(char**)((char*)this + 0x1c) + 0x1350) == 0 && *(int*)(*(char**)((char*)this + 0x1c) + 0x1354) == 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 2 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 6) {
        *(short*)((char*)this + 0x574) = *(short*)((char*)this + 0x574) + 5;
        if (*(short*)((char*)this + 0x574) > 0x7d0) {
            *(short*)((char*)this + 0x574) = 0;
        }
        *(short*)((char*)this + 0x576) = 0x270f;
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ee) = *(short*)((char*)this + 0x576);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ee) = *(short*)((char*)this + 0x576);
    } else if ((v108[63] & 0x80) != 0 && g_fkeyHeld == 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 2 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 6) {
        if (*(short*)((char*)this + 0x574) == 0x3e8) {
            if (*(short*)((char*)this + 0x576) == 0xd04) {
                *(short*)((char*)this + 0x574) = 0x7d0;
            } else {
                *(short*)((char*)this + 0x576) = 0xd04;
            }
        } else {
            *(short*)((char*)this + 0x574) = 0x3e8;
        }
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ee) = *(short*)((char*)this + 0x576);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ee) = *(short*)((char*)this + 0x576);
        g_fkeyHeld = 1;
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 1) {
        if ((v108[64] & 0x80) != 0 && g_fkeyHeld == 0) {
            (*(*(char**)((char*)this + 0x1c) + 0x1346))++;
            if (*(*(char**)((char*)this + 0x1c) + 0x1346) > 2) {
                *(*(char**)((char*)this + 0x1c) + 0x1346) = 0;
            }
            g_fkeyHeld = 1;
        } else if ((v108[65] & 0x80) != 0 && g_fkeyHeld == 0) {
            *(int*)(*(char**)((char*)this + 0x1c) + 0x1348) = *(int*)(*(char**)((char*)this + 0x1c) + 0x1348) == 0;
            g_fkeyHeld = 1;
        }
    } else if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 5 && *(*(char**)((char*)this + 0x1c) + 0x14283) == 2 && (v108[64] & 0x80) != 0) {
        Unk7661a0();
    }
    if ((v108[66] & 0x80) != 0 && g_fkeyHeld == 0) {
        *(int*)((char*)this + 0x588) = *(int*)((char*)this + 0x588) == 0;
        g_fkeyHeld = 1;
    }
    if (*(short*)((char*)this + 0x574) == 0x7d0) {
        *(short*)((char*)this + 0x574) = 0;
        *(short*)((char*)this + 0x576) = 0x270f;
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ee) = *(short*)((char*)this + 0x576);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ee) = *(short*)((char*)this + 0x576);
        *(int*)(*(char**)((char*)this + 0xc) + 0x108) = 0x270f;
        *(int*)(*(char**)((char*)this + 0x10) + 0x108) = 0x270f;
    }
    if ((v108[63] & 0x80) != 0 || (v108[64] & 0x80) != 0 || (v108[65] & 0x80) != 0 || (v108[66] & 0x80) != 0) {
        g_fkeyHeld = 1;
    } else {
        g_fkeyHeld = 0;
    }
    if (1) {
    } else {
        if ((v108[59] & 0x80) != 0) {
            *((char*)this + 0x578) = 1;
        }
        if ((v108[60] & 0x80) != 0) {
            *((char*)this + 0x578) = 2;
        }
        if ((v108[61] & 0x80) != 0) {
            *((char*)this + 0x578) = 3;
        }
        if ((v108[67] & 0x80) != 0) {
            *(int*)((char*)this + 0x58c) = 1;
        }
        if ((v108[68] & 0x80) != 0) {
            *(int*)((char*)this + 0x58c) = 0;
        }
        if ((v108[87] & 0x80) != 0) {
            *(int*)((char*)this + 0x590) = 0;
        }
        if ((v108[88] & 0x80) != 0) {
            *(int*)(*(char**)((char*)this + 0xc) + 0x108) = 1;
            *(int*)(*(char**)((char*)this + 0x10) + 0x108) = 1;
        }
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x14283) == 1 && *(int*)((char*)this + 0x588) == 0) {
        if (*(*(char**)((char*)this + 0x1c) + 0x1340) > 0) {
            *(short*)((char*)this + 0x574) = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
            *(short*)((char*)this + 0x576) = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
        } else {
            *(short*)((char*)this + 0x574) = 0x3e8;
            *(short*)((char*)this + 0x576) = 0x270f;
        }
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ee) = *(short*)((char*)this + 0x576);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ee) = *(short*)((char*)this + 0x576);
        return;
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x14283) == 2 && *(int*)((char*)this + 0x588) == 0) {
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(short*)((char*)this + 0x574));
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(short*)((char*)this + 0x576));
    }
}

int CScene3::Unk765fa0()
{
    if (*(double*)((char*)this + 0x580) < 100.0) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Brighten((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), 0, 0xff, (int)(100.0 - *(double*)((char*)this + 0x580)));
        ((CSound*)*(int*)((char*)this + 0x28))->SetVolume(*(short*)(*(char**)((char*)this + 0x1c) + 0xf26), (int)(-*(double*)((char*)this + 0x580) * 100.0 / 2.0) + *(int*)(*(char**)((char*)this + 0x1c) + 0xf2c));
    }
    (*(double*)((char*)this + 0x580))++;
    if (*(double*)((char*)this + 0x580) >= 200.0) {
        return 1;
    }
    return 0;
}

void CScene3::Unk766070()
{
    if (*(*(char**)((char*)this + 0x1c) + 0x1350) == 0) {
        return;
    }
    EffectDesc v48;
    switch (*(*(char**)((char*)this + 0x1c) + 0x1350)) {
    case 1:
        v48.unk0 = 0;
        v48.x = 160.0;
        v48.y = 120.0;
        v48.side = 0;
        v48.unk20 = 2;
        v48.unk21 = 2;
        v48.unk24 = 1;
        v48.type = 0x1b;
        v48.unk2c = -1;
        ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&v48);
        *(*(char**)((char*)this + 0x1c) + 0x1350) = 0x63;
        *(short*)(*(char**)((char*)this + 0x1c) + 0x1352) = 0x12c;
        break;
    case 2:
        v48.unk0 = 0;
        v48.x = 160.0;
        v48.y = 120.0;
        v48.side = 0;
        v48.unk20 = 2;
        v48.unk21 = 2;
        v48.unk24 = 1;
        v48.type = 5;
        v48.unk2c = *(*(char**)((char*)this + 0x1c) + 0x134d) + 0xb;
        ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&v48);
        *(*(char**)((char*)this + 0x1c) + 0x1350) = 0x63;
        *(short*)(*(char**)((char*)this + 0x1c) + 0x1352) = 0x10e;
    }
}

void CScene3::Unk7661a0()
{
    char v34[40];
    char vc[8];

    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 5 && *(*(char**)((char*)this + 0x1c) + 0x14283) == 2) {
        CScene::Unk759c90((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), 0, 0, 0);
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Close();
        strcpy(v34, "replay\\data");
        _itoa(*(*(char**)((char*)this + 0x1c) + 0x14282) + 1, vc, 0xa);
        strcat(v34, (const char*)vc);
        strcat(v34, "-");
        _itoa(*(*(char**)((char*)this + 0x1c) + 0x14281) + 1, vc, 0xa);
        strcat(v34, (const char*)vc);
        strcat(v34, ".rep");
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->OpenWrite((const char*)v34);
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x14) + 0x8d));
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x18) + 0x8d));
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(0x68);
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)((char*)this + 0x1c) + 0xf32));
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x14) + 0x8e));
        ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x18) + 0x8e));
        ((CGame*)*(int*)((char*)this + 0x1c))->Reset();
        ((CPlayer*)*(int*)*(char**)((char*)this + 0x14))->Vf11();
        ((CPlayer*)*(int*)*(char**)((char*)this + 0x18))->Vf11();
        *(short*)(*(char**)((char*)this + 0xc) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(short*)(*(char**)((char*)this + 0x10) + 0x30ec) = *(short*)((char*)this + 0x574);
        *(*(char**)((char*)this + 0x1c) + 0x1350) = 1;
        *(int*)((char*)this + 0x440) = 0;
        *(int*)((char*)this + 0x444) = -0x32;
        *(int*)((char*)this + 0x448) = *(int*)((char*)this + 0x440);
        *(int*)((char*)this + 0x44c) = *(int*)((char*)this + 0x444);
        *(int*)((char*)this + 0x450) = 5;
        *(int*)((char*)this + 0x454) = -0xa0;
        *(int*)((char*)this + 0x458) = 0;
        *((char*)this + 0x578) = 3;
        Unk7647b0();
        Draw();
        CScene::Unk759e20((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), 0);
    }
}

void CScene3::Unk766480()
{
    int l1f0;
    int v1ec;
    CollisionInfo x1e8;
    int vf8;
    int lf4;
    CollisionInfo vf0;

    x1e8.frame = *(PatternFrame*)(char*)(*(int*)(*(char**)(*(char**)((char*)this + 0xc) + 0x164) + *(WORD*)(*(char**)((char*)this + 0xc) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0xc) + 0xa) * 0xc8);
    x1e8.anim = *(EffectFrame*)(char*)(*(int*)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + *(WORD*)(*(char**)((char*)this + 0xc) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0xc) + 0xa) * 0xc);
    x1e8.x = *(double*)(*(char**)((char*)this + 0xc) + 0x20);
    x1e8.y = *(double*)(*(char**)((char*)this + 0xc) + 0x28);
    x1e8.facing = *(*(char**)((char*)this + 0xc) + 0x50);
    vf0.frame = *(PatternFrame*)(char*)(*(int*)(*(char**)(*(char**)((char*)this + 0x10) + 0x164) + *(WORD*)(*(char**)((char*)this + 0x10) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + 0xa) * 0xc8);
    vf0.anim = *(EffectFrame*)(char*)(*(int*)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + *(WORD*)(*(char**)((char*)this + 0x10) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + 0xa) * 0xc);
    vf0.x = *(double*)(*(char**)((char*)this + 0x10) + 0x20);
    vf0.y = *(double*)(*(char**)((char*)this + 0x10) + 0x28);
    vf0.facing = *(*(char**)((char*)this + 0x10) + 0x50);
    lf4 = Unk7679b0(*(int*)((char*)this + 0xc), *(int*)((char*)this + 0x10), (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0);
    v1ec = Unk7679b0(*(int*)((char*)this + 0x10), *(int*)((char*)this + 0xc), (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8);
    *(int*)(*(char**)((char*)this + 0xc) + 0x144) = 0;
    *(int*)(*(char**)((char*)this + 0x10) + 0x144) = 0;
    vf8 = *(short*)(*(char**)((char*)this + 0xc) + 0x2cc);
    while (vf8 != *(short*)(*(char**)((char*)this + 0xc) + 0x2ca)) {
        l1f0 = *(short*)(*(char**)((char*)this + 0x10) + 0x2cc);
        while (l1f0 != *(short*)(*(char**)((char*)this + 0x10) + 0x2ca)) {
            if (*(int*)(*(char**)((char*)this + 0xc) + 0x3d0 + vf8 * 4) != 0 && *(int*)(*(char**)((char*)this + 0x10) + 0x3d0 + l1f0 * 4) != 0) {
                Unk76bab0(*(int*)((char*)this + 0xc), *(int*)((char*)this + 0x10), vf8, l1f0);
            }
            l1f0++;
            if (l1f0 >= 0x40) {
                l1f0 = 0;
            }
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = *(short*)(*(char**)((char*)this + 0xc) + 0x2cc);
    while (vf8 != *(short*)(*(char**)((char*)this + 0xc) + 0x2ca)) {
        l1f0 = *(short*)(*(char**)((char*)this + 0x10) + 0x2cc);
        while (l1f0 != *(short*)(*(char**)((char*)this + 0x10) + 0x2ca)) {
            if (*(int*)(*(char**)((char*)this + 0xc) + 0x3d0 + vf8 * 4) != 0 && *(int*)(*(char**)((char*)this + 0x10) + 0x3d0 + l1f0 * 4) != 0) {
                Unk76b090(*(int*)((char*)this + 0xc), *(int*)((char*)this + 0x10), vf8, l1f0);
                Unk76b090(*(int*)((char*)this + 0x10), *(int*)((char*)this + 0xc), l1f0, vf8);
            }
            l1f0++;
            if (l1f0 >= 0x40) {
                l1f0 = 0;
            }
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = *(short*)(*(char**)((char*)this + 0x10) + 0x2cc);
    while (vf8 != *(short*)(*(char**)((char*)this + 0x10) + 0x2ca)) {
        if (*(int*)(*(char**)((char*)this + 0x10) + 0x3d0 + vf8 * 4) != 0) {
            Unk7697d0(*(int*)((char*)this + 0x10), *(int*)((char*)this + 0xc), vf8, (CollisionInfo*)&x1e8);
            Unk76bd40(*(int*)((char*)this + 0xc), *(int*)((char*)this + 0x10), (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0, vf8);
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = *(short*)(*(char**)((char*)this + 0xc) + 0x2cc);
    while (vf8 != *(short*)(*(char**)((char*)this + 0xc) + 0x2ca)) {
        if (*(int*)(*(char**)((char*)this + 0xc) + 0x3d0 + vf8 * 4) != 0) {
            Unk7697d0(*(int*)((char*)this + 0xc), *(int*)((char*)this + 0x10), vf8, (CollisionInfo*)&vf0);
            Unk76bd40(*(int*)((char*)this + 0x10), *(int*)((char*)this + 0xc), (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8, vf8);
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    x1e8.unke9 = *(*(char**)((char*)this + 0xc) + 0x168);
    x1e8.unkea = *(short*)(*(char**)((char*)this + 0xc) + 0x16c);
    vf0.unke9 = *(*(char**)((char*)this + 0x10) + 0x168);
    vf0.unkea = *(short*)(*(char**)((char*)this + 0x10) + 0x16c);
    if (v1ec == 0) {
        Unk767f60(*(int*)((char*)this + 0xc), *(int*)((char*)this + 0x10), (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0);
    }
    if (lf4 == 0) {
        Unk767f60(*(int*)((char*)this + 0x10), *(int*)((char*)this + 0xc), (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8);
    }
}

void CScene3::Unk766b50()
{
    int x3c;
    RECT v38;
    RECT v28;
    double n18;
    double v10;
    double x8;

    v10 = *(double*)(*(char**)((char*)this + 0xc) + 0x30);
    n18 = *(double*)(*(char**)((char*)this + 0x10) + 0x30);
    *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = 0.0;
    *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = 0.0;
    v38 = this->Unk767600((int)(ObjBase*)(CPlayer*)*(int*)((char*)this + 0xc), *(int*)(*(char**)(*(char**)((char*)this + 0xc) + 0x164) + *(WORD*)(*(char**)((char*)this + 0xc) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0xc) + 0xa) * 0xc8 + 0x90);
    v28 = this->Unk767600((int)(ObjBase*)(CPlayer*)*(int*)((char*)this + 0x10), *(int*)(*(char**)(*(char**)((char*)this + 0x10) + 0x164) + *(WORD*)(*(char**)((char*)this + 0x10) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + 0xa) * 0xc8 + 0x90);
    if (Unk767930((int)&v38, (int)&v28) != 0) {
        if (v38.left + v38.right - (v28.left + v28.right) > 0) {
            x3c = v28.right - v38.left;
            (int)(*(double*)(*(char**)((char*)this + 0xc) + 0x20) <= 160.0);
            *(double*)(*(char**)((char*)this + 0xc) + 0x20) += x3c / 2.0;
            (int)(*(double*)(*(char**)((char*)this + 0xc) + 0x20) > 160.0);
            *(double*)(*(char**)((char*)this + 0x10) + 0x20) = *(double*)(*(char**)((char*)this + 0x10) + 0x20) - x3c / 2.0;
            if ((char)((CPlayer*)*(int*)((char*)this + 0xc))->Unk40ff70() == -1) {
                v10 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 < 0.0) * v10;
                n18 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18 < 0.0) * n18;
                if (*(*(char**)((char*)this + 0xc) + 0x50) * v10 < *(*(char**)((char*)this + 0x10) + 0x50) * n18) {
                    x8 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18) / 2.0;
                    n18 = *(*(char**)((char*)this + 0x10) + 0x50) * x8;
                    *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = v10 - *(double*)(*(char**)((char*)this + 0xc) + 0x30);
                    *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = n18 - *(double*)(*(char**)((char*)this + 0x10) + 0x30);
                }
                return;
            }
            if ((char)((CPlayer*)*(int*)((char*)this + 0x10))->Unk40ff70() == 1) {
                n18 = (*(*(char**)((char*)this + 0x10) + 0x50) * n18 > 0.0) * n18;
                v10 = (*(*(char**)((char*)this + 0x10) + 0x50) * n18 + *(*(char**)((char*)this + 0xc) + 0x50) * v10 > 0.0) * v10;
                if (*(*(char**)((char*)this + 0x10) + 0x50) * n18 > *(*(char**)((char*)this + 0xc) + 0x50) * v10) {
                    x8 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18) / 2.0;
                    v10 = *(*(char**)((char*)this + 0xc) + 0x50) * x8;
                    *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = v10 - *(double*)(*(char**)((char*)this + 0xc) + 0x30);
                    *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = n18 - *(double*)(*(char**)((char*)this + 0x10) + 0x30);
                }
                return;
            }
            if (*(*(char**)((char*)this + 0x10) + 0x50) * n18 >= 0.0 && *(*(char**)((char*)this + 0xc) + 0x50) * v10 <= 0.0) {
                x8 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18) / 2.0;
                v10 = *(*(char**)((char*)this + 0xc) + 0x50) * x8;
                n18 = *(*(char**)((char*)this + 0x10) + 0x50) * x8;
                *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = v10 - *(double*)(*(char**)((char*)this + 0xc) + 0x30);
                *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = n18 - *(double*)(*(char**)((char*)this + 0x10) + 0x30);
                return;
            }
            return;
        }
        x3c = v28.left - v38.right;
        (int)(*(double*)(*(char**)((char*)this + 0x10) + 0x20) >= 479.0);
        *(double*)(*(char**)((char*)this + 0xc) + 0x20) += x3c / 2.0;
        (int)(*(double*)(*(char**)((char*)this + 0x10) + 0x20) < 479.0);
        *(double*)(*(char**)((char*)this + 0x10) + 0x20) = *(double*)(*(char**)((char*)this + 0x10) + 0x20) - x3c / 2.0;
        if ((char)((CPlayer*)*(int*)((char*)this + 0xc))->Unk40ff70() == 1) {
            v10 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 > 0.0) * v10;
            n18 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18 > 0.0) * n18;
            if (*(*(char**)((char*)this + 0xc) + 0x50) * v10 > *(*(char**)((char*)this + 0x10) + 0x50) * n18) {
                x8 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18) / 2.0;
                n18 = *(*(char**)((char*)this + 0x10) + 0x50) * x8;
                *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = v10 - *(double*)(*(char**)((char*)this + 0xc) + 0x30);
                *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = n18 - *(double*)(*(char**)((char*)this + 0x10) + 0x30);
            }
            return;
        }
        if ((char)((CPlayer*)*(int*)((char*)this + 0x10))->Unk40ff70() == -1) {
            n18 = (*(*(char**)((char*)this + 0x10) + 0x50) * n18 < 0.0) * n18;
            v10 = (*(*(char**)((char*)this + 0x10) + 0x50) * n18 + *(*(char**)((char*)this + 0xc) + 0x50) * v10 < 0.0) * v10;
            if (*(*(char**)((char*)this + 0xc) + 0x50) * v10 < *(*(char**)((char*)this + 0x10) + 0x50) * n18) {
                x8 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18) / 2.0;
                v10 = *(*(char**)((char*)this + 0xc) + 0x50) * x8;
                *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = v10 - *(double*)(*(char**)((char*)this + 0xc) + 0x30);
                *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = n18 - *(double*)(*(char**)((char*)this + 0x10) + 0x30);
            }
            return;
        }
        if (*(*(char**)((char*)this + 0x10) + 0x50) * n18 <= 0.0 && *(*(char**)((char*)this + 0xc) + 0x50) * v10 >= 0.0) {
            x8 = (*(*(char**)((char*)this + 0xc) + 0x50) * v10 + *(*(char**)((char*)this + 0x10) + 0x50) * n18) / 2.0;
            v10 = *(*(char**)((char*)this + 0xc) + 0x50) * x8;
            n18 = *(*(char**)((char*)this + 0x10) + 0x50) * x8;
            *(double*)(*(char**)((char*)this + 0xc) + 0xb0) = v10 - *(double*)(*(char**)((char*)this + 0xc) + 0x30);
            *(double*)(*(char**)((char*)this + 0x10) + 0xb0) = n18 - *(double*)(*(char**)((char*)this + 0x10) + 0x30);
        }
    }
}

RECT CScene3::Unk767600(int p1, int p2)
{
    short v18;
    RECT v14;
    short l4;

    l4 = *(short*)(*(char**)(*(char**)((char*)p1 + 8) + *(WORD*)(char*)p1 * 8 + 4) + *(WORD*)((char*)p1 + 2) * 0xc + 4);
    v18 = *(short*)(*(char**)(*(char**)((char*)p1 + 8) + *(WORD*)(char*)p1 * 8 + 4) + *(WORD*)((char*)p1 + 2) * 0xc + 6);
    if (*((char*)p1 + 0x48) == 1) {
        v14.top = (int)(*(double*)((char*)p1 + 0x20) - v18 + *(int*)((char*)p2 + 4));
        v14.bottom = (int)(*(double*)((char*)p1 + 0x20) - v18 + *(int*)((char*)p2 + 0xc));
        v14.left = (int)(*(double*)((char*)p1 + 0x18) - 0.5 - l4 + *(int*)(char*)p2);
        v14.right = (int)(*(double*)((char*)p1 + 0x18) - 0.5 - l4 + *(int*)((char*)p2 + 8));
    } else {
        v14.top = (int)(*(double*)((char*)p1 + 0x20) - v18 + *(int*)((char*)p2 + 4));
        v14.bottom = (int)(*(double*)((char*)p1 + 0x20) - v18 + *(int*)((char*)p2 + 0xc));
        v14.left = (int)(*(double*)((char*)p1 + 0x18) + 0.5 + l4 - *(int*)((char*)p2 + 8));
        v14.right = (int)(*(double*)((char*)p1 + 0x18) + 0.5 + l4 - *(int*)(char*)p2);
    }
    return v14;
}

RECT CScene3::Unk7677a0(int p1, int p2)
{
    short v18;
    RECT v14;
    short l4;

    l4 = *(short*)((char*)p1 + 0xcc);
    v18 = *(short*)((char*)p1 + 0xce);
    if (*((char*)p1 + 0xe8) == 1) {
        v14.top = (int)(*(double*)((char*)p1 + 0xe0) - v18 + *(int*)((char*)p2 + 4));
        v14.bottom = (int)(*(double*)((char*)p1 + 0xe0) - v18 + *(int*)((char*)p2 + 0xc));
        v14.left = (int)(*(double*)((char*)p1 + 0xd8) - 0.5 - l4 + *(int*)(char*)p2);
        v14.right = (int)(*(double*)((char*)p1 + 0xd8) - 0.5 - l4 + *(int*)((char*)p2 + 8));
    } else {
        v14.top = (int)(*(double*)((char*)p1 + 0xe0) - v18 + *(int*)((char*)p2 + 4));
        v14.bottom = (int)(*(double*)((char*)p1 + 0xe0) - v18 + *(int*)((char*)p2 + 0xc));
        v14.left = (int)(*(double*)((char*)p1 + 0xd8) + 0.5 + l4 - *(int*)((char*)p2 + 8));
        v14.right = (int)(*(double*)((char*)p1 + 0xd8) + 0.5 + l4 - *(int*)(char*)p2);
    }
    return v14;
}

int CScene3::Unk767930(int p1, int p2)
{
    if (*(int*)((char*)p1 + 8) <= *(int*)(char*)p1 || *(int*)((char*)p1 + 4) >= *(int*)((char*)p1 + 0xc) || *(int*)((char*)p2 + 8) <= *(int*)(char*)p2 || *(int*)((char*)p2 + 4) >= *(int*)((char*)p2 + 0xc)) {
        return 0;
    }
    return ~(*(int*)((char*)p2 + 8) - *(int*)(char*)p1 | *(int*)((char*)p1 + 8) - *(int*)(char*)p2 | *(int*)((char*)p2 + 0xc) - *(int*)((char*)p1 + 4) | *(int*)((char*)p1 + 0xc) - *(int*)((char*)p2 + 4)) >> 0x1f;
}

int CScene3::Unk7679b0(int p1, int p2, CollisionInfo* p3, CollisionInfo* p4)
{
    RECT b29c;
    int v28c;
    RECT n288;
    int v278;
    int v274;
    int v270[4][5];
    RECT l220[5];
    PatternFrame b1d0;
    PatternFrame v108;
    RECT x40[4];

    v274 = 0;
    b1d0 = *(PatternFrame*)(char*)p3;
    v108 = *(PatternFrame*)(char*)p4;
    v28c = 0;
    for (; v28c < 4; v28c++) {
        x40[v28c] = this->Unk7677a0((int)p3, (int)&b1d0.attackBoxes[v28c]);
    }
    v28c = 0;
    for (; v28c < 5; v28c++) {
        l220[v28c] = this->Unk7677a0((int)p4, (int)&v108.boxes[v28c]);
    }
    b29c = this->Unk7677a0((int)p4, (int)&v108.box90);
    if (*(int*)((char*)p1 + 0x168) == 0 && (v108.flagsB0 & 0x20) == 0 && *(short*)((char*)p1 + 0x16c) > 0 && (*((char*)p2 + 0x130) <= 0 || (b1d0.flagsAA & 0x40) <= 0) && ((CPlayer*)p2)->Unk4102e0() == 0 && *(short*)((char*)p2 + 0x13c) == 0) {
        if ((b1d0.flagsAA & 0x40) > 0) {
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v270[v28c][0] = 1;
                v274 = Unk767930((int)&x40[v28c], (int)&b29c) | v274;
            }
        } else {
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    v270[v28c][v278] = Unk767930((int)&x40[v28c], (int)&l220[v278]);
                    v274 |= v270[v28c][v278];
                }
            }
        }
        if (v274 != 0) {
            n288 = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    if (v270[v28c][v278] != 0) {
                        if (n288.left < x40[v28c].left) {
                            n288.left = x40[v28c].left;
                        }
                        if (n288.top < x40[v28c].top) {
                            n288.top = x40[v28c].top;
                        }
                        if (n288.right > x40[v28c].right) {
                            n288.right = x40[v28c].right;
                        }
                        if (n288.bottom > x40[v28c].bottom) {
                            n288.bottom = x40[v28c].bottom;
                        }
                        if (n288.left < l220[v278].left) {
                            n288.left = l220[v278].left;
                        }
                        if (n288.top < l220[v278].top) {
                            n288.top = l220[v278].top;
                        }
                        if (n288.right > l220[v278].right) {
                            n288.right = l220[v278].right;
                        }
                        if (n288.bottom > l220[v278].bottom) {
                            n288.bottom = l220[v278].bottom;
                        }
                    }
                }
            }
            if (*(int*)((char*)p2 + 0x170) != 0 && *(short*)((char*)p2 + 0x14e) >= 0x1e && *(short*)((char*)p2 + 0x13a) == 0 && ((CPlayer*)p2)->Unk4100f0((int)&b1d0) != 0 && (b1d0.flagsAA & 0x80) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void CScene3::Unk767f60(int p1, int p2, CollisionInfo* p3, CollisionInfo* p4)
{
    RECT v2e4;
    int v2d4;
    RECT v2d0;
    int v278;
    int v274;
    int v270[4][5];
    RECT l220[5];
    PatternFrame b1d0;
    PatternFrame v108;
    RECT x40[4];

    v274 = 0;
    b1d0 = *(PatternFrame*)(char*)p3;
    v108 = *(PatternFrame*)(char*)p4;
    EffectDesc k2c0;
    v2d4 = 0;
    for (; v2d4 < 4; v2d4++) {
        x40[v2d4] = this->Unk7677a0((int)p3, (int)&b1d0.attackBoxes[v2d4]);
    }
    v2d4 = 0;
    for (; v2d4 < 5; v2d4++) {
        l220[v2d4] = this->Unk7677a0((int)p4, (int)&v108.boxes[v2d4]);
    }
    v2e4 = this->Unk7677a0((int)p4, (int)&v108.box90);
    if (*((char*)p3 + 0xe9) == 0 && (v108.flagsB0 & 0x20) == 0 && *(short*)((char*)p3 + 0xea) > 0 && (*((char*)p2 + 0x130) <= 0 || (b1d0.flagsAA & 0x40) <= 0) && ((CPlayer*)p2)->Unk4102e0() == 0 && *(short*)((char*)p2 + 0x13c) == 0) {
        if ((b1d0.flagsAA & 0x40) > 0) {
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v270[v2d4][0] = 1;
                v274 = Unk767930((int)&x40[v2d4], (int)&v2e4) | v274;
            }
        } else {
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    v270[v2d4][v278] = Unk767930((int)&x40[v2d4], (int)&l220[v278]);
                    v274 |= v270[v2d4][v278];
                }
            }
        }
        if (v274 != 0) {
            v2d0 = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    if (v270[v2d4][v278] != 0) {
                        if (v2d0.left < x40[v2d4].left) {
                            v2d0.left = x40[v2d4].left;
                        }
                        if (v2d0.top < x40[v2d4].top) {
                            v2d0.top = x40[v2d4].top;
                        }
                        if (v2d0.right > x40[v2d4].right) {
                            v2d0.right = x40[v2d4].right;
                        }
                        if (v2d0.bottom > x40[v2d4].bottom) {
                            v2d0.bottom = x40[v2d4].bottom;
                        }
                        if (v2d0.left < l220[v278].left) {
                            v2d0.left = l220[v278].left;
                        }
                        if (v2d0.top < l220[v278].top) {
                            v2d0.top = l220[v278].top;
                        }
                        if (v2d0.right > l220[v278].right) {
                            v2d0.right = l220[v278].right;
                        }
                        if (v2d0.bottom > l220[v278].bottom) {
                            v2d0.bottom = l220[v278].bottom;
                        }
                    }
                }
            }
            if ((v108.flagsB0 & 0x1000) > 0 && (b1d0.flagsAA & 0x100) == 0 && (b1d0.flagsAA & 1) > 0) {
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p1 + 0x168) = 2;
                *(int*)((char*)p1 + 0x168) = 6;
                *(int*)((char*)p2 + 0x168) = 6;
                return;
            }
            if ((v108.flagsB0 & 0x800) > 0 && (b1d0.flagsAA & 0x100) == 0 && (b1d0.flagsAA & 2) > 0) {
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p1 + 0x168) = 2;
                *(int*)((char*)p1 + 0x168) = 6;
                *(int*)((char*)p2 + 0x168) = 6;
                return;
            }
            if (*(int*)((char*)p2 + 0x170) != 0 && *(short*)((char*)p2 + 0x14e) >= 0x1e && *(short*)((char*)p2 + 0x13a) == 0 && ((CPlayer*)p2)->Unk4100f0((int)&b1d0) != 0 && (b1d0.flagsAA & 0x80) == 0) {
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x148) += b1d0.unkb6;
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                k2c0.type = 0x11;
                k2c0.unk2c = 0xa;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
                if (*(double*)((char*)p2 + 0x28) == 0.0) {
                    *(short*)((char*)p2 + 8) = (*((char*)p2 + 0x189) == 1) + 0xa8;
                } else {
                    *(short*)((char*)p2 + 8) = 0xaa;
                }
                ((CPlayer*)p1)->Unk40f190();
                ((CPlayer*)p2)->Unk40f190();
                *(short*)((char*)p2 + 0x14c) = 0x3c;
                *(int*)((char*)p2 + 0x170) = 0;
                *(int*)((char*)p1 + 0x170) = 1;
                return;
            }
            if (*(short*)((char*)p2 + 0x14e) >= 0x1e && *(double*)((char*)p2 + 0x28) < 0.0 && ((CPlayer*)p2)->Unk410050((int)&b1d0, (int)&v108) != 0) {
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x148) += b1d0.unkb6;
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                k2c0.type = 0x11;
                k2c0.unk2c = 0xa;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
                *(short*)((char*)p2 + 8) = 0xaa;
                ((CPlayer*)p1)->Unk40f190();
                ((CPlayer*)p2)->Unk40f190();
                *(short*)((char*)p2 + 0x14c) = 0x3c;
                *(int*)((char*)p1 + 0x170) = 1;
                return;
            }
            if (((CPlayer*)p2)->Unk410050((int)&b1d0, (int)&v108) != 0 && *(short*)((char*)p2 + 0x14e) >= 0x1e && *(double*)((char*)p2 + 0x28) == 0.0 && *(WORD*)((char*)p2 + 8) != 0xa8 && *(WORD*)((char*)p2 + 8) != 0xa9) {
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x148) += b1d0.unkb6;
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                k2c0.type = 0x11;
                k2c0.unk2c = 0xa;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
                *(short*)((char*)p2 + 8) = (*((char*)p2 + 0x189) == 1) + 0xa8;
                ((CPlayer*)p1)->Unk40f190();
                ((CPlayer*)p2)->Unk40f190();
                *(short*)((char*)p2 + 0x14c) = 0x3c;
                *(int*)((char*)p1 + 0x170) = 1;
                return;
            }
            if ((v108.flagsB0 & 0x200) > 0 && (v108.flagsAA & 1) > 0 && (b1d0.flagsAA & 1) > 0) {
                (*(short*)((char*)p1 + 0x16c))--;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x14a) = b1d0.unkc2;
                *(short*)((char*)p2 + 0x14a) = b1d0.unkc4;
                *(int*)((char*)p2 + 0x108) -= b1d0.unka8;
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                *(float*)((char*)p2 + 0x134) = b1d0.unka0 / 0x1e + *(float*)((char*)p2 + 0x134);
                if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                    *(int*)((char*)p2 + 0x134) = 0x43b40000;
                }
                return;
            }
            if ((v108.flagsB0 & 0x200) > 0 && (v108.flagsAA & 2) > 0 && (b1d0.flagsAA & 2) > 0) {
                (*(short*)((char*)p1 + 0x16c))--;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x14a) = b1d0.unkc2;
                *(short*)((char*)p2 + 0x14a) = b1d0.unkc4;
                *(int*)((char*)p2 + 0x108) -= b1d0.unka8;
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                *(float*)((char*)p2 + 0x134) = b1d0.unka0 / 0x1e + *(float*)((char*)p2 + 0x134);
                if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                    *(int*)((char*)p2 + 0x134) = 0x43b40000;
                }
                return;
            }
            if ((v108.flagsB0 & 0x200) > 0 && (v108.flagsAA & 4) > 0 && (b1d0.flagsAA & 4) > 0 && *(double*)((char*)p2 + 0x28) < 0.0) {
                (*(short*)((char*)p1 + 0x16c))--;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x14a) = b1d0.unkc2;
                *(short*)((char*)p2 + 0x14a) = b1d0.unkc4;
                *(int*)((char*)p2 + 0x108) -= b1d0.unka8;
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                return;
            }
            if (((CPlayer*)p2)->Unk410050((int)&b1d0, (int)&v108) != 0) {
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x148) += b1d0.unkb6;
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = *((char*)p2 + 0x50) == -1;
                k2c0.unk20 = 2;
                k2c0.unk21 = 1;
                k2c0.unk24 = 0;
                *(short*)((char*)p2 + 8) = (b1d0.flagsAA & 0x10) / 0x10 + 0x96 + (b1d0.flagsAA & 0x20) / 0x20 * 2 + (*((char*)p2 + 0x189) == 1 || (b1d0.flagsAA & v108.flagsB0 & 5) == 0 && *(int*)((char*)p2 + 0xa4) != 0) * 3;
                if (*(double*)((char*)p2 + 0x28) < 0.0) {
                    *(short*)((char*)p2 + 8) = 0x9c;
                }
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
                *(short*)((char*)p1 + 0x14a) = b1d0.unkc2;
                *(short*)((char*)p2 + 0x14a) = b1d0.unkc4;
                *(int*)((char*)p2 + 0x108) -= b1d0.unka8;
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                if (*(float*)((char*)p1 + 0x134) > 0.0f) {
                    *(float*)((char*)p1 + 0x134) = *(float*)((char*)p1 + 0x134) - b1d0.unka0 / 0x1e;
                    if (*(float*)((char*)p1 + 0x134) < 0.0f) {
                        *(float*)((char*)p2 + 0x134) = *(float*)((char*)p2 + 0x134) - *(float*)((char*)p1 + 0x134);
                        *(int*)((char*)p1 + 0x134) = 0;
                    }
                } else {
                    *(float*)((char*)p2 + 0x134) = b1d0.unka0 / 0x1e + *(float*)((char*)p2 + 0x134);
                    if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                        *(int*)((char*)p2 + 0x134) = 0x43b40000;
                    }
                }
                *(int*)((char*)p2 + 0x154) = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
                return;
            }
            if ((v108.flagsB0 & 4) == 0 && *(short*)((char*)p2 + 0x138) == 0 || ((v108.flagsB0 & 4) > 0 || *(short*)((char*)p2 + 0x138) > 0) && (b1d0.flagsAA & 0x100) > 0 || (b1d0.flagsAA & 0x40) > 0) {
                if (*(double*)((char*)p2 + 0x28) >= 0.0) {
                    if (b1d0.unkae > 0) {
                        *(short*)((char*)p2 + 8) = b1d0.unkae;
                    } else if ((v108.flagsB0 & 3) == 3) {
                        *(short*)((char*)p2 + 8) = 0x3b;
                    } else if ((v108.flagsB0 & 1) != 0) {
                        *(short*)((char*)p2 + 8) = ((b1d0.flagsAA & 8) > 0) * 3 + 0x32 + ((b1d0.flagsAA & 0x10) > 0) + ((b1d0.flagsAA & 0x20) > 0) * 2;
                    } else if ((v108.flagsB0 & 2) != 0) {
                        *(short*)((char*)p2 + 8) = ((b1d0.flagsAA & 0x10) > 0) + 0x38 + ((b1d0.flagsAA & 0x20) > 0) * 2;
                    }
                } else if (b1d0.unkac > 0) {
                    *(short*)((char*)p2 + 8) = b1d0.unkac;
                } else {
                    *(short*)((char*)p2 + 8) = 0x3b;
                }
                *(int*)((char*)p1 + 0x168) = 3;
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
            } else {
                *(short*)((char*)p1 + 0x174) = 0;
                ((CPlayer*)p2)->Unk410ac0(0xdf, 3);
                *(int*)((char*)p1 + 0x168) = 7;
            }
            if ((v108.flagsB0 & 0x10) > 0) {
                *(short*)((char*)p1 + 0x174) = 0;
                if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                    *(double*)((char*)p1 + 0x178) -= 20.0;
                } else {
                    *(double*)((char*)p1 + 0x178) = 10000.0;
                }
            }
            *(double*)((char*)p2 + 0xc0) = b1d0.unkb8;
            *(double*)((char*)p2 + 0xc8) = b1d0.unkbc;
            *(int*)((char*)p2 + 0xd0) = 1;
            if (*(short*)((char*)p1 + 0x174) == 0) {
                *(int*)((char*)p2 + 0x10c) = *(int*)((char*)p2 + 0x108);
            }
            *(int*)((char*)p1 + 0x144) = (b1d0.flagsAA & 0x2000) > 0 && (v108.flagsB0 & 0x2000) > 0;
            *(int*)((char*)p2 + 0x108) -= (int)((double)b1d0.unka0 * ((CPlayer*)p1)->Unk410480() * ((CPlayer*)p2)->Unk410530() * ((CPlayer*)p1)->Unk410560());
            *(short*)((char*)p2 + 0x124) = (int)(b1d0.unkb2 * (*(double*)((char*)p1 + 0x178) / 10000.0 * 0.8));
            *(int*)((char*)p2 + 0x128) = (b1d0.flagsAA & 0x400) > 0;
            *(int*)((char*)p2 + 0x12c) = (b1d0.flagsAA & 0x800) > 0;
            *((char*)p2 + 0x158) = 0;
            *((char*)p2 + 0x159) = 0;
            *((char*)p2 + 0x15a) = 0;
            *(double*)((char*)p1 + 0xf8) = *(double*)((char*)p1 + 0x178) / 100.0;
            *(double*)((char*)p1 + 0x178) = b1d0.unka4 / 1e+03f * *(double*)((char*)p1 + 0x178);
            if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                *(double*)((char*)p1 + 0x178) = b1d0.unka4 / 1e+03f * *(double*)((char*)p1 + 0x178);
            }
            (*(short*)((char*)p1 + 0x174))++;
            *(short*)((char*)p1 + 0xf4) = *(short*)((char*)p1 + 0x174);
            *(short*)((char*)p1 + 0x104) = 0xb4;
            *(int*)((char*)p1 + 0x100) = *(int*)((char*)p2 + 0x10c) - *(int*)((char*)p2 + 0x108);
            *(short*)((char*)p1 + 0x148) += b1d0.unkb4;
            *(short*)((char*)p1 + 0x14a) = b1d0.unkc2;
            *(short*)((char*)p2 + 0x14a) = b1d0.unkc4;
            (*(short*)((char*)p1 + 0x16c))--;
            k2c0.unk0 = 0;
            k2c0.type = b1d0.unkc0;
            k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
            k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
            k2c0.side = *((char*)p1 + 0x50) < 0;
            k2c0.unk20 = 2;
            k2c0.unk21 = 1;
            k2c0.unk24 = 0;
            k2c0.unk2c = b1d0.unkc1;
            ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k2c0);
            if (*(int*)((char*)p2 + 0x108) <= 0 && *(short*)((char*)p2 + 0x140) == 0) {
                *(short*)((char*)p2 + 8) = b1d0.unkac;
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
            }
            ((CPlayer*)p1)->Unk410790((int)&b1d0);
        }
    }
}

void CScene3::Unk7697d0(int p1, int p2, int p3, CollisionInfo* p4)
{
    RECT v11c;
    RECT l10c;
    int mfc;
    int vf8[4][5];
    RECT na8[5];
    RECT a58[4];
    char* k14;
    int v10;
    int bc;
    char* x8;
    char* l4;

    k14 = (char*)(p1 + p3 * 0x98 + 0x4d0);
    x8 = (char*)(*(int*)(*(char**)((char*)p1 + 0x164) + *(WORD*)k14 * 8 + 4) + *(WORD*)(k14 + 2) * 0xc8);
    l4 = (char*)p4;
    if (*(int*)(k14 + 0x80) == 0 && (*(WORD*)(l4 + 0xb0) & 0x20) == 0 && *(short*)(k14 + 0x84) > 0 && (*((char*)p2 + 0x130) <= 0 || (*(WORD*)(x8 + 0xaa) & 0x40) <= 0) && ((CPlayer*)p2)->Unk4102e0() == 0 && *(short*)((char*)p2 + 0x13c) == 0) {
        mfc = 0;
        v10 = 0;
        for (; v10 < 4; v10++) {
            a58[v10] = this->Unk767600((int)k14, (int)(x8 + (v10 << 4) + 0x50));
        }
        v10 = 0;
        for (; v10 < 5; v10++) {
            na8[v10] = this->Unk7677a0((int)p4, (int)((v10 << 4) + l4));
        }
        v11c = this->Unk7677a0((int)p4, (int)(l4 + 0x90));
        if ((*(WORD*)(x8 + 0xaa) & 0x40) > 0) {
            v10 = 0;
            for (; v10 < 4; v10++) {
                vf8[v10][0] = 1;
                mfc = Unk767930((int)&a58[v10], (int)&v11c) | mfc;
            }
        } else {
            v10 = 0;
            for (; v10 < 4; v10++) {
                bc = 0;
                for (; bc < 5; bc++) {
                    vf8[v10][bc] = Unk767930((int)&a58[v10], (int)&na8[bc]);
                    mfc |= vf8[v10][bc];
                }
            }
        }
        if (mfc != 0) {
            EffectDesc k168;
            l10c = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v10 = 0;
            for (; v10 < 4; v10++) {
                bc = 0;
                for (; bc < 5; bc++) {
                    if (vf8[v10][bc] != 0) {
                        if (l10c.left < a58[v10].left) {
                            l10c.left = a58[v10].left;
                        }
                        if (l10c.top < a58[v10].top) {
                            l10c.top = a58[v10].top;
                        }
                        if (l10c.right > a58[v10].right) {
                            l10c.right = a58[v10].right;
                        }
                        if (l10c.bottom > a58[v10].bottom) {
                            l10c.bottom = a58[v10].bottom;
                        }
                        if (l10c.left < na8[bc].left) {
                            l10c.left = na8[bc].left;
                        }
                        if (l10c.top < na8[bc].top) {
                            l10c.top = na8[bc].top;
                        }
                        if (l10c.right > na8[bc].right) {
                            l10c.right = na8[bc].right;
                        }
                        if (l10c.bottom > na8[bc].bottom) {
                            l10c.bottom = na8[bc].bottom;
                        }
                    }
                }
            }
            if ((*(WORD*)(l4 + 0xb0) & 0x400) > 0 && (*(WORD*)(x8 + 0xaa) & 0x100) == 0) {
                (*(short*)(k14 + 0x84))--;
                *(int*)(k14 + 0x80) = 2;
                *(int*)((char*)p1 + 0x168) = 6;
                *(int*)((char*)p2 + 0x168) = 6;
                return;
            }
            if (*(int*)((char*)p2 + 0x170) != 0 && *(short*)((char*)p2 + 0x14e) >= 0x1e && *(short*)((char*)p2 + 0x13a) == 0 && ((CPlayer*)p2)->Unk4100f0((int)x8) != 0 && (*(WORD*)(x8 + 0xaa) & 0x80) == 0) {
                *(int*)(k14 + 0x80) = 2;
                *(short*)((char*)p1 + 0x148) += *(short*)(x8 + 0xb6);
                (*(short*)(k14 + 0x84))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p2 + 0x50) == -1;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                k168.type = 0x11;
                k168.unk2c = 0xa;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                ((CPlayer*)p2)->Vf0();
                *((char*)p2 + 0x50) = -*(k14 + 0x48);
                if (*(double*)((char*)p2 + 0x28) == 0.0) {
                    *(short*)((char*)p2 + 8) = (*((char*)p2 + 0x189) == 1) + 0xa8;
                } else {
                    *(short*)((char*)p2 + 8) = 0xaa;
                }
                ((CPlayer*)p1)->Unk40f190();
                ((CPlayer*)p2)->Unk40f190();
                *(short*)((char*)p2 + 0x14c) = 0x3c;
                *(int*)((char*)p2 + 0x170) = 0;
                *(int*)((char*)p1 + 0x170) = 1;
                return;
            }
            if (*(short*)((char*)p2 + 0x14e) >= 0x1e && *(double*)((char*)p2 + 0x28) < 0.0 && ((CPlayer*)p2)->Unk410050((int)x8, (int)l4) != 0) {
                *(int*)(k14 + 0x80) = 2;
                *(short*)((char*)p1 + 0x148) += *(short*)(x8 + 0xb6);
                (*(short*)(k14 + 0x84))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p2 + 0x50) == -1;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                k168.type = 0x11;
                k168.unk2c = 0xa;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                ((CPlayer*)p2)->Vf0();
                *((char*)p2 + 0x50) = -*(k14 + 0x48);
                *(short*)((char*)p2 + 8) = 0xaa;
                ((CPlayer*)p1)->Unk40f190();
                ((CPlayer*)p2)->Unk40f190();
                *(short*)((char*)p2 + 0x14c) = 0x3c;
                *(int*)((char*)p1 + 0x170) = 1;
                return;
            }
            if (((CPlayer*)p2)->Unk410050((int)x8, (int)l4) != 0 && *(short*)((char*)p2 + 0x14e) >= 0x1e && *(double*)((char*)p2 + 0x28) == 0.0 && *(WORD*)((char*)p2 + 8) != 0xa8 && *(WORD*)((char*)p2 + 8) != 0xa9) {
                *(int*)(k14 + 0x80) = 2;
                *(short*)((char*)p1 + 0x148) += *(short*)(x8 + 0xb6);
                (*(short*)(k14 + 0x84))--;
                *(int*)((char*)p2 + 0xd0) = 1;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p2 + 0x50) == -1;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                k168.type = 0x11;
                k168.unk2c = 0xa;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                ((CPlayer*)p2)->Vf0();
                *((char*)p2 + 0x50) = -*(k14 + 0x48);
                *(short*)((char*)p2 + 8) = (*((char*)p2 + 0x189) == 1) + 0xa8;
                ((CPlayer*)p1)->Unk40f190();
                ((CPlayer*)p2)->Unk40f190();
                *(short*)((char*)p2 + 0x14c) = 0x3c;
                *(int*)((char*)p1 + 0x170) = 1;
                return;
            }
            if ((*(WORD*)(l4 + 0xb0) & 0x200) > 0 && (*(WORD*)(l4 + 0xaa) & 1) > 0 && (*(WORD*)(x8 + 0xaa) & 1) > 0) {
                (*(short*)(k14 + 0x84))--;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p2 + 0x50) == -1;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                k168.type = 2;
                k168.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x14a) = *(short*)(x8 + 0xc2);
                *(short*)((char*)p2 + 0x14a) = *(short*)(x8 + 0xc4);
                *(int*)((char*)p2 + 0x108) -= *(short*)(x8 + 0xa8);
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                *(float*)((char*)p2 + 0x134) = *(short*)(x8 + 0xa0) / 0x1e + *(float*)((char*)p2 + 0x134);
                if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                    *(int*)((char*)p2 + 0x134) = 0x43b40000;
                }
                return;
            }
            if ((*(WORD*)(l4 + 0xb0) & 0x200) > 0 && (*(WORD*)(l4 + 0xaa) & 2) > 0 && (*(WORD*)(x8 + 0xaa) & 2) > 0) {
                (*(short*)(k14 + 0x84))--;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p2 + 0x50) == -1;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                k168.type = 2;
                k168.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x14a) = *(short*)(x8 + 0xc2);
                *(short*)((char*)p2 + 0x14a) = *(short*)(x8 + 0xc4);
                *(int*)((char*)p2 + 0x108) -= *(short*)(x8 + 0xa8);
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                *(float*)((char*)p2 + 0x134) = *(short*)(x8 + 0xa0) / 0x1e + *(float*)((char*)p2 + 0x134);
                if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                    *(int*)((char*)p2 + 0x134) = 0x43b40000;
                }
                return;
            }
            if ((*(WORD*)(l4 + 0xb0) & 0x200) > 0 && (*(WORD*)(l4 + 0xaa) & 4) > 0 && (*(WORD*)(x8 + 0xaa) & 4) > 0 && *(double*)((char*)p2 + 0x28) < 0.0) {
                (*(short*)(k14 + 0x84))--;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p2 + 0x50) == -1;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                k168.type = 2;
                k168.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                *(int*)((char*)p1 + 0x168) = 2;
                *(short*)((char*)p1 + 0x14a) = *(short*)(x8 + 0xc2);
                *(short*)((char*)p2 + 0x14a) = *(short*)(x8 + 0xc4);
                *(int*)((char*)p2 + 0x108) -= *(short*)(x8 + 0xa8);
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                *(float*)((char*)p2 + 0x134) = *(short*)(x8 + 0xa0) / 0x1e + *(float*)((char*)p2 + 0x134);
                if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                    *(int*)((char*)p2 + 0x134) = 0x43b40000;
                }
                return;
            }
            if (((CPlayer*)p2)->Unk410050((int)x8, (int)l4) != 0) {
                *(short*)((char*)p2 + 8) = (*(WORD*)(x8 + 0xaa) & 0x10) / 0x10 + 0x96 + (*(WORD*)(x8 + 0xaa) & 0x20) / 0x20 * 2 + (*((char*)p2 + 0x189) == 1 || (*(WORD*)(x8 + 0xaa) & *(WORD*)(l4 + 0xb0) & 5) == 0 && *(int*)((char*)p2 + 0xa4) != 0) * 3;
                if (*(double*)((char*)p2 + 0x28) < 0.0) {
                    *(short*)((char*)p2 + 8) = 0x9c;
                }
                ((CPlayer*)p2)->Vf0();
                *((char*)p2 + 0x50) = -*(k14 + 0x48);
                *(int*)(k14 + 0x80) = 2;
                *(short*)(k14 + 0x86) = *(short*)(x8 + 0xc2);
                *(short*)((char*)p2 + 0x14a) = *(short*)(x8 + 0xc4);
                *(short*)((char*)p1 + 0x148) += *(short*)(x8 + 0xb6);
                (*(short*)(k14 + 0x84))--;
                *(int*)((char*)p2 + 0xd0) = 0;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = *((char*)p1 + 0x50) < 0;
                k168.unk20 = 2;
                k168.unk21 = 1;
                k168.unk24 = 0;
                *(int*)((char*)p2 + 0x108) -= *(short*)(x8 + 0xa8);
                if (*(int*)((char*)p2 + 0x108) <= 0) {
                    *(int*)((char*)p2 + 0x108) = 1;
                }
                if (*(float*)((char*)p1 + 0x134) > 0.0f) {
                    *(float*)((char*)p1 + 0x134) = *(float*)((char*)p1 + 0x134) - *(short*)(x8 + 0xa0) / 0x1e;
                    if (*(float*)((char*)p1 + 0x134) < 0.0f) {
                        *(float*)((char*)p2 + 0x134) = *(float*)((char*)p2 + 0x134) - *(float*)((char*)p1 + 0x134);
                        *(int*)((char*)p1 + 0x134) = 0;
                    }
                } else {
                    *(float*)((char*)p2 + 0x134) = *(short*)(x8 + 0xa0) / 0x1e + *(float*)((char*)p2 + 0x134);
                    if (*(float*)((char*)p2 + 0x134) > 3.6e+02f) {
                        *(int*)((char*)p2 + 0x134) = 0x43b40000;
                    }
                }
                *(int*)((char*)p2 + 0x154) = 1;
                k168.type = 2;
                k168.unk2c = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
                return;
            }
            if ((*(WORD*)(l4 + 0xb0) & 4) == 0 && *(short*)((char*)p2 + 0x138) == 0 || ((*(WORD*)(l4 + 0xb0) & 4) > 0 || *(short*)((char*)p2 + 0x138) > 0) && (*(WORD*)(x8 + 0xaa) & 0x100) > 0 || (*(WORD*)(x8 + 0xaa) & 0x40) > 0) {
                if (*(double*)((char*)p2 + 0x28) >= 0.0) {
                    if (*(short*)(x8 + 0xae) > 0) {
                        *(short*)((char*)p2 + 8) = *(short*)(x8 + 0xae);
                    } else if ((*(WORD*)(l4 + 0xb0) & 3) == 3) {
                        *(short*)((char*)p2 + 8) = 0x3b;
                    } else if ((*(WORD*)(l4 + 0xb0) & 1) != 0) {
                        *(short*)((char*)p2 + 8) = ((*(WORD*)(x8 + 0xaa) & 8) > 0) * 3 + 0x32 + ((*(WORD*)(x8 + 0xaa) & 0x10) > 0) + ((*(WORD*)(x8 + 0xaa) & 0x20) > 0) * 2;
                    } else if ((*(WORD*)(l4 + 0xb0) & 2) != 0) {
                        *(short*)((char*)p2 + 8) = ((*(WORD*)(x8 + 0xaa) & 0x10) > 0) + 0x38 + ((*(WORD*)(x8 + 0xaa) & 0x20) > 0) * 2;
                    }
                } else if (*(short*)(x8 + 0xac) > 0) {
                    *(short*)((char*)p2 + 8) = *(short*)(x8 + 0xac);
                } else {
                    *(short*)((char*)p2 + 8) = 0x3b;
                }
                *(int*)(k14 + 0x80) = 3;
                ((CPlayer*)p2)->Vf0();
                *((char*)p2 + 0x50) = -*(k14 + 0x48);
            } else {
                *(short*)((char*)p1 + 0x174) = 0;
                ((CPlayer*)p2)->Unk410ac0(0xe9, 3);
                *(int*)(k14 + 0x80) = 7;
            }
            if ((*(WORD*)(l4 + 0xb0) & 0x10) > 0) {
                *(short*)((char*)p1 + 0x174) = 0;
                if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                    *(double*)((char*)p1 + 0x178) -= 20.0;
                } else {
                    *(double*)((char*)p1 + 0x178) = 10000.0;
                }
            }
            *(double*)((char*)p2 + 0xc0) = *(float*)(x8 + 0xb8);
            *(double*)((char*)p2 + 0xc8) = *(float*)(x8 + 0xbc);
            *(int*)((char*)p2 + 0xd0) = 0;
            if (*(short*)((char*)p1 + 0x174) == 0) {
                *(int*)((char*)p2 + 0x10c) = *(int*)((char*)p2 + 0x108);
            }
            *(int*)((char*)p2 + 0x108) -= (int)((double)*(short*)(x8 + 0xa0) * ((CPlayer*)p1)->Unk410480() * ((CPlayer*)p2)->Unk410530() * ((CPlayer*)p1)->Unk410560());
            *(short*)((char*)p2 + 0x124) = (int)(*(short*)(x8 + 0xb2) * (*(double*)((char*)p1 + 0x178) / 10000.0) * (((*(WORD*)(x8 + 0xaa) & 0x2000) > 0 && (*(WORD*)(l4 + 0xb0) & 0x2000) > 0) + 1));
            *(int*)((char*)p2 + 0x128) = (*(WORD*)(x8 + 0xaa) & 0x400) > 0;
            *(int*)((char*)p2 + 0x12c) = (*(WORD*)(x8 + 0xaa) & 0x800) > 0;
            *((char*)p2 + 0x158) = 0;
            *((char*)p2 + 0x159) = 0;
            *((char*)p2 + 0x15a) = 0;
            *(double*)((char*)p1 + 0xf8) = *(double*)((char*)p1 + 0x178) / 100.0;
            *(double*)((char*)p1 + 0x178) = *(float*)(x8 + 0xa4) / 1e+03f * *(double*)((char*)p1 + 0x178);
            if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                *(double*)((char*)p1 + 0x178) = *(float*)(x8 + 0xa4) / 1e+03f * *(double*)((char*)p1 + 0x178);
            }
            (*(short*)((char*)p1 + 0x174))++;
            *(short*)((char*)p1 + 0xf4) = *(short*)((char*)p1 + 0x174);
            *(short*)((char*)p1 + 0x104) = 0xb4;
            *(int*)((char*)p1 + 0x100) = *(int*)((char*)p2 + 0x10c) - *(int*)((char*)p2 + 0x108);
            *(short*)((char*)p1 + 0x148) += *(short*)(x8 + 0xb4);
            *(short*)(k14 + 0x86) = *(short*)(x8 + 0xc2);
            *(short*)((char*)p2 + 0x14a) = *(short*)(x8 + 0xc4);
            (*(short*)(k14 + 0x84))--;
            k168.unk0 = 0;
            k168.type = *(x8 + 0xc0);
            k168.x = (double)((l10c.right + l10c.left) / 2);
            k168.y = (double)((l10c.bottom + l10c.top) / 2);
            k168.side = *((char*)p1 + 0x50) < 0;
            k168.unk20 = 2;
            k168.unk21 = 1;
            k168.unk24 = 0;
            k168.unk2c = *(x8 + 0xc1);
            ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&k168);
            if (*(int*)((char*)p2 + 0x108) <= 0 && *(short*)((char*)p2 + 0x140) == 0) {
                *(short*)((char*)p2 + 8) = *(short*)(x8 + 0xac);
                ((CPlayer*)p2)->Vf0();
                ((CPlayer*)p2)->Unk40e630();
            }
            ((CPlayer*)p1)->Unk410790((int)x8);
        }
    }
}

void CScene3::Unk76b090(int p1, int p2, int p3, int p4)
{
    RECT x10c;
    int xfc;
    int xf8[4][5];
    RECT ea8[5];
    RECT n58[4];
    char* l18;
    int v14;
    char* n10;
    int rc;
    char* x8;
    char* l4;

    n10 = (char*)(p1 + p3 * 0x98 + 0x4d0);
    l18 = (char*)(p2 + p4 * 0x98 + 0x4d0);
    x8 = (char*)(*(int*)(*(char**)((char*)p1 + 0x164) + *(WORD*)n10 * 8 + 4) + *(WORD*)(n10 + 2) * 0xc8);
    l4 = (char*)(*(int*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l18 * 8 + 4) + *(WORD*)(l18 + 2) * 0xc8);
    if (*(int*)(n10 + 0x80) == 0 && *(short*)(n10 + 0x84) > 0 && (*(WORD*)(x8 + 0xaa) & 0x40) == 0) {
        xfc = 0;
        v14 = 0;
        for (; v14 < 4; v14++) {
            n58[v14] = this->Unk767600((int)n10, (int)(x8 + (v14 << 4) + 0x50));
        }
        v14 = 0;
        for (; v14 < 5; v14++) {
            ea8[v14] = this->Unk767600((int)l18, (int)((v14 << 4) + l4));
        }
        v14 = 0;
        for (; v14 < 4; v14++) {
            rc = 0;
            for (; rc < 5; rc++) {
                xf8[v14][rc] = Unk767930((int)&n58[v14], (int)&ea8[rc]);
                xfc |= xf8[v14][rc];
            }
        }
        if (xfc != 0) {
            x10c = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v14 = 0;
            for (; v14 < 4; v14++) {
                rc = 0;
                for (; rc < 5; rc++) {
                    if (xf8[v14][rc] != 0) {
                        if (x10c.left < n58[v14].left) {
                            x10c.left = n58[v14].left;
                        }
                        if (x10c.top < n58[v14].top) {
                            x10c.top = n58[v14].top;
                        }
                        if (x10c.right > n58[v14].right) {
                            x10c.right = n58[v14].right;
                        }
                        if (x10c.bottom > n58[v14].bottom) {
                            x10c.bottom = n58[v14].bottom;
                        }
                        if (x10c.left < ea8[rc].left) {
                            x10c.left = ea8[rc].left;
                        }
                        if (x10c.top < ea8[rc].top) {
                            x10c.top = ea8[rc].top;
                        }
                        if (x10c.right > ea8[rc].right) {
                            x10c.right = ea8[rc].right;
                        }
                        if (x10c.bottom > ea8[rc].bottom) {
                            x10c.bottom = ea8[rc].bottom;
                        }
                    }
                }
            }
            if ((*(WORD*)(l4 + 0xb0) & 0x10) == 0) {
                (*(short*)(n10 + 0x84))--;
                *(int*)(n10 + 0x80) = 5;
            }
            *(int*)(l18 + 0x80) = 5;
            if ((*(WORD*)(l4 + 0xb0) & 0x2000) > 0) {
                *(PatternFrame*)l4 = *(PatternFrame*)(char*)(*(int*)(*(char**)((char*)p2 + 0x164) + *(WORD*)((char*)p2 + 8) * 8 + 4) + *(WORD*)((char*)p2 + 0xa) * 0xc8);
                if ((*(WORD*)(l4 + 0xb0) & 4) == 0 && *(short*)((char*)p2 + 0x138) == 0 || ((*(WORD*)(l4 + 0xb0) & 4) > 0 || *(short*)((char*)p2 + 0x138) > 0) && (*(WORD*)(x8 + 0xaa) & 0x100) > 0 || (*(WORD*)(x8 + 0xaa) & 0x40) > 0) {
                    if (*(double*)((char*)p2 + 0x28) >= 0.0) {
                        if (*(short*)(x8 + 0xae) > 0) {
                            *(short*)((char*)p2 + 8) = *(short*)(x8 + 0xae);
                        } else if ((*(WORD*)(l4 + 0xb0) & 3) == 3) {
                            *(short*)((char*)p2 + 8) = 0x3b;
                        } else if ((*(WORD*)(l4 + 0xb0) & 1) != 0) {
                            *(short*)((char*)p2 + 8) = ((*(WORD*)(x8 + 0xaa) & 8) > 0) * 3 + 0x32 + ((*(WORD*)(x8 + 0xaa) & 0x10) > 0) + ((*(WORD*)(x8 + 0xaa) & 0x20) > 0) * 2;
                        } else if ((*(WORD*)(l4 + 0xb0) & 2) != 0) {
                            *(short*)((char*)p2 + 8) = ((*(WORD*)(x8 + 0xaa) & 0x10) > 0) + 0x38 + ((*(WORD*)(x8 + 0xaa) & 0x20) > 0) * 2;
                        }
                    } else if (*(short*)(x8 + 0xac) > 0) {
                        *(short*)((char*)p2 + 8) = *(short*)(x8 + 0xac);
                    } else {
                        *(short*)((char*)p2 + 8) = 0x3b;
                    }
                    ((CPlayer*)p2)->Vf0();
                    ((CPlayer*)p2)->Unk40e630();
                } else {
                    *(short*)((char*)p1 + 0x174) = 0;
                    ((CPlayer*)p2)->Unk410ac0(0xdf, 2);
                }
                if ((*(WORD*)(l4 + 0xb0) & 0x10) > 0) {
                    *(short*)((char*)p1 + 0x174) = 0;
                    if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                        *(double*)((char*)p1 + 0x178) -= 20.0;
                    } else {
                        *(double*)((char*)p1 + 0x178) = 10000.0;
                    }
                }
                *(double*)((char*)p2 + 0xc0) = *(float*)(x8 + 0xb8);
                *(double*)((char*)p2 + 0xc8) = *(float*)(x8 + 0xbc);
                *(int*)((char*)p2 + 0xd0) = 1;
                if (*(short*)((char*)p1 + 0x174) == 0) {
                    *(int*)((char*)p2 + 0x10c) = *(int*)((char*)p2 + 0x108);
                }
                *(int*)((char*)p2 + 0x108) -= (int)((double)*(short*)(x8 + 0xa0) * ((CPlayer*)p1)->Unk410480() * ((CPlayer*)p2)->Unk410530() * ((CPlayer*)p1)->Unk410560());
                *(short*)((char*)p2 + 0x124) = (int)(*(short*)(x8 + 0xb2) * (*(double*)((char*)p1 + 0x178) / 10000.0 * 0.8));
                *(int*)((char*)p2 + 0x128) = (*(WORD*)(x8 + 0xaa) & 0x400) > 0;
                *(int*)((char*)p2 + 0x12c) = (*(WORD*)(x8 + 0xaa) & 0x800) > 0;
                *((char*)p2 + 0x158) = 0;
                *((char*)p2 + 0x159) = 0;
                *((char*)p2 + 0x15a) = 0;
                *(double*)((char*)p1 + 0xf8) = *(double*)((char*)p1 + 0x178) / 100.0;
                *(double*)((char*)p1 + 0x178) = *(float*)(x8 + 0xa4) / 1e+03f * *(double*)((char*)p1 + 0x178);
                if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                    *(double*)((char*)p1 + 0x178) = *(float*)(x8 + 0xa4) / 1e+03f * *(double*)((char*)p1 + 0x178);
                }
                (*(short*)((char*)p1 + 0x174))++;
                *(short*)((char*)p1 + 0xf4) = *(short*)((char*)p1 + 0x174);
                *(short*)((char*)p1 + 0x104) = 0xb4;
                *(int*)((char*)p1 + 0x100) = *(int*)((char*)p2 + 0x10c) - *(int*)((char*)p2 + 0x108);
                *(short*)((char*)p1 + 0x148) += *(short*)(x8 + 0xb4);
                *(short*)((char*)p1 + 0x14a) = *(short*)(x8 + 0xc2);
                *(short*)((char*)p2 + 0x14a) = *(short*)(x8 + 0xc4);
                if (*(int*)((char*)p2 + 0x108) <= 0 && *(short*)((char*)p2 + 0x140) == 0) {
                    *(short*)((char*)p2 + 8) = *(short*)(x8 + 0xac);
                    ((CPlayer*)p2)->Vf0();
                    ((CPlayer*)p2)->Unk40e630();
                }
                ((CPlayer*)p1)->Unk410790((int)x8);
            }
            EffectDesc v158;
            v158.unk0 = 0;
            v158.type = *(x8 + 0xc0);
            v158.x = (double)((x10c.right + x10c.left) / 2);
            v158.y = (double)((x10c.bottom + x10c.top) / 2);
            v158.side = *((char*)p1 + 0x50) < 0;
            v158.unk20 = 2;
            v158.unk21 = 1;
            v158.unk24 = 0;
            v158.unk2c = *(x8 + 0xc1);
            ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&v158);
        }
    }
}

void CScene3::Unk76bab0(int p1, int p2, int p3, int p4)
{
    RECT v30;
    RECT v20;
    char* l10;
    char* vc;
    int x8;
    int l4;

    vc = (char*)(p1 + p3 * 0x98 + 0x4d0);
    l10 = (char*)(p2 + p4 * 0x98 + 0x4d0);
    x8 = *(int*)(*(char**)((char*)p1 + 0x164) + *(WORD*)vc * 8 + 4) + *(WORD*)(vc + 2) * 0xc8;
    l4 = *(int*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8 + 4) + *(WORD*)(l10 + 2) * 0xc8;
    if (*(int*)(vc + 0x80) == 0 && *(int*)(l10 + 0x80) == 0 && *(short*)(vc + 0x84) > 0 && *(short*)(l10 + 0x84) > 0 && *(short*)(*(char**)((char*)p1 + 0x164) + *(WORD*)vc * 8) > 0 && *(short*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8) > 0) {
        v20 = this->Unk767600((int)vc, x8 + 0x90);
        v30 = this->Unk767600((int)l10, l4 + 0x90);
        if (Unk767930((int)&v20, (int)&v30) != 0) {
            if (*(short*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8) == *(short*)(*(char**)((char*)p1 + 0x164) + *(WORD*)vc * 8)) {
                *(int*)(vc + 0x80) = 4;
                *(int*)(l10 + 0x80) = 4;
            } else if (*(short*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8) > *(short*)(*(char**)((char*)p1 + 0x164) + *(WORD*)vc * 8)) {
                *(int*)(vc + 0x80) = 4;
            } else if (*(short*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8) < *(short*)(*(char**)((char*)p1 + 0x164) + *(WORD*)vc * 8)) {
                *(int*)(l10 + 0x80) = 4;
            }
            if (*(short*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8) > 1) {
                (*(short*)(vc + 0x84))--;
            }
            if (*(short*)(*(char**)((char*)p1 + 0x164) + *(WORD*)vc * 8) > 1) {
                (*(short*)(l10 + 0x84))--;
            }
        }
    }
}

void CScene3::Unk76bd40(int p1, int p2, CollisionInfo* p3, CollisionInfo* p4, int p5)
{
    RECT b1cc;
    int r1bc;
    int k1b8[4][5];
    RECT v168[5];
    PatternFrame n118;
    RECT n50[4];
    char* l10;
    int vc;
    int x8;
    char* l4;

    l10 = (char*)(p2 + p5 * 0x98 + 0x4d0);
    l4 = (char*)p3;
    if (*(int*)((char*)p1 + 0x168) == 0 && *(short*)((char*)p1 + 0x16c) > 0 && (*(WORD*)(l4 + 0xaa) & 0x40) == 0) {
        n118 = *(PatternFrame*)(char*)(*(int*)(*(char**)((char*)p2 + 0x164) + *(WORD*)l10 * 8 + 4) + *(WORD*)(l10 + 2) * 0xc8);
        r1bc = 0;
        vc = 0;
        for (; vc < 4; vc++) {
            n50[vc] = this->Unk7677a0((int)p3, (int)(l4 + (vc << 4) + 0x50));
        }
        vc = 0;
        for (; vc < 5; vc++) {
            v168[vc] = this->Unk767600((int)l10, (int)&n118.boxes[vc]);
        }
        vc = 0;
        for (; vc < 4; vc++) {
            x8 = 0;
            for (; x8 < 5; x8++) {
                k1b8[vc][x8] = Unk767930((int)&n50[vc], (int)&v168[x8]);
                r1bc |= k1b8[vc][x8];
            }
        }
        if (r1bc != 0) {
            b1cc = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            vc = 0;
            for (; vc < 4; vc++) {
                x8 = 0;
                for (; x8 < 5; x8++) {
                    if (k1b8[vc][x8] != 0) {
                        if (b1cc.left < n50[vc].left) {
                            b1cc.left = n50[vc].left;
                        }
                        if (b1cc.top < n50[vc].top) {
                            b1cc.top = n50[vc].top;
                        }
                        if (b1cc.right > n50[vc].right) {
                            b1cc.right = n50[vc].right;
                        }
                        if (b1cc.bottom > n50[vc].bottom) {
                            b1cc.bottom = n50[vc].bottom;
                        }
                        if (b1cc.left < v168[x8].left) {
                            b1cc.left = v168[x8].left;
                        }
                        if (b1cc.top < v168[x8].top) {
                            b1cc.top = v168[x8].top;
                        }
                        if (b1cc.right > v168[x8].right) {
                            b1cc.right = v168[x8].right;
                        }
                        if (b1cc.bottom > v168[x8].bottom) {
                            b1cc.bottom = v168[x8].bottom;
                        }
                    }
                }
            }
            if ((n118.flagsB0 & 0x10) == 0) {
                (*(short*)((char*)p1 + 0x16c))--;
                *(int*)((char*)p1 + 0x168) = 5;
            }
            *(int*)(l10 + 0x80) = 5;
            if ((n118.flagsB0 & 0x2000) > 0) {
                n118 = *(PatternFrame*)(char*)p4;
                if ((n118.flagsB0 & 4) == 0 && *(short*)((char*)p2 + 0x138) == 0 || ((n118.flagsB0 & 4) > 0 || *(short*)((char*)p2 + 0x138) > 0) && (*(WORD*)(l4 + 0xaa) & 0x100) > 0 || (*(WORD*)(l4 + 0xaa) & 0x40) > 0) {
                    if (*(double*)((char*)p2 + 0x28) >= 0.0) {
                        if (*(short*)(l4 + 0xae) > 0) {
                            *(short*)((char*)p2 + 8) = *(short*)(l4 + 0xae);
                        } else if ((n118.flagsB0 & 3) == 3) {
                            *(short*)((char*)p2 + 8) = 0x3b;
                        } else if ((n118.flagsB0 & 1) != 0) {
                            *(short*)((char*)p2 + 8) = ((*(WORD*)(l4 + 0xaa) & 8) > 0) * 3 + 0x32 + ((*(WORD*)(l4 + 0xaa) & 0x10) > 0) + ((*(WORD*)(l4 + 0xaa) & 0x20) > 0) * 2;
                        } else if ((n118.flagsB0 & 2) != 0) {
                            *(short*)((char*)p2 + 8) = ((*(WORD*)(l4 + 0xaa) & 0x10) > 0) + 0x38 + ((*(WORD*)(l4 + 0xaa) & 0x20) > 0) * 2;
                        }
                    } else if (*(short*)(l4 + 0xac) > 0) {
                        *(short*)((char*)p2 + 8) = *(short*)(l4 + 0xac);
                    } else {
                        *(short*)((char*)p2 + 8) = 0x3b;
                    }
                    ((CPlayer*)p2)->Vf0();
                    ((CPlayer*)p2)->Unk40e630();
                } else {
                    *(short*)((char*)p1 + 0x174) = 0;
                    ((CPlayer*)p2)->Unk410ac0(0xdf, 2);
                }
                if ((n118.flagsB0 & 0x10) > 0) {
                    *(short*)((char*)p1 + 0x174) = 0;
                    if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                        *(double*)((char*)p1 + 0x178) -= 20.0;
                    } else {
                        *(double*)((char*)p1 + 0x178) = 10000.0;
                    }
                }
                *(double*)((char*)p2 + 0xc0) = *(float*)(l4 + 0xb8);
                *(double*)((char*)p2 + 0xc8) = *(float*)(l4 + 0xbc);
                *(int*)((char*)p2 + 0xd0) = 1;
                if (*(short*)((char*)p1 + 0x174) == 0) {
                    *(int*)((char*)p2 + 0x10c) = *(int*)((char*)p2 + 0x108);
                }
                *(int*)((char*)p2 + 0x108) -= (int)((double)*(short*)(l4 + 0xa0) * ((CPlayer*)p1)->Unk410480() * ((CPlayer*)p2)->Unk410530() * ((CPlayer*)p1)->Unk410560());
                *(short*)((char*)p2 + 0x124) = (int)(*(short*)(l4 + 0xb2) * (*(double*)((char*)p1 + 0x178) / 10000.0 * 0.8));
                *(int*)((char*)p2 + 0x128) = (*(WORD*)(l4 + 0xaa) & 0x400) > 0;
                *(int*)((char*)p2 + 0x12c) = (*(WORD*)(l4 + 0xaa) & 0x800) > 0;
                *((char*)p2 + 0x158) = 0;
                *((char*)p2 + 0x159) = 0;
                *((char*)p2 + 0x15a) = 0;
                *(double*)((char*)p1 + 0xf8) = *(double*)((char*)p1 + 0x178) / 100.0;
                *(double*)((char*)p1 + 0x178) = *(float*)(l4 + 0xa4) / 1e+03f * *(double*)((char*)p1 + 0x178);
                if (*(double*)((char*)p1 + 0x178) > 10000.0) {
                    *(double*)((char*)p1 + 0x178) = *(float*)(l4 + 0xa4) / 1e+03f * *(double*)((char*)p1 + 0x178);
                }
                (*(short*)((char*)p1 + 0x174))++;
                *(short*)((char*)p1 + 0xf4) = *(short*)((char*)p1 + 0x174);
                *(short*)((char*)p1 + 0x104) = 0xb4;
                *(int*)((char*)p1 + 0x100) = *(int*)((char*)p2 + 0x10c) - *(int*)((char*)p2 + 0x108);
                *(short*)((char*)p1 + 0x148) += *(short*)(l4 + 0xb4);
                *(short*)((char*)p1 + 0x14a) = *(short*)(l4 + 0xc2);
                *(short*)((char*)p2 + 0x14a) = *(short*)(l4 + 0xc4);
                if (*(int*)((char*)p2 + 0x108) <= 0 && *(short*)((char*)p2 + 0x140) == 0) {
                    *(short*)((char*)p2 + 8) = *(short*)(l4 + 0xac);
                    ((CPlayer*)p2)->Vf0();
                    ((CPlayer*)p2)->Unk40e630();
                }
                ((CPlayer*)p1)->Unk410790((int)l4);
            }
            EffectDesc n218;
            n218.unk0 = 0;
            n218.type = *(l4 + 0xc0);
            n218.x = (double)((b1cc.right + b1cc.left) / 2);
            n218.y = (double)((b1cc.bottom + b1cc.top) / 2);
            n218.side = *((char*)p1 + 0x50) < 0;
            n218.unk20 = 2;
            n218.unk21 = 1;
            n218.unk24 = 0;
            n218.unk2c = *(l4 + 0xc1);
            ((CGame*)*(int*)((char*)this + 0x1c))->CreateEffect((EffectDesc*)&n218);
        }
    }
}
