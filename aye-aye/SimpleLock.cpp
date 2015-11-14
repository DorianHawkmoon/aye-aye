#include "SimpleLock.h"
#include "SidePath.h"

SimpleLock::SimpleLock(Room* origin, const Direction& directionOrigin,
	Room* destination, const Direction& directionDestination,
	const char* name, const bool opened,
	const char * descriptionOpened, const char * descriptionClosed, 
	const char * descriptionOpening, const char * descriptionClosing)
: Path(origin, directionOrigin,destination, directionDestination, name),
descriptionClosed(descriptionClosed), descriptionClosing(descriptionClosing),
descriptionOpened(descriptionOpened), descriptionOpening(descriptionOpening) {
	
	this->origin->setOpened(opened);
	this->destination->setOpened(opened);
}

SimpleLock::~SimpleLock() {}


const std::string SimpleLock::look(const SidePath * origin) const {
	if (origin->isOpened()) {
		return descriptionOpened;
	} else {
		return descriptionClosed;
	}
}

const std::string SimpleLock::see(const SidePath * origin) const {
	if (origin->isOpened()) {
		return descriptionOpened;
	} else {
		return descriptionClosed;
	}
}

const std::string SimpleLock::open(const SidePath * origin, const std::list<Item*>& openItems) {
	if (needed.size()==0) {
		//no items needed
		this->origin->setOpened(true);
		destination->setOpened(true);
		return descriptionOpening;
	} else {
		//check the items
		return "Is closed! You need the key or something to open this.";
	}
}
