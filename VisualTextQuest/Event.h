// Event.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

class Event {
private:
	string m_description;
	int m_healthModifier;
public:
	Event();
	Event(string description, int healthModifier);
	~Event();
	string getDescription();
	void setDescription(string description);
	int getHealthModifier();
	void setHealthModifier(int healthModifier);
};

#endif
