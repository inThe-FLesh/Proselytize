#include "Decode.hpp"
#include <libavcodec/avcodec.h>

Decode::Decode(AVCodec *codec, AVCodecContext *codecContext) {
  this->codec = codec;
  this->codecContext = codecContext;

  int res = avcodec_open2(codecContext, codec, NULL);

  ERROR_CHECK_RES(res, "opening avcodec");
}
