#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include <string>
#include "Direction.h"
#include <list>

class Room;
class Path;

class World {
public:
	World();
	virtual ~World();

	//actual room where player is
	Room* getActualRoom() const;

	//go to another room, return a string indication the result of action
	//std::string& go(Direction& direction);

private:
	Room* actualRoom;
	std::list<Room*> listRooms;
	std::list<Path*> listPath;
};

#endif // !_WORLD_H_