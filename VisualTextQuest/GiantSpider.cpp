// GiantSpider.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#include "GiantSpider.h"

GiantSpider::GiantSpider() : Enemy() {
}

GiantSpider::GiantSpider(string name, int health, int strength, int magic) : Enemy(name, health, strength, magic) {
	//Adds a unique random suffix to the enemy's name based on enemy type
	string rank = "";
	int randRank = rand() % 2;
	if (randRank == 0) {
		rank = "Hatchling";
	}
	else {
		rank = "Queen";
	}
	setRank(rank);
	setName(getName() + " " + rank);
}

//Giant Spider randomly chooses a target and applies damage to that target
void GiantSpider::attack(vector<Character*> targets) {
	Character* target = NULL;

	// Pick a target at random but not ourselves!
	while (!target || target == this) {
		target = targets[rand() % targets.size()];
	}

	//Example damage calculation involving strength and magic stats of both characters
	int damage = 5 + (((getStrength() + getMagic()) / 10) - ((target->getStrength() + target->getMagic()) / 20));

	damageTarget(target, damage);
}