#include "Room.h"
#include "Game.h"

Room Room::roomArray[10][10];

Room::Room() {

}

Room::Room(int arg_x, int arg_y, vector<Event*> eventLoaded) {
	//Initialize the coodinates
	x = arg_x;
	y = arg_y;
	//Make doors
	roomArray[x][y].door_E = false;
	roomArray[x][y].door_W = false;
	roomArray[x][y].door_S = false;
	roomArray[x][y].door_N = false;
	visited = false;
	generateEventIntheRoom(eventLoaded);
	generateEnemyIntheRoom();
}

Room::~Room(){

}

Room Room::getRoomFromArray(int x, int y) {
	return roomArray[x][y];
}

void Room::setRoomToArray(int x, int y, Room incomingRoom) {
	roomArray[x][y] = incomingRoom;
	
	if (x - 1 < 0) {
		roomArray[x][y].door_N = false;
	}
	if (y - 1 < 0) {
		roomArray[x][y].door_W = false;
	}

	
	if (x > 0) {
		roomArray[x][y].door_N = roomArray[x - 1][y].door_S;

	}
	if (y > 0) {
		roomArray[x][y].door_W = roomArray[x][y - 1].door_E;
	}


	int isDoor = rand() % 2;
	if (isDoor == 0) {
		roomArray[x][y].door_S = true;
	}
	isDoor = rand() % 2;
	if (isDoor == 0) {
		roomArray[x][y].door_E = true;
	}

	if (x + 1 > 9) {
		roomArray[x][y].door_S = false;
	}
	if (y + 1 > 9) {
		roomArray[x][y].door_E = false;
	}


}

void Room::setPlayer(int x, int y)
{
	if (!roomArray[x][y].player) {
		roomArray[x][y].player = true;
		roomArray[x][y].visited = true;
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
bool Room::getVisited() { return visited; }



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

int Room::generateEventIntheRoom(vector<Event*> eventLoaded) {
	try
	{
		vector<Event*> events = eventLoaded;
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

void Room::clearRoom(int x, int y) {
	roomArray[x][y].enemyList.clear();
	roomArray[x][y].eventList.clear();
}
void Room::setVisited(int x, int y) {
	roomArray[x][y].visited = true;
}
