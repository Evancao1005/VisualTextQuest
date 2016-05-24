// GiantSpider.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#ifndef GIANTSPIDER_H
#define GIANTSPIDER_H

#include <iostream>
#include <string>

#include "Enemy.h"

using namespace std;

class GiantSpider : public Enemy {
public:
	GiantSpider();
	GiantSpider(string name, int health, int strength, int magic);
	virtual void attack(vector<Character*> targets);
};

#endif
