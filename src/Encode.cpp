#include "Encode.hpp"
#include <libavcodec/avcodec.h>

// constructor
Encode::Encode(AVCodec *encoder, AVCodecContext *inputCodecContext) {
  this->encoder = encoder;
  this->inputCodecContext = inputCodecContext;
  init_output_context();
}

// PRIVATE
void Encode::init_output_context() {
  outputCodecContext = avcodec_alloc_context3(encoder);
}

// PUBLIC
