// CScene2 (0x76c6f0-0x76e47f), scene 2: setting up a match. It picks random characters
// and stages where asked, makes the stage's animated background, loads the stage and
// the "now loading" screen (system\nl), and opens the replay file to record or play.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene2::CScene2(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    m_loadingSurface = 0;
}

CScene2::~CScene2()
{
    if (m_loadingSurface != 0) {
        (TOPTR(IUnknown*, m_loadingSurface))->Release();
        m_loadingSurface = 0;
    }
}

BYTE CScene2::Update()
{
    int picture; // the loading screen shown, system\nl\nlNNN
    char number[8];
    char path[40];

    picture = rand() % 0xaf;
    if (0) {
        picture = 0x70;
    }
    m_players[0] = *m_player1Ref;
    m_players[1] = *m_player2Ref;
    strcpy(path, "system\\nl\\nl");
    if (picture < 0x64) {
        strcat(path, "0");
    }
    if (picture < 0xa) {
        strcat(path, "0");
    }
    _itoa(picture, number, 0xa);
    strcat(path, (const char*)number);
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)path, 0, 1);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 1, 0xfe);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)path, 1);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 1, 0xfe);
    }
    Draw();
    CScene::FadeIn(m_palette, 0);
    SetupMatch();
    CScene::FadeOut(m_palette, 0, -0x1f4, 0xc8);
    if (m_loadingSurface != 0) {
        (TOPTR(IUnknown*, m_loadingSurface))->Release();
        m_loadingSurface = 0;
    }
    m_game->PlayMusic(m_game->m_stage + 0xa);
    return 3;
}

void CScene2::Draw()
{
    m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, m_loadingSurface), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    m_graphics->Flip();
}

void CScene2::SetupMatch()
{
    char path[40];
    int pick; // a random character, and in the demo a random stage
    char number[8];

    if (m_game->m_gameMode == 6) {
        pick = 0x16;
        while (pick == 0x13 || pick == 0x16) {
            pick = rand() % 0x18;
            if (m_game->m_extraChars == 0 && (pick == 0x14 || pick == 0x15 || pick == 0x17)) {
                pick = 0x16;
            }
            if (m_game->m_extraChars == -1 && (pick == 0xc || pick == 0xd || pick == 0xe || pick == 0xf)) {
                pick = 0x16;
            }
        }
        CreateCharacter(m_player1Ref, m_player2Ref, 0, pick);
        pick = 0x16;
        while (pick == 0x13 || pick == 0x16) {
            pick = rand() % 0x18;
            if (m_game->m_extraChars == 0 && (pick == 0x14 || pick == 0x15 || pick == 0x17)) {
                pick = 0x16;
            }
            if (m_game->m_extraChars == -1 && (pick == 0xc || pick == 0xd || pick == 0xe || pick == 0xf)) {
                pick = 0x16;
            }
        }
        CreateCharacter(m_player2Ref, m_player1Ref, 1, pick);
        (*m_player1Ref)->m_paletteIndex = 0;
        (*m_player2Ref)->m_paletteIndex = (*m_player2Ref)->m_charId == (*m_player1Ref)->m_charId;
        (*m_player1Ref)->m_cpu = 1;
        (*m_player2Ref)->m_cpu = 1;
        pick = 0x17;
        while (pick == 0x17) {
            pick = rand() % 0x17;
            if (m_game->m_extraChars == 0 && pick >= 0xd && pick <= 0x10) {
                pick = 0x17;
            }
            if (m_game->m_extraChars == -1 && pick >= 0x12 && pick <= 0x16) {
                pick = 0x17;
            }
        }
        m_game->m_stage = pick;
        m_game->m_editColor[0] = 0;
        m_game->m_editColor[1] = 0;
    } else if (m_game->m_gameMode == 5) {
        strcpy(path, "replay\\data");
        _itoa(m_game->m_replayPage + 1, number, 0xa);
        strcat(path, (const char*)number);
        strcat(path, "-");
        _itoa(m_game->m_replaySlot + 1, number, 0xa);
        strcat(path, (const char*)number);
        strcat(path, ".rep");
        if (m_game->m_replayMode == 1) {
            m_game->m_replay.OpenRead((const char*)path);
            CreateCharacter(m_player1Ref, m_player2Ref, 0, m_game->m_replay.Read());
            CreateCharacter(m_player2Ref, m_player1Ref, 1, m_game->m_replay.Read());
            m_game->m_stage = m_game->m_replay.Read();
            if (m_game->m_stage > 0x64) {
                m_game->m_replayVersion = m_game->m_stage;
                m_game->m_stage = m_game->m_replay.Read();
            } else {
                m_game->m_replayVersion = 0;
            }
            (*m_player1Ref)->m_paletteIndex = m_game->m_replay.Read();
            (*m_player2Ref)->m_paletteIndex = m_game->m_replay.Read();
        } else if (m_game->m_replayMode == 2) {
            m_game->m_replay.OpenWrite((const char*)path);
            m_game->m_replay.Write((*m_player1Ref)->m_charId);
            m_game->m_replay.Write((*m_player2Ref)->m_charId);
            m_game->m_replay.Write(0x68);
            m_game->m_replay.Write(m_game->m_stage);
            m_game->m_replay.Write((*m_player1Ref)->m_paletteIndex);
            m_game->m_replay.Write((*m_player2Ref)->m_paletteIndex);
        }
    } else if (m_game->m_gameMode == 0 && (unsigned char)m_game->m_continued == 0 || m_game->m_gameMode == 2) {
        pick = 0x16;
        while ((1 << pick & m_game->m_beatenChars) != 0 || pick == 0x12 || pick == 0x13 || pick == 0x16) {
            pick = rand() % 0x18;
            if (m_game->m_extraChars == 0 && (pick == 0x14 || pick == 0x15 || pick == 0x17)) {
                pick = 0x16;
            }
            if (m_game->m_extraChars == -1 && (pick == 0xc || pick == 0xd || pick == 0xe || pick == 0xf)) {
                pick = 0x16;
            }
        }
        if (m_game->m_gameMode == 0) {
            if (m_game->m_arcadeMatch == 8) {
                if ((unsigned char)m_game->m_continuedAt == 0 || (unsigned char)m_game->m_continuedAt == 8) {
                    pick = 0x13;
                } else {
                    pick = 0x18;
                }
                if (m_game->m_extraChars == 0) {
                    pick = 0x18;
                }
            }
        } else if (m_game->m_extraChars == 0) {
            if (m_game->m_arcadeMatch == 8) {
                pick = 0x18;
            }
        } else {
            if (m_game->m_arcadeMatch == 8) {
                pick = 0x13;
            }
            if (m_game->m_arcadeMatch == 7) {
                pick = 0x18;
            }
        }
        if (m_game->m_isCpu[0] == 1) {
            CreateCharacter(m_player1Ref, m_player2Ref, 0, pick);
            (*m_player1Ref)->m_paletteIndex = 0;
            if ((*m_player1Ref)->m_charId == (*m_player2Ref)->m_charId && (*m_player2Ref)->m_paletteIndex == 0) {
                (*m_player1Ref)->m_paletteIndex = 1;
            }
        } else {
            CreateCharacter(m_player2Ref, m_player1Ref, 1, pick);
            (*m_player2Ref)->m_paletteIndex = 0;
            if ((*m_player2Ref)->m_charId == (*m_player1Ref)->m_charId && (*m_player1Ref)->m_paletteIndex == 0) {
                (*m_player2Ref)->m_paletteIndex = 1;
            }
        }
        switch (pick) {
        case 0:
            m_game->m_stage = 4;
            break;
        case 1:
            m_game->m_stage = 7;
            break;
        case 2:
            m_game->m_stage = 0;
            break;
        case 3:
            m_game->m_stage = 6;
            break;
        case 4:
            m_game->m_stage = 0xa;
            break;
        case 5:
            m_game->m_stage = 0xb;
            break;
        case 6:
            m_game->m_stage = 3;
            break;
        case 7:
            m_game->m_stage = 5;
            break;
        case 8:
            m_game->m_stage = 0x16;
            break;
        case 9:
            m_game->m_stage = 2;
            break;
        case 0xa:
            m_game->m_stage = 8;
            break;
        case 0xb:
            m_game->m_stage = 9;
            break;
        case 0xc:
            m_game->m_stage = 4;
            break;
        case 0xd:
            m_game->m_stage = 1;
            break;
        case 0xe:
            m_game->m_stage = 0x13;
            break;
        case 0xf:
            m_game->m_stage = 0x14;
            break;
        case 0x10:
            m_game->m_stage = 0x11;
            break;
        case 0x11:
            m_game->m_stage = 8;
            break;
        case 0x12:
            m_game->m_stage = 0xc;
            break;
        case 0x13:
            m_game->m_stage = 0x10;
            break;
        case 0x14:
            m_game->m_stage = 0xe;
            break;
        case 0x15:
            m_game->m_stage = 0xd;
            break;
        case 0x17:
            m_game->m_stage = 0xf;
            break;
        case 0x18:
            m_game->m_stage = 0xc;
        }
    }
    _itoa(m_game->m_stage, number, 0xa);
    if (m_game->m_stage < 0xa) {
        strcpy(path, "system\\bg\\bg0");
    } else {
        strcpy(path, "system\\bg\\bg");
    }
    strcat(path, (const char*)number);
    if (1) {
        strcat(path, ".dat");
        if ((int)m_game->m_stageSurface != 0) {
            m_game->m_stageSurface->Release();
            m_game->m_stageSurface = (IDirectDrawSurface*)0;
        }
        m_game->LoadDat(&m_game->m_stageSurface, (const char*)path, 0, 1);
        m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, 0, 1, 0x5e);
        _itoa(m_game->m_stage, number, 0xa);
        if (m_game->m_stage < 0xa) {
            strcpy(path, "system\\bg\\bg0");
        } else {
            strcpy(path, "system\\bg\\bg");
        }
        strcat(path, (const char*)number);
        strcat(path, "b.dat");
        if ((int)m_game->m_stageNegative != 0) {
            m_game->m_stageNegative->Release();
            m_game->m_stageNegative = (IDirectDrawSurface*)0;
        }
        m_game->LoadDat(&m_game->m_stageNegative, (const char*)path, 0, 0xaf);
    } else {
        strcat(path, ".bmp");
        if ((int)m_game->m_stageSurface != 0) {
            m_game->m_stageSurface->Release();
            m_game->m_stageSurface = (IDirectDrawSurface*)0;
        }
        m_graphics->LoadBmp(&m_game->m_stageSurface, (const char*)path, 1);
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)path, 0, 1, 0x5e);
        _itoa(m_game->m_stage, number, 0xa);
        if (m_game->m_stage < 0xa) {
            strcpy(path, "system\\bg\\bg0");
        } else {
            strcpy(path, "system\\bg\\bg");
        }
        strcat(path, (const char*)number);
        strcat(path, "b.bmp");
        if ((int)m_game->m_stageNegative != 0) {
            m_game->m_stageNegative->Release();
            m_game->m_stageNegative = (IDirectDrawSurface*)0;
        }
        m_graphics->LoadBmp(&m_game->m_stageNegative, (const char*)path, 0xaf);
    }
    switch (m_game->m_stage) {
    case 1:
        if (0) {}
        if (0) {}
        m_game->m_background = new CBg01(m_graphics);
        break;
    case 0xa:
        m_game->m_background = new CBg10(m_graphics);
        break;
    case 0xc:
        m_game->m_background = new CBg12(m_graphics);
        break;
    case 0x10:
        m_game->m_background = new CBg16(m_graphics);
    }
    if (m_game->m_stage == 0x10) {
        m_game->m_bgParallax = 0.125;
    } else {
        m_game->m_bgParallax = 1.0;
    }
    (*m_player1Ref)->Load();
    (*m_player2Ref)->Load();
    if (m_game->m_gameMode == 2) {
        (*m_player1Ref)->m_cpuSkill = m_game->m_arcadeMatch / 1.5f;
        (*m_player2Ref)->m_cpuSkill = m_game->m_arcadeMatch / 1.5f;
    } else {
        (*m_player1Ref)->m_cpuSkill = m_game->m_cpuLevel;
        (*m_player2Ref)->m_cpuSkill = m_game->m_cpuLevel;
    }
    m_game->Reset();
    m_graphics->BuildBlendTables(m_game->m_palette);
}

void CScene2::HandleKeys()
{
}

void CScene2::CreateCharacter(PTR32(CPlayer)* player, PTR32(CPlayer)* opponent, char side, char charId)
{
    switch (charId) {
    case 0:
        *player = new CNanase(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 1:
        *player = new CAyu(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 2:
        *player = new CMai(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 3:
        *player = new CMakoto(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 4:
        *player = new CAkane(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 5:
        *player = new CMayu(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 6:
        *player = new CNagamori(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 7:
        *player = new CMisaki(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 8:
        *player = new CShiori(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 9:
        *player = new CSayuri(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xa:
        *player = new CNayuki(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xb:
        *player = new CMio(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xc:
        *player = new CEXNanase(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xd:
        *player = new CKaori(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xe:
        *player = new CIkumi(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xf:
        *player = new CMishio(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x10:
        *player = new CAkiko(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x11:
        *player = new CNayukiB(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x12:
        *player = new CMizukaB(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x13:
        *player = new CKanna(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x14:
        *player = new CKano(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x15:
        *player = new CMinagi(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x16:
        *player = new CNayuki(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x17:
        *player = new CMisuzu(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x18:
        *player = new CMizuka(opponent, m_game, m_graphics, m_input, m_sound, side);
    }
    (*player)->m_charId = charId;
    m_players[side] = *player;
    (*player)->m_cpu = m_game->m_isCpu[side];
}
