// myIDirectDraw (myIDirectDraw.h). Each class of myIDirectDraw.h has its own source
// file, linked in the header's order: the original's .rdata has each object's strings
// followed by its vtable, and its Rich header two objects more than one file gives.
#include "stdafx.h"
#include "myIDirectDraw.h"
#include "EfzRender.h"
#include "Log.h"
#include "SoftwareSurface.h"
#include "Config.h"
#include <DxErr.h>

// GLOBAL: 0x100b6a40
// Surfaces made since the DirectDraw: the first is the primary.
int g_surfaceCount;

// The interface's implicit constructor (see SoftwareSurface.cpp).
// FUNCTION: 0x1001f130 ??0IDirectDraw@@QAE@XZ

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

// FUNCTION: 0x1001f100 ??_GmyIDirectDraw@@UAEPAXI@Z
// FUNCTION: 0x1001f140
myIDirectDraw::~myIDirectDraw()
{
}

// FUNCTION: 0x1001f150
ULONG myIDirectDraw::AddRef()
{
    return 0;
}

// FUNCTION: 0x1001f160
HRESULT myIDirectDraw::QueryInterface(REFIID riid, LPVOID *object)
{
    return DD_OK;
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

