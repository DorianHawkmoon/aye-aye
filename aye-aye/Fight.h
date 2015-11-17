#pragma once
#ifndef _FIGHT_H_

#include <list>
#include <iostream>
#include <string>
#include <vector>
class Creature;

class Fight {
public:
	Fight(Creature* player, const std::list<Creature*>& enemies, const bool canEscape);
	virtual ~Fight();

	void update();
	void draw();
	void input();
	void finalize();

	//return true if the fight ends (no matters if win or loose) or false if the player run away
	const bool fight();

private:
	bool resultFight;
	bool endFight;
	const bool canEscape;
	std::string* output;
	Creature* player;
	const std::list<Creature*> enemies;
	std::vector<std::string> parts;

private:
	const bool allEnemiesDied() const;
};

#endif // ! _FIGHT_H_