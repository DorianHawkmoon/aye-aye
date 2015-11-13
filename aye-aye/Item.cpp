#include "Item.h"

unsigned int Item::nextId=-1;

Item::Item(const char * name, const char * description)
: idItem(++nextId), name(name), description(description) {
}

Item::~Item() {}
