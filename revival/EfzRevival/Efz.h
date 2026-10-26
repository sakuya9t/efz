// efz.exe 4.02 as EfzRevival.dll sees it: the globals it reads and patches and the parts
// of the game's objects it touches. The names are the game's decompilation's (src/efz.h,
// src/main.cpp, src/scene3.cpp); fields it hasn't named keep their offset. Offsets in
// the comments are the game's, from the start of each object.
#pragma once
#include <winsock2.h>          // before windows.h, for boost.asio
#include <windows.h>
#include <ddraw.h>
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0700
#endif
#include <dinput.h>
#include <mmsystem.h>
#include <dsound.h>

class CGame;

// One sprite frame of an animation (the game's EffectFrame): the hotspot and size are
// what the box display uses.
struct SpriteRect {
    short x;                    // 0x0 hotspot within the frame
    short y;                    // 0x2
    short width;                // 0x4
    short height;               // 0x6
};

struct SpriteFrame {
    WORD duration;              // 0x0 in game frames
    WORD surface;               // 0x2
    SpriteRect rect;            // 0x4
};

// The animation of one pattern (the game's EffectAnim), 8 bytes.
struct SpriteAnim {
    BYTE frameCount;
    BYTE unk1;
    WORD unk2;
    SpriteFrame *frames;        // 0x4
};

// One frame of a pattern's data, read from <character>.pat (src/efz.h PatternFrame).
struct PatternFrame {
    RECT hurtBoxes[5];          // 0x00
    RECT hitBoxes[4];           // 0x50
    RECT collisionBox;          // 0x90
    short unka0;
    short unka2;
    float unka4;
    short unka8;
    WORD flagsAA;               // 0xaa: 0x40 the attack may hit again
    short unkac;
    short unkae;
    WORD flagsB0;               // 0xb0: 0x20 no hurtboxes (invincible)
    short unkb2;
    short unkb4;
    short unkb6;
    float unkb8;
    float unkbc;
    char unkc0;
    char unkc1;
    short unkc2;
    short unkc4;
    short unkc6;
};

// A pattern's frames (src/efz.h PatternData), 8 bytes: CPlayer+0x164 holds 505.
struct PatternData {
    short unk0;
    short unk2;
    PatternFrame *frames;       // 0x4
};

// A snapshot of a player's frame, position and facing, as CScene3 gathers them for its
// collision checks (src/efz.h CollisionInfo). 0xf0 bytes.
struct CollisionInfo {
    PatternFrame frame;         // 0x00
    SpriteFrame sprite;         // 0xc8
    double x;                   // 0xd8
    double y;                   // 0xe0
    char facing;                // 0xe8 CPlayer+0x50
    char unke9;
    short unkea;
    int unkec;
};

// One of the 64 objects (projectiles, effects with boxes) a player spawns, 0x98 bytes;
// it starts with the game's ObjBase.
struct PlayerObject {
    short pattern;              // 0x00
    short frame;                // 0x02
    char unk4[0x80 - 0x04];
    int unk80;                  // 0x80 nonzero once the object has hit
    short unk84;                // 0x84 nonzero while it can be hit
    char unk86[0x98 - 0x86];
};

// A character (src/efz.h CPlayer, 0x3138 bytes, with ObjBase at 8).
class CPlayer {
public:
    void *vtable;               // 0x000
    int unk4;
    short pattern;              // 0x008 the current action
    short frame;                // 0x00a
    short unkc;                 // 0x00c frame counter of the action
    short unke;
    SpriteAnim *anims;          // 0x010 one per pattern
    char unk14[0x20 - 0x14];
    double x;                   // 0x020
    double y;                   // 0x028
    double vx;                  // 0x030
    double vy;                  // 0x038
    char unk40[0x50 - 0x40];
    char facing;                // 0x050 1 or -1
    char unk51[0x78 - 0x51];
    short **unk78;              // 0x078 *unk78[2] is the opponent's action
    CGame *game;                // 0x07c
    char unk80[0x8d - 0x80];
    char character;             // 0x08d
    BYTE palette;               // 0x08e
    char unk8f[0xac - 0x8f];
    BYTE unkac;                 // 0x0ac
    char unkad[0x124 - 0xad];
    short unk124;               // 0x124
    short unk126;
    int unk128;                 // 0x128
    char unk12c[0x134 - 0x12c];
    float unk134;               // 0x134
    char unk138[0x13c - 0x138];
    char unk13c;                // 0x13c nonzero: no hurtboxes
    char unk13d[0x14a - 0x13d];
    short unk14a;               // 0x14a
    char unk14c[0x164 - 0x14c];
    PatternData *patterns;      // 0x164
    char unk168[0x16c - 0x168];
    char unk16c;                // 0x16c nonzero while the attack has not hit yet
    char unk16d[0x2ca - 0x16d];
    char objectEnd;             // 0x2ca the objects in use run from objectStart
    char unk2cb;
    char objectStart;           // 0x2cc   to objectEnd, wrapping at 64
    char unk2cd[0x3d0 - 0x2cd];
    int objectActive[64];       // 0x3d0
    PlayerObject objects[64];   // 0x4d0
};

// DirectInput: the keyboard and two joysticks (src/efz.h CInput). Each player's
// bindings are a 16-byte block, swapped whole when the players are switched.
struct KeyBindings {
    short keys[8];              // right, left, down, up, the four buttons
};

class CInput {
public:
    char keyState[0x100];       // 0x000
    char unk100[0x20];
    DIJOYSTATE joyState[2];     // 0x120
    KeyBindings bindings[2];    // 0x1c0
    HWND hwnd;                  // 0x1e0
    IDirectInput7 *di;          // 0x1e4
    IDirectInputDevice7 *devices[3];  // 0x1e8 the keyboard, then the joysticks
    int unk1f4;
};

// DirectSound (src/efz.h CSound): 150 sounds, 0x96 means none.
class CSound {
public:
    DWORD loopLength;
    DWORD loopEnd;
    HWND hwnd;
    IDirectSound *ds;
    BYTE *data[0x96];
    DWORD size[0x96];
    IDirectSoundBuffer *buffers[0x96];  // 0x4c0
};

// A replay file (src/efz.h CReplayFile): EfzRevival.cpp replaces its methods, and the
// handle then holds the DLL's stream (EfzReplay.h).
struct CReplayFile {
    BOOL eof;
    HANDLE handle;
    DWORD remaining;
    DWORD read;
};

// The shared game state (src/efz.h CGame, 0x142f0 bytes).
class CGame {
public:
    char unk0[0xf26];
    WORD music;                 // 0x0f26 the music's sound ID
    char unkf28[0xf35 - 0xf28];
    PALETTEENTRY palette[0x100];  // 0x0f35; each player's colours are 95 + 40 * player
    char unk1335[0x1338 - 0x1335];
    BOOL hasPalette[2];         // 0x1338 per player: a palette was chosen (read as a bool)
    char unk1340[0x1343 - 0x1340];
    char unk1343;               // 0x1343 the side a human plays (single player)
    char unk1344[0x134c - 0x1344];
    char unk134c;               // 0x134c
    char unk134d;
    char unk134e;
    BYTE unk134f;               // 0x134f
    char unk1350[0x1364 - 0x1350];
    BYTE unk1364;               // 0x1364 the game mode's menu entry
    BYTE unk1365;
    char unk1366;               // 0x1366
    char unk1367;
    char unk1368;               // 0x1368 (a BOOL WinMain toggles every frame)
    char unk1369[3];
    char unk136c;               // 0x136c
    char unk136d[3];
    BYTE unk1370;
    char unk1371[0x137c - 0x1371];
    void *background;           // 0x137c the stage's animated background (CAnimBg)
    char unk1380[0x14283 - 0x1380];
    char replayMode;            // 0x14283 0 none, 1 playing, 2 recording
    CReplayFile replay;         // 0x14284
    char unk14294[0x142f0 - 0x14294];
};

// The scenes WinMain runs (src/efz.h CScene): 0 title, 1 character select, 2 versus
// screen, 3 the fight, ...
class CScene {
public:
    virtual void Draw() = 0;
    virtual BYTE Update() = 0;  // the next scene
    virtual void Vf2() = 0;

    UINT lastMessage;
    HWND hwnd;
    CPlayer *player1;           // 0x0c
    CPlayer *player2;
    CPlayer **players[2];       // 0x14 WinMain's g_player1 and g_player2
    CGame *game;                // 0x1c
    void *graphics;
    CInput *input;
    CSound *sound;
    char unk2c;
    char unk2d;                 // 0x2d the fight: 1 round over, 2 match over
    BYTE unk2e[2];
};

// The title screen and its menu (scene 0).
class CScene0 : public CScene {
public:
    char unk30[0x43c - 0x30];
    char menuChoice;            // 0x43c 2 VS COM, 3 VS PLAYER, 4 replay ...
};

// Character select (scene 1).
class CScene1 : public CScene {
public:
    char unk30[0x49e - 0x30];
    char unk49e[2];             // 0x49e per player: 6 once the choice is final
    char unk4a0[0x53c - 0x4a0];
    char character[2];          // 0x53c
    char palette[2];            // 0x53e
};

// The fight (scene 3, src/efz.h CScene3).
class CScene3 : public CScene {
public:
    char unk30[0x45c - 0x30];
    POINT camera;               // 0x45c
    char unk464[0x578 - 0x464];
    char speed;                 // 0x578 3 normally, 0 stops the fight
};

// DDRAW.dll's screen palette: its IDirectDrawPalette, with a method of its own after
// COM's that gives the colours it holds.
struct ProxyPalette : public IDirectDrawPalette {
    virtual void unknown1c() = 0;
    virtual void getColors(PALETTEENTRY **colors) = 0;
};

// The size of each character's CPlayer (efz.exe's `new`, src/efz.h SIZE), by character
// number. Each object that includes this header has its own copy (fifteen in the DLL).
static int g_characterSizes[25] = {
    0x3470, 0x3450, 0x3458, 0x3450, 0x3450, 0x3448, 0x34b0, 0x3448, 0x3458, 0x3458,
    0x3460, 0x3458, 0x3468, 0x3450, 0x3478, 0x3478, 0x3468, 0x3458, 0x3460, 0x3458,
    0x3478, 0x3458, 0x3460, 0x3488, 0x3460,
};

// --- Globals (src/main.cpp) ------------------------------------------------------------

// efz.exe 0x79010c: g_game
#define EFZ_GAME (*(CGame **)0x79010c)
// efz.exe 0x790110: g_scenes
#define EFZ_SCENES ((CScene **)0x790110)
// efz.exe 0x790148: g_scene, the current scene
#define EFZ_SCENE (*(int *)0x790148)
// efz.exe 0x790150: g_graphics (CGraphics)
#define EFZ_GRAPHICS ((void *)0x790150)
// CGraphics::m_ddpal, the screen palette (g_graphics + 0x20814)
#define EFZ_DDPALETTE (*(ProxyPalette **)0x7b0964)
// CGraphics::m_back, the back buffer (g_graphics + 0x20810)
#define EFZ_BACK_BUFFER (*(IDirectDrawSurface **)0x7b0960)
// efz.exe 0x7b0968: g_inputDev
#define EFZ_INPUT ((CInput *)0x7b0968)
// efz.exe 0x7b0b60: g_sound
#define EFZ_SOUND ((CSound *)0x7b0b60)
// efz.exe 0x7b128c: g_joystickCount (src/input.cpp)
#define EFZ_JOYSTICK_COUNT (*(char *)0x7b128c)
// efz.exe 0x7b1290: g_fkeyHeld (src/scene3.cpp)
#define EFZ_FKEY_HELD ((void *)0x7b1290)

// --- Functions -------------------------------------------------------------------------

// efz.exe 0x40b8a0: CGraphics::BuildBlendTables
typedef void (__thiscall *BuildBlendTablesFn)(void *graphics, PALETTEENTRY *palette);
#define EFZ_BUILD_BLEND_TABLES ((BuildBlendTablesFn)0x40b8a0)
// efz.exe 0x40cae0: EnumJoysticks, CInput::Init's callback
#define EFZ_ENUM_JOYSTICKS ((LPDIENUMDEVICESCALLBACK)0x40cae0)
// efz.exe 0x40d140: CInput::LoadBindings (key.ini)
typedef void (__thiscall *LoadBindingsFn)(CInput *input);
#define EFZ_LOAD_BINDINGS ((LoadBindingsFn)0x40d140)
// efz.exe 0x7631f0: CScene3::Unk7631f0, drawn by CScene3::Draw after the players
typedef void (__thiscall *DrawFightFn)(CScene3 *fight);
#define EFZ_DRAW_FIGHT ((DrawFightFn)0x7631f0)
// efz.exe 0x767600: CScene3::Unk767600: an object's box in the fight's coordinates
// efz.exe 0x7677a0: CScene3::Unk7677a0: the same from a CollisionInfo
// Members that don't use their scene: called without one, with the RECT they return
// by value given as the first argument (and returned).
typedef RECT *(__stdcall *ObjectBoxFn)(RECT *result, PlayerObject *object, RECT *box);
typedef RECT *(__stdcall *InfoBoxFn)(RECT *result, CollisionInfo *info, RECT *box);
#define EFZ_OBJECT_BOX ((ObjectBoxFn)0x767600)
#define EFZ_INFO_BOX ((InfoBoxFn)0x7677a0)
