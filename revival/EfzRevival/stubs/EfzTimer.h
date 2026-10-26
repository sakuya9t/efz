// STUB
// DDRAW.dll's frame timer (getEfzTimer): the game runs at fps frames a second; reset
// goes back to the default. Its functions are inline (COMDATs 0x10028c80, 0x10028cf0,
// emitted by the practice session's object, the first to use them).
#pragma once
#include <windows.h>

struct EfzTimer {
    // FUNCTION: 0x10028c80
    void setFps(double value)
    {
        if (value <= 0.0)
            return;
        if (value > 0.0) {
            if (fps != value)
                frames = 0;
            fps = value;
        }
        msPerFrame = 1000.0 / fps;
    }

    // FUNCTION: 0x10028cf0
    void reset()
    {
        setFps(defaultFps);
    }

    double defaultFps;      // 0x00
    double unknown8;        // 0x08
    double fps;             // 0x10
    __int64 frames;         // 0x18
    double msPerFrame;      // 0x20
};
