#include "SimpleLock.h"
#include "SidePath.h"
#include "Inventory.h"
#include "Entity.h"

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

void SimpleLock::addItemNeeded(const Entity * key) {
	needed.push_back(key);
}


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

const std::string SimpleLock::close(SidePath * origin, const Inventory * closeItems) {
	if (needed.size() == 0) {
		//no items needed
		if (!origin->isOpened()) {
			return "Already closed";
		}
		this->origin->setOpened(false);
		destination->setOpened(false);
		return descriptionClosing;
	} else {
		//check the items
		if (Utilities::matchNeeded(needed, closeItems)) {
			this->origin->setOpened(false);
			destination->setOpened(false);
			return descriptionClosing;
		}
		return "Is still open. You need something to close this.";
	}
}

const std::string SimpleLock::open(SidePath * origin, const Inventory * openItems) {
	if (needed.size()==0) {
		//no items needed
		if (origin->isOpened()) {
			return "Already opened";
		}
		this->origin->setOpened(true);
		destination->setOpened(true);
		return descriptionOpening;
	} else {
		//check the items
		if (Utilities::matchNeeded(needed, openItems)) {
			this->origin->setOpened(true);
			destination->setOpened(true);
			return descriptionOpening;
		} else {
			return "Is closed! You need something to open this.";
		}
	}
}
