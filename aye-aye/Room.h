#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <list>
#include "Direction.h"
#include "Entity.h"

class SidePath;
class Item;

class Room : public Entity {
public:
	Room(const char* name, const char* description);
	virtual ~Room();

	virtual const std::string look() const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const std::list<Entity*>& openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity * item);
	virtual Entity* take(const std::string& name);
	
	Room* go(const Direction& direction) const;
	bool addPath(SidePath* path);

	void addItem(Entity* item);

private:
	std::list<SidePath*> paths;
	std::list<Entity*> items;
};

#endif /* _ROOM_H_ */