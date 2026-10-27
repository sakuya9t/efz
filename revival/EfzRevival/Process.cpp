// An object between PracticeSession.cpp's and Recorder.cpp's with no code of its own:
// the original's static initializers have one there with std::ignore and boost.bind's
// _1-_9 (Log.h's) and nothing else. DDRAW.dll links a Process.cpp (process helpers
// nothing calls) that would sort there; with link-time code generation and /OPT:REF
// none of an unreferenced object's functions stay. Its name and contents are guesses.
#include "stdafx.h"
#include "Log.h"
