#include <iostream>
#include <queue>

extern "C" {
#include <libavformat/avformat.h>
}

struct StreamsList {
  AVStream *unknownStream, *videoStream, *audioStream, *dataStream,
      *subtitleStream, *attachmentStream, *NBStream;
};

class Streams {

private:
  unsigned nbStreams;
  StreamsList list;
  AVFormatContext *formatContext;

  void set_unknown(AVStream *stream);

  void set_video(AVStream *stream);

  void set_audio(AVStream *stream);

  void set_data(AVStream *stream);

  void set_subtitle(AVStream *stream);

  void set_attachment(AVStream *stream);

  void set_NB(AVStream *stream);

public:
  StreamsList get_stream_list();

  Streams(AVFormatContext *formatContext, unsigned nbStreams);

  void parse_streams();
};
