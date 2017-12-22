#include "PlayerInput.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "Paddle.h"

PlayerInput::PlayerInput(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}

void PlayerInput::handleInput(const Ball &ball)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sf::Vector2f pos = paddle.getPosition();
        pos.y += 1;
        paddle.setPosition(pos);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sf::Vector2f pos = paddle.getPosition();
        pos.y -= 1;
        paddle.setPosition(pos);
    }
}

PlayerInput::~PlayerInput()
{
    //dtor
}
