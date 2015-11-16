#include "Application.h"
#include <iostream>

Application::Application(): world(), player(world.getActualRoom()), end(false) {
	parts.reserve(10);
	output = new std::string(player.actualState());
}


Application::~Application() {}

void Application::run() {
	std::cout << "Welcome to Aye-Aye" << std::endl;

	while (!end) { 
		draw(); //we consider draw as writting
		input();
		update();
	}
}

void Application::update() {
	//execute commands and get the result
	if (parts.size() > 0 && Utilities::compareTo(parts[0], "quit")) {
		end = true;
	} else {
		//process the input by the player
		delete output; //make sure deleted the previous string
		output = new std::string(player.action(parts)); //make a new string to not get the returned value out of scope
	}
}

void Application::input() {
	//read the input
	std::string lecture;
	do {
		lecture.clear();
		parts.clear();
		//read all line
		std::getline(std::cin, lecture);
	} while (lecture.size()<=0);
	//split into words
	Utilities::split(lecture, ' ', parts);
}

void Application::finalize() {
	//nothing to delete, when world and player will be delete with this class, everything else will be released
}

void Application::draw() {
	//nothing to draw, but in this case, will consider drawing as writing in the output
	std::cout << std::endl << *output << std::endl << std::endl;
}
