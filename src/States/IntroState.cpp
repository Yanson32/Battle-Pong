#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Font.hpp>
#include <iostream>

#include "States/PlayState.h"
#include "Settings.h"

IntroState::IntroState(Engin::Engin& newEngin): StateBase(), engin(newEngin)
{
    //ctor


    if(!headerFont.loadFromFile("/home/me/Desktop/Pong/Build/Resources/Fonts/caviar-dreams/CaviarDreams.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
        std::exit(1);
    }
    header.setString(Settings::inst().getTitle());
    header.setCharacterSize(54);
    header.setColor(sf::Color::White);
    header.setFont(headerFont);
    header.setPosition(sf::Vector2f(350, 0));
    header.setStyle(sf::Text::Bold);

    tgui::Button::Ptr button = tgui::Button::create("Start");
    button->connect("pressed", &IntroState::onStartPressed, this);
    button->setPosition({300, 300});
    button->setSize(200, 25);
    gui.add(button);
}


void IntroState::HandleEvents(Engin::Engin& engin)
{
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            gui.handleEvent(event);
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

    }
}

void IntroState::Draw(Engin::Engin& engin)
{
	window.clear(background);
    window.draw(header);
    gui.draw();
	window.display();
}


void IntroState::onStartPressed()
{
    clean();
    engin.ChangeState<PlayState>();
}

void IntroState::clean()
{

}

IntroState::~IntroState()
{
    //dtor
}
