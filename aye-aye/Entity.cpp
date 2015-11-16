#include "Entity.h"

unsigned int Entity::nextId = -1;

Entity::Entity(const char* name, const char* description, const TypeEntity type)
	: id(++nextId), name(name), description(description), type(type) {}

Entity::Entity(const Entity& entity) : id(entity.id), name(entity.name), description(entity.description), type(entity.type){ }


Entity::~Entity() {}
