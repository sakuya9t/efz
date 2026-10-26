// The DirectDraw the game sees (DirectDrawCreate), on top of Direct3D 9. EFZ uses a
// small part of it: one primary surface with an attached back buffer, plain 8-bit
// surfaces it locks and writes itself, a palette, and Flip. Every surface is an 8-bit
// Direct3D surface in system memory (or a SoftwareSurface); the methods the game
// doesn't use succeed doing nothing, and nothing is reference counted but surfaces.
//
// The Direct3D state lives in g_render (EfzRender.h): SetCooperativeLevel makes the
// device, GetAttachedSurface the frame's surfaces, Flip draws (myIDirectDrawSurface::Flip).
#pragma once
#include <windows.h>
#include <ddraw.h>
#include <d3d9.h>

// The IDirectDraw. 0x10 bytes. The methods are declared without STDMETHOD's nothrow:
// CreateSurface and GetAttachedSurface clean up after a throwing constructor.
class myIDirectDraw : public IDirectDraw {
public:
    myIDirectDraw();

    HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *object);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall Compact();
    HRESULT __stdcall CreateClipper(DWORD flags, LPDIRECTDRAWCLIPPER *clipper, IUnknown *outer);
    HRESULT __stdcall CreatePalette(DWORD flags, LPPALETTEENTRY entries, LPDIRECTDRAWPALETTE *palette,
        IUnknown *outer);
    HRESULT __stdcall CreateSurface(LPDDSURFACEDESC desc, LPDIRECTDRAWSURFACE *surface, IUnknown *outer);
    HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE surface, LPDIRECTDRAWSURFACE *duplicate);
    HRESULT __stdcall EnumDisplayModes(DWORD flags, LPDDSURFACEDESC desc, LPVOID context,
        LPDDENUMMODESCALLBACK callback);
    HRESULT __stdcall EnumSurfaces(DWORD flags, LPDDSURFACEDESC desc, LPVOID context,
        LPDDENUMSURFACESCALLBACK callback);
    HRESULT __stdcall FlipToGDISurface();
    HRESULT __stdcall GetCaps(LPDDCAPS driverCaps, LPDDCAPS helCaps);
    HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC desc);
    HRESULT __stdcall GetFourCCCodes(LPDWORD count, LPDWORD codes);
    HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE *surface);
    HRESULT __stdcall GetMonitorFrequency(LPDWORD frequency);
    HRESULT __stdcall GetScanLine(LPDWORD line);
    HRESULT __stdcall GetVerticalBlankStatus(LPBOOL blank);
    HRESULT __stdcall Initialize(GUID *guid);
    HRESULT __stdcall RestoreDisplayMode();
    HRESULT __stdcall SetCooperativeLevel(HWND window, DWORD flags);
    HRESULT __stdcall SetDisplayMode(DWORD width, DWORD height, DWORD bpp);
    HRESULT __stdcall WaitForVerticalBlank(DWORD flags, HANDLE event);

    virtual ~myIDirectDraw();

    // The 8-bit format the device can make surfaces of (EfzRender::format); false when
    // there is none, or software is set: the surfaces are SoftwareSurfaces then.
    bool findFormat(bool software);

    IDirect3D9 *d3d;                // 0x04
    IDirect3DDevice9 *device;       // 0x08
    int unknown0c;                  // 0x0c
};

// A palette: 256 colours as the device's X8R8G8B8. 0xc bytes.
class myIDirectDrawPalette : public IDirectDrawPalette {
public:
    myIDirectDrawPalette(IDirect3DDevice9 *device);

    HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *object);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall GetCaps(LPDWORD caps);
    HRESULT __stdcall GetEntries(DWORD flags, DWORD base, DWORD count, LPPALETTEENTRY entries);
    HRESULT __stdcall Initialize(LPDIRECTDRAW ddraw, DWORD flags, LPPALETTEENTRY entries);
    HRESULT __stdcall SetEntries(DWORD flags, DWORD start, DWORD count, LPPALETTEENTRY entries);

    virtual ~myIDirectDrawPalette();
    virtual void getColors(DWORD **colors);

    DWORD *colors;                  // 0x04
    IDirect3DDevice9 *device;       // 0x08
};

// A surface: one of the game's 8-bit images, in an IDirect3DSurface9. 0x20 bytes.
class myIDirectDrawSurface : public IDirectDrawSurface {
public:
    myIDirectDrawSurface(IDirect3DSurface9 *surface, int width, int height);

    HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *object);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE surface);
    HRESULT __stdcall AddOverlayDirtyRect(LPRECT rect);
    HRESULT __stdcall Blt(LPRECT destRect, LPDIRECTDRAWSURFACE source, LPRECT sourceRect, DWORD flags,
        LPDDBLTFX fx);
    HRESULT __stdcall BltBatch(LPDDBLTBATCH batch, DWORD count, DWORD flags);
    HRESULT __stdcall BltFast(DWORD x, DWORD y, LPDIRECTDRAWSURFACE source, LPRECT sourceRect,
        DWORD flags);
    HRESULT __stdcall DeleteAttachedSurface(DWORD flags, LPDIRECTDRAWSURFACE surface);
    HRESULT __stdcall EnumAttachedSurfaces(LPVOID context, LPDDENUMSURFACESCALLBACK callback);
    HRESULT __stdcall EnumOverlayZOrders(DWORD flags, LPVOID context, LPDDENUMSURFACESCALLBACK callback);
    HRESULT __stdcall Flip(LPDIRECTDRAWSURFACE target, DWORD flags);
    HRESULT __stdcall GetAttachedSurface(LPDDSCAPS caps, LPDIRECTDRAWSURFACE *surface);
    HRESULT __stdcall GetBltStatus(DWORD flags);
    HRESULT __stdcall GetCaps(LPDDSCAPS caps);
    HRESULT __stdcall GetClipper(LPDIRECTDRAWCLIPPER *clipper);
    HRESULT __stdcall GetColorKey(DWORD flags, LPDDCOLORKEY key);
    HRESULT __stdcall GetDC(HDC *dc);
    HRESULT __stdcall GetFlipStatus(DWORD flags);
    HRESULT __stdcall GetOverlayPosition(LPLONG x, LPLONG y);
    HRESULT __stdcall GetPalette(LPDIRECTDRAWPALETTE *palette);
    HRESULT __stdcall GetPixelFormat(LPDDPIXELFORMAT format);
    HRESULT __stdcall GetSurfaceDesc(LPDDSURFACEDESC desc);
    HRESULT __stdcall Initialize(LPDIRECTDRAW ddraw, LPDDSURFACEDESC desc);
    HRESULT __stdcall IsLost();
    HRESULT __stdcall Lock(LPRECT rect, LPDDSURFACEDESC desc, DWORD flags, HANDLE event);
    HRESULT __stdcall ReleaseDC(HDC dc);
    HRESULT __stdcall Restore();
    HRESULT __stdcall SetClipper(LPDIRECTDRAWCLIPPER clipper);
    HRESULT __stdcall SetColorKey(DWORD flags, LPDDCOLORKEY key);
    HRESULT __stdcall SetOverlayPosition(LONG x, LONG y);
    HRESULT __stdcall SetPalette(LPDIRECTDRAWPALETTE palette);
    HRESULT __stdcall Unlock(LPVOID data);
    HRESULT __stdcall UpdateOverlay(LPRECT sourceRect, LPDIRECTDRAWSURFACE dest, LPRECT destRect,
        DWORD flags, LPDDOVERLAYFX fx);
    HRESULT __stdcall UpdateOverlayDisplay(DWORD flags);
    HRESULT __stdcall UpdateOverlayZOrder(DWORD flags, LPDIRECTDRAWSURFACE reference);

    virtual ~myIDirectDrawSurface();

    int id;                         // 0x04 in creation order: 0 is the primary
    int refs;                       // 0x08
    IDirect3DSurface9 *surface;     // 0x0c
    myIDirectDrawSurface *back;        // 0x10 GetAttachedSurface's: what Flip shows
    myIDirectDrawPalette *palette;     // 0x14
    int width;                      // 0x18
    int height;                     // 0x1c
};

// The game's DirectDraw object (DDRAW.cpp)
extern myIDirectDraw *g_ddraw;
