#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
class Room;

class Player {
public:
	Player(Room* room);
	virtual ~Player();

	//do something with the words written by the player
	const std::string& action(const std::vector<std::string>& arguments);

	const std::string& actualState() const;

private:
	//Room in which we are
	Room* actualRoom;
	//list of object (inventary)
	//stats of the player (protagonist)
};

#endif // ! _PLAYER_H_