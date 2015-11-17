#pragma once
#ifndef _CRIATURE_H_
#define _CRIATURE_H_

#include "Entity.h"
#include "Inventory.h"
#include <vector>
#include <string>

class Room;
class Armor;
class Weapon;

class Creature : public Entity {
public:
	Creature(const char* name, const char * description, const int life, const int baseAttack=1, const int baseDefense=0, const TypeEntity& type=CREATURE);
	virtual ~Creature();

	const bool isAlive() const;
	//how damage it receive (will be modified by armor)
	const std::string damage(const int damage);
	//how much will recove
	void recove(const int recove);
	//its attack, modified by armor
	const int hit() const;

	virtual const std::string equip(const std::vector<std::string>& arguments);
	virtual const std::string unequip(const std::vector<std::string>& arguments);
	virtual void autoEquip();
	const std::string stats() const;
	const std::list<Entity*> getInventory();

	const std::string getDescription() const;

	virtual const std::string look(const std::vector<std::string>& arguments) const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity* item);
	virtual Entity* take(const std::string& name);
	virtual const std::string go(const std::vector<std::string>& arguments);
	virtual const std::string take(const std::vector<std::string>& arguments);

private:
	int life;
	const int maxLife;
	const int baseAttack;
	const int baseDefense;
	Armor* armor;
	Weapon* weapon;

private:
	void dead();

protected:
	//list of object (inventary)
	Inventory inventory;
};

#endif // ! _CRIATURE_H_