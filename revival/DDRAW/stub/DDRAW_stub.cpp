// TEMPORARY: empty definitions of DDRAW.dll's exports, linked only to produce the
// DDRAW.lib that EfzRevival.dll links against, until DDRAW.dll's own sources exist.
#include "../EfzRender.h"


class __declspec(dllexport) CDDRAW {
public:
    CDDRAW();
};
CDDRAW::CDDRAW() {}

EfzRender::EfzRender() {}
EfzRender::~EfzRender() {}
void EfzRender::renderText() {}
void EfzRender::setRenderText(bool) {}
void EfzRender::addTextRender(std::wstring, int, int, DWORD) {}
void EfzRender::clearTextRender() {}
void EfzRender::initTextRender() {}
void EfzRender::resetDev(_D3DPRESENT_PARAMETERS_ &) {}
void EfzRender::toggleFullScreen() {}
void EfzRender::setFullscreen(bool) {}
bool EfzRender::isFullscreen() { return false; }
bool EfzRender::isActiveWindow() { return false; }
void EfzRender::setBoxRender(bool) {}
void EfzRender::addRectRender(RECT, DWORD, unsigned int) {}
void EfzRender::renderBox() {}
void EfzRender::clearBoxRender() {}

EfzRender *getEfzRender() { return 0; }
extern "C" __declspec(dllexport) void *getEfzInput() { return 0; }
extern "C" __declspec(dllexport) void *getEfzTimer() { return 0; }
extern "C" __declspec(dllexport) HRESULT WINAPI DirectDrawCreate(GUID *, void **, IUnknown *) { return 0; }
