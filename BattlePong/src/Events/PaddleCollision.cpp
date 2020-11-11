#include "Events/PaddleCollision.h"


PaddleCollision::PaddleCollision(const ObjectId newPaddle):
EventBase(EventId::PADDLE_COLLISION),
paddle(newPaddle)
{
    //ctor
}

PaddleCollision::~PaddleCollision()
{
    //dtor
}
