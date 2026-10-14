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

// FUNCTION: 0x405a20
// Opens the config file and returns the byte at the given offset.
BYTE ReadConfigByte(int offset);

// DirectDraw wrapper.
class CGraphics {
public:
    // FUNCTION: 0x4083b0
    void Init(HWND hWnd, BYTE mode);
    // FUNCTION: 0x408a60
    // Restores the display mode and releases the DirectDraw objects.
    void Shutdown();

    char unk[0x20808];
    IUnknown* unk20808; // IDirectDraw7, judging by RestoreDisplayMode at vtable +0x4c
    IUnknown* unk2080c;
    IUnknown* unk20810;
    IUnknown* unk20814;
};

// DirectInput wrapper.
class CInput {
public:
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

    char unk0[0xf26];
    short unkf26;
    char unkf28[0x1368 - 0xf28];
    BOOL unk1368;
    char unk136c[0x142f0 - 0x136c];
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
