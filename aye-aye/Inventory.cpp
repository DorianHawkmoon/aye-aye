#include "Inventory.h"
#include <sstream>
#include "Utilities.h"
#include "Item.h"
#include <algorithm>


Inventory::Inventory() {}


Inventory::~Inventory() {}

const std::string Inventory::look() const {
	std::stringstream result;

	unsigned int size;
	if (size = items.size()) {
		result << std::endl << "There are";
	} else {
		return "You have nothing";
	}
	unsigned int count = 0;
	for each(const Item* item in items) {
		++count;
		if (count == size) {
			result << " and";
		}
		result << " " << numberToString(item->getCount()) << " " << item->getName();

		if (count == size) {
			result << "." << std::endl;
		} else {
			result << ",";
		}
	}

	return result.str();
}

Item * Inventory::getItem(const std::string name) {
	Item* result = nullptr;

	std::list<Item*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](Item* item) { //given the direction, check if this concrete exit is found
		return compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		result = *resultIt;
	}

	return result;
}

const std::string Inventory::storeItem(Item * item) {
	//TODO: mejorar lo que devuelve
	Item* previousItem = getItem(item->getName());
	if (previousItem == nullptr) {
		items.push_back(item);
	} else {
		previousItem->addItem();
		delete item;
	}
	return "stored";
}

Item * Inventory::takeOutItem(const std::string name) {
	Item* result = nullptr;

	std::list<Item*>::const_iterator resultIt = std::find_if(items.begin(), items.end(),
		[&name](Item* item) { //given the direction, check if this concrete exit is found
		return compareTo(item->getName(), name);
	});

	if (resultIt != items.end()) {
		//TODO: controlar cuando quiero sólo una cantidad o varias
		result = *resultIt;
		//erase the pointer in the list (but it doesn't delete the object)
		items.erase(resultIt);
	}

	return result;
}

const std::string Inventory::look() {
	std::stringstream result;
	//add to description the description of objects
	unsigned int size;
	if (size = items.size()) {
		result << std::endl << "You have";
	}
	unsigned int count = 0;
	for each(const Item* item in items) {
		++count;
		if (count == size && count>1) {
			result << " and";
		}
		result << " " << numberToString(item->getCount()) << " " << item->getName();

		if (count == size) {
			result << "." << std::endl;
		} else {
			result << ",";
		}
	}
	return result.str();
}
