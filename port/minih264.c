/* minih264's H.264 encoder (https://github.com/lieff/minih264, CC0), built once for the
   videos of fights (port/mp4.cpp): baseline profile, one thread, no SVC. */
#define H264E_SVC_API 0
#define H264E_MAX_THREADS 0
#define MINIH264_IMPLEMENTATION
#include "minih264e.h"
