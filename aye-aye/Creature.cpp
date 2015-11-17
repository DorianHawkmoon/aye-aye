#include "Creature.h"
#include "Utilities.h"
#include "Direction.h"
#include "Room.h"
#include <sstream>
#include <iostream>
#include "Armor.h"
#include "Weapon.h"
#include <assert.h>
#include "Fight.h"
#include "Food.h"
#include "SidePath.h"

Creature::Creature(const char* name, const char * description, const int life, const int baseAttack, const int baseDefense, const TypeEntity& type)
	: Entity(name, description, type), life(life), maxLife(life), baseAttack(baseAttack), baseDefense(baseDefense), weapon(nullptr), armor(nullptr) {}

Creature::~Creature() {}

const bool Creature::isAlive() const {
	return life > 0;
}

const std::string Creature::damage(const int damage) {
	int defense = baseDefense;

	if (armor != nullptr) {
		defense += armor->getDefense();
	}
	int totalDamage = damage - defense;
	if (totalDamage < 0) {
		totalDamage = 1; //always some damage
	}
	if (life >= totalDamage) {
		life = life - totalDamage;
	} else {
		life = 0;
	}
	
	std::stringstream result;
	result << "Damage by " << totalDamage << " points.";
	if (!isAlive()) {
		this->dead();
	}
	return result.str();
}

const std::string Creature::recove(const int recove) {
	life = life + recove;
	if (life > maxLife) {
		life = maxLife;
		return "Fully recovered!";
	} else {
		std::stringstream result;
		result << "Recovered " << recove << " points";
		return result.str();
	}
}

const int Creature::hit() const {
	unsigned int result = baseAttack;
	if (weapon != nullptr) {
		result = result + weapon->getHit();
	}
	return result;
}

const std::string Creature::equip(const std::vector<std::string>& arguments) {
	if (arguments.size() < 2) {
		return "Equip what?";
	}
	Item* item;
	Entity* entity = inventory.getEntity(arguments[1]);
	if (entity == nullptr) {
		return "Equip what?";
	} else if (entity->getType() != ITEM) {
		return "It's not a weapon or armor";
	} else {
		//get the item from the inventory
		entity = inventory.take(entity->getName());
		item = static_cast<Item*>(entity);
	}

	if (item->getTypeItem() == WEAPON) {
		if (weapon != nullptr) {
			//drop it to inventary
			inventory.storeItem(weapon);
		}
		weapon = static_cast<Weapon*>(item);
	} else {
		if (armor != nullptr) {
			//drop it to inventary
			inventory.storeItem(armor);
		}
		armor = static_cast<Armor*>(item);
	}
	return "Equiped " + item->getName();
}

const std::string Creature::unequip(const std::vector<std::string>& arguments) {
	if (arguments.size() < 2) {
		return "Equip what?";
	} else if (Utilities::compareTo(arguments[1], "weapon") || Utilities::compareTo(arguments[1], weapon->getName())) {
		inventory.storeItem(weapon);
		return "Unequiped";
	} else if (Utilities::compareTo(arguments[1], "armor") || Utilities::compareTo(arguments[1], armor->getName())) {
		inventory.storeItem(armor);
		return "Unequiped";
	} else {
		return "Unequip what?";
	}
}

void Creature::autoEquip() {
	Entity* entity = const_cast<Entity*>(inventory.getWeapon()); // remove the const modifier
	//its true the object will not be modified, but because of changes between pointers and
	//the methods of inventory does not admit const, we need this conversion
	if (entity != nullptr) {
		weapon = static_cast<Weapon*>(entity);
	}

	entity = const_cast<Entity*>(inventory.getArmor());
	if (entity != nullptr) {
		armor = static_cast<Armor*>(entity);
	}
}

const std::string Creature::stats() const {
	std::stringstream result;
	result << this->name << std::endl;
	result << "Life: " << life << "/" << maxLife << std::endl;

	result << "Strength: " << baseAttack << " + " <<
		((weapon != nullptr) ? weapon->getDescription() : "no weapon")
		<< std::endl;

	result << "Defense: " << baseDefense << " + " <<
		((armor != nullptr) ? armor->getDescription() : "no armor")
		<< std::endl;

	return result.str();
}

const std::list<Entity*> Creature::getInventory() {
	return inventory.getInventory();
}

const std::string Creature::eat(const std::vector<std::string>& arguments) {
	if (arguments.size() < 2) {
		return "Eat what?";
	} else {
		Entity* entity=inventory.getEntity(arguments[1]);
		if (entity == nullptr) {
			return "Eat what?";
		} else if (entity->getType() != ITEM || (static_cast<Item*>(entity))->getTypeItem()!=FOOD) {
			return "I can't eat that";
		} else {
			Food* food=static_cast<Food*>(entity);
			return recove(food->getRecover());
		}
	}
}

const std::string Creature::getDescription() const {
	if (isAlive()) {
		return this->description;
	} else {
		return this->description + "(dead)";
	}
}

const std::string Creature::look(const std::vector<std::string>& arguments) const {
	//the problems is when look in a room, without asking for any particular, may ask for this entities
	//solved in class room, detecting the creature class and asking personally
	unsigned int size = arguments.size();
	if (size > 1 && Utilities::compareTo(arguments[1], "inventory")) {
		return inventory.look(arguments);
	} else if (size > 1 && Utilities::compareTo(arguments[1], this->getName())) {
		if (isAlive()) {
			return this->stats();
		} else {
			return this->getDescription();
		}
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

	} else if (size <= 1) {
		return parent->look(arguments);

	} else if (Utilities::compareTo(arguments[1], this->getName())) {
		return this->stats();

	} else {
		return parent->see(arguments);
	}
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

void Creature::dead() {
	const std::vector<std::string> args = {"unequip", "weapon"};
	unequip(args);
	const std::vector<std::string> args2={"unequip", "weapon"};
	unequip(args2);
}

const std::string Creature::go(const std::vector<std::string>& arguments) {
	Direction direction = Directions::toDirection(arguments[1]);
	if (direction == NOWHERE) {
		return "Go where?";
	}

	assert(parent->getType() == ROOM);

	Room* origin = static_cast<Room*>(parent);
	Room* destiny = origin->go(direction);
	//TODO: here check if has combat
	if (destiny != nullptr) {
		this->changeParent(destiny);

		//check if enemies...
		std::list<Creature*> enemies = destiny->getEnemies();
		if (enemies.size() > 0) {
			//get the side of running away
			const SidePath* originSide = origin->getPath(direction);
			assert(originSide);
			const SidePath* escapeSide=originSide->getOtherSide();

			//test if I can go by this side (is still opened behind me)
			bool canEscape = escapeSide->go() != nullptr;

			Fight combat(const_cast<Creature*>(this), enemies, canEscape);
			bool result=combat.fight();
			if (!result) {
				//running away...
				this->changeParent(origin); //coming back to the room
				return "You escaped and come back to the previous site";
			}
		} else {
			return std::string(parent->getName() + '\n' + parent->getDescription());
		}
	}
	return std::string();
}
