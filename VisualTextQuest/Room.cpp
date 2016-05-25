#include "Room.h"
#include "Game.h"

Room Room::roomArray[9][9];

Room::Room() {

}

Room::Room(int arg_x, int arg_y) {
	//Initialize the coodinates
	x = arg_x;
	y = arg_y;
	//Make doors
	roomArray[x][y].door_E = false;
	roomArray[x][y].door_W = false;
	roomArray[x][y].door_S = false;
	roomArray[x][y].door_N = false;
}

Room::~Room(){

}

Room Room::getRoomFromArray(int x, int y) {
	return roomArray[x][y];
}

void Room::setRoomToArray(int x, int y, Room incomingRoom) {
	roomArray[x][y] = incomingRoom;

	if ((!(x - 1 < 0)) && (!(y - 1 < 0))) {
		if (roomArray[x][y - 1].door_E == true)
		{
			roomArray[x][y].door_W = true;
		}
		if (roomArray[x - 1][y].door_S == true)
		{
			roomArray[x][y].door_N = true;
		}
	}
	else if (x - 1 < 0) { roomArray[x][y].door_N = false; }
	else { roomArray[x][y].door_W = false; }


	int isDoor = rand() % 2;
	if (isDoor == 0) {
		roomArray[x][y].door_E = true;
	}
	isDoor = rand() % 2;
	if (isDoor == 0) {
		roomArray[x][y].door_S = true;
	}
}

void Room::setPlayer(int x, int y)
{
	if (!roomArray[x][y].player) {
		roomArray[x][y].player = true;
	}
	else {
		roomArray[x][y].player = false;
	}

}

bool Room::getPlayer() { return player; }
int Room::getX() { return x; }
int Room::getY() { return y; }
bool Room::getDoorE() { return door_E; }
bool Room::getDoorW() { return door_W; }
bool Room::getDoorS() { return door_S; }
bool Room::getDoorN() { return door_N; }



bool Room::canAccesstheGivenDirection(string direction)
{
	if (direction == "N") { return door_N; }
	else if (direction == "S") { return door_S; }
	else if (direction == "W") { return door_W; }
	else if (direction == "E") { return door_E; }
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