#define __HIP_PLATFORM_AMD__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavformat/avformat.h>
#include <libavutil/common.h>
}

#include "Error_Checking.hpp"

#include <cstdio>
#include <hip/hip_runtime.h>
#include <queue>

#ifndef ENCODE
#define ENCODE
struct Frames {
  std::queue<AVFrame *> videoFrames, audioFrames;
};

class Encode {
private:
  Frames frames;
  const AVCodec *encoder, *audioEncoder;
  AVCodecContext *outputVideoContext, *inputCodecContext, *outputAudioContext,
      *inputAudioContext;

  void init_output_context();

  void init_audio_context();

public:
  Encode(Frames frames, const AVCodec *encoder, const AVCodec *audioEncoder,
         AVCodecContext *inputCodecContext, AVCodecContext *inputAudioContext);

  void start_encode();

  void encode_video(AVFrame *frame);

  void encode_audio(AVFrame *frame);
};
#endif // ENCODE
