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

    if(ballPos.y > paddlePos.y)
    {
        paddle.move({0, MOVE_SPEED});
    }
    else if(ballPos.y < paddlePos.y)
    {
        paddle.move({0, -MOVE_SPEED});
    }
}


AI::~AI()
{
    //dtor
}
