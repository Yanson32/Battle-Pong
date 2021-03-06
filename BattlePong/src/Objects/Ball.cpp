#include "Objects/Ball.h"
#include <Box2D/Box2D.h>
#include "Box2D/Box2DFunctions.h"
#include "Events/Id.h"

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

    b2Fixture *fix = body->CreateFixture(&bodyFixture);




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
    float x = (newVelocity.x > MINIMUM_X_VEL)? newVelocity.x : MINIMUM_X_VEL;
    float y = (newVelocity.y > MINIMUM_Y_VEL)? newVelocity.y : MINIMUM_Y_VEL;

    body->SetLinearVelocity(toMeters({x, y}));
}




Ball::~Ball()
{
    //dtor
}
