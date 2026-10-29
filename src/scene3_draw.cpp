// The drawing helpers CScene3::Draw calls (0x75db70-0x76339f): numbers from digit
// sprites, the gauges and the rest of the fight's overlay. They are a file of their own,
// as in the original: their floating-point constants precede the string section the
// rest of CScene3 (scene3.cpp) starts with.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CScene3::Unk75db70(int p1, int p2, int p3, BYTE p4, BYTE p5, int p6)
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
        v2c.top = unk464[p4].top;
        v2c.bottom = unk464[p4].bottom;
        v2c.left = unk464[p4].right * v1c;
        v2c.right = unk464[p4].right * (v1c + 1);
        l18.top = p2;
        l18.bottom = unk464[p4].bottom - unk464[p4].top + p2;
        l18.right = l4;
        l18.left = l4 - unk464[p4].right;
        if (p6 != 0) {
            m_graphics->BlitEx(l18, m_game->m_objectSurface, v2c, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(l18, m_game->m_objectSurface, v2c, m_game->m_colorKey, 0);
        }
        l4 -= unk464[p4].right + p5;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene3::Unk75dd50()
{
    RECT v30;
    int v20;
    RECT x1c;
    int vc;
    int x8;
    int l4;

    vc = (int)(-unk45c * m_game->unk14258 + (160.0 - 160.0 * m_game->unk14258));
    x8 = (int)((0xf0 - unk460) * m_game->unk14258 + (120.0 - 120.0 * m_game->unk14258));
    l4 = 0;
    v20 = 0;
    if (vc > 0x140) {
        l4 = 0x140 - vc;
        vc = 0x140;
    } else if (vc < 0) {
        l4 = -vc;
        vc = 0;
    }
    if (x8 > 0xf0) {
        v20 = 0xf0 - x8;
        x8 = 0xf0;
    } else if (x8 < 0) {
        v20 = -x8;
        x8 = 0;
    }
    v30 = MakeRect(vc, x8, 0x140, 0xf0);
    x1c = MakeRect(l4, v20, 0x140, 0xf0);
    if (m_players[0]->unk30c4 > 0 && m_players[1]->unk30c4 > 0) {
        if ((char)m_game->unkf33 == 0) {
            m_graphics->FillRect(x1c, m_players[0]->unk30c0);
        } else {
            m_graphics->FillRect(x1c, m_players[1]->unk30c0);
        }
        if (m_players[0]->unk14c == 0 && m_players[1]->unk14c == 0) {
            m_players[0]->unk30c4--;
            m_players[1]->unk30c4--;
        }
        return;
    }
    if (m_players[0]->unk30c4 > 0) {
        m_graphics->FillRect(x1c, m_players[0]->unk30c0);
        if (m_players[0]->unk14c == 0 && m_players[1]->unk14c == 0) {
            m_players[0]->unk30c4--;
        }
        return;
    }
    if (m_players[1]->unk30c4 > 0) {
        m_graphics->FillRect(x1c, m_players[1]->unk30c0);
        if (m_players[0]->unk14c == 0 && m_players[1]->unk14c == 0) {
            m_players[1]->unk30c4--;
        }
        return;
    }
    if (m_game->unk14278 > 0) {
        m_graphics->Blit(x1c, m_game->unke9c, v30, 0, 0);
        if (m_players[0]->unk14c == 0 && m_players[1]->unk14c == 0) {
            m_game->unk14278--;
        }
        return;
    }
    m_graphics->Blit(x1c, m_game->unke98, v30, 0, 0);
    if ((int)m_game->m_background != 0) {
        m_game->m_background->Vf1(unk45c, unk460, 0);
    }
}

void CScene3::Unk75e240()
{
    RECT v24;
    int v14;
    RECT n10;

    if (m_players[0]->unk110 > m_players[0]->m_hp) {
        m_players[0]->unk110 -= 0xc8;
        if (m_players[0]->unk110 < m_players[0]->m_hp) {
            m_players[0]->unk110 = m_players[0]->m_hp;
        }
    }
    if (m_players[0]->unk110 < m_players[0]->m_hp) {
        m_players[0]->unk110 += 0xc8;
        if (m_players[0]->unk110 > m_players[0]->m_hp) {
            m_players[0]->unk110 = m_players[0]->m_hp;
        }
    }
    if (m_players[1]->m_comboHits == 0) {
        m_players[0]->m_comboStartHp -= (m_players[0]->m_comboStartHp > m_players[0]->m_hp) * 0x64;
        if (m_players[0]->m_comboStartHp < m_players[0]->m_hp) {
            m_players[0]->m_comboStartHp = m_players[0]->m_hp;
        }
    }
    if (m_players[1]->unk110 > m_players[1]->m_hp) {
        m_players[1]->unk110 -= 0xc8;
        if (m_players[1]->unk110 < m_players[1]->m_hp) {
            m_players[1]->unk110 = m_players[1]->m_hp;
        }
    }
    if (m_players[1]->unk110 < m_players[1]->m_hp) {
        m_players[1]->unk110 += 0xc8;
        if (m_players[1]->unk110 > m_players[1]->m_hp) {
            m_players[1]->unk110 = m_players[1]->m_hp;
        }
    }
    if (m_players[0]->m_comboHits == 0) {
        m_players[1]->m_comboStartHp -= (m_players[1]->m_comboStartHp > m_players[1]->m_hp) * 0x64;
        if (m_players[1]->m_comboStartHp < m_players[1]->m_hp) {
            m_players[1]->m_comboStartHp = m_players[1]->m_hp;
        }
    }
    if (m_game->unk1420c > 0) {
        return;
    }
    v24 = MakeRect(0, 0, m_players[0]->anims[0x30].frames->width, m_players[0]->anims[0x30].frames->height);
    n10 = MakeRect(0, 0xe, m_players[0]->anims[0x30].frames->width, m_players[0]->anims[0x30].frames->height);
    m_graphics->Blit(n10, m_players[0]->surfaces[m_players[0]->anims[0x30].frames->surface], v24, m_players[0]->colorKey, 0);
    v24 = MakeRect(0, 0, m_players[1]->anims[0x30].frames->width, m_players[1]->anims[0x30].frames->height);
    n10 = MakeRect(0x140 - m_players[1]->anims[0x30].frames->width, 0xe, m_players[1]->anims[0x30].frames->width, m_players[1]->anims[0x30].frames->height);
    m_graphics->Blit(n10, m_players[1]->surfaces[m_players[1]->anims[0x30].frames->surface], v24, m_players[1]->colorKey, 1);
    v24 = MakeRect(0, 0, 0x140, 0x2c);
    n10 = MakeRect(0, 0, 0x140, 0x2c);
    m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    v24 = MakeRect(0, 0, m_players[0]->anims[0x2d].frames->width, m_players[0]->anims[0x2d].frames->height);
    n10 = MakeRect(1, 0x28, m_players[0]->anims[0x2d].frames->width, m_players[0]->anims[0x2d].frames->height);
    m_graphics->Blit(n10, m_players[0]->surfaces[m_players[0]->anims[0x2d].frames->surface], v24, m_players[0]->colorKey, 0);
    v24 = MakeRect(0, 0, m_players[1]->anims[0x2d].frames->width, m_players[1]->anims[0x2d].frames->height);
    n10 = MakeRect(0x13f - m_players[1]->anims[0x2d].frames->width, 0x28, m_players[1]->anims[0x2d].frames->width, m_players[1]->anims[0x2d].frames->height);
    m_graphics->Blit(n10, m_players[1]->surfaces[m_players[1]->anims[0x2d].frames->surface], v24, m_players[1]->colorKey, 0);
    v14 = (int)(m_players[0]->m_comboStartHp * 120.0 / 9999.0);
    if (v14 > 0) {
        v24 = MakeRect(0x78 - v14, 0x5b, v14, 6);
        n10 = MakeRect(0x8a - v14, 0x12, v14, 6);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    v14 = (int)(m_players[0]->unk110 * 120.0 / 9999.0);
    if (v14 >= 0x28) {
        v24 = MakeRect(0x78 - v14, 0x49, v14, 6);
        n10 = MakeRect(0x8a - v14, 0x12, v14, 6);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    } else if (v14 > 0) {
        v24 = MakeRect(0x78 - v14, m_players[0]->unk30f0 % 0x24 / 0x12 * 6 + 0x4f, v14, 6);
        n10 = MakeRect(0x8a - v14, 0x12, v14, 6);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    v14 = (int)(m_players[1]->m_comboStartHp * 120.0 / 9999.0);
    if (v14 > 0) {
        v24 = MakeRect(0x78, 0x5b, v14, 6);
        n10 = MakeRect(0xb6, 0x12, v14, 6);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    v14 = (int)(m_players[1]->unk110 * 120.0 / 9999.0);
    if (v14 >= 0x28) {
        v24 = MakeRect(0x78, 0x49, v14, 6);
        n10 = MakeRect(0xb6, 0x12, v14, 6);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    } else if (v14 > 0) {
        v24 = MakeRect(0x78, m_players[1]->unk30f0 % 0x24 / 0x12 * 6 + 0x4f, v14, 8);
        n10 = MakeRect(0xb6, 0x12, v14, 6);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    v24 = MakeRect(0x53, 0x93, 7, 0xd);
    if (m_game->unk134e >= 1) {
        n10 = MakeRect(0x7b, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
        n10 = MakeRect(0xbe, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_game->unk134e >= 2) {
        n10 = MakeRect(0x83, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
        n10 = MakeRect(0xb6, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_game->unk134e >= 3) {
        n10 = MakeRect(0x8b, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
        n10 = MakeRect(0xae, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    v24 = MakeRect(0x4c, 0x93, 7, 0xd);
    if (m_players[0]->unkac >= 1) {
        n10 = MakeRect(0x7b, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_players[0]->unkac >= 2) {
        n10 = MakeRect(0x83, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_players[0]->unkac >= 3) {
        n10 = MakeRect(0x8b, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_players[1]->unkac >= 1) {
        n10 = MakeRect(0xbe, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_players[1]->unkac >= 2) {
        n10 = MakeRect(0xb6, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (m_players[1]->unkac >= 3) {
        n10 = MakeRect(0xae, 0x21, 7, 0xd);
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    Unk75db70(0xa9, 9, unk43c, 0, 2, 0);
}

void CScene3::Unk760060()
{
    int v2c;
    RECT l28;
    int l18;
    RECT v14;
    int l4;

    if (m_game->unk1420c > 0) {
        return;
    }
    l28 = MakeRect(0, 0x28, 0x140, 0x21);
    v14 = MakeRect(0, 0xce, 0x140, 0x21);
    m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    l18 = m_players[0]->m_gauge * 0x6c / 0xbb8;
    if (m_players[0]->m_gauge < 0x3e8) {
        l28 = MakeRect(0x6c - l18, 0x73, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    } else if (m_players[0]->m_gauge < 0x7d0) {
        l28 = MakeRect(0, 0x94, 0x18, 0x18);
        v14 = MakeRect(6, 0xd1, 0x18, 0x18);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
        l28 = MakeRect(0x6c - l18, 0x77, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    } else if (m_players[0]->m_gauge < 0xbb8) {
        l28 = MakeRect(0x18, 0x94, 0x18, 0x18);
        v14 = MakeRect(6, 0xd1, 0x18, 0x18);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
        l28 = MakeRect(0x6c - l18, 0x7b, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    } else {
        l28 = MakeRect(0x30, 0x94, 0x18, 0x18);
        v14 = MakeRect(6, 0xd1, 0x18, 0x18);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
        l28 = MakeRect(0x6c - l18, m_players[0]->unk30f0 % 0x5a / 0x12 * 4 + 0x7f, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    }
    l18 = m_players[1]->m_gauge * 0x6c / 0xbb8;
    if (m_players[1]->m_gauge < 0x3e8) {
        l28 = MakeRect(0x6c, 0x73, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    } else if (m_players[1]->m_gauge < 0x7d0) {
        l28 = MakeRect(0, 0x94, 0x18, 0x18);
        v14 = MakeRect(0x122, 0xd1, 0x18, 0x18);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
        l28 = MakeRect(0x6c, 0x77, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    } else if (m_players[1]->m_gauge < 0xbb8) {
        l28 = MakeRect(0x18, 0x94, 0x18, 0x18);
        v14 = MakeRect(0x122, 0xd1, 0x18, 0x18);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
        l28 = MakeRect(0x6c, 0x7b, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    } else {
        l28 = MakeRect(0x30, 0x94, 0x18, 0x18);
        v14 = MakeRect(0x122, 0xd1, 0x18, 0x18);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
        l28 = MakeRect(0x6c, m_players[1]->unk30f0 % 0x5a / 0x12 * 4 + 0x7f, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    }
    if (m_players[0]->unk120 == 0) {
        if (m_players[0]->unk118 < 500.0) {
            l18 = (int)(60.0 * m_players[0]->unk118 * 2 / 1000.0);
            l28 = MakeRect(0x3c - l18, 0x66, l18, 2);
        } else {
            l28 = MakeRect(0, 0x66, 0x3c, 2);
            v14 = MakeRect(0x4f, 0xe8, 0x3c, 2);
            m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
            l18 = (int)((m_players[0]->unk118 - 500.0) * 60.0 * 2 / 1000.0);
            l28 = MakeRect(0x3c - l18, 0x64, l18, 2);
        }
    } else {
        l18 = (int)(60.0 * m_players[0]->unk118 / 1000.0);
        l28 = MakeRect(0x3c - l18, m_players[0]->unk30f0 % 0x5a / 0x12 * 2 + 0x68, l18, 2);
    }
    v14 = MakeRect(0x8b - l18, 0xe8, l18, 2);
    m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    if (m_players[1]->unk120 == 0) {
        if (m_players[1]->unk118 < 500.0) {
            l18 = (int)(60.0 * m_players[1]->unk118 * 2 / 1000.0);
            l28 = MakeRect(0x3c, 0x66, l18, 2);
        } else {
            l28 = MakeRect(0x3c, 0x66, 0x3c, 2);
            v14 = MakeRect(0xb5, 0xe8, 0x3c, 2);
            m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
            l18 = (int)((m_players[1]->unk118 - 500.0) * 60.0 * 2 / 1000.0);
            l28 = MakeRect(0x3c, 0x64, l18, 2);
        }
    } else {
        l18 = (int)(60.0 * m_players[1]->unk118 / 1000.0);
        l28 = MakeRect(0x3c, m_players[1]->unk30f0 % 0x5a / 0x12 * 2 + 0x68, l18, 2);
    }
    v14 = MakeRect(0xb5, 0xe8, l18, 2);
    m_graphics->Blit(v14, m_game->m_objectSurface, l28, m_game->m_colorKey, 0);
    if (m_game->unk1354 == 0) {
        v2c = 0;
        for (; v2c < 2; v2c++) {
            if (m_players[v2c]->unk124 > 0 && m_players[v2c]->unk128 == 0 && m_players[v2c]->y < 0.0 && m_players[v2c]->pattern >= 0x32 && m_players[v2c]->pattern < 0x96 && (m_players[v2c]->m_patterns[m_players[v2c]->pattern].frames[m_players[v2c]->frame].flagsAA & 0x400) == 0) {
                if (m_players[v2c]->facing == 1) {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)m_players[v2c]->x + unk45c + l4;
                        v14.top = unk460 + 0xd2 + (int)m_players[v2c]->y - (m_players[v2c]->y < 0.0) + l4;
                        v14.right = m_players[v2c]->unk124 * (m_players[v2c]->unk124 < 0x64) + v14.left + (m_players[v2c]->unk124 >= 0x64) * 0x64;
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xd3 - (m_players[v2c]->unk124 > 0x1e) * 3 - (m_players[v2c]->unk124 > 0x3c) * 7);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xc2);
                    }
                } else {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)m_players[v2c]->x + unk45c - (m_players[v2c]->unk124 * (m_players[v2c]->unk124 < 0x64) + (m_players[v2c]->unk124 >= 0x64) * 0x64) - l4;
                        v14.top = unk460 + 0xd2 + (int)m_players[v2c]->y - (m_players[v2c]->y < 0.0) + l4;
                        v14.right = m_players[v2c]->unk124 * (m_players[v2c]->unk124 < 0x64) + v14.left + (m_players[v2c]->unk124 >= 0x64) * 0x64;
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xd3 - (m_players[v2c]->unk124 > 0x1e) * 3 - (m_players[v2c]->unk124 > 0x3c) * 7);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xc2);
                    }
                }
            }
            if (m_players[v2c]->unk134 != 0.0f && m_players[v2c]->Unk410340() != 0) {
                if (m_players[v2c]->facing == 1) {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)m_players[v2c]->x + unk45c + l4;
                        v14.top = unk460 + 0xd2 + (int)m_players[v2c]->y - (m_players[v2c]->y < 0.0) + l4;
                        v14.right = (int)(v14.left + m_players[v2c]->unk134 * 1e+02f / 3.6e+02f);
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xdc);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xc2);
                    }
                } else {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)((int)m_players[v2c]->x + unk45c - m_players[v2c]->unk134 * 1e+02f / 3.6e+02f - l4);
                        v14.top = unk460 + 0xd2 + (int)m_players[v2c]->y - (m_players[v2c]->y < 0.0) + l4;
                        v14.right = (int)(v14.left + m_players[v2c]->unk134 * 1e+02f / 3.6e+02f);
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xdc);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        m_graphics->FillRect(v14, 0xc2);
                    }
                }
            }
        }
    }
}

void CScene3::Unk7623b0(CPlayer* p1)
{
    RECT v24;
    int v14;
    RECT n10;

    v14 = p1->m_shownHits;
    if (v14 > 0x63) {
        v14 = 0x63;
    }
    if (p1->m_side > 0) {
        v24 = MakeRect(0, 0xac, 0x3d, 0x26);
        n10 = MakeRect(0x102, 0x3f, 0x3d, 0x26);
        if (p1->m_comboTimer <= 6) {
            m_graphics->BlitEx(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
        }
        if (v14 > 9) {
            Unk75db70(0x11e, 0x3b, v14, 1, 0, p1->m_comboTimer <= 6);
        } else {
            Unk75db70(0x11e, 0x3b, v14, 1, 0, p1->m_comboTimer <= 6);
        }
        Unk75db70(0x11d, 0x52, p1->m_comboDamage, 2, 0, p1->m_comboTimer <= 6);
        Unk75db70(0x113, 0x5c, (int)p1->m_shownProration, 2, 0, p1->m_comboTimer <= 6);
        Unk75db70(0x11d, 0x5c, (int)(p1->m_shownProration * 10.0) % 0xa, 2, 0, p1->m_comboTimer <= 6);
        v24 = MakeRect(0x46, 0xe1, 3, 9);
        n10 = MakeRect(0x113, 0x5c, 3, 9);
        if (p1->m_comboTimer <= 6) {
            m_graphics->BlitEx(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
        }
        return;
    }
    v24 = MakeRect(0, 0xac, 0x3d, 0x26);
    n10 = MakeRect(6, 0x3f, 0x3d, 0x26);
    if (p1->m_comboTimer <= 6) {
        m_graphics->BlitEx(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0, 0);
    } else {
        m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
    }
    if (v14 > 9) {
        Unk75db70(0x22, 0x3b, v14, 1, 0, p1->m_comboTimer <= 6);
    } else {
        Unk75db70(0x22, 0x3b, v14, 1, 0, p1->m_comboTimer <= 6);
    }
    Unk75db70(0x21, 0x52, p1->m_comboDamage, 2, 0, p1->m_comboTimer <= 6);
    Unk75db70(0x17, 0x5c, (int)p1->m_shownProration, 2, 0, p1->m_comboTimer <= 6);
    Unk75db70(0x21, 0x5c, (int)(p1->m_shownProration * 10.0) % 0xa, 2, 0, p1->m_comboTimer <= 6);
    v24 = MakeRect(0x46, 0xe1, 3, 9);
    n10 = MakeRect(0x17, 0x5c, 3, 9);
    if (p1->m_comboTimer <= 6) {
        m_graphics->BlitEx(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0, 0);
        return;
    }
    m_graphics->Blit(n10, m_game->m_objectSurface, v24, m_game->m_colorKey, 0);
}

void CScene3::Unk762c50()
{
    int v34;
    RECT v30;
    int v20;
    char* v1c;
    int l18;
    RECT v14;
    int l4;

    l18 = 0;
    for (; l18 < 2; l18++) {
        if (m_players[l18]->unk60 != 0) {
            v1c = (char*)&m_players[l18]->anims[m_players[l18]->pattern].frames[m_players[l18]->frame].duration;
            if (*(short*)(v1c + 6) < *(short*)(v1c + 0xa)) {
                v20 = *(short*)(v1c + 6);
                l4 = 0;
            } else {
                v20 = *(short*)(v1c + 0xa);
                l4 = *(short*)(v1c + 6) - *(short*)(v1c + 0xa);
            }
            v30.left = 0;
            v30.top = 0;
            v30.right = *(short*)(v1c + 8);
            v30.bottom = v20;
            v14.left = (int)m_players[l18]->x + unk45c - *(short*)(v1c + 4) * (m_players[l18]->facing == 1) - (*(short*)(v1c + 8) - *(short*)(v1c + 4)) * (m_players[l18]->facing == -1);
            v14.top = 0xd2 - ((int)m_players[l18]->y - (m_players[l18]->y < 0.0)) + unk460 + l4;
            v14.right = *(short*)(v1c + 8) + v14.left;
            v14.bottom = v20 / 3 + v14.top;
            if (v14.top < 0xf0 && v14.bottom > 0) {
                m_graphics->BlitShadow(v14, m_players[l18]->surfaces[*(WORD*)(v1c + 2)], v30, m_players[l18]->colorKey, m_players[l18]->facing == -1, 0xb0);
            }
        }
        v34 = m_players[l18]->m_objectTail;
        while (v34 != m_players[l18]->m_objectHead) {
            if (m_players[l18]->m_objectActive[v34] != 0 && m_players[l18]->m_objects[v34].unk58 != 0 && (m_players[l18]->m_objects[v34].unk8c != 0 || m_game->unk1420e == 0)) {
                v1c = (char*)&m_players[l18]->anims[m_players[l18]->m_objects[v34].pattern].frames[m_players[l18]->m_objects[v34].frame].duration;
                if (*(short*)(v1c + 6) < *(short*)(v1c + 0xa)) {
                    v20 = *(short*)(v1c + 6);
                    l4 = 0;
                } else {
                    v20 = *(short*)(v1c + 0xa);
                    l4 = *(short*)(v1c + 6) - *(short*)(v1c + 0xa);
                }
                v30.left = 0;
                v30.top = 0;
                v30.right = *(short*)(v1c + 8);
                v30.bottom = v20;
                if (m_players[l18]->m_objects[v34].facing == -1) {
                    v14.left = (int)m_players[l18]->m_objects[v34].x + unk45c - (*(short*)(v1c + 8) - *(short*)(v1c + 4));
                    v14.top = unk460 + 0xd2 - (int)m_players[l18]->m_objects[v34].y + l4;
                    v14.right = *(short*)(v1c + 8) + v14.left;
                    v14.bottom = v20 / 3 + v14.top;
                } else {
                    v14.left = (int)m_players[l18]->m_objects[v34].x + unk45c - *(short*)(v1c + 4);
                    v14.top = unk460 + 0xd2 - (int)m_players[l18]->m_objects[v34].y + l4;
                    v14.right = *(short*)(v1c + 8) + v14.left;
                    v14.bottom = v20 / 3 + v14.top;
                }
                if (v14.top < 0xf0 && v14.bottom > 0) {
                    m_graphics->BlitShadow(v14, m_players[l18]->surfaces[*(WORD*)(v1c + 2)], v30, m_players[l18]->colorKey, m_players[l18]->m_objects[v34].facing == -1, 0xb0);
                }
            }
            v34++;
            if (v34 >= 0x40) {
                v34 = 0;
            }
        }
    }
}

void CScene3::Unk7631f0()
{
    int l10;
    int vc;
    int x8;
    int l4;

    vc = -unk45c;
    x8 = 0xf0 - unk460;
    l4 = 0;
    l10 = 0;
    if (vc > 0x140) {
        l4 = 0x140 - vc;
        vc = 0x140;
    } else if (vc < 0) {
        l4 = -vc;
        vc = 0;
    }
    if (x8 > 0xf0) {
        l10 = 0xf0 - x8;
        x8 = 0xf0;
    } else if (x8 < 0) {
        l10 = -x8;
        x8 = 0;
    }
    m_graphics->FillRect(MakeRect(0, (l10 + 0xf0) * (l10 < 0), 0x140, abs(l10)), 0);
    m_graphics->FillRect(MakeRect((l4 + 0x140) * (l4 < 0), (l10 >= 0) * l10, abs(l4), 0xf0 - abs(l10)), 0);
    m_graphics->Flip();
}
