#include "SidePath.h"
#include "Path.h"

SidePath::SidePath(Room* room, const Direction& direction, Path* parent)
	: origin(room), direction(direction), parent(parent), opened(true) {}


SidePath::~SidePath() {}

const std::string& SidePath::getName() const {
	return parent->getName();
}

Room * SidePath::go() const {
	return parent->go(this);
}

const std::string SidePath::look() const {
	return parent->look(this);
}

Entity * SidePath::getEntity(const std::string & name) const {
	//Its myself?
	if (Utilities::compareTo(getName(), name)) {
		return const_cast<SidePath*>(this);
	} else {
		return nullptr;
	}
}

const std::string SidePath::see(const std::vector<std::string>& arguments) const {
	return parent->see(this);
}

const std::string SidePath::open(const std::vector<std::string>& arguments, const std::list<Entity*>& openItems) {
	return parent->open(this, openItems);
}

const std::string SidePath::drop(const std::vector<std::string>& arguments, Entity* item) {
	return "You can't drop anything here";
}

Entity * SidePath::take(const std::string & name) {
	return nullptr;
}


