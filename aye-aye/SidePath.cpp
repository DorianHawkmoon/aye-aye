#include "SidePath.h"
#include "Path.h"
#include "Inventory.h"

SidePath::SidePath(Room* room, const Direction& direction, Path* parent)
	: Entity("","",PATH), origin(room), direction(direction), parentPath(parent), opened(true) {
	
}


SidePath::~SidePath() {}

const std::string& SidePath::getName() const {
	return parentPath->getName();
}

Room * SidePath::go() const {
	return parentPath->go(this);
}

const SidePath * SidePath::getOtherSide() const {
	return parentPath->getOtherSide(this);
}

const std::string SidePath::look(const std::vector<std::string>& arguments) const {
	return parentPath->look(this);
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
	return parentPath->see(this);
}

const std::string SidePath::open(const std::vector<std::string>& arguments, const Inventory * openItems) {
	return parentPath->open(this, openItems);
}

const std::pair<bool, std::string> SidePath::drop(const std::vector<std::string>& arguments, Entity* item) {
	std::pair<bool, std::string> result;
	result.first = false;
	result.second = "You can't drop anything here";
	return result;
}

Entity * SidePath::take(const std::string & name) {
	return nullptr;
}

const std::string SidePath::close(const std::vector<std::string>& arguments, const Inventory * closeItems) {
	return parentPath->close(this, closeItems);
}

const std::string SidePath::go(const std::vector<std::string>& arguments) {
	return std::string("A path can't go anywhere!");
}

const std::string SidePath::take(const std::vector<std::string>& arguments) {
	return std::string("A path can't take anything!");
}


