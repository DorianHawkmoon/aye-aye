#pragma once
#ifndef _FIGHT_H_
#define _FIGHT_H_

#include <list>
#include <iostream>
#include <string>
#include <vector>
class Creature;

class Fight {
public:
	Fight(Creature* player, const std::list<Creature*>& enemies, const bool canEscape);
	virtual ~Fight();
	//emulate loop game
	void update();
	void draw();
	void input();
	void finalize();

	//return true if the fight ends (no matters if win or loose) or false if the player run away
	const bool fight();

private:
	// true if the fight ends, false if player run away
	bool resultFight;
	//when its finished (independant of the result of fight)
	bool endFight;
	const bool canEscape;
	std::string* output;
	Creature* player;
	const std::list<Creature*> enemies;
	//parts of the input readed
	std::vector<std::string> parts;

private:
	const bool allEnemiesDied() const;
};

#endif // ! _FIGHT_H_