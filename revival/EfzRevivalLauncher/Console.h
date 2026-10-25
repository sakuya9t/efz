// The launcher's console: text written at a cursor the class keeps itself, under a
// named mutex (several threads print).
#pragma once
#include <windows.h>
#include <string>

class Console {
public:
    Console();
    ~Console();
    Console &operator=(Console &&other);
    void clear();
    int printChar(wchar_t c);
    int print(std::wstring text);
    void updateCursor();

private:
    HANDLE output_;
    HANDLE mutex_;
    COORD cursor_;
    CONSOLE_SCREEN_BUFFER_INFO info_;
};
