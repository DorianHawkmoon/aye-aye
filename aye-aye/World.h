#pragma once
#ifndef _WORLD_H_
#define _WORLD_H_

#include <string>
#include <list>
#include "Creature.h" //full import because of friend

class Room;
class Entity;
class Path;
/* The world with contains rooms and paths and 
create the whole game (creatures, items...)*/
class World {
//public methods
public:
	World();
	virtual ~World();

	//actual room where player is
	Room* getActualRoom() const;
	//check the win condition
	const bool winCondition() const;


	
//private fields
private:
	Room* actualRoom;
	std::list<Room*> listRooms;
	std::list<Path*> listPath;
	//list of the targets to check the win condition (don't delete, this class not own the objects)
	std::list<Creature*> listCreature;

//private methods
private:
	friend void Creature::addItem(Entity* entity);

};

#endif // !_WORLD_H_