#include "Events/LeftPaddleGoal.h"
#include "Events/EventId.h"

LeftPaddleGoal::LeftPaddleGoal(): EventBase(EventId::LEFT_GOAL_COLLISION)
{
    //ctor
}

LeftPaddleGoal::~LeftPaddleGoal()
{
    //dtor
}
