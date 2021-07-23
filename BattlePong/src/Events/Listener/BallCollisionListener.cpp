#include "Events/Listeners/BallCollisionListener.h"
#include "Events/Events.h"
#include "Sounds/Id.h"
#include "Macros.h"

BallCollisionListener::BallCollisionListener()
{
    //ctor
}

void BallCollisionListener::OnEvent(GU::Evt::EventPtr event)
{
    UNUSED(event);
    EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::BUTTON);
}


BallCollisionListener::~BallCollisionListener()
{
    //dtor
}
