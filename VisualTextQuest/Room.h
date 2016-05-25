#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Event.h"
#include "EnemyFactory.h"

using namespace std;

class Room {
public:
	Room();
	Room(int x, int y);
	~Room();
	int generateEnemyIntheRoom();
	int generateEventIntheRoom();
	bool canAccesstheGivenDirection(string);
	int getX();
	int getY();
private:
	int x, y;
	bool door_N, door_S, door_W, door_E, visited;
	vector<Event*> eventList;
	vector<Enemy*> enemyList;

	static Room room[9][9];
};
#endif // ROOM_H
