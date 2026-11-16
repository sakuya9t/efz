// Last object of the game's code: CScene0 (0x775d60-0x77697d), scene 0, the title screen
// (system\title, title_ob). 0x776820 and 0x7768d0 are never called.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene0::CScene0(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_titleSurface, "system\\title.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\title_ob.dat", 0, 193);
        m_graphics->LoadPaletteDat(m_palette, "system\\title.dat", 0, 1, 192);
        m_graphics->LoadPaletteDat(m_palette, "system\\title_ob.dat", 0, 193, 48);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_titleSurface, "system\\title.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\title_ob.bmp", 193);
        m_graphics->LoadPaletteBmp(m_palette, "system\\title.bmp", 0, 1, 192);
        m_graphics->LoadPaletteBmp(m_palette, "system\\title_ob.bmp", 0, 193, 48);
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

#ifdef EFZ_NATIVE
// The native game's title menu has a row more, NET PLAY after VS HUMAN, when it has
// netplay (efz::NetplayHooks); it is drawn with the menu's own letters and the menu
// moves up a row to make room for it.
static int TitleRows()
{
    return efz::g_netplay.drawTitleItem ? 8 : 7;
}

static int TitleMenuY()
{
    return efz::g_netplay.drawTitleItem ? 116 : 130;
}

// NET PLAY is item 7 (m_cursor keeps the original's item numbers) and the fourth row,
// after VS HUMAN: the row an item is on, and the item on a row.
static const int kNetPlayRow = 3;

static int TitleRow(int item)
{
    if (TitleRows() == 7)
        return item;
    return item == 7 ? kNetPlayRow : item < kNetPlayRow ? item : item + 1;
}

static int TitleItem(int row)
{
    if (TitleRows() == 7)
        return row;
    return row == kNetPlayRow ? 7 : row < kNetPlayRow ? row : row - 1;
}
#define TITLE_MENU_Y TitleMenuY()
#else
#define TITLE_MENU_Y 130
#endif

BYTE CScene0::Update()
{
    int side; // the player whose input is read; becomes m_humanSide

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
#ifdef EFZ_NATIVE
    // EfzRevival makes the demo's branch never taken (efz.exe 0x776053): a network match
    // starts on the title, and must not leave it on its own.
    if (m_idleTime > 1800 && !efz::g_netplay.active) {
#else
    if (m_idleTime > 1800 && 1) {
#endif
        m_idleTime = 0;
        m_game->m_gameMode = 6;
        CScene::FadeOut(m_palette, 1, 0, 0);
        m_enter = 2;
        return 2;
    }
    HandleKeys();
    m_game->UpdateInput();
    side = 0;
    for (; side < 2; side++) {
        if (m_held[side] == 0 && m_game->m_inputY[side] != 0) {
            m_game->PlaySE(8);
#ifdef EFZ_NATIVE
            // Up and down go through the rows in their order, NET PLAY's among them.
            {
                int row = TitleRow(m_cursor) + m_game->m_inputY[side];
                if (row > TitleRows() - 1) {
                    row = 0;
                }
                if (row < 0) {
                    row = TitleRows() - 1;
                }
                m_cursor = TitleItem(row);
            }
#else
            m_cursor += m_game->m_inputY[side];
            if (m_cursor > 6) {
                m_cursor = 0;
            }
            if (m_cursor < 0) {
                m_cursor = 6;
            }
#endif
            unk43e = 0;
            m_held[side] = 1;
        }
        if (m_game->m_inputY[side] == 0) {
            m_held[side] = 0;
            m_idleTime++;
        } else {
            m_idleTime = 0;
        }
        if (m_game->m_pressA[side] == 1) {
            switch (m_cursor) {
            case 0:
                *(char*)&m_game->m_isCpu[0] = side == 1;
                *(char*)&m_game->m_isCpu[1] = side == 0;
                m_game->m_humanSide = side;
                m_game->PlaySE(6);
                m_game->m_gameMode = 0;
                m_game->m_roundsToWin = 2;
                CScene::FadeOut(m_palette, 1, 0, 0);
                m_enter = 2;
                return 1;
            case 1:
                *(char*)&m_game->m_isCpu[0] = side == 1;
                *(char*)&m_game->m_isCpu[1] = side == 0;
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
                *(char*)&m_game->m_isCpu[0] = side == 1;
                *(char*)&m_game->m_isCpu[1] = side == 0;
                m_game->m_humanSide = side;
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
#ifdef EFZ_NATIVE
                break;
            case 7:
                // NET PLAY: netplay's own menu, over the title.
                m_game->PlaySE(6);
                m_held[0] = 1;
                m_held[1] = 1;
                efz::g_netplay.openMenu();
                Draw();
                return 0;
#endif
            }
        }
    }
    Draw();
    return 0;
}

void CScene0::Draw()
{
    m_graphics->Blit(MakeRect(0, 0, 320, 240), TOPTR(IDirectDrawSurface*, m_titleSurface), MakeRect(0, 0, 320, 240), 0, 0);
#ifdef EFZ_NATIVE
    if (TitleRows() == 8) {
        // ARCADE to VS HUMAN, NET PLAY, then PRACTICE to EXIT a row lower.
        m_graphics->Blit(MakeRect(195, TITLE_MENU_Y, 120, kNetPlayRow * 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0, 120, kNetPlayRow * 14), m_colorKey, 0);
        efz::g_netplay.drawTitleItem(m_graphics, TOPTR(IDirectDrawSurface*, m_menuSurface), m_colorKey, m_cursor == 7, 195, TITLE_MENU_Y + kNetPlayRow * 14);
        m_graphics->Blit(MakeRect(195, TITLE_MENU_Y + (kNetPlayRow + 1) * 14, 120, 98 - kNetPlayRow * 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, kNetPlayRow * 14, 120, 98 - kNetPlayRow * 14), m_colorKey, 0);
        if (m_cursor != 7)
            m_graphics->Blit(MakeRect(195, TitleRow(m_cursor) * 14 + TITLE_MENU_Y, 120, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, m_cursor * 14 + 98, 120, 14), m_colorKey, 0);
        m_graphics->Flip();
        return;
    }
#endif
    m_graphics->Blit(MakeRect(195, TITLE_MENU_Y, 120, 98), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0, 120, 98), m_colorKey, 0);
    m_graphics->Blit(MakeRect(195, m_cursor * 14 + TITLE_MENU_Y, 120, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, m_cursor * 14 + 98, 120, 14), m_colorKey, 0);
    m_graphics->Flip();
}

void CScene0::HandleKeys()
{
    int hr;
    char keys[256];

    hr = m_input->m_keyboard->GetDeviceState(0x100, keys);
    if (hr < 0 && hr == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((keys[1] & 0x80) != 0) {
        PostMessageA(m_hwnd, 0x10, 0, 0);
    }
}

void CScene0::DimTitle()
{
    int level;
    int frameStart;
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16

    frameStart = timeGetTime();
    shortFrame = 0;
    m_dimming = 1;
    level = 20;
    for (; level >= 0; level--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xc1, level * 3 + 0x28);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
    m_dimming = 0;
}

void CScene0::UndimTitle()
{
    int level;
    int frameStart;
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16

    frameStart = timeGetTime();
    shortFrame = 0;
    m_dimming = 1;
    level = 0;
    for (; level <= 20; level++) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xc1, level * 3 + 0x28);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
    m_dimming = 0;
}
