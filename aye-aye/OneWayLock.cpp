#include "OneWayLock.h"



OneWayLock::OneWayLock(Room* origin, Room* destination, const char* description): Path(origin, destination, description) {}


OneWayLock::~OneWayLock() {}
