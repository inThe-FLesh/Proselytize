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

#include "AV_Extraction.hpp"
#include <libavformat/avformat.h>

// PRIVATE
AV_Extraction::AV_Extraction(Files files) { this->files = files; }

AV_Extraction::~AV_Extraction() { avformat_free_context(formatContext); }

AVFormatContext *AV_Extraction::AV_read() {
  AVFormatContext *formatContext = NULL;
  res = avformat_open_input(&formatContext, files.inputFile, nullptr, nullptr);
  ERROR_CHECK_RES(res, "Opening input file");

  return formatContext;
}

void AV_Extraction::dump_format() {
  av_dump_format(formatContext, 0, files.inputFile, 0);
}

void AV_Extraction::stream_info() {
  res = avformat_find_stream_info(formatContext, nullptr);
  ERROR_CHECK_RES(res, "Finding stream info");
}

void AV_Extraction::set_nbStreams() { nbStreams = formatContext->nb_streams; }

void AV_Extraction::set_streamsList() {
  Streams streams(formatContext, nbStreams);
  streams.parse_streams();
  streamsList = streams.get_stream_list();
}

// PUBLIC
AVFormatContext *AV_Extraction::get_format_context() { return formatContext; }

void AV_Extraction::extractAV() {
  formatContext = AV_read();
  // dump_format();
  stream_info();
  set_nbStreams();
  set_streamsList();
}
