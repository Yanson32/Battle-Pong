#include "AI.h"
#include "Ball.h"
#include "Paddle.h"


AI::AI(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}


void AI::handleInput(const Ball &ball)
{
    const int MOVE_SPEED = 1;
    sf::Vector2f ballPos = ball.getPosition();
    sf::Vector2f paddlePos = paddle.getPosition();

    if(ballPos.y > paddlePos.y)
    {
        paddlePos.y += MOVE_SPEED;
        paddle.setPosition(paddlePos);
    }
    else if(ballPos.y < paddlePos.y)
    {
        paddlePos.y -= MOVE_SPEED;
        paddle.setPosition(paddlePos);
    }
}


AI::~AI()
{
    //dtor
}
