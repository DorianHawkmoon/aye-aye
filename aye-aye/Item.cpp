#include "Item.h"
#include "Utilities.h"
#include "Inventory.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Item::Item(const char * name, const char * description, const TypeItem type, const unsigned int count)
	:Entity(name, description, TypeEntity::ITEM), count(count), opened(false), container(false), canTaked(true), typeItem(type) {}

Item::Item(const Item & item) : Entity(item), count(item.count), opened(item.opened), typeItem(item.typeItem) {

}

Item::~Item() {
	//delete all items it owns
	std::list<Entity*>::iterator it = items.begin();
	while (it != items.end()) {
		delete *it;
		it = items.erase(it);
	}
}

const std::string Item::look(const std::vector<std::string>& arguments) const {
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
		//tell all items
		for (const Entity* entity : items) {
			++count;
			if (count == size  && count > 1) {
				result << " and";
			}
			result << " " << entity->look(arguments);

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
		//tell every item
		for (const Entity* entity : items) {
			++count;
			if (count == size  && count > 1) {
				result << " and";
			}
			//use of look for not going to deeper and avoid circular petitions
			result << " " << entity->look(arguments);

			if (count != size) {
				result << ",";
			}
		}
	}
	return result.str();
}

const std::string Item::open(const std::vector<std::string>& arguments, const Inventory * openItems) {
	//TODO aquí es donde seguramente tenga que vigilar cuando enciendo luces y similares 
	//para establecer si algo se ve o no. Pendiente de implementar
	if (container) {
		if (opened) {
			return "Is already opened";
		} else if (needed.size() == 0) {
			opened = true;
			return std::string(this->name + " opened");
		} else if (openItems!=nullptr && Utilities::matchNeeded(needed, openItems)) {
			opened = true;
			return std::string(this->name + " opened");
		} else {
			return "Can't open, you need something for this";
		}
	} else {
		return "There's nothing to open";
	}
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

		//it found...
		if (resultIt != items.end()) {
			result = *resultIt;
			if (result->getType()==ITEM && ((Item*) result)->canTake()) {
				items.erase(resultIt);
			} else {
				result = nullptr;
				std::cout << std::endl << "Can't take it" << std::endl;
			}

		//search inside other items
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
	//TODO reacción de abrir sacos, pero también de encender luces, la mesa... no puedo usar container sin más
	if (container) {
		if (!opened) {
			return "Is already closed";
		} else if (needed.size() == 0) {
			opened = true;
			return std::string(this->name + " closed");
		} else if (closeItems != nullptr && Utilities::matchNeeded(needed, closeItems)) {
			opened = true;
			return std::string(this->name + " closed");
		} else {
			return "Can't close, you need something for this";
		}
	} else {
		return "There's nothing to close";
	}
	return std::string();
}

const std::string Item::go(const std::vector<std::string>& arguments) {
	//TODO: make items move between rooms ;P
	return std::string("An item can't go anywhere!");
}

const std::string Item::take(const std::vector<std::string>& arguments) {
	return "An item can't take anything!";
}
/*
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
*/
const std::pair<bool, std::string> Item::storeItem(Entity * item) {
	std::pair<bool, std::string> result;
	result.first = false;
	if (item == nullptr) {
		result.second = "Drop what?";
	}

	if (!container) {
		result.second = "Can't drop " + item->getName() + " into " + this->getName();
		return result;
	}
	
	items.push_back(item);
	item->changeParent(this);

	result.first = true;
	result.second = "Dropped into " + this->getName();
	return result;
}

void Item::addItemNeeded(const Entity * key) {
	needed.push_back(key);
}