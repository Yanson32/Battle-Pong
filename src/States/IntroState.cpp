#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Font.hpp>
#include <iostream>

IntroState::IntroState(): StateBase()
{
    //ctor


    if(!headerFont.loadFromFile("/home/me/Desktop/Pong/Build/Resources/Fonts/caviar-dreams/CaviarDreams.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        std::exit(1);
    }
    header.setString("Test");
    header.setCharacterSize(28);
    header.setColor(sf::Color::Blue);
    header.setFont(headerFont);
    header.setPosition(sf::Vector2f(0, 0));
    header.setStyle(sf::Text::Bold | sf::Text::Underlined);
}


void IntroState::HandleEvents(Engin::Engin& engin)
{

    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            switch (event.type)
            {

                case sf::Event::Closed:
					engin.Quit();
                    break;


                case sf::Event::KeyPressed:
                    break;

                default:
                    break;
            }
        }
    }
}

void IntroState::Update(Engin::Engin& engin)
{
    if(!IsPaused())
    {
        world->Step(timeStep, velocityIterations, positionIterations);
    }
}

void IntroState::Draw(Engin::Engin& engin)
{
	window.clear(background);
    window.draw(header);
	window.display();
}

IntroState::~IntroState()
{
    //dtor
}
