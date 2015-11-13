#pragma once
#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <list>
class Item;

class Inventory {
public:
	Inventory();
	virtual ~Inventory();

private:
	std::list<Item*> items;
};

#endif // ! _INVENTORY_H_