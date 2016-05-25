#include "Room.h"
#include "Game.h"

Room Room::room[9][9];

Room::Room() {

}

Room::Room(int arg_x, int arg_y) {
	//Initialize the coodinates
	x = arg_x;
	y = arg_y;

	//Make doors
	room[x][y].door_E = false;
	room[x][y].door_W = false;
	room[x][y].door_S = false;
	room[x][y].door_N = false;

	if (room[x][y - 1].door_E == true)
	{
		room[x][y].door_W = true;
	}
	if (room[x - 1][y].door_S == true)
	{
		room[x][y].door_N = true;
	}

	int isDoor = rand() % 2;
	if (isDoor == 0) {
		room[x][y].door_E = true;
	}
	isDoor = rand() % 2;
	if (isDoor == 0) {
		room[x][y].door_S = true;
	}

}

Room::~Room(){

}

int Room::getX() { return x; }
int Room::getY() { return y; }

bool Room::canAccesstheGivenDirection(string direction)
{
	if (direction == "N") { return room[x][y].door_N; }
	else if (direction == "S") { return room[x][y].door_S; }
	else if (direction == "W") { return room[x][y].door_W; }
	else if (direction == "E") { return room[x][y].door_E; }
}

int Room::generateEnemyIntheRoom() {
	try
	{
		int numEnemies = rand() % 3 + 1;
		for (int i = 0; i < numEnemies; i++) {
			enemyList.push_back(EnemyFactory::getInstance()->makeEnemy());
		}
		return 1000;
	}
	catch (const std::exception&)
	{
		return 1001;
	}
}

int Room::generateEventIntheRoom() {
	try
	{
		Game game;
		vector<Event*> events = game.getEvents();
		int numEvents = rand() % 3 + 1;

		for (int i = 0; i < numEvents; i++) {
			int randEvent = rand() % events.size();
			eventList.push_back(events[randEvent]);
		}
		return 1000;
	}
	catch (const std::exception&)
	{
		return 1002;
	}
}