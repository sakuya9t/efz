// DDRAW.dll's exports (DDRAW.def): DirectDrawCreate, which efz.exe calls in place of
// the system's, and the accessors EfzRevival.dll uses (EfzRender.h, EfzTimer.h,
// EfzFixes.h); and the template's sample class.
#include "stdafx.h"
#include "DDRAW.h"
#include "EfzFixes.h"
#include "EfzRender.h"
#include "EfzTimer.h"
// ddraw.h declares the system's DirectDrawCreate, which this one replaces.
#define DirectDrawCreate DirectDrawCreateSystem
#include "myIDirectDraw.h"
#undef DirectDrawCreate

// GLOBAL: 0x100b6a38
myIDirectDraw *g_ddraw;

// Unreferenced (see Process.cpp's): after SoftwareSurface's vtable.
// GLOBAL: 0x100a8e70 ?value@?$UnusedFour@$03@@2HB
template <int N> struct UnusedFour { static const int value; };
template <int N> const int UnusedFour<N>::value = N;
template struct UnusedFour<4>;

// FUNCTION: 0x1001b9b0
extern "C" __declspec(dllexport) HRESULT WINAPI DirectDrawCreate(GUID *guid,
    LPDIRECTDRAW *ddraw, IUnknown *outer)
{
    g_ddraw = new myIDirectDraw();
    *ddraw = g_ddraw;
    return DD_OK;
}

// FUNCTION: 0x1001b9f0
extern "C" __declspec(dllexport) EfzRender *getEfzRender()
{
    return &g_render;
}

// FUNCTION: 0x1001ba00
extern "C" __declspec(dllexport) BYTE getEfzInput(bool player2)
{
    return efzInput(player2);
}

// FUNCTION: 0x1001ba10
extern "C" __declspec(dllexport) EfzTimer *getEfzTimer()
{
    return &g_timer;
}

// FUNCTION: 0x1001b9a0 ??4CDDRAW@@QAEAAV0@ABV0@@Z
// FUNCTION: 0x1001ba20
CDDRAW::CDDRAW()
{
    return;
}
