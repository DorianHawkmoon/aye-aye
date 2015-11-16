#include "Utilities.h"
#include <sstream>
#include "Entity.h"
#include "Inventory.h"

const bool Utilities::compareTo(const std::string& a, const std::string& b)  {
	return strcmp(a.c_str(), b.c_str()) == 0;
}

const std::string Utilities::numberToString(const unsigned int number) {
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

const std::vector<std::string>& Utilities::split(const std::string &s, const char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}


const std::vector<std::string> Utilities::split(const std::string &s, const char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

const bool Utilities::matchNeeded(const std::list<const Entity*> needed, const Inventory * items) {
	bool result = true;
	for (std::list<const Entity*>::const_iterator it = needed.begin(); it != needed.end() && result; ++it) {
		result = items->getEntity((*it)->getName()) != nullptr;
	}
	return result;
}