// Dragon.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 28/04/2016

#include "Dragon.h"

Dragon::Dragon() : Enemy() {

}

Dragon::Dragon(string name, int health, int strength, int magic) : Enemy(name, health, strength, magic) {
	//Adds a unique random prefix to the enemy's name based on enemy type
	string rank = "";
	int randRank = rand() % 2;
	if (randRank == 0) {
		rank = "Baby";
	}
	else {
		rank = "Red";
	}
	setRank(rank);
	setName(rank + " " + getName());
}

//Dragon attacks all targets and applies damage to all targets
void Dragon::attack(vector<Character*> targets) {

	vector<Character*>::iterator iter;
	int damage = 0;

	cout << getName() << " unleashes it's fire breath, attacking everyone nearby!" << endl;

	for (Character* target : targets) {

		//Ensures Dragon doesn't attack itself
		if (target != this) {
			//Example damage calculation involving strength and magic stats of both characters
			damage = 5 + (((getStrength() + getMagic()) / 10) - ((target->getStrength() + target->getMagic()) / 20));

			damageTarget(target, damage);
		}
	}
}