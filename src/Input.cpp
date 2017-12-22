#include "Input.h"
#include "Ball.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "Paddle.h"

Input::Input(Paddle &newPaddle):paddle(newPaddle)
{
    //ctor
}

void Input::handleInput(const Ball &ball)
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

Input::~Input()
{
    //dtor
}
