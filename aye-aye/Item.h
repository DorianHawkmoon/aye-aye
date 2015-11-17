#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include "Entity.h"
#include <list>

enum TypeItem {
	NORMAL_ITEM,
	WEAPON,
	ARMOR,
	FOOD
};

class Item : public Entity {
public:
	Item(const char* name, const char* description, const TypeItem type = NORMAL_ITEM, const unsigned int count = 1);
	Item(const Item& item);
	virtual ~Item();

	//methods override of entity
	virtual const std::string look(const std::vector<std::string>& arguments) const;
	virtual Entity* getEntity(const std::string& name) const;
	virtual const std::string see(const std::vector<std::string>& arguments) const;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems);
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity * item);
	virtual Entity* take(const std::string& name);
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems);
	virtual const std::string go(const std::vector<std::string>& arguments);
	virtual const std::string take(const std::vector<std::string>& arguments);

	inline const bool isOpened() const {
		return opened;
	}
	inline void setOpened(const bool opened) {
		this->opened = opened;
	}

	//is a container and can store another items?
	inline const bool isContainer() const {
		return container;
	}
	inline void setContainer(const bool isContainer) {
		container = isContainer;
	}

	//is an item I can take?
	inline const bool canTake() const {
		return canTaked;
	}
	inline void setCanTake(const bool canTake) {
		canTaked = canTake;
	}

	inline const TypeItem getTypeItem() const {
		return typeItem;
	}

	//const bool addItem(unsigned int value = 1);
	//const bool substractItem(unsigned int value = 1);
	inline const unsigned int getCount() const {
		return count;
	}

	const std::pair<bool, std::string> storeItem(Entity* item);

private:
	unsigned int count;
	//items that contains
	std::list<Entity*> items;
	bool opened;
	bool container;
	bool canTaked;
	//elements needed to open
	std::list<const Entity*> needed;
	const TypeItem typeItem;

private:
	void addItemNeeded(const Entity * key);

};


#endif // ! _ITEM_H_