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

#include <windows.h>
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>
#include <math.h>

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
    EffectFrame* frames;
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

    DWORD unk0;
    DWORD unk4;
    DWORD unk8;
    DWORD unkc;
    DWORD unk10;
    DWORD unk14;
    DWORD unk18;
    DWORD unk1c;
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
    void ReleaseSurface(IDirectDrawSurface** surface);
    // FUNCTION: 0x408c70
    // Posts WM_CLOSE to the game window.
    BOOL Close();
    // FUNCTION: 0x408ca0
    BOOL RestorePrimary();
    // FUNCTION: 0x408cd0
    BOOL RestoreSurface(IDirectDrawSurface** surface);
    // FUNCTION: 0x408d00
    // Loads an 8-bit .bmp into a new surface, adding `base` to every pixel; returns
    // the image's rectangle.
    RECT LoadBmp(IDirectDrawSurface** surface, const char* name, BYTE base);
    // FUNCTION: 0x409090
    // The same, but pixels 40 and above map to 175 and up instead of having base added.
    RECT LoadBmpHigh(IDirectDrawSurface** surface, const char* name, BYTE base);
    // FUNCTION: 0x409470
    // Creates a surface from an image inside a .dat file; returns the bytes consumed,
    // or 0 on failure. With rle nonzero, a byte above rle repeats the previous colour
    // (byte - rle) more times.
    int LoadSurface(IDirectDrawSurface** surface, BYTE* data, BYTE rle, BYTE base);
    // FUNCTION: 0x409740
    // LoadSurface with LoadBmpHigh's mapping.
    int LoadSurfaceHigh(IDirectDrawSurface** surface, BYTE* data, BYTE rle, BYTE base);
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
    IDirectDraw* m_dd;
    IDirectDrawSurface* m_primary;
    IDirectDrawSurface* m_back;
    IDirectDrawPalette* m_ddpal;
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
    IDirectInput7* m_di;
    IDirectInputDevice7* m_keyboard;
    IDirectInputDevice7* m_joysticks[2];
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
    IDirectSound* m_ds;
    BYTE* m_data[0x96];
    DWORD m_size[0x96];
    IDirectSoundBuffer* m_buffers[0x96];
};

// One frame of a pattern's data (boxes, physics values), copied whole by some scenes.
// No byte arrays in here: /GS would then protect every function with one as a local.
struct PatternFrame {
    RECT boxes[5];      // probably hurtboxes
    RECT attackBoxes[4];
    RECT box90;
    short unka0;
    short unka2;
    float unka4;
    short unka8;
    WORD flagsAA;
    short unkac;
    short unkae;
    WORD flagsB0;
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

// A player's frame, position and facing, gathered for CScene3's collision checks.
struct CollisionInfo {
    PatternFrame frame;
    EffectFrame anim;
    double x;
    double y;
    char facing;        // CPlayer+0x50
    char unke9;         // CPlayer+0x168
    short unkea;        // CPlayer+0x16c
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
            operator delete((void*)v4);
        }
    }
    // FUNCTION: 0x412ad0
    void Alloc(int p1)
    {
        int v4;

        if (p1 > 0) {
            v4 = (int)operator new(p1 * 0xc8);
            frames = (PatternFrame*)v4;
        }
    }

    short unk0;
    short unk2;
    PatternFrame* frames;
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
    EffectAnim* anims; // +8: the character's sprite animations, one per pattern
    IDirectDrawSurface** surfaces; // +0xc: the character's sprites
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
    int unk58;
    RECT clip;        // +0x5c: drawn clipped to it unless top == bottom
    char unk6c;
    BYTE unk6d[3];
    double unk70;
    double unk78;
    int unk80;
    short unk84;
    short unk86;
    int unk88;
    int unk8c;
    BYTE unk90[8];
};

// The last 60 positions of a player, for drawing afterimages: x and y, facing, pattern
// and frame. Kept at CPlayer+0x2bc0.
struct Afterimages {
    // FUNCTION: 0x412840
    Afterimages()
    {
        pos = 0;
        unk0 = 0;
        unk2 = 0;
    }
    // FUNCTION: 0x412910
    void Unk412910()
    {
        unk2 = unk0 * 3;
        unk0 = 0;
    }
    // FUNCTION: 0x412930
    void Unk412930(ObjBase* p1)
    {
        unk1 = unk0;
        unk2 = 0;
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
    void Unk412a10(ObjBase* p1, char p2)
    {
        int v4;

        if (unk0 == 0 && unk2 == 0) {
            v4 = 0;
            for (; v4 < 0x3c; v4++) {
                x[v4] = p1->x;
                y[v4] = p1->y;
                facing[v4] = p1->facing;
                pattern[v4] = p1->pattern;
                frame[v4] = p1->frame;
            }
        }
        unk0 = p2;
        unk1 = p2;
    }

    BYTE unk0;
    BYTE unk1;
    BYTE unk2;
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
class CPlayer : public ObjBase {
public:
    // FUNCTION: 0x40e630
    // Faces the opponent; returns whether the facing changed.
    int FaceOpponent();
    // FUNCTION: 0x40e6c0
    // The same towards x = p1.
    int FaceX(double p1);
    // FUNCTION: 0x40e740
    void Unk40e740();
    // FUNCTION: 0x40eae0
    CPlayer(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    void Unk40f230();
    // FUNCTION: 0x40f470
    void Unk40f470();
    // FUNCTION: 0x40f580
    void Unk40f580();
    // FUNCTION: 0x40f980
    void Unk40f980();
    // FUNCTION: 0x40ff70
    char Unk40ff70();
    // FUNCTION: 0x410050
    int Unk410050(PatternFrame* p1, PatternFrame* p2);
    // FUNCTION: 0x4100f0
    int Unk4100f0(PatternFrame* p1);
    // FUNCTION: 0x4102e0
    int Unk4102e0();
    // FUNCTION: 0x410340
    int Unk410340();
    // FUNCTION: 0x4103a0
    int Unk4103a0();
    // FUNCTION: 0x410420
    int Unk410420();
    // FUNCTION: 0x410480
    // The attacker's damage factor, 1 + unk118 / 10000, scaled by the game settings.
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
    void Unk410790(PatternFrame* p1);
    // FUNCTION: 0x410840
    void AddScore(int p1);
    // FUNCTION: 0x4108a0
    // A random number from p1 up to p2: rand() while recording a replay, which stores it,
    // or the replay's next word when playing one back (docs/compat.md).
    short Random(short p1, short p2);
    // FUNCTION: 0x410940
    void Unk410940();
    // FUNCTION: 0x4109d0
    // Starts drawing afterimages (m_afterimages), for p1.
    void StartAfterimages(BYTE p1);
    // FUNCTION: 0x410a10
    // Shakes the screen p1 pixels, holding for p2 frames.
    void ShakeScreen(int p1, int p2);
    // FUNCTION: 0x410a40
    void Unk410a40(int p1, int p2);
    // FUNCTION: 0x410a80
    void Unk410a80(int p1, int p2);
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
    void Unk4121a0(int p1, int p2);
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
    virtual void Vf8() = 0;
    // FUNCTION: 0x412b10
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x412e60
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x410b70
    virtual void Load();
    // FUNCTION: 0x40edf0
    virtual void Reset();

    char unk58;
    BYTE unk59[0x60 - 0x59];
    int unk60;
    BYTE unk64[0x78 - 0x64];
    CPlayer** m_opponent;   // +0x78: the other player's slot, g_player1 or g_player2. Set
                            // first: initialized before m_afterimages
    CGame* m_game;          // +0x7c
    CGraphics* m_graphics;  // +0x80
    CInput* m_input;        // +0x84
    CSound* m_sound;        // +0x88
    char m_side;            // +0x8c: 0 for player 1, 1 for player 2
    char m_charId;          // +0x8d: the character's number on the select screen
    char m_paletteIndex;    // +0x8e: which <name>N.pal (N = index + 1)
    BYTE unk8f[0x94 - 0x8f];
    char m_name[0x10];      // +0x94: the character's folder and file name, "akane"
    int m_cpu;
    float unka8;
    char unkac;
    BYTE unkad[0xb0 - 0xad];
    double unkb0;
    double unkb8;
    double unkc0;
    double unkc8;
    int unkd0;
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
    int unk110;
    BYTE unk114[0x118 - 0x114];
    double unk118;
    char unk120;
    BYTE unk121[0x124 - 0x121];
    short unk124;
    BYTE unk126[0x128 - 0x126];
    int unk128;
    int unk12c;
    char unk130;
    BYTE unk131[0x134 - 0x131];
    float unk134;
    short unk138;
    short unk13a;
    short unk13c;
    short unk13e;
    short unk140;
    BYTE unk142[0x144 - 0x142];
    int unk144;
    short m_gauge;          // +0x148: the power gauge, a level per 1000, up to 3000
    short unk14a;
    short unk14c;
    short unk14e;
    int unk150;
    int unk154;
    BYTE unk158;
    BYTE unk159;
    BYTE unk15a;
    BYTE unk15b;
    int unk15c;
    int unk160;
    PatternData* m_patterns; // +0x164: one per pattern, 505 of them
    int m_attackResult;     // +0x168: of the current attack: 0 none yet, 2 guarded, 3 hit,
                            // 6 clashed
    short m_hitsLeft;       // +0x16c: hits the current attack can still land
    BYTE unk16e[0x170 - 0x16e];
    int unk170;
    short m_comboHits;      // +0x174: hits in the current combo
    BYTE unk176[0x178 - 0x176];
    double m_proration;     // +0x178: the combo's damage scaling, 10000 = 100%
    double m_defense;       // +0x180: the defender's damage factor, 1.0
    // This frame's input (Unk410b70): the direction relative to facing (1 forward, -1
    // back), up (-1) or down (1), and whether A-D went down this frame.
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
    int unk1a0;
    int unk1a4;
    BYTE m_bufferedPress;   // +0x1a8: the last button input during a special move
                            // (pattern 0xc8 and up), in m_inputHistory's bits
    BYTE m_dashBufferedPress; // +0x1a9: the same during a dash (0xa3-0xa6)
    BYTE m_dashBufferTime;  // +0x1aa: frames m_dashBufferedPress is kept, from 15
    // The last 180 frames of input, a ring buffer: bits 1 forward, 2 back, 4 down, 8 up,
    // 0x10-0x80 the buttons that went down.
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
    int unk2d0[0x40];       // one per object
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
    int unk30dc;
    int unk30e0;
    int unk30e4;
    int unk30e8;
    short unk30ec;
    short unk30ee;
    int unk30f0;
    char m_resultPictures;  // +0x30f4: results pictures system\<name>\NN.dat to choose
                            // from at random
    char m_rivals[0x14];    // +0x30f5: m_charIds with a results picture of their own,
                            // NN = 10 + index; -1 for none
    BYTE unk3109[0x3110 - 0x3109];
    int m_cpuRoll;          // +0x3110: CpuInput's random number, Random(0, 100) or (0, 1000)
    int m_cpuAction;        // +0x3114: what CpuInput decided to do
    int unk3118;
    int unk311c;
    int unk3120;
    DWORD unk3124;
    int unk3128;
    BYTE unk312c[0x3130 - 0x312c];
    DWORD unk3130;
    DWORD unk3134;
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
    BYTE facing;  // an object's; copied to Effect::unk48 for an effect
    BYTE unk19;
    short unk1a;
    int side;
    BYTE scale;  // copied to Effect's
    BYTE layer;
    short unk22;
    int screen;
    int unk28;
    BYTE unk2c;  // copied to Effect::unk6c
    BYTE unk2d;
    short unk2e;
    int unk30;
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
    void LoadDat(IDirectDrawSurface** surface, const char* name, BYTE rle, BYTE offset);
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
    void Unk407ce0(BYTE value);
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
    void Unk4080c0(int value);
    // FUNCTION: 0x408100
    // Sets m_extraChars: 1 if all six extra characters' files exist, 0 if one of
    // misuzu, minagi or kano is missing, -1 if one of exnanase, ikumi or kaori is.
    void CheckExtraChars();

    CGraphics* m_graphics;
    CInput* m_input;
    CSound* m_sound;
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
    IDirectDrawSurface* m_surfaces[0x398]; // effect sprites
    IDirectDrawSurface* unke98;
    IDirectDrawSurface* unke9c;
    IDirectDrawSurface* m_objectSurface;   // system\object.dat
    WORD m_sounds[0x41];          // sound IDs; 0x96 means none
    WORD m_music;                 // sound ID of the music; passed to the sound system every frame
    int m_musicTarget;
    int m_musicVolume;
    short m_musicStep;
    char unkf32;
    BYTE m_fillSide;              // whose background fill shows when both players have one
    char m_colorKey;              // the object sprite's transparent colour
    PALETTEENTRY m_palette[0x100];
    char unk1335[3];
    int unk1338[2];         // one per player
    char unk1340;
    char m_extraChars;
    char unk1342;
    BYTE unk1343[2];        // one per player
    BYTE unk1345;
    BYTE unk1346;
    BYTE unk1347;
    int unk1348;
    char m_winner;                // the side the results screen (CScene5) shows
    char unk134d;
    char unk134e;
    char unk134f;
    char unk1350;
    char unk1351;
    short unk1352;
    int unk1354;
    char unk1358;
    BYTE unk1359[0x135c - 0x1359];
    int unk135c;
    int unk1360;
    char unk1364;
    char unk1365;
    char unk1366;
    char unk1367;
    BOOL unk1368;                 // toggled every frame by WinMain
    int unk136c;
    char unk1370;
    char unk1371[3];
    BOOL unk1374;
    char unk1378;
    char unk1379;
    BYTE unk137a[2];
    CAnimBg* m_background;        // the stage's animated background, if it has one
    short m_effectHead;           // next slot CreateEffect uses
    short m_effectTail;           // oldest live slot
    int m_effectActive[0x280];
    int m_effectUnk1d84[0x280];
    BYTE m_effectUnk2784[0x280];
    char unk2a04[4];
    Effect m_effects[0x280];
    EffectAnim* m_effectAnims;
    short unk1420c;
    short unk1420e;
    double m_shake;               // amplitude in pixels
    int m_shakeHold;              // frames before the amplitude starts to decay
    int m_shakeX;
    int m_shakeY;
    double m_shakeAngleX;         // degrees
    double m_shakeAngleY;
    int unk14238;
    int unk1423c;
    int unk14240;
    int unk14244;
    RECT m_view;            // +0x14248: the part of the stage on screen, set by CScene3
    double unk14258;
    double m_fade;                // -100 to 100
    int m_fadeHold;
    char m_fadeDir;               // 1: FlashWhite, -1: FlashBlack, 0: none
    int m_fadeIn;
    int m_fadeOut;
    int unk14278;
    BOOL unk1427c;
    BYTE unk14280;
    char unk14281;
    char unk14282;
    char m_replayMode;      // 1 playing a replay back, 2 recording one
    CReplayFile m_replay;
    int unk14294;                 // spawn counter for the ellipse effects (0x26, 0x35, 0x36)
    int unk14298;                 // random angle in degrees, 0..359
    int unk1429c;                 // unk14298 plus 30..149 degrees
    int unk142a0;
    int unk142a4;
    char unk142a8[0x142f0 - 0x142a8];
};

// Base of the scenes WinMain runs: Update returns the index of the next scene. The
// constructor and the fades are inline; their copies follow the first scene object.
class CScene {
public:
    // FUNCTION: 0x759c10
    CScene(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6,
           CSound* p7)
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
        unk2c = -1;
        unk2d = 0;
    }
    // FUNCTION: 0x759c90
    // Darkens (p2 0) or brightens (p2 1) the palette over 21 frames, drawing each one, and
    // fades the music volume with it.
    void Unk759c90(PALETTEENTRY* p1, BYTE p2, int p3, int p4)
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
    void Unk759e20(PALETTEENTRY* p1, BYTE p2)
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
    virtual void Vf2() = 0;

    UINT lastMessage;       // set by WndProc to the message it is handling
    HWND m_hwnd;
    CPlayer* m_players[2];  // the players when the scene was made
    CPlayer** m_player1Ref; // WinMain's g_player1 and g_player2
    CPlayer** m_player2Ref;
    CGame* m_game;
    CGraphics* m_graphics;
    CInput* m_input;
    CSound* m_sound;
    char unk2c;
    char unk2d;
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
    void Unk751030();

    virtual void Vf0() = 0;
    virtual void Vf1(int p1, int p2, char p3) = 0;

    short m_number;         // +4: NN in system\bg\bgNN
    short m_lastFrame;      // +6: frames 0 to m_lastFrame
    CGraphics* m_graphics;  // +8
    IDirectDrawSurface** m_surfaces; // +0xc: one per frame
    BgObject* m_objects;    // +0x10
    EffectAnim* m_anims;    // +0x14
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
    virtual void Vf0();
    // FUNCTION: 0x751730
    virtual void Vf1(int p1, int p2, char p3);

    BYTE unk[0x1c - sizeof(CAnimBg)];
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
    virtual void Vf0();
    // FUNCTION: 0x751df0
    virtual void Vf1(int p1, int p2, char p3);

    BYTE unk[0x1c - sizeof(CAnimBg)];
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
    virtual void Vf0();
    // FUNCTION: 0x752470
    virtual void Vf1(int p1, int p2, char p3);

    BYTE unk[0x1c - sizeof(CAnimBg)];
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
    virtual void Vf0();
    // FUNCTION: 0x752dc0
    virtual void Vf1(int p1, int p2, char p3);

    BYTE unk[0x1c - sizeof(CAnimBg)];
};

// Scene1: derived from CScene.
// SIZE: 0x560
class CScene1 : public CScene {
public:
    // FUNCTION: 0x753260
    CScene1(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x7538b0
    ~CScene1();
    // FUNCTION: 0x7539f0
    virtual BYTE Update();
    // FUNCTION: 0x755500
    virtual void Draw();
    // FUNCTION: 0x7586b0
    void Unk7586b0(CPlayer** p1, CPlayer** p2, char p3);
    // FUNCTION: 0x759460
    void Unk759460();
    // FUNCTION: 0x7595d0
    void Unk7595d0(char p1);
    // FUNCTION: 0x759770
    virtual void Vf2();
    // FUNCTION: 0x7598d0
    void Unk7598d0();

    BYTE unk430[0x434 - 0x430];
    int unk434;
    int unk438;
    int unk43c;
    int unk440;
    int unk444[0x2]; // indexed
    char unk44c[0x4]; // indexed
    double unk450;
    double unk458;
    double unk460;
    double unk468;
    double unk470;
    int unk478;
    int unk47c[0x6]; // indexed
    short unk494[0x2]; // indexed
    short unk498[0x2]; // indexed
    BYTE unk49c[0x2]; // indexed
    char unk49e[0x2]; // indexed
    char unk4a0[0x19]; // indexed
    char unk4b9[0x18]; // indexed
    BYTE unk4d1[0x4d4 - 0x4d1];
    int unk4d4[0x18]; // indexed
    BYTE unk534[0x538 - 0x534];
    char unk538[0x2]; // indexed
    char unk53a[0x2]; // indexed
    char unk53c[0x2]; // indexed
    char unk53e[0x2]; // indexed
    short unk540[0x2]; // indexed
    BYTE unk544[0xd]; // indexed
    char unk551;
    char unk552;
    char unk553;
    char unk554;
    BYTE unk555[0x556 - 0x555];
    char unk556;
    char unk557;
    char unk558;
    char unk559;
    char unk55a;
    BYTE unk55b[0x560 - 0x55b];
};

// Scene6: derived from CScene.
// SIZE: 0x760
class CScene6 : public CScene {
public:
    // FUNCTION: 0x759f30
    CScene6(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x75a3b0
    ~CScene6();
    // FUNCTION: 0x75a4c0
    virtual BYTE Update();
    // FUNCTION: 0x75b0a0
    virtual void Draw();
    // FUNCTION: 0x75d260
    void Unk75d260(int p1, int p2, int p3);
    // FUNCTION: 0x75d350
    virtual void Vf2();
    // FUNCTION: 0x75d400
    void Unk75d400();
    // FUNCTION: 0x75d580
    void Unk75d580();
    // FUNCTION: 0x75d660
    void Unk75d660();
    // FUNCTION: 0x75d8d0
    void Unk75d8d0(int p1);
    // FUNCTION: 0x75d970
    void Unk75d970(BYTE p1);
    // FUNCTION: 0x75da30
    void Unk75da30(BYTE p1);

    BYTE unk430[0x434 - 0x430];
    int unk434;
    int unk438;
    int unk43c;
    int unk440;
    int unk444;
    char unk448;
    char unk449;
    char unk44a;
    BYTE unk44b[0x3]; // indexed
    BYTE unk44e[0x450 - 0x44e];
    CharRecord m_record;    // +0x450: the shown character's
    char m_names[0x18][0x1e]; // +0x470: the characters' folder names
    char unk740;
    char unk741;
    BYTE unk742[0x748 - 0x742];
    double unk748;
    int unk750;
    int unk754;
    int unk758;
    BYTE unk75c[0x760 - 0x75c];
};

// Scene3: derived from CScene.
// SIZE: 0x598
class CScene3 : public CScene {
public:
    // FUNCTION: 0x75db70
    void Unk75db70(int p1, int p2, int p3, BYTE p4, BYTE p5, int p6);
    // FUNCTION: 0x75dd50
    void Unk75dd50();
    // FUNCTION: 0x75e240
    void Unk75e240();
    // FUNCTION: 0x760060
    void Unk760060();
    // FUNCTION: 0x7623b0
    void Unk7623b0(CPlayer* p1);
    // FUNCTION: 0x762c50
    void Unk762c50();
    // FUNCTION: 0x7631f0
    void Unk7631f0();
    // FUNCTION: 0x7633a0
    CScene3(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x763c00
    ~CScene3();
    // FUNCTION: 0x763c20
    virtual BYTE Update();
    // FUNCTION: 0x7642a0
    virtual void Draw();
    // FUNCTION: 0x7647b0
    void Unk7647b0();
    // FUNCTION: 0x764db0
    void Unk764db0();
    // FUNCTION: 0x764f10
    void Unk764f10();
    // FUNCTION: 0x765040
    void Unk765040();
    // FUNCTION: 0x765660
    virtual void Vf2();
    // FUNCTION: 0x765fa0
    int Unk765fa0();
    // FUNCTION: 0x766070
    void Unk766070();
    // FUNCTION: 0x7661a0
    void Unk7661a0();
    // FUNCTION: 0x766480
    void Unk766480();
    // FUNCTION: 0x766b50
    void Unk766b50();
    // FUNCTION: 0x767600
    RECT Unk767600(ObjBase* p1, RECT* p2);
    // FUNCTION: 0x7677a0
    RECT Unk7677a0(CollisionInfo* p1, RECT* p2);
    // FUNCTION: 0x767930
    int Unk767930(RECT* p1, RECT* p2);
    // FUNCTION: 0x7679b0
    int Unk7679b0(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4);
    // FUNCTION: 0x767f60
    void Unk767f60(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4);
    // FUNCTION: 0x7697d0
    void Unk7697d0(CPlayer* p1, CPlayer* p2, int p3, CollisionInfo* p4);
    // FUNCTION: 0x76b090
    void Unk76b090(CPlayer* p1, CPlayer* p2, int p3, int p4);
    // FUNCTION: 0x76bab0
    void Unk76bab0(CPlayer* p1, CPlayer* p2, int p3, int p4);
    // FUNCTION: 0x76bd40
    void Unk76bd40(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4, int p5);

    BYTE unk430[0x434 - 0x430];
    int unk434;
    int unk438;
    int unk43c;
    int unk440;
    int unk444;
    int unk448;
    int unk44c;
    int unk450;
    int unk454;
    int unk458;
    int unk45c;
    int unk460;
    RECT unk464[0x11];      // indexed
    short unk574;
    short unk576;
    BYTE unk578;
    BYTE unk579[0x580 - 0x579];
    double unk580;
    int unk588;
    int unk58c;
    int unk590;
    BYTE unk594[0x598 - 0x594];
};

// Scene2: derived from CScene.
// SIZE: 0x438
class CScene2 : public CScene {
public:
    // FUNCTION: 0x76c6f0
    CScene2(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x76c740
    ~CScene2();
    // FUNCTION: 0x76c790
    virtual BYTE Update();
    // FUNCTION: 0x76c980
    virtual void Draw();
    // FUNCTION: 0x76ca50
    void Unk76ca50();
    // FUNCTION: 0x76da10
    virtual void Vf2();
    // FUNCTION: 0x76da20
    void Unk76da20(CPlayer** p1, CPlayer** p2, char p3, char p4);

    BYTE unk430[0x434 - 0x430];
    int unk434;
};

// Scene8: derived from CScene.
// SIZE: 0x758
class CScene8 : public CScene {
public:
    // FUNCTION: 0x76e480
    CScene8(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x76efe0
    ~CScene8();
    // FUNCTION: 0x76f060
    virtual BYTE Update();
    // FUNCTION: 0x76f780
    virtual void Draw();
    // FUNCTION: 0x770d80
    virtual void Vf2();
    // FUNCTION: 0x770e30
    void Unk770e30();
    // FUNCTION: 0x771170
    void Unk771170();
    // FUNCTION: 0x771230
    void Unk771230();

    BYTE unk430[0x434 - 0x430];
    int unk434;
    int unk438;
    int unk43c;
    int unk440;
    BYTE unk444[0x446 - 0x444];
    short unk446;
    short unk448;
    short unk44a;
    short unk44c;
    BYTE unk44e[0x13]; // indexed
    BYTE unk461[0x462 - 0x461];
    char unk462;
    char unk463;
    char unk464;
    char unk465;
    BYTE unk466[0x467 - 0x466];
    char unk467;
    BYTE unk468[0x469 - 0x468];
    char unk469;
    char unk46a;
    char unk46b;
    char unk46c;
    char unk46d;
    char unk46e[0x2da]; // indexed
    double unk748;
    double unk750;
};

// Scene5: derived from CScene.
// SIZE: 0x474
class CScene5 : public CScene {
public:
    // FUNCTION: 0x7712f0
    CScene5(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x771400
    ~CScene5();
    // FUNCTION: 0x7714e0
    virtual BYTE Update();
    // FUNCTION: 0x772800
    virtual void Draw();
    // FUNCTION: 0x774a10
    void Unk774a10(int p1, int p2, int p3);
    // FUNCTION: 0x774b00
    void Unk774b00();
    // FUNCTION: 0x775750
    virtual void Vf2();

    BYTE unk430[0x434 - 0x430];
    int unk434;
    int unk438;
    int unk43c;
    int unk440;
    short unk444;
    short unk446;
    short unk448;
    short unk44a;
    short unk44c;
    short unk44e;
    short unk450;
    short unk452;
    short unk454;
    short unk456;
    short unk458;
    short unk45a;
    short unk45c;
    char unk45e;
    char unk45f;
    char unk460;
    BYTE unk461[0x464 - 0x461];
    int unk464;
    int unk468;
    int unk46c;
    int unk470;
};

// Scene7: derived from CScene.
// SIZE: 0x448
class CScene7 : public CScene {
public:
    // FUNCTION: 0x7758b0
    CScene7(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x7759a0
    ~CScene7();
    // FUNCTION: 0x7759f0
    virtual BYTE Update();
    // FUNCTION: 0x775b80
    virtual void Draw();
    // FUNCTION: 0x775d50
    virtual void Vf2();

    BYTE unk430[0x434 - 0x430];
    int unk434;
    double unk438;
    int unk440;
    BYTE unk444[0x448 - 0x444];
};

// Scene0: derived from CScene.
// SIZE: 0x44c
class CScene0 : public CScene {
public:
    // FUNCTION: 0x775d60
    CScene0(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7);
    // FUNCTION: 0x775f30
    ~CScene0();
    // FUNCTION: 0x775fb0
    virtual BYTE Update();
    // FUNCTION: 0x7764b0
    virtual void Draw();
    // FUNCTION: 0x776760
    virtual void Vf2();
    // FUNCTION: 0x776820
    void Unk776820();
    // FUNCTION: 0x7768d0
    void Unk7768d0();

    BYTE unk430[0x434 - 0x430];
    int unk434;
    int unk438;
    char unk43c;
    BYTE unk43d[0x43e - 0x43d];
    short unk43e;
    BYTE unk440[0x3]; // indexed
    BYTE unk443[0x444 - 0x443];
    DWORD unk444;
    int unk448;
};

// Shiori: one of the character classes.
// SIZE: 0x3458
class CShiori : public CPlayer {
public:
    // FUNCTION: 0x4136d0
    virtual void UpdatePattern();
    // FUNCTION: 0x422d70
    CShiori(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x4261c0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4261f0
    virtual void ReadCommand();
    // FUNCTION: 0x4276b0
    virtual void CpuInput();
    // FUNCTION: 0x42b190
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158[0x40]; // indexed
    int unk3258[0x40]; // indexed
    int unk3358[0x40]; // indexed
};

// Sayuri: one of the character classes.
// SIZE: 0x3458
class CSayuri : public CPlayer {
public:
    // FUNCTION: 0x434060
    virtual void UpdatePattern();
    // FUNCTION: 0x4463e0
    CSayuri(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x449390
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4493c0
    virtual void ReadCommand();
    // FUNCTION: 0x44ab30
    virtual void CpuInput();
    // FUNCTION: 0x44db60
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154[0x40]; // indexed
    int unk3254[0x40]; // indexed
    int unk3354[0x40]; // indexed
    BYTE unk3454[0x3458 - 0x3454];
};

// Nayuki: one of the character classes.
// SIZE: 0x3460
class CNayuki : public CPlayer {
public:
    // FUNCTION: 0x451850
    virtual void UpdatePattern();
    // FUNCTION: 0x461090
    CNayuki(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x464190
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4641c0
    virtual void ReadCommand();
    // FUNCTION: 0x4654a0
    virtual void CpuInput();
    // FUNCTION: 0x468870
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158;
    int unk315c[0x40]; // indexed
    int unk325c[0x40]; // indexed
    int unk335c[0x40]; // indexed
    BYTE unk345c[0x3460 - 0x345c];
};

// Mizukab: one of the character classes.
// SIZE: 0x3460
class CMizukaB : public CPlayer {
public:
    // FUNCTION: 0x4c04b0
    virtual void UpdatePattern();
    // FUNCTION: 0x4d2850
    CMizukaB(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x4d5aa0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4d5ad0
    virtual void ReadCommand();
    // FUNCTION: 0x4d6f50
    virtual void CpuInput();
    // FUNCTION: 0x4db160
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148[0x40]; // indexed
    int unk3248[0x40]; // indexed
    int unk3348[0x40]; // indexed
    int unk3448;
    int unk344c;
    int unk3450;
    int unk3454;
    int unk3458;
    int unk345c;
};

// Mizuka: one of the character classes.
// SIZE: 0x3460
class CMizuka : public CPlayer {
public:
    // FUNCTION: 0x4e7ec0
    virtual void UpdatePattern();
    // FUNCTION: 0x4f8300
    CMizuka(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x4faf40
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4faf70
    virtual void ReadCommand();
    // FUNCTION: 0x4fdc10
    virtual void CpuInput();
    // FUNCTION: 0x501e20
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148[0x40]; // indexed
    int unk3248[0x40]; // indexed
    int unk3348[0x40]; // indexed
    int unk3448;
    int unk344c;
    int unk3450;
    int unk3454;
    int unk3458;
    BYTE unk345c[0x3460 - 0x345c];
};

// Misuzu: one of the character classes.
// SIZE: 0x3488
class CMisuzu : public CPlayer {
public:
    // FUNCTION: 0x50c4b0
    virtual void UpdatePattern();
    // FUNCTION: 0x519e00
    CMisuzu(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x51df30
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x51df60
    virtual void ReadCommand();
    // FUNCTION: 0x51f3e0
    virtual void CpuInput();
    // FUNCTION: 0x5236d0
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158[0x40]; // indexed
    int unk3258[0x40]; // indexed
    int unk3358[0x40]; // indexed
    int unk3458;
    int unk345c;
    int unk3460;
    int unk3464;
    int unk3468;
    int unk346c;
    int unk3470;
    int unk3474;
    int unk3478;
    int unk347c;
    int unk3480;
    BYTE unk3484[0x3488 - 0x3484];
};

// Mishio: one of the character classes.
// SIZE: 0x3478
class CMishio : public CPlayer {
public:
    // FUNCTION: 0x530bc0
    virtual void UpdatePattern();
    // FUNCTION: 0x546480
    CMishio(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x54ad50
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x54ad80
    virtual void ReadCommand();
    // FUNCTION: 0x54c250
    virtual void CpuInput();
    // FUNCTION: 0x54fd30
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158;
    int unk315c;
    int unk3160;
    int unk3164;
    int unk3168;
    int unk316c;
    int unk3170;
    int unk3174[0x40]; // indexed
    int unk3274[0x40]; // indexed
    int unk3374[0x40]; // indexed
    BYTE unk3474[0x3478 - 0x3474];
};

// Misaki: one of the character classes.
// SIZE: 0x3448
class CMisaki : public CPlayer {
public:
    // FUNCTION: 0x5571f0
    virtual void UpdatePattern();
    // FUNCTION: 0x567900
    CMisaki(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x56a610
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x56a640
    virtual void ReadCommand();
    // FUNCTION: 0x56b630
    virtual void CpuInput();
    // FUNCTION: 0x56f920
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148[0x40]; // indexed
    int unk3248[0x40]; // indexed
    int unk3348[0x40]; // indexed
};

// Mio: one of the character classes.
// SIZE: 0x3458
class CMio : public CPlayer {
public:
    // FUNCTION: 0x5736d0
    virtual void UpdatePattern();
    // FUNCTION: 0x588310
    CMio(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x58dac0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x58daf0
    virtual void ReadCommand();
    // FUNCTION: 0x58ee20
    virtual void CpuInput();
    // FUNCTION: 0x594ea0
    virtual void UpdateObjects();

    int unk3138;
    BYTE unk313c[0x3140 - 0x313c];
    double unk3140;
    double unk3148;
    int unk3150;
    int unk3154;
    int unk3158[0x40]; // indexed
    int unk3258[0x40]; // indexed
    int unk3358[0x40]; // indexed
};

// Minagi: one of the character classes.
// SIZE: 0x3458
class CMinagi : public CPlayer {
public:
    // FUNCTION: 0x59c4a0
    virtual void UpdatePattern();
    // FUNCTION: 0x5a9fa0
    CMinagi(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x5ad520
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x5ad550
    virtual void ReadCommand();
    // FUNCTION: 0x5aea20
    virtual void CpuInput();
    // FUNCTION: 0x5b2d10
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154[0x40]; // indexed
    int unk3254[0x40]; // indexed
    int unk3354[0x40]; // indexed
    BYTE unk3454[0x3458 - 0x3454];
};

// Mayu: one of the character classes.
// SIZE: 0x3448
class CMayu : public CPlayer {
public:
    // FUNCTION: 0x5c8580
    virtual void UpdatePattern();
    // FUNCTION: 0x5dddf0
    CMayu(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x5e1080
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x5e10b0
    virtual void ReadCommand();
    // FUNCTION: 0x5e2440
    virtual void CpuInput();
    // FUNCTION: 0x5e5c30
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148[0x40]; // indexed
    int unk3248[0x40]; // indexed
    int unk3348[0x40]; // indexed
};

// Makoto: one of the character classes.
// SIZE: 0x3450
class CMakoto : public CPlayer {
public:
    // FUNCTION: 0x5e85f0
    virtual void UpdatePattern();
    // FUNCTION: 0x5f6d90
    CMakoto(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x5f9d40
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x5f9d70
    virtual void ReadCommand();
    // FUNCTION: 0x5fb040
    virtual void CpuInput();
    // FUNCTION: 0x5ff4c0
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c[0x40]; // indexed
    int unk324c[0x40]; // indexed
    int unk334c[0x40]; // indexed
    BYTE unk344c[0x3450 - 0x344c];
};

// Mai: one of the character classes.
// SIZE: 0x3458
class CMai : public CPlayer {
public:
    // FUNCTION: 0x607930
    virtual void UpdatePattern();
    // FUNCTION: 0x6163b0
    CMai(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x61a830
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x61a860
    virtual void ReadCommand();
    // FUNCTION: 0x61b9a0
    virtual void CpuInput();
    // FUNCTION: 0x61f750
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158[0x40]; // indexed
    int unk3258[0x40]; // indexed
    int unk3358[0x40]; // indexed
};

// Kanna: one of the character classes.
// SIZE: 0x3458
class CKanna : public CPlayer {
public:
    // FUNCTION: 0x667570
    virtual void UpdatePattern();
    // FUNCTION: 0x675c80
    CKanna(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x677e30
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x677e60
    virtual void ReadCommand();
    // FUNCTION: 0x678c30
    virtual void CpuInput();
    // FUNCTION: 0x67cf50
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154[0x40]; // indexed
    int unk3254[0x40]; // indexed
    int unk3354[0x40]; // indexed
    BYTE unk3454[0x3458 - 0x3454];
};

// Ayu: one of the character classes.
// SIZE: 0x3450
class CAyu : public CPlayer {
public:
    // FUNCTION: 0x6d93f0
    virtual void UpdatePattern();
    // FUNCTION: 0x6e8130
    CAyu(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x6eafa0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x6eafd0
    virtual void ReadCommand();
    // FUNCTION: 0x6ec160
    virtual void CpuInput();
    // FUNCTION: 0x6ef410
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150[0x40]; // indexed
    int unk3250[0x40]; // indexed
    int unk3350[0x40]; // indexed
};

// Akane: one of the character classes.
// SIZE: 0x3450
class CAkane : public CPlayer {
public:
    // FUNCTION: 0x6f2f20
    virtual void UpdatePattern();
    // FUNCTION: 0x7039d0
    CAkane(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x706aa0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x706ad0
    virtual void ReadCommand();
    // FUNCTION: 0x707e50
    virtual void CpuInput();
    // FUNCTION: 0x70bc00
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c[0x40]; // indexed
    int unk324c[0x40]; // indexed
    int unk334c[0x40]; // indexed
    BYTE unk344c[0x3450 - 0x344c];
};

// Akiko: one of the character classes.
// SIZE: 0x3468
class CAkiko : public CPlayer {
public:
    // FUNCTION: 0x712500
    virtual void UpdatePattern();
    // FUNCTION: 0x7219a0
    CAkiko(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x725bd0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x725c00
    virtual void ReadCommand();
    // FUNCTION: 0x726f10
    virtual void CpuInput();
    // FUNCTION: 0x729cc0
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158;
    int unk315c;
    int unk3160;
    int unk3164[0x40]; // indexed
    int unk3264[0x40]; // indexed
    int unk3364[0x40]; // indexed
    BYTE unk3464[0x3468 - 0x3464];
};

// Nanase: one of the character classes.
// SIZE: 0x3470
class CNanase : public CPlayer {
public:
    // FUNCTION: 0x46d970
    virtual void UpdatePattern();
    // FUNCTION: 0x47c130
    void Unk47c130();
    // FUNCTION: 0x48a720
    CNanase(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    void Unk48d940();
    // FUNCTION: 0x48dd00
    virtual void DrawGauge();
    // FUNCTION: 0x48e140
    void Unk48e140(char p1);
    // FUNCTION: 0x48e250
    virtual void Vf8();
    // FUNCTION: 0x48e260
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x48e290
    virtual void ReadCommand();
    // FUNCTION: 0x48f690
    virtual void CpuInput();
    // FUNCTION: 0x492db0
    virtual void UpdateObjects();
    // FUNCTION: 0x497540
    void Unk497540();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c[0x40]; // indexed
    int unk324c[0x40]; // indexed
    int unk334c[0x40]; // indexed
    int unk344c;
    int unk3450;
    int unk3454;
    char unk3458;
    BYTE unk3459[0x345c - 0x3459];
    EffectAnim* unk345c;          // the second animation and pattern tables
    PatternData* unk3460;
    int unk3464;
    int unk3468;
    BYTE unk346c[0x3470 - 0x346c];
};

// Nagamori: one of the character classes.
// SIZE: 0x34b0
class CNagamori : public CPlayer {
public:
    // FUNCTION: 0x49d610
    virtual void UpdatePattern();
    // FUNCTION: 0x4add90
    CNagamori(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x4adfa0
    virtual void Reset();
    // FUNCTION: 0x4ae130
    virtual void StartPattern();
    // FUNCTION: 0x4ae170
    virtual void RemoveObject(short p1);
    // FUNCTION: 0x4ae1d0
    void Unk4ae1d0(short p1, short p2, short p3, short p4);
    // FUNCTION: 0x4ae2c0
    virtual void Move();
    // FUNCTION: 0x4ae2e0
    virtual void StartCommand();
    // FUNCTION: 0x4b12e0
    virtual void DrawGauge();
    // FUNCTION: 0x4b1720
    virtual void Vf8();
    // FUNCTION: 0x4b1750
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x4b1780
    virtual void ReadCommand();
    // FUNCTION: 0x4b2ac0
    virtual void CpuInput();
    // FUNCTION: 0x4b6680
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158;
    int unk315c;
    int unk3160;
    int unk3164;
    int unk3168;
    char unk316c[0x40]; // indexed
    int unk31ac[0x40]; // indexed
    int unk32ac[0x40]; // indexed
    int unk33ac[0x40]; // indexed
    BYTE unk34ac[0x34b0 - 0x34ac];
};

// Kaori: one of the character classes.
// SIZE: 0x3450
class CKaori : public CPlayer {
public:
    // FUNCTION: 0x62a5e0
    virtual void UpdatePattern();
    // FUNCTION: 0x638d90
    CKaori(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x63b630
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x63b660
    virtual void ReadCommand();
    // FUNCTION: 0x63c960
    virtual void CpuInput();
    // FUNCTION: 0x640710
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c[0x40]; // indexed
    int unk324c[0x40]; // indexed
    int unk334c[0x40]; // indexed
    BYTE unk344c[0x3450 - 0x344c];
};

// Kano: one of the character classes.
// SIZE: 0x3478
class CKano : public CPlayer {
public:
    // FUNCTION: 0x6429c0
    virtual void UpdatePattern();
    // FUNCTION: 0x653a20
    CKano(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x657e70
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x657ea0
    virtual void ReadCommand();
    // FUNCTION: 0x659250
    virtual void CpuInput();
    // FUNCTION: 0x65cd30
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158;
    int unk315c;
    int unk3160;
    int unk3164;
    int unk3168;
    int unk316c;
    int unk3170;
    int unk3174[0x40]; // indexed
    int unk3274[0x40]; // indexed
    int unk3374[0x40]; // indexed
    BYTE unk3474[0x3478 - 0x3474];
};

// Ikumi: one of the character classes.
// SIZE: 0x3478
class CIkumi : public CPlayer {
public:
    // FUNCTION: 0x683550
    virtual void UpdatePattern();
    // FUNCTION: 0x694d00
    void Unk694d00();
    // FUNCTION: 0x6a59c0
    CIkumi(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
    // FUNCTION: 0x6a5c50
    virtual void Reset();
    // FUNCTION: 0x6a5dc0
    ~CIkumi();
    // FUNCTION: 0x6a5e70
    virtual void Load();
    // FUNCTION: 0x6a5eb0
    void Unk6a5eb0();
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
    virtual void Vf8();
    // FUNCTION: 0x6ab6a0
    void Unk6ab6a0(char p1);
    // FUNCTION: 0x6ab7b0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x6ab7e0
    virtual void ReadCommand();
    // FUNCTION: 0x6acc10
    virtual void CpuInput();
    // FUNCTION: 0x6b06f0
    virtual void UpdateObjects();
    // FUNCTION: 0x6b7900
    void Unk6b7900();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158;
    int unk315c;
    int unk3160[0x40]; // indexed
    int unk3260[0x40]; // indexed
    int unk3360[0x40]; // indexed
    char unk3460;
    BYTE unk3461[0x3464 - 0x3461];
    EffectAnim* unk3464;          // the second animation and pattern tables
    PatternData* unk3468;
    int unk346c;
    int unk3470;
    BYTE unk3474[0x3478 - 0x3474];
};

// Exnanase: one of the character classes.
// SIZE: 0x3468
class CEXNanase : public CPlayer {
public:
    // FUNCTION: 0x6be9c0
    virtual void UpdatePattern();
    // FUNCTION: 0x6cfbb0
    CEXNanase(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x6d2740
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x6d2770
    virtual void ReadCommand();
    // FUNCTION: 0x6d38e0
    virtual void CpuInput();
    // FUNCTION: 0x6d6e40
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154[0x40]; // indexed
    int unk3254[0x40]; // indexed
    int unk3354[0x40]; // indexed
    int unk3454;
    BYTE unk3458[0x3460 - 0x3458];
    char unk3460;
    BYTE unk3461[0x3468 - 0x3461];
};

// Nayukib: one of the character classes.
// SIZE: 0x3458
class CNayukiB : public CPlayer {
public:
    // FUNCTION: 0x730710
    virtual void UpdatePattern();
    // FUNCTION: 0x73e790
    CNayukiB(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6);
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
    virtual void Vf8();
    // FUNCTION: 0x741bc0
    virtual void SpawnObject(EffectDesc* p1);
    // FUNCTION: 0x741bf0
    virtual void ReadCommand();
    // FUNCTION: 0x742eb0
    virtual void CpuInput();
    // FUNCTION: 0x7472c0
    virtual void UpdateObjects();

    int unk3138;
    int unk313c;
    int unk3140;
    int unk3144;
    int unk3148;
    int unk314c;
    int unk3150;
    int unk3154;
    int unk3158[0x40]; // indexed
    int unk3258[0x40]; // indexed
    int unk3358[0x40]; // indexed
};

#endif
