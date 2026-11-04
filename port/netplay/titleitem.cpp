// The title menu's NET PLAY row, made from the menu's own letters.
//
// system\title_ob.dat holds the menu: seven rows of 14 pixels (ARCADE, VS CPU,
// VS HUMAN, PRACTICE, REPLAY, OPTION, EXIT), then the same rows highlighted, the
// letters dark on a bar. Every letter of NET PLAY is in them: N from VS HUMAN, E and T
// from EXIT, PLAY as REPLAY has it. The rows are cut into letters at the columns no
// pixel of the row uses; NET's letters are set the width apart that EXIT's are, and the
// space is VS CPU's. The highlighted row is the bar of the highlighted rows, taken a
// column at a time from a row that has no letter there (or, where all have one, filled
// from beside the letter), with the highlighted letters copied on.
#include <vector>

#include "efz.h"
#include "../log.h"

namespace efz {
namespace netplay {

namespace {

const int kWidth = 120;
const int kRow = 14;
const int kRows = 7;
const int kHighlight = 98; // the highlighted rows' first line

struct Glyph {
    int x0, x1; // columns [x0, x1)
};

IDirectDrawSurface* g_item; // 120 x 28: the row, then the row highlighted
bool g_tried;

BYTE At(IDirectDrawSurface* s, int x, int y)
{
    return ((BYTE*)s->pixels)[y * s->pitch + x];
}

BYTE& Out(int x, int y)
{
    return ((BYTE*)g_item->pixels)[y * g_item->pitch + x];
}

// The columns of a row's letters: runs of columns with a pixel that isn't the key.
std::vector<Glyph> Letters(IDirectDrawSurface* menu, int row, BYTE key)
{
    std::vector<Glyph> out;
    int start = -1;
    for (int x = 0; x <= kWidth; x++) {
        bool ink = false;
        for (int y = row * kRow; x < kWidth && y < row * kRow + kRow && !ink; y++)
            ink = At(menu, x, y) != key;
        if (ink && start < 0)
            start = x;
        if (!ink && start >= 0) {
            out.push_back(Glyph{start, x});
            start = -1;
        }
    }
    return out;
}

// Whether column x of a row has a letter's pixel within one pixel of it.
bool NearLetter(IDirectDrawSurface* menu, int row, int x, BYTE key)
{
    for (int dx = -1; dx <= 1; dx++) {
        int c = x + dx;
        if (c < 0 || c >= kWidth)
            continue;
        for (int y = row * kRow; y < row * kRow + kRow; y++)
            if (At(menu, c, y) != key)
                return true;
    }
    return false;
}

bool Build(IDirectDrawSurface* menu, BYTE key)
{
    if (!menu || menu->width < kWidth || menu->height < kHighlight + kRows * kRow)
        return false;
    static const int counts[kRows] = {6, 5, 7, 8, 6, 6, 4};
    std::vector<Glyph> rows[kRows];
    for (int r = 0; r < kRows; r++) {
        rows[r] = Letters(menu, r, key);
        if ((int)rows[r].size() != counts[r]) {
            LogWarn("net", "the title menu's row %d has %d letters, not %d", r,
                    (int)rows[r].size(), counts[r]);
            return false;
        }
    }
    // Where each piece of NET PLAY comes from, and where it goes.
    struct Piece {
        int row;
        Glyph from;
        int to;
    };
    const Glyph& n = rows[2][6];
    const Glyph& e = rows[6][0];
    const Glyph& t = rows[6][3];
    Glyph play = {rows[4][2].x0, rows[4][5].x1};
    int letterGap = rows[6][1].x0 - rows[6][0].x1;
    int space = rows[1][2].x0 - rows[1][1].x1;
    int x = rows[0][0].x0;
    std::vector<Piece> pieces;
    pieces.push_back(Piece{2, n, x});
    x += n.x1 - n.x0 + letterGap;
    pieces.push_back(Piece{6, e, x});
    x += e.x1 - e.x0 + letterGap;
    pieces.push_back(Piece{6, t, x});
    x += t.x1 - t.x0 + space;
    pieces.push_back(Piece{4, play, x});
    if (x + play.x1 - play.x0 > kWidth)
        return false;

    g_item = new IDirectDrawSurface(kWidth, 2 * kRow);
    // The bar: each column from a highlighted row without a letter near it.
    std::vector<bool> fill(kWidth * kRow, false);
    for (int c = 0; c < kWidth; c++) {
        int from = -1;
        for (int r = kRows - 1; r >= 0 && from < 0; r--)
            if (!NearLetter(menu, r, c, key))
                from = r;
        int r = from >= 0 ? from : kRows - 1;
        for (int y = 0; y < kRow; y++) {
            Out(c, kRow + y) = At(menu, c, kHighlight + r * kRow + y);
            Out(c, y) = key;
            if (from < 0 && At(menu, c, r * kRow + y) != key)
                fill[y * kWidth + c] = true;
        }
    }
    // Where every row has a letter: EXIT's letters filled from the bar beside them.
    for (int y = 0; y < kRow; y++) {
        for (int c = 0; c < kWidth; c++) {
            if (!fill[y * kWidth + c])
                continue;
            for (int d = 1; d < kWidth; d++) {
                int l = c - d, rr = c + d;
                if (rr < kWidth && !fill[y * kWidth + rr]) {
                    Out(c, kRow + y) = Out(rr, kRow + y);
                    break;
                }
                if (l >= 0 && !fill[y * kWidth + l]) {
                    Out(c, kRow + y) = Out(l, kRow + y);
                    break;
                }
            }
        }
    }
    // The letters, plain and highlighted.
    for (const Piece& p : pieces) {
        for (int c = p.from.x0; c < p.from.x1; c++) {
            int to = p.to + c - p.from.x0;
            for (int y = 0; y < kRow; y++) {
                if (At(menu, c, p.row * kRow + y) == key)
                    continue;
                Out(to, y) = At(menu, c, p.row * kRow + y);
                Out(to, kRow + y) = At(menu, c, kHighlight + p.row * kRow + y);
            }
        }
    }
    return true;
}

} // namespace

// Draws the row at (x, y), over the highlighted one when selected, as the menu draws its
// rows. False if the menu's letters couldn't be made into it (the screen then writes it).
bool DrawTitleItem(CGraphics* graphics, IDirectDrawSurface* menu, BYTE key, bool selected, int x,
                   int y)
{
    if (!g_tried) {
        g_tried = true;
        if (!Build(menu, key)) {
            LogWarn("net", "NET PLAY is written over the title menu, not in its letters");
            g_item = nullptr;
        }
    }
    if (!g_item)
        return false;
    graphics->Blit(MakeRect(x, y, kWidth, kRow), g_item, MakeRect(0, 0, kWidth, kRow), key, 0);
    if (selected)
        graphics->Blit(MakeRect(x, y, kWidth, kRow), g_item, MakeRect(0, kRow, kWidth, kRow), key, 0);
    return true;
}

} // namespace netplay
} // namespace efz
