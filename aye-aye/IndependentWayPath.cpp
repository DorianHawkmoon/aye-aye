#include "IndependentWayPath.h"
#include "SidePath.h"
#include "Room.h"
#include "Utilities.h"

IndependentWayPath::IndependentWayPath(const char* name, Room * origin, const Direction & directionOrigin, const Side & originInfo, Room * destination, const Direction & directionDestination, const Side & destinyInfo)
:Path(origin, directionOrigin, destination, directionDestination, name), originSide(originInfo), destinySide(destinyInfo) {
	this->origin->setOpened(false);
	this->destination->setOpened(false);
}

IndependentWayPath::~IndependentWayPath() {
}

const std::string IndependentWayPath::look(const SidePath * origin) const {
	const IndependentWayPath::Side side = getTheSide(origin);
	if (origin->isOpened()) {
		return side.descriptionOpened;
	} else {
		return side.descriptionClosed;
	}
}

const std::string IndependentWayPath::see(const SidePath * origin) const {
	const IndependentWayPath::Side side = getTheSide(origin);
	if (origin->isOpened()) {
		return side.descriptionOpened;
	} else {
		return side.descriptionClosed;
	}
}

const std::string IndependentWayPath::open(SidePath * origin, const Inventory * openItems) {
	IndependentWayPath::Side side = getTheSide(origin);

	if (side.needed.size()==0) {
		//no items needed
		if (origin->isOpened()) {
			return "Already opened";
		}
		origin->setOpened(true); //TODO: error bug, fix!
		return side.descriptionOpening;
	} else {
		//check the items
		if (Utilities::matchNeeded(side.needed, openItems)) {
			origin->setOpened(true);
			return side.descriptionOpening;
		} else {
			return "Is closed! You need something to open this.";
		}
	}
}

const std::string IndependentWayPath::close(SidePath * origin, const Inventory * closeItems) {
	IndependentWayPath::Side side = getTheSide(origin);

	if (side.needed.size() == 0) {
		//no items needed
		if (!origin->isOpened()) {
			return "Already closed";
		}
		origin->setOpened(false);
		return side.descriptionClosing;
	} else {
		//check the items
		if (Utilities::matchNeeded(side.needed, closeItems)) {
			origin->setOpened(false);
			return side.descriptionClosing;
		} else {
			return "Is still open. You need something to close this.";
		}
	}
}

const SidePath * IndependentWayPath::getOtherSide(const SidePath * origin) const {
	if (Utilities::compareTo(origin->getRoom()->getName(), this->originSide.nameRoom)) {
		return this->destination;
	} else {
		return this->origin;
	}
}

const IndependentWayPath::Side& IndependentWayPath::getTheSide(const SidePath * origin) const {
	if (Utilities::compareTo(origin->getRoom()->getName(), this->originSide.nameRoom)) {
		return this->originSide;
	} else {
		return this->destinySide;
	}
}
