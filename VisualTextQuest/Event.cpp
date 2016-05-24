// Event.cpp
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#include "Event.h"

Event::Event() {
	m_description = "";
	m_healthModifier = 0;
}

Event::Event(string description, int healthModifier) {
	m_description = description;
	m_healthModifier = healthModifier;
}

Event::~Event() {

}

string Event::getDescription() {
	return m_description;
}

void Event::setDescription(string description) {
	m_description = description;
}

int Event::getHealthModifier() {
	return m_healthModifier;
}

void Event::setHealthModifier(int healthModifier) {
	m_healthModifier = healthModifier;
}