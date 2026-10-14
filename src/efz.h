// Shared declarations recovered from efz.exe 4.02.
//
// Annotations give the original address of each definition:
//   // FUNCTION: 0x401000      a function or method
//   // GLOBAL: 0x790150        a global variable
//   // SIZE: 0x142f0           sizeof a class, from the original `new` call
// Names starting with Unk are placeholders until the function is understood.
// Classes are padded to their original size; fields are named as they are recovered.
#ifndef EFZ_H
#define EFZ_H

#include <windows.h>
#include <string.h>

// FUNCTION: 0x405a20
// Opens the config file and returns the byte at the given offset.
BYTE ReadConfigByte(int offset);

// DirectDraw wrapper.
class CGraphics {
public:
    // FUNCTION: 0x401950
    // Defined inline, so the copy main.obj uses is placed right after main.obj's code.
    CGraphics()
    {
        unk4 = 0;
        for (int i = 0; i < 0x200; i++)
            quarterSquares[i] = (i - 0x100) * (i - 0x100) / 4;
    }
    // FUNCTION: 0x408b50
    ~CGraphics();
    // FUNCTION: 0x4083b0
    void Init(HWND hWnd, BYTE mode);
    // FUNCTION: 0x408a60
    // Restores the display mode and releases the DirectDraw objects.
    void Shutdown();

    int unk0;
    BYTE unk4;
    char unk5[0x20406 - 5];
    // (i - 256)^2 / 4 for i in 0..511: a quarter-squares table, so that
    // a * b == quarterSquares[256 + a + b] - quarterSquares[256 + a - b].
    short quarterSquares[0x200];
    IUnknown* unk20808; // IDirectDraw7, judging by RestoreDisplayMode at vtable +0x4c
    IUnknown* unk2080c;
    IUnknown* unk20810;
    IUnknown* unk20814;
};

// DirectInput wrapper.
class CInput {
public:
    // FUNCTION: 0x40c5e0
    CInput();
    // FUNCTION: 0x40c990
    ~CInput();
    // FUNCTION: 0x40c6f0
    void Init(HWND hWnd);
    // FUNCTION: 0x40c880
    // Unacquires and releases the DirectInput devices.
    void Shutdown();
    // FUNCTION: 0x40d460
    void Unk40d460(int value);
    // FUNCTION: 0x40d140
    void Unk40d140();

    char unk[0x1f8]; // TODO: size and layout
};

// DirectSound wrapper.
class CSound {
public:
    // FUNCTION: 0x40d810
    CSound();
    // FUNCTION: 0x40d870
    ~CSound();
    // FUNCTION: 0x40d9f0
    void Init(HWND hWnd);
    // FUNCTION: 0x40d930
    // Releases all 150 sound buffers and the DirectSound object.
    void Shutdown();
    // FUNCTION: 0x40e4d0
    void Unk40e4d0(short value);
};

// Abstract base of the object held for each player (inferred: one per side, since there
// are two of them and the destructor releases sound slots and per-character arrays).
// Its vtable at 0x787bcc has one implemented slot and eight pure virtual ones.
class CPlayer {
public:
    // FUNCTION: 0x40ecb0
    ~CPlayer();

    virtual void Unk0();
    virtual void Unk1() = 0;
    virtual void Unk2() = 0;
    virtual void Unk3() = 0;
    virtual void Unk4() = 0;
    virtual void Unk5() = 0;
    virtual void Unk6() = 0;
    virtual void Unk7() = 0;
    virtual void Unk8() = 0;
};

// A frame of an effect animation.
struct EffectFrame {
    WORD duration; // in game frames
    WORD unk2;
    int unk4;
    int unk8;
};

// Animation of one effect type: CGame::m_effectAnims is indexed by Effect::type.
struct EffectAnim {
    BYTE frameCount;
    BYTE unk1;
    WORD unk2;
    EffectFrame* frames;
};

// One running effect (sparks, debris, screen flashes...). CGame keeps 640 of them in a
// ring buffer.
struct Effect {
    WORD type;   // index into CGame::m_effectAnims, and the case in UpdateEffect
    WORD frame;  // current animation frame
    WORD timer;  // game frames spent on the current animation frame
    short unk6;
    int unk8;
    int unkc;
    int unk10;
    int unk14;
    double x;
    double y;
    double vx;
    double vy;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    BYTE unk48;
    BYTE unk49;
    short unk4a;
    int side;    // 0 or 1; (side * 2 - 1) mirrors horizontal motion
    BYTE unk50;
    BYTE unk51;
    short unk52;
    int unk54;
    int unk58;
    int unk5c;
    int unk60;
    int unk64;
    int unk68;
    BYTE unk6c;
    BYTE unk6d;
    short unk6e;
};

// Parameters for CGame::CreateEffect, built on the stack by the caller.
struct EffectDesc {
    // FUNCTION: 0x405490
    EffectDesc() { memset(this, 0, sizeof(*this)); }

    int unk0;    // stored per slot in CGame::m_effectUnk1d84
    short type;
    short unk6;
    double x;
    double y;
    BYTE unk18;  // copied to Effect::unk48
    BYTE unk19;
    short unk1a;
    int side;
    BYTE unk20;  // copied to Effect::unk50
    BYTE unk21;  // copied to Effect::unk51
    short unk22;
    int unk24;   // copied to Effect::unk54
    int unk28;
    BYTE unk2c;  // copied to Effect::unk6c
    BYTE unk2d;
    short unk2e;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
};

// SIZE: 0x142f0
class CGame {
public:
    // FUNCTION: 0x406070
    CGame(CGraphics* graphics, CInput* input, CSound* sound);
    // FUNCTION: 0x406260
    ~CGame();
    // FUNCTION: 0x406780
    void Unk406780();
    // FUNCTION: 0x406e60
    void Unk406e60();
    // FUNCTION: 0x406aa0
    void Unk406aa0();
    // FUNCTION: 0x401c20
    // Runs one frame of the effect in slot `index`: its type-specific behaviour, then
    // its animation. Removes the effect when the animation ends.
    void UpdateEffect(short index);
    // FUNCTION: 0x407100
    // Starts an effect in the next free ring-buffer slot.
    void CreateEffect(EffectDesc* desc);
    // FUNCTION: 0x4072a0
    void RemoveEffect(short index);

    char unk0[0x38];
    IUnknown* m_surfaces[0x398];  // released by ~CGame
    IUnknown* unke98;
    IUnknown* unke9c;
    IUnknown* unkea0;
    short m_sounds[0x41];         // sound IDs; 0x96 means none
    short unkf26;                 // sound ID passed to the sound system every frame
    char unkf28[0x134d - 0xf28];
    char unk134d;
    char unk134e[2];
    BYTE unk1350;
    char unk1351[0x1366 - 0x1351];
    char unk1366;
    char unk1367;
    BOOL unk1368;                 // toggled every frame by WinMain
    char unk136c[0x1380 - 0x136c];
    short m_effectHead;           // next slot CreateEffect uses
    short m_effectTail;           // oldest live slot
    int m_effectActive[0x280];
    int m_effectUnk1d84[0x280];
    BYTE m_effectUnk2784[0x280];
    char unk2a04[4];
    Effect m_effects[0x280];
    EffectAnim* m_effectAnims;
    char unk1420c[0x14294 - 0x1420c];
    int unk14294;                 // spawn counter for the ellipse effects (0x26, 0x35, 0x36)
    int unk14298;                 // random angle in degrees, 0..359
    int unk1429c;                 // unk14298 plus 30..149 degrees
    int unk142a0;
    int unk142a4;
    char unk142a8[0x142f0 - 0x142a8];
};

// Base of the top-level game states. Update() runs one frame and returns the
// index of the state to run next.
class CScene {
public:
    virtual void Unk0();
    virtual BYTE Update();

    UINT lastMessage; // set by WndProc to the message it is handling
};

#define DECLARE_SCENE(name, size)                                                           \
    class name : public CScene {                                                            \
    public:                                                                                 \
        name(HWND hWnd, CPlayer** player1, CPlayer** player2, CGame* game,                  \
             CGraphics* graphics, CInput* input, CSound* sound);                            \
        char unk[size - 8];                                                                 \
    }

// FUNCTION: 0x775d60
DECLARE_SCENE(CScene0, 0x44c);
// FUNCTION: 0x753260
DECLARE_SCENE(CScene1, 0x560);
// FUNCTION: 0x76c6f0
DECLARE_SCENE(CScene2, 0x438);
// FUNCTION: 0x7633a0
DECLARE_SCENE(CScene3, 0x598);
// FUNCTION: 0x7712f0
DECLARE_SCENE(CScene5, 0x474);
// FUNCTION: 0x759f30
DECLARE_SCENE(CScene6, 0x760);
// FUNCTION: 0x7758b0
DECLARE_SCENE(CScene7, 0x448);
// FUNCTION: 0x76e480
DECLARE_SCENE(CScene8, 0x758);

#endif
