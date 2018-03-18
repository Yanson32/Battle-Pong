#include "Events/Listeners/BallCollisionListener.h"
#include "Events/Events.h"

BallCollisionListener::BallCollisionListener()
{
    //ctor
}

void BallCollisionListener::OnEvent(GU::Evt::EventPtr event)
{
    EventManager::inst().Post<GU::Evt::PlaySound>("Ball Sound");
}


BallCollisionListener::~BallCollisionListener()
{
    //dtor
}
