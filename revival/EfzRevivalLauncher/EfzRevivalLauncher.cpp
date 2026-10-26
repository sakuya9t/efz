// The launcher's front end: the console menu (host / join / spectate / local play /
// tournament), reading an address from the console or the clipboard, and starting a
// netplay session or a local game.
#include "Network.h"
#include "Console.h"
#include "GameProcess.h"
#include "Version.h"
// OBJECT: 0x414710 0x41aa50
#include <boost/algorithm/string.hpp>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>

// Strips carriage returns, newlines and spaces from a pasted or typed address.
// FUNCTION: 0x418720
std::string cleanString(std::string input)
{
    std::string result = input;
    boost::algorithm::replace_all(result, "\r", "");
    boost::algorithm::replace_all(result, "\n", "");
    boost::algorithm::replace_all(result, " ", "");
    return result;
}

// The clipboard text, cleaned; empty when there is none.
// FUNCTION: 0x4192e0
std::string getClipboard()
{
    // TODO: differs: the compiler lays the empty-string return out after the
    // GlobalLock path, so a few branch displacements and the block order differ from
    // the original; the instructions are otherwise the same.
    if (OpenClipboard(NULL)) {
        HANDLE data = GetClipboardData(CF_TEXT);
        if (data) {
            char *text = (char *)GlobalLock(data);
            std::string value(text);
            GlobalUnlock(data);
            CloseClipboard();
            return cleanString(value);
        }
        CloseClipboard();
    }
    return std::string();
}

// Starts efz.exe locally and injects EfzRevival.dll with the mode (2 practice, 3
// tournament) and version, then lets the game run.
// FUNCTION: 0x419430
void injectGame(int mode)
{
    GameProcess game;
    int args[2];
    args[0] = mode;
    args[1] = REVIVAL_VERSION;
    game.inject("efz.exe", "EfzRevival.dll", args, 8);
    PROCESS_INFORMATION info = game.getProcessInfo();
    ResumeThread(info.hThread);
    CloseHandle(info.hThread);
}

// Reads a line from the console with echo and returns it as a number (the menu choice).
// FUNCTION: 0x419af0
int readMenu()
{
    char buffer[512];
    DWORD read;
    DWORD mode;
    memset(buffer, 0, sizeof(buffer));
    read = 0;
    mode = 0;
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(input, &mode);
    SetConsoleMode(input, 0x81);
    FlushConsoleInputBuffer(input);
    ReadConsoleA(input, buffer, 0x1ff, &read, NULL);
    SetConsoleMode(input, mode);
    return atoi(buffer);
}

// Runs a netplay session: mode 0 hosts, 1 joins address, 2 spectates address.
// FUNCTION: 0x419c10
// TODO: differs: the host case's empty std::string gets a different stack slot than the
// original (net at ebp-0x4b8, string at ebp-0x4d0), so the [ebp-...] displacements
// differ; the instruction sequence matches.
void runNetplay(int mode, std::string address)
{
    Network net;
    switch (mode) {
    case 0: {
        std::string empty("");
        net.start(0, empty);
        break;
    }
    case 1:
        net.start(1, address);
        break;
    case 2:
        net.start(2, address);
        break;
    }
}

// FUNCTION: 0x41a770
// TODO: differs: the console handle and the menu choice land in the opposite callee-
// saved registers (the original keeps the handle in edi and the choice in esi), and the
// Console and the two std::strings get different stack slots. The control flow, calls,
// strings and the version arithmetic all match; only register/slot allocation differs.
int wmain()
{
    char input[128];
    memset(input, 0, 0x80);
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(console, 0x80);
    Console display;
    int minor = 2;
    double version = REVIVAL_VERSION / 100.0;
    while (true) {
        display.clear();
        int major = (int)std::floor(version);
        display << "Efz -Revival- " << major << ".0" << minor << REVIVAL_SUFFIX << "\n\n";
        display << "1: Host\n2: Join\n3: Join from clipboard\n4: Spectate from clipboard\n"
                   "5: Local Play (for practice select VS PLAYER in EFZ proper)\n"
                   "6: Offline Tournament\n\nOther: Quit\n";
        int choice = readMenu();
        std::string address;
        std::string unused;
        switch (choice) {
        case 1:
            runNetplay(0, std::string());
            break;
        case 2: {
            display << "Input host ip:port ";
            SetConsoleMode(console, 0x87);
            DWORD read;
            ReadConsoleA(console, input, 0x80, &read, NULL);
            address = cleanString(std::string(input));
            runNetplay(1, std::string(address));
            break;
        }
        case 3:
            runNetplay(1, getClipboard());
            break;
        case 4:
            runNetplay(2, getClipboard());
            break;
        case 5:
            injectGame(2);
            choice = 0;
            break;
        case 6:
            injectGame(3);
            choice = 0;
            break;
        default:
            choice = 0;
            break;
        }
        if (choice == 0)
            return 0;
    }
}
