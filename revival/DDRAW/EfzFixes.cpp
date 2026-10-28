// The changes to efz.exe that make it run on its own, and the DLL's globals: the frame
// timer, the log and the renderer. dllmain.cpp's initVanilla applies the changes from
// WinMain (0x401016), before the game makes its window.
#include "stdafx.h"
#include "Version.h"
#include "EfzFixes.h"
#include "EfzRender.h"
#include "EfzTimer.h"
#include "Hook.h"
#include "Log.h"
#include "Config.h"
#include <shellapi.h>
#define DIRECTINPUT_VERSION 0x0700
#include <dinput.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// GLOBAL: 0x100b6ad0
EfzTimer g_timer;

// GLOBAL: 0x100b6a3c
// A copy of CInput::GetInput (0x40cd00), which getEfzInput calls.
void *g_inputCode;

// Helpers defined after their first use (the code is in the order of the definitions).
static bool patchGame(void *address, const void *bytes, int size);
static void inputHook();
static void readHat(BYTE *result, BYTE *player);
static BYTE hatDirection(DIJOYSTATE *state);
static void ikumiHook();
static void fixIkumiUpdate();
static void timerHook();
static void replayHook();
static void readFrameCount(DWORD *count, HANDLE file);
static HRESULT WINAPI directInputCreate(HINSTANCE instance, DWORD version, REFIID iid,
    LPVOID *object, LPUNKNOWN outer);

// --- The frame timer

// The thread waits out each frame in 1 ms steps on the game's never-signalled event,
// signals the frame, and spreads the time it was off over the next frames, at most a
// frame's worth at a time.
// FUNCTION: 0x1001c3b0
void EfzTimer::run()
{
    TIMECAPS caps = {};
    timeGetDevCaps(&caps, sizeof(caps));
    g_log << "Caps " << caps.wPeriodMin << " " << caps.wPeriodMax << "\n";
    double wait = msPerFrame;
    for (;;) {
        *startTime = timeGetTime();
        for (int remaining = (int)floor(wait); remaining > 0; ) {
            DWORD before = timeGetTime();
            WaitForSingleObject(*sleepEvent, 1);
            remaining += before - timeGetTime();
        }
        SetEvent(*frameEvent);
        error += wait - (double)(timeGetTime() - *startTime);
        double correction = 0.0;
        if (abs(error) >= 1.0)
            correction = max(-msPerFrame, (double)(error > 0.0 ? 1 : -1));
        if (error > 64.0)
            error = 64.0;
        wait = msPerFrame + correction;
        error -= correction;
    }
}

// FUNCTION: 0x1001c570
void EfzTimer::restart()
{
    setMsPerFrame(msPerFrame);
}

// The log and the renderer are defined here, after the timer's functions: the template
// code of their destructors comes out after what run() uses (abs, 0x1001efa0, is
// between the file stream's and basic_ios's), and their data follows g_timer's.
// GLOBAL: 0x100b6b08
std::fstream g_log;
// GLOBAL: 0x100b6bc8
EfzRender g_render;

// --- The window

// The client area of a window rectangle (unused).
// FUNCTION: 0x1001c580
BOOL clientRect(RECT *rect, DWORD style, BOOL menu, DWORD exStyle)
{
    RECT frame;
    SetRectEmpty(&frame);
    BOOL ok = AdjustWindowRectEx(&frame, style, menu, exStyle);
    if (ok) {
        rect->left -= frame.left;
        rect->top -= frame.top;
        rect->right -= frame.right;
        rect->bottom -= frame.bottom;
    }
    return ok;
}

// FUNCTION: 0x1001c5d0
static void onResize()
{
    LOG("Resized\n");
}

// Alt+Enter switches fullscreen; the rest is the game's WndProc (0x401670).
// FUNCTION: 0x1001c600
static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_SIZE:
        onResize();
        break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        if (wParam == VK_RETURN) {
            if (HIWORD(lParam) & KF_ALTDOWN)
                g_render.toggleFullScreen();
        } else if (wParam == 0x2000) {
            return 0;
        }
        break;
    }
    return ((WNDPROC)0x401670)(window, message, wParam, lParam);
}

// skipWindowCreation has a local object with an empty constructor and destructor: their
// code is here (0x1001c670, 0x1001c680), just before the function that uses them, though
// link-time code generation drops the calls. What the object was is lost.
struct Unknown1001c670 {
    // FUNCTION: 0x1001c670 ??0Unknown1001c670@@QAE@XZ
    Unknown1001c670()
    {
    }

    // FUNCTION: 0x1001c680 ??1Unknown1001c670@@QAE@XZ
    ~Unknown1001c670()
    {
    }
};

// WinMain jumps over its own CreateWindowEx (0x40101c to 0x4010da).
// FUNCTION: 0x1001c690
void skipWindowCreation()
{
    Unknown1001c670 unknown;
    BYTE jump[5] = { 0xe9, 0xb9, 0x00, 0x00, 0x00 };
    patchGame((void *)0x40101c, jump, 5);
}

// The window the game would have made, at the ini's position and size (640x480 at
// 10, 10 when they don't fit the screen), with the exe's icon and windowProc. The
// handle goes into WinMain's hwnd (its ebp - 0x48: the hook's caller's frame). Also
// opens the log when the ini asks for it.
// The size check is two checks with the same fallback, which the compiler merges: the
// same code as one condition, but its register allocator (which weighs each variable by
// its uses in the blocks its lifetime spans) then gives esi to width after the
// GetSystemMetrics calls and the stack to x and y, as in the original; with one
// condition y gets esi.
// FUNCTION: 0x1001c6c0
void createWindow()
{
    // A local static: its data comes after the type descriptors of the earlier objects'
    // exceptions, where a global's would come before them.
    // GLOBAL: 0x100b58a0 ?className@?1??createWindow@@YAXXZ@4PADA
    static char className[] = "ETERNAL FIGHTER ZERO";
    Config config(L"./EfzRevival.ini");
    if (config.debug) {
        g_log.open("logDdraw.txt", std::ios::out);
        LOG("Opened\n");
        LOG("Adding EFZ fixes\n");
    }
    HWND *gameWindow = NULL;
    __asm {
        mov eax, ebp
        mov eax, [eax]
        sub eax, 0x48
        mov gameWindow, eax
    }
    HINSTANCE instance = GetModuleHandleW(NULL);
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(NULL, path, MAX_PATH);
    HICON icon = ExtractIconW(NULL, path, 0);
    int width = config.windowWidth;
    int height = config.windowHeight;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    if (width < 1 || width > screenWidth) {
        width = 640;
        height = 480;
    } else if (height < 1 || height > screenHeight) {
        width = 640;
        height = 480;
    }
    int x = config.windowX;
    int y = config.windowY;
    if (x < 0 || y < 0 || x >= screenWidth || y >= screenHeight) {
        x = 10;
        y = 10;
    }
    WNDCLASSA windowClass;
    memset(&windowClass, 0, sizeof(windowClass));
    windowClass.hInstance = instance;
    windowClass.lpszClassName = className;
    windowClass.lpfnWndProc = windowProc;
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.hIcon = icon;
    windowClass.hCursor = LoadCursorW(instance, IDC_ARROW);
    windowClass.lpszMenuName = NULL;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
    windowClass.lpszClassName = className;
    if (!RegisterClassA(&windowClass))
        return;
    RECT rect;
    SetRect(&rect, 0, 0, width, height);
    AdjustWindowRect(&rect, WS_WINDOW, FALSE);
    HWND window = CreateWindowExA(0, className, className, WS_WINDOW, x, y,
        rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, windowClass.hInstance, NULL);
    if (!window)
        return;
    patchGame(gameWindow, &window, 4);
    ShowCursor(TRUE);
    SetFocus(window);
}

// This file's own copy of Hook.cpp's patchCode (the name is lost; renamed to keep the
// annotations apart).
// FUNCTION: 0x1001c970
static bool patchGame(void *address, const void *bytes, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(address, size, PAGE_READWRITE, &protect);
    memcpy(address, bytes, size);
    return ok && VirtualProtect(address, size, protect, &protect);
}

// --- The game's code

// Called instead of a memset the game leaves out: zeroes 0x100 bytes of the caller's
// locals (its ebp - 0x108).
// FUNCTION: 0x1001c9e0
static void clearLocals()
{
    void *locals;
    __asm {
        mov eax, ebp
        mov eax, [eax]
        sub eax, 0x108
        mov locals, eax
    }
    memset(locals, 0, 0x100);
}

// CSound (0x40da6a in Init, 0x40dd53 in CreateBuffer).
// FUNCTION: 0x1001ca10
void fixSounds()
{
    BYTE value = 1;
    patchGame((void *)0x40da6a, &value, 1);
    DWORD flags = 0x8080;
    patchGame((void *)0x40dd53, &flags, 4);
}

// FUNCTION: 0x1001ca50
void fixGame()
{
    hookCall((void *)0x40c72e, 5, (void *)directInputCreate);
    BYTE value = 6;
    patchGame((void *)0x40c7bc, &value, 1);
    value = 0xeb;
    patchGame((void *)0x40c813, &value, 1);
    hook((void *)0x776769, 5, (void *)clearLocals);
    hook((void *)0x759779, 5, (void *)clearLocals);
    hook((void *)0x765669, 5, (void *)clearLocals);
    hook((void *)0x775759, 5, (void *)clearLocals);
    hook((void *)0x770d89, 5, (void *)clearLocals);
    hook((void *)0x75d359, 5, (void *)clearLocals);
    DWORD zero = 0;
    value = 0x74;
    BYTE nops[9];
    memset(nops, 0x90, sizeof(nops));
    patchGame((void *)0x7767bc, &zero, 4);
    patchGame((void *)0x7767c0, &value, 1);
    patchGame((void *)0x7597cc, &zero, 4);
    patchGame((void *)0x7597d0, &value, 1);
    patchGame((void *)0x7656bc, &zero, 4);
    patchGame((void *)0x7656c0, &value, 1);
    patchGame((void *)0x770ddc, &zero, 4);
    patchGame((void *)0x770de0, &value, 1);
    patchGame((void *)0x75d3ac, &zero, 4);
    patchGame((void *)0x75d3b0, &value, 1);
    patchGame((void *)0x40cd6a, &zero, 4);
    patchGame((void *)0x40cd6e, &value, 1);
    patchGame((void *)0x40cde5, &zero, 4);
    patchGame((void *)0x40cde9, &value, 1);
    patchGame((void *)0x40cdac, nops, 9);
    patchGame((void *)0x40ce5f, &zero, 4);
    patchGame((void *)0x40ce63, &value, 1);
    patchGame((void *)0x40ce27, nops, 9);
}

// Unused.
// FUNCTION: 0x1001cca0
void fix64c7fe()
{
    BYTE value = 0x9c;
    patchGame((void *)0x64c7fe, &value, 1);
    value = 0;
    patchGame((void *)0x64c804, &value, 1);
}

// Unused.
// FUNCTION: 0x1001cce0
void fix7586e8()
{
    DWORD value = 0x7ed;
    patchGame((void *)0x7586e8, &value, 4);
    value = 0xd9f3d9e8;
    patchGame((void *)0x758f22, &value, 4);
    BYTE count = 0x18;
    patchGame((void *)0x753631, &count, 1);
}

// FUNCTION: 0x1001cd30
void copyInput()
{
    if (g_inputCode)
        free(g_inputCode);
    g_inputCode = malloc(0x437);
    DWORD protect;
    VirtualProtect(g_inputCode, 0x437, PAGE_EXECUTE_READWRITE, &protect);
    memcpy(g_inputCode, (void *)0x40cd00, 0x437);
    hook((void *)0x40cd1d, 7, (void *)inputHook);
    hook((char *)g_inputCode + 0x1d, 7, (void *)inputHook);
}

// In CInput::GetInput (0x40cd1d) and the copy: its result is at ebp - 0x15, the
// player is its argument.
// FUNCTION: 0x1001cdc0
static void inputHook()
{
    BYTE *result;
    BYTE *player;
    __asm {
        mov ebx, [ebp]
        mov ecx, ebx
        add ebx, 8
        mov player, ebx
        sub ecx, 0x15
        mov result, ecx
    }
    readHat(result, player);
}

// When none of the player's four directions is bound to a joystick but a button is,
// the hat of that button's joystick gives the direction.
// Each joystick's case reads its state itself; the compiler merges the two copies only
// after allocating registers. Until then the device's uses in both make it heavier than
// the loop's binding byte, so the allocator colours it first (esi), before the player's
// pointer (edi), as in the original; with one copy after the if, the pointer gets esi.
// FUNCTION: 0x1001cdf0
static void readHat(BYTE *result, BYTE *player)
{
    BYTE *input = *(BYTE **)(*(BYTE **)(*(BYTE **)0x79011c + 0x1c) + 4);
    IDirectInputDevice2A *device = NULL;
    DIJOYSTATE state;
    memset(&state, 0, sizeof(state));
    short *bindings = (short *)(input + (*player + 0x1c) * 0x10);
    bool bound = false;
    for (int i = 0; i < 4; i++)
        bound |= HIBYTE(bindings[i]);
    if (bound)
        return;
    for (int i = 4; i < 8; i++) {
        BYTE kind = HIBYTE(bindings[i]);
        if (kind == 0)
            continue;
        if (kind == 1) {
            device = *(IDirectInputDevice2A **)(input + 0x1ec);
            if (device) {
                device->Acquire();
                if (device->GetDeviceState(sizeof(state), &state) != DI_OK)
                    return;
                break;
            }
        } else if (kind == 2) {
            device = *(IDirectInputDevice2A **)(input + 0x1f0);
            if (device) {
                device->Acquire();
                if (device->GetDeviceState(sizeof(state), &state) != DI_OK)
                    return;
                break;
            }
        }
    }
    if (device)
        *result = hatDirection(&state);
}

// --- Input

// The joystick's hat as a direction (0-3 right, left, down, up): the first hat that
// isn't centred.
// FUNCTION: 0x1001cec0
static BYTE hatDirection(DIJOYSTATE *state)
{
    for (DWORD pov : state->rgdwPOV) {
        if (LOWORD(pov) != 0xffff) {
            if (pov >= 33750 || pov < 2250)
                return 8;
            if (pov >= 2250 && pov < 6750)
                return 9;
            if (pov >= 6750 && pov < 11250)
                return 1;
            if (pov >= 11250 && pov < 15750)
                return 5;
            if (pov >= 15750 && pov < 20250)
                return 4;
            if (pov >= 20250 && pov < 24750)
                return 6;
            if (pov >= 24750 && pov < 29250)
                return 2;
            if (pov >= 29250 && pov < 33750)
                return 10;
        }
    }
    return 0;
}

// FUNCTION: 0x1001cf40
BYTE efzInput(bool player2)
{
    typedef BYTE (__thiscall *GetInput)(void *input, BYTE player);
    if (!g_inputCode)
        return 0;
    BYTE *scene = *(BYTE **)0x79011c;
    BYTE *game = *(BYTE **)(scene + 0x1c);
    void *input = *(void **)(game + 4);
    return ((GetInput)g_inputCode)(input, player2);
}

// FUNCTION: 0x1001cf60
void fixIkumi()
{
    hook((void *)0x6a5a90, 6, (void *)ikumiHook);
    fixIkumiUpdate();
}

// --- Ikumi, scenes, replays

// In CIkumi's constructor (0x6a5a90): clears its object's 0x3460 (the hook's caller's
// ebp - 0x10 holds the object).
// FUNCTION: 0x1001cf80
static void ikumiHook()
{
    BYTE **object;
    __asm {
        mov ecx, [ebp]
        sub ecx, 0x10
        mov object, ecx
    }
    *(DWORD *)(*object + 0x3460) = 0;
}

// FUNCTION: 0x1001cfa0
static void fixIkumiUpdate()
{
    BYTE value = 0;
    patchGame((void *)0x6a5c5a, &value, 1);
}

// FUNCTION: 0x1001cfc0
void hookTimer()
{
    hook((void *)0x40187f, 7, (void *)timerHook);
}

// FUNCTION: 0x1001cfe0
void hookReplays()
{
    hook((void *)0x405edb, 10, (void *)replayHook);
}

// FUNCTION: 0x1001d000
void fixScene()
{
    BYTE value = 8;
    patchGame((void *)0x778c7b, &value, 1);
}

// The hook on FrameTimerThread's loop (hookTimer).
// FUNCTION: 0x1001d020
static void timerHook()
{
    g_timer.run();
}

// FUNCTION: 0x1001d030
void restartTimer()
{
    g_timer.restart();
}

// In CReplayFile::OpenRead (0x405edb): edx points at the file's handle, followed by
// the frame count it read.
// FUNCTION: 0x1001d040
static void replayHook()
{
    HANDLE file = 0;
    DWORD *count;
    __asm {
        add edx, 4
        mov ecx, [edx]
        mov file, ecx
        add edx, 4
        mov count, edx
    }
    readFrameCount(count, file);
}

// An extended replay (EfzRevival.dll's) ends with its frame count and -1: the count
// replaces what the game read.
// FUNCTION: 0x1001d070
static void readFrameCount(DWORD *count, HANDLE file)
{
    DWORD marker = 0;
    LONG position = SetFilePointer(file, 0, NULL, FILE_CURRENT);
    SetFilePointer(file, -4, NULL, FILE_END);
    DWORD read;
    ReadFile(file, &marker, 4, &read, NULL);
    SetFilePointer(file, position, NULL, FILE_BEGIN);
    if (marker == 0xffffffff) {
        DWORD frames = 0;
        SetFilePointer(file, -8, NULL, FILE_END);
        ReadFile(file, &frames, 4, &read, NULL);
        SetFilePointer(file, position, NULL, FILE_BEGIN);
        *count = frames;
    }
}

// DirectInput 7's DirectInputCreateW for the game's DirectInputCreateEx.
// FUNCTION: 0x1001d100
static HRESULT WINAPI directInputCreate(HINSTANCE instance, DWORD version, REFIID iid,
    LPVOID *object, LPUNKNOWN outer)
{
    typedef HRESULT (WINAPI *Create)(HINSTANCE, DWORD, LPVOID *, LPUNKNOWN);
    Create create = (Create)GetProcAddress(GetModuleHandleW(L"DINPUT.dll"), "DirectInputCreateW");
    if (!create) {
        MessageBoxA(NULL, "Cannot find DirectInputCreate", "Error", MB_OK);
        return -1;
    }
    return create(instance, version, object, outer);
}
