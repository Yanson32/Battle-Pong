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
#include "Resources/ResourceManager.h"
#include "Events/Events.h"
#include "Macros.h"
#include "Gui/PlayPanel.h" 
#include "Gui/ButtonId.h"
#include "States/IntroState.h"
#include "Gui/IntroState/GeneralPanel.h"
#include "Gui/IntroState/ControlPanel.h"
#include "Gui/IntroState/VideoPanel.h"
#include "Gui/IntroState/SoundPanel.h"
#include "Gui/IntroState/NetworkPanel.h"
#include "Gui/IntroState/DevPanel.h"


PlayState::PlayState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId): StateBase(newEngin, newWindow, debugDraw, newGui, newId)
{




}

void PlayState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    UNUSED(deltaTime);
    
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    if(window.isOpen())
    {
        sf::Event event;

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
    while(EventManager::inst().Poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr, frame);
    }
}

void PlayState::Update(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    const int SECONDS = 1;

    StateBase::Update(engin, deltaTime, frame);

    if(!IsPaused())
    {
        if(!isSystemPaused())
        {
            pongFrame->world->Step( timeStep, velocityIterations, positionIterations);
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
            //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "3")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("2");
            centerText();
            messageClock.restart();
            //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "2")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("1");
            centerText();
            messageClock.restart();
            //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "1")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("Go!");
            centerText();
            messageClock.restart();
            //EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
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

void PlayState::Draw(GU::Engin::Engin& engin, const float &deltaTime, std::shared_ptr<GU::Engin::Frame> frame)
{

    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    StateBase::Draw(engin, deltaTime, frame);
    if(userMessage.getString() == "")
        window.draw(*pongFrame->ball);
    window.draw(userMessage);


    window.display();

}

void PlayState::Init(std::shared_ptr<GU::Engin::Frame> frame)
{
    StateBase::Init(frame);
    Settings::stateId = StateId::PLAY_STATE; 
    
    //Crate pong frame 
    std::shared_ptr<PongFrame> pongFrame = std::dynamic_pointer_cast<PongFrame>(frame);
    if(!pongFrame)
    {
       //GU::Evt::LogEvent("Pointer should not be null", GU::Evt::LogType::ERROR); 
       return;
    }        
    
    //Setup paddle 1 
    paddle1Hud->setScore(0);
    Settings::p1Score = 0;
    if(Settings::p1Input == "None")
        pongFrame->leftPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*pongFrame->leftPaddle)));
    else
        pongFrame->leftPaddle->setInput(std::unique_ptr<Input>(new AI(*pongFrame->leftPaddle)));

    //Setup paddle 2
    paddle2Hud->setScore(0);
    Settings::p2Score = 0;
    if(Settings::p2Input  == "None")
        pongFrame->rightPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*pongFrame->rightPaddle)));
    else
        pongFrame->rightPaddle->setInput(std::unique_ptr<Input>(new AI(*pongFrame->rightPaddle)));

    systemPause(true);
    userMessage.setCharacterSize(34);
    userMessage.setPosition(sf::Vector2f(400, 300));
    
    //Load ball sound
    if(!ResourceManager::sound.isLoaded(soundId::BALL))
        ResourceManager::sound.load(soundId::BALL, sf::String("Resources/Sounds/BallCollision.ogg"));

    
//    ResourceManager::sound.load(Sound::Id::MESSAGE, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");
//
//    userMessage.setFont(ResourceManager::font.get("Header Font"));
    centerText();
    reset(pongFrame);
}

void PlayState::Clean(std::shared_ptr<GU::Engin::Frame> frame)
{
    gui.removeAllWidgets();
    
    //Remove ball sound
    if(ResourceManager::sound.isLoaded(soundId::BALL))
        ResourceManager::sound.load(soundId::BALL, sf::String("Resources/Sounds/BallCollision.ogg"));
//
//    ResourceManager::sound.remove(Sound::Id::MESSAGE);
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::sound.remove(Sound::Id::BALL);
//    ResourceManager::font.remove("Header Font");

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
                        StateBase::Init(frame);
                        tgui::Panel::Ptr cust(new PlayPanel());
                        std::shared_ptr<PlayPanel> p = std::dynamic_pointer_cast<PlayPanel>(cust);
                        p->init(window.getSize().x, window.getSize().y);
                        gui.add(cust, "PanelPointer");
                        EventManager::inst().Post<GU::Evt::Click>(Button::id::GENERAL_TAB);
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
}

PlayState::~PlayState()
{

}
