// Dragon.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#ifndef DRAGON_H
#define DRAGON_H

#include <iostream>
#include <string>

#include "Enemy.h"

using namespace std;

class Dragon : public Enemy {
public:
	Dragon();
	Dragon(string name, int health, int strength, int magic);
	virtual void attack(vector<Character*> targets);
};

#endif
