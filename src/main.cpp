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

#include "main.hpp"
#include <libavcodec/codec.h>
#include <ostream>

int main(int argc, char *argv[]) {
  Files files;
  std::queue<AVPacket *> packetQueue;

  // Checking if the file is valid and then extracting the input and output into
  // the file struct
  files = File_Validation::extract_files(argc, argv);

  // Extracting the AV format context and getting our streams
  AV_Extraction extract(files);
  extract.extractAV();

  AVFormatContext *formatContext = extract.get_format_context();

  Packets packets(formatContext);

  packets.Extract_Packets();

  PacketsList packetsList = packets.get_packets();

  CodecContexts codecContext = extract.get_codec_contexts();

  std::cout << "video codec ID: " << codecContext.videoContext->codec_id
            << std::endl;

  const AVCodec *videoCodec =
      avcodec_find_decoder(codecContext.videoContext->codec_id);

  const AVCodec *audioCodec =
      avcodec_find_decoder(codecContext.audioContext->codec_id);

  CodecList codecs;

  codecs.videoCodec = videoCodec;
  codecs.audioCodec = audioCodec;

  CodecContextList contexts;

  contexts.videoCodecContext = codecContext.videoContext;
  contexts.audioCodecContext = codecContext.audioContext;

  Decode decode(codecs, contexts, packetsList);

  Frames frames = decode.get_frames();

  const AVCodec *encoder = avcodec_find_encoder_by_name("ff_libx265_encoder");

  Encode encode(encoder, contexts.videoCodecContext);

  return 0;
}
