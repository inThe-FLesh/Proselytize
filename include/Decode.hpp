#define __HIP_PLATFORM_AMD__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavutil/common.h>
}

#include "Error_Checking.hpp"

#include <cstdio>
#include <hip/hip_runtime.h>

class Decode {
private:
  AVCodec *codec;
  AVCodecContext *codecContext;

public:
  Decode(AVCodec *codec, AVCodecContext *codecContext);
};
