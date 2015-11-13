#include "Utilities.h"

bool compareTo(const std::string& a, const std::string& b)  {
	return strcmp(a.c_str(), b.c_str()) == 0;
}

const std::string numberToString(const unsigned int number) {
	switch (number) {
		case 0:
			return "zero";
		case 1:
			return "one";
		case 2:
			return "two";
		case 3:
			return "three";
		case 4:
			return "four";
		case 5:
			return "five";
		case 6:
			return "six";
		case 7:
			return "seven";
		case 8:
			return "eigth";
		case 9:
			return "nine";
		case 10:
			return "ten";
		default:
			return "indetermined";
	}
}