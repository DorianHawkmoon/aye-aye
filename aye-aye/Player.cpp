#include "Player.h"
#include "Room.h"
#include "Direction.h"
#include <iostream>
#include "SidePath.h"
#include <list>
#include "Entity.h"


Player::Player(Room* room) : actualRoom(room) {}

Player::~Player() {}


const std::string Player::action(const std::vector<std::string>& arguments) {
	if (Utilities::compareTo(arguments[0], "look")) {
		return look(arguments);
	} else if (Utilities::compareTo(arguments[0], "go")) {
		return go(arguments);
	} else if (Utilities::compareTo(arguments[0], "see")) {
		return see(arguments);
	} else if (Utilities::compareTo(arguments[0], "open")) {
		return open(arguments);
	} else if (Utilities::compareTo(arguments[0], "take")) {
		return take(arguments);
	} else if (Utilities::compareTo(arguments[0], "drop")) {
		return drop(arguments);
	} else {
		return "eemmm... sorry?";
	}
}

const std::string Player::actualState() const {
	std::string result(actualRoom->getName());
	result += '\n';
	result.append(actualRoom->getDescription());
	return result;
}

const std::string Player::go(const std::vector<std::string>& arguments) {
	Direction direction = Directions::toDirection(arguments[1]);
	if (direction == NOWHERE) {
		return "Go where?";
	}

	Room* destiny = actualRoom->go(direction);
	if (destiny != nullptr) {
		actualRoom = destiny;
		return std::string(actualRoom->getName() + '\n' + actualRoom->getDescription());
	} else {
		return "I'm lost...";
	}

}

const std::string Player::look(const std::vector<std::string>& arguments) {
	if (arguments.size() > 1 && Utilities::compareTo(arguments[1], "inventory")) {
		return inventory.look();
	} else if (arguments.size() == 1) {
		return actualRoom->look();
	} else {
		return "look what?";
	}
}

const std::string Player::see(const std::vector<std::string>& arguments) {
	//TODO control if seeing an object from inventory
	//look a concrete object
	if (Utilities::compareTo(arguments[1], "room") || arguments.size() == 1) {
		return actualRoom->look();
	} else {
		return actualRoom->see(arguments);
	}
}

const std::string Player::open(const std::vector<std::string>& arguments) {
	const Inventory* inv = &inventory;
		return actualRoom->open(arguments, inv);
	
}

const std::string Player::take(const std::vector<std::string>& arguments) {
	Entity* item = actualRoom->take(arguments[1]);
	if (item == nullptr) {
		return std::string("There's nothing");
	} else {
		return inventory.drop(arguments, item).second;
	}
}

const std::string Player::drop(const std::vector<std::string>& arguments) {
	if (arguments.size() < 2) {
		return "Drop what?";
	} else {
		//Entity* item=inventory.takeOutItem(arguments[1]);
		Entity* item = inventory.getEntity(arguments[1]);
		if (item == nullptr) {
			return "Drop what?";
		}
		std::pair<bool, std::string> result = actualRoom->drop(arguments, item);
		if (result.first) {
			inventory.take(arguments[1]);
		}
		return result.second;
	}
}