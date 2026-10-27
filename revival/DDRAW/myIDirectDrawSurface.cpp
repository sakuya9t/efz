// myIDirectDrawSurface (myIDirectDraw.h).
#include "stdafx.h"
#include "myIDirectDraw.h"
#include "EfzRender.h"
#include "Log.h"
#include "SoftwareSurface.h"
#include <DxErr.h>

// myIDirectDraw.cpp
extern int g_surfaceCount;

// The interface's implicit constructor (see SoftwareSurface.cpp).
// FUNCTION: 0x1001f8d0 ??0IDirectDrawSurface@@QAE@XZ

// --- myIDirectDrawSurface

// The 8-bit image through the palette into the 32-bit one (at the end).
static void convert(IDirect3DSurface9 *source, myIDirectDrawPalette *palette,
    IDirect3DSurface9 *target, int width, int height);

// FUNCTION: 0x1001f850
myIDirectDrawSurface::myIDirectDrawSurface(IDirect3DSurface9 *surface_, int width_, int height_)
    : surface(surface_), width(width_), height(height_)
{
    id = g_surfaceCount++;
    palette = NULL;
    back = NULL;
    refs = 1;
}

// FUNCTION: 0x1001f8a0 ??_GmyIDirectDrawSurface@@UAEPAXI@Z
// FUNCTION: 0x1001f8e0
myIDirectDrawSurface::~myIDirectDrawSurface()
{
    surface->Release();
    width = 0;
    height = 0;
}

// FUNCTION: 0x1001f910
HRESULT myIDirectDrawSurface::QueryInterface(REFIID riid, LPVOID *object)
{
    return DD_OK;
}

// FUNCTION: 0x1001f920
ULONG myIDirectDrawSurface::AddRef()
{
    return ++refs;
}

// FUNCTION: 0x1001f940
ULONG myIDirectDrawSurface::Release()
{
    if (--refs == 0)
        delete this;
    return 0;
}

// FUNCTION: 0x1001f960
HRESULT myIDirectDrawSurface::AddAttachedSurface(LPDIRECTDRAWSURFACE surface)
{
    return DD_OK;
}

// FUNCTION: 0x1001f970
HRESULT myIDirectDrawSurface::AddOverlayDirtyRect(LPRECT rect)
{
    return DD_OK;
}

// FUNCTION: 0x1001f980
HRESULT myIDirectDrawSurface::Blt(LPRECT destRect, LPDIRECTDRAWSURFACE source, LPRECT sourceRect,
    DWORD flags, LPDDBLTFX fx)
{
    return DD_OK;
}

// FUNCTION: 0x1001f990
HRESULT myIDirectDrawSurface::BltBatch(LPDDBLTBATCH batch, DWORD count, DWORD flags)
{
    return DD_OK;
}

// FUNCTION: 0x1001f9a0
HRESULT myIDirectDrawSurface::BltFast(DWORD x, DWORD y, LPDIRECTDRAWSURFACE source, LPRECT sourceRect,
    DWORD flags)
{
    return DD_OK;
}

// FUNCTION: 0x1001f9b0
HRESULT myIDirectDrawSurface::DeleteAttachedSurface(DWORD flags, LPDIRECTDRAWSURFACE surface)
{
    return DD_OK;
}

// FUNCTION: 0x1001f9c0
HRESULT myIDirectDrawSurface::EnumAttachedSurfaces(LPVOID context, LPDDENUMSURFACESCALLBACK callback)
{
    return DD_OK;
}

// FUNCTION: 0x1001f9d0
HRESULT myIDirectDrawSurface::EnumOverlayZOrders(DWORD flags, LPVOID context,
    LPDDENUMSURFACESCALLBACK callback)
{
    return DD_OK;
}

// A frame, on the primary: its back buffer through its palette into g_render.surface,
// that onto renderTarget, the overlay, then renderTarget onto the device's back buffer.
// In fullscreen the picture keeps 4:3 (640x480) within the back buffer, as it would on
// the monitor: pillarboxed on a wider one, letterboxed on a narrower one.
// FUNCTION: 0x1001f9e0
HRESULT myIDirectDrawSurface::Flip(LPDIRECTDRAWSURFACE target, DWORD flags)
{
    IDirect3DDevice9 *device = g_render.device;
    device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    IDirect3DSurface9 *frame = g_render.surface;
    IDirect3DSurface9 *overlay = g_render.renderTarget;
    device->BeginScene();
    convert(back->surface, palette, frame, width, height);
    device->StretchRect(frame, NULL, overlay, NULL, g_render.filter);
    device->EndScene();
    g_render.renderText();
    g_render.renderBox();
    IDirect3DSurface9 *backBuffer = NULL;
    device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
    if (g_render.isFullscreen()) {
        MONITORINFO monitor = { sizeof(monitor) };
        GetMonitorInfoW(MonitorFromWindow(g_render.window, MONITOR_DEFAULTTONEAREST), &monitor);
        D3DDISPLAYMODE mode;
        device->GetDisplayMode(0, &mode);
        float gameAspect = 640.0 / 480.0;
        float monitorAspect = (float)(monitor.rcMonitor.right - monitor.rcMonitor.left)
            / (float)(monitor.rcMonitor.bottom - monitor.rcMonitor.top);
        float bufferWidth = (float)g_render.params.BackBufferWidth;
        float bufferHeight = (float)g_render.params.BackBufferHeight;
        float bufferAspect = bufferWidth / bufferHeight;
        RECT rect;
        if (monitorAspect > gameAspect) {
            float width = bufferHeight * gameAspect * bufferAspect / monitorAspect;
            rect.left = (int)((bufferWidth - width) / 2.0f);
            rect.top = 0;
            rect.right = (int)(rect.left + width);
            rect.bottom = (int)bufferHeight;
        } else {
            float height = bufferWidth * monitorAspect / (bufferAspect * gameAspect);
            rect.left = 0;
            rect.top = (int)((bufferHeight - height) / 2.0f);
            rect.right = g_render.params.BackBufferWidth;
            rect.bottom = (int)(rect.top + height);
        }
        device->StretchRect(overlay, NULL, backBuffer, &rect, g_render.filter);
    } else {
        device->StretchRect(overlay, NULL, backBuffer, NULL, g_render.filter);
    }
    backBuffer->Release();
    if (device->Present(NULL, NULL, NULL, NULL) != D3D_OK)
        g_render.resetDev(g_render.params);
    return DD_OK;
}

// The back buffer, and with it the frame's 32-bit surfaces (g_render.surface and
// renderTarget).
// FUNCTION: 0x1001fc60
HRESULT myIDirectDrawSurface::GetAttachedSurface(LPDDSCAPS caps, LPDIRECTDRAWSURFACE *surface)
{
    IDirect3DDevice9 *device = g_render.device;
    device->CreateOffscreenPlainSurface(width, height, g_render.displayFormat, D3DPOOL_DEFAULT,
        &g_render.surface, NULL);
    device->CreateRenderTarget(640, 480, g_render.displayFormat, D3DMULTISAMPLE_NONE, 0, TRUE,
        &g_render.renderTarget, NULL);
    myIDirectDrawSurface *attached;
    if (g_render.software) {
        attached = new myIDirectDrawSurface(new SoftwareSurface(width, height), width, height);
    } else {
        IDirect3DSurface9 *image = NULL;
        device->CreateOffscreenPlainSurface(width, height, g_render.format, D3DPOOL_SYSTEMMEM,
            &image, NULL);
        attached = new myIDirectDrawSurface(image, width, height);
    }
    back = attached;
    *surface = attached;
    LOG("GetAttachedSurface: " << attached << "\n");
    return DD_OK;
}

// FUNCTION: 0x1001fde0
HRESULT myIDirectDrawSurface::GetBltStatus(DWORD flags)
{
    return DD_OK;
}

// FUNCTION: 0x1001fdf0
HRESULT myIDirectDrawSurface::GetCaps(LPDDSCAPS caps)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe00
HRESULT myIDirectDrawSurface::GetClipper(LPDIRECTDRAWCLIPPER *clipper)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe10
HRESULT myIDirectDrawSurface::GetColorKey(DWORD flags, LPDDCOLORKEY key)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe20
HRESULT myIDirectDrawSurface::GetDC(HDC *dc)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe30
HRESULT myIDirectDrawSurface::GetFlipStatus(DWORD flags)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe40
HRESULT myIDirectDrawSurface::GetOverlayPosition(LPLONG x, LPLONG y)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe50
HRESULT myIDirectDrawSurface::GetPalette(LPDIRECTDRAWPALETTE *palette)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe60
HRESULT myIDirectDrawSurface::GetPixelFormat(LPDDPIXELFORMAT format)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe70
HRESULT myIDirectDrawSurface::GetSurfaceDesc(LPDDSURFACEDESC desc)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe80
HRESULT myIDirectDrawSurface::Initialize(LPDIRECTDRAW ddraw, LPDDSURFACEDESC desc)
{
    return DD_OK;
}

// FUNCTION: 0x1001fe90
HRESULT myIDirectDrawSurface::IsLost()
{
    return DD_OK;
}

// FUNCTION: 0x1001fea0
HRESULT myIDirectDrawSurface::Lock(LPRECT rect, LPDDSURFACEDESC desc, DWORD flags, HANDLE event)
{
    D3DLOCKED_RECT locked = {};
    HRESULT result = surface->LockRect(&locked, rect, flags & ~DDLOCK_WAIT);
    desc->lpSurface = locked.pBits;
    desc->dwHeight = height;
    desc->lPitch = locked.Pitch;
    if (result != D3D_OK)
        LOG("Lock error " << DXGetErrorStringA(result) << "\n");
    return result;
}

// FUNCTION: 0x1001ff30
HRESULT myIDirectDrawSurface::ReleaseDC(HDC dc)
{
    return DD_OK;
}

// FUNCTION: 0x1001ff40
HRESULT myIDirectDrawSurface::Restore()
{
    return DD_OK;
}

// FUNCTION: 0x1001ff50
HRESULT myIDirectDrawSurface::SetClipper(LPDIRECTDRAWCLIPPER clipper)
{
    return DD_OK;
}

// FUNCTION: 0x1001ff60
HRESULT myIDirectDrawSurface::SetColorKey(DWORD flags, LPDDCOLORKEY key)
{
    return DD_OK;
}

// FUNCTION: 0x1001ff70
HRESULT myIDirectDrawSurface::SetOverlayPosition(LONG x, LONG y)
{
    return DD_OK;
}

// FUNCTION: 0x1001ff80
HRESULT myIDirectDrawSurface::SetPalette(LPDIRECTDRAWPALETTE palette)
{
    this->palette = (myIDirectDrawPalette *)palette;
    return DD_OK;
}

// FUNCTION: 0x1001ffa0
HRESULT myIDirectDrawSurface::Unlock(LPVOID data)
{
    return surface->UnlockRect();
}

// FUNCTION: 0x1001ffc0
HRESULT myIDirectDrawSurface::UpdateOverlay(LPRECT sourceRect, LPDIRECTDRAWSURFACE dest,
    LPRECT destRect, DWORD flags, LPDDOVERLAYFX fx)
{
    return DD_OK;
}

// FUNCTION: 0x1001ffd0
HRESULT myIDirectDrawSurface::UpdateOverlayDisplay(DWORD flags)
{
    return DD_OK;
}

// FUNCTION: 0x1001ffe0
HRESULT myIDirectDrawSurface::UpdateOverlayZOrder(DWORD flags, LPDIRECTDRAWSURFACE reference)
{
    return DD_OK;
}

// Flip's conversion, defined last.
// FUNCTION: 0x1001fff0
static void convert(IDirect3DSurface9 *source, myIDirectDrawPalette *palette,
    IDirect3DSurface9 *target, int width, int height)
{
    D3DLOCKED_RECT from;
    source->LockRect(&from, NULL, 0);
    D3DLOCKED_RECT to;
    target->LockRect(&to, NULL, 0);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            ((DWORD *)((BYTE *)to.pBits + to.Pitch * y))[x] =
                palette->colors[((BYTE *)from.pBits)[from.Pitch * y + x]];
    }
    target->UnlockRect();
    source->UnlockRect();
}
