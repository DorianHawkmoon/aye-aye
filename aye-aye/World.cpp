#include "World.h"
#include "Room.h"
#include "Path.h"
#include "SimpleLock.h"
#include "Item.h"
#include "Creature.h"
#include "Weapon.h"
#include "Armor.h"
#include "IndependentWayPath.h"
#include "Food.h"

World::World() {
	//create rooms
	Room* forrest = new Room("Forrest",
		"This is a forrest's clearing in front of a house");
	Room* frontHouse = new Room("Front house",
		"The front of the house");
	Room* grove = new Room("Grove",
		"The grove of the house, with some withered plants and a lot of weeds");
	Room* westHouse = new Room("West of house",
		"A simple garden in the west of the house");
	Room* kitchen = new Room("Kitchen", "A small, beautiful and rustic kitchen");
	Room* bedroom = new Room("Bedroom", "A simple bedroom");
	Room* bottomWell = new Room("Bottom well", "Its the bottom of a well, with some water on the floor");
	this->listRooms.push_back(forrest);
	this->listRooms.push_back(frontHouse);
	this->listRooms.push_back(grove);
	this->listRooms.push_back(westHouse);
	this->listRooms.push_back(kitchen);
	this->listRooms.push_back(bedroom);
	this->listRooms.push_back(bottomWell);

	//create objects
	Item* letter = new Item("letter","letter that said:\nDear neighbor: I'm sorry to tell you that your house has been invaded by vermins.\n\nOh man! I was coming to spend the summer, now I have to clean up this mess.");
	letter->setCanTake(true);
	letter->setContainer(false);
	letter->setOpened(false);

	Item* boxmail = new Item("boxmail", "boxmail");
	boxmail->setCanTake(false);
	boxmail->setContainer(true);
	boxmail->setOpened(false);
	boxmail->storeItem(letter);

	Item* key = new Item("key", "key of the house");
	key->setCanTake(true);
	key->setContainer(false);
	key->setOpened(false);
	
	Item* box = new Item("box", "little box");
	box->setCanTake(true);
	box->setContainer(true);
	box->setOpened(false);
	box->storeItem(key);
	
	Item* ladder = new Item("ladder", "old and insecure ladder");
	ladder->setCanTake(true);
	ladder->setContainer(false);
	ladder->setOpened(false);

	Food* can = new Food("can", "can of food", 10);
	can->setCanTake(true);
	can->setContainer(false);
	can->setOpened(false);

	Food* bread = new Food("bread", "bread", 5);
	bread->setCanTake(true);
	bread->setContainer(false);
	bread->setOpened(false);

	Food* cupcake = new Food("cupcake", "cupcake of chocolate", 13);
	cupcake->setCanTake(true);
	cupcake->setContainer(false);
	cupcake->setOpened(false);

	Food* meat = new Food("meat", "raw meat", 5);
	meat->setCanTake(true);
	meat->setContainer(false);
	meat->setOpened(false);
	
	Item* shelves = new Item("shelves", "dusty shelves");
	shelves->setCanTake(false);
	shelves->setContainer(true);
	shelves->setOpened(true);
	shelves->storeItem(can);
	shelves->storeItem(bread);
	shelves->storeItem(cupcake);

	Weapon* weapon = new Weapon(4, "hoe", "hoe for the grove");
	Weapon* knife = new Weapon(4, "knife", "little knife");
	
	Armor* armor = new Armor(4, "overalls", "dirty overalls for work");
	
	Item* wardrobe = new Item("wardrobe", "worn wardrobe");
	wardrobe->setCanTake(false);
	wardrobe->setContainer(true);
	wardrobe->setOpened(false);
	wardrobe->storeItem(weapon);
	wardrobe->storeItem(armor);

	//store the objects
	forrest->addItem(knife);
	kitchen->addItem(shelves);
	bedroom->addItem(wardrobe);
	forrest->addItem(boxmail);
	frontHouse->addItem(box);
	bottomWell->addItem(ladder);

	//create paths
	Path* forrestFrontHouse = new Path(forrest, Direction::SOUTH, frontHouse, Direction::NORTH, "path", "there is a little path in the fence which surround the house");
	Path* frontHouseWest = new Path(frontHouse, Direction::WEST, westHouse, Direction::EAST, "path", "there is a little path");
	Path* frontHouseGrove = new Path(frontHouse, Direction::EAST, grove, Direction::NORTH, "path", "there is a little path");
	SimpleLock* doorHouse = new SimpleLock(frontHouse, Direction::SOUTH, kitchen, Direction::NORTH, "door", false,
		"the door is open", "the door is closed with a padlock", "You unlock and opened the door", "You close and lock the door");
	doorHouse->addItemNeeded(key);
	SimpleLock* windowHouse = new SimpleLock(kitchen, Direction::EAST, grove, Direction::WEST, "window", true,
		"the window is open, maybe the animals come inside the house by the window","the window is closed", "You opened the window", "You closed the window with a little effort");
	Path* kitchenBedroom = new Path(kitchen, Direction::WEST, bedroom, Direction::EAST, "curtains", "there is a curtain separating the rooms");

	IndependentWayPath::Side airSide;
	airSide.nameRoom = westHouse->getName();
	airSide.descriptionClosed = std::string("there is a closed trapdoor on the floor with a padlock");
	airSide.descriptionClosing = std::string("You closed the trapdoor");
	airSide.descriptionOpened = std::string("there is an open trapdoor and a hole in which I can't see nothing inside");
	airSide.descriptionOpening = std::string("You opened the trapdoor");
	airSide.needed.push_back(key);

	IndependentWayPath::Side bottomSide;
	bottomSide.nameRoom = kitchen->getName();
	bottomSide.descriptionClosed = std::string("there is some rays of light from a trapdoor above my head");
	bottomSide.descriptionClosing = std::string("You quit the ladder");
	bottomSide.descriptionOpened = std::string("There is a ladder to get out of this hole");
	bottomSide.descriptionOpening = std::string("You put the ladder");
	bottomSide.needed.push_back(ladder);

	IndependentWayPath* westHouseWell = new IndependentWayPath("trapdoor", westHouse, Direction::DOWN, airSide, bottomWell, Direction::UP, bottomSide);

	//store paths
	this->listPath.push_back(forrestFrontHouse);
	this->listPath.push_back(doorHouse);
	this->listPath.push_back(windowHouse);
	this->listPath.push_back(kitchenBedroom);
	this->listPath.push_back(westHouseWell);
	this->listPath.push_back(frontHouseGrove);
	this->listPath.push_back(frontHouseWest);

	//create enemies
	Creature* spider = new Creature("giantspider", "a giant spider!!", 20, 7);
	Creature* vole = new Creature("vole", "a little vole", 5, 4);
	Creature* vole2 = new Creature("vole", "a little vole", 10, 4);
	Creature* vole3 = new Creature("vole", "a little vole", 10, 4);
	Creature* snake = new Creature("snake", "a dangerous snake", 13, 7);
	Creature* rat = new Creature("rat", "a rat", 8, 3);
	Creature* rat2 = new Creature("rat", "a rat", 8, 3);
	Creature* ferret = new Creature("ferret", "a nervous ferret", 10, 4);
	ferret->addItem(meat);

	//add the creatures to the list 
	listCreature.push_back(spider);
	listCreature.push_back(vole);
	listCreature.push_back(vole2);
	listCreature.push_back(vole3);
	listCreature.push_back(snake);
	listCreature.push_back(rat);
	listCreature.push_back(rat2);
	listCreature.push_back(ferret);

	//add the enemies to the room
	frontHouse->addItem(vole);
	grove->addItem(vole2);
	grove->addItem(vole3);
	bedroom->addItem(ferret);
	westHouse->addItem(snake);
	bottomWell->addItem(rat);
	bottomWell->addItem(rat2);
	bottomWell->addItem(spider);
	
	//place of start
	this->actualRoom = forrest;

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

	//don't delete list of creatures, world don't own that

}


Room* World::getActualRoom() const {
	return actualRoom;
}

const bool World::winCondition() const {
	bool died = true;
	for (std::list<Creature*>::const_iterator it = listCreature.begin(); it != listCreature.end() && died; ++it) {
		died = !(*it)->isAlive(); //if not alive, is dead! :D
	}
	return died;
}


