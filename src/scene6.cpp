// CScene6 (0x759f30-0x75db6f), scene 6: the config menu (system\config_bg, config_ob,
// score), which writes its settings back with WriteConfigByte.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene6::CScene6(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    unk43c = 0;
    unk444 = 0;
    if (1) {
        m_game->LoadDat((IDirectDrawSurface**)&unk434, "system\\config_bg.dat", 0, 1);
        m_game->LoadDat((IDirectDrawSurface**)&unk438, "system\\config_ob.dat", 0, 0xa1);
        m_game->LoadDat((IDirectDrawSurface**)&unk440, "system\\score.dat", 0, 0xa1);
        m_graphics->LoadPaletteDat(m_palette, "system\\config_bg.dat", 0, 1, 0xa1);
        m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa2, 0x20);
    } else {
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk434, "system\\config_bg.bmp", 1);
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk438, "system\\config_ob.bmp", 0xa1);
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk440, "system\\score.bmp", 0xa1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\config_bg.bmp", 0, 1, 0xa1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
    }
    m_colorKey = m_graphics->GetColorKey((IDirectDrawSurface*)unk438);
    unk741 = m_graphics->GetColorKey((IDirectDrawSurface*)unk440);
    unk448 = 0;
    unk449 = 0;
    unk44a = 0;
    unk44b[0] = 0;
    unk44b[1] = 0;
    unk44b[2] = 0;
    unk2c = 1;
    unk2d = 0;
    unk748 = 0.0;
    unk750 = 0;
    unk754 = 0;
    unk758 = 0;
    strcpy((char*)this + 0x470, "nanase");
    strcpy((char*)this + 0x48e, "ayu");
    strcpy((char*)this + 0x4ac, "mai");
    strcpy((char*)this + 0x4ca, "makoto");
    strcpy((char*)this + 0x4e8, "akane");
    strcpy((char*)this + 0x506, "mayu");
    strcpy((char*)this + 0x524, "nagamori");
    strcpy((char*)this + 0x542, "misaki");
    strcpy((char*)this + 0x560, "shiori");
    strcpy((char*)this + 0x57e, "sayuri");
    strcpy((char*)this + 0x59c, "nayuki");
    strcpy((char*)this + 0x5ba, "mio");
    strcpy((char*)this + 0x5d8, "misuzu");
    strcpy((char*)this + 0x5f6, "minagi");
    strcpy((char*)this + 0x614, "kano");
    strcpy((char*)this + 0x632, "mizukab");
    strcpy((char*)this + 0x650, "EXnanase");
    strcpy((char*)this + 0x66e, "kaori");
    strcpy((char*)this + 0x68c, "ikumi");
    strcpy((char*)this + 0x6aa, "mishio");
    strcpy((char*)this + 0x6c8, "nayukiB");
    strcpy((char*)this + 0x6e6, "akiko");
    strcpy((char*)this + 0x704, "kanna");
}

CScene6::~CScene6()
{
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
    if (unk438 != 0) {
        ((IUnknown*)unk438)->Release();
        unk438 = 0;
    }
    if (unk440 != 0) {
        ((IUnknown*)unk440)->Release();
        unk440 = 0;
    }
    if (unk43c != 0) {
        ((IUnknown*)unk43c)->Release();
        unk43c = 0;
    }
    if (unk444 != 0) {
        ((IUnknown*)unk444)->Release();
        unk444 = 0;
    }
}

BYTE CScene6::Update()
{
    int xc;
    int v8;
    int v4;

    Vf2();
    if (unk2c == 1) {
        unk448 = 0;
        unk449 = 0;
        unk44a = 0;
        unk2c = 0;
        unk44b[2] = 0;
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa1, 0x20);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
        }
        if (m_game->m_extraChars == 0) {
            m_game->PlayMusic(6);
        } else {
            m_game->PlayMusic(7);
        }
        CScene::Unk759e20(m_palette, 1);
    }
    if (unk2d == 1) {
        CScene::Unk759c90(m_palette, 1, 0, 0x64);
        m_game->StopMusic();
        unk2c = 1;
        unk2d = 0;
        unk44b[2] = 0;
        return 0;
    }
    if ((char)unk44b[2] == 0) {
        m_game->UpdateInput();
        v4 = 0;
        for (; v4 < 2; v4++) {
            if (m_game->m_inputY[v4] != 0 && unk44b[v4] == 0) {
                unk448 += m_game->m_inputY[v4];
                if (unk448 > 7) {
                    unk448 = 0;
                }
                if (unk448 < 0) {
                    unk448 = 7;
                }
                m_game->PlaySE(8);
                unk44b[v4] = 1;
            }
            if (m_game->m_inputX[v4] == 0 && m_game->m_inputY[v4] == 0) {
                unk44b[v4] = 0;
            }
            switch (unk448) {
            case 0:
                if (m_game->m_inputX[v4] != 0 && unk44b[v4] == 0) {
                    m_game->unk136c += m_game->m_inputX[v4];
                    if (m_game->unk136c > 1) {
                        m_game->unk136c = 0;
                    }
                    if (m_game->unk136c < 0) {
                        m_game->unk136c = 1;
                    }
                    WriteConfigByte(0x22, m_game->unk136c + 1);
                    m_game->PlaySE(8);
                    unk44b[v4] = 1;
                }
                break;
            case 1:
                if (m_game->m_inputX[v4] != 0 && unk44b[v4] == 0) {
                    *(char*)&m_game->unk1370 += m_game->m_inputX[v4];
                    if ((char)m_game->unk1370 > 3) {
                        m_game->unk1370 = 1;
                    }
                    if ((char)m_game->unk1370 < 1) {
                        m_game->unk1370 = 3;
                    }
                    WriteConfigByte(0x24, (char)m_game->unk1370);
                    m_game->PlaySE(8);
                    unk44b[v4] = 1;
                }
                break;
            case 2:
                if (m_game->m_inputX[v4] != 0 && unk44b[v4] == 0) {
                    m_game->unk1366 += m_game->m_inputX[v4];
                    if (m_game->unk1366 > 1) {
                        m_game->unk1366 = 0;
                    }
                    if (m_game->unk1366 < 0) {
                        m_game->unk1366 = 1;
                    }
                    WriteConfigByte(0x23, m_game->unk1366 + 1);
                    m_game->PlaySE(8);
                    unk44b[v4] = 1;
                }
                break;
            case 3:
                if (m_game->m_inputX[v4] != 0 && unk44b[v4] == 0) {
                    *(char*)&m_game->unk1365 += m_game->m_inputX[v4];
                    if ((char)m_game->unk1365 > 4) {
                        m_game->unk1365 = 1;
                    }
                    if ((char)m_game->unk1365 < 1) {
                        m_game->unk1365 = 4;
                    }
                    WriteConfigByte(0x21, (char)m_game->unk1365);
                    m_game->PlaySE(8);
                    unk44b[v4] = 1;
                }
                break;
            case 4:
                if (m_game->m_inputX[v4] != 0 && unk44b[v4] == 0) {
                    *(char*)&m_game->unk134f += m_game->m_inputX[v4];
                    if ((char)m_game->unk134f > 3) {
                        m_game->unk134f = 1;
                    }
                    if ((char)m_game->unk134f < 1) {
                        m_game->unk134f = 3;
                    }
                    WriteConfigByte(0x26, (char)m_game->unk134f);
                    m_game->PlaySE(8);
                    unk44b[v4] = 1;
                }
                break;
            case 5:
                if ((char)m_game->m_pressA[v4] == 1) {
                    m_game->PlaySE(6);
                    Unk75d660();
                }
                break;
            case 6:
                if ((char)m_game->m_pressA[v4] == 1) {
                    m_game->PlaySE(6);
                    Unk75da30(0);
                    if (1) {
                        m_graphics->LoadPaletteDat(m_palette, "system\\score.dat", 0, 0xa1, 0x20);
                    } else {
                        m_graphics->LoadPaletteBmp(m_palette, "system\\score.bmp", 0, 0xa1, 0x20);
                    }
                    unk44b[2] = 1;
                    Unk75d400();
                    m_graphics->SetPalette(m_palette);
                    Unk75da30(1);
                }
                break;
            case 7:
                if ((char)m_game->m_pressA[v4] == 1) {
                    unk2d = 1;
                }
            }
            if ((char)m_game->m_pressB[v4] == 1) {
                unk2d = 1;
            }
        }
    } else if ((char)unk44b[2] == 1) {
        m_game->UpdateInput();
        v8 = 0;
        for (; v8 < 2; v8++) {
            if (m_game->m_inputX[v8] != 0 && unk44b[v8] == 0) {
                m_game->PlaySE(8);
                unk449 += m_game->m_inputX[v8];
                if (m_game->m_extraChars == 0) {
                    if (unk449 == 0xc) {
                        unk449 = 0xf;
                    }
                    if (unk449 == 0xe) {
                        unk449 = 0xb;
                    }
                }
                if (m_game->m_extraChars == -1) {
                    if (unk449 == 0x10) {
                        unk449 = 0x14;
                    }
                    if (unk449 == 0x13) {
                        unk449 = 0xf;
                    }
                    if (unk449 == 0x16) {
                        if (m_game->m_inputX[v8] > 0) {
                            unk449 = 0;
                        } else {
                            unk449 = 0x14;
                        }
                    }
                }
                if (unk449 > 0x16) {
                    unk449 = 0;
                }
                if (unk449 < 0) {
                    unk449 = 0x16;
                }
                Unk75d580();
                unk44b[v8] = 1;
            }
            if (m_game->m_inputX[v8] == 0 && m_game->m_inputY[v8] == 0) {
                unk44b[v8] = 0;
            }
            if ((char)m_game->m_pressA[v8] != 0 || (char)m_game->m_pressB[v8] != 0) {
                if ((char)m_game->m_pressA[v8] != 0) {
                    m_game->PlaySE(6);
                }
                Unk75da30(0);
                if (1) {
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa1, 0x20);
                } else {
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
                }
                m_graphics->SetPalette(m_palette);
                unk44b[2] = 0;
                Unk75da30(1);
            }
        }
    } else if ((char)unk44b[2] == 2) {
        m_game->UpdateInput();
        xc = 0;
        for (; xc < 2; xc++) {
            if (m_game->m_inputX[xc] != 0 || m_game->m_inputY[xc] != 0) {
                m_game->PlaySE(8);
                unk758 = m_game->m_inputX[xc] + m_game->m_inputY[xc] * 0xa + unk758;
                if (unk758 > 0xae) {
                    unk758 = 0;
                }
                if (unk758 < 0) {
                    unk758 = 0xae;
                }
                Unk75d660();
            }
            if ((char)m_game->m_pressA[xc] != 0 || (char)m_game->m_pressB[xc] != 0) {
                if ((char)m_game->m_pressA[xc] != 0) {
                    m_game->PlaySE(6);
                }
                Unk75d8d0(1);
                if (1) {
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_bg.dat", 0, 1, 0xa0);
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa1, 0x20);
                } else {
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_bg.bmp", 0, 1, 0xa0);
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
                }
                unk44b[2] = 0;
                Unk75d970(0);
            }
        }
    }
    Draw();
    return 6;
}

void CScene6::Draw()
{
    RECT v20;
    RECT v10;

    if ((char)unk44b[2] == 0) {
        v10 = MakeRect(0, 0, 0x140, 0xf0);
        v20 = MakeRect(0, 0, 0x140, 0xf0);
        m_graphics->Blit(v20, (IDirectDrawSurface*)unk434, v10, 0xff, 0);
        m_graphics->Blit(MakeRect(0, 0 - unk754, 0x140, 0x28), (IDirectDrawSurface*)unk438, MakeRect(0, 0, 0x140, 0x28), m_colorKey, 0);
        m_graphics->Blit(MakeRect(0, unk754 + 0x28, 0x140, 0xc8), (IDirectDrawSurface*)unk438, MakeRect(0, 0x28, 0x140, 0xc8), m_colorKey, 0);
        switch (unk448) {
        case 0:
            m_graphics->Blit(MakeRect(0, unk754 + 0x5f, 0x70, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x105, 0x70, 0xe), m_colorKey, 0);
            break;
        case 1:
            m_graphics->Blit(MakeRect(0, unk754 + 0x71, 0x70, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x117, 0x70, 0xe), m_colorKey, 0);
            break;
        case 2:
            m_graphics->Blit(MakeRect(0, unk754 + 0x83, 0x70, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x129, 0x70, 0xe), m_colorKey, 0);
            break;
        case 3:
            m_graphics->Blit(MakeRect(0, unk754 + 0x95, 0x70, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x13b, 0x70, 0xe), m_colorKey, 0);
            break;
        case 4:
            m_graphics->Blit(MakeRect(0, unk754 + 0xa7, 0x70, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x14d, 0x70, 0xe), m_colorKey, 0);
            break;
        case 5:
            m_graphics->Blit(MakeRect(0, unk754 + 0xb9, 0x140, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x15f, 0x140, 0xe), m_colorKey, 0);
            break;
        case 6:
            m_graphics->Blit(MakeRect(0, unk754 + 0xcb, 0x140, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x171, 0x140, 0xe), m_colorKey, 0);
            break;
        case 7:
            m_graphics->Blit(MakeRect(0, unk754 + 0xdd, 0x140, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0, 0x183, 0x140, 0xe), m_colorKey, 0);
        }
        if (m_game->unk136c == 0) {
            m_graphics->Blit(MakeRect(0x70, unk754 + 0x5f, 0x50, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x70, 0x105, 0x50, 0xe), m_colorKey, 0);
        } else if (m_game->unk136c == 1) {
            m_graphics->Blit(MakeRect(0xc0, unk754 + 0x5f, 0x50, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xc0, 0x105, 0x50, 0xe), m_colorKey, 0);
        }
        if ((char)m_game->unk1370 == 1) {
            m_graphics->Blit(MakeRect(0x70, unk754 + 0x71, 0x40, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x70, 0x117, 0x40, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk1370 == 2) {
            m_graphics->Blit(MakeRect(0xb0, unk754 + 0x71, 0x40, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xb0, 0x117, 0x40, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk1370 == 3) {
            m_graphics->Blit(MakeRect(0xf0, unk754 + 0x71, 0x40, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xf0, 0x117, 0x40, 0xe), m_colorKey, 0);
        }
        if (m_game->unk1366 == 0) {
            m_graphics->Blit(MakeRect(0x70, unk754 + 0x83, 0x30, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x70, 0x129, 0x30, 0xe), m_colorKey, 0);
        } else if (m_game->unk1366 == 1) {
            m_graphics->Blit(MakeRect(0xa0, unk754 + 0x83, 0x30, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xa0, 0x129, 0x30, 0xe), m_colorKey, 0);
        }
        if ((char)m_game->unk1365 == 1) {
            m_graphics->Blit(MakeRect(0x80, unk754 + 0x95, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x80, 0x13b, 0x18, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk1365 == 2) {
            m_graphics->Blit(MakeRect(0x98, unk754 + 0x95, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x98, 0x13b, 0x18, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk1365 == 3) {
            m_graphics->Blit(MakeRect(0xb0, unk754 + 0x95, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xb0, 0x13b, 0x18, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk1365 == 4) {
            m_graphics->Blit(MakeRect(0xc8, unk754 + 0x95, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xc8, 0x13b, 0x18, 0xe), m_colorKey, 0);
        }
        if ((char)m_game->unk134f == 1) {
            m_graphics->Blit(MakeRect(0x80, unk754 + 0xa7, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x80, 0x14d, 0x18, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk134f == 2) {
            m_graphics->Blit(MakeRect(0x98, unk754 + 0xa7, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0x98, 0x14d, 0x18, 0xe), m_colorKey, 0);
        } else if ((char)m_game->unk134f == 3) {
            m_graphics->Blit(MakeRect(0xb0, unk754 + 0xa7, 0x18, 0xe), (IDirectDrawSurface*)unk438, MakeRect(0xb0, 0x14d, 0x18, 0xe), m_colorKey, 0);
        }
    } else if ((char)unk44b[2] == 1) {
        v10 = MakeRect(0, 0, 0x140, 0xf0);
        v20 = MakeRect(0, 0, 0x140, 0xf0);
        m_graphics->Blit(v20, (IDirectDrawSurface*)unk434, v10, 0xff, 0);
        m_graphics->Blit(MakeRect(0, 0 - unk754, 0x140, 0x28), (IDirectDrawSurface*)unk440, MakeRect(0, 0, 0x140, 0x28), unk741, 0);
        m_graphics->Blit(MakeRect(0, unk754 + 0x28, 0x140, 0xc8), (IDirectDrawSurface*)unk440, MakeRect(0, 0x28, 0x140, 0xc8), unk741, 0);
        m_graphics->Blit(MakeRect(unk750 + 0x50, unk754, 0x140, 0xf0), (IDirectDrawSurface*)unk43c, MakeRect(0, 0, 0x140, 0xf0), unk740, 0);
        Unk75d260(0xa0, unk754 + 0x8f, unk450);
        Unk75d260(0xa0, unk754 + 0xa1, unk454);
        Unk75d260(0xa0, unk754 + 0xb3, unk458);
        Unk75d260(0xa0, unk754 + 0xc5, unk46c);
        Unk75d260(0xa0, unk754 + 0xd7, unk468);
    } else if ((char)unk44b[2] == 2) {
        m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)unk444, MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    }
    m_graphics->Flip();
}

void CScene6::Unk75d260(int p1, int p2, int p3)
{
    RECT v2c;
    int v1c;
    RECT l18;
    DWORD x8;
    int l4;

    x8 = p3;
    l4 = p1;
    do {
        v1c = x8 % 0xa;
        v2c.top = 0xf0;
        v2c.bottom = 0xfe;
        v2c.left = (v1c << 4) + 2;
        v2c.right = (v1c << 4) + 0xe;
        l18.top = p2;
        l18.bottom = p2 + 0xe;
        l18.right = l4 - 2;
        l18.left = l4 - 0xe;
        m_graphics->Blit(l18, (IDirectDrawSurface*)unk440, v2c, unk741, 0);
        l4 -= 0xa;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene6::Vf2()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        unk2d = 1;
    }
}

void CScene6::Unk75d400()
{
    char v38[52];

    strcpy(v38, "system\\");
    strcat(v38, (const char*)((char*)this + unk449 * 0x1e + 0x470));
    strcat(v38, "\\");
    strcat(v38, (const char*)((char*)this + unk449 * 0x1e + 0x470));
    if (1) {
        strcat(v38, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk43c, (const char*)v38, 0, 0xd6);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v38, 0, 0xd6, 0x28);
    } else {
        strcat(v38, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk43c, (const char*)v38, 0xd6);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v38, 0, 0xd6, 0x28);
    }
    unk740 = m_graphics->GetColorKey((IDirectDrawSurface*)unk43c);
    ((CharRecord*)&unk450)->Load((const char*)((char*)this + unk449 * 0x1e + 0x470));
}

void CScene6::Unk75d580()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x168; xc += 0xa) {
        Draw();
        unk750 = (int)(160.0 - cos(xc / 57.29579143313326) * 160.0);
        if (xc == 0xb4) {
            Unk75d400();
            m_graphics->SetPalette(m_palette);
        }
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    unk750 = 0;
}

void CScene6::Unk75d660()
{
    int v58;
    char v54[20];
    int l40;
    int x3c;
    char v38[52];

    v58 = timeGetTime();
    x3c = 0;
    l40 = 0xa;
    for (; l40 >= 0; l40--) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, l40 * 0xa);
        while ((DWORD)(timeGetTime() - v58) < (BYTE)(0x10 - x3c)) {
        }
        v58 = timeGetTime();
        x3c = x3c == 0;
    }
    strcpy(v38, "system\\nl\\nl");
    if (unk758 < 0x64) {
        strcat(v38, "0");
    }
    if (unk758 < 0xa) {
        strcat(v38, "0");
    }
    _itoa(unk758, v54, 0xa);
    strcat(v38, (const char*)v54);
    if (unk444 != 0) {
        ((IUnknown*)unk444)->Release();
        unk444 = 0;
    }
    if (1) {
        strcat(v38, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk444, (const char*)v38, 0, 1);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v38, 0, 1, 0xfe);
    } else {
        strcat(v38, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk444, (const char*)v38, 1);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v38, 0, 1, 0xfe);
    }
    unk44b[2] = 2;
    l40 = 0;
    for (; l40 <= 0xa; l40++) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, l40 * 0xa);
        while ((DWORD)(timeGetTime() - v58) < (BYTE)(0x10 - x3c)) {
        }
        v58 = timeGetTime();
        x3c = x3c == 0;
    }
}

void CScene6::Unk75d8d0(int p1)
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene6::Unk75d970(BYTE p1)
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        m_graphics->Darken(m_palette, 1, p1, xc << 1);
        m_graphics->Darken(m_palette, p1, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene6::Unk75da30(BYTE p1)
{
    int l10;
    int vc;
    int x8;
    int l4;

    x8 = timeGetTime();
    l4 = 0;
    if (p1 == 0) {
        vc = 0;
        for (; vc <= 0x5a; vc += 5) {
            Draw();
            unk754 = (short)(int)((1.0 - cos(vc / 57.29579143313326)) * 320.0);
            while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
            }
            x8 = timeGetTime();
            l4 = l4 == 0;
        }
        return;
    }
    l10 = 0x5a;
    for (; l10 >= 0; l10 -= 5) {
        Draw();
        unk754 = (short)(int)((1.0 - cos(l10 / 57.29579143313326)) * 320.0);
        while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
        }
        x8 = timeGetTime();
        l4 = l4 == 0;
    }
}
