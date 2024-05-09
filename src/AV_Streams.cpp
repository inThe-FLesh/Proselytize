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

StreamsList AV_Streams::get_stream_list() { return list; }

// PUBLIC
AV_Streams::AV_Streams(AVFormatContext *formatContext, unsigned nbStreams) {
  this->formatContext = formatContext;
  this->nbStreams = nbStreams;
}

void AV_Streams::parse_streams() {
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
