// The drawing helpers CScene3::Draw calls (0x75db70-0x76339f): numbers from digit
// sprites, the gauges and the rest of the fight's overlay. They are a file of their own,
// as in the original: their floating-point constants precede the string section the
// rest of CScene3 (scene3.cpp) starts with.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CScene3::DrawNumber(int right, int top, int value, BYTE font, BYTE gap, int blend)
{
    RECT src;
    int digit;
    RECT dst;
    DWORD rest; // the digits not drawn yet
    int x; // the next digit's right edge

    rest = value;
    x = right;
    do {
        digit = rest % 0xa;
        src.top = m_digitFonts[font].top;
        src.bottom = m_digitFonts[font].bottom;
        src.left = m_digitFonts[font].right * digit;
        src.right = m_digitFonts[font].right * (digit + 1);
        dst.top = top;
        dst.bottom = m_digitFonts[font].bottom - m_digitFonts[font].top + top;
        dst.right = x;
        dst.left = x - m_digitFonts[font].right;
        if (blend != 0) {
            m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        }
        x -= m_digitFonts[font].right + gap;
        rest = rest / 0xa;
    } while (rest > 0);
}

void CScene3::DrawBackground()
{
    RECT src;
    int dstY; // where the stage's top edge lands on the screen
    RECT dst;
    int srcX;
    int srcY;
    int dstX; // where the stage's left edge lands on the screen

    srcX = (int)(-m_drawX * m_game->m_bgParallax + (160.0 - 160.0 * m_game->m_bgParallax));
    srcY = (int)((0xf0 - m_drawY) * m_game->m_bgParallax + (120.0 - 120.0 * m_game->m_bgParallax));
    dstX = 0;
    dstY = 0;
    if (srcX > 0x140) {
        dstX = 0x140 - srcX;
        srcX = 0x140;
    } else if (srcX < 0) {
        dstX = -srcX;
        srcX = 0;
    }
    if (srcY > 0xf0) {
        dstY = 0xf0 - srcY;
        srcY = 0xf0;
    } else if (srcY < 0) {
        dstY = -srcY;
        srcY = 0;
    }
    src = MakeRect(srcX, srcY, 0x140, 0xf0);
    dst = MakeRect(dstX, dstY, 0x140, 0xf0);
    if (m_players[0]->m_fillTime > 0 && m_players[1]->m_fillTime > 0) {
        if ((char)m_game->m_fillSide == 0) {
            m_graphics->FillRect(dst, m_players[0]->m_fillColor);
        } else {
            m_graphics->FillRect(dst, m_players[1]->m_fillColor);
        }
        if (m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_players[0]->m_fillTime--;
            m_players[1]->m_fillTime--;
        }
        return;
    }
    if (m_players[0]->m_fillTime > 0) {
        m_graphics->FillRect(dst, m_players[0]->m_fillColor);
        if (m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_players[0]->m_fillTime--;
        }
        return;
    }
    if (m_players[1]->m_fillTime > 0) {
        m_graphics->FillRect(dst, m_players[1]->m_fillColor);
        if (m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_players[1]->m_fillTime--;
        }
        return;
    }
    if (m_game->m_negativeTime > 0) {
        m_graphics->Blit(dst, m_game->m_stageNegative, src, 0, 0);
        if (m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_game->m_negativeTime--;
        }
        return;
    }
    m_graphics->Blit(dst, m_game->m_stageSurface, src, 0, 0);
    if ((int)m_game->m_background != 0) {
        m_game->m_background->Draw(m_drawX, m_drawY, 0);
    }
}

void CScene3::DrawLifeBars()
{
    RECT src;
    int length; // the bar's length in pixels, 120 at 9999
    RECT dst;

    if (m_players[0]->m_shownHp > m_players[0]->m_hp) {
        m_players[0]->m_shownHp -= 0xc8;
        if (m_players[0]->m_shownHp < m_players[0]->m_hp) {
            m_players[0]->m_shownHp = m_players[0]->m_hp;
        }
    }
    if (m_players[0]->m_shownHp < m_players[0]->m_hp) {
        m_players[0]->m_shownHp += 0xc8;
        if (m_players[0]->m_shownHp > m_players[0]->m_hp) {
            m_players[0]->m_shownHp = m_players[0]->m_hp;
        }
    }
    if (m_players[1]->m_comboHits == 0) {
        m_players[0]->m_comboStartHp -= (m_players[0]->m_comboStartHp > m_players[0]->m_hp) * 0x64;
        if (m_players[0]->m_comboStartHp < m_players[0]->m_hp) {
            m_players[0]->m_comboStartHp = m_players[0]->m_hp;
        }
    }
    if (m_players[1]->m_shownHp > m_players[1]->m_hp) {
        m_players[1]->m_shownHp -= 0xc8;
        if (m_players[1]->m_shownHp < m_players[1]->m_hp) {
            m_players[1]->m_shownHp = m_players[1]->m_hp;
        }
    }
    if (m_players[1]->m_shownHp < m_players[1]->m_hp) {
        m_players[1]->m_shownHp += 0xc8;
        if (m_players[1]->m_shownHp > m_players[1]->m_hp) {
            m_players[1]->m_shownHp = m_players[1]->m_hp;
        }
    }
    if (m_players[0]->m_comboHits == 0) {
        m_players[1]->m_comboStartHp -= (m_players[1]->m_comboStartHp > m_players[1]->m_hp) * 0x64;
        if (m_players[1]->m_comboStartHp < m_players[1]->m_hp) {
            m_players[1]->m_comboStartHp = m_players[1]->m_hp;
        }
    }
    if (m_game->m_hideHudTime > 0) {
        return;
    }
    src = MakeRect(0, 0, m_players[0]->anims[kHudPortrait].frames->width, m_players[0]->anims[kHudPortrait].frames->height);
    dst = MakeRect(0, 0xe, m_players[0]->anims[kHudPortrait].frames->width, m_players[0]->anims[kHudPortrait].frames->height);
    m_graphics->Blit(dst, m_players[0]->surfaces[m_players[0]->anims[kHudPortrait].frames->surface], src, m_players[0]->colorKey, 0);
    src = MakeRect(0, 0, m_players[1]->anims[kHudPortrait].frames->width, m_players[1]->anims[kHudPortrait].frames->height);
    dst = MakeRect(0x140 - m_players[1]->anims[kHudPortrait].frames->width, 0xe, m_players[1]->anims[kHudPortrait].frames->width, m_players[1]->anims[kHudPortrait].frames->height);
    m_graphics->Blit(dst, m_players[1]->surfaces[m_players[1]->anims[kHudPortrait].frames->surface], src, m_players[1]->colorKey, 1);
    src = MakeRect(0, 0, 0x140, 0x2c);
    dst = MakeRect(0, 0, 0x140, 0x2c);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    src = MakeRect(0, 0, m_players[0]->anims[kHudName].frames->width, m_players[0]->anims[kHudName].frames->height);
    dst = MakeRect(1, 0x28, m_players[0]->anims[kHudName].frames->width, m_players[0]->anims[kHudName].frames->height);
    m_graphics->Blit(dst, m_players[0]->surfaces[m_players[0]->anims[kHudName].frames->surface], src, m_players[0]->colorKey, 0);
    src = MakeRect(0, 0, m_players[1]->anims[kHudName].frames->width, m_players[1]->anims[kHudName].frames->height);
    dst = MakeRect(0x13f - m_players[1]->anims[kHudName].frames->width, 0x28, m_players[1]->anims[kHudName].frames->width, m_players[1]->anims[kHudName].frames->height);
    m_graphics->Blit(dst, m_players[1]->surfaces[m_players[1]->anims[kHudName].frames->surface], src, m_players[1]->colorKey, 0);
    length = (int)(m_players[0]->m_comboStartHp * 120.0 / 9999.0);
    if (length > 0) {
        src = MakeRect(0x78 - length, 0x5b, length, 6);
        dst = MakeRect(0x8a - length, 0x12, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = (int)(m_players[0]->m_shownHp * 120.0 / 9999.0);
    if (length >= 0x28) {
        src = MakeRect(0x78 - length, 0x49, length, 6);
        dst = MakeRect(0x8a - length, 0x12, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (length > 0) {
        src = MakeRect(0x78 - length, m_players[0]->m_blinkTimer % 0x24 / 0x12 * 6 + 0x4f, length, 6);
        dst = MakeRect(0x8a - length, 0x12, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = (int)(m_players[1]->m_comboStartHp * 120.0 / 9999.0);
    if (length > 0) {
        src = MakeRect(0x78, 0x5b, length, 6);
        dst = MakeRect(0xb6, 0x12, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = (int)(m_players[1]->m_shownHp * 120.0 / 9999.0);
    if (length >= 0x28) {
        src = MakeRect(0x78, 0x49, length, 6);
        dst = MakeRect(0xb6, 0x12, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (length > 0) {
        src = MakeRect(0x78, m_players[1]->m_blinkTimer % 0x24 / 0x12 * 6 + 0x4f, length, 8);
        dst = MakeRect(0xb6, 0x12, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    src = MakeRect(0x53, 0x93, 7, 0xd);
    if (m_game->m_roundsToWin >= 1) {
        dst = MakeRect(0x7b, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        dst = MakeRect(0xbe, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_game->m_roundsToWin >= 2) {
        dst = MakeRect(0x83, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        dst = MakeRect(0xb6, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_game->m_roundsToWin >= 3) {
        dst = MakeRect(0x8b, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        dst = MakeRect(0xae, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    src = MakeRect(0x4c, 0x93, 7, 0xd);
    if (m_players[0]->m_roundsWon >= 1) {
        dst = MakeRect(0x7b, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[0]->m_roundsWon >= 2) {
        dst = MakeRect(0x83, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[0]->m_roundsWon >= 3) {
        dst = MakeRect(0x8b, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[1]->m_roundsWon >= 1) {
        dst = MakeRect(0xbe, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[1]->m_roundsWon >= 2) {
        dst = MakeRect(0xb6, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[1]->m_roundsWon >= 3) {
        dst = MakeRect(0xae, 0x21, 7, 0xd);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    DrawNumber(0xa9, 9, m_fps, 0, 2, 0);
}

void CScene3::DrawGauges()
{
    int side;
    RECT src;
    int length; // the bar's length in pixels
    RECT dst;
    int i;

    if (m_game->m_hideHudTime > 0) {
        return;
    }
    src = MakeRect(0, 0x28, 0x140, 0x21);
    dst = MakeRect(0, 0xce, 0x140, 0x21);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    length = m_players[0]->m_gauge * 0x6c / 0xbb8;
    if (m_players[0]->m_gauge < 0x3e8) {
        src = MakeRect(0x6c - length, 0x73, length, 4);
        dst = MakeRect(0x8c - length, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[0]->m_gauge < 0x7d0) {
        src = MakeRect(0, 0x94, 0x18, 0x18);
        dst = MakeRect(6, 0xd1, 0x18, 0x18);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(0x6c - length, 0x77, length, 4);
        dst = MakeRect(0x8c - length, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[0]->m_gauge < 0xbb8) {
        src = MakeRect(0x18, 0x94, 0x18, 0x18);
        dst = MakeRect(6, 0xd1, 0x18, 0x18);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(0x6c - length, 0x7b, length, 4);
        dst = MakeRect(0x8c - length, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else {
        src = MakeRect(0x30, 0x94, 0x18, 0x18);
        dst = MakeRect(6, 0xd1, 0x18, 0x18);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(0x6c - length, m_players[0]->m_blinkTimer % 0x5a / 0x12 * 4 + 0x7f, length, 4);
        dst = MakeRect(0x8c - length, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = m_players[1]->m_gauge * 0x6c / 0xbb8;
    if (m_players[1]->m_gauge < 0x3e8) {
        src = MakeRect(0x6c, 0x73, length, 4);
        dst = MakeRect(0xb4, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[1]->m_gauge < 0x7d0) {
        src = MakeRect(0, 0x94, 0x18, 0x18);
        dst = MakeRect(0x122, 0xd1, 0x18, 0x18);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(0x6c, 0x77, length, 4);
        dst = MakeRect(0xb4, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[1]->m_gauge < 0xbb8) {
        src = MakeRect(0x18, 0x94, 0x18, 0x18);
        dst = MakeRect(0x122, 0xd1, 0x18, 0x18);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(0x6c, 0x7b, length, 4);
        dst = MakeRect(0xb4, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else {
        src = MakeRect(0x30, 0x94, 0x18, 0x18);
        dst = MakeRect(0x122, 0xd1, 0x18, 0x18);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(0x6c, m_players[1]->m_blinkTimer % 0x5a / 0x12 * 4 + 0x7f, length, 4);
        dst = MakeRect(0xb4, 0xe0, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[0]->m_rfBlue == 0) {
        if (m_players[0]->m_rfGauge < 500.0) {
            length = (int)(60.0 * m_players[0]->m_rfGauge * 2 / 1000.0);
            src = MakeRect(0x3c - length, 0x66, length, 2);
        } else {
            src = MakeRect(0, 0x66, 0x3c, 2);
            dst = MakeRect(0x4f, 0xe8, 0x3c, 2);
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
            length = (int)((m_players[0]->m_rfGauge - 500.0) * 60.0 * 2 / 1000.0);
            src = MakeRect(0x3c - length, 0x64, length, 2);
        }
    } else {
        length = (int)(60.0 * m_players[0]->m_rfGauge / 1000.0);
        src = MakeRect(0x3c - length, m_players[0]->m_blinkTimer % 0x5a / 0x12 * 2 + 0x68, length, 2);
    }
    dst = MakeRect(0x8b - length, 0xe8, length, 2);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    if (m_players[1]->m_rfBlue == 0) {
        if (m_players[1]->m_rfGauge < 500.0) {
            length = (int)(60.0 * m_players[1]->m_rfGauge * 2 / 1000.0);
            src = MakeRect(0x3c, 0x66, length, 2);
        } else {
            src = MakeRect(0x3c, 0x66, 0x3c, 2);
            dst = MakeRect(0xb5, 0xe8, 0x3c, 2);
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
            length = (int)((m_players[1]->m_rfGauge - 500.0) * 60.0 * 2 / 1000.0);
            src = MakeRect(0x3c, 0x64, length, 2);
        }
    } else {
        length = (int)(60.0 * m_players[1]->m_rfGauge / 1000.0);
        src = MakeRect(0x3c, m_players[1]->m_blinkTimer % 0x5a / 0x12 * 2 + 0x68, length, 2);
    }
    dst = MakeRect(0xb5, 0xe8, length, 2);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    if (m_game->m_roundOver == 0) {
        side = 0;
        for (; side < 2; side++) {
            if (m_players[side]->m_untechTime > 0 && m_players[side]->m_noAirRecovery == 0 && m_players[side]->y < 0.0 && m_players[side]->pattern >= kFirstHitReaction && m_players[side]->pattern < kFirstGuard && (m_players[side]->m_patterns[m_players[side]->pattern].frames[m_players[side]->frame].flagsAA & kAttackNoAirRecovery) == 0) {
                if (m_players[side]->facing == 1) {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)m_players[side]->x + m_drawX + i;
                        dst.top = m_drawY + 0xd2 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = m_players[side]->m_untechTime * (m_players[side]->m_untechTime < 0x64) + dst.left + (m_players[side]->m_untechTime >= 0x64) * 0x64;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xd3 - (m_players[side]->m_untechTime > 0x1e) * 3 - (m_players[side]->m_untechTime > 0x3c) * 7);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xc2);
                    }
                } else {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)m_players[side]->x + m_drawX - (m_players[side]->m_untechTime * (m_players[side]->m_untechTime < 0x64) + (m_players[side]->m_untechTime >= 0x64) * 0x64) - i;
                        dst.top = m_drawY + 0xd2 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = m_players[side]->m_untechTime * (m_players[side]->m_untechTime < 0x64) + dst.left + (m_players[side]->m_untechTime >= 0x64) * 0x64;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xd3 - (m_players[side]->m_untechTime > 0x1e) * 3 - (m_players[side]->m_untechTime > 0x3c) * 7);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xc2);
                    }
                }
            }
            if (m_players[side]->m_guardGauge != 0.0f && m_players[side]->IsGuarding() != 0) {
                if (m_players[side]->facing == 1) {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)m_players[side]->x + m_drawX + i;
                        dst.top = m_drawY + 0xd2 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = (int)(dst.left + m_players[side]->m_guardGauge * 1e+02f / 3.6e+02f);
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xdc);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xc2);
                    }
                } else {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)((int)m_players[side]->x + m_drawX - m_players[side]->m_guardGauge * 1e+02f / 3.6e+02f - i);
                        dst.top = m_drawY + 0xd2 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = (int)(dst.left + m_players[side]->m_guardGauge * 1e+02f / 3.6e+02f);
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xdc);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 0xc2);
                    }
                }
            }
        }
    }
}

void CScene3::DrawComboCount(CPlayer* attacker)
{
    RECT src;
    int hits; // m_shownHits, at most 99
    RECT dst;

    hits = attacker->m_shownHits;
    if (hits > 0x63) {
        hits = 0x63;
    }
    if (attacker->m_side > 0) {
        src = MakeRect(0, 0xac, 0x3d, 0x26);
        dst = MakeRect(0x102, 0x3f, 0x3d, 0x26);
        if (attacker->m_comboTimer <= 6) {
            m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        }
        if (hits > 9) {
            DrawNumber(0x11e, 0x3b, hits, 1, 0, attacker->m_comboTimer <= 6);
        } else {
            DrawNumber(0x11e, 0x3b, hits, 1, 0, attacker->m_comboTimer <= 6);
        }
        DrawNumber(0x11d, 0x52, attacker->m_comboDamage, 2, 0, attacker->m_comboTimer <= 6);
        DrawNumber(0x113, 0x5c, (int)attacker->m_shownProration, 2, 0, attacker->m_comboTimer <= 6);
        DrawNumber(0x11d, 0x5c, (int)(attacker->m_shownProration * 10.0) % 0xa, 2, 0, attacker->m_comboTimer <= 6);
        src = MakeRect(0x46, 0xe1, 3, 9);
        dst = MakeRect(0x113, 0x5c, 3, 9);
        if (attacker->m_comboTimer <= 6) {
            m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        }
        return;
    }
    src = MakeRect(0, 0xac, 0x3d, 0x26);
    dst = MakeRect(6, 0x3f, 0x3d, 0x26);
    if (attacker->m_comboTimer <= 6) {
        m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
    } else {
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (hits > 9) {
        DrawNumber(0x22, 0x3b, hits, 1, 0, attacker->m_comboTimer <= 6);
    } else {
        DrawNumber(0x22, 0x3b, hits, 1, 0, attacker->m_comboTimer <= 6);
    }
    DrawNumber(0x21, 0x52, attacker->m_comboDamage, 2, 0, attacker->m_comboTimer <= 6);
    DrawNumber(0x17, 0x5c, (int)attacker->m_shownProration, 2, 0, attacker->m_comboTimer <= 6);
    DrawNumber(0x21, 0x5c, (int)(attacker->m_shownProration * 10.0) % 0xa, 2, 0, attacker->m_comboTimer <= 6);
    src = MakeRect(0x46, 0xe1, 3, 9);
    dst = MakeRect(0x17, 0x5c, 3, 9);
    if (attacker->m_comboTimer <= 6) {
        m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
        return;
    }
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
}

void CScene3::DrawShadows()
{
    int slot;
    RECT src;
    int rows; // the sprite's rows above its feet, squashed to a third
    EffectFrame* sprite;
    int side;
    RECT dst;
    int gap; // how far the sprite's bottom is above its feet

    side = 0;
    for (; side < 2; side++) {
        if (m_players[side]->m_drawShadow != 0) {
            sprite = &m_players[side]->anims[m_players[side]->pattern].frames[m_players[side]->frame];
            if (sprite->y < sprite->height) {
                rows = sprite->y;
                gap = 0;
            } else {
                rows = sprite->height;
                gap = sprite->y - sprite->height;
            }
            src.left = 0;
            src.top = 0;
            src.right = sprite->width;
            src.bottom = rows;
            dst.left = (int)m_players[side]->x + m_drawX - sprite->x * (m_players[side]->facing == 1) - (sprite->width - sprite->x) * (m_players[side]->facing == -1);
            dst.top = 0xd2 - ((int)m_players[side]->y - (m_players[side]->y < 0.0)) + m_drawY + gap;
            dst.right = sprite->width + dst.left;
            dst.bottom = rows / 3 + dst.top;
            if (dst.top < 0xf0 && dst.bottom > 0) {
                m_graphics->BlitShadow(dst, m_players[side]->surfaces[sprite->surface], src, m_players[side]->colorKey, m_players[side]->facing == -1, 0xb0);
            }
        }
        slot = m_players[side]->m_objectTail;
        while (slot != m_players[side]->m_objectHead) {
            if (m_players[side]->m_objectActive[slot] != 0 && m_players[side]->m_objects[slot].shadow != 0 && (m_players[side]->m_objects[slot].drawnWhileHidden != 0 || m_game->m_hideObjectsTime == 0)) {
                sprite = &m_players[side]->anims[m_players[side]->m_objects[slot].pattern].frames[m_players[side]->m_objects[slot].frame];
                if (sprite->y < sprite->height) {
                    rows = sprite->y;
                    gap = 0;
                } else {
                    rows = sprite->height;
                    gap = sprite->y - sprite->height;
                }
                src.left = 0;
                src.top = 0;
                src.right = sprite->width;
                src.bottom = rows;
                if (m_players[side]->m_objects[slot].facing == -1) {
                    dst.left = (int)m_players[side]->m_objects[slot].x + m_drawX - (sprite->width - sprite->x);
                    dst.top = m_drawY + 0xd2 - (int)m_players[side]->m_objects[slot].y + gap;
                    dst.right = sprite->width + dst.left;
                    dst.bottom = rows / 3 + dst.top;
                } else {
                    dst.left = (int)m_players[side]->m_objects[slot].x + m_drawX - sprite->x;
                    dst.top = m_drawY + 0xd2 - (int)m_players[side]->m_objects[slot].y + gap;
                    dst.right = sprite->width + dst.left;
                    dst.bottom = rows / 3 + dst.top;
                }
                if (dst.top < 0xf0 && dst.bottom > 0) {
                    m_graphics->BlitShadow(dst, m_players[side]->surfaces[sprite->surface], src, m_players[side]->colorKey, m_players[side]->m_objects[slot].facing == -1, 0xb0);
                }
            }
            slot++;
            if (slot >= 0x40) {
                slot = 0;
            }
        }
    }
}

void CScene3::DrawBordersAndFlip()
{
    int dstY; // where the stage's top edge lands; the rows it leaves are filled black
    int srcX;
    int srcY;
    int dstX; // where the stage's left edge lands; the columns it leaves are filled black

    srcX = -m_drawX;
    srcY = 0xf0 - m_drawY;
    dstX = 0;
    dstY = 0;
    if (srcX > 0x140) {
        dstX = 0x140 - srcX;
        srcX = 0x140;
    } else if (srcX < 0) {
        dstX = -srcX;
        srcX = 0;
    }
    if (srcY > 0xf0) {
        dstY = 0xf0 - srcY;
        srcY = 0xf0;
    } else if (srcY < 0) {
        dstY = -srcY;
        srcY = 0;
    }
    m_graphics->FillRect(MakeRect(0, (dstY + 0xf0) * (dstY < 0), 0x140, abs(dstY)), 0);
    m_graphics->FillRect(MakeRect((dstX + 0x140) * (dstX < 0), (dstY >= 0) * dstY, abs(dstX), 0xf0 - abs(dstY)), 0);
    m_graphics->Flip();
}
