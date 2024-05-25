#include "Decode.hpp"

Decode::Decode(CodecList codecs, CodecContextList contexts,
               PacketsList packets) {
  videoCodec = codecs.videoCodec;
  audioCodec = codecs.audioCodec;
  videoCodecContext = contexts.videoCodecContext;
  audioCodecContext = contexts.audioCodecContext;
  this->packets = packets;
}

Frames Decode::get_frames() {
  populate_video_frame_queue();
  populate_audio_frame_queue();

  return frames;
}

// Private
void Decode::populate_video_frame_queue() {
  int res = -1;
  AVFrame *frame = av_frame_alloc();
  std::queue<AVPacket> videoPackets = packets.videoPackets;

  res = avcodec_open2(videoCodecContext, videoCodec, NULL);

  ERROR_CHECK_RES(res, "opening video codec in populate_video_frame_queue");

  while (!videoPackets.empty()) {
    res = avcodec_send_packet(videoCodecContext, &videoPackets.front());
    videoPackets.pop();

    ERROR_CHECK_RES(res, "sending packet in populate_video_frame_queue");

    res = avcodec_receive_frame(videoCodecContext, frame);

    if (res == 0) {
      frames.videoFrames.push(frame);
    } else if (res == AVERROR(EAGAIN) || res == AVERROR_EOF) {
      break;
    } else {
      ERROR_CHECK_RES(res, "receiving frames in populate_video_frame_queue");
    }

    av_frame_unref(frame);
  }
}

void Decode::populate_audio_frame_queue() {
  int res = -1;
  AVFrame *frame = av_frame_alloc();
  std::queue<AVPacket> audioPackets = packets.audioPackets;

  res = avcodec_open2(audioCodecContext, audioCodec, NULL);

  while (!audioPackets.empty()) {
    res = avcodec_send_packet(audioCodecContext, &audioPackets.front());
    audioPackets.pop();

    ERROR_CHECK_RES(res, "sending packet in populate_audio_frame_queue");

    res = avcodec_receive_frame(audioCodecContext, frame);

    if (res == 0) {
      frames.audioFrames.push(frame);
    } else if (res == AVERROR(EAGAIN) || res == AVERROR_EOF) {
      break;
    } else {
      ERROR_CHECK_RES(res, "receiving frames in populate_video_frame_queue");
    }

    av_frame_unref(frame);
  }
}
