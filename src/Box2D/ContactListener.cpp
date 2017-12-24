#include "Box2D/ContactListener.h"
#include <iostream>
#include "Events/EventManager.h"
#include "Events/BallCollision.h"

ContactListener::ContactListener()
{
    //ctor
}

void ContactListener::BeginContact(b2Contact* contact)
{
    if(IsBall(contact->GetFixtureA()))
    {
        EventManager::inst().Post<BallCollision>();
    }

    if(IsBall(contact->GetFixtureB()))
    {
        EventManager::inst().Post<BallCollision>();
    }
}

bool ContactListener::IsBall(b2Fixture* fixture)
{
    if(fixture == nullptr)
        return false;

    b2Body *body = fixture->GetBody();

    if(body->GetUserData() == nullptr)
        return false;

    if(*static_cast<int *>(body->GetUserData()) == 1)
        return true;

    return false;
}


ContactListener::~ContactListener()
{
    //dtor
}
