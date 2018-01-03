#include "Box2D/ContactListener.h"
#include "Events/EventManager.h"
#include "Events/BallCollision.h"
#include "Events/GoalCollision.h"
#include "Events/Id.h"
#include "Events/LeftPaddleGoal.h"
#include "Events/RightPaddleGoal.h"

ContactListener::ContactListener()
{
    //ctor
}

void ContactListener::BeginContact(b2Contact* contact)
{
    if(!contact)
        return;

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    if(fixtureA)
    {
        b2Body *bodyA = fixtureA->GetBody();
        if(bodyA)
        {
            void* vA = bodyA->GetUserData();
            if(vA)
            {
                int intA = (*static_cast<int*>(vA));
                dispatchEvent(intA, fixtureB->IsSensor());
            }
        }
    }

    if(fixtureB)
    {
        b2Body *bodyB = fixtureB->GetBody();
        if(bodyB)
        {
            void* vB = bodyB->GetUserData();
            if(vB)
            {
                int intB = (*static_cast<int*>(vB));
                dispatchEvent(intB, fixtureA->IsSensor());
            }
        }
    }


    if(IsBall(contact->GetFixtureA()))
    {
        EventManager::inst().Post<BallCollision>();
    }

    if(IsBall(contact->GetFixtureB()))
    {
        EventManager::inst().Post<BallCollision>();
    }

    if(IsGoal(contact->GetFixtureA()))
    {
        EventManager::inst().Post<GoalCollision>();
    }

    if(IsGoal(contact->GetFixtureB()))
    {
        EventManager::inst().Post<GoalCollision>();
    }
}

bool ContactListener::IsBall(b2Fixture* fixture)
{
    if(fixture == nullptr)
        return false;

    b2Body *body = fixture->GetBody();

    if(body->GetUserData() == nullptr)
        return false;

    if(*static_cast<int *>(body->GetUserData()) == EventId::BALL_COLLISION)
        return true;

    return false;
}

bool ContactListener::IsGoal(b2Fixture* fixture)
{
    if(fixture == nullptr)
        return false;

    b2Body *body = fixture->GetBody();

    if(body->GetUserData() == nullptr)
        return false;

    if(*static_cast<int *>(body->GetUserData()) == EventId::GOAL_COLLISION)
        return true;

    return false;
}

bool ContactListener::IsLeftGoal(b2Fixture* fixture)
{

}


bool ContactListener::IsRightGoal(b2Fixture* fixture)
{

}

void ContactListener::dispatchEvent(const int &id, const bool sensor) const
{
    switch(id)
    {
        case ObjectId::BALL:
            if(!sensor)
                EventManager::inst().Post<BallCollision>();
        break;
        case ObjectId::LEFT_GOAL:
            EventManager::inst().Post<LeftPaddleGoal>();
        break;
        case ObjectId::RIGHT_GOAL:
            EventManager::inst().Post<RightPaddleGoal>();
        break;
        case ObjectId::RIGHT_PADDLE:
        break;
        case ObjectId::LEFT_PADDLE:
        break;
    }
}

ContactListener::~ContactListener()
{
    //dtor
}
