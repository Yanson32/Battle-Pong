#include "Events/RightPaddleGoal.h"
#include "Events/EventId.h"

RightPaddleGoal::RightPaddleGoal(): EventBase(EventId::RIGHT_GOAL_COLLISION)
{
    //ctor
}

RightPaddleGoal::~RightPaddleGoal()
{
    //dtor
}
