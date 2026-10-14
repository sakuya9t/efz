#include <stdlib.h>
#include <time.h>
#include "efz.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI FrameTimerThread(LPVOID param);

// GLOBAL: 0x78f040
// Milliseconds the frame timer sleeps per frame; raised by 1 each second the game ran
// faster than 64 frames.
BYTE g_frameWait = 10;
// GLOBAL: 0x790100
DWORD g_startTime;
// GLOBAL: 0x790104
CPlayer* g_player1;
// GLOBAL: 0x790108
CPlayer* g_player2;
// GLOBAL: 0x79010c
CGame* g_game;
// GLOBAL: 0x790110
CScene* g_scenes[9];
// GLOBAL: 0x790134
// wParam of the last WM_ACTIVATEAPP: nonzero while the game window is active.
WPARAM g_appActive;
// GLOBAL: 0x790138
DWORD g_timerThreadId;
// GLOBAL: 0x79013c
// Never signalled after startup; the timer thread waits on it as an interruptible sleep.
HANDLE g_sleepEvent;
// GLOBAL: 0x790140
// Signalled by the timer thread once per frame; the main loop waits on it.
HANDLE g_frameEvent;
// GLOBAL: 0x790144
HANDLE g_timerThread;
// GLOBAL: 0x790148
BYTE g_scene;
// GLOBAL: 0x79014c
// Set once the scenes exist; WndProc only touches scenes while it is set.
int g_scenesReady;
// GLOBAL: 0x790150
CGraphics g_graphics;
// GLOBAL: 0x7b0968
CInput g_input;
// GLOBAL: 0x7b0b60
CSound g_sound;

// FUNCTION: 0x401000
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    WNDCLASS wc;
    HWND hwnd;

    memset(&wc, 0, sizeof(wc));
    wc.hInstance = hInstance;
    wc.lpszClassName = "ETENAL FIGHTER ZERO";
    wc.lpfnWndProc = WndProc;
    wc.style = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "ETENAL FIGHTER ZERO";
    if (!RegisterClass(&wc))
        return 0;

    hwnd = CreateWindowEx(0, "ETENAL FIGHTER ZERO", "ETENAL FIGHTER ZERO", WS_POPUP, 0, 0,
                          GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
                          NULL, NULL, hInstance, NULL);
    if (!hwnd)
        return 0;
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    srand(time(NULL));
    timeBeginPeriod(1);
    g_startTime = timeGetTime();
    g_sleepEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    g_frameEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    SetEvent(g_sleepEvent);
    SetEvent(g_frameEvent);
    g_timerThread = CreateThread(NULL, 0, FrameTimerThread, NULL, 0, &g_timerThreadId);
    SetThreadPriority(g_timerThread, THREAD_PRIORITY_TIME_CRITICAL);
    ShowCursor(FALSE);

    g_graphics.Init(hwnd, ReadConfigByte(0x20));
    g_input.Init(hwnd);
    g_sound.Init(hwnd);
    if (ReadConfigByte(0x9c) > 0)
        g_input.Unk40d460(ReadConfigByte(0x9c));
    else
        g_input.Unk40d140();

    g_game = new CGame(&g_graphics, &g_input, &g_sound);
    g_game->Unk406780();
    g_game->Unk406e60();
    g_game->Unk406aa0();

    g_player1 = 0;
    g_player2 = 0;
    g_scenes[0] = new CScene0(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
    g_scenes[1] = new CScene1(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
    g_scenes[2] = new CScene2(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
    g_scenes[3] = new CScene3(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
    g_scenes[4] = NULL;
    g_scenes[5] = new CScene5(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
    if (1) {
        g_scenes[6] = new CScene6(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
        g_scenes[7] = new CScene7(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
        g_scenes[8] = new CScene8(hwnd, &g_player1, &g_player2, g_game, &g_graphics, &g_input, &g_sound);
    } else {
        g_scenes[6] = NULL;
        g_scenes[7] = NULL;
        g_scenes[8] = NULL;
    }
    g_scenesReady = 1;

    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
            if (!GetMessage(&msg, NULL, 0, 0))
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            g_game->unk1368 = !g_game->unk1368;
            if (g_scenes[g_scene] != NULL) {
                g_sound.Unk40e4d0(g_game->unkf26);
                g_scene = g_scenes[g_scene]->Update();
            }
            WaitForSingleObject(g_frameEvent, INFINITE);
        }
    }
    return msg.wParam;
}

// FUNCTION: 0x401670
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int i;

    if (g_scenesReady && g_scenes[g_scene] != NULL)
        g_scenes[g_scene]->lastMessage = msg;

    switch (msg) {
    case WM_ACTIVATEAPP:
        g_appActive = wParam;
        break;
    case WM_DESTROY:
        g_scenesReady = 0;
        for (i = 0; i < 9; i++) {
            if (g_scenes[i] != NULL) {
                delete g_scenes[i];
                g_scenes[i] = NULL;
            }
        }
        delete g_game;
        g_game = NULL;
        if (g_player1 != NULL)
            delete g_player1;
        if (g_player2 != NULL)
            delete g_player2;
        g_sound.Shutdown();
        g_input.Shutdown();
        g_graphics.Shutdown();
        TerminateThread(g_timerThread, 0);
        CloseHandle(g_frameEvent);
        CloseHandle(g_sleepEvent);
        CloseHandle(g_timerThread);
        timeEndPeriod(1);
        PostQuitMessage(1000);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// FUNCTION: 0x401850
// Paces the game: signals g_frameEvent every g_frameWait ms, and slows down by 1 ms
// whenever more than 64 frames ran in a second.
DWORD WINAPI FrameTimerThread(LPVOID param)
{
    int frames = 0;
    int unused1 = 0;
    int unused2 = 0;

    g_startTime = timeGetTime();
    while (1) {
        WaitForSingleObject(g_sleepEvent, g_frameWait);
        SetEvent(g_frameEvent);
        frames++;
        if (timeGetTime() - g_startTime >= 1000) {
            if (frames > 64)
                g_frameWait++;
            frames = 0;
            g_startTime = timeGetTime();
        }
    }
    return 0;
}

// Compiler-generated scalar deleting destructors, emitted in this object by the
// `delete` expressions in WndProc.
// FUNCTION: 0x4018f0 ??_GCGame@@QAEPAXI@Z
// FUNCTION: 0x401920 ??_GCPlayer@@QAEPAXI@Z

// Dynamic initializers ($E1, $E4, $E7) and the atexit destructors they register ($E2,
// $E5, $E8) for the three subsystem globals. The compiler puts them in .text$yc and
// .text$yd, which the linker sorts to the end of .text.
// FUNCTION: 0x786420 _$E1
// FUNCTION: 0x786440 _$E4
// FUNCTION: 0x786460 _$E7
// FUNCTION: 0x786480 _$E2
// FUNCTION: 0x786490 _$E5
// FUNCTION: 0x7864a0 _$E8
