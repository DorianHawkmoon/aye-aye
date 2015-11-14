#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "World.h"
#include <string>
#include <vector>

class Application
{
public:
	Application();
	virtual ~Application();

	void run();

private:
	void update();
	void draw();
	void input();
	void finalize();

	World world;
	Player player;
	bool end;
};

#endif // !_APPLICATION_H_