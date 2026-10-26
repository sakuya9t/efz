// A stand-in for code of the original that the link dropped (/OPT:REF), kept for what it
// referred to. Observed: the CRT's tolower.obj is loaded right after the objects' own
// references are resolved, after stdafx.obj's signal and before the entry point's, so an
// object linked after stdafx.obj referred to tolower, though nothing in the image calls
// it; the CRT objects loaded after it (_wctype.obj, ...) follow from that. Nothing of
// this object is in the image.
// OBJECT: 0x44a710 0x44a710
#include <ctype.h>

int unusedLower(int c)
{
    return tolower(c);
}
