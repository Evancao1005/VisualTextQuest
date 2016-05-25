#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Event.h"
#include "Room.h"

using namespace std;

class Game {
private:
	Player* player;
	vector<Vocation*> vocations;
	vector<Event*> events;
	Room* room;
public:
	Game();
	~Game();
	Player* getPlayer();
	vector<Vocation*> getVocations();
	vector<Event*> getEvents();
	Room* getRoom();
};

#endif // ! GAME_H

