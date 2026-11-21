/* minih264's H.264 encoder (https://github.com/lieff/minih264, CC0), built once for the
   videos of fights (port/mp4.cpp): baseline profile, one thread, no SVC. */
#define H264E_SVC_API 0
#define H264E_MAX_THREADS 0
#define MINIH264_IMPLEMENTATION
/* Its branch for Apple's arm64 compilers (the quantizer's zigzag lookup) calls vtbl2q_u8,
   which no arm_neon.h has: the one it means is vqtbl2_u8, a lookup of eight indices in a
   32-byte table of two q registers (what vtbl4_u8 does with four d ones elsewhere). */
#if defined(__APPLE__) && defined(__aarch64__)
#define vtbl2q_u8 vqtbl2_u8
#endif
#include "minih264e.h"
