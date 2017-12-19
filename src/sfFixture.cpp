#include "sfFixture.h"
#include "Box2DFunctions.h"
sfFixture::sfFixture()
{
    //ctor
}

std::size_t sfFixture::getPointCount() const
{
    const b2Shape* shape = this->GetShape();
    b2Shape::Type shapeType = GetType();

    if(shapeType == b2Shape::e_polygon)
    {
        const b2PolygonShape* polygonShape = static_cast<const b2PolygonShape*>(GetShape());
        return polygonShape->GetVertexCount();
    }
    else if(shapeType == b2Shape::e_circle)
    {
        const b2CircleShape* circle = static_cast<const b2CircleShape*>(GetShape());
        return circle->GetVertexCount();
    }
}

sf::Vector2f sfFixture::getPoint(std::size_t index) const
{
    const b2Shape* shape = this->GetShape();
    b2Shape::Type shapeType = GetType();
    b2Vec2 worldPoint;
    if(shapeType == b2Shape::e_polygon)
    {
        const b2PolygonShape* polygonShape = static_cast<const b2PolygonShape*>(GetShape());

         worldPoint = GetBody()->GetWorldPoint(polygonShape->GetVertex(index));
    }
    else if(shapeType == b2Shape::e_circle)
    {
        const b2CircleShape* circle = static_cast<const b2CircleShape*>(GetShape());
        worldPoint = GetBody()->GetWorldPoint(circle->GetVertex(index));
    }

    return toPixles(worldPoint);
}

sfFixture::~sfFixture()
{
    //dtor
}
