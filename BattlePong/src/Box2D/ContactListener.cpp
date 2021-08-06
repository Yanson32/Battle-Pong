#include "Box2D/ContactListener.h"
#include "Events/EventManager.h"
#include "Events/BallCollision.h"
#include "Events/GoalCollision.h"
#include "Events/EventId.h"
#include "Events/LeftPaddleGoal.h"
#include "Events/RightPaddleGoal.h"
#include "Events/PaddleCollision.h"
#include <iostream>
#include "Macros.h"

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

    if(IsPaddle(fixtureA) && IsBall(fixtureB))
    {
        EventManager::inst().Post<PaddleCollision>(*static_cast<ObjectId*>(fixtureA->GetBody()->GetUserData()));
    }

    if(IsPaddle(fixtureB) && IsBall(fixtureA))
    {
        EventManager::inst().Post<PaddleCollision>(*static_cast<ObjectId*>(fixtureB->GetBody()->GetUserData()));
    }
}

bool ContactListener::IsBall(b2Fixture* fixture)
{
    if(fixture == nullptr)
        return false;

    b2Body *body = fixture->GetBody();

    if(body->GetUserData() == nullptr)
        return false;

    if(*static_cast<int *>(body->GetUserData()) == ObjectId::BALL)
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
    UNUSED(fixture);
    return false;
}


bool ContactListener::IsRightGoal(b2Fixture* fixture)
{
    UNUSED(fixture);
    return false;
}

bool ContactListener::IsPaddle(b2Fixture* fixture)
{

    if(getObjectId(fixture) == ObjectId::LEFT_PADDLE || getObjectId(fixture) == ObjectId::RIGHT_PADDLE)
    {
        return true;
    }



    return false;
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

ObjectId ContactListener::getObjectId(b2Fixture* fixture)
{

    if(fixture == nullptr)
        return ObjectId::NONE;

    b2Body *body = fixture->GetBody();

    if(body->GetUserData() == nullptr)
        return ObjectId::NONE;

    return *static_cast<ObjectId *>(body->GetUserData());


}
ContactListener::~ContactListener()
{
    //dtor
}
