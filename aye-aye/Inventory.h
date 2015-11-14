#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <list>
class Item;

class Inventory {
public:
	Inventory();
	virtual ~Inventory();

	const std::string look() const;

	Item* getItem(const std::string name);
	const std::string storeItem(Item* item);
	Item* takeOutItem(const std::string name);
	const std::string look();

private:
	std::list<Item*> items;
};

#endif // ! _INVENTORY_H_