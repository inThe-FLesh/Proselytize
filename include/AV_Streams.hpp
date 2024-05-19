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
#include <libavcodec/codec_par.h>
#include <queue>

extern "C" {
#include <libavformat/avformat.h>
}

#ifndef AV_STREAMS
#define AV_STREAMS

struct StreamsList {
  AVStream *unknownStream, *videoStream, *audioStream, *dataStream,
      *subtitleStream, *attachmentStream, *NBStream;

  AVCodecParameters *unknownStream_params, *videoStream_params,
      *audioStream_params, *dataStream_params, *subtitleStream_params,
      *attachmentStream_params, *NBStream_params;
};

class AV_Streams {

private:
  bool areStreamsSet = false;
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

  void set_unknown_params(AVCodecParameters *codec_params);

  void set_video_params(AVCodecParameters *codec_params);

  void set_audio_params(AVCodecParameters *codec_params);

  void set_data_params(AVCodecParameters *codec_params);

  void set_subtitle_params(AVCodecParameters *codec_params);

  void set_attachment_params(AVCodecParameters *codec_params);

  void set_NB_params(AVCodecParameters *codec_params);

  void set_codec_params(int streamID);

public:
  StreamsList get_stream_list();

  void set_streams();

  AV_Streams(AVFormatContext *formatContext, unsigned nbStreams);
};

#endif // AV_STREAMS
