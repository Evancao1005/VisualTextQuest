// Vocation.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Vocation.h"

Vocation::Vocation() {
	m_name = "";
	m_defaultHealth = 0;
	m_defaultStrength = 0;
	m_defaultMagic = 0;
}

Vocation::Vocation(string name, int defaultHealth, int defaultStrength, int defaultMagic) {
	m_name = name;
	m_defaultHealth = defaultHealth;
	m_defaultStrength = defaultStrength;
	m_defaultMagic = defaultMagic;
}

string Vocation::getName() {
	return m_name;
}

void Vocation::setName(string name) {
	m_name = name;
}

int Vocation::getDefaultHealth() {
	return m_defaultHealth;
}

void Vocation::setDefaultHealth(int defaultHealth) {
	m_defaultHealth = defaultHealth;
}

int Vocation::getDefaultStrength() {
	return m_defaultStrength;
}

void Vocation::setDefaultStrength(int defaultStrength) {
	m_defaultStrength = defaultStrength;
}

int Vocation::getDefaultMagic() {
	return m_defaultMagic;
}

void Vocation::setDefaultMagic(int defaultMagic) {
	m_defaultMagic = defaultMagic;
}

// overload the out-stream operator so it outputs the vocation name
ostream & operator<<(ostream & os, Vocation& vocation)
{
	return os << vocation.m_name;
}
