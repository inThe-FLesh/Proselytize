#include "Files.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <sys/stat.h>

#ifndef FILE_VALIDATION_H
#define FILE_VALIDATION_H
class File_Validation {
public:
  static Files extract_files(int argc, char *argv[]);

private:
  static bool validate_file(Files files);

  static std::string extract_extension(char *file);
};
#endif
