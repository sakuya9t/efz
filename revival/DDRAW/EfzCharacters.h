// The size of each character's CPlayer (efz.exe's `new`, src/efz.h SIZE), by character
// number: the table EfzRevival.dll's Efz.h has. Config.cpp and Process.cpp include it
// (files DDRAW.dll shares with the DLL's project); nothing reads it, but each of the two
// objects has its own copy in .data (0x100b5770, 0x100b57d8).
#pragma once

static int g_characterSizes[25] = {
    0x3470, 0x3450, 0x3458, 0x3450, 0x3450, 0x3448, 0x34b0, 0x3448, 0x3458, 0x3458,
    0x3460, 0x3458, 0x3468, 0x3450, 0x3478, 0x3478, 0x3468, 0x3458, 0x3460, 0x3458,
    0x3478, 0x3458, 0x3460, 0x3488, 0x3460,
};
