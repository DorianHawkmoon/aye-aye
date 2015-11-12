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
	//show the actual situation
	std::cout << std::endl << output << std::endl << std::endl;

	while (true) { //TODO: put an exit condition
		//read the input
		std::vector<std::string> parts;
		readInput(parts);

		//process the input by the player
		player.action(parts);

		//give some space between the reaction of player and the player's word
		std::cout << std::endl;
	}
}

const void Application::readInput(std::vector<std::string>& parts) {
	std::string lecture;
	//read all line
	std::getline(std::cin, lecture);
	//split into words
	split(lecture, ' ', parts);
	//give some space between player's word and the output
	std::cout << std::endl;
}

const std::vector<std::string>& Application::split(const std::string &s, const char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}


const std::vector<std::string> Application::split(const std::string &s, const char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}