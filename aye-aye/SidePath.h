#pragma once
#ifndef _SIDE_PATH_H_
#define _SIDE_PATH_H_

#include <vector>
#include "Direction.h"
#include "Entity.h"
class Inventory;
class Room;
class Path;

class SidePath : public Entity {
public:
	SidePath(Room* room, const Direction& direction, Path* parent);
	virtual ~SidePath();

	virtual const std::string& getName() const;
	inline const Direction& getDirection() const {
		return direction;
	}
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

	const SidePath* getOtherSide() const;

	virtual const std::string look(const std::vector<std::string>& arguments) const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const ;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity * item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);
	const std::string go(const std::vector<std::string>& arguments);
	virtual const std::string take(const std::vector<std::string>& arguments);

protected:
	const Direction direction;
	Room* origin;
	bool opened;
	Path* parentPath;
};

#endif // ! _SIDE_PATH_H_