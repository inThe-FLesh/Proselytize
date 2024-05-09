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
#include "Error_Checking.hpp"
#include "Files.hpp"
#include <cstdlib>
#include <libavcodec/packet.h>
#include <vector>

extern "C" {
#include <libavformat/avformat.h>
}

class AV_Extraction {

private:
  int res;
  Files files;
  unsigned nbStreams;
  StreamsList streamsList;
  AVFormatContext *formatContext;

  AVFormatContext *AV_read();

  void dump_format();

  void stream_info();

  void set_nbStreams();

  void set_streamsList();

public:
  AV_Extraction(Files files);

  ~AV_Extraction();

  AVFormatContext *get_format_context();

  void extractAV();
};
