// The screen on SDL3: CGraphics's back buffer (graphics.cpp) converted through the
// palette into a texture that SDL scales to the window, with its aspect kept and its
// pixels sharp.
#include <SDL3/SDL.h>

#include "efz.h"
#include "platform.h"
#include "log.h"

namespace {

SDL_Renderer* g_renderer;
SDL_Texture* g_texture;
uint32_t g_rgb[640 * 480]; // the frame in the texture's format
int g_rgbWidth;
int g_rgbHeight;

// "Rev build" in the bottom-left corner, telling this build from the original. It is
// drawn on the window over the frame, not into it: the game's screenshots and --dump
// keep the original's frames.
void DrawWatermark()
{
    const char* text = "Rev build";
    const float x = 4;
    const float y = 480 - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE - 4;
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 160);
    SDL_RenderDebugText(g_renderer, x + 1, y + 1, text);
    SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 192);
    SDL_RenderDebugText(g_renderer, x, y, text);
}

} // namespace

namespace efz {

bool Drawing()
{
    return true;
}

bool OpenScreen(int w, int h)
{
    if (!g_renderer) {
        g_renderer = SDL_CreateRenderer(Window(), nullptr);
        if (!g_renderer) {
            LogError("video", "cannot create a renderer: %s", SDL_GetError());
            return false;
        }
        SDL_SetRenderVSync(g_renderer, 0);
        const char* name = SDL_GetRendererName(g_renderer);
        LogInfo("video", "renderer %s", name ? name : "?");
        SetSessionString("renderer", name ? name : "?");
    }
    if (g_texture)
        SDL_DestroyTexture(g_texture);
    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_XRGB8888,
                                  SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!g_texture) {
        LogError("video", "cannot create the screen's %dx%d texture: %s", w, h,
                 SDL_GetError());
        return false;
    }
    SDL_SetTextureScaleMode(g_texture, SDL_SCALEMODE_NEAREST);
    SDL_SetRenderLogicalPresentation(g_renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    return true;
}

void Present(IDirectDrawSurface* back, const PALETTEENTRY* pal)
{
    if (!g_renderer || !back)
        return;
    uint32_t colors[0x100];
    for (int i = 0; i < 0x100; i++) {
        const PALETTEENTRY& e = pal ? pal[i] : PALETTEENTRY();
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
    DrawWatermark();
    SDL_RenderPresent(g_renderer);
}

void CloseScreen()
{
    if (g_texture)
        SDL_DestroyTexture(g_texture);
    if (g_renderer)
        SDL_DestroyRenderer(g_renderer);
    g_texture = nullptr;
    g_renderer = nullptr;
}

bool SaveFrame(const char* path)
{
    SDL_Surface* s = SDL_CreateSurfaceFrom(g_rgbWidth, g_rgbHeight, SDL_PIXELFORMAT_XRGB8888,
                                           g_rgb, g_rgbWidth * 4);
    if (!s)
        return false;
    bool ok = SDL_SaveBMP(s, path);
    SDL_DestroySurface(s);
    return ok;
}

} // namespace efz
