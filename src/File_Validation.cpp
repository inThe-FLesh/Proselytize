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
