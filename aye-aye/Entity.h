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

	//get the id (TODO: need the id?
	inline const unsigned int getId() const {
		return id;
	}

	//get the description of the entity
	virtual inline const std::string getDescription() const {
		return description;
	}
	//get the name of entity
	virtual inline const std::string& getName() const {
		return name;
	}
	//get type of entity
	inline TypeEntity getType() const {
		return type;
	}
	//change the parent in which is stored or stayed
	inline void changeParent(Entity* entity) {
		if (entity != nullptr) {
			parent = entity;
		}
	}
	//get the parent (the entity in which is stored/stayed in)
	inline Entity* getParent() const{
		return parent;
	}
	//look around the room or object, see the games
	virtual const std::string look(const std::vector<std::string>& arguments) const = 0;
	//search for an entity given its name
	virtual Entity* getEntity(const std::string& name) const = 0;
	//see an object in detail (description)
	virtual const std::string see(const std::vector<std::string>& arguments) const = 0;
	//open an entity given the inventory has to i TODO: ese inglés!
	virtual const std::string open(const std::vector<std::string>& arguments, const Inventory * openItems) = 0;
	//close an entity with the inventory has to it TODO: ese inglés
	virtual const std::string close(const std::vector<std::string>& arguments, const Inventory* closeItems) = 0;
	//drop the item
	virtual const std::pair<bool, std::string> drop(const std::vector<std::string>& arguments, Entity* item) = 0;
	//take the entity (remove it from its original site)
	virtual Entity* take(const std::string& name) = 0;
	//action of taking an object (room can't take, but creature can)
	virtual const std::string take(const std::vector<std::string>& arguments) = 0;
	//go to another place
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