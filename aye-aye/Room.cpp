#include "Room.h"
#include <algorithm>
#include "SidePath.h"
#include <sstream>
#include <iostream>
#include "Item.h"
#include "Utilities.h"
#include "Inventory.h"
#include "Creature.h"

Room::Room(const char* name, const char* description) : Entity(name, description, ROOM) {}

Room::~Room() {
	//delete all items
	for each (const Item* item in items) {
		delete item;
	}
}

const std::string Room::look(const std::vector<std::string>& arguments) const {
	std::stringstream result;
	result << name << std::endl << description;

	if (arguments.size() == 0) {
		return result.str();
	}

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
		if (count == size  && count > 1) {
			result << " and";
		}
		if (entity->getType() == CREATURE) {
			result << " " << entity->getDescription();
		} else {
			result << " " << entity->look(arguments);
		}
		if (count == size) {
			result << "." << std::endl;
		} else {
			result << ",";
		}
	}

	//add to description the description of paths
	for each (SidePath* path in paths) {
		result << std::endl << "At " << Directions::toString(path->getDirection()) << " " \
			<< path->look(arguments);//specifing from where I'm looking the path
	}
	return result.str();
}

Entity* Room::getEntity(const std::string& name) const {
	Entity* result = nullptr;

	//Is myself?
	if (Utilities::compareTo(this->name, name)) {
		return const_cast<Room*>(this);
	}

	//search in directions
	Direction direction = Directions::toDirection(name);
	if (direction != NOWHERE) {
		std::list<SidePath*>::const_iterator resultIt = std::find_if(paths.begin(), paths.end(),
			[&direction](const SidePath* exit) { //given the direction, check if this concrete exit is found
			return exit->getDirection() == direction;
		});

		if (resultIt != paths.end()) {
			result = *resultIt;
		}

	} else {
		//search by name of paths
		std::list<SidePath*>::const_iterator resultIt = std::find_if(paths.begin(), paths.end(),
			[&name](const SidePath* exit) { //given the direction, check if this concrete exit is found
			return Utilities::compareTo(exit->getName(), name);
		});

		if (resultIt != paths.end()) {
			result = *resultIt;
		} else {
			//look in the objects of the room
			for (std::list<Entity *>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
				result = (*it)->getEntity(name);
			}
		}
	}
	return result;
}

const std::string Room::see(const std::vector<std::string>& arguments) const {
	unsigned int size = arguments.size();
	if (size < 2) {
		return look(arguments);
	} else if (Utilities::compareTo(arguments[1], "room") || Utilities::compareTo(arguments[1], this->getName())) {
		return look(arguments);
	} else {
		//search the entity
		Entity* entity = getEntity(arguments[1]);
		if (entity == nullptr) {
			return "See what?";
		}
		return entity->see(arguments);
	}
}

const std::string Room::open(const std::vector<std::string>& arguments, const Inventory * openItems) {
	if (arguments.size() < 2) {
		return "Open what?";
	}
	if (Entity* entity = getEntity(arguments[1])) { //check in objects of the room
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
	} else {
		std::cout << "There's no way on this side" << std::endl;
		resultRoom = nullptr;
	}
	return resultRoom;
}

bool Room::addPath(SidePath* path) {
	paths.push_back(path);
	return true;
}

const SidePath * Room::getPath(const Direction & direction) const {
	std::list<SidePath*>::const_iterator result = std::find_if(paths.begin(), paths.end(),
		[&direction](const SidePath* exit) { //given the direction, check if this concrete exit is found
		return exit->getDirection() == direction;
	});

	const SidePath* side = nullptr;
	if (result != paths.end()) {
		side = *result;
	}
	return side;
}

const std::list<Creature*> Room::getEnemies() const {
	std::list<Creature*> result;
	for each(Entity* entity in items) {
		if (entity->getType() == CREATURE) {
			Creature* creature = static_cast<Creature*>(entity);
			if (creature->isAlive()) {
				result.push_back(creature);
			}
		}
	}
	return result;
}

void Room::addItem(Entity* item) {
	items.push_back(item);
	item->changeParent(this);
}

Entity * Room::take(const std::string & name) {
	Entity* result = nullptr;

	std::list<Entity*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](const Entity* item) {
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
		if (result->getType() == ITEM && (static_cast<Item*>(result))->canTake()) {
			items.erase(resultIt);
		} else {
			std::cout << std::endl << "Can't take it" << std::endl;
			result = nullptr;
		}
	} else {
		//search inside the items
		for (std::list<Entity*>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
			result = (*it)->take(name);
		}
	}

	return result;
}

const std::string Room::close(const std::vector<std::string>& arguments, const Inventory * closeItems) {
	if (arguments.size() < 2) {
		return "Close what?";
	}
	if (Entity* entity = getEntity(arguments[1])) { //check in objects of the room
		return entity->close(arguments, closeItems);

	} else {
		return "Close what?";
	}
}

const std::string Room::take(const std::vector<std::string>& arguments) {
	return std::string("A room can take anything!");
}


const std::string Room::go(const std::vector<std::string>& arguments) {
	return std::string("A room can't go anywhere!");
}

const std::pair<bool, std::string> Room::drop(const std::vector<std::string>& arguments, Entity * item) {
	if (item == nullptr) {
		std::pair<bool, std::string> result;
		result.first = false;
		result.second = "Drop what?";
		return result;
	}
	unsigned int size = arguments.size();
	if (size > 2) {
		//get the name
		std::string into((size > 3) ? arguments[3] : arguments[2]);
		if (Utilities::compareTo(this->name, into) || Utilities::compareTo("room", into)) {
			//its me
			addItem(item);
			std::pair<bool, std::string> result;
			result.first = true;
			result.second = "Dropped";
			return result;
		} else {
			//it's not me, get the item into store if opened
			Entity* itemInto = getEntity(into);
			if (itemInto != nullptr) {
				return itemInto->drop(arguments, item);
			} else {
				std::pair<bool, std::string> result;
				result.first = false;
				result.second = "Drop where?";
				return result;
			}
		}

	} else {
		addItem(item);
		std::pair<bool, std::string> result;
		result.first = true;
		result.second = "Dropped";
		return result;
	}
}