#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Item.h"

class Weapon : public Item {
public:
	Weapon(const int hit, const char* name, const char* description, const TypeItem type = WEAPON, const unsigned int count = 1);
	virtual ~Weapon();

	virtual const std::string getDescription() const;

	inline const int getHit() const {
		return hit;
	}

private:
	const int hit;
};

#endif // ! _WEAPON_H_