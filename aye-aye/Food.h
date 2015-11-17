#pragma once
#ifndef _FOOD_H_

#include "Item.h"

class Food : public Item{
public:
	Food(const char * name, const char * description, int recover);
	virtual ~Food();

	inline const int getRecover() const{
		return recover;
	}

private:
	const int recover;
};

#endif // ! _FOOD_H_