#include "EventFactory.h"

EventFactory* EventFactory::instance = NULL;

EventFactory::EventFactory() {}

EventFactory* EventFactory::getInstance() {
	return EventFactory::instance == NULL ? instance = new EventFactory() : instance;
}

Event* EventFactory::makeEvent() {
	int randEvent = rand() % events.size();

	//Outputs random event information and modifies character's health accordingly
	cout << events[randEvent]->getDescription() << endl;
	player->setHealth(player->getHealth() + events[randEvent]->getHealthModifier());
}