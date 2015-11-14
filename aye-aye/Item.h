#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include "Entity.h"
#include <list>

class Item : public Entity {
public:
	Item(const char* name, const char* description);
	Item(const Item& item);
	virtual ~Item();

	virtual const std::string look() const;
	virtual const Entity* getEntity(const std::string& name);
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems);

	
	inline const std::string& getDescription() const {
		return description;
	}
	inline const std::string& getName() const {
		return name;
	}

	inline void addItem() {
		++count;
	}
	inline void substractItem() {
		--count;
	}
	const bool addItem(unsigned int value);
	const bool substractItem(unsigned int value);

	inline const unsigned int getCount() const {
		return count;
	}

protected:
	const static unsigned int MAX_ITEMS=10;
	const std::string description;
	const std::string name;
	unsigned int count;
};


#endif // ! _ITEM_H_