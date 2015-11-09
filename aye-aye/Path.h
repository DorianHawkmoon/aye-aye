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

	Room* go(const Room* origin) const;

private:
	Room* origin;
	Room* destination;
};
#endif /* _PATH_H_ */
