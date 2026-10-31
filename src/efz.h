// Shared declarations recovered from efz.exe 4.02.
//
// Annotations give the original address of each definition:
//   // FUNCTION: 0x401000      a function or method
//   // GLOBAL: 0x790150        a global variable
//   // SIZE: 0x142f0           sizeof a class, from the original `new` call
// Names starting with Unk are placeholders until the function is understood, and
// members named unk<offset> until the field is: their type is the one the code reads.
// Classes are padded to their original size with byte arrays named unk<offset>; an unk
// byte array with a comment is a real array of unknown purpose. A `// +0x..` comment
// gives a member's offset. tools/members.py layout checks offsets and sizes, and
// docs/readability.md says which source changes keep the compiled code.
#ifndef EFZ_H
#define EFZ_H

#ifdef EFZ_NATIVE
// The native build (port/, CMakeLists.txt): SDL3 in place of Win32 and DirectX.
#include "efz_native.h"
#else
#include <windows.h>
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>
#include <math.h>

// The game's structures hold pointers in 32 bits, and its code keeps pointers in ints
// too. These macros mark the pointer members and each cast between a pointer and an
// integer, so that the native build, whose pointers are 64 bits wide, can keep them as
// 32-bit handles (port/guest.h). Here they are what the original was compiled from.
//   PTR32(T)        a pointer member of type T*
//   PTRAT(addr)     the pointer stored at addr, as a char*
//   PTRSET(addr, p) stores the pointer p at addr
//   TOPTR(T*, v)    the 32-bit value v as a pointer
//   TOINT(T, p)     the pointer p as the 32-bit integer type T
// And for floating point, which the original computed on the x87 at double precision:
//   F32             a float in the game's structures; arithmetic on one is in double
//                   precision, rounded to float only when it is stored
//   F32CAST(x)      a cast to float inside an expression, which this compiler drops:
//                   the value goes on unrounded (the native build makes it a double)
//   FABSF(x)        fabs of a float expression: <math.h>'s float overload, which gets
//                   its argument as a float, rounded (the native build rounds it)
#define PTR32(T) T*
#define PTRAT(addr) (*(char**)(addr))
#define PTRSET(addr, p) (*(char**)(addr) = (p))
#define TOPTR(T, v) ((T)(v))
#define TOINT(T, p) ((T)(p))
#define F32 float
#define F32CAST(x) ((float)(x))
#define FABSF(x) fabs(x)
#endif

struct EffectDesc;
class CAnimBg;
class CGame;

// A frame of an effect animation, read from system\effect\effect.pat.
struct EffectFrame {
    WORD duration; // in game frames
    WORD surface;  // index into CGame::m_surfaces
    short x;       // hotspot within the frame
    short y;
    short width;
    short height;
};

// Animation of one effect type: CGame::m_effectAnims is indexed by Effect::type.
struct EffectAnim {
    // Inline methods are emitted in the order they are defined, which puts Alloc before
    // the constructor after the CGame object, and both before CFile's.
    // FUNCTION: 0x4082d0
    void Alloc(int count)
    {
        frameCount = count;
        if (count > 0)
            frames = new EffectFrame[count];
    }
    // FUNCTION: 0x408310
    EffectAnim() { frames = NULL; }
    // FUNCTION: 0x408270
    ~EffectAnim()
    {
        if (frames)
            delete frames;
    }

    BYTE frameCount;
    BYTE unk1;
    WORD unk2;
    PTR32(EffectFrame) frames;
};

// Win32 file wrapper used by the loaders.
class CFile {
public:
    // FUNCTION: 0x408330
    // Defined inline; the copy is placed after the CGame object, which uses it first.
    CFile(const char* name, DWORD mode)
    {
        Reset();
        Open(name, mode);
    }
    // FUNCTION: 0x408360
    ~CFile() { Close(); }

    // FUNCTION: 0x4054b0
    // mode: 1 read, 2 write; 0x10 truncate, 0x20 open always, both: create always.
    BOOL Open(const char* name, DWORD mode);
    // FUNCTION: 0x4055a0
    BOOL Close();
    // FUNCTION: 0x405600
    DWORD Read(void* buffer, DWORD size);
    // FUNCTION: 0x405640
    // Reads up to a newline; returns the line length minus one.
    int ReadLine(char* line, int size);
    // FUNCTION: 0x405700
    int ReadInt();
    // FUNCTION: 0x405720
    short ReadShort();
    // FUNCTION: 0x405740
    float ReadFloat();
    // FUNCTION: 0x405760
    DWORD Write(const void* buffer, DWORD size);
    // FUNCTION: 0x4057a0
    void WriteInt(int value);
    // FUNCTION: 0x4057c0
    void WriteFloat(float value);
    // FUNCTION: 0x4057e0
    BOOL Printf(const char* format, ...);
    // FUNCTION: 0x405850
    DWORD Seek(LONG offset, int origin);
    // FUNCTION: 0x4058c0
    DWORD SeekToStart();
    // FUNCTION: 0x4058f0
    DWORD SeekToEnd();
    // FUNCTION: 0x405920
    DWORD GetSize();
    // FUNCTION: 0x405950
    BOOL IsOpen();
    // FUNCTION: 0x405970
    BOOL Reset();
    // FUNCTION: 0x4059a0
    // Reads the whole file into a NUL-terminated buffer the CFile owns.
    char* Load(const char* name);

    HANDLE m_handle;
    char* m_data;
    int unk8; // never used; the class is 12 bytes on the stack
};

// FUNCTION: 0x405a20
// Returns the byte at `offset` in key.ini, or 0 if the file is missing or short.
// The file is reread on every call.
BYTE ReadConfigByte(BYTE offset);
// FUNCTION: 0x405ae0
// Rewrites key.ini with the byte at `offset` replaced.
BYTE WriteConfigByte(BYTE offset, BYTE newValue);

// Eight per-character counters, kept at CPlayer+0x3118 and saved as
// system\<name>\<name>.rec (36 bytes: the counters and a zero word). Callers increment
// one before saving.
struct CharRecord {
    // FUNCTION: 0x405be0
    void Save(const char* name);
    // FUNCTION: 0x405cf0
    void Load(const char* name);

    DWORD uses; // times a human picked the character (arcade's first match, practice, VS)
    DWORD vsWins; // VS HUMAN matches won
    DWORD vsLosses; // VS HUMAN matches lost
    DWORD bestScore; // best arcade score, low part (score = bestScoreHigh * 10^8 +
                     // bestScore); saved only in mode 2, so never in practice
    DWORD bestScoreHigh; // best arcade score, high part
    DWORD unk14;
    DWORD maxCombo; // most hits in a combo (at damage 100%)
    DWORD maxDamage; // most damage in a combo (at damage 100%)
};

// A replay file: a stream of 16-bit input words.
class CReplayFile {
public:
    // FUNCTION: 0x405e60
    CReplayFile();
    // FUNCTION: 0x405f80
    ~CReplayFile();
    // FUNCTION: 0x405e90
    // Returns the file size, or 0 if it cannot be opened.
    DWORD OpenRead(const char* name);
    // FUNCTION: 0x405f00
    void OpenWrite(const char* name);
    // FUNCTION: 0x405f50
    void Close();
    // FUNCTION: 0x405fb0
    // Returns the next word, or 0 and sets m_eof at the end of the file.
    short Read();
    // FUNCTION: 0x406020
    void Write(short value);

    BOOL m_eof;
    HANDLE m_handle;
    DWORD m_remaining; // bytes left to read
    DWORD m_read;
};

// DirectDraw wrapper: a 320x240 or 640x480 8-bit palettised screen with one back buffer.
// Sprites are system-memory surfaces that the Blit functions copy to the back buffer in
// software, through inline assembly loops.
class CGraphics {
public:
    // FUNCTION: 0x401950
    // Defined inline, so the copy main.obj uses is placed right after main.obj's code.
    CGraphics()
    {
        m_mode = 0;
        for (int i = 0; i < 0x200; i++)
            m_quarterSquares[i] = (i - 0x100) * (i - 0x100) / 4;
    }
    // FUNCTION: 0x408b50
    ~CGraphics();
    // FUNCTION: 0x4083b0
    // mode 0: 320x240, 1: 640x480. Shows a message and closes the window on failure.
    BOOL Init(HWND hWnd, BYTE mode);
    // FUNCTION: 0x408640
    // Recreates the screen surfaces in 8-bit colour.
    BOOL SetMode8();
    // FUNCTION: 0x408850
    // Recreates the screen surfaces in 16-bit colour.
    BOOL SetMode16();
    // FUNCTION: 0x408a60
    // Restores the display mode and releases the DirectDraw objects.
    void Shutdown();
    // FUNCTION: 0x408c40
    void ReleaseSurface(PTR32(IDirectDrawSurface)* surface);
    // FUNCTION: 0x408c70
    // Posts WM_CLOSE to the game window.
    BOOL Close();
    // FUNCTION: 0x408ca0
    BOOL RestorePrimary();
    // FUNCTION: 0x408cd0
    BOOL RestoreSurface(PTR32(IDirectDrawSurface)* surface);
    // FUNCTION: 0x408d00
    // Loads an 8-bit .bmp into a new surface, adding `base` to every pixel; returns
    // the image's rectangle.
    RECT LoadBmp(PTR32(IDirectDrawSurface)* surface, const char* name, BYTE base);
    // FUNCTION: 0x409090
    // The same, but pixels 40 and above map to 175 and up instead of having base added.
    RECT LoadBmpHigh(PTR32(IDirectDrawSurface)* surface, const char* name, BYTE base);
    // FUNCTION: 0x409470
    // Creates a surface from an image inside a .dat file; returns the bytes consumed,
    // or 0 on failure. With rle nonzero, a byte above rle repeats the previous colour
    // (byte - rle) more times.
    int LoadSurface(PTR32(IDirectDrawSurface)* surface, BYTE* data, BYTE rle, BYTE base);
    // FUNCTION: 0x409740
    // LoadSurface with LoadBmpHigh's mapping.
    int LoadSurfaceHigh(PTR32(IDirectDrawSurface)* surface, BYTE* data, BYTE rle,
                        BYTE base);
    // FUNCTION: 0x409a90
    // Copies `src` of `surface` to `dst` on the back buffer, clipped to 320x240, skipping
    // pixels equal to `key` (if nonzero), mirrored if `flip`. Returns FALSE if a surface
    // was lost.
    BOOL Blit(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip);
    // FUNCTION: 0x409db0
    // Blit onto any surface, clipped to 640x480. Unused.
    BOOL BlitTo(IDirectDrawSurface* target, RECT dst, IDirectDrawSurface* surface, RECT src,
                BYTE key, BOOL flip);
    // FUNCTION: 0x40a0b0
    // Blit through blend table `mode` (0 or 1): each pixel becomes
    // m_blend[mode][source][destination].
    BOOL BlitEx(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                char mode);
    // FUNCTION: 0x40a440
    // Paints the sprite's shape: each pixel becomes m_blend[1][source][color].
    BOOL BlitTint(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                  BYTE color);
    // FUNCTION: 0x40a7b0
    // Draws the sprite's shadow: squashed to a third of its height and upside down,
    // darkening the back buffer through m_blend[0][destination][shade].
    BOOL BlitShadow(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                    BYTE shade);
    // FUNCTION: 0x40aae0
    // Smears the back buffer under the sprite's shape: each pixel copies the one 3 to
    // its left.
    BOOL BlitSmear(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip);
    // FUNCTION: 0x40ae10
    // Darkens a line from (x1, y1) to (x2, y2) through m_blend[1][0xe2].
    BOOL DrawLine(int x1, int y1, int x2, int y2);
    // FUNCTION: 0x40b110
    // Outlines `rc` in `color`, clamped to the screen.
    BOOL DrawFrame(RECT rc, BYTE color);
    // FUNCTION: 0x40b300
    BOOL FillRect(RECT rc, BYTE color);
    // FUNCTION: 0x40b440
    // In 640x480 mode, doubles the 320x240 image in the back buffer to fill it.
    BOOL Upscale();
    // FUNCTION: 0x40b5e0
    // Presents the back buffer; returns FALSE if the surface was lost.
    BOOL Flip();
    // FUNCTION: 0x40b640
    // Reads `count` colours of an 8-bit .bmp's palette, from entry `from`, into
    // palette[to]...
    BOOL LoadPaletteBmp(PALETTEENTRY* palette, const char* name, int from, int to, int count);
    // FUNCTION: 0x40b760
    // The same from a .dat file, whose palette is stored as 3-byte entries after the
    // first byte.
    BOOL LoadPaletteDat(PALETTEENTRY* palette, const char* name, int from, int to, int count);
    // FUNCTION: 0x40b8a0
    // Fills m_blend from `palette`: [0][a][b] is the colour nearest to the average of a
    // and b, [1][a][b] the colour nearest to their sum.
    void BuildBlendTables(PALETTEENTRY* palette);
    // FUNCTION: 0x40bcc0
    // Returns the surface's top-left pixel, which the game uses as its transparent colour.
    BYTE GetColorKey(IDirectDrawSurface* surface);
    // FUNCTION: 0x40bd30
    // Sets the screen palette; entry 255 is left out.
    BOOL SetPalette(PALETTEENTRY* palette);
    // FUNCTION: 0x40bd70
    BOOL SetPaletteRange(PALETTEENTRY* palette, BYTE start, BYTE count);
    // FUNCTION: 0x40bdc0
    BOOL ClearPalette(PALETTEENTRY* palette);
    // FUNCTION: 0x40be20
    // Sets screen palette entries from..to-1 to `percent` of `palette`'s brightness.
    void Darken(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent);
    // FUNCTION: 0x40bf20
    // Sets screen palette entries from..to-1 to `palette` blended with white; 100 keeps
    // the colours, 0 is white.
    void Brighten(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent);
    // FUNCTION: 0x40c070
    // Sets screen palette entries from..to-1 to `palette` moved `percent` of the way to
    // its negative.
    void Invert(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent);
    // FUNCTION: 0x40c1c0
    // Saves the 320x240 screen as snap\snNNNN.bmp.
    void Screenshot(int number, PALETTEENTRY* palette);

    HWND m_hwnd;
    BYTE m_mode;
    PALETTEENTRY m_palette[0x100];
    BYTE m_blend[2][0x100][0x100]; // [table][source][destination]
    BYTE unk20405;
    // (i - 256)^2 / 4 for i in 0..511: a quarter-squares table, so that
    // a * b == m_quarterSquares[256 + a + b] - m_quarterSquares[256 + a - b].
    // BuildBlendTables uses it for squared colour distances.
    WORD m_quarterSquares[0x200];
    PTR32(IDirectDraw) m_dd;
    PTR32(IDirectDrawSurface) m_primary;
    PTR32(IDirectDrawSurface) m_back;
    PTR32(IDirectDrawPalette) m_ddpal;
};

// FUNCTION: 0x40c590
RECT MakeRect(int x, int y, int width, int height);

// DirectInput wrapper: the keyboard and up to two joysticks, read as 8 bindings per
// player.
class CInput {
public:
    // FUNCTION: 0x40c5e0
    // Default bindings: player 1 J G N Y and Q W E D, player 2 the arrows and P @ [ ].
    CInput();
    // FUNCTION: 0x40c990
    ~CInput();
    // FUNCTION: 0x40c6f0
    BOOL Init(HWND hWnd);
    // FUNCTION: 0x40c880
    // Unacquires and releases the DirectInput devices.
    void Shutdown();
    // FUNCTION: 0x40caa0
    // Shows a message and closes the window.
    void Fail();
    // FUNCTION: 0x40cd00
    // Returns a player's controls: bits 0-3 right, left, down, up; bits 4-7 the buttons.
    BYTE GetInput(BYTE player);
    // FUNCTION: 0x40d140
    // Loads the bindings from key.ini.
    void LoadBindings();
    // FUNCTION: 0x40d460
    // Loads the bindings from preset `set` of key.ini (39 bytes each).
    void LoadPreset(int set);

    char m_keyState[0x100];       // from the keyboard's GetDeviceState
    char unk100[0x20];
    DIJOYSTATE m_joyState[2];
    // Per player: right, left, down, up, then the four buttons. The low byte is a key
    // (DIK_*) or joystick code; the high byte is the device: 0 keyboard, 1 or 2 a
    // joystick, whose codes 0x10-0x13 are up, down, left and right on the stick and
    // lower codes its buttons.
    short m_bindings[2][8];
    HWND m_hwnd;
    PTR32(IDirectInput7) m_di;
    PTR32(IDirectInputDevice7) m_keyboard;
    PTR32(IDirectInputDevice7) m_joysticks[2];
    int unk1f4;
};

// DirectSound wrapper: up to 150 sounds, each a .wav file kept in memory and copied to its
// own static buffer. IDs index the arrays; 0x96 (150) means none.
class CSound {
public:
    // FUNCTION: 0x40d810
    CSound();
    // FUNCTION: 0x40d870
    ~CSound();
    // FUNCTION: 0x40d930
    // Releases all 150 sound buffers and the DirectSound object.
    void Shutdown();
    // FUNCTION: 0x40d9f0
    void Init(HWND hWnd);
    // FUNCTION: 0x40dab0
    // Copies a sound's data into its buffer, restoring the buffer if it was lost.
    void Fill(WORD id);
    // FUNCTION: 0x40dc50
    void ReleaseBuffer(WORD id);
    // FUNCTION: 0x40dcd0
    void CreateBuffer(WORD id, WAVEFORMATEX* format);
    // FUNCTION: 0x40ddd0
    // Returns the first ID without a buffer, or 0x96 after a message if none is free.
    WORD FindFreeSlot();
    // FUNCTION: 0x40de40
    void Stop(WORD id);
    // FUNCTION: 0x40de80
    // Plays a sound from the start; loop == 1 repeats it.
    void Play(WORD id, BOOL loop);
    // FUNCTION: 0x40df50
    void Release(WORD id);
    // FUNCTION: 0x40dfb0
    // Loads a PCM .wav file; returns its sound ID, or 0x96 on failure.
    WORD Load(const char* name);
    // FUNCTION: 0x40e2b0
    // Sets the music loop from the 'cue ' and 'adtl' chunks in the last 320 bytes of a
    // .wav file; without both, the music does not loop back.
    void LoadLoop(const char* name);
    // FUNCTION: 0x40e4d0
    // Called every frame for the music: once its play cursor passes m_loopEnd, moves it
    // back by m_loopLength.
    void UpdateLoop(WORD id);
    // FUNCTION: 0x40e5d0
    void SetVolume(WORD id, int volume);

    DWORD m_loopLength;  // bytes
    DWORD m_loopEnd;
    HWND m_hwnd;
    PTR32(IDirectSound) m_ds;
    PTR32(BYTE) m_data[0x96];
    DWORD m_size[0x96];
    PTR32(IDirectSoundBuffer) m_buffers[0x96];
};

// One frame of a pattern's data (boxes, physics values), copied whole by some scenes.
// No byte arrays in here: /GS would then protect every function with one as a local.
// BEGIN constants (tools/constants.py declare): bits of PatternFrame::flagsAA
enum {
    kAttackGuardStand = 0x1,      // may be guarded standing
    kAttackGuardCrouch = 0x2,     // may be guarded crouching
    kAttackGuardAir = 0x4,        // may be guarded in the air
    kAttackBodyHit = 0x8,         // a standing defender takes 0x35-0x37 (doubled over)
                                  // instead of 0x32-0x34 (head snapped back)
    kAttackMedium = 0x10,         // strength: +1 to the hit reaction (0x33) and the guard
                                  // reaction (0x97)
    kAttackHeavy = 0x20,          // strength: +2 (0x34, 0x98)
    kAttackThrow = 0x40,          // tests the defender's push box (box90) instead of its
                                  // hurtboxes
    kAttackUnblockable = 0x80,    // CanGuard fails and recoil guard too
    kAttackIgnoresArmor = 0x100,  // beats armor (flagsB0 4 / m_armorTime, scene3.cpp), the
                                  // parry frames (flagsB0 0x800/0x1000,) and an object
                                  // reflect (flagsB0 0x400,)
    kAttackUnused200 = 0x200,     // set on 1237 frames, never tested by the code
    kAttackNoAirRecovery = 0x400, // sets the defender's m_noAirRecovery
    kAttackLandHittable = 0x800,  // sets m_landHittable: the defender lands in 0x61, which
                                  // can still be hit, instead of 0x62
    kAttackUnused1000 = 0x1000,   // set on 142 frames (Ayu 0x13b-0x13d, Mio 0x1a2 ...),
                                  // never tested
    kAttackCounterHit = 0x2000,   // with flagsB0 0x2000 on the defender's frame: a counter
                                  // hit
};
// END constants

// BEGIN constants (tools/constants.py declare): bits of PatternFrame::flagsB0
enum {
    kStateStanding = 0x1,           // posture: hit as standing (0x32-0x37, scene3.cpp)
    kStateCrouching = 0x2,          // posture: hit as crouching (0x38-0x3a, scene3.cpp)
    kStateArmor = 0x4,              // hits do damage but cause no reaction (tint 0xdf,
                                    // m_attackResult 7) unless flagsAA 0x100 or 0x40
    kStateCancellable = 0x8,        // a move may start on this frame: tested by every
                                    // StartCommand before each move (1002 sites, akane.cpp)
    kStateCanGuard = 0x10,          // the player may guard here
    kStateInvulnerable = 0x20,      // not hit at all: knockdown landing 0x62, lying 0x63,
                                    // wake-up 0x60, supers' startup
    kStateThrowProtect = 0x40,      // keeps m_throwProtect at 27: jump start (4-6), guard
                                    // (0x96-0x9c), knockdowns, wake-up
    kStateUnused80 = 0x80,          // one frame (Mai 0xcf), never tested
    kStateGuardPoint = 0x200,       // with the frame's own flagsAA 1/2/4: guards attacks of
                                    // those heights without leaving the move (chip damage,
                                    // hitstop, guard gauge, m_attackResult 2
    kStateReflect = 0x400,          // an object's attack on this frame is cancelled (both
                                    // players' m_attackResult = 6) unless flagsAA 0x100
    kStateParryLow = 0x800,         // parries attacks that can be guarded crouching
                                    // (flagsAA 2) without 0x100: both m_attackResult = 6,
                                    // the attacker loses the hit
    kStateParryHigh = 0x1000,       // the same for attacks that can be guarded standing
                                    // (flagsAA 1)
    kStateCounterHittable = 0x2000, // the startup and active frames of attacks: a hit with
                                    // flagsAA 0x2000 is a counter hit. On an object's
                                    // frame: a hit on the object hits its owner
};
// END constants

struct PatternFrame {
    RECT boxes[5];      // probably hurtboxes
    RECT attackBoxes[4];
    RECT pushBox; // the push box: keeps the players apart, the target of throws, and
                  // where objects clash
    short damage; // base damage of a hit; also guard gauge (damage/30) and score
    short unka2;
    F32 proration; // the combo's damage scaling after this hit, per mille
    short chipDamage; // HP a guarded hit takes (never below 1)
    WORD flagsAA;
    short airHitPattern; // the reaction of a defender hit in the air, 0 = 0x3b; also the
                         // KO reaction
    short groundHitPattern; // the reaction of a defender hit on the ground, 0 = by
                            // posture and strength
    WORD flagsB0;
    short untechTime; // base of the defender's m_untechTime
    short gaugeOnHit; // power gauge the attacker gains on a hit
    short gaugeOnGuard; // power gauge the attacker gains when guarded
    F32 hitVx; // the defender's launch speed x, .pat value / -100
    F32 hitVy; // the defender's launch speed y, .pat value / 100
    char hitEffect; // the effect type created at the hit
    char hitSound; // its sound (CGame::m_sounds index)
    short attackerHitstop; // ticks of hitstop for the attacker (or the attacking object)
    short defenderHitstop; // ticks of hitstop for the defender
    short unkc6;
};

// A player's frame, position and facing, gathered for CScene3's collision checks.
struct CollisionInfo {
    PatternFrame frame;
    EffectFrame anim;
    double x;
    double y;
    char facing;        // CPlayer+0x50
    char attackResult;         // CPlayer+0x168
    short hitsLeft;        // CPlayer+0x16c
};

// Per-pattern data read from <name>.pat beside the sprite frames, one per pattern
// (CPlayer+0x164 holds 505 of them): 0xc8-byte frames with boxes and physics values.
struct PatternData {
    // Inline methods are emitted after the CPlayer object in order of first use.
    // FUNCTION: 0x412820
    PatternData()
    {
        frames = (PatternFrame*)0;
    }
    // FUNCTION: 0x4128e0
    ~PatternData()
    {
        int v4;

        if ((int)frames != 0) {
            v4 = (int)frames;
            operator delete(TOPTR(void*, v4));
        }
    }
    // FUNCTION: 0x412ad0
    void Alloc(int p1)
    {
        int v4;

        if (p1 > 0) {
            v4 = TOINT(int, operator new(p1 * 0xc8));
            frames = TOPTR(PatternFrame*, v4);
        }
    }

    short level; // a move may start only if its level is at least the current pattern's
                 // cancelLevel; objects of a higher level win a clash
    short cancelLevel; // the level a move needs to cancel this pattern (0 for idle
                       // states)
    PTR32(PatternFrame) frames;
};

// What a player and each of the objects it spawns have in common: pattern and frame,
// the sprite animations, position and facing. CPlayer derives from it (at offset 8,
// after the vtable pointer), and so do the 0x98-byte entries of its object table.
struct ObjBase {
    // Inline: each copy sits after the first object that uses it.
    // FUNCTION: 0x434010
    // Sets the velocity from a direction in degrees and a speed.
    void SetVelocity(double angle, double speed)
    {
        vx = cos(angle / 57.29579143313326) * speed;
        vy = sin(angle / 57.29579143313326) * speed;
    }
    // FUNCTION: 0x4c0480
    // The direction of (dx, dy) in degrees.
    double AngleTo(double dx, double dy)
    {
        return atan2(dy, dx) * 57.29579143313326;
    }

    WORD pattern;     // +0
    WORD frame;       // +2: the frame of the pattern's animation
    WORD timer;       // +4: game frames spent on the current frame
    BYTE unk6[2];
    PTR32(EffectAnim) anims;                   // +8: the character's sprite animations, one
                                               // per pattern
    PTR32(PTR32(IDirectDrawSurface)) surfaces; // +0xc: the character's sprites
    WORD lastSurface; // +0x10: sprites 0 to lastSurface are loaded
    char colorKey;    // +0x12: the sprites' transparent colour
    BYTE unk13[5];
    double x;         // +0x18
    double y;         // +0x20: 0 on the ground, negative in the air
    double vx;        // +0x28
    double vy;        // +0x30
    double ax;        // +0x38: most states add or subtract it from vx every frame
    double ay;        // +0x40: gravity, added to vy every frame
    char facing;      // +0x48: 1 or -1
    BYTE unk49[3];
    int side;         // +0x4c: objects' only, from their descriptor's
};

// One of the 64 objects a player spawns (projectiles, its parts of supers...): the
// 0x98-byte entries of CPlayer's object table.
struct PlayerObject : ObjBase {
    char scale;       // +0x50: as Effect's
    char layer;       // +0x51
    BYTE unk52[2];
    int screen;       // +0x54
    int shadow; // CScene3 draws its shadow
    RECT clip;        // +0x5c: drawn clipped to it unless top == bottom
    char sound; // copied from EffectDesc::sound; never played for an object
    BYTE unk6d[3];
    double unk70;
    double unk78;
    int attackResult; // as m_attackResult: 0 none, 2 guarded or reflected, 3 hit, 4 lost
                      // a clash, 5 hit or hit by an object, 7 absorbed by armor
    short hitsLeft; // hits it can still land
    short hitstop; // ticks it is stopped after a hit or guard
    int movesInFreeze; // keeps moving during its owner's m_freezeTime
    int drawnWhileHidden; // drawn while CGame::m_hideObjectsTime hides the objects (a darkened
                          // screen)
    BYTE unk90[8];
};

// The last 60 positions of a player, for drawing afterimages: x and y, facing, pattern
// and frame. Kept at CPlayer+0x2bc0.
struct Afterimages {
    // FUNCTION: 0x412840
    Afterimages()
    {
        pos = 0;
        spacing = 0;
        fadeLength = 0;
    }
    // FUNCTION: 0x412910
    void Stop()
    {
        fadeLength = spacing * 3;
        spacing = 0;
    }
    // FUNCTION: 0x412930
    void Record(ObjBase* p1)
    {
        step = spacing; // recorded positions between the three afterimages while on; 0
                        // off
        fadeLength = 0;
        x[pos] = p1->x;
        y[pos] = p1->y;
        facing[pos] = p1->facing;
        pattern[pos] = p1->pattern;
        frame[pos] = p1->frame;
        pos++;
        if (pos >= 0x3c) {
            pos = 0;
        }
    }
    // FUNCTION: 0x412a10
    void Start(ObjBase* p1, char p2)
    {
        int v4;

        if (spacing == 0 && fadeLength == 0) {
            v4 = 0;
            for (; v4 < 0x3c; v4++) {
                x[v4] = p1->x;
                y[v4] = p1->y;
                facing[v4] = p1->facing;
                pattern[v4] = p1->pattern;
                frame[v4] = p1->frame;
            }
        }
        spacing = p2;
        step = p2;
    }

    BYTE spacing;
    BYTE step; // the spacing the trail is drawn with, kept while it fades
    BYTE fadeLength; // positions left in the trail after Stop, one fewer each drawn frame
    BYTE unk3[0x8 - 0x3];
    double x[0x3c];         // +8
    double y[0x3c];         // +0x1e8
    char facing[0x3c];      // +0x3c8
    WORD pattern[0x3c];     // +0x404
    WORD frame[0x3c];       // +0x47c
    short pos;              // +0x4f4: the slot the next position goes in
    BYTE unk4f6[0x4f8 - 0x4f6];
};

// Base of the character classes, one per side. Characters override the pure virtual
// slots; the vtable at 0x787bcc implements slots 0 and 9-12. The destructor is not
// virtual: g_player1 and g_player2 are deleted as CPlayer.
// BEGIN constants (tools/constants.py declare): the actions every character shares (ObjBase::pattern)
enum {
    kStand = 0x0,                      // player.cpp MoveOnGround with no input
    kWalkForward = 0x1,                // player.cpp left/right toward facing
    kWalkBack = 0x2,                   // player.cpp
    kCrouch = 0x3,                     // player.cpp down held, after 0x8
    kJump = 0x4,                       // player.cpp up, no direction
    kJumpForward = 0x5,                // player.cpp
    kJumpBack = 0x6,                   // player.cpp
    kStandUp = 0x7,                    // player.cpp down released while crouching
    kCrouchDown = 0x8,                 // player.cpp down pressed while standing
    kFall = 0x9,                       // akane_vf6.cpp falling after a jump's animation, an
                                       // air dash, air 22C, recoil guard in the air
    kSuperJump = 0xa,                  // player.cpp up with m_command 3, which no
                                       // ReadCommand produces: unreachable
    kSuperJumpForward = 0xb,           // player.cpp m_command 4, unreachable
    kSuperJumpBack = 0xc,              // player.cpp m_command 5, unreachable
    kLand = 0xd,                       // akane_vf6.cpp landing from any jump or fall (sound
                                       // 9) -> 0x7, or 0x3 holding down
    kAirJump = 0xe,                    // akane.cpp command 6 in the air with m_airActions
                                       // left
    kAirJumpForward = 0xf,             // akane.cpp the same holding forward
    kAirJumpBack = 0x10,               // akane.cpp holding back
    kHudName = 0x2d,                   // scene3_draw.cpp the name plate under the life bar
                                       // (Akane's reads "AKANE SATOMURA")
    kResultLoserFall = 0x2f,           // scene5.cpp the loser drops in from (480, -240) on
                                       // the result screen
    kHudPortrait = 0x30,               // scene3_draw.cpp the face beside the life bar
    kOffscreenMarker = 0x31,           // player.cpp a speech-bubble face drawn at the
                                       // screen's bottom edge when the player is below the
                                       // screen (unless m_hideOffscreenMarker)
    kHitStandHighLight = 0x32,         // scene3.cpp a standing defender, light attack
    kHitStandHighMedium = 0x33,        // flagsAA 0x10
    kHitStandHighHeavy = 0x34,         // flagsAA 0x20
    kHitStandLowLight = 0x35,          // flagsAA 8 (2A, 2B...): sprite doubled over
    kHitStandLowMedium = 0x36,
    kHitStandLowHeavy = 0x37,
    kHitCrouchLight = 0x38,            // scene3.cpp a crouching defender (flagsB0 2)
    kHitCrouchMedium = 0x39,
    kHitCrouchHeavy = 0x3a,
    kHitAir = 0x3b,                    // scene3.cpp the default air reaction (also both
                                       // players on a double KO,)
    kHitAirHigh = 0x3c,                // akane_vf6.cpp as 0x3b, rising speed capped at 4
    kHitAirHigher = 0x3d,              // akane_vf6.cpp capped at 6
    kHitAirCarry = 0x3e,               // akane_vf6.cpp vy*0.75 + m_hitVy, no cap
    kHitAirLaunch = 0x3f,              // akane_vf6.cpp vy = m_hitVy outright (the usual
                                       // launcher/sweep reaction, 440 attack frames)
    kHitAirWallBounce = 0x40,          // akane_vf6.cpp 0x3b that turns into 0x46 at a
                                       // screen edge
    kHitAirHighWallBounce = 0x41,      // akane_vf6.cpp 0x3c with the wall bounce
    kHitAirCarryWallBounce = 0x42,     // akane_vf6.cpp 0x3e with the wall bounce
    kHitAirLaunchWallBounce = 0x43,    // akane_vf6.cpp 0x3f with the wall bounce
    kHitBlownAwayWallBounce = 0x44,    // akane_vf6.cpp flies in a straight line at
                                       // (m_hitVx, m_hitVy) every tick, no gravity, -> 0x46
                                       // at an edge
    kHitBlownAway = 0x45,              // akane_vf6.cpp the same without the bounce (supers'
                                       // finishers, 35 attackers)
    kHitWallBounce = 0x46,             // akane_vf6.cpp bounces off the wall (vx 0.5, vy
                                       // -2.5, sound 0x1f, effect 0), +120 untech time once
    kHitAirHeavy = 0x47,               // akane_vf6.cpp vy = m_hitVy with gravity 0.072
                                       // instead of 0.032: slammed down
    kHitStandHighHold = 0x48,          // akane_vf6.cpp no movement, 72 ticks, -> 0x7
    kHitStandLowHold = 0x49,           // akane_vf6.cpp the same, doubled-over pose
    kHitCrouchHold = 0x4a,             // akane_vf6.cpp the same crouching, -> 0x3
    kHitStandHighPull = 0x4b,          // akane_vf6.cpp slides toward the attacker (vx +2.2
                                       // slowing by 0.06), head-hit pose
    kHitStandLowPull = 0x4c,           // akane_vf6.cpp doubled-over pose
    kHitCrouchPull = 0x4d,             // akane_vf6.cpp crouching, -> 0x3
    kHitBurn = 0x51,                   // akane_vf6.cpp spawns 0x1f3 (blue flames over the
                                       // player), drifts down and lands in a knockdown
    kHitShock = 0x52,                  // akane_vf6.cpp frames 0-3 alternate the sprite with
                                       // a black silhouette in a lightning outline (8
                                       // loops, sound 0x1e), then launched by
                                       // m_hitVx/m_hitVy
    kEncased = 0x53,                   // akane_vf6.cpp the sprite becomes a jagged cream-
                                       // coloured block (shared palette, sprite 422)
    kEncased2 = 0x54,                  // akane_vf6.cpp identical code and data to 0x53
    kEncasedAir = 0x55,                // akane_vf6.cpp the block lying (sprite 423)
                                       // launched by m_hitVx/m_hitVy, gravity 0.04,
                                       // knockdown on landing
    kEncasedSpin = 0x56,               // akane_vf6.cpp the block tumbling (sprites
                                       // 423-429), gravity 0.06, knockdown on landing
    kFallInDarkness = 0x57,            // akane_vf6.cpp the player's sprite is blank and its
                                       // screen-space object 0x1ef shows it falling
    kWakeUp = 0x60,                    // akane_vf6.cpp getting up after 0x63 (invulnerable,
                                       // throw-protected), -> 0x0/0x3
    kKnockdownHittable = 0x61,         // akane_vf6.cpp hitting the ground (shake, effect 3,
                                       // sound 7) after an attack with flagsAA 0x800
                                       // (m_landHittable): its frames have no flagsB0 0x20,
                                       // so it can be hit
    kKnockdown = 0x62,                 // akane_vf6.cpp the usual ground hit after an air
                                       // reaction, invulnerable (flagsB0 0x63)
    kLyingDown = 0x63,                 // akane_vf6.cpp lies 100 ticks then 0x60, or for
                                       // good when KO'd
    kThrownStandHigh = 0x64,           // throw pose set on the opponent and moved around by
                                       // throws (akane_vf6.cpp etc.)
    kThrownStandLow = 0x65,            // throw pose: 0x35's first frame
    kThrownCrouch = 0x66,              // throw pose: 0x38's first frame
    kThrownDoubledOver = 0x67,         // throw pose: 0x35's deepest frame
    kThrownAirborne = 0x68,            // throw pose: an air-hit frame (0x3b frame 3)
    kThrownUpsideDown = 0x69,          // throw pose: 0x3b's last frame, head down
    kThrownLying = 0x6a,               // throw pose: lying (0x63's sprite)
    kThrownStandHigh2 = 0x6b,          // second set of the same seven poses (0x6b-0x71, all
                                       // hittable)
    kThrownStandLow2 = 0x6c,           // as 0x65
    kThrownCrouch2 = 0x6d,             // as 0x66
    kThrownAirRising = 0x6e,           // 0x3b frame 1 (rising), hittable
    kThrownAirborne2 = 0x6f,           // as 0x68
    kThrownUpsideDown2 = 0x70,         // as 0x69
    kThrownLying2 = 0x71,              // as 0x6a
    kThrownStandHighInverted = 0x72,   // third set (0x72-0x78): the seven poses' sprites
                                       // flipped upside down, all invulnerable and throw-
                                       // protected (flagsB0 0x60)
    kThrownStandLowInverted = 0x73,
    kThrownCrouchInverted = 0x74,
    kThrownDoubledOverInverted = 0x75,
    kThrownAirborneInverted = 0x76,
    kThrownUpsideDownInverted = 0x77,  // i.e. upright
    kThrownLyingInverted = 0x78,
    kThrownHidden = 0x79,              // a blank sprite: the thrower's own sprite shows
                                       // both (29 sites, e.g. akiko_vf6.cpp)
    kHeadOnly = 0x7a,                  // only the character's head, five expressions
                                       // (frames)
    kEatingJam = 0x7b,                 // eating from Akiko's jar (head and arms with a jar)
    kGuardStandLight = 0x96,           // scene3.cpp a standing guard against a light attack
                                       // (blockstun 30 ticks)
    kGuardStandMedium = 0x97,          // flagsAA 0x10 (45 ticks)
    kGuardStandHeavy = 0x98,           // flagsAA 0x20 (66 ticks)
    kGuardCrouchLight = 0x99,          // + 3 when holding down (or a CPU, by the attack's
                                       // height)
    kGuardCrouchMedium = 0x9a,
    kGuardCrouchHeavy = 0x9b,
    kGuardAir = 0x9c,                  // scene3.cpp any guard in the air
    kAirRecoveryForward = 0x9d,        // player.cpp a button in air hitstun once
                                       // m_untechTime is 0, holding forward
    kAirRecoveryBack = 0x9e,           // player.cpp holding back
    kWakeUpAttack = 0xa2,              // akane_vf6.cpp rises and attacks (effect 9, sound
                                       // 0x3e) for 1000 gauge, invulnerable
    kDashForward = 0xa3,               // akane.cpp double tap toward the opponent on the
                                       // ground
    kDashBack = 0xa4,                  // akane.cpp double tap away
    kAirDashForward = 0xa5,            // akane.cpp in the air above y -30, toward the
                                       // opponent
    kAirDashBack = 0xa6,               // akane.cpp
    kInstantCharge = 0xa7,             // akane.cpp 22C after an attack connected, m_rfGauge
                                       // >= 500 or blue (level 500: cancels anything)
    kRecoilGuardStand = 0xa8,          // scene3.cpp guard within 30 ticks of pressing back
                                       // (m_recoilGuardWindow)
    kRecoilGuardCrouch = 0xa9,         // the same holding down
    kRecoilGuardAir = 0xaa,            // scene3.cpp
    kAirInstantCharge = 0xab,          // akane.cpp 22C in the air
    kDashStop = 0xb2,                  // akane_vf6.cpp the run's skid (vx -0.03 a tick),
                                       // jump-cancellable, -> 0
    kObjFallInDarkness = 0x1ef,        // object every class has: akane.cpp screen-space,
                                       // the player falling upside down, removed when its
                                       // owner leaves 0x57
    kObjEncasedBreak = 0x1f0,          // object every class has: akane.cpp spawned once on
                                       // entering 0x53-0x56 (blank sprite)
    kObjShardSmall = 0x1f1,            // akane.cpp a small cream-coloured shard: rand speed
                                       // (not replayed), gravity 0.05, bounces, lives
                                       // 80-140 ticks
    kObjShardLarge = 0x1f2,            // akane.cpp a larger shard: gravity 0.03, lives
                                       // 120-220 ticks
    kObjBurnFlames = 0x1f3,            // akane.cpp blue flames that follow the player
                                       // through 0x51, removed after their 8 frames
};
// END constants

// BEGIN constants (tools/constants.py declare): bounds of ranges of actions
enum {
    kLastFreeAction = 0x31,       // the last of the actions a player moves freely in
                                  // (standing, walking, jumping...)
    kFirstHitReaction = 0x32,     // the first hit reaction (0x32-0x95)
    kLastHitReaction = 0x95,      // the last hit reaction
    kFirstGuard = 0x96,           // the first guard reaction (0x96-0x9c)
    kLastSharedAction = 0xc7,     // the last action every character shares
    kFirstCharacterAction = 0xc8, // the first of the character's own actions: normals,
                                  // specials, supers, objects
};
// END constants

// BEGIN constants (tools/constants.py declare): the commands every character shares (CPlayer::m_command)
enum {
    kCmdDashLeft = 0x0,  // left twice (on the screen, not by facing), within 45 frames
    kCmdDashRight = 0x1, // right twice (on the screen, not by facing), within 45 frames
    kCmdUp = 0x6,        // up pressed again within 5 frames: the air jump
    kCmd236A = 0xa,      // 236 + A, within 45 frames
    kCmd236B = 0xb,      // 236 + B, within 45 frames
    kCmd236C = 0xc,      // 236 + C, within 45 frames
    kCmd236D = 0xd,      // 236 + D, within 45 frames
    kCmd623A = 0x14,     // 623 + A, within 60 frames
    kCmd623B = 0x15,     // 623 + B, within 60 frames
    kCmd623C = 0x16,     // 623 + C, within 60 frames
    kCmd623D = 0x17,     // 623 + D, within 60 frames
    kCmd214A = 0x1e,     // 214 + A, within 45 frames
    kCmd214B = 0x1f,     // 214 + B, within 45 frames
    kCmd214C = 0x20,     // 214 + C, within 45 frames
    kCmd214D = 0x21,     // 214 + D, within 45 frames
    kCmd22A = 0x32,      // 5 2 5 2 A, within 45 frames
    kCmd22B = 0x33,      // 5 2 5 2 B, within 45 frames
    kCmd22C = 0x34,      // 5 2 5 2 C, within 90 frames
    kCmd22D = 0x35,      // 5 2 5 2 D, within 90 frames
    kCmdNone = 0x63,     // nothing recognised
};
// END constants

class CPlayer : public ObjBase {
public:
    // FUNCTION: 0x40e630
    // Faces the opponent; returns whether the facing changed.
    int FaceOpponent();
    // FUNCTION: 0x40e6c0
    // The same towards x = p1.
    int FaceX(double p1);
    // FUNCTION: 0x40e740
    // walking, crouching and jumping from neutral by the input (each character's Move)
    void MoveOnGround();
    // FUNCTION: 0x40eae0
    CPlayer(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x40ecb0
    ~CPlayer();
    // FUNCTION: 0x40f170
    // Forgets m_bufferedPress and m_dashBufferedPress; called as a move starts.
    void ClearBufferedPress();
    // FUNCTION: 0x40f190
    // Clears m_inputHistory and m_command.
    void ClearInput();
    // FUNCTION: 0x40f1e0
    // Zeroes the velocity and acceleration.
    void StopMoving();
    // FUNCTION: 0x40f230
    // per tick after ReadInput: combo reset, Move in neutral, the F4/F5 refill, air
    // recovery, StartCommand
    void ProcessInput();
    // FUNCTION: 0x40f470
    // counts down m_untechTime; at 0 a button with a direction in the air starts 0x9d/0x9e
    void TryAirRecovery();
    // FUNCTION: 0x40f580
    // moves the player by its velocity within the screen edges, and its objects
    void ApplyVelocity();
    // FUNCTION: 0x40f980
    // per tick: hitstop, guard gauge, throw protection and the other timers, RF gauge,
    // gauge clamps
    void UpdateGaugesAndTimers();
    // FUNCTION: 0x40ff70
    // 1 at the left edge (the wall, or 280 px from the opponent), -1 at the right edge,
    // else 0
    char AtScreenEdge();
    // FUNCTION: 0x410050
    // whether the player guards the attack frame p1 while on frame p2
    int CanGuard(PatternFrame* p1, PatternFrame* p2);
    // FUNCTION: 0x4100f0
    // whether the guard input matches the attack's height (a CPU decides at random by
    // m_cpuSkill)
    int HoldsGuard(PatternFrame* p1);
    // FUNCTION: 0x4102e0
    // in air hitstun with m_untechTime run out: the player may recover and can't be hit
    int CanAirRecover();
    // FUNCTION: 0x410340
    // in a guard (0x96-0x9c) or recoil guard (0xa8-0xaa; the range also takes 0xab)
    int IsGuarding();
    // FUNCTION: 0x4103a0
    // in a hit reaction (0x32-0x95) while the opponent isn't knocked down (0x60-0x63)
    int IsInHitstun();
    // FUNCTION: 0x410420
    // in a dash (0xa3-0xa6)
    int IsDashing();
    // FUNCTION: 0x410480
    // The attacker's damage factor, 1 + m_rfGauge / 10000, scaled by the game settings.
    double AttackFactor();
    // FUNCTION: 0x410530
    // The defender's: from 1 at full HP to 0.5 at none, times m_defense.
    double DefenseFactor();
    // FUNCTION: 0x410560
    // m_proration as a factor, at most 1.
    double ProrationFactor();
    // FUNCTION: 0x4105a0
    // Takes p1 times the three factors off the opponent's HP, multiplies m_proration
    // by p2 / 1000 and counts the hit in the combo and the score.
    void DealDamage(int p1, double p2);
    // FUNCTION: 0x410790
    // DealDamage's bookkeeping (max combo, score) for a hit CScene3 applied itself
    void ScoreHit(PatternFrame* p1);
    // FUNCTION: 0x410840
    void AddScore(int p1);
    // FUNCTION: 0x4108a0
    // A random number from p1 up to p2: rand() while recording a replay, which stores it,
    // or the replay's next word when playing one back (docs/compat.md).
    short Random(short p1, short p2);
    // FUNCTION: 0x410940
    // once a drawn frame: records the position, or shortens the fading trail
    void UpdateAfterimages();
    // FUNCTION: 0x4109d0
    // Starts drawing afterimages (m_afterimages), for p1.
    void StartAfterimages(BYTE p1);
    // FUNCTION: 0x410a10
    // Shakes the screen p1 pixels, holding for p2 frames.
    void ShakeScreen(int p1, int p2);
    // FUNCTION: 0x410a40
    // weights the camera p1 percent toward this player for p2 ticks
    void FocusCameraX(int p1, int p2);
    // FUNCTION: 0x410a80
    // the same vertically
    void FocusCameraY(int p1, int p2);
    // FUNCTION: 0x410ac0
    // Draws the sprite tinted with colour p1 for p2 frames (half as long in one mode).
    void Tint(BYTE p1, int p2);
    // FUNCTION: 0x410b10
    // Fills the stage background with colour p1 for p2 frames, as supers do.
    void FillBackground(BYTE p1, int p2);
    // FUNCTION: 0x411080
    // <name>\<name>.dat: the sprites.
    void LoadSprites();
    // FUNCTION: 0x4116a0
    // <name>\<name>.pat: the animations and the frames' boxes and values.
    void LoadPatterns();
    // FUNCTION: 0x411ae0
    // <name>\wave\NN.wav into m_voices.
    void LoadVoices();
    // FUNCTION: 0x411be0
    void ReadInput();
    // FUNCTION: 0x4121a0
    // draws the afterimages and the sprite at camera offset (p1, p2), or the marker when
    // below the screen
    void DrawSprite(int p1, int p2);
    // FUNCTION: 0x412f10
    void AdvanceObjectHead();
    // FUNCTION: 0x413040
    void ClearObjects();
    // FUNCTION: 0x413090
    void InitEffectDesc(EffectDesc* p1);
    // FUNCTION: 0x413100
    void DrawObjects(int p1, int p2, BYTE p3);

    // FUNCTION: 0x40f110
    virtual void StartPattern();
    virtual void DrawGauge() = 0;
    virtual void ReadCommand() = 0;
    virtual void Move() = 0;
    virtual void StartCommand() = 0;
    virtual void CpuInput() = 0;
    virtual void UpdatePattern() = 0;
    virtual void UpdateObjects() = 0;
    // the character's per-tick bookkeeping, called after ProcessInput and before
    // UpdatePattern; empty in most classes
    virtual void PreUpdate() = 0;
    // FUNCTION: 0x412b10
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x412e60
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x410b70
    virtual void Load();
    // FUNCTION: 0x40edf0
    virtual void Reset();

    char m_drawMode; // how the sprite is drawn: 0 normally, 1-2 through blend table 0/1
                     // (BlitEx), 3 smeared (BlitSmear); as PlayerObject::scale
    BYTE unk59[0x60 - 0x59];
    int m_drawShadow; // nonzero: CScene3 draws the player's shadow (set by Reset)
    BYTE unk64[0x78 - 0x64];
    PTR32(PTR32(CPlayer)) m_opponent; // +0x78: the other player's slot, g_player1 or
                                      // g_player2. Set first: initialized before
                                      // m_afterimages
    PTR32(CGame) m_game;              // +0x7c
    PTR32(CGraphics) m_graphics;      // +0x80
    PTR32(CInput) m_input;            // +0x84
    PTR32(CSound) m_sound;            // +0x88
    char m_side;            // +0x8c: 0 for player 1, 1 for player 2
    char m_charId;          // +0x8d: the character's number on the select screen
    char m_paletteIndex;    // +0x8e: which <name>N.pal (N = index + 1)
    BYTE unk8f[0x94 - 0x8f];
    char m_name[0x10];      // +0x94: the character's folder and file name, "akane"
    int m_cpu;
    F32 m_cpuSkill; // the CPU's level (scene2.cpp: the CPU level setting 1-4, or the
                    // arcade match number / 1.5 in mode 2): the CPU guards when rand <=
                    // m_cpuSkill*10000, and CpuInput scales its random chances by it
    char m_roundsWon; // rounds won in this match; reaching CGame::m_roundsToWin wins it
    BYTE unkad[0xb0 - 0xad];
    double m_pushVx; // speed correction from the push boxes overlapping the opponent's
                     // (CScene3::PushApart), added to vx for this tick
    double m_cornerPushback; // a hit or guard reaction's pushback while at a stage wall;
                             // the attacker moves back by it instead (if m_hitByBody)
    double m_hitVx; // the last hit's launch speed (PatternFrame::hitVx), applied by the
                    // air hit reactions
    double m_hitVy; // the last hit's launch speed (PatternFrame::hitVy)
    int m_hitByBody; // 1 when the last hit or guard came from the opponent himself, 0
                     // from one of his objects: only the former passes m_cornerPushback
                     // to the attacker
    BYTE unkd4[0xdc - 0xd4];
    short unkdc;
    char unkde;
    BYTE unkdf[0xe8 - 0xdf];
    double unke8;
    BYTE unkf0[0xf2 - 0xf0];
    short unkf2;
    short m_shownHits;      // +0xf4: the combo counter on screen
    BYTE unkf6[0xf8 - 0xf6];
    double m_shownProration; // +0xf8: the proration on screen, in percent
    int m_comboDamage;      // +0x100: the current combo's damage so far
    short m_comboTimer;     // +0x104: frames the combo counter stays on screen
    BYTE unk106[0x108 - 0x106];
    int m_hp;               // +0x108: 9999 full
    int m_comboStartHp;     // +0x10c: m_hp when the combo against this player began
    int m_shownHp; // the HP bar's length, following m_hp by 200 per drawn frame
    BYTE unk114[0x118 - 0x114];
    double m_rfGauge; // the RF (Reinforce) gauge under the power gauge, 0-1000. Refills
                      // 0.1 a tick (0.3 below 500, doubled while guarding) out of
                      // hitstun; 500 pays for a C special and 22C (Instant Charge); adds
                      // up to 10% damage (AttackFactor)
    char m_rfBlue; // set when m_rfGauge fills (it turns blue): no refill, drains while
                   // being hit, C specials cost 250, 22C restores m_rfGauge*5 proration;
                   // cleared when it empties
    BYTE unk121[0x124 - 0x121];
    short m_untechTime; // ticks before an air recovery is allowed: the hit's untechTime *
                        // proration * 0.8; counts down only while m_guardGauge is empty;
                        // drawn as a bar under the player
    BYTE unk126[0x128 - 0x126];
    int m_noAirRecovery; // set by a hit with flagsAA 0x400: no air recovery (nor juggle
                         // protection) until the next hit
    int m_landHittable; // set by a hit with flagsAA 0x800: landing goes to 0x61, which
                        // can be hit, instead of the invulnerable 0x62
    char m_throwProtect; // ticks the player can't be thrown: 27 after leaving a frame
                         // with flagsB0 0x40
    BYTE unk131[0x134 - 0x131];
    F32 m_guardGauge; // EFZ's guard gauge, 0-360: + damage/30 per guarded hit, drains
                      // 0.075 a tick (faster in hitstun); air recovery waits until it is
                      // empty; drawn under a guarding player
    short m_armorTime; // while > 0 hits do damage but cause no reaction (as flagsB0 4),
                       // except flagsAA 0x100 and throws
    short m_noGuardTime; // while > 0 the player can't guard or recoil-guard
    short m_invulTime; // while > 0 the player can't be hit
    short m_hideOffscreenMarker; // while > 0 no marker (0x31) is drawn when the player is
                                 // below the screen
    short m_koDelay; // while > 0 a KO doesn't end the round or start the KO reaction
                     // (supers hold it at 30000 until they finish)
    BYTE unk142[0x144 - 0x142];
    int m_counterHit; // the last hit was a counter hit (flagsAA 0x2000 on flagsB0
                      // 0x2000); cleared every tick, never read
    short m_gauge;          // +0x148: the power gauge, a level per 1000, up to 3000
    short m_hitstop; // ticks this player is stopped by hitstop
                     // (PatternFrame::attackerHitstop / defenderHitstop); counts down
                     // unless the opponent's m_freezeTime runs
    short m_freezeTime; // ticks the opponent stays frozen: a super's flash (0x78), 22C
                        // (0x5a), a recoil guard (0x3c), a KO (+0xb4); CScene3::Update
                        // counts it down
    short m_recoilGuardWindow; // 60 when back is pressed from neutral, counting down; a
                               // guard while it is >= 30 is a recoil guard (0xa8-0xaa)
    int m_heldDirection; // whether left or right is held this tick
    int m_guardedObject; // 1 when the last guarded hit came from one of the opponent's
                         // objects, 0 from the opponent; never read
    BYTE m_dashMomentum; // 1 during the run (0xa3) and the move started from it: jumps
                         // get extra speed, normals keep sliding
    BYTE m_airDashes; // air dashes used in this jump (1 allowed, 2 for some characters)
    BYTE m_airActions; // double jumps and air dashes used in this jump; a double jump
                       // needs it below 1 (2 for some)
    BYTE unk15b;
    int m_sealLevel; // set by Akiko's supers on the opponent for 1000 ticks: 1 no dashes,
                     // 2 also no specials or supers, 3 also no jumps
    int m_timerSuper; // Akiko's timer super: 1-3 its level (the counting speed), 4 time
                      // up, 0 none; in CPlayer so that an Akiko mirror can read the
                      // opponent's
    PTR32(PatternData) m_patterns; // +0x164: one per pattern, 505 of them
    int m_attackResult;     // +0x168: of the current attack: 0 none yet, 2 guarded, 3 hit,
                            // 6 clashed
    short m_hitsLeft;       // +0x16c: hits the current attack can still land
    BYTE unk16e[0x170 - 0x16e];
    int m_canRecoilCounter; // set on a player whose attack was recoil-guarded, until its
                            // next pattern: it can recoil-guard the counterattack from
                            // any state
    short m_comboHits;      // +0x174: hits in the current combo
    BYTE unk176[0x178 - 0x176];
    double m_proration;     // +0x178: the combo's damage scaling, 10000 = 100%
    double m_defense;       // +0x180: the defender's damage factor, 1.0
    // This frame's input (ReadInput): the direction on the screen (1 right, -1 left; with
    // both held, the one away from the opponent wins), up (-1) or down (1), and whether
    // A-D went down this frame. Forward is m_inputX == facing.
    char m_inputX;          // +0x188
    char m_inputY;          // +0x189
    char m_pressA;          // +0x18a
    char m_pressB;          // +0x18b
    char m_pressC;          // +0x18c
    char m_pressD;          // +0x18d
    BYTE unk18e[0x190 - 0x18e];
    int m_holdA;            // +0x190: whether A was held last frame
    int m_holdB;            // +0x194
    int m_holdC;            // +0x198
    int m_holdD;            // +0x19c
    int m_cpuWalkRight; // CpuInput: ticks it keeps walking right
    int m_cpuWalkLeft; // CpuInput: ticks it keeps walking left
    BYTE m_bufferedPress;   // +0x1a8: the last button input during a special move
                            // (pattern 0xc8 and up), in m_inputHistory's bits
    BYTE m_dashBufferedPress; // +0x1a9: the same during a dash (0xa3-0xa6)
    BYTE m_dashBufferTime;  // +0x1aa: frames m_dashBufferedPress is kept, from 15
    // The last 180 frames of input, a ring buffer: bits 1 right, 2 left (on the screen;
    // ReadCommand works out forward from facing), 4 down, 8 up, 0x10-0x80 the buttons
    // that went down.
    char m_inputHistory[0xb4]; // +0x1ab
    BYTE unk25f;
    short m_inputPos;       // +0x260: the newest entry in m_inputHistory
    short m_command;        // +0x262: the move m_inputHistory makes, 0x63 for none
    short m_voices[0x32];   // +0x264: the character's own sound IDs; 0x96 means none
    char m_playVoice;       // +0x2c8: m_voices index CScene3 plays this frame, -1 none
    char m_playSound;       // +0x2c9: CGame::m_sounds index CScene3 plays this frame, -1 none
    short m_objectHead;
    short m_objectTail;
    BYTE unk2ce[0x2d0 - 0x2ce];
    int m_objectKeep[0x40]; // per object slot (EffectDesc::keep): AdvanceObjectHead
                            // doesn't reuse the slot while set
    int m_objectActive[0x40];       // one per object
    PlayerObject m_objects[0x40]; // +0x4d0
    // Points on the character's body relative to (x, y), five set by each constructor:
    // throws put the opponent at one of the thrower's, some moves put the character at
    // one of the opponent's.
    short m_pointX[0x14];   // +0x2ad0
    short m_pointY[0x14];   // +0x2af8
    BYTE unk2b20[0x2bc0 - 0x2b20];
    Afterimages m_afterimages;
    char m_tintColor;       // +0x30b8: Tint's
    BYTE unk30b9[0x30bc - 0x30b9];
    int m_tintTime;         // +0x30bc
    char m_fillColor;       // +0x30c0: FillBackground's
    BYTE unk30c1[0x30c4 - 0x30c1];
    int m_fillTime;         // +0x30c4
    int m_score;            // +0x30c8: below 100,000,000
    int m_scoreHigh;        // +0x30cc: the score's hundred millions
    int m_hitsLanded;       // +0x30d0
    int m_maxHits;          // +0x30d4: the round's longest combo
    int m_maxDamage;        // +0x30d8: the round's most damaging combo
    int m_wonHpTotal; // the HP left at each won round, added up (mode 2's life bonus)
    int m_hitsDecayStep; // with m_hitsDecayTimer, how m_hitsLanded falls in open play: 12
                         // after a hit, -1 per step, steps every m_hitsDecayStep*15 ticks
    int m_hitsDecayTimer; // 900 while the opponent is in hitstun; at 0 m_hitsLanded drops
                          // by one
    int m_loaded; // the sprites, patterns and voices are loaded (Load does it once)
    short m_refillMeter; // CScene3::m_refillMeter (F4/F5, recorded in replays): nonzero refills
                         // both players whenever both are in neutral; below 1000 the RF
                         // gauge's red value, 1000-1999 blue at 2000 minus it
    short m_refillHp; // the HP the refill sets: 9999 or 3332
    int m_blinkTimer; // counts down from 0x3138 and wraps; the HUD blinks and animates by
                      // it
    char m_resultPictures;  // +0x30f4: results pictures system\<name>\NN.dat to choose
                            // from at random
    char m_rivals[0x14];    // +0x30f5: m_charIds with a results picture of their own,
                            // NN = 10 + index; -1 for none
    BYTE unk3109[0x3110 - 0x3109];
    int m_cpuRoll;          // +0x3110: CpuInput's random number, Random(0, 100) or (0, 1000)
    int m_cpuAction;        // +0x3114: what CpuInput decided to do
    int m_recordUses; // CharRecord (system\<name>\<name>.rec, 0x3118-0x3137): times a
                      // human picked the character
    int m_recordVsWins;
    int m_recordVsLosses;
    DWORD m_recordBestScore;
    int m_recordBestScoreHigh;
    BYTE unk312c[0x3130 - 0x312c];
    DWORD m_recordMaxCombo;
    DWORD m_recordMaxDamage;
};

// One running effect (sparks, debris, screen flashes...). CGame keeps 640 of them in a
// ring buffer.
// BEGIN constants (tools/constants.py declare): effect types (Effect::type)
enum {
    kEffectHitBurst = 0x0,             // big blue-white star burst. The usual hit spark in
                                       // frame data (4377 attack frames, mostly with sound
                                       // 2)
    kEffectEnergySphere = 0x1,         // blue energy sphere that bursts into a ring
    kEffectGuardSpark = 0x2,           // blue ripple of rings: a guarded hit (scene3.cpp,
                                       // sound 3)
    kEffectGroundBurst = 0x3,          // fiery burst with a flat ring on the ground: a
                                       // knocked-down player hitting the ground (actions
                                       // 0x61/0x62, with a screen shake, ayu_vf6.cpp) and
                                       // attacks that slam the ground (0xd4/0xd6, sound 7)
    kEffectBlueFlames = 0x4,           // blue flames rising on both sides
    kEffectRoundFlash = 0x5,           // streaks and a flash of light: a round's call,
                                       // sound 0xb + round. At frame 10 starts 0x15 "ROUND"
                                       // and the round's digit 0x38 + round, at frame 15
                                       // the swoosh 0x1a
    kEffectGetReadyZoom = 0x6,         // "GET READY?" zooming at the screen, blended
    kEffectAttackZoom = 0x7,           // "ATTACK" zooming in a burst of streaks
    kEffectGroundRing = 0x8,           // flat blue ellipse ring: air recovery (actions
                                       // 0x9d/0x9e, started by a button in the air,
                                       // player.cpp), recoil guard (0xa8/0xa9), some supers
                                       // (Akane 0x12f-0x131)
    kEffectFlashVortex = 0x9,          // white circle that grows and turns into a blue
                                       // vortex: actions 0xa1/0xa2 (y - 60, sound 0x3e,
                                       // ayu_vf6.cpp) and some supers (Akane
                                       // 0x137/0x138/0x13b, EXNanase 0x12d-0x131, Kanna
                                       // 0x135, a Mai object
    kEffectBlueSpark = 0xa,            // small blue spark flying off at a random angle and
                                       // speed up to 16
    kEffectHitLight = 0xb,             // small orange hit spark
    kEffectHitMedium = 0xc,            // medium orange hit spark
    kEffectHitHeavy = 0xd,             // large orange hit spark with a ring
    kEffectSlashLight = 0xe,           // blue slash flash
    kEffectSlashMedium = 0xf,          // bigger blue slash flash
    kEffectSlashHeavy = 0x10,          // blue slash flash set forward of its point
    kEffectRecoilGuard = 0x11,         // swirl of blue shields: a recoil guard, the
                                       // defender having pressed back within 30 ticks
                                       // (CPlayer::m_recoilGuardWindow >= 0x1e) and entering
                                       // 0xa8/0xa9/0xaa, sound 0xa
    kEffectAttackWipe = 0x12,          // grey streak wiping across the screen as "ATTACK!!"
                                       // leaves
    kEffectDown = 0x13,                // "DOWN / Don't give up! Be prepared for next
                                       // round!" banner over the loser's half (x 80 or 240)
                                       // after a round that does not end the match, sound
                                       // 0x1d
    kEffectDownUnused = 0x14,          // the same banner with another first frame
    kEffectRoundText = 0x15,           // "ROUND"
    kEffectGetReadyIn = 0x16,          // "GET READY?" (with a small line of English under
                                       // it) appearing, sound 0x17
    kEffectGetReadyOut = 0x17,         // "GET READY?" leaving
    kEffectAttackIn = 0x18,            // "ATTACK!!" appearing, sound 0x18
    kEffectAttackOut = 0x19,           // "ATTACK!!" leaving
    kEffectRoundSwoosh = 0x1a,         // blue swoosh curve behind "ROUND"
    kEffectMotto = 0x1b,               // "the true eternal does exists here." fading in and
                                       // out at a match's start
    kEffectAttackTextUnused = 0x1c,    // "Attack!!" in blue block letters, one frame
    kEffectShatterUnused = 0x1d,       // a curve, then glass-like shards
    kEffectDoubleKoUnused = 0x1e,      // "DOUBLE K.O" text
    kEffectDashDust = 0x1f,            // cloud of dust kicked up: dashes (actions
                                       // 0xa3/0xa4, akiko_vf6.cpp) and moves that rush
                                       // forward
    kEffectSkidDust = 0x20,            // low trail of dust along the ground
    kEffectPowerBurst = 0x21,          // orange explosion with a ring of 40 sparks 0x26 on
                                       // a tilted ellipse, sound 0xb: the C version of
                                       // specials, which costs 500 of CPlayer::m_rfGauge
    kEffectSpark = 0x22,               // tiny spark drifting from its point at a random
                                       // angle, speed up to 1.6
    kEffectSliver = 0x23,              // blue sliver flying at a random angle
    kEffectDot = 0x24,                 // tiny dot flying at a random angle, speed up to 2.5
    kEffectEmber = 0x25,               // orange ember flying at a random angle
    kEffectRingSpark = 0x26,           // tiny spark moving out along a flattened ellipse
                                       // tilted by -25 degrees (CGame::m_ellipseIndex numbers
                                       // them)
    kEffectGuardParticle = 0x27,       // tiny dot thrown toward one side (side * 2 - 1)
    kEffectBlueFlash = 0x28,           // blue-white flash with a slash: action 0xf9 of
                                       // Akane, Akiko, Ayu, Kanna, Mai and Mizuka (sound
                                       // 0x13, akane_vf6.cpp)
    kEffectBlueFlashLarge = 0x29,      // larger version of 0x28
    kEffectParticleDiagonal = 0x2a,    // dot thrown 35-55 degrees up or down-back
    kEffectSliverDiagonal = 0x2b,      // sliver thrown 25-65 degrees
    kEffectParticleLevel = 0x2c,       // dot thrown within 10 degrees of level
    kEffectSliverLevel = 0x2d,         // sliver within 20 degrees of level
    kEffectEmberBounce = 0x2e,         // ember thrown up that falls under gravity and
                                       // bounces on the ground
    kEffectSliverBounce = 0x2f,        // sliver thrown backwards that falls and bounces
    kEffectDownTextUnused = 0x30,      // "DOWN!!" text
    kEffectKoUnused = 0x31,            // "K.O." text
    kEffectRushingGroundUnused = 0x32, // 640x180 ground or clouds rushing past
    kEffectGroundStillUnused = 0x33,   // a 640x300 still of the same
    kEffectExplosion = 0x34,           // big orange explosion with spinning rings: frame
                                       // data of explosive hits (sound 0x16/0x24), Akiko's,
                                       // Mai's and Nayuki's supers, Kano's and Shiori's
                                       // objects. Full effects: 16 pairs of 0x2e and 40
                                       // each of 0x35/0x36
    kEffectExplosionEmber = 0x35,      // ember thrown out along an ellipse rotated by
                                       // CGame::m_ellipseAngle, slowing by 6% a tick
    kEffectExplosionEmber2 = 0x36,     // the same on a second ellipse rotated by
                                       // CGame::m_ellipseAngle2
    kEffectStreakUnused = 0x37,        // grey streak like 0x05's
    kEffectNone = 0x38,                // a 4x4 sprite placed 640 pixels down, 40 ticks: a
                                       // hit that only plays its sound (frame data of
                                       // throws and supers, sound 0x1a), and the round
                                       // digit's slot for round 0
    kEffectDigit1 = 0x39,              // big outlined "1": a round's number, created as
                                       // 0x38 + CGame::m_round
    kEffectDigit2 = 0x3a,              // "2"
    kEffectDigit3 = 0x3b,              // "3"
    kEffectDigit4 = 0x3c,              // "4"
    kEffectDigit5 = 0x3d,              // "5"
    kEffectDigit6 = 0x3e,              // "6"
    kEffectDigit7 = 0x3f,              // "7"
    kEffectDigit8 = 0x40,              // "8"
    kEffectDigit9 = 0x41,              // "9" (the round number stops at 9)
    kEffectDigit0 = 0x42,              // "0"
    kEffectSideBlast = 0x43,           // orange blast through a ring of fire, shooting
                                       // forward
    kEffectSuperFlash1 = 0x44,         // blue ring expanding from a burst: a level 1 super
                                       // starting (0x12c, 0x12f, 0x132..., sound 0x13)
    kEffectSuperFlash2 = 0x45,         // blue crossed ellipses: a level 2 super starting
                                       // (0x12d, 0x130, 0x133..., sound 5)
    kEffectSuperFlash3 = 0x46,         // big blue burst opening into a ring: a level 3
                                       // super starting (0x12e, 0x131, 0x134..., sound
                                       // 0x40), created as kept (EffectDesc::unk0 = 1,
                                       // ayu_vf6.cpp)
    kEffectSuperSparkle = 0x47,        // cloud of blue sparkles spreading
    kEffectFirePillar = 0x48,          // orange explosion on the ground with a pillar of
                                       // fire: Akiko's 0x108/0x10a/0x10c
    kEffectEmpty = 0x49,               // no frames
};
// END constants

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
    BYTE facing; // EffectDesc::facing, copied; never read
    BYTE unk49;
    short unk4a;
    int side;    // 0 or 1; (side * 2 - 1) mirrors horizontal motion. Nonzero draws flipped.
    char scale;  // >0: drawn with CGraphics::BlitEx(scale - 1)
    BYTE layer;  // CGame::DrawEffects draws one layer at a time
    short unk52;
    BOOL screen; // position is in screen space rather than relative to the camera
    int unk58;
    int unk5c;
    int unk60;
    int unk64;
    int unk68;
    BYTE sound; // sound effect (index into CGame::m_sounds) CScene3::PlayEffectSounds
                // plays once, then -1; 0xff none
    BYTE unk6d;
    short unk6e;
};

// Parameters for CGame::CreateEffect, built on the stack by the caller.
struct EffectDesc {
    // FUNCTION: 0x405490
    EffectDesc() { memset(this, 0, sizeof(*this)); }

    int keep;    // stored per slot in CGame::m_effectUnk1d84
    short type;
    short unk6;
    double x;
    double y;
    BYTE facing;  // an object's; copied to Effect::unk48 for an effect
    BYTE unk19;
    short unk1a;
    int side;
    BYTE scale;  // copied to Effect's
    BYTE layer;
    short unk22;
    int screen;
    int shadow; // objects only: drawn with a shadow (PlayerObject::unk58)
    BYTE sound;  // copied to Effect::sound
    BYTE unk2d;
    short unk2e;
    int movesInFreeze; // objects only: keeps updating while its owner's freeze
                       // (CPlayer::m_freezeTime) runs (PlayerObject::movesInFreeze)
    RECT clip;   // an object's PlayerObject::clip
    int unk44;
};

// Shared game state: input edges, effect sprites and their ring buffer, sound effects
// and music, screen shake and palette fades.
// SIZE: 0x142f0
class CGame {
public:
    // FUNCTION: 0x406070
    CGame(CGraphics* graphics, CInput* input, CSound* sound);
    // FUNCTION: 0x406260
    ~CGame();
    // FUNCTION: 0x406440
    void Reset();
    // FUNCTION: 0x406590
    // Polls both players' controls and records which buttons went down this frame.
    void UpdateInput();
    // FUNCTION: 0x406780
    // Loads wave\se\00.wav to 64.wav.
    void LoadSounds();
    // FUNCTION: 0x406860
    void PlaySE(WORD index);
    // FUNCTION: 0x4068b0
    // Streams wave\bgm\bgmNN.wav; tracks 2, 3, 4 and 9 play once, the rest loop.
    void PlayMusic(WORD track);
    // FUNCTION: 0x406a10
    void StopMusic();
    // FUNCTION: 0x406a70
    // Moves the music volume towards `volume` by `step` each frame.
    void FadeMusic(int volume, short step);
    // FUNCTION: 0x406aa0
    // Loads the 920 effect sprites from system\effect\effect.dat, then system\object.dat.
    void LoadEffects();
    // FUNCTION: 0x406db0
    void LoadDat(PTR32(IDirectDrawSurface)* surface, const char* name, BYTE rle,
                 BYTE offset);
    // FUNCTION: 0x406e60
    // Reads the effect animations from system\effect\effect.pat.
    void LoadEffectAnims();
    // FUNCTION: 0x401c20
    // Runs one frame of the effect in slot `index`: its type-specific behaviour, then
    // its animation. Removes the effect when the animation ends.
    void UpdateEffect(short index);
    // FUNCTION: 0x407100
    // Starts an effect in the next free ring-buffer slot.
    void CreateEffect(EffectDesc* desc);
    // FUNCTION: 0x4072a0
    void RemoveEffect(short index);
    // FUNCTION: 0x407370
    // Advances the head to the next slot, pushing the tail along when it catches up.
    void AdvanceEffectHead();
    // FUNCTION: 0x4074c0
    void RemoveEffectsOfType(int type);
    // FUNCTION: 0x407560
    void ClearEffects();
    // FUNCTION: 0x4075b0
    void UpdateEffects();
    // FUNCTION: 0x407620
    // Draws the effects on one layer; (x, y) is the camera offset.
    void DrawEffects(int x, int y, BYTE layer);
    // FUNCTION: 0x4079c0
    void UpdateTimers();
    // FUNCTION: 0x407b40
    void UpdateShake();
    // FUNCTION: 0x407ce0
    // asks the fight to run `value` ticks per frame (3 normal); Shiori's supers slow it
    // down
    void SetGameSpeed(BYTE value);
    // FUNCTION: 0x407d10
    // Steps the palette fade started by FlashWhite or FlashBlack.
    void UpdateFade();
    // FUNCTION: 0x408040
    // Fades the screen to white over `in` frames, holds it `hold` frames, then fades back
    // over `out` frames.
    void FlashWhite(int in, int hold, int out);
    // FUNCTION: 0x408080
    // The same with black.
    void FlashBlack(int in, int hold, int out);
    // FUNCTION: 0x4080c0
    // shows the stage's negative for `value` frames (half at 30 FPS); every super calls it
    // as it starts
    void FlashNegative(int value);
    // FUNCTION: 0x408100
    // Sets m_extraChars: 1 if all six extra characters' files exist, 0 if one of
    // misuzu, minagi or kano is missing, -1 if one of exnanase, ikumi or kaori is.
    void CheckExtraChars();

    PTR32(CGraphics) m_graphics;
    PTR32(CInput) m_input;
    PTR32(CSound) m_sound;
    // Per player: direction (-1, 0, 1), and for the four buttons whether they went
    // down this frame and whether they are held.
    char m_inputX[2];
    char m_inputY[2];
    char m_pressA[2];
    char m_pressB[2];
    char m_pressC[2];
    char m_pressD[2];
    BOOL m_holdA[2];
    BOOL m_holdB[2];
    BOOL m_holdC[2];
    BOOL m_holdD[2];
    PTR32(IDirectDrawSurface) m_surfaces[0x398]; // effect sprites
    PTR32(IDirectDrawSurface) m_stageSurface;
    PTR32(IDirectDrawSurface) m_stageNegative;
    PTR32(IDirectDrawSurface) m_objectSurface;   // system\object.dat
    WORD m_sounds[0x41];          // sound IDs; 0x96 means none
    WORD m_music;                 // sound ID of the music; passed to the sound system every frame
    int m_musicTarget;
    int m_musicVolume;
    short m_musicStep;
    char m_stage; // stage number 0-22: background bgNN, music bgm(NN + 10), the replay
                  // header's fourth word
    BYTE m_fillSide;              // whose background fill shows when both players have one
    char m_colorKey;              // the object sprite's transparent colour
    PALETTEENTRY m_palette[0x100];
    char unk1335[3];
    int m_editColor[2]; // per side: load the player's edited palette
                        // (<name>\<name><n>.pal); chosen with down or D on character
                        // select's colour ("EDIT COLOR")
    char m_replayVersion; // the playing replay's header word 3 when above 100 (this
                          // version writes 0x68), else 0: older replays have no per-frame
                          // F4/F5 words
    char m_extraChars;
    char m_humanSide; // the side that started ARCADE or PRACTICE; the result screen's
                      // continue prompt and score use it
    BYTE m_isCpu[2]; // per side: 1 the CPU plays it (copied to CPlayer::m_cpu by the
                     // scenes that create players)
    BYTE unk1345;
    BYTE m_dummyStance; // practice: what the CPU dummy holds, 0 nothing, 1 up, 2 down; F6
                        // cycles it
    BYTE unk1347;
    int m_dummyGuard; // practice: nonzero lets the CPU dummy guard; F7 toggles it
    char m_winner;                // the side the results screen (CScene5) shows
    char m_round; // the current round, 1 at the start of a match, up to 9; picks the
                  // round call's sound (0xb + round) and digit effect (0x38 + round)
    char m_roundsToWin; // rounds a player must win: 2, or m_roundsSetting in VS CPU and
                        // VS HUMAN
    char m_roundsSetting; // config "勝利本数" (rounds to win in VS modes), 1-3, key.ini byte
                          // 0x26
    char m_intro; // the round's opening: 1 a match starts, 2 a later round starts
                  // (CScene3::StartIntro creates the effects), 0x63 the opening plays, 0
                  // fighting; players' input is ignored while nonzero
    char unk1351;
    short unk1352;
    int m_roundOver; // set by a KO; cleared (HP back to 9999, m_intro = 2) once both
                     // players are back in neutral; input is ignored while set
    char m_arcadeMatch; // arcade: the match number, 1-8 (match 7/8 bring the bosses);
                        // mode 2 also sets the CPU level from it
    BYTE unk1359[0x135c - 0x1359];
    int m_beatenChars; // arcade: bitmask (1 << character ID) of the opponents beaten, not
                       // picked again
    int m_playedStages; // bitmask (1 << stage) of the stages fought since character
                        // select; never read
    char m_gameMode; // 0 ARCADE, 1 PRACTICE, 2 arcade with stage results and score (never
                     // set: not on the title menu), 3 VS CPU, 4 VS HUMAN, 5 REPLAY, 6
                     // demo (the title left idle 1800 frames)
    char m_cpuLevel; // config "CPU難易度", 1-4, key.ini byte 0x21; copied to both players'
                     // CPU guard rate (CPlayer::m_cpuSkill)
    char m_fullEffects; // config "エフェクト": 0 簡易 (simple), 1 通常 (normal, the particle
                        // bursts are spawned); key.ini 0x23 minus 1
    char unk1367;
    BOOL m_oddFrame;                 // toggled every frame by WinMain
    int m_drawEveryFrame; // config "描画周期": 0 30FPS (the fight draws every second frame;
                          // tints, fills and the negative stage last half the frames), 1
                          // 60FPS; key.ini 0x22 minus 1
    char m_damageLevel; // config "ダメージ": 1 50%, 2 100%, 3 200% (CPlayer::AttackFactor);
                        // key.ini 0x24. Records keep max combo and damage only at 100%
    char unk1371[3];
    BOOL m_hasConfig; // key.ini's settings bytes (0x21-0x26) are present (byte 0x21 > 0);
                      // otherwise the defaults
    char m_continued; // arcade: the player chose YES at the continue prompt; the next
                      // match is a rematch with the same opponent
    char m_continuedAt; // arcade: the match at which the player last continued, 0 if
                        // never; the final boss is Kanna only if 0, else Mizuka
    BYTE unk137a[2];
    PTR32(CAnimBg) m_background;  // the stage's animated background, if it has one
    short m_effectHead;           // next slot CreateEffect uses
    short m_effectTail;           // oldest live slot
    int m_effectActive[0x280];
    int m_effectKeep[0x280]; // per ring slot: the effect was created with
                             // EffectDesc::keep; AdvanceEffectHead skips the slot while
                             // it lives
    BYTE m_effectUnk2784[0x280];
    char unk2a04[4];
    Effect m_effects[0x280];
    PTR32(EffectAnim) m_effectAnims;
    short m_hideHudTime; // frames the life bars and gauges are hidden (counts down in
                         // UpdateTimers); Akiko's, Kaori's and Misuzu's cinematic supers
                         // set 30000
    short m_hideObjectsTime; // frames only the objects with PlayerObject::drawnWhileHidden set are
                             // drawn; set by Akiko's, Kanna's, Kaori's and Misuzu's
                             // supers
    double m_shake;               // amplitude in pixels
    int m_shakeHold;              // frames before the amplitude starts to decay
    int m_shakeX;
    int m_shakeY;
    double m_shakeAngleX;         // degrees
    double m_shakeAngleY;
    int m_cameraFocusX; // camera weighting of the players' x (-50 P2 .. 50 P1) set by
                        // CPlayer::FocusCameraX for m_cameraFocusXTime frames
    int m_cameraFocusY; // vertical weighting set by CPlayer::FocusCameraY for
                        // m_cameraFocusYTime frames
    int m_cameraFocusXTime; // frames left of m_cameraFocusX; counts down only while no
                            // player is in hitstop or freeze
    int m_cameraFocusYTime; // frames left of m_cameraFocusY; the same
    RECT m_view;            // +0x14248: the part of the stage on screen, set by CScene3
    double m_bgParallax; // how fast the stage picture scrolls with the camera: 0.125 on
                         // stage 16, 1.0 elsewhere
    double m_fade;                // -100 to 100
    int m_fadeHold;
    char m_fadeDir;               // 1: FlashWhite, -1: FlashBlack, 0: none
    int m_fadeIn;
    int m_fadeOut;
    int m_negativeTime; // frames the stage is drawn in negative (FlashNegative); the
                        // animated background is hidden meanwhile
    BOOL m_speedRequested; // SetGameSpeed was called; the fight takes m_requestedSpeed at
                           // its next frame
    BYTE m_requestedSpeed; // ticks per frame asked by SetGameSpeed (CScene3::m_speed)
    char m_replaySlot; // the replay file's DATA row (0-8):
                       // replay\data<page+1>-<slot+1>.rep
    char m_replayPage; // the replay file's REPLAY page (0-8)
    char m_replayMode;      // 1 playing a replay back, 2 recording one
    CReplayFile m_replay;
    int m_ellipseIndex;                 // spawn counter for the ellipse effects (0x26, 0x35, 0x36)
    int m_ellipseAngle;                 // random angle in degrees, 0..359
    int m_ellipseAngle2;                 // m_ellipseAngle plus 30..149 degrees
    int m_swooshFrame; // effect 0x1a's frame, copied every update; never read
    int m_swooshTimer; // effect 0x1a's timer, copied every update; never read
    char unk142a8[0x142f0 - 0x142a8];
};

// Base of the scenes WinMain runs: Update returns the index of the next scene. The
// constructor and the fades are inline; their copies follow the first scene object.
class CScene {
public:
    // FUNCTION: 0x759c10
    CScene(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5,
           CInput* p6, CSound* p7)
    {
        m_player1Ref = p2;
        m_player2Ref = p3;
        m_hwnd = p1;
        m_players[0] = *p2;
        m_players[1] = *p3;
        m_game = p4;
        m_graphics = p5;
        m_input = p6;
        m_sound = p7;
        m_enter = -1;
        m_leave = 0;
    }
    // FUNCTION: 0x759c90
    // Darkens (p2 0) or brightens (p2 1) the palette over 21 frames, drawing each one, and
    // fades the music volume with it.
    void FadeOut(PALETTEENTRY* p1, BYTE p2, int p3, int p4)
    {
        int l10;
        int vc;
        int x8;
        int l4;

        x8 = timeGetTime();
        l4 = 0;
        if (p2 == 0) {
            vc = 0x14;
            for (; vc >= 0; vc--) {
                Draw();
                m_graphics->Darken(p1, 0, 0xff, vc * 5);
                m_sound->SetVolume((short)m_game->m_music, p3 - (0x14 - vc) * p4 / 2);
                while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
                }
                x8 = timeGetTime();
                l4 = l4 == 0;
            }
        }
        if (p2 == 1) {
            l10 = 0x14;
            for (; l10 >= 0; l10--) {
                Draw();
                m_graphics->Brighten(p1, 0, 0xff, l10 * 5);
                m_sound->SetVolume((short)m_game->m_music, p3 - (0x14 - l10) * p4 / 2);
                while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
                }
                x8 = timeGetTime();
                l4 = l4 == 0;
            }
        }
    }
    // FUNCTION: 0x759e20
    // The same without the music.
    void FadeIn(PALETTEENTRY* p1, BYTE p2)
    {
        int l10;
        int vc;
        int x8;
        int l4;

        x8 = timeGetTime();
        l4 = 0;
        if (p2 == 0) {
            vc = 0;
            for (; vc <= 0x14; vc++) {
                Draw();
                m_graphics->Darken(p1, 0, 0xff, vc * 5);
                while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
                }
                x8 = timeGetTime();
                l4 = l4 == 0;
            }
        }
        if (p2 == 1) {
            l10 = 0;
            for (; l10 <= 0x14; l10++) {
                Draw();
                m_graphics->Brighten(p1, 0, 0xff, l10 * 5);
                while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
                }
                x8 = timeGetTime();
                l4 = l4 == 0;
            }
        }
    }

    virtual void Draw() = 0;
    virtual BYTE Update() = 0;
    // reads the keyboard each frame: Esc leaves; character select's F1-F4 load key
    // bindings; the fight's F4-F8 and replay words
    virtual void HandleKeys() = 0;

    UINT lastMessage;       // set by WndProc to the message it is handling
    HWND m_hwnd;
    PTR32(CPlayer) m_players[2];        // the players when the scene was made
    PTR32(PTR32(CPlayer)) m_player1Ref; // WinMain's g_player1 and g_player2
    PTR32(PTR32(CPlayer)) m_player2Ref;
    PTR32(CGame) m_game;
    PTR32(CGraphics) m_graphics;
    PTR32(CInput) m_input;
    PTR32(CSound) m_sound;
    char m_enter; // nonzero: the next Update starts the scene over (state reset, fade
                  // in); the value picks how it fades in
    char m_leave; // nonzero: the next Update fades out and returns another scene.
                  // CScene3: 1 quit (Esc, a replay's end, a key in the demo), 2 the match
                  // is over. CScene8: 2 go to record a replay
    PALETTEENTRY m_palette[0x100]; // +0x2e
    char m_colorKey;        // +0x42e
    BYTE unk42f;
};

// One of an animated background's objects: 0x70 bytes.
struct BgObject : ObjBase {
    char scale;             // +0x50: as Effect's
    char layer;             // +0x51
    BYTE unk52[0x70 - 0x52];
};

// An animated stage background: its frames are system\bg\bgNN\MMM.dat.
class CAnimBg {
public:
    // FUNCTION: 0x7519f0
    CAnimBg() {}
    // FUNCTION: 0x750d30
    void Load();
    // FUNCTION: 0x751030
    void LoadAnims();

    virtual void Update() = 0;
    // (x, y, layer): draws the objects on that layer at the camera offset; CBg01 has only
    // layer 0
    virtual void Draw(int p1, int p2, char p3) = 0;

    short m_number;         // +4: NN in system\bg\bgNN
    short m_lastFrame;      // +6: frames 0 to m_lastFrame
    PTR32(CGraphics) m_graphics;                 // +8
    PTR32(PTR32(IDirectDrawSurface)) m_surfaces; // +0xc: one per frame
    PTR32(BgObject) m_objects;                   // +0x10
    PTR32(EffectAnim) m_anims;                   // +0x14
    char m_colorKey;        // +0x18
    BYTE unk19[0x1c - 0x19];
};

// Bg01: derived from CAnimBg.
// SIZE: 0x1c
class CBg01 : public CAnimBg {
public:
    // FUNCTION: 0x751370
    CBg01(CGraphics* p1);
    // FUNCTION: 0x751500
    ~CBg01();
    // FUNCTION: 0x7515d0
    virtual void Update();
    // FUNCTION: 0x751730
    virtual void Draw(int p1, int p2, char p3);

};

// Bg10: derived from CAnimBg.
// SIZE: 0x1c
class CBg10 : public CAnimBg {
public:
    // FUNCTION: 0x751a40
    CBg10(CGraphics* p1);
    // FUNCTION: 0x751bc0
    ~CBg10();
    // FUNCTION: 0x751c90
    virtual void Update();
    // FUNCTION: 0x751df0
    virtual void Draw(int p1, int p2, char p3);

};

// Bg12: derived from CAnimBg.
// SIZE: 0x1c
class CBg12 : public CAnimBg {
public:
    // FUNCTION: 0x7520b0
    CBg12(CGraphics* p1);
    // FUNCTION: 0x752240
    ~CBg12();
    // FUNCTION: 0x752310
    virtual void Update();
    // FUNCTION: 0x752470
    virtual void Draw(int p1, int p2, char p3);

};

// Bg16: derived from CAnimBg.
// SIZE: 0x1c
class CBg16 : public CAnimBg {
public:
    // FUNCTION: 0x752900
    CBg16(CGraphics* p1);
    // FUNCTION: 0x752a90
    ~CBg16();
    // FUNCTION: 0x752b60
    virtual void Update();
    // FUNCTION: 0x752dc0
    virtual void Draw(int p1, int p2, char p3);

};

// Scene1: derived from CScene.
// SIZE: 0x560
class CScene1 : public CScene {
public:
    // FUNCTION: 0x753260
    CScene1(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x7538b0
    ~CScene1();
    // FUNCTION: 0x7539f0
    virtual BYTE Update();
    // FUNCTION: 0x755500
    virtual void Draw();
    // FUNCTION: 0x7586b0
    void CreateCharacter(PTR32(CPlayer)* p1, PTR32(CPlayer)* p2, char p3);
    // FUNCTION: 0x759460
    void LoadStagePicture();
    // FUNCTION: 0x7595d0
    void SetPortraitPalette(char p1);
    // FUNCTION: 0x759770
    virtual void HandleKeys();
    // FUNCTION: 0x7598d0
    void Enter();

    BYTE unk430[0x434 - 0x430];
    int m_bgSurface;
    int m_obSurface;
    int m_stagePicture;
    int m_stageNames;
    int m_portraits[0x2]; // indexed
    char m_colorKeys[0x4]; // indexed
    double m_bgScroll;
    double m_p1BarOffset;
    double m_p2BarOffset;
    double m_barScroll;
    double m_gridY;
    int m_bgSlideTime;
    int m_anim[0x6]; // [0], [1] the side bars' slide speeds (2 in, -2 out); [2] unused;
                     // [3] the grid's slide angle (0-60); [4] the stage list's opening
                     // angle (0-90); [5] its scroll angle
    short m_portraitAngle[0x2]; // indexed
    short m_portraitOffset[0x2]; // indexed
    BYTE m_held[0x2]; // indexed
    char m_state[0x2]; // per side: 5 intro, 0 choosing, 1 portrait sliding in, 2 sliding
                       // out (B), 3 choosing colour, 6 done, 7 stage list opening, 4
                       // choosing a stage, 8 closing it, 9/10 scrolling it up/down
    char m_namePlate[0x19]; // character ID -> row of its name plate in chr_sel_ob.dat (y
                            // 0x100 + row * 32)
    char m_grid[0x18]; // grid cell (column + row * 3, 3 x 8) -> character ID; -1 the "?"
                       // random cell
    BYTE unk4d1[0x4d4 - 0x4d1];
    int m_portraitShift[0x18]; // grid cell -> x shift of the big portrait
    BYTE unk534[0x538 - 0x534];
    char m_cursorX[0x2]; // indexed
    char m_cursorY[0x2]; // indexed
    char m_charId[0x2]; // indexed
    char m_paletteIndex[0x2]; // per side: colour 0-5 (two sides on one character never
                              // share one); -1 for arcade's CPU
    short m_randomTime[0x2]; // per side: frames of random cursor moves after C or the "?"
                             // cell; [0] also times the random stage
    BYTE m_stageHidden[0xd]; // one byte per stage, 0x17 in all with the following
                             // members: the stage list skips set ones (stages 13-16
                             // without the extra characters, 18-22 when m_extraChars is
                             // -1)
    char m_stageHidden13;
    char m_stageHidden14;
    char m_stageHidden15;
    char m_stageHidden16;
    BYTE unk555[0x556 - 0x555];
    char m_stageHidden18;
    char m_stageHidden19;
    char m_stageHidden20;
    char m_stageHidden21;
    char m_stageHidden22;
    BYTE unk55b[0x560 - 0x55b];
};

// Scene6: derived from CScene.
// SIZE: 0x760
class CScene6 : public CScene {
public:
    // FUNCTION: 0x759f30
    CScene6(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x75a3b0
    ~CScene6();
    // FUNCTION: 0x75a4c0
    virtual BYTE Update();
    // FUNCTION: 0x75b0a0
    virtual void Draw();
    // FUNCTION: 0x75d260
    void DrawNumber(int p1, int p2, int p3);
    // FUNCTION: 0x75d350
    virtual void HandleKeys();
    // FUNCTION: 0x75d400
    void LoadRecord();
    // FUNCTION: 0x75d580
    void SwitchRecord();
    // FUNCTION: 0x75d660
    void ShowLoadingScreen();
    // FUNCTION: 0x75d8d0
    void FadeToBlack(int p1);
    // FUNCTION: 0x75d970
    void FadeFromBlack(BYTE p1);
    // FUNCTION: 0x75da30
    void SlidePage(BYTE p1);

    BYTE unk430[0x434 - 0x430];
    int m_bgSurface;
    int m_menuSurface;
    int m_portraitSurface;
    int m_scoreSurface;
    int m_loadingSurface;
    char m_cursor;
    char m_recordChar;
    char unk44a;
    BYTE m_held[0x3]; // [0], [1] per player: a direction is held; [2] the page: 0 menu, 1
                      // records, 2 loading screens
    BYTE unk44e[0x450 - 0x44e];
    CharRecord m_record;    // +0x450: the shown character's
    char m_names[0x18][0x1e]; // +0x470: the characters' folder names
    char m_portraitKey;
    char m_scoreKey;
    BYTE unk742[0x748 - 0x742];
    double unk748;
    int m_portraitX;
    int m_pageY;
    int m_loadingScreen;
    BYTE unk75c[0x760 - 0x75c];
};

// Scene3: derived from CScene.
// SIZE: 0x598
class CScene3 : public CScene {
public:
    // FUNCTION: 0x75db70
    void DrawNumber(int p1, int p2, int p3, BYTE p4, BYTE p5, int p6);
    // FUNCTION: 0x75dd50
    void DrawBackground();
    // FUNCTION: 0x75e240
    void DrawLifeBars();
    // FUNCTION: 0x760060
    void DrawGauges();
    // FUNCTION: 0x7623b0
    void DrawComboCount(CPlayer* p1);
    // FUNCTION: 0x762c50
    void DrawShadows();
    // FUNCTION: 0x7631f0
    void DrawBordersAndFlip();
    // FUNCTION: 0x7633a0
    CScene3(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x763c00
    ~CScene3();
    // FUNCTION: 0x763c20
    virtual BYTE Update();
    // FUNCTION: 0x7642a0
    virtual void Draw();
    // FUNCTION: 0x7647b0
    void UpdateCamera();
    // FUNCTION: 0x764db0
    void PlayPlayerSounds();
    // FUNCTION: 0x764f10
    void PlayEffectSounds();
    // FUNCTION: 0x765040
    // handles KOs: round wins, the DOWN banner, a double KO (both rounds counted, never
    // ending the match), the match's end and m_winner
    void CheckKo();
    // FUNCTION: 0x765660
    virtual void HandleKeys();
    // FUNCTION: 0x765fa0
    int UpdateEndFade();
    // FUNCTION: 0x766070
    // creates a round's opening effects when CGame::m_intro asks (1: 0x1b then the round
    // call, 2: the round call 0x05)
    void StartIntro();
    // FUNCTION: 0x7661a0
    // F6 while recording a replay: starts the file and the match over
    void RestartRecording();
    // FUNCTION: 0x766480
    void CheckHits();
    // FUNCTION: 0x766b50
    // separates the players' overlapping collision boxes (box90) and averages their speeds
    // into CPlayer::m_pushVx
    void PushApart();
    // FUNCTION: 0x767600
    RECT BoxOnStage(ObjBase* p1, RECT* p2);
    // FUNCTION: 0x7677a0
    RECT InfoBoxOnStage(CollisionInfo* p1, RECT* p2);
    // FUNCTION: 0x767930
    int BoxesOverlap(RECT* p1, RECT* p2);
    // FUNCTION: 0x7679b0
    // whether p2 will recoil-guard p1's attack using m_canRecoilCounter; then p2's own
    // attack isn't resolved this tick
    int WillRecoilCounter(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4);
    // FUNCTION: 0x767f60
    // p1's attack against p2: parry, recoil guard, guard point, guard, armor, or the hit
    void ResolvePlayerAttack(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4);
    // FUNCTION: 0x7697d0
    // p1's object p3 against p2
    void ResolveObjectAttack(CPlayer* p1, CPlayer* p2, int p3, CollisionInfo* p4);
    // FUNCTION: 0x76b090
    // p1's object p3 against p2's object p4
    void ResolveObjectHitsObject(CPlayer* p1, CPlayer* p2, int p3, int p4);
    // FUNCTION: 0x76bab0
    // two objects' push boxes meet: the lower level is cancelled
    void ClashObjects(CPlayer* p1, CPlayer* p2, int p3, int p4);
    // FUNCTION: 0x76bd40
    // p1's attack against p2's object p5
    void ResolvePlayerHitsObject(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4, int p5);

    BYTE unk430[0x434 - 0x430];
    int m_frameCount;
    int m_secondStart;
    int m_fps; // frames drawn last second; shown at the top of the screen
    int m_focusXDefault;
    int m_focusYHigh;
    int m_focusX; // camera weighting of P1's x against P2's, -50..50 (0 midway)
    int m_focusY;
    int m_focusYStep;
    int m_scrollX; // stage-to-screen x offset, -319..0, easing toward the players
    int m_scrollY; // stage-to-screen y offset, 0..240
    int m_drawX; // m_scrollX plus the screen shake: what everything is drawn with
    int m_drawY;
    RECT m_digitFonts[0x11]; // 17 digit sets in system\object.dat: top, bottom, and the
                             // digit width in .right
    short m_refillMeter; // F4/F5 (practice, VS, replay): nonzero refills both players in
                         // neutral (gauge 3000, HP m_refillHp, CPlayer::m_rfGauge = value,
                         // or 2000 - value with m_rfBlue set from 1000 up); written to
                         // replays each frame
    short m_refillHp; // HP the refill sets: 9999, or 3332 after F5's second press; the
                      // replay's second per-frame word
    BYTE m_speed; // fight ticks per frame: 3, 1 after a match-ending KO, or
                  // CGame::SetGameSpeed's
    BYTE unk579[0x580 - 0x579];
    double m_endFade; // frames since the match ended: whitens the screen and fades the
                      // music for 100; the scene ends at 200
    int m_paused; // F8: nonzero stops the fight (Update returns at once)
    int m_capturing; // debug (F9/F10, compiled out): saves a screenshot every second
                     // frame
    int m_captureFrame;
    BYTE unk594[0x598 - 0x594];
};

// Scene2: derived from CScene.
// SIZE: 0x438
class CScene2 : public CScene {
public:
    // FUNCTION: 0x76c6f0
    CScene2(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x76c740
    ~CScene2();
    // FUNCTION: 0x76c790
    virtual BYTE Update();
    // FUNCTION: 0x76c980
    virtual void Draw();
    // FUNCTION: 0x76ca50
    void SetupMatch();
    // FUNCTION: 0x76da10
    virtual void HandleKeys();
    // FUNCTION: 0x76da20
    void CreateCharacter(PTR32(CPlayer)* p1, PTR32(CPlayer)* p2, char p3, char p4);

    BYTE unk430[0x434 - 0x430];
    int m_loadingSurface;
};

// Scene8: derived from CScene.
// SIZE: 0x758
class CScene8 : public CScene {
public:
    // FUNCTION: 0x76e480
    CScene8(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x76efe0
    ~CScene8();
    // FUNCTION: 0x76f060
    virtual BYTE Update();
    // FUNCTION: 0x76f780
    virtual void Draw();
    // FUNCTION: 0x770d80
    virtual void HandleKeys();
    // FUNCTION: 0x770e30
    void Enter();
    // FUNCTION: 0x771170
    void FadeOutDimmed();
    // FUNCTION: 0x771230
    void FadeInDimmed();

    BYTE unk430[0x434 - 0x430];
    int m_bgSurface;
    int m_menuSurface;
    int unk43c;
    int unk440;
    BYTE unk444[0x446 - 0x444];
    short unk446;
    short unk448;
    short unk44a;
    short unk44c;
    BYTE m_held[0x13]; // [0], [1] per player: a direction or B is held; [2]-[0x12] a
                       // character table the constructor fills and nothing reads
    BYTE unk461[0x462 - 0x461];
    char unk462;
    char unk463;
    char unk464;
    char unk465;
    BYTE unk466[0x467 - 0x466];
    char unk467;
    BYTE unk468[0x469 - 0x468];
    char m_state;
    char m_slot;
    char m_menuChoice;
    char m_overwriteChoice;
    char m_page;
    char m_replays[0x2da]; // [page * 9 + slot] the file exists; at +0x51 [page][slot * 2
                           // + side] its two character IDs; at +0xf6 RECTs the
                           // constructor sets and nothing reads
    double m_menuAngle;
    double m_listScroll;
};

// Scene5: derived from CScene.
// SIZE: 0x474
class CScene5 : public CScene {
public:
    // FUNCTION: 0x7712f0
    CScene5(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x771400
    ~CScene5();
    // FUNCTION: 0x7714e0
    virtual BYTE Update();
    // FUNCTION: 0x772800
    virtual void Draw();
    // FUNCTION: 0x774a10
    void DrawNumber(int p1, int p2, int p3);
    // FUNCTION: 0x774b00
    void Enter();
    // FUNCTION: 0x775750
    virtual void HandleKeys();

    BYTE unk430[0x434 - 0x430];
    int m_winnerSurface;
    int m_resultSurface;
    int m_winPicture;
    int m_portrait;
    short m_panX;
    short m_panSpeed;
    short m_band1X;
    short m_band1Y;
    short m_band2X;
    short m_band2Y;
    short m_curtain;
    short m_curtainSpeed;
    short m_portraitX;
    short m_portraitSpeed;
    short m_pictureY;
    short m_pictureSpeed;
    short m_entranceTime;
    char m_state; // 0 the loser's entrance, 1 shown, 2 arcade's continue prompt, 3 mode
                  // 2's stage result
    char m_continueChoice;
    char m_held;
    BYTE unk461[0x464 - 0x461];
    int m_lifeBonus;
    int m_comboBonus;
    int m_damageBonus;
    int m_straightBonus;
};

// Scene7: derived from CScene.
// SIZE: 0x448
class CScene7 : public CScene {
public:
    // FUNCTION: 0x7758b0
    CScene7(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x7759a0
    ~CScene7();
    // FUNCTION: 0x7759f0
    virtual BYTE Update();
    // FUNCTION: 0x775b80
    virtual void Draw();
    // FUNCTION: 0x775d50
    virtual void HandleKeys();

    BYTE unk430[0x434 - 0x430];
    int m_staffSurface;
    double m_scroll;
    int m_skip;
    BYTE unk444[0x448 - 0x444];
};

// Scene0: derived from CScene.
// SIZE: 0x44c
class CScene0 : public CScene {
public:
    // FUNCTION: 0x775d60
    CScene0(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x775f30
    ~CScene0();
    // FUNCTION: 0x775fb0
    virtual BYTE Update();
    // FUNCTION: 0x7764b0
    virtual void Draw();
    // FUNCTION: 0x776760
    virtual void HandleKeys();
    // FUNCTION: 0x776820
    void DimTitle();
    // FUNCTION: 0x7768d0
    void UndimTitle();

    BYTE unk430[0x434 - 0x430];
    int m_titleSurface;
    int m_menuSurface;
    char m_cursor; // title menu row: 0 ARCADE, 1 VS CPU, 2 VS HUMAN, 3 PRACTICE, 4
                   // REPLAY, 5 OPTION, 6 EXIT
    BYTE unk43d[0x43e - 0x43d];
    short unk43e;
    BYTE m_held[0x3]; // [0], [1] per player: up or down is held (the cursor moves once
                      // per press); [2] cleared, never read
    BYTE unk443[0x444 - 0x443];
    DWORD m_idleTime; // frames without up or down; at 1800 the demo starts
    int m_dimming;
};

// Shiori: one of the character classes.
// SIZE: 0x3458
class CShiori : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CShiori's own actions
    enum {
        k5A = 0xc8,                 // A standing
        k5BClose = 0xc9,            // B standing within 70 px of the opponent
        k5BFar = 0xca,              // B standing otherwise
        k5C = 0xcb,                 // C standing
        k2A = 0xcc,                 // A crouching
        k2B = 0xcd,                 // B crouching
        k2C = 0xce,                 // C crouching
        kJumpA = 0xcf,              // A in the air
        kJumpB = 0xd0,              // B in the air
        kJumpC = 0xd1,              // C in the air
        kThrow = 0xdc,              // C + forward/back within 30 px of a grounded opponent
                                    // not in hitstun
        kThrowConnected = 0xdd,     // the ground throw connected: DealDamage(1000) at loop
                                    // 8, opponent -> 0x56
        kDashA = 0xe6,              // A during the forward dash 0xa3
        kDashB = 0xe7,              // B during 0xa3
        kDashC = 0xe8,              // C during 0xa3, a hop (vx 1, vy -0.9)
        kDash2A = 0xe9,             // 2A during 0xa3
        kDash2B = 0xea,             // 2B during 0xa3
        kDash2C = 0xeb,             // 2C during 0xa3
        kAirThrow = 0xf8,           // 6C in the air within 100 px of an airborne opponent
        kAirThrowConnected = 0xf9,  // the air throw connected: DealDamage(1100) at loop 8,
                                    // opponent -> 0x56
        k236A = 0xfa,               // cmd 0xa
        k236B = 0xfb,               // cmd 0xb (or 0xc without the EX meter)
        k236C = 0xfc,               // cmd 0xc with m_rfGauge >= 500 or m_rfBlue
        k623A = 0xfd,               // cmd 0x14
        k623B = 0xfe,               // cmd 0x15 (or 0x16 without the EX meter)
        k623C = 0xff,               // cmd 0x16 with m_rfGauge >= 500 or m_rfBlue
        kAir412A = 0x100,           // cmd 0x28 in the air
        kAir412B = 0x101,           // cmd 0x29 in the air
        kAir412C = 0x102,           // cmd 0x2a in the air with m_rfGauge >= 500 or m_rfBlue
        k214A = 0x103,              // cmd 0x1e on the ground, refused while m_summonOut
        k214B = 0x104,              // cmd 0x1f
        k214C = 0x105,              // cmd 0x20 with m_rfGauge >= 500 or m_rfBlue
        kAir236A = 0x106,           // cmd 0xa in the air
        kAir236B = 0x107,           // cmd 0xb in the air
        kAir236C = 0x108,           // cmd 0xc in the air with the EX meter
        k412A = 0x109,              // cmd 0x28 on the ground
        k412B = 0x10a,              // cmd 0x29 on the ground
        k412C = 0x10b,              // cmd 0x2a on the ground (no EX meter needed or spent)
        kAir214A = 0x10c,           // cmd 0x1e in the air
        kAir214B = 0x10d,           // cmd 0x1f in the air
        kAir214C = 0x10e,           // cmd 0x20 in the air with the EX meter
        kUnusedSuperSummon = 0x12c, // never started (no StartCommand or CPU path)
        k641236A = 0x12f,           // cmd 0x78-0x7a with 1000 gauge (LV1)
        k641236B = 0x130,           // cmd 0x79/0x7a with 2000 gauge (LV2)
        k641236C = 0x131,           // cmd 0x7a with 3000 gauge (LV3)
        k214214A = 0x132,           // cmd 0x6e-0x70 with 1000 gauge (LV1)
        k214214B = 0x133,           // cmd 0x6f/0x70 with 2000 gauge (LV2)
        k214214C = 0x134,           // cmd 0x70 with 3000 gauge (LV3)
        k5D = 0x135,                // D on the ground while m_dObjectTime == 0
        kUnused5DLv2 = 0x136,       // never started
        kUnused5DLv3 = 0x137,       // never started
        kAir21436A = 0x138,         // cmd 0xaa-0xac in the air with 1000 gauge (LV1)
        kAir21436B = 0x139,         // cmd 0xab/0xac in the air with 2000 (LV2)
        kAir21436C = 0x13a,         // cmd 0xac in the air with 3000 (LV3)
        k21436A = 0x13b,            // cmd 0xaa-0xac on the ground with 1000 (LV1)
        k21436B = 0x13c,            // cmd 0xab/0xac with 2000 (LV2)
        k21436C = 0x13d,            // cmd 0xac with 3000 (LV3)
        kLv4 = 0x13e,               // cmd 0x5f = 236236 B C with exactly 3000 gauge and HP
                                    // < 3333
        kLv4Connected = 0x13f,      // the LV4 object caught the opponent: she leaps to
                                    // them, holds 360 frames, 0x1bd deals 5000
        kObj5CEffect = 0x190,       // 5C's ground effect, no hits
        kObj236AB = 0x191,          // 236A/B's attack object, stationary, 3 hits (hitsLeft)
        kObjAir412AB = 0x192,       // air 412A/B's object: falls at (2, 2) until the ground
        kObjAir412C = 0x194,        // air 412C's: the same with 4 hits
        kObjUnusedSummon = 0x195,   // never spawned
        kObj214AAppear = 0x197,     // 214A's call, behind her
        kObjAir236AB = 0x198,       // air 236A/B's attack object, kept at her front while
                                    // 0x106-0x108
        kObj214BAttack = 0x199,     // what the 214B creatures shoot (1 hit)
        kObj214BAppear = 0x19a,     // 214B's call
        kObjSummonDebris1 = 0x19c,  // one of five pieces a broken 214 creature bursts into,
                                    // plain rand lifetime 80-140
        kObjSummonDebris2 = 0x19d,
        kObjSummonDebris3 = 0x19e,
        kObjSummonDebris4 = 0x19f,
        kObjSummonDebris5 = 0x1a0,
        kObj623CEffect = 0x1a1,     // kept on her (x+23, y-48) while 0xff, removed after
        kObj412Drop = 0x1a2,        // 412's falling object: from 480+ px up, 1 hit, shakes
                                    // the screen on landing
        kObjLv4Start = 0x1a3,       // drifting effect at the LV4's start (also the unused
                                    // 0x12c)
        kObj214214AHit = 0x1a4,     // dropped by the 214214A mover, 1 hit, then 0x1b0
        kObj214214BHit = 0x1a5,     // the same for 214214B
        kObj214214CHit = 0x1a6,     // the same for 214214C
        kObj5D = 0x1a7,             // 5D's object, kept on her (x, y-50), re-armed with 1
                                    // hit every frame
        kObjUnused5DLv2 = 0x1a8,    // 0x136's object: as 0x1a7, -3 a frame
        kObjUnused5DLv3 = 0x1a9,    // 0x137's: -2 a frame
        kObj236C = 0x1ab,           // 236C's attack objects, 1 hit each
        kObjAir236C = 0x1ac,        // air 236C's, kept at one of three offsets
                                    // (m_patternVar3) from her while 0x106-0x108
        kObj641236Column = 0x1ad,   // 641236's column piece, stacked 80 px apart, renews
                                    // itself while the super runs
        kObj641236Foot = 0x1ae,     // the piece at the column's foot
        kObj641236CFoot = 0x1af,    // the extra foot piece of 641236C
        kObj214214HitEnd = 0x1b0,   // what 0x1a4-0x1a6 become when their animation ends
        kObj214A = 0x1b1,           // 214A's creature: hovers near her, then charges at vx
                                    // 4 (1 hit)
        kObj214B = 0x1b2,           // 214B's creature: hovers, shoots 0x199 three times
        kObj21436Shot = 0x1b3,      // 21436's shot, 1 hit, angle Random(0,90)-45, speed
                                    // Random(30,25)/10
        kObj21436Flash = 0x1b4,     // spawned with each shot, no hits
        kObj214214AMover = 0x1b5,   // moves along the ground at vx 1, drops 0x1a4 each
                                    // cycle (3)
        kObj214214BMover = 0x1b6,   // vx 1.5 +0.5 a cycle, drops 0x1a5 (6)
        kObj214214CMover = 0x1b7,   // vx 1.5 +0.4 a cycle, drops 0x1a6 at y +-10 (15)
        kObjLv4 = 0x1b8,            // the LV4's object in front of her (99 hits)
        kObjLv4Wait = 0x1b9,        // armed: a hit during 0x13e saves the opponent's
                                    // position, -> 0x1bc and she -> 0x13f
        kObjLv4Toss = 0x1ba,        // after 0x1bc: shakes the opponent at m_lv4Hold, throws
                                    // them up (vy -10.5), places them at frames 9-12
        kObjLv4End = 0x1bb,         // 0x1b9 fading when it caught nothing or she left 0x13e
        kObjLv4Hold = 0x1bc,        // holds the opponent at m_lv4HoldX/Y with Random
                                    // jitter, then 0x1ba
        kObjLv4Finish = 0x1bd,      // spawned on the opponent by 0x13f's hit
        kObjLv4Piece1 = 0x1be,      // one of four pieces from 0x1bd
        kObjLv4Piece2 = 0x1bf,
        kObjLv4Piece3 = 0x1c0,
        kObjLv4Piece4 = 0x1c1,
        kObjAir214BAppear = 0x1c2,  // air 214B's call
        kObjAir214B = 0x1c3,        // air 214B's creature: stays put, shoots 0x199 three
                                    // times
        kObj214CAppear = 0x1c4,     // 214C's call (ground and air)
        kObj214CStop = 0x1c5,       // 0x1c6 when its drift ends: stays, 2 hits a cycle for
                                    // 4 cycles
        kObj214C = 0x1c6,           // 214C's creature: drifts forward (vx 1.65, slowing)
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CShiori's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd236236C = 0x5f, // 2 3 6 2 3 6 C, within 90 frames
        kCmd236236B = 0x65, // 2 3 6 2 3 6 B, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
        kCmd21436A = 0xaa,  // 21436 + A, within 90 frames
        kCmd21436B = 0xab,  // 21436 + B, within 90 frames
        kCmd21436C = 0xac,  // 21436 + C, within 90 frames
        kCmd21436D = 0xad,  // 21436 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x4136d0
    virtual void UpdatePattern();
    // FUNCTION: 0x422d70
    CShiori(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x422f40
    virtual void Reset();
    // FUNCTION: 0x423090
    virtual void StartPattern();
    // FUNCTION: 0x4230d0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x423120
    virtual void Move();
    // FUNCTION: 0x423140
    virtual void StartCommand();
    // FUNCTION: 0x425d70
    virtual void DrawGauge();
    // FUNCTION: 0x4261b0
    virtual void PreUpdate();
    // FUNCTION: 0x4261c0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4261f0
    virtual void ReadCommand();
    // FUNCTION: 0x4276b0
    virtual void CpuInput();
    // FUNCTION: 0x42b190
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current action, zeroed by StartPattern: loop
                       // counts (how often a frame repeats), frame countdowns
    int m_patternVar2; // Scratch for the current action, zeroed by StartPattern: frame
                       // counters, vx * 100 held over the 21436 super flash
    int m_patternVar3; // Scratch for the current action, zeroed by StartPattern: throw
                       // loop count, vy * 100 over the super flash, which 0x1ac air 236C
                       // is spawning (0-2)
    int m_encasedBreakOut; // 1 while the object 0x1f0 that shared actions 0x53-0x56 spawn
                           // is out; cleared when it bursts into 0x1f1/0x1f2
    int m_summonOut; // 1 while one of her 214 creatures (0x1b1, 0x1b2, 0x1c3, 0x1c5,
                     // 0x1c6) is out, which blocks another 214; set by the creature every
                     // frame
    int m_dObjectTime; // Frames x4 left on her 5D object 0x1a7: 3600 at the start, -4 a
                       // frame (900 frames); D is refused while nonzero; DrawGauge draws
                       // it as a bar
    int m_lv4HoldX; // The opponent's x (int) when the LV4 object caught them; the hold
                    // objects shake the opponent around it
    int m_lv4HoldY; // The opponent's y (int) when the LV4 object caught them
    int m_objectVar1[0x40]; // Per-object scratch, zeroed by RemoveObject: usually a once-
                            // flag and loop count; 0x1ac's x offset
    int m_objectVar2[0x40]; // Per-object scratch, zeroed by RemoveObject: usually a
                            // lifetime countdown (debris); 0x1ac's y offset, 0x1b7's
                            // height toggle
    int m_objectVar3[0x40]; // Per-object scratch, zeroed by RemoveObject: a once-flag
                            // (0x1b6, 0x1b7)
};

// Sayuri: one of the character classes.
// SIZE: 0x3458
class CSayuri : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CSayuri's own actions
    enum {
        k5A = 0xc8,                     // 5A
        k5BClose = 0xc9,                // 5B within 70 px
        k5BFar = 0xca,                  // 5B otherwise
        k5C = 0xcb,                     // 5C, 2 hits
        k2A = 0xcc,                     // 2A
        k2B = 0xcd,                     // 2B
        k2C = 0xce,                     // 2C (jump-cancels on hit only)
        kJumpA = 0xcf,                  // j.A
        kJumpB = 0xd0,                  // j.B
        kJumpC = 0xd1,                  // j.C
        kUnusedDive = 0xd2,             // unreached: air dive (vx 1, vy 1), 3 hits
        kUnusedDiveRebound = 0xd5,      // unreached: bounce back (vx -1, vy -2.4), as
                                        // Makoto's 0xd5
        kUnusedDiveLanding = 0xd6,      // unreached: landing with a screen shake
        kThrow = 0xdc,                  // ground throw
        kThrowHold = 0xdd,              // the ground throw: 1150 damage at frame 3
        kUnusedDashA = 0xe6,            // unreached: no StartCommand path
        kUnusedDashB = 0xe7,            // unreached
        kUnusedDashC = 0xe8,            // unreached: hop (vx 1.1, vy -2.5)
        kAirThrow = 0xf8,               // air 6C near an airborne opponent
        kAirThrowHold = 0xf9,           // the air throw: spins (m_patternVar1 loops, 0x1a6
                                        // at the second), 1200 damage
        k236A = 0xfa,                   // 236A on the ground with no shot out (m_shotsOut
                                        // 0): shot 0x191 at frame 4
        k236B = 0xfb,                   // 236B: shot 0x191
        k236C = 0xfc,                   // 236C (costs 500/250 of m_rfGauge): two shots 0x191,
                                        // at frames 4 and 8
        k41236A = 0xfd,                 // 41236A (parsed as 4,1,3 + button): running grab
                                        // (vx 1.8)
        k41236B = 0xfe,                 // 41236B: as 0xfd, one more loop
        k41236C = 0xff,                 // 41236C (costs as 0xfc): vx 2.9, 1350 damage
        k214Parry = 0x100,              // 214A/B/C: a parry stance
        kUnusedGuardCounter = 0x101,    // unreached: same as 0x102 one frame later, without
                                        // its 0x1a5
        kGuardCounter = 0x102,          // A/B/C while guarding the attack last parried
                                        // (m_patternVar1 1, set when the guard starts):
                                        // rising counter (vx 2, vy -3), 3 hits, object
                                        // 0x1a5
        kAir412A = 0x103,               // air 412A (4,1,2 + button, only in the air): dives
                                        // (vx 1.3, vy 1.3) with 0x193/0x194
        kAir412B = 0x104,               // air 412B: vx 1.5, 2 hits
        kAir412C = 0x105,               // air 412C (costs as 0xfc): vx 1.7, 2 hits, 5 extra
                                        // loops
        k623A = 0x106,                  // 623A: dash (vx 4.0)
        k623B = 0x107,                  // 623B: hop (vx 1.0, vy -1.5), hits at frames 4 and
                                        // 8
        k623C = 0x108,                  // 623C (costs as 0xfc): 0x107 followed by 0x106's
                                        // dash
        kAir236A = 0x109,               // air 236A: shot 0x192 and a hop back (vx -0.5, vy
                                        // -1.4)
        kAir236B = 0x10a,               // air 236B: shot 0x1a3
        kAir236C = 0x10b,               // air 236C: shot 0x1a4
        kAir412BRebound = 0x10c,        // air 412B guarded: bounces back (vx -0.6, vy -1.4)
        k214ParryCounter = 0x12b,       // the parry's counter: freezes the screen 160
                                        // frames, 600 damage
        k21436Lv1 = 0x12c,              // 21436 with 1 level: the 41236 carry as a super
                                        // (vx 2.5), 2250 damage at the wall, object 0x195
        k21436Lv2 = 0x12d,              // 2 levels: vx 3.0
        k21436Lv3 = 0x12e,              // 3 levels: vx 3.5
        k236236Lv1 = 0x132,             // 236236 with 1 level: summons shooters 0x198,
                                        // 0x19b that fire 0x197
        k236236Lv2 = 0x133,             // 2 levels: adds shooters 0x199, 0x19c
        k236236Lv3 = 0x134,             // 3 levels: adds shooters 0x19a, 0x19d
        k6321463214Lv1 = 0x135,         // 63214 63214 (parsed 6,3,1,4,6,3,1,4 + button,
                                        // 135-frame window) with 1 level: grab of a
                                        // grounded opponent at frame 5, sky strikes 0x1a0
                                        // around
        k6321463214Lv1Hold = 0x136,     // holds the opponent overhead while 0x1a0 strikes
                                        // fall (random x, CPlayer::Random), 1350 damage
        k6321463214Lv2 = 0x137,         // 2 levels: to 0x138
        k6321463214Lv2Hold = 0x138,     // more strikes, 2450 damage
        k6321463214Lv3 = 0x139,         // 3 levels: to 0x13a
        k6321463214Lv3Hold = 0x13a,     // more strikes, 3450 damage
        kLv4Drop = 0x13b,               // 2, A, 2, D (neutral between
        kLv4DropHit = 0x13c,            // sits on the opponent: many 100-damage stomps at
                                        // proration 998, objects 0x19f
        kObjGuardEffect = 0x190,        // object: spawned once by her guard states
                                        // (0x96-0x9b, 0xa8, 0xa9, m_guardEffectOut)
        kObj236Shot = 0x191,            // object: ground 236 shot: accelerates to 2
                                        // px/frame
        kObjAir236AShot = 0x192,        // object: air 236A shot, as 0x191
        kObjAir412Start = 0x193,        // object: follows her during the first frames of
                                        // 0x103-0x105
        kObjAir412Trail = 0x194,        // object: follows her during the dive of
                                        // 0x103-0x105 until she lands
        kObj21436Slam = 0x195,          // object: played once at the wall slam of
                                        // 0x12c-0x12e
        kObj236236Hit = 0x196,          // object: 1-hit object 114 px ahead at frame 17 of
                                        // each 0x132-0x134 loop
        kObjShooterShot = 0x197,        // object: the shot the shooters 0x198-0x19d fire
        kObjShooterLv1A = 0x198,        // object: shooter 80 px ahead (236236 any level):
                                        // fires 0x197 until the super ends
        kObjShooterLv2A = 0x199,        // object: shooter 10 px behind (level 2 and 3)
        kObjShooterLv3A = 0x19a,        // object: shooter 55 px ahead (level 3)
        kObjShooterLv1B = 0x19b,        // object: shooter 100 px ahead (any level)
        kObjShooterLv2B = 0x19c,        // object: shooter 40 px behind (level 2 and 3)
        kObjShooterLv3B = 0x19d,        // object: shooter 70 px behind (level 3)
        kObjLv4Appear = 0x19e,          // object: where she appears above the opponent at
                                        // 0x13b frame 10
        kObjLv4Stomp = 0x19f,           // object: the stomps of 0x13c
        kObjSkyStrike = 0x1a0,          // object: spawned 240 px up by 0x135-0x13a: 1 hit,
                                        // at frame 3 spawns its lower part 0x1a1 160 px
                                        // below
        kObjSkyStrikeLow = 0x1a1,       // object: the lower part of 0x1a0
        kObjAir236BShot = 0x1a3,        // object: air 236B shot: as 0x191, curving down
        kObjAir236CShot = 0x1a4,        // object: air 236C shot: curving down more
        kObjGuardCounterEffect = 0x1a5, // object: kept at her feet while 0x102 runs
        kObjAirThrowEffect = 0x1a6,     // object: from 0xf9, removed once she passes frame
                                        // 1
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CSayuri's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,      // 412 + A, within 45 frames
        kCmd412B = 0x29,      // 412 + B, within 45 frames
        kCmd412C = 0x2a,      // 412 + C, within 45 frames
        kCmd412D = 0x2b,      // 412 + D, within 45 frames
        kCmd41236A = 0x46,    // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,    // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,    // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,    // 41236 + D (read as 413), within 60 frames
        kCmd25A25D = 0x62,    // 2 5 A 2 5 D, within 90 frames
        kCmd214214A = 0x64,   // 214214 + A, within 90 frames
        kCmd214214B = 0x65,   // 214214 + B, within 90 frames
        kCmd214214C = 0x66,   // 214214 + C, within 90 frames
        kCmd214214D = 0x67,   // 214214 + D, within 90 frames
        kCmd236236A = 0x6e,   // 236236 + A, within 90 frames
        kCmd236236B = 0x6f,   // 236236 + B, within 90 frames
        kCmd236236C = 0x70,   // 236236 + C, within 90 frames
        kCmd236236D = 0x71,   // 236236 + D, within 90 frames
        kCmd63146314A = 0xa0, // 63146314 + A, within 135 frames
        kCmd63146314B = 0xa1, // 63146314 + B, within 135 frames
        kCmd63146314C = 0xa2, // 63146314 + C, within 135 frames
        kCmd63146314D = 0xa3, // 63146314 + D, within 135 frames
        kCmd21436A = 0xaa,    // 21436 + A, within 90 frames
        kCmd21436B = 0xab,    // 21436 + B, within 90 frames
        kCmd21436C = 0xac,    // 21436 + C, within 90 frames
        kCmd21436D = 0xad,    // 21436 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x434060
    virtual void UpdatePattern();
    // FUNCTION: 0x4463e0
    CSayuri(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x446590
    virtual void Reset();
    // FUNCTION: 0x4466d0
    virtual void StartPattern();
    // FUNCTION: 0x446710
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x446760
    virtual void Move();
    // FUNCTION: 0x446780
    virtual void StartCommand();
    // FUNCTION: 0x4492f0
    virtual void DrawGauge();
    // FUNCTION: 0x449300
    virtual void PreUpdate();
    // FUNCTION: 0x449390
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4493c0
    virtual void ReadCommand();
    // FUNCTION: 0x44ab30
    virtual void CpuInput();
    // FUNCTION: 0x44db60
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern; in the
                       // guard states 1 when guarding the parried attack (guard counter
                       // allowed)
    int m_patternVar2; // Scratch for the current pattern, zeroed by StartPattern (frame
                       // and loop counts)
    int m_patternVar3; // Scratch for the current pattern, zeroed by StartPattern
    int m_bounceDebrisOut; // 1 while the debris object 0x1f0 from the shared knock-back
                           // states is out
    int m_guardEffectOut; // 1 while her guard object 0x190 is out
    int m_shotsOut; // Her 236 shots on screen (0x191, 0x192, 0x1a3, 0x1a4); 236 starts
                    // only at 0
    int m_parriedPattern; // The opponent's pattern her 214 parry last caught, 999 for
                          // none; guarding it again allows the guard counter 0x102
    int m_objectVar1[0x40]; // Per-object scratch (index as m_objects), zeroed by
                            // RemoveObject: phase counts, "initialised" flags
    int m_objectVar2[0x40]; // Per-object scratch, zeroed by RemoveObject: debris lifetime
    int m_objectVar3[0x40]; // Per-object scratch, zeroed by RemoveObject; unused
    BYTE unk3454[0x3458 - 0x3454];
};

// Nayuki: one of the character classes.
// SIZE: 0x3460
class CNayuki : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CNayuki's own actions
    enum {
        k5A = 0xc8,
        k5BClose = 0xc9,              // nayuki.cpp B within 80 px
        k5BFar = 0xca,                // nayuki.cpp B otherwise (also 2B -> B at warm-up >=
                                      // 2)
        k5C = 0xcb,                   // nayuki.cpp
        k2A = 0xcc,
        k2B = 0xcd,                   // nayuki.cpp (not from 5B close unless warm-up >= 1)
        k2C = 0xce,
        kJumpA = 0xcf,
        kJumpB = 0xd0,                // nayuki.cpp
        kJumpC = 0xd1,                // nayuki.cpp
        k6B = 0xd2,                   // nayuki.cpp B + forward at warm-up >= 2
        kUnusedD3 = 0xd3,             // UpdatePattern never entered (no frames in
                                      // nayuki.pat)
        kUnusedAirDive = 0xd4,        // UpdatePattern never entered: dive, to 0x101 on hit
        kUnusedD5 = 0xd5,             // UpdatePattern never entered: falling attack, lands
                                      // to 0x61
        k5BFarC = 0xd6,               // nayuki.cpp C during 5B far's hop at warm-up >= 5
        kThrow = 0xdc,                // nayuki.cpp C + direction within 30 px of a grounded
                                      // opponent
        kThrowHit = 0xdd,             // UpdatePattern 1000 damage, opponent to 0x3f
        kDashJumpA = 0xe6,            // nayuki.cpp A during the forward dash (0xa3 is a
                                      // hop)
        kDashJumpB = 0xe7,
        kDashJumpC = 0xe8,            // nayuki.cpp/375
        kAirThrow = 0xf8,             // nayuki.cpp 6C in the air within 100 px of an
                                      // airborne opponent
        kAirThrowHit = 0xf9,          // UpdatePattern 1300 damage, opponent to 0x3f
        k236A = 0xfa,                 // nayuki.cpp
        k236B = 0xfb,                 // nayuki.cpp (0x0b, or 0x0c without EX)
        k236C = 0xfc,                 // nayuki.cpp EX
        kUnusedFd = 0xfd,             // UpdatePattern never entered: leap, then 0x100/0x102
        kUnusedFe = 0xfe,             // UpdatePattern never entered: leap with
                                      // kObjUnused194, then 0x102
        kUnused100 = 0x100,           // UpdatePattern only from 0xfd: dash at 2.4 that
                                      // bounces off (0x101) on contact
        kRebound = 0x101,             // UpdatePattern airborne recoil after a dash connects
                                      // (0x132, unused 0x100/0xd4), ends in 9
        kUnused102 = 0x102,           // UpdatePattern only from 0xfd/0xfe: falling attack
        k5D = 0x103,                  // nayuki.cpp D on the ground below warm-up 9
        k623A = 0x104,                // nayuki.cpp warm-up >= 2
        k623B = 0x105,                // nayuki.cpp (0x15, or 0x16 without EX)
        k623C = 0x106,                // nayuki.cpp EX
        kUnused107 = 0x107,           // UpdatePattern never entered: rising multi-hit
                                      // (warm-up + 6 hits)
        k41236A = 0x108,              // nayuki.cpp warm-up >= 1
        k41236B = 0x109,              // nayuki.cpp (0x47, or 0x48 without EX)
        k41236C = 0x10a,              // nayuki.cpp EX
        kUnused10b = 0x10b,           // UpdatePattern never entered: rush at 2.8, 99 hits
        k214Stance = 0x10c,           // nayuki.cpp 0x1e-0x20 (also from 41236A/B)
        kStanceAWarm = 0x10d,         // UpdatePattern A from the stance at warm-up >= 5:
                                      // jumping hit, lands with a shake (= 0x113)
        kUnused10e = 0x10e,           // UpdatePattern never entered: copy of 0x114
        kStanceD = 0x10f,             // UpdatePattern D from the stance (or from a step):
                                      // warm-up +1 on frame 5
        kUnused110 = 0x110,           // UpdatePattern never entered: copy of 0x115
        kUnused111 = 0x111,           // UpdatePattern never entered: copy of 0x116
        kStanceB = 0x112,             // UpdatePattern B from the stance: throws kObjStanceB
                                      // (4B kObjStanceBBack, 6B kObjStanceBForward)
        kStanceA = 0x113,             // UpdatePattern A from the stance below warm-up 5
        kStanceC = 0x114,             // UpdatePattern C from the stance: lunges 40 px a
                                      // frame on frames 3-5, hops
        kStance6D = 0x115,            // UpdatePattern 6D in the stance: steps forward
                                      // (1.4), buttons cancel it, returns to the stance's
                                      // frame 8
        kStance4D = 0x116,            // UpdatePattern 4D in the stance: steps back
        k236D = 0x117,                // nayuki.cpp 0x0d
        k2D = 0x118,                  // nayuki.cpp D + down, and 2D in the stance
        kStance2C = 0x119,            // UpdatePattern 2C from the stance
        k236236A = 0x12c,             // nayuki.cpp level 1
        k236236B = 0x12d,             // nayuki.cpp level 2
        k236236C = 0x12e,             // nayuki.cpp level 3
        k214214A = 0x12f,             // nayuki.cpp level 1
        k214214B = 0x130,             // nayuki.cpp level 2
        k214214C = 0x131,             // nayuki.cpp level 3
        kLv4 = 0x132,                 // nayuki.cpp 0x61 (C then 236236) with HP below 3333
                                      // and level 3
        kObjAirDashStep = 0x190,      // nayuki.cpp air dash 0xa5/0xa6: on its frame 5 sets
                                      // m_patternVar1 to 1, which starts the dash
        kObj236A = 0x191,             // nayuki.cpp tossed in front, lands
        kObj236B = 0x192,             // nayuki.cpp kicked by 0xfb (2.0, -3.5)
        kObj236C = 0x193,             // nayuki.cpp kicked by 0xfc (2.2, -1.6), 5 hits
        kObjUnused194 = 0x194,        // nayuki.cpp only from the unused 0xfe
        kObj214214EmitterEnd = 0x195, // nayuki.cpp an emitter's last form when 214214 ends,
                                      // plays once
        kObj236236ABomb = 0x196,      // nayuki.cpp tossed, explodes into kObjExplosion1 on
                                      // its frame 5
        kObj236236BBomb = 0x197,      // nayuki.cpp two kObjExplosion2 40 px either side
        kObj236236CBomb = 0x198,      // nayuki.cpp three kObjExplosion3
        kObjExplosion1 = 0x199,       // nayuki.cpp 1 hit
        kObjExplosion2 = 0x19a,       // nayuki.cpp same, 12%
        kObjExplosion3 = 0x19b,       // nayuki.cpp same, 10%
        kObjExplosionSpark = 0x19c,   // nayuki.cpp effect 0x22 every 2 frames
        kObj214214Upper = 0x19d,      // nayuki.cpp follows her 80 px up
                                      // (m_upperEmitterX/Y), spawns kObj214214UpperHit
                                      // every 3/2/1 loops
        kObj214214Lower = 0x19e,      // nayuki.cpp at her feet (m_lowerEmitterX/Y), spawns
                                      // kObj214214LowerHit
        kObj214214UpperHit = 0x19f,   // nayuki.cpp 320x111, 1 hit, kept at the upper
                                      // emitter
        kObj214214LowerHit = 0x1a0,   // nayuki.cpp kept at the lower emitter
        kObjLv4Shed = 0x1a1,          // nayuki.cpp flies off backward (-1.9, -2.5) when the
                                      // LV4's charge ends
        kObjStanceBBack = 0x1ab,      // nayuki.cpp thrown in an arc (0.3, -3.5), bounces
                                      // off on contact
        kObjStanceB = 0x1ac,          // nayuki.cpp (0.8, -3.5)
        kObjStanceBForward = 0x1ad,   // nayuki.cpp (1.3, -3.5)
        kObjState7b = 0x1ae,          // nayuki.cpp lives only in the shared state 0x7b's
                                      // first frames
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CNayuki's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 60 frames
        kCmdC236236 = 0x61, // C 2 3 6 2 3 6, within 90 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x451850
    virtual void UpdatePattern();
    // FUNCTION: 0x461090
    CNayuki(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x461260
    virtual void Reset();
    // FUNCTION: 0x4613b0
    virtual void StartPattern();
    // FUNCTION: 0x4613f0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x461440
    virtual void Move();
    // FUNCTION: 0x461460
    virtual void StartCommand();
    // FUNCTION: 0x463dd0
    virtual void DrawGauge();
    // FUNCTION: 0x464180
    virtual void PreUpdate();
    // FUNCTION: 0x464190
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4641c0
    virtual void ReadCommand();
    // FUNCTION: 0x4654a0
    virtual void CpuInput();
    // FUNCTION: 0x468870
    virtual void UpdateObjects();

    int m_patternVar1; // scratch of the current pattern, zeroed by StartPattern;
                       // kObjAirDashStep sets it 1 to start an air dash's motion
    int m_patternVar2; // the same: a second counter of the current pattern
    int m_patternVar3; // the same: shared states only
    int m_encasedBreakOut; // 1 while the kObjBurst that states 0x53-0x56 spawn is alive
    int m_warmUp; // 0-9, 3 each round: 5D and the stance's D add 1, getting up (0x60)
                  // takes 1; speeds up her moves, adds hits and air dashes, unlocks
                  // moves; DrawGauge shows it
    int m_upperEmitterX; // 214214: x of kObj214214Upper, where its kObj214214UpperHit are
                         // kept
    int m_lowerEmitterX; // 214214: x of kObj214214Lower, where its kObj214214LowerHit are
                         // kept
    int m_upperEmitterY; // 214214: y of kObj214214Upper
    int m_lowerEmitterY; // 214214: y of kObj214214Lower
    int m_objectVar1[0x40]; // per object, zeroed by RemoveObject: timers and once-flags
    int m_objectVar2[0x40]; // per object, zeroed by RemoveObject: the debris lifetimes
    int m_objectVar3[0x40]; // per object, zeroed by RemoveObject; never otherwise used
    BYTE unk345c[0x3460 - 0x345c];
};

// Mizukab: one of the character classes.
// SIZE: 0x3460
class CMizukaB : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMizukaB's own actions
    enum {
        k5A = 0xc8,                    // mizukab.cpp
        k5BClose = 0xc9,               // mizukab.cpp within 70 px
        k5BFar = 0xca,
        k5C = 0xcb,                    // mizukab.cpp
        k2A = 0xcc,
        k2B = 0xcd,
        k2C = 0xce,                    // mizukab.cpp
        kJumpA = 0xcf,
        kJumpB = 0xd0,
        kJumpC = 0xd1,
        kJump6C = 0xd2,
        kUnusedD3 = 0xd3,              // UpdatePattern never entered (as in CMizuka)
        kUnusedAirDive = 0xd4,         // UpdatePattern never entered
        kUnusedAirDiveRebound = 0xd5,  // UpdatePattern only from 0xd4
        kUnusedAirDiveLanding = 0xd6,  // UpdatePattern only from 0xd4
        kThrow = 0xdc,
        kThrowHit = 0xdd,              // UpdatePattern the three-helper throw (carrier
                                       // deals 800 here)
        kDashA = 0xe6,                 // mizukab.cpp A in the forward dash
        kDashB = 0xe7,
        kDashC = 0xe8,
        kDash2A = 0xe9,                // mizukab.cpp down+A in the forward dash
        kDash2B = 0xea,                // mizukab.cpp
        kDash2C = 0xeb,                // mizukab.cpp
        kAirThrow = 0xf8,              // mizukab.cpp 6C in the air within 100 px of an
                                       // airborne opponent
        kAirThrowHit = 0xf9,           // UpdatePattern 1000 damage, opponent to 0x3c
        k236A = 0xfa,                  // mizukab.cpp
        k236B = 0xfb,                  // mizukab.cpp
        k236C = 0xfc,                  // mizukab.cpp EX
        k214A = 0xfd,                  // mizukab.cpp
        k214B = 0xfe,                  // mizukab.cpp
        k214C = 0xff,                  // mizukab.cpp EX
        k41236A = 0x100,               // mizukab.cpp
        k41236B = 0x101,
        k41236C = 0x102,
        k623A = 0x103,                 // mizukab.cpp 0x14
        k623B = 0x104,                 // mizukab.cpp 0x15, or 0x16 without EX
        k623C = 0x105,                 // mizukab.cpp 0x16 EX
        kAir236A = 0x106,              // mizukab.cpp
        kAir236B = 0x107,              // mizukab.cpp
        kAir236C = 0x108,              // mizukab.cpp EX
        kUnusedAir214 = 0x109,         // UpdatePattern never entered in CMizukaB (its air
                                       // 214 line became 623A)
        k421A = 0x10a,                 // mizukab.cpp 0x50 on the ground
        k421B = 0x10b,                 // mizukab.cpp 0x51
        k421C = 0x10c,                 // mizukab.cpp 0x52
        kAir421A = 0x10d,              // mizukab.cpp 0x50 in the air, once a jump
        kAir421B = 0x10e,
        kAir421C = 0x10f,              // mizukab.cpp
        k236236A = 0x12c,              // mizukab.cpp 0x64 on the ground, level 1
        k236236B = 0x12d,              // mizukab.cpp 0x65 on the ground, level 1 (costs
                                       // 1000)
        kUnused12e = 0x12e,            // UpdatePattern never entered (0x66 on the ground
                                       // starts nothing)
        k463214A = 0x12f,              // mizukab.cpp 0x82-0x84 at level 1
        k463214B = 0x130,              // mizukab.cpp 0x83/0x84 at level 2
        k463214C = 0x131,              // mizukab.cpp 0x84 at level 3
        k463214AHit = 0x132,           // UpdatePattern = CMizuka's 0x132
        k463214BHit = 0x133,
        k463214CHit = 0x134,
        kUnused135 = 0x135,            // UpdatePattern never entered (as in CMizuka)
        kUnused136 = 0x136,            // UpdatePattern never entered
        kUnused137 = 0x137,            // UpdatePattern never entered
        kUnused138 = 0x138,            // UpdatePattern never entered (no 0x139 path here)
        kUnused139 = 0x139,            // UpdatePattern never entered: costs 3000, restores
                                       // 10 HP a frame on frames 22-24 until full
        kLv4 = 0x13a,                  // mizukab.cpp 0x5a (C,5,B,6,A,5,A) with HP <= 3333
                                       // and level 3
        kLv4Hit = 0x13b,               // UpdatePattern = CMizuka's 214214CHit cinematic
        kUnused13c = 0x13c,            // UpdatePattern never entered in CMizukaB (CMizuka's
                                       // 463214C)
        kAir236236A = 0x13d,           // mizukab.cpp 0x64 in the air, level 1
        kAir236236B = 0x13e,           // mizukab.cpp 0x65/0x66 in the air, level 2
        kAir236236C = 0x13f,           // mizukab.cpp 0x66 in the air, level 3
        kObj5BCloseEffect = 0x190,     // mizukab.cpp as CMizuka
        kObj5BFarEffect = 0x191,
        kObj2BEffect = 0x192,
        kObjUnused193 = 0x193,         // mizukab.cpp only from the unused 0x136/0x137
        kObjJumpBEffect = 0x194,
        kObjJumpCEffect = 0x195,
        kObj214 = 0x196,
        kObj214CChain1 = 0x198,
        kObj214CChain2 = 0x199,
        kObj214CChain3 = 0x19a,
        kObjWalker1 = 0x19b,           // mizukab.cpp spawned by the walker sources, Random
                                       // speed
        kObjWalker2 = 0x19c,
        kObjWalker3 = 0x19d,
        kObjWalker4 = 0x19e,
        kObjWalker5 = 0x19f,
        kObjWalker6 = 0x1a0,
        kObj236A = 0x1a1,              // mizukab.cpp stops on its frame 3, 5 hits in place
        kObj236B = 0x1a2,              // mizukab.cpp same, launched at 3.5
        kObj236C = 0x1a3,              // mizukab.cpp one slow accelerating orb that holds
                                       // the opponent like CMizuka's
        kObj236Launched = 0x1a4,       // mizukab.cpp the launched form of kObj236A/B
                                       // (pattern switched in place)
        kObjRiser1 = 0x1a5,            // mizukab.cpp LV4 cinematic
        kObjRiser2 = 0x1a6,
        kObjRiser3 = 0x1a7,
        kObjRiser4 = 0x1a8,
        kObjRiser5 = 0x1a9,
        kObjRiser6 = 0x1aa,
        kObjSweeper1 = 0x1ac,
        kObjSweeper2 = 0x1ad,
        kObjSweeper3 = 0x1ae,
        kObjSweeper4 = 0x1af,
        kObjSweeper5 = 0x1b0,
        kObjFinaleBackdrop = 0x1b2,
        kObj623Effect = 0x1b5,
        kObjGrabber = 0x1b6,
        kObjCatchProp = 0x1b7,
        kObjCatcher = 0x1b8,
        kObj5AEffect = 0x1b9,
        kObj2AEffect = 0x1ba,
        kObjJumpAEffect = 0x1bb,
        kObj41236Flat1 = 0x1bc,
        kObj41236Flat2 = 0x1bd,
        kObj41236Flat3 = 0x1be,
        kObj41236Flat4 = 0x1bf,
        kObj41236Up35 = 0x1c0,
        kObj41236Up60 = 0x1c1,
        kObj41236Up60b = 0x1c2,
        kObj41236Up85 = 0x1c3,
        kObj463214C = 0x1c4,           // mizukab.cpp only spawned by the unused 0x13c here
        kObjCatchThrow3 = 0x1c5,
        kObjCatchThrow1 = 0x1c6,
        kObjCatchThrow2 = 0x1c7,
        kObjThrowHelperBack = 0x1c8,
        kObjThrowCarrier = 0x1c9,      // mizukab.cpp 800 damage (CMizuka 1200), opponent's
                                       // m_untechTime 120
        kObjThrowHelperFront = 0x1ca,
        kObjAir214 = 0x1cb,            // mizukab.cpp only spawned by the unused 0x109 here
        kObjJump6CEffect = 0x1cc,
        kObjWalkerSourceFront = 0x1cd, // mizukab.cpp invisible emitter: 14 walkers from
                                       // beyond the screen edge she faces, walking at her
        kObjWalkerSourceBack = 0x1ce,  // mizukab.cpp 14 walkers from the edge behind her
        kObjWalkerSourceNear = 0x1cf,  // mizukab.cpp 36 walkers from 340 px behind her
                                       // (CMizuka's way)
        kObjAir236236A = 0x1d0,        // mizukab.cpp held in her hands frame by frame,
                                       // thrown down (2, 2) with 5 hits and a trail,
                                       // becomes kObjAir236236AImpact on landing
        kObjAir236236AImpact = 0x1d1,  // mizukab.cpp one hit, voice 4
        kObjAir236236B = 0x1d2,        // mizukab.cpp as kObjAir236236A for 0x13e
        kObjAir236236BImpact = 0x1d3,  // mizukab.cpp one hit (305x480)
        kObjAir236236Trail = 0x1d4,    // mizukab.cpp plays once, left where the thrown
                                       // object starts its fall
        kObjAir236236C = 0x1d5,        // mizukab.cpp as kObjAir236236A for 0x13f
        kObjAir236236CImpact = 0x1d6,  // mizukab.cpp one hit
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMizukaB's own commands (ReadCommand)
    enum {
        kCmd66A = 0x3c,     // 66 + A, within 55 frames
        kCmd66B = 0x3d,     // 66 + B, within 55 frames
        kCmd66C = 0x3e,     // 66 + C, within 55 frames
        kCmd66D = 0x3f,     // 66 + D, within 55 frames
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 60 frames
        kCmd421A = 0x50,    // 421 + A, within 60 frames
        kCmd421B = 0x51,    // 421 + B, within 60 frames
        kCmd421C = 0x52,    // 421 + C, within 60 frames
        kCmd421D = 0x53,    // 421 + D, within 60 frames
        kCmdC5B6A5A = 0x5a, // C 5 B 6 A 5 A, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd4631A = 0x82,   // 4631 + A, within 75 frames
        kCmd4631B = 0x83,   // 4631 + B, within 75 frames
        kCmd4631C = 0x84,   // 4631 + C, within 75 frames
        kCmd4631D = 0x85,   // 4631 + D, within 75 frames
    };
    // END constants

    // FUNCTION: 0x4c04b0
    virtual void UpdatePattern();
    // FUNCTION: 0x4d2850
    CMizukaB(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x4d29e0
    virtual void Reset();
    // FUNCTION: 0x4d2b00
    virtual void StartPattern();
    // FUNCTION: 0x4d2b40
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x4d2b90
    virtual void Move();
    // FUNCTION: 0x4d2bb0
    virtual void StartCommand();
    // FUNCTION: 0x4d59d0
    virtual void DrawGauge();
    // FUNCTION: 0x4d59e0
    virtual void PreUpdate();
    // FUNCTION: 0x4d5aa0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4d5ad0
    virtual void ReadCommand();
    // FUNCTION: 0x4d6f50
    virtual void CpuInput();
    // FUNCTION: 0x4db160
    virtual void UpdateObjects();

    int m_patternVar1; // scratch of the current pattern, zeroed by StartPattern (as
                       // CMizuka's)
    int m_patternVar2; // the same; also the spacing of the 236236 walker sources (read by
                       // the objects)
    int m_patternVar3; // the same (as CMizuka's)
    int m_encasedBreakOut; // 1 while the kObjBurst that states 0x53-0x56 spawn is alive
    int m_objectVar1[0x40]; // per object, zeroed by RemoveObject: each object type's own
                            // counter or flag
    int m_objectVar2[0x40]; // per object, zeroed by RemoveObject
    int m_objectVar3[0x40]; // per object, zeroed by RemoveObject
    int m_catchState; // 463214 super: 0 none, 1 caught, 2 cinematic running, 3 a roll
                      // failed, 4 a roll won, 5 finished (CMizuka's code)
    int m_throwArrived; // 1 when a kObjCatchThrow* reaches the caught opponent;
                        // kObjCatcher clears it
    int m_throwHelperFacing; // the facing kObjThrowCarrier hands to the two throw helpers
    int m_homingOrbHit; // only ever cleared here: CMizuka's 236C flag, unused by
                        // CMizukaB's single 236C orb
    int m_flying; // 1 during D's flight, 0 otherwise; the time is paid from m_rfGauge
                  // instead (Vf8, 1 a frame)
    int m_flightDrainTimer; // Vf8's counter while flying: +1 then, being > 0, takes 1
                            // from m_rfGauge and resets, every frame
};

// Mizuka: one of the character classes.
// SIZE: 0x3460
class CMizuka : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMizuka's own actions
    enum {
        k5A = 0xc8,                   // mizuka.cpp A standing
        k5BClose = 0xc9,              // mizuka.cpp B within 70 px of the opponent
        k5BFar = 0xca,                // mizuka.cpp B otherwise
        k5C = 0xcb,                   // mizuka.cpp C standing
        k2A = 0xcc,                   // mizuka.cpp
        k2B = 0xcd,                   // mizuka.cpp
        k2C = 0xce,                   // mizuka.cpp
        kJumpA = 0xcf,                // mizuka.cpp
        kJumpB = 0xd0,                // mizuka.cpp
        kJumpC = 0xd1,                // mizuka.cpp
        kJump6C = 0xd2,               // mizuka.cpp C in the air holding forward
        kUnusedD3 = 0xd3,             // UpdatePattern never entered: a ground normal
                                      // hitting on frame 3
        kUnusedAirDive = 0xd4,        // UpdatePattern never entered: falling air attack, to
                                      // 0xd5 on hit, 0xd6 on landing
        kUnusedAirDiveRebound = 0xd5, // UpdatePattern only from 0xd4: bounces back (vx -1,
                                      // vy -2.4)
        kUnusedAirDiveLanding = 0xd6, // UpdatePattern only from 0xd4: landing with screen
                                      // shake
        kThrow = 0xdc,                // mizuka.cpp C + forward/back within 40 px, opponent
                                      // not in hitstun
        kThrowHit = 0xdd,             // UpdatePattern throws the opponent up (0x3b), spawns
                                      // kObjThrowHelperBack/Carrier/Front
        kDashA = 0xe6,                // mizuka.cpp A during the forward dash 0xa3
        kDashB = 0xe7,
        kDashC = 0xe8,
        kUnusedF9 = 0xf9,             // UpdatePattern never entered (sets unkdc 4, unkde
                                      // -20, m_freezeTime 60, effect 0x28)
        k236A = 0xfa,                 // mizuka.cpp 0x0a on the ground
        k236B = 0xfb,                 // mizuka.cpp 0x0b, or 0x0c without EX
        k236C = 0xfc,                 // mizuka.cpp 0x0c EX
        k214A = 0xfd,                 // mizuka.cpp 0x1e
        k214B = 0xfe,                 // mizuka.cpp 0x1f, or 0x20 without EX
        k214C = 0xff,                 // mizuka.cpp 0x20 EX
        k41236A = 0x100,              // mizuka.cpp 0x46
        k41236B = 0x101,              // mizuka.cpp 0x47
        k41236C = 0x102,              // mizuka.cpp 0x48 (no EX needed)
        k623 = 0x103,                 // mizuka.cpp 0x14-0x16 (0x16 without EX)
        kUnused104 = 0x104,           // UpdatePattern never entered in CMizuka (copy of
                                      // 0x103
        k623C = 0x105,                // mizuka.cpp 0x16 EX
        kAir236A = 0x106,             // mizuka.cpp 0x0a in the air
        kAir236B = 0x107,             // mizuka.cpp
        kAir236C = 0x108,             // mizuka.cpp EX
        kAir214 = 0x109,              // mizuka.cpp 0x1e-0x20 in the air
        k236236A = 0x12c,             // mizuka.cpp 0x64-0x66 at level 1
        k236236B = 0x12d,             // mizuka.cpp 0x65/0x66 at level 2
        k236236C = 0x12e,             // mizuka.cpp 0x66 at level 3 (tests 0x12c's priority,
                                      // a copy slip)
        k641236A = 0x12f,             // mizuka.cpp 0x78-0x7a at level 1
        k641236B = 0x130,             // mizuka.cpp 0x79/0x7a at level 2
        k641236C = 0x131,             // mizuka.cpp 0x7a at level 3
        k641236AHit = 0x132,          // UpdatePattern cinematic (Mizuka x 230, opponent 420
                                      // in the catcher), throws kObjCatchThrow1, one roll
        k641236BHit = 0x133,          // UpdatePattern two throws (kObjCatchThrow1, 2),
                                      // kObjCatchProp beside her
        k641236CHit = 0x134,          // UpdatePattern three throws (kObjCatchThrow1-3)
        kUnused135 = 0x135,           // UpdatePattern never entered: holds the opponent
                                      // (0x67), 4x300 damage, leaps and slams for 800
        kUnused136 = 0x136,           // UpdatePattern never entered: costs 3000, holds the
                                      // opponent, 3500 damage after 11 rounds
        kUnused137 = 0x137,           // UpdatePattern never entered: same shape, 1000
                                      // damage after 9 rounds
        kUnused138 = 0x138,           // UpdatePattern only from 0x139: hits on frame 2,
                                      // freezes the opponent 500 frames
        kUnused139 = 0x139,           // UpdatePattern never entered: waits, restarts on a
                                      // clash, then 0x138 (its 3000 cost sits in a dead
                                      // branch)
        k214214C = 0x13a,             // mizuka.cpp 0x70 at level 3
        k214214CHit = 0x13b,          // UpdatePattern cinematic at x 320: kObjRiser1-6,
                                      // flash, kObjGrabber (5900 damage) and kObjSweeper1-5
        k463214C = 0x13c,             // mizuka.cpp 0x84 at level 3
        kObj5BCloseEffect = 0x190,    // mizuka.cpp plays once (no attack box in mizuka.pat)
        kObj5BFarEffect = 0x191,      // mizuka.cpp plays once
        kObj2BEffect = 0x192,         // mizuka.cpp plays once
        kObjUnused193 = 0x193,        // mizuka.cpp plays once
        kObjJumpBEffect = 0x194,      // mizuka.cpp follows her, removed when she leaves
                                      // 0xd0
        kObjJumpCEffect = 0x195,      // mizuka.cpp follows her, loops while 0xd1 is before
                                      // frame 8
        kObj214 = 0x196,              // mizuka.cpp ground object, 1 hit, attack box on its
                                      // frame 8 (107x133)
        kObj214CChain1 = 0x198,       // mizuka.cpp like kObj214
        kObj214CChain2 = 0x199,       // mizuka.cpp spawns kObj214CChain3
        kObj214CChain3 = 0x19a,       // mizuka.cpp spawns kObj214CChain1 (the chain runs to
                                      // the screen edge)
        kObjWalker1 = 0x19b,          // mizuka.cpp walks forward at 0.7-0.9 (Random), 1
                                      // hit, removed off screen
        kObjWalker2 = 0x19c,          // mizuka.cpp same
        kObjWalker3 = 0x19d,          // mizuka.cpp same
        kObjWalker4 = 0x19e,          // mizuka.cpp same
        kObjWalker5 = 0x19f,          // mizuka.cpp same
        kObjWalker6 = 0x1a0,          // mizuka.cpp same
        kObj236A = 0x1a1,             // mizuka.cpp orb at 0.5 px/frame
        kObj236B = 0x1a2,             // mizuka.cpp same, rising (0.35, -0.35)
        kObj236CHoming = 0x1a3,       // mizuka.cpp same, homes on the opponent (AngleTo),
                                      // accelerates
        kObjAir236B = 0x1a4,          // mizuka.cpp same, descending (0.35, 0.35)
        kObjRiser1 = 0x1a5,           // mizuka.cpp 214214C cinematic: drifts up (vy -1.1,
                                      // vx 0.3)
        kObjRiser2 = 0x1a6,           // mizuka.cpp same
        kObjRiser3 = 0x1a7,           // mizuka.cpp same
        kObjRiser4 = 0x1a8,           // mizuka.cpp same
        kObjRiser5 = 0x1a9,           // mizuka.cpp same
        kObjRiser6 = 0x1aa,           // mizuka.cpp same
        kObjSweeper1 = 0x1ac,         // mizuka.cpp crosses the screen (2.5, 0.5)
        kObjSweeper2 = 0x1ad,         // mizuka.cpp same
        kObjSweeper3 = 0x1ae,         // mizuka.cpp same
        kObjSweeper4 = 0x1af,         // mizuka.cpp same
        kObjSweeper5 = 0x1b0,         // mizuka.cpp same
        kObjFinaleBackdrop = 0x1b2,   // mizuka.cpp screen-space 320x320 loop at (0,0),
                                      // removed at 0x13b's frame 1
        kObj623Effect = 0x1b5,        // mizuka.cpp plays once, voice 1
        kObjGrabber = 0x1b6,          // mizuka.cpp sweeps in, on its frame 2 grabs the
                                      // opponent (0x45), 5900 damage when they land
        kObjCatchProp = 0x1b7,        // mizuka.cpp stands beside her in 0x133/0x134, shows
                                      // frame 2 while she is on frame 0x1c, fades after
        kObjCatcher = 0x1b8,          // mizuka.cpp falls from y -480 at the opponent
        kObj5AEffect = 0x1b9,         // mizuka.cpp plays once (90x5)
        kObj2AEffect = 0x1ba,         // mizuka.cpp plays once
        kObjJumpAEffect = 0x1bb,      // mizuka.cpp follows her, removed when she leaves
                                      // 0xcf
        kObj41236Flat1 = 0x1bc,       // mizuka.cpp thrown level at 3.6, bounces off on
                                      // contact, removed off screen
        kObj41236Flat2 = 0x1bd,       // mizuka.cpp same
        kObj41236Flat3 = 0x1be,       // mizuka.cpp same
        kObj41236Flat4 = 0x1bf,       // mizuka.cpp same
        kObj41236Up35 = 0x1c0,        // mizuka.cpp same at -35 degrees
        kObj41236Up60 = 0x1c1,        // mizuka.cpp same at -60 degrees
        kObj41236Up60b = 0x1c2,       // mizuka.cpp same at -60 degrees (41236C's)
        kObj41236Up85 = 0x1c3,        // mizuka.cpp same at -85 degrees
        kObj463214C = 0x1c4,          // mizuka.cpp large ground hit (frames 1-7), repeats
                                      // 4x, spawns another 60 px on
        kObjCatchThrow3 = 0x1c5,      // mizuka.cpp flies at 3.6
        kObjCatchThrow1 = 0x1c6,      // mizuka.cpp same
        kObjCatchThrow2 = 0x1c7,      // mizuka.cpp same
        kObjThrowHelperBack = 0x1c8,  // mizuka.cpp throw: 80 px behind the opponent, jumps,
                                      // runs with the carrier, faces m_throwHelperFacing
        kObjThrowCarrier = 0x1c9,     // mizuka.cpp throw: catches the falling opponent
                                      // (0x71), carries them 160 px, throws for 1200 (0x40)
        kObjThrowHelperFront = 0x1ca, // mizuka.cpp throw: 80 px in front of the opponent
        kObjAir214 = 0x1cb,           // mizuka.cpp 320x111, 99 hits (hitsLeft 0x63), voice 0xd
        kObjJump6CEffect = 0x1cc,     // mizuka.cpp follows her, loops while 0xd2 is before
                                      // frame 9
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMizuka's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,         // 412 + A, within 70 frames
        kCmd412B = 0x29,         // 412 + B, within 70 frames
        kCmd412C = 0x2a,         // 412 + C, within 70 frames
        kCmd412D = 0x2b,         // 412 + D, within 70 frames
        kCmd66A = 0x3c,          // 66 + A, within 55 frames
        kCmd66B = 0x3d,          // 66 + B, within 55 frames
        kCmd66C = 0x3e,          // 66 + C, within 55 frames
        kCmd66D = 0x3f,          // 66 + D, within 55 frames
        kCmd41236A = 0x46,       // 41236 + A (read as 413), within 70 frames
        kCmd41236B = 0x47,       // 41236 + B (read as 413), within 70 frames
        kCmd41236C = 0x48,       // 41236 + C (read as 413), within 70 frames
        kCmd41236D = 0x49,       // 41236 + D (read as 413), within 70 frames
        kCmd421A = 0x50,         // 421 + A, within 70 frames
        kCmd421B = 0x51,         // 421 + B, within 70 frames
        kCmd421C = 0x52,         // 421 + C, within 70 frames
        kCmd421D = 0x53,         // 421 + D, within 70 frames
        kCmdA5A6BC = 0x5a,       // A 5 A 6 B C, within 135 frames
        kCmd6BA65A = 0x5b,       // 6 B A 6 5 A, within 135 frames
        kCmd222C = 0x5c,         // 5 2 5 2 5 2 C, within 80 frames
        kCmdA5A4BC = 0x5d,       // A 5 A 4 B C, within 135 frames
        kCmdB5A2AB = 0x5e,       // B 5 A 2 A B, within 135 frames
        kCmd236236CExact = 0x5f, // 2 3 6 2 3 6 C with the C after the last 6 (unused),
                                 // within 80 frames
        kCmd263C = 0x60,         // 2 6 3 C, within 70 frames
        kCmdC236236 = 0x61,      // C 2 3 6 2 3 6, within 80 frames
        kCmd236236A = 0x64,      // 236236 + A, within 80 frames
        kCmd236236B = 0x65,      // 236236 + B, within 80 frames
        kCmd236236C = 0x66,      // 236236 + C, within 80 frames
        kCmd236236D = 0x67,      // 236236 + D, within 80 frames
        kCmd214214A = 0x6e,      // 214214 + A, within 80 frames
        kCmd214214B = 0x6f,      // 214214 + B, within 80 frames
        kCmd214214C = 0x70,      // 214214 + C, within 80 frames
        kCmd214214D = 0x71,      // 214214 + D, within 80 frames
        kCmd641236A = 0x78,      // 641236 + A (read as 6413), within 80 frames
        kCmd641236B = 0x79,      // 641236 + B (read as 6413), within 80 frames
        kCmd641236C = 0x7a,      // 641236 + C (read as 6413), within 80 frames
        kCmd641236D = 0x7b,      // 641236 + D (read as 6413), within 80 frames
        kCmd4631A = 0x82,        // 4631 + A, within 80 frames
        kCmd4631B = 0x83,        // 4631 + B, within 80 frames
        kCmd4631C = 0x84,        // 4631 + C, within 80 frames
        kCmd4631D = 0x85,        // 4631 + D, within 80 frames
        kCmd23614A = 0x8c,       // 23614 + A, within 80 frames
        kCmd23614B = 0x8d,       // 23614 + B, within 80 frames
        kCmd23614C = 0x8e,       // 23614 + C, within 80 frames
        kCmd23614D = 0x8f,       // 23614 + D, within 80 frames
        kCmd413413A = 0x96,      // 413413 + A, within 90 frames
        kCmd413413B = 0x97,      // 413413 + B, within 90 frames
        kCmd413413C = 0x98,      // 413413 + C, within 90 frames
        kCmd413413D = 0x99,      // 413413 + D, within 90 frames
        kCmd631631A = 0xa0,      // 631631 + A, within 90 frames
        kCmd631631B = 0xa1,      // 631631 + B, within 90 frames
        kCmd631631C = 0xa2,      // 631631 + C, within 90 frames
        kCmd631631D = 0xa3,      // 631631 + D, within 90 frames
        kCmd21436A = 0xaa,       // 21436 + A, within 80 frames
        kCmd21436B = 0xab,       // 21436 + B, within 80 frames
        kCmd21436C = 0xac,       // 21436 + C, within 80 frames
        kCmd21436D = 0xad,       // 21436 + D, within 80 frames
    };
    // END constants

    // FUNCTION: 0x4e7ec0
    virtual void UpdatePattern();
    // FUNCTION: 0x4f8300
    CMizuka(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x4f8480
    virtual void Reset();
    // FUNCTION: 0x4f8590
    virtual void StartPattern();
    // FUNCTION: 0x4f85d0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x4f8620
    virtual void Move();
    // FUNCTION: 0x4f8640
    virtual void StartCommand();
    // FUNCTION: 0x4faf20
    virtual void DrawGauge();
    // FUNCTION: 0x4faf30
    virtual void PreUpdate();
    // FUNCTION: 0x4faf40
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4faf70
    virtual void ReadCommand();
    // FUNCTION: 0x4fdc10
    virtual void CpuInput();
    // FUNCTION: 0x501e20
    virtual void UpdateObjects();

    int m_patternVar1; // scratch of the current pattern, zeroed by StartPattern: loop
                       // counts, frame counts, once-flags, vx*100 saved over a hitstop
    int m_patternVar2; // the same: a second counter, vy*100 in 0xaa/0xab, 0x13b's landing
                       // x (set by kObjGrabber)
    int m_patternVar3; // the same: 1 while 0x13b's kObjGrabber holds the opponent (the
                       // sweepers freeze), then the landing y
    int m_encasedBreakOut; // 1 while the kObjBurst that states 0x53-0x56 spawn is alive,
                           // so they spawn only one; the object clears it
    int m_objectVar1[0x40]; // per object, zeroed by RemoveObject: each object type's own
                            // counter or flag (loop counts, once-flags, saved vx*100)
    int m_objectVar2[0x40]; // per object, zeroed by RemoveObject: lifetimes of the
                            // debris, saved vy*100
    int m_objectVar3[0x40]; // per object, zeroed by RemoveObject: kObj236CHoming's angle,
                            // the sweepers' frozen state
    int m_catchState; // 641236 super: 0 none, 1 kObjCatcher caught the opponent, 2
                      // cinematic running, 3 a roll failed, 4 a roll won (damage), 5
                      // finished
    int m_throwArrived; // 1 when a kObjCatchThrow* reaches the caught opponent (x > 370);
                        // kObjCatcher advances and clears it
    int m_throwHelperFacing; // the facing (1/-1, stored in an int, read as a char) that
                             // kObjThrowCarrier hands to the two throw helpers
    int m_homingOrbHit; // 1 once one of 236C's four kObj236CHoming caught the opponent:
                        // the others stop; cleared when 236C starts
    int m_flightTime; // frames of D's flight left: 1000 at 0xb3's start, -1 a frame while
                      // flying or air dashing, 0 on landing; > 0 = flying
    BYTE unk345c[0x3460 - 0x345c];
};

// Misuzu: one of the character classes.
// SIZE: 0x3488
class CMisuzu : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMisuzu's own actions
    enum {
        k5A = 0xc8,                   // A standing
        k5BClose = 0xc9,              // B standing within 70 px of the opponent
        k5BFar = 0xca,                // B standing otherwise
        k5C = 0xcb,                   // C standing
        k2A = 0xcc,                   // A crouching
        k2B = 0xcd,                   // B crouching
        k2C = 0xce,                   // C crouching
        kJumpA = 0xcf,                // A in the air
        kJumpB = 0xd0,                // B in the air
        kJumpC = 0xd1,                // C in the air
        kUnusedHopAttack = 0xd2,      // never started (no pattern = 0xd2 in her code
        k6C = 0xd3,                   // C + forward
        kUnusedAirDive = 0xd4,        // never started (the j.2C slot in Ayu, ayu.cpp)
        kUnusedAirDiveRebound = 0xd5, // UpdatePattern entered from 0xd4 when it connects:
                                      // bounces back (vx -1, vy -2.4)
        kUnusedAirDiveLanding = 0xd6, // UpdatePattern entered from 0xd4 on landing: screen
                                      // shake, dust
        kThrow = 0xdc,                // C + a direction within 30 px of a grounded opponent
                                      // not in hit/guard stun
        kThrowHit = 0xdd,             // UpdatePattern holds the opponent (0x64/0x6c/0x68),
                                      // DealDamage(1200) at frame 5, throws it (0x3b)
        kDashA = 0xe6,                // dash A slot
        kDashB = 0xe7,                // as 0xe6 for B
        kDashC = 0xe8,                // as 0xe6 for C
        kDash2A = 0xe9,               // not Misuzu's (no case, never entered)
        kDash2B = 0xea,               // as 0xe9
        kDash2C = 0xeb,               // as 0xe9
        kAirThrow = 0xf8,             // air, forward + C within 100 px of an airborne
                                      // opponent
        kAirThrowHit = 0xf9,          // UpdatePattern carries the opponent,
                                      // DealDamage(1200) at frame 4, lands -> 0xd
        k214A = 0xfa,                 // 214A
        k214B = 0xfb,                 // 214B
        k214C = 0xfc,                 // 214C
        k236A = 0xfd,                 // 236A
        k236B = 0xfe,                 // 236B
        k236C = 0xff,                 // 236C
        k41236A = 0x100,              // 41236A with the crow idle and within 50 px
        k41236B = 0x101,              // 41236B
        k41236C = 0x102,              // 41236C (m_rfGauge >= 500 unless stocked)
        k623A = 0x103,                // 623A on the ground
        k623B = 0x104,                // 623B
        k623C = 0x105,                // 623C (m_rfGauge >= 500)
        kAir623A = 0x106,             // 623A in the air
        kAir623B = 0x107,
        kAir623C = 0x108,             // misuzu.cpp, UpdatePattern (costs 500)
        k421A = 0x109,                // 421A
        k421B = 0x10a,                // 421B
        k421C = 0x10b,                // 421C (m_rfGauge >= 500)
        k214214Lv1 = 0x12c,           // 214214 with 1 level
        k214214Lv2 = 0x12d,           // 2 levels
        k214214Lv3 = 0x12e,           // 3 levels
        k214214Counter = 0x12f,       // UpdatePattern entered when 0x12c-0x12e catch an
                                      // attack: throws 0x1a9-0x1ab, jumps (vy -2.9), spawns
                                      // 0x1b3
        kAir214214Lv1 = 0x130,        // air 214214, UpdatePattern (keeps vx/vy/ay
                                      // x100/x1000 in m_patternVar1-m_patternVar3)
        kAir214214Lv2 = 0x131,        // misuzu.cpp, unreachable and has no case in
                                      // UpdatePattern
        kAir214214Lv3 = 0x132,        // misuzu.cpp, unreachable, no case
        k236236Lv1 = 0x133,           // 236236 with 1 level
        k236236Lv2 = 0x134,           // misuzu.cpp, UpdatePattern spawns 0x1b6
        k236236Lv3 = 0x135,           // misuzu.cpp, UpdatePattern spawns 0x1b8 from below
                                      // the ground
        k46321 = 0x136,               // 4,6,3,1 + any button, 1 level, all buttons give it
        k46321Lv2 = 0x137,            // UpdatePattern costs 2 levels, adds 2 stocks
        k46321Lv3 = 0x138,            // UpdatePattern costs 3 levels, adds 3 stocks
        k41236AStock = 0x139,         // 41236A with a crow stock
        k41236BStock = 0x13a,         // misuzu.cpp, UpdatePattern
        k41236CStock = 0x13b,         // misuzu.cpp (no m_rfGauge needed), UpdatePattern
        kLv4 = 0x13c,                 // A,5,A,2,B,C (command 0x5d) with a full gauge and HP
                                      // < 3333
        kLv4Finish = 0x13d,           // set by object 0x1c1 after its 5000 damage when the
                                      // KO doesn't end the match
        kObjCrow = 0x190,             // spawned by Reset
        kObjAirTrapA = 0x193,         // misuzu.cpp from 0xfa: if an airborne opponent comes
                                      // within 50 px during frame 1 it catches (frame 2)
        kObjAirTrapB = 0x194,         // misuzu.cpp from 0xfb, as 0x193
        kObjAirTrapC = 0x195,         // misuzu.cpp from 0xfc, as 0x193 but freezes 90
                                      // frames
        kObjGroundTrapA = 0x196,      // misuzu.cpp from 0xfd: after 20 frames, triggers
                                      // when the opponent is within 50 px horizontally
        kObjGroundTrapB = 0x197,      // misuzu.cpp from 0xfe, as 0x196
        kObjGroundTrapC = 0x198,      // misuzu.cpp from 0xff, triggers within 70 px
        kObjCrowAttackA = 0x199,      // misuzu.cpp the crow from 41236A: sinks, at frame 4
                                      // swoops forward (vx 4, slowing 0.06), back to 0x190
        kObjCrowAttackB = 0x19a,      // misuzu.cpp from 41236B, as 0x199
        kObjCrowAttackC = 0x19b,      // misuzu.cpp from 41236C: 5 hits, dives (vx 3.4, vy
                                      // 1) at frame 4, spawns 0x19c, holds frame 5 until it
                                      // is below ground
        kObjCrowDiveEffect = 0x19c,   // misuzu.cpp sits on the crow (m_crowX/Y) during
                                      // 0x19b
        kObj421HoldA = 0x19d,         // misuzu.cpp on Misuzu during 0x109 (removed if she
                                      // leaves it, is hit, or past frame 24)
        kObj421LauncherA = 0x19e,     // misuzu.cpp above her head: at frame 10 fires 0x1c8
                                      // unless she was hit or restarted 421
        kObj421HoldB = 0x1a0,         // misuzu.cpp as 0x19d for 0x10a, spawns 0x1a1
        kObj421LauncherB = 0x1a1,     // misuzu.cpp fires 0x1c9
        kObj421HoldC = 0x1a3,         // misuzu.cpp as 0x19d for 0x10b, spawns 0x1a4
        kObj421LauncherC = 0x1a4,     // misuzu.cpp fires 0x1ca
        kObjFloaterPop = 0x1a8,       // misuzu.cpp what every poison floater turns into
                                      // when it ends or hits: plays once, removed
        kObjCounterPoisonLv1 = 0x1a9, // misuzu.cpp thrown by 0x12f after 0x12c (vy -1.5,
                                      // gravity 0.035, 1 hit): a hit adds 1 poison level,
                                      // full poison time
        kObjCounterPoisonLv2 = 0x1aa, // misuzu.cpp after 0x12d: +3 poison levels
        kObjCounterPoisonLv3 = 0x1ab, // misuzu.cpp after 0x12e: +5 poison levels (the
                                      // maximum)
        kObjCounterDropA = 0x1ac,     // misuzu.cpp one of three random drops
                                      // (Random(0,3)+0x1ac,): falls, on the ground splashes
                                      // 4 of 0x1af-0x1b2, voice 0xb
        kObjCounterDropB = 0x1ad,     // misuzu.cpp as 0x1ac
        kObjCounterDropC = 0x1ae,     // misuzu.cpp as 0x1ac
        kObjCounterSplashA = 0x1af,   // misuzu.cpp one of four random splash pieces
                                      // (Random(0,4)+0x1af): small random hop, gravity
                                      // 0.035
        kObjCounterSplashB = 0x1b0,   // misuzu.cpp as 0x1af
        kObjCounterSplashC = 0x1b1,   // misuzu.cpp as 0x1af
        kObjCounterSplashD = 0x1b2,   // misuzu.cpp as 0x1af
        kObjCounterJump = 0x1b3,      // misuzu.cpp spawned at her feet by 0x12f
        kObjSummonLv1 = 0x1b4,        // misuzu.cpp from 0x133: while she stays in 0x133,
                                      // frame 7 fires 0x1b5 (frame 8 repeats it 20 times)
        kObjSummonLv1Shot = 0x1b5,    // misuzu.cpp 1 hit, vx 1.0-1.9 random, rising slowly
        kObjSummonLv2 = 0x1b6,        // misuzu.cpp from 0x134, 45 px up: frame 8 fires
                                      // 0x1b7, 20 repeats
        kObjSummonLv2Shot = 0x1b7,    // misuzu.cpp 1 hit, vx 1.5-2.4, vy 0-0.9 random
        kObjSummonLv3 = 0x1b8,        // misuzu.cpp from 0x135, rises from 200 px below (vy
                                      // -6.8), frames 1 and 2 each fire 0x1b9, 16 loops (32
                                      // shots)
        kObjSummonLv3Shot = 0x1b9,    // misuzu.cpp 1 hit, SetVelocity(45 - 2*m_summonShots
                                      // degrees, 4) plus random
        kObjSummonVanish = 0x1ba,     // misuzu.cpp what 0x1b4/0x1b6 become when done or
                                      // when she leaves the super: plays once, removed
        kObjCrowStockA = 0x1bb,       // misuzu.cpp the crow during 0x139: acts in the
                                      // freeze (movesInFreeze), 99 hits flag (hitsLeft 0x63) then 6,
                                      // ground attack looping frames 18-21 ten times
        kObjCrowStockB = 0x1bc,       // misuzu.cpp during 0x13a: lands, frame 9 spawns
                                      // 0x1be in front, frame 14 releases it
                                      // (m_crowShotRelease)
        kObjCrowStockC = 0x1bd,       // misuzu.cpp during 0x13b: 10 hits, lands, jumps
                                      // forward at frame 7 (vx 1.5, vy -3.5)
        kObjCrowStockShot = 0x1be,    // misuzu.cpp floats in front of the crow until
                                      // m_crowShotRelease, then flies (vx 3.5, 99 hits) off
                                      // the screen
        kObjCrowStockEffect = 0x1bf,  // misuzu.cpp spawned at the crow when 0x1bb-0x1bd
                                      // start and end
        kObjCounterJumpRise = 0x1c0,  // misuzu.cpp from 0x1b3: rises (vy -3, gravity
                                      // 0.045), plays once
        kObjLv4Finisher = 0x1c1,      // misuzu.cpp screen object from 0x13c: at frame 16
                                      // takes 5000 HP, puts the opponent in 0x63 and Misuzu
                                      // in 0x13d
        kObjLv4Intro = 0x1c2,         // misuzu.cpp spawned as 0x13c starts at her hand (x +
                                      // 7*facing, y - 42)
        kObjLv4Intro2 = 0x1c3,        // misuzu.cpp continues 0x1c2
        kObjLv4IntroEffect = 0x1c4,   // misuzu.cpp at (x + 9*facing, y - 53), plays once
        kObjPoisonFloaterA = 0x1c5,   // misuzu.cpp from 0x1cb: 1 hit, drifts down swaying,
                                      // pops (0x1a8) near the ground (y >= -75), after 20
                                      // loops or 1200 frames
        kObjPoisonFloaterB = 0x1c6,   // misuzu.cpp from 0x1cc: drifts back (vx -0.3)
                                      // bobbing
        kObjPoisonFloaterC = 0x1c7,   // misuzu.cpp two from 0x1cd, random drift
        kObj421ShotA = 0x1c8,         // misuzu.cpp from 0x19e: flies up and forward (vx 4,
                                      // vy -2.5), bursts (0x1cb) over the opponent (within
                                      // 5 px) or at its end
        kObj421ShotB = 0x1c9,         // misuzu.cpp from 0x1a1: flies straight (vx 4), stops
                                      // once past the opponent, bursts (0x1cc)
        kObj421ShotC = 0x1ca,         // misuzu.cpp from 0x1a4: as 0x1c8, bursts into 0x1cd
        kObj421BurstA = 0x1cb,        // misuzu.cpp at frame 10 releases 0x1c5 unless she
                                      // was hit or restarted 421
        kObj421BurstB = 0x1cc,        // misuzu.cpp releases 0x1c6
        kObj421BurstC = 0x1cd,        // misuzu.cpp releases two 0x1c7
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMisuzu's own commands (ReadCommand)
    enum {
        kCmd421A = 0x3c,    // 421 + A, within 45 frames
        kCmd421B = 0x3d,    // 421 + B, within 45 frames
        kCmd421C = 0x3e,    // 421 + C, within 45 frames
        kCmd421D = 0x3f,    // 421 + D, within 45 frames
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 60 frames
        kCmdA5A2BC = 0x5d,  // A 5 A 2 B C, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd4631A = 0x82,   // 4631 + A, within 75 frames
        kCmd4631B = 0x83,   // 4631 + B, within 75 frames
        kCmd4631C = 0x84,   // 4631 + C, within 75 frames
        kCmd4631D = 0x85,   // 4631 + D, within 75 frames
    };
    // END constants

    // FUNCTION: 0x50c4b0
    virtual void UpdatePattern();
    // FUNCTION: 0x519e00
    CMisuzu(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x51a070
    virtual void Reset();
    // FUNCTION: 0x51a2a0
    virtual void StartPattern();
    // FUNCTION: 0x51a2e0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x51a330
    virtual void Move();
    // FUNCTION: 0x51a350
    virtual void StartCommand();
    // FUNCTION: 0x51d390
    virtual void DrawGauge();
    // FUNCTION: 0x51dde0
    virtual void PreUpdate();
    // FUNCTION: 0x51df30
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x51df60
    virtual void ReadCommand();
    // FUNCTION: 0x51f3e0
    virtual void CpuInput();
    // FUNCTION: 0x5236d0
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch value of the current action, zeroed by StartPattern:
                       // loop counts (236's windup, 236236's repeats), dash frame count,
                       // vx * 100 kept across a freeze; object 0x1bb also reads it
    int m_patternVar2; // Second scratch value of the current action, zeroed by
                       // StartPattern: dash frame count (a held dash ends at 120), vy *
                       // 100 kept across a freeze, 0x13d's loop count
    int m_patternVar3; // Third scratch value of the current action, zeroed by
                       // StartPattern: one-shot flags, ay * 1000 in 0x130, 0x13c's loop
                       // count
    int m_encasedBreakOut; // 1 while object 0x1f0 (spawned by hit states 0x53-0x56)
                           // exists, so only one is spawned; cleared when it bursts into
                           // 0x1f1/0x1f2
    int m_crowX; // The crow's (object 0x190) x, as an int, written by the crow every
                 // frame; 41236 needs Misuzu within 50 px of it
    int m_crowY; // The crow's y, as an int, written with m_crowX
    int m_crowBusy; // 1 while the crow is attacking (0x199-0x19b, 0x1bb-0x1bd), 0 once it
                    // is back to 0x190; 41236 needs 0
    int m_summonShots; // Shots 0x1b9 fired so far by 236236 lv3's object 0x1b8 (aims each
                       // at 45 - 2n degrees); 0 when 0x1b8 ends
    int m_objectVar1[0x40]; // Per-object scratch, zeroed when the object is removed:
                            // init/motion step, repeat counts, a hit-once flag, a
                            // cancelled flag
    int m_objectVar2[0x40]; // Per-object scratch, zeroed when the object is removed: once
                            // flags, repeat counts, age in frames of the poison floaters
                            // (they expire past 1200), lifetime countdown of 0x1f1/0x1f2
    int m_objectVar3[0x40]; // Per-object scratch, zeroed when the object is removed:
                            // animation cycles of the poison floaters (they pop past 20
                            // or 6)
    int m_poisonTick; // Frames since the poison last took HP; the opponent loses 10 HP
                      // each time it passes 45 - 7 * m_poisonLevel (never below 1 HP), in
                      // PreUpdate (Vf8)
    int m_poisonTime; // Frames of poison left, at most 3000: a poisoning hit sets 3000
                      // (adds 1000 if already poisoned); DrawGauge draws it as a bar
    int m_poisonLevel; // Poison level 0-5 on the opponent, raised by the hits of her
                       // poison objects; 0 ends it; cleared when Misuzu is hit, the time
                       // runs out or the opponent is KO
    int m_crowStock; // Crow stocks 0-3, added by 46321 (0x136); with one, 41236 becomes
                     // 0x139-0x13b and uses it; DrawGauge draws one icon per stock
    int m_crowShotRelease; // Set by the stocked crow 0x1bc at its frame 14: its shot
                           // 0x1be, waiting in frame 0, then flies; cleared when
                           // 0x1bc/0x1bd end
    int m_airTrapA; // 1 while 214A's object 0x193 exists; 214A can't start again until it
                    // is gone
    int m_airTrapB; // 1 while 214B's object 0x194 exists; blocks 214B
    int m_airTrapC; // 1 while 214C's object 0x195 exists; blocks 214C
    int m_groundTrapA; // 1 while 236A's object 0x196 exists; blocks 236A
    int m_groundTrapB; // 1 while 236B's object 0x197 exists; blocks 236B
    int m_groundTrapC; // 1 while 236C's object 0x198 exists; blocks 236C
    BYTE unk3484[0x3488 - 0x3484];
};

// Mishio: one of the character classes.
// SIZE: 0x3478
class CMishio : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMishio's own actions
    enum {
        k5A = 0xc8,                         // A standing
        k5BClose = 0xc9,                    // B standing within 90 px of the opponent
        k5BFar = 0xca,                      // B standing otherwise
        k5C = 0xcb,                         // C standing
        k2A = 0xcc,                         // A crouching
        k2B = 0xcd,                         // B crouching
        k2C = 0xce,                         // C crouching
        kJumpA = 0xcf,                      // A in the air
        kJumpB = 0xd0,                      // B in the air
        kJumpC = 0xd1,                      // C in the air
        k6B = 0xd2,                         // forward+B, only with power-up bit 1
                                            // (m_powerUp 2 or 3): a hop kick, vx 1.0 vy
                                            // -1.3 at frame 2
        k6C = 0xd3,                         // forward+C, only with power-up bit 0
                                            // (m_powerUp 1 or 3)
        kAirDiveUnused = 0xd4,              // a falling attack (vx halved, ay 0.07) that
                                            // bounces off on contact (0xd5) or lands with a
                                            // shake (0xd6)
        kAirDiveBounce = 0xd5,              // 0xd4 on contact: rebound vx -1.0 vy -2.4,
                                            // then falls (9)
        kAirDiveLanding = 0xd6,             // 0xd4 reaching the ground: shake, dust effect
                                            // 3
        kThrow = 0xdc,                      // C + a direction next to (|dx| < 30) a
                                            // grounded opponent not in a hit/guard action
        kThrowConnected = 0xdd,             // 0xdc caught (frame 2, hit): opponent
                                            // 0x6b/0x6c, put behind her and turned (0x34),
                                            // she turns
        kDashA = 0xe6,                      // A during the forward dash (0xa3)
        kDashB = 0xe7,                      // B during the forward dash
        kDashC = 0xe8,                      // C during the forward dash
        kDash2A = 0xe9,                     // down+A during the forward dash
        kDash2B = 0xea,                     // down+B during the forward dash
        kDash2C = 0xeb,                     // down+C during the forward dash
        kAirThrow = 0xf8,                   // forward+C in the air within 100 px of an
                                            // airborne opponent
        kAirThrowConnected = 0xf9,          // 0xf8 caught: opponent 0x67 held,
                                            // DealDamage(0x47e), opponent 0x76/0x62/0x75
        k623A = 0xfa,                       // 623A with no power-up: on contact
                                            // (m_attackResult > 0) grants m_powerUp 1 or 2
                                            // at random (Random(0,1000) < 500) at its end
        k623B = 0xfb,                       // 623B with no power-up
        k623C = 0xfc,                       // 623C with no power-up: needs m_rfGauge >= 500 or
                                            // m_rfBlue, takes 500 (250) of m_rfGauge, 2 hits,
                                            // grants a power-up if it connected
        k236B = 0xfd,                       // 236B (also 236C without the m_rfGauge cost),
                                            // power-up bit 0: rush vx 3.0 at frame 5, 6
                                            // hits, frames 5-6 twice
        k236A = 0xfe,                       // 236A, power-up bit 0: stationary, 4 hits
                                            // (frames 6/9/0xc/0xf)
        k236C = 0xff,                       // 236C, power-up bit 0, needs/takes m_rfGauge 500
                                            // (250): rush vx 3.2, 99 hits
        k214C = 0x100,                      // 214C on the ground, power-up bit 0: turns
                                            // round at frame 4, then flies up-forward (-45
                                            // deg, speed 2.2) with trail 0x194
        k214A = 0x101,                      // 214A on the ground, power-up bit 0: flies up-
                                            // forward (-45 deg) with trail 0x194, follow-
                                            // ups as 0x100
        k214B = 0x102,                      // 214B on the ground, power-up bit 0: flies
                                            // straight up (-90 deg) with trail 0x193
        kAir214A = 0x103,                   // 214A in the air: flies forward (0 deg) with
                                            // trail 0x195
        kAir214B = 0x104,                   // 214B in the air: flies down-forward (45 deg)
                                            // with trail 0x196
        kAir214C = 0x105,                   // 214C in the air: flies straight down (90 deg)
                                            // with trail 0x197
        k214Follow8 = 0x106,                // 214 follow-up, button + up: flies up (-90)
                                            // with trail 0x193
        k214Follow9 = 0x107,                // 214 follow-up, button + up-forward (up-back
                                            // turns round): flies -45 with trail 0x194
        k214Follow6 = 0x108,                // 214 follow-up, button + forward (back turns
                                            // round): flies 0 deg with trail 0x195
        k214Follow3 = 0x109,                // 214 follow-up, button + down-forward (down-
                                            // back turns round): flies 45 deg with trail
                                            // 0x196
        k214Follow2 = 0x10a,                // 214 follow-up, button + down: flies 90 deg
                                            // with trail 0x197
        k214FollowRecovery = 0x10b,         // after a 214 follow-up: slows, falls, lands
        k412A = 0x10c,                      // 412A (back, down-back, down), power-up bit 1,
                                            // needs m_shotOut 0: shot 0x190 at frame 7
        k412B = 0x10d,                      // 412B: shot 0x191
        k412C = 0x10e,                      // 412C, needs/takes m_rfGauge 500 (250): shot
                                            // 0x192
        k22A = 0x10f,                       // 22A, power-up bit 1, needs m_fieldOut 0:
                                            // object 0x198 on the ground at the opponent's
                                            // x, at most 150 px away
        k22B = 0x110,                       // 22B: as 22A but 0x198 goes to the opponent's
                                            // x only when farther than 150 px, else 150 px
                                            // away
        k623APower1 = 0x111,                // 623A with power-up 1: sweeping arc 0x1b5
                                            // (trail 0x19b) at frame 2
        k623BPower1 = 0x112,                // 623B with power-up 1: arc 0x1b5
        k623CPower1 = 0x113,                // 623C with power-up 1, m_rfGauge cost: arc 0x1bc
                                            // (reverse sweep) at frame 3, 0x1b5 at frame 9
        k623APower2 = 0x114,                // 623A with power-up 2: arc 0x1b6 (trail 0x1b7)
                                            // and flash 0x1b8
        k623BPower2 = 0x115,                // 623B with power-up 2: arc 0x1b6, 0x1b8, slow
                                            // 5-hit orb 0x1ba
        k623CPower2 = 0x116,                // 623C with power-up 2, m_rfGauge cost: arcs 0x1bd
                                            // then 0x1b6, two 0x1b8
        k623APower3 = 0x117,                // 623A (and, by a slip, 623B) with power-up 3:
                                            // plain attack, grants nothing
        k623BPower3 = 0x118,                // 623B with power-up 3 as written (lunge vx
                                            // 2.5), but StartCommand starts 0x117 instead:
                                            // unreachable
        k623CPower3 = 0x119,                // 623C with power-up 3, m_rfGauge cost, 2 hits
        k214Recovery = 0x11a,               // after a 214 flight with no follow-up (ground
                                            // 214s, air 214B/C running out): one follow-up
                                            // still allowed
        k214Recovery2 = 0x11b,              // same code as 0x11a (another animation): after
                                            // air 214A, and air 214B/C landing
        k236236A = 0x12c,                   // 236236 + A/B/C on the ground, 1000 gauge,
                                            // power-up bit 0: rush vx 3.5, 99 hits, first
                                            // hit freezes the opponent
        k236236B = 0x12d,                   // 2000 gauge (B or C): as A, longer, sparkles
                                            // 0x19a
        k236236C = 0x12e,                   // 3000 gauge (C): longest, sparkles 0x19a/0x19b
        k214214A = 0x12f,                   // 214214, 1000 gauge, power-up bit 0: flies -45
                                            // deg with trail 0x19e
        k214214B = 0x130,                   // 2000 gauge: m_superLevel 2, up to 3 follow-
                                            // ups
        k214214C = 0x131,                   // 3000 gauge: m_superLevel 3, up to 4 follow-
                                            // ups, screen effect FlashNegative(0xf) during them
        k214214Follow8 = 0x132,             // 214214 follow-up up: flies -90 with trail
                                            // 0x19c
        k214214Follow9 = 0x133,             // 214214 follow-up up-forward/up-back: flies
                                            // -45 with trail 0x19e
        k214214Follow6 = 0x134,             // 214214 follow-up forward/back: flies 0 deg
                                            // with trail 0x19d
        k214214Follow3 = 0x135,             // 214214 follow-up down-forward/down-back:
                                            // flies 45 deg with trail 0x19f
        k214214Follow2 = 0x136,             // 214214 follow-up down: flies 90 deg with
                                            // trail 0x1a0
        k214214Recovery = 0x137,            // after 214214 and its follow-ups (one more
                                            // follow-up while allowed)
        k641236A = 0x138,                   // 641236 + A/B/C, 1000 gauge, power-up bit 1:
                                            // orb 0x1a1 over her head (+ glow 0x1ad)
        k641236B = 0x139,                   // 2000 gauge, held B charges, shots 0x1a3/0x1af
        k641236C = 0x13a,                   // 3000 gauge, held C charges, shots
                                            // 0x1a4/0x1b0, FlashNegative(0xf)
        kAir236236A = 0x13b,                // 236236 in the air, 1000 gauge, power-up bit
                                            // 1: recoils back-up, one orb 0x1a6 down at 50
                                            // deg
        kAir236236B = 0x13c,                // 2000 gauge: orbs 0x1a8, 0x1b1, 0x1a7
                                            // (45/50/55 deg)
        kAir236236C = 0x13d,                // 3000 gauge: orbs 0x1ac, 0x1ab, 0x1b2, 0x1aa,
                                            // 0x1a9 (40-60 deg)
        kLv4 = 0x13e,                       // LV4: B 5 B 2 5 C A (command 0x62), HP < 3333,
                                            // 3000 gauge, grounded: burst 0x1b3, aura
                                            // 0x1b4, glows 0x1ad
        kObjShotFast = 0x190,               // 412A's shot: vx 2.5, 1 hit, frames 0x1d-0x30
                                            // five times, fades from 0x31 (on hit too)
        kObjShotSlow = 0x191,               // 412B's shot: vx 1.2, 3 hits, loops seven
                                            // times
        kObjShotAccel = 0x192,              // 412C's shot: from vx 0, +0.0025 a frame, 99
                                            // hits, loops until it leaves the screen
        kObjFlightTrailUp = 0x193,          // follows her during 214B / up follow-up
                                            // (0x102, 0x106), fades at frame 0x1a when the
                                            // flight ends
        kObjFlightTrailUpForward = 0x194,   // the same for 0x100, 0x101, 0x107
        kObjFlightTrailForward = 0x195,     // the same for 0x103, 0x108
        kObjFlightTrailDownForward = 0x196, // the same for 0x104, 0x109
        kObjFlightTrailDown = 0x197,        // the same for 0x105, 0x10a
        kObjField = 0x198,                  // 22A/22B's object: hits at frames 0 and 0x12,
                                            // then every 15 frames spawns 0x199 within +-50
                                            // px (Random)
        kObjFieldHit = 0x199,               // 0x198's hits: 1 hit, one animation
        kObjSuperSparkle = 0x19a,           // spawned at random around her in 236236B/C
        kObjSparkle = 0x19b,                // trail sparkle of 0x19c-0x1a0 and the power-1
                                            // arcs 0x1b5/0x1bc, and in 236236C
        kObjSuperTrailUp = 0x19c,           // follows her in 214214's up follow-up (0x132),
                                            // sparkles 0x19b every 12 frames
        kObjSuperTrailForward = 0x19d,      // the same for 0x134
        kObjSuperTrailUpForward = 0x19e,    // the same for 0x12f-0x131 and 0x133
        kObjSuperTrailDownForward = 0x19f,  // the same for 0x135
        kObjSuperTrailDown = 0x1a0,         // the same for 0x136
        kObjOrb = 0x1a1,                    // 641236's orb: 1 hit, held 148 px over her
                                            // head while charging, in front of her from
                                            // frame 0xc, loops while the shots fire
        kObjOrbShotA = 0x1a2,               // 641236A's shot, 1 hit
        kObjOrbShotB = 0x1a3,               // 641236B's shot
        kObjOrbShotC = 0x1a4,               // 641236C's shot
        kObjFlash = 0x1a5,                  // flash when 641236 is fully charged and when
                                            // the air 236236 orbs leave
        kObjAirOrbA = 0x1a6,                // air 236236A's orb: down at 50 deg, lands,
                                            // lingers 2 hits for 20 loops
        kObjAirOrbB55 = 0x1a7,              // air 236236B, 55 deg, 3 hits on the ground
        kObjAirOrbB45 = 0x1a8,              // air 236236B, 45 deg
        kObjAirOrbC60 = 0x1a9,              // air 236236C, 60 deg, 4 hits on the ground
        kObjAirOrbC55 = 0x1aa,              // air 236236C, 55 deg
        kObjAirOrbC45 = 0x1ab,              // air 236236C, 45 deg
        kObjAirOrbC40 = 0x1ac,              // air 236236C, 40 deg
        kObjGlow = 0x1ad,                   // follows 641236's orb
        kObjOrbShotChargedA = 0x1ae,        // 641236A's shot after a full charge
        kObjOrbShotChargedB = 0x1af,
        kObjOrbShotChargedC = 0x1b0,
        kObjAirOrbB50 = 0x1b1,              // air 236236B, 50 deg, 3 hits on the ground
        kObjAirOrbC50 = 0x1b2,              // air 236236C, 50 deg, 4 hits
        kObjLv4Burst = 0x1b3,               // the LV4's hit around her (1 hit, follows her
                                            // during 0x13e)
        kObjLv4Aura = 0x1b4,                // LV4 start
        kObjArcPower1 = 0x1b5,              // power-1 623's arc: alive during 0x111-0x113,
                                            // sweeps an angle each frame and spawns sparkle
                                            // 0x19b along it (radius Random(0,30)+60)
        kObjArcPower2 = 0x1b6,              // power-2 623's arc (0x114-0x116), sparkles
                                            // 0x1b7
        kObjArcPower2Sparkle = 0x1b7,
        kObjArcPower2Flash = 0x1b8,         // at her feet with each power-2 arc
        kObjSlowOrbSparkle = 0x1b9,         // sparkles of 0x1ba/0x1bb
        kObjSlowOrb = 0x1ba,                // 623B power-2's orb: vx 0.5, 5 hits, loops 5
                                            // times, sparkles 0x1b9
        kObjSlowOrbBig = 0x1bb,             // as 0x1ba with 10 hits and 10 loops
        kObjArcPower1Reverse = 0x1bc,       // 623C power-1's first arc, swept the other way
        kObjArcPower2Reverse = 0x1bd,       // 623C power-2's first arc, swept the other way
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMishio's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd236236A = 0x64, // 236236 + A, within 80 frames
        kCmd236236B = 0x65, // 236236 + B, within 80 frames
        kCmd236236C = 0x66, // 236236 + C, within 80 frames
        kCmd236236D = 0x67, // 236236 + D, within 80 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
        kCmd21436A = 0xaa,  // 21436 + A, within 90 frames
        kCmd21436B = 0xab,  // 21436 + B, within 90 frames
        kCmd21436C = 0xac,  // 21436 + C, within 90 frames
        kCmd21436D = 0xad,  // 21436 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x530bc0
    virtual void UpdatePattern();
    // FUNCTION: 0x546480
    CMishio(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x546690
    virtual void Reset();
    // FUNCTION: 0x546830
    virtual void StartPattern();
    // FUNCTION: 0x546870
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x5468c0
    virtual void Move();
    // FUNCTION: 0x5468e0
    virtual void StartCommand();
    // FUNCTION: 0x549dc0
    virtual void DrawGauge();
    // FUNCTION: 0x54aa90
    virtual void PreUpdate();
    // FUNCTION: 0x54ad50
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x54ad80
    virtual void ReadCommand();
    // FUNCTION: 0x54c250
    virtual void CpuInput();
    // FUNCTION: 0x54fd30
    virtual void UpdateObjects();

    int m_patternVar1; // scratch for the current action, zeroed by StartPattern: loop
                       // counts, hit-landed flags, vx * 100 saved over a hit stop
    int m_patternVar2; // scratch for the current action, zeroed by StartPattern: follow-
                       // ups used, shot repeats, vy * 100 saved
    int m_patternVar3; // scratch for the current action, zeroed by StartPattern: once-
                       // per-action flags, loop counts
    int m_encasedBreakOut; // 1 while object 0x1f0 (spawned by shared actions 0x53-0x56)
                           // is out; cleared when it bursts into 0x1f1/0x1f2
    int m_shotOut; // 1 while 412's shot (0x190-0x192) is out; 412 can't start again until
                   // the shot hits, fades or leaves
    int m_fieldOut; // 1 while 22A/22B's object 0x198 is out; 22A/22B can't start again
                    // until it ends
    int m_superCounter; // not reset by StartPattern: 236236's first-hit flag (freezes the
                        // opponent once); 214214's follow-ups used, at most m_superLevel
                        // + 1
    int m_superLevel; // 214214's level, 1-3 (A/B/C, 1000-3000 gauge); bounds its follow-
                      // ups
    int m_powerUp; // 0 none; 1 or 2 drawn at random when 623+button connects with none;
                   // bit 0 opens 236, 214, 6C, 236236, 214214, bit 1 opens 412, 22, 6B,
                   // 641236, air 236236; the move (mostly) sets it back to 0; 3 both,
                   // from the LV4, for m_powerUpTime
    int m_powerUpParticleTimer; // Vf8: frames to the next particle effect (0x22 power 1,
                                // 0x24 power 2) around her while powered up, every 2
                                // frames
    int m_powerUpTintTimer; // Vf8: 0-0x90 while m_powerUp is 3; tints her every 0x12
                            // frames
    int m_powerUpIconTimer; // DrawGauge: 0-0x1d; the power-up icon's animation frame is
                            // it / 6
    int m_powerUpTime; // frames left of the LV4's double power-up, from 4500; m_powerUp
                       // drops to 0 at 0; drawn as a bar
    int unk316c;
    int unk3170;
    int m_objectVar1[0x40]; // per object, zeroed by RemoveObject: once-flags, loop
                            // counts, spawn countdowns, sweep angles
    int m_objectVar2[0x40]; // per object, zeroed by RemoveObject: re-hit timers, loop
                            // counts, angle steps, lifetimes
    int unk3374[0x40]; // indexed
    BYTE unk3474[0x3478 - 0x3474];
};

// Misaki: one of the character classes.
// SIZE: 0x3448
class CMisaki : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMisaki's own actions
    enum {
        k5A = 0xc8,                 // A standing
        k5BClose = 0xc9,            // B standing within 70 px of the opponent
        k5BFar = 0xca,              // B standing farther than 70 px
        k5C = 0xcb,                 // C standing
        k2A = 0xcc,                 // A crouching
        k2B = 0xcd,                 // B crouching
        k2C = 0xce,                 // C crouching: a slide, vx 4.5 at frame 3 decelerating
                                    // by 0.08
        kJumpA = 0xcf,              // A in the air
        kJumpB = 0xd0,              // B in the air
        kJumpC = 0xd1,              // C in the air
        kUnusedHopAttack = 0xd2,    // never started (no assignment anywhere): hop vx 1.4 vy
                                    // -1.5, hit at frame 2, lands
        kUnusedGroundAttack = 0xd3, // never started: standing attack at frame 3, jump-
                                    // cancellable
        kUnusedDive = 0xd4,         // never started: falling attack (vx halved, ay 0.07),
                                    // hit -> 0xd5, landing -> 0xd6
        kUnusedDiveRebound = 0xd5,  // only from 0xd4 on hit: bounces back vx -1 vy -2.4,
                                    // then falls (9)
        kUnusedDiveLanding = 0xd6,  // only from 0xd4 on landing: shake + dust effect 3,
                                    // then stand
        kThrow = 0xdc,              // C + forward or back within 30 px of a grounded, not
                                    // hit/guarding opponent
        kThrowHit = 0xdd,           // lifts the opponent over her head and slams them down
                                    // (opponent 0x67 then 0x61), DealDamage 1250
        kDashA = 0xe6,              // A during forward dash 0xa3 (not holding back)
        kDashB = 0xe7,              // B during forward dash
        kDashC = 0xe8,              // C during forward dash: lunge vx 3.0 at frame 3
        kDash2A = 0xe9,             // down + A during forward dash
        kDash2B = 0xea,             // down + B during forward dash
        kDash2C = 0xeb,             // down + C during forward dash: hop vx 1.5 vy -1.5,
                                    // hits at frame 7, lands at frame 15
        kUnusedDash2C = 0xec,       // never started: a copy of 0xeb's code
        kAirThrow = 0xf8,           // air, forward + C within 100 px of an airborne, not
                                    // hit opponent
        kAirThrowHit = 0xf9,        // carries the opponent over and throws them behind
                                    // (0x3c), DealDamage 1300, turns round, -> 0xfd
        k214A = 0xfa,               // 214A ground: hop vx 1.4 vy -1.5 at frame 6, falling
                                    // hit once vy > 0.2, lands -> 0xfd
        k214B = 0xfb,               // 214B (and 214C without the C condition): hits at
                                    // frame 2 and falling once vy > 0.8
        k214C = 0xfc,               // 214C when m_rfGauge >= 500 or m_rfBlue (costs m_rfGauge
                                    // 500/250), ground or air: higher hop vy -2.9, 60
                                    // frames of m_invulTime, bounces at frame 0x12 spawning
                                    // 0x199
        kSpecialLanding = 0xfd,     // falls with ay to the ground, landing sound 9, then
                                    // recovery frames: the end of 214, 623A/B, the air
                                    // throw and 0x136
        k236A = 0xfe,               // 236A: spawns projectile 0x196 at frame 3
        k236B = 0xff,               // 236B (and 236C without the C condition): spawns
                                    // projectile 0x197
        k236C = 0x100,              // 236C when m_rfGauge >= 500 or m_rfBlue (costs m_rfGauge
                                    // 500/250): spawns 0x1a1, a moving source of 5 ground
                                    // bursts
        k623A = 0x101,              // 623A: anti-air catch: jumps vx 1.4 vy -3.0 and grabs
                                    // an airborne opponent at frames 5-6, throws behind,
                                    // DealDamage 850, -> 0xfd
        k623C = 0x102,              // 623C when m_rfGauge >= 500 or m_rfBlue (costs m_rfGauge
                                    // 500/250): ground catch of an airborne opponent at
                                    // frame 4 -> 0x103
        k623CSlam = 0x103,          // after 0x102 catches: slams the opponent down 3 times
                                    // (DealDamage 350 each), then launches them (0x3f) for
                                    // a last hit
        k623B = 0x104,              // 623B (and 623C without the C condition): as 0x101
                                    // with a higher jump (vy -4.0), DealDamage 650
        k22A = 0x105,               // 22A: counter stance
        kCounterAttack = 0x106,     // the strike after 0x105/0x109 catch an attack, spawns
                                    // visual 0x191 in front
        kAir214A = 0x107,           // 214A in the air: stops, hops again (vy -1.5) at frame
                                    // 4, loops once, lands at frame 0x13
        kAir214B = 0x108,           // 214B in the air (and air 214C without the condition):
                                    // as 0x107, active from frame 2
        k22B = 0x109,               // 22B: the same counter stance as 0x105 (identical code
        kAir236236A = 0x12c,        // 236236 in the air, level 1 (gauge 1000): freeze,
                                    // rises, spawns column 0x1a3 at frame 9
        kAir236236B = 0x12d,        // level 2 (2000): column 0x193
        kAir236236C = 0x12e,        // level 3 (3000): column 0x1a7
        k236236A = 0x12f,           // 236236 on the ground, level 1: tosses one of
                                    // 0x19b/0x19d/0x19f (Random: 50/25/25%) each loop of
                                    // frames 4-10, 15 tosses
        k236236B = 0x130,           // level 2: 21 tosses, m_invulTime 135
        k236236C = 0x131,           // level 3: 30 tosses, m_invulTime 153
        k6321463214A = 0x132,       // 6321463214 + A (two half circles back), level 1:
                                    // pulls a grounded opponent in (m_hitByBody/m_cornerPushback) for 15
                                    // loops spawning 0x1a2
        k6321463214B = 0x133,       // level 2: stronger pull, caught -> 0x136
        k6321463214C = 0x134,       // level 3: catches airborne too, fastest pull, caught
                                    // -> 0x137
        k6321463214AThrow = 0x135,  // 4 slams (DealDamage 300 each), then jumps (vy -7) and
                                    // lands on the opponent, DealDamage 1400, spawns 0x190
        k6321463214BThrow = 0x136,  // 7 slams, launches the opponent, jumps and drops
                                    // column 0x193 at frame 0x1b, -> 0xfd
        k6321463214CThrow = 0x137,  // holds the opponent overhead for 10 passes of frames
                                    // 2-6, each spawning column 0x193 from 250 px above,
                                    // then launches them with DealDamage 1000, visual 0x191
        kLv4Strike = 0x138,         // after 0x139 counters: strike spawning visuals 0x192
                                    // and 0x191
        kLv4Counter = 0x139,        // LV4, 222D with a full gauge and HP below 3333:
                                    // counter stance, an attack met at frame 2
                                    // (m_attackResult 6) -> 0x138
        kObjImpact = 0x190,         // visual, no hits: 5C at frame 4 and 0x135's landing
        kObjStrikeEffect = 0x191,   // visual, no hits, in front at ground level: 0x106,
                                    // 0x137's end, 0x138
        kObjLv4Effect = 0x192,      // visual, no hits: 0x138 at frame 2
        kObjColumnB = 0x193,        // level-2 column segment, hits every frame: at frame 1
                                    // spawns another segment 40 px lower while above y -80,
                                    // else 0x194 on the ground
        kObjColumnBGround = 0x194,  // 0x193's ground end, no hits: spawns 0x195, plays 3
                                    // times
        kObjColumnBBlast = 0x195,   // the hitting part: frame 0 repeated 16 times, re-armed
                                    // (hitsLeft = 1) each time
        kObj236A = 0x196,           // 236A projectile: vx 1.5 slowing to 0.2, one hit
        kObj236B = 0x197,           // 236B projectile: vx 2.2 slowing to 0.4
        kObj236CBurst = 0x198,      // one ground hit, spawned 5 times by 0x1a1
        kObj214CEffect = 0x199,     // visual, no hits: 0xfc's bounce at frame 0x12
        kObj236Vanish = 0x19a,      // what 0x196/0x197 become when they hit or Misaki is
                                    // hit: animates once, no hits
        kObjTossFast = 0x19b,       // 236236's tossed item, vx 2.5-3.4 vy -1.2..-3.1
                                    // (Random): on landing or hit bounces once, spawns
                                    // 0x19c, voice 1
        kObjTossFastPiece = 0x19c,  // 0x19b's piece, no hits
        kObjTossLow = 0x19d,        // tossed item vx 1.7-3.6 vy -0.5..-1.4, piece 0x19e
        kObjTossLowPiece = 0x19e,
        kObjTossHigh = 0x19f,       // tossed item vx 1.0-1.9 vy -1.8..-3.7, piece 0x1a0
        kObjTossHighPiece = 0x1a0,
        kObj236C = 0x1a1,           // 236C: moves at vx 1.0, spawns 0x198 on the ground
                                    // each loop, gone after 5
        kObjPullEffect = 0x1a2,     // visual, no hits: every third pull loop of 0x132-0x134
        kObjColumnA = 0x1a3,        // level-1 column segment (0x12c), as 0x193, ground end
                                    // 0x1a5
        kObjColumnAGround = 0x1a5,  // 0x1a3's ground end, no hits: spawns 0x1a6, plays once
        kObjColumnABlast = 0x1a6,   // the hitting part: frame 0 repeated 9 times, re-armed
                                    // each time
        kObjColumnC = 0x1a7,        // level-3 column segment (0x12e), as 0x193, plays 3
                                    // times, ground end 0x1a9
        kObjColumnCGround = 0x1a9,  // 0x1a7's ground end, no hits: spawns 0x1aa, plays 4
                                    // times
        kObjColumnCBlast = 0x1aa,   // the hitting part: frame 0 repeated 29 times, re-armed
                                    // each time
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMisaki's own commands (ReadCommand)
    enum {
        kCmd222D = 0x5c,      // 5 2 5 2 5 2 D, within 90 frames
        kCmd236236A = 0x64,   // 236236 + A, within 90 frames
        kCmd236236B = 0x65,   // 236236 + B, within 90 frames
        kCmd236236C = 0x66,   // 236236 + C, within 90 frames
        kCmd236236D = 0x67,   // 236236 + D, within 90 frames
        kCmd63146314A = 0xa0, // 63146314 + A, within 135 frames
        kCmd63146314B = 0xa1, // 63146314 + B, within 135 frames
        kCmd63146314C = 0xa2, // 63146314 + C, within 135 frames
        kCmd63146314D = 0xa3, // 63146314 + D, within 135 frames
    };
    // END constants

    // FUNCTION: 0x5571f0
    virtual void UpdatePattern();
    // FUNCTION: 0x567900
    CMisaki(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x567a90
    virtual void Reset();
    // FUNCTION: 0x567ba0
    virtual void StartPattern();
    // FUNCTION: 0x567be0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x567c30
    virtual void Move();
    // FUNCTION: 0x567c50
    virtual void StartCommand();
    // FUNCTION: 0x56a5f0
    virtual void DrawGauge();
    // FUNCTION: 0x56a600
    virtual void PreUpdate();
    // FUNCTION: 0x56a610
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x56a640
    virtual void ReadCommand();
    // FUNCTION: 0x56b630
    virtual void CpuInput();
    // FUNCTION: 0x56f920
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch value of the current action, zeroed by StartPattern: a
                       // loop or frame counter in most actions (dash length, 623 rise
                       // loops, slam count), vx * 100 saved across 0xaa's freeze
    int m_patternVar2; // Second scratch value of the current action, zeroed by
                       // StartPattern: loop counts (5C, 236236's tosses, 6321463214's
                       // pull), vy * 100 saved in 0xaa/0xab
    int m_patternVar3; // Third scratch value of the current action, zeroed by
                       // StartPattern: a one-shot flag in 0xaa, 0x136's loop count
    int m_encasedBreakOut; // 1 while object 0x1f0 (spawned by patterns 0x53-0x56) exists,
                           // so only one is spawned; cleared when it bursts into
                           // 0x1f1/0x1f2
    int m_objectVar1[0x40]; // Per-object scratch, zeroed when the object is removed:
                            // animation-loop or spawn counter (0x195, 0x1a1, 0x1a6,
                            // 0x1aa), init flag of 0x1f1/0x1f2
    int m_objectVar2[0x40]; // Per-object scratch, zeroed when the object is removed:
                            // phase of the column objects 0x193/0x1a3/0x1a7 and their
                            // ground parts, lifetime in frames of 0x1f1/0x1f2
    int unk3348[0x40]; // indexed
};

// Mio: one of the character classes.
// SIZE: 0x3458
class CMio : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMio's own actions
    enum {
        k5A = 0xc8,                      // stance 0 A
        k5BClose = 0xc9,                 // stance 0 B within 70 px
        k5BFar = 0xca,                   // stance 0 B otherwise
        k5C = 0xcb,                      // stance 0 C
        k2A = 0xcc,                      // stance 0 2A
        k2B = 0xcd,                      // stance 0 2B, multi-hit: frames 3-5 repeat 3
                                         // times
        k2C = 0xce,                      // stance 0 2C, slides forward (vx += 1.7)
        kJumpA = 0xcf,                   // stance 0 air A
        kJumpB = 0xd0,                   // stance 0 air B
        kJumpC = 0xd1,                   // stance 0 air C, 3 hits, frames repeat once
        kFloat5A = 0xd2,                 // stance 1 A
        kFloat5BClose = 0xd3,            // stance 1 B
        kFloat5BFar = 0xd4,              // stance 1 far B, unreachable: StartCommand's far
                                         // branch starts 0xd3 instead
        kFloat5C = 0xd5,                 // stance 1 C
        kFloat2A = 0xd6,                 // stance 1 2A
        kFloat2B = 0xd7,                 // stance 1 2B
        kFloat2C = 0xd8,                 // stance 1 2C, 7 hits, frames repeat once
        kFloatJumpA = 0xd9,              // stance 1 air A
        kFloatJumpB = 0xda,              // stance 1 air B
        kFloatJumpC = 0xdb,              // stance 1 air C
        kThrow = 0xdc,                   // either stance: C + direction within 30 px of a
                                         // grounded opponent not in hit/guard states
        kThrowHold = 0xdd,               // mio_vf6.cpp sits on the opponent (pattern 0x6b),
                                         // loops frames 3-4: 100 damage per loop (frame 4,
                                         // at least every 70 frames), released after 600
                                         // frames or KO with 400 damage (opponent 0x62)
        kJump2C = 0xdf,                  // stance 0 air 2C, dives forward-down (vx = vy =
                                         // 1, accelerating)
        kJump2CLanding = 0xe0,           // mio_vf6.cpp slides to a stop, no more hits
                                         // (m_attackResult forced 3)
        k6C = 0xe1,                      // stance 0 6C, lunges (vx 2.0 at frame 3)
        kFloatJump2B = 0xe3,             // stance 1 air 2B
        kFloat4B = 0xe4,                 // stance 1 4B
        kFloatJump2C = 0xe5,             // stance 1 air 2C
        kDashA = 0xe6,                   // stance 0 A during the forward dash (0xa3)
        kDashB = 0xe7,
        kDashC = 0xe8,
        kDash2A = 0xe9,
        kDash2B = 0xea,
        kDash2C = 0xeb,                  // lunging slide (vx 2.3)
        kFloatDashA = 0xec,              // stance 1 A during the forward dash
        kFloatDashB = 0xed,
        kFloatDashC = 0xee,
        kFloatDash2A = 0xef,
        kFloatDash2B = 0xf0,
        kFloatDash2C = 0xf1,             // 7 hits, frames repeat 3 times
        kFloat5AClose = 0xf2,            // stance 1 A within 60 px
        kFloat2AClose = 0xf3,            // stance 1 2A within 60 px
        kFloatAirThrow = 0xf7,           // stance 1 air 6C near an airborne opponent
        kAirThrow = 0xf8,                // stance 0 air 6C near an airborne opponent
        kAirThrowSlam = 0xf9,            // both air throws: carries the opponent (0x64), at
                                         // frame 3 1000 damage and launch (0x3f), spawns
                                         // 0x1c2-0x1c4
        k623A = 0xfa,                    // stance 0: spinning rise (vy -1.8) then fall, 8
                                         // hits
        k623B = 0xfb,                    // vy -2.8, 12 hits
        k623C = 0xfc,                    // costs 500 of m_rfGauge (250 with m_rfBlue), 20 hits,
                                         // aura 0x1bd
        k236A = 0xfe,                    // stance 0 one hit
        k236C = 0xff,                    // stance 0, costs 500 of m_rfGauge: a column of 7
                                         // objects 0x1c0/0x1c1 in front
        k236AFollowupA = 0x100,          // 4 x 0x197 from 0x8a px in to 0x18 px, 3 hits
        k214A = 0x102,                   // stance 0: hop, then a forward slide (vx 1.7), 4
                                         // hits
        k214B = 0x103,                   // slide vx 2.4, 10 hits
        k214C = 0x104,                   // costs 500 of m_rfGauge, slide repeats up to 5 more
                                         // times (+2 hits each)
        kFloat412A = 0x105,              // stance 1, ground or air (air starts at frame 3):
                                         // rises and throws up to 7 x 0x194 forward-down
        kFloat412B = 0x106,              // up to 12 x 0x194
        kFloat412C = 0x107,              // costs 500 of m_rfGauge (in the air at frame 3), up
                                         // to 16 x 0x1bc aimed by m_patternVar3's swing
        kFloat236A = 0x108,              // stance 1: throws 0x195 (vx 6)
        kFloat236B = 0x109,              // throws 0x195 twice (frames 6 and 13)
        kFloat236C = 0x10a,              // costs 500 of m_rfGauge, turns away and throws
                                         // 0x196, which wraps around the stage
        kFloat214A = 0x10b,              // stance 1: marker 0x1c5 on the ground 0x58 px
                                         // ahead (things drop from the sky there)
        kFloat214B = 0x10c,              // the same 0x80 px ahead
        kFloat214C = 0x10d,              // the same 0xbc px ahead, no m_rfGauge cost
        kStanceChange = 0x10e,           // D on the ground, either stance: toggles m_stance
                                         // at frame 4
        k236B = 0x10f,                   // stance 0 one hit
        k236BFollowupA = 0x110,          // 4 x 0x197 then 0x198, 5 hits + 1
        k236FollowupB = 0x111,           // spawns 0x1c8 (re-hitting shot)
        kUnusedSuperToFloat = 0x12c,     // nothing starts it: 1-level super flash, sets
                                         // m_stance = 1
        kUnusedSuperToGround = 0x12d,    // nothing starts it: 1-level super flash, sets
                                         // m_stance = 0
        k236236A = 0x12f,                // stance 0 ground, 1 level: on hit at frame 3
                                         // freezes the opponent 120 frames, objects
                                         // 0x19b/0x19c/0x19d drop from y -480 around her
                                         // for 100 frames
        k236236B = 0x130,                // 2 levels, 145 frames
        k236236C = 0x131,                // 3 levels, 200 frames
        kFloat236236A = 0x132,           // stance 1, ground or air, 1 level: rises and
                                         // fires 0x1a2, bounces 16 times
        kFloat236236B = 0x133,           // 2 levels, fires 0x1a8
        kFloat236236C = 0x134,           // 3 levels, fires 0x1a9
        k214214A = 0x135,                // stance 0 ground, 1 level: 0x1be in front every
                                         // 21 frames, 8 hits
        k214214B = 0x136,                // 2 levels, every 15 frames, 15 hits
        k214214C = 0x137,                // 3 levels, one 0x1be
        kFloat214214A = 0x138,           // stance 1 ground, 1 level: volleys of 3 x 0x1aa
                                         // at frames 12/16/20/24, once
        kFloat214214B = 0x139,           // 2 levels, the volleys twice
        kFloat214214C = 0x13a,           // 3 levels, four times
        kLv4 = 0x13b,                    // stance 0: 641236C (command 0x7a) with full gauge
                                         // and HP < 3333: a rush (vx 2 at frame 7)
        kLv4ChainA = 0x13c,              // LV4 chain hit 1
        kLv4ChainB = 0x13d,              // C on hit -> 0x13e
        kLv4ChainC = 0x13e,              // A on hit -> 0x13f
        kLv4ChainA2 = 0x13f,             // B on hit -> 0x140
        kLv4ChainB2 = 0x140,             // C on hit -> 0x141
        kLv4ChainC2 = 0x141,             // 4 hits, repeats
        kLv4ChainD = 0x142,              // on hit 623C (command 0x16) -> 0x143, 236C (0xc)
                                         // -> 0x144
        kLv4Finish623C = 0x143,          // super flash, leaps (vx 4, vy -1) at frame 7, 2
                                         // hits
        kLv4Finish236C = 0x144,          // super flash, object 0x1ba in front, frames 5-6
                                         // repeat 15 times
        kFloatLv4 = 0x14a,               // stance 1: B,5,A,2,A,B (command 0x5e) with full
                                         // gauge and HP < 3333
        kFloatLv4Hit = 0x14b,            // opponent held (0x79/0x63) between x 160 and 480
                                         // while objects 0x1ab-0x1b9 gather around it
        kObjUnusedHopper = 0x190,        // nothing in Mio spawns it: rises (vx 0.5, vy
                                         // -2.8), on landing or contact bursts into
                                         // 0x191-0x193
        kObjUnusedHopperPiece1 = 0x191,  // from 0x190, plain rand velocity
        kObjUnusedHopperPiece2 = 0x192,
        kObjUnusedHopperPiece3 = 0x193,
        kObjFloat412Throw = 0x194,       // 412A/B's thrown object: vy about 1.5-2.5
                                         // (Random, downward), vx about 2, curving up
        kObjFloat236Shot = 0x195,        // vx 6
        kObjFloat236CShot = 0x196,       // as 0x195, thrown away from the opponent
        kObj236FollowupStrike = 0x197,   // static, plays once
        kObj236FollowupRiser = 0x198,    // behind her head, drifts back (vx -= 0.05) and up
                                         // (vy -= 0.02) until off-screen
        kObjFloat214ColumnBase = 0x199,  // hitting object at y 0, spawned by the lowest
                                         // 0x19a
        kObjFloat214Column = 0x19a,      // drops in from y -560: at its frame 2 spawns the
                                         // next one 160 px lower, or 0x199 once below y
                                         // -190
        kObjSuperDrop = 0x19b,           // 236236's falling object (gravity 0.045), removed
                                         // below y 100
        kObjSuperDropBounce = 0x19c,     // falls, bounces once on contact or the ground
                                         // (hitbox off)
        kObjSuperDropBreak = 0x19d,      // falls, on contact or the ground bounces and
                                         // breaks into 0x19e-0x1a1
        kObjSuperDropPiece1 = 0x19e,     // Random velocities
        kObjSuperDropPiece2 = 0x19f,
        kObjSuperDropPiece3 = 0x1a0,
        kObjSuperDropPiece4 = 0x1a1,
        kObjFloatSuperShotA = 0x1a2,     // float 236236A: hitsLeft = 7, its hit result cleared
                                         // every 3 frames (re-hits), accelerates (vx 1 +
                                         // 0.02/frame)
        kObjFloatSuperShotTrail = 0x1a3, // left behind by 0x1a8/0x1a9
        kObjUnusedShotSlow = 0x1a4,      // nothing spawns it: straight shot vx 2.3
        kObjUnusedShotMid = 0x1a5,       // nothing spawns it: vx 2.6
        kObjFloat214Summoner = 0x1a6,    // three from 0x1c5
        kObjUnusedShotFast = 0x1a7,      // nothing spawns it: vx 3.0
        kObjFloatSuperShotB = 0x1a8,     // as 0x1a2 (vx +0.03/frame), trail every 18 frames
        kObjFloatSuperShotC = 0x1a9,     // vx +0.04/frame, trail every 6 frames, sparks,
                                         // ground dust
        kObjFloat214214Shot = 0x1aa,     // flies up-forward (vx 6, vy -4.5), removed above
                                         // y -640
        kObjFloatLv4Far1 = 0x1ab,        // 0x14b frame 1, beyond the opponent
        kObjFloatLv4Far2 = 0x1ac,        // frame 2
        kObjFloatLv4Far3 = 0x1ad,        // frame 3
        kObjFloatLv4Far4 = 0x1ae,        // frame 4
        kObjFloatLv4Far5 = 0x1af,        // frame 5
        kObjFloatLv4Far6 = 0x1b0,        // frame 6
        kObjFloatLv4FarRise = 0x1b1,     // 0x1b0 flying up (vy -15) off the top
        kObjFloatLv4Near1 = 0x1b2,       // 0x14b frame 1, on Mio's side of the opponent
        kObjFloatLv4Near2 = 0x1b3,
        kObjFloatLv4Near3 = 0x1b4,
        kObjFloatLv4Near4 = 0x1b5,
        kObjFloatLv4Near5 = 0x1b6,
        kObjFloatLv4Near6 = 0x1b7,       // frame 6
        kObjFloatLv4NearRise = 0x1b8,    // 0x1b7 flying up (vy -15)
        kObjFloatLv4Floor = 0x1b9,       // on the floor (layer 0) under each figure
        kObjLv4Finish236C = 0x1ba,       // 0x144's attack, 2 hits, held while 0x144's frame
                                         // <= 5
        kObjFloatLv4Lift = 0x1bb,        // at the opponent's x when 0x1b7 ends, removed
                                         // above y -640
        kObjFloat412CThrow = 0x1bc,      // 412C's thrown object, vy = m_patternVar3, vx =
                                         // 2.8 - it/2
        kObj623CAura = 0x1bd,            // follows her (x, y - 50) during 623C until its
                                         // frame 5
        kObj214214Strike = 0x1be,        // static in front of her (x + 0x32), plays once
        kObj214214CHit = 0x1bf,          // at the opponent when 214214C hits
        kObj236CWallA = 0x1c0,           // 236C's column, 4 of 7 pieces
        kObj236CWallB = 0x1c1,           // the other 3 pieces
        kObjAirThrowImpact1 = 0x1c2,     // at the slam point, pops up and falls
        kObjAirThrowImpact2 = 0x1c3,     // plays once in place
        kObjAirThrowImpact3 = 0x1c4,     // pops up and falls
        kObjFloat214Marker = 0x1c5,      // float 214's ground marker
        kObjThrowHold = 0x1c6,           // the throw hold's object: frame 1 while Mio's
                                         // frame is 4 (the hit), gone when 0xdd passes
                                         // frame 4
        kObj236FollowupBSpark = 0x1c7,   // random spot around 0x1c8 at each of its re-hits
        kObj236FollowupBShot = 0x1c8,    // vx 1.5, re-arms its hitbox up to 6 times
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMio's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmdB5A2AB = 0x5e,  // B 5 A 2 A B, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x5736d0
    virtual void UpdatePattern();
    // FUNCTION: 0x588310
    CMio(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x5884b0
    virtual void Reset();
    // FUNCTION: 0x5885d0
    virtual void StartPattern();
    // FUNCTION: 0x588610
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x588660
    virtual void Move();
    // FUNCTION: 0x588680
    virtual void StartCommand();
    // FUNCTION: 0x58d6e0
    virtual void DrawGauge();
    // FUNCTION: 0x58dab0
    virtual void PreUpdate();
    // FUNCTION: 0x58dac0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x58daf0
    virtual void ReadCommand();
    // FUNCTION: 0x58ee20
    virtual void CpuInput();
    // FUNCTION: 0x594ea0
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch counter of the current action, 0 at each StartPattern:
                       // loop and hit counts (2B, jC, supers), the throw hold's frames
                       // (released after 600), 0x64 marks 412C started in the air;
                       // 0xaa/0xab keep vx*100 in it
    BYTE unk313c[0x3140 - 0x313c];
    double m_patternVar2; // Second scratch of the current action, 0 at each StartPattern:
                          // mostly a frame count (forward dash, throw hold 70-frame
                          // cadence, 214214 spawn cooldown); also 412's swing step,
                          // vy*100 in 0xaa/0xab, and 1.0 from object 0x1b7 to make 0x14b
                          // deal its damage
    double m_patternVar3; // Third scratch of the current action, 0 at each StartPattern:
                          // 412's aim, swung between 0 and 2.5 and read by object 0x1bc
                          // as its vy; 1.0 in 0x14b tells the LV4 objects to vanish;
                          // 0xaa's "velocity restored" flag
    int m_stance; // 0 or 1, toggled by D (0x10e) on the ground. 0: own normals/specials
                  // (623, 214, 236 with follow-ups, 641236C LV4). 1 ("float"): slower
                  // walk, slow floaty jumps, two air dashes, air D hover 0x11,
                  // 412/236/214 specials, B,5,A,2,A,B LV4. Reset to 0 each round; the
                  // gauge icon shows it
    int m_encasedBreakOut; // 1 while object 0x1f0 (spawned on entering 0x53-0x56) exists;
                           // it keeps a second one from spawning, cleared when it bursts
                           // into 0x1f1/0x1f2
    int m_objectVar1[0x40]; // Per object, cleared by RemoveObject: a one-time-init flag
                            // for most objects, the bounce flag of 0x19c, the re-hit
                            // count of 0x1c8
    int m_objectVar2[0x40]; // Per object countdown, cleared by RemoveObject: frames to
                            // the next trail object (0x1a8: 18, 0x1a9: 6), the lifetime
                            // of the 0x1f1/0x1f2 burst pieces
    int m_objectVar3[0x40]; // Per object countdown: 0x1a9's ground dust effect, every
                            // third trail
};

// Minagi: one of the character classes.
// SIZE: 0x3458
class CMinagi : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMinagi's own actions
    enum {
        k5A = 0xc8,                       // A standing
        k5BClose = 0xc9,                  // B standing within 50 px of the opponent
        k5BFar = 0xca,                    // B standing otherwise
        k5C = 0xcb,                       // C standing
        k2A = 0xcc,                       // A crouching
        k2B = 0xcd,                       // B crouching
        k2C = 0xce,                       // C crouching
        kJumpA = 0xcf,                    // A in the air
        kJumpB = 0xd0,                    // B in the air
        kJumpC = 0xd1,                    // C in the air
        kUnusedHopAttack = 0xd2,          // never started (no pattern = 0xd2 anywhere)
        kUnusedAirDive = 0xd4,            // never started
        kUnusedAirDiveRebound = 0xd5,     // only from 0xd4: bounces back vx -1 vy -2.4,
                                          // then falls (9)
        kUnusedAirDiveLanding = 0xd6,     // only from 0xd4: landing with screen shake and
                                          // dust effect 3
        kThrow = 0xdc,                    // C + left/right within 30 px of a grounded,
                                          // throwable opponent
        kThrowHit = 0xdd,                 // 0xdc connected: DealDamage(1250) at frame 4
        kDashA = 0xe6,                    // A during forward dash 0xa3 (not holding back):
                                          // slides vx 2.0
        kDashB = 0xe7,                    // B during forward dash
        kDashC = 0xe8,                    // C during forward dash
        kDash2A = 0xe9,                   // A + down during forward dash, ends crouching
        kDash2B = 0xea,                   // B + down during forward dash
        kDash2C = 0xeb,                   // C + down during forward dash, jump-cancelable
                                          // on hit
        kAirThrow = 0xf8,                 // forward + C in the air near an airborne
                                          // opponent
        kAirThrowHit = 0xf9,              // 0xf8 caught: holds the opponent (0x64, then
                                          // 0x79), spawns 0x1c5 at frame 6
        k5D = 0xfa,                       // D, no direction, Michiru idle/walking/ready:
                                          // calls Michiru to the ready stance 0x191 or out
                                          // of it
        kDRight = 0xfb,                   // D + right (m_inputX is absolute) with Michiru
                                          // idle: Michiru walks right (0x192 facing 1)
        kDLeft = 0xfc,                    // D + left with Michiru idle: Michiru walks left
                                          // (0x192 facing -1)
        k236A = 0xfd,                     // Michiru hop attack 0x194 (0x1a6 from ready)
        k236B = 0xfe,                     // Michiru 0x195 / 0x1a7
        k236C = 0xff,                     // Michiru 0x196 / 0x1a8
        k421A = 0x100,                    // Michiru anti-air jump 0x197
        k421B = 0x101,                    // Michiru 0x198
        k421C = 0x102,                    // Michiru 0x199
        k214A = 0x103,                    // Michiru vertical multi-hit jump 0x19a (0x1aa
                                          // from ready)
        k214B = 0x104,                    // Michiru 0x19b / 0x1ab
        k214C = 0x105,                    // Michiru 0x19c / 0x1ac
        k41236A = 0x106,                  // ground only, one shot at a time (m_shotState):
                                          // Minagi's own shot 0x1ad at frame 5
        k41236B = 0x107,                  // shot 0x1ae
        k41236C = 0x108,                  // shot 0x1af + follower 0x1b0
        kAir236A = 0x109,                 // 236A in the air, ends falling (9)
        kAir236B = 0x10a,
        kAir236C = 0x10b,
        kAir421A = 0x10d,
        kAir421B = 0x10e,
        kAir421C = 0x10f,
        kAir214A = 0x110,
        kAir214B = 0x111,
        kAir214C = 0x112,
        k623A = 0x113,                    // ground only: Michiru rising multi-hit 0x1d2
        k623B = 0x114,                    // Michiru 0x1d3
        k623C = 0x115,                    // Michiru 0x1d4
        k236236A = 0x12c,                 // 1 level: super flash, Michiru 0x1c6
        k236236B = 0x12d,                 // 2 levels, Michiru 0x1c7
        k236236C = 0x12e,                 // 3 levels, Michiru 0x1c8
        k214214A = 0x12f,                 // 1 level, Michiru 0x1a0 (0x1a1 from ready): a
                                          // strike that freezes the opponent
        k214214B = 0x130,                 // 2 levels, Michiru 0x1a2 / 0x1a3
        k214214C = 0x131,                 // 3 levels, Michiru 0x1a4 / 0x1a5
        kAir236236A = 0x132,
        kAir236236B = 0x133,
        kAir236236C = 0x134,
        kAir214214A = 0x135,
        kAir214214B = 0x136,
        kAir214214C = 0x137,
        k21436A = 0x138,                  // ground, 1 level: Minagi fires rising shots
                                          // 0x1b8 (every 30 frames, 4 loops), Michiru 0x1b5
        k21436B = 0x139,                  // 2 levels: shots 0x1b9 every 21 frames, 6 loops
        k21436C = 0x13a,                  // 3 levels: shots 0x1ba every 12 frames, 8 loops
        kLv4 = 0x13b,                     // 222D with full gauge, HP < 3333, Michiru not
                                          // busy: Michiru 0x1be calls down 0x1bf from the
                                          // sky
        kUnused236236A = 0x13c,           // never started
        kUnused236236B = 0x13d,           // never started
        kUnused236236C = 0x13e,           // never started
        kUnusedAir236236A = 0x13f,        // never started
        kUnusedAir236236B = 0x140,        // never started
        kUnusedAir236236C = 0x141,        // never started
        kObjMichiru = 0x190,              // Michiru idle beside Minagi, spawned by Reset 40
                                          // px behind her
        kObjMichiruReady = 0x191,         // 5D: frames 8-0x10 loop as the ready stance
                                          // (m_michiruState 3), specials started from it
                                          // use the 0x1a1/0x1a6/0x1aa... versions or skip
                                          // the windup
        kObjMichiruWalk = 0x192,          // D+left/right: walks 1.5 px/frame for 11 frames
                                          // then slows, clamped to x 20-620
        kObjMichiruKnockedBack = 0x193,   // entered from any attack when
                                          // PlayerObject::attackResult is 4 (lost a clash,
                                          // scene3.cpp) or 5 (struck): hops back vx -1 vy
                                          // -2.5, lands with shake, back to 0x190
        kObjMichiru236A = 0x194,          // hop at the opponent vx 0.9 vy -1.1, 1 hit
        kObjMichiru236B = 0x195,          // vx 1.5 vy -1.4, 1 hit
        kObjMichiru236C = 0x196,          // vx 2.0 vy -1.4, 5 hits
        kObjMichiru421A = 0x197,          // jumps up vx 0.2 vy -2.5 (hits only an airborne
                                          // opponent at frame 9), lands, then a hop-back
                                          // hit at frame 0x12
        kObjMichiru421B = 0x198,          // vx 0.5 vy -2.5
        kObjMichiru421C = 0x199,          // vx 1.3 vy -3.5
        kObjMichiru214A = 0x19a,          // jumps straight up vy -1.8, falls slowly (vy <=
                                          // 0.3), 4 hits
        kObjMichiru214B = 0x19b,          // 6 hits, same fall
        kObjMichiru214C = 0x19c,          // 12 hits, fall vy <= 0.15
        kObjMichiru214214A = 0x1a0,       // strikes in place at frame 4 (effect 0x1f)
        kObjMichiruReady214214A = 0x1a1,  // from ready: dashes 2.2 px/frame (until within
                                          // 50 px, up to 3 loops), strikes, freeze 90
                                          // frames
        kObjMichiru214214B = 0x1a2,       // freeze 75 frames
        kObjMichiruReady214214B = 0x1a3,  // dash up to 5 loops, freeze 150
        kObjMichiru214214C = 0x1a4,       // freeze 100 frames
        kObjMichiruReady214214C = 0x1a5,  // dash up to 7 loops, freeze 200
        kObjMichiruReady236A = 0x1a6,     // 0x194 started at frame 8, without the rebound
                                          // on contact
        kObjMichiruReady236B = 0x1a7,
        kObjMichiruReady236C = 0x1a8,
        kObjMichiru236Rebound = 0x1a9,    // 0x194-0x196 made contact (attackResult > 0): bounces
                                          // back at half speed, vy -2.5, lands, back to
                                          // 0x190
        kObjMichiruReady214A = 0x1aa,     // 0x19a started at frame 8, drifting back toward
                                          // Minagi while airborne
        kObjMichiruReady214B = 0x1ab,
        kObjMichiruReady214C = 0x1ac,
        kObjShot41236A = 0x1ad,           // Minagi's shot: vx 1.7 slowing to 0.8, 1 hit,
                                          // fades 30 frames after hitting, gone after 2
                                          // animation loops
        kObjShot41236B = 0x1ae,           // vx 2.1, 1 hit
        kObjShot41236C = 0x1af,           // vx 2.0 slowing to 0.6, 2 hits, 4 loops,
                                          // publishes its x in m_shotX
        kObjShot41236CFollower = 0x1b0,   // spawned with 0x1af, held at m_shotX
        kObjMichiruWalkBack = 0x1b4,      // Michiru more than 300 px from Minagi walks back
                                          // to within 200 px
        kObjMichiru21436 = 0x1b5,         // Michiru's part of the 21436 super: fires 0x1bb
                                          // every 21 frames, loops 5/8/11 times for A/B/C
        kObjShot21436A = 0x1b8,           // rising shot: vx 1.2 + Random(0,10)/10 slowing
                                          // to 0.8, rises (vy -= 0.015 per frame), 1 hit
        kObjShot21436B = 0x1b9,           // vx 1.6 + Random(0,10)/10
        kObjShot21436C = 0x1ba,           // vx 2.0 + Random(0,10)/10
        kObjMichiruShot21436 = 0x1bb,     // Michiru's rising shot, vx 0.5 + Random(0,10)/10
        kObjMichiruLv4 = 0x1be,           // Michiru's part of the LV4 (voice 2): every 18
                                          // frames spawns 0x1bf at y -480 and a random x,
                                          // 17 loops
        kObjLv4FallingShot = 0x1bf,       // falls from the sky vx 1.5 vy 3.0, 1 hit, leaves
                                          // trail objects 0x1c0-0x1c4 every 6 frames,
                                          // removed below y 200
        kObjLv4Trail0 = 0x1c0,            // trail of 0x1bf (type m_objectVar2 + 0x1c0,
                                          // minagi.cpp): plays once and is removed
        kObjLv4Trail1 = 0x1c1,
        kObjLv4Trail2 = 0x1c2,
        kObjLv4Trail3 = 0x1c3,
        kObjLv4Trail4 = 0x1c4,
        kObjAirThrowSlam = 0x1c5,         // spawned by 0xf9: carries the opponent down at
                                          // vy 3.0, on landing puts it in 0x62 and
                                          // DealDamage(1200)
        kObjMichiru236236A = 0x1c6,       // rises vx 0.5 vy -0.5 with 99 hits refreshed
                                          // every few frames, sprays 0x1cf, lands at frame
                                          // 8
        kObjMichiru236236B = 0x1c7,       // sprays 0x1cf/0x1d0
        kObjMichiru236236C = 0x1c8,       // sprays 0x1cf-0x1d1
        kObjMichiruUnused236236A = 0x1c9, // only from unused 0x13c/0x13f with Michiru
                                          // ready: hop vx 1.5 vy -1.4, 5 hits
        kObjMichiruUnused236236B = 0x1ca, // only from unused 0x13d/0x140
        kObjMichiruUnused236236C = 0x1cb, // only from unused 0x13e/0x141
        kObj236236Spray1 = 0x1cf,         // 236236's spray: moves vx 2.0, plays once
        kObj236236Spray2 = 0x1d0,         // vx 2.5
        kObj236236Spray3 = 0x1d1,         // vx 3.0
        kObjMichiru623A = 0x1d2,          // at frame 0xb rises vx 0.5 vy -2.0 with 99 hits,
                                          // lands at frame 0x10
        kObjMichiru623B = 0x1d3,          // longer fall (ay 0.025)
        kObjMichiru623C = 0x1d4,          // as B, frame 0xb held 3 more times
        kObjMichiruHeld = 0x1d5,          // while Minagi is in shared action 0x7b (the hold
                                          // Akiko's 0x13f puts the opponent in,
                                          // akiko_vf6.cpp) Michiru stops and is placed 60
                                          // px in front of her
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMinagi's own commands (ReadCommand)
    enum {
        kCmd421A = 0x46,    // 421 + A, within 45 frames
        kCmd421B = 0x47,    // 421 + B, within 45 frames
        kCmd421C = 0x48,    // 421 + C, within 45 frames
        kCmd421D = 0x49,    // 421 + D, within 45 frames
        kCmd4136A = 0x50,   // 4136 + A, within 70 frames
        kCmd4136B = 0x51,   // 4136 + B, within 70 frames
        kCmd4136C = 0x52,   // 4136 + C, within 70 frames
        kCmd4136D = 0x53,   // 4136 + D, within 70 frames
        kCmd222D = 0x5c,    // 5 2 5 2 5 2 D, within 90 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd21436A = 0xaa,  // 21436 + A, within 80 frames
        kCmd21436B = 0xab,  // 21436 + B, within 80 frames
        kCmd21436C = 0xac,  // 21436 + C, within 80 frames
        kCmd21436D = 0xad,  // 21436 + D, within 80 frames
    };
    // END constants

    // FUNCTION: 0x59c4a0
    virtual void UpdatePattern();
    // FUNCTION: 0x5a9fa0
    CMinagi(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x5aa180
    virtual void Reset();
    // FUNCTION: 0x5aa340
    virtual void StartPattern();
    // FUNCTION: 0x5aa380
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x5aa3d0
    virtual void Move();
    // FUNCTION: 0x5aa3f0
    virtual void StartCommand();
    // FUNCTION: 0x5ad500
    virtual void DrawGauge();
    // FUNCTION: 0x5ad510
    virtual void PreUpdate();
    // FUNCTION: 0x5ad520
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x5ad550
    virtual void ReadCommand();
    // FUNCTION: 0x5aea20
    virtual void CpuInput();
    // FUNCTION: 0x5b2d10
    virtual void UpdateObjects();

    int m_patternVar1; // Per-action scratch, cleared by StartPattern: a once-flag, a
                       // frame count, a spawn countdown or a loop count, whichever the
                       // current action needs
    int m_patternVar2; // Second per-action scratch, cleared by StartPattern (loop counts
                       // of the 21436 super, frames held in the air dash, a saved vy*100)
    int m_patternVar3; // Third per-action scratch, cleared by StartPattern; only 0xaa
                       // uses it, as "velocity restored"
    int m_encasedBreakOut; // 1 while the shared object 0x1f0 (spawned in actions
                           // 0x53-0x56) is alive; it clears this when it bursts into
                           // 0x1f1/0x1f2
    int m_michiruState; // What Michiru (object 0x190 and the objects it turns into) is
                        // doing, written by her object every frame: 0 idle beside Minagi,
                        // 1 starting 5D, 2 walking, 3 ready stance, 4 busy (attacking,
                        // knocked back, held). Her specials need it != 4
    int m_shotState; // The 41236 shot: 0 none, 1 in flight, 2 the C shot's hits are spent
                     // (its follower 0x1b0 then ends). 41236 needs 0
    int m_shotX; // x of the 41236C shot (0x1af), copied each frame to its follower 0x1b0
    int m_objectVar1[0x40]; // Per-object scratch, cleared by RemoveObject: first-frame
                            // flags, a 30-frame fade countdown, a freeze-applied flag,
                            // loop counts
    int m_objectVar2[0x40]; // Second per-object scratch, cleared by RemoveObject: shot
                            // init flags, dash and stance loop counts, the next LV4 trail
                            // index
    int m_objectVar3[0x40]; // Third per-object scratch, cleared by RemoveObject:
                            // animation-loop counts and spawn countdowns (21436, LV4,
                            // trails)
    BYTE unk3454[0x3458 - 0x3454];
};

// Mayu: one of the character classes.
// SIZE: 0x3448
class CMayu : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMayu's own actions
    enum {
        k5A = 0xc8,                    // 5A
        k5BClose = 0xc9,               // 5B within 70 px
        k5BFar = 0xca,                 // 5B otherwise: steps in (vx 1.2)
        k5C = 0xcb,                    // 5C, 2 hits
        k2A = 0xcc,                    // 2A
        k2B = 0xcd,                    // 2B: slides (vx 1.5), one extra loop
        k2C = 0xce,                    // 2C: long slide (vx 3.0)
        kJumpA = 0xcf,                 // j.A
        kJumpB = 0xd0,                 // j.B
        kJumpC = 0xd1,                 // j.C
        k6B = 0xd2,                    // 6B: hop (vx 1.0, vy -2.6)
        k1B = 0xd3,                    // 1B (down-back + B), checked before 2B
        kThrow = 0xdc,                 // ground throw
        kThrowHold = 0xdd,             // the ground throw: 1000 damage at frame 3
        kDashHopA = 0xe6,              // A in the air of her forward dash hop (0xa3 after
                                       // frame 5)
        kDashHopB = 0xe7,              // B in the dash hop, 2 hits
        kDashHopC = 0xe8,              // C in the dash hop
        kDashHopLanding = 0xe9,        // landing of 0xe6-0xe8
        kAirThrow = 0xf8,              // air 6C near an airborne opponent
        kAirThrowHold = 0xf9,          // the air throw: spins and slams, 1000 damage
        k41236A = 0xfa,                // 41236A (parsed as 4,1,3 + button): running grab
                                       // (vx 1.8, one extra loop)
        k41236B = 0xfb,                // 41236B: vx 2.4, two extra loops
        k41236C = 0xfc,                // 41236C (costs 500/250 of m_rfGauge): as 0xfa, on hit
                                       // the stronger throw 0xfe
        k41236Throw = 0xfd,            // the A/B grab: 500 damage (combo count not raised)
        k41236CThrow = 0xfe,           // the C grab: 1000 damage
        kUnusedAirSpin = 0xff,         // unreached: keeps 30% of vx, 9 hits, lands into
                                       // 0x102
        k236Dive = 0x100,              // A while falling in 0x104/0x107: dives (vx 0.5, vy
                                       // 3.0) into 0x101
        k236DiveLanding = 0x101,       // landing of 0x100
        k236JumpLanding = 0x102,       // landing of 0x107 (and of the unused 0xff)
        k236A = 0x103,                 // 236A on the ground: dash (vx 3.0), 3 extra loops
        k236B = 0x104,                 // 236B: jumps (vx 1.2, vy -3.3)
        k236C = 0x105,                 // 236C (costs as 0xfc): flying tackle (vx 3.0),
                                       // rebounds on contact, 4 extra loops
        kRisingStrike = 0x106,         // from 0x103 holding A, or 236 after frame 19 of
                                       // 0x110/0x112: rises (vy -3.3), 3 hits
        k236AJump = 0x107,             // from 0x103 holding B: jumps (vx 0.8, vy -3.1)
        kWallJumpDiveLanding = 0x108,  // landing of 0x10d/0x10e
        k214BDiveLanding = 0x109,      // landing of 0x11d-0x11f
        k623A = 0x10a,                 // 623A: leaping attack (vx 3, vy -3)
        k623B = 0x10b,                 // 623B: higher (vx 4, vy -4.5)
        k623C = 0x10c,                 // 623C (costs as 0xfc): vx 2, vy -4
        kWallJumpA = 0x10d,            // A after a wall jump (0x110/0x112, frames 16-19):
                                       // dives (vx 0.5, vy 3.0), turning if holding back
        kWallJumpB = 0x10e,            // B after a wall jump: diagonal dive (vx 2.2, vy
                                       // 2.2)
        kWallJumpC = 0x10f,            // C after a wall jump: 4 hits, bounces on landing
        k214A = 0x110,                 // 214A: leaps backwards (vx -3), clings to the
                                       // screen edge (AtScreenEdge) for frames 12-15, jumps
                                       // off (vx 1.5, vy -2.5)
        k214D = 0x111,                 // 214D: leaps back to the wall, jumps off low (vx
                                       // 2.2) and grabs a grounded opponent at frame 18:
                                       // 0x113
        k214C = 0x112,                 // 214C: as 0x110 but leaps forwards, turning round
                                       // at the wall
        k214DThrow = 0x113,            // the wall-jump grab: 1200 damage at frame 10
        kAir236A = 0x118,              // air 236A: dives (vx 0.7, vy 2.0)
        kAir236B = 0x119,              // air 236B: dives (vx 2.0, vy 2.0)
        kAir236C = 0x11a,              // air 236C (costs as 0xfc): dive, a hit makes it
                                       // unlimited-hit
        k41236D = 0x11b,               // 41236D: grab
        k41236DRide = 0x11c,           // stands on the opponent (at their m_pointX/Y[0])
                                       // then drops off
        k214BDiveNear = 0x11d,         // 214B dive when the opponent is within 70 px: vx
                                       // 0.5, vy 3.0
        k214BDiveMid = 0x11e,          // within 140 px: vx 2.2, vy 2.2
        k214BDiveFar = 0x11f,          // farther: vx 4.0, vy 1.5
        k214BDiveRebound = 0x120,      // any contact during 0x11d-0x11f: bounces back (vx
                                       // -0.4, vy -0.9)
        k214B = 0x121,                 // 214B: leaps back to the wall, then dives by
                                       // distance (0x11d/0x11e/0x11f)
        kRisingStrike236B = 0x122,     // from 0x104 with 236 again: same code as 0x106
        kAir236Hit = 0x123,            // follow-up of a hitting air 236A/B: 5 hits
        kUnusedSuperLv1 = 0x12c,       // unreached (no command): 1000 gauge, stepping
                                       // multi-hit rush
        kUnusedSuperLv2 = 0x12d,       // unreached: 2000 gauge, ends in a jump (pattern
                                       // 0xa)
        kUnusedSuperLv3 = 0x12e,       // unreached: 3000 gauge
        kLv4Grab = 0x12f,              // 2,3,6,9,3 + D with exactly 3000 gauge on the
                                       // ground and HP < 3333: leaping grab (vx 1.5, vy
                                       // -2.0)
        kLv4GrabClose = 0x130,         // the LV4 within 60 px: standing grab at frame 4, to
                                       // 0x132
        kLv4Slam = 0x131,              // jumps with the opponent (vy -5) and slams, 1000
                                       // damage, into 0x133
        kLv4GrabCloseHold = 0x132,     // holds the opponent, then 0x131
        kLv4Stomps = 0x133,            // bounces on the opponent for about 830 frames
                                       // (m_patternVar1), helpers 0x191/0x192 drop in at
                                       // 80/120 and stomp too, random 0x195
                                       // (CPlayer::Random)
        k641236Lv1 = 0x134,            // 641236 (6,4,1,3 + A-C) with 1 level: rising grab
                                       // (vx 2, vy -3.2) that only takes an airborne
                                       // opponent
        k641236Lv2 = 0x135,            // 2 levels: to 0x138
        k641236Lv3 = 0x136,            // 3 levels: to 0x139
        k641236Lv1Throw = 0x137,       // the air throw of 0x134: 2350 damage
        k641236Lv2Throw = 0x138,       // the throw of 0x135
        k641236Lv3Throw = 0x139,       // the throw of 0x136
        k214214Lv1 = 0x13a,            // 214214 with 1 level: steerable spin (vx up to 1.2
                                       // with 4/6), 12 hits
        k214214Lv2 = 0x13b,            // 2 levels: vx up to 1.3, unlimited hits, more loops
        k214214Lv3 = 0x13c,            // 3 levels: vx up to 1.4, more loops
        k21436Lv1 = 0x13d,             // 21436 with 1 level: dash strike (vx 3.2)
        k21436Lv1Hit = 0x13e,          // the rush of 0x13d, ends with a rising hit
        k21436Lv2 = 0x13f,             // 2 levels: vx 4.0, to 0x140
        k21436Lv2Hit = 0x140,          // the rush of 0x13f
        k21436Lv3 = 0x141,             // 3 levels: vx 4.5, to 0x142
        k21436Lv3Hit = 0x142,          // the rush of 0x141: three rising hits
        kObjUnusedShot = 0x190,        // object: never spawned: shot, vx 2.0 slowing
        kObjLv4Helper1 = 0x191,        // object: spawned at y -320 by 0x133 when
                                       // m_patternVar1 reaches 80: drops on the opponent,
                                       // 300 damage (never below 1 HP), keeps hopping with
                                       // her until m_patternVar1 > 730, then 0x193
        kObjLv4Helper2 = 0x192,        // object: as 0x191, spawned at 120, leaves as 0x194
        kObjLv4Helper1Leave = 0x193,   // object: walks off screen once m_patternVar3 is 1
        kObjLv4Helper2Leave = 0x194,   // object: hops away, then sets m_patternVar3 = 1
        kObjLv4Puff = 0x195,           // object: random one-shot animation around her
                                       // during 0x133
        kObjUnusedLv4CloseA = 0x196,   // object: never spawned: follows her x while 0x132
                                       // runs
        kObjUnusedLv4CloseB = 0x197,   // object: never spawned: as 0x196
        kObjUnusedSkyDropRise = 0x198, // object: never spawned: rises (vx 2, vy -4) to y
                                       // -680, then 0x199 over the opponent
        kObjUnusedSkyDropFall = 0x199, // object: only from 0x198: falls (vx 3, vy 6), 4
                                       // hits, 0x19a on the ground
        kObjUnusedSkyDropLand = 0x19a, // object: only from 0x199
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMayu's own commands (ReadCommand)
    enum {
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 60 frames
        kCmd23693D = 0x62,  // 2 3 6 9 3 D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 80 frames
        kCmd214214B = 0x6f, // 214214 + B, within 80 frames
        kCmd214214C = 0x70, // 214214 + C, within 80 frames
        kCmd214214D = 0x71, // 214214 + D, within 80 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
        kCmd21436A = 0xaa,  // 21436 + A, within 90 frames
        kCmd21436B = 0xab,  // 21436 + B, within 90 frames
        kCmd21436C = 0xac,  // 21436 + C, within 90 frames
        kCmd21436D = 0xad,  // 21436 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x5c8580
    virtual void UpdatePattern();
    // FUNCTION: 0x5dddf0
    CMayu(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x5ddf90
    virtual void Reset();
    // FUNCTION: 0x5de0a0
    virtual void StartPattern();
    // FUNCTION: 0x5de0e0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x5de130
    virtual void Move();
    // FUNCTION: 0x5de150
    virtual void StartCommand();
    // FUNCTION: 0x5e1060
    virtual void DrawGauge();
    // FUNCTION: 0x5e1070
    virtual void PreUpdate();
    // FUNCTION: 0x5e1080
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x5e10b0
    virtual void ReadCommand();
    // FUNCTION: 0x5e2440
    virtual void CpuInput();
    // FUNCTION: 0x5e5c30
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern; in the
                       // LV4 0x133 the frame count its helper objects also read
    int m_patternVar2; // Scratch for the current pattern, zeroed by StartPattern
    int m_patternVar3; // Scratch for the current pattern, zeroed by StartPattern; object
                       // 0x194 sets it to 1 to send 0x193 away
    int m_bounceDebrisOut; // 1 while the debris object 0x1f0 from the shared knock-back
                           // states is out
    int m_objectVar1[0x40]; // Per-object scratch (index as m_objects), zeroed by
                            // RemoveObject: "initialised" flags
    int m_objectVar2[0x40]; // Per-object scratch, zeroed by RemoveObject: debris lifetime
    int m_objectVar3[0x40]; // Per-object scratch, zeroed by RemoveObject; unused
};

// Makoto: one of the character classes.
// SIZE: 0x3450
class CMakoto : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMakoto's own actions
    enum {
        k5A = 0xc8,                   // 5A
        k5BClose = 0xc9,              // 5B within 70 px
        k5BFar = 0xca,                // 5B otherwise: spawns 0x19d at frame 4
        k5C = 0xcb,                   // 5C: spawns 0x190 at frame 6
        k2A = 0xcc,                   // 2A
        k2B = 0xcd,                   // 2B
        k2C = 0xce,                   // 2C: slides (vx 1.9), up to 4 loops, the last ones
                                      // without hits
        kJumpA = 0xcf,                // j.A
        kJumpB = 0xd0,                // j.B
        kJump2C = 0xd1,               // j.2C: spawns 0x191
        k6B = 0xd2,                   // 6B: hop (vx 0.6, vy -1.4), hits on the way down
        kJumpC = 0xd3,                // j.C: spawns 0x190 at frame 5
        kUnusedDive = 0xd4,           // unreached (no StartCommand path): air dive, ay 0.07
        kUnusedDiveRebound = 0xd5,    // only from 0xd4: bounces back (vx -1, vy -2.4)
        kUnusedDiveLanding = 0xd6,    // only from 0xd4: landing with a screen shake
        kThrow = 0xdc,                // ground throw
        kThrowHold = 0xdd,            // the ground throw: hop and slam
        kDashA = 0xe6,                // A during the forward run 0xa3 (not holding back)
        kDashB = 0xe7,                // B during the run
        kDashC = 0xe8,                // C during the run: hop (vx 1.8, vy -1.5)
        kDash2A = 0xe9,               // 2A during the run
        kDash2B = 0xea,               // 2B during the run
        kDash2C = 0xeb,               // 2C during the run: slide, up to 4 loops
        kAirThrow = 0xf8,             // air 6C near an airborne opponent
        kAirThrowHold = 0xf9,         // the air throw: carries the opponent down, 1100
                                      // damage at frame 8
        k236A = 0xfa,                 // 236A: spawns hopper 0x193 at frame 3
        k236B = 0xfb,                 // 236B: hopper 0x194
        k236C = 0xfc,                 // 236C (needs m_rfGauge >= 500 or m_rfBlue
        k214A = 0xfd,                 // 214A: tosses firecracker 0x196 at frame 4
        k214B = 0xfe,                 // 214B: firecracker 0x197
        k214C = 0xff,                 // 214C (costs as 0xfc): firecracker 0x198
        k623A = 0x100,                // 623A: leaping attack (vx 1.5, vy -1.5)
        k623B = 0x101,                // 623B: higher leap (vy -1.8)
        k623C = 0x102,                // 623C (costs as 0xfc): two leaps, the second at
                                      // frame 12
        k412A = 0x103,                // 412A (4,1,2 + button) with no bouncer out: bouncer
                                      // 0x19a and flash 0x192, sets m_bouncerOut
        k412B = 0x104,                // 412B: bouncer 0x19b
        k412C = 0x105,                // 412C (costs as 0xfc): bouncer 0x19c
        kAir214A = 0x106,             // unreached: StartCommand picks it for y < 0 inside a
                                      // branch that needs y == 0
        k236236A = 0x12c,             // 236236A (1 level): spawns 0x1a2, a slow 5-hit
                                      // object that rises then sinks
        k236236B = 0x12d,             // 236236B (1 level): 0x1a3, hovers bobbing
        k236236C = 0x12e,             // 236236C (1 level): 0x1a4, drifts forward
        k214214Lv1 = 0x12f,           // 214214 with 1 level: jumps (vy -2.4) and floats
                                      // down over the ground hit 0x19f, throwing 0x191
                                      // strikes and 0x1a5 debris
        k214214Lv2 = 0x130,           // 2 levels: as 0x12f with 0x1a0, more loops
        k214214Lv3 = 0x131,           // 3 levels: 0x1a1, more loops
        k641236Lv1 = 0x132,           // 641236 (6,4,1,3 + A-C) with 1 level: charging rush
                                      // (vx 1.9) with 0x1a7 in front, 5 hits
        k641236Lv2 = 0x133,           // 2 levels: vx 2.3, 12 hits, 0x1a7 also scatters
                                      // 0x1a8
        k641236Lv3 = 0x134,           // 3 levels: vx 2.5, 19 hits
        kLv4Heal = 0x135,             // 2,6,3 + D with exactly 3000 gauge and HP < 3333:
                                      // throws 0x1a6 up
        kLv4HealFailed = 0x136,       // from 0x135 when 0x1a6 was struck (m_patternVar2 =
                                      // 2): a loop with no effect
        kObjCStrike = 0x190,          // object: the strike of 5C and j.C, played once
        kObjJump2CStrike = 0x191,     // object: the strike of j.2C
        kObjBouncerLaunch = 0x192,    // object: flash where a 412 bouncer appears
        kObjHopper236A = 0x193,       // object: 236A: hops out (vx 0.5, vy -2.7), paces
                                      // back and forth leaving 0x22 effects, attacks within
                                      // 25 px of a grounded opponent or when 236 is pressed
                                      // again
        kObjHopper236B = 0x194,       // object: 236B hopper: vx 1.1, vy -2.2, 8 loops
        kObjHopper236C = 0x195,       // object: 236C hopper: random launch
                                      // (CPlayer::Random), 30 loops
        kObjFirecracker214A = 0x196,  // object: 214A: tossed, lands, sputters 0x199 every
                                      // 15 frames, bursts into four 0x199 after 3 loops
        kObjFirecracker214B = 0x197,  // object: 214B: as 0x196, sparks on a 21 count
                                      // decremented twice a tick (about every 11 frames),
                                      // no final burst
        kObjFirecracker214C = 0x198,  // object: 214C: as 0x196, 6 loops then four 0x199
        kObjFirecrackerSpark = 0x199, // object: rises (vy -1.5), 1 hit
        kObjBouncer412A = 0x19a,      // object: 412A: flies diagonally at 1.5 px/frame,
                                      // bouncing off the screen edges up to 3 times, 1 hit
        kObjBouncer412B = 0x19b,      // object: 412B bouncer: starts at frame 6 (another
                                      // direction)
        kObjBouncer412C = 0x19c,      // object: 412C bouncer: 3 px/frame, its hit re-armed
                                      // at each bounce
        kObj5BFar = 0x19d,            // object: spawned by far 5B
        kObj5BFarGround = 0x19e,      // object: the ground part of 0x19d
        kObj214214HitLv1 = 0x19f,     // object: unlimited-hit object on the ground under
                                      // her while 0x12f runs (until frame 0x13)
        kObj214214HitLv2 = 0x1a0,     // object: as 0x19f for 0x130
        kObj214214HitLv3 = 0x1a1,     // object: as 0x19f for 0x131
        kObj236236A = 0x1a2,          // object: 5 hits, rises (vy -0.45) then sinks, one
                                      // hit per 90 frames, removed on the ground
        kObj236236B = 0x1a3,          // object: 5 hits, hovers bobbing (vy +-0.3), 12 loops
        kObj236236C = 0x1a4,          // object: 5 hits, drifts forward (vx 0.3)
        kObj214214Debris = 0x1a5,     // object: thrown backwards with random speed
                                      // (CPlayer::Random), bounces on the ground
        kObjLv4Thrown = 0x1a6,        // object: thrown up by 0x135: falling back below y
                                      // -70 means caught (m_patternVar2 = 1)
        kObj641236Aura = 0x1a7,       // object: kept 12 px in front of her during
                                      // 0x132-0x134, leaves 0x22 effects
        kObj641236Spark = 0x1a8,      // object: from 0x1a7, played once
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMakoto's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd263D = 0x60,    // 2 6 3 D, within 60 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x5e85f0
    virtual void UpdatePattern();
    // FUNCTION: 0x5f6d90
    CMakoto(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x5f6f20
    virtual void Reset();
    // FUNCTION: 0x5f7040
    virtual void StartPattern();
    // FUNCTION: 0x5f7080
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x5f70d0
    virtual void Move();
    // FUNCTION: 0x5f70f0
    virtual void StartCommand();
    // FUNCTION: 0x5f9d20
    virtual void DrawGauge();
    // FUNCTION: 0x5f9d30
    virtual void PreUpdate();
    // FUNCTION: 0x5f9d40
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x5f9d70
    virtual void ReadCommand();
    // FUNCTION: 0x5fb040
    virtual void CpuInput();
    // FUNCTION: 0x5ff4c0
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern (loop
                       // counts, flags)
    int m_patternVar2; // Scratch for the current pattern, zeroed by StartPattern; in the
                       // LV4 0x135 object 0x1a6 writes 1 (caught) or 2 (struck)
    int m_patternVar3; // Scratch for the current pattern, zeroed by StartPattern
    int m_bounceDebrisOut; // 1 while the debris object 0x1f0 from the shared knock-back
                           // states is out
    int m_bouncerOut; // 1 while a 412 bouncer (0x19a-0x19c) is out; 412 can't start again
                      // until it is gone
    int m_objectVar1[0x40]; // Per-object scratch (index as m_objects), zeroed by
                            // RemoveObject: loop counts, "initialised" flags
    int m_objectVar2[0x40]; // Per-object scratch, zeroed by RemoveObject: timers (effect
                            // trails, spark and rehit intervals)
    int m_objectVar3[0x40]; // Per-object scratch, zeroed by RemoveObject: loop count of
                            // object 0x1a3
    BYTE unk344c[0x3450 - 0x344c];
};

// Mai: one of the character classes.
// SIZE: 0x3458
class CMai : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CMai's own actions
    enum {
        k5A = 0xc8,                         // 5A
        k5BClose = 0xc9,                    // 5B within 70 px of the opponent
        k5BFar = 0xca,                      // 5B otherwise
        k5C = 0xcb,                         // 5C
        k2A = 0xcc,                         // 2A
        k2B = 0xcd,                         // 2B
        k2C = 0xce,                         // 2C
        kJumpA = 0xcf,                      // j.A
        kJumpB = 0xd0,                      // j.B
        kJumpC = 0xd1,                      // j.C
        k6A = 0xd2,                         // 6A: spawns 0x19f behind/above her
        k6B = 0xd3,                         // 6B: spawns 0x1a0
        k6C = 0xd4,                         // 6C: spawns 0x1a1
        k6AAwakened = 0xd5,                 // 6A while m_familiarState == 4 (awakened):
                                            // costs 1000 of m_familiarGauge, also jump-
                                            // cancels on guard
        k6BAwakened = 0xd6,                 // 6B while awakened, costs 1000 of
                                            // m_familiarGauge
        k6CAwakened = 0xd7,                 // 6C while awakened, costs 1000 of
                                            // m_familiarGauge
        k4C = 0xd8,                         // 4C (also 3C when 2C cannot start): sliding
                                            // kick, vx 3.0 at frame 3 then slows
        kThrow = 0xdc,                      // C + direction within 30 px of a grounded
                                            // opponent
        kThrowHold = 0xdd,                  // the ground throw: carries the opponent over
                                            // her, 1200 damage at frame 4
        kDashHopA = 0xe6,                   // unreached: no StartCommand path (A during the
                                            // dash hop starts j.A)
        kDashHopB = 0xe7,                   // unreached, as 0xe6
        kDashHopC = 0xe8,                   // C while airborne (y < -10) in her forward
                                            // dash hop 0xa3
        kAirThrow = 0xf0,                   // air 6C within 100 px of an airborne opponent
        kAirThrowHold = 0xf1,               // the air throw: 1300 damage at frame 3, lands
                                            // into 0xd
        kAir623A = 0xfa,                    // air 623A: halves the momentum and falls (ay
                                            // 0.025), shorter frames in the air
        kAir623B = 0xfb,                    // air 623B, ay 0.035
        kAir623C = 0xfc,                    // air 623C: costs 500 of m_rfGauge (250 with
                                            // m_rfBlue) or 1000 of m_familiarGauge when
                                            // awakened
        kAir623Landing = 0xfd,              // landing recovery of 0xfa-0xfc
        k412A = 0xfe,                       // 412A (4,1,2 + button): sinks and reappears 60
                                            // px in front of the opponent
        k412B = 0xff,                       // 412B: reappears 180 px in front of the
                                            // opponent
        k412C = 0x100,                      // 412C: costs 500 of m_rfGauge (or 1000 of
                                            // m_familiarGauge when awakened)
        k214A = 0x101,                      // 214A: summons the familiar to strike 40 px
                                            // ahead (object 0x19c), or when awakened a
                                            // burst 0x1a8 80 px ahead for 1000 of
                                            // m_familiarGauge
        k214B = 0x102,                      // 214B: 0x19c 120 px ahead, or 0x1a8 160 px
                                            // ahead when awakened
        k214C = 0x103,                      // 214C: 0x19c 200 px ahead, or 0x1a8 240 px
                                            // ahead when awakened
        kSummonFamiliar = 0x104,            // D (not 2D) on the ground with no familiar:
                                            // summons object 0x191 at her (6D: 60 px ahead,
                                            // 4D: 60 px behind) with m_familiarGauge 10000
        k412AHeld = 0x105,                  // 412A with A held over 30 frames: a forward
                                            // strike, vx 2.0
        k412BHeld = 0x106,                  // 412B with B held over 30 frames: drops from
                                            // 100 px above, 100 px in front of the opponent
        k236A = 0x107,                      // 236A with no familiar: summons object 0x1ac
                                            // (familiar dash, 4 hits, then recharges)
        k236B = 0x108,                      // 236B: object 0x1ad (dash
        k236C = 0x109,                      // 236C (needs m_rfGauge >= 500 or m_rfBlue): object
                                            // 0x1ae (16 hits
        k623A = 0x10a,                      // 623A with no familiar: object 0x1b0 80 px
                                            // ahead (its attack 0x1c5, then it stays out)
        k623B = 0x10b,                      // 623B: 0x1b0 160 px ahead
        k623C = 0x10c,                      // 623C: 0x1b0 240 px ahead
        kRecallFamiliar = 0x10d,            // D with the familiar out (m_familiarState 1):
                                            // the familiar leaves (0x194) and recharges
                                            // fast
        k236236Lv1 = 0x12f,                 // 236236 with 1 level: dash slash (vx 5)
        k236236Lv2 = 0x130,                 // 236236B/C with 2 levels: vx 7
        k236236Lv3 = 0x131,                 // 236236C with 3 levels: vx 10
        k236236Lv1Flurry = 0x132,           // the level 1 follow-up: the frozen opponent
                                            // takes 2400 at the end
        k236236Lv2Flurry = 0x133,           // level 2 follow-up, 3200
        k236236Lv3Flurry = 0x134,           // level 3 follow-up, 4500
        kLv4Awaken = 0x135,                 // 236236D with 3 levels, HP < 3333 and no
                                            // familiar: spawns 0x1ab, which puts her in the
                                            // awakened mode (m_familiarState 4)
        kUnusedFlurry = 0x138,              // unreached: a fourth flurry like 0x134 (4200
                                            // damage, launches higher)
        kUnusedSuperLv1 = 0x13b,            // unreached: stands while an old familiar super
                                            // (object 0x199, 1000 gauge) runs
        kUnusedSuperLv2 = 0x13c,            // unreached, as 0x13b (2000 gauge)
        kUnusedSuperLv3 = 0x13d,            // unreached, as 0x13b (3000 gauge)
        k214214Lv1 = 0x13e,                 // 214214 with 1 level and no familiar: summons
                                            // 0x1b6, which fires one 5-hit shot 0x1b8
        k214214Lv1Familiar = 0x13f,         // 214214 with 1 level and the familiar out: the
                                            // familiar (0x191 -> 0x1b7) fires 2 shots 0x1b9
                                            // and pays the gauge itself
        k214214Lv2 = 0x140,                 // 2 levels, no familiar: 0x1ba fires a 7-hit
                                            // shot 0x1bc
        k214214Lv2Familiar = 0x141,         // 2 levels with the familiar out: 0x1bb fires 4
                                            // shots 0x1b9 at two heights
        k214214Lv3 = 0x142,                 // 3 levels, no familiar: 0x1be fires a 10-hit
                                            // shot 0x1c0
        k214214Lv3Familiar = 0x143,         // 3 levels with the familiar out: 0x1bf fires 6
                                            // shots 0x1b9 at random heights
                                            // (CPlayer::Random)
        kAwakened236236D = 0x144,           // 236236D while awakened with HP < 3333 (no
                                            // gauge check: the mode holds m_gauge at 0)
        kAwakened236236DHit = 0x145,        // the finisher: 3500 + 0.15 * m_familiarGauge
                                            // damage, spawns screen object 0x1c2, ends the
                                            // mode
        kObjFamiliar = 0x191,               // object: the familiar out and idle: sets
                                            // m_familiarState 1, faces the opponent, takes
                                            // the D commands (236D 0x1af, 214D 0x1c3, 412D
                                            // 0x1b4, 22D 0x19e) and the 214214 supers
        kObjFamiliarKnockedOut = 0x192,     // object: struck (attackResult 4/5) or Mai hit: flies
                                            // off, then recharge 1200
        kObjFamiliarExpire = 0x193,         // object: m_familiarGauge ran out: recharge
                                            // 1200 at the normal rate
        kObjFamiliarRecall = 0x194,         // object: dismissed by 0x10d: recharge 1200 at
                                            // the fast rate
        kObjFamiliarUnusedFly = 0x196,      // object: never spawned: flies forward (vx 2.5,
                                            // vy 0.9), takes 5000 of m_familiarGauge, back
                                            // to 0x191
        kObjFamiliarUnusedShoot = 0x197,    // object: never spawned: fires homing shot
                                            // 0x198 at frame 5
        kObjUnusedHomingShot = 0x198,       // object: only from 0x197: re-aims at the
                                            // opponent up to 3 times
        kObjFamiliarUnusedSuper = 0x199,    // object: never spawned: the old super of
                                            // 0x13b-0x13d, freezes the screen and drops
                                            // 3/5/10 objects 0x19a/0x1a7/0x1a9
        kObjUnusedDropLv1 = 0x19a,          // object: only from 0x199: falls, bursts on the
                                            // ground as 0x19b
        kObjUnusedBurstLv1 = 0x19b,         // object: only from 0x19a
        kObjFamiliar214 = 0x19c,            // object: the familiar of 214A/B/C: rises
                                            // forward at -60 degrees, 6 hits, then recharge
                                            // (fast)
        kObjFamiliarUnusedWalk = 0x19d,     // object: never spawned: walks forward, then
                                            // becomes 0x19e
        kObjFamiliar22D = 0x19e,            // object: 22D with the familiar out: flies
                                            // forward at -30 degrees, 6 hits, then recharge
        kObj6A = 0x19f,                     // object: the strike 6A spawns, played once
        kObj6B = 0x1a0,                     // object: the strike 6B spawns
        kObj6C = 0x1a1,                     // object: the strike 6C spawns
        kObjAir623C = 0x1a2,                // object: the strike air 623C spawns at frame 7
        kObjFlurryOverlay1 = 0x1a3,         // object: screen object (0, 20) while 0x134
                                            // runs, then shrinks away
        kObjFlurryOverlay2 = 0x1a4,         // object: screen object (0, 38), as 0x1a3
        kObjUnusedArc1 = 0x1a5,             // object: never spawned: thrown in an arc (vx
                                            // 1.1, vy -1)
        kObjUnusedArc2 = 0x1a6,             // object: never spawned: thrown in an arc (vx
                                            // 0.8, vy -0.5), removed off screen
        kObjUnusedDropLv2 = 0x1a7,          // object: only from 0x199: falls, becomes 0x1a8
                                            // on the ground
        kObjGroundBurst = 0x1a8,            // object: a 1-hit burst on the ground: 214A/B/C
                                            // while awakened, and the landing of 0x1a7
        kObjUnusedDropLv3 = 0x1a9,          // object: only from 0x199: falls, becomes 0x1aa
        kObjUnusedBurstLv3 = 0x1aa,         // object: only from 0x1a9
        kObjAwakening = 0x1ab,              // object: spawned by the LV4 0x135: freezes the
                                            // opponent, then sets m_familiarState 4 and
                                            // m_familiarGauge 10000
        kObjFamiliar236A = 0x1ac,           // object: 236A: dashes (vx 1.7), 4 hits, then
                                            // recharge (fast)
        kObjFamiliar236B = 0x1ad,           // object: 236B: dashes, 4 hits, then stays out
                                            // as 0x191
        kObjFamiliar236C = 0x1ae,           // object: 236C: dashes (vx 2.0), 16 hits, then
                                            // stays out
        kObjFamiliar236D = 0x1af,           // object: 236D with the familiar out: dashes
                                            // (vx 1.3), 8 hits, then recharge
        kObjFamiliar623 = 0x1b0,            // object: 623A/B/C: appears 80/160/240 px
                                            // ahead, spawns 0x1c5 at frame 2, then stays
                                            // out as 0x191
        kObjFamiliarUnusedRush = 0x1b3,     // object: never spawned: like 0x1c3 with vx
                                            // 5.25
        kObjFamiliar412D = 0x1b4,           // object: 412D with the familiar out: spawns
                                            // its strike 0x1c6 at frame 4, then recharge
                                            // (fast)
        kObjUnusedShot1 = 0x1b5,            // object: never spawned: slow shot (vx 0.7, 3
                                            // hits)
        kObjFamiliar214214Lv1 = 0x1b6,      // object: summoned by 0x13e: fires 0x1b8 at
                                            // frame 7, then recharge
        kObjFamiliarOut214214Lv1 = 0x1b7,   // object: the familiar out, from 0x191 at 0x13f
                                            // frame 3: takes 1000 gauge, fires 2 shots
                                            // 0x1b9
        kObj214214ShotLv1 = 0x1b8,          // object: vx 2.8, 5 hits
        kObj214214ShotFamiliar = 0x1b9,     // object: the shots of 0x1b7/0x1bb/0x1bf: vx
                                            // 4.0 slowing to 1.0, 1 hit
        kObjFamiliar214214Lv2 = 0x1ba,      // object: summoned by 0x140: fires 0x1bc
        kObjFamiliarOut214214Lv2 = 0x1bb,   // object: from 0x191 at 0x141: takes 2000
                                            // gauge, 4 shots 0x1b9 at y-27/y-87
        kObj214214ShotLv2 = 0x1bc,          // object: vx 3.5, 7 hits
        kObjUnusedShot2 = 0x1bd,            // object: never spawned: shot vx 1.3, 2 hits
        kObjFamiliar214214Lv3 = 0x1be,      // object: summoned by 0x142: fires 0x1c0
        kObjFamiliarOut214214Lv3 = 0x1bf,   // object: from 0x191 at 0x143: takes 3000
                                            // gauge, 6 shots 0x1b9 at random heights
        kObj214214ShotLv3 = 0x1c0,          // object: vx 4.2, 10 hits
        kObjUnusedShot3 = 0x1c1,            // object: never spawned: shot vx 1.9, 3 hits
        kObjAwakenedFinisherScreen = 0x1c2, // object: screen object at 0x145 frame 1
        kObjFamiliar214D = 0x1c3,           // object: 214D with the familiar out: dashes
                                            // (vx 4.0) until 120 px from the opponent, 1
                                            // hit, then recharge (rate 4)
        kObjFamiliar623Hit = 0x1c5,         // object: the attack of 0x1b0, 2 hits
        kObjFamiliar412DHit = 0x1c6,        // object: the attack of 0x1b4, 1 hit
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CMai's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x607930
    virtual void UpdatePattern();
    // FUNCTION: 0x6163b0
    CMai(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x616570
    virtual void Reset();
    // FUNCTION: 0x6166c0
    virtual void StartPattern();
    // FUNCTION: 0x616700
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x616750
    virtual void Move();
    // FUNCTION: 0x616770
    virtual void StartCommand();
    // FUNCTION: 0x619d50
    virtual void DrawGauge();
    // FUNCTION: 0x61a620
    virtual void PreUpdate();
    // FUNCTION: 0x61a830
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x61a860
    virtual void ReadCommand();
    // FUNCTION: 0x61b9a0
    virtual void CpuInput();
    // FUNCTION: 0x61f750
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern: loop
                       // counts or flags, by pattern
    int m_patternVar2; // Scratch for the current pattern, zeroed by StartPattern (hold-
                       // frame counts, flags)
    int m_patternVar3; // Scratch for the current pattern, zeroed by StartPattern (0x104:
                       // 1 summon ahead, 2 behind)
    int m_familiarState; // Mai's familiar: 0 none, 1 out and idle (object 0x191), 2
                         // acting, 3 recharging, 4 awakened (after the LV4)
    int m_familiarGauge; // The familiar's gauge DrawGauge draws: time left out of 10000
                         // while out or awakened, recharge countdown from 1200 in state
                         // 3; Vf8 drains it
    int m_familiarSummoned; // 1 after the D summon (0x104) until some familiar ends or
                            // the recharge ends; read only by CpuInput
    int m_familiarRate; // Vf8 takes 1 a frame from m_familiarGauge (2 while recharging),
                        // 4 more at rate 1, 1 less at rate 2, 1 more at 3 and 4; rate 1
                        // also marks a fresh summon for object 0x191
    int m_bounceDebrisOut; // 1 while the debris object 0x1f0 from the shared knock-back
                           // states is out
    int m_objectVar1[0x40]; // Per-object scratch (index as m_objects), zeroed by
                            // RemoveObject: loop counts, "initialised" flags
    int m_objectVar2[0x40]; // Per-object scratch, zeroed by RemoveObject: second counter
                            // (lifetimes, speeds)
    int m_objectVar3[0x40]; // Per-object scratch, zeroed by RemoveObject: aim angle /
                            // timer of object 0x198
};

// Kanna: one of the character classes.
// SIZE: 0x3458
class CKanna : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CKanna's own actions
    enum {
        k5A = 0xc8,
        k5BClose = 0xc9,             // B within 110 px
        k5BFar = 0xca,               // kanna.cpp
        k5C = 0xcb,                  // kanna.cpp
        k2A = 0xcc,
        k2B = 0xcd,                  // kanna.cpp
        k2C = 0xce,
        kJumpA = 0xcf,               // kanna.cpp
        kJumpB = 0xd0,               // kanna.cpp
        kJumpC = 0xd1,               // kanna.cpp
        kUnused6B = 0xd2,            // unused, empty in kanna.pat
        kUnused6C = 0xd3,            // unused, no data
        kUnusedJump2C = 0xd4,        // unused, no data
        kUnusedJump2CRebound = 0xd5, // unused, no data
        kUnusedJump2CLanding = 0xd6, // unused, no data
        kUnusedThrow = 0xdc,         // unused: Kanna's StartCommand has no throw
        kUnusedThrowHit = 0xdd,      // DealDamage(1250)
        kUnusedDashA = 0xe6,         // unused dash attacks (Kanna has no 0xa3 check), same
                                     // order as Akane's 0xe6-0xeb
        kUnusedDashB = 0xe7,
        kUnusedDashC = 0xe8,
        kUnusedDash2A = 0xe9,
        kUnusedDash2B = 0xea,
        kUnusedDash2C = 0xeb,        // hop (1.5, -1.5) as Akane's 0xeb
        kUnusedF9 = 0xf9,            // unused stub, no data
        k236 = 0xfa,                 // 236A/B/C on the ground
        k236C = 0xfb,                // 236C on the ground, costs m_rfGauge
        kAir236 = 0xfd,              // 236A/B/C in the air
        k623 = 0x100,                // 623A/B/C on the ground
        k623C = 0x101,               // costs m_rfGauge
        k623Landing = 0x103,
        k214A = 0x107,               // kanna.cpp
        k214B = 0x108,               // kanna.cpp
        k214C = 0x109,               // kanna.cpp
        k41236 = 0x10a,              // 41236A/B on the ground
        k41236C = 0x10b,             // costs m_rfGauge
        k236236A = 0x12c,            // 236236A, 3 levels, ground or air
        k236236B = 0x12f,            // 236236B on the ground, 3 levels
        kAir236236B = 0x132,         // 236236B in the air, 3 levels
        kLv4 = 0x135,                // 236236C at full gauge, HP < 3333, ground
        kLv4Miss = 0x136,            // 0x135 without a hit by frame 0x24
        kObj214A = 0x190,            // rises (vy -3), loops once, drops (vy 7)
        kObj214B = 0x191,            // impact 125 px ahead
        kObj214C = 0x192,            // impact 200 px ahead
        kObj214Impact = 0x193,       // 1 hit, shakes the screen
        kObj236Effect = 0x194,       // 236's effect behind Kanna, no hit of its own
        kObj41236Flash = 0x195,      // 41236A/B frame 7
        kObj41236Shot = 0x196,       // 99 hits, vx 3 slowing to 1.2
        kObjUnused197 = 0x197,       // never spawned: slow 1-hit shot, contact -> 0x19a
        kObjUnused198 = 0x198,       // never spawned
        kObj41236ShotEnd = 0x199,
        kObjUnused19a = 0x19a,       // only from 0x197
        kObjUnused19b = 0x19b,       // never spawned
        kObjUnused19c = 0x19c,       // only from 0x19b
        kObjUnused19d = 0x19d,       // never spawned
        kObjUnused19e = 0x19e,       // only from 0x19d
        kObj236236ALead = 0x19f,     // 236236A frame 7, flies back (-3, 0.5), 1 hit
        kObjFeatherSlow = 0x1a0,     // 236236A: vx 1-2 from Random
        kObjFeatherFast = 0x1a1,     // vx 3.5-4.5
        kObj236236BBurst = 0x1a2,    // kept at Kanna +-10 px while 0x12f lasts
        kObjUnused1a3 = 0x1a3,       // never spawned
        kObj5BCloseEffect = 0x1a4,   // follows Kanna, removed when 0xc9 ends, held in
                                     // hitstop
        kObj5BFarEffect = 0x1a5,
        kObj2BEffect = 0x1a6,
        kObjJumpBEffect = 0x1a7,
        kObj5CEffect = 0x1a8,
        kObjJumpCEffect = 0x1a9,
        kObjAir236236B = 0x1aa,      // attached to Kanna, 1 hit (4500 dmg in .pat)
        kObj236CFlash = 0x1ab,       // on its frame 4 spawns 0x1ac
        kObj236CBeam = 0x1ac,        // kept at the view's left edge, 60 px above 0x1ab
        kObj41236CEmitter = 0x1ad,   // frame 4: six 0x1ae
        kObj41236CHoming = 0x1ae,    // angles +-140/165/170, steers to the opponent's
                                     // height, trail 0x1af
        kObj41236CTrail = 0x1af,     // also the homing shot's end
        kObjLv4Attached3 = 0x1b0,    // 0x135 frame 0x20, follows Kanna
        kObjLv4Attached4 = 0x1b1,    // 0x135 frame 0x2b, follows Kanna, ends at frame 0x37
        kObjLv4Attached1 = 0x1b2,    // 0x135 frame 5
        kObjLv4Attached2 = 0x1b3,    // 0x135 frame 0x10
        kObjLv4Screen1 = 0x1b4,      // screen-space, frame 0x33
        kObjLv4Screen2 = 0x1b5,
        kObjLv4Screen3 = 0x1b6,
        kObjLv4Sky = 0x1b7,          // 160 px above Kanna when frame 0x35 hits
        kObjLv4Rise = 0x1b8,         // frame 0x37, 150 px above Kanna
        kObj623Effect = 0x1b9,       // spawned by 0x100/0x101
        kObjLv4Sky1 = 0x1ba,
        kObjLv4Sky2 = 0x1bb,
        kObjLv4Sky3 = 0x1bc,
        kObjLv4Sky4 = 0x1bd,
        kObjLv4Sky5 = 0x1be,
        kObjLv4Sky6 = 0x1bf,
        kObjLv4RiseSide = 0x1c0,     // three with 0x1b8
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CKanna's own commands (ReadCommand)
    enum {
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 55 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 55 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 55 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 55 frames
        kCmd236236A = 0x64, // 236236 + A, within 70 frames
        kCmd236236B = 0x65, // 236236 + B, within 70 frames
        kCmd236236C = 0x66, // 236236 + C, within 70 frames
        kCmd236236D = 0x67, // 236236 + D, within 70 frames
    };
    // END constants

    // FUNCTION: 0x667570
    virtual void UpdatePattern();
    // FUNCTION: 0x675c80
    CKanna(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x675e20
    virtual void Reset();
    // FUNCTION: 0x675f40
    virtual void StartPattern();
    // FUNCTION: 0x675f80
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x675fd0
    virtual void Move();
    // FUNCTION: 0x6763c0
    virtual void StartCommand();
    // FUNCTION: 0x677e10
    virtual void DrawGauge();
    // FUNCTION: 0x677e20
    virtual void PreUpdate();
    // FUNCTION: 0x677e30
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x677e60
    virtual void ReadCommand();
    // FUNCTION: 0x678c30
    virtual void CpuInput();
    // FUNCTION: 0x67cf50
    virtual void UpdateObjects();

    int m_patternVar1;
    int m_patternVar2;
    int m_patternVar3; // Scratch value of the current pattern (loop counts; the angle
                       // index of 41236C's homing shots); zeroed by StartPattern
    int m_encasedBreakOut; // 1 from a hit reaction 0x53-0x56 spawning object 0x1f0 until
                           // it bursts
    int m_airMoveDelay; // Ticks a jump or air move must last before the next air move can
                        // start: 60, set by the constructor and Reset
    int m_cpuHitCooldown; // CpuInput only: 180 while Kanna is hit or guarding
                          // (0x32-0xa0), then counts down; most CPU ground attacks wait
                          // for 0. Not initialised
    int m_cpuAirPause; // CpuInput only: set to 180 at random in the air, counts down; the
                       // CPU does not steer in the air until 0. Not initialised
    int m_objectVar1[0x40]; // indexed
    int m_objectVar2[0x40]; // indexed
    int m_objectVar3[0x40]; // Per object scratch value (a "started" flag, a timer);
                            // zeroed by RemoveObject
    BYTE unk3454[0x3458 - 0x3454];
};

// Ayu: one of the character classes.
// SIZE: 0x3450
class CAyu : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CAyu's own actions
    enum {
        k5A = 0xc8,
        k5BClose = 0xc9,            // B within 70 px
        k5BFar = 0xca,
        k5C = 0xcb,
        k2A = 0xcc,
        k2B = 0xcd,
        k2C = 0xce,
        kJumpA = 0xcf,
        kJumpB = 0xd0,
        kJumpC = 0xd1,
        k6B = 0xd2,                 // B standing holding forward
        k6C = 0xd3,                 // C standing holding forward
        kJump2C = 0xd4,             // C in the air holding down
        kJump2CRebound = 0xd5,      // bounces back (-1, -2.4)
        kJump2CLanding = 0xd6,      // shake + dust
        kThrow = 0xdc,
        kThrowHit = 0xdd,           // DealDamage(1200)
        kUnusedE6 = 0xe6,           // unused air attack
        kUnusedE7 = 0xe7,
        kUnusedE8 = 0xe8,
        kAirThrow = 0xf0,
        kAirThrowHit = 0xf1,        // DealDamage(1100)
        kUnusedF9 = 0xf9,           // unused stub, see CAkane 0xf9
        k623A = 0xfa,               // 623A, ground or air
        k623C = 0xfb,               // 623C on the ground, costs m_rfGauge
        k623B = 0xfc,               // 623B
        kUnusedFd = 0xfd,           // unused: charge
        kUnusedFe = 0xfe,           // unused, no data: like 0xfd, hits grow by 2 per loop
        kUnusedFf = 0xff,           // unused: 0xfd's D cancel
        k214A = 0x100,              // 214A, ground or air
        k214B = 0x101,              // 214B
        k214C = 0x102,              // 214C, costs m_rfGauge
        k214Rebound = 0x103,        // 0x100/0x101 made contact on the way down: bounces
                                    // back
        k236A = 0x104,              // 236A on the ground
        k236B = 0x105,              // 236B
        k236C = 0x106,              // 236C, costs m_rfGauge
        k236End = 0x107,            // end of 0x104-0x106 on contact or after the loops:
                                    // slides, shake, 1 hit
        kAir623C = 0x10b,           // 623C in the air, costs m_rfGauge
        k214214A = 0x12c,           // 1 level, ground
        k214214B = 0x12d,           // 2 levels, ground
        k214214C = 0x12e,           // 3 levels, ground
        kAir214214A = 0x12f,        // 1 level, air
        kAir214214B = 0x130,        // 2 levels, air
        kAir214214C = 0x131,        // 3 levels, air
        k641236A = 0x132,           // 1 level
        k641236B = 0x133,           // 2 levels
        k641236C = 0x134,           // 3 levels
        k236236A = 0x13b,           // 1 level
        k236236B = 0x13c,           // 2 levels
        k236236C = 0x13d,           // 3 levels
        kLv4 = 0x13e,               // A,N,A,4,B,C (cmd 0x5d) at full gauge, HP < 3333
        kObj623Shot = 0x190,        // 623A/B: flies up-forward (2, -4), 3 hits
        kObjDashFeatherA = 0x191,   // dash feathers of 0xa3-0xa6, plain rand (ayu.cpp
        kObjDashFeatherB = 0x192,
        kObjUnused193 = 0x193,      // never spawned
        kObjUnused194 = 0x194,      // never spawned
        kObj214214AShot = 0x195,    // decelerating, 99 hits, plays twice
        kObj641236Burst2 = 0x196,   // 641236B/C, kept at Ayu +-10 px while the super lasts
        kObj641236Burst3 = 0x197,   // 641236C's last
        kObj623CShot = 0x198,       // up-forward, 8 hits
        kObjAir623CShot = 0x199,    // down-forward (2, 4), 4 hits
        kObjAir623CImpact = 0x19a,  // 1 hit
        kObjUnusedLob = 0x19b,      // never spawned: lobbed (vx 0.6, 1.4 holding forward),
                                    // D -> 0x1a6, lands/guarded -> 0x1a7 (no cases)
        kObjUnusedStill = 0x19c,    // never spawned: stays 6 loops then 0x1a7
        kObjUnusedFall = 0x19d,     // never spawned: falls, clears unk3148
        kObjLv4Aura = 0x19e,        // follows Ayu during 0x13e
        kObjLv4Burst = 0x19f,       // 1 hit
        kObjLv4FeatherFast = 0x1a0, // vx 2.5-3.5 from Random (ayu.cpp
        kObjLv4FeatherSlow = 0x1a1, // vx 1-2
        kObj236236Front = 0x1a2,    // kept in front of Ayu during 0x13b-0x13d
        kObj214214BShot = 0x1a3,    // decelerating, 99 hits, plays 4 times
        kObj214214CShot = 0x1a4,    // starts at m_shotSpeed/10, plays 5 times
        kObj641236Burst1 = 0x1a5,   // 641236A/C, kept at Ayu +-10 px
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CAyu's own commands (ReadCommand)
    enum {
        kCmdA5A4BC = 0x5d,  // A 5 A 4 B C, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x6d93f0
    virtual void UpdatePattern();
    // FUNCTION: 0x6e8130
    CAyu(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x6e82f0
    virtual void Reset();
    // FUNCTION: 0x6e8420
    virtual void StartPattern();
    // FUNCTION: 0x6e8460
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x6e84b0
    virtual void Move();
    // FUNCTION: 0x6e84d0
    virtual void StartCommand();
    // FUNCTION: 0x6eaf80
    virtual void DrawGauge();
    // FUNCTION: 0x6eaf90
    virtual void PreUpdate();
    // FUNCTION: 0x6eafa0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x6eafd0
    virtual void ReadCommand();
    // FUNCTION: 0x6ec160
    virtual void CpuInput();
    // FUNCTION: 0x6ef410
    virtual void UpdateObjects();

    int m_patternVar1;
    int m_patternVar2;
    int m_patternVar3; // Scratch value of the current pattern (loop counts, a "done once"
                       // flag); zeroed by StartPattern
    int m_encasedBreakOut; // 1 from a hit reaction 0x53-0x56 spawning object 0x1f0 until
                           // it bursts
    int unk3148;
    int m_shotSpeed; // vx * 10 that the next 214214C shot (object 0x1a4) starts with:
                     // 45/30/15 on the ground, 50/35/20 in the air
    int m_objectVar1[0x40]; // indexed
    int m_objectVar2[0x40]; // indexed
    int m_objectVar3[0x40]; // Per object scratch value (a "started" flag, a replay
                            // count); zeroed by RemoveObject
};

// Akane: one of the character classes.
// SIZE: 0x3450
class CAkane : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CAkane's own actions
    enum {
        k5A = 0xc8,                    // A standing
        k5BClose = 0xc9,               // B standing within 70 px
        k5BFar = 0xca,                 // B standing otherwise
        k5C = 0xcb,                    // C standing
        k2A = 0xcc,                    // A crouching
        k2B = 0xcd,                    // B crouching
        k2C = 0xce,                    // C crouching
        kJumpA = 0xcf,                 // A in the air
        kJumpB = 0xd0,                 // B in the air
        kJumpC = 0xd1,                 // C in the air
        kUnusedAirDive = 0xd2,         // unused: frame 6 vx 1 vy 1, 3 hits, frames 7-9 loop
                                       // until landing
        kJump6C = 0xd3,                // C in the air holding forward, not down
        kUnusedRebound = 0xd5,         // unused, no data: hop back (-1, -2.4) to 9
        kUnusedDiveLanding = 0xd6,     // unused, no data: shake + dust, then stand/crouch
        kThrow = 0xdc,                 // C + a direction within 30 px of a grounded
                                       // opponent not in 0x32-0x9c
        kThrowHit = 0xdd,              // 0xdc connected on frame 1: the opponent is held
                                       // (0x6b), then hit (1 hit, 1000 dmg in .pat) and
                                       // released into 0x32
        kDashA = 0xe6,                 // A during the forward dash 0xa3, not holding back
        kDashB = 0xe7,                 // B during 0xa3
        kDashC = 0xe8,                 // C during 0xa3
        kDash2A = 0xe9,                // A during 0xa3 holding down
        kDash2B = 0xea,                // B during 0xa3 holding down
        kDash2C = 0xeb,                // C during 0xa3 holding down
        kAirThrow = 0xf0,              // air C+6 within 100 px of an airborne opponent not
                                       // in hitstun
        kAirThrowHit = 0xf1,           // 0xf0 connected: carries the opponent, slams,
                                       // DealDamage(1200)
        kUnusedF9 = 0xf9,              // unused stub found in all four of these classes:
                                       // freezes the opponent 60 ticks (m_freezeTime), effect
                                       // 0x28
        k236A = 0xfa,                  // 236A
        k236B = 0xfb,                  // 236B
        k236C = 0xfc,                  // 236C, costs 500 of m_rfGauge
        k623A = 0xfd,                  // 623A
        k623B = 0xfe,                  // 623B
        k623C = 0xff,                  // 623C, costs m_rfGauge
        k214A = 0x100,                 // 214A
        k214B = 0x101,                 // 214B
        k214C = 0x102,                 // 214C
        k412A = 0x103,                 // 412A, ground or air
        k412B = 0x104,                 // 412B
        k412C = 0x105,                 // 412C
        kLeap236A = 0x106,             // 236A during a 214/412 leap: throws three 0x190
                                       // down-forward
        kLeap236B = 0x107,             // 236B during a leap: three 0x191
        kLeap236C = 0x108,             // 236C during a leap, costs m_rfGauge: three 0x192
        kLeapC = 0x109,                // C during a leap: dives (1, 2), slides on landing
        kLeap2C = 0x10a,               // C+2 during a 412 leap: drops straight down (vy
                                       // 2.1), 3 hits
        kLeap4C = 0x10b,               // C+4 during a 214 leap: air grab
        kLeap4CHit = 0x10c,            // 0x10b connected: carries and slams,
                                       // DealDamage(1000)
        kLeapLanding = 0x10d,          // landing after 0x101, 0x103-0x108: plain recovery
        kLeapLandingAttack = 0x10e,    // landing after 0x100/0x102: steps forward (vx 1), 1
                                       // hit on frame 1
        kAir236A = 0x10f,              // 236A in the air
        kAir236B = 0x110,              // 236B in the air
        kAir236C = 0x111,              // 236C in the air, costs m_rfGauge
        k236236A = 0x12c,              // 236236A, 1 level
        k236236B = 0x12d,              // 236236B, 2 levels
        k236236C = 0x12e,              // 236236C, 3 levels
        k214214A = 0x12f,              // 214214A, 1 level
        k214214B = 0x130,              // 214214B, 1 level
        k214214C = 0x131,              // 214214C, 1 level
        k641236A = 0x132,              // 641236A, 1 level, no helper out
        k641236B = 0x133,              // 641236B, 2 levels
        k641236C = 0x134,              // 641236C, 3 levels
        kLv4 = 0x135,                  // A,N,A,6,B,C (cmd 0x5a) at full gauge, HP < 3333
        kUnusedGrabSuper = 0x137,      // unused 3-level grab, grab on frame 5 -> 0x138
        kUnusedGrabSuperHit = 0x138,   // 0x137 connected: objects 0x1a5-0x1ab fly at the
                                       // held opponent
        kUnusedAirSuper = 0x13b,       // unused, no data: 1 level, hops back throwing 0x192
        kObjLeapShotA = 0x190,         // thrown three at a time by 0x106: (4, 2), stops on
                                       // hit/landing, knocked off -> 0x194
        kObjLeapShotB = 0x191,         // by 0x107: (4, 1.3)
        kObjLeapShotC = 0x192,         // by 0x108 and 0x13b: (4, 2)
        kObjLeapShotPopped = 0x193,    // 0x192 after being guarded: pops up (0.2, -3.5) and
                                       // falls, then 0x194
        kObjLeapShotKnocked = 0x194,   // a 0x190-0x193 knocked away: falls off, removed
                                       // below the floor
        kObj236236Rise = 0x195,        // spawned by 0x12c-0x12e above Akane, flies up (vy
                                       // -8)
        kObj236236FallSlow = 0x196,    // falls at the opponent (2, 8), stops at a random
                                       // height (Random)
        kObj236236FallMid = 0x197,     // falls (4, 8)
        kObj236236FallFast = 0x198,    // falls (7, 8)
        kObjHelper236C = 0x199,        // the helper of 236C, runs at 1.5 facing back
        kObjHelperHit = 0x19a,         // any helper hit by the opponent: thrown up (-0.8,
                                       // -3), lands, then 0x19d
        kObjHelperDrop = 0x19b,        // spawned when 0x199 is hit: something falls off it
        kObj214214 = 0x19c,            // 214214's object: drifts forward
        kObjHelperFlee = 0x19d,        // a hit helper jumps away (-6, -4)
        kObjHelper236A = 0x19e,        // 236A's helper, flies in (2.3, 0.8)
        kObjHelper236B = 0x19f,        // 236B's helper, runs (vx 3)
        kObjHelper236BAttack = 0x1a0,  // 236B's helper attacking
        kObjHelper641236A = 0x1a1,     // 641236A's helper: lands, attacks in 3 loops, sets
                                       // m_helperState 1 to free Akane
        kObjHelper641236B = 0x1a2,     // 641236B's helper: 6 loops, 99 hits
        kObjHelper641236C = 0x1a3,     // 641236C's helper: on hit freezes the opponent 120
                                       // ticks, spawns 0x1a4, flies up
        kObjHelper641236CHold = 0x1a4, // drifts with 0x1a3 until the opponent's freeze ends
        kObjRushFront = 0x1a5,         // unused super 0x138: crosses at the opponent from
                                       // in front, vx -10
        kObjRushFrontMid = 0x1a6,      // (-9, -1.8), 64 px lower start
        kObjRushFrontHigh = 0x1a7,     // (-9.6, -3.8)
        kObjRushBack = 0x1a8,          // from behind, vx 10
        kObjRushBackMid = 0x1a9,       // (9.8, -2.46)
        kObjRushBackHigh = 0x1aa,      // (10, -4)
        kObjRushBelow = 0x1ab,         // rises under the opponent, vy -10
        kObjLv4Finish = 0x1ac,         // screen-space picture spawned when kLv4 KOs
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CAkane's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmdA5A6BC = 0x5a,  // A 5 A 6 B C, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x6f2f20
    virtual void UpdatePattern();
    // FUNCTION: 0x7039d0
    CAkane(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x703b70
    virtual void Reset();
    // FUNCTION: 0x703c90
    virtual void StartPattern();
    // FUNCTION: 0x703cd0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x703d20
    virtual void Move();
    // FUNCTION: 0x703d40
    virtual void StartCommand();
    // FUNCTION: 0x706a80
    virtual void DrawGauge();
    // FUNCTION: 0x706a90
    virtual void PreUpdate();
    // FUNCTION: 0x706aa0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x706ad0
    virtual void ReadCommand();
    // FUNCTION: 0x707e50
    virtual void CpuInput();
    // FUNCTION: 0x70bc00
    virtual void UpdateObjects();

    int m_patternVar1;
    int m_patternVar2;
    int m_patternVar3; // Scratch value of the current pattern (loop counts, tick
                       // counters, vx * 100 saved over a freeze); zeroed by StartPattern
    int m_helperState; // 0 no helper; 1 a 236 helper is on screen, or a 641236 helper has
                       // let Akane go; 2 a 641236 helper is attacking and Akane holds her
                       // pose. 236 and 641236 need 0
    int m_encasedBreakOut; // 1 from a hit reaction 0x53-0x56 spawning object 0x1f0 until
                           // it bursts into 0x1f1/0x1f2
    int m_objectVar1[0x40]; // indexed
    int m_objectVar2[0x40]; // indexed
    int m_objectVar3[0x40]; // Per object scratch value (flags, a random stop height);
                            // zeroed by RemoveObject
    BYTE unk344c[0x3450 - 0x344c];
};

// Akiko: one of the character classes.
// SIZE: 0x3468
class CAkiko : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CAkiko's own actions
    enum {
        k5A = 0xc8,
        k5BClose = 0xc9,                  // B within 70 px
        k5BFar = 0xca,
        k5C = 0xcb,
        k2A = 0xcc,
        k2B = 0xcd,                       // akiko.cpp
        k2C = 0xce,
        kJumpA = 0xcf,
        kJumpB = 0xd0,                    // akiko.cpp
        kJumpC = 0xd1,                    // akiko.cpp
        kUnused6B = 0xd2,                 // unused
        kUnused6C = 0xd3,                 // unused
        kUnusedJump2C = 0xd4,             // unused
        kUnusedJump2CRebound = 0xd5,      // unused
        kUnusedJump2CLanding = 0xd6,      // unused
        kThrow = 0xdc,
        kThrowHit = 0xdd,                 // 0xdc connected: spawns 0x1a7, which pushes the
                                          // opponent into the wall
        kUnusedE6 = 0xe6,                 // unused air attack (vx 0.5, gravity 0.03)
        kUnusedE7 = 0xe7,
        kUnusedE8 = 0xe8,
        kAirThrow = 0xf0,
        kAirThrowHit = 0xf1,              // 0xf0 connected: spawns 0x1a8, which carries the
                                          // opponent down
        kUnusedF9 = 0xf9,                 // unused stub, see CAkane 0xf9
        k236A = 0xfa,                     // akiko.cpp
        k236B = 0xfb,                     // akiko.cpp
        k236C = 0xfc,                     // costs m_rfGauge
        k623A = 0xfd,                     // akiko.cpp
        k623CFinish = 0xfe,               // last of the 623C chain, from 0x102 after 3
                                          // repeats
        k623Second = 0xff,                // second lunge, from 0xfd/0x100 on hit + 623A/B
        k623B = 0x100,                    // akiko.cpp
        k623C = 0x101,                    // costs m_rfGauge
        k623CRepeat = 0x102,              // 623C again on hit, up to 3 more times, then
                                          // 0xfe
        k623Finish = 0x103,               // third hit of the 623A/B chain, from 0xff
        k214A = 0x104,                    // akiko.cpp
        k214B = 0x105,                    // akiko.cpp
        k214C = 0x106,                    // costs m_rfGauge
        k41236A = 0x107,                  // akiko.cpp
        k41236AHit = 0x108,               // 0x107 connected: DealDamage(1500), spawns
                                          // 0x19d/0x19e
        k41236B = 0x109,                  // akiko.cpp
        k41236BHit = 0x10a,               // DealDamage(1500)
        k41236C = 0x10b,                  // costs m_rfGauge
        k41236CHit = 0x10c,               // DealDamage(1750)
        k236236A = 0x12c,                 // 1 level
        k236236B = 0x12d,                 // 2 levels
        k236236C = 0x12e,                 // 3 levels
        k214214A = 0x12f,                 // 1 level
        k214214AHit = 0x130,              // DealDamage(1000)
        k214214B = 0x131,                 // 2 levels
        k214214BHit = 0x132,              // seals dashes, specials and supers (m_sealLevel = 2)
        k214214C = 0x133,                 // 3 levels
        k214214CHit = 0x134,              // also seals jumps (m_sealLevel = 3)
        k641236A = 0x135,                 // 1 level, no slow-down running
        k641236B = 0x136,                 // 2 levels
        k641236C = 0x137,                 // 3 levels
        kLv4 = 0x13e,                     // 2,N,A,2,N,B,C (cmd 0x5d) at full gauge, HP <
                                          // 3333
        kLv4Hit = 0x13f,                  // 0x13e connected on frame 10: DealDamage(5500)
        kObjShotFlash = 0x190,            // static at Akiko's hand with every 236 volley
        kObjShotBurst = 0x191,            // a small shot's end
        kObjSmallShotStraight = 0x192,    // 236A third volley: vx 1.25-1.7, small vy, trail
                                          // 0x19b
        kObjSmallShotSpread = 0x193,      // 236A first volley (5): vy 1.0 down to -0.9,
                                          // bursts on the floor
        kObjSmallShotAccel = 0x194,       // 236A second volley (3): starts slow (vx 0-0.45)
                                          // and speeds up
        kObjBigShotBurst = 0x195,         // end of 0x196/0x197, and popped by 0x1b1
        kObjBigShotStraight = 0x196,      // 236B/C: one shot 70 px ahead
        kObjBigShotSpread = 0x197,        // 236B/C: three with random vy
        kObjBigShotLob = 0x198,           // 236B/C: lobbed (gravity 0.015)
        kObjLobImpact = 0x199,            // 0x198's impact, 1 hit
        kObjUnused19a = 0x19a,            // never spawned
        kObjShotTrail = 0x19b,            // left every 5 ticks by the 236 shots
        kObj41236SlamA = 0x19d,           // spawned at Akiko when 0x108/0x10a/0x10c slam
        kObj41236SlamB = 0x19e,           // spawned with 0x19d
        kObj214ALauncher = 0x19f,         // 214A
        kObj214AField = 0x1a0,            // static field: drains the opponent's m_rfGauge by 1
                                          // every 2 ticks within 50 px, 15 cycles
        kObj214Particle = 0x1a1,          // particles of the 214 fields, positions from
                                          // Random
        kObj214BLauncher = 0x1a2,         // 214B -> 0x1a3
        kObj214BField = 0x1a3,            // drifts at 0.3, 30 cycles
        kObj214CLauncher = 0x1a4,         // 214C -> 0x1a5
        kObj214CField = 0x1a5,            // moves at 1.8, 12 hits, 30 cycles
        kObj236236ARunIn = 0x1a6,         // 236236A: crosses from 360 px behind at vx 5
        kObjThrowPusher = 0x1a7,          // 0xdd: pushes the opponent back at 3 until they
                                          // hit a wall, then launch + DealDamage(1200)
        kObjAirThrowSlam = 0x1a8,         // 0xf1: carries the opponent down (vy 3),
                                          // DealDamage(1200) on landing
        kObjLv4Effect = 0x1a9,            // 0x13f frame 1, at the opponent
        kObjLv4Screen = 0x1aa,            // 0x13f frame 2, screen-space
        kObj236236BRunIn = 0x1ab,
        kObj236236CRunIn = 0x1ac,
        kObjDebrisRising = 0x1ad,         // 236236 explosion: random upward angle (Random),
                                          // slows to 0.5
        kObjDebrisSparking = 0x1ae,       // any angle, stops
        kObjDebris = 0x1af,               // any angle, slow
        kObjDebrisRisingSparking = 0x1b0, // upward, fast
        kObjDebrisRisingBursting = 0x1b1, // 236236C only
        kObjDebrisSmall = 0x1b2,          // same code as 0x1af
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CAkiko's own commands (ReadCommand)
    enum {
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 60 frames
        kCmd25A25BC = 0x5d, // 2 5 A 2 5 B C, within 90 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x712500
    virtual void UpdatePattern();
    // FUNCTION: 0x7219a0
    CAkiko(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x721ba0
    virtual void Reset();
    // FUNCTION: 0x721d10
    virtual void StartPattern();
    // FUNCTION: 0x721d50
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x721da0
    virtual void Move();
    // FUNCTION: 0x721dc0
    virtual void StartCommand();
    // FUNCTION: 0x724780
    virtual void DrawGauge();
    // FUNCTION: 0x7256b0
    virtual void PreUpdate();
    // FUNCTION: 0x725bd0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x725c00
    virtual void ReadCommand();
    // FUNCTION: 0x726f10
    virtual void CpuInput();
    // FUNCTION: 0x729cc0
    virtual void UpdateObjects();

    int m_patternVar1;
    int m_patternVar2;
    int m_patternVar3; // Scratch value of the current pattern (loop counts, 236C's random
                       // volley, the grab's pull); zeroed by StartPattern
    int m_encasedBreakOut; // 1 from a hit reaction 0x53-0x56 spawning object 0x1f0 until
                           // it bursts
    int m_sealTime; // Ticks left of 214214's seal on the opponent, 1000 when it hits; at
                    // 0 Vf8 clears the opponent's m_sealLevel. DrawGauge draws it as a bar
    int m_slowTick; // Tick count in the 641236 slow-down: the opponent is frozen on every
                    // other tick (2..36), a voice at 36, then 0
    int m_nextShot; // The volley 236A/B throws next: 0, 1, 2, then 0 again; only Reset
                    // zeroes it
    int m_slowCountOnes; // Ones digit of the slow-down's counter, which rises by 4 -
                         // m_timerSuper per tick to 999; drawn with anims[0x28]
    int m_slowCountTens; // Tens digit of the slow-down's counter
    int m_slowCountHundreds; // Hundreds digit of the slow-down's counter
    int m_slowEndTime; // Ticks since the slow-down's counter passed 999 (0 while it
                       // counts); the slow-down ends at 180
    int m_objectVar1[0x40]; // indexed
    int m_objectVar2[0x40]; // indexed
    int m_objectVar3[0x40]; // Per object scratch value (trail countdown, a random angle);
                            // zeroed by RemoveObject
    BYTE unk3464[0x3468 - 0x3464];
};

// Nanase: one of the character classes.
// SIZE: 0x3470
class CNanase : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CNanase's own actions
    enum {
        k5A = 0xc8,                      // A
        k5BClose = 0xc9,                 // B within 70 px
        k5BFar = 0xca,                   // B otherwise
        k5C = 0xcb,                      // C
        k2A = 0xcc,                      // 2A
        k2B = 0xcd,                      // 2B
        k2C = 0xce,                      // 2C
        kJumpA = 0xcf,                   // air A
        kJumpB = 0xd0,                   // air B
        kJumpC = 0xd1,                   // air C, 3 hits
        kHopAttackUnused = 0xd2,         // unused here (EXNanase's 6C): hop vx 1.4, vy
                                         // -1.5, 1 hit
        kUnusedD3 = 0xd3,                // unused ground normal: gauge +30, jump-
                                         // cancellable on hit
        kAirDiveUnused = 0xd4,           // unused dive: on hit -> 0xd5, on landing -> 0xd6
        kAirDiveRebound = 0xd5,          // only from 0xd4: bounce back vx -1, vy -2.4
        kAirDiveLanding = 0xd6,          // only from 0xd4: landing with ShakeScreen(3)
        kThrow = 0xdc,                   // C + direction within 30 px, opponent standing
        kThrowHit = 0xdd,                // DealDamage(1200), opponent ends in 0x62
        kDashA = 0xe6,                   // A during forward dash 0xa3
        kDashB = 0xe7,                   // B during 0xa3
        kDashC = 0xe8,                   // C during 0xa3
        kDash2A = 0xe9,                  // 2A during 0xa3
        kDash2B = 0xea,                  // 2B during 0xa3
        kDash2C = 0xeb,                  // 2C during 0xa3
        kAirThrow = 0xf8,                // air C + forward within 100 px, opponent airborne
        kAirThrowHit = 0xf9,             // DealDamage(1400)
        k41236A = 0xfa,                  // command grab: 41236A (41236 any button once the
                                         // sword is thrown)
        kGrabHold = 0xfb,                // lifts and tosses the opponent
        kGrab236B = 0xfc,                // smash of the tossed opponent: DealDamage(4500 x
                                         // (y/80 + 1)) if y in (-80, 0)
        k236A = 0xfd,                    // 236A
        k236B = 0xfe,                    // 236B
        k236C = 0xff,                    // 236C with m_rfGauge
        k623A = 0x100,                   // 623A (also in the air from frame 9)
        k623B = 0x101,                   // 623B
        k623C = 0x102,                   // 623C with m_rfGauge
        k214A = 0x103,                   // 214A
        k214B = 0x104,                   // 214B
        k214C = 0x105,                   // 214C with m_rfGauge
        kGrab236A = 0x106,               // 236A during 0xfb: one more hit
        k41236B = 0x107,                 // 41236B while armed
        k41236C = 0x108,                 // 41236C while armed
        kUnused109 = 0x109,              // unused, nanase2 table only
        kUnused10a = 0x10a,              // unused, nanase2 table only
        kPickUpSword = 0x12b,            // D standing within 30 px of the sword on the
                                         // floor (0x194): back to nanase.pat
        k214214Lv1 = 0x12c,              // 214214 1 level, armed
        k214214Lv2 = 0x12d,              // 2 levels
        k214214Lv3 = 0x12e,              // 3 levels
        k236236Lv1 = 0x12f,              // 236236 1 level, sword thrown (m_swordThrown == 1)
        k236236Lv2 = 0x130,              // 2 levels, sword thrown
        k236236Lv3 = 0x131,              // 3 levels, sword thrown
        kGrabLv4 = 0x132,                // 236C during 0xfb with gauge 3000 and HP <= 3333:
                                         // LV4 flash (effects 0x46+0x47), DealDamage(6500 x
                                         // (y/80 + 1))
        kLv4 = 0x133,                    // 41364136 + D, gauge 3000, HP < 3333, armed
        k41364136Lv1 = 0x134,            // 41364136 + button, 1 level, armed
        k41364136Lv2 = 0x135,            // 2 levels
        k41364136Lv3 = 0x136,            // 3 levels
        kObjSwordThrown = 0x190,         // 623A/B's sword: flies vx 3, vy 1.8, re-hits
                                         // every 15 frames, 99 hits
        kObjSwordTrail = 0x191,          // flies with the sword, effect 0x22 every frame,
                                         // gone when it lands
        kObjSwordImpact = 0x192,         // where the sword lands: hits once (frame 1),
                                         // sparkles 0x1ab
        kObjSwordBounce = 0x193,         // the sword bouncing off the floor, walls at
                                         // 20/620
        kObjSwordOnFloor = 0x194,        // the sword lying on the floor until she picks it
                                         // up
        kObjRock1 = 0x195,               // rock from 0x1ad: random rise, hits, breaks into
                                         // 3 pebbles on landing or after a hit
        kObjRock2 = 0x196,               // the same, other speed
        kObjRock3 = 0x197,               // the same
        kObjRock4 = 0x198,               // the same
        kObjPebble = 0x199,              // small piece: random hop, one bounce, then gone
        kObjPebble2 = 0x19a,             // as 0x199, faster
        kObj214Impact = 0x19b,           // one-shot at 214's strike and at each 0x1ad loop
        kObjGrabLv4Fx = 0x19c,           // one-shot of 0x132
        kObjSwordThrownC = 0x19d,        // 623C's sword: as 0x190
        kObjSwordImpactC = 0x19e,        // hits
        kObjSuperSwordLv1 = 0x1a3,       // 0x134's sword: vx 2, vy 1, hits at frames 1/5
        kObjSuperSwordLv2 = 0x1a4,       // 0x135's: vx 2.4, vy 0.8
        kObjSuperSwordSplash = 0x1a5,    // side splashes of 0x1a4/0x1ac's landing, sparkles
                                         // 0x1ab
        kObjSuperSwordImpactLv1 = 0x1a6, // 0x1a3's landing: hits once
        kObjSuperSwordTrail = 0x1a7,     // glued to m_superSwordX/Y, hits on frames 1/5,
                                         // gone when the sword lands (m_superSwordY == 0)
        kObjSuperSwordBounce = 0x1a8,    // the super sword bouncing up after landing, then
                                         // -> 0x194
        kObjSuperSwordImpactLv2 = 0x1a9, // 0x1a4's landing: hits once
        kObjSuperSwordImpactLv3 = 0x1aa, // 0x1ac's landing: hits once
        kObjSparkle = 0x1ab,             // spawns effect 0x22 every 2 frames until its
                                         // animation ends
        kObjSuperSwordLv3 = 0x1ac,       // 0x136's: vx 2.4, vy 0.4
        kObj214CShockwave = 0x1ad,       // 214C: moves vx 2, each of its 4 loops spawns
                                         // 0x19b, 4 pebbles and 4 rocks
        kObjLv4Aura = 0x1af,             // LV4 power-up: counts m_lv4Time down
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CNanase's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,        // 412 + A, within 45 frames
        kCmd412B = 0x29,        // 412 + B, within 45 frames
        kCmd412C = 0x2a,        // 412 + C, within 45 frames
        kCmd412D = 0x2b,        // 412 + D, within 45 frames
        kCmd41236A = 0x46,      // 41236 + A (read as 413), within 90 frames
        kCmd41236B = 0x47,      // 41236 + B (read as 413), within 90 frames
        kCmd41236C = 0x48,      // 41236 + C (read as 413), within 90 frames
        kCmd41236D = 0x49,      // 41236 + D (read as 413), within 90 frames
        kCmd236236A = 0x64,     // 236236 + A, within 90 frames
        kCmd236236B = 0x65,     // 236236 + B, within 90 frames
        kCmd236236C = 0x66,     // 236236 + C, within 90 frames
        kCmd236236D = 0x67,     // 236236 + D, within 90 frames
        kCmd214214A = 0x6e,     // 214214 + A, within 90 frames
        kCmd214214B = 0x6f,     // 214214 + B, within 90 frames
        kCmd214214C = 0x70,     // 214214 + C, within 90 frames
        kCmd214214D = 0x71,     // 214214 + D, within 90 frames
        kCmd4123641236A = 0x96, // 4123641236 + A (read as 4136413), within 135 frames
        kCmd4123641236B = 0x97, // 4123641236 + B (read as 4136413), within 135 frames
        kCmd4123641236C = 0x98, // 4123641236 + C (read as 4136413), within 135 frames
        kCmd4123641236D = 0x99, // 4123641236 + D (read as 4136413), within 135 frames
    };
    // END constants

    // FUNCTION: 0x46d970
    virtual void UpdatePattern();
    // FUNCTION: 0x47c130
    // UpdatePattern while the nanase2 tables are in use: the same pattern numbers, unarmed
    void UpdatePattern2();
    // FUNCTION: 0x48a720
    CNanase(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x48a9b0
    virtual void Reset();
    // FUNCTION: 0x48ab00
    ~CNanase();
    // FUNCTION: 0x48abb0
    virtual void Load();
    // FUNCTION: 0x48abf0
    virtual void StartPattern();
    // FUNCTION: 0x48ac30
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x48ac80
    virtual void Move();
    // FUNCTION: 0x48aca0
    virtual void StartCommand();
    // FUNCTION: 0x48d940
    // Reads nanase\nanase2.pat into m_anims2 and m_patterns2, the same format as
    // CPlayer::LoadPatterns
    void LoadPatterns2();
    // FUNCTION: 0x48dd00
    virtual void DrawGauge();
    // FUNCTION: 0x48e140
    // p1 1: switches anims (hers and every object's) and m_patterns to the nanase2 tables;
    // p1 0: back to nanase.pat
    void UsePatterns2(char p1);
    // FUNCTION: 0x48e250
    virtual void PreUpdate();
    // FUNCTION: 0x48e260
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x48e290
    virtual void ReadCommand();
    // FUNCTION: 0x48f690
    virtual void CpuInput();
    // FUNCTION: 0x492db0
    virtual void UpdateObjects();
    // FUNCTION: 0x497540
    // UpdateObjects while the nanase2 tables are in use; also runs the thrown sword until
    // it lies on the floor (0x194)
    void UpdateObjects2();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern
                       // (counters, one-shot flags, saved vx * 100)
    int m_patternVar2; // The same, a second one
    int m_patternVar3; // The same, a third one; 1 when 623C was started in the air, so it
                       // charges m_rfGauge although it skips frame 0
    int m_encasedBreakOut; // 1 while an object 0x1f0 (spawned entering 0x53-0x56) waits
                           // to burst into particles
    int m_lv4Time; // Frames left of the LV4 power-up (0x133, object 0x1af): 3000 at the
                   // start; DrawGauge draws it as a bar; while > 0 she takes half damage
    int m_objectState[0x40]; // Per object: a small state or counter of the object's own
                             // code; zeroed by RemoveObject
    int m_objectTimer[0x40]; // Per object: a timer of the object's own code (re-hit
                             // interval of the thrown sword, particles' lifetime)
    int unk334c[0x40]; // indexed
    int m_swordThrown; // 1 from the moment 623 or a 41364136 super throws her sword until
                       // she picks it up (pattern 0x12b); kept equal to m_usingPatterns2
    int m_superSwordX; // x of the flying super sword (0x1a3/0x1a4/0x1ac), for its trail
                       // 0x1a7
    int m_superSwordY; // y of the flying super sword, 0 once it has landed (the trail
                       // then removes itself)
    char m_usingPatterns2; // 1 while anims and m_patterns are the nanase2.pat tables
                           // (sword thrown); UpdatePattern and UpdateObjects then run
                           // UpdatePattern2 and UpdateObjects2
    BYTE unk3459[0x345c - 0x3459];
    PTR32(EffectAnim) m_anims2;    // the second animation and pattern tables
    PTR32(PatternData) m_patterns2;
    int m_anims1; // The nanase.pat animations (anims as Load set it), held as an int so
                  // UsePatterns2(0) and the destructor can restore them
    int m_patterns1; // The nanase.pat frame data, likewise
    BYTE unk346c[0x3470 - 0x346c];
};

// Nagamori: one of the character classes.
// SIZE: 0x34b0
class CNagamori : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CNagamori's own actions
    enum {
        k5A = 0xc8,
        k5BClose = 0xc9,          // B within 70 px
        k5BFar = 0xca,
        k5C = 0xcb,
        k2A = 0xcc,
        k2B = 0xcd,
        k2C = 0xce,               // 2C with the shot in hand
        kJumpA = 0xcf,
        kJumpB = 0xd0,
        kJumpC = 0xd1,            // nagamori.cpp
        kHopAttackUnused = 0xd2,  // unused
        kAirDiveUnused = 0xd4,    // unused
        kAirDiveRebound = 0xd5,   // only from 0xd4
        kAirDiveLanding = 0xd6,   // only set by the unused 0xd4
        k2CShotOut = 0xd7,        // 2C while the 236 shot is out (m_shotState > 0)
        k6B = 0xd8,               // 6B
        kThrow = 0xdc,
        kThrowHit = 0xdd,         // DealDamage(75) then DealDamage(800), opponent to 0x61
        kDashA = 0xe6,
        kDashB = 0xe7,
        kDashC = 0xe8,
        kDash2A = 0xe9,
        kDash2B = 0xea,
        kDash2C = 0xeb,
        kAirThrow = 0xf8,
        kAirThrowHit = 0xf9,
        k623A = 0xfa,             // 623A (ground or air)
        k623B = 0xfb,             // 623B
        k623C = 0xfc,             // 623C with m_rfGauge
        kHopBombUnused = 0xfd,    // unused: hop back, spawns an explosion 0x195
        kHopPlaceUnused = 0xfe,   // unused: hop back, places a bomb 0x190
        k214A = 0xff,             // 214A, gauge > 50
        k214B = 0x100,            // 214B
        k214C = 0x101,            // 214C
        kAir236A = 0x104,         // air 236A, gauge > 50
        kAir236B = 0x105,         // nagamori.cpp
        kAir236C = 0x106,         // nagamori.cpp
        kAir236Landing = 0x107,   // landing recovery of 0x104-0x106
        kUnused109 = 0x109,       // unused: places explosions 0x195 twice
        kUnused10a = 0x10a,       // unused: hop back with explosion 0x195
        k236A = 0x10b,            // 236A with the shot in hand
        k236B = 0x10c,            // 236B (or C without m_rfGauge)
        k236C = 0x10d,            // 236C with m_rfGauge
        k412A = 0x10e,            // 412A
        k412B = 0x10f,            // 412B
        k412C = 0x110,            // 412C with m_rfGauge
        kAir214A = 0x113,         // 214A in the air
        kAir214B = 0x114,         // nagamori.cpp
        kAir214C = 0x115,         // nagamori.cpp
        k236AShotUp = 0x116,      // 236A while the shot is out: m_shotOrder 1, the shot
                                  // rises
        k236BShotDown = 0x117,    // 236B while out: m_shotOrder -1, the shot dives
        k236CShotForward = 0x118, // 236C while out: m_shotOrder 2, the shot flies out again
        k236236Lv1 = 0x12c,       // 236236 1 level
        k236236Lv2 = 0x12d,       // 2 levels
        k236236Lv3 = 0x12e,       // 3 levels
        k236236Lv1Hit = 0x12f,    // pins the opponent (0x71), small hits then
                                  // DealDamage(2000)
        k236236Lv2Hit = 0x130,    // the same, more hits
        k236236Lv3Hit = 0x131,    // the same, DealDamage(2500) at the end
        k214214B = 0x132,         // 214214B, 1 level
        k214214A = 0x133,         // 214214A, 1 level
        k214214C = 0x134,         // 214214C, 1 level, only while no 0x191 is out
                                  // (m_bouncerOut)
        kAir214214B = 0x135,      // in the air
        kAir214214A = 0x136,      // in the air
        kAir214214C = 0x137,      // in the air
        kLv4 = 0x138,             // 6, B, A, 6, neutral, A with gauge 3000 on the ground,
                                  // HP < 3333
        k6413Lv1 = 0x139,         // 6413 + button, 1 level, shot in hand
        k6413Lv2 = 0x13a,         // 2 levels
        k6413Lv3 = 0x13b,         // 3 levels
        kObjBomb = 0x190,         // placed by 214A, air 236A/214A, 412B/C, dropped by
                                  // 0x19d: bobs
        kObjBouncer = 0x191,      // 214214C's: vx 0.75, bounces on the floor, every 20
                                  // frames drops 0x19a
        kObjSuperBomb = 0x192,    // 214214A's: like 0x190 but survives its explosions
        kObjSuperBombBig = 0x193, // 214214B's: like 0x190, explodes into the big 0x1c6
        kObj2CFx = 0x194,         // one-shot of 2C
        kObjExplosion = 0x195,    // hits at frame 14, triggers objects within 90 px
                                  // (chain), pulls the opponent toward it at speed 2.2 when
                                  // it hits (SetVelocity)
        kObjBombB = 0x196,        // 214B/air 236B/air 214B: drifts forward vx 1.8 slowing
                                  // down, then bobs
        kObjBombC = 0x197,        // 214C: flies up-forward (1.8, -1.8) slowing down, then
                                  // bobs
        kObjBombAirC = 0x198,     // air 236C/214C: flies down-forward (1.8, 1.8), stops at
                                  // the floor, then bobs
        kObjBombRise = 0x199,     // from 0x19a: rises (vy -1.2), then bobs
        kObjBouncerDrop = 0x19a,  // dropped by 0x191: at frame 6 spawns bombs 0x1c1, 0x19f,
                                  // 0x199
        kObjShotA = 0x19b,        // 236A's shot: vx 4.2 slowing to 0 (hits, triggers
                                  // objects it passes), then homes back and is caught
        kObjShotB = 0x19c,        // 236B's shot: arcs up (2.0, -2.3) first
        kObjShotC = 0x19d,        // 236C's shot: drops a bomb 0x190 + 0x19e every 90 frames
                                  // on its way back, up to 5
        kObjPlaceFx = 0x19e,      // one-shot (voice 1) next to a newly placed 0x190
        kObjBombBack = 0x19f,     // from 0x19a: drifts back-down (-1.2, 1.2), then bobs
        kObjUnused1a0 = 0x1a0,    // never spawned: one-shot that clears m_keepBombs
        kObjLv4Director = 0x1a1,  // LV4: counts m_lv4Time down, keeps the opponent frozen
                                  // (m_freezeTime 1200), gauge 0, spawns 0x1a2-0x1be at set times
        kObjLv4Scene01 = 0x1a2,   // the LV4's screen-space pieces 0x1a2-0x1be, spawned in
                                  // order by 0x1a1 (first at m_lv4Time 1150)
        kObjLv4Scene02 = 0x1a3,   // see 0x1a2
        kObjLv4Scene03 = 0x1a4,
        kObjLv4Scene04 = 0x1a5,
        kObjLv4Scene05 = 0x1a6,
        kObjLv4Scene06 = 0x1a7,
        kObjLv4Scene07 = 0x1a8,
        kObjLv4Scene08 = 0x1a9,
        kObjLv4Scene09 = 0x1aa,
        kObjLv4Scene10 = 0x1ab,
        kObjLv4Scene11 = 0x1ac,
        kObjLv4Scene12 = 0x1ad,
        kObjLv4Scene13 = 0x1ae,
        kObjLv4Scene14 = 0x1af,
        kObjLv4Scene15 = 0x1b0,
        kObjLv4Scene16 = 0x1b1,
        kObjLv4Scene17 = 0x1b2,
        kObjLv4Scene18 = 0x1b3,
        kObjLv4Scene19 = 0x1b4,
        kObjLv4Scene20 = 0x1b5,
        kObjLv4Scene21 = 0x1b6,
        kObjLv4Scene22 = 0x1b7,
        kObjLv4Scene23 = 0x1b8,
        kObjLv4Scene24 = 0x1b9,
        kObjLv4Scene25 = 0x1ba,
        kObjLv4Scene26 = 0x1bb,
        kObjLv4Scene27 = 0x1bc,
        kObjLv4Scene28 = 0x1bd,   // spawned at m_lv4Time 540
        kObjLv4Scene29 = 0x1be,   // spawned at m_lv4Time 300
        kObjLv4Start = 0x1bf,     // 45 frames into 0x138: at its frame 25 triggers objects
                                  // within 320 px and flashes
        kObjLv4StartEnd = 0x1c0,  // 0x1bf's second part, removed when she leaves 0x138
        kObjBombFwd = 0x1c1,      // from 0x19a: drifts forward-down (1.2, 1.2), then bobs
        kObj6413Lv1Blast = 0x1c2, // glued to her (y-55), hits at frame 1 and spawns 0x1c5
        kObj6413Lv2Blast = 0x1c3,
        kObj6413Lv3Blast = 0x1c4,
        kObj6413Flash = 0x1c5,    // glued to her
        kObjExplosionBig = 0x1c6, // 0x193's explosion: as 0x195 with a 120 px trigger box
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CNagamori's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd6BA65A = 0x5b,  // 6 B A 6 5 A, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 80 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 80 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 80 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 80 frames
    };
    // END constants

    // FUNCTION: 0x49d610
    virtual void UpdatePattern();
    // FUNCTION: 0x4add90
    CNagamori(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5,
              BYTE p6);
    // FUNCTION: 0x4adfa0
    virtual void Reset();
    // FUNCTION: 0x4ae130
    virtual void StartPattern();
    // FUNCTION: 0x4ae170
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x4ae1d0
    // Sets m_objectTriggered for each active object within p3 (x) and p4 (y) of (p1, p2):
    // her attacks and explosions detonate bombs this way
    void TriggerObjectsNear(short p1, short p2, short p3, short p4);
    // FUNCTION: 0x4ae2c0
    virtual void Move();
    // FUNCTION: 0x4ae2e0
    virtual void StartCommand();
    // FUNCTION: 0x4b12e0
    virtual void DrawGauge();
    // FUNCTION: 0x4b1720
    virtual void PreUpdate();
    // FUNCTION: 0x4b1750
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4b1780
    virtual void ReadCommand();
    // FUNCTION: 0x4b2ac0
    virtual void CpuInput();
    // FUNCTION: 0x4b6680
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern; object
                       // 0x1bf also sets it during the LV4
    int m_patternVar2; // The same, a second one
    int m_patternVar3; // The same, a third one
    int m_encasedBreakOut; // 1 while an object 0x1f0 (spawned entering 0x53-0x56) waits
                           // to burst into particles
    int m_shotState; // The 236 shot (0x19b-0x19d): 0 in her hand, 1 flying out, 2 coming
                     // back; most specials need 0
    int m_keepBombs; // Set by the 6413 supers (which trigger every object), cleared by
                     // 0x1c5: meanwhile exploding bombs are not removed
    int m_lv4Time; // Frames left of the LV4 sequence (object 0x1a1), from 1200; DrawGauge
                   // draws it as a bar; no 22C guard cancel while > 0
    int m_shotOrder; // An order for the flying shot, given by 236 while it is out: 1
                     // rise, -1 dive, 2 fly out again; the shot resets it to 0
    int unk3158;
    int unk315c;
    int m_bombsPlaced; // Bombs 0x190 placed by 214A and 412B/C; never read
    int m_bouncerDrops; // 0, 1, 2 cycled by each drop 0x19a of the bouncer; never read
    int m_bouncerOut; // 1 while the 214214C bouncer 0x191 is on screen; 214214C needs 0
    char m_objectTriggered[0x40]; // Per object: set by TriggerObjectsNear this frame; a
                                  // bomb that sees it (and whose cooldown is over)
                                  // explodes
    int m_objectState[0x40]; // Per object: loops of its animation done, the shot's phase,
                             // or the angle an explosion pulls the opponent at
    int m_objectTimer[0x40]; // Per object: a bomb's 120-frame cooldown after exploding,
                             // frames between 0x19d's drops, or a particle's lifetime
    int m_objectPhase[0x40]; // Per object: a bomb's 0 start, 1 moving, 2 floating (only
                             // then it can be triggered), or a count of the object's
                             // spawns
    BYTE unk34ac[0x34b0 - 0x34ac];
};

// Kaori: one of the character classes.
// SIZE: 0x3450
class CKaori : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CKaori's own actions
    enum {
        k5A = 0xc8,                   // A
        k5BClose = 0xc9,              // B within 50 px of the opponent
        k5BFar = 0xca,                // B otherwise
        k5C = 0xcb,                   // C
        k2A = 0xcc,                   // 2A
        k2B = 0xcd,                   // 2B
        k2C = 0xce,                   // 2C
        kJumpA = 0xcf,                // A in the air
        kJumpB = 0xd0,                // B in the air
        kJumpC = 0xd1,                // C in the air
        kAirDiveUnused = 0xd2,        // unused: stops, then dives vx 1, vy 1 with 3 hits
                                      // until landing
        kAirAttackUnused = 0xd3,      // an air normal entered only by the whiff of the
                                      // unused 0xf0
        kHopBackUnused = 0xd5,        // unused: hop back vx -1, vy -2.4, then falls
        kLandingShakeUnused = 0xd6,   // unused: landing with ShakeScreen(3) and effect 3
        kThrow = 0xdc,                // C + direction within 30 px, opponent standing
        kThrowHit = 0xdd,             // the throw connected: DealDamage(1200), opponent to
                                      // 0x51, 8 sparks 0x191
        kDashA = 0xe6,                // A during forward dash 0xa3
        kDashB = 0xe7,                // B during 0xa3
        kDashC = 0xe8,                // C during 0xa3
        kDash2A = 0xe9,               // 2A during 0xa3
        kDash2B = 0xea,               // 2B during 0xa3
        kDash2C = 0xeb,               // 2C during 0xa3
        kAirThrow2Unused = 0xf0,      // unused second air throw: on connect jumps vx 1, vy
                                      // -2.5 into 0xf1, whiff into 0xd3
        kAirThrow2Hit = 0xf1,         // only from 0xf0: carries the opponent and slams,
                                      // DealDamage(1000)
        kAirThrow = 0xf8,             // air C + forward within 100 px, opponent airborne
        kAirThrowHit = 0xf9,          // air throw connected: DealDamage(1400), opponent to
                                      // 0x45
        kDashStep = 0xfa,             // her ground 66 (kaori.cpp, replaces 0xa3): step vx
                                      // 2.5
        kBackdashStep = 0xfb,         // 66 on landing of the backdash 0xa4: longer step vx
                                      // 4.0, same follow-ups
        k214A = 0xfd,                 // 214A
        k214B = 0xfe,                 // 214B
        k214C = 0xff,                 // 214C with m_rfGauge >= 500
        k623A = 0x100,                // 623A
        k623B = 0x101,                // 623B
        k623C = 0x102,                // 623C with m_rfGauge >= 500
        kStepA = 0x103,               // A from 0xfa/0xfb
        kStepC = 0x104,               // C from 0xfa/0xfb
        kStep2C = 0x105,              // 2C from 0xfa/0xfb
        kStepUnused = 0x106,          // unused copy of 0x105 that ends standing
        kStepB = 0x107,               // B from 0xfa/0xfb
        k236236Lv1 = 0x12c,           // 236236 1 level
        k236236Lv1Hit = 0x12d,        // puts Kaori left of the opponent (facing forced to
                                      // 1) and spawns 0x192-0x194
        k236236Lv2 = 0x12e,           // 236236 2 levels
        k236236Lv2Hit = 0x12f,        // as 0x12d
        k236236Lv3 = 0x130,           // 236236 3 levels
        k236236Lv3Hit = 0x131,        // spawns 0x195-0x197 which burst into sparks
        k214214Lv1 = 0x132,           // 214214 1 level
        k214214Lv1Hit = 0x133,        // 6 hits
        k214214Lv2 = 0x134,           // 214214 2 levels
        k214214Lv2Hit = 0x135,        // 15 hits
        k214214Lv3 = 0x136,           // 214214 3 levels
        k214214Lv3Hit = 0x137,        // 15 hits
        k6413Lv1 = 0x138,             // 6413 + button (forward, back, down-back, down-
                                      // forward), 1 level
        k6413Lv2 = 0x139,             // 2 levels
        k6413Lv3 = 0x13a,             // 3 levels
        kLv4 = 0x13b,                 // 6 6 6 + D (forward taps), gauge 3000, HP < 3333
        kLv4Hit = 0x13c,              // DealDamage(5000), opponent to 0x57, screen objects
                                      // 0x198/0x199, then drops the opponent from y -640
        kObj623B = 0x190,             // object of 0x101: follows x+40 while she is in
                                      // 0x100-0x102, else skips to frame 0x3e
        kObjHitSpark = 0x191,         // one-shot, no hit: 8 at random round a throw, 3 from
                                      // each of 0x195-0x197
        kObj236236Hit1 = 0x192,       // one-shot of 0x12d/0x12f at frame 1
        kObj236236Hit2 = 0x193,       // the same at frame 10
        kObj236236Hit3 = 0x194,       // the same at frame 18
        kObj236236Lv3Hit1 = 0x195,    // of 0x131
        kObj236236Lv3Hit2 = 0x196,    // the same
        kObj236236Lv3Hit3 = 0x197,    // the same
        kObjLv4Backdrop = 0x198,      // screen-space at (0,0), layer 0, looping, removed at
                                      // 0x13c frame 3
        kObjLv4BackdropFront = 0x199, // screen-space at (0,0), layer 1, drifts vx 0.08,
                                      // removed with 0x198
        kObj623A = 0x19a,             // object of 0x100 at x+40: 15 hits (hitsLeft), re-hits
                                      // on 9 frames, skips to 0x3e when she leaves 0x100
        kObj623C = 0x19b,             // object of 0x102: follows x+40, loops frames to 0x1e
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CKaori's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd666D = 0x5d,    // 5 6 5 6 5 6 D, within 135 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x62a5e0
    virtual void UpdatePattern();
    // FUNCTION: 0x638d90
    CKaori(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x638f10
    virtual void Reset();
    // FUNCTION: 0x639030
    virtual void StartPattern();
    // FUNCTION: 0x639070
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x6390c0
    virtual void Move();
    // FUNCTION: 0x6390e0
    virtual void StartCommand();
    // FUNCTION: 0x63b610
    virtual void DrawGauge();
    // FUNCTION: 0x63b620
    virtual void PreUpdate();
    // FUNCTION: 0x63b630
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x63b660
    virtual void ReadCommand();
    // FUNCTION: 0x63c960
    virtual void CpuInput();
    // FUNCTION: 0x640710
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern: a frame
                       // count, a repeat count, or vx * 100 saved across a freeze
    int m_patternVar2; // The same, a second one: also vy * 100 saved across a freeze
    int m_patternVar3; // The same, a third one: one-shot flags and loop counts
    int unk3144;
    int m_encasedBreakOut; // 1 while an object 0x1f0 (spawned entering 0x53-0x56) waits
                           // to burst into particles, so only one is spawned
    int m_objectState[0x40]; // Per object: a small state or counter of the object's own
                             // code (0 = not initialised yet); zeroed by RemoveObject
    int m_objectTimer[0x40]; // Per object: frames left (the particles 0x1f1/0x1f2 shrink
                             // under 10 and vanish below 0)
    int unk334c[0x40]; // indexed
    BYTE unk344c[0x3450 - 0x344c];
};

// Kano: one of the character classes.
// SIZE: 0x3478
class CKano : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CKano's own actions
    enum {
        k5A = 0xc8,                     // A standing
        k5BClose = 0xc9,                // B standing within 70 px of the opponent
        k5BFar = 0xca,                  // B standing, farther
        k5C = 0xcb,                     // C standing
        k2A = 0xcc,                     // down + A
        k2B = 0xcd,                     // down + B
        k2C = 0xce,                     // down + C
        kJumpA = 0xcf,                  // A in the air
        kJumpB = 0xd0,                  // B in the air
        kJumpC = 0xd1,                  // C in the air, 5 hits, loops once
        k6C = 0xd2,                     // forward + C standing: object 0x199 hits 150 px
                                        // ahead at y -40, costs 20 gauge
        kUnusedD3 = 0xd3,               // never started (no reference outside its case)
        k3C = 0xd4,                     // down-forward + C: slides forward at 2.6, 3 hits
        kJump2A = 0xd5,                 // down + A in the air above y -25: dives at 30
                                        // degrees, speed 2.2, until landing
        kJump2B = 0xd6,                 // the same with B, above y -30
        kJump2C = 0xd7,                 // the same with C, above y -25
        k6B = 0xd9,                     // forward + B standing
        kThrow = 0xdc,                  // C + a direction within 30 px of a grounded
                                        // opponent not being hit
        kThrowConnected = 0xdd,         // the throw connecting: DealDamage(1000, 750)
        kDashA = 0xe6,                  // A during the forward dash 0xa3
        kDashB = 0xe7,                  // B during the forward dash
        kDashC = 0xe8,                  // C during the forward dash
        kDash2A = 0xe9,                 // down + A during the forward dash
        kDash2B = 0xea,                 // down + B during the forward dash
        kDash2C = 0xeb,                 // down + C during the forward dash, 6 hits
        kAirThrow = 0xf8,               // forward + C in the air within 100 px of an
                                        // airborne opponent not being hit
        kAirThrowConnected = 0xf9,      // the air throw connecting: DealDamage(1200, 500),
                                        // lands in 0xd
        k5D = 0xfa,                     // D on the ground, charge gauge below full: chant
                                        // loop (frames 3-6), +0x4b charge a frame until
                                        // full or D again
        k236D = 0xfb,                   // 236D with CPlayer::m_rfGauge >= 500 (or m_rfBlue > 0)
                                        // and the charge gauge below full
        k236A = 0xfe,                   // 236A, no eruption out: startup loop charges until
                                        // full, then the eruption 0x1bb 150 +
                                        // 70*(left/right held) px ahead on the ground
        k236B = 0xff,                   // the same with eruption 0x1bc (2 bursts), costs
                                        // 5000 charge and 20 gauge
        k236C = 0x100,                  // the same with eruption 0x1bd (5 bursts), costs
                                        // 7500 charge and 50 gauge
        k214A = 0x101,                  // 214A, no shot out: one shot 0x191 at y -45
        k214B = 0x102,                  // 214B: three shots 0x191 at three heights, costs
                                        // 5000 charge and 7 gauge per shot
        k214C = 0x103,                  // 214C: five shots 0x191, costs 7500 charge and 10
                                        // gauge per shot
        k421A = 0x104,                  // 421A (back, down, down-back + A), no orb out: orb
                                        // 0x1b8 at y -80 that fires one aimed shot
        k421B = 0x105,                  // 421B: orb 0x1b9, two aimed shots
        k421C = 0x106,                  // 421C: orb 0x1ba, three aimed shots
        kUnused107 = 0x107,             // never started: chant at +0x12c a frame, then two
                                        // remote hits 0x199 110 px ahead
        kUnused108 = 0x108,             // never started: the same as 0x107
        kUnused109 = 0x109,             // never started: drops three objects 0x1a2 from 480
                                        // px above
        kUnused10a = 0x10a,             // never started: the same as 0x109
        kUnused10b = 0x10b,             // never started: the same as 0x109
        kUnused10c = 0x10c,             // never started: air move halving the velocity, +45
                                        // gauge, object 0x197 behind
        kUnused10d = 0x10d,             // never started: the same as 0x10c
        kUnused10e = 0x10e,             // never started: 0x10c spending 500 of m_rfGauge, with
                                        // three more 0x197
        k641236A = 0x12c,               // 641236A, gauge >= 1000: chant to a full charge,
                                        // then object 0x1c7 75 px ahead that creeps forward
                                        // while A is held and erupts (0x19a, 3 times) when
                                        // A is let go
        k641236B = 0x12d,               // 641236B, gauge >= 2000: object 0x1a3 that speeds
                                        // up and rushes forward as 0x1a4 (up to 99 hits)
        k641236C = 0x12e,               // 641236C, gauge >= 3000: pillar on Kano (0x1c1 ->
                                        // 0x1be) throwing debris 0x1c0
        k236236A = 0x12f,               // 236236A, gauge >= 1000: throws bomb 0x19c down-
                                        // forward, which bursts into a chain of 7
                                        // explosions
        k236236B = 0x130,               // 236236B, gauge >= 2000: three lingering blasts
                                        // 0x1ad and a rising chain blast 0x19d 45-75 px
                                        // ahead
        k236236C = 0x131,               // 236236C, gauge >= 3000: launches 0x1c2 into the
                                        // sky
        k21436A = 0x132,                // 21436A, gauge >= 1000: three homing shots 0x19e,
                                        // 30 frames apart
        k21436B = 0x133,                // 21436B (or C with 2000-2999 gauge): four homing
                                        // shots 0x19f
        k21436C = 0x134,                // 21436C, gauge >= 3000: five homing shots 0x1a0
        k22B = 0x135,                   // 22B, gauge >= 2000: summons 0x1ae, which leaves
                                        // floor trap 0x1af
        k214214A = 0x138,               // 214214A, gauge >= 1000: big shot 0x1a7 (vx 4)
                                        // that pops up on a hit and bursts 8 times
        k214214B = 0x139,               // 214214B, gauge >= 2000: shot 0x1ac (vx 4.5, 7
                                        // hits) that stops on a hit and bursts every 2
                                        // frames
        k214214C = 0x13a,               // 214214C, gauge >= 3000: shot 0x1b2 that rises,
                                        // then flies level with 99 hits, trailing hitting
                                        // sparks 0x1b0
        kLv4 = 0x13b,                   // LV4: 21436D from the shared states 0xa8/0xa9 with
                                        // HP below 3333 and the gauge full
        kLv4Connected = 0x13c,          // LV4 connecting: carries the opponent up
        kObjEruptionHit = 0x190,        // spawned by the eruptions 0x1bb-0x1bd on each of
                                        // their animation frames, one hit each
        kObjShot = 0x191,               // 214's shot: vx 3.0 slowing to 1.5, one hit, ->
                                        // 0x193 on contact
        kObjUnusedShotLauncher = 0x192, // never spawned: spawns a 0x191 40 px ahead at its
                                        // frame 1
        kObjShotHit = 0x193,            // 0x191's hit flash, one hit
        kObjUnusedRisingShot = 0x194,   // never spawned: rises (vy -3), loops 5 times,
                                        // flies at (3, 0.8), bursts 0x195 on contact or the
                                        // ground
        kObjShotBurst = 0x195,          // where shots, orbs and blasts end (and
                                        // 0x1a7/0x1ac's bursts)
        kObjChantFront = 0x196,         // at Kano's position on frame 3 of every chant,
                                        // layer 1
        kObjChantBack = 0x197,          // the same on layer 0
        kObjRefill = 0x198,             // 236D's effect 40 px above Kano
        kObjRemoteHit = 0x199,          // 6C's hit
        kObjControlledEruption = 0x19a, // 641236A's eruption, spawned by 0x1c7 at frame
                                        // 0xf, offsets 0/-45/+45
        kObjIdleBonus = 0x19b,          // Vf8: shown above Kano with the +300 gauge after
                                        // 630 still frames
        kObjBomb = 0x19c,               // 236236A: thrown at (3.5, 2.0), one hit
        kObjChainBlast = 0x19d,         // 7 explosions 0x1a5 around it, each with a random
                                        // voice 0xb-0xd
        kObjHomingShotA = 0x19e,        // 21436A: starts backwards (-2.5, -1.5), turns
                                        // towards the opponent's height, trail 0x1a6 every
                                        // 6 frames
        kObjHomingShotB = 0x19f,        // 21436B: the same code
        kObjHomingShotC = 0x1a0,        // 21436C: the same code
        kObjUnusedHomingShot = 0x1a1,   // never spawned: the same code
        kObjUnusedHomingShot2 = 0x1a2,  // the same code
        kObjRushStart = 0x1a3,          // 641236B: speeds up from 0, -> 0x1a4 at its
                                        // animation's end
        kObjRush = 0x1a4,               // 641236B: vx 4.0, up to 99 hits, voices 8/9
        kObjChainBlastHit = 0x1a5,      // one explosion of 0x19d, one hit
        kObjHomingTrail = 0x1a6,        // 0x19e-0x1a2's trail
        kObjBigShot = 0x1a7,            // 214214A: vx 4, one hit
        kObjBigShotSpark1 = 0x1a8,      // 0x1a7's trail when it hasn't hit (one of
                                        // 0x1a8-0x1ab at random), one hit
        kObjBigShotSpark2 = 0x1a9,      // the same
        kObjBigShotSpark3 = 0x1aa,      // the same
        kObjBigShotSpark4 = 0x1ab,      // the same
        kObjMultiHitShot = 0x1ac,       // 214214B: vx 4.5, 7 hits
        kObjLingeringBlast = 0x1ad,     // 236236B: 5 hits, rearmed at frames
                                        // 8/0xe/0x14/0x1a, gone when out of hits or after
                                        // 1200 frames
        kObjTrapSummon = 0x1ae,         // 22B: at its frame 0xb leaves the trap 0x1af
        kObjFloorTrap = 0x1af,          // 22B's trap: attacks (frames 0xa-0xb) while Kano
                                        // stands within 30 px of it
        kObjSuperShotTrail = 0x1b0,     // 214214C: spawned by 0x1b2 each frame, one hit
        kObjSuperShotSpark = 0x1b1,     // 0x1b0's spark
        kObjSuperShot = 0x1b2,          // 214214C: (3, -1.2) rising, then level
        kObjAimedShot70 = 0x1b3,        // 421 orb's shot at 70 degrees (steepest), speed 3
        kObjAimedShot55 = 0x1b4,        // the same at 55 degrees
        kObjAimedShot40 = 0x1b5,        // the same at 40 degrees
        kObjAimedShot25 = 0x1b6,        // the same at 25 degrees
        kObjAimedShot10 = 0x1b7,        // the same at 10 degrees
        kObjOrbA = 0x1b8,               // 421A: rises (vy -3 slowing to 0), fires one aimed
                                        // shot, then is gone
        kObjOrbB = 0x1b9,               // 421B: fires two aimed shots 15 frames apart
        kObjOrbC = 0x1ba,               // 421C: fires three
        kObjEruptionA = 0x1bb,          // 236A: on the ground, one burst 0x190
        kObjEruptionB = 0x1bc,          // 236B: two bursts 25 px apart
        kObjEruptionC = 0x1bd,          // 236C: five bursts spread over 100 px
        kObjPillar = 0x1be,             // 641236C: on Kano (follows her x), shakes the
                                        // screen, throws 6 debris 0x1c0
        kObjImpactFlash = 0x1bf,        // with the pillar, its debris and the meteor's
                                        // landing
        kObjPillarDebris = 0x1c0,       // 641236C: at its frame 2 spawns 0x1c6 at Kano's x
                                        // on the ground
        kObjPillarStart = 0x1c1,        // 641236C: on Kano, at its frame 0xe spawns the
                                        // pillar 0x1be
        kObjMeteorLaunch = 0x1c2,       // 236236C: flies off at (6, -6), gone above y -1600
        kObjMeteor = 0x1c3,             // Vf8, 600 frames after 236236C: falls from y -480
                                        // at 60 degrees, speed 4
        kObjMeteorCrater = 0x1c4,       // left by the meteor
        kObjMeteorBlast = 0x1c5,        // the meteor's explosion, one hit, shakes the
                                        // screen
        kObjPillarDebrisHit = 0x1c6,    // 0x1c0's hit at Kano's x
        kObjControlledCharge = 0x1c7,   // 641236A: creeps forward until A is let go, then
                                        // erupts (0x19a)
        kObjLv4Finish = 0x1c8,          // LV4: screen object
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CKano's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd421A = 0x3c,    // 421 + A, within 60 frames
        kCmd421B = 0x3d,    // 421 + B, within 60 frames
        kCmd421C = 0x3e,    // 421 + C, within 60 frames
        kCmd421D = 0x3f,    // 421 + D, within 60 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
        kCmd21436A = 0xaa,  // 21436 + A, within 90 frames
        kCmd21436B = 0xab,  // 21436 + B, within 90 frames
        kCmd21436C = 0xac,  // 21436 + C, within 90 frames
        kCmd21436D = 0xad,  // 21436 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x6429c0
    virtual void UpdatePattern();
    // FUNCTION: 0x653a20
    CKano(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x653c30
    virtual void Reset();
    // FUNCTION: 0x653dd0
    virtual void StartPattern();
    // FUNCTION: 0x653e10
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x653e60
    virtual void Move();
    // FUNCTION: 0x653e80
    virtual void StartCommand();
    // FUNCTION: 0x657500
    virtual void DrawGauge();
    // FUNCTION: 0x657b70
    virtual void PreUpdate();
    // FUNCTION: 0x657e70
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x657ea0
    virtual void ReadCommand();
    // FUNCTION: 0x659250
    virtual void CpuInput();
    // FUNCTION: 0x65cd30
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current action, zeroed by StartPattern: once-
                       // flags, loop counts, D's charge frames, 0xaa/0xab's saved vx *
                       // 100
    int m_patternVar2; // Scratch for the current action, zeroed by StartPattern: the
                       // dash's frame count, 0xaa/0xab's saved vy * 100, 21436's 30-frame
                       // timer between shots
    int m_patternVar3; // Scratch for the current action, zeroed by StartPattern: 0xaa's
                       // once-flag, 21436's shot count, 236236C's loop count
    int m_encasedBreakOut; // 1 while object 0x1f0 (spawned by the shared hit actions
                           // 0x53-0x56) is out; cleared when it bursts into 0x1f1/0x1f2
    int unk3148;
    int unk314c;
    int m_chargeGauge; // The second gauge DrawGauge draws, 0 to 10000: D (0xfa) and the
                       // startup loop of every special and super fill it, 236D fills it
                       // at once; a special fires at full and leaves 7500/5000/2500
                       // (A/B/C), a super empties it; full when a move starts skips its
                       // startup
    int m_gaugeRegenTimer; // Vf8's frame count for the power gauge's own regeneration: +1
                           // every 3 + 4 * level frames outside supers and freezes
    int m_idleTimer; // Vf8: frames standing still (vx 0, not hit or guarding, not in a
                     // super); at 630 the gauge gains 300 and object 0x19b shows
    int m_meteorsPending; // Meteors (object 0x1c3) still to fall from 236236C; Vf8 drops
                          // one each time m_meteorTimer runs out
    int m_meteorTimer; // Vf8's countdown to the next meteor: 600 frames after 236236C,
                       // then 180 between meteors
    int m_meteorFacing; // Kano's facing when she used 236236C: the meteor's direction and
                        // the side it falls on
    int m_orbsOut; // 421's orbs (0x1b8-0x1ba) and their aimed shots (0x1b3-0x1b7) on
                   // screen; 421 can start only at 0
    int m_shotsOut; // 214's shots (0x191) on screen; 214 can start only at 0
    int m_eruptionsOut; // 236's ground eruptions (0x1bb-0x1bd) on screen; 236 can start
                        // only at 0
    int m_objectVar1[0x40]; // Per object, zeroed by RemoveObject: 0 until the object's
                            // first update, then its step or loop counter
    int m_objectVar2[0x40]; // Per object, zeroed by RemoveObject: timers, hit or shot
                            // counts, a random voice pick
    int m_objectVar3[0x40]; // Per object, zeroed by RemoveObject: cooldowns between
                            // bursts, shots or hits, once-flags
    BYTE unk3474[0x3478 - 0x3474];
};

// Ikumi: one of the character classes.
// SIZE: 0x3478
class CIkumi : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CIkumi's own actions
    enum {
        k5A = 0xc8,                     // A standing
        k5BClose = 0xc9,                // B standing within 70 px of the opponent
        k5BFar = 0xca,                  // B standing otherwise
        k5C = 0xcb,                     // C standing
        k2A = 0xcc,                     // A crouching
        k2B = 0xcd,                     // B crouching
        k2C = 0xce,                     // C crouching
        kJumpA = 0xcf,                  // A in the air
        kJumpB = 0xd0,                  // B in the air
        kJumpC = 0xd1,                  // C in the air
        kThrow = 0xdc,                  // C + a direction within 30 px of a grounded
                                        // opponent
        kThrowConnected = 0xdd,         // the throw landing: DealDamage(900, 750), opponent
                                        // -> 0x3f
        kDashA = 0xe6,                  // A during the forward dash 0xa3
        kDashB = 0xe7,                  // B during the dash
        kDashC = 0xe8,                  // C during the dash
        kDash2A = 0xe9,                 // 2A during the dash
        kDash2B = 0xea,                 // 2B during the dash
        kDash2C = 0xeb,                 // 2C during the dash: a hop (vy -1.2, vx 1.0) that
                                        // lands on frame 0xb
        kAirThrow = 0xf8,               // forward + C in the air near an airborne opponent
        kAirThrowConnected = 0xf9,      // air throw: frame 5 repeats 5 times,
                                        // DealDamage(1200, 500) (1400 in the mode), object
                                        // 0x199
        k214A = 0xfa,                   // 214A: at frame 5 a pillar 0x193 rises from the
                                        // ground 60 px ahead
        k214B = 0xfb,                   // 214B: the pillar 120 px ahead
        k214C = 0xfc,                   // 214C: the pillar 180 px ahead
        k236A = 0xfd,                   // 236A: rushes forward (vx 2.5), stops short at 150
                                        // px from the opponent and strikes (frame 8 on),
                                        // effect 0x191
        k236B = 0xfe,                   // 236B (stocks 0-2), as 0xfd
        k236C = 0xff,                   // 236C (stocks 0-2) with m_rfGauge >= 500 or m_rfBlue:
                                        // spends 500 of m_rfGauge (250 under m_rfBlue)
        k623A = 0x100,                  // 623A: a forward leap (vx 1.1, vy -1.5) with
                                        // effect 0x190, lands into 0x103
        k623B = 0x101,                  // 623B (stocks 0-2), vx 1.4
        k623C = 0x102,                  // 623C (stocks 0-2) with m_rfGauge >= 500 or m_rfBlue,
                                        // spends it
        k623Landing = 0x103,            // landing of 0x100-0x102
        k41236C = 0x107,                // 41236C command grab, grounded opponent only,
                                        // connects on frame 2 -> 0x108 (opponent 0x6b)
        k41236CHold = 0x108,            // holds the opponent (m_hitstop 0x5dc),
                                        // DealDamage(250, 1000), orbs 0x1d6, then
                                        // DealDamage(250, 600) (500/700 in the mode) with
                                        // two 0x1dd bursts
        k236BStock3 = 0x10a,            // 236B with 3-5 stocks (takes one): 2 hits
        k236CStock3 = 0x10b,            // 236C with 3-5 stocks (takes one) and m_rfGauge
        k236BStock6 = 0x10d,            // 236B with 6-8 stocks (takes one) or in the mode
                                        // (free): 3 hits
        k236CStock6 = 0x10e,            // 236C with 6-8 stocks or in the mode
        k623BStock3 = 0x110,            // 623B with 3-5 stocks (takes one)
        k623CStock3 = 0x111,            // 623C with 3-5 stocks and m_rfGauge
        k623Stock3Landing = 0x112,      // landing of 0x110/0x111
        k623BStock6 = 0x114,            // 623B with 6-8 stocks or in the mode
        k623CStock6 = 0x115,            // 623C with 6-8 stocks or in the mode, and m_rfGauge
        k623Stock6Landing = 0x116,      // landing of 0x114/0x115
        k214AStock3 = 0x117,            // 214A with 3-5 stocks: pillar 0x19a (2 cycles) 60
                                        // px ahead
        k214BStock3 = 0x118,            // 214B with 3-5 stocks: 120 px
        k214CStock3 = 0x119,            // 214C with 3-5 stocks: 180 px
        k214AStock6 = 0x11a,            // 214A with 6-8 stocks or in the mode: pillar 0x19c
                                        // (4 cycles, 2 hits each) 60 px
        k214BStock6 = 0x11b,            // 214B, 120 px
        k214CStock6 = 0x11c,            // 214C, 180 px
        kModeStart = 0x12c,             // started by Vf8 when m_stocks reaches 8 in a
                                        // neutral state: freeze, aura 0x19e, an
                                        // invulnerable hit (frames 5-8), 8 loops
        k4123641236A = 0x12f,           // 41236 41236 + A, 1000 gauge: grab super, grounded
                                        // opponent, connects on frame 1 -> 0x130
        k4123641236AHold = 0x130,       // holds the opponent at y-87 with effect 0x19f and
                                        // orbs, DealDamage(2000, 500) (2800 in the mode)
        k4123641236B = 0x131,           // + B (or C), 2000 gauge -> 0x132
        k4123641236BHold = 0x132,       // effect 0x1a0, DealDamage(3000, 500) (3800)
        k4123641236C = 0x133,           // + C, 3000 gauge -> 0x134
        k4123641236CHold = 0x134,       // effect 0x1a1, DealDamage(4100, 500) (5500)
        k214214A = 0x135,               // 214214A, 1000 gauge, not in the mode: a double of
                                        // Ikumi (0x1a4) that rushes like 236
        k214214B = 0x136,               // 214214B, 1000 gauge: double 0x1a5 that leaps, 3
                                        // hits
        k214214C = 0x137,               // 214214C, 1000 gauge: double 0x1a6 that walks up
                                        // and raises a 4-hit pillar
        k21436A = 0x138,                // 21436A, 1000 gauge: stores a level-1 strike
                                        // (m_storedSuperLevel = 1), ground effect 0x1a7
        k21436B = 0x139,                // 21436B, 2000 gauge: stores level 2
        k21436C = 0x13a,                // 21436C, 3000 gauge: stores level 3
        k21436Release1 = 0x13b,         // 21436 any button with a level-1 strike stored, no
                                        // gauge: strike 0x1a8 under the opponent
        k21436Release2 = 0x13c,         // level 2: 0x1aa under the opponent plus four 0x1a9
                                        // around
        k21436Release3 = 0x13d,         // level 3: 0x1ab plus 0x1a9s
        k21436AMode = 0x13e,            // 21436A in the mode, 1000 gauge: the level-1
                                        // strike at once
        k21436BMode = 0x13f,            // 21436B in the mode, 2000 gauge: level 2 at once
        k21436CMode = 0x140,            // 21436C in the mode, 3000 gauge: level 3 at once
        kLv4 = 0x141,                   // 236236236C, 3000 gauge, HP < 3333, not in the
                                        // mode: a lunge (vx 5) that on hit at frame 0xd ->
                                        // 0x142
        kLv4Connected = 0x142,          // LV4 sequence: moves onto the opponent, strikes
                                        // 0x1af-0x1b2 fly in, figures 0x1b3-0x1b6 drop in,
                                        // final blast 0x1b7
        kObj623Effect = 0x190,          // follows Ikumi (x, y each frame) during 623,
                                        // 107x129
        kObj236Effect = 0x191,          // 162x68 effect where 236 strikes
        kObj214GroundEffect = 0x192,    // 183x35 flat effect at the 214 pillar's spot
        kObj214Eruption = 0x193,        // 109x226, 1 hit (frame 5), spawns pillar 0x196 at
                                        // frame 0
        kObj214Pillar = 0x196,          // 90x217 pillar, 1 hit (frames 27-38), drops 5 orbs
                                        // (0x1de) on hit
        kObjThrowImpact = 0x199,        // 298x295 effect at the end of the air throw and
                                        // 41236C
        kObj214EruptionStock3 = 0x19a,  // as 0x193 for 0x117-0x119, spawns 0x19b
        kObj214PillarStock3 = 0x19b,    // as 0x196, cycles twice
        kObj214EruptionStock6 = 0x19c,  // as 0x193 for 0x11a-0x11c, spawns 0x19d
        kObj214PillarStock6 = 0x19d,    // 2 hits per cycle, 4 cycles, orbs once per cycle
        kObjModeStartAura = 0x19e,      // 248x368 effect of 0x12c
        kObjGrabSuperEffect1 = 0x19f,   // 223x212 effect of 0x130 (two, at ground and
                                        // y-160), loops while Ikumi's frame < 7
        kObjGrabSuperEffect2 = 0x1a0,   // 306x284 effect of 0x132
        kObjGrabSuperEffect3 = 0x1a1,   // 306x284 effect of 0x134, scatters 0x1a2/0x1a3 at
                                        // random
        kObjGrabSuperSpark = 0x1a2,     // 40x86 random spark of 0x1a1
        kObjGrabSuperSparkTall = 0x1a3, // 41x138 random spark of 0x1a1
        kObjDouble236 = 0x1a4,          // Ikumi-sized double of 214214A: rushes (vx 2.5) to
                                        // 150 px and strikes, 3 hits, effect 0x191
        kObjDoubleLeap = 0x1a5,         // double of 214214B: closes to 50 px, leaps, 3 hits
                                        // (frames 0x1e/0x26/0x2f)
        kObjDouble214 = 0x1a6,          // double of 214214C: walks up to 50 px and raises
                                        // pillar 0x1ac 50 px ahead
        kObj21436GroundEffect = 0x1a7,  // 204x48 flat effect (layer 0) at Ikumi's feet when
                                        // 21436 stores a strike and under the opponent when
                                        // it is released
        kObj21436Strike1 = 0x1a8,       // 172x200 strike under the opponent, 1 hit (frames
                                        // 4-10)
        kObj21436ExtraPillar = 0x1a9,   // same 172x200 sprite with no hit (hitsLeft 0), placed
                                        // around the opponent by levels 2-3
        kObj21436Strike2 = 0x1aa,       // 12x32 hit-carrier under the opponent for level 2,
                                        // 1 hit
        kObj21436Strike3 = 0x1ab,       // 12x32 hit-carrier for level 3, 1 hit
        kObjDoubleEruption = 0x1ac,     // as 0x193, from double 0x1a6, spawns 0x1ad
        kObjDoublePillar = 0x1ad,       // pillar of 0x1a6: 4 hits (2 in the mode), 4 cycles
        kObjDoubleVanish = 0x1ae,       // 55x226: a double (0x1a4-0x1a6) disappearing, at
                                        // its end or when Ikumi is hit
        kObjLv4Strike1 = 0x1af,         // flies in from the opponent - 320 px, y + 160 (vx
                                        // 7, vy -3.5), 1 hit
        kObjLv4Strike2 = 0x1b0,         // from + 320 px, mirrored
        kObjLv4Strike3 = 0x1b1,         // from - 160 px, y + 280 (vx 3.5, vy -7)
        kObjLv4Strike4 = 0x1b2,         // from + 160 px, mirrored
        kObjLv4Figure1 = 0x1b3,         // human-sized figure that drops in (from 390 px
                                        // behind, 330 up), lands, leaves at Ikumi's frame
                                        // 0x18
        kObjLv4Figure2 = 0x1b4,         // as 0x1b3 from 195 px behind, 495 up
        kObjLv4Figure3 = 0x1b5,         // as 0x1b3 in front
        kObjLv4Figure4 = 0x1b6,         // as 0x1b4 in front
        kObjLv4Blast = 0x1b7,           // 259x310 final blast at Ikumi, 1 hit
        kObjOrbBurst3 = 0x1d6,          // 48x99 burst at the opponent that releases 3 small
                                        // orbs (frame 2)
        kObjOrbBurst6 = 0x1d7,          // 95x144, 4 small + 2 medium orbs
        kObjOrbSmall = 0x1d8,           // 7x8 orb launched up at a random angle
        kObjOrbMedium = 0x1d9,          // 26x25, +30
        kObjOrbLarge = 0x1da,           // 26x40, +50
        kObjOrbCaught = 0x1db,          // 28x33 flash an orb becomes when caught
        kObjOrbOnGround = 0x1dc,        // 32x7 orb lying on the ground: walking over it on
                                        // its frame 4 gives +8
        kObjOrbBurst14 = 0x1dd,         // 8 small + 4 medium + 2 large
        kObjOrbBurst5 = 0x1de,          // 48x99, 4 small + 1 medium
        kObjOrbBurst9 = 0x1df,          // 5 small + 3 medium + 1 large
        kObjOrbBurst10 = 0x1e0,         // 5 small + 3 medium + 2 large
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CIkumi's own commands (ReadCommand)
    enum {
        kCmd41236A = 0x46,      // 41236 + A (read as 413), within 60 frames
        kCmd41236B = 0x47,      // 41236 + B (read as 413), within 60 frames
        kCmd41236C = 0x48,      // 41236 + C (read as 413), within 60 frames
        kCmd41236D = 0x49,      // 41236 + D (read as 413), within 60 frames
        kCmd236236236C = 0x5e,  // 2 3 6 2 3 6 2 3 6 C, within 110 frames
        kCmd214214A = 0x6e,     // 214214 + A, within 90 frames
        kCmd214214B = 0x6f,     // 214214 + B, within 90 frames
        kCmd214214C = 0x70,     // 214214 + C, within 90 frames
        kCmd214214D = 0x71,     // 214214 + D, within 90 frames
        kCmd4123641236A = 0x96, // 4123641236 + A (read as 4136413), within 135 frames
        kCmd4123641236B = 0x97, // 4123641236 + B (read as 4136413), within 135 frames
        kCmd4123641236C = 0x98, // 4123641236 + C (read as 4136413), within 135 frames
        kCmd4123641236D = 0x99, // 4123641236 + D (read as 4136413), within 135 frames
        kCmd21436A = 0xaa,      // 21436 + A, within 90 frames
        kCmd21436B = 0xab,      // 21436 + B, within 90 frames
        kCmd21436C = 0xac,      // 21436 + C, within 90 frames
        kCmd21436D = 0xad,      // 21436 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x683550
    virtual void UpdatePattern();
    // FUNCTION: 0x694d00
    // UpdatePattern while the alt tables are in: the same actions, with more damage and a
    // few changed loops and cancels
    void UpdatePatternAlt();
    // FUNCTION: 0x6a59c0
    CIkumi(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x6a5c50
    virtual void Reset();
    // FUNCTION: 0x6a5dc0
    ~CIkumi();
    // FUNCTION: 0x6a5e70
    virtual void Load();
    // FUNCTION: 0x6a5eb0
    // Reads ikumi\ikumi2.pat into m_altAnims and m_altPatterns, as CPlayer::LoadPatterns
    // reads ikumi.pat
    void LoadAltPatterns();
    // FUNCTION: 0x6a6270
    virtual void StartPattern();
    // FUNCTION: 0x6a62c0
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x6a6310
    virtual void Move();
    // FUNCTION: 0x6a6330
    virtual void StartCommand();
    // FUNCTION: 0x6a93f0
    virtual void DrawGauge();
    // FUNCTION: 0x6ab060
    virtual void PreUpdate();
    // FUNCTION: 0x6ab6a0
    // p1 1: swaps m_altAnims/m_altPatterns in (anims, every object's anims, m_patterns);
    // 0: puts the base tables back
    void UseAltPatterns(char p1);
    // FUNCTION: 0x6ab7b0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x6ab7e0
    virtual void ReadCommand();
    // FUNCTION: 0x6acc10
    virtual void CpuInput();
    // FUNCTION: 0x6b06f0
    virtual void UpdateObjects();
    // FUNCTION: 0x6b7900
    // UpdateObjects while the alt tables are in: orbs add to m_modeTimer instead of
    // m_stockCharge
    void UpdateObjectsAlt();

    int m_patternVar1; // Scratch for the current action, zeroed by StartPattern: loop
                       // counts, once-flags, saved vx * 100
    int m_patternVar2; // The same, a second one
    int m_patternVar3; // The same, a third one
    int m_encasedBreakOut; // 1 while the shared states 0x53-0x56's object 0x1f0 is out;
                           // cleared when it bursts into 0x1f1/0x1f2
    int m_stockCharge; // Progress to the next stock, 0-99: orbs caught add 10/30/50 (8
                       // from the ground); at 100 it resets and m_stocks rises
    int m_stocks; // Stocks, 0-8 (DrawGauge's pips): specials use their stronger version
                  // at 3+ and 6+ and take one; at 8 Vf8 starts the powered mode (0x12c);
                  // 0xa during the mode
    int m_modeTimer; // Frames left of the powered mode, from 1260 (0x4ec, the bar's full
                     // width); -1 per frame in Vf8, orbs add to it; 0 outside the mode
    int m_orbBurstSpawned; // Set once Vf8 has dropped this action's orb burst on the
                           // opponent (on its first hit); zeroed by StartPattern
    int m_modeTintTimer; // Counts 0 to 0xb9 during the powered mode; Vf8 cycles the
                         // sprite's tint by it
    int m_storedSuperLevel; // Level (1-3) of the strike 21436A/B/C stored; the next 21436
                            // releases it under the opponent for no gauge; 0 none
    int m_objectVar1[0x40]; // Per-object scratch (zeroed by RemoveObject): once-flags and
                            // loop counts
    int m_objectVar2[0x40]; // Per-object scratch: an orb's launch angle, a spark's
                            // lifetime, a pillar's per-cycle hit flag
    int m_objectVar3[0x40]; // Per-object scratch: only double 0x1a4's loop count
    char m_altPatternsIn; // 1 while m_altAnims/m_altPatterns (ikumi2.pat, the powered
                          // mode's faster frame data) are in use; UpdatePattern and
                          // UpdateObjects then hand over to their Alt versions
    BYTE unk3461[0x3464 - 0x3461];
    PTR32(EffectAnim) m_altAnims;    // the second animation and pattern tables
    PTR32(PatternData) m_altPatterns;
    int m_baseAnims; // ikumi.pat's anims, saved as an int by Load so UseAltPatterns(0)
                     // and the destructor can put them back
    int m_basePatterns; // ikumi.pat's m_patterns, saved the same way
    BYTE unk3474[0x3478 - 0x3474];
};

// Exnanase: one of the character classes.
// SIZE: 0x3468
class CEXNanase : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CEXNanase's own actions
    enum {
        k5A = 0xc8,                      // A
        k5BClose = 0xc9,                 // B within 50 px
        k5BFar = 0xca,
        k5C = 0xcb,
        k2A = 0xcc,
        k2B = 0xcd,
        k2C = 0xce,
        kJumpA = 0xcf,
        kJumpB = 0xd0,
        kJumpC = 0xd1,                   // exnanase.cpp
        k6C = 0xd2,                      // 6C (forward + C, not in throw range)
        kUnusedD3 = 0xd3,                // unused
        kAirDiveUnused = 0xd4,           // unused
        kAirDiveRebound = 0xd5,          // only from 0xd4
        kAirDiveLanding = 0xd6,          // only from 0xd4
        kThrow = 0xdc,
        kThrowHit = 0xdd,
        kDashA = 0xe6,
        kDashB = 0xe7,
        kDashC = 0xe8,
        kDash2A = 0xe9,
        kDash2B = 0xea,
        kDash2C = 0xeb,
        kAirThrow = 0xf8,
        kAirThrowHit = 0xf9,
        k41236C = 0xfa,                  // 41236C
        kGrabFollowB = 0xfb,             // 236B or 214B at the end of 0xfe (unless the
                                         // opponent pressed B): toss
        k41236A = 0xfc,                  // 41236A
        k41236B = 0xfd,                  // 41236B
        kGrabHold = 0xfe,                // holds the opponent overhead
        kGrabFollowA = 0xff,             // slam: DealDamage(1500)
        kGrabFollowUnused = 0x100,       // unused: escaped if the opponent pressed A, else
                                         // DealDamage(1800) and 0x190
        kGrabRelease = 0x101,            // no follow-up input: drops the opponent with one
                                         // hit
        kGrabEscaped = 0x102,            // the opponent guessed the follow-up (pressed C
                                         // before an A branch, B before a B branch): they
                                         // go to 0x9e
        kGrabExUnused = 0x103,           // unused C-version grab: costs m_rfGauge, lunges vx
                                         // 1.3, on hit -> 0xfe
        k214A = 0x10f,                   // 214A
        k214B = 0x110,                   // 214B
        k214C = 0x111,                   // 214C with m_rfGauge
        k623A = 0x112,                   // 623A
        k623B = 0x113,                   // 623B
        k623C = 0x114,                   // 623C with m_rfGauge
        kGrabFollowAA = 0x12c,           // from 0xff: 5 hits (50 x4 + 500)
        kGrabFollowUnused2 = 0x12d,      // unused: a 2-level version, DealDamage(2400)
        kGrabFollowAAA = 0x12e,          // from 0x12c: big throw, DealDamage(4200), objects
                                         // 0x19a/0x199/0x198
        k236236Lv1Unused = 0x12f,        // unused copy of Nanase's unarmed 236236
        k236236Lv2Unused = 0x130,        // unused copy
        k236236Lv3Unused = 0x131,        // unused copy
        kGrabFollowAB = 0x132,           // from 0xff (facing flipped): DealDamage(1800),
                                         // object 0x197
        kGrabFollowAAB = 0x133,          // from 0x12c: jump and slam, DealDamage(4500),
                                         // impact 0x19b
        k236236Lv1 = 0x135,              // 236236 1 level
        k236236Lv1Hit = 0x136,           // DealDamage(2300), object 0x190
        k236236Lv2 = 0x137,              // 2 levels
        k236236Lv2Hit = 0x138,           // DealDamage(3300), 0x198
        k236236Lv3 = 0x139,              // 3 levels
        k236236Lv3Hit = 0x13a,           // DealDamage(4900), objects 0x19a/0x199/0x198
        k214214Lv1 = 0x13b,              // 214214 1 level
        k214214Lv2 = 0x13c,              // 2 levels
        k214214Lv3 = 0x13d,              // 3 levels
        kGrabFollowABA = 0x13e,          // from 0x132: runs pushing the opponent (0x63) to
                                         // the wall, DealDamage(3000) there
        kGrabFollowABB = 0x13f,          // from 0x132: ground hit 0x1a2 + 0x19f
        kAwaken = 0x140,                 // automatic (Vf8, exnanase.cpp): gauge 3000, HP <
                                         // 1666, on the ground
        kObjGrabFinishFx = 0x190,        // one-shot of 0x100/0x136
        kObj214AHit = 0x191,             // 214A's: hits once, at frame 0
        kObj214BHit = 0x192,
        kObj214CHit = 0x193,
        kObj623AFx = 0x194,              // glued to her during 0x112, loops 0xf-0x1c until
                                         // frame 7 passes, then plays out
        kObj623BFx = 0x195,              // the same for 0x113
        kObj623CFx = 0x196,              // the same for 0x114
        kObjGrabFollowABFx = 0x197,      // one-shot of 0x132
        kObjFinishFlash = 0x198,         // one-shot at the finish of
                                         // 0x12e/0x138/0x13a/0x13e
        kObjSuperHoldRandom = 0x199,     // 8 at random points during 0x12e/0x13a, hold
                                         // their last frame until 0x198 appears
        kObjSuperHold = 0x19a,           // one at a fixed point, same behaviour as 0x199
        kObjGrabFollowAABImpact = 0x19b, // one-shot at 0x133's landing
        kObj214214Lv1Hit = 0x19c,        // 0x13b's ground hit 60 px ahead, hits at frame 1
        kObj214214Lv2Hit = 0x19d,
        kObj214214Lv3Hit = 0x19e,
        kObj214214Back = 0x19f,          // one-shot on layer 0 with 0x19c-0x19e and 0x1a2
        kObjGrabFollowABAPush = 0x1a0,   // glued 80 px ahead of her while 0x13e is at frame
                                         // <= 10
        kObjGrabFollowABAFx = 0x1a1,     // one-shot each time 0x13e loops
        kObjGrabFollowABBHit = 0x1a2,    // 0x13f's ground hit, hits at frame 1
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CEXNanase's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd41236A = 0x46,  // 41236 + A (read as 413), within 75 frames
        kCmd41236B = 0x47,  // 41236 + B (read as 413), within 75 frames
        kCmd41236C = 0x48,  // 41236 + C (read as 413), within 75 frames
        kCmd41236D = 0x49,  // 41236 + D (read as 413), within 75 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
    };
    // END constants

    // FUNCTION: 0x6be9c0
    virtual void UpdatePattern();
    // FUNCTION: 0x6cfbb0
    CEXNanase(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5,
              BYTE p6);
    // FUNCTION: 0x6cfd80
    virtual void Reset();
    // FUNCTION: 0x6cfed0
    virtual void StartPattern();
    // FUNCTION: 0x6cff10
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x6cff60
    virtual void Move();
    // FUNCTION: 0x6cff80
    virtual void StartCommand();
    // FUNCTION: 0x6d2400
    virtual void DrawGauge();
    // FUNCTION: 0x6d2410
    void Unk6d2410(int p1);
    // FUNCTION: 0x6d2420
    virtual void PreUpdate();
    // FUNCTION: 0x6d2740
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x6d2770
    virtual void ReadCommand();
    // FUNCTION: 0x6d38e0
    virtual void CpuInput();
    // FUNCTION: 0x6d6e40
    virtual void UpdateObjects();

    int m_patternVar1; // Scratch for the current pattern, zeroed by StartPattern; in the
                       // grab chain (0xfe, 0xff, 0x12c, 0x132) the opponent's escape
                       // guess: 1 A, 2 B, 3 C
    int m_patternVar2; // The same, a second one
    int m_patternVar3; // The same, a third one (a 45-frame re-hit timer in 623)
    int m_encasedBreakOut; // 1 while an object 0x1f0 (spawned entering 0x53-0x56) waits
                           // to burst into particles
    int m_finishFlashOut; // 1 while object 0x198 (a super's finishing flash) plays;
                          // objects 0x199/0x19a remove themselves meanwhile
    int m_tintCycle; // While awakened: frames 0-144 of the colour cycle, Tint at every 18
    int m_sparkTimer; // While awakened: frames to the next effect 0x22 on her body (every
                      // 2 frames)
    int m_objectState[0x40]; // Per object: a small state of the object's own code (init
                             // flag of the particles); zeroed by RemoveObject
    int m_objectTimer[0x40]; // Per object: frames left of the particles 0x1f1/0x1f2
    int unk3354[0x40]; // indexed
    int m_awakened; // 1 once 0x140 has run (gauge full, HP < 1666, set by Vf8) until
                    // Reset: gauge +1 a frame, faster animations, walk and jumps
    BYTE unk3458[0x3460 - 0x3458];
    char unk3460;
    BYTE unk3461[0x3468 - 0x3461];
};

// Nayukib: one of the character classes.
// SIZE: 0x3458
class CNayukiB : public CPlayer {
public:
    // BEGIN constants (tools/constants.py declare): CNayukiB's own actions
    enum {
        k5A = 0xc8,
        k5BClose = 0xc9,                      // nayukib.cpp within 70 px
        k5BFar = 0xca,
        k5C = 0xcb,
        k2A = 0xcc,
        k2B = 0xcd,
        k2C = 0xce,                           // nayukib.cpp
        kJumpA = 0xcf,
        kJumpB = 0xd0,
        kJumpC = 0xd1,
        kUnusedD2 = 0xd2,                     // UpdatePattern never entered
        kUnusedD3 = 0xd3,                     // UpdatePattern never entered
        kUnusedAirDive = 0xd4,                // UpdatePattern never entered: to 0xd5 on
                                              // hit, 0xd6 on landing
        kUnusedAirDiveRebound = 0xd5,         // UpdatePattern only from 0xd4
        kUnusedAirDiveLanding = 0xd6,         // UpdatePattern only from 0xd4
        kThrow = 0xdc,                        // nayukib.cpp within 30 px
        kThrowHit = 0xdd,                     // UpdatePattern 1000 damage, opponent to 0x3c
        kDashA = 0xe6,                        // nayukib.cpp A in the forward dash
        kDashB = 0xe7,
        kDashC = 0xe8,
        kDash2A = 0xe9,
        kDash2B = 0xea,                       // nayukib.cpp
        kDash2C = 0xeb,                       // nayukib.cpp
        kAirThrow = 0xf8,
        kAirThrowHit = 0xf9,                  // UpdatePattern 1000 damage, opponent to 0x3c
        k623A = 0xfa,                         // nayukib.cpp 0x14
        k623B = 0xfb,                         // nayukib.cpp 0x15, or 0x16 without EX
        k623C = 0xfc,                         // nayukib.cpp EX
        k236A = 0xfd,                         // nayukib.cpp
        k236B = 0xfe,                         // nayukib.cpp
        k236C = 0xff,                         // nayukib.cpp (no EX)
        k412A = 0x100,                        // nayukib.cpp 0x28 (4,1,2), air too (from
                                              // frame 2)
        k412B = 0x101,                        // nayukib.cpp
        k412C = 0x102,                        // nayukib.cpp EX (tests 0x103's priority, a
                                              // copy slip)
        k214A = 0x103,                        // nayukib.cpp
        k214B = 0x104,                        // nayukib.cpp 0x1f, or 0x20 without EX
        k214C = 0x105,                        // nayukib.cpp EX
        kAir214A = 0x106,
        kAir214B = 0x107,
        kAir214C = 0x108,                     // nayukib.cpp EX
        kAir214214A = 0x12c,                  // nayukib.cpp in the air, level 1
        kAir214214B = 0x12d,                  // nayukib.cpp level 2
        kAir214214C = 0x12e,                  // nayukib.cpp level 3
        k236236A = 0x12f,                     // nayukib.cpp ground, level 1
        k236236B = 0x130,                     // nayukib.cpp level 2
        k236236C = 0x131,                     // nayukib.cpp level 3
        k641236A = 0x132,                     // nayukib.cpp level 1, no orbit running
        k641236B = 0x133,                     // nayukib.cpp level 2
        k641236C = 0x134,                     // nayukib.cpp level 3
        kLv4 = 0x135,                         // nayukib.cpp 0x67 (236236D) with HP below
                                              // 3333 and level 3
        kUnused136 = 0x136,                   // UpdatePattern never entered: stands still
                                              // for 8 loops
        kObj236236A = 0x190,                  // nayukib.cpp rises (1.2, -2.1), 3 hits,
                                              // removed above y -600
        kObj236236B = 0x191,                  // nayukib.cpp 6 hits, sheds a kObj236236Spark
                                              // every 10 frames
        kObj236236C = 0x192,                  // nayukib.cpp 15 hits, a spark every 3 frames
        kObj236236Spark = 0x193,              // nayukib.cpp Random direction and speed, no
                                              // hits (hitsLeft 0)
        kObjSatellite = 0x194,                // nayukib.cpp orbits 50 px around her at
                                              // m_orbitAngle (y squashed to 1/4)
        kObjSatelliteOpposite = 0x195,        // nayukib.cpp the same at m_orbitAngle + 180
        kObjSatelliteSpent = 0x196,           // nayukib.cpp keeps orbiting, then
                                              // kObjSatelliteForming
        kObjSatelliteOppositeSpent = 0x197,
        kObjSatelliteForming = 0x198,         // nayukib.cpp what 0x132-0x134 spawn
        kObjSatelliteOppositeForming = 0x199,
        kObjSatelliteSparkle = 0x19b,         // nayukib.cpp plays once
        kObjLv4Summon1 = 0x19c,               // nayukib.cpp bounces out (Random), lands,
                                              // shows kObjLv4Popup1-5, then hits on frames
                                              // 11-12 twenty times
        kObjLv4Summon2 = 0x19d,               // nayukib.cpp same, voice 0xa
        kObjLv4Summon3 = 0x19e,               // nayukib.cpp same, voice 0xb
        kObjLv4Bomb = 0x19f,                  // nayukib.cpp shows one popup every 15 loops
        kObjLv4Summon4 = 0x1a1,               // nayukib.cpp as Summon1, voice 0xc
        kObjLv4Summon5 = 0x1a2,               // nayukib.cpp releases kObjLv4Summon5Wave 11
                                              // times, voice 0x10
        kObjLv4Summon6 = 0x1a3,               // nayukib.cpp spawns kObjLv4Summon6Hit on its
                                              // frame 11, voice 0xf
        kObjLv4Summon6Left = 0x1a4,           // nayukib.cpp the same moving left (spawned
                                              // instead when she faces left)
        kObjLv4Summon7 = 0x1a5,               // nayukib.cpp becomes kObjLv4Summon7Attack,
                                              // voice 0xe
        kObjLv4Summon7Attack = 0x1a6,         // nayukib.cpp hits (frames 0-4) 11 loops
                                              // shedding kObjLv4Puff, then explodes like
                                              // the bomb
        kObjLv4Summon8 = 0x1a7,               // nayukib.cpp fires kObjLv4Shot, voice 0x12
        kObjLv4Shot = 0x1a8,                  // nayukib.cpp small (17x20), hops then runs
                                              // along the ground at 1, removed off screen
        kObjLv4Summon9 = 0x1a9,               // nayukib.cpp hits on frames 12-15, 16 loops,
                                              // voice 0x11
        kObjLv4Smoke = 0x1ab,                 // nayukib.cpp Random direction and speed,
                                              // plays once (114x114, no hits)
        kObjLv4Puff = 0x1ac,                  // nayukib.cpp Random direction, plays once
                                              // (64x64)
        kObjLv4Spark = 0x1ad,                 // nayukib.cpp 10x10, Random vx, sheds 16
                                              // kObjLv4Puff
        kObjLv4Summon5Wave = 0x1ae,           // nayukib.cpp on the ground below Summon5,
                                              // plays once (172x78)
        kObjLv4Summon6Hit = 0x1af,            // nayukib.cpp the hitting part of Summon6
                                              // (attack on frames 1-12)
        kObjLv4Popup1 = 0x1b1,                // nayukib.cpp drawn above a summon, plays
                                              // once
        kObjLv4Popup2 = 0x1b2,
        kObjLv4Popup3 = 0x1b3,
        kObjLv4Popup4 = 0x1b4,
        kObjLv4Popup5 = 0x1b5,
    };
    // END constants

    // BEGIN constants (tools/constants.py declare): CNayukiB's own commands (ReadCommand)
    enum {
        kCmd412A = 0x28,    // 412 + A, within 45 frames
        kCmd412B = 0x29,    // 412 + B, within 45 frames
        kCmd412C = 0x2a,    // 412 + C, within 45 frames
        kCmd412D = 0x2b,    // 412 + D, within 45 frames
        kCmd263C = 0x60,    // 2 6 3 C, within 60 frames
        kCmd236236A = 0x64, // 236236 + A, within 90 frames
        kCmd236236B = 0x65, // 236236 + B, within 90 frames
        kCmd236236C = 0x66, // 236236 + C, within 90 frames
        kCmd236236D = 0x67, // 236236 + D, within 90 frames
        kCmd214214A = 0x6e, // 214214 + A, within 90 frames
        kCmd214214B = 0x6f, // 214214 + B, within 90 frames
        kCmd214214C = 0x70, // 214214 + C, within 90 frames
        kCmd214214D = 0x71, // 214214 + D, within 90 frames
        kCmd641236A = 0x78, // 641236 + A (read as 6413), within 75 frames
        kCmd641236B = 0x79, // 641236 + B (read as 6413), within 75 frames
        kCmd641236C = 0x7a, // 641236 + C (read as 6413), within 75 frames
        kCmd641236D = 0x7b, // 641236 + D (read as 6413), within 75 frames
    };
    // END constants

    // FUNCTION: 0x730710
    virtual void UpdatePattern();
    // FUNCTION: 0x73e790
    CNayukiB(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x73e970
    virtual void Reset();
    // FUNCTION: 0x73eac0
    virtual void StartPattern();
    // FUNCTION: 0x73eb00
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x73eb50
    virtual void Move();
    // FUNCTION: 0x73eb70
    virtual void StartCommand();
    // FUNCTION: 0x741680
    virtual void DrawGauge();
    // FUNCTION: 0x741ac0
    virtual void PreUpdate();
    // FUNCTION: 0x741bc0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x741bf0
    virtual void ReadCommand();
    // FUNCTION: 0x742eb0
    virtual void CpuInput();
    // FUNCTION: 0x7472c0
    virtual void UpdateObjects();

    int m_patternVar1; // scratch of the current pattern, zeroed by StartPattern; 0x135
                       // keeps vy*100 in it
    int m_patternVar2; // the same; 0x135 keeps vx*100 in it
    int m_patternVar3; // the same: shared states only
    int m_encasedBreakOut; // 1 while the kObjBurst that states 0x53-0x56 spawn is alive
    int m_orbitAngle; // 641236's satellites: degrees 0-359, advanced by m_orbitDirection
                      // each frame (Vf8)
    int m_orbitLevel; // 641236's level, 1-3 (0 = no orbit); a satellite's hit costs
                      // 1000-350*level of m_orbitTime
    int m_orbitTime; // 641236's time left, 3000 down by 2 a frame (Vf8); 0 when she is
                     // hit or a player is KO; DrawGauge's bar
    int m_orbitDirection; // 641236's direction, her facing when it started (+1/-1): the
                          // angle step and the x mirror
    int m_objectVar1[0x40]; // per object, zeroed by RemoveObject: once-flags, loop
                            // counts, kObjLv4Smoke's angle
    int m_objectVar2[0x40]; // per object, zeroed by RemoveObject: spark timers,
                            // kObjLv4Bomb's loop count, speeds
    int m_objectVar3[0x40]; // per object, zeroed by RemoveObject: kObjLv4Bomb's popup
                            // count
};

#ifdef EFZ_TRACE
// src/trace.cpp: the replay test's harness, in make trace and the native build.
void TraceStart(CGame* game, CScene** scenes, BYTE* scene);
int TraceFast();
int TraceQuit(BYTE scene);
void TraceTick(CScene3* scene);
int TraceInput(BYTE player, BYTE* input);
#endif

#endif
