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

StateBase::StateBase(Engin::Engin& newEngin): Engin::GameState(), engin(newEngin), theme{"TGUI/themes/Black.txt"}, sysPause(false)
{


    leftPaddle->setColor(sf::Color(255, 100, 0));
    rightPaddle->setColor(sf::Color::Blue);



    leftPaddle->setInput(std::unique_ptr<AI>(new AI(*leftPaddle)));



    rightPaddle->setInput(std::unique_ptr<AI>(new AI(*rightPaddle)));

    ground->setPosition({400, 600});
    celing->setPosition({400, 0});
    leftWall->setPosition({0, 300});
    RightWall->setPosition({800, 300});

    world->SetDebugDraw(&debugDraw);

    debugDraw.SetFlags(b2Draw::e_aabbBit | b2Draw::e_jointBit | b2Draw::e_shapeBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    world->SetContactListener(&contactListener);

}


//void StateBase::Update(Engin::Engin& engin)
//{
//    if(!IsPaused())
//    {
//        world->Step(timeStep, velocityIterations, positionIterations);
//    }
//}


void StateBase::Draw(Engin::Engin& engin)
{
    window.clear();
    //window.draw(debugDraw);
    window.draw(*leftPaddle);
    window.draw(*rightPaddle);
    window.draw(*ball);
    window.draw(*celing);
    window.draw(*leftWall);
    window.draw(*RightWall);
    window.draw(*ground);
}

void StateBase::systemPause(const bool newSysPause)
{
    sysPause = newSysPause;
}

bool StateBase::isSystemPaused() const
{
    return sysPause;
}

StateBase::~StateBase()
{

}
