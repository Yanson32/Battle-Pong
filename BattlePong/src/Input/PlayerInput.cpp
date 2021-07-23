#include "Input/PlayerInput.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "Objects/Paddle.h"
#include "Macros.h"

PlayerInput::PlayerInput(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}

void PlayerInput::handleInput(const Ball &ball)
{
    UNUSED(ball);
    const  int MOVE_SPEED = 200;
    sf::Vector2f up(0, -MOVE_SPEED);
    sf::Vector2f down(0, MOVE_SPEED);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        paddle.move(down);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        paddle.move(up);
    }
    else
    {
        paddle.move({0, 0});
    }
}

PlayerInput::~PlayerInput()
{
    //dtor
}
