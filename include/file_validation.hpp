#include "files.hpp"
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <sys/stat.h>

Files extract_files(int argc, char *argv[]);

bool validate_file(Files files);

std::string extract_extension(char *file);
