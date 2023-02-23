#include "Objects/Paddle.h"
#include "Box2D/Box2DFunctions.h"
#include "Objects/ObjectId.h"

Paddle::Paddle(std::shared_ptr<b2World> world, const ObjectId &newId, const std::array<sf::Vector2f, 4> vert):
ObjectBase<sf::ConvexShape>::ObjectBase(world)
{

    const int SIZE = 4;

    b2Vec2 vertices[SIZE];
    vertices[0].Set(toMeters(vert[0]).x, toMeters(vert[0]).y);
    vertices[1].Set(toMeters(vert[1]).x, toMeters(vert[1]).y);
    vertices[2].Set(toMeters(vert[2]).x, toMeters(vert[2]).y);
    vertices[3].Set(toMeters(vert[3]).x, toMeters(vert[3]).y);

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;


    //ctor
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 0);
    bodyDef.angle = 0;
    bodyDef.gravityScale = 0;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    bodyDef.userData = new int(newId);

    body = world->CreateBody(&bodyDef);

    bodyDef.type = b2_staticBody;
    jointBody = world->CreateBody(&bodyDef);

    b2PolygonShape polyShape;
    polyShape.Set(vertices, SIZE);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &polyShape;
    bodyFixture.friction = 1;
    bodyFixture.restitution = 0;
    bodyFixture.density = 100;
    bodyFixture.filter.categoryBits = ObjectId::RIGHT_PADDLE | ObjectId::LEFT_PADDLE; 
    bodyFixture.filter.maskBits = ObjectId::BALL | ObjectId::PADDLE_STOP; 
    body->CreateFixture(&bodyFixture);

    //Create the joint
    b2PrismaticJointDef jointDef;
    jointDef.bodyA = jointBody;
    jointDef.bodyB = body;
    jointDef.collideConnected = false;
    jointDef.localAxisA = b2Vec2(0.0f, 1.0f);
    jointDef.enableLimit = true;
    jointDef.upperTranslation = toMeters(225);
    jointDef.lowerTranslation = toMeters(-225);

    prisJoint = static_cast<b2PrismaticJoint*>(world->CreateJoint(&jointDef));

    shape.setFillColor(sf::Color::Red);
    shape.setPointCount(SIZE + 1);
    shape.setPoint(0, sf::Vector2f(vert[0].x, vert[0].y));
    shape.setPoint(1, sf::Vector2f(vert[1].x, vert[1].y));
    shape.setPoint(2, sf::Vector2f(vert[2].x, vert[2].y));
    shape.setPoint(3, sf::Vector2f(vert[3].x, vert[3].y));
    shape.setPoint(4, sf::Vector2f(vert[0].x, vert[0].y));

}

void Paddle::move(const sf::Vector2f &direction)
{
    body->SetLinearVelocity(toMeters(direction));
}

void Paddle::update()
{
    shape.setPosition(toPixles(body->GetPosition()));
}

void Paddle::setPosition(const sf::Vector2f &position)
{
    body->SetTransform(toMeters(position), body->GetAngle());
    jointBody->SetTransform(toMeters(position), jointBody->GetAngle());
}

sf::Vector2f Paddle::getPosition() const
{
    b2Vec2 vec = body->GetPosition();
    return toPixles(vec);
}

void Paddle::handleInput(const Ball &ball)
{
   if(input.get())
        input->handleInput(ball);
}

void Paddle::setInput(std::unique_ptr<Input> newInput)
{
    input = std::move(newInput);
}
Paddle::~Paddle()
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
}
