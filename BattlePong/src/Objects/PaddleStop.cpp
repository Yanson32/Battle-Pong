#include "Objects/PaddleStop.h"
#include "Settings.h"
#include "Objects/ObjectId.h"
#include <GameUtilities/Core/Macros.h>

PaddleStop::PaddleStop(std::shared_ptr<b2World> newWorld, const std::array<sf::Vector2f, 4> &vert):
ObjectBase<sf::ConvexShape>::ObjectBase(newWorld)
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
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0, 0);
    bodyDef.angle = 0;
    bodyDef.gravityScale = 0;
    bodyDef.fixedRotation = true;
    bodyDef.bullet = true;
    //bodyDef.userData = new int(newId);

    body = world->CreateBody(&bodyDef);

    b2PolygonShape polyShape;
    polyShape.Set(vertices, SIZE);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &polyShape;
    bodyFixture.friction = 1;
    bodyFixture.restitution = 0;
    bodyFixture.density = 100;
    bodyFixture.filter.categoryBits = ObjectId::PADDLE_STOP;
    bodyFixture.filter.maskBits = ObjectId::RIGHT_PADDLE | ObjectId::LEFT_PADDLE;

    body->CreateFixture(&bodyFixture);

    shape.setFillColor(sf::Color::Transparent);
    shape.setPointCount(SIZE);


}

void PaddleStop::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  UNUSED(target);
  UNUSED(states);
}


void PaddleStop::update()
{

}


PaddleStop::~PaddleStop()
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
