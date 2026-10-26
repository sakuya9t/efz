// The input display of the practice and replay sessions: a player's last inputs, one
// line each from y = 200 down, newest first, with how many frames each was held (the
// arrows of the direction, then A, B, C and D). All of it is inline (COMDATs emitted by
// the practice session's object, the first to use them). The y and colour parameters
// are the same at every call, so link-time code generation passes nothing for them.
#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "EfzGame.h"

// FUNCTION: 0x10028c40 ?toWString@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z
inline std::wstring toWString(int value)
{
    wchar_t buffer[64];
    swprintf_s(buffer, 64, L"%d", value);
    return std::wstring(buffer);
}

// An input byte (bits 0-3 right, left, down, up; 4-7 A-D) as text.
// FUNCTION: 0x10028d10 ?inputString@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@E@Z
inline std::wstring inputString(BYTE input)
{
    std::wstring text(L"");
    if ((input & 2) && (input & 8))
        text.append(L"\x2196 ");
    else if ((input & 2) && (input & 4))
        text.append(L"\x2199 ");
    else if ((input & 1) && (input & 8))
        text.append(L"\x2197 ");
    else if ((input & 1) && (input & 4))
        text.append(L"\x2198 ");
    else if (input & 8)
        text.append(L"\x2191 ");
    else if (input & 2)
        text.append(L"\x2190 ");
    else if (input & 4)
        text.append(L"\x2193 ");
    else if (input & 1)
        text.append(L"\x2192 ");
    else
        text.append(L"  ");
    text.append((input & 0x10) ? L"A" : L" ");
    text.append((input & 0x20) ? L"B" : L" ");
    text.append((input & 0x40) ? L"C" : L" ");
    if (input & 0x80)
        text.append(L"D");
    return text;
}

// FUNCTION: 0x10028e50 ?drawLine@@YAXHABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@HHK@Z
inline void drawLine(int y, const std::wstring &text, int line, int x, DWORD color)
{
    g_game.addText(text, x, y + line * 14, color);
}

// The last 15 inputs of `inputs` (oldest first), each with the frames it was held,
// divided by `divisor` (the practice session records 3 entries a frame).
// FUNCTION: 0x10028e80 ?drawInputs@@YAXABV?$vector@EV?$allocator@E@std@@@std@@HHKH@Z
inline void drawInputs(const std::vector<BYTE> &inputs, int y, int x, DWORD color, int divisor)
{
    if (inputs.size() == 0)
        return;
    std::wstring unused(L"");
    int line = 0;
    std::vector<BYTE>::const_iterator it = inputs.end();
    --it;
    std::vector<BYTE>::const_iterator last = it;
    while (it != inputs.begin()) {
        if (line > 14)
            break;
        int frames = 0;
        while (it != inputs.begin()) {
            if (*it != *last)
                break;
            frames++;
            --it;
            if (frames > divisor * 999)
                frames = divisor * 999;
        }
        std::wostringstream count;
        count << std::setw(3) << frames / divisor;
        std::wstring text = count.str();
        text.append(L" ");
        text += inputString(*last);
        drawLine(y, text, line, x, color);
        line++;
        last = it;
    }
}
