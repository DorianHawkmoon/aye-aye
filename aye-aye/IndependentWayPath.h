#pragma once
#ifndef _ONE_WAY_PATH_H_

#include "Path.h"

struct Side {
	bool opened;
	const std::string nameRoom;
	const std::string descriptionOpened;
	const std::string descriptionClosed;
	const std::string descriptionOpening;
	const std::string descriptionClosing;
	std::list<const Entity*> needed;
};

class IndependentWayPath :	public Path {
public:
	struct Side {
		const std::string nameRoom;
		const std::string descriptionOpened;
		const std::string descriptionClosed;
		const std::string descriptionOpening;
		const std::string descriptionClosing;
		std::list<const Entity*> needed;
	};

	IndependentWayPath(const char* name, Room* origin, const Direction& directionOrigin, const Side& originInfo,
		Room* destination, const Direction& directionDestination, const Side& destinyInfo);
	virtual ~IndependentWayPath();

	virtual const std::string look(const SidePath* origin) const;
	virtual const std::string see(const SidePath* origin) const;
	virtual const std::string open(const SidePath* origin, const Inventory * openItems);
	virtual const std::string close(const SidePath* origin, const Inventory* closeItems);

private:
	Side originSide;
	Side destinySide;

private:
	const Side& getTheSide(const SidePath* origin) const;
};

#endif // ! _ONE_WAY_PATH_H_