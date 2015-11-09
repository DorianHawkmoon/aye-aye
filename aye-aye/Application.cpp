#include "Application.h"
#include <string>
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
	std::cin >> lecture;
	return true;
}
