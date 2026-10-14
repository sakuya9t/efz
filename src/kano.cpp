// CKano (0x6429c0-0x66756f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CKano::Vf6()
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
        *(double*)((char*)this + 0x30) = 0.6;
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
        *(double*)((char*)this + 0x30) = -0.6;
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
            *(double*)((char*)this + 0x48) = 0.025;
            *(double*)((char*)this + 0x38) = -2.2;
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
            *(double*)((char*)this + 0x48) = 0.025;
            *(double*)((char*)this + 0x38) = -2.2;
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
            *(double*)((char*)this + 0x48) = 0.025;
            *(double*)((char*)this + 0x38) = -2.2;
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
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.025;
            *(double*)((char*)this + 0x38) = -2.2;
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
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.025;
            *(double*)((char*)this + 0x38) = -2.2;
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
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.025;
            *(double*)((char*)this + 0x38) = -2.2;
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
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
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
        if (*(WORD*)((char*)this + 0xa) > 3) {
            *(double*)((char*)this + 0x30) = 1.5;
        }
        *((char*)this + 0x158) = 1;
        (*(short*)((char*)this + 0xc))++;
        (*(int*)((char*)this + 0x3138))++;
        (*(int*)((char*)this + 0x313c))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                break;
            }
        }
        if (*((char*)this + 0x188) == *((char*)this + 0x50) && *(int*)((char*)this + 0x313c) >= 0x50) {
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
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x30) = -3.1;
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x48) = 0.0;
            *(int*)((char*)this + 0x3138) = 1;
            *((char*)this + 0x2c9) = 0x11;
        }
        if (*(WORD*)((char*)this + 0xa) > -1) {
            *(double*)((char*)this + 0x30) += 0.04;
        }
        if (*(double*)((char*)this + 0x30) >= 0.0 && *(WORD*)((char*)this + 0xa) > -1) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
            *(short*)((char*)this + 8) = 0;
            Vf0();
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        break;
    case 0xa5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            *(double*)((char*)this + 0x30) = 1.1;
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
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        if (*((char*)this + 0x188) == *((char*)this + 0x50) && *(int*)((char*)this + 0x313c) >= 0x78) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = 0.9;
            *(double*)((char*)this + 0x48) = 0.02;
            if (CPlayer::Unk40e630() != 0) {
                *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            }
        }
        if (*((char*)this + 0x188) != *((char*)this + 0x50) && *(int*)((char*)this + 0x3138) >= 0x30) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = 0.9;
            *(double*)((char*)this + 0x48) = 0.02;
            if (CPlayer::Unk40e630() != 0) {
                *(double*)((char*)this + 0x30) = -*(double*)((char*)this + 0x30);
            }
        }
        break;
    case 0xa6:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) == 0) {
            *(double*)((char*)this + 0x30) = -1.1;
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
                *(short*)((char*)this + 0xa) = 0;
            }
        }
        if (*((char*)this + 0x188) == -*((char*)this + 0x50) && *(int*)((char*)this + 0x313c) >= 0x78) {
            *(short*)((char*)this + 8) = 9;
            Vf0();
            *(double*)((char*)this + 0x30) = -0.9;
            *(double*)((char*)this + 0x48) = 0.02;
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
                if (*(double*)((char*)this + 0x48) == 0.0) {
                    *(double*)((char*)this + 0x48) = 0.02;
                }
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
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) > 0.0 && *(WORD*)((char*)this + 0xa) < 9) {
            CPlayer::Unk40f1e0();
            *(double*)((char*)this + 0x28) = 0.0;
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 9;
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
            if (*(WORD*)((char*)this + 0xa) == 9) {
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
        if (*((char*)this + 0x189) == -1 && *(WORD*)((char*)this + 0xa) > 0 && *(int*)((char*)this + 0x15c) < 3 && *(int*)((char*)this + 0x168) > 0 && *(int*)((char*)this + 0x168) != 6) {
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
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
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
    case 0xcb:
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
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
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
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 1;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
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
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
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
            if (*(WORD*)((char*)this + 0xa) == 4 || *(WORD*)((char*)this + 0xa) == 9) {
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
            *(short*)((char*)this + 0x16c) = 5;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa && *(WORD*)((char*)this + 0xc) == 0) {
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
            if (*(WORD*)((char*)this + 0xa) == 7 || *(WORD*)((char*)this + 0xa) == 9 || *(WORD*)((char*)this + 0xa) == 0xb || *(WORD*)((char*)this + 0xa) == 0xd) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xe && *(int*)((char*)this + 0x3138) < 1) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 7;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 9;
                Vf0();
            }
        }
        break;
    case 0xd2:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x199;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x96);
            l50.y = -40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            (*(int*)((char*)this + 0x3138))++;
            *((char*)this + 0x2c8) = 2;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x14;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 8) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xd3:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 1.2;
            *(double*)((char*)this + 0x38) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
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
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 1;
            }
        }
        break;
    case 0xd4:
        if (*(WORD*)((char*)this + 0xa) == 0) {
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
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 2.6;
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(WORD*)((char*)this + 0xa) > 0) {
            *(double*)((char*)this + 0x30) -= 0.03;
        }
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            if (*(WORD*)((char*)this + 0xa) < 2) {
                *(int*)((char*)this + 0x168) = 0;
            }
            if (*(WORD*)((char*)this + 0xa) == 4 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
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
    case 0xd5:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) < 5) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 5;
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
                ObjBase::SetVelocity(30.0, 2.2);
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xd6:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) < 5) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 5;
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
                ObjBase::SetVelocity(45.0, 1.7);
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xd7:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) = 0.0;
            *(double*)((char*)this + 0x38) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x16c) = 1;
        }
        if (*(double*)((char*)this + 0x28) + *(double*)((char*)this + 0x38) >= 0.0 && *(WORD*)((char*)this + 0xa) < 5) {
            *(double*)((char*)this + 0x28) = 0.0;
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 5;
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
                ObjBase::SetVelocity(60.0, 1.5);
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 7;
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0xd9:
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
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
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
    case 0xdc:
        *(double*)((char*)this + 0x30) = 0.0;
        *(double*)((char*)this + 0x38) = 0.0;
        *((char*)this + 0x158) = 0;
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
            *(short*)((char*)this + 0x16c) = 1;
        } else {
            *(short*)((char*)this + 0x16c) = 0;
        }
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
            l50.y = -52.0;
            l50.x = (double)(int)(*((char*)this + 0x50) * 0x23 + *(double*)((char*)this + 0x20));
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
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x1e;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x4a);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x36);
            l50.unk20 = 2;
            l50.unk2c = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk4105a0(0x3e8, 750.0);
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3f;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -2.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -1.5;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
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
        *(double*)((char*)this + 0x30) -= 0.01;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
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
        *(double*)((char*)this + 0x30) -= 0.01;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 4 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x14;
            *(short*)((char*)this + 0x16c) = 1;
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
        *(double*)((char*)this + 0x30) -= 0.01;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
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
        *(double*)((char*)this + 0x30) -= 0.01;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
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
        *(double*)((char*)this + 0x30) -= 0.01;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
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
        *(double*)((char*)this + 0x30) -= 0.01;
        if (*(double*)((char*)this + 0x30) < 0.0) {
            *(double*)((char*)this + 0x30) = 0.0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x38) = 0.0;
            *(double*)((char*)this + 0x30) = 1.2;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c9) = 0x15;
            *(short*)((char*)this + 0x16c) = 6;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
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
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xf9;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
            l50.type = 0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1d);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3e);
            l50.unk20 = 2;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1d + *(double*)((char*)this + 0x20);
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 62.0;
            CPlayer::Unk410a40(0x32, 3);
            CPlayer::Unk410a80(0x32, 3);
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
        if (*(WORD*)((char*)this + 0xa) < 5) {
            CPlayer::Unk410a40(0x32, 3);
        }
        if (*(WORD*)((char*)this + 0xa) < 5) {
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
        if (*(WORD*)((char*)this + 0xa) == 2) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 47.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1c + *(double*)((char*)this + 0x20);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x65;
        }
        if (*(WORD*)((char*)this + 0xa) == 3) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 38.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x14 + *(double*)((char*)this + 0x20);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x65;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 4) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 62.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1d + *(double*)((char*)this + 0x20);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) == 5 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = *(double*)((char*)this + 0x28) - 72.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *(double*)((char*)this + 0x20);
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3f;
            *(*(char**)*(char**)((char*)this + 0x78) + 0x50) = *((char*)this + 0x50);
            CPlayer::Unk4105a0(0x4b0, 500.0);
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc0) = -1.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xc8) = -2.3;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x48) = 0.035;
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
    case 0xfa:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
            (*(int*)((char*)this + 0x3138))++;
            if (*(int*)((char*)this + 0x3150) > 0x2710) {
                *(int*)((char*)this + 0x3150) = 0x2710;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *((char*)this + 0x18d) == 1 || *(int*)((char*)this + 0x3150) >= 0x2710 && *(WORD*)((char*)this + 0xa) < 7) {
            *(short*)((char*)this + 0xc) = 0;
            *(short*)((char*)this + 0xa) = 7;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (0) {}
            if (0) {}
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xfb:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 3) {
                *(short*)((char*)this + 0x16c) = 1;
                if (*((char*)this + 0x120) == 0) {
                    *(double*)((char*)this + 0x118) -= 500.0;
                } else {
                    *(double*)((char*)this + 0x118) -= 250.0;
                }
                *(int*)((char*)this + 0x3150) = 0x2710;
                l50.type = 0x198;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                l50.type = 0x197;
                l50.x = (double)(int)*(double*)((char*)this + 0x20);
                l50.y = (double)(int)*(double*)((char*)this + 0x28);
                l50.unk20 = 2;
                l50.unk21 = 0;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *((char*)this + 0x2c8) = 1;
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
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x1d4c;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 1) {
                l50.type = 0x1bb;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) * 0x96 + *((char*)this + 0x188) * 0x46));
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *((char*)this + 0x2c8) = 3;
                (*(int*)((char*)this + 0x3170))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0xff:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x1388;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 1) {
                l50.type = 0x1bc;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) * 0x96 + *((char*)this + 0x188) * 0x46));
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *((char*)this + 0x2c8) = 3;
                (*(int*)((char*)this + 0x3170))++;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x14;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x100:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x9c4;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 1) {
                l50.type = 0x1bd;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) * 0x96 + *((char*)this + 0x188) * 0x46));
                l50.y = 0.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
                *((char*)this + 0x2c8) = 3;
                (*(int*)((char*)this + 0x3170))++;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x32;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x101:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x1d4c;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x10 && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x11 && *(int*)((char*)this + 0x3138) < 1) {
                l50.type = 0x191;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2d);
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                l50.unk0 = 1;
                Vf9(&l50);
                *((char*)this + 0x2c8) = 5;
                (*(int*)((char*)this + 0x316c))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 1) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x102:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x1388;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x10 && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x11) {
                if (*(int*)((char*)this + 0x3138) == 0) {
                    l50.type = 0x191;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2d);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk0 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 5;
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 7;
                }
                if (*(int*)((char*)this + 0x3138) == 1) {
                    l50.type = 0x191;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x14);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 7;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x46);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 5;
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 7;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x103:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x9c4;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x10 && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x11) {
                if (*(int*)((char*)this + 0x3138) == 0) {
                    l50.type = 0x191;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2d);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 5;
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xa;
                }
                if (*(int*)((char*)this + 0x3138) == 1) {
                    l50.type = 0x191;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x14);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk0 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xa;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x46);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 5;
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xa;
                }
                if (*(int*)((char*)this + 0x3138) == 2) {
                    l50.type = 0x191;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) + 5);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xa;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x26);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x5f);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 5;
                    (*(int*)((char*)this + 0x316c))++;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xa;
                }
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 3) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x104:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x1d4c;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
                l50.type = 0x1b8;
                l50.x = *(double*)((char*)this + 0x20);
                l50.y = -80.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                l50.unk0 = 1;
                Vf9(&l50);
                (*(int*)((char*)this + 0x3168))++;
                *((char*)this + 0x2c8) = 4;
                *(int*)((char*)this + 0x313c) = 0x15;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x105:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x1388;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
                l50.type = 0x1b9;
                l50.x = *(double*)((char*)this + 0x20);
                l50.y = -80.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                l50.unk0 = 1;
                Vf9(&l50);
                *((char*)this + 0x2c8) = 4;
                (*(int*)((char*)this + 0x3168))++;
                *(int*)((char*)this + 0x313c) = 0x15;
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x14;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x106:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x4b;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0x9c4;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) > 0xb && *(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0)) {
            Vf0();
            CPlayer::Unk40f1e0();
            *(short*)((char*)this + 8) = 0xfb;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
                l50.type = 0x1ba;
                l50.x = *(double*)((char*)this + 0x20);
                l50.y = -80.0;
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                l50.unk0 = 1;
                Vf9(&l50);
                (*(int*)((char*)this + 0x3168))++;
                *((char*)this + 0x2c8) = 4;
                *(int*)((char*)this + 0x313c) = 0x15;
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x32;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x107:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 6) {
            *(int*)((char*)this + 0x3150) += 0x12c;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 6 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xf) {
            (*(int*)((char*)this + 0x313c))--;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3138) < 1) {
            l50.type = 0x199;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x6e);
            l50.y = -40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            (*(int*)((char*)this + 0x3138))++;
            *((char*)this + 0x2c8) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x108:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 6) {
            *(int*)((char*)this + 0x3150) += 0x12c;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 6 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xf) {
            (*(int*)((char*)this + 0x313c))--;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3138) < 1) {
            l50.type = 0x199;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xa0);
            l50.y = -40.0;
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            (*(int*)((char*)this + 0x3138))++;
            *((char*)this + 0x2c8) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(int*)((char*)this + 0x3138) < 2) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x109:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(int*)((char*)this + 0x3138) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x64);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e0);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x50);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x208);
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x82);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x212);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10a:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(int*)((char*)this + 0x3138) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xb4);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e0);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xa0);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x208);
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xd2);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x212);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10b:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *(int*)((char*)this + 0x3138) = 2;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 6;
            l50.type = 0x1a2;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x104);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e0);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xf0);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x208);
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x122);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x212);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
                CPlayer::Unk40e630();
            }
        }
        break;
    case 0x10c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            *(double*)((char*)this + 0x38) *= 0.5;
            *(double*)((char*)this + 0x48) = 0.01;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 3;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 9;
                *(double*)((char*)this + 0x48) = 0.035;
            }
        }
        break;
    case 0x10d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            *(double*)((char*)this + 0x38) *= 0.5;
            *(double*)((char*)this + 0x48) = 0.01;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 3;
        }
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 9;
                *(double*)((char*)this + 0x48) = 0.035;
            }
        }
        break;
    case 0x10e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *(double*)((char*)this + 0x30) *= 0.5;
            *(double*)((char*)this + 0x38) *= 0.5;
            *(double*)((char*)this + 0x48) = 0.01;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x2d;
            *(int*)((char*)this + 0x3138) = 3;
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
        *(double*)((char*)this + 0x38) = *(double*)((char*)this + 0x38) + *(double*)((char*)this + 0x48);
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) > 1) {
            (*(int*)((char*)this + 0x313c))++;
        }
        if (*(int*)((char*)this + 0x313c) == 0x10) {
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1e);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (*(int*)((char*)this + 0x313c) == 0x20) {
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0xa);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        if (*(int*)((char*)this + 0x313c) == 0x30) {
            l50.type = 0x197;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x14);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0xa);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk21 = 1;
            l50.unk20 = 2;
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x3138) < 3) {
                (*(int*)((char*)this + 0x3138))++;
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                break;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                Vf0();
                *(short*)((char*)this + 8) = 9;
                *(double*)((char*)this + 0x48) = 0.035;
            }
        }
        break;
    case 0x12c:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x64);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x64;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0x10 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 0x1d;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x10 && *(WORD*)((char*)this + 0xc) == 0 && *(int*)((char*)this + 0x3138) < 1) {
                l50.type = 0x1c7;
                l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x4b);
                l50.y = 0.0;
                if (*(int*)((char*)this + 0x3138) == 1) {
                    l50.x = *((char*)this + 0x50) * 0x1e + *(double*)((char*)this + 0x20);
                }
                if (*(int*)((char*)this + 0x3138) == 2) {
                    l50.x = *((char*)this + 0x50) * 0x78 + *(double*)((char*)this + 0x20);
                }
                if (*(int*)((char*)this + 0x3138) == 3) {
                    l50.x = *((char*)this + 0x50) * 0x50 + *(double*)((char*)this + 0x20);
                }
                if (*(int*)((char*)this + 0x3138) == 4) {
                    l50.x = *((char*)this + 0x50) * 0x91 + *(double*)((char*)this + 0x20);
                }
                l50.unk20 = 2;
                l50.unk21 = 1;
                l50.unk18 = *((char*)this + 0x50);
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 0x12 && *(int*)((char*)this + 0x3138) < 3) {
                (*(short*)((char*)this + 0xa))--;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x12d:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x64);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x64;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xf && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1a3;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x28);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 6) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x12e:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x64;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xa && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 0xa4);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1c1;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            l50.unk30 = 1;
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x12f:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x64);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x64;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xe && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x19c;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x6e);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x130:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x40);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x96;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1ad;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x3c);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x2d);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) + 0xa);
            l50.unk0 = 1;
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x4b);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0xa);
            l50.unk0 = 1;
            Vf9(&l50);
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x3c);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk0 = 1;
            l50.type = 0x19d;
            Vf9(&l50);
            CPlayer::Unk410a10(4, 0);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x131:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x64;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1c2;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0xa);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x37);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
            (*(int*)((char*)this + 0x315c))++;
            *(int*)((char*)this + 0x3160) = 0x258;
            *(int*)((char*)this + 0x3164) = *((char*)this + 0x50);
        }
        if (*(WORD*)((char*)this + 0xa) > 0xd) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xc && *(int*)((char*)this + 0x3140) < 8) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 2;
                (*(int*)((char*)this + 0x3140))++;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x11 && *(int*)((char*)this + 0x313c) < 5) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
                (*(int*)((char*)this + 0x313c))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x132:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 0xd) {
            *(int*)((char*)this + 0x3150) += 0xc8;
            if (*(int*)((char*)this + 0x3150) > 0x2710) {
                *(int*)((char*)this + 0x3150) = 0x2710;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            (*(int*)((char*)this + 0x313c))--;
        }
        if (*(int*)((char*)this + 0x313c) <= 0 && *(int*)((char*)this + 0x3140) < 3 && *(WORD*)((char*)this + 0xa) > 0xf) {
            *(int*)((char*)this + 0x3150) = 0;
            *((char*)this + 0x2c8) = 0xe;
            l50.type = 0x19e;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *(int*)((char*)this + 0x313c) = 0x1e;
            (*(int*)((char*)this + 0x3140))++;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0x13c) = 0xf;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 6) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x133:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 0xd) {
            *(int*)((char*)this + 0x3150) += 0xc8;
            if (*(int*)((char*)this + 0x3150) > 0x2710) {
                *(int*)((char*)this + 0x3150) = 0x2710;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            (*(int*)((char*)this + 0x313c))--;
        }
        if (*(int*)((char*)this + 0x313c) <= 0 && *(int*)((char*)this + 0x3140) < 4 && *(WORD*)((char*)this + 0xa) > 0xf) {
            *(int*)((char*)this + 0x3150) = 0;
            *((char*)this + 0x2c8) = 0xe;
            l50.type = 0x19f;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *(int*)((char*)this + 0x313c) = 0x1e;
            (*(int*)((char*)this + 0x3140))++;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0x13c) = 0x2d;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 6) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x134:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) > 2) {
            ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
        }
        if (*(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x32);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *(short*)((char*)this + 0x16c) = 5;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) == 6 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 0xd) {
            *(int*)((char*)this + 0x3150) += 0xc8;
            if (*(int*)((char*)this + 0x3150) > 0x2710) {
                *(int*)((char*)this + 0x3150) = 0x2710;
            }
        }
        if (*(WORD*)((char*)this + 0xa) > 0xf && *(WORD*)((char*)this + 0xa) < 0x13) {
            (*(int*)((char*)this + 0x313c))--;
        }
        if (*(int*)((char*)this + 0x313c) <= 0 && *(int*)((char*)this + 0x3140) < 5 && *(WORD*)((char*)this + 0xa) > 0xf) {
            *(int*)((char*)this + 0x3150) = 0;
            *((char*)this + 0x2c8) = 0xe;
            l50.type = 0x1a0;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *(int*)((char*)this + 0x313c) = 0x1e;
            (*(int*)((char*)this + 0x3140))++;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 0x10) {
                *(short*)((char*)this + 0x13c) = 0xb4;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x13 && *(int*)((char*)this + 0x3138) < 6) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
                (*(int*)((char*)this + 0x3138))++;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x135:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x40);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x96;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1ae;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0x12;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x138:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x44;
            l50.unk2c = 0x13;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x40);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x96;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0x11 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1a7;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0x11;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x139:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        if (*(WORD*)((char*)this + 0xa) == 9 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x45;
            l50.unk2c = 5;
            l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0xe);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x40);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x96;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 8;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 0xc && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1ac;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x3c);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk0 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            *((char*)this + 0x2c8) = 0xf;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 3;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x13a:
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
        }
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 7 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7) {
            *(int*)((char*)this + 0x3150) += 0x64;
        }
        if (*(WORD*)((char*)this + 0xa) > 2 && *(WORD*)((char*)this + 0xa) < 7 && *(int*)((char*)this + 0x3150) >= 0x2710) {
            *(int*)((char*)this + 0x3150) = 0;
            *(short*)((char*)this + 0xa) = 7;
            *(short*)((char*)this + 0xc) = 0;
            break;
        }
        if (*(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x196;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 1;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
            l50.type = 0x197;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk20 = 2;
            l50.unk21 = 0;
            l50.unk18 = *((char*)this + 0x50);
            Vf9(&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 8 && *(WORD*)((char*)this + 0xc) == 0) {
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x16c) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 0xa4);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
        }
        if (*(WORD*)((char*)this + 0xa) == 0xd && *(WORD*)((char*)this + 0xc) == 0) {
            l50.type = 0x1b2;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)(int)*(double*)((char*)this + 0x28);
            l50.unk18 = *((char*)this + 0x50);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            Vf9(&l50);
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 4;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x13b:
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x158) = 0;
            CPlayer::Unk40f1e0();
            *((char*)this + 0x2c8) = 0;
            *(short*)((char*)this + 0x14c) = 0x78;
            *(short*)((char*)this + 0x16c) = 1;
            *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
            CPlayer::Unk410b10(0xb0, 3);
            l50.type = 0x46;
            l50.unk2c = 0x40;
            l50.x = (double)(int)*(double*)((char*)this + 0x20);
            l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2b);
            l50.unk20 = 2;
            l50.unk0 = 1;
            l50.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
            *((char*)this + 0x2c9) = 0x25;
            l50.type = 0x47;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
        }
        if (*(WORD*)((char*)this + 0xa) == 7 && *(int*)((char*)this + 0x168) == 3) {
            *(short*)((char*)this + 0xa) = 0;
            *(short*)((char*)this + 8) = 0x13c;
            ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40f1e0();
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xa) = 0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xc) = 0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x6b;
            break;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 7) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                    *(short*)((char*)this + 0x16c) = 1;
                } else {
                    *(short*)((char*)this + 0x16c) = 0;
                }
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
        break;
    case 0x13c:
        CPlayer::Unk410a80(0x32, 3);
        if (*(WORD*)((char*)this + 0xa) == 0 && *(WORD*)((char*)this + 0xc) == 0) {
            *((char*)this + 0x2c8) = 0x1b;
        }
        if (*(WORD*)((char*)this + 0xa) > 0x11 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0x63) {
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xc) = 0;
        }
        (*(short*)((char*)this + 0xc))++;
        if (*(WORD*)((char*)this + 0xc) >= l4) {
            *(short*)((char*)this + 0xc) = 0;
            (*(short*)((char*)this + 0xa))++;
            *(int*)((char*)this + 0x168) = 0;
            if (*(WORD*)((char*)this + 0xa) == 4) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x37 + *(double*)((char*)this + 0x20);
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -61.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 5) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x2e + *(double*)((char*)this + 0x20);
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -74.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 6) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x21 + *(double*)((char*)this + 0x20);
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -86.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 7) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = (*((char*)this + 0x50) << 5) + *(double*)((char*)this + 0x20);
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -87.0;
                l50.type = 0x1c8;
                l50.x = 0.0;
                l50.y = 200.0;
                l50.unk20 = 0;
                l50.unk21 = 1;
                l50.unk0 = 1;
                l50.unk18 = 1;
                l50.unk24 = 1;
                l50.unk30 = 1;
                Vf9(&l50);
            }
            if (*(WORD*)((char*)this + 0xa) == 8) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x64;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) = *((char*)this + 0x50) * 0x1f + *(double*)((char*)this + 0x20);
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -87.0;
            }
            if (*(WORD*)((char*)this + 0xa) == 0xb && *(int*)((char*)this + 0x3138) == 0) {
                *(short*)((char*)this + 0xa) = *(WORD*)((char*)this + 0xa) - 3;
            }
            if (*(WORD*)((char*)this + 0xa) == 0x11) {
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0;
                *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x3b;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) = -20.0;
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x48) = 0.035;
            }
            if (*(WORD*)((char*)this + 0xa) >= x8) {
                *(short*)((char*)this + 8) = 0;
                Vf0();
            }
        }
    }
}

CKano::CKano(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "kano");
    *(short*)((char*)this + 0x18) = 0x434;
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
    *(short*)((char*)this + 0x2ad0) = -0xd;
    *(short*)((char*)this + 0x2af8) = -0x38;
    *(short*)((char*)this + 0x2ad2) = 0x13;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0xb;
    *(short*)((char*)this + 0x2afc) = -7;
    *(short*)((char*)this + 0x2ad6) = -3;
    *(short*)((char*)this + 0x2afe) = -0x13;
    *(short*)((char*)this + 0x2ad8) = -0x16;
    *(short*)((char*)this + 0x2b00) = -0x26;
    *((char*)this + 0x30f4) = 5;
    *((char*)this + 0x30f5) = 0x17;
    *((char*)this + 0x30f6) = 0x18;
    *((char*)this + 0x30ff) = 0x14;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3174) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3274) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3374) = 0;
    }
}

void CKano::Vf12()
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

void CKano::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CKano::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3174) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3274) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3374) = 0;
    CPlayer::Vf10(p1);
}

void CKano::Vf3()
{
    CPlayer::Unk40e740();
}

void CKano::Vf4()
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
        if (*(int*)((char*)this + 0x108) < 0xd05 && (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) && *(short*)((char*)this + 0x262) == 0xad && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9d8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13b;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9d0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13a;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x6f && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9c8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x139;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x6e && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9c0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x138;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x988)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x131;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x65 && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x980)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x130;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x64 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x978)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12f;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xac && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x134;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0xab || *(short*)((char*)this + 0x262) == 0xac) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x998)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x133;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0xaa || *(short*)((char*)this + 0x262) == 0xab || *(short*)((char*)this + 0x262) == 0xac) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x990)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x132;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x33 && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x135;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x7a && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12e;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x79 && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12d;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x78 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12c;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x3e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x3168) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x830) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x106;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x9c4;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x3d && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x3168) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x828) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x105;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x1388;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x3c && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x3168) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x104;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x1d4c;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x20 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x316c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x103;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x9c4;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x1f && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x316c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x1388;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x316c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x1d4c;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xc && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x3170) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x9c4;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xb && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x3170) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xff;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x1388;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(int*)((char*)this + 0x3170) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfe;
            if (*(int*)((char*)this + 0x3150) >= 0x2710) {
                *(short*)((char*)this + 0xa) = 7;
                *(short*)((char*)this + 0xc) = 0;
                *(int*)((char*)this + 0x3150) = 0x1d4c;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xd && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d8) && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x3150) < 0x2710) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfb;
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
            if (*(double*)((char*)this + 0x28) < -25.0 && *((char*)this + 0x189) == 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6a8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd5;
                return;
            }
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
            if (*(double*)((char*)this + 0x28) < -30.0 && *((char*)this + 0x189) == 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6b0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd6;
                return;
            }
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
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6c8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd9;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x648) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -70.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 70.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
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
            if (*(double*)((char*)this + 0x28) < -25.0 && *((char*)this + 0x189) == 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6b8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd7;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x688) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd1;
                return;
            }
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *((char*)this + 0x188) == *((char*)this + 0x50) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6a0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xd4;
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x670) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xce;
            return;
        }
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *((char*)this + 0x188) != 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -30.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6e0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xdc;
                return;
            }
            if (*(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x690) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd2;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x658) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xcb;
                return;
            }
        }
    }
    if (*(int*)((char*)this + 0x15c) < 2 && (*((char*)this + 0x18d) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x80) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x80) != 0) && *(int*)((char*)this + 0x3150) < 0x2710 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
        Vf0();
        CPlayer::Unk40f170();
        *(short*)((char*)this + 8) = 0xfa;
    }
}

void CKano::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (*(int*)((char*)this + 0x3150) == 0x2710) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x154);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3150) != 0 && *(int*)((char*)this + 0x3150) < 0x2710) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3150) != 0 && *(int*)((char*)this + 0x3150) < 0x2710) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, *(int*)((char*)this + 0x3150) * x1c.width / 0x2710, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x3150) * x1c.width / 0x2710, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x3150) * x1c.width / 0x2710, 0x1f - x1c.y, *(int*)((char*)this + 0x3150) * x1c.width / 0x2710, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CKano::Vf8()
{
    EffectDesc v48;
    CPlayer::Unk413090((EffectDesc*)&v48);
    if (*(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0 && *(WORD*)((char*)this + 8) < 0x12c) {
        (*(int*)((char*)this + 0x3154))++;
    }
    if (*(int*)((char*)this + 0x3154) > 0x1e - (0x1c - ((int)(*(short*)((char*)this + 0x148) * 0.001) << 2))) {
        (*(short*)((char*)this + 0x148))++;
        *(int*)((char*)this + 0x3154) = 0;
    }
    if (0.0 != (*(int*)((char*)this + 0x3154) > 0x1e - (0x1c - ((int)(*(short*)((char*)this + 0x148) * 0.001) << 2))) * 0.5 && *(WORD*)((char*)this + 8) == 3) {
        (*(short*)((char*)this + 0x148))++;
        *(int*)((char*)this + 0x3154) = 0;
    }
    if (*(double*)((char*)this + 0x30) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0 && *(WORD*)((char*)this + 8) < 0x12c && (*(WORD*)((char*)this + 8) < 0x32 || *(WORD*)((char*)this + 8) > 0xc8)) {
        (*(int*)((char*)this + 0x3158))++;
    } else {
        *(int*)((char*)this + 0x3158) = 0;
    }
    if (*(int*)((char*)this + 0x3158) > 0x276) {
        *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) + 0x12c;
        *(int*)((char*)this + 0x3158) = 0;
        v48.type = 0x19b;
        v48.x = (double)(int)*(double*)((char*)this + 0x20);
        v48.y = *(double*)((char*)this + 0x28) - 50.0;
        v48.unk18 = 1;
        v48.unk20 = 0;
        v48.unk21 = 1;
        Vf9(&v48);
    }
    (*(int*)((char*)this + 0x3160))--;
    if (*(int*)((char*)this + 0x315c) > 0 && *(int*)((char*)this + 0x3160) <= 0) {
        v48.type = 0x1c3;
        v48.x = (double)((int)*(double*)((char*)this + 0x20) + 0x78 - (WORD)CPlayer::Unk4108a0(0, 0xf0) - (int)(*(int*)((char*)this + 0x3164) * 192.0));
        v48.y = -480.0;
        v48.unk18 = *((char*)this + 0x3164);
        v48.unk20 = 2;
        v48.unk21 = 1;
        v48.unk0 = 1;
        Vf9(&v48);
        (*(int*)((char*)this + 0x315c))--;
        *(int*)((char*)this + 0x3160) = 0xb4;
    }
}

void CKano::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CKano::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
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
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
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
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x78;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x3c + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
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
    v4 = *(short*)((char*)this + 0x260) + 0x87;
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
    v4 = *(short*)((char*)this + 0x260) + 0x87;
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

void CKano::Vf5()
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 25.0f * *(float*)((char*)this + 0xa8) + (*(double*)((char*)this + 0x28) < 0.0) * 0x1e * *(float*)((char*)this + 0xa8) + (*(int*)((char*)this + 0x3114) == 3) * 0x190 + (*(WORD*)((char*)this + 8) == 0xaa) * 0x12c) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x7d0) < ((*((char*)this + 0x130) > 0) * 4.0 + 1.0) * 8.0 * *(float*)((char*)this + 0xa8) * ((*(WORD*)((char*)this + 8) > 0x95 && *(WORD*)((char*)this + 8) < 0x9d) * 2 + 1)) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 4e+01f * *(float*)((char*)this + 0xa8) && *(WORD*)((char*)this + 8) > 0xc7) {
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
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
            *(int*)((char*)this + 0x3114) = 3;
        } else {
            *(int*)((char*)this + 0x3114) = 0;
        }
        *((char*)this + 0x188) = 1 - (((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) << 1);
        *((char*)this + 0x18d) = (WORD)CPlayer::Unk4108a0(0, 0xf0) < x8;
        *((char*)this + 0x18d) = (WORD)CPlayer::Unk4108a0(0, 0x140) < v10;
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
            if (v10 < 40.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 > 20.0 && v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
                *((char*)this + 0x18a) = 3;
                *((char*)this + 0x189) = 1;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x16;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && v10 < 80.0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && v10 < 150.0 && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
        }
        if (v10 < 220.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
        }
        if (v10 > 220.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5f;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -100.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -100.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18c) = 1;
            *((char*)this + 0x189) = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
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
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
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
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0xfa || *(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0xfc || *(WORD*)((char*)this + 8) == 0x10e || *(WORD*)((char*)this + 8) == 0x10f || *(WORD*)((char*)this + 8) == 0x110)) {
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
    if (*(int*)((char*)this + 0x168) > 1 && *(short*)((char*)this + 0x14a) == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 25.0f && *(int*)((char*)this + 0x3114) != 1 && *(int*)((char*)this + 0x3114) != 2) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * *(float*)((char*)this + 0xa8)) {
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
                if ((WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && x8 < 90.0 && *(int*)((char*)this + 0x3110) > 0xaa && *(int*)((char*)this + 0x3110) < 0xdc) {
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
                if ((WORD)CPlayer::Unk4108a0(0, 0x140) < v10 - 100.0 && x8 < 180.0 && *(int*)((char*)this + 0x3110) > 0xaa && *(int*)((char*)this + 0x3110) < 0xf0) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3.0f * *(float*)((char*)this + 0xa8)) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        return;
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && v10 > 60.0 && v10 < 140.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * *(float*)((char*)this + 0xa8) && *(double*)((char*)this + 0x20) > 120.0 && *(double*)((char*)this + 0x20) < 520.0) {
        *(short*)((char*)this + 0x262) = -((*((char*)this + 0x50) == 1) - 1);
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 2) {
        *(int*)((char*)this + 0x3114) = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
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

void CKano::Vf7()
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
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
            case 0x191:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0) {
                    l50.type = 0x193;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x316c))--;
                    Vf10(v4);
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x316c))--;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.03;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 1.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.5;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 6;
                    }
                }
                break;
            case 0x192:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        l50.type = 0x191;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x28);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x193:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
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
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) == 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 4) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                            break;
                        }
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.8;
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x195:
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
            case 0x199:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                if (*(WORD*)((char*)this + 8) == 0xd2) {
                    *(int*)((char*)this + 0x168) = *(int*)((char*)this + v4 * 0x98 + 0x550);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19a:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
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
            case 0x19b:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.2;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
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
            case 0x19c:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *((char*)this + 0x2c8) = 0xa;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 2.0;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x550) != 6 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19d;
                    l50.type = 0x1a5;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
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
            case 0x19d:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(WORD*)((char*)this + 8) == 0x130) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                        l50.type = 0x1a5;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 1) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x32);
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0x28);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 2) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x1e);
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0x46);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 3) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x14);
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0xa);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 4) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0xa);
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0x14);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 5) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x1e);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    *(int*)((char*)this + v4 * 4 + 0x3274) = (WORD)CPlayer::Unk4108a0(0, 3);
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) == 0) {
                        *((char*)this + 0x2c8) = 0xb;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) == 1) {
                        *((char*)this + 0x2c8) = 0xc;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) == 2) {
                        *((char*)this + 0x2c8) = 0xd;
                    }
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 6) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                        } else {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x19e:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.5;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 6;
                    }
                }
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x550) != 6 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xe;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -80.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 720.0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19f:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.5;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 6;
                    }
                }
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x550) != 6 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xe;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -80.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 720.0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a0:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.5;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 6;
                    }
                }
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x550) != 6 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xe;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -80.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 720.0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a1:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.5;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 6;
                    }
                }
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x550) != 6 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xe;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -80.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 720.0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
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
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.035;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 1.5) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.5;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 6;
                    }
                }
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x550) != 6 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xe;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -80.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 720.0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a3:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *((char*)this + 0x2c8) = 7;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.005;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a4;
                    }
                }
                break;
            case 0x1a4:
                if (*(int*)((char*)this + v4 * 4 + 0x3274) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                    *((char*)this + 0x2c8) = 8;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(int*)((char*)this + v4 * 4 + 0x3374) == 0) {
                    *((char*)this + 0x2c8) = 9;
                    (*(int*)((char*)this + v4 * 4 + 0x3374))++;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
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
            case 0x1a5:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
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
            case 0x1a6:
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
            case 0x1a7:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                if ((*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 640.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < 0.0) && *(int*)((char*)this + v4 * 0x98 + 0x550) == 0) {
                    Vf10(v4);
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.5;
                    (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) < 8 && *(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                        l50.type = 0x195;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + -0x32 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + (WORD)CPlayer::Unk4108a0(0, 0x14));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                        *(int*)((char*)this + v4 * 4 + 0x3274) = 0xf;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) > 7) {
                        Vf10(v4);
                    }
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 0) {
                            l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1a8;
                            l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + (WORD)CPlayer::Unk4108a0(0, 0xa));
                            l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + -5 + (WORD)CPlayer::Unk4108a0(0, 0xa));
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = *((char*)this + 0x50);
                            Vf9(&l50);
                        }
                    }
                }
                break;
            case 0x1a8:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
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
            case 0x1a9:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
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
            case 0x1aa:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
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
            case 0x1ab:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
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
            case 0x1ac:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 7;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.5;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *((char*)this + 0x2c8) = 0x10;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(int*)((char*)this + v4 * 4 + 0x3374) <= 0) {
                        l50.type = 0x195;
                        l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + -0x32 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + -0x32 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3374) = 2;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3374))--;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ad:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 5;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                if (*(short*)((char*)this + v4 * 0x98 + 0x554) == 0 || *(int*)((char*)this + v4 * 4 + 0x3274) > 0x4b0) {
                    Vf10(v4);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x14 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1a) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 8;
                    }
                }
                break;
            case 0x1ae:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1af;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 0x13;
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
            case 0x1af:
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 1 && (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb)) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xc;
                    *(int*)((char*)this + v4 * 4 + 0x3374) = 2;
                    (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 9 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    if (*(double*)((char*)this + 0x28) == 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 30.0 > *(double*)((char*)this + 0x20) && *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 30.0 < *(double*)((char*)this + 0x20) && *(int*)((char*)this + v4 * 4 + 0x3374) <= 0) {
                        if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 0xb) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xa;
                            break;
                        }
                    } else if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) != 0xc && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) != 0xd) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xc;
                        break;
                    }
                }
                (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                if ((*(int*)((char*)this + v4 * 4 + 0x3174) > 0x960 || *(int*)((char*)this + v4 * 4 + 0x3274) > 9) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xe) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xe;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3374))--;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b0:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe && (WORD)CPlayer::Unk4108a0(0, 3) < 2) {
                        l50.type = 0x1b1;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x96));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b1:
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
            case 0x1b2:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *((char*)this + 0x2c8) = 0x17;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    *(int*)((char*)this + v4 * 4 + 0x3174) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.2;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(int*)((char*)this + v4 * 4 + 0x3174) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 2) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0) {
                    Vf10(v4);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b0;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + (WORD)CPlayer::Unk4108a0(0, 0x28));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + (WORD)CPlayer::Unk4108a0(0, 0x14));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                break;
            case 0x1b3:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(70.0, 3.0);
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1b4:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(55.0, 3.0);
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1b5:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(40.0, 3.0);
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1b6:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(25.0, 3.0);
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1b7:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(10.0, 3.0);
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1b8:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) == 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) > 2 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    if (*((char*)this + v4 * 0x98 + 0x518) == 1) {
                        l50.type = 0x1b3;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    if (*((char*)this + v4 * 0x98 + 0x518) == -1) {
                        l50.type = 0x1b3;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk0 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    }
                }
                break;
            case 0x1b9:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) == 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) > 2 && *(int*)((char*)this + v4 * 4 + 0x3374) > 0xf) {
                    if (*((char*)this + v4 * 0x98 + 0x518) == 1) {
                        l50.type = 0x1b3;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    if (*((char*)this + v4 * 0x98 + 0x518) == -1) {
                        l50.type = 0x1b3;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x3168))++;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) == 2) {
                        Vf10(v4);
                        (*(int*)((char*)this + 0x3168))--;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                    *(int*)((char*)this + v4 * 4 + 0x3374) = 0;
                    break;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3374))++;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    }
                }
                break;
            case 0x1ba:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) == 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    l50.type = 0x195;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3168))--;
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3174) > 2 && *(int*)((char*)this + v4 * 4 + 0x3374) > 0xf) {
                    if (*((char*)this + v4 * 0x98 + 0x518) == 1) {
                        l50.type = 0x1b3;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    if (*((char*)this + v4 * 0x98 + 0x518) == -1) {
                        l50.type = 0x1b3;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20), *(double*)((char*)this + v4 * 0x98 + 0x4f0) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28)) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk0 = 1;
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x3168))++;
                    if (*(int*)((char*)this + v4 * 4 + 0x3274) == 4) {
                        Vf10(v4);
                        (*(int*)((char*)this + 0x3168))--;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3274))++;
                    *(int*)((char*)this + v4 * 4 + 0x3374) = 0;
                    break;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3374))++;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    }
                }
                break;
            case 0x1bb:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x190;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3170))--;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 0) {
                            (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                            break;
                        }
                        Vf10(v4);
                        (*(int*)((char*)this + 0x3170))--;
                    }
                }
                break;
            case 0x1bd:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x190;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + (*(int*)((char*)this + v4 * 4 + 0x3174) * 0x19 - 0x32) * *((char*)this + v4 * 0x98 + 0x518));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3170))--;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 4) {
                            (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                            break;
                        }
                        Vf10(v4);
                        (*(int*)((char*)this + 0x3170))--;
                    }
                }
                break;
            case 0x1bc:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x190;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + (*(int*)((char*)this + v4 * 4 + 0x3174) - 1) * 0x19 * *((char*)this + v4 * 0x98 + 0x518));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    Vf10(v4);
                    (*(int*)((char*)this + 0x3170))--;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 2) {
                            (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                            break;
                        }
                        Vf10(v4);
                        (*(int*)((char*)this + 0x3170))--;
                    }
                }
                break;
            case 0x1be:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    CPlayer::Unk410a10(0xa, 0xa);
                    *((char*)this + 0x2c8) = 0x14;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 8 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xb && *(int*)((char*)this + v4 * 4 + 0x3174) < 6 && *(int*)((char*)this + v4 * 4 + 0x3274) <= 0) {
                    l50.type = 0x1c0;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + -0x50 + (WORD)CPlayer::Unk4108a0(0, 0xa0));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0xf - (WORD)CPlayer::Unk4108a0(0, 0x1e));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1bf;
                    Vf9(&l50);
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 0x2d;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    CPlayer::Unk410a10(5, 5);
                    *((char*)this + 0x2c8) = 0x15;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3274))--;
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb && *(WORD*)((char*)this + 0xa) == 0xd) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bf:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
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
            case 0x1c0:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        l50.type = 0x1c6;
                        l50.x = (double)(int)*(double*)((char*)this + 0x20);
                        l50.y = 0.0;
                        l50.unk20 = 2;
                        l50.unk21 = 0;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *((char*)this + 0x2c8) = 0x16;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1be;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1bf;
                    Vf9(&l50);
                    *(int*)((char*)this + v4 * 4 + 0x3274) = 0x2d;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    CPlayer::Unk410a10(5, 5);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
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
            case 0x1c2:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *((char*)this + 0x2c8) = 0x17;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 6.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -6.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -1600.0) {
                    Vf10(v4);
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
            case 0x1c3:
                if (*(int*)((char*)this + v4 * 4 + 0x3174) == 0) {
                    *((char*)this + 0x2c8) = 0x18;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(60.0, 4.0);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    l50.type = 0x1bf;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk20 = 2;
                    l50.unk21 = 0;
                    l50.unk18 = *((char*)this + 0x3164);
                    Vf9(&l50);
                    l50.type = 0x1c4;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x3164);
                    Vf9(&l50);
                    l50.type = 0x1c5;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x3164);
                    Vf9(&l50);
                    Vf10(v4);
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
            case 0x1c4:
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
            case 0x1c5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *((char*)this + 0x2c8) = 0x19;
                    CPlayer::Unk410a10(0xa, 0);
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
            case 0x1c6:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
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
            case 0x1c7:
                if (*(int*)((char*)this + 0x190) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xf) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xf;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *((char*)this + 0x2c8) = 0x1c;
                    *((char*)this + 0x2c8) = 6;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xf) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.0025;
                } else {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xf && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x19a;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 1) {
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x2d;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 2) {
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x2d;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 3) {
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x5a;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3174) == 4) {
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x5a;
                    }
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xf) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3174) < 2) {
                            (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                            (*(int*)((char*)this + v4 * 4 + 0x3174))++;
                        } else {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x1c8:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        l50.type = 0x34;
                        l50.y = -87.0;
                        l50.x = (double)(int)(*((char*)this + 0x50) * 0x1f + *(double*)((char*)this + 0x20));
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x65;
                        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x270f;
                        *((char*)this + 0x2c8) = 0x1c;
                        CPlayer::Unk4105a0(0x1388, 850.0);
                        *(int*)((char*)this + 0x3138) = 1;
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
