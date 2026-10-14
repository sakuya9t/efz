// Sixth object of efz.exe (0x4083b0-0x40c5df): CGraphics, the DirectDraw layer.
#include <stdlib.h>
#include <string.h>
#include "efz.h"

BOOL CGraphics::Init(HWND hWnd, BYTE mode)
{
    DDSURFACEDESC ddsd;
    HRESULT hr;
    DDSCAPS caps;

    m_mode = mode;
    m_hwnd = hWnd;
    hr = DirectDrawCreate(NULL, &m_dd, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "DirectDrawオブジェクトの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    hr = m_dd->SetCooperativeLevel(m_hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);
    if (hr != DD_OK) {
        MessageBox(NULL, "DirectDraw協調に失敗", "ERROR", MB_OK);
        return Close();
    }
    if (mode == 1) {
        hr = m_dd->SetDisplayMode(640, 480, 8);
        if (hr != DD_OK) {
            MessageBox(NULL, "640*480の解像度の設定に失敗", "ERROR", MB_OK);
            return Close();
        }
    } else {
        hr = m_dd->SetDisplayMode(320, 240, 8);
        if (hr != DD_OK) {
            MessageBox(NULL, "320*240の解像度の設定に失敗", "ERROR", MB_OK);
            return Close();
        }
    }
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwWidth = m_mode * 320 + 320;
    ddsd.dwHeight = m_mode * 240 + 240;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwBackBufferCount = 1;
    hr = m_dd->CreateSurface(&ddsd, &m_primary, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "主サーフェイスの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    hr = m_primary->GetAttachedSurface(&caps, &m_back);
    if (hr != DD_OK) {
        MessageBox(NULL, "バックバッファの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    m_dd->CreatePalette(DDPCAPS_8BIT, m_palette, &m_ddpal, NULL);
    m_primary->SetPalette(m_ddpal);
    return TRUE;
}

BOOL CGraphics::SetMode8()
{
    DDSURFACEDESC ddsd;
    HRESULT hr;
    DDSCAPS caps;

    if (m_back) {
        m_back->Release();
        m_back = NULL;
    }
    if (m_primary) {
        m_primary->Release();
        m_primary = NULL;
    }
    if (m_mode == 1) {
        hr = m_dd->SetDisplayMode(640, 480, 8);
        if (hr != DD_OK) {
            MessageBox(NULL, "640*480の解像度の設定に失敗", "ERROR", MB_OK);
            return Close();
        }
    } else {
        hr = m_dd->SetDisplayMode(320, 240, 8);
        if (hr != DD_OK) {
            MessageBox(NULL, "320*240の解像度の設定に失敗", "ERROR", MB_OK);
            return Close();
        }
    }
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwWidth = m_mode * 320 + 320;
    ddsd.dwHeight = m_mode * 240 + 240;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwBackBufferCount = 1;
    hr = m_dd->CreateSurface(&ddsd, &m_primary, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "主サーフェイスの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    hr = m_primary->GetAttachedSurface(&caps, &m_back);
    if (hr != DD_OK) {
        MessageBox(NULL, "バックバッファの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    return TRUE;
}

BOOL CGraphics::SetMode16()
{
    DDSURFACEDESC ddsd;
    HRESULT hr;
    DDSCAPS caps;

    if (m_back) {
        m_back->Release();
        m_back = NULL;
    }
    if (m_primary) {
        m_primary->Release();
        m_primary = NULL;
    }
    if (m_mode == 1) {
        hr = m_dd->SetDisplayMode(640, 480, 16);
        if (hr != DD_OK) {
            MessageBox(NULL, "640*480の解像度の設定に失敗", "ERROR", MB_OK);
            return Close();
        }
    } else {
        hr = m_dd->SetDisplayMode(320, 240, 16);
        if (hr != DD_OK) {
            MessageBox(NULL, "320*240の解像度の設定に失敗", "ERROR", MB_OK);
            return Close();
        }
    }
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwWidth = m_mode * 320 + 320;
    ddsd.dwHeight = m_mode * 240 + 240;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwBackBufferCount = 1;
    hr = m_dd->CreateSurface(&ddsd, &m_primary, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "主サーフェイスの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    caps.dwCaps = DDSCAPS_BACKBUFFER;
    hr = m_primary->GetAttachedSurface(&caps, &m_back);
    if (hr != DD_OK) {
        MessageBox(NULL, "バックバッファの生成に失敗", "ERROR", MB_OK);
        return Close();
    }
    return TRUE;
}

void CGraphics::Shutdown()
{
    if (m_ddpal) {
        m_ddpal->Release();
        m_ddpal = NULL;
    }
    if (m_back) {
        m_back->Release();
        m_back = NULL;
    }
    if (m_primary) {
        m_primary->Release();
        m_primary = NULL;
    }
    if (m_dd) {
        m_dd->RestoreDisplayMode();
        m_dd->Release();
        m_dd = NULL;
    }
}

CGraphics::~CGraphics()
{
    if (m_ddpal) {
        m_ddpal->Release();
        m_ddpal = NULL;
    }
    if (m_back) {
        m_back->Release();
        m_back = NULL;
    }
    if (m_primary) {
        m_primary->Release();
        m_primary = NULL;
    }
    if (m_dd) {
        m_dd->RestoreDisplayMode();
        m_dd->Release();
        m_dd = NULL;
    }
}

void CGraphics::ReleaseSurface(IDirectDrawSurface** surface)
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
    if (m_primary->Restore() != DD_OK)
        return FALSE;
    return TRUE;
}

BOOL CGraphics::RestoreSurface(IDirectDrawSurface** surface)
{
    if ((*surface)->Restore() != DD_OK)
        return FALSE;
    return TRUE;
}

RECT CGraphics::LoadBmp(IDirectDrawSurface** surface, const char* name, BYTE base)
{
    DDSURFACEDESC ddsd;
    BYTE* data;
    HRESULT hr;
    int width;
    int height;
    DWORD dw;
    DWORD fileSize;
    int off;
    BYTE* dst;
    DDSURFACEDESC lock;
    HANDLE h;

    h = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    fileSize = GetFileSize(h, NULL);
    data = new BYTE[fileSize];
    ReadFile(h, data, fileSize, &dw, NULL);
    width = data[0x12] + (data[0x13] << 8);
    width = (4 - width % 4) * (width % 4 > 0) + width;
    height = data[0x16] + (data[0x17] << 8);
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    hr = m_dd->CreateSurface(&ddsd, surface, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "オフスクリーンサーフェイスの生成に失敗", name, MB_OK);
        return MakeRect(0, 0, 0, 0);
    }
    lock.dwSize = sizeof(lock);
    off = data[0xa] + (data[0xb] << 8);
    hr = (*surface)->Lock(NULL, &lock, DDLOCK_WAIT, NULL);
    dst = (BYTE*)lock.lpSurface;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            dst[(height - 1 - y) * lock.lPitch + x] = data[y * width + x + off] + base;
    }
    hr = (*surface)->Unlock(lock.lpSurface);
    CloseHandle(h);
    delete data;
    return MakeRect(0, 0, width, height);
}

RECT CGraphics::LoadBmpHigh(IDirectDrawSurface** surface, const char* name, BYTE base)
{
    DDSURFACEDESC ddsd;
    BYTE* data;
    HRESULT hr;
    int width;
    int height;
    DWORD dw;
    DWORD fileSize;
    int off;
    BYTE* dst;
    BYTE pix;
    DDSURFACEDESC lock;
    HANDLE h;

    h = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    fileSize = GetFileSize(h, NULL);
    data = new BYTE[fileSize];
    ReadFile(h, data, fileSize, &dw, NULL);
    width = data[0x12] + (data[0x13] << 8);
    width = (4 - width % 4) * (width % 4 > 0) + width;
    height = data[0x16] + (data[0x17] << 8);
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    hr = m_dd->CreateSurface(&ddsd, surface, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "オフスクリーンサーフェイスの生成に失敗", name, MB_OK);
        return MakeRect(0, 0, 0, 0);
    }
    lock.dwSize = sizeof(lock);
    off = data[0xa] + (data[0xb] << 8);
    hr = (*surface)->Lock(NULL, &lock, DDLOCK_WAIT, NULL);
    dst = (BYTE*)lock.lpSurface;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pix = data[y * width + x + off];
            if (pix >= 0x28)
                dst[(height - 1 - y) * lock.lPitch + x] = pix + 0x87;
            else
                dst[(height - 1 - y) * lock.lPitch + x] = pix + base;
        }
    }
    hr = (*surface)->Unlock(lock.lpSurface);
    CloseHandle(h);
    delete data;
    return MakeRect(0, 0, width, height);
}

int CGraphics::LoadSurface(IDirectDrawSurface** surface, BYTE* data, BYTE rle, BYTE base)
{
    DDSURFACEDESC ddsd;
    BYTE run;
    BYTE c;
    HRESULT hr;
    int width;
    int height;
    int offset;
    BYTE* bits;
    DDSURFACEDESC lock;

    offset = 0;
    run = 0;
    c = 0;
    width = data[offset] + (data[offset + 1] << 8);
    height = data[offset + 2] + (data[offset + 3] << 8);
    offset += 4;
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    hr = m_dd->CreateSurface(&ddsd, surface, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "オフスクリーンサーフェイスの生成に失敗", NULL, MB_OK);
        return 0;
    }
    lock.dwSize = sizeof(lock);
    hr = (*surface)->Lock(NULL, &lock, DDLOCK_WAIT, NULL);
    bits = (BYTE*)lock.lpSurface;
    if (rle == 0) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                bits[(height - 1 - y) * lock.lPitch + x] = data[y * width + x + 4] + base;
                offset++;
            }
        }
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (run == 0) {
                    if (data[offset] <= rle) {
                        c = data[offset] + base;
                        offset++;
                    } else {
                        run = data[offset] - rle - 1;
                        offset++;
                    }
                } else {
                    run--;
                }
                bits[y * lock.lPitch + x] = c;
            }
        }
    }
    hr = (*surface)->Unlock(lock.lpSurface);
    return offset;
}

int CGraphics::LoadSurfaceHigh(IDirectDrawSurface** surface, BYTE* data, BYTE rle, BYTE base)
{
    DDSURFACEDESC ddsd;
    BYTE run;
    BYTE c;
    HRESULT hr;
    int width;
    int height;
    int offset;
    BYTE* bits;
    BYTE pix;
    DDSURFACEDESC lock;

    offset = 0;
    run = 0;
    c = 0;
    width = data[offset] + (data[offset + 1] << 8);
    height = data[offset + 2] + (data[offset + 3] << 8);
    offset += 4;
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
    ddsd.dwWidth = width;
    ddsd.dwHeight = height;
    hr = m_dd->CreateSurface(&ddsd, surface, NULL);
    if (hr != DD_OK) {
        MessageBox(NULL, "オフスクリーンサーフェイスの生成に失敗", NULL, MB_OK);
        return 0;
    }
    lock.dwSize = sizeof(lock);
    hr = (*surface)->Lock(NULL, &lock, DDLOCK_WAIT, NULL);
    bits = (BYTE*)lock.lpSurface;
    if (rle == 0) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                pix = data[y * width + x + 4];
                if (pix >= 0x28)
                    bits[(height - 1 - y) * lock.lPitch + x] = pix + 0x87;
                else
                    bits[(height - 1 - y) * lock.lPitch + x] = pix + base;
                offset++;
            }
        }
    } else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (run == 0) {
                    if (data[offset] <= rle) {
                        if (data[offset] >= 0x28) {
                            c = data[offset] + 0x87;
                            offset++;
                        } else {
                            c = data[offset] + base;
                            offset++;
                        }
                    } else {
                        run = data[offset] - rle - 1;
                        offset++;
                    }
                } else {
                    run--;
                }
                bits[y * lock.lPitch + x] = c;
            }
        }
    }
    hr = (*surface)->Unlock(lock.lpSurface);
    return offset;
}

// The clipping shared by the blitters: rejects empty rectangles, clips `dst` to the
// screen (and to minLeft on the left) and `src` with it, mirrors `src` within the sprite when flipping, and rejects
// what is left if it is empty.
#define CLIP(minLeft, screenWidth, screenHeight, failure)                            \
    r = src.right;                                                          \
    if (dst.top >= dst.bottom || dst.left >= dst.right)                     \
        return failure;                                                     \
    if (src.top >= src.bottom || src.left >= src.right)                     \
        return failure;                                                     \
    if (dst.top < 0) {                                                      \
        src.top -= dst.top;                                                 \
        dst.top = 0;                                                        \
    }                                                                       \
    if (dst.left < minLeft) {                                               \
        src.left -= dst.left;                                               \
        dst.left = minLeft;                                                 \
    }                                                                       \
    if (dst.bottom > screenHeight) {                                        \
        src.bottom -= dst.bottom - screenHeight;                            \
        dst.bottom = screenHeight;                                          \
    }                                                                       \
    if (dst.right > screenWidth) {                                          \
        src.right -= dst.right - screenWidth;                               \
        dst.right = screenWidth;                                            \
    }                                                                       \
    if (flip) {                                                             \
        save = r - src.left;                                                \
        src.left = r - src.right;                                           \
        src.right = save;                                                   \
    }                                                                       \
    if (dst.top >= dst.bottom || dst.left >= dst.right)                     \
        return TRUE;                                                        \
    if (src.top >= src.bottom || src.left >= src.right)                     \
        return TRUE;

// Locks the source and the destination; a lost surface returns FALSE.
#define LOCK(target)                                                        \
    srcsd.dwSize = sizeof(srcsd);                                           \
    ddsdDst.dwSize = sizeof(ddsdDst);                                       \
    hr = surface->Lock(&src, &srcsd, DDLOCK_WAIT | DDLOCK_READONLY, NULL);  \
    if (hr != DD_OK) {                                                      \
        if (hr == DDERR_SURFACELOST)                                        \
            return FALSE;                                                   \
        return TRUE;                                                        \
    }                                                                       \
    hr = target->Lock(&dst, &ddsdDst, DDLOCK_WAIT, NULL);                   \
    if (hr != DD_OK) {                                                      \
        if (hr == DDERR_SURFACELOST)                                        \
            return FALSE;                                                   \
        return TRUE;                                                        \
    }

BOOL CGraphics::Blit(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip)
{
    BYTE* srcBits;
    int r;
    HRESULT hr;
    int save;
    int width;
    int height;
    BYTE* lpDst;
    DDSURFACEDESC ddsdDst;
    DDSURFACEDESC srcsd;

    CLIP(0, 320, 240, TRUE)
    LOCK(m_back)
    srcBits = (BYTE*)srcsd.lpSurface;
    lpDst = (BYTE*)ddsdDst.lpSurface;
    width = dst.right - dst.left;
    height = dst.bottom - dst.top;
    if (key > 0) {
        BYTE ck = key;
        if (flip) {
            __asm {
                push esi
                push edi
                mov ah, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row1:
                mov ecx, width
                dec ecx
            pixel1:
                mov ebx, width
                dec ebx
                sub ebx, ecx
                mov al, [esi + ebx]
                cmp ah, al
                je skip1
                mov [edi + ecx], al
            skip1:
                dec ecx
                jns pixel1
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row1
                pop edi
                pop esi
            }
        } else {
            __asm {
                push esi
                push edi
                mov ah, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row2:
                mov ecx, width
                dec ecx
            pixel2:
                mov al, [esi + ecx]
                cmp ah, al
                je skip2
                mov [edi + ecx], al
            skip2:
                dec ecx
                jns pixel2
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row2
                pop edi
                pop esi
            }
        }
    } else {
        __asm {
            push esi
            push edi
            mov edi, lpDst
            mov esi, srcBits
            mov edx, height
            dec edx
        row3:
            mov ecx, width
            dec ecx
        pixel3:
            mov al, [esi + ecx]
            mov [edi + ecx], al
            dec ecx
            jns pixel3
            add esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row3
            pop edi
            pop esi
        }
    }
    hr = m_back->Unlock(ddsdDst.lpSurface);
    hr = surface->Unlock(srcsd.lpSurface);
    return TRUE;
}

BOOL CGraphics::BlitTo(IDirectDrawSurface* target, RECT dst, IDirectDrawSurface* surface, RECT src,
                       BYTE key, BOOL flip)
{
    BYTE* srcBits;
    int r;
    HRESULT hr;
    int save;
    int width;
    int height;
    BYTE* lpDst;
    DDSURFACEDESC ddsdDst;
    DDSURFACEDESC srcsd;

    CLIP(0, 640, 480, TRUE)
    LOCK(target)
    srcBits = (BYTE*)srcsd.lpSurface;
    lpDst = (BYTE*)ddsdDst.lpSurface;
    width = dst.right - dst.left;
    height = dst.bottom - dst.top;
    if (key > 0) {
        BYTE ck = key;
        if (flip) {
            __asm {
                push esi
                push edi
                mov ah, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row1:
                mov ecx, width
                dec ecx
            pixel1:
                mov ebx, width
                dec ebx
                sub ebx, ecx
                mov al, [esi + ebx]
                cmp ah, al
                je skip1
                mov [edi + ecx], al
            skip1:
                dec ecx
                jns pixel1
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row1
                pop edi
                pop esi
            }
        } else {
            __asm {
                push esi
                push edi
                mov ah, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row2:
                mov ecx, width
                dec ecx
            pixel2:
                mov al, [esi + ecx]
                cmp ah, al
                je skip2
                mov [edi + ecx], al
            skip2:
                dec ecx
                jns pixel2
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row2
                pop edi
                pop esi
            }
        }
    } else {
        __asm {
            push esi
            push edi
            mov edi, lpDst
            mov esi, srcBits
            mov edx, height
            dec edx
        row3:
            mov ecx, width
            dec ecx
        pixel3:
            mov al, [esi + ecx]
            mov [edi + ecx], al
            dec ecx
            jns pixel3
            add esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row3
            pop edi
            pop esi
        }
    }
    hr = target->Unlock(ddsdDst.lpSurface);
    hr = surface->Unlock(srcsd.lpSurface);
    return TRUE;
}

BOOL CGraphics::BlitEx(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                       char mode)
{
    BYTE* srcBits;
    int r;
    HRESULT hr;
    int save;
    int width;
    int height;
    BYTE* lpDst;
    BYTE* table;
    DDSURFACEDESC ddsdDst;
    DDSURFACEDESC srcsd;

    if (mode != 0 && mode != 1)
        return FALSE;
    CLIP(0, 320, 240, TRUE)
    LOCK(m_back)
    srcBits = (BYTE*)srcsd.lpSurface;
    lpDst = (BYTE*)ddsdDst.lpSurface;
    table = (BYTE*)m_blend[mode];
    width = dst.right - dst.left;
    height = dst.bottom - dst.top;
    if (key > 0) {
        BYTE ck = key;
        if (flip) {
            __asm {
                push esi
                push edi
                mov al, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row1:
                mov ecx, width
                dec ecx
            pixel1:
                mov ebx, width
                dec ebx
                sub ebx, ecx
                mov al, ck
                mov ah, [esi + ebx]
                cmp ah, al
                je skip1
                mov ebx, table
                mov al, [edi + ecx]
                mov al, [ebx + eax]
                mov [edi + ecx], al
            skip1:
                dec ecx
                jns pixel1
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row1
                pop edi
                pop esi
            }
        } else {
            __asm {
                push esi
                push edi
                mov al, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row2:
                mov ecx, width
                dec ecx
            pixel2:
                mov al, ck
                mov ah, [esi + ecx]
                cmp ah, al
                je skip2
                mov ebx, table
                mov al, [edi + ecx]
                mov al, [ebx + eax]
                mov [edi + ecx], al
            skip2:
                dec ecx
                jns pixel2
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row2
                pop edi
                pop esi
            }
        }
    } else {
        __asm {
            push esi
            push edi
            mov edi, lpDst
            mov esi, srcBits
            mov edx, height
            mov ebx, table
            dec edx
        row3:
            mov ecx, width
            dec ecx
        pixel3:
            mov ah, [esi + ecx]
            mov al, [edi + ecx]
            mov al, [ebx + eax]
            mov [edi + ecx], al
            dec ecx
            jns pixel3
            add esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row3
            pop edi
            pop esi
        }
    }
    hr = m_back->Unlock(ddsdDst.lpSurface);
    hr = surface->Unlock(srcsd.lpSurface);
    return TRUE;
}

BOOL CGraphics::BlitTint(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                         BYTE color)
{
    BYTE* srcBits;
    int r;
    HRESULT hr;
    int save;
    int width;
    int height;
    BYTE* lpDst;
    BYTE* table;
    DDSURFACEDESC ddsdDst;
    DDSURFACEDESC srcsd;

    CLIP(0, 320, 240, TRUE)
    LOCK(m_back)
    srcBits = (BYTE*)srcsd.lpSurface;
    lpDst = (BYTE*)ddsdDst.lpSurface;
    table = (BYTE*)m_blend[1];
    width = dst.right - dst.left;
    height = dst.bottom - dst.top;
    if (key > 0) {
        BYTE ck = key;
        if (flip) {
            __asm {
                push esi
                push edi
                mov al, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row1:
                mov ecx, width
                dec ecx
            pixel1:
                mov ebx, width
                dec ebx
                sub ebx, ecx
                mov al, ck
                mov ah, [esi + ebx]
                cmp ah, al
                je skip1
                mov ebx, table
                mov al, color
                mov al, [ebx + eax]
                mov [edi + ecx], al
            skip1:
                dec ecx
                jns pixel1
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row1
                pop edi
                pop esi
            }
        } else {
            __asm {
                push esi
                push edi
                mov al, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row2:
                mov ecx, width
                dec ecx
            pixel2:
                mov al, ck
                mov ah, [esi + ecx]
                cmp ah, al
                je skip2
                mov ebx, table
                mov al, color
                mov al, [ebx + eax]
                mov [edi + ecx], al
            skip2:
                dec ecx
                jns pixel2
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row2
                pop edi
                pop esi
            }
        }
    } else {
        __asm {
            push esi
            push edi
            mov edi, lpDst
            mov esi, srcBits
            mov edx, height
            mov ebx, table
            dec edx
        row3:
            mov ecx, width
            dec ecx
        pixel3:
            mov ah, [esi + ecx]
            mov al, color
            mov al, [ebx + eax]
            mov [edi + ecx], al
            dec ecx
            jns pixel3
            add esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row3
            pop edi
            pop esi
        }
    }
    hr = m_back->Unlock(ddsdDst.lpSurface);
    hr = surface->Unlock(srcsd.lpSurface);
    return TRUE;
}

BOOL CGraphics::BlitShadow(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip,
                           BYTE shade)
{
    BYTE* srcBits;
    int r = src.right;
    int flag = 0;
    HRESULT hr;
    int save;
    int width;
    int height;
    BYTE* lpDst;
    BYTE* table;
    int start;
    DDSURFACEDESC ddsdDst;
    DDSURFACEDESC srcsd;
    BYTE col;

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
        save = r - src.left;
        src.left = r - src.right;
        src.right = save;
    }
    if (dst.top > dst.bottom || dst.left > dst.right)
        return TRUE;
    if (src.top > src.bottom || src.left > src.right)
        return TRUE;
    LOCK(m_back)
    srcBits = (BYTE*)srcsd.lpSurface;
    lpDst = (BYTE*)ddsdDst.lpSurface;
    table = (BYTE*)m_blend[0];
    width = dst.right - dst.left;
    height = dst.bottom - dst.top;
    start = (src.bottom - src.top - 1) * srcsd.lPitch;
    col = key;
    if (flip) {
        __asm {
            push esi
            push edi
            mov ah, col
            mov edi, lpDst
            mov esi, srcBits
            add esi, start
            mov edx, height
            dec edx
        row1:
            mov ecx, width
            dec ecx
        pixel1:
            mov ah, col
            mov ebx, width
            dec ebx
            sub ebx, ecx
            mov al, [esi + ebx]
            cmp ah, al
            je skip1
            mov ebx, table
            mov ah, [edi + ecx]
            mov al, shade
            mov al, [ebx + eax]
            mov [edi + ecx], al
        skip1:
            dec ecx
            jns pixel1
            sub esi, srcsd.lPitch
            sub esi, srcsd.lPitch
            sub esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row1
            pop edi
            pop esi
        }
    } else {
        __asm {
            push esi
            push edi
            mov ah, col
            mov edi, lpDst
            mov esi, srcBits
            add esi, start
            mov edx, height
            dec edx
        row2:
            mov ecx, width
            dec ecx
        pixel2:
            mov ah, col
            mov al, [esi + ecx]
            cmp ah, al
            je skip2
            mov ebx, table
            mov ah, [edi + ecx]
            mov al, shade
            mov al, [ebx + eax]
            mov [edi + ecx], al
        skip2:
            dec ecx
            jns pixel2
            sub esi, srcsd.lPitch
            sub esi, srcsd.lPitch
            sub esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row2
            pop edi
            pop esi
        }
    }
    hr = m_back->Unlock(ddsdDst.lpSurface);
    hr = surface->Unlock(srcsd.lpSurface);
    return TRUE;
}

BOOL CGraphics::BlitSmear(RECT dst, IDirectDrawSurface* surface, RECT src, BYTE key, BOOL flip)
{
    BYTE* srcBits;
    int r;
    HRESULT hr;
    int save;
    int width;
    int height;
    BYTE* lpDst;
    DDSURFACEDESC ddsdDst;
    DDSURFACEDESC srcsd;

    CLIP(3, 320, 240, TRUE)
    LOCK(m_back)
    srcBits = (BYTE*)srcsd.lpSurface;
    lpDst = (BYTE*)ddsdDst.lpSurface;
    width = dst.right - dst.left;
    height = dst.bottom - dst.top;
    if (key > 0) {
        BYTE ck = key;
        if (flip) {
            __asm {
                push esi
                push edi
                mov ah, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row1:
                mov ecx, width
                dec ecx
            pixel1:
                mov ebx, width
                dec ebx
                sub ebx, ecx
                mov al, [esi + ebx]
                cmp ah, al
                je skip1
                mov al, [edi + ecx - 3]
                mov [edi + ecx], al
            skip1:
                dec ecx
                jns pixel1
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row1
                pop edi
                pop esi
            }
        } else {
            __asm {
                push esi
                push edi
                mov ah, ck
                mov edi, lpDst
                mov esi, srcBits
                mov edx, height
                dec edx
            row2:
                mov ecx, width
                dec ecx
            pixel2:
                mov al, [esi + ecx]
                cmp ah, al
                je skip2
                mov al, [edi + ecx - 3]
                mov [edi + ecx], al
            skip2:
                dec ecx
                jns pixel2
                add esi, srcsd.lPitch
                add edi, ddsdDst.lPitch
                dec edx
                jns row2
                pop edi
                pop esi
            }
        }
    } else {
        __asm {
            push esi
            push edi
            mov edi, lpDst
            mov esi, srcBits
            mov edx, height
            dec edx
        row3:
            mov ecx, width
            dec ecx
        pixel3:
            mov al, [edi + ecx - 3]
            mov [edi + ecx], al
            dec ecx
            jns pixel3
            add esi, srcsd.lPitch
            add edi, ddsdDst.lPitch
            dec edx
            jns row3
            pop edi
            pop esi
        }
    }
    hr = m_back->Unlock(ddsdDst.lpSurface);
    hr = surface->Unlock(srcsd.lpSurface);
    return TRUE;
}

BOOL CGraphics::DrawLine(int x1, int y1, int x2, int y2)
{
    RECT r;
    HRESULT hr;
    int offset;
    int dw;
    int hgt;
    double slope;
    BYTE* dst;
    BYTE* shade;
    DDSURFACEDESC desc;

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
    dw = r.right - r.left + 1;
    hgt = r.bottom - r.top + 1;
    desc.dwSize = sizeof(desc);
    hr = m_back->Lock(&r, &desc, DDLOCK_WAIT, NULL);
    if (hr != DD_OK) {
        if (hr == DDERR_SURFACELOST)
            return FALSE;
        return TRUE;
    }
    dst = (BYTE*)desc.lpSurface;
    shade = m_blend[1][0xe2];
    slope = (double)hgt / dw;
    if (hgt < slope)
        slope = hgt;
    if ((y2 - y1) * (x2 - x1) >= 0) {
        for (int i = 0; i < dw; i++) {
            for (double y = i * slope; y <= (i + 1) * slope; y += 1.0) {
                offset = (int)y * desc.lPitch + i;
                dst[offset] = shade[dst[offset]];
            }
        }
    } else {
        for (int i = 0; i < dw; i++) {
            for (double y = i * slope; y <= (i + 1) * slope; y += 1.0) {
                offset = dw - 1 - i + (int)y * desc.lPitch;
                dst[offset] = shade[dst[offset]];
            }
        }
    }
    hr = m_back->Unlock(desc.lpSurface);
    return TRUE;
}

BOOL CGraphics::DrawFrame(RECT rc, BYTE color)
{
    int j;
    HRESULT hr;
    int width;
    int height;
    BYTE* bits;
    DDSURFACEDESC sd;

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
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;
    sd.dwSize = sizeof(sd);
    hr = m_back->Lock(&rc, &sd, DDLOCK_WAIT, NULL);
    if (hr != DD_OK) {
        if (hr == DDERR_SURFACELOST)
            return FALSE;
        return TRUE;
    }
    bits = (BYTE*)sd.lpSurface;
    for (j = 0; j < width; j++) {
        bits[j] = color;
        bits[(height - 1) * sd.lPitch + j] = color;
    }
    for (j = 0; j < height; j++) {
        bits[j * sd.lPitch] = color;
        bits[j * sd.lPitch + width - 1] = color;
    }
    hr = m_back->Unlock(sd.lpSurface);
    return TRUE;
}

BOOL CGraphics::FillRect(RECT rc, BYTE color)
{
    HRESULT hr;
    int width;
    int height;
    BYTE* bits;
    DDSURFACEDESC sd;

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
    sd.dwSize = sizeof(sd);
    hr = m_back->Lock(&rc, &sd, DDLOCK_WAIT, NULL);
    if (hr != DD_OK) {
        if (hr == DDERR_SURFACELOST)
            return FALSE;
        return TRUE;
    }
    bits = (BYTE*)sd.lpSurface;
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;
    __asm {
        push edi
        mov edi, bits
        mov edx, height
        dec edx
    row:
        mov ecx, width
        dec ecx
    pixel:
        mov al, color
        mov [edi + ecx], al
        dec ecx
        jns pixel
        add edi, sd.lPitch
        dec edx
        jns row
        pop edi
    }
    hr = m_back->Unlock(sd.lpSurface);
    return TRUE;
}

BOOL CGraphics::Upscale()
{
    int offset2;
    RECT r;
    HRESULT hr;
    int width;
    int height;
    BYTE* bits;
    int srcOffset;
    DDSURFACEDESC sd;

    r = MakeRect(0, 0, 640, 480);
    sd.dwSize = sizeof(sd);
    hr = m_back->Lock(&r, &sd, DDLOCK_WAIT, NULL);
    if (hr != DD_OK) {
        if (hr == DDERR_SURFACELOST)
            return FALSE;
        return TRUE;
    }
    bits = (BYTE*)sd.lpSurface;
    srcOffset = sd.lPitch * 239;
    offset2 = sd.lPitch * 478;
    width = 320;
    height = 240;
    // From the bottom-right corner up, each pixel of the top-left 320x240 becomes a 2x2
    // block.
    __asm {
        push esi
        push edi
        mov edi, bits
        add edi, offset2
        mov esi, bits
        add esi, srcOffset
        mov edx, 239
    row:
        mov ecx, 319
        mov ebx, 638
    pixel:
        mov al, [esi + ecx]
        mov [edi + ebx], al
        inc ebx
        mov [edi + ebx], al
        add ebx, sd.lPitch
        mov [edi + ebx], al
        dec ebx
        mov [edi + ebx], al
        sub ebx, sd.lPitch
        sub ebx, 2
        dec ecx
        jns pixel
        sub edi, sd.lPitch
        sub edi, sd.lPitch
        sub esi, sd.lPitch
        dec edx
        jns row
        pop edi
        pop esi
    }
    hr = m_back->Unlock(sd.lpSurface);
    return TRUE;
}

BOOL CGraphics::Flip()
{
    HRESULT hr;

    if (m_mode)
        Upscale();
    hr = m_primary->Flip(NULL, DDFLIP_WAIT);
    if (hr != DD_OK) {
        if (hr == DDERR_SURFACELOST)
            return FALSE;
        return TRUE;
    }
    return TRUE;
}

BOOL CGraphics::LoadPaletteBmp(PALETTEENTRY* palette, const char* name, int from, int to, int count)
{
    int j;
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    int offset;
    HANDLE hFile;

    hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    size = GetFileSize(hFile, NULL);
    data = new BYTE[size];
    ReadFile(hFile, data, size, &dwRead, NULL);
    offset = 0x36;
    for (j = 0; j < count; j++) {
        palette[j + to].peBlue = data[(j + from) * 4 + offset];
        palette[j + to].peGreen = data[(j + from) * 4 + 1 + offset];
        palette[j + to].peRed = data[(j + from) * 4 + 2 + offset];
        palette[j + to].peFlags = 0;
    }
    CloseHandle(hFile);
    delete data;
    return TRUE;
}

BOOL CGraphics::LoadPaletteDat(PALETTEENTRY* palette, const char* name, int from, int to, int count)
{
    int j;
    BYTE* data;
    DWORD dwRead;
    DWORD size;
    int offset;
    HANDLE hFile;

    hFile = CreateFile(name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        return FALSE;
    }
    size = GetFileSize(hFile, NULL);
    data = new BYTE[size];
    ReadFile(hFile, data, size, &dwRead, NULL);
    offset = 1;
    for (j = 0; j < count; j++) {
        palette[j + to].peBlue = data[(j + from) * 3 + offset];
        palette[j + to].peGreen = data[(j + from) * 3 + 1 + offset];
        palette[j + to].peRed = data[(j + from) * 3 + 2 + offset];
        palette[j + to].peFlags = 0;
    }
    CloseHandle(hFile);
    delete data;
    return TRUE;
}

void CGraphics::BuildBlendTables(PALETTEENTRY* palette)
{
    BYTE m;
    BYTE c;
    BYTE jb;
    WORD a3;
    WORD dist1;
    WORD aveB;
    WORD kr;
    BYTE* row08;
    BYTE* ra;
    BYTE* redC;
    BYTE* bC2;
    BYTE* red;
    BYTE* pGa;
    BYTE* sumRow;
    WORD avgG;
    WORD cG;
    WORD cB7;
    BYTE* gbase;
    BYTE* bbase;
    WORD sr3;
    WORD end;
    BYTE* pgb;
    WORD blueSum;
    WORD best;
    BYTE* redB;
    BYTE* pbb;
    BYTE* pgc;
    WORD* sq;
    WORD meanR;
    WORD addG;
    BYTE* aBlue;

    sq = &m_quarterSquares[0x100];
    row08 = m_blend[0][0] - 0x100;
    sumRow = m_blend[1][0] - 0x100;
    red = &palette[-1].peRed;
    ra = red;
    gbase = &palette[-1].peGreen;
    pGa = gbase;
    bbase = &palette[-1].peBlue;
    aBlue = bbase;
    for (a3 = 0; a3 < 0x100; a3++) {
        end = a3 + 1;
        if (end > 0xff)
            end = 0xff;
        row08 += 0x100;
        sumRow += 0x100;
        ra += 4;
        pGa += 4;
        aBlue += 4;
        redB = red;
        pgb = gbase;
        pbb = bbase;
        for (jb = 0; jb < end; jb++) {
            sr3 = *ra + *(redB += 4);
            addG = *pGa + *(pgb += 4);
            blueSum = *aBlue + *(pbb += 4);
            meanR = sr3 >> 1;
            avgG = addG >> 1;
            aveB = blueSum >> 1;
            best = 40000;
            dist1 = best;
            if (sr3 > 0xfe)
                sr3 = 0xfe;
            if (addG > 0xfe)
                addG = 0xfe;
            if (blueSum > 0xfe)
                blueSum = 0xfe;
            redC = red + 4;
            pgc = gbase + 4;
            bC2 = bbase + 4;
            for (c = 1; c < 0xff; c++) {
                redC += 4;
                kr = *redC;
                pgc += 4;
                cG = *pgc;
                bC2 += 4;
                cB7 = *bC2;
                if (*(sq + kr - meanR) + *(sq + cG - avgG) + *(sq + cB7 - aveB) < best) {
                    best = *(sq + kr - meanR) + *(sq + cG - avgG) + *(sq + cB7 - aveB);
                    row08[jb] = c;
                }
                if (*(sq + kr - sr3) + *(sq + cG - addG) + *(sq + cB7 - blueSum) < dist1) {
                    dist1 = *(sq + kr - sr3) + *(sq + cG - addG) + *(sq + cB7 - blueSum);
                    sumRow[jb] = c;
                }
            }
        }
    }
    for (m = 0; m < 0xff; m++) {
        for (a3 = 0; a3 < m; a3++) {
            m_blend[0][a3][m] = m_blend[0][m][a3];
            m_blend[1][a3][m] = m_blend[1][m][a3];
        }
    }
}

BYTE CGraphics::GetColorKey(IDirectDrawSurface* surface)
{
    DDSURFACEDESC ddsd;
    HRESULT hr;
    int offset = 0x36;
    DWORD key;

    ddsd.dwSize = sizeof(ddsd);
    hr = surface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
    key = *(DWORD*)ddsd.lpSurface;
    key &= 0xff;
    surface->Unlock(ddsd.lpSurface);
    return (BYTE)key;
}

BOOL CGraphics::SetPalette(PALETTEENTRY* palette)
{
    m_ddpal->SetEntries(0, 0, 0xff, palette);
    return TRUE;
}

BOOL CGraphics::SetPaletteRange(PALETTEENTRY* palette, BYTE start, BYTE count)
{
    m_ddpal->SetEntries(0, start, count, &palette[start]);
    return TRUE;
}

BOOL CGraphics::ClearPalette(PALETTEENTRY* palette)
{
    int i;

    for (i = 0; i < 0x100; i++) {
        palette[i].peRed = 0;
        palette[i].peGreen = 0;
        palette[i].peBlue = 0;
    }
    return TRUE;
}

void CGraphics::Darken(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent)
{
    int i;
    PALETTEENTRY entries[0x100];

    m_ddpal->GetEntries(0, 0, 0xff, entries);
    for (i = from; i < to; i++) {
        entries[i].peRed = palette[i].peRed * percent / 100;
        entries[i].peGreen = palette[i].peGreen * percent / 100;
        entries[i].peBlue = palette[i].peBlue * percent / 100;
    }
    m_ddpal->SetEntries(0, 0, 0xff, entries);
}

void CGraphics::Brighten(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent)
{
    int i;
    PALETTEENTRY entries[0x100];

    m_ddpal->GetEntries(0, 0, 0xff, entries);
    for (i = from; i < to; i++) {
        entries[i].peRed = (0xff - palette[i].peRed) * (100 - percent) / 100 + palette[i].peRed;
        entries[i].peGreen = (0xff - palette[i].peGreen) * (100 - percent) / 100 + palette[i].peGreen;
        entries[i].peBlue = (0xff - palette[i].peBlue) * (100 - percent) / 100 + palette[i].peBlue;
    }
    m_ddpal->SetEntries(0, 0, 0xff, entries);
}

void CGraphics::Invert(PALETTEENTRY* palette, BYTE from, BYTE to, BYTE percent)
{
    int i;
    PALETTEENTRY entries[0x100];

    m_ddpal->GetEntries(0, 0, 0xff, entries);
    for (i = from; i < to; i++) {
        entries[i].peRed = (0xff - palette[i].peRed * 2) * percent / 100 + palette[i].peRed;
        entries[i].peGreen = (0xff - palette[i].peGreen * 2) * percent / 100 + palette[i].peGreen;
        entries[i].peBlue = (0xff - palette[i].peBlue * 2) * percent / 100 + palette[i].peBlue;
    }
    m_ddpal->SetEntries(0, 0, 0xff, entries);
}

void CGraphics::Screenshot(int number, PALETTEENTRY* palette)
{
    int m;
    int j;
    HRESULT hr;
    int width;
    DWORD dwWrite;
    HANDLE hFile;
    BYTE* bits;
    char num[10];
    BYTE* dat;
    DDSURFACEDESC desc;
    char fname[30];

    _strnset(fname, 0, 30);
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
    hFile = CreateFile(fname, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    dat = new BYTE[0x13036];
    desc.dwSize = sizeof(desc);
    hr = m_back->Lock(NULL, &desc, DDLOCK_WAIT, NULL);
    bits = (BYTE*)desc.lpSurface;
    width = (m_mode + 1) * 320;
    for (j = 0; j < 240; j++) {
        for (m = 0; m < 320; m++)
            dat[0x12ef6 - j * 320 + m] = bits[j * width + m];
    }
    hr = m_back->Unlock(desc.lpSurface);
    for (j = 0; j < 0x100; j++) {
        dat[j * 4 + 0x36] = palette[j].peBlue;
        dat[j * 4 + 0x37] = palette[j].peGreen;
        dat[j * 4 + 0x38] = palette[j].peRed;
        dat[j * 4 + 0x39] = 0;
    }
    // The BITMAPFILEHEADER and BITMAPINFOHEADER of a 320x240 8-bit image.
    for (j = 0; j < 0x3a; j++)
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
    delete dat;
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
