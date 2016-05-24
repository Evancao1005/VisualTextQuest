// Player.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

#include "Character.h"
#include "Vocation.h"

using namespace std;

class Player : public Character {
private:
	// we keep track of the player's vocation by a pointer to one of the valid vocations loaded from file
	// this also gives us access to the default stats if we wanted to restore the character stats to defaults for the vocation (e.g. to full health)
	Vocation* m_vocation;
public:
	Player();
	Player(string name, Vocation*);
	virtual void attack(vector<Character*> targets);
	Vocation* getVocation();
};

#endif
