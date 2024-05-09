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
