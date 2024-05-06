#include "AV_Extraction.hpp"
#include <libavcodec/packet.h>
#include <libavformat/avformat.h>
#include <queue>

AV_Extraction::AV_Extraction(Files files) { this->files = files; }

std::queue<AVPacket *> AV_Extraction::extract() {

  AVFormatContext *formatContext = AV_read();

  std::queue<AVPacket *> packetQueue;

  int done = 0;

  while (done == 0) {
    AVPacket *packet = new AVPacket();
    done = av_read_frame(formatContext, packet);

    if (done < 0)
      break;

    packetQueue.push(packet);
  }

  return packetQueue;
}

AVFormatContext *AV_Extraction::AV_read() {
  AVFormatContext *formatContext = NULL;
  int read_input =
      avformat_open_input(&formatContext, files.inputFile, nullptr, nullptr);

  if (read_input != 0) {
    std::cerr << "Error opening file: " << files.inputFile << std::endl;
  }

  return formatContext;
}
