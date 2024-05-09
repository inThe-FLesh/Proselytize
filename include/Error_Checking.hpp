#include <iostream>
#include <string>

#ifndef ERROR_CHECKING_H
#define ERROR_CHECKING_H

// Used to check the returned ints from the libav functions
// The name stands for error check result
void ERROR_CHECK_RES(int res, std::string location);

#endif // !ERROR_CHECKING_H
