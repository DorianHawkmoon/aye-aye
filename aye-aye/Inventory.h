#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <list>
class Entity;

class Inventory {
public:
	Inventory();
	virtual ~Inventory();

	Entity* getItem(const std::string& name);
	const std::string storeItem(Entity* item);
	Entity* takeOutItem(const std::string name);

	virtual const std::string look() const;
	virtual const std::string see(const std::string& name) const;
	virtual const std::string open(const std::string& name, const std::list<Entity*>& openItems);

private:
	std::list<Entity*> items;
};

#endif // ! _INVENTORY_H_