// An 8-bit image in plain memory behind Direct3D's surface interface, for when the
// card has no 8-bit format or EfzRevival.ini asks for SoftwareRendering. Only locking
// does anything: Flip converts it through the palette like a device surface.
// 0x18 bytes.
#pragma once
#include <windows.h>
#include <d3d9.h>

class SoftwareSurface : public IDirect3DSurface9 {
public:
    SoftwareSurface();
    SoftwareSurface(int width, int height);

    HRESULT __stdcall QueryInterface(REFIID riid, void **object);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall GetDevice(IDirect3DDevice9 **device);
    HRESULT __stdcall SetPrivateData(REFGUID guid, CONST void *data, DWORD size, DWORD flags);
    HRESULT __stdcall GetPrivateData(REFGUID guid, void *data, DWORD *size);
    HRESULT __stdcall FreePrivateData(REFGUID guid);
    DWORD __stdcall SetPriority(DWORD priority);
    DWORD __stdcall GetPriority();
    void __stdcall PreLoad();
    D3DRESOURCETYPE __stdcall GetType();
    HRESULT __stdcall GetContainer(REFIID riid, void **container);
    HRESULT __stdcall GetDesc(D3DSURFACE_DESC *desc);
    HRESULT __stdcall LockRect(D3DLOCKED_RECT *locked, CONST RECT *rect, DWORD flags);
    HRESULT __stdcall UnlockRect();
    HRESULT __stdcall GetDC(HDC *dc);
    HRESULT __stdcall ReleaseDC(HDC dc);

    virtual ~SoftwareSurface();

    int refs;                       // 0x04
    int locks;                      // 0x08
    BYTE *data;                     // 0x0c
    int width;                      // 0x10 also the pitch
    int height;                     // 0x14
};
