#include "Input/AI.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include <cmath>
#include <iostream>
#include "Settings.h"

AI::AI(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}


void AI::handleInput(const Ball &ball)
{
    int MOVE_SPEED = Settings::paddleSpeed;

    sf::Vector2f ballPos = ball.getPosition();
    sf::Vector2f paddlePos = paddle.getPosition();

    float difference = std::abs(ballPos.y - paddlePos.y);
    float movement = (difference > MOVE_SPEED)? MOVE_SPEED : difference;
    //std::cout << "Movement " << movement << std::endl;
    if(ballPos.y > paddlePos.y)
    {
        paddle.move({0, movement});
        //paddlePos.y = movement;
        //paddle.setVelocity(paddlePos);
    }
    else if(ballPos.y < paddlePos.y)
    {
        paddle.move({0, -movement});
    }

    //paddle.setPosition({paddlePos.x, ballPos.y});
}


AI::~AI()
{
    //dtor
}
