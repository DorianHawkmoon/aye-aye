#include "Path.h"
#include "SidePath.h"
#include "Room.h"
#include <iostream>
#include "Inventory.h"

Path::Path(Room* origin, const Direction& directionOrigin,
	Room* destination, const Direction& directionDestination,
	const char* name, const char* description)
	:name(name), description(description) {
	
	//create the sides
	this->origin = new SidePath(origin, directionOrigin, this);
	this->destination = new SidePath(destination, directionDestination, this);

	//tell the rooms it has a new path
	origin->addPath(this->origin);
	destination->addPath(this->destination);

}

Path::Path(Room * origin, const Direction & directionOrigin, Room * destination, const Direction & directionDestination,
	const char * name): Path(origin, directionOrigin, destination, directionDestination, name, "there's a") {}

Path::~Path(){
	delete origin;
	delete destination;
}

const std::string Path::look(const SidePath* origin) const {
	return std::string(description + " " + name);
}

const std::string Path::see(const SidePath * origin) const {
	return std::string(description + " " + name);
}

Room* Path::go(const SidePath* origin) const {
	Room* result=nullptr;
	//if where i am is closed... bad
	if(origin->isOpened()==false){
		std::cout << "Is closed!" << std::endl;

	//if the origin side its my origin field stored, return the adecuate room
	}else if (this->origin->getId() == origin->getId()) {
		result = destination->getRoom();
	} else {
		result = this->origin->getRoom();
	}
	return result;
}

const SidePath * Path::getOtherSide(const SidePath * origin) const {
	if (Utilities::compareTo(origin->getName(), this->origin->getName())) {
		return this->destination;
	} else {
		return this->origin;
	}
}

const std::string Path::close(SidePath * origin, const Inventory * closeItems) {
	return "There's nothing here to close";
}

const std::string Path::open(SidePath* origin, const Inventory * openItems) {
	return "There's nothing here to open";
}
