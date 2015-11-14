#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "Utilities.h"
#include "Inventory.h"

class Room;

class Player {
public:
	Player(Room* room);
	virtual ~Player();

	//do something with the words written by the player
	const std::string action(const std::vector<std::string>& arguments);

	const std::string actualState() const;

private:
	//Room in which we are
	Room* actualRoom;
	//list of object (inventary)
	Inventory inventory;
	//stats of the player (protagonist)

private:
	const std::string go(const std::vector<std::string>& arguments);
	const std::string look(const std::vector<std::string>& arguments);
	const std::string see(const std::vector<std::string>& arguments);
	const std::string open(const std::vector<std::string>& arguments);
	const std::string take(const std::vector<std::string>& arguments);
};

#endif // ! _PLAYER_H_