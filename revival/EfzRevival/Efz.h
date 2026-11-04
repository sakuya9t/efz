// efz.exe 4.02 as EfzRevival.dll sees it: the globals it reads and patches and the parts
// of the game's objects it touches. Members and constants have the names of the game's
// decompilation (src/efz.h, src/main.cpp, src/scene3.cpp), so they can be looked up there;
// the pattern frame's boxes keep the names the box display gives them. Bytes the DLL
// doesn't touch are padding named for their offset (unk<offset>). Offsets in the
// comments are the game's, from the start of each object.
//
// Types are the DLL's, not always the game's: where the DLL reads a byte of a wider
// member (m_invulTime, m_hitsLeft, m_objectHead), the member is that byte, and the code
// compiles to the original's reads. Each class has as many members as it had before the
// names, and the constants are macros, not enums: the order of the DLL's strings follows
// a count of what the compiler meets in every object (docs/revival.md, "Strings"), which
// a macro can't move.
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

// --- Constants (src/efz.h) -------------------------------------------------------------

// Shared actions, the values of CPlayer::pattern every character has.
#define kFirstHitReaction 0x32  // the first hit reaction (0x32-0x95)
#define kWakeUp 0x60            // getting up after kLyingDown
#define kKnockdownHittable 0x61 // hitting the ground, can be hit
#define kKnockdown 0x62         // the usual ground hit after an air hit, invulnerable
#define kLyingDown 0x63         // lies on the ground, then kWakeUp
#define kFirstGuard 0x96        // the first guard reaction (0x96-0x9c)
#define kGuardStandMedium 0x97
#define kGuardCrouchLight 0x99
#define kGuardAir 0x9c
#define kRecoilGuardStand 0xa8  // a guard within 30 ticks of pressing back
#define kRecoilGuardCrouch 0xa9
#define kRecoilGuardAir 0xaa

// Mishio's (character 15) CMishio::kObjFieldHit: the hits of 22A/22B's field, 1 hit,
// one animation.
#define kMishioFieldHit 0x199

// Bits of PatternFrame::flagsAA (the attack) and flagsB0 (the state).
#define kAttackThrow 0x40       // a throw: tests the defender's push box (collisionBox)
#define kStateInvulnerable 0x20 // not hit at all

// The input bits of a player's tick (CInput::GetInput): the direction on the screen,
// then the buttons.
#define kInputRight 0x1
#define kInputLeft 0x2
#define kInputDown 0x4
#define kInputUp 0x8
#define kInputA 0x10
#define kInputB 0x20
#define kInputC 0x40
#define kInputD 0x80

// --- Objects ---------------------------------------------------------------------------

// One sprite frame of an animation (the game's EffectFrame, whose x, y, width and height
// this nests): the hotspot and size are what the box display uses.
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

// One frame of a pattern's data, read from <character>.pat (src/efz.h PatternFrame). The
// boxes are named for what the box display draws them as (the game's boxes, attackBoxes
// and pushBox).
struct PatternFrame {
    RECT hurtBoxes[5];          // 0x00 blue
    RECT hitBoxes[4];           // 0x50 red
    RECT collisionBox;          // 0x90 yellow: the push box, which keeps the players
                                //   apart, is what throws test and where objects clash
    short damage;               // 0xa0
    short unka2;
    float proration;            // 0xa4
    short chipDamage;           // 0xa8
    WORD flagsAA;               // 0xaa the attack's kAttack bits
    short airHitPattern;        // 0xac
    short groundHitPattern;     // 0xae
    WORD flagsB0;               // 0xb0 the state's kState bits
    short untechTime;           // 0xb2
    short gaugeOnHit;           // 0xb4
    short gaugeOnGuard;         // 0xb6
    float hitVx;                // 0xb8
    float hitVy;                // 0xbc
    char hitEffect;             // 0xc0
    char hitSound;              // 0xc1
    short attackerHitstop;      // 0xc2
    short defenderHitstop;      // 0xc4
    short unkc6;
};

// A pattern's frames (src/efz.h PatternData), 8 bytes: CPlayer::m_patterns holds 505.
struct PatternData {
    short level;
    short cancelLevel;
    PatternFrame *frames;       // 0x4
};

// A snapshot of a player's frame, position and facing, as CScene3 gathers them for its
// collision checks (src/efz.h CollisionInfo; its anim is sprite here). 0xf0 bytes.
struct CollisionInfo {
    PatternFrame frame;         // 0x00
    SpriteFrame sprite;         // 0xc8
    double x;                   // 0xd8
    double y;                   // 0xe0
    char facing;                // 0xe8 CPlayer::facing
    char attackResult;          // 0xe9 CPlayer::m_attackResult
    short hitsLeft;             // 0xea CPlayer::m_hitsLeft
    int unkec;                  // 0xec padding to the double's alignment
};

// One of the 64 objects (projectiles, effects with boxes) a player spawns, 0x98 bytes;
// it starts with the game's ObjBase.
struct PlayerObject {
    short pattern;              // 0x00
    short frame;                // 0x02
    char unk4[0x80 - 0x04];
    int attackResult;           // 0x80 nonzero once the object's attack has connected
    short hitsLeft;             // 0x84 hits it can still land
    char unk86[0x98 - 0x86];
};

// A character (src/efz.h CPlayer, 0x3138 bytes, with ObjBase at 8).
class CPlayer {
public:
    void *vtable;               // 0x000
    int unk4;                   // 0x004 padding: ObjBase starts at 8
    short pattern;              // 0x008 the current action
    short frame;                // 0x00a the frame of the pattern's animation
    short timer;                // 0x00c game frames spent on the current frame
    short unke;
    SpriteAnim *anims;          // 0x010 one per pattern
    char unk14[0x20 - 0x14];
    double x;                   // 0x020
    double y;                   // 0x028 0 on the ground, negative in the air
    double vx;                  // 0x030
    double vy;                  // 0x038
    char unk40[0x50 - 0x40];
    char facing;                // 0x050 1 or -1
    char unk51[0x78 - 0x51];
    // The other player's slot, WinMain's g_player1 or g_player2 (the game's CPlayer**).
    // Game::isHit reads m_opponent[2] as the opponent's action, see there.
    short **m_opponent;         // 0x078
    CGame *m_game;              // 0x07c
    char unk80[0x8d - 0x80];
    char m_charId;              // 0x08d the character's number on the select screen
    BYTE m_paletteIndex;        // 0x08e which <name>N.pal (N = index + 1)
    char unk8f[0xac - 0x8f];
    BYTE m_roundsWon;           // 0x0ac rounds won in this match
    char unkad[0x124 - 0xad];
    short m_untechTime;         // 0x124 ticks before an air recovery is allowed
    short unk126;
    int m_noAirRecovery;        // 0x128 set by a hit with flagsAA 0x400
    char unk12c[0x134 - 0x12c];
    float m_guardGauge;         // 0x134 0-360; an air recovery waits until it is empty
    char unk138[0x13c - 0x138];
    char m_invulTime;           // 0x13c the low byte of the game's short: while > 0 the
                                //   player can't be hit
    char unk13d[0x14a - 0x13d];
    short m_hitstop;            // 0x14a ticks the player is stopped by hitstop
    char unk14c[0x164 - 0x14c]; // 0x14e m_recoilGuardWindow (Recorder::setRecoilGuard)
    PatternData *m_patterns;    // 0x164 one per pattern, 505 of them
    char unk168[0x16c - 0x168];
    char m_hitsLeft;            // 0x16c the low byte of the game's short: hits the
                                //   current attack can still land
    char unk16d[0x2ca - 0x16d];
    // The objects in use run from m_objectTail to m_objectHead, wrapping at 64 (the
    // game's shorts; the DLL reads their low bytes).
    char m_objectHead;          // 0x2ca where the next object goes
    char unk2cb;
    char m_objectTail;          // 0x2cc the oldest object
    char unk2cd[0x3d0 - 0x2cd];
    int m_objectActive[64];     // 0x3d0
    PlayerObject m_objects[64]; // 0x4d0
};

// DirectInput: the keyboard and two joysticks (src/efz.h CInput). Each player's
// bindings are a 16-byte block, swapped whole when the players are switched.
struct KeyBindings {
    short keys[8];              // right, left, down, up, the four buttons
};

class CInput {
public:
    char m_keyState[0x100];     // 0x000
    char unk100[0x20];
    DIJOYSTATE m_joyState[2];   // 0x120
    KeyBindings m_bindings[2];  // 0x1c0
    HWND m_hwnd;                // 0x1e0
    IDirectInput7 *m_di;        // 0x1e4
    IDirectInputDevice7 *m_devices[3];  // 0x1e8 m_keyboard, then m_joysticks[2]
    int unk1f4;
};

// DirectSound (src/efz.h CSound): 150 sounds, 0x96 means none.
class CSound {
public:
    DWORD m_loopLength;
    DWORD m_loopEnd;
    HWND m_hwnd;
    IDirectSound *m_ds;
    BYTE *m_data[0x96];
    DWORD m_size[0x96];
    IDirectSoundBuffer *m_buffers[0x96];  // 0x4c0
};

// A replay file (src/efz.h CReplayFile): EfzRevival.cpp replaces its methods, and the
// handle then holds the DLL's stream (EfzReplay.h).
struct CReplayFile {
    BOOL m_eof;
    HANDLE m_handle;
    DWORD m_remaining;
    DWORD m_read;
};

// The shared game state (src/efz.h CGame, 0x142f0 bytes).
class CGame {
public:
    char unk0[0xf26];
    WORD m_music;               // 0x0f26 the music's sound ID
    char unkf28[0xf35 - 0xf28];
    PALETTEENTRY m_palette[0x100];  // 0x0f35; each player's colours are 95 + 40 * player
    char unk1335[0x1338 - 0x1335];
    BOOL m_editColor[2];        // 0x1338 per player: the edited palette was chosen (read
                                //   as a bool)
    char unk1340[0x1343 - 0x1340];
    char m_isCpu[2];            // 0x1343 per player: 1 the CPU plays it. With one human,
                                //   m_isCpu[0] is the human's side
    char unk1345[0x134c - 0x1345];
    char m_winner;              // 0x134c the side that won the match
    char m_round;               // 0x134d
    char m_roundsToWin;         // 0x134e
    BYTE m_roundsSetting;       // 0x134f config: rounds to win in VS modes, 1-3
    char unk1350[0x1364 - 0x1350];
    BYTE m_gameMode;            // 0x1364 0 ARCADE, 1 PRACTICE, 3 VS CPU, 4 VS HUMAN,
                                //   5 REPLAY, 6 demo
    BYTE m_cpuLevel;            // 0x1365 config: 1-4
    char m_fullEffects;         // 0x1366 config: 0 simple effects, 1 normal
    char unk1367;
    char m_oddFrame;            // 0x1368 the low byte of a BOOL WinMain toggles every frame
    char unk1369[3];
    char m_drawEveryFrame;      // 0x136c the low byte of the config's int: 0 30FPS, 1 60FPS
    char unk136d[3];
    BYTE m_damageLevel;         // 0x1370 config: 1 50%, 2 100%, 3 200%
    char unk1371[0x137c - 0x1371];
    void *m_background;         // 0x137c the stage's animated background (CAnimBg), if any
    char unk1380[0x14283 - 0x1380];
    char m_replayMode;          // 0x14283 0 none, 1 playing, 2 recording
    CReplayFile m_replay;       // 0x14284
    char unk14294[0x142f0 - 0x14294];
};

// The scenes WinMain runs (src/efz.h CScene): 0 title, 1 character select, 2 versus
// screen, 3 the fight, ...
class CScene {
public:
    virtual void Draw() = 0;
    virtual BYTE Update() = 0;  // the next scene
    virtual void HandleKeys() = 0;

    UINT lastMessage;
    HWND m_hwnd;
    CPlayer *m_player1;         // 0x0c m_players[0] and [1]: the players when the scene
    CPlayer *m_player2;         //   was made
    CPlayer **m_playerRefs[2];  // 0x14 m_player1Ref, m_player2Ref: WinMain's g_player1 and
                                //   g_player2
    CGame *m_game;              // 0x1c
    void *m_graphics;
    CInput *m_input;
    CSound *m_sound;
    char m_enter;               // 0x2c
    char m_leave;               // 0x2d nonzero: the scene is being left. The fight: 1 quit
                                //   (Esc, a replay's end, a key in the demo), 2 the match
                                //   is over
    BYTE unk2e[2];              // 0x2e the start of m_palette
};

// The title screen and its menu (scene 0).
class CScene0 : public CScene {
public:
    char unk30[0x43c - 0x30];
    char m_cursor;              // 0x43c the menu's row: 0 ARCADE, 1 VS CPU, 2 VS HUMAN,
                                //   3 PRACTICE, 4 REPLAY, 5 OPTION, 6 EXIT
};

// Character select (scene 1).
class CScene1 : public CScene {
public:
    char unk30[0x49e - 0x30];
    char m_state[2];            // 0x49e per player: 6 once the choice is final
    char unk4a0[0x53c - 0x4a0];
    char m_charId[2];           // 0x53c
    char m_paletteIndex[2];     // 0x53e
};

// The fight (scene 3, src/efz.h CScene3).
class CScene3 : public CScene {
public:
    char unk30[0x45c - 0x30];
    POINT m_draw;               // 0x45c m_drawX, m_drawY: the stage-to-screen offset with
                                //   the screen shake, what everything is drawn with
    char unk464[0x578 - 0x464];
    char m_speed;               // 0x578 fight ticks per frame: 3 normally, 0 stops it
};

// DDRAW.dll's screen palette: its IDirectDrawPalette (myIDirectDraw.h), with two virtual
// functions of its own after COM's: the destructor, then the colours it holds.
struct ProxyPalette : public IDirectDrawPalette {
    virtual void destructor() = 0;
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
// efz.exe 0x7631f0: CScene3::DrawBordersAndFlip, called by CScene3::Draw after the players
typedef void (__thiscall *DrawFightFn)(CScene3 *fight);
#define EFZ_DRAW_FIGHT ((DrawFightFn)0x7631f0)
// efz.exe 0x767600: CScene3::BoxOnStage: an object's box in the fight's coordinates
// efz.exe 0x7677a0: CScene3::InfoBoxOnStage: the same from a CollisionInfo
// Members that don't use their scene: called without one, with the RECT they return
// by value given as the first argument (and returned).
typedef RECT *(__stdcall *ObjectBoxFn)(RECT *result, PlayerObject *object, RECT *box);
typedef RECT *(__stdcall *InfoBoxFn)(RECT *result, CollisionInfo *info, RECT *box);
#define EFZ_OBJECT_BOX ((ObjectBoxFn)0x767600)
#define EFZ_INFO_BOX ((InfoBoxFn)0x7677a0)
