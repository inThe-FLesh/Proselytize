#include "File_Validation.hpp"

Files File_Validation::extract_files(int argc, char *argv[]) {
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
    exit(EXIT_FAILURE);
  }

  return files;
}

bool File_Validation::validate_file(Files files) {
  struct stat buffer;
  bool inputFileOK = stat(files.inputFile, &buffer) == 0;
  return inputFileOK;
}

std::string File_Validation::extract_extension(char *file) {
  std::string filename(file);
  return filename.substr(filename.find_last_of('.') + 1);
}
