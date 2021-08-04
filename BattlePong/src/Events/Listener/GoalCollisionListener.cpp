#include "Events/Listeners/GoalCollisionListener.h"
#include "Events/EventManager.h"
#include "Events/LeftPaddleGoal.h"
#include "Events/RightPaddleGoal.h"
#include "Objects/ObjectId.h"
#include <iostream>
GoalCollisionListener::GoalCollisionListener()
{
    //ctor
}

void GoalCollisionListener::OnEvent(GU::Evt::EventPtr event)
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
