#include "Room.h"
#include <algorithm>
#include "Path.h"
#include <sstream>
#include <iostream>
#include "Item.h"
#include "Utilities.h"

unsigned int Room::nextId = -1;


Room::Room(const char* name, const char* description): name(name), description(description), id(++nextId){
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
	//TODO: add to description the description of objects

	//add to description the description of paths
	for each (Exits exit in paths) {
		result << std::endl << "At " << toString(exit.direction) << " " \
			<< exit.path->look(this);//specifing from where I'm looking the path
	}
	return result.str();
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

const Path * Room::getPath(const Direction & direction) const {
	std::list<Exits>::const_iterator result = std::find_if(paths.begin(), paths.end(),
		[&direction](const Exits& exit) { //given the direction, check if this concrete exit is found
		return exit.direction == direction;
	});

	const Path* resultPath;
	if (result != paths.end()) {
		resultPath = result->path;
	}else{
		resultPath = nullptr;
	}
	return resultPath;
}

bool Room::addPath(Path* path, const Direction & direction) {
	Exits exit(direction, path);
	paths.push_back(exit);
	return true;
}

const void Room::addItem(const Item * item) {
	items.push_back(item);
}

const Item * Room::getItem(const std::string & name) {
	const Item* result = nullptr;
	
	std::list<const Item*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](const Item* item) { //given the direction, check if this concrete exit is found
		return compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
	}

	return result;
}


Path * Room::getPath(const std::string& name) const {
	Path* result = nullptr;

	std::list<Exits>::const_iterator resultIt = std::find_if(paths.begin(), paths.end(),
		[&name](const Exits& exit) { //given the direction, check if this concrete exit is found
		return compareTo(exit.path->getName(), name);
	});

	if (resultIt != paths.end()) {
		result = resultIt->path;
	}

	return result;
}