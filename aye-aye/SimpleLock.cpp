#include "SimpleLock.h"
#include <iostream>


SimpleLock::SimpleLock(Room* origin, Room* destination, const char* name, const bool opened,
	const char * descriptionOpened, const char * descriptionClosed, 
	const char * descriptionOpening, const char * descriptionClosing)
: Path(origin,destination, name), descriptionClosed(descriptionClosed), descriptionClosing(descriptionClosing), descriptionOpened(descriptionOpened), descriptionOpening(descriptionOpening) {
	this->opened = opened;
}

SimpleLock::~SimpleLock() {}

const std::string SimpleLock::look(const Room* origin) const {
	if (opened) {
		return descriptionOpened;
	} else {
		return descriptionClosed;
	}
}

const bool SimpleLock::open() {
	std::cout << descriptionOpening << std::endl;
	opened = true;
	return opened;
}
