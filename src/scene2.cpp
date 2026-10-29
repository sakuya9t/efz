// CScene2 (0x76c6f0-0x76e47f), scene 2: setting up a match. It picks random characters
// and stages where asked, makes the stage's animated background, loads the stage and
// the "now loading" screen (system\nl), and opens the replay file to record or play.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene2::CScene2(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    unk434 = 0;
}

CScene2::~CScene2()
{
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
}

BYTE CScene2::Update()
{
    int v38;
    char v34[8];
    char v2c[40];

    v38 = rand() % 0xaf;
    if (0) {
        v38 = 0x70;
    }
    m_players[0] = *m_player1Ref;
    m_players[1] = *m_player2Ref;
    strcpy(v2c, "system\\nl\\nl");
    if (v38 < 0x64) {
        strcat(v2c, "0");
    }
    if (v38 < 0xa) {
        strcat(v2c, "0");
    }
    _itoa(v38, v34, 0xa);
    strcat(v2c, (const char*)v34);
    if (1) {
        strcat(v2c, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk434, (const char*)v2c, 0, 1);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, 0, 1, 0xfe);
    } else {
        strcat(v2c, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk434, (const char*)v2c, 1);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, 0, 1, 0xfe);
    }
    Draw();
    CScene::Unk759e20(m_palette, 0);
    Unk76ca50();
    CScene::Unk759c90(m_palette, 0, -0x1f4, 0xc8);
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
    m_game->PlayMusic(m_game->unkf32 + 0xa);
    return 3;
}

void CScene2::Draw()
{
    m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)unk434, MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    m_graphics->Flip();
}

void CScene2::Unk76ca50()
{
    char v38[40];
    int l10;
    char vc[8];

    if (m_game->unk1364 == 6) {
        l10 = 0x16;
        while (l10 == 0x13 || l10 == 0x16) {
            l10 = rand() % 0x18;
            if (m_game->m_extraChars == 0 && (l10 == 0x14 || l10 == 0x15 || l10 == 0x17)) {
                l10 = 0x16;
            }
            if (m_game->m_extraChars == -1 && (l10 == 0xc || l10 == 0xd || l10 == 0xe || l10 == 0xf)) {
                l10 = 0x16;
            }
        }
        Unk76da20(m_player1Ref, m_player2Ref, 0, l10);
        l10 = 0x16;
        while (l10 == 0x13 || l10 == 0x16) {
            l10 = rand() % 0x18;
            if (m_game->m_extraChars == 0 && (l10 == 0x14 || l10 == 0x15 || l10 == 0x17)) {
                l10 = 0x16;
            }
            if (m_game->m_extraChars == -1 && (l10 == 0xc || l10 == 0xd || l10 == 0xe || l10 == 0xf)) {
                l10 = 0x16;
            }
        }
        Unk76da20(m_player2Ref, m_player1Ref, 1, l10);
        (*m_player1Ref)->m_paletteIndex = 0;
        (*m_player2Ref)->m_paletteIndex = (*m_player2Ref)->unk8d == (*m_player1Ref)->unk8d;
        (*m_player1Ref)->m_cpu = 1;
        (*m_player2Ref)->m_cpu = 1;
        l10 = 0x17;
        while (l10 == 0x17) {
            l10 = rand() % 0x17;
            if (m_game->m_extraChars == 0 && l10 >= 0xd && l10 <= 0x10) {
                l10 = 0x17;
            }
            if (m_game->m_extraChars == -1 && l10 >= 0x12 && l10 <= 0x16) {
                l10 = 0x17;
            }
        }
        m_game->unkf32 = l10;
        m_game->unk1338[0] = 0;
        m_game->unk1338[1] = 0;
    } else if (m_game->unk1364 == 5) {
        strcpy(v38, "replay\\data");
        _itoa(m_game->unk14282 + 1, vc, 0xa);
        strcat(v38, (const char*)vc);
        strcat(v38, "-");
        _itoa(m_game->unk14281 + 1, vc, 0xa);
        strcat(v38, (const char*)vc);
        strcat(v38, ".rep");
        if (m_game->m_replayMode == 1) {
            m_game->m_replay.OpenRead((const char*)v38);
            Unk76da20(m_player1Ref, m_player2Ref, 0, m_game->m_replay.Read());
            Unk76da20(m_player2Ref, m_player1Ref, 1, m_game->m_replay.Read());
            m_game->unkf32 = m_game->m_replay.Read();
            if (m_game->unkf32 > 0x64) {
                m_game->unk1340 = m_game->unkf32;
                m_game->unkf32 = m_game->m_replay.Read();
            } else {
                m_game->unk1340 = 0;
            }
            (*m_player1Ref)->m_paletteIndex = m_game->m_replay.Read();
            (*m_player2Ref)->m_paletteIndex = m_game->m_replay.Read();
        } else if (m_game->m_replayMode == 2) {
            m_game->m_replay.OpenWrite((const char*)v38);
            m_game->m_replay.Write((*m_player1Ref)->unk8d);
            m_game->m_replay.Write((*m_player2Ref)->unk8d);
            m_game->m_replay.Write(0x68);
            m_game->m_replay.Write(m_game->unkf32);
            m_game->m_replay.Write((*m_player1Ref)->m_paletteIndex);
            m_game->m_replay.Write((*m_player2Ref)->m_paletteIndex);
        }
    } else if (m_game->unk1364 == 0 && (unsigned char)m_game->unk1378 == 0 || m_game->unk1364 == 2) {
        l10 = 0x16;
        while ((1 << l10 & m_game->unk135c) != 0 || l10 == 0x12 || l10 == 0x13 || l10 == 0x16) {
            l10 = rand() % 0x18;
            if (m_game->m_extraChars == 0 && (l10 == 0x14 || l10 == 0x15 || l10 == 0x17)) {
                l10 = 0x16;
            }
            if (m_game->m_extraChars == -1 && (l10 == 0xc || l10 == 0xd || l10 == 0xe || l10 == 0xf)) {
                l10 = 0x16;
            }
        }
        if (m_game->unk1364 == 0) {
            if (m_game->unk1358 == 8) {
                if ((unsigned char)m_game->unk1379 == 0 || (unsigned char)m_game->unk1379 == 8) {
                    l10 = 0x13;
                } else {
                    l10 = 0x18;
                }
                if (m_game->m_extraChars == 0) {
                    l10 = 0x18;
                }
            }
        } else if (m_game->m_extraChars == 0) {
            if (m_game->unk1358 == 8) {
                l10 = 0x18;
            }
        } else {
            if (m_game->unk1358 == 8) {
                l10 = 0x13;
            }
            if (m_game->unk1358 == 7) {
                l10 = 0x18;
            }
        }
        if (m_game->unk1343[0] == 1) {
            Unk76da20(m_player1Ref, m_player2Ref, 0, l10);
            (*m_player1Ref)->m_paletteIndex = 0;
            if ((*m_player1Ref)->unk8d == (*m_player2Ref)->unk8d && (*m_player2Ref)->m_paletteIndex == 0) {
                (*m_player1Ref)->m_paletteIndex = 1;
            }
        } else {
            Unk76da20(m_player2Ref, m_player1Ref, 1, l10);
            (*m_player2Ref)->m_paletteIndex = 0;
            if ((*m_player2Ref)->unk8d == (*m_player1Ref)->unk8d && (*m_player1Ref)->m_paletteIndex == 0) {
                (*m_player2Ref)->m_paletteIndex = 1;
            }
        }
        switch (l10) {
        case 0:
            m_game->unkf32 = 4;
            break;
        case 1:
            m_game->unkf32 = 7;
            break;
        case 2:
            m_game->unkf32 = 0;
            break;
        case 3:
            m_game->unkf32 = 6;
            break;
        case 4:
            m_game->unkf32 = 0xa;
            break;
        case 5:
            m_game->unkf32 = 0xb;
            break;
        case 6:
            m_game->unkf32 = 3;
            break;
        case 7:
            m_game->unkf32 = 5;
            break;
        case 8:
            m_game->unkf32 = 0x16;
            break;
        case 9:
            m_game->unkf32 = 2;
            break;
        case 0xa:
            m_game->unkf32 = 8;
            break;
        case 0xb:
            m_game->unkf32 = 9;
            break;
        case 0xc:
            m_game->unkf32 = 4;
            break;
        case 0xd:
            m_game->unkf32 = 1;
            break;
        case 0xe:
            m_game->unkf32 = 0x13;
            break;
        case 0xf:
            m_game->unkf32 = 0x14;
            break;
        case 0x10:
            m_game->unkf32 = 0x11;
            break;
        case 0x11:
            m_game->unkf32 = 8;
            break;
        case 0x12:
            m_game->unkf32 = 0xc;
            break;
        case 0x13:
            m_game->unkf32 = 0x10;
            break;
        case 0x14:
            m_game->unkf32 = 0xe;
            break;
        case 0x15:
            m_game->unkf32 = 0xd;
            break;
        case 0x17:
            m_game->unkf32 = 0xf;
            break;
        case 0x18:
            m_game->unkf32 = 0xc;
        }
    }
    _itoa(m_game->unkf32, vc, 0xa);
    if (m_game->unkf32 < 0xa) {
        strcpy(v38, "system\\bg\\bg0");
    } else {
        strcpy(v38, "system\\bg\\bg");
    }
    strcat(v38, (const char*)vc);
    if (1) {
        strcat(v38, ".dat");
        if ((int)m_game->unke98 != 0) {
            m_game->unke98->Release();
            m_game->unke98 = (IDirectDrawSurface*)0;
        }
        m_game->LoadDat(&m_game->unke98, (const char*)v38, 0, 1);
        m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v38, 0, 1, 0x5e);
        _itoa(m_game->unkf32, vc, 0xa);
        if (m_game->unkf32 < 0xa) {
            strcpy(v38, "system\\bg\\bg0");
        } else {
            strcpy(v38, "system\\bg\\bg");
        }
        strcat(v38, (const char*)vc);
        strcat(v38, "b.dat");
        if ((int)m_game->unke9c != 0) {
            m_game->unke9c->Release();
            m_game->unke9c = (IDirectDrawSurface*)0;
        }
        m_game->LoadDat(&m_game->unke9c, (const char*)v38, 0, 0xaf);
    } else {
        strcat(v38, ".bmp");
        if ((int)m_game->unke98 != 0) {
            m_game->unke98->Release();
            m_game->unke98 = (IDirectDrawSurface*)0;
        }
        m_graphics->LoadBmp(&m_game->unke98, (const char*)v38, 1);
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v38, 0, 1, 0x5e);
        _itoa(m_game->unkf32, vc, 0xa);
        if (m_game->unkf32 < 0xa) {
            strcpy(v38, "system\\bg\\bg0");
        } else {
            strcpy(v38, "system\\bg\\bg");
        }
        strcat(v38, (const char*)vc);
        strcat(v38, "b.bmp");
        if ((int)m_game->unke9c != 0) {
            m_game->unke9c->Release();
            m_game->unke9c = (IDirectDrawSurface*)0;
        }
        m_graphics->LoadBmp(&m_game->unke9c, (const char*)v38, 0xaf);
    }
    switch (m_game->unkf32) {
    case 1:
        if (0) {}
        if (0) {}
        m_game->m_background = (CAnimBg*)(int)new CBg01((int)m_graphics);
        break;
    case 0xa:
        m_game->m_background = (CAnimBg*)(int)new CBg10((int)m_graphics);
        break;
    case 0xc:
        m_game->m_background = (CAnimBg*)(int)new CBg12((int)m_graphics);
        break;
    case 0x10:
        m_game->m_background = (CAnimBg*)(int)new CBg16((int)m_graphics);
    }
    if (m_game->unkf32 == 0x10) {
        m_game->unk14258 = 0.125;
    } else {
        m_game->unk14258 = 1.0;
    }
    (*m_player1Ref)->Load();
    (*m_player2Ref)->Load();
    if (m_game->unk1364 == 2) {
        (*m_player1Ref)->unka8 = m_game->unk1358 / 1.5f;
        (*m_player2Ref)->unka8 = m_game->unk1358 / 1.5f;
    } else {
        (*m_player1Ref)->unka8 = m_game->unk1365;
        (*m_player2Ref)->unka8 = m_game->unk1365;
    }
    m_game->Reset();
    m_graphics->BuildBlendTables(m_game->m_palette);
}

void CScene2::Vf2()
{
}

void CScene2::Unk76da20(CPlayer** p1, CPlayer** p2, char p3, char p4)
{
    switch (p4) {
    case 0:
        *p1 = new CNanase(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 1:
        *p1 = new CAyu(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 2:
        *p1 = new CMai(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 3:
        *p1 = new CMakoto(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 4:
        *p1 = new CAkane(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 5:
        *p1 = new CMayu(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 6:
        *p1 = new CNagamori(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 7:
        *p1 = new CMisaki(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 8:
        *p1 = new CShiori(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 9:
        *p1 = new CSayuri(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xa:
        *p1 = new CNayuki(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xb:
        *p1 = new CMio(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xc:
        *p1 = new CEXNanase(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xd:
        *p1 = new CKaori(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xe:
        *p1 = new CIkumi(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xf:
        *p1 = new CMishio(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x10:
        *p1 = new CAkiko(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x11:
        *p1 = new CNayukiB(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x12:
        *p1 = new CMizukaB(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x13:
        *p1 = new CKanna(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x14:
        *p1 = new CKano(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x15:
        *p1 = new CMinagi(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x16:
        *p1 = new CNayuki(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x17:
        *p1 = new CMisuzu(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x18:
        *p1 = new CMizuka(p2, m_game, m_graphics, m_input, m_sound, p3);
    }
    (*p1)->unk8d = p4;
    m_players[p3] = *p1;
    (*p1)->m_cpu = m_game->unk1343[p3];
}
