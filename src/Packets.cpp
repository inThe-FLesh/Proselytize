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

#include "Packets.hpp"
#include <libavcodec/packet.h>
#include <memory>

// Constructor
Packets::Packets(AVFormatContext *formatContext) {
  this->formatContext = formatContext;
}

// PUBLIC

PacketsList Packets::get_packets() { return packets; }

void Packets::Extract_Packets() {
  int OKSignal = 0;
  AVPacket *pkt = NULL;

  OKSignal = av_read_frame(formatContext, pkt);

  std::cout << "OKSignal: " << OKSignal << std::endl;

  while (OKSignal == 0) {
    OKSignal = av_read_frame(formatContext, pkt);

    switch (pkt->stream_index) {
    case 0:
      packets.videoPackets.push(*pkt);
    case 1:
      packets.audioPackets.push(*pkt);
    case 3:
      packets.subtitlePackets.push(*pkt);
    default:
      trash.push(*pkt);
    }
  }
}
