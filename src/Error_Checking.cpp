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

void ERROR_CHECK_BOOL(bool OKSignal, std::string location) {
  if (!OKSignal) {
    // making error text red with ANSI code
    std::cerr << "\033[1;31m ERROR FAILED AT: " << location << "\033[0m"
              << std::endl;
    exit(EXIT_FAILURE);
  }
}
