#include "Entity.h"

unsigned int Entity::nextId = -1;

Entity::Entity(): id(++nextId) {}

Entity::Entity(const Entity& entity) : id(entity.id){ }


Entity::~Entity() {}
