#include "Path.h"
#include "Room.h"
#include <iostream>

Path::Path(Room * origin, Room * destination): Path(origin, destination, "there's a path") {}

Path::Path(Room* origin, Room * destination, const char* description)
	:origin(origin), destination(destination), description(description), opened(true) {
	
}

Path::~Path(){
}

const std::string Path::look(const Room* origin) const {
	return description;
}

Room* Path::go(const Room* origin) const {
	Room* result=nullptr;
	if(!opened){
		std::cout << "Is closed!" << std::endl;
	}else if (this->origin->getId() == origin->getId()) {
		result = destination;
	} else {
		result = this->origin;
	}
	return result;
}

const bool Path::open() {
	std::cout << "There's nothing here to open" << std::endl;
	return false;
}
