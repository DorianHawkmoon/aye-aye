#pragma once
#ifndef _PATH_H_
#define _PATH_H_

#include "Direction.h"
#include <string>
#include "Entity.h"
#include <list>

class Room;
class SidePath;
class Inventory;

class Path {
public:
	Path(Room* origin, const Direction& directionOrigin, 
		Room* destination, const Direction& directionDestination,
		const char* name, const char* description);
	Path(Room* origin, const Direction& directionOrigin,
		Room* destination, const Direction& directionDestination,
		const char* name);
	virtual ~Path();

	inline const std::string& getName() const {
		return name;
	}
	inline const std::string& getDescription() const {
		return description;
	}
	Room* go(const SidePath* origin) const;
	virtual const SidePath* getOtherSide(const SidePath* origin) const;

	virtual const std::string look(const SidePath* origin) const;
	virtual const std::string see(const SidePath* origin) const;
	virtual const std::string open(SidePath* origin, const Inventory * openItems);
	virtual const std::string close(SidePath* origin, const Inventory* closeItems);

protected:
	SidePath* origin;
	SidePath* destination;
private:
	const std::string description;
	const std::string name;
};
#endif /* _PATH_H_ */
