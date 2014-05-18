#include "utils.hpp"

#include <algorithm>
#include <chrono>

std::mt19937& random_generator()
{
	static std::mt19937 gen(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
	return gen;
}

void trim(std::string& s)
{
	// Right trim
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

	// Left trim
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}
