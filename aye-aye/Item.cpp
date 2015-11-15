#include "Item.h"
#include "Utilities.h"
#include <algorithm>
#include <sstream>

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
		result= const_cast<Item*>(this);
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

const std::string Item::open(const std::vector<std::string>& arguments, const std::list<Entity*>& openItems) {
	//TODO reacci�n de abrir sacos, pero tambi�n de encender luces, la mesa... no puedo usar container sin m�s
	return "There's nothing to open";
}

const std::string Item::drop(const std::vector<std::string>& arguments, Entity* item) {
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
			return "Drop where?"; 
		}

	} else if(!opened) {
		return "Can't drop here, is closed";
	} else {
		return storeItem(item);
	}
}

Entity * Item::take(const std::string & name) {
	Entity* result = nullptr;

	//its me?
	if (Utilities::compareTo(this->name, name)) {
		result= this;

	} else if(opened){
		for (std::list<Entity *>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
			result = (*it)->take(name);
		}
	}
	return result;
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

Entity * Item::getItem(const std::string name) {
	Entity* result = nullptr;

	std::list<Entity*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](Entity* item) {
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
	}

	return result;
}

const std::string Item::storeItem(Entity * item) {
	if (!container) {
		return "Can't drop " + item->getName() + " into " + this->getName();
	}
	//Entity* previousItem = getItem(item->getName());
	//if (previousItem == nullptr) {
		items.push_back(item);
	/*} else {
		previousItem->addItem();
		delete item;
	}*/
	return "Dropped into " + this->getName();
}

