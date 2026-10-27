// EfzRender: the overlay EfzRevival.dll draws over the game (text and boxes), and the
// fullscreen switch. Both kinds of overlay are drawn into renderTarget between the
// frame and its presentation (myIDirectDrawSurface::Flip).
#include "stdafx.h"
// d3dx9.h before EfzRender.h (but after <memory>): D3DXVECTOR2's constructor comes
// between std::shared_ptr's and TextRender's (0x10015f30).
#include <memory>
#include <d3dx9.h>
#include "EfzRender.h"
#include "EfzFixes.h"
#include "myIDirectDraw.h"

// The implicit members the export brings, and TextRender's.
// FUNCTION: 0x10016000 ??4EfzRender@@QAEAAV0@ABV0@@Z
// FUNCTION: 0x10016440 ??0TextRender@@QAE@ABU0@@Z
// FUNCTION: 0x10016470 ??1TextRender@@QAE@XZ
// FUNCTION: 0x10015f30 ??0D3DXVECTOR2@@QAE@XZ

// FUNCTION: 0x10016020 ??8@YA_NABURectRender@@0@Z
bool operator==(const RectRender &a, const RectRender &b)
{
    return a.rect.left == b.rect.left && a.rect.right == b.rect.right
        && a.rect.top == b.rect.top && a.rect.bottom == b.rect.bottom;
}

// FUNCTION: 0x10016050
EfzRender::EfzRender()
{
    format = D3DFMT_P8;
    displayFormat = D3DFMT_X8R8G8B8;
    deviceType = D3DDEVTYPE_HAL;
    filter = D3DTEXF_NONE;
    textEnabled = false;
    primary = NULL;
    surface = NULL;
    renderTarget = NULL;
    font = NULL;
    memset(&params, 0, sizeof(params));
    device = NULL;
    d3d = NULL;
    window = NULL;
    software = false;
    memset(&placement, 0, sizeof(placement));
    fullscreen = false;
    texts = new std::list<TextRender>();
    boxEnabled = false;
    boxes = new std::unordered_set<RectRender>();
}

// FUNCTION: 0x10016170
EfzRender::~EfzRender()
{
}

// Each line is drawn four times in black, a pixel off in each direction, then in
// white over them: white text with a black outline.
// FUNCTION: 0x10016180
void EfzRender::renderText()
{
    if (!textEnabled || !font || !surface)
        return;
    IDirect3DSurface9 *target;
    device->GetRenderTarget(0, &target);
    device->SetRenderTarget(0, renderTarget);
    device->BeginScene();
    for (TextRender text : *texts) {
        text.format |= DT_NOCLIP | DT_SINGLELINE;
        if (text.format & DT_RIGHT)
            text.x -= 200;
        RECT rect;
        rect.right = text.x + 200;
        rect.top = text.y;
        rect.left = text.x;
        rect.bottom = text.y + 20;
        RECT outline = rect;
        outline.left--;
        outline.right--;
        font->DrawTextW(NULL, text.text->c_str(), text.text->length(), &outline, text.format, 0xff000000);
        outline = rect;
        outline.left++;
        outline.right++;
        font->DrawTextW(NULL, text.text->c_str(), text.text->length(), &outline, text.format, 0xff000000);
        outline = rect;
        outline.top--;
        outline.bottom--;
        font->DrawTextW(NULL, text.text->c_str(), text.text->length(), &outline, text.format, 0xff000000);
        outline = rect;
        outline.top++;
        outline.bottom++;
        font->DrawTextW(NULL, text.text->c_str(), text.text->length(), &outline, text.format, 0xff000000);
        font->DrawTextW(NULL, text.text->c_str(), text.text->length(), &rect, text.format, 0xffffffff);
    }
    device->EndScene();
    device->SetRenderTarget(0, target);
    target->Release();
}

// FUNCTION: 0x10016480
void EfzRender::setRenderText(bool enable)
{
    textEnabled = enable;
}

// FUNCTION: 0x10016490
void EfzRender::addTextRender(std::wstring text, int x, int y, DWORD format)
{
    texts->push_back(TextRender(text, x, y, format));
}

// FUNCTION: 0x10016510
void EfzRender::clearTextRender()
{
    texts->clear();
}

// Consolas from Vista on, MS Gothic before. The latter's name is the Shift-JIS bytes
// of "ＭＳゴシック" read as code page 1252, as a compiler on a Western system reads a
// Shift-JIS source.
// FUNCTION: 0x10016520
void EfzRender::initTextRender()
{
    OSVERSIONINFOW version;
    memset(&version, 0, sizeof(version));
    version.dwOSVersionInfoSize = sizeof(version);
    GetVersionExW(&version);
    if (version.dwMajorVersion < 6) {
        D3DXCreateFontW(device, 14, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_OUTLINE_PRECIS,
            PROOF_QUALITY, FIXED_PITCH | FF_MODERN,
            L"\x201a\x006c\x201a\x0072\x0192\x0053\x0192\x0056\x0192\x0062\x0192\x004e", &font);
    } else {
        D3DXCreateFontW(device, 15, 0, 0, 0, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"Consolas", &font);
    }
    textEnabled = false;
}

// After a failed Present: the default-pool surfaces and the font go before Reset and
// come back after it.
// FUNCTION: 0x100165c0
void EfzRender::resetDev(D3DPRESENT_PARAMETERS &params)
{
    HRESULT result = device->TestCooperativeLevel();
    if (result != D3DERR_DEVICENOTRESET && result != D3D_OK)
        return;
    if (surface)
        surface->Release();
    if (renderTarget)
        renderTarget->Release();
    font->OnLostDevice();
    device->Reset(&params);
    font->OnResetDevice();
    if (surface)
        device->CreateOffscreenPlainSurface(primary->width, primary->height, displayFormat,
            D3DPOOL_DEFAULT, &surface, NULL);
    if (renderTarget)
        device->CreateRenderTarget(640, 480, displayFormat, D3DMULTISAMPLE_NONE, 0, TRUE,
            &renderTarget, NULL);
}

// FUNCTION: 0x10016670
void EfzRender::toggleFullScreen()
{
    setFullscreen(!fullscreen);
}

// Borderless over the whole monitor, and back to the window as it was.
// FUNCTION: 0x10016690
void EfzRender::setFullscreen(bool fullscreen)
{
    if (!device || !window)
        return;
    if (fullscreen == isFullscreen())
        return;
    DWORD style = GetWindowLongW(window, GWL_STYLE);
    if (style & WS_OVERLAPPEDWINDOW) {
        MONITORINFO monitor = { sizeof(monitor) };
        if (GetWindowPlacement(window, &placement)
            && GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY), &monitor)) {
            SetWindowLongW(window, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(window, HWND_TOPMOST, monitor.rcMonitor.left, monitor.rcMonitor.top,
                monitor.rcMonitor.right - monitor.rcMonitor.left,
                monitor.rcMonitor.bottom - monitor.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }
    } else {
        SetWindowLongW(window, GWL_STYLE, style | WS_WINDOW);
        SetWindowPlacement(window, &placement);
        SetWindowPos(window, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
    this->fullscreen = fullscreen;
    ShowCursor(!fullscreen);
}

// FUNCTION: 0x100167c0
bool EfzRender::isFullscreen()
{
    return fullscreen;
}

// FUNCTION: 0x100167d0
bool EfzRender::isActiveWindow()
{
    return GetForegroundWindow() == window;
}

// FUNCTION: 0x100167f0
void EfzRender::setBoxRender(bool enable)
{
    boxEnabled = enable;
}

// FUNCTION: 0x10016800
void EfzRender::addRectRender(RECT rect, DWORD color, unsigned int flags)
{
    boxes->insert(RectRender(rect, color, flags));
}

// Each box is a closed line two pixels wide, stippled by its flags (EfzRevival.dll
// gives the hitboxes that have already hit a broken pattern).
// FUNCTION: 0x10016850
void EfzRender::renderBox()
{
    if (!surface)
        return;
    IDirect3DSurface9 *target;
    device->GetRenderTarget(0, &target);
    device->SetRenderTarget(0, renderTarget);
    device->BeginScene();
    for (RectRender box : *boxes) {
        ID3DXLine *line;
        D3DXCreateLine(device, &line);
        D3DXVECTOR2 points[5];
        D3DXVECTOR2 point;
        point.x = (float)box.rect.left;
        point.y = (float)box.rect.top;
        points[0] = point;
        point.x = (float)box.rect.right;
        point.y = (float)box.rect.top;
        points[1] = point;
        point.x = (float)box.rect.right;
        point.y = (float)box.rect.bottom;
        points[2] = point;
        point.x = (float)box.rect.left;
        point.y = (float)box.rect.bottom;
        points[3] = point;
        point.x = (float)box.rect.left;
        point.y = (float)box.rect.top;
        points[4] = point;
        line->SetWidth(2.0f);
        line->SetPatternScale(1.0f);
        line->SetPattern(box.flags);
        line->Draw(points, 5, box.color);
        line->Release();
    }
    device->EndScene();
    device->SetRenderTarget(0, target);
    target->Release();
}

// FUNCTION: 0x10016aa0
void EfzRender::clearBoxRender()
{
    boxes->clear();
}
