#include "Fight.h"
#include "Creature.h"
#include "Utilities.h"
#include "Entity.h"
#include <algorithm>
#include "Item.h"

Fight::Fight(Creature * player, const std::list<Creature*>& enemies, const bool canEscape)
	:canEscape(canEscape), player(player), enemies(enemies), resultFight(false) {}

Fight::~Fight() {
	if (output != nullptr) {
		delete output;
	}
}

const bool Fight::fight() {
	while (!endFight) {
		draw(); //we consider draw as writting
		input();
		update();
	}
	finalize();
	//writte the last news
	if (output != nullptr) {
		std::cout << std::endl << *output << std::endl << std::endl;
	}
	std::cout << "You: " << player->stats() << std::endl; 
	

	return resultFight;
}

const bool Fight::allEnemiesDied() const {
	bool died = true;
	for (std::list<Creature*>::const_iterator it = enemies.begin(); it != enemies.end() && died; ++it) {
		died = !(*it)->isAlive(); //if not alive, is dead! :D
	}
	return died;
}

void Fight::update() {
	delete output; //make sure deleted the previous string
	output = new std::string("");
	bool enemyAttackTurn = false;
	unsigned int size = parts.size();
	//execute commands and get the result
	if (size > 0) {
		//process the input by the player
		//make a new string in output to not get the returned value out of scope
		if (Utilities::compareTo(parts[0], "escape")) {
			if (canEscape) {
				output = new std::string("You has run away, you coward...");
				endFight = true;
			} else {
				output = new std::string("You can't escape!!! AaAaaaAAaHHhh!!");
			}

		} else if (Utilities::compareTo(parts[0], "attack")) {
			if (size > 1) {
				std::string name(parts[1]);
				std::list<Creature*>::const_iterator resultIt = std::find_if(enemies.begin(), enemies.end(),
					[&name](const Creature* creature) { //given the direction, check if this concrete exit is found
					return creature->getName() == name;
				});

				if (resultIt != enemies.end()) {
					Creature* enemy = (*resultIt);
					output->append("Attack " + enemy->getName() + "! " +
						enemy->damage(player->hit()));
					enemyAttackTurn = true;
				} else {
					output->append("Attack to who enemy?");
				}

			} else if (enemies.size() == 1) {
				output->append("Attack " + enemies.front()->getName() + "! " +
					enemies.front()->damage(player->hit()));
				if (!enemies.front()->isAlive()) {
					output->append("Enemy killed! ");
				}
				enemyAttackTurn = true;
			} else {
				output->append("Attack to who enemy?");
			}

		} else if (Utilities::compareTo(parts[0], "look")) {
			const std::vector<std::string> args = {"look", "inventory"};
			output->append(player->look(args));

		} else if (Utilities::compareTo(parts[0], "equip")) {
			output->append(player->equip(parts));

		} else if (Utilities::compareTo(parts[0], "unequip")) {
			output->append(player->unEquip(parts));

		} else {
			output->append("eemmm... sorry?");
		}
	} else {
		output->append("What are you going to do?!?");
	}


	if (enemyAttackTurn) {
		//enemies made his damage, get output and append
		output->append("\n\n");
		for (std::list<Creature*>::const_iterator it = enemies.begin(); it != enemies.end() && enemyAttackTurn; ++it) {
			if ((*it)->isAlive()) {
				unsigned int damage = (*it)->hit();
				output->append("Attacked by " + (*it)->getName() + "! " +
					player->damage(damage));

				if (!player->isAlive()) {
					output->append("Ouch!");
					enemyAttackTurn = false;
				}
			}
		}
	}

	if (!player->isAlive() || allEnemiesDied()) {
		resultFight = true;
		endFight = true;
	}

}

void Fight::input() {
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

void Fight::finalize() {
	//get sacks with the inventory of the enemies
	if (allEnemiesDied() && player->isAlive()) {
		for (std::list<Creature*>::const_iterator it = enemies.begin(); it != enemies.end(); ++it) {
			Creature* enemy = (*it);
			if (enemy->isAlive()) {
				continue;
			}
			Item* sack = new Item(std::string("remains-" + enemy->getName()).c_str(), std::string("remains from the enemy " + enemy->getName()).c_str());
			sack->setOpened(false);
			sack->setCanTake(false);
			sack->setContainer(true);

			std::list<Entity*> inventory = enemy->getInventory();
			for (std::list<Entity*>::iterator inventoryIt = inventory.begin(); inventoryIt != inventory.end(); ++inventoryIt) {
				sack->storeItem(*it);
			}

			//exact name is not needed, room will check only if have two arguments and drop it in the room
			const std::vector<std::string> args = {"drop", "sack"};
			player->getParent()->drop(args, sack);
		}

		output->append("\n\nYou defeated all the enemies!");
	}
}

void Fight::draw() {
	//nothing to draw, but in this case, will consider drawing as writing in the output
	if (output != nullptr) {
		std::cout << std::endl << *output << std::endl << std::endl;
	}
	std::cout << "You: " << player->stats() << std::endl;
	std::cout << "Enemies: ";
	bool first = true;
	for (std::list<Creature*>::const_iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if ((*it)->isAlive()) {
			if (first) {
				first = false;
			} else {
				std::cout << ", ";
			}
			std::cout << (*it)->getName();
		}
	}
	std::cout << std::endl << std::endl;
	std::cout << "Escape? Attack enemy? Look in inventory for better armor or weapon to equip?" << std::endl << std::endl;
}
