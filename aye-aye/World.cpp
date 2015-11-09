#include "World.h"
#include "Room.h"
#include "Path.h"

World::World() {
	//create a room
	Room* westHouse= new Room("West of house",
		"This is an open field west of a white house, with a boarded front door. There is a small mailbox here. A rubber mat saying 'Welcome to Zork!' lies by the door.");
	this->listRooms.push_back(westHouse);
	this->actualRoom = westHouse;

	//create a room
	Room* southHouse = new Room("South of house",
		"You are facing the south side of a white house.  There is no door here, and all the windows are barred.");
	this->listRooms.push_back(southHouse);
	//create a path between two rooms
	Path* pathSouthWest = new Path(westHouse, southHouse);
	this->listPath.push_back(pathSouthWest);
	//add the path to the room specifying where the exit is located
	westHouse->addPath(pathSouthWest, Direction::SOUTH);
	southHouse->addPath(pathSouthWest, Direction::WEST);

	//create a room
	Room* behindHouse = new Room("Behind of house",
		"You are behind the white house.  In one corner of the house there is a small window which is slightly ajar.");
	this->listRooms.push_back(behindHouse);
	Path* pathSouthBehind = new Path(southHouse, behindHouse);
	this->listPath.push_back(pathSouthBehind);
	//add the path to the room specifying where the exit is located
	southHouse->addPath(pathSouthWest, Direction::EAST);
	behindHouse->addPath(pathSouthWest, Direction::SOUTH);

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
