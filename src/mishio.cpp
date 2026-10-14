// CMishio (0x530bc0-0x5571ef): the character class whose files are in mishio\ in the game
// folder (mishio.dat sprites, mishio.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMishio::Vf6()
{
    WORD x8;
    WORD l4;

    if (*(short*)((char*)this + 0x14a) > 0 || *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) > 0) {
        return;
    }
    EffectDesc l50;
    l4 = *(short*)(*(char**)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc);
    x8 = *(BYTE*)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + 8) * 8);
    CPlayer::Unk413090((EffectDesc*)&l50);
    switch (*(WORD*)((char*)this + 8)) {
    default:
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 1:
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) = 0.4;
        *(double*)((char*)this + 0x38) = 0.0;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 2:
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) = -0.4;
        *(double*)((char*)this + 0x38) = 0.0;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 3:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        *((char*)this + 0x158) = 0;
        CPlayer::Unk40e630();
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 4:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(BYTE*)((char*)this + 0x158) == 0) {
                CPlayer::Unk40e630();
            }
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.04;
            *(double*)((char*)this + 0x38) = -2.45;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *(double*)((char*)this + 0x30) = 0.3;
                *((char*)this + 0x158) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(BYTE*)((char*)this + 0x158) == 0) {
                CPlayer::Unk40e630();
            }
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.04;
            *(double*)((char*)this + 0x38) = -2.45;
            *(double*)((char*)this + 0x30) = 0.7;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *(double*)((char*)this + 0x30) = 1.1;
                *((char*)this + 0x158) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 6:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(BYTE*)((char*)this + 0x158) == 0) {
                CPlayer::Unk40e630();
            }
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.04;
            *(double*)((char*)this + 0x38) = -2.45;
            *(double*)((char*)this + 0x30) = -0.7;
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 7:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        *((char*)this + 0x158) = 0;
        CPlayer::Unk40e630();
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 8:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        *((char*)this + 0x158) = 0;
        CPlayer::Unk40e630();
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 9:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        *((char*)this + 0x158) = 0;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0xd:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        *((char*)this + 0x158) = 0;
        CPlayer::Unk40e630();
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0xe:
        *(double*)((char*)this + 0x48) = 0.04;
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.45;
            *(double*)((char*)this + 0x30) = 0.0;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *(double*)((char*)this + 0x30) = 0.4;
                *((char*)this + 0x158) = 0;
            }
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0xf:
        *(double*)((char*)this + 0x48) = 0.04;
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.45;
            *(double*)((char*)this + 0x30) = 0.7;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *(double*)((char*)this + 0x30) = 1.1;
                *((char*)this + 0x158) = 0;
            }
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0x10:
        *(double*)((char*)this + 0x48) = 0.04;
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.45;
            *(double*)((char*)this + 0x30) = -0.7;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *((char*)this + 0x158) = 0;
            }
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0x2f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x48) = 0.035;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 2;
            *((char*)this + 0x2c9) = 7;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                (*(short*)((char*)this + 0xa))--;
            }
        }
        break;
    case 0x32:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.1;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 10.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x33:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.5;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 20.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x34:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.8;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x35:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.1;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 10.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x36:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.5;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 20.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x37:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.8;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x38:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.1;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 10.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x39:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.5;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 20.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x3a:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
            *(double*)((char*)this + 0x30) = (2.0 - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) / 10000.0) * -1.8;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)((char*)this + 0x28) < 0.0) * 0.2) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x3b:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            if (*(double*)((char*)this + 0x38) < -2.0) {
                *(double*)((char*)this + 0x38) = -2.0;
            } else if (*(double*)((char*)this + 0x38) > -0.5) {
                *(double*)((char*)this + 0x38) = -0.5;
            }
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3c:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            if (*(double*)((char*)this + 0x38) < -4.0) {
                *(double*)((char*)this + 0x38) = -4.0;
            } else if (*(double*)((char*)this + 0x38) > -0.5) {
                *(double*)((char*)this + 0x38) = -0.5;
            }
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3d:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            if (*(double*)((char*)this + 0x38) < -6.0) {
                *(double*)((char*)this + 0x38) = -6.0;
            } else if (*(double*)((char*)this + 0x38) > -0.5) {
                *(double*)((char*)this + 0x38) = -0.5;
            }
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3e:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x3f:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x40:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) > 0 && (char)CPlayer::Unk40ff70() != 0) {
            *(short*)((char*)this + 8) = 0x46;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            if (*(double*)((char*)this + 0x38) < -2.0) {
                *(double*)((char*)this + 0x38) = -2.0;
            } else if (*(double*)((char*)this + 0x38) > -0.5) {
                *(double*)((char*)this + 0x38) = -0.5;
            }
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x41:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) > 0 && (char)CPlayer::Unk40ff70() != 0) {
            *(short*)((char*)this + 8) = 0x46;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            if (*(double*)((char*)this + 0x38) < -4.0) {
                *(double*)((char*)this + 0x38) = -4.0;
            } else if (*(double*)((char*)this + 0x38) > -0.5) {
                *(double*)((char*)this + 0x38) = -0.5;
            }
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x42:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) > 0 && (char)CPlayer::Unk40ff70() != 0) {
            *(short*)((char*)this + 8) = 0x46;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) * 0.75 + *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x43:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) > 0 && (char)CPlayer::Unk40ff70() != 0) {
            *(short*)((char*)this + 8) = 0x46;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x44:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 1.5;
        }
        *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 3;
        *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
        (*(short*)((char*)this + 0xc))++;
        if ((char)CPlayer::Unk40ff70() != 0) {
            *(short*)((char*)this + 8) = 0x46;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x45:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 1.5;
        }
        *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 3;
        *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x46:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            (*(int*)((char*)this + 0x3138))++;
            *(short*)((char*)this + 0x124) = *(short*)((char*)this + 0x124) + 0x78;
            *(double*)((char*)this + 0x30) = 0.5;
            *(double*)((char*)this + 0x38) = -2.5;
            *(double*)((char*)this + 0x48) = 0.025;
            *((char*)this + 0x2c9) = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x47:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.072;
        }
        if (*(double*)((char*)this + 0x38) <= 0.0) {
            *(short*)((char*)this + 0xa) = 1;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) <= 1) {
            *(short*)((char*)this + 0xa) = 2;
            *(short*)((char*)this + 0xc) = 0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x48:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) * 0.25) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x49:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) * 0.25) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x4a:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) * 0.25) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x4b:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
            *(double*)((char*)this + 0x30) = 2.2;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x48) = 0.0;
        *(double*)((char*)this + 0x40) = 0.06;
        *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0x30) - *(double*)((char*)this + 0x40);
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) * 0.25) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x4c:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
            *(double*)((char*)this + 0x30) = 2.2;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x48) = 0.0;
        *(double*)((char*)this + 0x40) = 0.06;
        *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0x30) - *(double*)((char*)this + 0x40);
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) * 0.25) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x4d:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.6;
        }
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
            *(double*)((char*)this + 0x30) = 2.2;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x28) = 0.0;
        *(double*)((char*)this + 0x48) = 0.0;
        *(double*)((char*)this + 0x40) = 0.06;
        *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0x30) - *(double*)((char*)this + 0x40);
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = (1.0 - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) * 0.25) * *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x51:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1f3;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            Vf9(&l50);
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.032;
        }
        *(double*)((char*)this + 0x30) += 0.02;
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                (*(short*)((char*)this + 0xa))--;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) == 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x52:
        if (*((char*)this + 0x120) != 0) {
            *(double*)((char*)this + 0x118) -= 0.8;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            *((char*)this + 0x2c9) = 0x1e;
            *(double*)((char*)this + 0x38) = -0.45;
            *(double*)((char*)this + 0x30) = -0.1;
            (*(int*)((char*)this + 0x3138))++;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
            *(double*)((char*)this + 0x48) = 0.032;
        }
        if (*(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) == 4) {
            *(short*)((char*)this + 0xa) = 5;
            *(short*)((char*)this + 0xc) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 8) {
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x53:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(int*)((char*)this + 0x3144) == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(int*)((char*)this + 0x3144) = 1;
            }
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
            *((char*)this + 0x2c9) = 0x21;
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x30) = -0.8;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
        }
        *(double*)((char*)this + 0x38) += 0.04;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 1;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 1) {
            *(double*)((char*)this + 0x30) += 0.01;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -2.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x30) += 0.06;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x54:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(int*)((char*)this + 0x3144) == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(int*)((char*)this + 0x3144) = 1;
            }
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
            *((char*)this + 0x2c9) = 0x21;
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x30) = -0.8;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
        }
        *(double*)((char*)this + 0x38) += 0.04;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 1;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 1) {
            *(double*)((char*)this + 0x30) += 0.01;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -2.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x30) += 0.06;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x55:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(int*)((char*)this + 0x3144) == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(int*)((char*)this + 0x3144) = 1;
            }
            if (*((char*)this + 0x120) != 0) {
                *(double*)((char*)this + 0x118) -= 30.0;
            }
            *((char*)this + 0x2c9) = 0x21;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
        }
        *(double*)((char*)this + 0x38) += 0.04;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x56:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(int*)((char*)this + 0x3144) == 0) {
                l50.type = 0x1f0;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(int*)((char*)this + 0x3144) = 1;
            }
            if (*(int*)((char*)this + 0x3138) == 0) {
                if (*((char*)this + 0x120) != 0) {
                    *(double*)((char*)this + 0x118) -= 30.0;
                }
                *((char*)this + 0x2c9) = 0x21;
                *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0xc0);
                *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0xc8);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
                (*(int*)((char*)this + 0x3138))++;
            }
        }
        *(double*)((char*)this + 0x38) += 0.06;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            if (*(int*)((char*)this + 0x12c) != 0) {
                *(short*)((char*)this + 8) = 0x61;
                Vf0();
            } else {
                *(short*)((char*)this + 8) = 0x62;
                Vf0();
            }
        }
        break;
    case 0x57:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1ef;
            l50.x = 60.0;
            l50.y = 40.0;
            l50.unk24 = 1;
            l50.unk18 = 1;
            l50.unk20 = 0;
            l50.unk21 = 0;
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x60:
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8 - 1) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x61:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 7;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x63;
                Vf0();
            }
        }
        break;
    case 0x62:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 7;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x63;
                Vf0();
            }
        }
        break;
    case 0x63:
        (*(short*)((char*)this + 0xc))++;
        *((char*)this + 0x158) = 0;
        if (*(int*)((char*)this + 0x108) > 0 && *(WORD*)((char*)this + 0xc) > 0x63 && *(WORD*)((char*)this + 0xa) == 0) {
            *(short*)((char*)this + 8) = 0x60;
            Vf0();
        }
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x60;
                Vf0();
            }
        }
        break;
    case 0x96:
        if (*((char*)this + 0x189) == 1) {
            *(short*)((char*)this + 8) = 0x99;
        }
        if (*((char*)this + 0x189) != 1) {
            *(short*)((char*)this + 8) = 0x96;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *(double*)((char*)this + 0x30) = -1.5;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x97:
        if (*((char*)this + 0x189) == 1) {
            *(short*)((char*)this + 8) = 0x9a;
        }
        if (*((char*)this + 0x189) != 1) {
            *(short*)((char*)this + 8) = 0x97;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *(double*)((char*)this + 0x30) = -1.8;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x98:
        if (*((char*)this + 0x189) == 1) {
            *(short*)((char*)this + 8) = 0x9b;
        }
        if (*((char*)this + 0x189) != 1) {
            *(short*)((char*)this + 8) = 0x98;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
            *(double*)((char*)this + 0x30) = -2.3;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
            }
        }
        break;
    case 0x99:
        if (*((char*)this + 0x189) == 1) {
            *(short*)((char*)this + 8) = 0x99;
        }
        if (*((char*)this + 0x189) != 1) {
            *(short*)((char*)this + 8) = 0x96;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *(double*)((char*)this + 0x30) = -1.5;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x9a:
        if (*((char*)this + 0x189) == 1) {
            *(short*)((char*)this + 8) = 0x9a;
        }
        if (*((char*)this + 0x189) != 1) {
            *(short*)((char*)this + 8) = 0x97;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *(double*)((char*)this + 0x30) = -1.8;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x9b:
        if (*((char*)this + 0x189) == 1) {
            *(short*)((char*)this + 8) = 0x9b;
        }
        if (*((char*)this + 0x189) != 1) {
            *(short*)((char*)this + 8) = 0x98;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
            *(double*)((char*)this + 0x30) = -2.3;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
        }
        *(double*)((char*)this + 0x38) = 0.0;
        *(double*)((char*)this + 0x30) += 0.06;
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x20) - 20.0 <= 0.0 || *(double*)((char*)this + 0x20) + 20.0 >= 639.0) {
            *(double*)((char*)this + 0xb8) = *(double*)((char*)this + 0x30);
        } else {
            *(double*)((char*)this + 0xb8) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x9c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.6;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *(double*)((char*)this + 0x48) = 0.06;
        }
        *(double*)((char*)this + 0x30) = -1.2;
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0x9d:
        *(double*)((char*)this + 0x30) = 1.0;
        *(double*)((char*)this + 0x48) = 0.045;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.3;
            l50.type = 8;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        } else {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0x9e:
        *(double*)((char*)this + 0x30) = -1.0;
        *(double*)((char*)this + 0x48) = 0.045;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.3;
            l50.type = 8;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        } else {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 0xa1:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            l50.type = 9;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x3e;
            (*(int*)((char*)this + 0x3138))++;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
                *(double*)((char*)this + 0x48) = 0.035;
            }
        }
        break;
    case 0xa2:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x48) = 0.025;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            l50.type = 9;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x3e;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            (*(int*)((char*)this + 0x3138))++;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
            Vf0();
            *(double*)((char*)this + 0x28) = 0.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0xa3:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk4109d0(3);
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 1.0;
        }
        *((char*)this + 0x158) = 1;
        (*(short*)((char*)this + 0xc))++;
        (*(int*)((char*)this + 0x3138))++;
        (*(int*)((char*)this + 0x313c))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*((char*)this + 0x188) == *((char*)this + 0x50) && *(int*)((char*)this + 0x313c) >= 0x78) {
            *(short*)((char*)this + 8) = 0xb2;
            Vf0();
        }
        if (*((char*)this + 0x188) != *((char*)this + 0x50) && *(int*)((char*)this + 0x3138) >= 0x3c) {
            *(short*)((char*)this + 8) = 0xb2;
            Vf0();
        }
        break;
    case 0xa4:
        CPlayer::Unk4109d0(2);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 0 && *(WORD*)((char*)this + 0xa) < 3) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) >= 0.0 && *(int*)((char*)this + 0x3138) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            (*(int*)((char*)this + 0x3138))++;
            *((char*)this + 0x2c9) = 9;
            *(short*)((char*)this + 0xa) = 3;
            *(short*)((char*)this + 0xc) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
                *(double*)((char*)this + 0x30) = -1.7;
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x48) = 0.04;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xa5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            *(double*)((char*)this + 0x30) = 1.3;
            CPlayer::Unk4109d0(3);
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            *((char*)this + 0x2c9) = 0x11;
        }
        (*(short*)((char*)this + 0xc))++;
        (*(int*)((char*)this + 0x3138))++;
        (*(int*)((char*)this + 0x313c))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*((char*)this + 0x188) == *((char*)this + 0x50) && *(int*)((char*)this + 0x313c) >= 0x78) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = 1.3;
            *(double*)((char*)this + 0x48) = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            }
        }
        if (*((char*)this + 0x188) != *((char*)this + 0x50) && *(int*)((char*)this + 0x3138) >= 0x27) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = 1.3;
            *(double*)((char*)this + 0x48) = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            }
        }
        break;
    case 0xa6:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            *(double*)((char*)this + 0x30) = -1.3;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            CPlayer::Unk4109d0(3);
            *((char*)this + 0x2c9) = 0x11;
        }
        (*(short*)((char*)this + 0xc))++;
        (*(int*)((char*)this + 0x3138))++;
        (*(int*)((char*)this + 0x313c))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        if (*((char*)this + 0x188) == -*((char*)this + 0x50) && *(int*)((char*)this + 0x313c) >= 0x78) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = -0.9;
            *(double*)((char*)this + 0x48) = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            }
        }
        if (*((char*)this + 0x188) != -*((char*)this + 0x50) && *(int*)((char*)this + 0x3138) >= 0x30) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = -0.9;
            *(double*)((char*)this + 0x48) = 0.03;
            if (CPlayer::Unk40e630() != 0) {
                *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            }
        }
        break;
    case 0xa7:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            if (*((char*)this + 0x120) == 1) {
                *(double*)((char*)this + 0x178) = *(double*)((char*)this + 0x118) * 5.0 + *(double*)((char*)this + 0x178);
            }
            *(double*)((char*)this + 0x118) = 0.0;
            *(short*)((char*)this + 0x14c) = 0x5a;
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x12;
            l50.type = 1;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 4;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xa8:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            *(short*)((char*)this + 0x14e) = 0;
            *(double*)((char*)this + 0xb8) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            l50.type = 8;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xa9:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            *(short*)((char*)this + 0x14e) = 0;
            *(double*)((char*)this + 0xb8) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            l50.type = 8;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == x8) {
                CPlayer::Unk40e630();
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0xaa:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(int*)((char*)this + 0x3138) = (int)(*(double*)((char*)this + 0x30) * 100.0);
            *(int*)((char*)this + 0x313c) = (int)(*(double*)((char*)this + 0x38) * 100.0);
            if (*(double*)((char*)this + 0x48) == 0.0) {
                *(double*)((char*)this + 0x48) = 0.035;
            }
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0x14e) = 0;
            *(double*)((char*)this + 0xb8) = 0.0;
            *(short*)((char*)this + 0x14c) = 0x3c;
        }
        if (*(short*)((char*)this + 0x14c) == 0 && *(int*)((char*)this + 0x3140) == 0) {
            (*(int*)((char*)this + 0x3140))++;
            *(double*)((char*)this + 0x30) = *(int*)((char*)this + 0x3138) * 0.01;
            *(double*)((char*)this + 0x38) = *(int*)((char*)this + 0x313c) * 0.01;
        }
        if (*(short*)((char*)this + 0x14c) == 0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xa9;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xab:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(int*)((char*)this + 0x3138) = (int)(*(double*)((char*)this + 0x30) * 100.0);
            *(int*)((char*)this + 0x313c) = (int)(*(double*)((char*)this + 0x38) * 100.0);
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            if (*((char*)this + 0x120) == 1) {
                *(double*)((char*)this + 0x178) = *(double*)((char*)this + 0x118) * 5.0 + *(double*)((char*)this + 0x178);
            }
            *(double*)((char*)this + 0x118) = 0.0;
            *(short*)((char*)this + 0x14c) = 0x5a;
            CPlayer::Unk410b10(0xb0, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x12;
            l50.type = 1;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                *(double*)((char*)this + 0x30) = *(int*)((char*)this + 0x3138) * 0.01;
                *(double*)((char*)this + 0x38) = *(int*)((char*)this + 0x313c) * 0.01;
                *(double*)((char*)this + 0x48) = 0.035;
                Vf0();
            }
        }
        break;
    case 0xb2:
        *(double*)((char*)this + 0x30) -= 0.03;
        *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0x30);
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                break;
            }
        }
        break;
    case 0xb4:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk4109d0(2);
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 0xa) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xa;
            *((char*)this + 0x2c9) = 9;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)((char*)this + 0x30) = -0.5;
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x48) = 0.028;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
            }
        }
        break;
    case 0xc8:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.03;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xc9:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.03;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 4) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                if (*((char*)this + 0x189) != 1) {
                    *(short*)((char*)this + 8) = 7;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xca:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.03;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcb:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.06;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcc:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.03;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcd:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.03;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xd;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 4) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xce:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.03;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcf:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) == 0) {
            (*((char*)this + 0x15a))++;
            *(short*)((char*)this + 8) = 0xe;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 0xf;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 0x10;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xd0:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) == 0) {
            (*((char*)this + 0x15a))++;
            *(short*)((char*)this + 8) = 0xe;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 0xf;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 0x10;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xd;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xd1:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) == 0) {
            (*((char*)this + 0x15a))++;
            *(short*)((char*)this + 8) = 0xe;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 0xf;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 0x10;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) += 0.035;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)((char*)this + 0x30) = 1.0;
                *(double*)((char*)this + 0x38) = -1.3;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd3:
        if (*(BYTE*)((char*)this + 0x158) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        if (*(double*)((char*)this + 0x30) > 0.0 && *(BYTE*)((char*)this + 0x158) == 1) {
            *(double*)((char*)this + 0x30) -= 0.06;
        } else {
            *(double*)((char*)this + 0x30) = 0.0;
            *((char*)this + 0x158) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
                *((char*)this + 0x2c9) = 0x14;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd4:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
            *(double*)((char*)this + 0x30) = *(double*)((char*)this + 0x30) / 2.0;
            *(double*)((char*)this + 0x48) = 0.07;
        }
        if (*(int*)((char*)this + 0x168) > 1) {
            *(short*)((char*)this + 8) = 0xd5;
            Vf0();
            CPlayer::Unk40f1e0();
            break;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk2c = 7;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 7;
            *(short*)((char*)this + 8) = 0xd6;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0xd5:
        *(double*)((char*)this + 0x48) = 0.042;
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -1.0;
            *(double*)((char*)this + 0x38) = -2.4;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xd6:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk2c = 7;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xdc:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x168) == 3) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0xb8) = 0.0;
            Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)((char*)this + 8) = 0xdd;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x24);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2e);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 2 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xdd:
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1e + *(double*)((char*)this + 0x20);
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6c;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0xd + *(double*)((char*)this + 0x20);
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6c;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                if ((char)CPlayer::Unk40ff70() != 0) {
                    *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 5 + *(double*)((char*)this + 0x20);
                }
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 5;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x34;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*(*(char**)*(char**)((char*)this + 0x78) + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *((char*)this + 0x50) = -*((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xe6:
        CPlayer::Unk4109d0(3);
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) -= 0.02;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xe7:
        CPlayer::Unk4109d0(3);
        *((char*)this + 0x158) = 0;
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) == 3) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        *(double*)((char*)this + 0x30) -= 0.045;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.side = *((char*)this + 0x50) == -1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xe8:
        CPlayer::Unk4109d0(3);
        *((char*)this + 0x158) = 0;
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) == 3) {
            *(short*)((char*)this + 8) = 4;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(short*)((char*)this + 8) = 6;
            }
            *(int*)((char*)this + 0x168) = 0;
            Vf0();
            break;
        }
        *(double*)((char*)this + 0x30) -= 0.045;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.side = *((char*)this + 0x50) == -1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xe9:
        CPlayer::Unk4109d0(3);
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) -= 0.02;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0xea:
        CPlayer::Unk4109d0(3);
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) -= 0.045;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.side = *((char*)this + 0x50) == -1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0xeb:
        CPlayer::Unk4109d0(3);
        *((char*)this + 0x158) = 0;
        *(double*)((char*)this + 0x30) -= 0.045;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) += 2.0;
            l50.type = 0x1f;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.side = *((char*)this + 0x50) == -1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0xf8:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x128) = 1;
            CPlayer::Unk40f1e0();
            Vf0();
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) << 5));
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x39);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0xa) = 0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0xf9;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1d + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 73.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 1 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95)) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0xd1;
                *(short*)((char*)this + 0xa) = 2;
            }
        }
        break;
    case 0xf9:
        *(short*)((char*)this + 0x13e) = 2;
        if (*(WORD*)((char*)this + 0xa) < 6) {
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk4105a0(0x47e, 500.0);
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
        }
        if (*(WORD*)((char*)this + 0xa) > 1 && *(WORD*)((char*)this + 0xa) < 4) {
            *(double*)((char*)this + 0x38) += 0.05;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x11 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) + 11.0;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                CPlayer::Unk40f1e0();
                *(double*)((char*)this + 0x28) = 0.0;
                *(short*)((char*)this + 0xa) = 4;
                *(short*)((char*)this + 0xc) = 0;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 6;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                l50.type = 0;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 9);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) + 4);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk2c = 2;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                break;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 6 && *(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) += 0.035;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                CPlayer::Unk40f1e0();
                *(double*)((char*)this + 0x28) = 0.0;
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 0x10;
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 22.0;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x27 + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *((char*)this + 0x50) = -*((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(double*)((char*)this + 0x30) = -1.5;
                *(double*)((char*)this + 0x38) = -1.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
            }
        }
        break;
    case 0xfa:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x168) > 0 && *(int*)((char*)this + 0x3158) == 0) {
                    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 0x1f4) {
                        *(int*)((char*)this + 0x3158) = 1;
                    } else {
                        *(int*)((char*)this + 0x3158) = 2;
                    }
                }
                Vf0();
            }
        }
        break;
    case 0xfb:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x168) > 0 && *(int*)((char*)this + 0x3158) == 0) {
                    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 0x1f4) {
                        *(int*)((char*)this + 0x3158) = 1;
                    } else {
                        *(int*)((char*)this + 0x3158) = 2;
                    }
                }
                Vf0();
            }
        }
        break;
    case 0xfc:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(short*)((char*)this + 0x16c) = 2;
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            *(int*)((char*)this + 0x3138) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3138) > 0 && *(int*)((char*)this + 0x3158) == 0) {
                    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 0x1f4) {
                        *(int*)((char*)this + 0x3158) = 1;
                    } else {
                        *(int*)((char*)this + 0x3158) = 2;
                    }
                }
                Vf0();
            }
        }
        break;
    case 0xfd:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 6;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x10 || *(WORD*)((char*)this + 0xa) == 0x13) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                l50.type = 0x1f;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x28);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                *(double*)((char*)this + 0x30) = 3.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x168) == 0) {
                *(short*)((char*)this + 0xa) = 0x16;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xfe:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 4;
        }
        if ((*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xc || *(WORD*)((char*)this + 0xa) == 0xf) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xc || *(WORD*)((char*)this + 0xa) == 0xf) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xff:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x10 || *(WORD*)((char*)this + 0xa) == 0x13 || *(WORD*)((char*)this + 0xa) == 0x16 || *(WORD*)((char*)this + 0xa) == 0x19 || *(WORD*)((char*)this + 0xa) == 0x1c || *(WORD*)((char*)this + 0xa) == 0x1f) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                l50.type = 0x1f;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x28);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                *(double*)((char*)this + 0x30) = 3.2;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                *(int*)((char*)this + 0x168) = 0;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x168) == 0) {
                *(short*)((char*)this + 0xa) = 0x1f;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x100:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 7 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x50) = -*((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
                l50.type = 0x1f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x194;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
                *(short*)((char*)this + 8) = 0x11a;
                Vf0();
            }
        }
        break;
    case 0x101:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 7 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
                l50.type = 0x1f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x194;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
                *(short*)((char*)this + 8) = 0x11a;
                Vf0();
            }
        }
        break;
    case 0x102:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 7 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-90.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
                l50.type = 0x1f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x193;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
                *(short*)((char*)this + 8) = 0x11a;
                Vf0();
            }
        }
        break;
    case 0x103:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 5 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(0.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
                l50.type = 0x195;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x11b;
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 0x104:
        if (*(WORD*)((char*)this + 0xa) > 3 && *(WORD*)((char*)this + 0xa) < 6 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0x11b;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(45.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
                l50.type = 0x196;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x11a;
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 0x105:
        if (*(WORD*)((char*)this + 0xa) > 3 && *(WORD*)((char*)this + 0xa) < 6 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0x11b;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(90.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x14;
                l50.type = 0x197;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x11a;
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 0x106:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-90.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
                l50.type = 0x193;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 9 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10b;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x107:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
                l50.type = 0x194;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 9 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10b;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x108:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(0.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
                l50.type = 0x195;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 9 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10b;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x109:
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0x10b;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(45.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
                l50.type = 0x196;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10b;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x10a:
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0x10b;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 5;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(90.0, 2.2);
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
                l50.type = 0x197;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10b;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x10b:
        if (*(int*)((char*)this + 0x3140) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            if (*(double*)((char*)this + 0x38) < 0.0) {
                *(double*)((char*)this + 0x38) *= 0.75;
            }
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(int*)((char*)this + 0x313c) == 0 && *(WORD*)((char*)this + 0xa) < 5 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 7) {
            *(double*)((char*)this + 0x38) += 0.035;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 7;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.05;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
                CPlayer::Unk40e630();
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x10c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 1;
            l50.type = 0x190;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) << 6));
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            l50.unk0 = 1;
            Vf9(&l50);
            *(int*)((char*)this + 0x3148) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
            }
        }
        break;
    case 0x10d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 1;
            l50.type = 0x191;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) << 6));
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            l50.unk0 = 1;
            Vf9(&l50);
            *(int*)((char*)this + 0x3148) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x10e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 2;
            l50.type = 0x192;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            l50.unk0 = 1;
            Vf9(&l50);
            *(int*)((char*)this + 0x3148) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x10f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x198;
            if (*(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 150.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -150.0) {
                l50.x = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20);
            } else {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + 0x20)) {
                    l50.x = *(double*)((char*)this + 0x20) + 150.0;
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + 0x20)) {
                    l50.x = *(double*)((char*)this + 0x20) - 150.0;
                }
            }
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            l50.unk0 = 1;
            Vf9(&l50);
            *(int*)((char*)this + 0x314c) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
            *((char*)this + 0x2c8) = 3;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x110:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x198;
            if (*(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > 150.0 || *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < -150.0) {
                l50.x = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20);
            } else {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + 0x20)) {
                    l50.x = *(double*)((char*)this + 0x20) + 150.0;
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + 0x20)) {
                    l50.x = *(double*)((char*)this + 0x20) - 150.0;
                }
            }
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            l50.unk0 = 1;
            Vf9(&l50);
            *(int*)((char*)this + 0x314c) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
            *((char*)this + 0x2c8) = 3;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x111:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                l50.type = 0x1b5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 5;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
                Vf0();
            }
        }
        break;
    case 0x112:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.04500000178813934;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 5;
                *(double*)((char*)this + 0x30) = 2.5;
                l50.type = 0x1b5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
                Vf0();
            }
        }
        break;
    case 0x113:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(short*)((char*)this + 0x16c) = 1;
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)((char*)this + 0x30) = 1.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            *(int*)((char*)this + 0x3138) = 1;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.02500000037252903;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 5;
                l50.type = 0x1bc;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(short*)((char*)this + 0x16c) = 1;
                *(int*)((char*)this + 0x168) = 0;
                *((char*)this + 0x2c8) = 5;
                l50.type = 0x1b5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
                Vf0();
            }
        }
        break;
    case 0x114:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 4;
                l50.type = 0x1b6;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
                Vf0();
            }
        }
        break;
    case 0x115:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.04500000178813934;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 4;
                l50.type = 0x1b6;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1ba;
                l50.unk0 = 1;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x5a);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
                Vf0();
            }
        }
        break;
    case 0x116:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(short*)((char*)this + 0x16c) = 1;
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            *(int*)((char*)this + 0x3138) = 1;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.02500000037252903;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 4;
                l50.type = 0x1bd;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(short*)((char*)this + 0x16c) = 1;
                *(int*)((char*)this + 0x168) = 0;
                *((char*)this + 0x2c8) = 4;
                l50.type = 0x1b6;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1b8;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
                Vf0();
            }
        }
        break;
    case 0x117:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x118:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.04500000178813934;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 0;
                *(double*)((char*)this + 0x30) = 2.5;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x119:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(short*)((char*)this + 0x16c) = 2;
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            *(int*)((char*)this + 0x3138) = 1;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.02500000037252903;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *((char*)this + 0x2c8) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x11a:
        if (*(int*)((char*)this + 0x3140) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            if (*(double*)((char*)this + 0x38) < 0.0) {
                *(double*)((char*)this + 0x38) *= 0.75;
            }
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(int*)((char*)this + 0x313c) == 0 && *(WORD*)((char*)this + 0xa) < 5 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 7) {
            *(double*)((char*)this + 0x38) += 0.035;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 7;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.05;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x11b:
        if (*(int*)((char*)this + 0x3140) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            if (*(double*)((char*)this + 0x38) < 0.0) {
                *(double*)((char*)this + 0x38) *= 0.75;
            }
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(int*)((char*)this + 0x313c) == 0 && *(WORD*)((char*)this + 0xa) < 5 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x106;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x107;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x108;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x10a;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    (*(int*)((char*)this + 0x313c))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x109;
                    (*(int*)((char*)this + 0x313c))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 7) {
            *(double*)((char*)this + 0x38) += 0.035;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 7;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.05;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x12c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 0x63;
            *(int*)((char*)this + 0x3150) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(int*)((char*)this + 0x168) == 3 && *(int*)((char*)this + 0x3150) == 0) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xb4;
            *(short*)((char*)this + 0x14a) = 0x5a;
            (*(int*)((char*)this + 0x3150))++;
        }
        if (*(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(WORD*)((char*)this + 0xa) < 0xa) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x37;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x10 || *(WORD*)((char*)this + 0xa) == 0x13 || *(WORD*)((char*)this + 0xa) == 0x16 || *(WORD*)((char*)this + 0xa) == 0x19 || *(WORD*)((char*)this + 0xa) == 0x1c || *(WORD*)((char*)this + 0xa) == 0x1f) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                l50.type = 0x1f;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x28);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                *(double*)((char*)this + 0x30) = 3.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x168) != 3) {
                *(short*)((char*)this + 0xa) = 0x22;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = 0xb;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1f && *(int*)((char*)this + 0x3140) < 3) {
                *(short*)((char*)this + 0xa) = 0x16;
                (*(int*)((char*)this + 0x3140))++;
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8 || *(WORD*)((char*)this + 0xa) == 0x28) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x12d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 0x63;
            *(int*)((char*)this + 0x3150) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.04;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(int*)((char*)this + 0x168) == 3 && *(int*)((char*)this + 0x3150) == 0) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xb4;
            *(short*)((char*)this + 0x14a) = 0x5a;
            (*(int*)((char*)this + 0x3150))++;
        }
        if (*(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(WORD*)((char*)this + 0xa) < 0xa) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x37;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x15 && *(WORD*)((char*)this + 0xa) < 0x1f && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0xa) {
            l50.type = 0x19a;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x6e) - 0x14) * *((char*)this + 0x50));
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - (WORD)CPlayer::Unk4108a0(0, 0x5a));
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x10 || *(WORD*)((char*)this + 0xa) == 0x13 || *(WORD*)((char*)this + 0xa) == 0x16 || *(WORD*)((char*)this + 0xa) == 0x19 || *(WORD*)((char*)this + 0xa) == 0x1c || *(WORD*)((char*)this + 0xa) == 0x1f) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                l50.type = 0x1f;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x28);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                *(double*)((char*)this + 0x30) = 4.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x168) != 3) {
                *(short*)((char*)this + 0xa) = 0x28;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14 && *(int*)((char*)this + 0x313c) < 3) {
                *(short*)((char*)this + 0xa) = 0xb;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1f && *(int*)((char*)this + 0x3140) < 4) {
                *(short*)((char*)this + 0xa) = 0x16;
                (*(int*)((char*)this + 0x3140))++;
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8 || *(WORD*)((char*)this + 0xa) == 0x28) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x12e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 0x63;
            *(int*)((char*)this + 0x3150) = 0;
            *((char*)this + 0x2c9) = 0x25;
            CPlayer::Unk40f1e0();
        }
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.045;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(int*)((char*)this + 0x168) == 3 && *(int*)((char*)this + 0x3150) == 0) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xb4;
            *(short*)((char*)this + 0x14a) = 0x5a;
            (*(int*)((char*)this + 0x3150))++;
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0x5d);
        }
        if (*(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(WORD*)((char*)this + 0xa) < 0xa) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x37;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x15 && *(WORD*)((char*)this + 0xa) < 0x1f && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0xa) {
            l50.type = 0x19a;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x6e) - 0x14) * *((char*)this + 0x50));
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - (WORD)CPlayer::Unk4108a0(0, 0x5a));
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 0x15 && *(WORD*)((char*)this + 0xa) < 0x1f && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5) {
            l50.type = 0x19b;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x6e) - 0x14) * *((char*)this + 0x50));
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - (WORD)CPlayer::Unk4108a0(0, 0x5a));
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x10 || *(WORD*)((char*)this + 0xa) == 0x13 || *(WORD*)((char*)this + 0xa) == 0x16 || *(WORD*)((char*)this + 0xa) == 0x19 || *(WORD*)((char*)this + 0xa) == 0x1c || *(WORD*)((char*)this + 0xa) == 0x1f) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                l50.type = 0x1f;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x28);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                *(double*)((char*)this + 0x30) = 5.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x168) != 3) {
                *(short*)((char*)this + 0xa) = 0x28;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14 && *(int*)((char*)this + 0x313c) < 3) {
                *(short*)((char*)this + 0xa) = 0xb;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1f && *(int*)((char*)this + 0x3140) < 8) {
                *(short*)((char*)this + 0xa) = 0x16;
                (*(int*)((char*)this + 0x3140))++;
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8 || *(WORD*)((char*)this + 0xa) == 0x28) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x12f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(int*)((char*)this + 0x3154) = 1;
            *(int*)((char*)this + 0x3150) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(WORD*)((char*)this + 0xa) < 0xb && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 0xa;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                l50.type = 0x1f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb && *(int*)((char*)this + 0x3138) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
                *(short*)((char*)this + 8) = 0x137;
                Vf0();
            }
        }
        break;
    case 0x130:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(int*)((char*)this + 0x3154) = 2;
            *(int*)((char*)this + 0x3150) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(WORD*)((char*)this + 0xa) < 0xb && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                *((char*)this + 0x2c8) = 0xa;
                l50.type = 0x1f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb && *(int*)((char*)this + 0x3138) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
                *(short*)((char*)this + 8) = 0x137;
                Vf0();
            }
        }
        break;
    case 0x131:
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(int*)((char*)this + 0x3154) = 3;
            *(int*)((char*)this + 0x3150) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(WORD*)((char*)this + 0xa) < 0xb && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                *(short*)((char*)this + 0x13c) = 0x2d;
                *((char*)this + 0x2c8) = 0xa;
                l50.type = 0x1f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 0;
                l50.side = *((char*)this + 0x50) == -1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb && *(int*)((char*)this + 0x3138) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
                *(short*)((char*)this + 8) = 0x137;
                Vf0();
            }
        }
        break;
    case 0x132:
        if (*(int*)((char*)this + 0x3154) == 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 6 && *(WORD*)((char*)this + 0xa) < 9 && *(int*)((char*)this + 0x3150) < *(int*)((char*)this + 0x3154) + 1 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 0xa;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-90.0, 2.2);
                l50.type = 0x19c;
                l50.unk0 = 1;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 9 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x137;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x133:
        if (*(int*)((char*)this + 0x3154) == 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 6 && *(WORD*)((char*)this + 0xa) < 9 && *(int*)((char*)this + 0x3150) < *(int*)((char*)this + 0x3154) + 1 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 0xa;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(-45.0, 2.2);
                l50.type = 0x19e;
                l50.unk0 = 1;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 9 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x137;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x134:
        if (*(int*)((char*)this + 0x3154) == 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 6 && *(WORD*)((char*)this + 0xa) < 9 && *(int*)((char*)this + 0x3150) < *(int*)((char*)this + 0x3154) + 1 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 0xa;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(0.0, 2.2);
                l50.type = 0x19d;
                l50.unk0 = 1;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 9 && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x137;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x135:
        if (*(int*)((char*)this + 0x3154) == 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0x137;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0xa && *(int*)((char*)this + 0x3150) < *(int*)((char*)this + 0x3154) + 1 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 0xa;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(45.0, 2.2);
                l50.type = 0x19f;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x137;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x136:
        if (*(int*)((char*)this + 0x3154) == 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0x137;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0xa && *(int*)((char*)this + 0x3150) < *(int*)((char*)this + 0x3154) + 1 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
                *((char*)this + 0x2c8) = 0xa;
                *(short*)((char*)this + 0x16c) = 1;
                ((CShiori*)((char*)this + 8))->Unk434010(90.0, 2.2);
                l50.type = 0x1a0;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk20 = 2;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 0) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 4) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x137;
                *(short*)((char*)this + 0xa) = 0;
                (*(int*)((char*)this + 0x313c))++;
            }
        }
        break;
    case 0x137:
        if (*(int*)((char*)this + 0x3154) == 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(int*)((char*)this + 0x3140) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            if (*(double*)((char*)this + 0x38) < 0.0) {
                *(double*)((char*)this + 0x38) *= 0.75;
            }
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(int*)((char*)this + 0x3150) < *(int*)((char*)this + 0x3154) + 1 && *(WORD*)((char*)this + 0xa) < 5 && (*((char*)this + 0x18a) == 1 || *((char*)this + 0x18b) == 1 || *((char*)this + 0x18c) == 1 || *((char*)this + 0x18d) == 1)) {
            if (*((char*)this + 0x189) == -1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x132;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x133;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
            }
            if (*((char*)this + 0x189) == 0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x134;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
            if (*((char*)this + 0x189) == 1) {
                if (*((char*)this + 0x188) == 0) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x136;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    *(short*)((char*)this + 8) = 0x135;
                    (*(int*)((char*)this + 0x3150))++;
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 7) {
            *(double*)((char*)this + 0x38) += 0.035;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 7;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.05;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                Vf0();
                CPlayer::Unk40e630();
                if (*(int*)((char*)this + 0x3158) == 1) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x138:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x43);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *((char*)this + 0x2c8) = 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1ad;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                if (*(int*)((char*)this + 0x3138) > 8) {
                    l50.type = 0x1a5;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    break;
                }
                if (*(int*)((char*)this + 0x190) > 0) {
                    (*(int*)((char*)this + 0x3138))++;
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *((char*)this + 0x2c8) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                l50.type = 0x1a2;
                if (*(int*)((char*)this + 0x3138) > 8) {
                    l50.type = 0x1ae;
                }
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x68);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
                if (*(int*)((char*)this + 0x313c) == 1) {
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
                }
                if (*(int*)((char*)this + 0x313c) == 2) {
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                }
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x313c) < 6) {
                (*(int*)((char*)this + 0x313c))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x139:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x43);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(short*)((char*)this + 0x13c) = 0xf;
                *((char*)this + 0x2c8) = 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1ad;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                if (*(int*)((char*)this + 0x3138) > 8) {
                    l50.type = 0x1a5;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    break;
                }
                if (*(int*)((char*)this + 0x194) > 0) {
                    (*(int*)((char*)this + 0x3138))++;
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *((char*)this + 0x2c8) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                l50.type = 0x1a3;
                if (*(int*)((char*)this + 0x3138) > 8) {
                    l50.type = 0x1af;
                }
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x68);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
                if (*(int*)((char*)this + 0x313c) == 1) {
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
                }
                if (*(int*)((char*)this + 0x313c) == 2) {
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                }
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x313c) < 6) {
                (*(int*)((char*)this + 0x313c))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x13a:
        if (*(WORD*)((char*)this + 0xa) > 2) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x43);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(short*)((char*)this + 0x13c) = 0x1e;
                *((char*)this + 0x2c8) = 6;
                l50.type = 0x1a1;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1ad;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                if (*(int*)((char*)this + 0x3138) > 8) {
                    l50.type = 0x1a5;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x94);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    break;
                }
                if (*(int*)((char*)this + 0x198) > 0) {
                    (*(int*)((char*)this + 0x3138))++;
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *((char*)this + 0x2c8) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                l50.type = 0x1a4;
                if (*(int*)((char*)this + 0x3138) > 8) {
                    l50.type = 0x1b0;
                }
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x68);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
                if (*(int*)((char*)this + 0x313c) == 1) {
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
                }
                if (*(int*)((char*)this + 0x313c) == 2) {
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                }
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x313c) < 6) {
                (*(int*)((char*)this + 0x313c))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x13b:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3140) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x1f);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x61);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(WORD*)((char*)this + 0xa) > 9 && *(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) += 0.02;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                CPlayer::Unk40f1e0();
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 0x10;
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *((char*)this + 0x2c8) = 9;
                *(double*)((char*)this + 0x30) = -1.3;
                *(double*)((char*)this + 0x38) = -0.8;
                l50.type = 0x1a6;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x13c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3140) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x1f);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x61);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(WORD*)((char*)this + 0xa) > 9 && *(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) += 0.02;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                CPlayer::Unk40f1e0();
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 0x10;
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *((char*)this + 0x2c8) = 9;
                *(double*)((char*)this + 0x30) = -1.3;
                *(double*)((char*)this + 0x38) = -0.8;
                l50.type = 0x1a8;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xe && *(int*)((char*)this + 0x313c) < 2) {
                *((char*)this + 0x2c8) = 9;
                (*(int*)((char*)this + 0x313c))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                if (*(int*)((char*)this + 0x313c) == 1) {
                    l50.type = 0x1b1;
                }
                if (*(int*)((char*)this + 0x313c) == 2) {
                    l50.type = 0x1a7;
                }
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x13d:
        if (*(WORD*)((char*)this + 0xa) > 2) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(3);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *((char*)this + 0x158) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3140) == 0) {
            *((char*)this + 0x158) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x1f);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x61);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
            CPlayer::Unk40f1e0();
            (*(int*)((char*)this + 0x3140))++;
        }
        if (*(WORD*)((char*)this + 0xa) > 9 && *(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) += 0.02;
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                CPlayer::Unk40f1e0();
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 0x10;
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *((char*)this + 0x2c8) = 9;
                *(double*)((char*)this + 0x30) = -1.3;
                *(double*)((char*)this + 0x38) = -0.8;
                l50.type = 0x1ac;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xe && *(int*)((char*)this + 0x313c) < 4) {
                *((char*)this + 0x2c8) = 9;
                (*(int*)((char*)this + 0x313c))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                if (*(int*)((char*)this + 0x313c) == 1) {
                    l50.type = 0x1ab;
                }
                if (*(int*)((char*)this + 0x313c) == 2) {
                    l50.type = 0x1b2;
                }
                if (*(int*)((char*)this + 0x313c) == 3) {
                    l50.type = 0x1aa;
                }
                if (*(int*)((char*)this + 0x313c) == 4) {
                    l50.type = 0x1a9;
                }
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x1a5;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x20);
                l50.unk20 = 2;
                l50.unk0 = 1;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                if (*(int*)((char*)this + 0x3158) == 2) {
                    *(int*)((char*)this + 0x3158) = 0;
                }
            }
        }
        break;
    case 0x13e:
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk410a80(0x32, 3);
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xd);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x34);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
            l50.type = 0x47;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x1b4;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xd);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x34);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            l50.unk30 = 1;
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 0xb;
            CPlayer::Unk410a10(5, 0);
            *(int*)((char*)this + 0x3158) = 3;
            *(int*)((char*)this + 0x3168) = 0x1194;
            l50.type = 0x1b3;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 5);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2d);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x1ad;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 5);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x1ad;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x2d);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x1ad;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x23);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xa && *(int*)((char*)this + 0x3138) < 5) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
    }
}

CMishio::CMishio(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "mishio");
    *(short*)((char*)this + 0x18) = 0x517;
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(int*)((char*)this + 0x3158) = 0;
    *(int*)((char*)this + 0x315c) = 0;
    *(int*)((char*)this + 0x3160) = 0;
    *(int*)((char*)this + 0x3164) = 0;
    *(int*)((char*)this + 0x3168) = 0;
    *(int*)((char*)this + 0x316c) = 0;
    *(int*)((char*)this + 0x3170) = 0;
    *(short*)((char*)this + 0x2ad0) = -4;
    *(short*)((char*)this + 0x2af8) = -0x39;
    *(short*)((char*)this + 0x2ad2) = 0x12;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x15;
    *(short*)((char*)this + 0x2afc) = -0xc;
    *(short*)((char*)this + 0x2ad6) = 0x12;
    *(short*)((char*)this + 0x2afe) = -0xf;
    *(short*)((char*)this + 0x2ad8) = 0x26;
    *(short*)((char*)this + 0x2b00) = -0x27;
    *((char*)this + 0x30f4) = 7;
    *((char*)this + 0x30f5) = 3;
    *((char*)this + 0x30ff) = 0xf;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3274) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3374) = 0;
    }
}

void CMishio::Vf12()
{
    int v4;

    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(int*)((char*)this + 0x3158) = 0;
    *(int*)((char*)this + 0x315c) = 0;
    *(int*)((char*)this + 0x3160) = 0;
    *(int*)((char*)this + 0x3164) = 0;
    *(int*)((char*)this + 0x3168) = 0;
    *(int*)((char*)this + 0x316c) = 0;
    *(int*)((char*)this + 0x3170) = 0;
    *(short*)((char*)this + 0x2ad0) = -4;
    *(short*)((char*)this + 0x2af8) = -0x39;
    *(short*)((char*)this + 0x2ad2) = 0x12;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x15;
    *(short*)((char*)this + 0x2afc) = -0xc;
    *(short*)((char*)this + 0x2ad6) = 0x12;
    *(short*)((char*)this + 0x2afe) = -0xf;
    *(short*)((char*)this + 0x2ad8) = 0x26;
    *(short*)((char*)this + 0x2b00) = -0x27;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3274) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3374) = 0;
    }
    CPlayer::Vf12();
}

void CMishio::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CMishio::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3174) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3274) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3374) = 0;
    CPlayer::Vf10(p1);
}

void CMishio::Vf3()
{
    CPlayer::Unk40e740();
}

void CMishio::Vf4()
{
    if (*(WORD*)((char*)this + 8) < 0xc8) {
        *((char*)this + 0x1a8) = 0;
    }
    if (*(BYTE*)((char*)this + 0x1aa) <= 0) {
        *((char*)this + 0x1a9) = 0;
    } else {
        (*((char*)this + 0x1aa))--;
    }
    if (*(BYTE*)((char*)this + 0x1a9) == 0) {
        *((char*)this + 0x1aa) = 0;
    }
    if (*(short*)((char*)this + 0x262) == 0x34 && (*(double*)((char*)this + 0x118) >= 500.0 && *(int*)((char*)this + 0x168) > 1 || *((char*)this + 0x120) > 0 && *(int*)((char*)this + 0x168) > 1 && *(int*)((char*)this + 0x168) != 6) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x538)) {
        Vf0();
        CPlayer::Unk40f170();
        *(short*)((char*)this + 8) = 0xa7;
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(short*)((char*)this + 8) = 0xab;
        }
        return;
    }
    if (*(int*)((char*)this + 0x15c) < 2) {
        if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x62 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x168) != 6 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9f0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13e;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0x7a && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9d0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13a;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x7a || *(short*)((char*)this + 0x262) == 0x79) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9c8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x139;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x78 || *(short*)((char*)this + 0x262) == 0x79 || *(short*)((char*)this + 0x262) == 0x7a) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9c0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x138;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x988)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x131;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x70 || *(short*)((char*)this + 0x262) == 0x6f) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x980)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x130;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x978)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12f;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) < 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13d;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x66 || *(short*)((char*)this + 0x262) == 0x65) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) < 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13c;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) < 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13b;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12e;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x66 || *(short*)((char*)this + 0x262) == 0x65) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12d;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12c;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(int*)((char*)this + 0x314c) == 0 && *(short*)((char*)this + 0x262) == 0x33 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x880)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x110;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(int*)((char*)this + 0x314c) == 0 && *(short*)((char*)this + 0x262) == 0x32 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x878)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10f;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(int*)((char*)this + 0x3148) == 0 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && *(short*)((char*)this + 0x262) == 0x2a && *(double*)((char*)this + 0x28) == 0.0 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0 || *(double*)((char*)this + 0x28) == 0.0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x870)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10e;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(int*)((char*)this + 0x3148) == 0 && (*(short*)((char*)this + 0x262) == 0x29 || *(short*)((char*)this + 0x262) == 0x2a) && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x868)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10d;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *(int*)((char*)this + 0x3148) == 0 && *(short*)((char*)this + 0x262) == 0x28 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10c;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x16 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e0)) {
            Vf0();
            CPlayer::Unk40f170();
            if (*(int*)((char*)this + 0x3158) == 0) {
                *(short*)((char*)this + 8) = 0xfc;
            }
            if (*(int*)((char*)this + 0x3158) == 1) {
                *(short*)((char*)this + 8) = 0x113;
            }
            if (*(int*)((char*)this + 0x3158) == 2) {
                *(short*)((char*)this + 8) = 0x116;
            }
            if (*(int*)((char*)this + 0x3158) == 3) {
                *(short*)((char*)this + 8) = 0x119;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d8)) {
            Vf0();
            CPlayer::Unk40f170();
            if (*(int*)((char*)this + 0x3158) == 0) {
                *(short*)((char*)this + 8) = 0xfb;
            }
            if (*(int*)((char*)this + 0x3158) == 1) {
                *(short*)((char*)this + 8) = 0x112;
            }
            if (*(int*)((char*)this + 0x3158) == 2) {
                *(short*)((char*)this + 8) = 0x115;
            }
            if (*(int*)((char*)this + 0x3158) == 3) {
                *(short*)((char*)this + 8) = 0x117;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0)) {
            Vf0();
            CPlayer::Unk40f170();
            if (*(int*)((char*)this + 0x3158) == 0) {
                *(short*)((char*)this + 8) = 0xfa;
            }
            if (*(int*)((char*)this + 0x3158) == 1) {
                *(short*)((char*)this + 8) = 0x111;
            }
            if (*(int*)((char*)this + 0x3158) == 2) {
                *(short*)((char*)this + 8) = 0x114;
            }
            if (*(int*)((char*)this + 0x3158) == 3) {
                *(short*)((char*)this + 8) = 0x117;
            }
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0x20 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x105;
            }
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x104;
            }
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x103;
            }
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xff;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && (*(short*)((char*)this + 0x262) == 0xb || *(short*)((char*)this + 0x262) == 0xc) && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfd;
            return;
        }
        if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(WORD*)((char*)this + 8) != 0xfe && *(short*)((char*)this + 0x262) == 0xa && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfe;
            return;
        }
    }
    if (*(int*)((char*)this + 0x15c) < 1 && (*(short*)((char*)this + 0x262) == 0 || *(short*)((char*)this + 0x262) == 1)) {
        if (*(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x159) < 1) {
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) < 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == (1 - (*(short*)((char*)this + 0x262) << 1)) * -1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x528) && *(WORD*)((char*)this + 8) != 0xaa && *(double*)((char*)this + 0x28) < -40.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa5) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa5;
                CPlayer::Unk40e630();
                (*((char*)this + 0x159))++;
                (*((char*)this + 0x15a))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) > 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 - (*(short*)((char*)this + 0x262) << 1)) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x530) && *(WORD*)((char*)this + 8) != 0xaa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa6) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa6;
                CPlayer::Unk40e630();
                (*((char*)this + 0x159))++;
                (*((char*)this + 0x15a))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
        }
        if (*(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0) {
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) < 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == (1 - (*(short*)((char*)this + 0x262) << 1)) * -1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x518) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa3) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa3;
                CPlayer::Unk40e630();
                (*((char*)this + 0x158))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) > 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 - (*(short*)((char*)this + 0x262) << 1)) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x520) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa4) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa4;
                CPlayer::Unk40e630();
                *((char*)this + 0x1a8) = 0;
                return;
            }
        }
    }
    if (*(int*)((char*)this + 0x15c) < 3 && *(short*)((char*)this + 0x262) == 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x15a) < 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x70) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
        Vf0();
        CPlayer::Unk40f170();
        (*((char*)this + 0x15a))++;
        *(short*)((char*)this + 8) = 0xe;
        if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
            *(short*)((char*)this + 8) = 0xf;
        }
        if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
            *(short*)((char*)this + 8) = 0x10;
        }
        return;
    }
    if (*((char*)this + 0x18a) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x10) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x10) != 0) {
        if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe6;
            if (*((char*)this + 0x189) == 1) {
                *(short*)((char*)this + 8) = 0xe9;
            }
            return;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x678) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xcf;
            }
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x660) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xcc;
            return;
        }
        if ((*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x640) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xc8;
            return;
        }
    }
    if (*((char*)this + 0x18b) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x20) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x20) != 0) {
        if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe7;
            if (*((char*)this + 0x189) == 1) {
                *(short*)((char*)this + 8) = 0xea;
            }
            return;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x680) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd0;
            }
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x668) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xcd;
            return;
        }
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if ((*(int*)((char*)this + 0x3158) == 2 || *(int*)((char*)this + 0x3158) == 3) && *((char*)this + 0x188) == *((char*)this + 0x50) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x690) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd2;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x648) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -90.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 90.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xc9;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x650) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xca;
                return;
            }
        }
    }
    if (*((char*)this + 0x18c) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x40) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x40) != 0) {
        if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe8;
            if (*((char*)this + 0x189) == 1) {
                *(short*)((char*)this + 8) = 0xeb;
            }
            return;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50) && *((char*)this + 0x189) == 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -100.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 100.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7c0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xf8;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x688) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd1;
            }
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x670) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xce;
            return;
        }
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*((char*)this + 0x188) != 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -30.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6e0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xdc;
                return;
            }
            if ((*(int*)((char*)this + 0x3158) == 1 || *(int*)((char*)this + 0x3158) == 3) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x698) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd3;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x658) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xcb;
            }
        }
    }
}

void CMishio::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    (*(int*)((char*)this + 0x3164))++;
    if (*(int*)((char*)this + 0x3164) > 0x1d) {
        *(int*)((char*)this + 0x3164) = 0;
    }
    if (*(int*)((char*)this + 0x3158) == 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x13c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3158) == 1) {
        x1c = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x10) + 0x144) + *(int*)((char*)this + 0x3164) / 6 * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3158) == 2) {
        x1c = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x10) + 0x14c) + *(int*)((char*)this + 0x3164) / 6 * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3158) == 3) {
        x1c = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x10) + 0x154) + *(int*)((char*)this + 0x3164) / 6 * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0xb - x1c.x, 0xc4 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x136 - x1c.width, 0xc4 - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3168) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3168) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, *(int*)((char*)this + 0x3168) * x1c.width / 0x1194, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x3168) * x1c.width / 0x1194, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x3168) * x1c.width / 0x1194, 0x1f - x1c.y, *(int*)((char*)this + 0x3168) * x1c.width / 0x1194, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CMishio::Vf8()
{
    EffectDesc v48;
    CPlayer::Unk413090((EffectDesc*)&v48);
    if (*(int*)((char*)this + 0x3168) > 0 && *(int*)((char*)this + 0x3158) == 3) {
        if (*(WORD*)((char*)this + 8) != 0x13e) {
            (*(int*)((char*)this + 0x3168))--;
        }
        if (*(int*)((char*)this + 0x3168) <= 0) {
            *(int*)((char*)this + 0x3158) = 0;
        }
    }
    if (*(int*)((char*)this + 0x3158) > 0) {
        (*(int*)((char*)this + 0x315c))--;
        if (*(int*)((char*)this + 0x3158) == 3) {
            (*(int*)((char*)this + 0x3160))++;
            if (*(int*)((char*)this + 0x3160) > 0x90) {
                *(int*)((char*)this + 0x3160) = 0;
            }
            if (*(int*)((char*)this + 0x3160) == 0x12) {
                CPlayer::Unk410ac0(0xd1, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x24) {
                CPlayer::Unk410ac0(0xd0, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x36) {
                CPlayer::Unk410ac0(0xcf, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x48) {
                CPlayer::Unk410ac0(0xb1, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x5a) {
                CPlayer::Unk410ac0(0xcf, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x6c) {
                CPlayer::Unk410ac0(0xd0, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x7e) {
                CPlayer::Unk410ac0(0xd1, 0x1b);
            }
            if (*(int*)((char*)this + 0x3160) == 0x90) {
                CPlayer::Unk410ac0(0xd2, 0x1b);
            }
        }
        if (*(int*)((char*)this + 0x315c) <= 0 && (*(WORD*)((char*)this + 8) < 0x32 || *(WORD*)((char*)this + 8) > 0x95)) {
            if (*(int*)((char*)this + 0x3158) == 1) {
                v48.type = 0x22;
            }
            if (*(int*)((char*)this + 0x3158) == 2) {
                v48.type = 0x24;
            }
            if (*(int*)((char*)this + 0x3158) == 3) {
                if ((WORD)CPlayer::Unk4108a0(0, 0x64) <= 0x32) {
                    v48.type = 0x22;
                } else {
                    v48.type = 0x24;
                }
            }
            v48.x = (double)((int)*(double*)((char*)this + 0x20) + (0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28)) * *((char*)this + 0x50));
            v48.y = (double)((int)*(double*)((char*)this + 0x28) - (WORD)CPlayer::Unk4108a0(0, 0x5a));
            v48.unk20 = 2;
            v48.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&v48);
            *(int*)((char*)this + 0x315c) = 2;
        }
    }
}

void CMishio::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CMishio::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260);
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x10) != 0 && x6 == 6) {
            *(short*)((char*)this + 0x262) = 0x62;
            return;
        }
        if ((v5 & 0x40) != 0 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xb0) != 0 && x6 == 4) {
            break;
        }
        if (v5 == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xd0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xd0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xaa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 5;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x69;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x64;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x78;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0xaf;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 8) != 0 && x6 == 1) {
            *(short*)((char*)this + 0x262) = 6;
            return;
        }
        if ((v5 & 8) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x80) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x35;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0 && *(WORD*)((char*)this + 8) == 0x60) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x40) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x34;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x20) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x33;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x10) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x32;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf) == 1 && x6 == 3) {
            *(short*)((char*)this + 0x262) = 1;
            return;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf) == 2 && x6 == 3) {
            *(short*)((char*)this + 0x262) = 0;
            break;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
}

void CMishio::Vf5()
{
    double v10;
    double x8;

    *(short*)((char*)this + 0x262) = 0x63;
    if (*(int*)((char*)this + 0x1a0) > 0) {
        (*(int*)((char*)this + 0x1a0))--;
    }
    if (*(int*)((char*)this + 0x1a4) > 0) {
        (*(int*)((char*)this + 0x1a4))--;
    }
    *((char*)this + 0x188) = 0;
    *((char*)this + 0x189) = 0;
    *((char*)this + 0x18a) = 0;
    *((char*)this + 0x18b) = 0;
    *((char*)this + 0x18c) = 0;
    *((char*)this + 0x18d) = 0;
    *(short*)((char*)this + 0x14e) = 0;
    if ((double)(WORD)CPlayer::Unk4108a0(0, 0x3e8) < 25.0f * *(float*)((char*)this + 0xa8) + (*(double*)((char*)this + 0x28) < 0.0) * 0x1e * *(float*)((char*)this + 0xa8) + (*(int*)((char*)this + 0x3114) == 3) * 0x190 + (*(WORD*)((char*)this + 8) == 0xaa) * 0x12c) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if ((double)(WORD)CPlayer::Unk4108a0(0, 0x7d0) < ((*((char*)this + 0x130) > 0) * 4.0 + 1.0) * 8.0 * *(float*)((char*)this + 0xa8) * ((*(WORD*)((char*)this + 8) > 0x95 && *(WORD*)((char*)this + 8) < 0x9d) * 2 + 1)) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if ((double)(WORD)CPlayer::Unk4108a0(0, 0x3e8) < 4e+01f * *(float*)((char*)this + 0xa8) && *(WORD*)((char*)this + 8) > 0xc7) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if (*(int*)((char*)this + 0x170) == 1 && *(int*)((char*)this + 0x3114) == 2) {
        *(short*)((char*)this + 0x14e) = 0x1e;
        if (*(WORD*)((char*)this + 8) < 0xc8) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0x60) {
        return;
    }
    v10 = (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * *((char*)this + 0x50);
    x8 = fabs(*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28));
    if (*(WORD*)((char*)this + 8) >= 0x32 && *(WORD*)((char*)this + 8) <= 0x96 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
            *(int*)((char*)this + 0x3114) = 3;
        } else {
            *(int*)((char*)this + 0x3114) = 0;
        }
        *((char*)this + 0x188) = 1 - (((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) << 1);
        *((char*)this + 0x18d) = (double)(WORD)CPlayer::Unk4108a0(0, 0xf0) < x8;
        *((char*)this + 0x18d) = (double)(WORD)CPlayer::Unk4108a0(0, 0x140) < v10;
        if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 0xa) < 3 && x8 < 100.0 && v10 < 150.0) {
            *((char*)this + 0x18d) = 0;
        }
        return;
    }
    if ((*(WORD*)((char*)this + 8) >= 4 && *(WORD*)((char*)this + 8) <= 6 || *(WORD*)((char*)this + 8) >= 0xa && *(WORD*)((char*)this + 8) <= 0xc) && *(double*)((char*)this + 0x28) == 0.0) {
        return;
    }
    if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) >= 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x96 && *(WORD*)((char*)this + 8) == 0x108 && *(short*)((char*)this + 0x16c) > 1) {
        return;
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 && *(WORD*)((char*)this + 0xc) < 6) {
        if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0xc8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0xcc && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 < 40.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2.0) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 > 20.0 && v10 < 60.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 80.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2.0) {
                *((char*)this + 0x18a) = 3;
                *((char*)this + 0x189) = 1;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x16;
                return;
            }
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2.0 && v10 < 80.0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && v10 < 150.0 && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
        }
        if (v10 < 220.0) {
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
        }
        if (v10 > 220.0) {
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -40.0 && v10 < 80.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -100.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && v10 < 100.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -100.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && v10 < 120.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18c) = 1;
            *((char*)this + 0x189) = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) == 0.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 4 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
            return;
        }
        if (*(int*)((char*)this + 0x3110) > 0x55) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
            return;
        }
        if (*(int*)((char*)this + 0x3110) > 0x55) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0xfa || *(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0xfc || *(WORD*)((char*)this + 8) == 0x10e || *(WORD*)((char*)this + 8) == 0x10f || *(WORD*)((char*)this + 8) == 0x110)) {
        *(short*)((char*)this + 0x262) = 0x34;
        return;
    }
    if (*(int*)((char*)this + 0x3114) > 0 && *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x9e) {
        *(int*)((char*)this + 0x3114) = 0;
    }
    if (*(int*)((char*)this + 0x3114) == 1 && *(WORD*)((char*)this + 8) < 0xc8) {
        *(int*)((char*)this + 0x3114) = 0;
    }
    if (*(int*)((char*)this + 0x3114) == 2 && *(int*)((char*)this + 0x170) != 1) {
        *(int*)((char*)this + 0x3114) = 0;
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 4) {
        *((char*)this + 0x189) = -1;
        *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
        if (*(WORD*)((char*)this + 8) == 4 || *(WORD*)((char*)this + 8) == 5 || *(WORD*)((char*)this + 8) == 6) {
            *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
            if (*(WORD*)((char*)this + 8) == 0xa5) {
                *(int*)((char*)this + 0x3114) = 0;
            }
            *((char*)this + 0x189) = 0;
            *((char*)this + 0x188) = 0;
            return;
        }
    }
    if (*(int*)((char*)this + 0x3114) == 5 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 6 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 7;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 7 && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18a) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe6) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 8 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 9;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 9 && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18b) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xa && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0xb;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xb && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18c) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe8) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xc && *(WORD*)((char*)this + 8) < 0x32) {
        *((char*)this + 0x18a) = 1;
        *((char*)this + 0x189) = 1;
        if (*(WORD*)((char*)this + 8) == 0xcc) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x168) > 1 && *(short*)((char*)this + 0x14a) == 0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 25.0f && *(int*)((char*)this + 0x3114) != 1 && *(int*)((char*)this + 0x3114) != 2) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(WORD*)((char*)this + 8) == 0xc8) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (v10 < 50.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 125.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3ca) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xc9) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x258 && *(int*)((char*)this + 0x168) == 3) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0xc8) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x1c2 && v10 < 90.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if (v10 > 80.0) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xca) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x258 && v10 < 100.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x1f4 && *(int*)((char*)this + 0x168) == 3 && v10 < 80.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if (v10 > 110.0) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcb) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 90.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1ae && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1ae && *(int*)((char*)this + 0x3110) < 0x21c && *(int*)((char*)this + 0x168) != 3) {
                *(short*)((char*)this + 0x262) = 0x28;
                if (v10 > 120.0) {
                    *(short*)((char*)this + 0x262) = 0x29;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e && *(int*)((char*)this + 0x168) == 3) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcc) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 50.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 135.0 && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if (v10 > 110.0) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    return;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x258 && v10 < 100.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x12c && v10 < 100.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if (v10 > 110.0) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 90.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1ae && *(int*)((char*)this + 0x3110) < 0x21c && *(int*)((char*)this + 0x168) != 3) {
                *(short*)((char*)this + 0x262) = 0x28;
                if (v10 > 120.0) {
                    *(short*)((char*)this + 0x262) = 0x29;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcf) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                return;
            }
            if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                return;
            }
            if (v10 < 125.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 3;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd0) {
            if (*(int*)((char*)this + 0x3110) > 0x14 && *(int*)((char*)this + 0x3110) < 0x3c && *(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x50 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 3;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd1) {
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 3;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xdc && v10 < 90.0 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                *(int*)((char*)this + 0x3114) = 0xc;
                if (v10 > 110.0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xe8) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 90.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1ae && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1ae && *(int*)((char*)this + 0x3110) < 0x21c && *(int*)((char*)this + 0x168) != 3) {
                *(short*)((char*)this + 0x262) = 0x28;
                if (v10 > 120.0) {
                    *(short*)((char*)this + 0x262) = 0x29;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e && *(int*)((char*)this + 0x168) == 3) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
    }
    if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * *(float*)((char*)this + 0xa8)) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(double*)((char*)this + 0x28) == 0.0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63) {
                if (v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 5) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 50.0 && *(int*)((char*)this + 0x3110) < 0x17) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 75.0 && *(int*)((char*)this + 0x3110) < 0x1e) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x28 && *(int*)((char*)this + 0x3110) > 0x1e) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x34 && *(int*)((char*)this + 0x3110) > 0x28 || v10 > 80.0 && v10 < 130.0 && *(int*)((char*)this + 0x3110) < 0x50 && *(int*)((char*)this + 0x3110) > 0x34) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && *(int*)((char*)this + 0x3110) < 0x64 && *(int*)((char*)this + 0x3110) > 0x50) {
                    *(int*)((char*)this + 0x3114) = 8;
                    return;
                }
                if (v10 > 70.0 && v10 < 120.0 && *(int*)((char*)this + 0x3110) < 0x78 && *(int*)((char*)this + 0x3110) > 0x64) {
                    *(int*)((char*)this + 0x3114) = 8;
                    return;
                }
                if (v10 < 90.0 && v10 > 70.0 && *(int*)((char*)this + 0x3110) < 0x82 && *(int*)((char*)this + 0x3110) > 0x78) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && *(int*)((char*)this + 0x3110) < 0x91 && *(int*)((char*)this + 0x3110) > 0x82) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 140.0 && *(int*)((char*)this + 0x3110) < 0x98 && *(int*)((char*)this + 0x3110) > 0x91) {
                    *(int*)((char*)this + 0x3114) = 0xa;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0xa5 && *(int*)((char*)this + 0x3110) > 0x91 && *(double*)((char*)this + 0x118) > 500.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = 0x16;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0xaa && *(int*)((char*)this + 0x3110) > 0xa5 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                    return;
                }
                if (v10 > 200.0 && *(int*)((char*)this + 0x3110) < 0xaa && *(int*)((char*)this + 0x3110) > 0xa5 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x82;
                    return;
                }
                if (v10 > 200.0 && *(int*)((char*)this + 0x3110) < 0xbe && *(int*)((char*)this + 0x3110) > 0xaa) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && *(int*)((char*)this + 0x3110) < 0xd2 && *(int*)((char*)this + 0x3110) > 0xbe) {
                    *(short*)((char*)this + 0x262) = 0x28;
                    return;
                }
                if (v10 > 140.0 && v10 < 180.0 && *(int*)((char*)this + 0x3110) < 0xd2 && *(int*)((char*)this + 0x3110) > 0xbe) {
                    *(short*)((char*)this + 0x262) = 0x29;
                    return;
                }
                if (v10 > 200.0 && v10 < 240.0 && *(int*)((char*)this + 0x3110) < 0xd2 && *(int*)((char*)this + 0x3110) > 0xbe) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0xf && *(short*)((char*)this + 0x148) >= 0x3e8) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                        return;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && *(int*)((char*)this + 0x3110) < 6 && (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0)) {
                        *(short*)((char*)this + 0x262) = 0x16;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 100.0 && *(int*)((char*)this + 0x3110) < 0x23 && *(int*)((char*)this + 0x3110) > 0xa) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 180.0 && x8 > 140.0 && *(int*)((char*)this + 0x3110) < 0x3c && *(int*)((char*)this + 0x3110) > 0x23) {
                        *((char*)this + 0x18c) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 140.0 && x8 > 100.0 && *(int*)((char*)this + 0x3110) < 0x50 && *(int*)((char*)this + 0x3110) > 0x3c) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x6e && *(int*)((char*)this + 0x3110) > 0x50 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                        return;
                    }
                }
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x3114) != 3) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0x32) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0x32 && *(int*)((char*)this + 0x3110) < 0x78) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && *(int*)((char*)this + 0x3110) > 0x78 && *(int*)((char*)this + 0x3110) < 0xaa) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if ((double)(WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && x8 < 90.0 && *(int*)((char*)this + 0x3110) > 0xaa && *(int*)((char*)this + 0x3110) < 0xdc) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 100.0 && *(int*)((char*)this + 0x3110) > 0xf0 && *(int*)((char*)this + 0x3110) < 0x14a && x8 + 40.0 > v10 && x8 - 40.0 < v10) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x28;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0x14 && *(int*)((char*)this + 0x3110) < 0x28) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && *(int*)((char*)this + 0x3110) > 0x28 && *(int*)((char*)this + 0x3110) < 0x32) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if ((double)(WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && x8 < 180.0 && *(int*)((char*)this + 0x3110) > 0xaa && *(int*)((char*)this + 0x3110) < 0xf0) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 3.0f * *(float*)((char*)this + 0xa8)) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        return;
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && v10 > 60.0 && v10 < 140.0 && (double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * *(float*)((char*)this + 0xa8) && *(double*)((char*)this + 0x20) > 120.0 && *(double*)((char*)this + 0x20) < 520.0) {
        *(short*)((char*)this + 0x262) = -((*((char*)this + 0x50) == 1) - 1);
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 2) {
        *(int*)((char*)this + 0x3114) = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((double)(WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
            *(int*)((char*)this + 0x3114) = 3;
        } else {
            *(int*)((char*)this + 0x3114) = 0;
        }
        if (v10 > 180.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 140.0 && *(double*)((char*)this + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32) {
            *((char*)this + 0x188) = *((char*)this + 0x50);
            *((char*)this + 0x189) = -1;
            return;
        }
    }
    if (*(int*)((char*)this + 0x1a0) > 0) {
        if ((char)CPlayer::Unk40ff70() != 0 && *(int*)((char*)this + 0x1a0) > 0xf) {
            *(int*)((char*)this + 0x1a0) = 0xf;
        }
        *((char*)this + 0x188) = 1;
        return;
    }
    if (*(int*)((char*)this + 0x1a4) > 0) {
        if ((char)CPlayer::Unk40ff70() != 0 && *(int*)((char*)this + 0x1a4) > 0xf) {
            *(int*)((char*)this + 0x1a4) = 0xf;
        }
        *((char*)this + 0x188) = -1;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32 && v10 < 120.0) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        } else {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x2d;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        } else {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        }
        return;
    }
    if (*((char*)this + 0x50) == -1) {
        *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        return;
    }
    *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
}

void CMishio::Vf7()
{
    WORD v58;
    WORD v54;
    int v4;

    if (*(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) > 0) {
        return;
    }
    v4 = *(short*)((char*)this + 0x2cc);
    EffectDesc l50;
    while (v4 != *(short*)((char*)this + 0x2ca)) {
        if (*(int*)((char*)this + v4 * 4 + 0x3d0) != 0 && *(short*)((char*)this + v4 * 0x98 + 0x556) == 0 && (*(short*)((char*)this + 0x14c) == 0 || *(short*)((char*)this + 0x14c) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x558) != 0)) {
            v54 = *(short*)(*(char**)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + v4 * 0x98 + 0x4d0) * 8 + 4) + *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) * 0xc);
            v58 = *(BYTE*)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + v4 * 0x98 + 0x4d0) * 8);
            CPlayer::Unk413090((EffectDesc*)&l50);
            switch (*(WORD*)((char*)this + v4 * 0x98 + 0x4d0)) {
            case 0x190:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.5;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x31) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x31;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + 0x3148) = 0;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 0x31) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.06;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.3) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.3;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 700.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -60.0) {
                    Vf10(v4);
                    *(int*)((char*)this + 0x3148) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x31 && *(int*)((char*)this + v4 * 4 + 0x3174) < 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                        (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x31) {
                        *(int*)((char*)this + 0x3148) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x191:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.2;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 0x31) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.02;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.3) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.3;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x31) {
                    (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                    if (*(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x31;
                        *(int*)((char*)this + 0x3148) = 0;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 700.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -60.0) {
                    Vf10(v4);
                    *(int*)((char*)this + 0x3148) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) > 0x1e) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x31 && *(int*)((char*)this + v4 * 4 + 0x3174) < 7) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                        (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x31) {
                        *(int*)((char*)this + 0x3148) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x192:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.0025;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 700.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -60.0) {
                    Vf10(v4);
                    *(int*)((char*)this + 0x3148) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) > 0xf) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x193:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                }
                if ((*(WORD*)((char*)this + 8) != 0x102 && *(WORD*)((char*)this + 8) != 0x106 || *(WORD*)((char*)this + 8) == 0x106 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x194:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                }
                if ((*(WORD*)((char*)this + 8) != 0x101 && *(WORD*)((char*)this + 8) != 0x100 && *(WORD*)((char*)this + 8) != 0x107 || *(WORD*)((char*)this + 8) == 0x107 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x195:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                }
                if ((*(WORD*)((char*)this + 8) != 0x103 && *(WORD*)((char*)this + 8) != 0x108 || *(WORD*)((char*)this + 8) == 0x108 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x196:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                }
                if ((*(WORD*)((char*)this + 8) != 0x104 && *(WORD*)((char*)this + 8) != 0x109 || *(WORD*)((char*)this + 8) == 0x109 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x197:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                }
                if ((*(WORD*)((char*)this + 8) != 0x105 && *(WORD*)((char*)this + 8) != 0x10a || *(WORD*)((char*)this + 8) == 0x10a && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x198:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 0x12) {
                    (*(int*)((char*)this + v4 * 4 + 0x3174))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) <= 0) {
                        l50.type = 0x199;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x64));
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x64));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 0xf;
                    }
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10) {
                        *((char*)this + 0x2c8) = 4;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x314c) = 0;
                    }
                }
                break;
            case 0x199:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19a:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19b:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19c:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                    (*(int*)((char*)this + v4 * 4 + 0x3174))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x32) + 0x1e) * *((char*)this + 0x50));
                        l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50 - (WORD)CPlayer::Unk4108a0(0, 0x32));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 0xc;
                    }
                }
                if ((*(WORD*)((char*)this + 8) != 0x132 || *(WORD*)((char*)this + 8) == 0x132 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19e:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                    (*(int*)((char*)this + v4 * 4 + 0x3174))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x32) + 7) * *((char*)this + 0x50));
                        l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x32));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 0xc;
                    }
                }
                if ((*(WORD*)((char*)this + 8) != 0x12f && *(WORD*)((char*)this + 8) != 0x130 && *(WORD*)((char*)this + 8) != 0x131 && *(WORD*)((char*)this + 8) != 0x133 || *(WORD*)((char*)this + 8) == 0x133 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19d:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                    (*(int*)((char*)this + v4 * 4 + 0x3174))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x32) + 0x23) * *((char*)this + 0x50));
                        l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x32));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 0xc;
                    }
                }
                if ((*(WORD*)((char*)this + 8) != 0x134 && *(WORD*)((char*)this + 8) != 0x134 || *(WORD*)((char*)this + 8) == 0x134 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19f:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                    (*(int*)((char*)this + v4 * 4 + 0x3174))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x32) + 0x14) * *((char*)this + 0x50));
                        l50.y = (double)((int)*(double*)((char*)this + 0x28) + 0x19 - (WORD)CPlayer::Unk4108a0(0, 0x32));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 0xc;
                    }
                }
                if ((*(WORD*)((char*)this + 8) != 0x135 && *(WORD*)((char*)this + 8) != 0x135 || *(WORD*)((char*)this + 8) == 0x135 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a0:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                    (*(int*)((char*)this + v4 * 4 + 0x3174))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)((int)*(double*)((char*)this + 0x20) + ((WORD)CPlayer::Unk4108a0(0, 0x32) - 0x1e) * *((char*)this + 0x50));
                        l50.y = (double)((int)*(double*)((char*)this + 0x28) + 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x32));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 0xc;
                    }
                }
                if ((*(WORD*)((char*)this + 8) != 0x136 && *(WORD*)((char*)this + 8) != 0x136 || *(WORD*)((char*)this + 8) == 0x136 && *(WORD*)((char*)this + 0xa) < 6) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a1:
                if (*(WORD*)((char*)this + 8) != 0x138 && *(WORD*)((char*)this + 8) != 0x139 && *(WORD*)((char*)this + 8) != 0x13a && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    break;
                }
                if (*(WORD*)((char*)this + 8) != 0x138 && *(WORD*)((char*)this + 8) != 0x139 && *(WORD*)((char*)this + 8) != 0x13a && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1a;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                if (*(WORD*)((char*)this + 0xa) < 0xa && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 148.0;
                }
                if (*(WORD*)((char*)this + 0xa) == 0xb && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = (*((char*)this + 0x50) << 4) + *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 147.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 0x68 + *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 54.0;
                }
                if (*(WORD*)((char*)this + 0xa) > 0xc && *(WORD*)((char*)this + 0xa) < 0x12 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 0x68 + *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 53.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1a && *(int*)((char*)this + 0x313c) < 4) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        *((char*)this + 0x2c8) = 7;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a2:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a3:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a4:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a5:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a6:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(50.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 2;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a7:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(55.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x1e) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a8:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(45.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x1e) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a9:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(60.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x28) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1aa:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(55.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x28) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ab:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(45.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x28) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ac:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(40.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x28) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ad:
                if (*(WORD*)((char*)this + 8) == 0x138 || *(WORD*)((char*)this + 8) == 0x139 || *(WORD*)((char*)this + 8) == 0x13a) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 148.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ae:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1af:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b0:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b1:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(50.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x1e) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b2:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010(50.0, 2.5);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1d;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x2d && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x2d;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x2d && *(int*)((char*)this + v4 * 4 + 0x3274) < 0x28) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 0xa;
                        (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b3:
                if (*(WORD*)((char*)this + 8) == 0x13e) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 5 + *(double*)((char*)this + 0x20);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 45.0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b4:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b5:
                if (*(WORD*)((char*)this + 8) < 0x111 || *(WORD*)((char*)this + 8) > 0x113) {
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 0x14;
                }
                *(int*)((char*)this + v4 * 4 + 0x3174) += *(int*)((char*)this + v4 * 4 + 0x3274);
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 1) {
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 1;
                }
                ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010((double)(*(int*)((char*)this + v4 * 4 + 0x3174) - 0x78), (double)((WORD)CPlayer::Unk4108a0(0, 0x1e) + 0x3c));
                l50.type = 0x19b;
                l50.x = (int)*(double*)((char*)this + 0x20) + (*(double*)((char*)this + v4 * 0x98 + 0x4f8) + 20.0) * *((char*)this + 0x50);
                l50.y = (int)*(double*)((char*)this + 0x28) - 0x32 + *(double*)((char*)this + v4 * 0x98 + 0x500);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b6:
                if (*(WORD*)((char*)this + 8) < 0x114 || *(WORD*)((char*)this + 8) > 0x116) {
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 0x14;
                }
                *(int*)((char*)this + v4 * 4 + 0x3174) += *(int*)((char*)this + v4 * 4 + 0x3274);
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 1) {
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 1;
                }
                ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010((double)(*(int*)((char*)this + v4 * 4 + 0x3174) - 0x78), (double)((WORD)CPlayer::Unk4108a0(0, 0x1e) + 0x3c));
                l50.type = 0x1b7;
                l50.x = (int)*(double*)((char*)this + 0x20) + (*(double*)((char*)this + v4 * 0x98 + 0x4f8) + 20.0) * *((char*)this + 0x50);
                l50.y = (int)*(double*)((char*)this + 0x28) - 0x32 + *(double*)((char*)this + v4 * 0x98 + 0x500);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b7:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b8:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b9:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ba:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 5) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                            *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        } else {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x1bb:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0xa;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x32 - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 0xa) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                            *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        } else {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x1bc:
                if (*(WORD*)((char*)this + 8) < 0x111 || *(WORD*)((char*)this + 8) > 0x113) {
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 0x14;
                }
                *(int*)((char*)this + v4 * 4 + 0x3174) += *(int*)((char*)this + v4 * 4 + 0x3274);
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 1) {
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 1;
                }
                ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010((double)(0x78 - *(int*)((char*)this + v4 * 4 + 0x3174)), (double)((WORD)CPlayer::Unk4108a0(0, 0x1e) + 0x3c));
                l50.type = 0x19b;
                l50.x = (int)*(double*)((char*)this + 0x20) + (*(double*)((char*)this + v4 * 0x98 + 0x4f8) + 20.0) * *((char*)this + 0x50);
                l50.y = (int)*(double*)((char*)this + 0x28) - 0x32 + *(double*)((char*)this + v4 * 0x98 + 0x500);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bd:
                if (*(WORD*)((char*)this + 8) < 0x114 || *(WORD*)((char*)this + 8) > 0x116) {
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 0x14;
                }
                *(int*)((char*)this + v4 * 4 + 0x3174) += *(int*)((char*)this + v4 * 4 + 0x3274);
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 1) {
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 1;
                }
                ((CShiori*)((char*)this + v4 * 0x98 + 0x4d0))->Unk434010((double)(0x78 - *(int*)((char*)this + v4 * 4 + 0x3174)), (double)((WORD)CPlayer::Unk4108a0(0, 0x1e) + 0x3c));
                l50.type = 0x1b7;
                l50.x = (int)*(double*)((char*)this + 0x20) + (*(double*)((char*)this + v4 * 0x98 + 0x4f8) + 20.0) * *((char*)this + 0x50);
                l50.y = (int)*(double*)((char*)this + 0x28) - 0x32 + *(double*)((char*)this + v4 * 0x98 + 0x500);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ef:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -0.02;
                *(int*)((char*)this + v4 * 0x98 + 0x55c) = 0x7530;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + 8) != 0x57) {
                    Vf10(v4);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f0:
                if (*(WORD*)((char*)this + 8) != 0x53 && *(WORD*)((char*)this + 8) != 0x54 && *(WORD*)((char*)this + 8) != 0x55 && *(WORD*)((char*)this + 8) != 0x56 || *(WORD*)((char*)this + 8) == 0x53 && *(WORD*)((char*)this + 0xa) > 1 || *(WORD*)((char*)this + 8) == 0x54 && *(WORD*)((char*)this + 0xa) > 1) {
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x17);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 4);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - (*((char*)this + 0x50) << 2));
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 6);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0xe);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1a);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)*(double*)((char*)this + 0x20);
                    l50.y = (double)(int)*(double*)((char*)this + 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x19);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x23);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x12);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x14);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 2);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x41);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) << 4));
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    *((char*)this + 0x2c9) = 0x22;
                    Vf10(v4);
                    *(int*)((char*)this + 0x3144) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3274) = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f2:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3274) = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.03;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3274) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f3:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
            }
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}
