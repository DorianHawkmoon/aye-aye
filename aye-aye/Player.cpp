#include "Player.h"
#include "Room.h"
#include "Direction.h"
#include <iostream>

Player::Player(Room* room) : actualRoom(room) {

}


Player::~Player() {}

const void Player::action(const std::vector<std::string>& arguments) {
	if (compareTo(arguments[0], "look")) {
		std::cout << actualRoom->getDescription() << std::endl;
	} else if (compareTo(arguments[0], "go")) {
		go(arguments);
	}
}

const std::string & Player::actualState() const {
	return actualRoom->getDescription();
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
			std::cout << actualRoom->getDescription() << std::endl;
		}
	}
}

