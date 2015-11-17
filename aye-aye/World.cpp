#include "World.h"
#include "Room.h"
#include "Path.h"
#include "SimpleLock.h"
#include "Item.h"
#include "Creature.h"
#include "Weapon.h"
#include "Armor.h"

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
	Path* pathSouthWest = new Path(westHouse, Direction::SOUTH, southHouse, Direction::WEST, "path");
	this->listPath.push_back(pathSouthWest);

	//create a room
	Room* behindHouse = new Room("Behind of house",
		"You are behind the white house.");
	this->listRooms.push_back(behindHouse);

	Path* pathSouthBehind = new Path(southHouse, Direction::EAST, behindHouse, Direction::SOUTH, "path");
	this->listPath.push_back(pathSouthBehind);

	Creature* enemy = new Creature("rat", "disgusting rat!!", 20,7);
	behindHouse->addItem(enemy);

	



	Room* kitchen = new Room("Kitchen", "You are in the kitchen of the white house. A table seems to have been used recently for the preparation of food. On the table are some objects.");
	//A passage leads to the west and a dark staircase can be seen leading upward.
	this->listRooms.push_back(kitchen);

	Weapon* weapon = new Weapon(5, "sword", "rusty sword");
	Armor* armor = new Armor(5, "shield", "basic shield");
	kitchen->addItem(weapon);
	kitchen->addItem(armor);


	Item* bottle = new Item("bottle", "bottle filled with some water");
	Item* sack= new Item("sack", "brown, dirty and old sack");
	Item* key = new Item("key", "rusty key");
	Item* lookpick = new Item("lookpick", "lookpick for opening dificults doors");
	sack->setContainer(true);
	sack->setOpened(true);
	sack->storeItem(key);
	sack->storeItem(lookpick);
	
	kitchen->addItem(bottle);
	kitchen->addItem(sack);


	SimpleLock* window = new SimpleLock(behindHouse, Direction::WEST, kitchen, Direction::EAST, "window", true, "there is a small opened window",
		"there is a small window which is slightly ajar",
		"With great effort, you open the window far enough to allow entry.",
		"You closed the window");
	this->listPath.push_back(window);
	window->addItemNeeded(key);
	window->addItemNeeded(lookpick);
	
	this->actualRoom = kitchen;
	
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
