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
	virtual const Entity* getEntity(const std::string& name);
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems);

	inline const std::string& getDescription() const {
		return description;
	}
	inline const std::string& getName() const {
		return name;
	}
	
	Room* go(const Direction& direction) const;
	const SidePath * Room::getPath(const Direction & direction) const;
	SidePath* getPath(const std::string& name) const;
	bool addPath(SidePath* path);

	void addItem(Item* item);
	const Item* getItem(const std::string& name);
	Item * Room::take(const std::string & name);

private:

	std::string description;
	std::string name;

	std::list<SidePath*> paths;
	std::list<Item*> items;
};

#endif /* _ROOM_H_ */