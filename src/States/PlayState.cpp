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
#include "Events/ChangeState.h"

PlayState::PlayState(GU::Engin::Engin& newEngin, const stateId newId): StateBase(newEngin, newId)
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

void PlayState::HandleEvents(GU::Engin::Engin& engin, const int &deltaTime)
{
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event);
            sfEvent(engin, event);
            gui.handleEvent(event);
        }
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
    }

    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        StateBase::guEvent(engin, evtPtr);
        guEvent(engin, evtPtr);
    }
}

void PlayState::Update(GU::Engin::Engin& engin, const int &deltaTime)
{
    const int SECONDS = 1;

        StateBase::Update(engin, deltaTime);

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
                centerText();
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "3")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("2");
                centerText();
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "2")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("1");
                centerText();
                messageClock.restart();
                EventManager::inst().Post<PlaySound>(sf::String("Message Sound"));
            }
        }
        else if(userMessage.getString() == "1")
        {
            if(messageClock.getElapsedTime().asSeconds() > SECONDS)
            {
                userMessage.setString("Go!");
                centerText();
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

void PlayState::Draw(GU::Engin::Engin& engin, const int &deltaTime)
{

    StateBase::Draw(engin, deltaTime);
    window.draw(userMessage);

    if(userMessage.getString() == "")
        window.draw(*ball);
    window.display();
}

void PlayState::Init()
{
    StateBase::Init();
    ResourceManager::sound.load("Message Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Button Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::sound.load("Ball Sound", "../Resources/Sounds/tone1.ogg");
    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");

    userMessage.setFont(ResourceManager::font.get("Header Font"));
    Settings::inst().paddle1->setScore(0);
    Settings::inst().paddle2->setScore(0);
    paddle1Hud->setScore(0);
    paddle2Hud->setScore(0);
    centerText();
}

void PlayState::Clean()
{
    gui.removeAllWidgets();

    ResourceManager::sound.remove("Message Sound");
    ResourceManager::sound.remove("Button Sound");
    ResourceManager::sound.remove("Ball Sound");
    ResourceManager::font.remove("Header Font");

}

void PlayState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
{

}

void PlayState::guEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
        //GameUtilities event loop
        while(EventManager::inst().Poll((event)))
        {
            //EventManager::inst().Dispatch((evtPtr));
            switch(event->id)
            {

                case EventId::CHANGE_STATE:
                {
                    std::shared_ptr<ChangeState> temp =  std::dynamic_pointer_cast<ChangeState>(event);
                    switch(temp->state)
                    {
                        case stateId::CONNECT_STATE:
                            std::cout << "Playstate Connect state" << std::endl;
                        break;

                    }
                }
                break;

            }

        }
}

PlayState::~PlayState()
{

}
