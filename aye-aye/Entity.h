#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>
class Inventory;

enum TypeEntity {
	ENTITY,
	ROOM,
	PATH,
	ITEM,
	CREATURE,
	PLAYER,
	INVENTORY
};

class Entity {
public:
	Entity(const char* name = "", const char* description = "", const TypeEntity type = ENTITY);
	Entity(const Entity& entity);
	virtual ~Entity();

	inline const unsigned int getId() const {
		return id;
	}

	virtual inline const std::string getDescription() const {
		return description;
	}
	virtual inline const std::string& getName() const {
		return name;
	}

	inline TypeEntity getType() const {
		return type;
	}

	inline void changeParent(Entity* entity) {
		if (entity != nullptr) {
			parent = entity;
		}
	}

	inline Entity* getParent() const{
		return parent;
	}

	virtual const std::string look(const std::vector<std::string>& arguments) const = 0;
	virtual Entity* getEntity(const std::string& name) const = 0;
	virtual const std::string see(const std::vector<std::string>& arguments) const = 0;
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems) = 0;
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems) = 0;
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity* item) = 0;
	virtual Entity* take(const std::string& name) = 0;
	virtual const std::string take(const std::vector<std::string>& arguments) = 0;
	virtual const std::string go(const std::vector<std::string>& arguments) = 0;

protected:
	std::string description;
	std::string name;
	Entity* parent;

private:
	TypeEntity type;
	static unsigned int nextId;
	const unsigned int id;
};

#endif // ! _ENTITY_H_