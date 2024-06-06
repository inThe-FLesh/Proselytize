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
#include <libavcodec/avcodec.h>

// Constructor and Destructor
AV_Extraction::AV_Extraction(Files files) { this->files = files; }

AV_Extraction::~AV_Extraction() {
  // void function error check res not needed
  avformat_free_context(formatContext);
}

// PRIVATE
AVFormatContext *AV_Extraction::AV_read() {
  AVFormatContext *formatContext = NULL;
  res = avformat_open_input(&formatContext, files.inputFile, nullptr, nullptr);
  ERROR_CHECK_RES(res, "Opening input file");

  return formatContext;
}

void AV_Extraction::dump_format() {
  // void function error check res not needed
  av_dump_format(formatContext, 0, files.inputFile, 0);
}

void AV_Extraction::stream_info() {
  res = avformat_find_stream_info(formatContext, nullptr);
  ERROR_CHECK_RES(res, "Finding stream info");
}

void AV_Extraction::set_nbStreams() { nbStreams = formatContext->nb_streams; }

void AV_Extraction::set_streamsList() {
  AV_Streams streams(formatContext, nbStreams);
  streams.set_streams();
  streamsList = streams.get_stream_list();
}

void AV_Extraction::set_codec_ids() {
  codecs.videoCodec = streamsList.videoStream_params->codec_id;
  codecs.audioCodec = streamsList.audioStream_params->codec_id;
}

void AV_Extraction::set_video_codec_context() {
  decoders.videoDecoder = avcodec_find_decoder(codecs.videoCodec);
  std::cout << "video codec ID: " << codecs.videoCodec << std::endl;
  ERROR_CHECK_BOOL(decoders.videoDecoder != NULL, "finding video decoder");

  codecContexts.videoContext = avcodec_alloc_context3(decoders.videoDecoder);
  ERROR_CHECK_BOOL(codecContexts.videoContext != NULL,
                   "allocating video context");

  int res = avcodec_parameters_to_context(codecContexts.videoContext,
                                          streamsList.videoStream_params);

  ERROR_CHECK_RES(res,
                  "avcodec_parameters_to_context in set_video_codec_context");
}

void AV_Extraction::set_audio_codec_context() {
  decoders.audioDecoder = avcodec_find_decoder(codecs.audioCodec);
  ERROR_CHECK_BOOL(decoders.audioDecoder, "finding audio decoder");

  codecContexts.audioContext = avcodec_alloc_context3(decoders.audioDecoder);
  ERROR_CHECK_BOOL(codecContexts.audioContext, "allocating audio context");

  int res = avcodec_parameters_to_context(codecContexts.audioContext,
                                          streamsList.audioStream_params);

  ERROR_CHECK_RES(res,
                  "avcodec_parameters_to_context in set_audio_codec_context");
}

// PUBLIC
AVFormatContext *AV_Extraction::get_format_context() { return formatContext; }

CodecContexts AV_Extraction::get_codec_contexts() { return codecContexts; }

Decoders AV_Extraction::get_decoders() { return decoders; }

void AV_Extraction::extractAV() {
  formatContext = AV_read();
  dump_format();
  stream_info();
  set_nbStreams();
  set_streamsList();
  set_video_codec_context();
  set_audio_codec_context();
}
