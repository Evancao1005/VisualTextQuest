#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}


Player* Game::getPlayer()
{
	return player;
}
vector<Event*> Game::getEvents()
{
	return events;
}
vector<Vocation*> Game::getVocations()
{
	return vocations;
}

Room* Game::getRoom() {
	return room;
}

vector<Event*> Room::getEventList() {
	return eventList;
}

vector<Enemy*> Room::getEnemyList() {
	return enemyList;
}