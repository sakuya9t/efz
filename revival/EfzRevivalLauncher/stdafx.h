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
#pragma once
#include <boost/asio.hpp>
