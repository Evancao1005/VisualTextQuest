// Orc.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#ifndef ORC_H
#define ORC_H

#include <iostream>
#include <string>

#include "Enemy.h"

using namespace std;

class Orc : public Enemy {
public:
	Orc();
	Orc(string name, int health, int strength, int magic);
	virtual void attack(vector<Character*> targets);
};

#endif
