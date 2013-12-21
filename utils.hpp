#ifndef MLSTONE_UTILS
#define MLSTONE_UTILS

#include <string>
#include <random>

std::mt19937& random_generator();

// Trimming
// http://stackoverflow.com/a/217605/22459
// Evan Teran
void trim(std::string& s);

#endif
