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


PlayState::PlayState(GU::Engin::Engin& newEngin, sf::RenderWindow &newWindow, std::shared_ptr<Frame> newFrame, DebugDraw &debugDraw, tgui::Gui &newGui, const StateId newId): StateBase(newEngin, newWindow, newFrame, debugDraw, newGui, newId)
{


    if(Settings::paddle1.input == "None")
        frame->leftPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*frame->leftPaddle)));
    else
        frame->leftPaddle->setInput(std::unique_ptr<Input>(new AI(*frame->leftPaddle)));


    if(Settings::paddle2.input  == "None")
        frame->rightPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*frame->rightPaddle)));
    else
        frame->rightPaddle->setInput(std::unique_ptr<Input>(new AI(*frame->rightPaddle)));

    systemPause(true);
    userMessage.setCharacterSize(34);
    userMessage.setPosition(sf::Vector2f(400, 300));
    reset();


}

void PlayState::HandleEvents(GU::Engin::Engin& engin, const float &deltaTime)
{
    UNUSED(deltaTime);
    
    if(window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            StateBase::sfEvent(engin, event);
            sfEvent(engin, event);
            gui.handleEvent(event);
        }
        frame->leftPaddle->handleInput(*frame->ball);
        frame->rightPaddle->handleInput(*frame->ball);
    }

    //GameUtilities event loop
    GU::Evt::EventPtr evtPtr;
    while(EventManager::inst().Poll((evtPtr)))
    {
        handleGUEvent(engin, evtPtr);
    }
}

void PlayState::Update(GU::Engin::Engin& engin, const float &deltaTime)
{
    const int SECONDS = 1;

    StateBase::Update(engin, deltaTime);

    if(!IsPaused())
    {
        if(!isSystemPaused())
        {
            frame->world->Step( timeStep, velocityIterations, positionIterations);
        }
        debugDraw.update();
        frame->ball->update();
        frame->ground->update();
        frame->celing->update();
        frame->leftWall->update();
        frame->rightWall->update();
        frame->leftPaddle->update();
        frame->rightPaddle->update();

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

void PlayState::Draw(GU::Engin::Engin& engin, const float &deltaTime)
{

    StateBase::Draw(engin, deltaTime);
    if(userMessage.getString() == "")
        window.draw(*frame->ball);
    window.draw(userMessage);


    window.display();

}

void PlayState::Init()
{
    Settings::stateId = StateId::PLAY_STATE; 
    StateBase::Init();

    if(!ResourceManager::sound.isLoaded(soundId::BALL))
        ResourceManager::sound.load(soundId::BALL, sf::String("Resources/Sounds/BallCollision.ogg"));

    
//    ResourceManager::sound.load(Sound::Id::MESSAGE, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BUTTON, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::sound.load(Sound::Id::BALL, "../Resources/Sounds/tone1.ogg");
//    ResourceManager::font.load("Header Font", "../Resources/Fonts/caviar-dreams/CaviarDreams.ttf");
//
//    userMessage.setFont(ResourceManager::font.get("Header Font"));
    Settings::paddle1.score = 0;
    Settings::paddle2.score = 0;
    paddle1Hud->setScore(0);
    paddle2Hud->setScore(0);
    centerText();
    reset();
}

void PlayState::Clean()
{
    gui.removeAllWidgets();
//
//    ResourceManager::sound.remove(Sound::Id::MESSAGE);
//    ResourceManager::sound.remove(Sound::Id::BUTTON);
//    ResourceManager::sound.remove(Sound::Id::BALL);
//    ResourceManager::font.remove("Header Font");

}

void PlayState::sfEvent(GU::Engin::Engin& engin, const sf::Event &event)
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
                        StateBase::Init();
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

void PlayState::handleGUEvent(GU::Engin::Engin& engin, GU::Evt::EventPtr event)
{
    StateBase::handleGUEvent(engin, event);
}

PlayState::~PlayState()
{

}
