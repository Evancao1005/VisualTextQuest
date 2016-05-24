// Character.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Character.h"

void Character::damageTarget(Character * target, int damage)
{
	target->setHealth(target->getHealth() - damage);
	cout << getName() << " did " << damage << " damage to " << target->getName() << "!" << endl;

	if (target->getHealth() > 0) {
		cout << target->getName() << " has " << target->getHealth() << " health remaining." << endl;
	}
	else {
		cout << target->getName() << " has been defeated!" << endl;
	}
}

Character::Character() {
	m_name = "";
	m_health = 0;
	m_strength = 0;
	m_magic = 0;
}

Character::Character(string name, int health, int strength, int magic) {
	m_name = name;
	m_health = health;
	m_strength = strength;
	m_magic = magic;
}

string Character::getName() {
	return m_name;
}

void Character::setName(string name) {
	m_name = name;
}

int Character::getHealth() {
	return m_health;
}

void Character::setHealth(int health) {
	m_health = health;
}

int Character::getStrength() {
	return m_strength;
}

void Character::setStrength(int strength) {
	m_strength = strength;
}

int Character::getMagic() {
	return m_magic;
}

void Character::setMagic(int magic) {
	m_magic = magic;
}

void Character::attack(vector<Character*> targets) {

}