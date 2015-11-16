#include "Armor.h"
#include <sstream>


Armor::Armor(const int defense, const char * name, const char * description, const TypeItem type, const unsigned int count) 
	: Item(name, description, type, count), defense(defense) {}

Armor::~Armor() {}

const std::string Armor::getDescription() const {
	std::stringstream result;
	result << this->getName() << " defense: " << this->getDefense();
	return result.str();
}
