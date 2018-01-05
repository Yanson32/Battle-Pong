#include "Input/AI.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include <cmath>

AI::AI(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}


void AI::handleInput(const Ball &ball)
{
    const int MOVE_SPEED = 200;
    sf::Vector2f ballPos = ball.getPosition();
    sf::Vector2f paddlePos = paddle.getPosition();

    float difference = std::abs(ballPos.y - paddlePos.y);
    float movement = (difference > MOVE_SPEED)? MOVE_SPEED : difference;
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
