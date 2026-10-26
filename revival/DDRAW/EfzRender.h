// DDRAW.dll's renderer, which EfzRevival.dll drives for its overlay: text lines and
// the hit/hurt/collision boxes. The class is exported unconditionally, so a module
// that includes this header also emits and exports its implicit copy assignment
// (EfzRevival.dll exports ??4EfzRender), and its calls into DDRAW.dll go through the
// import table.
#pragma once
#include <windows.h>
#include <string>

struct _D3DPRESENT_PARAMETERS_;

class __declspec(dllexport) EfzRender {
public:
    EfzRender();
    ~EfzRender();
    void renderText();
    void setRenderText(bool enable);
    void addTextRender(std::wstring text, int x, int y, DWORD color);
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

private:
    // TODO: the members (0xb0 bytes, trivially copyable), from DDRAW.dll
    DWORD members_[0x2c];
};

extern "C" __declspec(dllexport) EfzRender *getEfzRender();
