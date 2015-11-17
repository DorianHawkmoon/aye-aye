#pragma once
#ifndef _ONE_WAY_PATH_H_

#include "Path.h"



class IndependentWayPath :	public Path {
public:
	struct Side {
		std::string nameRoom;
		std::string descriptionOpened;
		std::string descriptionClosed;
		std::string descriptionOpening;
		std::string descriptionClosing;
		std::list<const Entity*> needed;
	};

	IndependentWayPath(const char* name, Room* origin, const Direction& directionOrigin, const Side& originInfo,
		Room* destination, const Direction& directionDestination, const Side& destinyInfo);
	virtual ~IndependentWayPath();

	virtual const std::string look(const SidePath* origin) const;
	virtual const std::string see(const SidePath* origin) const;
	virtual const std::string open(SidePath* origin, const Inventory * openItems);
	virtual const std::string close(SidePath* origin, const Inventory* closeItems);

	const SidePath* getOtherSide(const SidePath* origin) const;

private:
	Side originSide;
	Side destinySide;

private:
	const Side& getTheSide(const SidePath* origin) const;
};

#endif // ! _ONE_WAY_PATH_H_