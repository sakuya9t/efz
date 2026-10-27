// DDRAW.dll's renderer, which EfzRevival.dll drives for its overlay: text lines and
// the hit/hurt/collision boxes. The class is exported unconditionally, so a module
// that includes this header also emits and exports its implicit copy assignment
// (EfzRevival.dll exports ??4EfzRender), and its calls into DDRAW.dll go through the
// import table.
//
// There is one, g_render (EfzFixes.cpp, 0x100b6bc8), which getEfzRender returns. It also
// holds the Direct3D 9 state the DirectDraw classes share (myIDirectDraw.cpp): the device,
// its present parameters, the surfaces a frame goes through and the window.
//
// A frame (myIDirectDrawSurface::Flip): the game draws into its 8-bit back buffer; Flip
// converts it through the palette into surface (32-bit), stretches that onto
// renderTarget (640x480), draws the text and the boxes over it there, and stretches
// renderTarget onto the device's back buffer (in fullscreen, into a 4:3 rectangle
// of it).
#pragma once
#include <windows.h>
#include <d3d9.h>
#include <list>
#include <memory>
#include <string>
#include <unordered_set>

struct ID3DXFont;
class myIDirectDrawSurface;

// A line of the text overlay (addTextRender). 0x14 bytes. Its implicit copy constructor
// is 0x10016440, its destructor 0x10016470.
struct TextRender {
    // FUNCTION: 0x10015f40 ??0TextRender@@QAE@V?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@HHK@Z
    TextRender(std::wstring text_, int x_, int y_, DWORD format_)
        : text(new std::wstring(text_)), x(x_), y(y_), format(format_)
    {
    }

    std::shared_ptr<std::wstring> text;     // 0x00
    int x;                                  // 0x08
    int y;                                  // 0x0c
    DWORD format;                           // 0x10 DT_ flags; DT_RIGHT: x is the right edge
};

// A box (addRectRender), drawn as a closed line. 0x18 bytes.
struct RectRender {
    // FUNCTION: 0x10015fc0
    RectRender(RECT rect_, DWORD color_, unsigned int flags_)
        : rect(rect_), color(color_), flags(flags_)
    {
    }

    RECT rect;                              // 0x00 in the game's 640x480 coordinates
    DWORD color;                            // 0x10
    unsigned int flags;                     // 0x14 ID3DXLine::SetPattern: the stipple
};

// Boxes are kept once per rectangle: the first one added for a rectangle wins.
bool operator==(const RectRender &a, const RectRender &b);

// Boxes are hashed by their rectangle's left edge. std::hash has nothing for RECT; this
// template stands in for it, so its functions are compiled with the object's templates
// (operator() 0x10016b50, after hash<RectRender>'s 0x10015ff0; hash 0x10016dc0). Being
// static, hash takes its argument in ecx (link-time code generation's own convention),
// where a member would keep it on the stack.
template <class Rect> struct RectHash {
    // FUNCTION: 0x10016b50 ??R?$RectHash@UtagRECT@@@@QBEIABUtagRECT@@@Z
    size_t operator()(const Rect &rect) const
    {
        return hash(rect.left);
    }

    // FUNCTION: 0x10016dc0 ?hash@?$RectHash@UtagRECT@@@@SAIABJ@Z
    static size_t hash(const LONG &value)
    {
        return std::_Hash_seq((const unsigned char *)&value, sizeof(value));
    }
};

namespace std {
template<> struct hash<RectRender> {
    // FUNCTION: 0x10015ff0 ??R?$hash@URectRender@@@std@@QBEIABURectRender@@@Z
    size_t operator()(const RectRender &box) const
    {
        return RectHash<RECT>()(box.rect);
    }
};
}

class __declspec(dllexport) EfzRender {
public:
    EfzRender();
    ~EfzRender();
    void renderText();
    void setRenderText(bool enable);
    void addTextRender(std::wstring text, int x, int y, DWORD format);
    void clearTextRender();
    void initTextRender();
    void resetDev(_D3DPRESENT_PARAMETERS_ &params);
    void toggleFullScreen();
    void setFullscreen(bool fullscreen);
    bool isFullscreen();
    bool isActiveWindow();
    void setBoxRender(bool enable);
    void addRectRender(RECT rect, DWORD color, unsigned int flags);
    void renderBox();
    void clearBoxRender();

    IDirect3DSurface9 *surface;             // 0x00 the frame in 32 bits (displayFormat)
    IDirect3DSurface9 *renderTarget;        // 0x04 640x480: the frame and the overlay
    myIDirectDrawSurface *primary;             // 0x08 the first surface the game creates
    D3DPRESENT_PARAMETERS params;           // 0x0c
    IDirect3DDevice9 *device;               // 0x44
    IDirect3D9 *d3d;                        // 0x48
    HWND window;                            // 0x4c
    D3DFORMAT format;                       // 0x50 the game's 8-bit surfaces (P8, else L8, ...)
    D3DFORMAT displayFormat;                // 0x54 X8R8G8B8
    D3DDEVTYPE deviceType;                  // 0x58 HAL
    RECT windowRect;                        // 0x5c the window when the device was made
    D3DTEXTUREFILTERTYPE filter;            // 0x6c StretchRect's: linear if the card can
    bool software;                          // 0x70 8-bit surfaces in memory (SoftwareSurface)
    bool fullscreen;                        // 0x71 borderless, the monitor's size
    ID3DXFont *font;                        // 0x74
    bool textEnabled;                       // 0x78 setRenderText
    bool boxEnabled;                        // 0x79 setBoxRender
    std::list<TextRender> *texts;           // 0x7c
    std::unordered_set<RectRender> *boxes;  // 0x80
    WINDOWPLACEMENT placement;              // 0x84 the window before going fullscreen
};

// GLOBAL: 0x100b6bc8 (EfzFixes.cpp)
extern EfzRender g_render;

extern "C" __declspec(dllexport) EfzRender *getEfzRender();
