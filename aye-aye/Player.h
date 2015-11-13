#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "Utilities.h"
class Room;

class Player{
public:
	Player(Room* room);
	virtual ~Player();

	//do something with the words written by the player
	const void action(const std::vector<std::string>& arguments);

	const std::string actualState() const;

private:
	//Room in which we are
	Room* actualRoom;
	//list of object (inventary)
	//stats of the player (protagonist)

private:
	void go(const std::vector<std::string>& arguments);
	void look(const std::vector<std::string>& arguments);
	void see(const std::vector<std::string>& arguments);
	void open(const std::vector<std::string>& arguments);
};

#endif // ! _PLAYER_H_