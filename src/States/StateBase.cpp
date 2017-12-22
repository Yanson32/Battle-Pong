#include "States/StateBase.h"
#include "Settings.h"
#include "Ball.h"
#include "Wall.h"
#include "Paddle.h"
#include "AI.h"

sf::RenderWindow StateBase::window(Settings::inst().getWindowSettings().getVideoMode(), Settings::inst().getTitle());
std::unique_ptr<b2World> StateBase::world(new b2World(b2Vec2(0, 0)));
tgui::Gui StateBase::gui(window);
DebugDraw StateBase::debugDraw(*world);

Ball* StateBase::ball = new Ball(*world);

namespace
{
    std::array<sf::Vector2f, 4> horizontalPoints = {sf::Vector2f(-400, -25), sf::Vector2f(400, -25), sf::Vector2f(400, 25), sf::Vector2f(-400, 25)};
    std::array<sf::Vector2f, 4> verticalPoints = {sf::Vector2f(-25, -300), sf::Vector2f(25, -300), sf::Vector2f(25, 300), sf::Vector2f(-25, 300)};
    std::array<sf::Vector2f, 4> paddlePoints = {sf::Vector2f(-10, -50), sf::Vector2f(10, -50), sf::Vector2f(10, 50),sf::Vector2f(-10, 50)};
}
Wall* StateBase::ground = new Wall(*world, horizontalPoints);
Wall* StateBase::celing = new Wall(*world, horizontalPoints);
Wall* StateBase::leftWall = new Wall(*world, verticalPoints);
Wall* StateBase::RightWall = new Wall(*world, verticalPoints);


Paddle* StateBase::leftPaddle = new Paddle(*world, paddlePoints);
Paddle* StateBase::rightPaddle = new Paddle(*world, paddlePoints);

StateBase::StateBase(): Engin::GameState()
{

    ball->setPosition({400, 300});
    ball->setVelocity({100, 100});






    leftPaddle->setPosition(sf::Vector2f(100, 100));
    leftPaddle->setInput(std::unique_ptr<AI>(new AI(*leftPaddle)));


    rightPaddle->setPosition(sf::Vector2f(700, 100));
    rightPaddle->setInput(std::unique_ptr<AI>(new AI(*rightPaddle)));

    ground->setPosition({400, 600});
    celing->setPosition({400, 0});
    leftWall->setPosition({0, 300});
    RightWall->setPosition({800, 300});

    world->SetDebugDraw(&debugDraw);

    debugDraw.SetFlags(b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_shapeBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
}


//void StateBase::Update(Engin::Engin& engin)
//{
//    if(!IsPaused())
//    {
//        world->Step(timeStep, velocityIterations, positionIterations);
//    }
//}



StateBase::~StateBase()
{

}
