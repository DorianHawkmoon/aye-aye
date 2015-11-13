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

protected:
	static unsigned int nextId;
	const unsigned int idItem;
	const std::string description;
	const std::string name;
};


#endif // ! _ITEM_H_