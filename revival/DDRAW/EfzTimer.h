// The game's frame timer, which getEfzTimer exports: DDRAW.dll replaces the loop of
// efz.exe's FrameTimerThread (0x401850) with run(), which paces the frames at fps
// instead of the game's fixed sleep, carrying the rounding error over. EfzRevival.dll
// changes fps for the practice mode's game speed and the spectator's catch-up.
// 0x34 bytes; one, g_timer (EfzFixes.cpp).
#pragma once
#include <windows.h>
#include <mmsystem.h>

struct EfzTimer {
    // FUNCTION: 0x1001c2c0
    EfzTimer()
    {
        defaultFps = 63.9;
        defaultMsPerFrame = 1000.0 / defaultFps;
        sleepEvent = (HANDLE *)0x79013c;
        frameEvent = (HANDLE *)0x790140;
        startTime = (DWORD *)0x790100;
        timeBeginPeriod(1);
        setFps(defaultFps);
    }

    // FUNCTION: 0x1001c320
    ~EfzTimer()
    {
    }

    // FUNCTION: 0x1001c330
    void setFps(double value)
    {
        if (value <= 0.0)
            return;
        if (value > 0.0) {
            if (fps != value)
                error = 0;
            fps = value;
        }
        msPerFrame = 1000.0 / fps;
    }

    void reset()
    {
        setFps(defaultFps);
    }

    double getMsPerFrame()
    {
        return msPerFrame;
    }

    // FUNCTION: 0x1001c380
    void setMsPerFrame(double value)
    {
        if (value > 0.0) {
            if (msPerFrame != value)
                error = 0;
            msPerFrame = value;
        }
    }

    // EfzFixes.cpp, after run(), where its code is.
    void restart();

    // The thread's loop: never returns.
    void run();

    double defaultFps;          // 0x00 63.9, the game's rate
    double defaultMsPerFrame;   // 0x08
    double fps;                 // 0x10
    double error;               // 0x18 milliseconds the frames ran late (+) or early (-)
    double msPerFrame;          // 0x20
    HANDLE *sleepEvent;         // 0x28 efz.exe's g_sleepEvent, never signalled
    HANDLE *frameEvent;         // 0x2c g_frameEvent, which the main loop waits for
    DWORD *startTime;           // 0x30 g_startTime: when the frame began
};

// GLOBAL: 0x100b6ad0 (EfzFixes.cpp)
extern EfzTimer g_timer;
