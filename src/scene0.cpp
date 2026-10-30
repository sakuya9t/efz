// Last object of the game's code: CScene0 (0x775d60-0x77697d), scene 0, the title screen
// (system\title, title_ob). 0x776820 and 0x7768d0 are never called.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene0::CScene0(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&unk434, "system\\title.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&unk438, "system\\title_ob.dat", 0, 0xc1);
        m_graphics->LoadPaletteDat(m_palette, "system\\title.dat", 0, 1, 0xc0);
        m_graphics->LoadPaletteDat(m_palette, "system\\title_ob.dat", 0, 0xc1, 0x30);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&unk434, "system\\title.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&unk438, "system\\title_ob.bmp", 0xc1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\title.bmp", 0, 1, 0xc0);
        m_graphics->LoadPaletteBmp(m_palette, "system\\title_ob.bmp", 0, 0xc1, 0x30);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, unk438));
    unk43c = 0;
    unk43e = 0;
    unk440[2] = 0;
    unk440[0] = 0;
    unk440[1] = 0;
    unk2c = 1;
    unk2d = 0;
    unk448 = 0;
    unk444 = 0;
}

CScene0::~CScene0()
{
    if (unk434 != 0) {
        (TOPTR(IUnknown*, unk434))->Release();
        unk434 = 0;
    }
    if (unk438 != 0) {
        (TOPTR(IUnknown*, unk438))->Release();
        unk438 = 0;
    }
}

BYTE CScene0::Update()
{
    int v4;

    if (unk2c == 1) {
        unk440[2] = 0;
        unk2c = 0;
        m_graphics->SetPalette(m_palette);
    } else if (unk2c == 2) {
        CScene::Unk759e20(m_palette, 1);
        unk2c = 0;
    } else if (unk2c == 3) {
        m_graphics->SetPalette(m_palette);
        CScene::Unk759e20(m_palette, 1);
        unk2c = 0;
    }
    if (unk444 > 0x708 && 1) {
        unk444 = 0;
        m_game->unk1364 = 6;
        CScene::Unk759c90(m_palette, 1, 0, 0);
        unk2c = 2;
        return 2;
    }
    Vf2();
    m_game->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        if (unk440[v4] == 0 && m_game->m_inputY[v4] != 0) {
            m_game->PlaySE(8);
            unk43c += m_game->m_inputY[v4];
            if (unk43c > 6) {
                unk43c = 0;
            }
            if (unk43c < 0) {
                unk43c = 6;
            }
            unk43e = 0;
            unk440[v4] = 1;
        }
        if (m_game->m_inputY[v4] == 0) {
            unk440[v4] = 0;
            unk444++;
        } else {
            unk444 = 0;
        }
        if (m_game->m_pressA[v4] == 1) {
            switch (unk43c) {
            case 0:
                *(char*)&m_game->unk1343[0] = v4 == 1;
                *(char*)&m_game->unk1343[1] = v4 == 0;
                m_game->unk1342 = v4;
                m_game->PlaySE(6);
                m_game->unk1364 = 0;
                m_game->unk134e = 2;
                CScene::Unk759c90(m_palette, 1, 0, 0);
                unk2c = 2;
                return 1;
            case 1:
                *(char*)&m_game->unk1343[0] = v4 == 1;
                *(char*)&m_game->unk1343[1] = v4 == 0;
                m_game->PlaySE(6);
                m_game->unk1364 = 3;
                m_game->unk134e = m_game->unk134f;
                CScene::Unk759c90(m_palette, 1, 0, 0);
                unk2c = 2;
                return 1;
            case 2:
                m_game->unk1343[0] = 0;
                m_game->unk1343[1] = 0;
                m_game->PlaySE(6);
                m_game->unk1364 = 4;
                m_game->unk134e = m_game->unk134f;
                CScene::Unk759c90(m_palette, 1, 0, 0);
                unk2c = 2;
                return 1;
            case 3:
                *(char*)&m_game->unk1343[0] = v4 == 1;
                *(char*)&m_game->unk1343[1] = v4 == 0;
                m_game->unk1342 = v4;
                m_game->PlaySE(6);
                m_game->unk1364 = 1;
                m_game->unk134e = 2;
                CScene::Unk759c90(m_palette, 1, 0, 0);
                unk2c = 2;
                return 1;
            case 4:
                m_game->unk1343[0] = 0;
                m_game->unk1343[1] = 0;
                m_game->PlaySE(6);
                m_game->unk1364 = 5;
                m_game->unk134e = 2;
                CScene::Unk759c90(m_palette, 1, 0, 0);
                unk2c = 3;
                return 8;
            case 5:
                m_game->PlaySE(6);
                CScene::Unk759c90(m_palette, 1, 0, 0);
                unk2c = 3;
                return 6;
            case 6:
                PostMessageA(m_hwnd, 0x10, 0, 0);
            }
        }
    }
    Draw();
    return 0;
}

void CScene0::Draw()
{
    m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, unk434), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    m_graphics->Blit(MakeRect(0xc3, 0x82, 0x78, 0x62), TOPTR(IDirectDrawSurface*, unk438), MakeRect(0, 0, 0x78, 0x62), m_colorKey, 0);
    m_graphics->Blit(MakeRect(0xc3, unk43c * 0xe + 0x82, 0x78, 0xe), TOPTR(IDirectDrawSurface*, unk438), MakeRect(0, unk43c * 0xe + 0x62, 0x78, 0xe), m_colorKey, 0);
    m_graphics->Flip();
}

void CScene0::Vf2()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        PostMessageA(m_hwnd, 0x10, 0, 0);
    }
}

void CScene0::Unk776820()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    unk448 = 1;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xc1, xc * 3 + 0x28);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    unk448 = 0;
}

void CScene0::Unk7768d0()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    unk448 = 1;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xc1, xc * 3 + 0x28);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    unk448 = 0;
}
