#pragma once
#ifndef _ONE_WAY_LOCK_H_
#define _ONE_WAY_LOCK_H_

#include "Path.h"

class OneWayLock : public Path{
public:
	OneWayLock();
	virtual ~OneWayLock();
};

#endif // ! _ONE_WAY_LOCK_H_