#pragma once
#ifndef _SIDE_PATH_H_
#define _SIDE_PATH_H_

#include <vector>
#include "Direction.h"
#include "Entity.h"

class Inventory;
class Room;
class Path;

/*A path consist of two sides of the path. The path defines their behaviour (if one side is opened, the other too or not,
both needs the same items or not...
This is the entity that rooms store to know their exists*/
class SidePath : public Entity {
public:
	SidePath(Room* room, const Direction& direction, Path* parent);
	virtual ~SidePath();

	virtual const std::string& getName() const;
	//get the direction in which this side is oriented in the room (the side is on north of the room)
	inline const Direction& getDirection() const {
		return direction;
	}
	//get the original room of this side
	inline Room* getRoom() const {
		return origin;
	}
	//move (get the room of destination)
	Room* go() const;
	//is open?
	inline const bool isOpened() const {
		return opened;
	}
	//set the opened
	inline void setOpened(const bool opened) {
		this->opened = opened;
	}
	//get the other side of the path
	const SidePath* getOtherSide() const;

	//methods override from Entity
	virtual const std::string look(const std::vector<std::string>& arguments) const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const ;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity * item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);
	virtual const std::string go(const std::vector<std::string>& arguments);
	virtual const std::string take(const std::vector<std::string>& arguments);

private:
	const Direction direction;
	Room* origin;
	bool opened;
	Path* parentPath;
};

#endif // ! _SIDE_PATH_H_