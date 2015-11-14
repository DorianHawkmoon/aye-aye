#pragma once
#ifndef _SIDE_PATH_H_
#define _SIDE_PATH_H_

#include <list>
#include "Direction.h"
#include "Entity.h"
class Room;
class Item;
class Path;

class SidePath : public Entity {
public:
	SidePath(Room* room, const Direction& direction, Path* parent);
	virtual ~SidePath();

	inline const Direction& getDirection() const {
		return direction;
	}
	const std::string getName() const;
	const std::string open(const std::list<Item*>& openItems);
	inline Room* getRoom() const {
		return origin;
	}
	Room* go() const;
	inline const bool isOpened() const {
		return opened;
	}
	inline void setOpened(const bool opened) {
		this->opened = opened;
	}

	virtual const std::string look() const;
	virtual const Entity* getEntity(const std::string& name);
	virtual const std::string see(const std::vector<std::string>& arguments) const ;
	virtual const std::string open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems) ;

protected:
	const Direction direction;
	Room* origin;
	bool opened;
	Path* parent;
};

#endif // ! _SIDE_PATH_H_