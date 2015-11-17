#pragma once
#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Item.h"

/* An item that can be used as a weapon */
class Weapon : public Item {
public:
	Weapon(const int hit, const char* name, const char* description, 
		const TypeItem type = WEAPON, const unsigned int count = 1);
	virtual ~Weapon();

	//get the description
	virtual const std::string getDescription() const;
	//get amount of damage of the weapon
	inline const int getHit() const {
		return hit;
	}

private:
	const int hit;
};

#endif // ! _WEAPON_H_