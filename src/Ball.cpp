#include "Ball.h"
#include <Box2D/Box2D.h>
#include "Box2DFunctions.h"
#include <iostream>

Ball::Ball(b2World &world, const unsigned radious)
{

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;

    //ctor
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 0);
    bodyDef.angle = 0;
    bodyDef.gravityScale = 0;
    bodyDef.bullet = true;

    body = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = toMeters(radious);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &circleShape;
    bodyFixture.friction = 0.0f;
    bodyFixture.restitution = 1.0f;
    //bodyFixture.density = 1.0f;

    b2Fixture *fix = body->CreateFixture(&bodyFixture);




    shape.setFillColor(sf::Color::Green);
    shape.setRadius(radious);
    shape.setOrigin(radious, radious);
}

void Ball::update()
{
    shape.setPosition(toPixles(body->GetPosition()));
}

void Ball::setVelocity(const sf::Vector2f &newVelocity)
{
    body->ApplyLinearImpulse(toMeters(newVelocity), toMeters(sf::Vector2f(0, 0)), true);
}

Ball::~Ball()
{
    //dtor
}
