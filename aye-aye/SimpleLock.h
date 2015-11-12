#pragma once
#ifndef _SIMPLE_LOCK_H_
#define _SIMPLE_LOCK_H_
#include "Path.h"

class SimpleLock : public Path{
public:
	SimpleLock(const bool opened, const char* descriptionOpened, const char* descriptionClosed, const char* descriptionOpening, const char* descriptionClosing);
	virtual ~SimpleLock();

	virtual bool open();
private:
	std::string descriptionOpened;
	std::string descriptionClosed;
	std::string descriptionOpening;
	std::string descriptionClosing;
};

#endif // ! _SIMPLE_LOCK_H