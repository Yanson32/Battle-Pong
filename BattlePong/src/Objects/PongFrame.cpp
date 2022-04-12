#include "Objects/PongFrame.h"
#include "Settings.h"
#include <GameUtilities/Core/Macros.h>

PongFrame::PongFrame(const sf::Vector2f &windowSize)
{
    world.reset(new b2World(b2Vec2(0, 0)));

    const float &wWidth = windowSize.x;
    const float &wHeight = windowSize.y;
    const float &wallTh = Settings::wallThickness;
    float paddleHeight = 100;
    std::array<sf::Vector2f, 4> horizontalPoints = {sf::Vector2f(0, 0), sf::Vector2f(wWidth, 0), sf::Vector2f(wWidth, wallTh), sf::Vector2f(-wWidth, wallTh)};
    std::array<sf::Vector2f, 4> verticalPoints = {sf::Vector2f(0, 0), sf::Vector2f(wallTh, 0), sf::Vector2f(wallTh, wHeight), sf::Vector2f(0, wHeight)};
    std::array<sf::Vector2f, 4> paddlePoints = {sf::Vector2f(0, 0), sf::Vector2f(wallTh, 0), sf::Vector2f(wallTh, paddleHeight),sf::Vector2f(0, paddleHeight)};
    std::array<sf::Vector2f, 4> goalPoints = {sf::Vector2f(0, 0), sf::Vector2f(wallTh, 0), sf::Vector2f(wallTh, wHeight), sf::Vector2f(0, wHeight)};

    ball.reset(new Ball(world, 10));

    ground.reset(new Wall(world, horizontalPoints));
    ground->setPosition({0, wHeight - wallTh});

    celing.reset(new Wall(world, horizontalPoints));
    celing->setPosition({0, 0});

    leftWall.reset(new Wall(world, verticalPoints));
    leftWall->setPosition({0, 0});

    rightWall.reset(new Wall(world, verticalPoints));
    rightWall->setPosition({wWidth - (wallTh), 0});

    leftPaddle.reset(new Paddle(world, ObjectId::LEFT_PADDLE, paddlePoints));
    leftPaddle->setInput(std::unique_ptr<AI>(new AI(*leftPaddle)));
    leftPaddle->setColor(sf::Color(255, 100, 0));

    rightPaddle.reset(new Paddle(world, ObjectId::RIGHT_PADDLE, paddlePoints));
    rightPaddle->setInput(std::unique_ptr<AI>(new AI(*rightPaddle)));
    rightPaddle->setColor(sf::Color::Blue);

    leftGoal.reset(new Goal(world, ObjectId::RIGHT_GOAL, goalPoints));
    leftGoal->setPosition(sf::Vector2f(wallTh, 0));

    rightGoal.reset(new Goal(world, ObjectId::LEFT_GOAL, goalPoints));
    rightGoal->setPosition(sf::Vector2f(wWidth - (wallTh * 2), 0));

    bottomPaddleStop.reset(new PaddleStop(world, horizontalPoints));
    bottomPaddleStop->setPosition({0, wHeight - (wallTh * 2)});

    topPaddleStop.reset(new PaddleStop(world, horizontalPoints));
    topPaddleStop->setPosition({0, (wallTh)});

    world->SetContactListener(&contactListener);
}
void PongFrame::Init()
{

}


void PongFrame::Clean()
{

}


void PongFrame::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime)
{
  UNUSED(engin);
  UNUSED(deltaTime);
}


void PongFrame::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
  UNUSED(engin);
  UNUSED(deltaTime);
}


void PongFrame::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{
  UNUSED(engin);
  UNUSED(deltaTime);
}


PongFrame::~PongFrame()
{

}
