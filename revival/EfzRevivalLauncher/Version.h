// The launcher's version: 102 is 1.02, also the version it gives EfzRevival.dll and
// sends in MessageInit; the suffix is printed after it ("1.02h!!!"). Every object that
// includes this header constructs its own copy of the suffix (static initializers
// 0x495290, 0x4953a0, ...).
#pragma once
#include <string>

const int REVIVAL_VERSION = 102;
static const std::wstring REVIVAL_SUFFIX = L"h!!!";
