#include "Item.h"

unsigned int Item::nextId=-1;

Item::Item(const char * name, const char * description)
: idItem(++nextId), name(name), description(description), count(1) {
}

Item::~Item() {}

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
