#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include <string>
#include "Direction.h"
#include <list>

class Room;
class Creature;
class Path;

class World {
public:
	World();
	virtual ~World();

	//actual room where player is
	Room* getActualRoom() const;

private:
	Room* actualRoom;
	std::list<Room*> listRooms;
	std::list<Path*> listPath;
};

#endif // !_WORLD_H_