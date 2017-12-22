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

StateBase::StateBase(): Engin::GameState()
{
    ball = new Ball(*world);
    ball->setPosition({400, 300});
    ball->setVelocity({100, 100});

    std::array<sf::Vector2f, 4> horizontalPoints;
    horizontalPoints[0] = sf::Vector2f(-400, -25);
    horizontalPoints[1] = sf::Vector2f(400, -25);
    horizontalPoints[2] = sf::Vector2f(400, 25);
    horizontalPoints[3] = sf::Vector2f(-400, 25);

    std::array<sf::Vector2f, 4> verticalPoints;
    verticalPoints[0] = sf::Vector2f(-25, -300);
    verticalPoints[1] = sf::Vector2f(25, -300);
    verticalPoints[2] = sf::Vector2f(25, 300);
    verticalPoints[3] = sf::Vector2f(-25, 300);

    ground = new Wall(*world, horizontalPoints);
    celing = new Wall(*world, horizontalPoints);
    leftWall = new Wall(*world, verticalPoints);
    RightWall = new Wall(*world, verticalPoints);

    std::array<sf::Vector2f, 4> leftPaddlePoints;
    leftPaddlePoints[0] = sf::Vector2f(-10, -50);
    leftPaddlePoints[1] = sf::Vector2f(10, -50);
    leftPaddlePoints[2] = sf::Vector2f(10, 50);
    leftPaddlePoints[3] = sf::Vector2f(-10, 50);

    leftPaddle = new Paddle(*world, leftPaddlePoints);
    leftPaddle->setPosition(sf::Vector2f(100, 100));
    leftPaddle->setInput(std::unique_ptr<AI>(new AI(*leftPaddle)));

    std::array<sf::Vector2f, 4> rightPaddlePoints;
    rightPaddlePoints[0] = sf::Vector2f(-10, -50);
    rightPaddlePoints[1] = sf::Vector2f(10, -50);
    rightPaddlePoints[2] = sf::Vector2f(10, 50);
    rightPaddlePoints[3] = sf::Vector2f(-10, 50);

    rightPaddle = new Paddle(*world, rightPaddlePoints);
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
