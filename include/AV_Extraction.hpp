#include "file_validation.hpp"
#include "files.hpp"
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
}

class AV_Extraction {

public:
  AV_Extraction(Files files);

  std::queue<AVPacket *> extract();

private:
  Files files;

  AVFormatContext *AV_read();
};
