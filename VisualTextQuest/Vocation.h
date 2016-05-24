// Vocation.h
// CPlusPlusQuest (A2 Sample Solution)
// Created by Peter Hoghton on 22/04/2016

#ifndef VOCATION_H
#define VOCATION_H

#include <string>
#include <ostream>

using namespace std;

class Vocation {
private:
	string m_name;
	int m_defaultHealth, m_defaultStrength, m_defaultMagic;
public:
	Vocation();
	Vocation(string name, int defaultHealth, int defaultStrength, int defaultMagic);
	string getName();
	void setName(string name);
	int getDefaultHealth();
	void setDefaultHealth(int defaultHealth);
	int getDefaultStrength();
	void setDefaultStrength(int defaultStrength);
	int getDefaultMagic();
	void setDefaultMagic(int defaultMagic);

	// overload the out-stream operator so it outputs the vocation name
	friend ostream& operator<<(ostream& os, Vocation& vocation);
};

ostream& operator<<(ostream& os, Vocation& vocation);

#endif