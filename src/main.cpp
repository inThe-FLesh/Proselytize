#include "main.hpp"

extern "C" {
#include <libavformat/avformat.h>
}

int main(int argc, char *argv[]) {
  Files files;
  std::queue<AVPacket *> packetQueue;

  files = File_Validation::extract_files(argc, argv);
  AV_Extraction extract(files);

  extract.extractAV();

  return 0;
}
