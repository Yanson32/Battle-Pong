#include "Events/BallCollision.h"
#include "Events/EventId.h"

BallCollision::BallCollision(): EventBase(EventId::BALL_COLLISION)
{
    //ctor
}

BallCollision::~BallCollision()
{
    //dtor
}
