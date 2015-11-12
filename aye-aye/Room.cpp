#include "Room.h"
#include <algorithm>
#include "Path.h"
#include <iostream>

unsigned int Room::nextId = -1;


Room::Room(const char* name, const char* description): name(name), description(description), id(++nextId){
}

Room::~Room(){
}

Room* Room::go(const Direction & direction) const {
	std::list<Exits>::const_iterator result = std::find_if(paths.begin(), paths.end(), 
		[&direction](const Exits& exit) { //given the direction, check if this concrete exit is found
			return exit.direction == direction;
		});

	Room* resultRoom;
	if (result != paths.end()) {
		//return
		const Path* path = result->path;
		resultRoom = path->go(this);
	}else {
		std::cout << "There's no way on this side" << std::endl;
		resultRoom = nullptr;
	}
	return resultRoom;
}

bool Room::addPath(const Path* path, const Direction & direction) {
	Exits exit(direction, path);
	paths.push_back(exit);
	return true;
}
