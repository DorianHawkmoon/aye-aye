#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>


class Item {
public:
	Item(const char* name, const char* description);
	virtual ~Item();

	inline const int getId() const {
		return idItem;
	}
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
	static unsigned int nextId;
	const static unsigned int MAX_ITEMS=10;
	const unsigned int idItem;
	const std::string description;
	const std::string name;
	unsigned int count;
};


#endif // ! _ITEM_H_