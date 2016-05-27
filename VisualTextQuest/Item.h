#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Item {
public:
	Item();
	Item(string, bool, int, int, int);
	~Item();
	string getName();
	bool getEquipable();
	int getPart();
	int getModificationType();
	int getModification();

private:
	string itemName;
	bool equipable;
	int part; //0: Head, 1: Body, 2: Left Arm, 3: Right Arm, 4: Left Leg, 5: Right Leg
	int modificationType; //0: Health, 1: Strength, 2: Magic
	int modification;

};
#endif // !ITEM_H
