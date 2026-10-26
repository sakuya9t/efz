// logDdraw.txt: opened when EfzRevival.ini's Debug is set (EfzFixes.cpp), written by the
// renderer and the DirectDraw classes. Every message is flushed at once.
#pragma once
#include <fstream>

// GLOBAL: 0x100b6b08 (EfzFixes.cpp)
extern std::fstream g_log;

#define LOG(message) do { g_log << message; g_log.flush(); } while (0)
