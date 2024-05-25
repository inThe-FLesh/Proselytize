#include <queue>
#define __HIP_PLATFORM_AMD__

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/packet.h>
#include <libavutil/common.h>
#include <libavutil/frame.h>
}

#include "Error_Checking.hpp"
#include "Packets.hpp"

#include <cstdio>
#include <hip/hip_runtime.h>

#ifndef DECODE
#define DECODE
struct Frames {
  std::queue<AVFrame *> videoFrames, audioFrames;
};

struct CodecList {
  const AVCodec *videoCodec, *audioCodec;
};

struct CodecContextList {
  AVCodecContext *videoCodecContext, *audioCodecContext;
};

class Decode {
private:
  bool populated = false;
  Frames frames;
  PacketsList packets;
  const AVCodec *videoCodec, *audioCodec;
  AVCodecContext *videoCodecContext, *audioCodecContext;

public:
  Decode(CodecList codecs, CodecContextList contexts, PacketsList packets);

  Frames get_frames();

private:
  void populate_video_frame_queue();

  void populate_audio_frame_queue();
};
#endif // !DECODE
