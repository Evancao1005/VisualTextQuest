// Enemy.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Enemy.h"

Enemy::Enemy() : Character() {
	m_rank = "";
}

Enemy::Enemy(string name, int health, int strength, int magic) : Character(name, health, strength, magic) {
}

void Enemy::attack(vector<Character*> targets) {
}

string Enemy::getRank() {
	return m_rank;
}

void Enemy::setRank(string rank) {
	m_rank = rank;
}