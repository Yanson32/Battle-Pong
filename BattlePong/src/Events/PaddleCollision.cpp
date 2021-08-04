#include "Events/PaddleCollision.h"
#include "Events/Id.h"

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
