// An object between Hook.cpp's and Music.cpp's with no code of its own: the original's
// static initializers have one there with std::ignore and boost.bind's _1-_9 (Log.h's)
// and nothing else, not even the version suffix every object that includes EfzGame.h
// has. Its name and whatever it held are guesses; anything it defined is unreferenced
// and so not in the image.
#include "stdafx.h"
#include "Log.h"
