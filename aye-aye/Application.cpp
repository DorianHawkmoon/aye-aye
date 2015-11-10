#include "Application.h"
#include <sstream>
#include <iostream>
#include "Player.h"
#include "World.h"

Application::Application() {}


Application::~Application() {}

void Application::run() {
	std::cout << "Welcome to Aye-Aye" << std::endl;
	World world;
	Player player(world.getActualRoom());
	
	std::string output=player.actualState();
	while (true) { //TODO: put an exit condition
		std::cout << output << std::endl;
		processInput();
	}
}

bool Application::processInput() {
	//read all line
	//split into words
	//pass it to player
	std::string lecture;
	std::getline(std::cin, lecture);
	std::vector<std::string> parts;
	split(lecture, ' ', parts);
	
	return true;
}

std::vector<std::string>& Application::split(const std::string &s, const char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}


std::vector<std::string> Application::split(const std::string &s, const char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}