#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <list>
class Item;

class Inventory {
public:
	Inventory();
	virtual ~Inventory();

	Item* getItem(const std::string name);
	const std::string storeItem(Item* item);
	Item* takeOutItem(const std::string name);

	virtual const std::string look() const;
	virtual const std::string see(const std::string& name) const;
	virtual const std::string open(const std::string& name, const std::list<Item*>& openItems);

private:
	std::list<Item*> items;
};

#endif // ! _INVENTORY_H_