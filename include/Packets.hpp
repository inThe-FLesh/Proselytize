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
#include <queue>
#include <thread>

extern "C" {
#include <libavcodec/packet.h>
#include <libavformat/avformat.h>
}

struct PacketsList {
  std::queue<AVPacket> videoPackets, audioPackets, subtitlePackets;
};

class Packets {
private:
  PacketsList packets;
  AVFormatContext *formatContext;
  std::queue<AVPacket> trash;

public:
  Packets(AVFormatContext *formatContext);

  PacketsList get_packets();

  // this could be sped up with parallelism
  void Extract_Packets();
};
