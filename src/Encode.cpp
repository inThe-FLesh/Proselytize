#include "Encode.hpp"
#include <libavcodec/avcodec.h>
#include <libavcodec/codec.h>
#include <libavformat/avformat.h>

// constructor
Encode::Encode(Frames frames, const AVCodec *encoder,
               const AVCodec *audioEncoder, AVCodecContext *inputCodecContext,
               AVCodecContext *inputAudioContext) {
  this->frames = frames;
  this->encoder = encoder;
  this->audioEncoder = audioEncoder;
  this->inputCodecContext = inputCodecContext;
  init_output_context();
  this->inputAudioContext = inputAudioContext;
  init_audio_context();
}

// PRIVATE
void Encode::init_output_context() {
  outputVideoContext = avcodec_alloc_context3(encoder);

  outputVideoContext->bit_rate = inputCodecContext->bit_rate;
  outputVideoContext->width = inputCodecContext->width;
  outputVideoContext->height = inputCodecContext->height;
  outputVideoContext->time_base = inputCodecContext->time_base;
  outputVideoContext->framerate = inputCodecContext->framerate;
  outputVideoContext->gop_size = inputCodecContext->gop_size;
  outputVideoContext->max_b_frames = inputCodecContext->max_b_frames;
  outputVideoContext->pix_fmt = inputCodecContext->pix_fmt;
  return;
}

void Encode::init_audio_context() {
  outputAudioContext = avcodec_alloc_context3(audioEncoder);

  outputAudioContext->bit_rate = inputAudioContext->bit_rate;
  outputAudioContext->sample_rate = inputAudioContext->sample_rate;
  outputAudioContext->sample_fmt = inputAudioContext->sample_fmt;
  outputAudioContext->time_base = inputAudioContext->time_base;
  return;
}

// PUBLIC

void Encode::start_encode() {
  /*
  AVStream *videoStream =
      avformat_new_stream(AVFormatContext * s, const struct AVCodec *c); */

  while (!frames.videoFrames.empty() && !frames.audioFrames.empty()) {
  }
}

void Encode::encode_video(AVFrame *frame) {
  int res = avcodec_send_frame(outputVideoContext, frame);
  ERROR_CHECK_RES(res, "sending frame in encode_video");
  return;
}

void Encode::encode_audio(AVFrame *frame) {
  int res = avcodec_send_frame(outputAudioContext, frame);
  ERROR_CHECK_RES(res, "sending frame in encode_audio");
  return;
}
