#pragma once
#ifndef _UTILITIES_H_
#define _UTILITIES_H

#include <string>
#include <vector>

namespace Utilities{

	const std::string numberToString(const unsigned int number);
	const bool compareTo(const std::string& a, const std::string& b);
	const std::vector<std::string> split(const std::string &s, const char delim);
	const std::vector<std::string>& split(const std::string &s, const char delim, std::vector<std::string> &elems);

}
#endif // ! _UTILITIES_H_
