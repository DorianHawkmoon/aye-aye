#pragma once
#ifndef _ONE_WAY_LOCK_H_
#define _ONE_WAY_LOCK_H_

#include "Path.h"

class OneWayLock : public Path{
public:
	OneWayLock(Room* origin, Room* destination, const char* description);
	virtual ~OneWayLock();
};

#endif // ! _ONE_WAY_LOCK_H_