#include "Player.h"
#include "Room.h"
#include "Direction.h"
#include <iostream>
#include "SidePath.h"
#include <list>
#include "Item.h"


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
	} else if (Utilities::compareTo(arguments[0], "drop")){
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
	Direction direction=Directions::toDirection(arguments[1]);
	if(direction==NOWHERE){
		return "Go where?";
	}

	Room* destiny = actualRoom->go(direction);
	if (destiny != nullptr) {
		actualRoom = destiny;
		return std::string(actualRoom->getName() + '\n' + actualRoom->getDescription());
	} else {
		//TODO: fix this
		return "WHAT THE HELL?!?!";
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
	//look a concrete object
	if (Utilities::compareTo(arguments[1], "room") || arguments.size() == 1) {
		return actualRoom->look();
	} else {
		Direction direction = Directions::toDirection(arguments[1]);
		if (direction != Direction::NOWHERE) {
			return actualRoom->getPath(direction)->see(arguments);
		} else {
			return actualRoom->see(arguments);
		}
	}
}

const std::string Player::open(const std::vector<std::string>& arguments) {
	//check if refers to a direction
	std::list<Item*> items; //subsitute with the inventory
	//check if refers a inventory (open box in inventory)
	if (false /*TODO: find object function in inventory that returns the object or null and store it.*/) {
	   //TODO: execute the open function on the object

   //check if refers to a name path or object in the room
	} else {
		return actualRoom->open(arguments, items);
	}
}

const std::string Player::take(const std::vector<std::string>& arguments) {
	Item* item = actualRoom->take(arguments[1]);
	return inventory.storeItem(item);
}

const std::string Player::drop(const std::vector<std::string>& arguments) {
	if (arguments.size() < 2) {
		return "Drop what?";
	} else {
		Item* item=inventory.takeOutItem(arguments[1]);
		if (item == nullptr) {
			return "Drop what?";
		}
		return actualRoom->drop(arguments, item);
	}
}