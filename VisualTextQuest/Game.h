#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Event.h"

using namespace std;

class Game {
private:
	Player* player;
	vector<Vocation*> vocations;
	vector<Event*> events;
public:
	Game();
	~Game();
	Player* getPlayer();
	vector<Vocation*> getVocations();
	vector<Event*> getEvents();
};

#endif // ! GAME_H

