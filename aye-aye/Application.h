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
	bool processInput();
	std::vector<std::string> &split(const std::string &s, const char delim, std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, const char delim);
};

#endif // !_APPLICATION_H_