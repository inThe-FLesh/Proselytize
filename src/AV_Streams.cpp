#include "AV_Streams.hpp"
#include <libavutil/avutil.h>

// PRIVATE
void Streams::set_unknown(AVStream *stream) { list.unknownStream = stream; }

void Streams::set_video(AVStream *stream) { list.videoStream = stream; }

void Streams::set_audio(AVStream *stream) { list.audioStream = stream; }

void Streams::set_data(AVStream *stream) { list.dataStream = stream; }

void Streams::set_subtitle(AVStream *stream) { list.subtitleStream = stream; }

void Streams::set_attachment(AVStream *stream) {
  list.attachmentStream = stream;
}

void Streams::set_NB(AVStream *stream) { list.NBStream = stream; }

StreamsList Streams::get_stream_list() { return list; }

// PUBLIC
Streams::Streams(AVFormatContext *formatContext, unsigned nbStreams) {
  this->formatContext = formatContext;
  this->nbStreams = nbStreams;
}

void Streams::parse_streams() {
  std::queue<AVStream> streamQueue;
  for (unsigned i = 0; i < nbStreams; i++) {
    AVStream *stream = formatContext->streams[i];
    int mediaType = stream->codecpar->codec_type;

    switch (mediaType) {
    case -1:
      set_unknown(stream);
    case 0:
      set_video(stream);
    case 1:
      set_audio(stream);
    case 2:
      set_data(stream);
    case 3:
      set_subtitle(stream);
    case 4:
      set_attachment(stream);
    case 5:
      set_NB(stream);
    }
  }
}
