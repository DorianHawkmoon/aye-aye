#include "SimpleLock.h"



SimpleLock::SimpleLock(const bool opened, const char * descriptionOpened, const char * descriptionClosed, const char * descriptionOpening, const char * descriptionClosing)
: descriptionClosed(descriptionClosed), descriptionClosing(descriptionClosing), descriptionOpened(descriptionOpened), descriptionOpening(descriptionOpening) {
	this->opened = opened;
}

SimpleLock::~SimpleLock() {}

bool SimpleLock::open() {
	return false;
}
