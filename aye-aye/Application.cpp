#include "Application.h"
#include <iostream>
#include "Utilities.h"

Application::Application() : world(), player("Aye-Aye", "Its you! Aye-aye!", 20, PLAYER), end(false) {
	player.changeParent((Entity*) world.getActualRoom());
	parts.reserve(5);
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
	draw(); //writte the last news
	finalize();
}

void Application::update() {
	//execute commands and get the result
	delete output; //make sure deleted the previous string
	if (parts.size() > 0 && Utilities::compareTo(parts[0], "quit")) {
		output = new std::string;
		end = true;
	} else {
		//process the input by the player
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
		} else if (Utilities::compareTo(parts[0], "equip")) {
			output = new std::string(player.equip(parts));
		} else if (Utilities::compareTo(parts[0], "unequip")) {
			output = new std::string(player.unequip(parts));
		} else if (Utilities::compareTo(parts[0], "stats")) {
			output = new std::string(player.stats());
		} else if (Utilities::compareTo(parts[0], "eat")) {
			output = new std::string(player.eat(parts));
		} else {
			output = new std::string("eemmm... sorry?");
		}
	}

	//check if the player is still alive and if win the game
	if (!end && !player.isAlive()) {
		output->append("\nYou die...\n\nGAME OVER!");
	} else if(!end && winCondition()){
		output->append("\nFinally! the house is clean!\nHome, sweet home... Let's relax!\n");
		end = true;
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
	} while (lecture.size() <= 0);
	//split into words
	Utilities::split(lecture, ' ', parts);
}

void Application::finalize() {
	//nothing to delete, when world and player will be delete with this class, everything else will be released
}

bool Application::winCondition() {
	return world.winCondition();
}

void Application::draw() {
	//nothing to draw, but in this case, will consider drawing as writing in the output
	std::cout << std::endl << "==============================================" << std::endl;
	if (output != nullptr) {
		std::cout << std::endl << *output << std::endl << std::endl;
	}
}
