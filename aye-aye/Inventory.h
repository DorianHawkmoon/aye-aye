#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <list>
#include <vector>
#include "Entity.h"

class Inventory : public Entity {
public:
	Inventory();
	virtual ~Inventory();

	const std::pair<bool, std::string> storeItem(Entity * item);
	//get the weapon (no delete from inventory)
	const Entity* getWeapon(const std::string& name) const;
	//ge the armor (no delete from inventory)
	const Entity* getArmor(const std::string& name) const;
	//get the first weapon it find
	const Entity* getWeapon() const;
	//get the first armor it find
	const Entity* getArmor() const;
	//get the list of entity of the inventory (used to drop items when a creature defeat)
	const std::list<Entity*> getInventory();

	//method override from entity
	virtual const std::string look(const std::vector<std::string>& arguments) const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity* item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);
	const std::string go(const std::vector<std::string>& arguments);
	virtual const std::string take(const std::vector<std::string>& arguments);

private:
	std::list<Entity*> items;
};

#endif // ! _INVENTORY_H_