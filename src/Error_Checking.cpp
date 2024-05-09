#include "Error_Checking.hpp"
#include <cstdlib>

void ERROR_CHECK_RES(int res, std::string location) {
  if (res != 0) {
    // making error text red with ANSI code
    std::cerr << "\033[1;31m ERROR FAILED AT: " << location << "\033[0m"
              << std::endl;
    exit(EXIT_FAILURE);
  }
}
