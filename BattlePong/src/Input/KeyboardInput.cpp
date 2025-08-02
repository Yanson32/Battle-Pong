#include "Input/KeyboardInput.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "Objects/Paddle.h"
#include "Macros.h"
#include "Settings.h"
#include "SFMLFunctions.h"

KeyboardInput::KeyboardInput(Paddle &newPaddle): Input(newPaddle)
{
    //ctor
}

void KeyboardInput::handleInput(const Ball &ball)
{
    UNUSED(ball);
    int MOVE_SPEED = Settings::paddleSpeed;
    sf::Vector2f up(0, -MOVE_SPEED);
    sf::Vector2f down(0, MOVE_SPEED);
    if(sf::Keyboard::isKeyPressed(toKey(Settings::keyboardControlDown)))
    {
        paddle.move(down);
    }
    else if(sf::Keyboard::isKeyPressed(toKey(Settings::keyboardControlUp)))
    {
        paddle.move(up);
    }
    else
    {
        paddle.move({0, 0});
    }
}

KeyboardInput::~KeyboardInput()
{
    //dtor
}
