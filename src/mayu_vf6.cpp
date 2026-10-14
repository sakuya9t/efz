// CMayu::Vf6 (0x5c8580-0x5dddef), the per-state update. It is a file of its own,
// as in the original: its floating-point constants precede the rest of CMayu's
// .rdata, which starts with its constructor's folder name (mayu.cpp).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CMayu::Vf6()
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
        *(double*)((char*)this + 0x30) = 0.9;
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
        *(double*)((char*)this + 0x30) = -0.9;
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
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = -2.8;
            *((char*)this + 0x2c8) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
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
            CPlayer::Unk40e630();
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = -2.8;
            *(double*)((char*)this + 0x30) = 1.0;
            *((char*)this + 0x2c8) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
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
            CPlayer::Unk40e630();
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = -2.8;
            *(double*)((char*)this + 0x30) = -1.0;
            *((char*)this + 0x2c8) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
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
    case 0xa:
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
        *(double*)((char*)this + 0x48) = 0.055;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -3.2;
            *(double*)((char*)this + 0x30) = 0.0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
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
        *(double*)((char*)this + 0x48) = 0.055;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -3.2;
            *(double*)((char*)this + 0x30) = 1.0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
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
        *(double*)((char*)this + 0x48) = 0.055;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = -3.2;
            *(double*)((char*)this + 0x30) = -1.0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
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
        if (*(WORD*)((char*)this + 0xa) < 9) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x38) = -1.8;
                *(double*)((char*)this + 0x48) = 0.05;
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) < 9 && *(WORD*)((char*)this + 0xa) > 4 && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                *(short*)((char*)this + 0xa) = 9;
            }
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
        if (*(int*)((char*)this + 0x108) > 0 && *(WORD*)((char*)this + 0xc) > 0x45 && *(WORD*)((char*)this + 0xa) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
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
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
        }
        break;
    case 0xa3:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(double*)((char*)this + 0x30) -= 0.05;
            if (*(double*)((char*)this + 0x30) < 0.5) {
                *(double*)((char*)this + 0x30) = 0.5;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 2.5;
            *(double*)((char*)this + 0x38) = -1.6;
            *(double*)((char*)this + 0x48) = 0.05;
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.08;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 8) = 0xb2;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *(double*)((char*)this + 0x48) = 0.08;
                    break;
                }
                (*(int*)((char*)this + 0x3138))++;
                if (*(int*)((char*)this + 0x3138) < 7) {
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                    (*(int*)((char*)this + 0x3138))++;
                }
            }
        }
        break;
    case 0xa4:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk4109d0(2);
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 0) {
            *(double*)((char*)this + 0x30) += 0.055;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            Vf0();
            *(short*)((char*)this + 8) = 0xd;
            break;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = -3.5;
                *(double*)((char*)this + 0x38) = -1.5;
                *(double*)((char*)this + 0x48) = 0.05;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
        }
        break;
    case 0xa5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 1.8;
            CPlayer::Unk4109d0(3);
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            if (*(int*)((char*)this + 0x3138) == 0) {
                *((char*)this + 0x2c9) = 0x11;
            }
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
        if (*((char*)this + 0x188) != *((char*)this + 0x50) && *(int*)((char*)this + 0x3138) >= 0x30) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -1.8;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            CPlayer::Unk4109d0(3);
            if (*(int*)((char*)this + 0x3138) == 0) {
                *((char*)this + 0x2c9) = 0x11;
            }
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
            if (*(double*)((char*)this + 0x48) == 0.0) {
                *(double*)((char*)this + 0x48) = 0.035;
            }
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
                if (*(double*)((char*)this + 0x48) == 0.0) {
                    *(double*)((char*)this + 0x48) = 0.035;
                }
                Vf0();
            }
        }
        break;
    case 0xb2:
        *(double*)((char*)this + 0x30) -= 0.08;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
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
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 0xc) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            *((char*)this + 0x2c9) = 9;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = -0.5;
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x48) = 0.028;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
            }
        }
        break;
    case 0xc8:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
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
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
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
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xca:
        *(double*)((char*)this + 0x30) -= 0.02;
        if (*(double*)((char*)this + 0x30) <= 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xf;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 4) {
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
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0x16c) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *((char*)this + 0x2c9) = 0x14;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 6) {
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
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
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
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 3;
                }
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xcd:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.025;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 1.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
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
    case 0xce:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
            *(double*)((char*)this + 0x30) = 3.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x30) -= 0.07;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x30) == 0.0) {
                *(short*)((char*)this + 0x16c) = 0;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *((char*)this + 0x2c9) = 0x14;
                *(short*)((char*)this + 0x16c) = 1;
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
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) < 1) {
            *(short*)((char*)this + 8) = 0xe;
            (*((char*)this + 0x15a))++;
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
                Vf0();
                *(short*)((char*)this + 8) = 9;
            }
        }
        break;
    case 0xd0:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) < 1) {
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
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xd;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x14;
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
    case 0xd1:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) < 1) {
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
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
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
            if (*(WORD*)((char*)this + 0xa) < 4) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
        if (*(double*)((char*)this + 0x30) <= 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 5;
                break;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 4) {
            *(double*)((char*)this + 0x30) -= 0.036;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
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
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(double*)((char*)this + 0x30) = 1.0;
                *(double*)((char*)this + 0x38) = -2.6;
                *(double*)((char*)this + 0x48) = 0.065;
            }
            if (*(WORD*)((char*)this + 0xa) < 4) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xd3:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
    case 0xdc:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(WORD*)((char*)this + 0xa) == 1 && *(int*)((char*)this + 0x168) == 3) {
            CPlayer::Unk40f1e0();
            Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)((char*)this + 8) = 0xdd;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x25);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x30);
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
            if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xdd:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x2ad0) * *((char*)this + 0x50);
            *(double*)((char*)this + 0x28) = *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x2af8) + 0x1e;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3b;
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -2.5;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -1.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x48) = 0.035;
            *(double*)((char*)this + 0x30) = -1.8;
            *(double*)((char*)this + 0x38) = -1.9;
            *(double*)((char*)this + 0x48) = 0.04;
            l50.type = 0;
            l50.unk2c = 2;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2d);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4105a0(0x3e8, 750.0);
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0xe6:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        CPlayer::Unk4109d0(3);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) < 1) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.5;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 5;
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xe9;
            Vf0();
            *(short*)((char*)this + 0xa) = 2;
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
                *(short*)((char*)this + 8) = 0xa;
                Vf0();
            }
        }
        break;
    case 0xe7:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        CPlayer::Unk4109d0(3);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) < 1) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.5;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xd;
            *(short*)((char*)this + 0x16c) = 2;
            *((char*)this + 0x2c9) = 0x14;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xe9;
            Vf0();
            *(short*)((char*)this + 0xa) = 1;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 5) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0xa;
                Vf0();
            }
        }
        break;
    case 0xe8:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        CPlayer::Unk4109d0(3);
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) >= 2 && *(BYTE*)((char*)this + 0x15a) < 1) {
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
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.5;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0xa;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xe9;
            Vf0();
            *(short*)((char*)this + 0xa) = 1;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 4) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0xa;
                Vf0();
            }
        }
        break;
    case 0xe9:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        CPlayer::Unk40e630();
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            *(int*)((char*)this + 0x168) = 3;
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
    case 0xf8:
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x128) = 1;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x16);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x36);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0xa) = 0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 8) = 0xf9;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 2 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95)) {
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
        if (*(WORD*)((char*)this + 0xa) < 0xb) {
            if (*(double*)((char*)this + 0x20) > 6100.0 && *((char*)this + 0x50) == 1) {
                *(double*)((char*)this + 0x20) = 6100.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 30.0 && *((char*)this + 0x50) == -1) {
                *(double*)((char*)this + 0x20) = 30.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xa || *(WORD*)((char*)this + 0xa) > 0xb && *(WORD*)((char*)this + 0xa) < 0xf) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
                if (*(WORD*)((char*)this + 0xa) < 0xa) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
                    *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                    CPlayer::Unk4105a0(0x3e8, 500.0);
                    l50.type = 0;
                    l50.x = (double)(int)*(double*)((char*)this + 0x20);
                    l50.y = (double)(int)*(double*)((char*)this + 0x28);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0xa;
                    *((char*)this + 0x2c9) = 2;
                    break;
                }
                if (*(WORD*)((char*)this + 0xa) == 0xe) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0xf;
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 1) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -70.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 2) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-25.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -65.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 3) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -43.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -29.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 5) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -23.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (23.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -36.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -58.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (14.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -73.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -78.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(double*)((char*)this + 0x30) = -0.8;
                *(double*)((char*)this + 0x38) = -1.0;
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0xfa:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            Vf0();
            *(short*)((char*)this + 8) = 0xfd;
            *(double*)((char*)this + 0x28) = *(short*)((char*)this + 0x2af8) + 0x32;
            *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) + (-*(short*)((char*)this + 0x2ad0) - 0x14) * *((char*)this + 0x50);
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 7);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(int*)((char*)this + 0x3140) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
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
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 1.8;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                *(short*)((char*)this + 0xa) = 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) > 1) {
                *(short*)((char*)this + 0xa) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xfb:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            Vf0();
            *(short*)((char*)this + 8) = 0xfd;
            *(double*)((char*)this + 0x28) = *(short*)((char*)this + 0x2af8) + 0x32;
            *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) + (-*(short*)((char*)this + 0x2ad0) - 0x14) * *((char*)this + 0x50);
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 7);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8 && *(int*)((char*)this + 0x3140) > 0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(int*)((char*)this + 0x3140) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
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
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 2.4;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                *(short*)((char*)this + 0xa) = 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) > 2) {
                *(short*)((char*)this + 0xa) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xfc:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 0;
            CPlayer::Unk40f1e0();
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfe;
            *(double*)((char*)this + 0x28) = *(short*)((char*)this + 0x2af8) + 0x32;
            *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) + (-*(short*)((char*)this + 0x2ad0) - 0x14) * *((char*)this + 0x50);
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 7);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 8) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(int*)((char*)this + 0x3140) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
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
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 1.8;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                *(short*)((char*)this + 0xa) = 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) > 1) {
                *(short*)((char*)this + 0xa) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xfd:
        if (*(WORD*)((char*)this + 0xa) < 3) {
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if ((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() != 0) {
                CPlayer::Unk40f1e0();
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            }
            if ((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() == 0) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (*(short*)((char*)this + 0x2ad0) + 0x14) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 3) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -69.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 3 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 3;
            *(double*)((char*)this + 0x28) = 0.0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3f;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-31.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -33.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            CPlayer::Unk4105a0(0x1f4, 750.0);
            (*(short*)((char*)this + 0x174))--;
            (*(short*)((char*)this + 0xf4))--;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = 0.8;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -3.2;
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = -1.0;
                *(double*)((char*)this + 0x38) = -1.3;
                *(double*)((char*)this + 0x48) = 0.03;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xfe:
        if (*(WORD*)((char*)this + 0xa) < 3) {
            *(double*)((char*)this + 0x30) -= 0.035;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if ((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() != 0) {
                CPlayer::Unk40f1e0();
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            }
            if ((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() == 0) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (*(short*)((char*)this + 0x2ad0) + 0x14) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 3) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -69.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 3 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 3;
            *(double*)((char*)this + 0x28) = 0.0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x43;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-41.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -43.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            CPlayer::Unk4105a0(0x3e8, 800.0);
            (*(short*)((char*)this + 0x174))--;
            (*(short*)((char*)this + 0xf4))--;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -4.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -0.8;
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = -1.0;
                *(double*)((char*)this + 0x38) = -2.1;
                *(double*)((char*)this + 0x48) = 0.025;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xff:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) *= 0.3;
            *(double*)((char*)this + 0x38) *= 0.5;
            *(double*)((char*)this + 0x48) = 0.035;
            *(short*)((char*)this + 0x16c) = 9;
        }
        if ((*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 7) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xa) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x102;
            *(double*)((char*)this + 0x28) = 0.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) >= x8) {
            *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
        }
        break;
    case 0x100:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.5;
            *(double*)((char*)this + 0x38) = 3.0;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x23;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x101;
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
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x101:
        *(double*)((char*)this + 0x30) -= 0.04;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
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
    case 0x102:
        *(double*)((char*)this + 0x30) -= 0.04;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
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
    case 0x103:
        if (*(WORD*)((char*)this + 0xa) > 8 && *(WORD*)((char*)this + 0xa) < 0xf && *(int*)((char*)this + 0x190) > 0) {
            Vf0();
            *(short*)((char*)this + 8) = 0x106;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(WORD*)((char*)this + 0xa) < 0xf && *(int*)((char*)this + 0x194) > 0) {
            Vf0();
            *(short*)((char*)this + 8) = 0x107;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 7) {
            *(double*)((char*)this + 0x30) -= 0.02;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 1;
            *(double*)((char*)this + 0x30) = 3.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3138) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x104:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) > 0xd) {
            *(double*)((char*)this + 0x30) -= 0.03;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(short*)((char*)this + 0x262) == 0xa && *(WORD*)((char*)this + 0xa) > 0xd) {
            Vf0();
            *(short*)((char*)this + 8) = 0x122;
            break;
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(double*)((char*)this + 0x38) > 0.0 && *((char*)this + 0x18a) == 1) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x100;
            break;
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 5 && *(WORD*)((char*)this + 0xa) < 0xa) {
            *(short*)((char*)this + 0xa) = 0xe;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            break;
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 9 && *(WORD*)((char*)this + 0xa) < 0xe) {
            *(short*)((char*)this + 0xa) = 0xe;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 1.2;
                *(double*)((char*)this + 0x38) = -3.3;
                *(double*)((char*)this + 0x48) = 0.055;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xe) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x105:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)((char*)this + 0x28) -= 25.0;
            *(double*)((char*)this + 0x30) = 3.0;
            *(short*)((char*)this + 0x16c) = 1;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) > 9) {
            *(double*)((char*)this + 0x30) -= 0.03;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(int*)((char*)this + 0x168) > 1 && *(WORD*)((char*)this + 0xa) > 1 && *(WORD*)((char*)this + 0xa) < 6) {
            *(short*)((char*)this + 0xa) = 6;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30) * 0.1;
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x48) = 0.036;
            break;
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 5 && *(WORD*)((char*)this + 0xa) < 0xa) {
            *(short*)((char*)this + 0xa) = 0xa;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                if (*(int*)((char*)this + 0x3138) < 4) {
                    *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                    (*(int*)((char*)this + 0x3138))++;
                } else {
                    *(short*)((char*)this + 0xa) = 0xa;
                    *(double*)((char*)this + 0x28) = 0.0;
                    break;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x106:
        *(double*)((char*)this + 0x30) -= 0.035;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xf && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xf;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 7) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(double*)((char*)this + 0x38) = -3.3;
                *(short*)((char*)this + 0x16c) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x107:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) > 0xa) {
            *(double*)((char*)this + 0x30) -= 0.03;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(double*)((char*)this + 0x38) > 0.0 && *((char*)this + 0x18a) == 1) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x100;
            break;
        }
        if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0 && *(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 0xa) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0x102;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 0.8;
                *(double*)((char*)this + 0x38) = -3.1;
                *(double*)((char*)this + 0x48) = 0.055;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
        }
        break;
    case 0x108:
        *(double*)((char*)this + 0x30) -= 0.05;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40f1e0();
            }
        }
        break;
    case 0x109:
        *(double*)((char*)this + 0x30) -= 0.05;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40f1e0();
            }
        }
        break;
    case 0x10a:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            *(double*)((char*)this + 0x30) -= 0.06;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) == 7) {
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)((char*)this + 0x48) = 0.09;
                *(double*)((char*)this + 0x38) = -3.0;
                *(double*)((char*)this + 0x30) = 3.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x10b:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            *(double*)((char*)this + 0x30) -= 0.06;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) == 7) {
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)((char*)this + 0x48) = 0.11;
                *(double*)((char*)this + 0x38) = -4.5;
                *(double*)((char*)this + 0x30) = 4.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x10c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0x16c) = 1;
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            *(double*)((char*)this + 0x30) -= 0.04;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 8 && *(WORD*)((char*)this + 0xa) < 0xd) {
            *(short*)((char*)this + 0xa) = 0xd;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(double*)((char*)this + 0x48) = 0.09;
                *(double*)((char*)this + 0x38) = -4.0;
                *(double*)((char*)this + 0x30) = 2.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
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
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.5;
            *(double*)((char*)this + 0x38) = 3.0;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x23;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x108;
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
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x10e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 2.2;
            *(double*)((char*)this + 0x38) = 2.2;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x23;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x108;
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
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x10f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x28;
            *(short*)((char*)this + 0x16c) = 4;
        }
        if (*(WORD*)((char*)this + 0xa) > 9 && *(WORD*)((char*)this + 0xa) < 0xe) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                CPlayer::Unk40f1e0();
                Vf0();
                *(short*)((char*)this + 0xa) = 0xe;
                break;
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 7) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
                *(double*)((char*)this + 0x28) = 0.0;
                *(double*)((char*)this + 0x38) = 0.0;
                Vf0();
                *(int*)((char*)this + 0x3138) = (int)(*(double*)((char*)this + 0x30) * 100.0);
                *(double*)((char*)this + 0x30) = 0.0;
                *(short*)((char*)this + 0xa) = 7;
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 || *(WORD*)((char*)this + 0xa) == 0xe) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x30) = *(int*)((char*)this + 0x3138) * 0.005;
                *(double*)((char*)this + 0x38) = -0.8;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x110:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 0x13 && *(short*)((char*)this + 0x262) == 0xa) {
            Vf0();
            *(short*)((char*)this + 8) = 0x106;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.03;
            *(double*)((char*)this + 0x38) = -2.0;
            *(double*)((char*)this + 0x30) = -3.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x14) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) += 0.015;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) -= 0.015;
            }
            if (*(double*)((char*)this + 0x30) < -2.5) {
                *(double*)((char*)this + 0x30) = -2.5;
            } else if (*(double*)((char*)this + 0x30) > 2.5) {
                *(double*)((char*)this + 0x30) = 2.5;
            }
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                *(short*)((char*)this + 8) = 0x10d;
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                *(short*)((char*)this + 8) = 0x10e;
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                }
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                }
                break;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc || *(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x14) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x50) == 1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14248) + 0xf;
            }
            if (*((char*)this + 0x50) == -1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14250) - 0xf;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0x14) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 0x14;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            *((char*)this + 0x2c9) = 0x1a;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(double*)((char*)this + 0x30) = 1.5;
                *(double*)((char*)this + 0x38) = -2.5;
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x111:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.03;
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x30) = -3.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x12 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x113;
            *(double*)((char*)this + 0x28) = *(short*)((char*)this + 0x2af8) + 0x32;
            *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) + (-*(short*)((char*)this + 0x2ad0) - 0x14) * *((char*)this + 0x50);
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 7);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc || *(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x50) == 1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14248) + 0xf;
            }
            if (*((char*)this + 0x50) == -1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14250) - 0xf;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 0x14;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            *((char*)this + 0x2c9) = 0x1a;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(double*)((char*)this + 0x30) = 2.2;
                *(double*)((char*)this + 0x38) = -0.5;
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x112:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 0x13 && *(short*)((char*)this + 0x262) == 0xa) {
            Vf0();
            *(short*)((char*)this + 8) = 0x106;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.03;
            *(double*)((char*)this + 0x38) = -2.0;
            *(double*)((char*)this + 0x30) = 3.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x14) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) += 0.015;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) -= 0.015;
            }
            if (*(double*)((char*)this + 0x30) < -2.5) {
                *(double*)((char*)this + 0x30) = -2.5;
            } else if (*(double*)((char*)this + 0x30) > 2.5) {
                *(double*)((char*)this + 0x30) = 2.5;
            }
            if (*((char*)this + 0x18a) == 1) {
                Vf0();
                *(short*)((char*)this + 8) = 0x10d;
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                }
                break;
            }
            if (*((char*)this + 0x18b) == 1) {
                Vf0();
                *(short*)((char*)this + 8) = 0x10e;
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                }
                break;
            }
            if (*((char*)this + 0x18c) == 1) {
                Vf0();
                *(short*)((char*)this + 8) = 0x10f;
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    *((char*)this + 0x50) = -*((char*)this + 0x50);
                }
                break;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc || *(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x14) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x50) == 1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14248) + 0xf;
            }
            if (*((char*)this + 0x50) == -1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14250) - 0xf;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0x14) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 0x14;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *((char*)this + 0x50) = -*((char*)this + 0x50);
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            *((char*)this + 0x2c9) = 0x1a;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(double*)((char*)this + 0x30) = 1.5;
                *(double*)((char*)this + 0x38) = -2.5;
                *(double*)((char*)this + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x113:
        CPlayer::Unk410a40(0x32, 3);
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (23.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -54.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 5) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -70.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-31.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -62.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-34.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -34.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-6.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -3.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-4.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -2.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa && *(WORD*)((char*)this + 0xc) == 0) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20);
            CPlayer::Unk4105a0(0x4b0, 960.0);
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk2c = 2;
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0x13 && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0xd;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0x63) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xc) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(double*)((char*)this + 0x30) = -0.5;
                *(double*)((char*)this + 0x38) = -1.3;
                *(double*)((char*)this + 0x48) = 0.05;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                (*(short*)((char*)this + 0xa))--;
            }
        }
        break;
    case 0x118:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x168) == 3) {
            *(double*)((char*)this + 0x30) *= 0.15;
            *(double*)((char*)this + 0x38) *= 0.15;
            Vf0();
            *(short*)((char*)this + 8) = 0x123;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x30) = 0.7;
                *(double*)((char*)this + 0x38) = 2.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 6;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x119:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x168) == 3) {
            *(double*)((char*)this + 0x30) *= 0.15;
            *(double*)((char*)this + 0x38) *= 0.15;
            Vf0();
            *(short*)((char*)this + 8) = 0x123;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x30) = 2.0;
                *(double*)((char*)this + 0x38) = 2.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 6;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x11a:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            CPlayer::Unk40f1e0();
            if (*((char*)this + 0x120) == 0) {
                *(double*)((char*)this + 0x118) -= 500.0;
            } else {
                *(double*)((char*)this + 0x118) -= 250.0;
            }
            l50.type = 0x21;
            l50.unk2c = 0xb;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            (*(int*)((char*)this + 0x3138))++;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 4) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x168) == 3) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0x16c) = 0x63;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(double*)((char*)this + 0x30) = 2.0;
                *(double*)((char*)this + 0x38) = 2.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 6;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x11b:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        if (*(WORD*)((char*)this + 0xa) == 2 && *(int*)((char*)this + 0x168) == 3) {
            CPlayer::Unk40f1e0();
            Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)((char*)this + 8) = 0x11c;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95)) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x19;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x11c:
        CPlayer::Unk410a80(-0x32, 3);
        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 3;
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) = 1.0;
            *(double*)((char*)this + 0x38) += 0.025;
        }
        if (*(WORD*)((char*)this + 0xa) > 3 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)((char*)this + 8) = 0xd;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x48;
            break;
        }
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 1) {
                *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x2ad0) * *((char*)this + 0x50);
                *(double*)((char*)this + 0x28) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) + *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x2af8) - 20.0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x11d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.5;
            *(double*)((char*)this + 0x38) = 3.0;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x23;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x120;
            break;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x109;
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
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x11e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 2.2;
            *(double*)((char*)this + 0x38) = 2.2;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x23;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x120;
            break;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x109;
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
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x11f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 4.0;
            *(double*)((char*)this + 0x38) = 1.5;
            *(short*)((char*)this + 0x16c) = 1;
            *((char*)this + 0x2c9) = 0x23;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x23;
        }
        if (*(int*)((char*)this + 0x168) > 0) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x120;
            break;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) > 2) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x109;
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
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x120:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = -0.4;
            *(double*)((char*)this + 0x38) = -0.9;
            *(double*)((char*)this + 0x48) = 0.045;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 8) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x121:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.03;
            *(double*)((char*)this + 0x38) = -1.5;
            *(double*)((char*)this + 0x30) = -3.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x12 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc || *(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x50) == 1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14248) + 0xf;
            }
            if (*((char*)this + 0x50) == -1) {
                *(double*)((char*)this + 0x20) = *(int*)(*(char**)((char*)this + 0x7c) + 0x14250) - 0xf;
            }
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xa) = 0x14;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if ((char)CPlayer::Unk40ff70() != 0 && *(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xc) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            *((char*)this + 0x2c9) = 0x1a;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                Vf0();
                CPlayer::Unk40f1e0();
                *(short*)((char*)this + 8) = 0x11f;
                if (*(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 140.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -140.0) {
                    *(short*)((char*)this + 8) = 0x11e;
                }
                if (*(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 70.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -70.0) {
                    *(short*)((char*)this + 8) = 0x11d;
                }
                break;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13) {
                (*(short*)((char*)this + 0xa))--;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x122:
        *(double*)((char*)this + 0x30) -= 0.035;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0xf && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xf;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 7) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(double*)((char*)this + 0x38) = -3.3;
                *(short*)((char*)this + 0x16c) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x123:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40e630();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0x16c) = 5;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xe) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
                *(short*)((char*)this + 0xc) = 0;
                *(short*)((char*)this + 0xa) = 0x16;
                *(double*)((char*)this + 0x28) = 0.0;
                CPlayer::Unk40f1e0();
                break;
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xe) {
                *(double*)((char*)this + 0x30) = 0.5;
                *(double*)((char*)this + 0x38) = 0.0;
                *(double*)((char*)this + 0x48) = 0.045;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x16) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x12c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
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
            *(short*)((char*)this + 0x13c) = 0x7e;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (*(WORD*)((char*)this + 0xa) >= 1) {
            *(short*)((char*)this + 0xf2) = 0xa;
        }
        if ((*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 7) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x10 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(short*)((char*)this + 0x13c) = 9;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                if (*(int*)((char*)this + 0x3138) > 1) {
                    *(short*)((char*)this + 0xa) = 0xc;
                    break;
                }
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
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
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
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
            *(short*)((char*)this + 0x13c) = 0x84;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (*(WORD*)((char*)this + 0xa) >= 1) {
            *(short*)((char*)this + 0xf2) = 0xa;
        }
        if ((*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 7) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xe && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x15 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x14 && *(WORD*)((char*)this + 0xa) < 0x1c) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            *(double*)((char*)this + 0x30) -= 0.04;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0x14 && *(WORD*)((char*)this + 0xa) < 0x1c && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xa) = 0x1c;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(short*)((char*)this + 0x13c) = 0x1e;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                if (*(int*)((char*)this + 0x3138) > 2) {
                    *(short*)((char*)this + 0xa) = 0xc;
                    break;
                }
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3138) < 2) {
                *(short*)((char*)this + 0xa) = 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14) {
                *(double*)((char*)this + 0x48) = 0.06;
                *(double*)((char*)this + 0x38) = -3.0;
                *(double*)((char*)this + 0x30) = 2.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1c) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0xa;
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
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
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
            *(short*)((char*)this + 0x13c) = 0x84;
            CPlayer::Unk410a80(0x32, 0x78);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if ((*(WORD*)((char*)this + 0xa) == 2 || *(WORD*)((char*)this + 0xa) == 7) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xe && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x12 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
            *(double*)((char*)this + 0x30) = 3.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x12 && *(WORD*)((char*)this + 0xa) < 0x17) {
            *(double*)((char*)this + 0x30) -= 0.04;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0x14 && *(WORD*)((char*)this + 0xa) < 0x17 || *(WORD*)((char*)this + 0xa) > 0x1c) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            *(double*)((char*)this + 0x30) -= 0.04;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) == 0x18 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 1.8;
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x20 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(short*)((char*)this + 0x16c) > 0 || *(WORD*)((char*)this + 0xa) < 0x22 && *(WORD*)((char*)this + 0xa) > 0x1b) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 2) {
                *(short*)((char*)this + 0x13c) = 0x3c;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                if (*(int*)((char*)this + 0x3138) > 3) {
                    *(short*)((char*)this + 0xa) = 0xc;
                    break;
                }
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3138) < 3) {
                *(short*)((char*)this + 0xa) = 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1c && *(int*)((char*)this + 0x3138) < 8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x12f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
        if (*(WORD*)((char*)this + 0xa) > 1) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) >= 0 && *(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x131;
            *(double*)((char*)this + 0x28) = *(short*)((char*)this + 0x2af8) + 0x32;
            *(double*)((char*)this + 0x20) = *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) + (-*(short*)((char*)this + 0x2ad0) - 0x14) * *((char*)this + 0x50);
            l50.type = 0;
            l50.x = (double)((int)*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) + *(short*)((char*)this + 0x2ad0));
            l50.y = (double)((int)*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) + *(short*)((char*)this + 0x2af8));
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 7;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) >= 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 1.5;
                *(double*)((char*)this + 0x38) = -2.0;
                *(double*)((char*)this + 0x48) = 0.045;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x130:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        if (*(WORD*)((char*)this + 0xa) >= 0 && *(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x168) == 3) {
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0x132;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x78;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1e + *(double*)((char*)this + 0x20);
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x2c);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 7);
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
            if (*(WORD*)((char*)this + 0xa) == 4 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) >= 0.0) {
                *(short*)((char*)this + 0x16c) = 1;
            } else {
                *(short*)((char*)this + 0x16c) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x131:
        CPlayer::Unk410a40(0x32, 3);
        CPlayer::Unk410a80(0x32, 3);
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) == 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0x7530;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (23.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -52.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 5) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -70.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-31.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -65.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-36.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -32.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-7.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -8.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xa) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-4.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -6.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) > 8 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            CPlayer::Unk40f1e0();
            Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20);
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 8) = 0x133;
            CPlayer::Unk4105a0(0x3e8, 960.0);
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk2c = 2;
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
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(double*)((char*)this + 0x30) = (1 - ((*(double*)((char*)this + 0x20) > 320.0) << 1)) * 0.6 * *((char*)this + 0x50);
                *(double*)((char*)this + 0x38) = -5.0;
                *(double*)((char*)this + 0x48) = 0.06;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
        }
        break;
    case 0x132:
        CPlayer::Unk410a40(0x32, 3);
        CPlayer::Unk410a80(0x32, 3);
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0x131;
                *(short*)((char*)this + 0xa) = 4;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0;
                *(double*)((char*)this + 0x30) = (1 - ((*(double*)((char*)this + 0x20) > 320.0) << 1)) * 0.6 * *((char*)this + 0x50);
                *(double*)((char*)this + 0x38) = -5.0;
                *(double*)((char*)this + 0x48) = 0.06;
            }
        }
        break;
    case 0x133:
        ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk410a80(0x32, 3);
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        *(short*)((char*)this + 0x13e) = 2;
        if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0x63) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xc) = 0;
        }
        if (*(int*)((char*)this + 0x3138) > 0x78 && *(int*)((char*)this + 0x3138) < 0x2d0 && *(WORD*)((char*)this + 0xa) > 5 && *(WORD*)((char*)this + 0xa) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5) {
            l50.type = 0x195;
            l50.x = *(double*)((char*)this + 0x20) + 80.0 - (WORD)CPlayer::Unk4108a0(0, 0xa0);
            l50.y = (double)-(WORD)CPlayer::Unk4108a0(0, 0x32);
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 5) {
            (*(int*)((char*)this + 0x3138))++;
        }
        if (*(int*)((char*)this + 0x3138) == 0x50) {
            l50.type = 0x191;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = -320.0;
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk28 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(int*)((char*)this + 0x3138) == 0x78) {
            l50.type = 0x192;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = -320.0;
            l50.unk20 = 0;
            l50.unk21 = 1;
            l50.unk28 = 1;
            l50.unk18 = *((char*)this + 0x50);
            l50.unk0 = 1;
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xa;
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0x7530;
            CPlayer::Unk4105a0(0x12c, 960.0);
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk2c = 2;
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xf && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x10;
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk4105a0(0x578, 960.0);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0;
            CPlayer::Unk410a10(0xa, 0xa);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x78;
            l50.type = 0;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk2c = 0x16;
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0x14 && *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x15;
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(double*)((char*)this + 0x28) = 0.0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xb && *(int*)((char*)this + 0x3138) > 0x334) {
            *(short*)((char*)this + 0xa) = 0xc;
            *(short*)((char*)this + 0xc) = 0;
            *(double*)((char*)this + 0x38) = -5.0;
            *(double*)((char*)this + 0x48) = 0.06;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x30) = 0.0;
                *(double*)((char*)this + 0x38) = -3.9;
                *(double*)((char*)this + 0x48) = 0.08;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                if (*(int*)((char*)this + 0x3138) <= 0x2da) {
                    *(short*)((char*)this + 0xa) = 6;
                    *(double*)((char*)this + 0x30) = 0.0;
                    *(double*)((char*)this + 0x38) = -3.9;
                    *(double*)((char*)this + 0x48) = 0.08;
                } else {
                    *(short*)((char*)this + 0xa) = 0xb;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12) {
                *(double*)((char*)this + 0x30) = -0.6;
                *(double*)((char*)this + 0x38) = -1.5;
                *(double*)((char*)this + 0x48) = 0.038;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1f && *(int*)((char*)this + 0x313c) < 4) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 0;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x134:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
        if (*(WORD*)((char*)this + 0xa) >= 0 && *(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4) && *(int*)((char*)this + 0x168) == 3) {
            if (*(double*)((char*)this + 0x20) > 580.0) {
                *(double*)((char*)this + 0x20) = 580.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 60.0) {
                *(double*)((char*)this + 0x20) = 60.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
            Vf0();
            *(double*)((char*)this + 0x48) = 0.025;
            *(short*)((char*)this + 8) = 0x137;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x2c);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0x70) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xc && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.025;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if ((*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4) && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 2.0;
                *(double*)((char*)this + 0x38) = -3.2;
                *(double*)((char*)this + 0x48) = 0.035;
                *(short*)((char*)this + 0x13c) = 6;
            }
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x38) *= 0.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x135:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
        if (*(WORD*)((char*)this + 0xa) >= 0 && *(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4) && *(int*)((char*)this + 0x168) == 3) {
            if (*(double*)((char*)this + 0x20) > 580.0) {
                *(double*)((char*)this + 0x20) = 580.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 60.0) {
                *(double*)((char*)this + 0x20) = 60.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
            Vf0();
            *(double*)((char*)this + 0x48) = 0.025;
            *(short*)((char*)this + 8) = 0x138;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x2c);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0x70) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xc && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.025;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if ((*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4) && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 2.0;
                *(double*)((char*)this + 0x38) = -3.2;
                *(double*)((char*)this + 0x48) = 0.035;
                *(short*)((char*)this + 0x13c) = 0xc;
            }
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x38) *= 0.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x136:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            CPlayer::Unk40f1e0();
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
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        if (*(WORD*)((char*)this + 0xa) >= 0 && *(WORD*)((char*)this + 0xa) < 3) {
            CPlayer::Unk410a80(0x32, 3);
        }
        if ((*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4) && *(int*)((char*)this + 0x168) == 3) {
            if (*(double*)((char*)this + 0x20) > 580.0) {
                *(double*)((char*)this + 0x20) = 580.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 60.0) {
                *(double*)((char*)this + 0x20) = 60.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
            Vf0();
            *(double*)((char*)this + 0x48) = 0.025;
            *(short*)((char*)this + 8) = 0x139;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x2c);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 6) {
            *(double*)((char*)this + 0x30) -= 0.025;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 4 && *(WORD*)((char*)this + 0xa) < 0x70) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xc && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0xc;
            break;
        }
        if ((*(WORD*)((char*)this + 0xa) == 3 || *(WORD*)((char*)this + 0xa) == 4) && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(double*)((char*)this + 0x30) = 2.0;
                *(double*)((char*)this + 0x38) = -3.2;
                *(double*)((char*)this + 0x48) = 0.035;
                *(short*)((char*)this + 0x13c) = 0x12;
            }
            if (*(WORD*)((char*)this + 0xa) == 5 && *(int*)((char*)this + 0x3138) < 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(double*)((char*)this + 0x38) *= 0.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                CPlayer::Unk40e630();
                Vf0();
            }
        }
        break;
    case 0x137:
        *(short*)((char*)this + 0x13e) = 2;
        if (*(WORD*)((char*)this + 0xa) < 0xe) {
            if (*(double*)((char*)this + 0x20) > 580.0) {
                *(double*)((char*)this + 0x20) = 580.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 60.0) {
                *(double*)((char*)this + 0x20) = 60.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xd || *(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x12) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
                if (*(WORD*)((char*)this + 0xa) < 0xd) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
                    *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x7e;
                    CPlayer::Unk4105a0(0x92e, 750.0);
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0xd;
                    *((char*)this + 0x2c9) = 0x16;
                    break;
                }
                if (*(WORD*)((char*)this + 0xa) == 0x11) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0x12;
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 0xd) {
            *(double*)((char*)this + 0x30) -= 0.025;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -70.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 5) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-25.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -65.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 6) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -43.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -29.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -23.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (23.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -36.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -58.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xb) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (14.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -73.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -78.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 3;
                *(double*)((char*)this + 0x30) = -1.2;
                *(double*)((char*)this + 0x38) = -2.0;
                *(double*)((char*)this + 0x48) = 0.035;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -1.0;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -1.2;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -2.0;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3b;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x138:
        *(short*)((char*)this + 0x13e) = 2;
        if (*(WORD*)((char*)this + 0xa) < 0x19) {
            if (*(double*)((char*)this + 0x20) > 580.0) {
                *(double*)((char*)this + 0x20) = 580.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 60.0) {
                *(double*)((char*)this + 0x20) = 60.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xd || *(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x19 || *(WORD*)((char*)this + 0xa) > 0x1a && *(WORD*)((char*)this + 0xa) < 0x1e) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
                if (*(WORD*)((char*)this + 0xa) < 0xd) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x96;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
                    *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
                    CPlayer::Unk4105a0(0x3e8, 980.0);
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0x7530;
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0xd;
                    *((char*)this + 0x2c9) = 0x16;
                    break;
                }
                if (*(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x19) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
                    *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x7e;
                    CPlayer::Unk410a10(0xf, 0);
                    CPlayer::Unk4105a0(0x834, 980.0);
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0;
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0x19;
                    *((char*)this + 0x2c9) = 0x16;
                    break;
                }
                if (*(WORD*)((char*)this + 0xa) == 0x1d) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0x1e;
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 0xd) {
            *(double*)((char*)this + 0x30) -= 0.025;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x19) {
            *(double*)((char*)this + 0x30) += 0.025;
            if (*(double*)((char*)this + 0x30) > 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 0xf || *(WORD*)((char*)this + 0xa) == 0x10) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -70.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 0x11) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-25.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -65.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 0x12) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -43.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 || *(WORD*)((char*)this + 0xa) == 0x13) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -29.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8 || *(WORD*)((char*)this + 0xa) == 0x14) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -23.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0x15) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (23.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -36.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa || *(WORD*)((char*)this + 0xa) == 0x16) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -58.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0x17) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (14.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -73.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc || *(WORD*)((char*)this + 0xa) == 0x18) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -78.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x19) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                *(double*)((char*)this + 0x30) = -4.0;
                *(double*)((char*)this + 0x38) = -4.0;
                *(double*)((char*)this + 0x48) = 0.025;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1b) {
                *(double*)((char*)this + 0x30) = -1.8;
                *(double*)((char*)this + 0x38) = -2.3;
                *(double*)((char*)this + 0x48) = 0.035;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -1.8;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -2.3;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3b;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x139:
        *(short*)((char*)this + 0x13e) = 2;
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        if (*(WORD*)((char*)this + 0xa) < 0x19) {
            if (*(double*)((char*)this + 0x20) > 580.0) {
                *(double*)((char*)this + 0x20) = 580.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            if (*(double*)((char*)this + 0x20) < 60.0) {
                *(double*)((char*)this + 0x20) = 60.0;
                *(double*)((char*)this + 0x30) = 0.0;
            }
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) < 0xd || *(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x19 || *(WORD*)((char*)this + 0xa) > 0x1a && *(WORD*)((char*)this + 0xa) < 0x1e) {
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
            if (*(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28) > 0.0) {
                if (*(WORD*)((char*)this + 0xa) < 0xd) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x96;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
                    *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
                    CPlayer::Unk4105a0(0x3e8, 980.0);
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0x7530;
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0xd;
                    *((char*)this + 0x2c9) = 0x16;
                    break;
                }
                if (*(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x19) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x62;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
                    *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
                    *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xba;
                    CPlayer::Unk4105a0(0xed8, 980.0);
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0;
                    CPlayer::Unk410a10(0x14, 0x1e);
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0x19;
                    *((char*)this + 0x2c9) = 0x16;
                    break;
                }
                if (*(WORD*)((char*)this + 0xa) == 0x1d) {
                    *(double*)((char*)this + 0x28) = 0.0;
                    CPlayer::Unk40f1e0();
                    *(short*)((char*)this + 0xc) = 0;
                    *(short*)((char*)this + 0xa) = 0x1e;
                    break;
                }
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 0xd) {
            *(double*)((char*)this + 0x30) -= 0.025;
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xe && *(WORD*)((char*)this + 0xa) < 0x19) {
            *(double*)((char*)this + 0x30) += 0.025;
            if (*(double*)((char*)this + 0x30) > 0.0) {
                *(double*)((char*)this + 0x30) = 0.0;
            }
        }
        if (*(WORD*)((char*)this + 0xa) < 4) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x16 + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 52.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 0xf || *(WORD*)((char*)this + 0xa) == 0x10) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (15.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -70.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
        }
        if (*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 0x11) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-25.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -65.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 6 || *(WORD*)((char*)this + 0xa) == 0x12) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -43.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 || *(WORD*)((char*)this + 0xa) == 0x13) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x75;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -29.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8 || *(WORD*)((char*)this + 0xa) == 0x14) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -23.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0x15) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x68;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (23.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -36.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa || *(WORD*)((char*)this + 0xa) == 0x16) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (28.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -58.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0x17) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x67;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (14.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -73.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc || *(WORD*)((char*)this + 0xa) == 0x18) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x76;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (-12.0 + *(double*)((char*)this + 0x30)) * *((char*)this + 0x50) + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -78.0 + *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x28);
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0x19) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf) {
                *(double*)((char*)this + 0x30) = -4.0;
                *(double*)((char*)this + 0x38) = -7.0;
                *(double*)((char*)this + 0x48) = 0.025;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1b) {
                *(double*)((char*)this + 0x30) = -1.8;
                *(double*)((char*)this + 0x38) = -2.3;
                *(double*)((char*)this + 0x48) = 0.035;
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -1.8;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -2.3;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3b;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                CPlayer::Unk40e630();
                *(short*)((char*)this + 8) = 3;
            }
        }
        break;
    case 0x13a:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x22);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk410a80(0x32, 0x78);
            *(short*)((char*)this + 0x16c) = 0xc;
        }
        if (*(WORD*)((char*)this + 0xc) == 0 && (*(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0xf)) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) += 0.012;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) -= 0.012;
            }
            if (*(double*)((char*)this + 0x30) < -1.2) {
                *(double*)((char*)this + 0x30) = -1.2;
            } else if (*(double*)((char*)this + 0x30) > 1.2) {
                *(double*)((char*)this + 0x30) = 1.2;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf) {
            if (*(double*)((char*)this + 0x30) > 0.0) {
                *(double*)((char*)this + 0x30) -= 0.01;
                if (*(double*)((char*)this + 0x30) < 0.0) {
                    *(double*)((char*)this + 0x30) = 0.0;
                }
            }
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) += 0.01;
                if (*(double*)((char*)this + 0x30) > 0.0) {
                    *(double*)((char*)this + 0x30) = 0.0;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0xf || *(WORD*)((char*)this + 0xa) == 0x10) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x13b:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x22);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk410a80(0x32, 0x78);
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if (*(WORD*)((char*)this + 0xc) == 0 && (*(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0xf)) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) += 0.012;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) -= 0.012;
            }
            if (*(double*)((char*)this + 0x30) < -1.3) {
                *(double*)((char*)this + 0x30) = -1.3;
            } else if (*(double*)((char*)this + 0x30) > 1.3) {
                *(double*)((char*)this + 0x30) = 1.3;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf) {
            if (*(double*)((char*)this + 0x30) > 0.0) {
                *(double*)((char*)this + 0x30) -= 0.01;
                if (*(double*)((char*)this + 0x30) < 0.0) {
                    *(double*)((char*)this + 0x30) = 0.0;
                }
            }
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) += 0.01;
                if (*(double*)((char*)this + 0x30) > 0.0) {
                    *(double*)((char*)this + 0x30) = 0.0;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0xf || *(WORD*)((char*)this + 0xa) == 0x10) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x13c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) > 0) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x22);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk410a80(0x32, 0x78);
            *(short*)((char*)this + 0x16c) = 0x63;
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xc) == 0 && (*(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0xf)) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(WORD*)((char*)this + 0xa) > 7 && *(WORD*)((char*)this + 0xa) < 0x10) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) += 0.012;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(double*)((char*)this + 0x30) -= 0.012;
            }
            if (*(double*)((char*)this + 0x30) < -1.4) {
                *(double*)((char*)this + 0x30) = -1.4;
            } else if (*(double*)((char*)this + 0x30) > 1.4) {
                *(double*)((char*)this + 0x30) = 1.4;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf) {
            if (*(double*)((char*)this + 0x30) > 0.0) {
                *(double*)((char*)this + 0x30) -= 0.01;
                if (*(double*)((char*)this + 0x30) < 0.0) {
                    *(double*)((char*)this + 0x30) = 0.0;
                }
            }
            if (*(double*)((char*)this + 0x30) < 0.0) {
                *(double*)((char*)this + 0x30) += 0.01;
                if (*(double*)((char*)this + 0x30) > 0.0) {
                    *(double*)((char*)this + 0x30) = 0.0;
                }
            }
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 0xa) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 1 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 0xa) == 0xf || *(WORD*)((char*)this + 0xa) == 0x10) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x13d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
            *(short*)((char*)this + 0x16c) = 1;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd && *(WORD*)((char*)this + 0xa) < 0x12 && *(int*)((char*)this + 0x168) == 3) {
            Vf0();
            CPlayer::Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xb4;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x49;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1e + *(double*)((char*)this + 0x20);
            *(short*)((char*)this + 8) = 0x13e;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
            break;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0 && *(WORD*)((char*)this + 0xa) < 0x12 && *(WORD*)((char*)this + 0xa) > 0xd) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x12;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xe) {
                *(double*)((char*)this + 0x30) = 3.2;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x3138) < 2) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x13e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if ((*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 0xa) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0x12 && *(WORD*)((char*)this + 0xa) < 0x1f && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x1f;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                if (*(int*)((char*)this + 0x3138) > 1) {
                    *(short*)((char*)this + 0xa) = 0xf;
                    break;
                }
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = 5;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13) {
                *(double*)((char*)this + 0x38) = -3.3;
                *(double*)((char*)this + 0x30) = 1.5;
                *(short*)((char*)this + 0x16c) = 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1f) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x13f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
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
            *(short*)((char*)this + 0x16c) = 1;
            CPlayer::Unk410a80(0x32, 0x78);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd && *(WORD*)((char*)this + 0xa) < 0x12 && *(int*)((char*)this + 0x168) == 3) {
            Vf0();
            CPlayer::Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xb4;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x49;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1e + *(double*)((char*)this + 0x20);
            *(short*)((char*)this + 8) = 0x140;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
            break;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0 && *(WORD*)((char*)this + 0xa) < 0x12 && *(WORD*)((char*)this + 0xa) > 0xd) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x12;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xe) {
                *(double*)((char*)this + 0x30) = 4.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x140:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if ((*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 0xa) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x48) = 0.055;
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0x19 && *(WORD*)((char*)this + 0xa) < 0x26 && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x26;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                if (*(int*)((char*)this + 0x3138) > 1) {
                    *(short*)((char*)this + 0xa) = 0xf;
                    break;
                }
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf && *(int*)((char*)this + 0x3138) < 2) {
                *(short*)((char*)this + 0xa) = 5;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x19) {
                *(double*)((char*)this + 0x38) = -4.0;
                *(double*)((char*)this + 0x30) = 1.6;
                *(short*)((char*)this + 0x16c) = 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x26) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x141:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
        }
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
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
            *(short*)((char*)this + 0x16c) = 1;
            CPlayer::Unk410a80(0x32, 0x78);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd && *(WORD*)((char*)this + 0xa) < 0x12 && *(int*)((char*)this + 0x168) == 3) {
            Vf0();
            CPlayer::Unk40f1e0();
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0xb4;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = 0.0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x49;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1e + *(double*)((char*)this + 0x20);
            *(short*)((char*)this + 8) = 0x142;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = -*((char*)this + 0x50);
            break;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.035;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(int*)((char*)this + 0x168) > 0 && *(WORD*)((char*)this + 0xa) < 0x12 && *(WORD*)((char*)this + 0xa) > 0xd) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x12;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) == 0xe) {
                *(double*)((char*)this + 0x30) = 4.5;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
        break;
    case 0x142:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 0x63;
        }
        if ((*(WORD*)((char*)this + 0xa) == 5 || *(WORD*)((char*)this + 0xa) == 0xa) && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
        }
        if (*(double*)((char*)this + 0x30) > 0.0) {
            *(double*)((char*)this + 0x30) -= 0.025;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(double*)((char*)this + 0x48) = 0.045;
            *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        }
        if (*(WORD*)((char*)this + 0xa) > 0x1b && *(WORD*)((char*)this + 0xa) < 0x21 && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x21;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x25 && *(WORD*)((char*)this + 0xa) < 0x2a && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x2a;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x2c && *(WORD*)((char*)this + 0xa) < 0x43 && *(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 0x43;
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 9) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xa) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xd) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf && *(int*)((char*)this + 0x3138) < 0xa) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = 5;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x14) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x16) {
                *(double*)((char*)this + 0x20) = *((char*)this + 0x50) * 0xf + *(double*)((char*)this + 0x20);
            }
            if (*(WORD*)((char*)this + 0xa) == 0xf && *(int*)((char*)this + 0x3138) < 8) {
                *(short*)((char*)this + 0xa) = 5;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x1c) {
                *(double*)((char*)this + 0x38) = -1.8;
                *(double*)((char*)this + 0x30) = 1.5;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x25) {
                *(double*)((char*)this + 0x38) = -2.6;
                *(double*)((char*)this + 0x30) = 1.5;
                *(short*)((char*)this + 0x16c) = 1;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x2d) {
                *(double*)((char*)this + 0x38) = -4.5;
                *(double*)((char*)this + 0x30) = 2.2;
                *(short*)((char*)this + 0x16c) = 8;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x43) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 3;
                Vf0();
            }
        }
    }
}
