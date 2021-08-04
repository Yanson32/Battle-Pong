#include "Objects/PaddleStop.h"
#include "Settings.h"
#include "Objects/ObjectId.h"

PaddleStop::PaddleStop(std::shared_ptr<b2World> newWorld):
ObjectBase<sf::ConvexShape>::ObjectBase(newWorld)
{
    const float &wWidth = Settings::window.dimensions.x;
    const float &wHeight = Settings::wallThickness;
    
    const int SIZE = 4;

    b2Vec2 vertices[SIZE];
    vertices[0].Set(toMeters(0), toMeters(0));
    vertices[1].Set(toMeters(wWidth), toMeters(0));
    vertices[2].Set(toMeters(wWidth), toMeters(wHeight * 2));
    vertices[3].Set(toMeters(0), toMeters(wHeight * 2));

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

}


void PaddleStop::update()
{

}


PaddleStop::~PaddleStop()
{

}
