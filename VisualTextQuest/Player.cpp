// Player.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Player.h"

Player::Player() : Character() {
}

// construct a player with the default stats for the specified vocation
Player::Player(string name, Vocation* vocation)
	: Character(name, vocation->getDefaultHealth(), vocation->getDefaultStrength(), vocation->getDefaultMagic())
	, m_vocation(vocation) {
}

//Prompts the player to choose a target to attack and applies damage to that target
void Player::attack(vector<Character*> targets) {

	vector<Character*>::iterator iter;
	int count = 0;
	int choice = 0;
	int damage = 0;

	while (choice < 1 || choice > count) {
		cout << "Choose a target to attack from the list below: " << endl;
		count = 0;
		//Iterator starts at element [1] so that the player cannot choose themselves
		for (iter = targets.begin() + 1; iter != targets.end(); iter++) {
			count++;
			cout << count << ": " << (*iter)->getName() << endl;
		}

		cin >> choice;
	}

	Character* target = targets[choice];

	//Example damage calculation involving strength and magic stats of both characters
	damage = 25 + (((getStrength() + getMagic()) / 10) - ((target->getStrength() + target->getMagic()) / 20));

	damageTarget(target, damage);
}

Vocation* Player::getVocation() {
	return m_vocation;
}