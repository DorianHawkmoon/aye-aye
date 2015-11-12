#include "Path.h"
#include "Room.h"


Path::Path(Room* origin, Room * destination) :origin(origin), destination(destination) {
	
}

Path::~Path(){
}

Room* Path::go(const Room* origin) const {
	Room* result=nullptr;
	if (this->origin->getId() == origin->getId()) {
		result = destination;
	} else {
		result = this->origin;
	}
	return result;
}
