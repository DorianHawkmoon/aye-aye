#include "Food.h"



Food::Food(const char * name, const char * description, int recover): Item(name, description, FOOD), recover(recover) {}

Food::~Food() {}
