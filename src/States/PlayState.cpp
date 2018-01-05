#include "States/PlayState.h"
#include "Objects/Ball.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include <Box2D/Box2D.h>
#include <iostream>
#include "Box2D/Box2DFunctions.h"
#include <SFML/Graphics/CircleShape.hpp>

#include "Objects/Wall.h"
#include "Objects/Paddle.h"
#include "Input/AI.h"
#include "Input/PlayerInput.h"
#include "Settings.h"
#include "Events/EventManager.h"
#include "Events/PlaySound.h"
#include "Events/PlayMusic.h"
#include "ResourceManager.h"
#include "States/OptionsState.h"

PlayState::PlayState(Engin::Engin& newEngin): StateBase(newEngin)
{


    sf::String p1Input = Settings::inst().paddle1->getInputType();
    if(p1Input == "None")
        leftPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*leftPaddle)));
    else
        leftPaddle->setInput(std::unique_ptr<Input>(new AI(*leftPaddle)));


    sf::String p1Input2 = Settings::inst().paddle2->getInputType();
    if(p1Input2 == "None")
        rightPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*rightPaddle)));
    else
        rightPaddle->setInput(std::unique_ptr<Input>(new AI(*rightPaddle)));

    systemPause(true);
    userMessage.setCharacterSize(34);
    userMessage.setPosition(sf::Vector2f(400, 300));
    reset();


}

void PlayState::HandleEvents(Engin::Engin& engin, const int &deltaTime)
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
                    if(event.key.code == sf::Keyboard::P)
                    {
                        if(!isSystemPaused())
                            Pause(!IsPaused());
                    }
                    break;

                default:
                    break;
            }
        }
        gameEvents();
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Pause();
            engin.Push<OptionsState>(engin);
        }
    }

}

void PlayState::Update(Engin::Engin& engin, const int &deltaTime)
{
    const int SECONDS = 1;

        if(!IsPaused())
        {
            if(!isSystemPaused())
            {
                world->Step( timeStep, velocityIterations, positionIterations);
            }
            debugDraw.update();
            ball->update();
            ground->update();
            celing->update();
            leftWall->update();
            RightWall->update();
            leftPaddle->update();
            rightPaddle->update();

        }

    {
        if(userMessage.getString() == "Ready!")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("3");
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "3")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("2");
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "2")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("1");
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "1")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("Go!");
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "Go!")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("");
                messageClock.restart();
                //EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
                systemPause(false);
            }
        }
    }
}

void PlayState::Draw(Engin::Engin& engin, const int &deltaTime)
{

    StateBase::Draw(engin, deltaTime);
    window.draw(userMessage);
    window.display();
}

void PlayState::Init()
{
    ResourceManager::sound.load("Message Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Button Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "/home/me/Desktop/Pong/Build/Resources/Sounds/tone1.ogg");
    ResourceManager::font.load("Header Font", "/home/me/Desktop/Pong/Build/Resources/Fonts/caviar-dreams/CaviarDreams.ttf");

    userMessage.setFont(ResourceManager::font.get("Header Font"));
}

void PlayState::Clean()
{
    gui.removeAllWidgets();

    ResourceManager::sound.remove("Message Sound");
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    ResourceManager::font.remove("Header Font");

}

PlayState::~PlayState()
{

}
