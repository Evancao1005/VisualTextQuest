// Character.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character {
protected:
	string m_name;
	int m_health, m_strength, m_magic;
	void damageTarget(Character* target, int damage);
public:
	Character();
	Character(string name, int health, int strength, int magic);
	string getName();
	void setName(string name);
	int getHealth();
	void setHealth(int health);
	int getStrength();
	void setStrength(int strength);
	int getMagic();
	void setMagic(int magic);
	virtual void attack(vector<Character*> targets);
};

#endif