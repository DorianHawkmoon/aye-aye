#include "Item.h"
#include "Utilities.h"
#include "Inventory.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Item::Item(const char * name, const char * description, const unsigned int count)
	:Entity(name, description), count(count), opened(false), container(false), canTaked(true) {}

Item::Item(const Item & item) : Entity(item), count(item.count), opened(item.opened) {

}

Item::~Item() {}

const std::string Item::look() const {
	std::stringstream result;
	result << Utilities::numberToString(count) + " " + name;
	//add to description the description of objects if the item is open
	if (opened) {
		unsigned int size;
		if (size = items.size()) {
			if (size == 1) {
				result << " in which there is";
			} else {
				result << " in which there are";
			}
		}
		unsigned int count = 0;
		for each(const Entity* entity in items) {
			++count;
			if (count == size  && count > 1) {
				result << " and";
			}
			result << " " << entity->look();

			if (count != size) {
				result << ",";
			}
		}
	}
	return result.str();

}

Entity * Item::getEntity(const std::string & name) const {
	Entity* result = nullptr;
	if (Utilities::compareTo(this->name, name)) {
		result = const_cast<Item*>(this);
	} else {
		//search inside if opened
		if (opened) {
			for (std::list<Entity *>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
				result = (*it)->getEntity(name);
			}
		}
	}
	return result;
}

const std::string Item::see(const std::vector<std::string>& arguments) const {
	std::stringstream result;
	result << Utilities::numberToString(count) + " " + description;
	//add to description the description of objects if the item is open
	if (opened) {
		unsigned int size;
		if (size = items.size()) {
			if (size == 1) {
				result << " in which there is";
			} else {
				result << " in which there are";
			}
		}
		unsigned int count = 0;
		for each(const Entity* entity in items) {
			++count;
			if (count == size  && count > 1) {
				result << " and";
			}
			result << " " << entity->look();

			if (count != size) {
				result << ",";
			}
		}
	}
	return result.str();
}

const std::string Item::open(const std::vector<std::string>& arguments, const Inventory * openItems) {
	//TODO reacción de abrir sacos, pero también de encender luces, la mesa... no puedo usar container sin más
	return "There's nothing to open";
}

const std::pair<bool, std::string> Item::drop(const std::vector<std::string>& arguments, Entity* item) {
	//drop X in/into/... Y
	//drop X Y
	unsigned int size = arguments.size();
	if (size > 2) {
		//get the name
		std::string into((size > 3) ? arguments[3] : arguments[2]);

		if (Utilities::compareTo(this->name, into)) {
			//its me
			return storeItem(item);
		} else {
			//it's not me, get the item into store if opened
			if (opened) {
				Entity* itemInto = getEntity(into);
				if (itemInto != nullptr) {
					return itemInto->drop(arguments, item);
				}
			}
			//I ask because if is not opened, don't know why I'm asking this item so probably is a mistake due to a misunderstanding and not because the item is closed
			std::pair<bool, std::string> result;
			result.first = false;
			result.second = "Drop where?";
			return result;
		}

	} else if (!opened) {
		std::pair<bool, std::string> result;
		result.first = false;
		result.second = "Can't drop here, is closed";
		return result;
	} else {
		return storeItem(item);
	}
}

Entity * Item::take(const std::string & name) {
	Entity* result = nullptr;

	if (opened) {
		std::list<Entity*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
			[&name](const Entity* item) {
			return Utilities::compareTo(item->getName(), name);
		});

		if (resultIt != items.end()) {

			result = *resultIt;
			if (((Item*) result)->canTake()) {
				items.erase(resultIt);
			} else {
				result = nullptr;
				std::cout << std::endl << "Can't take it" << std::endl;
			}

		} else {
			//search inside the items
			for (std::list<Entity*>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
				result = (*it)->take(name);
			}
		}

	}
	return result;
}

const std::string Item::close(const std::vector<std::string>& arguments, const Inventory * closeItems) {
	//TODO
	return std::string();
}

const bool Item::addItem(unsigned int value) {
	count += value;
	return true;
}

const bool Item::substractItem(unsigned int value) {
	if (count >= value) {
		count -= value;
		return true;
	} else {
		return false;
	}
}

const std::pair<bool, std::string> Item::storeItem(Entity * item) {
	std::pair<bool, std::string> result;
	if (!container) {
		result.first = false;
		result.second = "Can't drop " + item->getName() + " into " + this->getName();
		return result;
	}
	//Entity* previousItem = getItem(item->getName());
	//if (previousItem == nullptr) {
	items.push_back(item);
/*} else {
	previousItem->addItem();
	delete item;
}*/
	result.first = true;
	result.second = "Dropped into " + this->getName();
	return result;
}

