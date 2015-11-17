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
	const bool winCondition() const;

private:
	Room* actualRoom;
	std::list<Room*> listRooms;
	std::list<Path*> listPath;
	//list of the targets to check the win condition (don't delete, this class not own the objects)
	std::list<Creature*> listCreature;
};

#endif // !_WORLD_H_