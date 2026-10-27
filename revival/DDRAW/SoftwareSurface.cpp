// SoftwareSurface (SoftwareSurface.h).
#include "stdafx.h"
#include "SoftwareSurface.h"
#include "Log.h"
#include <stdlib.h>
#include <string.h>

// The interfaces' implicit constructors: the constructors' calls to them are dropped
// (they are empty), the functions stay.
// FUNCTION: 0x10019280 ??0IUnknown@@QAE@XZ
// FUNCTION: 0x10019290 ??0IDirect3DResource9@@QAE@XZ
// FUNCTION: 0x100192a0 ??0IDirect3DSurface9@@QAE@XZ

// Unused.
// FUNCTION: 0x10019220 ??0SoftwareSurface@@QAE@XZ
SoftwareSurface::SoftwareSurface()
{
    width = 0;
    height = 0;
    data = NULL;
    locks = 0;
    refs = 1;
}

// FUNCTION: 0x100192b0 ??0SoftwareSurface@@QAE@HH@Z
SoftwareSurface::SoftwareSurface(int width_, int height_)
    : width(width_), height(height_)
{
    data = (BYTE *)malloc(width * height);
    if (!data)
        throw "Couldn't create a sw surface";
    memset(data, 0, width * height);
    locks = 0;
    refs = 1;
}

// FUNCTION: 0x10019250 ??_GSoftwareSurface@@UAEPAXI@Z
// FUNCTION: 0x10019320
SoftwareSurface::~SoftwareSurface()
{
    if (locks != 0 || refs != 0)
        LOG("Error on surface destruction lock " << locks << " refs " << refs << "\n");
    refs = 0;
    locks = 0;
    width = 0;
    height = 0;
    if (data) {
        free(data);
        data = NULL;
    }
}

// FUNCTION: 0x100193c0
HRESULT SoftwareSurface::QueryInterface(REFIID riid, void **object)
{
    return D3D_OK;
}

// FUNCTION: 0x100193d0
HRESULT SoftwareSurface::GetDevice(IDirect3DDevice9 **device)
{
    return D3D_OK;
}

// FUNCTION: 0x100193e0
HRESULT SoftwareSurface::SetPrivateData(REFGUID guid, CONST void *data, DWORD size, DWORD flags)
{
    return D3D_OK;
}

// FUNCTION: 0x100193f0
HRESULT SoftwareSurface::GetPrivateData(REFGUID guid, void *data, DWORD *size)
{
    return D3D_OK;
}

// FUNCTION: 0x10019400
HRESULT SoftwareSurface::FreePrivateData(REFGUID guid)
{
    return D3D_OK;
}

// FUNCTION: 0x10019410
HRESULT SoftwareSurface::GetContainer(REFIID riid, void **container)
{
    return D3D_OK;
}

// FUNCTION: 0x10019420
HRESULT SoftwareSurface::GetDesc(D3DSURFACE_DESC *desc)
{
    return D3D_OK;
}

// FUNCTION: 0x10019430
HRESULT SoftwareSurface::LockRect(D3DLOCKED_RECT *locked, CONST RECT *rect, DWORD flags)
{
    locks++;
    if (!rect) {
        locked->Pitch = width;
        locked->pBits = data;
        return D3D_OK;
    }
    int offset = rect->top * width + rect->left;
    locked->Pitch = width;
    locked->pBits = data + offset;
    return D3D_OK;
}

// FUNCTION: 0x10019480
HRESULT SoftwareSurface::UnlockRect()
{
    if (--locks < 0) {
        LOG("Error on surface unlock " << locks << "\n");
        throw "Too many unlocks";
    }
    return D3D_OK;
}

// FUNCTION: 0x100194f0
HRESULT SoftwareSurface::GetDC(HDC *dc)
{
    return D3D_OK;
}

// FUNCTION: 0x10019500
HRESULT SoftwareSurface::ReleaseDC(HDC dc)
{
    return D3D_OK;
}

// FUNCTION: 0x10019510
D3DRESOURCETYPE SoftwareSurface::GetType()
{
    return D3DRTYPE_SURFACE;
}

// FUNCTION: 0x10019520
void SoftwareSurface::PreLoad()
{
}

// FUNCTION: 0x10019530
DWORD SoftwareSurface::GetPriority()
{
    return 0;
}

// FUNCTION: 0x10019540
DWORD SoftwareSurface::SetPriority(DWORD priority)
{
    return 0;
}

// FUNCTION: 0x10019550
ULONG SoftwareSurface::Release()
{
    if (--refs == 0) {
        delete this;
        return 0;
    }
    return refs;
}

// FUNCTION: 0x10019570
ULONG SoftwareSurface::AddRef()
{
    return ++refs;
}
