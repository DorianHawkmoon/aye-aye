#include "Inventory.h"
#include <sstream>
#include "Utilities.h"
#include <algorithm>
#include "Item.h"

Inventory::Inventory(): Entity("","",INVENTORY) {}


Inventory::~Inventory() {
	//delete all items
	std::list<Entity*>::iterator it = items.begin();
	while (it != items.end()) {
		it = items.erase(it);
	}
}

const std::string Inventory::see(const std::vector<std::string>& arguments) const {
	unsigned int size = arguments.size();
	if (size < 2) {
		return "See what?";
	} else if (Utilities::compareTo(arguments[1], name)) {
		return look(arguments);
	} else {
		//search the entity
		Entity* entity = getEntity(arguments[1]);
		if (entity == nullptr) {
			return "See what?";
		}
		return entity->see(arguments);
	}
}

const std::string Inventory::open(const std::vector<std::string>& arguments, const Inventory * openItems) {
	if (arguments.size() < 2) {
		return "Open what?";
	} else {
		Entity* entity = getEntity(arguments[1]);
		return (entity == nullptr) ? "Open what?" : entity->open(arguments, openItems);
	}
}

//drop deja el objeto en el inventario (no dentro de otro objeto, asi que dará igual si especifica otro sitio
const std::pair<bool, std::string> Inventory::drop(const std::vector<std::string>& arguments, Entity * item) {
	std::pair<bool, std::string> result;
	if (item == nullptr) {
		result.first = false;
		result.second = "Take what?";
	}
	//TODO: controlar cantidades
	//Entity* previousItem = getItem(item->getName());
	//if (previousItem == nullptr) {
	items.push_back(item);
//} else {
//	previousItem->addItem();
//	delete item;
//}
	
	result.first = true;
	result.second = "Taken " + item->getName();
	return result;
}

//take saca un objeto del inventario (lo elimina del inventario)
Entity * Inventory::take(const std::string & name) {
	Entity* result = nullptr;

	std::list<Entity*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](const Entity* item) {
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
		items.erase(resultIt);
	} else {
		//search inside the items
		for (std::list<Entity*>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
			result = (*it)->take(name);
		}
	}

	return result;

}

const std::string Inventory::close(const std::vector<std::string>& arguments, const Inventory * closeItems) {
	if (arguments.size() < 2) {
		return "Close what?";
	} else {
		Entity* entity = getEntity(arguments[1]);
		return (entity == nullptr) ? "Close what?" : entity->close(arguments, closeItems);
	}
}

const std::string Inventory::go(const std::vector<std::string>& arguments) {
	return std::string("An inventory can't go anywhere!");
}

const std::string Inventory::take(const std::vector<std::string>& arguments) {
	return std::string("An inventory can't take anything!");
}

const std::string Inventory::look(const std::vector<std::string>& arguments) const {
	std::stringstream result;
	//add to description the description of objects
	unsigned int size;
	if (size = items.size()) {
		result << std::endl << "You have";
	} else {
		return "You have nothing";
	}
	unsigned int count = 0;
	for each(const Entity* item in items) {
		++count;
		if (count == size && count > 1) {
			result << " and";
		}
		result << " " << item->look(arguments);

		if (count == size) {
			result << "." << std::endl;
		} else {
			result << ",";
		}
	}

	return result.str();
}

Entity * Inventory::getEntity(const std::string & name) const {
	Entity* result = nullptr;

	for (std::list<Entity *>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
		result = (*it)->getEntity(name);
	}

	return result;
}

const std::pair<bool, std::string> Inventory::storeItem(Entity * item) {
	std::pair<bool, std::string> result;
	if (item == nullptr) {
		result.first = false;
		result.second = "Take what?";
	}
	//TODO: controlar cantidades
	//Entity* previousItem = getItem(item->getName());
	//if (previousItem == nullptr) {
	items.push_back(item);
	//} else {
	//	previousItem->addItem();
	//	delete item;
	//}

	result.first = true;
	result.second = "Taken " + item->getName();
	return result;
}

const Entity * Inventory::getWeapon(const std::string & name) const {
	Entity* entity = getEntity(name);
	if (entity->getType() == ITEM && ((Item*) entity)->getTypeItem() == WEAPON) {
		return entity;
	} else {
		return nullptr;
	}
}

const Entity * Inventory::getArmor(const std::string & name) const {
	Entity* entity = getEntity(name);
	if (entity->getType() == ITEM && ((Item*) entity)->getTypeItem() == ARMOR) {
		return entity;
	} else {
		return nullptr;
	}
}

const Entity * Inventory::getWeapon() const {
	Entity* result = nullptr;

	for (std::list<Entity *>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
		Entity* entity = (*it);
		if ((*it)->getType() == ITEM) {
			if (static_cast<Item*>(entity)->getTypeItem() == WEAPON) {
				result = entity;
			}
		}
	}

	return result;
}

const Entity * Inventory::getArmor() const {
	Entity* result = nullptr;

	for (std::list<Entity *>::const_iterator it = items.begin(); it != items.end() && result == nullptr; ++it) {
		Entity* entity = (*it);
		if ((*it)->getType() == ITEM) {
			if (static_cast<Item*>(entity)->getTypeItem() == ARMOR) {
				result = entity;
			}
		}
	}

	return result;
}
