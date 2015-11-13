#include "Player.h"
#include "Room.h"
#include "Direction.h"
#include <iostream>
#include "Path.h"

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
	std::cout << actualRoom->look() << std::endl;
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

		const Path* path = actualRoom->getPath(direction);
		if (path == nullptr) {
			std::cout << "There's nothing there" << std::endl;
		} else {
			std::cout << path->look(actualRoom) << std::endl;
		}
	}
}

