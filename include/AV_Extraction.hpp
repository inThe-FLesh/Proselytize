#include "Error_Checking.hpp"
#include "Files.hpp"
#include <cstdlib>
#include <libavcodec/packet.h>
#include <vector>

extern "C" {
#include <libavformat/avformat.h>
}

class AV_Extraction {

private:
  int res;
  Files files;
  unsigned nbStreams;
  std::vector<AVStream *> streams;
  AVFormatContext *formatContext;

  AVFormatContext *AV_read();

  void dump_format();

  void stream_info();

  void set_nbStreams();

  void set_streams();

public:
  AV_Extraction(Files files);

  ~AV_Extraction();

  AVFormatContext *get_format_context();

  void extractAV();
};
