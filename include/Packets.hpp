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
  std::queue<AVPacket *> videoPackets, audioPackets, subtitlePackets;
};

class Packets {
private:
  PacketsList packets;
  AVFormatContext *formatContext;
  std::queue<AVPacket *> packetQueue;

  void set_video_packets(bool *OK, AVPacket *pkt);

  void set_audio_packets(bool *OK, AVPacket *pkt);

  void set_subtitle_packets(bool *OK, AVPacket *pkt);

  void set_packet_queue();

public:
  Packets(AVFormatContext *formatContext);

  PacketsList process_packet_queue();
};
