// The launcher's front end: the console menu (host / join / spectate / local play /
// tournament), reading an address from the console or the clipboard, and starting a
// netplay session or a local game.
#include "Version.h"
#include "Characters.h"
#include "Network.h"
#include "ProtocolContext.h"
#include "Console.h"
#include "GameProcess.h"
// OBJECT: 0x414710 0x41aa50
#include <boost/algorithm/string.hpp>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>

// The instantiations of Console::operator<< for string literals of every length are one
// function, emitted by an earlier object (as in Network.cpp):
// FUNCTION: 0x445300 ??$?6$$BY0P@$$CBD@Console@@QAEAAV0@AAY0P@$$CBD@Z
// FUNCTION: 0x445300 ??$?6$$BY02$$CBD@Console@@QAEAAV0@AAY02$$CBD@Z
// FUNCTION: 0x445300 ??$?6$$BY0KC@$$CBD@Console@@QAEAAV0@AAY0KC@$$CBD@Z
// FUNCTION: 0x445300 ??$?6$$BY0BE@$$CBD@Console@@QAEAAV0@AAY0BE@$$CBD@Z

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
    if (!OpenClipboard(NULL))
        return std::string();
    HANDLE data = GetClipboardData(CF_TEXT);
    if (!data) {
        CloseClipboard();
        return std::string();
    }
    char *text = (char *)GlobalLock(data);
    std::string value(text);
    GlobalUnlock(data);
    CloseClipboard();
    return cleanString(value);
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
void runNetplay(int mode, std::string address)
{
    Network net;
    switch (mode) {
    case 0:
        net.start(0, "");
        break;
    case 1:
        net.start(1, address);
        break;
    case 2:
        net.start(2, address);
        break;
    }
}

// FUNCTION: 0x41a770
int wmain()
{
    char input[128];
    memset(input, 0, 0x80);
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(console, 0x80);
    Console display;
    int minor = 2;
    double version = REVIVAL_VERSION / 100.0;
    int choice;
    do {
        display.clear();
        int major = (int)std::floor(version);
        display << "Efz -Revival- " << major << ".0" << minor << REVIVAL_SUFFIX << "\n\n";
        display << "1: Host\n2: Join\n3: Join from clipboard\n4: Spectate from clipboard\n"
                   "5: Local Play (for practice select VS PLAYER in EFZ proper)\n"
                   "6: Offline Tournament\n\nOther: Quit\n";
        choice = readMenu();
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
    } while (choice != 0);
    return 0;
}
