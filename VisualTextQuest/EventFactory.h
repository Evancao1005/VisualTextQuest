#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H
#include "Event.h"

// Singleton and factory patterns
class EventFactory {
private:
	EventFactory();
	static EventFactory* instance;
public:
	static EventFactory* getInstance();
	Event* makeEvent();
};

#endif