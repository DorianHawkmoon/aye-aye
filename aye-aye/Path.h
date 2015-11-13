#pragma once
#ifndef _PATH_H_
#define _PATH_H_

#include "Direction.h"
#include <string>
class Room;

class Path {
public:
	Path(Room* origin, Room* destination);
	Path(Room* origin, Room* destination, const char* description);
	virtual ~Path();

	virtual const std::string look(const Room* origin) const;
	virtual Room* go(const Room* origin) const;
	virtual const bool open(); //give the inventory to check if he have the objects needed

private:
	Room* origin;
	Room* destination;
	const std::string description;

protected:
	bool opened;
};
#endif /* _PATH_H_ */
