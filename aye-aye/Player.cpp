#include "Player.h"
#include "Room.h"
#include "Direction.h"
#include <iostream>
#include "SidePath.h"
#include <list>
#include "Item.h"

Player::Player(Room* room) : actualRoom(room) {

}


Player::~Player() {}

const void Player::action(const std::vector<std::string>& arguments) {
	if (compareTo(arguments[0], "look")) {
		look(arguments);
	} else if (compareTo(arguments[0], "go")) {
		go(arguments);
	} else if (compareTo(arguments[0], "see")) {
		see(arguments);
	} else if (compareTo(arguments[0], "open")) {
		open(arguments);
	} else if (compareTo(arguments[0], "take")) {
		take(arguments);
	}
}

const std::string Player::actualState() const {
	std::string result(actualRoom->getName());
	result+='\n';
	result.append(actualRoom->getDescription());
	return result;
}

void Player::go(const std::vector<std::string>& arguments) {
	Direction direction;
	bool understood = true;
	if (compareTo(arguments[1], "north")) {
		direction = Direction::NORTH;
	} else if (compareTo(arguments[1], "south")) {
		direction = Direction::SOUTH;
	} else if (compareTo(arguments[1], "west")) {
		direction = Direction::WEST;
	} else if (compareTo(arguments[1], "east")) {
		direction = Direction::EAST;
	} else {
		understood = false;
		std::cout << "Go where?" << std::endl;
	}

	if (understood) {
		Room* destiny = actualRoom->go(direction);
		if (destiny != nullptr) {
			actualRoom = destiny;
			std::cout << actualRoom->getName() << std::endl << actualRoom->getDescription() << std::endl;
		}
	}
}

void Player::look(const std::vector<std::string>& arguments) {
	if (arguments.size() > 1 && compareTo(arguments[1], "inventory")) {
		std::cout << inventory.look();
	} else if(arguments.size()==1) {
		std::cout << actualRoom->look() << std::endl;
	} else {
		std::cout << "look what?" << std::endl;
	}
}

void Player::see(const std::vector<std::string>& arguments) {
	//TODO: refactorizar esta mierda
	//look a concrete object
	if (compareTo(arguments[1], "room") || arguments.size() == 1) {
		std::cout<<actualRoom->look()<<std::endl;
	} else {
		Direction direction;
		if (compareTo(arguments[1], "north")) {
			direction = Direction::NORTH;
		} else if (compareTo(arguments[1], "south")) {
			direction = Direction::SOUTH;
		} else if (compareTo(arguments[1], "west")) {
			direction = Direction::WEST;
		} else if (compareTo(arguments[1], "east")) {
			direction = Direction::EAST;
		}

		std::cout << actualRoom->see(arguments) << std::endl;
		/* const Path* path = actualRoom->getPath(direction);
		if (path == nullptr) {
			std::cout << "There's nothing there" << std::endl;
		} else {
			std::cout << path->look(actualRoom) << std::endl;
		} */
	}
}

void Player::open(const std::vector<std::string>& arguments) {
	std::string direction = arguments[1];
	//check if refers to a direction
	if (compareTo(direction, "north") || compareTo(direction, "south") || compareTo(direction, "east") || compareTo(direction, "west")) {

	//check if refers to an object from the inventory
	} else if(false /*TODO: find object function in inventory that returns the object or null and store it.*/){
		//TODO: execute the open function on the object

	//check if refers to a name path or object in the room
	} else if(SidePath* path=actualRoom->getPath(direction) /*search in room */){
		std::list<Item*> items;
		std::cout << path->open(items) << std::endl;
	}
}

void Player::take(const std::vector<std::string>& arguments) {
	Item* item = actualRoom->take(arguments[1]);
	inventory.storeItem(item);
}
