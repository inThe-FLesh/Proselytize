/******************************************************************************
 * Copyright (c) 2024 Ross Gray
 *
 * This file is part of Proselytize.
 *
 * Proselytize is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Proselytize is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Proselytize. If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include <iostream>
#include <queue>

extern "C" {
#include <libavformat/avformat.h>
}

#ifndef AV_STREAMS
#define AV_STREAMS

struct StreamsList {
  AVStream *unknownStream, *videoStream, *audioStream, *dataStream,
      *subtitleStream, *attachmentStream, *NBStream;
};

class AV_Streams {

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

  AV_Streams(AVFormatContext *formatContext, unsigned nbStreams);

  void parse_streams();
};

#endif // AV_STREAMS
