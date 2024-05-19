#define __HIP_PLATFORM_AMD__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavutil/common.h>
}

#include "Error_Checking.hpp"

#include <cstdio>
#include <hip/hip_runtime.h>

class Encode {
private:
  AVCodec *encoder;
  AVCodecContext *outputCodecContext, *inputCodecContext;

  void init_output_context();

public:
  Encode(AVCodec *encoder, AVCodecContext *inputCodecContext);
};
