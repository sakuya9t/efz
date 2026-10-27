// The original links 22 objects compiled with /GL (its Rich header; the debug
// directory's feature record counts one C++ object more than the 21 recovered ones),
// and one of them left nothing in the image: no code, data or static initializers.
// Which file it was is unknown; RingBuffer.h, all template, would compile to nothing, as
// this does, and stands in for it.
#include "stdafx.h"
#include "RingBuffer.h"
