#include "Ball.h"
#include <Box2D/Box2D.h>
#include "Box2DFunctions.h"
#include <iostream>

Ball::Ball(b2World &world)
{
    const int RADIOUS = 10;

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;

    //ctor
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(toMeters(100), toMeters(100));
    bodyDef.angle = 0;
    bodyDef.gravityScale = 0;
    bodyDef.bullet = true;

    body = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = toMeters(RADIOUS);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &circleShape;
    bodyFixture.friction = 0;
    bodyFixture.restitution = 0.6;
    bodyFixture.density = 1;

    b2Fixture *fix = body->CreateFixture(&bodyFixture);


    body->ApplyLinearImpulse(toMeters(sf::Vector2f(4, 4)), toMeters(sf::Vector2f(0, 0)), true);

    shape.setFillColor(sf::Color::Green);
    shape.setRadius(RADIOUS);
    shape.setOrigin(RADIOUS, RADIOUS);
}

void Ball::update()
{
    shape.setPosition(toPixles(body->GetPosition()));
}


Ball::~Ball()
{
    //dtor
}
