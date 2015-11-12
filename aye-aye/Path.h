#pragma once
#ifndef _PATH_H_
#define _PATH_H_

#include "Direction.h"
#include <string>
class Room;

class Path {
public:
	Path(Room* origin, Room* destination);
	virtual ~Path();

	virtual Room* go(const Room* origin) const;
	virtual bool open(); //give the inventory to check if he have the objects needed

private:
	Room* origin;
	Room* destination;

protected:
	bool opened;
};
#endif /* _PATH_H_ */
