// CScene7 (0x7758b0-0x775d5f), scene 7: the staff roll (system\stfr), one tall image
// scrolled up the screen.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene7::CScene7(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_staffSurface, "system\\stfr.dat", 0, 1);
        m_graphics->LoadPaletteDat(m_palette, "system\\stfr.dat", 0, 1, 254);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_staffSurface, "system\\stfr.bmp", 1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\stfr.bmp", 0, 1, 254);
    }
    m_scroll = 0.0;
    m_skip = 0;
}

CScene7::~CScene7()
{
    if (m_staffSurface != 0) {
        (TOPTR(IUnknown*, m_staffSurface))->Release();
        m_staffSurface = 0;
    }
}

BYTE CScene7::Update()
{
    if (m_scroll == 0.0) {
        m_game->PlayMusic(5);
        Draw();
        CScene::FadeIn(m_palette, 0);
        m_scroll += 0.5;
        return 7;
    }
    if (m_scroll > 2800.0 || m_skip != 0) {
        CScene::FadeOut(m_palette, 0, -500, 200);
        m_game->StopMusic();
        m_scroll = 0.0;
        m_skip = 0;
        return 0;
    }
    m_game->UpdateInput();
    if (m_game->m_pressA[0] != 0 || m_game->m_pressB[0] != 0 || m_game->m_pressC[0] != 0 || m_game->m_pressD[0] != 0) {
        m_skip = 1;
    } else if (m_game->m_pressA[1] != 0 || m_game->m_pressB[1] != 0 || m_game->m_pressC[1] != 0 || m_game->m_pressD[1] != 0) {
        m_skip = 1;
    }
    m_scroll += 0.3;
    Draw();
    return 7;
}

void CScene7::Draw()
{
    if (m_scroll > 2280.0) {
        m_graphics->Blit(MakeRect(0, 0, 320, 240), TOPTR(IDirectDrawSurface*, m_staffSurface), MakeRect(0, 2280, 320, 240), 0, 0);
    } else {
        m_graphics->Blit(MakeRect(0, 0, 320, 240), TOPTR(IDirectDrawSurface*, m_staffSurface), MakeRect(0, (int)m_scroll, 320, 240), 0, 0);
    }
    m_graphics->Flip();
}

void CScene7::HandleKeys()
{
}
