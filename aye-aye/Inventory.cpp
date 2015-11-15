#include "Inventory.h"
#include <sstream>
#include "Utilities.h"
#include <algorithm>


Inventory::Inventory() {}


Inventory::~Inventory() {}

const std::string Inventory::see(const std::vector<std::string>& arguments) const {
	unsigned int size = arguments.size();
	if (size < 2) {
		return "See what?";
	} else if (Utilities::compareTo(arguments[1], name)) {
		return look();
	} else {
		//search the entity
		Entity* entity = getEntity(arguments[1]);
		if (entity == nullptr) {
			return "See what?";
		}
		return entity->see(arguments);
	}
}

const std::string Inventory::open(const std::vector<std::string>& arguments, const std::list<Entity*>& openItems) {
	if (arguments.size() < 2) {
		return "Open what?";
	} else {
		Entity* entity = getEntity(arguments[1]);
		(entity == nullptr) ? "Open what?" : entity->open(arguments, openItems);
	}
	return std::string();
}

//drop deja el objeto en el inventario (no dentro de otro objeto, asi que dará igual si especifica otro sitio
const std::pair<bool, std::string> Inventory::drop(const std::vector<std::string>& arguments, Entity * item) {
	//TODO: controlar cantidades
	//Entity* previousItem = getItem(item->getName());
	//if (previousItem == nullptr) {
	items.push_back(item);
//} else {
//	previousItem->addItem();
//	delete item;
//}
	std::pair<bool, std::string> result;
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

const std::string Inventory::storeItem(Entity* item) {
	items.push_back(item);
	return "Taken";
}

const std::string Inventory::look() const {
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
		result << " " << item->look();

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
