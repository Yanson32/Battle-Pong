#include "States/IntroState.h"
#include "GameUtilities/Engin/Engin.h"
#include <GameUtilities/Event/Event.h>
#include <GameUtilities/Event/EventQueue.h>


#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <SFML/Graphics/Font.hpp>
#include <iostream>

#include "States/PlayState.h"
#include "Settings.h"

#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Objects/Paddle.h"
#include "States/OptionsState.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"


#include "ResourceManager.h"

IntroState::IntroState(Engin::Engin& newEngin): StateBase(newEngin)
{
    //ctor
    ball->setPosition({400, 300});
    ball->setVelocity({100, 100});
    leftPaddle->setPosition(sf::Vector2f(100, 300));
    rightPaddle->setPosition(sf::Vector2f(700, 300));
    header.setString(Settings::inst().getTitle());
    header.setCharacterSize(54);
    header.setColor(sf::Color::White);
    header.setFont(ResourceManager::font.get("Header Font"));
    header.setPosition(sf::Vector2f(335, 25));
    header.setStyle(sf::Text::Bold);

    tgui::Button::Ptr startButton = tgui::Button::create("Start");
    startButton->connect("pressed", &IntroState::onStartPressed, this);
    startButton->setPosition({300, 300});
    startButton->setSize(200, 25);
    gui.add(startButton);


    tgui::Button::Ptr optionButton = tgui::Button::create("Options");
    optionButton->connect("pressed", &IntroState::onOptionsPressed, this);
    optionButton->setPosition({300, 350});
    optionButton->setSize(200, 25);
    gui.add(optionButton);

    reset();

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
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);

        gameEvents();
    }

}

void IntroState::Update(Engin::Engin& engin)
{

    world->Step( timeStep, velocityIterations, positionIterations);
    debugDraw.update();
    ball->update();
    ground->update();
    celing->update();
    leftWall->update();
    RightWall->update();
    leftPaddle->update();
    rightPaddle->update();
}

void IntroState::Draw(Engin::Engin& engin)
{
	StateBase::Draw(engin);
	window.draw(header);
    gui.draw();
    window.display();
}


void IntroState::onStartPressed()
{
    gui.removeAllWidgets();
    engin.Push<PlayState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

void IntroState::onOptionsPressed()
{
    gui.removeAllWidgets();
    engin.Push<OptionsState>(engin);
    EventManager::inst().Post<PlaySound>("Button Sound");
}

IntroState::~IntroState()
{
    //dtor


}
