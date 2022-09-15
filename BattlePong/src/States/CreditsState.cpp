#include "States/CreditsState.h"
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
#include "Resources/ResourceManager.h"
#include "Events/Events.h"
#include "Macros.h"
#include "Gui/PlayPanel.h"
#include "Gui/GuiId.h"
#include "States/IntroState.h"
#include <GameUtilities/Event/LogEvent.h>
#include <GameUtilities/Core/Macros.h>
#include "Log.h"

CreditsState::CreditsState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId): StateBase(newEngin, newWindow, debugDraw, newGui, newId)
{
  BP_LOG_TRACE(__FUNCTION__)
}

void CreditsState::handleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(deltaTime);

    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
      BP_LOG_FATAL_ERROR("Pointer should not be null")
      return;
    }
    if(window.isOpen())
    {
        sf::Event event;
        BP_LOG_MESSAGE("SFML Event Loop")
        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event, frame);
            sfEvent(engin, event, frame);
            gui.handleEvent(event);
        }
        pongFrame->leftPaddle->handleInput(*pongFrame->ball);
        pongFrame->rightPaddle->handleInput(*pongFrame->ball);
    }
    
    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr, frame);
    }
}

void CreditsState::update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    const int SECONDS = 1;

    StateBase::update(engin, deltaTime, frame);

    if(!isPaused())
    {
        if(!isSystemPaused())
        {
            pongFrame->world->Step( deltaTime, Settings::velocityIterations, Settings::positionIterations);
        }
        debugDraw.update();
        pongFrame->ball->update();
        pongFrame->ground->update();
        pongFrame->celing->update();
        pongFrame->leftWall->update();
        pongFrame->rightWall->update();
        pongFrame->leftPaddle->update();
        pongFrame->rightPaddle->update();

    }


    if(userMessage.getString() == "Ready!")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("3");
            centerText();
            messageClock.restart();
            //EventManager::inst().post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "3")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("2");
            centerText();
            messageClock.restart();
            //EventManager::inst().post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "2")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("1");
            centerText();
            messageClock.restart();
            //EventManager::inst().post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "1")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("Go!");
            centerText();
            messageClock.restart();
            //EventManager::inst().post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "Go!")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("");
            messageClock.restart();
            //EventManager::inst().post<PlaySound>(sf::String("Message Sound"));
            systemPause(false);
        }
    }

}

void CreditsState::draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    StateBase::draw(engin, deltaTime, frame);
    if(userMessage.getString() == "")
        window.draw(*pongFrame->ball);
    window.draw(userMessage);


    window.display();

}

void CreditsState::init(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(frame);

    StateBase::init(frame);
    Settings::stateId = StateId::CREDITS_STATE;

    //Crate pong frame
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }


    userMessage.setCharacterSize(34);
    userMessage.setPosition(sf::Vector2f(400, 300));

    //Load ball sound
    ResourceManager::loadSound(soundId::BALL, "BallCollision.ogg");


    centerText();
}

void CreditsState::clean(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(frame);
    gui.removeAllWidgets();

    //Remove ball sound
    if(ResourceManager::isLoaded(soundId::BALL))
        ResourceManager::remove(soundId::BALL);
}

void CreditsState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(engin);

    switch(event.type)
    {
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                {
                    Game *game = static_cast<Game*>(&engin);
                    game->setPop(true);
                }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }


}

void CreditsState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::handleGUEvent(engin, event, frame);
}

CreditsState::~CreditsState()
{
  BP_LOG_TRACE(__FUNCTION__)
}
