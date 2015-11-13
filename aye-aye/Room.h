#pragma once
#ifndef _ROOM_H_
#define _ROOM_H_

#include <string>
#include <list>
#include "Direction.h"

class Path;

class Room
{
public:
	Room(const char* name, const char* description);
	virtual ~Room();

	inline const std::string& getDescription() const {
		return description;
	}
	inline const std::string& getName() const {
		return name;
	}
	inline const unsigned int Room::getId() const {
		return id;
	}
	
	const std::string look() const;
	Room* go(const Direction& direction) const;
	const Path* getPath(const Direction& direction) const;
	bool addPath(const Path* path, const Direction& direction);

private:
	struct Exits {
		const Direction direction;
		const Path* path;

		Exits(const Direction& direction, const Path* path) : direction(direction), path(path) {};
	};
	static unsigned int nextId;

	std::string description;
	std::string name;
	unsigned int id;

	std::list<Exits> paths;
};

#endif /* _ROOM_H_ */