#include "Events/Listeners/BallCollisionListener.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"

BallCollisionListener::BallCollisionListener()
{
    //ctor
}

void BallCollisionListener::OnEvent(Evt::EventPtr event)
{
    EventManager::inst().Post<PlaySound>("Ball Sound");
}


BallCollisionListener::~BallCollisionListener()
{
    //dtor
}
