// What src/efz.h includes in the native build in place of <windows.h> and DirectX: the
// Win32 types the game uses, at their Win32 sizes, the few Win32 functions the game
// code calls (port/win32.cpp), the DirectX interfaces it touches, the 32-bit pointer
// handles (port/guest.h) and the original's floating point and rand (port/x87.h).
#ifndef EFZ_NATIVE_H
#define EFZ_NATIVE_H

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// --- Win32 types. Handles are 32-bit numbers, so that structures holding them keep
// the original's layout.
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;
typedef uint32_t ULONG;
typedef int BOOL;
typedef unsigned int UINT;
typedef int32_t HRESULT;
typedef char CHAR;
typedef char* LPSTR;
typedef const char* LPCSTR;
typedef void* LPVOID;
typedef DWORD* LPDWORD;
typedef uint32_t HANDLE;
typedef uint32_t HWND;
typedef uint32_t HINSTANCE;
typedef uint32_t WPARAM;
typedef int32_t LPARAM;
typedef int32_t LRESULT;

#define TRUE 1
#define FALSE 0
// Calling conventions, which x64 doesn't have (MinGW's headers define them too).
#ifndef WINAPI
#define WINAPI
#endif
#ifndef CALLBACK
#define CALLBACK
#endif

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

typedef struct tagPALETTEENTRY {
    BYTE peRed;
    BYTE peGreen;
    BYTE peBlue;
    BYTE peFlags;
} PALETTEENTRY;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES;

#pragma pack(push, 1)
typedef struct tWAVEFORMATEX {
    WORD wFormatTag;
    WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD nBlockAlign;
    WORD wBitsPerSample;
    WORD cbSize;
} WAVEFORMATEX;
#pragma pack(pop)

typedef struct DIJOYSTATE {
    LONG lX, lY, lZ;
    LONG lRx, lRy, lRz;
    LONG rglSlider[2];
    DWORD rgdwPOV[4];
    BYTE rgbButtons[32];
} DIJOYSTATE;

// --- The Win32 functions the game code calls (port/win32.cpp).
#define GENERIC_READ 0x80000000u
#define GENERIC_WRITE 0x40000000u
#define FILE_SHARE_READ 1
#define FILE_SHARE_WRITE 2
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define TRUNCATE_EXISTING 5
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#define INVALID_HANDLE_VALUE ((HANDLE)0xffffffffu)
#define INVALID_FILE_SIZE 0xffffffffu
#define MB_OK 0
#define WM_CLOSE 0x10

HANDLE CreateFileA(LPCSTR name, DWORD access, DWORD share, SECURITY_ATTRIBUTES* sa,
                   DWORD disposition, DWORD flags, HANDLE templ);
BOOL ReadFile(HANDLE h, LPVOID buffer, DWORD size, LPDWORD read, void* overlapped);
BOOL WriteFile(HANDLE h, const void* buffer, DWORD size, LPDWORD written, void* overlapped);
DWORD SetFilePointer(HANDLE h, LONG offset, LONG* high, DWORD method);
DWORD GetFileSize(HANDLE h, LPDWORD high);
BOOL CloseHandle(HANDLE h);
int MessageBoxA(HWND hwnd, LPCSTR text, LPCSTR caption, UINT type);
BOOL PostMessageA(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD timeGetTime();
#ifndef _WIN32
char* _itoa(int value, char* buffer, int radix);
char* _strnset(char* str, int c, size_t count);
#endif
#define CreateFile CreateFileA
#define MessageBox MessageBoxA
#define PostMessage PostMessageA

// --- DirectX: the game code only releases surfaces and reads the keyboard; the rest
// belongs to the platform classes (port/graphics.cpp, input.cpp, sound.cpp).
#define DD_OK 0
#define DI_OK 0
#define DS_OK 0

struct IUnknown {
    virtual ULONG Release() = 0;

protected:
    virtual ~IUnknown() {}
};
struct IDirectDraw;
struct IDirectDrawPalette;
// An 8-bit image in memory: the sprites, and the screen's back buffer.
struct IDirectDrawSurface : IUnknown {
    IDirectDrawSurface(int width, int height);
    ULONG Release();

    int width;
    int height;
    int pitch;
    BYTE* pixels;

protected:
    ~IDirectDrawSurface();
};
struct IDirectInput7;
struct IDirectSound;
struct IDirectSoundBuffer;
struct IDirectInputDevice7 : IUnknown {
    virtual HRESULT GetDeviceState(DWORD size, LPVOID data) = 0;
    virtual HRESULT Acquire() = 0;
};

#include "guest.h"
#include "x87.h"

#endif
