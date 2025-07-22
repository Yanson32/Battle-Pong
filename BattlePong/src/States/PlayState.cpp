#include "States/PlayState.h"
#include "Objects/Ball.h"
#include <SFML/Window/Event.hpp>
#include "Engin/Game.h"
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
#include "Gui/OptionsPanel/GeneralPanel.h"
#include "Gui/OptionsPanel/ControlPanel.h"
#include "Gui/OptionsPanel/VideoPanel.h"
#include "Gui/OptionsPanel/SoundPanel.h"
#include "Gui/OptionsPanel/NetworkPanel.h"
#include "Gui/OptionsPanel/DevPanel.h"
#include <GameUtilities/Event/Events/OnLog.h>
#include <GameUtilities/Core/Macros.h>
#include "Log.h"

PlayState::PlayState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId): StateBase(newEngin, newWindow, debugDraw, newGui, newId)
{
  BP_LOG_TRACE(__FUNCTION__)
}

void PlayState::handleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
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
    BP_LOG_MESSAGE("GameUtilities Game Loop")
    
    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr, frame);
    }
}

void PlayState::update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    Game *game = static_cast<Game*>(&engin);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }

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

    if(Settings::multiplayer)
    {
        if(Settings::isHost)
        {
            game->server.update();
        }   
        else
        {
            game->client.update();
        }
    }
    
}

void PlayState::draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    StateBase::draw(engin, deltaTime, frame);
    window.draw(*pongFrame->ball);
    window.draw(userMessage);


    window.display();

}

void PlayState::init(GU::Engin::Engin& engin, std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    UNUSED(frame);
    
    Game *game = static_cast<Game*>(&engin);

    StateBase::init(engin, frame);
    Settings::stateId = StateId::PLAY_STATE;
    
    //Crate pong frame
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }

    //Setup paddle 1
    pongFrame->paddle1Hud->setScore(0);
    Settings::p1Score = 0;
    if(Settings::p1Input == "None")
        pongFrame->leftPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*pongFrame->leftPaddle)));
    else
        pongFrame->leftPaddle->setInput(std::unique_ptr<Input>(new AI(*pongFrame->leftPaddle)));

    //Setup paddle 2
    pongFrame->paddle2Hud->setScore(0);
    Settings::p2Score = 0;
    if(Settings::p2Input  == "None")
        pongFrame->rightPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*pongFrame->rightPaddle)));
    else
        pongFrame->rightPaddle->setInput(std::unique_ptr<Input>(new AI(*pongFrame->rightPaddle)));

    messageClock.restart();

    //Load ball sound
    ResourceManager::loadSound(soundId::BALL, "BallCollision.ogg");


    reset(pongFrame);
    if(Settings::multiplayer)
    {
        if(Settings::isHost)
        {
            userMessage.setString("Waiting for player 2");
            centerText();
            game->server.init();
            systemPause(true);
            connectThread.reset(new std::thread([this, &engin](){
            Game *game = static_cast<Game*>(&engin);
            if(!game->server.isConnected())
            {
                game->server.connect();
                userMessage.setString("Ready!");
                messageClock.restart();
            }

        })); 
            connectThread->detach();
        }   
        else
        {
            game->client.init(); 
        }
    }
}

void PlayState::clean(std::shared_ptr<GU::Engin::Frame> frame)
{
    BP_LOG_TRACE(__FUNCTION__)
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       BP_LOG_FATAL_ERROR("Pointer should not be null")
       return;
    }
    gui.removeAllWidgets();

    //Remove ball sound
    if(ResourceManager::isLoaded(soundId::BALL))
        ResourceManager::remove(soundId::BALL);

//    ResourceManager::sound.remove(Sound::Id::MESSAGE);
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::sound.remove(Sound::Id::BALL);
    reset(pongFrame);
}

void PlayState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(engin);

    switch(event.type)
    {
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                {
                    if(gui.get("PanelPointer") == nullptr)
                    {
                        gui.removeAllWidgets();
                        StateBase::init(engin, frame);
                        tgui::Panel::Ptr cust(new Gui::PlayPanel());
                        std::shared_ptr<Gui::PlayPanel> p = std::dynamic_pointer_cast<Gui::PlayPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        EventManager::inst().post<GU::Evt::OnClick>(Gui::id::GENERAL_TAB);
                    }
                    else
                    {
                        tgui::Widget::Ptr widget = gui.get("PanelPointer");
                        gui.remove(widget);
                    }
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

void PlayState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event, std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::handleGUEvent(engin, event, frame);
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
        BP_LOG_FATAL_ERROR("Pointer should not be null")
        return;
    }

    switch(event->getId())
    {
        case EventId::CLICK:
        {
            std::shared_ptr<GU::Evt::OnClick> temp =  std::dynamic_pointer_cast<GU::Evt::OnClick>(event);
            if(temp)
            {
                switch(temp->m_buttonId)
                {
                    case Gui::id::OPTIONS_PANEL_BACK:
                    {
                        Game *game = static_cast<Game*>(&engin);
                        game->setPop(true);
                    }
                    break;
                }
            }
        }
    }
}

PlayState::~PlayState()
{
  BP_LOG_TRACE(__FUNCTION__)
}
