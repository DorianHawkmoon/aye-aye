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

	const std::string storeItem(Entity* item);

	virtual const std::string look() const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity* item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);

private:
	std::list<Entity*> items;
};

#endif // ! _INVENTORY_H_