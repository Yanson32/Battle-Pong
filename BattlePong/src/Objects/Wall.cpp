#include "Objects/Wall.h"
#include <SFML/System/Vector2.hpp>
#include "Box2D/Box2DFunctions.h"
#include "Events/EventId.h"
#include "Macros.h"
#include "Objects/ObjectId.h"

Wall::Wall(std::shared_ptr<b2World> world, const std::array<sf::Vector2f, 4> vert): ObjectBase<sf::ConvexShape>::ObjectBase(world)
{
    //ctor
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
    bodyDef.userData = new int(ObjectId::WALL);

    body = world->CreateBody(&bodyDef);

    b2PolygonShape polyShape;
    polyShape.Set(vertices, SIZE);


    b2FixtureDef bodyFixture;
    bodyFixture.shape = &polyShape;
    bodyFixture.friction = 0;
    bodyFixture.restitution = 1;
    bodyFixture.density = 100;

    body->CreateFixture(&bodyFixture);


    shape.setFillColor(sf::Color::Cyan);
    shape.setPointCount(SIZE);


}

void Wall::update()
{
//    sf::Vector2f bodyPosition = toPixles(body->GetPosition());
//
//    for(b2Fixture *fix = body->GetFixtureList(); fix; fix = fix->GetNext())
//    {
//        b2Shape::Type shapeType = fix->GetType();
//
//        if(shapeType == b2Shape::e_circle)
//        {
//            b2CircleShape* circleShape = (b2CircleShape*)fix->GetShape();
//            int vertCount = circleShape->GetVertexCount();
//            shape.setPointCount(vertCount);
//            for(int i = 0; i < vertCount; ++i)
//            {
//                b2Vec2 vert = body->GetWorldPoint(circleShape->GetVertex(i));
//                sf::Vector2f sfVert(toPixles(vert));
//                shape.setPoint(i, sfVert);
//
//            }
//
//        }
//        if(shapeType == b2Shape::e_polygon)
//        {
//            b2PolygonShape* poly = (b2PolygonShape*)fix->GetShape();
//            int vertCount = poly->GetVertexCount();
//            shape.setPointCount(vertCount);
//            for(int i = 0; i < vertCount; ++i)
//            {
//                b2Vec2 vert = body->GetWorldPoint(poly->GetVertex(i));
//                sf::Vector2f sfVert(toPixles(vert));
//                shape.setPoint(i, sfVert);
//
//            }
//        }
//    }

}


void Wall::setPosition(const sf::Vector2f &position)
{
    body->SetTransform(toMeters(position), body->GetAngle());
}

void Wall::setSize(const sf::Vector2f &size)
{
    UNUSED(size);
}

Wall::~Wall()
{
    //dtor
}
