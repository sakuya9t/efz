// myIDirectDrawPalette (myIDirectDraw.h).
#include "stdafx.h"
#include "myIDirectDraw.h"
#include "Log.h"

// The interface's implicit constructor (see SoftwareSurface.cpp).
// FUNCTION: 0x1001f720 ??0IDirectDrawPalette@@QAE@XZ

// --- myIDirectDrawPalette

// FUNCTION: 0x1001f6c0
myIDirectDrawPalette::myIDirectDrawPalette(IDirect3DDevice9 *device_)
    : device(device_)
{
    colors = (DWORD *)malloc(256 * sizeof(DWORD));
}

// FUNCTION: 0x1001f6f0 ??_GmyIDirectDrawPalette@@UAEPAXI@Z
// FUNCTION: 0x1001f730
myIDirectDrawPalette::~myIDirectDrawPalette()
{
}

// FUNCTION: 0x1001f740
HRESULT myIDirectDrawPalette::QueryInterface(REFIID riid, LPVOID *object)
{
    return DD_OK;
}

// FUNCTION: 0x1001f750
ULONG myIDirectDrawPalette::AddRef()
{
    return 0;
}

// FUNCTION: 0x1001f760
ULONG myIDirectDrawPalette::Release()
{
    LOG("Release Palette\n");
    free(colors);
    return 0;
}

// FUNCTION: 0x1001f7a0
HRESULT myIDirectDrawPalette::GetCaps(LPDWORD caps)
{
    return DD_OK;
}

// FUNCTION: 0x1001f7b0
HRESULT myIDirectDrawPalette::GetEntries(DWORD flags, DWORD base, DWORD count, LPPALETTEENTRY entries)
{
    memcpy(entries, colors, 256 * sizeof(DWORD));
    return DD_OK;
}

// FUNCTION: 0x1001f7d0
HRESULT myIDirectDrawPalette::Initialize(LPDIRECTDRAW ddraw, DWORD flags, LPPALETTEENTRY entries)
{
    return DD_OK;
}

// PALETTEENTRY's red, green, blue to the device's blue, green, red. One entry more than
// asked is copied.
// FUNCTION: 0x1001f7e0
HRESULT myIDirectDrawPalette::SetEntries(DWORD flags, DWORD start, DWORD count, LPPALETTEENTRY entries)
{
    for (DWORD i = start; i <= start + count; i++) {
        PALETTEENTRY entry = *entries++;
        ((BYTE *)colors)[i * 4] = entry.peBlue;
        ((BYTE *)colors)[i * 4 + 1] = entry.peGreen;
        ((BYTE *)colors)[i * 4 + 2] = entry.peRed;
        ((BYTE *)colors)[i * 4 + 3] = entry.peFlags;
    }
    return DD_OK;
}

// FUNCTION: 0x1001f840
void myIDirectDrawPalette::getColors(DWORD **colors)
{
    *colors = this->colors;
}

