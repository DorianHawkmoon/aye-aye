#include "Application.h"
#include <iostream>

Application::Application(): world(), player("Aye-Aye", "Its you! Aye-aye!", 20, PLAYER), end(false) {
	player.changeParent((Entity*)world.getActualRoom());
	parts.reserve(10);
	std::vector<std::string> args;
	output = new std::string(player.look(args));
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
	    //make a new string to not get the returned value out of scope
		if (Utilities::compareTo(parts[0], "look")) {
			output = new std::string(player.look(parts));
		} else if (Utilities::compareTo(parts[0], "go")) {
			output = new std::string(player.go(parts));
		} else if (Utilities::compareTo(parts[0], "see")) {
			output = new std::string(player.see(parts));
		} else if (Utilities::compareTo(parts[0], "open")) {
			output = new std::string(player.open(parts, nullptr));
		} else if (Utilities::compareTo(parts[0], "take")) {
			output = new std::string(player.take(parts));
		} else if (Utilities::compareTo(parts[0], "drop")) {
			output = new std::string(player.drop(parts, nullptr).second);
		} else if (Utilities::compareTo(parts[0], "close")) {
			output = new std::string(player.close(parts, nullptr));
		} else {
			output = new std::string("eemmm... sorry?");
		}
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
