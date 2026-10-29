// CScene7 (0x7758b0-0x775d5f), scene 7: the staff roll (system\stfr), one tall image
// scrolled up the screen.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene7::CScene7(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((IDirectDrawSurface**)&unk434, "system\\stfr.dat", 0, 1);
        m_graphics->LoadPaletteDat(m_palette, "system\\stfr.dat", 0, 1, 0xfe);
    } else {
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk434, "system\\stfr.bmp", 1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\stfr.bmp", 0, 1, 0xfe);
    }
    unk438 = 0.0;
    unk440 = 0;
}

CScene7::~CScene7()
{
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
}

BYTE CScene7::Update()
{
    if (unk438 == 0.0) {
        m_game->PlayMusic(5);
        Draw();
        CScene::Unk759e20(m_palette, 0);
        unk438 += 0.5;
        return 7;
    }
    if (unk438 > 2800.0 || unk440 != 0) {
        CScene::Unk759c90(m_palette, 0, -0x1f4, 0xc8);
        m_game->StopMusic();
        unk438 = 0.0;
        unk440 = 0;
        return 0;
    }
    m_game->UpdateInput();
    if ((char)m_game->m_pressA[0] != 0 || (char)m_game->m_pressB[0] != 0 || (char)m_game->m_pressC[0] != 0 || (char)m_game->m_pressD[0] != 0) {
        unk440 = 1;
    } else if ((char)m_game->m_pressA[1] != 0 || (char)m_game->m_pressB[1] != 0 || (char)m_game->m_pressC[1] != 0 || (char)m_game->m_pressD[1] != 0) {
        unk440 = 1;
    }
    unk438 += 0.3;
    Draw();
    return 7;
}

void CScene7::Draw()
{
    if (unk438 > 2280.0) {
        m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)unk434, MakeRect(0, 0x8e8, 0x140, 0xf0), 0, 0);
    } else {
        m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)unk434, MakeRect(0, (int)unk438, 0x140, 0xf0), 0, 0);
    }
    m_graphics->Flip();
}

void CScene7::Vf2()
{
}
