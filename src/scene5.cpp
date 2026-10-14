// CScene5 (0x7712f0-0x7758af), scene 5: the result screen after a match (system\result,
// system\winner). The <math.h> overload pow(int, int) it calls follows it:
// FUNCTION: 0x775810 ?pow@@YANHH@Z
// FUNCTION: 0x775830 ??$_Pow_int@H@@YAHHH@Z
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene5::CScene5(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), "system\\winner.dat", 0, 0xaf);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x438), "system\\result.dat", 0, 0xaf);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), "system\\winner.bmp", 0xaf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x438), "system\\result.bmp", 0xaf);
    }
    *(int*)((char*)this + 0x43c) = 0;
    *(int*)((char*)this + 0x440) = 0;
    *((char*)this + 0x2c) = 1;
    *((char*)this + 0x2d) = 0;
    *((char*)this + 0x45f) = 0;
}

CScene5::~CScene5()
{
    if (*(int*)((char*)this + 0x434) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x434))->Release();
        *(int*)((char*)this + 0x434) = 0;
    }
    if (*(int*)((char*)this + 0x438) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x438))->Release();
        *(int*)((char*)this + 0x438) = 0;
    }
    if (*(int*)((char*)this + 0x43c) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x43c))->Release();
        *(int*)((char*)this + 0x43c) = 0;
    }
    if (*(int*)((char*)this + 0x440) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x440))->Release();
        *(int*)((char*)this + 0x440) = 0;
    }
}

BYTE CScene5::Update()
{
    if (*((char*)this + 0x2c) == 1) {
        *((char*)this + 0x45e) = 0;
        *((char*)this + 0x45f) = 0;
        *(int*)((char*)this + 0xc) = *(int*)*(char**)((char*)this + 0x14);
        *(int*)((char*)this + 0x10) = *(int*)*(char**)((char*)this + 0x18);
        Unk774b00();
        ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
        CScene::Unk759e20((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), 1);
        *((char*)this + 0x2c) = 0;
    } else if (*((char*)this + 0x2d) == 1) {
        CScene::Unk759c90((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), *(*(char**)((char*)this + 0x1c) + 0x1364) != 0, 0, 0x64);
        *(int*)(*(char**)((char*)this + 0x1c) + 0x1360) |= 1 << *(*(char**)((char*)this + 0x1c) + 0xf32);
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0x137c) != 0) {
            delete (char*)*(int*)(*(char**)((char*)this + 0x1c) + 0x137c);
            *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = 0;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x14283) > 0) {
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Close();
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0) {
            if (*(*(char**)((char*)this + 0x1c) + 0x134c) == *(*(char**)((char*)this + 0x1c) + 0x1342)) {
                if (*(*(char**)((char*)this + 0x1c) + 0x1358) == 8) {
                    delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
                    delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
                    *(int*)*(char**)((char*)this + 0x14) = 0;
                    *(int*)*(char**)((char*)this + 0x18) = 0;
                    *((char*)this + 0x2d) = 0;
                    *((char*)this + 0x2c) = 1;
                    return 7;
                }
                if (*(*(char**)((char*)this + 0x1c) + 0x1342) == 1) {
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) |= 1 << *(*(char**)*(char**)((char*)this + 0x14) + 0x8d);
                    delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
                    *(int*)*(char**)((char*)this + 0x14) = 0;
                } else {
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) |= 1 << *(*(char**)*(char**)((char*)this + 0x18) + 0x8d);
                    delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
                    *(int*)*(char**)((char*)this + 0x18) = 0;
                }
                (*(*(char**)((char*)this + 0x1c) + 0x1358))++;
                *(*(char**)((char*)this + 0x1c) + 0x1378) = 0;
                *((char*)this + 0x2d) = 0;
                *((char*)this + 0x2c) = 1;
                return 2;
            }
            if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1378) > 0) {
                *((char*)this + 0x2d) = 0;
                *((char*)this + 0x2c) = 1;
                return 2;
            }
            delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
            delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
            *(int*)*(char**)((char*)this + 0x14) = 0;
            *(int*)*(char**)((char*)this + 0x18) = 0;
            *((char*)this + 0x2d) = 0;
            *((char*)this + 0x2c) = 1;
            return 1;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 2 && *(*(char**)((char*)this + 0x1c) + 0x134c) == *(*(char**)((char*)this + 0x1c) + 0x1342) && *(*(char**)((char*)this + 0x1c) + 0x1358) < 8) {
            if (*(*(char**)((char*)this + 0x1c) + 0x1342) == 1) {
                *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) |= 1 << *(*(char**)*(char**)((char*)this + 0x14) + 0x8d);
                delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
                *(int*)*(char**)((char*)this + 0x14) = 0;
            } else {
                *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) |= 1 << *(*(char**)*(char**)((char*)this + 0x18) + 0x8d);
                delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
                *(int*)*(char**)((char*)this + 0x18) = 0;
            }
            (*(*(char**)((char*)this + 0x1c) + 0x1358))++;
            *((char*)this + 0x2d) = 0;
            *((char*)this + 0x2c) = 1;
            return 2;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 6) {
            delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
            delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
            *(int*)*(char**)((char*)this + 0x14) = 0;
            *(int*)*(char**)((char*)this + 0x18) = 0;
            *((char*)this + 0x2d) = 0;
            *((char*)this + 0x2c) = 1;
            return 0;
        }
        delete (CPlayer*)*(int*)*(char**)((char*)this + 0x14);
        delete (CPlayer*)*(int*)*(char**)((char*)this + 0x18);
        *(int*)*(char**)((char*)this + 0x14) = 0;
        *(int*)*(char**)((char*)this + 0x18) = 0;
        *((char*)this + 0x2d) = 0;
        *((char*)this + 0x2c) = 1;
        return 1;
    }
    Vf2();
    if (*(short*)((char*)this + 0x45c) < 0x3c) {
        (*(short*)((char*)this + 0x45c))++;
        if (*(*(char**)((char*)this + 0x1c) + 0x134c) == 1) {
            ((CPlayer*)*(int*)((char*)this + 0xc))->Vf6();
            ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f580();
            ((CPlayer*)*(int*)((char*)this + 0xc))->Vf6();
            ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f580();
            ((CPlayer*)*(int*)((char*)this + 0xc))->Vf6();
            ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f580();
            if (*(*(char**)((char*)this + 0xc) + 0x2c9) >= 0 && *(*(char**)((char*)this + 0xc) + 0x2c9) < 0x41) {
                ((CSound*)*(int*)((char*)this + 0x28))->Play(*(short*)(*(char**)((char*)this + 0x1c) + 0xea4 + *(*(char**)((char*)this + 0xc) + 0x2c9) * 2), 0);
                *(*(char**)((char*)this + 0xc) + 0x2c9) = -1;
            }
        } else {
            ((CPlayer*)*(int*)((char*)this + 0x10))->Vf6();
            ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f580();
            ((CPlayer*)*(int*)((char*)this + 0x10))->Vf6();
            ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f580();
            ((CPlayer*)*(int*)((char*)this + 0x10))->Vf6();
            ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f580();
            if (*(*(char**)((char*)this + 0x10) + 0x2c9) >= 0 && *(*(char**)((char*)this + 0x10) + 0x2c9) < 0x41) {
                ((CSound*)*(int*)((char*)this + 0x28))->Play(*(short*)(*(char**)((char*)this + 0x1c) + 0xea4 + *(*(char**)((char*)this + 0x10) + 0x2c9) * 2), 0);
                *(*(char**)((char*)this + 0x10) + 0x2c9) = -1;
            }
        }
        if (*(short*)((char*)this + 0x45c) == 0x3c) {
            if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x13 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x14 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x15 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x17) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(4);
            } else if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0xe) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(9);
            } else if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 1 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x10 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x11 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0xd || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0xf || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 2 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 3 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 8 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 9 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0xa) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(2);
            } else {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(3);
            }
            *((char*)this + 0x45e) = 1;
        }
    }
    if (*(short*)((char*)this + 0x444) > 0x28 && *(short*)((char*)this + 0x45c) >= 0x3c) {
        *(short*)((char*)this + 0x444) -= *(short*)((char*)this + 0x446) / 3;
        if (*(short*)((char*)this + 0x444) < 0x78 && *(short*)((char*)this + 0x446) > 1) {
            (*(short*)((char*)this + 0x446))--;
        }
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
    if (*((char*)this + 0x45e) == 2) {
        if (*(*(char**)((char*)this + 0x1c) + 0xc + *(*(char**)((char*)this + 0x1c) + 0x1342)) != 0 && *((char*)this + 0x460) == 0) {
            (*((char*)this + 0x45f))++;
            ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
            if (*((char*)this + 0x45f) > 1) {
                *((char*)this + 0x45f) = 0;
            }
            *((char*)this + 0x460) = 1;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0xc + *(*(char**)((char*)this + 0x1c) + 0x1342)) == 0) {
            *((char*)this + 0x460) = 0;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x10 + *(*(char**)((char*)this + 0x1c) + 0x1342)) != 0) {
            ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
            if (*((char*)this + 0x45f) == 0) {
                if (*(*(char**)((char*)this + 0x1c) + 0x1358) < 8) {
                    *(*(char**)((char*)this + 0x1c) + 0x1379) = *(*(char**)((char*)this + 0x1c) + 0x1358);
                } else {
                    *(*(char**)((char*)this + 0x1c) + 0x1379) = 0;
                }
                *(*(char**)((char*)this + 0x1c) + 0x1378) = 1;
                *((char*)this + 0x2d) = 1;
            } else {
                *(*(char**)((char*)this + 0x1c) + 0x1378) = 0;
                *((char*)this + 0x2d) = 1;
            }
        }
    } else if (*(*(char**)((char*)this + 0x1c) + 0x10) != 0 || *(*(char**)((char*)this + 0x1c) + 0x12) != 0 || *(*(char**)((char*)this + 0x1c) + 0x14) != 0 || *(*(char**)((char*)this + 0x1c) + 0x16) != 0 || *(*(char**)((char*)this + 0x1c) + 0x11) != 0 || *(*(char**)((char*)this + 0x1c) + 0x13) != 0 || *(*(char**)((char*)this + 0x1c) + 0x15) != 0 || *(*(char**)((char*)this + 0x1c) + 0x17) != 0) {
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0 && *(*(char**)((char*)this + 0x1c) + 0x134c) != *(*(char**)((char*)this + 0x1c) + 0x1342) && *((char*)this + 0x45e) < 2) {
            if (*((char*)this + 0x45e) == 0) {
                if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x13 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x14 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x15 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x17) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(4);
                } else if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 1 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 2 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 3 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 8 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 9 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0xa) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(2);
                } else {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(3);
                }
            }
            *((char*)this + 0x45e) = 2;
            *(short*)((char*)this + 0x454) = -0xa0;
            *(short*)((char*)this + 0x458) = 0;
            *(short*)((char*)this + 0x444) = 0x28;
            *(short*)((char*)this + 0x450) = 0xa0;
            *(short*)((char*)this + 0x45c) = 0x3c;
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 2 && *((char*)this + 0x45e) < 2) {
            if (*((char*)this + 0x45e) == 0) {
                if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x13 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x14 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x15 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0x17) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(4);
                } else if (*(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 1 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 2 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 3 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 8 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 9 || *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8d) == 0xa) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(2);
                } else {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(3);
                }
            }
            *((char*)this + 0x45e) = 3;
            *(short*)((char*)this + 0x454) = -0xa0;
            *(short*)((char*)this + 0x458) = 0;
            *(short*)((char*)this + 0x444) = 0x28;
            *(short*)((char*)this + 0x450) = 0xa0;
            *(short*)((char*)this + 0x45c) = 0x3c;
        } else {
            *((char*)this + 0x2d) = 1;
        }
    }
    *(short*)((char*)this + 0x448) = *(short*)((char*)this + 0x448) + 2;
    if (*(short*)((char*)this + 0x448) >= 0x140) {
        *(short*)((char*)this + 0x448) = 0;
    }
    *(short*)((char*)this + 0x44a) = *(short*)((char*)this + 0x44a) + 1;
    if (*(short*)((char*)this + 0x44a) >= 0xf0) {
        *(short*)((char*)this + 0x44a) = 0;
    }
    *(short*)((char*)this + 0x44c) = *(short*)((char*)this + 0x44c) - 2;
    if (*(short*)((char*)this + 0x44c) < 0) {
        *(short*)((char*)this + 0x44c) = 0x140;
    }
    *(short*)((char*)this + 0x44e) = *(short*)((char*)this + 0x44e) - 1;
    if (*(short*)((char*)this + 0x44e) < 0) {
        *(short*)((char*)this + 0x44e) = 0xf0;
    }
    if (*(short*)((char*)this + 0x450) < 0xa0 && *(short*)((char*)this + 0x454) <= -0x50) {
        *(short*)((char*)this + 0x450) += *(short*)((char*)this + 0x452);
        if (*(short*)((char*)this + 0x450) > 0x73) {
            (*(short*)((char*)this + 0x452))--;
        }
    }
    if (*(short*)((char*)this + 0x454) > -0xa0 && *(short*)((char*)this + 0x444) < 0xa0) {
        *(short*)((char*)this + 0x454) -= *(short*)((char*)this + 0x456);
        if (*(short*)((char*)this + 0x454) < -0x28) {
            (*(short*)((char*)this + 0x456))--;
        }
    }
    if (*(short*)((char*)this + 0x458) < 0 && *(short*)((char*)this + 0x450) > 0x78) {
        *(short*)((char*)this + 0x458) += *(short*)((char*)this + 0x45a);
        if (*(short*)((char*)this + 0x458) >= 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) == 6) {
            *((char*)this + 0x2d) = 1;
        }
        if (*(short*)((char*)this + 0x458) > -0x78) {
            (*(short*)((char*)this + 0x45a))--;
        }
    }
    Draw();
    return 5;
}

void CScene5::Draw()
{
    int v8;
    int v4;

    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0, 0x140, 0xa0), (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe98), MakeRect(*(short*)((char*)this + 0x444), 0x140, 0x140, 0xa0), 0, 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(MakeRect(0, 0xa0, 0x140, 0x50), 0xb0);
    if (*(*(char**)((char*)this + 0x1c) + 0x134c) == 1) {
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk4121a0(-*(short*)((char*)this + 0x444), -0x50);
    } else {
        ((CPlayer*)*(int*)((char*)this + 0x10))->Unk4121a0(-*(short*)((char*)this + 0x444), -0x50);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(MakeRect(0x140 - *(short*)((char*)this + 0x450), 0, *(short*)((char*)this + 0x450), 0xf0), 0xe7);
    ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(MakeRect(0, 0, *(short*)((char*)this + 0x450), 0xf0), 0xe7);
    v4 = -0xf0;
    for (; v4 <= 0xf0; v4 += 0x50) {
        if (*(short*)((char*)this + 0x44c) <= 0xa0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x450) - 0xa0, *(short*)((char*)this + 0x44e) + v4, 0xa0, 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x44c), 0x30, 0xa0, 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0 - *(short*)((char*)this + 0x450) + 0xa0, *(short*)((char*)this + 0x44e) + v4, 0xa0 - *(short*)((char*)this + 0x44c), 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x44c) + 0xa0, 0x30, 0xa0 - *(short*)((char*)this + 0x44c), 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0 - *(short*)((char*)this + 0x450) + 0x140 - *(short*)((char*)this + 0x44c), *(short*)((char*)this + 0x44e) + v4, *(short*)((char*)this + 0x44c), 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0x30, *(short*)((char*)this + 0x44c), 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x450) - 0xa0, *(short*)((char*)this + 0x44e) + v4, 0x140 - *(short*)((char*)this + 0x44c), 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x44c), 0x30, 0x140 - *(short*)((char*)this + 0x44c), 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x450) + 0xa0 - *(short*)((char*)this + 0x44c), *(short*)((char*)this + 0x44e) + v4, *(short*)((char*)this + 0x44c) - 0xa0, 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0x30, *(short*)((char*)this + 0x44c) - 0xa0, 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0 - *(short*)((char*)this + 0x450) + 0xa0, *(short*)((char*)this + 0x44e) + v4, 0xa0, 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x44c) - 0xa0, 0x30, 0xa0, 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        }
    }
    v4 = -0xf0;
    for (; v4 <= 0xf0; v4 += 0x50) {
        if (*(short*)((char*)this + 0x448) <= 0xa0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x450) - 0xa0, *(short*)((char*)this + 0x44a) + v4, 0xa0, 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x448), 0, 0xa0, 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0 - *(short*)((char*)this + 0x450) + 0xa0, *(short*)((char*)this + 0x44a) + v4, 0xa0 - *(short*)((char*)this + 0x448), 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x448) + 0xa0, 0, 0xa0 - *(short*)((char*)this + 0x448), 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0 - *(short*)((char*)this + 0x450) + 0x140 - *(short*)((char*)this + 0x448), *(short*)((char*)this + 0x44a) + v4, *(short*)((char*)this + 0x448), 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0, *(short*)((char*)this + 0x448), 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x450) - 0xa0, *(short*)((char*)this + 0x44a) + v4, 0x140 - *(short*)((char*)this + 0x448), 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x448), 0, 0x140 - *(short*)((char*)this + 0x448), 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x450) + 0xa0 - *(short*)((char*)this + 0x448), *(short*)((char*)this + 0x44a) + v4, *(short*)((char*)this + 0x448) - 0xa0, 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0, *(short*)((char*)this + 0x448) - 0xa0, 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0 - *(short*)((char*)this + 0x450) + 0xa0, *(short*)((char*)this + 0x44a) + v4, 0xa0, 0x30), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(*(short*)((char*)this + 0x448) - 0xa0, 0, 0xa0, 0x30), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        }
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(short*)((char*)this + 0x454) + 0x50, 0, 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x440), MakeRect(0, 0, 0x140, 0xf0), *((char*)this + 0x42e), 0);
    if (*((char*)this + 0x45e) < 2) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(short*)((char*)this + 0x458), 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x43c), MakeRect(0, 0, 0x140, 0xf0), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (*((char*)this + 0x45e) == 2) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x57, 0x5a, 0x99, 0x19), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x1da, 0x99, 0x19), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        if (*((char*)this + 0x45f) == 0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x68, 0x7c, 0x33, 0x15), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x1f3, 0x33, 0x15), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xb4, 0x7e, 0x1e, 0x10), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x26, 0x208, 0x1e, 0x10), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x6e, 0x7e, 0x26, 0xf), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x208, 0x26, 0xf), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xaf, 0x7c, 0x27, 0x14), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x33, 0x1f4, 0x27, 0x14), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        }
    } else if (*((char*)this + 0x45e) == 3) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x49, 9, 0xd6, 0x2a), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, (*(*(char**)((char*)this + 0x1c) + 0x1358) - 1) * 0x2a, 0xd6, 0x2a), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(9, 0x3b, 0x34, 0x12), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x161, 0x34, 0x12), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        Unk774a10(0x136, 0x3a, *(int*)((char*)this + 0x464));
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(9, 0x56, 0x6a, 0x1d), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x173, 0x6a, 0x1d), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        Unk774a10(0x136, 0x5b, *(int*)((char*)this + 0x468));
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(9, 0x75, 0x75, 0x21), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x190, 0x75, 0x21), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        Unk774a10(0x136, 0x7c, *(int*)((char*)this + 0x46c));
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(9, 0x9c, 0x7e, 0x16), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x1b1, 0x7e, 0x16), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        Unk774a10(0x136, 0x9d, *(int*)((char*)this + 0x470));
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(9, 0xbe, 0x4a, 0x12), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x34, 0x161, 0x4a, 0x12), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x12a, 0xbb, 0xb, 0x11), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xb2, 0x1c8, 0xb, 0x11), *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        Unk774a10(0x128, 0xba, *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d0));
        Unk774a10(0x136, 0xd7, *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30c8));
        if (*(DWORD*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30cc) > 0) {
            Unk774a10(0xc6, 0xd7, *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30cc));
            v8 = 1;
            for (; v8 < 8; v8++) {
                if ((double)*(DWORD*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30c8) / pow(0xa, 8 - v8) < 1.0) {
                    Unk774a10(v8 * 0xe + 0xc6, 0xd7, 0);
                }
            }
        }
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene5::Unk774a10(int p1, int p2, int p3)
{
    RECT v2c;
    int v1c;
    RECT l18;
    DWORD x8;
    int l4;

    x8 = p3;
    l4 = p1;
    do {
        v1c = x8 % 0xa;
        v2c.top = 0x1c7;
        v2c.bottom = 0x1da;
        v2c.left = v1c << 4;
        v2c.right = v1c + 1 << 4;
        l18.top = p2;
        l18.bottom = p2 + 0x13;
        l18.right = l4;
        l18.left = l4 - 0x10;
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(l18, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v2c, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l4 -= 0xe;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene5::Unk774b00()
{
    int x3c;
    int v38;
    char v34[40];
    char vc[8];

    v38 = rand() % *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x30f4);
    if (*(int*)((char*)this + 0x440) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x440))->Release();
        *(int*)((char*)this + 0x440) = 0;
    }
    if (*(int*)((char*)this + 0x43c) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x43c))->Release();
        *(int*)((char*)this + 0x43c) = 0;
    }
    strcpy(v34, "system\\");
    strcat(v34, (const char*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x94));
    strcat(v34, "\\");
    strcat(v34, (const char*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x94));
    if (1) {
        strcat(v34, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x440), (const char*)v34, 0, *(*(char**)((char*)this + 0x1c) + 0x134c) * 0x28 + 0x5f);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), (const char*)v34, *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8e) * 0x28, *(*(char**)((char*)this + 0x1c) + 0x134c) * 0x28 + 0x5f, 0x28);
    } else {
        strcat(v34, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x440), (const char*)v34, *(*(char**)((char*)this + 0x1c) + 0x134c) * 0x28 + 0x5f);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), (const char*)v34, *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x8e) * 0x28, *(*(char**)((char*)this + 0x1c) + 0x134c) * 0x28 + 0x5f, 0x28);
    }
    *((char*)this + 0x42e) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x440));
    x3c = 0;
    for (; x3c < 0x14; x3c++) {
        if (*(*(char**)((char*)this + (1 - *(*(char**)((char*)this + 0x1c) + 0x134c)) * 4 + 0xc) + 0x8d) == *(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x30f5 + x3c)) {
            v38 = x3c + 0xa;
        }
    }
    strcpy(v34, "system\\");
    strcat(v34, (const char*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x134c) * 4 + 0xc) + 0x94));
    strcat(v34, "\\");
    _itoa(v38, vc, 0xa);
    if (v38 < 0xa) {
        strcat(v34, "0");
    }
    strcat(v34, (const char*)vc);
    if (1) {
        strcat(v34, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v34, 0, 0xaf);
    } else {
        strcat(v34, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v34, 0xaf);
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 4) {
        if (*(*(char**)((char*)this + 0x1c) + 0x134c) == 0) {
            ((CharRecord*)(*(int*)((char*)this + 0xc) + 0x3118))->Load((const char*)(*(int*)((char*)this + 0xc) + 0x94));
            (*(int*)(*(char**)((char*)this + 0xc) + 0x311c))++;
            ((CharRecord*)(*(int*)((char*)this + 0xc) + 0x3118))->Save((const char*)(*(int*)((char*)this + 0xc) + 0x94));
            ((CharRecord*)(*(int*)((char*)this + 0x10) + 0x3118))->Load((const char*)(*(int*)((char*)this + 0x10) + 0x94));
            (*(int*)(*(char**)((char*)this + 0x10) + 0x3120))++;
            ((CharRecord*)(*(int*)((char*)this + 0x10) + 0x3118))->Save((const char*)(*(int*)((char*)this + 0x10) + 0x94));
        } else {
            ((CharRecord*)(*(int*)((char*)this + 0x10) + 0x3118))->Load((const char*)(*(int*)((char*)this + 0x10) + 0x94));
            (*(int*)(*(char**)((char*)this + 0x10) + 0x311c))++;
            ((CharRecord*)(*(int*)((char*)this + 0x10) + 0x3118))->Save((const char*)(*(int*)((char*)this + 0x10) + 0x94));
            ((CharRecord*)(*(int*)((char*)this + 0xc) + 0x3118))->Load((const char*)(*(int*)((char*)this + 0xc) + 0x94));
            (*(int*)(*(char**)((char*)this + 0xc) + 0x3120))++;
            ((CharRecord*)(*(int*)((char*)this + 0xc) + 0x3118))->Save((const char*)(*(int*)((char*)this + 0xc) + 0x94));
        }
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 2) {
        *(int*)((char*)this + 0x464) = *(DWORD*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30dc) / 0x64;
        *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d0) += *(int*)((char*)this + 0x464);
        *(int*)((char*)this + 0x468) = *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d4) << 1;
        *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d0) += *(int*)((char*)this + 0x468);
        *(int*)((char*)this + 0x46c) = *(DWORD*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d8) / 0x64;
        *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d0) += *(int*)((char*)this + 0x46c);
        *(int*)((char*)this + 0x470) = *(*(char**)((char*)this + 0x1c) + 0x1358) * 0x32 * (*(*(char**)((char*)this + (1 - *(*(char**)((char*)this + 0x1c) + 0x1342)) * 4 + 0xc) + 0xac) == 0);
        *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30d0) += *(int*)((char*)this + 0x470);
        ((CharRecord*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3118))->Load((const char*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x94));
        if (*(DWORD*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3128) < *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30cc)) {
            *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3124) = *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30c8);
            *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3128) = *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30cc);
        } else if (*(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3128) == *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30cc) && *(DWORD*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3124) < *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30c8)) {
            *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3124) = *(int*)(*(char**)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x30c8);
        }
        ((CharRecord*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x3118))->Save((const char*)(*(int*)((char*)this + *(*(char**)((char*)this + 0x1c) + 0x1342) * 4 + 0xc) + 0x94));
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x1370) == 2) {
        if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) == 0) {
            ((CharRecord*)(*(int*)((char*)this + 0xc) + 0x3118))->Load((const char*)(*(int*)((char*)this + 0xc) + 0x94));
            if (*(DWORD*)(*(char**)((char*)this + 0xc) + 0x3130) < *(int*)(*(char**)((char*)this + 0xc) + 0x30d4)) {
                *(int*)(*(char**)((char*)this + 0xc) + 0x3130) = *(int*)(*(char**)((char*)this + 0xc) + 0x30d4);
            }
            if (*(DWORD*)(*(char**)((char*)this + 0xc) + 0x3134) < *(int*)(*(char**)((char*)this + 0xc) + 0x30d8)) {
                *(int*)(*(char**)((char*)this + 0xc) + 0x3134) = *(int*)(*(char**)((char*)this + 0xc) + 0x30d8);
            }
            ((CharRecord*)(*(int*)((char*)this + 0xc) + 0x3118))->Save((const char*)(*(int*)((char*)this + 0xc) + 0x94));
        }
        if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1344) == 0) {
            ((CharRecord*)(*(int*)((char*)this + 0x10) + 0x3118))->Load((const char*)(*(int*)((char*)this + 0x10) + 0x94));
            if (*(DWORD*)(*(char**)((char*)this + 0x10) + 0x3130) < *(int*)(*(char**)((char*)this + 0x10) + 0x30d4)) {
                *(int*)(*(char**)((char*)this + 0x10) + 0x3130) = *(int*)(*(char**)((char*)this + 0x10) + 0x30d4);
            }
            if (*(DWORD*)(*(char**)((char*)this + 0x10) + 0x3134) < *(int*)(*(char**)((char*)this + 0x10) + 0x30d8)) {
                *(int*)(*(char**)((char*)this + 0x10) + 0x3134) = *(int*)(*(char**)((char*)this + 0x10) + 0x30d8);
            }
            ((CharRecord*)(*(int*)((char*)this + 0x10) + 0x3118))->Save((const char*)(*(int*)((char*)this + 0x10) + 0x94));
        }
    }
    *(short*)((char*)this + 0x444) = 0xf0;
    *(short*)((char*)this + 0x446) = 0x12;
    *(short*)((char*)this + 0x448) = 0;
    *(short*)((char*)this + 0x44a) = 0;
    *(short*)((char*)this + 0x44c) = 0;
    *(short*)((char*)this + 0x44e) = 0;
    *(short*)((char*)this + 0x450) = -2;
    *(short*)((char*)this + 0x454) = 0x140;
    *(short*)((char*)this + 0x458) = -0xf0;
    *(short*)((char*)this + 0x452) = 9;
    *(short*)((char*)this + 0x456) = 0xf;
    *(short*)((char*)this + 0x45a) = 0xf;
    *(short*)((char*)this + 0x45c) = 0;
    if (*(*(char**)((char*)this + 0x1c) + 0x134c) == 1) {
        *(double*)(*(char**)((char*)this + 0xc) + 0x20) = 480.0;
        *(double*)(*(char**)((char*)this + 0xc) + 0x28) = -240.0;
        *(*(char**)((char*)this + 0xc) + 0x50) = -1;
        *(short*)(*(char**)((char*)this + 0xc) + 8) = 0x2f;
        ((CPlayer*)*(int*)((char*)this + 0xc))->Vf0();
        ((CPlayer*)*(int*)((char*)this + 0xc))->Unk40f1e0();
        *(int*)(*(char**)((char*)this + 0xc) + 0x30bc) = 0;
        *(*(char**)((char*)this + 0xc) + 0x2bc0) = 0;
        *(*(char**)((char*)this + 0xc) + 0x2bc2) = 0;
        *(*(char**)((char*)this + 0xc) + 0x58) = 0;
        *(double*)(*(char**)((char*)this + 0xc) + 0xb8) = 0.0;
        *(double*)(*(char**)((char*)this + 0x10) + 0xb8) = 0.0;
        return;
    }
    *(double*)(*(char**)((char*)this + 0x10) + 0x20) = 480.0;
    *(double*)(*(char**)((char*)this + 0x10) + 0x28) = -240.0;
    *(*(char**)((char*)this + 0x10) + 0x50) = -1;
    *(short*)(*(char**)((char*)this + 0x10) + 8) = 0x2f;
    ((CPlayer*)*(int*)((char*)this + 0x10))->Vf0();
    ((CPlayer*)*(int*)((char*)this + 0x10))->Unk40f1e0();
    *(int*)(*(char**)((char*)this + 0x10) + 0x30bc) = 0;
    *(*(char**)((char*)this + 0x10) + 0x2bc0) = 0;
    *(*(char**)((char*)this + 0x10) + 0x2bc2) = 0;
    *(*(char**)((char*)this + 0x10) + 0x58) = 0;
    *(double*)(*(char**)((char*)this + 0xc) + 0xb8) = 0.0;
    *(double*)(*(char**)((char*)this + 0x10) + 0xb8) = 0.0;
}

void CScene5::Vf2()
{
    int l10c;
    char v108[256];

    l10c = ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        *((char*)this + 0x2d) = 1;
        *(*(char**)((char*)this + 0x1c) + 0x1378) = 0;
    }
}
