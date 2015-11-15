#include "Entity.h"

unsigned int Entity::nextId = -1;

Entity::Entity(const char* name, const char* description): id(++nextId), name(name), description(description) {}

Entity::Entity(const Entity& entity) : id(entity.id){ }


Entity::~Entity() {}
