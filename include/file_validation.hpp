#include <queue>
#include <string>
#include <sys/stat.h>

struct Files {
  const char *inputFile, *outputFile;
};

bool validate_file(Files files);

std::string extract_extension(char *file);
