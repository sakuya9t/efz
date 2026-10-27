// The Visual Studio DLL template's precompiled header, with the standard library's
// strings and the log's file stream (Log.h). Every source but dllmain.cpp is compiled
// with it precompiled (/Yu): the inline functions it defines and the template code it
// instantiates are compiled after each object's own functions and templates, as each
// object first needs them, while those of the headers after it come in the order of
// their definitions. Compiling it (/Yc, stdafx.obj) emits the code it needs itself: the
// system error category, which comes after DDRAW.obj's code.
#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include "Log.h"
