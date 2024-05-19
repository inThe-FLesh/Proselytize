#define __HIP_PLATFORM_AMD__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavutil/common.h>
}

#include <cstdio>
#include <hip/hip_runtime.h>

__global__ void decode();

void decode_pkt();
