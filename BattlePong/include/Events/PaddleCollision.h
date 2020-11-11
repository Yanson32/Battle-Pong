#ifndef PADDLECOLLISION_H
#define PADDLECOLLISION_H
#include "Events/EventBase.h"
#include "Events/Id.h"
class PaddleCollision: public EventBase
{
    public:
        PaddleCollision(const ObjectId newPaddle);
        ObjectId paddle;
        virtual ~PaddleCollision();
    protected:
    private:

};

#endif // PADDLECOLLISION_H
