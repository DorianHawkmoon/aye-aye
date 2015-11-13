#pragma once
#ifndef _PATH_H_
#define _PATH_H_

#include "Direction.h"
#include <string>
class Room;

class Path {
public:
	Path(Room* origin, Room* destination, const char* name);
	Path(Room* origin, Room* destination, const char* name, const char* description);
	virtual ~Path();

	inline const std::string& getName() const {
		return name;
	}
	inline const std::string& getDescription() const {
		return description;
	}

	virtual const std::string look(const Room* origin) const;
	virtual Room* go(const Room* origin) const;
	virtual const bool open(); //give the inventory to check if he have the objects needed

private:
	Room* origin;
	Room* destination;
	const std::string description;
	const std::string name;

protected:
	bool opened;
};
#endif /* _PATH_H_ */
