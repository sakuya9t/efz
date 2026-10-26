// myIDirectDraw, myIDirectDrawPalette and myIDirectDrawSurface (myIDirectDraw.h).
#include "stdafx.h"
#include "myIDirectDraw.h"
#include "EfzRender.h"
#include "Log.h"
#include "SoftwareSurface.h"
#include "../EfzRevivalLauncher/Config.h"
#include <DxErr.h>

// GLOBAL: 0x100b6a40
// Surfaces made since the DirectDraw: the first is the primary.
int g_surfaceCount;

// The interfaces' implicit constructors (see SoftwareSurface.cpp).
// FUNCTION: 0x1001f130 ??0IDirectDraw@@QAE@XZ
// FUNCTION: 0x1001f720 ??0IDirectDrawPalette@@QAE@XZ
// FUNCTION: 0x1001f8d0 ??0IDirectDrawSurface@@QAE@XZ

// --- myIDirectDraw

// FUNCTION: 0x1001f070
myIDirectDraw::myIDirectDraw()
{
    unknown0c = 0;
    g_surfaceCount = 0;
    device = NULL;
    LOG("Creating ID3D\n");
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d)
        throw "Could not create d3d";
    LOG("Success\n");
    g_render.d3d = d3d;
}

// FUNCTION: 0x1001f160
HRESULT myIDirectDraw::QueryInterface(REFIID riid, LPVOID *object)
{
    return DD_OK;
}

// FUNCTION: 0x1001f150
ULONG myIDirectDraw::AddRef()
{
    return 0;
}

// FUNCTION: 0x1001f170
ULONG myIDirectDraw::Release()
{
    LOG("Release myIDirectDraw\n");
    d3d->Release();
    g_render.device->Release();
    return 0;
}

// FUNCTION: 0x1001f1b0
HRESULT myIDirectDraw::Compact()
{
    return DD_OK;
}

// FUNCTION: 0x1001f1c0
HRESULT myIDirectDraw::CreateClipper(DWORD flags, LPDIRECTDRAWCLIPPER *clipper, IUnknown *outer)
{
    return DD_OK;
}

// FUNCTION: 0x1001f1d0
HRESULT myIDirectDraw::CreatePalette(DWORD flags, LPPALETTEENTRY entries,
    LPDIRECTDRAWPALETTE *palette, IUnknown *outer)
{
    LOG("Create palette\n");
    *palette = new myIDirectDrawPalette(device);
    return DD_OK;
}

// The first surface made is the primary (g_render.primary).
// FUNCTION: 0x1001f230
HRESULT myIDirectDraw::CreateSurface(LPDDSURFACEDESC desc, LPDIRECTDRAWSURFACE *surface,
    IUnknown *outer)
{
    HRESULT result;
    myIDirectDrawSurface *created;
    IDirect3DSurface9 *image;
    if (g_render.software) {
        created = new myIDirectDrawSurface(new SoftwareSurface(desc->dwWidth, desc->dwHeight),
            desc->dwWidth, desc->dwHeight);
        result = DD_OK;
    } else {
        result = device->CreateOffscreenPlainSurface(desc->dwWidth, desc->dwHeight,
            g_render.format, D3DPOOL_SYSTEMMEM, &image, NULL);
        created = new myIDirectDrawSurface(image, desc->dwWidth, desc->dwHeight);
    }
    *surface = created;
    if (created->id == 0)
        g_render.primary = created;
    return result;
}

// FUNCTION: 0x1001f330
HRESULT myIDirectDraw::DuplicateSurface(LPDIRECTDRAWSURFACE surface, LPDIRECTDRAWSURFACE *duplicate)
{
    return DD_OK;
}

// FUNCTION: 0x1001f340
HRESULT myIDirectDraw::EnumDisplayModes(DWORD flags, LPDDSURFACEDESC desc, LPVOID context,
    LPDDENUMMODESCALLBACK callback)
{
    return DD_OK;
}

// FUNCTION: 0x1001f350
HRESULT myIDirectDraw::EnumSurfaces(DWORD flags, LPDDSURFACEDESC desc, LPVOID context,
    LPDDENUMSURFACESCALLBACK callback)
{
    return DD_OK;
}

// FUNCTION: 0x1001f360
HRESULT myIDirectDraw::FlipToGDISurface()
{
    return DD_OK;
}

// FUNCTION: 0x1001f370
HRESULT myIDirectDraw::GetCaps(LPDDCAPS driverCaps, LPDDCAPS helCaps)
{
    return DD_OK;
}

// FUNCTION: 0x1001f380
HRESULT myIDirectDraw::GetDisplayMode(LPDDSURFACEDESC desc)
{
    return DD_OK;
}

// FUNCTION: 0x1001f390
HRESULT myIDirectDraw::GetFourCCCodes(LPDWORD count, LPDWORD codes)
{
    return DD_OK;
}

// FUNCTION: 0x1001f3a0
HRESULT myIDirectDraw::GetGDISurface(LPDIRECTDRAWSURFACE *surface)
{
    return DD_OK;
}

// FUNCTION: 0x1001f3b0
HRESULT myIDirectDraw::GetMonitorFrequency(LPDWORD frequency)
{
    return DD_OK;
}

// FUNCTION: 0x1001f3c0
HRESULT myIDirectDraw::GetScanLine(LPDWORD line)
{
    return DD_OK;
}

// FUNCTION: 0x1001f3d0
HRESULT myIDirectDraw::GetVerticalBlankStatus(LPBOOL blank)
{
    return DD_OK;
}

// FUNCTION: 0x1001f3e0
HRESULT myIDirectDraw::Initialize(GUID *guid)
{
    return DD_OK;
}

// FUNCTION: 0x1001f3f0
HRESULT myIDirectDraw::RestoreDisplayMode()
{
    return DD_OK;
}

// The game calls this once with its window: the device is made here, windowed, with
// the ini's back buffer size (the window's size is separate: EfzFixes.cpp).
// FUNCTION: 0x1001f400
HRESULT myIDirectDraw::SetCooperativeLevel(HWND window, DWORD flags)
{
    Config config(L"./EfzRevival.ini");
    if (!findFormat(config.softwareRendering != 0)) {
        g_render.software = true;
        LOG("Using software mode\n");
    }
    // The defaults are swapped: an ini without a back buffer size gets a portrait one.
    if (config.backBufferWidth <= 0 || config.backBufferHeight <= 0) {
        config.backBufferWidth = 480;
        config.backBufferHeight = 640;
    }
    g_render.params.MultiSampleType = D3DMULTISAMPLE_NONE;
    g_render.params.BackBufferCount = 1;
    g_render.params.BackBufferWidth = config.backBufferWidth;
    g_render.params.BackBufferHeight = config.backBufferHeight;
    g_render.params.BackBufferFormat = D3DFMT_X8R8G8B8;
    g_render.params.Windowed = TRUE;
    g_render.params.SwapEffect = D3DSWAPEFFECT_FLIP;
    g_render.params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    g_render.params.hDeviceWindow = window;
    g_render.params.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, g_render.deviceType, window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE, &g_render.params, &device);
    LOG("CreateDevice: " << DXGetErrorStringA(result) << "\n");
    g_render.device = device;
    g_render.window = window;
    GetWindowRect(window, &g_render.windowRect);
    return result;
}

// FUNCTION: 0x1001f5b0
HRESULT myIDirectDraw::SetDisplayMode(DWORD width, DWORD height, DWORD bpp)
{
    return DD_OK;
}

// FUNCTION: 0x1001f5c0
HRESULT myIDirectDraw::WaitForVerticalBlank(DWORD flags, HANDLE event)
{
    return DD_OK;
}

// FUNCTION: 0x1001f100 ??_GmyIDirectDraw@@UAEPAXI@Z
// FUNCTION: 0x1001f140
myIDirectDraw::~myIDirectDraw()
{
}

// StretchRect filters linearly if the card can; the game's surfaces take the first
// 8-bit format the card has.
// FUNCTION: 0x1001f5d0
bool myIDirectDraw::findFormat(bool software)
{
    g_render.displayFormat = D3DFMT_X8R8G8B8;
    g_render.deviceType = D3DDEVTYPE_HAL;
    g_render.filter = D3DTEXF_NONE;
    D3DCAPS9 caps;
    memset(&caps, 0, sizeof(caps));
    d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
    if ((caps.StretchRectFilterCaps & D3DPTFILTERCAPS_MINFLINEAR)
        && (caps.StretchRectFilterCaps & D3DPTFILTERCAPS_MAGFLINEAR))
        g_render.filter = D3DTEXF_LINEAR;
    D3DFORMAT formats[5] = { D3DFMT_P8, D3DFMT_L8, D3DFMT_A8, D3DFMT_R3G3B2, D3DFMT_A4L4 };
    if (!software) {
        for (int i = 0; i < 5; i++) {
            if (d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, g_render.deviceType,
                    g_render.displayFormat, 0, D3DRTYPE_SURFACE, formats[i]) == D3D_OK) {
                g_render.format = formats[i];
                return true;
            }
        }
    }
    return false;
}

// --- myIDirectDrawPalette

// FUNCTION: 0x1001f6c0
myIDirectDrawPalette::myIDirectDrawPalette(IDirect3DDevice9 *device_)
    : device(device_)
{
    colors = (DWORD *)malloc(256 * sizeof(DWORD));
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

// FUNCTION: 0x1001f6f0 ??_GmyIDirectDrawPalette@@UAEPAXI@Z
// FUNCTION: 0x1001f730
myIDirectDrawPalette::~myIDirectDrawPalette()
{
}

// FUNCTION: 0x1001f840
void myIDirectDrawPalette::getColors(DWORD **colors)
{
    *colors = this->colors;
}

// --- myIDirectDrawSurface

// The 8-bit image through the palette into the 32-bit one.
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

// FUNCTION: 0x1001f850
myIDirectDrawSurface::myIDirectDrawSurface(IDirect3DSurface9 *surface_, int width_, int height_)
    : surface(surface_), width(width_), height(height_)
{
    id = g_surfaceCount++;
    palette = NULL;
    back = NULL;
    refs = 1;
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

// FUNCTION: 0x1001f8a0 ??_GmyIDirectDrawSurface@@UAEPAXI@Z
// FUNCTION: 0x1001f8e0
myIDirectDrawSurface::~myIDirectDrawSurface()
{
    surface->Release();
    width = 0;
    height = 0;
}
