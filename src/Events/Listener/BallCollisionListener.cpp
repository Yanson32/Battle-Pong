#include "Events/Listeners/BallCollisionListener.h"
#include <iostream>
#include "Events/EventManager.h"
#include "Events/PlaySound.h"

BallCollisionListener::BallCollisionListener()
{
    //ctor
}

void BallCollisionListener::OnEvent(Evt::EventPtr event)
{
    std::cout << "Ball Collision" << std::endl;
    EventManager::inst().Post<PlaySound>("Ball Sound");
}


BallCollisionListener::~BallCollisionListener()
{
    //dtor
}
