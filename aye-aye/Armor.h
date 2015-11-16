#pragma once
#ifndef _ARMOR_H_
#define _ARMOR_H_

#include "Item.h"

class Armor : public Item{
public:
	Armor(const int defense, const char* name, const char* description, const TypeItem type = ARMOR, const unsigned int count = 1);
	virtual ~Armor();

	virtual const std::string getDescription() const;

	inline const int getDefense() const {
		return defense;
	}

private:
	const int defense;
};

#endif // ! _ARMOR_H_