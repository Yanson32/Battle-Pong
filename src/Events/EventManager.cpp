#include "Events/EventManager.h"

EventManager::EventManager()
{
    //ctor
}

EventManager& EventManager::inst()
{
	static EventManager eventManager;
	return eventManager;
}

EventManager::~EventManager()
{
    //dtor
}
