// The launcher's console: text written at a cursor the class keeps itself, under a
// named mutex (several threads print).
#pragma once
#include <windows.h>
#include <sstream>
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

    // Prints anything a wide stream prints. Each instantiation is emitted by the first
    // object that uses it (operator<< <int> by the launcher's main file, 0x414870;
    // <unsigned short> by ProtocolStateClientConnect, 0x4446a0); the instantiations for
    // string literals of every length are one function (0x445300).
    template <class T>
    Console &operator<<(const T &value)
    {
        std::wstringstream stream;
        stream << value;
        print(stream.str());
        return *this;
    }

private:
    HANDLE output_;
    HANDLE mutex_;
    COORD cursor_;
    CONSOLE_SCREEN_BUFFER_INFO info_;
};
