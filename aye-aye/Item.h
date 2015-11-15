#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include "Entity.h"
#include <list>

class Item : public Entity {
public:
	Item(const char* name, const char* description, const unsigned int count=1);
	Item(const Item& item);
	virtual ~Item();

	virtual const std::string look() const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity * item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);

	inline const bool isOpened() const {
		return opened;
	}
	inline void setOpened(const bool opened) {
		this->opened = opened;
	}

	inline const bool isContainer() const {
		return container;
	}
	inline void setContainer(const bool isContainer) {
		container = isContainer;
	}

	inline const bool canTake() const {
		return canTaked;
	}
	inline void setCanTake(const bool canTake) {
		canTaked = canTake;
	}

	const bool addItem(unsigned int value=1);
	const bool substractItem(unsigned int value=1);
	inline const unsigned int getCount() const {
		return count;
	}

private:
	unsigned int count;
	std::list<Entity*> items;
	bool opened;
	bool container;
	bool canTaked;

private:
	const std::pair<bool, std::string> storeItem(Entity* item);
};


#endif // ! _ITEM_H_