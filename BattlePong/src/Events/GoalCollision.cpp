#include "Events/GoalCollision.h"
#include "Events/EventId.h"

GoalCollision::GoalCollision(): EventBase(EventId::GOAL_COLLISION)
{
    //ctor
}

GoalCollision::~GoalCollision()
{
    //dtor
}
