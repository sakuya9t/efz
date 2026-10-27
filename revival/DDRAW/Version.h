// DDRAW.dll's copy of the launcher's Version.h, from April 2022: the suffix was "h!" (the
// launcher's is "h!!!"). Each object that includes it constructs its own copy (Config.cpp,
// EfzFixes.cpp: static initializers 0x1007e7f0, 0x1007e970).
#pragma once
#include <string>

const int REVIVAL_VERSION = 102;
static const std::wstring REVIVAL_SUFFIX = L"h!";
