// Enemy.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>

#include "Character.h"

using namespace std;

class Enemy : public Character {
private:
	// rank is a randomly chosen descriptive string that makes enemies seem a bit more interesting
	string m_rank;
protected:
	// sub-classes choose their own rank: hence it has a protected setter
	void setRank(string rank);
public:
	Enemy();
	Enemy(string name, int health, int strength, int magic);
	virtual void attack(vector<Character*> targets);
	string getRank();
};

#endif
