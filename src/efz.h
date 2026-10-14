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
#include <ddraw.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <string.h>

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
    // FUNCTION: 0x40de40
    void Stop(WORD id);
    // FUNCTION: 0x40de80
    void Play(WORD id, BOOL loop);
    // FUNCTION: 0x40df50
    void Release(WORD id);
    // FUNCTION: 0x40dfb0
    // Loads a .wav file; returns its sound ID, or 0x96 on failure.
    WORD Load(const char* name);
    // FUNCTION: 0x40e2b0
    void Unk40e2b0(const char* name);
    // FUNCTION: 0x40e5d0
    void SetVolume(WORD id, int volume);
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
    BYTE unk18;  // copied to Effect::unk48
    BYTE unk19;
    short unk1a;
    int side;
    BYTE unk20;  // copied to Effect::scale
    BYTE unk21;  // copied to Effect::layer
    short unk22;
    int unk24;   // copied to Effect::screen
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
    BYTE m_pressA[2];
    BYTE m_pressB[2];
    BYTE m_pressC[2];
    BYTE m_pressD[2];
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
    BYTE unkf32;
    BYTE unkf33;
    BYTE m_colorKey;              // the object sprite's transparent colour
    PALETTEENTRY m_palette[0x100];
    char unk1335[0xc];
    char m_extraChars;
    char unk1342[3];
    BYTE unk1345;
    BYTE unk1346;
    BYTE unk1347;
    int unk1348;
    char unk134c;
    char unk134d;
    char unk134e;
    BYTE unk134f;
    BYTE unk1350;
    char unk1351[3];
    int unk1354;
    char unk1358[0x1365 - 0x1358];
    BYTE unk1365;
    char unk1366;
    char unk1367;
    BOOL unk1368;                 // toggled every frame by WinMain
    int unk136c;
    BYTE unk1370;
    char unk1371[3];
    BOOL unk1374;
    int unk1378;
    void* unk137c;
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
    char unk14238[0x14260 - 0x14238];
    double m_fade;                // -100 to 100
    int m_fadeHold;
    char m_fadeDir;               // 1: FlashWhite, -1: FlashBlack, 0: none
    int m_fadeIn;
    int m_fadeOut;
    int unk14278;
    BOOL unk1427c;
    BYTE unk14280;
    CReplayFile m_replay;
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
