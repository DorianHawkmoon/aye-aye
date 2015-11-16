#include "Weapon.h"
#include <sstream>

Weapon::Weapon(const int hit, const char * name, const char * description, const TypeItem type, const unsigned int count)
: Item(name, description, type, count), hit(hit) {}

Weapon::~Weapon() {}

const std::string Weapon::getDescription() const {
	std::stringstream result;
	result << this->getName() << " hit: " << this->getHit();
	return result.str();
}
