#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>
#include <list>
class Item;

class Entity {
public:
	Entity(const char* name = "", const char* description = "");
	Entity(const Entity& entity);
	virtual ~Entity();

	inline const unsigned int getId() const {
		return id;
	}

	virtual inline const std::string& getDescription() const {
		return description;
	}
	virtual inline const std::string& getName() const {
		return name;
	}

	virtual const std::string look() const=0;
	virtual Entity* getEntity(const std::string& name) const=0;
	virtual const std::string see(const std::vector<std::string>& arguments) const=0;
	virtual const std::string open(const std::vector<std::string>& arguments, const std::list<Entity*>& openItems)=0;
	virtual const std::string drop(const std::vector<std::string>& arguments, Entity* item) = 0;
	virtual Entity* take(const std::string& name) = 0;
	
protected:
	std::string description;
	std::string name;

private:
	static unsigned int nextId;
	const unsigned int id;
};

#endif // ! _ENTITY_H_