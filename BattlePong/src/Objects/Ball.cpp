#include "Objects/Ball.h"
#include <Box2D/Box2D.h>
#include "Box2D/Box2DFunctions.h"
#include "Events/EventId.h"
#include "Objects/ObjectId.h"
#include "Settings.h"

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
    velocity *= static_cast<float>(Settings::ballSpeed);
    body->SetLinearVelocity(velocity);
}

sf::Packet& operator <<(sf::Packet& packet, const std::shared_ptr<Ball> m)
{
    assert(m->body != nullptr);
    packet << float32(m->body->GetLinearVelocity().x) << float32(m->body->GetLinearVelocity().y); 
    packet << float32(m->body->GetPosition().x) << float32(m->body->GetPosition().y);
    packet << float32(m->body->GetAngle()) << float32(m->body->GetAngularVelocity());
    return packet;
}
 
sf::Packet& operator >>(sf::Packet& packet, std::shared_ptr<Ball> m)
{
    assert(m->body != nullptr);
    float32 velocity_x;
    float32 velocity_y;
    float32 position_x;
    float32 position_y;
    float32 angle; 
    float32 angularVelocity;
    packet >> velocity_x >> velocity_y >> position_x >> position_y >> angle >> angularVelocity;
    m->body->SetLinearVelocity(b2Vec2(velocity_x, velocity_y));
    m->body->SetTransform(b2Vec2(position_x, position_y), angle);
    m->body->SetAngularVelocity(angularVelocity);
    return packet;
}


Ball::~Ball()
{
    if(body != nullptr)
    {
        if(body->GetUserData() != nullptr)
        {
            int * data = static_cast<int*>(body->GetUserData());
            delete data;
            data = nullptr;
            body->SetUserData(nullptr);
        }
    }
    //dtor
}
