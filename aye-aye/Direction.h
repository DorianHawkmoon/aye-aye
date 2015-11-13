#pragma once
#ifndef _DIRECTION_H_
#define _DIRECTION_H_

enum Direction {
	NORTH=0,
	SOUTH,
	WEST,
	EAST,
	UP,
	DOWN
};

inline const char* toString(Direction dir) {
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

#endif // ! _DIRECTION_H_