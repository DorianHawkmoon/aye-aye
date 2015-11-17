#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "World.h"
#include "Creature.h"
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
	bool winCondition();

	World world;
	Creature player;
	bool end;

	std::vector<std::string> parts;
	std::string* output;
};

#endif // !_APPLICATION_H_