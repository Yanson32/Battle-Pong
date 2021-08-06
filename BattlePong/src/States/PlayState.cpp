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
#include "Sounds/Id.h"
#include "Macros.h"
#include "Gui/PlayPanel.h" 
#include "Gui/ButtonId.h"
#include "States/IntroState.h"
#include "Gui/IntroState/GeneralPanel.h"
#include "Gui/IntroState/ControlPanel.h"
#include "Gui/IntroState/SoundPanel.h"
#include "Gui/IntroState/DevPanel.h"


PlayState::PlayState(GU::Engin::Engin& newEngin, const stateId newId): StateBase(newEngin, newId)
{


    if(Settings::paddle1.input == "None")
        leftPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*leftPaddle)));
    else
        leftPaddle->setInput(std::unique_ptr<Input>(new AI(*leftPaddle)));


    if(Settings::paddle2.input  == "None")
        rightPaddle->setInput(std::unique_ptr<Input>(new PlayerInput(*rightPaddle)));
    else
        rightPaddle->setInput(std::unique_ptr<Input>(new AI(*rightPaddle)));

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
        leftPaddle->handleInput(*ball);
        rightPaddle->handleInput(*ball);
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


    if(userMessage.getString() == "Ready!")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("3");
            centerText();
            messageClock.restart();
            EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "3")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("2");
            centerText();
            messageClock.restart();
            EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "2")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("1");
            centerText();
            messageClock.restart();
            EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
        }
    }
    else if(userMessage.getString() == "1")
    {
        if(messageClock.getElapsedTime().asSeconds() > SECONDS)
        {
            userMessage.setString("Go!");
            centerText();
            messageClock.restart();
            EventManager::inst().Post<GU::Evt::PlaySound>(Sound::Id::MESSAGE);
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

    if(userMessage.getString() == "")
        window.draw(*ball);
    StateBase::Draw(engin, deltaTime);
    window.draw(userMessage);


    window.display();

}

void PlayState::Init()
{
    StateBase::Init();
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
                        EventManager::inst().Post<Click>(Button::id::GENERAL_TAB);
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

    //EventManager::inst().Dispatch((evtPtr));
    switch(event->id)
    {

        case EventId::CLICK:
            { 
                std::shared_ptr<Click> temp =  std::dynamic_pointer_cast<Click>(event);
                if(temp)
                {
                    switch(temp->buttonId)
                    {
                        case Button::id::INTRO_PANEL:
                            engin.ChangeState<IntroState>(engin);
                            break;
                        case Button::id::GENERAL_TAB:
                        {
                            gui.removeAllWidgets();
                            StateBase::Init();
                            tgui::Panel::Ptr cust(new Gui::GeneralPanel(true));
                            std::shared_ptr<Gui::GeneralPanel> p = std::dynamic_pointer_cast<Gui::GeneralPanel>(cust);
                            p->init(window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
                        }
                        break;
                        case Button::id::CONTROLS_TAB:
                        {
                            gui.removeAllWidgets();
                            StateBase::Init();
                            tgui::Panel::Ptr cust(new Gui::ControlPanel(nullptr));
                            std::shared_ptr<Gui::ControlPanel> p = std::dynamic_pointer_cast<Gui::ControlPanel>(cust);
                            p->init(window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
                        }
                        break;
                        case Button::id::SOUND_TAB:
                         {
                            gui.removeAllWidgets();
                            StateBase::Init();
                            tgui::Panel::Ptr cust(new Gui::SoundPanel(nullptr));
                            std::shared_ptr<Gui::SoundPanel> p = std::dynamic_pointer_cast<Gui::SoundPanel>(cust);
                            p->init(window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
                        }
                        break;
                        case Button::id::DEV_TAB:
                         {
                            gui.removeAllWidgets();
                            StateBase::Init();
                            tgui::Panel::Ptr cust(new Gui::DevPanel());
                            std::shared_ptr<Gui::DevPanel> p = std::dynamic_pointer_cast<Gui::DevPanel>(cust);
                            p->init(debugDraw.GetFlags(), window.getSize().x, window.getSize().y);
                            gui.add(cust, "PanelPointer");
                        }
                    }

                }
            }
            
            break;
        
        case EventId::CHANGE_STATE:
        {
            std::shared_ptr<GU::Evt::ChangeState> temp =  std::dynamic_pointer_cast<GU::Evt::ChangeState>(event);
            switch(temp->id)
            {
                case stateId::CONNECT_STATE:
                    std::cout << "Playstate Connect state" << std::endl;
                break;

            }
        }
        break;
    }

}

PlayState::~PlayState()
{

}
