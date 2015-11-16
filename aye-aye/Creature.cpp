#include "Creature.h"
#include "Utilities.h"
#include "Direction.h"
#include "Room.h"
#include <sstream>
#include <iostream>
#include <assert.h>

Creature::Creature(const char* name, const char * description, const int life, const int baseAttack, const int baseDefense, const TypeEntity& type)
	: Entity(name, description, type), life(life), maxLife(life), baseAttack(baseAttack), baseDefense(baseDefense) {}

Creature::~Creature() {
}

const bool Creature::isAlive() const {
	return life > 0;
}

void Creature::damage(const int damage) {
	//TODO: substract the armor
	life -= damage;
}

void Creature::recove(const int recove) {
	life += recove;
	if (life > maxLife) {
		life = maxLife;
	}
}

bool Creature::equip(const std::vector<std::string>& arguments) {
	//TODO equip
	return false;
}

bool Creature::unEquip(const std::vector<std::string>& arguments) {
	//TODO unequip
	return false;
}

bool Creature::autoEquip() {
	//TODO autoequip
	return false;
}

bool Creature::attack(const std::vector<std::string>& arguments) {
	//TODO attack
	return false;
}

const std::string Creature::stats() const {
	std::stringstream result;
	result << this->name << std::endl;
	result << "Life: " << life << "/" << maxLife << std::endl;

	result << "Strength: " << baseAttack << " + " <<
		((weapon != nullptr) ? weapon->getDescription() : "no weapon")
		<< std::endl;

	result << "Defense: " << baseAttack << " + " <<
		((armor != nullptr) ? armor->getDescription() : "no armor")
		<< std::endl;
	
	return result.str();
}

const std::string Creature::look(const std::vector<std::string>& arguments) const {
	//TODO y si me pide mirarme a mi mismo?
	if (arguments.size() > 1 && Utilities::compareTo(arguments[1], "inventory")) {
		return inventory.look(arguments);
	} else {
		return parent->look(arguments);
	}
}

Entity * Creature::getEntity(const std::string & name) const {
	return nullptr;
}

const std::string Creature::see(const std::vector<std::string>& arguments) const {
	//look a concrete object
	unsigned int size = arguments.size();
	if ((size > 2 && Utilities::compareTo(arguments[2], "inventory")) //see X inventory
		|| (size > 3 && Utilities::compareTo(arguments[3], "inventory"))) { //see X in inventory

		return inventory.see(arguments);
	}


	if (Utilities::compareTo(arguments[1], "room") || arguments.size() == 1) {
		return parent->look(arguments);
	} else {
		return parent->see(arguments);
	}
	//TODO y si me pide mirarme a mi mismo?
}

const std::string Creature::open(const std::vector<std::string>& arguments, const Inventory * openItems) {
	if (arguments.size() < 2) {
		return "Open what?";
	}
	const Inventory* inv = &inventory;
	return parent->open(arguments, inv);
}

const std::string Creature::close(const std::vector<std::string>& arguments, const Inventory * closeItems) {
	if (arguments.size() < 2) {
		return "Close what?";
	}
	const Inventory* inv = &inventory;
	return parent->close(arguments, inv);
}

const std::pair<bool, std::string> Creature::drop(const std::vector<std::string>& arguments, Entity * item) {
	std::pair<bool, std::string> result;
	if (arguments.size() < 2) {
		result.first = false;
		result.second = "Drop what?";
	} else {
		Entity* itemInventory = inventory.getEntity(arguments[1]);
		if (itemInventory == nullptr) {
			result.first = false;
			result.second = "Drop what?";
		} else {
			result = parent->drop(arguments, itemInventory);
			if (result.first) {
				inventory.take(arguments[1]);
			}
		}
	}
	return result;
}

Entity * Creature::take(const std::string & name) {
	return parent->take(name);
}

const std::string Creature::take(const std::vector<std::string>& arguments) {
	if (arguments.size() < 2) {
		return "Take what?";
	}

	Entity* item = parent->take(arguments[1]);
	if (item == nullptr) {
		return std::string("There's nothing");
	} else {
		return inventory.drop(arguments, item).second;
	}
}

const std::string Creature::go(const std::vector<std::string>& arguments) {
	Direction direction = Directions::toDirection(arguments[1]);
	if (direction == NOWHERE) {
		return "Go where?";
	}

	assert(parent->getType() == ROOM);
	Room* origin = static_cast<Room*>(parent);
	Room* destiny = origin->go(direction);
	if (destiny != nullptr) {
		this->changeParent(destiny);
		return std::string(parent->getName() + '\n' + parent->getDescription());
	} else {
		return "I'm lost...";
	}
}
