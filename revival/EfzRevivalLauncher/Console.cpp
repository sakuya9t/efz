#include "Console.h"
#include <cmath>

// FUNCTION: 0x40ff90
Console::Console()
{
    mutex_ = CreateMutexW(NULL, FALSE, L"Revival_Console");
    output_ = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(output_, &info_);
    cursor_ = info_.dwCursorPosition;
}

// Folded with boost::asio::detail::win_thread::~win_thread (0x422a40).
Console::~Console()
{
    CloseHandle(mutex_);
}

// FUNCTION: 0x40ffd0
Console &Console::operator=(Console &&other)
{
    output_ = other.output_;
    mutex_ = other.mutex_;
    cursor_ = other.cursor_;
    info_ = other.info_;
    other.mutex_ = NULL;
    return *this;
}

// FUNCTION: 0x410030
void Console::clear()
{
    DWORD written;
    WaitForSingleObject(mutex_, INFINITE);
    COORD origin = {0, 0};
    DWORD size = info_.dwSize.X * info_.dwSize.Y;
    FillConsoleOutputCharacterW(output_, L' ', size, origin, &written);
    GetConsoleScreenBufferInfo(output_, &info_);
    FillConsoleOutputAttribute(output_, info_.wAttributes, size, origin, &written);
    SetConsoleCursorPosition(output_, origin);
    GetConsoleScreenBufferInfo(output_, &info_);
    cursor_ = info_.dwCursorPosition;
    ReleaseMutex(mutex_);
}

// FUNCTION: 0x4100e0
int Console::printChar(wchar_t c)
{
    DWORD written;
    COORD step = {0, 0};
    switch (c) {
    case L'\a':
    case L'\v':
        break;
    case L'\n':
    case L'\f':
        step.X = -cursor_.X;
        step.Y = 1;
        break;
    case L'\t':
        WriteConsoleOutputCharacterW(output_, L"    ", 4, cursor_, &written);
        step.X = 4;
        break;
    default:
        step.X = 1;
        WriteConsoleOutputCharacterW(output_, &c, 1, cursor_, &written);
        break;
    }
    cursor_.Y = (SHORT)(std::floor((cursor_.X + step.X) / info_.dwSize.X) + step.Y + cursor_.Y);
    cursor_.X = (cursor_.X + step.X) % info_.dwSize.X;
    SetConsoleCursorPosition(output_, cursor_);
    return true;
}

// FUNCTION: 0x4101e0
int Console::print(std::wstring text)
{
    WaitForSingleObject(mutex_, INFINITE);
    updateCursor();
    for (wchar_t c : text)
        printChar(c);
    ReleaseMutex(mutex_);
    return true;
}

// FUNCTION: 0x410280
void Console::updateCursor()
{
    GetConsoleScreenBufferInfo(output_, &info_);
    cursor_ = info_.dwCursorPosition;
}
