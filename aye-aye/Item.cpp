#include "Item.h"
#include "Utilities.h"

Item::Item(const char * name, const char * description)
:Entity(), name(name), description(description), count(1) {
}

Item::Item(const Item & item): Entity(item), count(item.count), description(description), name(name){

}

Item::~Item() {}

const std::string Item::look() const {
	return std::string(numberToString(count) + " " + name);
}

const Entity * Item::getEntity(const std::string & name) {
	if (compareTo(this->name, name)) {
		return this;
	} else {
		return nullptr;
	}
}

const std::string Item::see(const std::vector<std::string>& arguments) const {
	return std::string(this->look() + " " + description);
}

const std::string Item::open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems) {
	return "There's nothing to open";
}

const bool Item::addItem(unsigned int value) {
	if (count+value<=MAX_ITEMS) {
		count += value;
		return true;
	} else {
		return false;
	}
}

const bool Item::substractItem(unsigned int value) {
	if (count >= value) {
		count -= value;
		return true;
	} else {
		return false;
	}
}
