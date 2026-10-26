// The size of each character's CPlayer in efz.exe (src/efz.h SIZE), by character number:
// EfzRevival.dll's save states copy that much of each player.
//
// Observed: the launcher has twelve copies of this table at the start of its objects'
// initialized data (0x4b7000 in Config.obj's, ...), one in every object that includes
// Version.h, though nothing in the launcher reads it; EfzRevival.dll and DDRAW.dll have
// it too. It is included next to Version.h here.
#pragma once

static int g_characterSizes[25] = {
    0x3470, 0x3450, 0x3458, 0x3450, 0x3450, 0x3448, 0x34b0, 0x3448, 0x3458, 0x3458,
    0x3460, 0x3458, 0x3468, 0x3450, 0x3478, 0x3478, 0x3468, 0x3458, 0x3460, 0x3458,
    0x3478, 0x3458, 0x3460, 0x3488, 0x3460,
};
