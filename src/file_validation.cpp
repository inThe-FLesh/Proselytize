#include "file_validation.hpp"

bool validate_file(Files files) {
  struct stat buffer;
  bool inputFileOK = stat(files.inputFile, &buffer) == 0;
  return inputFileOK;
}

std::string extract_extension(char *file) {
  std::string filename(file);
  return filename.substr(filename.find_last_of('.') + 1);
}
