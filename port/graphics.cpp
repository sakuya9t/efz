// CGraphics on SDL3, in place of src/graphics.cpp's DirectDraw.
//
// The screen is what it was: an 8-bit back buffer of 320x240 (640x480 in mode 1, which
// Upscale fills from the top-left quarter) and a 256-colour palette. Flip converts it
// through the palette into a texture that SDL scales to the window. Sprites are 8-bit
// surfaces in the arena. The loaders and the blitters follow src/graphics.cpp step for
// step, the inline-assembly loops included, so the frames are the original's.
#include <SDL3/SDL.h>

#include "efz.h"
#include "platform.h"

struct IDirectDraw : IUnknown {
    ULONG Release()
    {
        delete this;
        return 0;
    }
};

struct IDirectDrawPalette : IUnknown {
    PALETTEENTRY entries[0x100];

    ULONG Release()
    {
        delete this;
        return 0;
    }
    void GetEntries(int start, int count, PALETTEENTRY* out)
    {
        memcpy(out, &entries[start], count * sizeof(PALETTEENTRY));
    }
    void SetEntries(int start, int count, const PALETTEENTRY* in)
    {
        memcpy(&entries[start], in, count * sizeof(PALETTEENTRY));
    }
};

IDirectDrawSurface::IDirectDrawSurface(int w, int h)
{
    width = w;
    height = h;
    pitch = (w + 3) & ~3;
    pixels = new BYTE[pitch * h + 4];
}

IDirectDrawSurface::~IDirectDrawSurface()
{
    delete[] pixels;
}

ULONG IDirectDrawSurface::Release()
{
    delete this;
    return 0;
}

namespace {

SDL_Renderer* g_renderer;
SDL_Texture* g_texture;
uint32_t g_rgb[640 * 480]; // the frame in the texture's format
int g_rgbWidth;
int g_rgbHeight;

// A locked rectangle, as DirectDraw's Lock gives it: the address of its top-left pixel
// and the surface's pitch. Like Lock, it fails for a rectangle outside the surface.
struct Lock {
    BYTE* bits;
    int pitch;
    // Pixel (x, y) of the rectangle is inside the surface's memory: the loops read as
    // far as the original's did, which can pass the rectangle's edge.
    BYTE* base;
    BYTE* end;

    bool Take(IDirectDrawSurface* s, const RECT* r)
    {
        if (!s)
            return false;
        int left = 0, top = 0;
        if (r) {
            if (r->left < 0 || r->top < 0 || r->right > s->width || r->bottom > s->height ||
                r->left >= r->right || r->top >= r->bottom)
                return false;
            left = r->left;
            top = r->top;
        }
        pitch = s->pitch;
        base = s->pixels;
        end = s->pixels + s->pitch * s->height;
        bits = base + top * pitch + left;
        return true;
    }
    bool Inside(const BYTE* p) const { return p >= base && p < end; }
};

void Present(IDirectDrawSurface* back, IDirectDrawPalette* pal)
{
    if (!g_renderer || !back)
        return;
    uint32_t colors[0x100];
    for (int i = 0; i < 0x100; i++) {
        const PALETTEENTRY& e = pal ? pal->entries[i] : PALETTEENTRY();
        colors[i] = 0xff000000u | (e.peRed << 16) | (e.peGreen << 8) | e.peBlue;
    }
    for (int y = 0; y < back->height; y++) {
        const BYTE* row = back->pixels + y * back->pitch;
        uint32_t* out = g_rgb + y * back->width;
        for (int x = 0; x < back->width; x++)
            out[x] = colors[row[x]];
    }
    g_rgbWidth = back->width;
    g_rgbHeight = back->height;
    SDL_UpdateTexture(g_texture, nullptr, g_rgb, back->width * 4);
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);
    SDL_RenderTexture(g_renderer, g_texture, nullptr, nullptr);
    SDL_RenderPresent(g_renderer);
}

// Creates the screen surfaces and the texture for mode 0 (320x240) or 1 (640x480).
bool CreateScreen(CGraphics* g)
{
    int w = g->m_mode * 320 + 320;
    int h = g->m_mode * 240 + 240;
    g->m_primary = new IDirectDrawSurface(w, h);
    g->m_back = new IDirectDrawSurface(w, h);
    if (!g_renderer) {
        g_renderer = SDL_CreateRenderer(efz::Window(), nullptr);
        if (!g_renderer)
            return false;
        SDL_SetRenderVSync(g_renderer, 0);
    }
    if (g_texture)
        SDL_DestroyTexture(g_texture);
    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_XRGB8888,
                                  SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!g_texture)
        return false;
    SDL_SetTextureScaleMode(g_texture, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderLogicalPresentation(g_renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return true;
}

// Copies the sprite rows through `pixel`, as the blitters' loops do: from the last
// pixel of each row to the first, the source mirrored if `flip`.
template <class F>
void Blit8(const Lock& s, const Lock& d, int width, int height, BOOL flip, F pixel)
{
    BYTE* src = s.bits;
    BYTE* dst = d.bits;
    for (int y = 0; y < height; y++) {
        for (int x = width - 1; x >= 0; x--) {
            BYTE* sp = src + (flip ? width - 1 - x : x);
            if (s.Inside(sp) && d.Inside(dst + x))
                pixel(*sp, dst + x);
        }
        src += s.pitch;
        dst += d.pitch;
    }
}

} // namespace

bool efz::SaveFrame(const char* path)
{
    SDL_Surface* s = SDL_CreateSurfaceFrom(g_rgbWidth, g_rgbHeight, SDL_PIXELFORMAT_XRGB8888,
                                           g_rgb, g_rgbWidth * 4);
    if (!s)
        return false;
    bool ok = SDL_SaveBMP(s, path);
    SDL_DestroySurface(s);
    return ok;
}

BOOL CGraphics::Init(HWND hWnd, BYTE mode)
{
    m_mode = mode;
    m_hwnd = hWnd;
    m_dd = new IDirectDraw;
    if (!CreateScreen(this)) {
        MessageBox(0, SDL_GetError(), "ERROR", MB_OK);
        return Close();
    }
    m_ddpal = new IDirectDrawPalette;
    m_ddpal->SetEntries(0, 0x100, m_palette);
    return TRUE;
}

BOOL CGraphics::SetMode8()
{
    ReleaseSurface(&m_back);
    ReleaseSurface(&m_primary);
    if (!CreateScreen(this))
        return Close();
    return TRUE;
}

BOOL CGraphics::SetMode16()
{
    return SetMode8();
}

void CGraphics::Shutdown()
{
    if (m_ddpal) {
        m_ddpal->Release();
        m_ddpal = NULL;
    }
    ReleaseSurface(&m_back);
    ReleaseSurface(&m_primary);
    if (m_dd) {
        m_dd->Release();
        m_dd = NULL;
    }
    if (g_texture)
        SDL_DestroyTexture(g_texture);
    if (g_renderer)
        SDL_DestroyRenderer(g_renderer);
    g_texture = nullptr;
    g_renderer = nullptr;
}

CGraphics::~CGraphics()
{
    Shutdown();
}

void CGraphics::ReleaseSurface(PTR32(IDirectDrawSurface)* surface)
{
    if (*surface) {
        (*surface)->Release();
        *surface = NULL;
    }
}

BOOL CGraphics::Close()
{
    PostMessage(m_hwnd, WM_CLOSE, 0, 0);
    return TRUE;
}

BOOL CGraphics::RestorePrimary()
{
    return TRUE;
}

BOOL CGraphics::RestoreSurface(PTR32(IDirectDrawSurface)*)
{
    return TRUE;
}

RECT CGraphics::LoadBmp(PTR32(IDirectDrawSurface)* surface, const char* name, BYTE base)
{
    DWORD dw;
    HANDLE h = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD fileSize = GetFileSize(h, NULL);
    if (h == INVALID_HANDLE_VALUE) {
        MessageBox(0, "オフスクリーンサーフェイスの生成に失敗", name, MB_OK);
        return MakeRect(0, 0, 0, 0);
    }
    BYTE* data = new BYTE[fileSize];
    ReadFile(h, data, fileSize, &dw, NULL);
    int width = data[0x12] + (data[0x13] << 8);
    width = (4 - width % 4) * (width % 4 > 0) + width;
    int height = data[0x16] + (data[0x17] << 8);
    *surface = new IDirectDrawSurface(width, height);
    int off = data[0xa] + (data[0xb] << 8);
    BYTE* dst = (*surface)->pixels;
    int pitch = (*surface)->pitch;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            dst[(height - 1 - y) * pitch + x] = data[y * width + x + off] + base;
    }
    CloseHandle(h);
    delete[] data;
    return MakeRect(0, 0, width, height);
}

RECT CGraphics::LoadBmpHigh(PTR32(IDirectDrawSurface)* surface, const char* name, BYTE base)
{
    DWORD dw;
    HANDLE h = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD fileSize = GetFileSize(h, NULL);
    if (h == INVALID_HANDLE_VALUE) {
        MessageBox(0, "オフスクリーンサーフェイスの生成に失敗", name, MB_OK);
        return MakeRect(0, 0, 0, 0);
    }
    BYTE* data = new BYTE[fileSize];
    ReadFile(h, data, fileSize, &dw, NULL);
    int width = data[0x12] + (data[0x13] << 8);
    width = (4 - width % 4) * (width % 4 > 0) + width;
    int height = data[0x16] + (data[0x17] << 8);
    *surface = new IDirectDrawSurface(width, height);
    int off = data[0xa] + (data[0xb] << 8);
    BYTE* dst = (*surface)->pixels;
    int pitch = (*surface)->pitch;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            BYTE pix = data[y * width + x + off];
            dst[(height - 1 - y) * pitch + x] = pix >= 0x28 ? pix + 0x87 : pix + base;
        }
    }
    CloseHandle(h);
    delete[] data;
    return MakeRect(0, 0, width, height);
}

// LoadSurface and LoadSurfaceHigh: `high` maps colours 40 and up to 175 and up.
static int LoadDatImage(PTR32(IDirectDrawSurface)* surface, BYTE* data, BYTE rle, BYTE base,
                        bool high)
{
    int offset = 0;
    BYTE run = 0;
    BYTE c = 0;
    int width = data[offset] + (data[offset + 1] << 8);
    int height = data[offset + 2] + (data[offset + 3] << 8);
    offset += 4;
    *surface = new IDirectDrawSurface(width, height);
    BYTE* bits = (*surface)->pixels;
    int pitch = (*surface)->pitch;
    auto map = [&](BYTE pix) -> BYTE { return high && pix >= 0x28 ? pix + 0x87 : pix + base; };
    if (rle == 0) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bits[(height - 1 - y) * pitch + x] = map(data[y * width + x + 4]);
                offset++;
            }
        }
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (run == 0) {
                    if (data[offset] <= rle)
                        c = map(data[offset]);
                    else
                        run = data[offset] - rle - 1;
                    offset++;
                } else {
                    run--;
                }
                bits[y * pitch + x] = c;
            }
        }
    }
    return offset;
}

int CGraphics::LoadSurface(PTR32(IDirectDrawSurface)* surface, BYTE* data, BYTE rle, BYTE base)
{
    return LoadDatImage(surface, data, rle, base, false);
}

int CGraphics::LoadSurfaceHigh(PTR32(IDirectDrawSurface)* surface, BYTE* data, BYTE rle, BYTE base)
{
    return LoadDatImage(surface, data, rle, base, true);
}

// The clipping shared by the blitters (src/graphics.cpp's CLIP).
static bool Clip(RECT& dst, RECT& src, BOOL flip, int minLeft, int screenWidth, int screenHeight)
{
    int r = src.right;
    if (dst.top >= dst.bottom || dst.left >= dst.right)
        return false;
    if (src.top >= src.bottom || src.left >= src.right)
        return false;
    if (dst.top < 0) {
        src.top -= dst.top;
        dst.top = 0;
    }
    if (dst.left < minLeft) {
        src.left -= dst.left;
        dst.left = minLeft;
    }
    if (dst.bottom > screenHeight) {
        src.bottom -= dst.bottom - screenHeight;
        dst.bottom = screenHeight;
    }
    if (dst.right > screenWidth) {
        src.right -= dst.right - screenWidth;
        dst.right = screenWidth;
    }
    if (flip) {
        int save = r - src.left;
        src.left = r - src.right;
        src.right = save;
    }
    if (dst.top >= dst.bottom || dst.left >= dst.right)
        return false;
    if (src.top >= src.bottom || src.left >= src.right)
        return false;
    return true;
}

// Blit and BlitTo: a copy clipped to a screen of the given size.
static BOOL BlitCopy(IDirectDrawSurface* target, RECT dst, IDirectDrawSurface* surface, RECT src,
                     BYTE key, BOOL flip, int screenWidth, int screenHeight)
{
    Lock s, d;
    if (!Clip(dst, src, flip, 0, screenWidth, screenHeight))
        return TRUE;
    if (!s.Take(surface, &src) || !d.Take(target, &dst))
        return TRUE;
    int width = dst.right - dst.left;
    int height = dst.bottom - dst.top;
    if (key > 0)
        Blit8(s, d, width, height, flip, [&](BYTE p, BYTE* o) { if (p != key) *o = p; });
    else
        Blit8(s, d, width, height, FALSE, [&](BYTE p, BYTE* o) { *o = p; });
    return TRUE;
}

BOOL CGraphics::Blit(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip)
{
    return BlitCopy(m_back, dst, surface, src, key, flip, 320, 240);
}

BOOL CGraphics::BlitTo(IDirectDrawSurface* target, RECT dst, IDirectDrawSurface* surface,
                       RECT src, BYTE key, BOOL flip)
{
    return BlitCopy(target, dst, surface, src, key, flip, 640, 480);
}

BOOL CGraphics::BlitEx(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                       char mode)
{
    Lock s, d;
    if (mode != 0 && mode != 1)
        return FALSE;
    if (!Clip(dst, src, flip, 0, 320, 240))
        return TRUE;
    if (!s.Take(surface, &src) || !d.Take(m_back, &dst))
        return TRUE;
    BYTE* table = (BYTE*)m_blend[(int)mode];
    int width = dst.right - dst.left;
    int height = dst.bottom - dst.top;
    if (key > 0)
        Blit8(s, d, width, height, flip,
              [&](BYTE p, BYTE* o) { if (p != key) *o = table[p * 0x100 + *o]; });
    else
        Blit8(s, d, width, height, FALSE, [&](BYTE p, BYTE* o) { *o = table[p * 0x100 + *o]; });
    return TRUE;
}

BOOL CGraphics::BlitTint(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                         BYTE color)
{
    Lock s, d;
    if (!Clip(dst, src, flip, 0, 320, 240))
        return TRUE;
    if (!s.Take(surface, &src) || !d.Take(m_back, &dst))
        return TRUE;
    BYTE* table = (BYTE*)m_blend[1];
    int width = dst.right - dst.left;
    int height = dst.bottom - dst.top;
    if (key > 0)
        Blit8(s, d, width, height, flip,
              [&](BYTE p, BYTE* o) { if (p != key) *o = table[p * 0x100 + color]; });
    else
        Blit8(s, d, width, height, FALSE, [&](BYTE p, BYTE* o) { *o = table[p * 0x100 + color]; });
    return TRUE;
}

BOOL CGraphics::BlitShadow(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                           BYTE shade)
{
    Lock s, d;
    int r = src.right;
    if (dst.top >= dst.bottom || dst.left >= dst.right)
        return TRUE;
    if (src.top >= src.bottom || src.left >= src.right)
        return TRUE;
    if (dst.top < 0)
        dst.top = 0;
    if (dst.left < 0) {
        src.left -= dst.left;
        dst.left = 0;
    }
    if (dst.bottom >= 240)
        dst.bottom = 240;
    if (dst.right >= 320) {
        src.right -= dst.right - 320;
        dst.right = 320;
    }
    if (flip) {
        int save = r - src.left;
        src.left = r - src.right;
        src.right = save;
    }
    if (dst.top > dst.bottom || dst.left > dst.right)
        return TRUE;
    if (src.top > src.bottom || src.left > src.right)
        return TRUE;
    if (!s.Take(surface, &src) || !d.Take(m_back, &dst))
        return TRUE;
    BYTE* table = (BYTE*)m_blend[0];
    int width = dst.right - dst.left;
    int height = dst.bottom - dst.top;
    // Upside down and a third of the height: each row goes three source rows up.
    BYTE* srcRow = s.bits + (src.bottom - src.top - 1) * s.pitch;
    BYTE* dstRow = d.bits;
    for (int y = 0; y < height; y++) {
        for (int x = width - 1; x >= 0; x--) {
            BYTE* sp = srcRow + (flip ? width - 1 - x : x);
            if (s.Inside(sp) && d.Inside(dstRow + x) && *sp != key)
                dstRow[x] = table[dstRow[x] * 0x100 + shade];
        }
        srcRow -= 3 * s.pitch;
        dstRow += d.pitch;
    }
    return TRUE;
}

BOOL CGraphics::BlitSmear(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip)
{
    Lock s, d;
    if (!Clip(dst, src, flip, 3, 320, 240))
        return TRUE;
    if (!s.Take(surface, &src) || !d.Take(m_back, &dst))
        return TRUE;
    int width = dst.right - dst.left;
    int height = dst.bottom - dst.top;
    if (key > 0)
        Blit8(s, d, width, height, flip, [&](BYTE p, BYTE* o) { if (p != key) *o = o[-3]; });
    else
        Blit8(s, d, width, height, FALSE, [&](BYTE, BYTE* o) { *o = o[-3]; });
    return TRUE;
}

BOOL CGraphics::DrawLine(int x1, int y1, int x2, int y2)
{
    RECT r;
    Lock d;
    if (x1 <= x2) {
        r.left = x1;
        r.right = x2;
    } else {
        r.left = x2;
        r.right = x1;
    }
    if (y1 <= y2) {
        r.top = y1;
        r.bottom = y2;
    } else {
        r.top = y2;
        r.bottom = y1;
    }
    int dw = r.right - r.left + 1;
    int hgt = r.bottom - r.top + 1;
    if (!d.Take(m_back, &r))
        return TRUE;
    BYTE* dst = d.bits;
    BYTE* shade = m_blend[1][0xe2];
    double slope = (double)hgt / dw;
    if (hgt < slope)
        slope = hgt;
    for (int i = 0; i < dw; i++) {
        for (double y = i * slope; y <= (i + 1) * slope; y += 1.0) {
            int offset = (y2 - y1) * (x2 - x1) >= 0 ? (int)y * d.pitch + i
                                                     : dw - 1 - i + (int)y * d.pitch;
            if (d.Inside(dst + offset))
                dst[offset] = shade[dst[offset]];
        }
    }
    return TRUE;
}

BOOL CGraphics::DrawFrame(RECT rc, BYTE color)
{
    Lock d;
    if (rc.top < 0)
        rc.top = 0;
    else if (rc.top > 240)
        rc.top = 240;
    if (rc.bottom < 0)
        rc.bottom = 0;
    else if (rc.bottom > 240)
        rc.bottom = 240;
    if (rc.left < 0)
        rc.left = 0;
    else if (rc.left > 320)
        rc.left = 320;
    if (rc.right < 0)
        rc.right = 0;
    else if (rc.right > 320)
        rc.right = 320;
    if (rc.top >= rc.bottom || rc.left >= rc.right)
        return TRUE;
    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;
    if (!d.Take(m_back, &rc))
        return TRUE;
    BYTE* bits = d.bits;
    for (int j = 0; j < width; j++) {
        bits[j] = color;
        bits[(height - 1) * d.pitch + j] = color;
    }
    for (int j = 0; j < height; j++) {
        bits[j * d.pitch] = color;
        bits[j * d.pitch + width - 1] = color;
    }
    return TRUE;
}

BOOL CGraphics::FillRect(RECT rc, BYTE color)
{
    Lock d;
    if (rc.top >= rc.bottom || rc.left >= rc.right)
        return TRUE;
    if (rc.top < 0)
        rc.top = 0;
    if (rc.left < 0)
        rc.left = 0;
    if (rc.bottom > 240)
        rc.bottom = 240;
    if (rc.right > 320)
        rc.right = 320;
    if (rc.top >= rc.bottom || rc.left >= rc.right)
        return TRUE;
    if (!d.Take(m_back, &rc))
        return TRUE;
    for (int y = 0; y < rc.bottom - rc.top; y++)
        memset(d.bits + y * d.pitch, color, rc.right - rc.left);
    return TRUE;
}

BOOL CGraphics::Upscale()
{
    Lock d;
    RECT r = MakeRect(0, 0, 640, 480);
    if (!d.Take(m_back, &r))
        return TRUE;
    // From the bottom-right corner up, so no pixel is read after it is overwritten.
    for (int y = 239; y >= 0; y--) {
        for (int x = 319; x >= 0; x--) {
            BYTE c = d.bits[y * d.pitch + x];
            BYTE* o = d.bits + 2 * y * d.pitch + 2 * x;
            o[0] = o[1] = o[d.pitch] = o[d.pitch + 1] = c;
        }
    }
    return TRUE;
}

BOOL CGraphics::Flip()
{
    if (m_mode)
        Upscale();
    Present(m_back, m_ddpal);
    efz::PumpEvents();
    return TRUE;
}

BOOL CGraphics::LoadPaletteBmp(PALETTEENTRY* palette, const char* name, int from, int to, int count)
{
    DWORD dwRead;
    HANDLE hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return TRUE;
    DWORD size = GetFileSize(hFile, NULL);
    BYTE* data = new BYTE[size];
    ReadFile(hFile, data, size, &dwRead, NULL);
    int offset = 0x36;
    for (int j = 0; j < count; j++) {
        palette[j + to].peBlue = data[(j + from) * 4 + offset];
        palette[j + to].peGreen = data[(j + from) * 4 + 1 + offset];
        palette[j + to].peRed = data[(j + from) * 4 + 2 + offset];
        palette[j + to].peFlags = 0;
    }
    CloseHandle(hFile);
    delete[] data;
    return TRUE;
}

BOOL CGraphics::LoadPaletteDat(PALETTEENTRY* palette, const char* name, int from, int to, int count)
{
    DWORD dwRead;
    HANDLE hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;
    DWORD size = GetFileSize(hFile, NULL);
    BYTE* data = new BYTE[size];
    ReadFile(hFile, data, size, &dwRead, NULL);
    int offset = 1;
    for (int j = 0; j < count; j++) {
        palette[j + to].peBlue = data[(j + from) * 3 + offset];
        palette[j + to].peGreen = data[(j + from) * 3 + 1 + offset];
        palette[j + to].peRed = data[(j + from) * 3 + 2 + offset];
        palette[j + to].peFlags = 0;
    }
    CloseHandle(hFile);
    delete[] data;
    return TRUE;
}

// m_blend[0][a][b]: the palette colour nearest to the average of colours a and b;
// m_blend[1][a][b]: the one nearest to their sum. Distances are squared, through the
// quarter-squares table, and ties keep the lowest colour, as in the original.
void CGraphics::BuildBlendTables(PALETTEENTRY* palette)
{
    const WORD* sq = &m_quarterSquares[0x100];
    for (int a = 0; a < 0x100; a++) {
        int end = a + 1;
        if (end > 0xff)
            end = 0xff;
        for (int b = 0; b < end; b++) {
            const PALETTEENTRY& pa = palette[a];
            const PALETTEENTRY& pb = palette[b];
            WORD sumR = pa.peRed + pb.peRed;
            WORD sumG = pa.peGreen + pb.peGreen;
            WORD sumB = pa.peBlue + pb.peBlue;
            WORD meanR = sumR >> 1, meanG = sumG >> 1, meanB = sumB >> 1;
            WORD best = 40000, bestSum = 40000;
            if (sumR > 0xfe)
                sumR = 0xfe;
            if (sumG > 0xfe)
                sumG = 0xfe;
            if (sumB > 0xfe)
                sumB = 0xfe;
            for (int c = 1; c < 0xff; c++) {
                WORD r = palette[c].peRed, g = palette[c].peGreen, bl = palette[c].peBlue;
                WORD d = (WORD)(*(sq + r - meanR) + *(sq + g - meanG) + *(sq + bl - meanB));
                if (d < best) {
                    best = d;
                    m_blend[0][a][b] = c;
                }
                d = (WORD)(*(sq + r - sumR) + *(sq + g - sumG) + *(sq + bl - sumB));
                if (d < bestSum) {
                    bestSum = d;
                    m_blend[1][a][b] = c;
                }
            }
        }
    }
    for (int m = 0; m < 0xff; m++) {
        for (int a = 0; a < m; a++) {
            m_blend[0][a][m] = m_blend[0][m][a];
            m_blend[1][a][m] = m_blend[1][m][a];
        }
    }
}

BYTE CGraphics::GetColorKey(IDirectDrawSurface* surface)
{
    return surface->pixels[0];
}

BOOL CGraphics::SetPalette(PALETTEENTRY* palette)
{
    m_ddpal->SetEntries(0, 0xff, palette);
    return TRUE;
}

BOOL CGraphics::SetPaletteRange(PALETTEENTRY* palette, BYTE start, BYTE count)
{
    m_ddpal->SetEntries(start, count, &palette[start]);
    return TRUE;
}

BOOL CGraphics::ClearPalette(PALETTEENTRY* palette)
{
    for (int i = 0; i < 0x100; i++) {
        palette[i].peRed = 0;
        palette[i].peGreen = 0;
        palette[i].peBlue = 0;
    }
    return TRUE;
}

void CGraphics::Darken(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent)
{
    PALETTEENTRY entries[0x100];
    m_ddpal->GetEntries(0, 0xff, entries);
    for (int i = from; i < to; i++) {
        entries[i].peRed = palette[i].peRed * percent / 100;
        entries[i].peGreen = palette[i].peGreen * percent / 100;
        entries[i].peBlue = palette[i].peBlue * percent / 100;
    }
    m_ddpal->SetEntries(0, 0xff, entries);
}

void CGraphics::Brighten(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent)
{
    PALETTEENTRY entries[0x100];
    m_ddpal->GetEntries(0, 0xff, entries);
    for (int i = from; i < to; i++) {
        entries[i].peRed = (0xff - palette[i].peRed) * (100 - percent) / 100 + palette[i].peRed;
        entries[i].peGreen = (0xff - palette[i].peGreen) * (100 - percent) / 100 + palette[i].peGreen;
        entries[i].peBlue = (0xff - palette[i].peBlue) * (100 - percent) / 100 + palette[i].peBlue;
    }
    m_ddpal->SetEntries(0, 0xff, entries);
}

void CGraphics::Invert(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent)
{
    PALETTEENTRY entries[0x100];
    m_ddpal->GetEntries(0, 0xff, entries);
    for (int i = from; i < to; i++) {
        entries[i].peRed = (0xff - palette[i].peRed * 2) * percent / 100 + palette[i].peRed;
        entries[i].peGreen = (0xff - palette[i].peGreen * 2) * percent / 100 + palette[i].peGreen;
        entries[i].peBlue = (0xff - palette[i].peBlue * 2) * percent / 100 + palette[i].peBlue;
    }
    m_ddpal->SetEntries(0, 0xff, entries);
}

void CGraphics::Screenshot(int number, PALETTEENTRY* palette)
{
    char num[10];
    char fname[30];
    DWORD dwWrite;

    memset(fname, 0, sizeof(fname));
    strcat(fname, "snap\\sn");
    if (number < 1000)
        strcat(fname, "0");
    if (number < 100)
        strcat(fname, "0");
    if (number < 10)
        strcat(fname, "0");
    _itoa(number, num, 10);
    strcat(fname, num);
    strcat(fname, ".bmp");
    HANDLE hFile = CreateFile(fname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    BYTE* dat = new BYTE[0x13036];
    BYTE* bits = m_back->pixels;
    int width = m_back->pitch;
    for (int j = 0; j < 240; j++) {
        for (int m = 0; m < 320; m++)
            dat[0x12ef6 - j * 320 + m] = bits[j * width + m];
    }
    for (int j = 0; j < 0x100; j++) {
        dat[j * 4 + 0x36] = palette[j].peBlue;
        dat[j * 4 + 0x37] = palette[j].peGreen;
        dat[j * 4 + 0x38] = palette[j].peRed;
        dat[j * 4 + 0x39] = 0;
    }
    // The BITMAPFILEHEADER and BITMAPINFOHEADER of a 320x240 8-bit image.
    for (int j = 0; j < 0x3a; j++)
        dat[j] = 0;
    dat[0] = 'B';
    dat[1] = 'M';
    dat[2] = 0x36;
    dat[3] = 0x30;
    dat[4] = 1;
    dat[10] = 0x36;
    dat[11] = 4;
    dat[14] = 0x28;
    dat[18] = 0x40;
    dat[19] = 1;
    dat[22] = 0xf0;
    dat[26] = 1;
    dat[28] = 8;
    dat[0x2f] = 1;
    WriteFile(hFile, dat, 0x13036, &dwWrite, NULL);
    CloseHandle(hFile);
    delete[] dat;
}

RECT MakeRect(int x, int y, int width, int height)
{
    RECT rc;

    rc.left = x;
    rc.right = x + width;
    rc.top = y;
    rc.bottom = y + height;
    return rc;
}
