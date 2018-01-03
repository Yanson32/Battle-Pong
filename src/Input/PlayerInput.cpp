#include "Input/PlayerInput.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "Objects/Paddle.h"

PlayerInput::PlayerInput(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}

void PlayerInput::handleInput(const Ball &ball)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        paddle.move({0, 200});
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        paddle.move({0, -200});
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
