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
