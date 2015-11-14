#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>
#include <list>

class Item;

class Entity {
public:
	Entity();
	Entity(const Entity& entity);
	virtual ~Entity();

	inline const unsigned int getId() const {
		return id;
	}

	virtual const std::string look() const=0;
	virtual const Entity* getEntity(const std::string& name)=0;
	virtual const std::string see(const std::vector<std::string>& arguments) const=0;
	virtual const std::string open(const std::vector<std::string>& arguments, const std::list<Item*>& openItems)=0;

private:
	static unsigned int nextId;
	const unsigned int id;
};

#endif // ! _ENTITY_H_