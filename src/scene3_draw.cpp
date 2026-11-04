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
        digit = rest % 10;
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
        rest = rest / 10;
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
    srcY = (int)((240 - m_drawY) * m_game->m_bgParallax + (120.0 - 120.0 * m_game->m_bgParallax));
    dstX = 0;
    dstY = 0;
    if (srcX > 320) {
        dstX = 320 - srcX;
        srcX = 320;
    } else if (srcX < 0) {
        dstX = -srcX;
        srcX = 0;
    }
    if (srcY > 240) {
        dstY = 240 - srcY;
        srcY = 240;
    } else if (srcY < 0) {
        dstY = -srcY;
        srcY = 0;
    }
    src = MakeRect(srcX, srcY, 320, 240);
    dst = MakeRect(dstX, dstY, 320, 240);
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
        m_players[0]->m_shownHp -= 200;
        if (m_players[0]->m_shownHp < m_players[0]->m_hp) {
            m_players[0]->m_shownHp = m_players[0]->m_hp;
        }
    }
    if (m_players[0]->m_shownHp < m_players[0]->m_hp) {
        m_players[0]->m_shownHp += 200;
        if (m_players[0]->m_shownHp > m_players[0]->m_hp) {
            m_players[0]->m_shownHp = m_players[0]->m_hp;
        }
    }
    if (m_players[1]->m_comboHits == 0) {
        m_players[0]->m_comboStartHp -= (m_players[0]->m_comboStartHp > m_players[0]->m_hp) * 100;
        if (m_players[0]->m_comboStartHp < m_players[0]->m_hp) {
            m_players[0]->m_comboStartHp = m_players[0]->m_hp;
        }
    }
    if (m_players[1]->m_shownHp > m_players[1]->m_hp) {
        m_players[1]->m_shownHp -= 200;
        if (m_players[1]->m_shownHp < m_players[1]->m_hp) {
            m_players[1]->m_shownHp = m_players[1]->m_hp;
        }
    }
    if (m_players[1]->m_shownHp < m_players[1]->m_hp) {
        m_players[1]->m_shownHp += 200;
        if (m_players[1]->m_shownHp > m_players[1]->m_hp) {
            m_players[1]->m_shownHp = m_players[1]->m_hp;
        }
    }
    if (m_players[0]->m_comboHits == 0) {
        m_players[1]->m_comboStartHp -= (m_players[1]->m_comboStartHp > m_players[1]->m_hp) * 100;
        if (m_players[1]->m_comboStartHp < m_players[1]->m_hp) {
            m_players[1]->m_comboStartHp = m_players[1]->m_hp;
        }
    }
    if (m_game->m_hideHudTime > 0) {
        return;
    }
    src = MakeRect(0, 0, m_players[0]->anims[kHudPortrait].frames->width, m_players[0]->anims[kHudPortrait].frames->height);
    dst = MakeRect(0, 14, m_players[0]->anims[kHudPortrait].frames->width, m_players[0]->anims[kHudPortrait].frames->height);
    m_graphics->Blit(dst, m_players[0]->surfaces[m_players[0]->anims[kHudPortrait].frames->surface], src, m_players[0]->colorKey, 0);
    src = MakeRect(0, 0, m_players[1]->anims[kHudPortrait].frames->width, m_players[1]->anims[kHudPortrait].frames->height);
    dst = MakeRect(320 - m_players[1]->anims[kHudPortrait].frames->width, 14, m_players[1]->anims[kHudPortrait].frames->width, m_players[1]->anims[kHudPortrait].frames->height);
    m_graphics->Blit(dst, m_players[1]->surfaces[m_players[1]->anims[kHudPortrait].frames->surface], src, m_players[1]->colorKey, 1);
    src = MakeRect(0, 0, 320, 44);
    dst = MakeRect(0, 0, 320, 44);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    src = MakeRect(0, 0, m_players[0]->anims[kHudName].frames->width, m_players[0]->anims[kHudName].frames->height);
    dst = MakeRect(1, 40, m_players[0]->anims[kHudName].frames->width, m_players[0]->anims[kHudName].frames->height);
    m_graphics->Blit(dst, m_players[0]->surfaces[m_players[0]->anims[kHudName].frames->surface], src, m_players[0]->colorKey, 0);
    src = MakeRect(0, 0, m_players[1]->anims[kHudName].frames->width, m_players[1]->anims[kHudName].frames->height);
    dst = MakeRect(319 - m_players[1]->anims[kHudName].frames->width, 40, m_players[1]->anims[kHudName].frames->width, m_players[1]->anims[kHudName].frames->height);
    m_graphics->Blit(dst, m_players[1]->surfaces[m_players[1]->anims[kHudName].frames->surface], src, m_players[1]->colorKey, 0);
    length = (int)(m_players[0]->m_comboStartHp * 120.0 / 9999.0);
    if (length > 0) {
        src = MakeRect(120 - length, 91, length, 6);
        dst = MakeRect(138 - length, 18, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = (int)(m_players[0]->m_shownHp * 120.0 / 9999.0);
    if (length >= 40) {
        src = MakeRect(120 - length, 73, length, 6);
        dst = MakeRect(138 - length, 18, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (length > 0) {
        src = MakeRect(120 - length, m_players[0]->m_blinkTimer % 36 / 18 * 6 + 79, length, 6);
        dst = MakeRect(138 - length, 18, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = (int)(m_players[1]->m_comboStartHp * 120.0 / 9999.0);
    if (length > 0) {
        src = MakeRect(120, 91, length, 6);
        dst = MakeRect(182, 18, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = (int)(m_players[1]->m_shownHp * 120.0 / 9999.0);
    if (length >= 40) {
        src = MakeRect(120, 73, length, 6);
        dst = MakeRect(182, 18, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (length > 0) {
        src = MakeRect(120, m_players[1]->m_blinkTimer % 36 / 18 * 6 + 79, length, 8);
        dst = MakeRect(182, 18, length, 6);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    src = MakeRect(83, 147, 7, 13);
    if (m_game->m_roundsToWin >= 1) {
        dst = MakeRect(123, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        dst = MakeRect(190, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_game->m_roundsToWin >= 2) {
        dst = MakeRect(131, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        dst = MakeRect(182, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_game->m_roundsToWin >= 3) {
        dst = MakeRect(139, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        dst = MakeRect(174, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    src = MakeRect(76, 147, 7, 13);
    if (m_players[0]->m_roundsWon >= 1) {
        dst = MakeRect(123, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[0]->m_roundsWon >= 2) {
        dst = MakeRect(131, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[0]->m_roundsWon >= 3) {
        dst = MakeRect(139, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[1]->m_roundsWon >= 1) {
        dst = MakeRect(190, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[1]->m_roundsWon >= 2) {
        dst = MakeRect(182, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[1]->m_roundsWon >= 3) {
        dst = MakeRect(174, 33, 7, 13);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    DrawNumber(169, 9, m_fps, 0, 2, 0);
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
    src = MakeRect(0, 40, 320, 33);
    dst = MakeRect(0, 206, 320, 33);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    length = m_players[0]->m_gauge * 108 / 3000;
    if (m_players[0]->m_gauge < 1000) {
        src = MakeRect(108 - length, 115, length, 4);
        dst = MakeRect(140 - length, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[0]->m_gauge < 2000) {
        src = MakeRect(0, 148, 24, 24);
        dst = MakeRect(6, 209, 24, 24);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(108 - length, 119, length, 4);
        dst = MakeRect(140 - length, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[0]->m_gauge < 3000) {
        src = MakeRect(24, 148, 24, 24);
        dst = MakeRect(6, 209, 24, 24);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(108 - length, 123, length, 4);
        dst = MakeRect(140 - length, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else {
        src = MakeRect(48, 148, 24, 24);
        dst = MakeRect(6, 209, 24, 24);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(108 - length, m_players[0]->m_blinkTimer % 90 / 18 * 4 + 127, length, 4);
        dst = MakeRect(140 - length, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    length = m_players[1]->m_gauge * 108 / 3000;
    if (m_players[1]->m_gauge < 1000) {
        src = MakeRect(108, 115, length, 4);
        dst = MakeRect(180, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[1]->m_gauge < 2000) {
        src = MakeRect(0, 148, 24, 24);
        dst = MakeRect(290, 209, 24, 24);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(108, 119, length, 4);
        dst = MakeRect(180, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else if (m_players[1]->m_gauge < 3000) {
        src = MakeRect(24, 148, 24, 24);
        dst = MakeRect(290, 209, 24, 24);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(108, 123, length, 4);
        dst = MakeRect(180, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    } else {
        src = MakeRect(48, 148, 24, 24);
        dst = MakeRect(290, 209, 24, 24);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        src = MakeRect(108, m_players[1]->m_blinkTimer % 90 / 18 * 4 + 127, length, 4);
        dst = MakeRect(180, 224, length, 4);
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (m_players[0]->m_rfBlue == 0) {
        if (m_players[0]->m_rfGauge < 500.0) {
            length = (int)(60.0 * m_players[0]->m_rfGauge * 2 / 1000.0);
            src = MakeRect(60 - length, 102, length, 2);
        } else {
            src = MakeRect(0, 102, 60, 2);
            dst = MakeRect(79, 232, 60, 2);
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
            length = (int)((m_players[0]->m_rfGauge - 500.0) * 60.0 * 2 / 1000.0);
            src = MakeRect(60 - length, 100, length, 2);
        }
    } else {
        length = (int)(60.0 * m_players[0]->m_rfGauge / 1000.0);
        src = MakeRect(60 - length, m_players[0]->m_blinkTimer % 90 / 18 * 2 + 104, length, 2);
    }
    dst = MakeRect(139 - length, 232, length, 2);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    if (m_players[1]->m_rfBlue == 0) {
        if (m_players[1]->m_rfGauge < 500.0) {
            length = (int)(60.0 * m_players[1]->m_rfGauge * 2 / 1000.0);
            src = MakeRect(60, 102, length, 2);
        } else {
            src = MakeRect(60, 102, 60, 2);
            dst = MakeRect(181, 232, 60, 2);
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
            length = (int)((m_players[1]->m_rfGauge - 500.0) * 60.0 * 2 / 1000.0);
            src = MakeRect(60, 100, length, 2);
        }
    } else {
        length = (int)(60.0 * m_players[1]->m_rfGauge / 1000.0);
        src = MakeRect(60, m_players[1]->m_blinkTimer % 90 / 18 * 2 + 104, length, 2);
    }
    dst = MakeRect(181, 232, length, 2);
    m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    if (m_game->m_roundOver == 0) {
        side = 0;
        for (; side < 2; side++) {
            if (m_players[side]->m_untechTime > 0 && m_players[side]->m_noAirRecovery == 0 && m_players[side]->y < 0.0 && m_players[side]->pattern >= kFirstHitReaction && m_players[side]->pattern < kFirstGuard && (m_players[side]->m_patterns[m_players[side]->pattern].frames[m_players[side]->frame].flagsAA & kAttackNoAirRecovery) == 0) {
                if (m_players[side]->facing == 1) {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)m_players[side]->x + m_drawX + i;
                        dst.top = m_drawY + 210 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = m_players[side]->m_untechTime * (m_players[side]->m_untechTime < 100) + dst.left + (m_players[side]->m_untechTime >= 100) * 100;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 211 - (m_players[side]->m_untechTime > 30) * 3 - (m_players[side]->m_untechTime > 60) * 7);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 194);
                    }
                } else {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)m_players[side]->x + m_drawX - (m_players[side]->m_untechTime * (m_players[side]->m_untechTime < 100) + (m_players[side]->m_untechTime >= 100) * 100) - i;
                        dst.top = m_drawY + 210 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = m_players[side]->m_untechTime * (m_players[side]->m_untechTime < 100) + dst.left + (m_players[side]->m_untechTime >= 100) * 100;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 211 - (m_players[side]->m_untechTime > 30) * 3 - (m_players[side]->m_untechTime > 60) * 7);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 194);
                    }
                }
            }
            if (m_players[side]->m_guardGauge != 0.0f && m_players[side]->IsGuarding() != 0) {
                if (m_players[side]->facing == 1) {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)m_players[side]->x + m_drawX + i;
                        dst.top = m_drawY + 210 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = (int)(dst.left + m_players[side]->m_guardGauge * 1e+02f / 3.6e+02f);
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 220);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 194);
                    }
                } else {
                    i = 0;
                    for (; i < 3; i++) {
                        dst.left = (int)((int)m_players[side]->x + m_drawX - m_players[side]->m_guardGauge * 1e+02f / 3.6e+02f - i);
                        dst.top = m_drawY + 210 + (int)m_players[side]->y - (m_players[side]->y < 0.0) + i;
                        dst.right = (int)(dst.left + m_players[side]->m_guardGauge * 1e+02f / 3.6e+02f);
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 220);
                        dst.top += 2;
                        dst.bottom = dst.top + 1;
                        m_graphics->FillRect(dst, 194);
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
    if (hits > 99) {
        hits = 99;
    }
    if (attacker->m_side > 0) {
        src = MakeRect(0, 172, 61, 38);
        dst = MakeRect(258, 63, 61, 38);
        if (attacker->m_comboTimer <= 6) {
            m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        }
        if (hits > 9) {
            DrawNumber(286, 59, hits, 1, 0, attacker->m_comboTimer <= 6);
        } else {
            DrawNumber(286, 59, hits, 1, 0, attacker->m_comboTimer <= 6);
        }
        DrawNumber(285, 82, attacker->m_comboDamage, 2, 0, attacker->m_comboTimer <= 6);
        DrawNumber(275, 92, (int)attacker->m_shownProration, 2, 0, attacker->m_comboTimer <= 6);
        DrawNumber(285, 92, (int)(attacker->m_shownProration * 10.0) % 10, 2, 0, attacker->m_comboTimer <= 6);
        src = MakeRect(70, 225, 3, 9);
        dst = MakeRect(275, 92, 3, 9);
        if (attacker->m_comboTimer <= 6) {
            m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
        } else {
            m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
        }
        return;
    }
    src = MakeRect(0, 172, 61, 38);
    dst = MakeRect(6, 63, 61, 38);
    if (attacker->m_comboTimer <= 6) {
        m_graphics->BlitEx(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0, 0);
    } else {
        m_graphics->Blit(dst, m_game->m_objectSurface, src, m_game->m_colorKey, 0);
    }
    if (hits > 9) {
        DrawNumber(34, 59, hits, 1, 0, attacker->m_comboTimer <= 6);
    } else {
        DrawNumber(34, 59, hits, 1, 0, attacker->m_comboTimer <= 6);
    }
    DrawNumber(33, 82, attacker->m_comboDamage, 2, 0, attacker->m_comboTimer <= 6);
    DrawNumber(23, 92, (int)attacker->m_shownProration, 2, 0, attacker->m_comboTimer <= 6);
    DrawNumber(33, 92, (int)(attacker->m_shownProration * 10.0) % 10, 2, 0, attacker->m_comboTimer <= 6);
    src = MakeRect(70, 225, 3, 9);
    dst = MakeRect(23, 92, 3, 9);
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
            dst.top = 210 - ((int)m_players[side]->y - (m_players[side]->y < 0.0)) + m_drawY + gap;
            dst.right = sprite->width + dst.left;
            dst.bottom = rows / 3 + dst.top;
            if (dst.top < 240 && dst.bottom > 0) {
                m_graphics->BlitShadow(dst, m_players[side]->surfaces[sprite->surface], src, m_players[side]->colorKey, m_players[side]->facing == -1, 176);
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
                    dst.top = m_drawY + 210 - (int)m_players[side]->m_objects[slot].y + gap;
                    dst.right = sprite->width + dst.left;
                    dst.bottom = rows / 3 + dst.top;
                } else {
                    dst.left = (int)m_players[side]->m_objects[slot].x + m_drawX - sprite->x;
                    dst.top = m_drawY + 210 - (int)m_players[side]->m_objects[slot].y + gap;
                    dst.right = sprite->width + dst.left;
                    dst.bottom = rows / 3 + dst.top;
                }
                if (dst.top < 240 && dst.bottom > 0) {
                    m_graphics->BlitShadow(dst, m_players[side]->surfaces[sprite->surface], src, m_players[side]->colorKey, m_players[side]->m_objects[slot].facing == -1, 176);
                }
            }
            slot++;
            if (slot >= 64) {
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
    srcY = 240 - m_drawY;
    dstX = 0;
    dstY = 0;
    if (srcX > 320) {
        dstX = 320 - srcX;
        srcX = 320;
    } else if (srcX < 0) {
        dstX = -srcX;
        srcX = 0;
    }
    if (srcY > 240) {
        dstY = 240 - srcY;
        srcY = 240;
    } else if (srcY < 0) {
        dstY = -srcY;
        srcY = 0;
    }
    m_graphics->FillRect(MakeRect(0, (dstY + 240) * (dstY < 0), 320, abs(dstY)), 0);
    m_graphics->FillRect(MakeRect((dstX + 320) * (dstX < 0), (dstY >= 0) * dstY, abs(dstX), 240 - abs(dstY)), 0);
    m_graphics->Flip();
}
