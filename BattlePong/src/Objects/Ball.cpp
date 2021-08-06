#include "Objects/Ball.h"
#include <Box2D/Box2D.h>
#include "Box2D/Box2DFunctions.h"
#include "Events/EventId.h"
#include "Objects/ObjectId.h"

Ball::Ball(std::shared_ptr<b2World> world, const unsigned radius): ObjectBase(world)
{

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;

    //ctor
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 0);
    bodyDef.angle = 0;
    bodyDef.gravityScale = 0;
    bodyDef.bullet = true;
    bodyDef.userData = new int(ObjectId::BALL);
    bodyDef.fixedRotation = false;

    body = world->CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = toMeters(radius);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &circleShape;
    bodyFixture.friction = 0.0f;
    bodyFixture.restitution = 1.0f;
    bodyFixture.density = 1.0f;

    body->CreateFixture(&bodyFixture);




    shape.setFillColor(sf::Color::Green);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

void Ball::update()
{
    shape.setPosition(toPixles(body->GetPosition()));
}

void Ball::setVelocity(const sf::Vector2f &newVelocity)
{
    b2Vec2 velocity(toMeters(newVelocity.x), toMeters(newVelocity.y));
    velocity.Normalize(); 
    velocity *= 3.0;
    body->SetLinearVelocity(velocity);
}




Ball::~Ball()
{
    //dtor
}
