#pragma once
#ifndef _DIRECTION_H_
#define _DIRECTION_H_

#include <string>
#include "Utilities.h"

enum Direction {
	NORTH=0,
	SOUTH,
	WEST,
	EAST,
	UP,
	DOWN,
	NOWHERE
};

namespace Directions {
	inline const char* toString(const Direction dir) {
		switch (dir) {
			case NORTH:
				return "north";
			case SOUTH:
				return "south";
			case WEST:
				return "west";
			case EAST:
				return "east";
			case UP:
				return "up";
			case DOWN:
				return "down";
			default:
				return "nowhere";
		}
	}

	inline const Direction toDirection(const std::string& dir) {
		if (Utilities::compareTo(dir, "north")) return NORTH;
		if (Utilities::compareTo(dir, "south")) return SOUTH;
		if (Utilities::compareTo(dir, "east")) return EAST;
		if (Utilities::compareTo(dir, "west")) return WEST;
		if (Utilities::compareTo(dir, "up")) return UP;
		if (Utilities::compareTo(dir, "down")) return DOWN;

		return NOWHERE;
	}
}
#endif // ! _DIRECTION_H_