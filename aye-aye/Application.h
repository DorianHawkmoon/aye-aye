#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "World.h"

class Application
{
public:
	Application();
	virtual ~Application();

	void run();

private:
	bool processInput();
};

#endif // !_APPLICATION_H_