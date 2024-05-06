#include "main.hpp"
#include <libavcodec/packet.h>
#include <ostream>

extern "C" {
#include <libavformat/avformat.h>
}

int main(int argc, char *argv[]) {
  Files files = extract_files(argc, argv);

  AV_Extraction extract(files);

  std::queue<AVPacket *> packetQueue = extract.extract();

  while (!packetQueue.empty()) {
    std::cout << packetQueue.front()->duration << std::endl;
    packetQueue.pop();
  }

  return 0;
}
