#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <list>
#include "Direction.h"
#include "Entity.h"

class SidePath;
class Creature;
class Inventory;

class Room : public Entity {
public:
	Room(const char* name, const char* description);
	virtual ~Room();

	//method overrided from entity
	virtual const std::string look(const std::vector<std::string>& arguments) const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity * item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems) ;
	virtual const std::string go(const std::vector<std::string>& arguments);
	virtual const std::string take(const std::vector<std::string>& arguments);
	
	//move (get the room destination) return nullptr if i dont have an exit or is closed
	Room* go(const Direction& direction) const;
	//add an exit to the room
	bool addPath(SidePath* path);
	//get the side of the especified exit, return nullptr if not exist
	const SidePath* getPath(const Direction& direction) const;
	//list of creatures alives (enemies)
	const std::list<Creature*> getEnemies() const;
	//add an item to this room TODO:move to private and make friend
	void addItem(Entity* item);

private:
	//the exists
	std::list<SidePath*> paths;
	//every item and creature
	std::list<Entity*> items;
};

#endif /* _ROOM_H_ */