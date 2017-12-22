#include "States/IntroState.h"
#include <iostream>
#include <Box2D/Box2D.h>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "Game.h"

int main()
{

    sf::Clock timer;
    const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
    sf::Time accumulator = sf::seconds(0);

	Game engin;
	engin.Push<IntroState>(engin);

	while (engin.IsRunning())
	{
        accumulator += timer.restart();
        engin.HandleEvents();
        while(accumulator.asSeconds() >= deltaTime.asSeconds())
        {
            engin.Update();
            accumulator -= deltaTime;
        }
		engin.Draw();
	}

}
