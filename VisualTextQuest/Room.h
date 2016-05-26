#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <iostream>
#include "Event.h"
#include "EnemyFactory.h"

using namespace std;

class Room {
public:
	Room();
	Room(int x, int y, vector<Event*>);
	~Room();
	int generateEnemyIntheRoom();
	int generateEventIntheRoom(vector<Event*>);

	Room getRoomFromArray(int x, int y);
	void setRoomToArray(int x, int y, Room incomingRoom);
	int getX();
	int getY();
	bool getDoorN();
	bool getDoorW();
	bool getDoorE();
	bool getDoorS();
	void setPlayer(int x, int y);
	bool getPlayer();
	vector<Event*> getEventList();
	vector<Enemy*> getEnemyList();

public:
	void clearRoom(int, int);
private:
	int x, y;
	bool door_N, door_S, door_W, door_E, visited, player;
	vector<Event*> eventList;
	vector<Enemy*> enemyList;
	static Room roomArray[10][10];
};
#endif // ROOM_H
