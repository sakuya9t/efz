// The launcher's precompiled header. Every source of the project is compiled with it
// (/Yu, forced in with /FI, so EfzPackets.pb.cc and the shared Config.cpp needn't name
// it), and stdafx.cpp makes it (/Yc).
//
// Observed: of the header statics a precompiled header defines, the objects compiled
// with it emit only those their code uses, and stdafx.obj (linked after the other
// objects) emits all of them. Only stdafx.obj has boost.asio's error-category
// references, winsock_init and placeholders (static initializers 0x495c40-0x495cc0);
// Network.obj has the two placeholders its receive handler binds. The headers that the
// objects themselves include (boost/bind.hpp's _1-_9, Version.h) give every object its
// own copies.
//
// stdio.h and tchar.h, the lines Visual Studio's console template starts with, come
// after asio: the compiler keeps a scope's names in a table keyed by where they lie in its
// memory, so what the header holds decides the order in which EfzPackets.pb.obj lays out
// the messages' default_instance_ (the original's starts at MessagePalette, as with these
// two; asio alone starts at MessageRedirect). Before asio they would change the order in
// which every object refers to the CRT (memmove.obj and others would be loaded early).
#pragma once
#include <boost/asio.hpp>
#include <stdio.h>
#include <tchar.h>
