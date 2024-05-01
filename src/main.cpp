#include "main.hpp"

extern "C" {
#include <libavformat/avformat.h>
}

AVFormatContext *AV_read(Files files) {
  AVFormatContext *formatContext = NULL;
  int read_input =
      avformat_open_input(&formatContext, files.inputFile, nullptr, nullptr);

  if (read_input != 0) {
    std::cerr << "Error opening file: " << files.inputFile << std::endl;
  }

  return formatContext;
}

int main(int argc, char *argv[]) {
  Files files;

  try {
    if (argc < 3) {
      throw std::invalid_argument(
          "ERROR: Incorrect number of files. \nWhen using proselytize the "
          "correct "
          "syntax is \"proselytize [input file] [outputFile]\"");
    }

    files.inputFile = argv[1];
    files.outputFile = argv[2];

    bool fileOK = validate_file(files);
    if (!fileOK) {
      //     std::queue<std::string> missingFiles
      throw std::invalid_argument("ERROR: Can't locate one or more files");
    }
  } catch (std::invalid_argument &exception) {
    std::cerr << exception.what() << std::endl;
    return -1;
  }

  AVFormatContext *formatContext = AV_read(files);

  return 0;
}
