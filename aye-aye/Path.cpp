#include "Path.h"
#include "Room.h"
#include <iostream>

Path::Path(Room* origin, Room * destination) :origin(origin), destination(destination), opened(true) {
	
}

Path::~Path(){
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

bool Path::open() {
	std::cout << "There's nothing here to open" << std::endl;
	return false;
}
