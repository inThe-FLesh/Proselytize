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

#include "AV_Streams.hpp"
#include <libavcodec/codec_par.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>

// PRIVATE

// These setters are here to assign the streams to the stream list depending on
// the type of stream that they are Each corresponds to a type that an AV stream
// can have.
void AV_Streams::set_unknown(AVStream *stream) { list.unknownStream = stream; }

void AV_Streams::set_video(AVStream *stream) { list.videoStream = stream; }

void AV_Streams::set_audio(AVStream *stream) { list.audioStream = stream; }

void AV_Streams::set_data(AVStream *stream) { list.dataStream = stream; }

void AV_Streams::set_subtitle(AVStream *stream) {
  list.subtitleStream = stream;
}

void AV_Streams::set_attachment(AVStream *stream) {
  list.attachmentStream = stream;
}

void AV_Streams::set_NB(AVStream *stream) { list.NBStream = stream; }

void AV_Streams::set_unknown_params(AVCodecParameters *codec_params) {
  list.unknownStream_params = codec_params;
}

void AV_Streams::set_video_params(AVCodecParameters *codec_params) {
  list.videoStream_params = codec_params;
}

void AV_Streams::set_audio_params(AVCodecParameters *codec_params) {
  list.audioStream_params = codec_params;
}

void AV_Streams::set_data_params(AVCodecParameters *codec_params) {
  list.dataStream_params = codec_params;
}

void AV_Streams::set_subtitle_params(AVCodecParameters *codec_params) {
  list.subtitleStream_params = codec_params;
}

void AV_Streams::set_attachment_params(AVCodecParameters *codec_params) {
  list.attachmentStream_params = codec_params;
}

void AV_Streams::set_NB_params(AVCodecParameters *codec_params) {
  list.NBStream_params = codec_params;
}

void AV_Streams::set_codec_params(int streamID) {
  if (areStreamsSet) {
    switch (streamID) {
    case -1:
      set_unknown_params(list.unknownStream->codecpar);
    case 0:
      set_video_params(list.videoStream->codecpar);
    case 1:
      set_audio_params(list.audioStream->codecpar);
    case 2:
      set_data_params(list.dataStream->codecpar);
    case 3:
      set_subtitle_params(list.subtitleStream->codecpar);
    case 4:
      set_attachment_params(list.attachmentStream->codecpar);
    case 5:
      set_NB_params(list.NBStream->codecpar);
    }
  } else {
    std::cerr
        << "Cannot call \'set_codec_params\' until \'set_streams\' is called"
        << std::endl;
  }
}

// PUBLIC
AV_Streams::AV_Streams(AVFormatContext *formatContext, unsigned nbStreams) {
  this->formatContext = formatContext;
  this->nbStreams = nbStreams;
}

void AV_Streams::set_streams() {
  std::queue<AVStream> streamQueue;
  areStreamsSet = true;

  for (unsigned i = 0; i < nbStreams; i++) {
    AVStream *stream = formatContext->streams[i];
    int mediaType = stream->codecpar->codec_type;

    switch (mediaType) {
    case -1:
      set_unknown(stream);
      set_codec_params(mediaType);
    case 0:
      set_video(stream);
      set_codec_params(mediaType);
    case 1:
      set_audio(stream);
      set_codec_params(mediaType);
    case 2:
      set_data(stream);
      set_codec_params(mediaType);
    case 3:
      set_subtitle(stream);
      set_codec_params(mediaType);
    case 4:
      set_attachment(stream);
      set_codec_params(mediaType);
    case 5:
      set_NB(stream);
      set_codec_params(mediaType);
    }
  }
}

StreamsList AV_Streams::get_stream_list() { return list; }
