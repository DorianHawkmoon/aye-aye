#pragma once
#ifndef _SIMPLE_LOCK_H_
#define _SIMPLE_LOCK_H_

#include "Path.h"
class Entity;
class Inventory;

class SimpleLock : public Path {
public:
	SimpleLock(Room* origin, const Direction& directionOrigin,
		Room* destination, const Direction& directionDestination,
		const char* name, const bool opened,
		const char* descriptionOpened, const char* descriptionClosed, 
		const char* descriptionOpening, const char* descriptionClosing);

	virtual ~SimpleLock();

	void addItemNeeded(const Entity* key);

	virtual const std::string look(const SidePath* origin) const;
	virtual const std::string see(const SidePath* origin) const;
	virtual const std::string open(SidePath* origin, const Inventory * openItems);
	virtual const std::string close(SidePath* origin, const Inventory* closeItems);
	Room* go(const SidePath* origin) const;

private:
	std::list<const Entity*> needed;
	const std::string descriptionOpened;
	const std::string descriptionClosed;
	const std::string descriptionOpening;
	const std::string descriptionClosing;
};

#endif // ! _SIMPLE_LOCK_H