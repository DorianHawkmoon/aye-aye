#include "SidePath.h"
#include "Path.h"

SidePath::SidePath(Room* room, const Direction& direction, Path* parent)
	: origin(room), direction(direction), parent(parent), opened(true) {}


SidePath::~SidePath() {}

const std::string SidePath::getName() const {
	return parent->getName();
}

const std::string SidePath::open(const std::list<Item*>& openItems) {
	return parent->open(this, openItems);
}

Room * SidePath::go() const {
	return parent->go(this);
}

const std::string SidePath::look() const {
	return parent->look(this);
}

const Entity * SidePath::getEntity(const std::string & name) {
	return nullptr;
}

const std::string SidePath::see(const std::vector<std::string>& arguments) const {
	return parent->see(this);
}

const std::string SidePath::open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems) {
	return parent->open(this, openItems);
}


