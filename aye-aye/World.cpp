#include "World.h"
#include "Room.h"
#include "Path.h"
#include "SimpleLock.h"
#include "OneWayLock.h"
#include "Item.h"

World::World() {
	//create a room
	Room* westHouse= new Room("West of house",
		"This is an open field west of a white house, with a boarded front door. There is a small mailbox here. A rubber mat saying 'Welcome to Zork!' lies by the door.");
	this->listRooms.push_back(westHouse);
	

	//create a room
	Room* southHouse = new Room("South of house",
		"You are facing the south side of a white house.  There is no door here, and all the windows are barred.");
	this->listRooms.push_back(southHouse);

	//create a path between two rooms
	Path* pathSouthWest = new Path(westHouse, southHouse, "path");
	this->listPath.push_back(pathSouthWest);
	//add the path to the room specifying where the exit is located
	westHouse->addPath(pathSouthWest, Direction::SOUTH);
	southHouse->addPath(pathSouthWest, Direction::WEST);

	//create a room
	Room* behindHouse = new Room("Behind of house",
		"You are behind the white house.");
	this->listRooms.push_back(behindHouse);

	Path* pathSouthBehind = new Path(southHouse, behindHouse, "path");
	this->listPath.push_back(pathSouthBehind);
	//add the path to the room specifying where the exit is located
	southHouse->addPath(pathSouthBehind, Direction::EAST);
	behindHouse->addPath(pathSouthBehind, Direction::SOUTH);

	Room* kitchen = new Room("Kitchen", "You are in the kitchen of the white house. A table seems to have been used recently for the preparation of food. On the table are some objects.");
	//A passage leads to the west and a dark staircase can be seen leading upward.
		//To the east is a small window which is open.
		
	this->listRooms.push_back(kitchen);


	Item* bottle = new Item("bottle", "filled with some water");
	Item* sack= new Item("sack", "brown, dirty and old");
	kitchen->addItem(bottle);
	kitchen->addItem(sack);


	Path* window = new SimpleLock(behindHouse, kitchen, "window", false, "there is a small opened window", 
		"there is a small window which is slightly ajar",
		"With great effort, you open the window far enough to allow entry.",
		"You closed the window");
	this->listPath.push_back(window);
	behindHouse->addPath(window, Direction::WEST);
	kitchen->addPath(window, Direction::EAST);

	this->actualRoom = behindHouse;
}


World::~World() {
	//delete all path
	std::list<Path*>::iterator it = listPath.begin();
	while (it != listPath.end()) {
		it = listPath.erase(it);
	}

	//delete all rooms
	std::list<Room*>::iterator it2 = listRooms.begin();
	while (it2 != listRooms.end()) {
		it2 = listRooms.erase(it2);
	}
}


Room* World::getActualRoom() const{
	return actualRoom;
}
