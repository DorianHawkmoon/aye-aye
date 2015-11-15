#include "Inventory.h"
#include <sstream>
#include "Utilities.h"
#include "Entity.h"
#include <algorithm>


Inventory::Inventory() {}


Inventory::~Inventory() {}

const std::string Inventory::see(const std::string& name) const {
	//TODO: buscar objeto y mostrar
	return "see what?";
}

const std::string Inventory::open(const std::string& name, const std::list<Entity*>& openItems) {
	//TODO: buscar objeto y abrir
	return std::string();
}

Entity * Inventory::getItem(const std::string& name) {
	Entity* result = nullptr;

	std::list<Entity*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](Entity* item) { //given the direction, check if this concrete exit is found
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
	}

	return result;
}

const std::string Inventory::storeItem(Entity* item) {
	//TODO: mejorar lo que devuelve
	//Entity* previousItem = getItem(item->getName());
	//if (previousItem == nullptr) {
		items.push_back(item);
	/*} else {
	    previousItem->addItem();
		delete item;
	}*/
	return "Taken";
}

Entity * Inventory::takeOutItem(const std::string name) {
	Entity* result = nullptr;

	std::list<Entity*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](Entity* item) { //given the direction, check if this concrete exit is found
		return Utilities::compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		//TODO: controlar cuando quiero sólo una cantidad o varias
		result = *resultIt;
		//erase the pointer in the list (but it doesn't delete the object)
		items.erase(resultIt);
	}

	return result;
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
			if (count == size && count>1) {
				result << " and";
			}
			result << " " << \
				//Utilities::numberToString(item->getCount()) << " " << 
				item->getName();

			if (count == size) {
				result << "." << std::endl;
			} else {
				result << ",";
			}
		}

		return result.str();
}
