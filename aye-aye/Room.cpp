#include "Room.h"
#include <algorithm>
#include "SidePath.h"
#include <sstream>
#include <iostream>
#include "Item.h"
#include "Utilities.h"


Room::Room(const char* name, const char* description): Entity(), name(name), description(description){
}

Room::~Room(){
	//delete all items
	for each (const Item* item in items) {
		delete item;
	}
}

const std::string Room::look() const {
	std::stringstream result;
	result << description;
	//add to description the description of objects
	unsigned int size;
	if (size = items.size()) {
		if (size == 1) {
			result << std::endl << "There is";
		} else {
			result << std::endl << "There are";
		}
	}
	unsigned int count = 0;
	for each(const Entity* entity in items) {
		++count;
		if (count == size  && count>1) {
			result << " and";
		}
		result << " " <<  entity->look();

		if (count == size) {
			result << "." << std::endl;
		} else {
			result << ",";
		}
	}

	//add to description the description of paths
	for each (SidePath* path in paths) {
		result << std::endl << "At " << Directions::toString(path->getDirection()) << " " \
			<< path->look();//specifing from where I'm looking the path
	}
	return result.str();
}

Entity* Room::getEntity(const std::string& name) const{
	return nullptr;
}

const std::string Room::see(const std::vector<std::string>& arguments) const {
	//TODO: see a wall if something, or see an object
	//if seeing a direction
	//if seeing an object
	return std::string();
}

const std::string Room::open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems) {
	if (arguments.size() < 2) {
		return "Open what?";
	}
	Direction direction = Directions::toDirection(arguments[1]);
	if (direction != NOWHERE) {
		//TODO: hacer por dirección
		SidePath* path = getPath(direction);
		path->open(arguments, openItems);
		return "TODO";
	}else if(SidePath* path = getPath(arguments[1])){ //check by name of path
		return path->open(arguments, openItems);

	} else if(Entity* entity=getEntity(arguments[1])) { //check in objects of the room
		return entity->open(arguments, openItems);

	} else {
		return "Open what?";
	}
}


Room* Room::go(const Direction & direction) const {
	std::list<SidePath*>::const_iterator result = std::find_if(paths.begin(), paths.end(), 
		[&direction](const SidePath* exit) { //given the direction, check if this concrete exit is found
			return exit->getDirection() == direction;
		});

	Room* resultRoom;
	if (result != paths.end()) {
		//return
		resultRoom = (*result)->go();
	}else {
		std::cout << "There's no way on this side" << std::endl;
		resultRoom = nullptr;
	}
	return resultRoom;
}

SidePath * Room::getPath(const Direction & direction) const {
	std::list<SidePath*>::const_iterator result = std::find_if(paths.begin(), paths.end(),
		[&direction](const SidePath* exit) { //given the direction, check if this concrete exit is found
		return exit->getDirection() == direction;
	});

	SidePath* resultPath;
	if (result != paths.end()) {
		resultPath = *result;
	}else{
		resultPath = nullptr;
	}
	return resultPath;
}

bool Room::addPath(SidePath* path) {
	paths.push_back(path);
	return true;
}

void Room::addItem(Item * item) {
	items.push_back(item);
}

const Item * Room::getItem(const std::string & name) {
	const Item* result = nullptr;
	
	std::list<Item*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](const Item* item) { 
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
	}

	return result;
}

Item * Room::take(const std::string & name) {
	Item* result = nullptr;

	std::list<Item*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](const Item* item) {
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
		items.erase(resultIt);
	}

	return result;
}

SidePath* Room::getPath(const std::string& name) const {
	SidePath* result = nullptr;

	std::list<SidePath*>::const_iterator resultIt = std::find_if(paths.begin(), paths.end(),
		[&name](const SidePath* exit) { //given the direction, check if this concrete exit is found
		return Utilities::compareTo(exit->getName(), name);
	});

	if (resultIt != paths.end()) {
		result = *resultIt;
	}

	return result;
}