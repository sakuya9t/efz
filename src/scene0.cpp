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
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_titleSurface, "system\\title.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\title_ob.dat", 0, 0xc1);
        m_graphics->LoadPaletteDat(m_palette, "system\\title.dat", 0, 1, 0xc0);
        m_graphics->LoadPaletteDat(m_palette, "system\\title_ob.dat", 0, 0xc1, 0x30);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_titleSurface, "system\\title.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\title_ob.bmp", 0xc1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\title.bmp", 0, 1, 0xc0);
        m_graphics->LoadPaletteBmp(m_palette, "system\\title_ob.bmp", 0, 0xc1, 0x30);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_menuSurface));
    m_cursor = 0;
    unk43e = 0;
    m_held[2] = 0;
    m_held[0] = 0;
    m_held[1] = 0;
    m_enter = 1;
    m_leave = 0;
    m_dimming = 0;
    m_idleTime = 0;
}

CScene0::~CScene0()
{
    if (m_titleSurface != 0) {
        (TOPTR(IUnknown*, m_titleSurface))->Release();
        m_titleSurface = 0;
    }
    if (m_menuSurface != 0) {
        (TOPTR(IUnknown*, m_menuSurface))->Release();
        m_menuSurface = 0;
    }
}

BYTE CScene0::Update()
{
    int v4;

    if (m_enter == 1) {
        m_held[2] = 0;
        m_enter = 0;
        m_graphics->SetPalette(m_palette);
    } else if (m_enter == 2) {
        CScene::FadeIn(m_palette, 1);
        m_enter = 0;
    } else if (m_enter == 3) {
        m_graphics->SetPalette(m_palette);
        CScene::FadeIn(m_palette, 1);
        m_enter = 0;
    }
    if (m_idleTime > 0x708 && 1) {
        m_idleTime = 0;
        m_game->m_gameMode = 6;
        CScene::FadeOut(m_palette, 1, 0, 0);
        m_enter = 2;
        return 2;
    }
    HandleKeys();
    m_game->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        if (m_held[v4] == 0 && m_game->m_inputY[v4] != 0) {
            m_game->PlaySE(8);
            m_cursor += m_game->m_inputY[v4];
            if (m_cursor > 6) {
                m_cursor = 0;
            }
            if (m_cursor < 0) {
                m_cursor = 6;
            }
            unk43e = 0;
            m_held[v4] = 1;
        }
        if (m_game->m_inputY[v4] == 0) {
            m_held[v4] = 0;
            m_idleTime++;
        } else {
            m_idleTime = 0;
        }
        if (m_game->m_pressA[v4] == 1) {
            switch (m_cursor) {
            case 0:
                *(char*)&m_game->m_isCpu[0] = v4 == 1;
                *(char*)&m_game->m_isCpu[1] = v4 == 0;
                m_game->m_humanSide = v4;
                m_game->PlaySE(6);
                m_game->m_gameMode = 0;
                m_game->m_roundsToWin = 2;
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 2;
                return 1;
            case 1:
                *(char*)&m_game->m_isCpu[0] = v4 == 1;
                *(char*)&m_game->m_isCpu[1] = v4 == 0;
                m_game->PlaySE(6);
                m_game->m_gameMode = 3;
                m_game->m_roundsToWin = m_game->m_roundsSetting;
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 2;
                return 1;
            case 2:
                m_game->m_isCpu[0] = 0;
                m_game->m_isCpu[1] = 0;
                m_game->PlaySE(6);
                m_game->m_gameMode = 4;
                m_game->m_roundsToWin = m_game->m_roundsSetting;
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 2;
                return 1;
            case 3:
                *(char*)&m_game->m_isCpu[0] = v4 == 1;
                *(char*)&m_game->m_isCpu[1] = v4 == 0;
                m_game->m_humanSide = v4;
                m_game->PlaySE(6);
                m_game->m_gameMode = 1;
                m_game->m_roundsToWin = 2;
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 2;
                return 1;
            case 4:
                m_game->m_isCpu[0] = 0;
                m_game->m_isCpu[1] = 0;
                m_game->PlaySE(6);
                m_game->m_gameMode = 5;
                m_game->m_roundsToWin = 2;
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 3;
                return 8;
            case 5:
                m_game->PlaySE(6);
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 3;
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
    m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, m_titleSurface), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    m_graphics->Blit(MakeRect(0xc3, 0x82, 0x78, 0x62), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0, 0x78, 0x62), m_colorKey, 0);
    m_graphics->Blit(MakeRect(0xc3, m_cursor * 0xe + 0x82, 0x78, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, m_cursor * 0xe + 0x62, 0x78, 0xe), m_colorKey, 0);
    m_graphics->Flip();
}

void CScene0::HandleKeys()
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

void CScene0::DimTitle()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    m_dimming = 1;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xc1, xc * 3 + 0x28);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    m_dimming = 0;
}

void CScene0::UndimTitle()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    m_dimming = 1;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xc1, xc * 3 + 0x28);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    m_dimming = 0;
}
