#include "Events/Listeners/GoalCollisionListener.h"
#include <iostream>
#include "Events/EventManager.h"
#include "Events/LeftPaddleGoal.h"
#include "Events/RightPaddleGoal.h"
#include "Events/Id.h"

GoalCollisionListener::GoalCollisionListener()
{
    //ctor
}

void GoalCollisionListener::OnEvent(Evt::EventPtr event)
{
    switch(event->id)
    {
        case ObjectId::LEFT_GOAL:
            EventManager::inst().Post<LeftPaddleGoal>();
        break;
        case ObjectId::RIGHT_GOAL:
            EventManager::inst().Post<RightPaddleGoal>();
        break;
        default:
            std::cout << "default case triggered GoalCollisionListener id = " << event->id << std::endl;
    }

}

GoalCollisionListener::~GoalCollisionListener()
{
    //dtor
}
