#pragma once
#ifndef _SIMPLE_LOCK_H_
#define _SIMPLE_LOCK_H_
#include "Path.h"

class SimpleLock : public Path{
public:
	SimpleLock(Room* origin, Room* destination, const bool opened, 
		const char* descriptionOpened, const char* descriptionClosed, 
		const char* descriptionOpening, const char* descriptionClosing);
	virtual ~SimpleLock();
	virtual const std::string look(const Room* origin) const;
	virtual const bool open();
private:
	const std::string descriptionOpened;
	const std::string descriptionClosed;
	const std::string descriptionOpening;
	const std::string descriptionClosing;
};

#endif // ! _SIMPLE_LOCK_H