// CNayuki::Vf6 (0x451850-0x46108f), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CNayuki's
// .rdata, which starts with its constructor's folder name (nayuki.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CNayuki::Vf6()
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
        *(double*)((char*)this + 0x30) = *(int*)((char*)this + 0x3148) * 0.02 + 0.6;
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
        *(double*)((char*)this + 0x30) = -0.6 - *(int*)((char*)this + 0x3148) * 0.02;
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
            CPlayer::Unk40e630();
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.024;
            *(double*)((char*)this + 0x38) = -2.0;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *(double*)((char*)this + 0x30) = 0.4;
                *((char*)this + 0x158) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
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
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.024;
            *(double*)((char*)this + 0x38) = -2.0;
            *(double*)((char*)this + 0x30) = 0.5;
            if (*(BYTE*)((char*)this + 0x158) == 1) {
                *(double*)((char*)this + 0x30) = 0.7;
                *((char*)this + 0x158) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
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
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            CPlayer::Unk40e630();
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
        }
        break;
    case 6:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.024;
            *(double*)((char*)this + 0x38) = -2.0;
            *(double*)((char*)this + 0x30) = -0.5;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
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
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
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
        CPlayer::Unk40e630();
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
    case 0xe:
        *(double*)((char*)this + 0x48) = 0.024;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.0;
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
        *(double*)((char*)this + 0x48) = 0.024;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.0;
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
        *(double*)((char*)this + 0x48) = 0.024;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -2.0;
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
            *(double*)((char*)this + 0x30) = 0.6;
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
            l50.unk21 = 1;
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
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3148) > 0) {
            (*(int*)((char*)this + 0x3148))--;
        }
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
        if (*(int*)((char*)this + 0x108) > 0 && *(WORD*)((char*)this + 0xc) > 0x63) {
            *(short*)((char*)this + 8) = 0x60;
            Vf0();
        }
        (*(short*)((char*)this + 0xc))++;
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
    case 0x7b:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
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
    case 0x96:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x46);
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
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x48) = 0.025;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            l50.type = 9;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x46);
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
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0xa3:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk4109d0(1);
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) < 0xb && *(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 0xb) {
            *(short*)((char*)this + 0xc) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 0xb;
            *(double*)((char*)this + 0x28) = 0.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x30) = 1.4;
                *(double*)((char*)this + 0x38) = -0.75;
                *(double*)((char*)this + 0x48) = 0.015;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                break;
            }
        }
        break;
    case 0xa4:
        CPlayer::Unk4109d0(2);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) += 0.02;
            *(double*)((char*)this + 0x38) += 0.035;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 0xb) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xb;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(double*)((char*)this + 0x30) = -2.0 - *(int*)((char*)this + 0x3148) * 0.1;
                *(double*)((char*)this + 0x38) = -1.2;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0xa5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            if (*(int*)((char*)this + 0x3148) > 7) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            CPlayer::Unk40f1e0();
            l50.type = 0x190;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x24);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3e);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 0;
            l50.unk20 = 0;
            Vf9(&l50);
        }
        if (*(int*)((char*)this + 0x3138) == 1 && *(WORD*)((char*)this + 0xa) == 0) {
            *(double*)((char*)this + 0x30) = 1.9;
            *(double*)((char*)this + 0x38) = -0.2;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 1;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            Vf0();
            *(short*)((char*)this + 8) = 0xb3;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0xa6:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            if (*(int*)((char*)this + 0x3148) > 4) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            l50.type = 0x190;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x24);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3e);
            l50.unk18 = -*((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 0;
            Vf9(&l50);
        }
        if (*(int*)((char*)this + 0x3138) == 1 && *(WORD*)((char*)this + 0xa) == 0) {
            *(double*)((char*)this + 0x30) = -1.9;
            *(double*)((char*)this + 0x38) = -0.2;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 1;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            Vf0();
            *(short*)((char*)this + 8) = 0xb3;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0xa7:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            if (*(double*)((char*)this + 0x48) == 0.0) {
                *(double*)((char*)this + 0x48) = 0.035;
            }
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
                *(short*)((char*)this + 8) = 9;
                CPlayer::Unk40e630();
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
    case 0xb3:
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
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 0xb) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xb;
            *((char*)this + 0x2c9) = 9;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(double*)((char*)this + 0x30) = -0.5;
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x48) = 0.028;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb) {
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
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
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
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(short*)((char*)this + 0xa) = 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 3) {
                *(short*)((char*)this + 0xa) = 3;
            }
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
    case 0xca:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            if (*(int*)((char*)this + 0x3148) > 5) {
                *(short*)((char*)this + 0x16c) = 1;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 8;
        }
        if (*(WORD*)((char*)this + 0xa) < 0xa && *(WORD*)((char*)this + 0xa) > 5) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            if (*(WORD*)((char*)this + 0xa) < 0xa && *(WORD*)((char*)this + 0xa) > 5) {
                *(short*)((char*)this + 0xa) = 0xa;
                CPlayer::Unk410a10(3, 0);
                l50.type = 3;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 2;
                l50.unk21 = 0;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                *((char*)this + 0x2c9) = 7;
            }
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) >= 0xa) {
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x38) = -1.5;
                *(double*)((char*)this + 0x30) = *(int*)((char*)this + 0x3148) * 0.05 + 1.0;
                *(double*)((char*)this + 0x48) = 0.06;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb) {
                if (*(int*)((char*)this + 0x3148) > 4) {
                    *(short*)((char*)this + 0x16c) = 1;
                } else {
                    *(short*)((char*)this + 0x16c) = 0;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 7 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x3148) > 4 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x3148) > 6) {
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
        if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *((char*)this + 0x2c9) = 0x14;
            if (*(int*)((char*)this + 0x3148) > 5) {
                *(short*)((char*)this + 0x16c) = 1;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            Vf0();
            *(short*)((char*)this + 8) = 0xd;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *((char*)this + 0x2c8) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) < 9) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 8 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xa) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0x28 + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xe) {
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x30) = 0.7;
                *(double*)((char*)this + 0x48) = 0.033;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                (*(short*)((char*)this + 0xa))--;
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
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(short*)((char*)this + 0xa) = 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 4) {
                *(short*)((char*)this + 0xa) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
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
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= 3 && (*(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x3148) > 0 || *(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 1 || *(WORD*)((char*)this + 0xa) == 3 && *(int*)((char*)this + 0x3148) > 3 || *(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3148) > 5)) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
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
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) < *(int*)((char*)this + 0x3148) - 4 && *(WORD*)((char*)this + 0xa) < 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
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
            if (*(WORD*)((char*)this + 0xa) < 2) {
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
            *(short*)((char*)this + 0x16c) = *(int*)((char*)this + 0x3148) / 2 + 2;
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
            if (*(WORD*)((char*)this + 0xa) < 6) {
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
            *(short*)((char*)this + 0x16c) = 3;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) < *(int*)((char*)this + 0x3148) - 3 && *(WORD*)((char*)this + 0xa) < 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
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
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = -1.7;
            *(double*)((char*)this + 0x30) = 0.5;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
                break;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xb) {
            *(double*)((char*)this + 0x28) = 0.0;
            *((char*)this + 0x2c9) = 9;
            *(short*)((char*)this + 0xa) = 0xb;
            *(short*)((char*)this + 0xc) = 0;
            CPlayer::Unk40f1e0();
        }
        break;
    case 0xd3:
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
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
    case 0xd4:
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
            *(double*)((char*)this + 0x38) -= -1.0;
            *(double*)((char*)this + 0x48) = 0.035;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(int*)((char*)this + 0x168) > 1) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(short*)((char*)this + 8) = 0x101;
            *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            *(double*)((char*)this + 0x38) = -2.5;
            *(double*)((char*)this + 0x48) = 0.025;
            break;
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) < 5 && *(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 5;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 7;
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                (*(short*)((char*)this + 0xa))--;
            }
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd5:
        *(double*)((char*)this + 0x48) = 0.04;
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0x61;
            CPlayer::Unk40f1e0();
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
    case 0xd6:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x1e;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 3;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 0xa;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                Vf0();
            }
        }
        break;
    case 0xdc:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x168) == 3) {
            if (*(double*)((char*)this + 0x20) > 600.0) {
                *(double*)((char*)this + 0x20) = 600.0;
            }
            if (*(double*)((char*)this + 0x20) < 40.0) {
                *(double*)((char*)this + 0x20) = 40.0;
            }
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0xb8) = 0.0;
            Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)((char*)this + 8) = 0xdd;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x25);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x16);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
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
    case 0xdd:
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk4105a0(0x3e8, 750.0);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3f;
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = 1.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -2.5;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -50.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xe6:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) == 0) {
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
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xe7:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) == 0) {
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
            *(short*)((char*)this + 0x16c) = *(int*)((char*)this + 0x3148) / 2 + 2;
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
            if (*(WORD*)((char*)this + 0xa) < 6) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xe8:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) == 0) {
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
            *(short*)((char*)this + 0x16c) = 3;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xd;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) < *(int*)((char*)this + 0x3148) - 3 && *(WORD*)((char*)this + 0xa) < 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xf8:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xf9;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x21);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x33);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x21 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 61.0;
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
        if (*(WORD*)((char*)this + 0xa) < 7) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) < 7) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 1) {
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 5) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            Vf0();
            *(short*)((char*)this + 8) = 0xd;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 1) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 66.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x17 + *(double*)((char*)this + 0x20);
        }
        if (*(WORD*)((char*)this + 0xa) == 2) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 69.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x15 + *(double*)((char*)this + 0x20);
        }
        if (*(WORD*)((char*)this + 0xa) == 3) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 73.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x13 + *(double*)((char*)this + 0x20);
        }
        if (*(WORD*)((char*)this + 0xa) == 4) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 74.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x13 + *(double*)((char*)this + 0x20);
        }
        if (*(WORD*)((char*)this + 0xa) == 5) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 71.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x11 + *(double*)((char*)this + 0x20);
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 70.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (*((char*)this + 0x50) << 4) + *(double*)((char*)this + 0x20);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 60.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x25;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3f;
            CPlayer::Unk4105a0(0x514, 500.0);
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -2.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -1.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xb && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.035;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xb) {
                *((char*)this + 0x50) = -*((char*)this + 0x50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0xfa:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 0;
            l50.unk28 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 - (*(WORD*)((char*)this + 0xa) == 4) * *(int*)((char*)this + 0x3148) * 3) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xfb:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x192;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 0;
            l50.unk28 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 - (*(WORD*)((char*)this + 0xa) == 4) * *(int*)((char*)this + 0x3148) * 3) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xfc:
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
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x193;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk28 = 1;
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 - (*(WORD*)((char*)this + 0xa) == 4) * *(int*)((char*)this + 0x3148) * 3) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xfd:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 2;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *((char*)this + 0x2c9) = 0x14;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.2;
                *(double*)((char*)this + 0x38) = -2.5;
                *(double*)((char*)this + 0x48) = 0.03;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x100;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x102;
                }
                Vf0();
            }
        }
        break;
    case 0xfe:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *((char*)this + 0x2c9) = 0x14;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.7;
                *(double*)((char*)this + 0x38) = -1.7;
                l50.type = 0x194;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x102;
                Vf0();
            }
        }
        break;
    case 0x100:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 2.4;
            *(short*)((char*)this + 0x16c) = 1;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && *(int*)((char*)this + 0x313c) == 0) {
            *(double*)((char*)this + 0x30) = -0.7;
            *(double*)((char*)this + 0x38) = -2.0;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 8) = 0x101;
            *((char*)this + 0x2c9) = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            (*(int*)((char*)this + 0x313c))++;
            break;
        }
        if (*(short*)((char*)this + 0x16c) == 0) {
            *(double*)((char*)this + 0x30) = -0.7;
            *(double*)((char*)this + 0x38) = -2.0;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 8) = 0x101;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(double*)((char*)this + 0x28) == 0.0 && *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
        }
        break;
    case 0x101:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        CPlayer::Unk40f170();
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 9;
            }
        }
        break;
    case 0x102:
        *(double*)((char*)this + 0x48) = 0.04;
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0x61;
            CPlayer::Unk40f1e0();
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
    case 0x103:
        CPlayer::Unk40f1e0();
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 4;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa && *(WORD*)((char*)this + 0xc) == 0) {
            (*(int*)((char*)this + 0x3148))++;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 5;
        }
        if (*(int*)((char*)this + 0x3148) > 9) {
            *(int*)((char*)this + 0x3148) = 9;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 7;
            }
        }
        break;
    case 0x104:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 9) {
            *(double*)((char*)this + 0x30) -= 0.025;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            (*(int*)((char*)this + 0x313c))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.8;
                *(double*)((char*)this + 0x38) = -1.9;
                if (*(int*)((char*)this + 0x3148) > 2) {
                    *(double*)((char*)this + 0x30) = 2.1;
                    *(double*)((char*)this + 0x38) = -2.0;
                }
                if (*(int*)((char*)this + 0x3148) > 5) {
                    *(double*)((char*)this + 0x30) = 2.4;
                    *(double*)((char*)this + 0x38) = -2.1;
                }
                if (*(int*)((char*)this + 0x3148) > 8) {
                    *(double*)((char*)this + 0x30) = 3.0;
                    *(double*)((char*)this + 0x38) = -2.2;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                if (*(int*)((char*)this + 0x3148) > 2) {
                    *(short*)((char*)this + 0xa) = 6;
                }
                if (*(int*)((char*)this + 0x3148) > 5) {
                    *(short*)((char*)this + 0xa) = 7;
                }
                if (*(int*)((char*)this + 0x3148) > 8) {
                    *(short*)((char*)this + 0xa) = 8;
                }
                break;
            }
            if (*(WORD*)((char*)this + 0xa) > 5 && *(WORD*)((char*)this + 0xa) < 9) {
                *(short*)((char*)this + 0xa) = 9;
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x48) = 0.035;
                *(double*)((char*)this + 0x30) *= 0.3;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x105:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 3;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 5 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x10;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            (*(int*)((char*)this + 0x313c))++;
            if (*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xd) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.2;
                *(double*)((char*)this + 0x38) = -1.2;
                *(double*)((char*)this + 0x48) = 0.03;
                if (*(int*)((char*)this + 0x3148) > 6) {
                    *(double*)((char*)this + 0x38) = -2.2;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 8 && *(int*)((char*)this + 0x3148) < 5 || *(WORD*)((char*)this + 0xa) == 0xb && *(int*)((char*)this + 0x3148) < 7) {
                *(short*)((char*)this + 0xa) = 0xf;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                if (*(double*)((char*)this + 0x38) < 0.0) {
                    *(double*)((char*)this + 0x38) *= 0.5;
                }
                *(double*)((char*)this + 0x30) *= 0.5;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x106:
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
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = *(int*)((char*)this + 0x3148) + 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x10;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            (*(int*)((char*)this + 0x313c))++;
            if (*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xd) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 0.8;
                *(double*)((char*)this + 0x38) = -1.5;
                *(double*)((char*)this + 0x48) = 0.035;
                *(short*)((char*)this + 0x13c) = *(int*)((char*)this + 0x3148) * 0xc + 0x1e;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 || *(WORD*)((char*)this + 0xa) == 0xb) {
                *(double*)((char*)this + 0x38) = -1.4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = 4;
            }
            if ((*(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 8) && *(int*)((char*)this + 0x3138) > *(int*)((char*)this + 0x3148)) {
                *(short*)((char*)this + 0xa) = 0xc;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 8) {
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf && *(double*)((char*)this + 0x38) < 0.0) {
                *(double*)((char*)this + 0x38) *= 0.5;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x107:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = *(int*)((char*)this + 0x3148) + 6;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf) {
            *(double*)((char*)this + 0x30) -= 0.028;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 0xb) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x30) > 0.0 && *(WORD*)((char*)this + 0xa) > 5 && *(WORD*)((char*)this + 0xa) < 0x10) {
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0xa) = 0x10;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            (*(int*)((char*)this + 0x313c))++;
            if (*(int*)((char*)this + 0x313c) > 2) {
                *(int*)((char*)this + 0x168) = 0;
                *(int*)((char*)this + 0x313c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.8;
                *(double*)((char*)this + 0x38) = -1.7;
                *(double*)((char*)this + 0x48) = 0.035;
                if (*(int*)((char*)this + 0x3138) == 1) {
                    *(double*)((char*)this + 0x30) = 0.6;
                    *(double*)((char*)this + 0x38) = -3.2;
                    *(double*)((char*)this + 0x48) = 0.024;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0xa) = 5;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
            }
        }
        break;
    case 0x108:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) > 9) {
            *(double*)((char*)this + 0x30) -= 0.08;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 6) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= 0x18 && *(int*)((char*)this + 0x3148) > 3 && *(WORD*)((char*)this + 0xa) == 0xb) {
            (*(short*)((char*)this + 0xa))++;
            *(short*)((char*)this + 0xc) = 0;
            *(int*)((char*)this + 0x168) = 0;
        }
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - *(int*)((char*)this + 0x3148) * 3 && *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x3148) > 2 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 2.2;
                if (*(int*)((char*)this + 0x3138) == 1) {
                    *(double*)((char*)this + 0x30) = 3.4;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) == 1 && *(int*)((char*)this + 0x313c) < 4) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x109:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) > 9) {
            *(double*)((char*)this + 0x30) += 0.08;
            if (*(double*)((char*)this + 0x30) > 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 6) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= 0x18 && *(int*)((char*)this + 0x3148) > 3 && *(WORD*)((char*)this + 0xa) == 0xb) {
            (*(short*)((char*)this + 0xa))++;
            *(short*)((char*)this + 0xc) = 0;
            *(int*)((char*)this + 0x168) = 0;
        }
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - *(int*)((char*)this + 0x3148) * 3 && *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x3148) > 2 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = -2.2;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) == 1 && *(int*)((char*)this + 0x313c) < 4) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x10a:
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
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = *(int*)((char*)this + 0x3148) + 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 9) {
            *(double*)((char*)this + 0x30) -= 0.3;
            *(short*)((char*)this + 0x16c) = 1;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 6) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xc) >= l4 - *(int*)((char*)this + 0x3148) * 3 && *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x3148) > 2 || *(WORD*)((char*)this + 0xc) >= l4 - 3 && *(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x3148) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 2.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) == 1 && *(int*)((char*)this + 0x313c) < 4) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x10b:
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
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if (*(WORD*)((char*)this + 0xa) > 9) {
            *(double*)((char*)this + 0x30) -= 0.3;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 6) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 0xb) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 2.8;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x313c) < 2) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) == 1 && *(int*)((char*)this + 0x313c) < 4) {
                *(short*)((char*)this + 0xa) = 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x10c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7) {
            if (*(short*)((char*)this + 0x262) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xa3;
                if (*((char*)this + 0x50) == -1) {
                    *(short*)((char*)this + 8) = 0xa4;
                }
                break;
            }
            if (*(short*)((char*)this + 0x262) == 0) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xa4;
                if (*((char*)this + 0x50) == -1) {
                    *(short*)((char*)this + 8) = 0xa3;
                }
                break;
            }
            if (*(short*)((char*)this + 0x262) == 0xa && *(int*)((char*)this + 0x3148) > 0) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xfa;
                break;
            }
            if (*(short*)((char*)this + 0x262) == 0xb && *(int*)((char*)this + 0x3148) > 0) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xfb;
                break;
            }
            if (*(short*)((char*)this + 0x262) == 0x14 && *(int*)((char*)this + 0x3148) > 0) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x104;
                break;
            }
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x113;
                if (*(int*)((char*)this + 0x3148) > 4) {
                    *(short*)((char*)this + 8) = 0x10d;
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x112;
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x114;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x119;
                }
                break;
            }
            if (*((char*)this + 0x18d) == 1) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0x115;
                    if (*(int*)((char*)this + 0x3148) > 4) {
                        *(short*)((char*)this + 8) = 0x115;
                    }
                    break;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0x116;
                    if (*(int*)((char*)this + 0x3148) > 4) {
                        *(short*)((char*)this + 8) = 0x116;
                    }
                    break;
                }
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x118;
                }
                if (*(int*)((char*)this + 0x3148) == 9) {
                    *(short*)((char*)this + 8) = 0x10c;
                    *(short*)((char*)this + 0xa) = 8;
                }
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            (*(int*)((char*)this + 0x313c))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40f1e0();
                Vf0();
                break;
            }
        }
        break;
    case 0x10d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x30) > 0.0 && *(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8) {
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 8;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 7;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.4;
                *(double*)((char*)this + 0x38) = -2.1;
                *(double*)((char*)this + 0x48) = 0.045;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                CPlayer::Unk40f1e0();
                Vf0();
            }
        }
        break;
    case 0x10e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *((char*)this + 0x2c9) = 0x14;
        }
        if (*(WORD*)((char*)this + 0xa) > 8) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            Vf0();
            *(short*)((char*)this + 8) = 0xd;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *((char*)this + 0x2c8) = 3;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0x28 + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x30) = 0.7;
                *(double*)((char*)this + 0x48) = 0.033;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                (*(short*)((char*)this + 0xa))--;
            }
        }
        break;
    case 0x10f:
        CPlayer::Unk40f1e0();
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 5;
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            (*(int*)((char*)this + 0x3148))++;
        }
        if (*(int*)((char*)this + 0x3148) > 9) {
            *(int*)((char*)this + 0x3148) = 9;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 7;
            }
        }
        break;
    case 0x110:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 1.4;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) -= 0.08;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 3) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x113;
                if (*(int*)((char*)this + 0x3148) > 4) {
                    *(short*)((char*)this + 8) = 0x10d;
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x112;
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x114;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x119;
                }
                break;
            }
            if (*((char*)this + 0x18d) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x118;
                }
                if (*(int*)((char*)this + 0x3148) == 9) {
                    *(short*)((char*)this + 8) = 0x10c;
                    *(short*)((char*)this + 0xa) = 8;
                }
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x313c) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10c;
                CPlayer::Unk40f1e0();
                Vf0();
                *(short*)((char*)this + 0xa) = 8;
                break;
            }
        }
        break;
    case 0x111:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -1.4;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) -= 0.08;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 3) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x113;
                if (*(int*)((char*)this + 0x3148) > 4) {
                    *(short*)((char*)this + 8) = 0x10d;
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x112;
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x114;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x119;
                }
                break;
            }
            if (*((char*)this + 0x18d) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x118;
                }
                if (*(int*)((char*)this + 0x3148) == 9) {
                    *(short*)((char*)this + 8) = 0x10c;
                    *(short*)((char*)this + 0xa) = 8;
                }
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x313c) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10c;
                CPlayer::Unk40f1e0();
                Vf0();
                *(short*)((char*)this + 0xa) = 8;
                break;
            }
        }
        break;
    case 0x112:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 - (*(WORD*)((char*)this + 0xa) == 9) * *(int*)((char*)this + 0x3148) * 3) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
                l50.type = 0x1ac;
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    l50.type = 0x1ad;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    l50.type = 0x1ab;
                }
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
                l50.unk20 = 0;
                l50.unk28 = 1;
                l50.unk21 = 0;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *((char*)this + 0x2c8) = 0;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x113:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x30) > 0.0 && *(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8) {
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 8;
            CPlayer::Unk410a10(3, 0);
            l50.type = 3;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 7;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
                *(double*)((char*)this + 0x30) = 1.4;
                *(double*)((char*)this + 0x38) = -2.1;
                *(double*)((char*)this + 0x48) = 0.045;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                CPlayer::Unk40f1e0();
                Vf0();
            }
        }
        break;
    case 0x114:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *((char*)this + 0x2c9) = 0x14;
        }
        if (*(WORD*)((char*)this + 0xa) > 8) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            Vf0();
            *(short*)((char*)this + 8) = 0xd;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0x27 - *(int*)((char*)this + 0x3148) * 3) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *((char*)this + 0x2c8) = 3;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) < 3) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0x28 + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x38) = -0.7;
                *(double*)((char*)this + 0x30) = 0.7;
                *(double*)((char*)this + 0x48) = 0.033;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                (*(short*)((char*)this + 0xa))--;
            }
        }
        break;
    case 0x115:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 1.4;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) -= 0.08;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 3) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x113;
                if (*(int*)((char*)this + 0x3148) > 4) {
                    *(short*)((char*)this + 8) = 0x10d;
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x112;
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x114;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x119;
                }
                break;
            }
            if (*((char*)this + 0x18d) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x118;
                }
                if (*(int*)((char*)this + 0x3148) == 9) {
                    *(short*)((char*)this + 8) = 0x10c;
                    *(short*)((char*)this + 0xa) = 8;
                }
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x313c) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10c;
                CPlayer::Unk40f1e0();
                Vf0();
                *(short*)((char*)this + 0xa) = 8;
                break;
            }
        }
        break;
    case 0x116:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -1.4;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x40) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) -= 0.08;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if ((*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 3) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x113;
                if (*(int*)((char*)this + 0x3148) > 4) {
                    *(short*)((char*)this + 8) = 0x10d;
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x112;
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x114;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x119;
                }
                break;
            }
            if (*((char*)this + 0x18d) == 1) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0x118;
                }
                if (*(int*)((char*)this + 0x3148) == 9) {
                    *(short*)((char*)this + 8) = 0x10c;
                    *(short*)((char*)this + 0xa) = 8;
                }
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x313c) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0x10c;
                CPlayer::Unk40f1e0();
                Vf0();
                *(short*)((char*)this + 0xa) = 8;
                break;
            }
        }
        break;
    case 0x12c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) >= 2) {
            *(short*)((char*)this + 0xf2) = 0xa;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.unk0 = 1;
            l50.type = 0x196;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.unk28 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == l4 - *(int*)((char*)this + 0x3148) * 6) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x117:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x191;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 0;
            l50.unk28 = 1;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 - (*(WORD*)((char*)this + 0xa) == 4) * *(int*)((char*)this + 0x3148) * 3) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x118:
        CPlayer::Unk40f1e0();
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 4;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
            }
        }
        break;
    case 0x119:
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
                *(short*)((char*)this + 8) = 0;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x12d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) >= 2) {
            *(short*)((char*)this + 0xf2) = 0xa;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.unk0 = 1;
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.unk28 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == l4 - *(int*)((char*)this + 0x3148) * 6) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x12e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.unk0 = 1;
            l50.type = 0x198;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x29);
            l50.unk20 = 0;
            l50.unk21 = 0;
            l50.unk28 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4 || *(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == l4 - *(int*)((char*)this + 0x3148) * 6) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x12f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 7) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            if (*((char*)this + 0x189) == -1) {
                *(double*)((char*)this + 0x38) = -0.5;
            }
            if (*((char*)this + 0x189) == 1) {
                *(double*)((char*)this + 0x38) = 0.5;
            }
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) = 0.5;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) = -0.5;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0xc) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                l50.unk0 = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk20 = 0;
                l50.unk21 = 1;
                Vf9(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                if (*(int*)((char*)this + 0x3138) < 0xe) {
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                    (*(int*)((char*)this + 0x3138))++;
                } else {
                    *(double*)((char*)this + 0x48) = 0.015;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x130:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 7) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            if (*((char*)this + 0x189) == -1) {
                *(double*)((char*)this + 0x38) = -0.65;
            }
            if (*((char*)this + 0x189) == 1) {
                *(double*)((char*)this + 0x38) = 0.65;
            }
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) = 0.65;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) = -0.65;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0xc) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                l50.unk0 = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk20 = 0;
                l50.unk21 = 1;
                Vf9(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                if (*(int*)((char*)this + 0x3138) < 0x14) {
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                    (*(int*)((char*)this + 0x3138))++;
                } else {
                    *(double*)((char*)this + 0x48) = 0.015;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x131:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 7) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            if (*((char*)this + 0x189) == -1) {
                *(double*)((char*)this + 0x38) = -0.8;
            }
            if (*((char*)this + 0x189) == 1) {
                *(double*)((char*)this + 0x38) = 0.8;
            }
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) = 0.8;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) = -0.8;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0xc) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                l50.unk0 = 1;
                l50.type = 0x19d;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                l50.unk18 = *((char*)this + 0x50);
                l50.unk20 = 0;
                l50.unk21 = 1;
                Vf9(&l50);
                l50.type = 0x19e;
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                if (*(int*)((char*)this + 0x3138) < 0x14) {
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                    (*(int*)((char*)this + 0x3138))++;
                } else {
                    *(double*)((char*)this + 0x48) = 0.015;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x132:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xe) {
            *(double*)((char*)this + 0x30) += 0.035;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
            l50.type = 0x47;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xa && *(WORD*)((char*)this + 0xa) < 0xf) {
            CPlayer::Unk410a10(3, 0xa);
        }
        if ((char)CPlayer::Unk40ff70() != 0 && *(WORD*)((char*)this + 0xa) > 0xe && *(double*)((char*)this + 0x30) > 4.0) {
            *(double*)((char*)this + 0x30) = -2.7;
            *(double*)((char*)this + 0x38) = -3.5;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 8) = 0x101;
            Vf0();
            *((char*)this + 0x2c9) = 0x1f;
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            l50.type = 0x19b;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x32);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x19b;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x32);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1f;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = *((char*)this + 0x50) == -1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xf && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1f;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.side = *((char*)this + 0x50) == -1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                if (*(int*)((char*)this + 0x3138) < 0xa) {
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                    (*(int*)((char*)this + 0x3138))++;
                } else {
                    l50.type = 0x34;
                    l50.x = (double)(int)*(double*)((char*)this + 0x20);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x19);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk2c = 0x16;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(double*)((char*)this + 0x30) = 0.5;
                    CPlayer::Unk410a10(0xf, 0xa);
                    l50.unk0 = 1;
                    l50.type = 0x1a1;
                    l50.x = (double)(int)*(double*)((char*)this + 0x20);
                    l50.y = (double)(int)*(double*)((char*)this + 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 0;
                    l50.unk28 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
        }
    }
}
