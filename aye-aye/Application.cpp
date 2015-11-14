#include "Application.h"
#include <iostream>
#include "Player.h"
#include "World.h"

Application::Application(): world(), player(world.getActualRoom()), end(false) {}


Application::~Application() {}

void Application::run() {
	std::cout << "Welcome to Aye-Aye" << std::endl;

	std::string output=player.actualState();
	//show the actual situation
	std::cout << std::endl << output << std::endl << std::endl;

	while (!end) { //TODO: put an exit condition
		input();
		update();
		draw(); //we consider draw as writting
	}
}

void Application::update() {
	//execute commands and get the result
}

void Application::input() {
	//read the input
	std::vector<std::string> parts;

	std::string lecture;
	//read all line
	std::getline(std::cin, lecture);
	//split into words
	Utilities::split(lecture, ' ', parts);

	//TODO: check if finish the game

	//process the input by the player
	player.action(parts);
}

void Application::finalize() {
	//nothing to delete, when world and player will be delete with this class, everything else will be released
}

void Application::draw() {
	//nothing to draw, but in this case, will consider drawing as writing in the output

	//give some space between the reaction of player and the player's word
	std::cout << std::endl;
}
