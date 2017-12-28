#include "Objects/Paddle.h"
#include "Box2D/Box2DFunctions.h"
#include <iostream>



Paddle::Paddle(b2World &world, const ObjectId &newId, const std::array<sf::Vector2f, 4> vert):
ObjectBase<sf::ConvexShape>::ObjectBase()
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

    body = world.CreateBody(&bodyDef);

    bodyDef.type = b2_staticBody;
    jointBody = world.CreateBody(&bodyDef);

    b2PolygonShape polyShape;
    polyShape.Set(vertices, SIZE);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &polyShape;
    bodyFixture.friction = 1;
    bodyFixture.restitution = 0;
    bodyFixture.density = 100;

    b2Fixture *fix = body->CreateFixture(&bodyFixture);

    //Create the joint
    b2PrismaticJointDef jointDef;
    jointDef.bodyA = jointBody;
    jointDef.bodyB = body;
    jointDef.collideConnected = false;
    jointDef.localAxisA = b2Vec2(0.0f, 1.0f);
    jointDef.enableLimit = true;
    jointDef.upperTranslation = toMeters(225);
    jointDef.lowerTranslation = toMeters(-225);

    prisJoint = static_cast<b2PrismaticJoint*>(world.CreateJoint(&jointDef));

    shape.setFillColor(sf::Color::Red);
    shape.setPointCount(SIZE);


}

void Paddle::move(const sf::Vector2f &direction)
{
    body->SetLinearVelocity(toMeters(direction));
}

void Paddle::update()
{
    sf::Vector2f bodyPosition = toPixles(body->GetPosition());

    for(b2Fixture *fix = body->GetFixtureList(); fix; fix = fix->GetNext())
    {
        b2Shape::Type shapeType = fix->GetType();

        if(shapeType == b2Shape::e_circle)
        {
            b2CircleShape* circleShape = (b2CircleShape*)fix->GetShape();
            int vertCount = circleShape->GetVertexCount();
            shape.setPointCount(vertCount);
            for(int i = 0; i < vertCount; ++i)
            {
                b2Vec2 vert = body->GetWorldPoint(circleShape->GetVertex(i));
                sf::Vector2f sfVert(toPixles(vert));
                shape.setPoint(i, sfVert);

            }

        }
        if(shapeType == b2Shape::e_polygon)
        {
            b2PolygonShape* poly = (b2PolygonShape*)fix->GetShape();
            int vertCount = poly->GetVertexCount();
            shape.setPointCount(vertCount);
            for(int i = 0; i < vertCount; ++i)
            {
                b2Vec2 vert = body->GetWorldPoint(poly->GetVertex(i));
                sf::Vector2f sfVert(toPixles(vert));
                shape.setPoint(i, sfVert);

            }
        }
    }
}

void Paddle::setPosition(const sf::Vector2f &position)
{
    body->SetTransform(toMeters(position), body->GetAngle());
    sf::Vector2f tempPos = position;
    tempPos.y -= toMeters(200);
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
}
