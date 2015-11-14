#pragma once
#ifndef _SIMPLE_LOCK_H_
#define _SIMPLE_LOCK_H_

#include "Path.h"

class SimpleLock : public Path{
public:
	SimpleLock(Room* origin, const Direction& directionOrigin,
		Room* destination, const Direction& directionDestination,
		const char* name, const bool opened,
		const char* descriptionOpened, const char* descriptionClosed, 
		const char* descriptionOpening, const char* descriptionClosing);
	virtual ~SimpleLock();

	const std::string look(const SidePath* origin) const;
	virtual const std::string see(const SidePath* origin) const;
	virtual const std::string open(const SidePath* origin, const std::list<Item*>& openItems);
	Room* go(const SidePath* origin) const;

private:
	const std::list<const Item*> needed;
	const std::string descriptionOpened;
	const std::string descriptionClosed;
	const std::string descriptionOpening;
	const std::string descriptionClosing;
};

#endif // ! _SIMPLE_LOCK_H