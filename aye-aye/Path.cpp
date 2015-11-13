#include "Path.h"
#include "Room.h"
#include <iostream>

Path::Path(Room * origin, Room * destination, const char* name): Path(origin, destination, name, "there's a") {}

Path::Path(Room* origin, Room * destination, const char* name, const char* description)
	:origin(origin), destination(destination), name(name), description(description), opened(true) {
	
}

Path::~Path(){
}

const std::string Path::look(const Room* origin) const {
	return std::string(description + " " + name);
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
