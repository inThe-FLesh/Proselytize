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

  PacketsList packetsList = packets.process_packet_queue();

  return 0;
}
